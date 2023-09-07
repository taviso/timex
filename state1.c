#include <stddef.h>
#include <c88.h>
#include <stdint.h>
#include <stdbool.h>
#include <timex.h>

#define MAX_DB_CHARS 8

void show_message(void);
bool print_database_chars(void);

static uint8_t banner[] = {
    LCDBANNER_COL10,
        DM5_S, DM5_T, DM5_A, DM5_T, DM5_E, DM5_1, DM5_EXCLAMATION,
    LCD_END_BANNER
};

void default_state_manager(void)
{
    static int8_t press = 0;

    switch (CORECurrentEvent) {
        case COREEVENT_STATEENTRY:
            coreEnableSwitchReleaseEvents();
            coreAllowKeys(COREALLOWALLSWITCHES);
            lcdDispBannerMsg(&banner);
            break;
        case COREEVENT_CROWN_SET:
            coreRequestStateChange(CORESETBANNERSTATE);
            break;
        case COREEVENT_STARTSPLITDEPRESS:
            // On alternate presses, demonstrate reading a database.
            if (press++ % 2) {
                print_database_chars();
                break;
            }
            // Second press, display message.
            show_message();
            break;
        case COREEVENT_MODEDEPRESS:
            coreRequestModeChangeNext();
            break;
    }

    return;
}

bool print_database_chars(void)
{
    uint8_t i;
    uint8_t dbstr[MAX_DB_CHARS];

    dbOpenFile();

    // There must be at least two records (column, end)
    if (DBNumberOfRecords > MAX_DB_CHARS || DBNumberOfRecords < 2) {
        dbCloseFile();
        return false;
    }

    // Reach each record
    for (i = 0; i < DBNumberOfRecords; i++) {
        dbReadRecordRandomVar(&dbstr[i], i, 1);
    }

    // The last entry must be an end marker.
    if (dbstr[i - 1] != LCD_END_BANNER) {
        dbCloseFile();
        return false;
    }

    dbCloseFile();
    lcdClearDisplay();
    lcdDispBannerMsg(&dbstr);
    return true;
}
