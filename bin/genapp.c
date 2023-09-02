#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

#pragma pack(1)

struct record {
    uint16_t    recordsz;
    uint8_t     reserved;
    uint8_t     code[];
};

struct header {
    uint16_t    totalsz;
    uint16_t    dbsz;
    uint8_t     appsz;
    uint16_t    nrecs;
    uint8_t     apphdr[];
};

static size_t fsize(FILE *stream)
{
    size_t size;
    fseek(stream, 0, SEEK_END);
    size = ftell(stream);
    rewind(stream);
    return size;
}

int main(int argc, char **argv)
{
    struct header hdr = {0};
    struct record **recs;
    uint16_t addr = sizeof(hdr) + sizeof(struct record);

    hdr.nrecs    = argc - 1;
    hdr.appsz    = sizeof(hdr.nrecs);
    hdr.totalsz  = sizeof(hdr);
    hdr.totalsz += hdr.nrecs * sizeof(uint16_t);        // EEPROM Address
    hdr.totalsz += hdr.nrecs * sizeof(struct record);   // Record Headers

    // Read in all records here.
    recs = calloc(sizeof(struct record *), argc);

    for (int i = 0; i < argc - 1; i++) {
        FILE *obj = fopen(argv[i + 1], "r");
        size_t objsize;

        objsize = fsize(obj);

        recs[i] = malloc(sizeof(struct record) + objsize);
        recs[i]->recordsz = objsize + sizeof(struct record);
        recs[i]->reserved = !!i;

        // Read in data.
        fread(recs[i]->code, objsize, 1, obj);

        // Include size of code in header.
        hdr.totalsz += objsize;

        // No longer need the code.
        fclose(obj);
    }

    hdr.dbsz     = hdr.totalsz;
    hdr.totalsz += 64 - (hdr.dbsz % 64);

    fwrite(&hdr, sizeof hdr, 1, stdout);

    for (int i = 0; i < argc - 1; i++) {

        fwrite(&addr, sizeof(addr), 1, stdout);

        addr += recs[i]->recordsz;
    }

    for (int i = 0; i < argc - 1; i++) {
        fwrite(recs[i], recs[i]->recordsz, 1, stdout);
        free(recs[i]);
    }

    for (int i = hdr.dbsz; i < hdr.totalsz; i++) {
        fputc(0, stdout);
    }

    free(recs);
    return 0;
}
