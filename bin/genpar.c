#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <getopt.h>
#include <err.h>

#pragma pack(1)

struct params {
    uint8_t acboffmask;
    struct {
        uint8_t tod;
        uint8_t backup;
        uint8_t tzcheck;
        uint8_t timer;
        uint8_t stopwatch;
        uint8_t synchro;
    } reqs;
    uint8_t lcdflags1;
    uint8_t lcdflags2;
    uint16_t codeheapsz;
    uint16_t sysheapsz;
    uint16_t dbheapsz;
    uint8_t  coreacd;
    uint8_t apptype;
    uint8_t appinstance;
    uint16_t asdoff;
    uint16_t dboff;
    uint16_t smoff;     // State Manager, this is where the states are loaded
    uint16_t bgoff;     // BG handler, where common will be loaded
    uint16_t modename;
};

int main(int argc, char **argv)
{
    int opt;
    struct params data = {0};

    if (fread(&data, sizeof data, 1, stdin) != 1) {
        err(EXIT_FAILURE, "failed to read in parameters");
    }

    while ((opt = getopt(argc, argv, "c:")) != -1) {
        switch (opt) {
            case 'c': data.codeheapsz = strtoul(optarg, NULL, 0);
                      break;
            default:
                err(EXIT_FAILURE, "unrecognized argument");
        }
    }

    if (optind != argc) {
        err(EXIT_FAILURE, "more arguments than expected");
    }

    if (fwrite(&data, sizeof data, 1, stdout) != 1) {
        err(EXIT_FAILURE, "failed to write out parameters");
    }

    return 0;
}
