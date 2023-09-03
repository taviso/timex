// vim:ff=dos

#ifndef __TIMEX_CORE_H
#define __TIMEX_CORE_H

_sfrbyte COREKeyMask _at(0xF0FD);
_sfrbyte COREInitializationASDAddress _at(0xF10C);

enum KEY_MASK {
    bCORESwitch1                    = 1 << 0,
    bCORESwitch2                    = 1 << 1,
    bCORESwitch3                    = 1 << 2,
    bCORECWSwitch                   = 1 << 3,
    bCORECCWSwitch                  = 1 << 4,
    bCOREELSwitch                   = 1 << 5,
    bCOREModeSwitch                 = bCORESwitch1,
    bCOREStopResetSwitch            = bCORESwitch2,
    bCOREStartSplitSwitch           = bCORESwitch3
};

#define COREALLOWALLSWITCHES (bCORESwitch1|bCORESwitch2|bCORESwitch3|bCORECWSwitch|bCORECCWSwitch|bCOREELSwitch)
#define COREALLOWALLSWITCHESEXCEPTINDIGLO (bCORESwitch1|bCORESwitch2|bCORESwitch3|bCORECWSwitch|bCORECCWSwitch)

enum STATE_INDEX {
    COREBANNERSTATE                 = 0x00,
    COREDEFAULTSTATE                = 0x01,
    CORESET1BANNERSTATE             = 0x02,
    CORESET1STATE                   = 0x03,
    COREPOPUPSTATE                  = 0x04,
    COREPASSWORDDEFAULTSTATE        = 0x05,
    COREPASSWORDSETBANNERSTATE      = 0x06,
    COREPASSWORDSETSTATE            = 0x07,
    COREMISCSTATE0                  = 0x05,
    COREMISCSTATE1                  = 0x06,
    COREMISCSTATE2                  = 0x07,
    COREMISCSTATE3                  = 0x08,
    COREMISCSTATE4                  = 0x09,
    COREMISCSTATE5                  = 0x0A,
    COREMISCSTATE6                  = 0x0B,
    COREMISCSTATE7                  = 0x0C,
    COREMISCSTATE8                  = 0x0D,
    COREMISCSTATE9                  = 0x0E,
    COREMISCSTATE10                 = 0x0F,
    COREMISCSTATE11                 = 0x10,
    COREMISCSTATE12                 = 0x11,
    COREMISCSTATE13                 = 0x12,
    COREMISCSTATE14                 = 0x13,
    COREMISCSTATE15                 = 0x14,
    COREMISCSTATE16                 = 0x15,
    COREMISCSTATE17                 = 0x16,
    COREMISCSTATE18                 = 0x17,
    COREMISCSTATE19                 = 0x18,
    COREMISCSTATE20                 = 0x19,
    CORESETBANNERSTATE              = CORESET1BANNERSTATE,
    CORESETSTATE                    = CORESET1STATE
};

#endif
