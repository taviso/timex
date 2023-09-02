#include <stddef.h>
#include <c88.h>
#include <stdint.h>
#include <timex.h>

static const char _near * globe[] = {
   "    XXXX   ",
   "   X....X  ",
   "  X......X ",
   "  X......X ",
   "   X....X  ",
   "    XXXX   ",
   NULL
};

static const uint8_t kBaseX = 16;
static const uint8_t kBaseY = 6;

void show_message(void)
{
    int8_t x, y;
    int8_t i, j;
    uint8_t banner[] = {
        LCDBANNER_COL10,
        DM5_H, DM5_E, DM5_L, DM5_L, DM5_O, DM5_EXCLAMATION,
        LCD_END_BANNER
    };

    // Draw "hello!" using lcdDispBannerMsg macro
    lcdDispBannerMsg(&banner);

    // Draw the globe from the ascii art above.
    for (y = 0; globe[y]; y++) {
        for (x = 0; globe[y][x]; x++) {
            // A space character is cleared.
            if (globe[y][x] == ' ') {
                lcdClrMainDMPixel(x + kBaseX, y + kBaseY);
            // An X character is set.
            } else if (globe[y][x] == 'X') {
                lcdDispMainDMPixel(x + kBaseX, y + kBaseY);
            }
        }
    }

    // Any '.' character is randomized to look like animation.
    for (i = 0; i < 16; i++) {
        // Wait a short delay
        for (j = 0; j < 8; j++)
            hwLongDelay(56);

        // That might have taken a while, so let the watchdog know we're not
        // dead.
        hwResetWatchdog();

        // Look for '.' characters
        for (y = 0; globe[y]; y++) {
            for (x = 0; globe[y][x]; x++) {
                if (globe[y][x] != '.')
                    continue;
                if (coreRandom() & 1) {
                    lcdClrMainDMPixel(x + kBaseX, y + kBaseY);
                    continue;
                }
                lcdDispMainDMPixel(x + kBaseX, y + kBaseY);
            }
        }
    }

    return;
}
