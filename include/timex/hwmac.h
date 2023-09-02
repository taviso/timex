#ifndef __TIMEX_HWMAC_H
#define __TIMEX_HWMAC_H

__spoils(a)     extern _asmfunc hwShortDelay(int8_t msec);
__spoils(ab)    extern _asmfunc hwLongDelay(int8_t msec);

void _inline hwResetWatchdog(void)
{
#pragma asm_noflush
    HW_RESET_WATCHDOG
#pragma endasm
}

#endif
