#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <getopt.h>
#include <err.h>

#pragma pack(1)

struct dbhdr {
    uint16_t allocsz;
    uint16_t dbsz;
    uint8_t  hdrsz;
    uint16_t nrecs;
};

int main(int argc, char **argv)
{
    int opt;
    struct dbhdr hdr = {0};
    uint16_t *recsize;
    uint8_t **records;


    while ((opt = getopt(argc, argv, "")) != -1) {
        switch (opt) {
            default:
                err(EXIT_FAILURE, "unrecognized argument");
        }
    }

    // Allocate space for the offsets.
    hdr.nrecs = argc - optind;
    recsize = calloc(sizeof(*recsize), hdr.nrecs);
    records = calloc(sizeof(*records), hdr.nrecs);

    // Initialize the sizes with the parts we know.
    hdr.dbsz  = sizeof(hdr);
    hdr.dbsz += hdr.nrecs * sizeof(uint16_t);
    hdr.hdrsz = sizeof(hdr.nrecs);

    // We need to read in all the data.
    for (int i = 0; i < hdr.nrecs; i++) {
        const char *filename = argv[optind + i];
        FILE *record;

        record = fopen(filename, "r");

        if (record == NULL) {
            err(EXIT_FAILURE, "failed to open record %s", filename);
        }

        // Get the record size
        if (fseek(record, 0, SEEK_END) != 0) {
            err(EXIT_FAILURE, "could not seek on record %s", filename);
        }

        recsize[i]  = ftell(record);
        records[i]  = malloc(recsize[i]);
        hdr.dbsz   += recsize[i];

        rewind(record);

        if (fread(records[i], recsize[i], 1, record) != 1) {
            err(EXIT_FAILURE, "failed to read in record %s", filename);
        }

        fclose(record);
    }

    hdr.allocsz = (((hdr.dbsz - 1) / 64) + 1) * 64;

    fwrite(&hdr, sizeof hdr, 1, stdout);

    // Now write out the record offsets, starting from the first.
    uint16_t offset = hdr.nrecs * sizeof(*recsize);

    for (int i = 0; i < hdr.nrecs; i++) {
        if (fwrite(&offset, sizeof offset, 1, stdout) != 1) {
            err(EXIT_FAILURE, "failed to write out record %d offset", i);
        }

        // Increment past the data
        offset += recsize[i];
    }

    // Now the data itself.
    for (int i = 0; i < hdr.nrecs; i++) {
        if (fwrite(records[i], recsize[i], 1, stdout) != 1) {
            err(EXIT_FAILURE, "failed to write out record %u data", i);
        }
    }

    // Now the padding.
    for (int i = hdr.dbsz; i < hdr.allocsz; i++)
        fputc(0, stdout);

    return 0;
}
