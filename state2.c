#include <stddef.h>
#include <c88.h>
#include <stdint.h>
#include <timex.h>


// This is the entry point when the user presses the mode button and your
// application becomes active.
static uint8_t banner[] = {
    LCDBANNER_COL10,
        DM5_S, DM5_T, DM5_A, DM5_T, DM5_E, DM5_2, DM5_EXCLAMATION,
    LCD_END_BANNER
};

// This state is used when the user pulls the crown, indicating
// they want to change a setting.
// This state is for initialization, displaying a message, and so on.
// Once initiailzation is complete, request a change to set default state.
void set_banner_state_manager (void)
{
    switch (CORECurrentEvent) {
        case COREEVENT_STATEENTRY:
            lcdDispBannerMsg(&banner);

            // Request a timeout event.
            coreRequestTimeoutLoRes(1);
            break;
        case COREEVENT_TIMEOUTDONE_LOWRES:
            // The display is automatically cleared on state change, unless you
            // specifically use coreRequestStateChangeNoClearDisplay() instead.
            coreRequestStateChange(CORESETSTATE);
            break;
    }

    return;
}
