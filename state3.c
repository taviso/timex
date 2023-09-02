#include <stddef.h>
#include <c88.h>
#include <stdint.h>
#include <timex.h>


static uint8_t banner[] = {
    LCDBANNER_COL10,
        DM5_S, DM5_T, DM5_A, DM5_T, DM5_E, DM5_3, DM5_EXCLAMATION,
    LCD_END_BANNER
};

void set_state_manager (void)
{
    static int position = 10;

    switch (CORECurrentEvent) {
        case COREEVENT_STATEENTRY:
            lcdDispBannerMsg(&banner);
            coreEnableRingEvents();
            break;
        case COREEVENT_CROWN_HOME:
            // The display is automatically cleared on state change, unless you
            // specifically use coreRequestStateChangeNoClearDisplay() instead.
            coreRequestStateChange(COREDEFAULTSTATE);
            break;
        case COREEVENT_CW_EDGE_TRAILING:
            lcdClearDisplay();
            banner[0] = 0x80 | --position;
            lcdDispBannerMsg(&banner);
            break;
        case COREEVENT_CCW_EDGE_TRAILING:
            lcdClearDisplay();
            banner[0] = 0x80 | ++position;
            lcdDispBannerMsg(&banner);
            break;
    }
    return;
}
