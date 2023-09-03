#include <stddef.h>
#include <c88.h>
#include <stdint.h>
#include <timex.h>

// The common code and background handler is special, it never gets swapped out.
// Give it a unique name so the locator can always find it.
#pragma renamesect

void background_handler (void)
{
    switch (COREBackgroundEvent) {
        // We are required to handle at least these events.
        // However, it is completely valid to just return.
        case COREEVENT_INIT:
        case COREEVENT_TASKEXIT:
        case COREEVENT_PEEK:
        case COREEVENT_APP_SHUTDOWN_FOR_COMM:
            break;
    }
    return;
}
