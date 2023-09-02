#include <stddef.h>
#include <c88.h>
#include <stdint.h>
#include <timex.h>

// The common code and background handler is special, it never gets swapped out.
// Give it a unique name so the locator can always find it.
#pragma renamesect

void background_handler (void)
{
    return;
}

void sleep (int n)
{
    return;
}
