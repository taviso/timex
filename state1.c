#include <stddef.h>
#include <c88.h>
#include <stdint.h>
#include <timex.h>

void show_message(void);

static uint8_t banner[] = {
    LCDBANNER_COL10,
        DM5_S, DM5_T, DM5_A, DM5_T, DM5_E, DM5_1, DM5_EXCLAMATION,
    LCD_END_BANNER
};

void default_state_manager(void)
{
    int j;

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
            show_message();
            break;
        case COREEVENT_MODEDEPRESS:
            coreRequestModeChangeNext();
            break;
    }

    return;
}

