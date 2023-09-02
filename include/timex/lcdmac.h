#ifndef __TIMEX_LCDMAC_H
#define __TIMEX_LCDMAC_H

__spoils(hl)    extern _asmfunc lcdClearDisplay(void);
__spoils(hl)    extern _asmfunc lcdDispBannerMsg(const void _near *msg);
__spoils(hl)    extern _asmfunc lcdDispMainDMLine1_HOLIDAY(void);
__spoils(hl)    extern _asmfunc lcdDispSmDMMsg_YOU_ROCK(void);
__spoils(hl)    extern _asmfunc lcdFillDisplay(void);
__spoils(hl)    extern _asmfunc lcdGetMainDMPixelStatus(int8_t x, int8_t y);
__spoils(hl)    extern _asmfunc lcdPixelScrollMsgLeft(int8_t pixels);

__spoils(hl) _inline _asmfunc lcdDispMainDMPixel(int8_t x, int8_t y)
{
    __use((int8_t, int8_t), (x, y));
#pragma asm_noflush
    LD      B, L
    CAR     lcdDispMainDMPixel
#pragma endasm
}

__spoils(hl) _inline _asmfunc lcdClrMainDMPixel(int8_t x, int8_t y)
{
    __use((int8_t, int8_t), (x, y));
#pragma asm_noflush
    LD      B, L
    CAR     lcdClrMainDMPixel
#pragma endasm
}

#endif
