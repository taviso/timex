#include <stddef.h>
#include <c88.h>
#include <stdint.h>
#include <timex.h>

// This is the entry point when the user presses the mode button and your
// application becomes active.
static uint8_t banner[] = {
    LCDBANNER_COL10,
        DM5_S, DM5_T, DM5_A, DM5_T, DM5_E, DM5_0, DM5_EXCLAMATION,
    LCD_END_BANNER
};

void banner_state_manager (void)
{
    int j;

    // If you just use the default handler, it will display the mode name
    // from the parameter block for 1.5 seconds, and then switch to the
    // default state.
    switch (CORECurrentEvent) {
        case COREEVENT_STATEENTRY:
            coreSetPopDownState(COREDEFAULTSTATE);

            // Print my message.
            lcdDispBannerMsg(&banner);

            // Request a timeout event.
            coreRequestTimeoutLoRes(1);
            break;
        case COREEVENT_TIMEOUTDONE_LOWRES:
            // The display is automatically cleared on state change, unless you
            // specifically use coreRequestStateChangeNoClearDisplay() instead.
            coreRequestStateChange(COREDEFAULTSTATE);
            break;
        default:
            // Use the default handler for all other events.
            coreCommonBannerStateHandler();
            break;
    }

    return;
}
