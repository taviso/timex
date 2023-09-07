#ifndef __TIMEX_COREMAC_H
#define __TIMEX_COREMAC_H

__spoils(hl)    extern _asmfunc coreEnableSwitchReleaseEvents(void);
__spoils(b)     extern _asmfunc coreRequestModeChangeNext(void);
int8_t          extern _asmfunc coreRandom(void);
void            extern _asmfunc coreCommonBannerStateHandler(void);
__spoils(hl)    extern _asmfunc coreSuspendRingEvents(void);
__spoils(hl)    extern _asmfunc coreEnableRingEvents(void);
__spoils(b)     extern _asmfunc coreSuspendSwitchReleaseEvents(void);
__spoils(hl)    extern _asmfunc coreEnableSwitchReleaseEvents(void);
__spoils(hl)    extern _asmfunc coreCallModeName(int8_t state);
__spoils(b)     extern _asmfunc coreSetAutoreturnToPrimary(void);
__spoils(b)     extern _asmfunc coreClearAutoreturnToPrimary(void);

__spoils(b) _inline _asmfunc coreSetPopDownState(int8_t state)
{
    __use((int8_t), (state));
#pragma asm_noflush
    LD      B, A
    CAR     coreSetPopDownState
#pragma endasm
}

__spoils(b) _inline _asmfunc coreRequestStateChange(int8_t state)
{
    __use((int8_t), (state));
#pragma asm_noflush
    LD      B, A
    CAR     coreRequestStateChange
#pragma endasm
}

__spoils(b) _inline _asmfunc coreRequestStateChangeNoClearDisplay(int8_t state)
{
    __use((int8_t), (state));
#pragma asm_noflush
    LD      B, A
    CAR     coreRequestStateChangeNoClearDisplay
#pragma endasm
}

__spoils(b) _inline _asmfunc coreRequestTimeoutLoRes(int8_t secs)
{
    __use((int8_t), (secs));
#pragma asm_noflush
    LD      B, A
    car     coreRequestTimeoutLoRes
#pragma endasm
}

__spoils(b) _inline _asmfunc coreRequestTimeoutHiRes(int8_t timeout)
{
    __use((int8_t), (timeout));
#pragma asm_noflush
    LD      B, A
    car     coreRequestTimeoutHiRes
#pragma endasm
}

void _inline coreAllowKeys(int8_t keymask)
{
    COREKeyMask = keymask;
}

#endif
