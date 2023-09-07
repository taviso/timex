// vim:ff=dos

#ifndef __TIMEX_DBMAC_H
#define __TIMEX_DBMAC_H

// Note that you don't *have* to use the db api, you could just
// call hwEepromRead() if you want precise control.
//
// You can think of the eeprom as a filesystem. It is not memory mapped,
// you have to ask the kernel to transfer an eeprom address to ram for you.
//

_sfrword DBExternalBaseAddress _at(0xF000);
_sfrword DBNumberOfRecords _at(0xF002);
_sfrbyte DBSizePerRecord _at(0xF004);
_sfrword DBInternalMemoryAddress _at(0xF005);
_sfrword DBExternalMemoryAddress _at(0xF007);
_sfrbyte DBLengthLo _at(0xF00B);
_sfrbyte DBRecordOffset _at (0xF00F);
_sfrword DBRecordNumber _at (0xF00D);

void extern _asmfunc dbCloseFile(void);

void _inline _asmfunc dbOpenFile(void)
{
    DBExternalMemoryAddress = CORECurrentADDAddress;
#pragma asm_noflush
    CAR     dbOpenFile
#pragma endasm
}

void _inline _asmfunc dbOpenFileLinkList(void)
{
    DBExternalMemoryAddress = CORECurrentADDAddress;
#pragma asm_noflush
    CAR     dbOpenFile
#pragma endasm
}

void _inline _asmfunc dbReadApplicationInfoHeader(const void *dst,
                                                  uint8_t len,
                                                  uint8_t off)
{
    DBInternalMemoryAddress = (unsigned) dst;
    DBLengthLo = len;
    DBRecordOffset = off;
#pragma asm_noflush
    CAR     dbReadApplicationInfoHeader
#pragma endasm
}

void _inline _asmfunc dbWriteApplicationInfoHeader(const void *dst,
                                                   uint8_t len,
                                                   uint8_t off)
{
    DBInternalMemoryAddress = (uint16_t) dst;
    DBLengthLo = len;
    DBRecordOffset = off;
#pragma asm_noflush
    CAR     dbWriteApplicationInfoHeader
#pragma endasm
}

uintptr_t _inline _asmfunc dbGetAbsoluteAddressOfRecordRandomVar(uint16_t recnum)
{
    DBRecordNumber = recnum;
#pragma asm_noflush
    CAR dbGetAbsoluteAddressOfRecordRandomVar
#pragma endasm
}

void _inline _asmfunc dbWriteRecord(intptr_t dst, const void *src, uint8_t len)
{
    DBInternalMemoryAddress = (uint16_t) src;
    DBExternalMemoryAddress = dst;
    DBLengthLo = len;
#pragma asm_noflush
    CAR dbWriteRecord
#pragma endasm
}

void _inline _asmfunc dbWriteRecordWithOffset(intptr_t dst,
                                              const void *src,
                                              uint8_t len,
                                              uint8_t off)
{
    DBInternalMemoryAddress = (uint16_t) src;
    DBExternalMemoryAddress = dst;
    DBLengthLo = len;
    DBRecordOffset = off;
#pragma asm_noflush
    CAR dbWriteRecordWithOffset
#pragma endasm
}

void _inline _asmfunc dbWriteRecordRandomFix(const void *src,
                                             uint16_t recnum,
                                             uint8_t len)
{
    DBInternalMemoryAddress = (uint16_t) src;
    DBRecordNumber = recnum;
    DBLengthLo = len;
#pragma asm_noflush
    CAR dbWriteRecordRandomFix
#pragma endasm
}

void _inline _asmfunc dbWriteRecordWithOffsetRandomFix(const void *src,
                                                       uint16_t recnum,
                                                       uint8_t len,
                                                       uint8_t off)
{
    DBInternalMemoryAddress = (uint16_t) src;
    DBRecordNumber = recnum;
    DBLengthLo = len;
    DBRecordOffset = off;
#pragma asm_noflush
    CAR dbWriteRecordRandomFix
#pragma endasm
}

void _inline _asmfunc dbWriteRecordRandomVar(const void *src,
                                             uint16_t recnum,
                                             uint8_t len)
{
    DBInternalMemoryAddress = (uint16_t) src;
    DBRecordNumber = recnum;
    DBLengthLo = len;
#pragma asm_noflush
    CAR dbWriteRecordRandomVar
#pragma endasm
}

void _inline _asmfunc dbWriteRecordWithOffsetRandomVar(const void *src,
                                                       uint16_t recnum,
                                                       uint8_t len,
                                                       uint8_t off)
{
    DBInternalMemoryAddress = (uint16_t) src;
    DBRecordNumber = recnum;
    DBLengthLo = len;
    DBRecordOffset = off;
#pragma asm_noflush
    CAR dbWriteRecordWithOffsetRandomVar
#pragma endasm
}

void _inline _asmfunc dbReadRecord(uintptr_t src, void *dst, uint8_t len)
{
    DBExternalMemoryAddress = src;
    DBInternalMemoryAddress = (uint16_t) dst;
    DBLengthLo = len;
    // This pointer can be modified.
    __useptr(dst);
#pragma asm_noflush
    CAR dbReadRecord
#pragma endasm
}

void _inline _asmfunc dbReadRecordWithOffset(void *dst,
                                             uintptr_t src,
                                             uint8_t len,
                                             uint8_t off)
{
    DBExternalMemoryAddress = src;
    DBInternalMemoryAddress = (uint16_t) dst;
    DBLengthLo = len;
    DBRecordOffset = off;
    // This pointer can be modified.
    __useptr(dst);
#pragma asm_noflush
    CAR dbReadRecordWithOffset
#pragma endasm
}

void _inline _asmfunc dbReadRecordRandomFix(void *dst,
                                            uint16_t recnum,
                                            uint8_t len)
{
    DBInternalMemoryAddress = (uint16_t) dst;
    DBRecordNumber = recnum;
    DBLengthLo = len;
    // This pointer can be modified.
    __useptr(dst);
#pragma asm_noflush
    CAR dbReadRecordRandomFix
#pragma endasm
}

void _inline _asmfunc dbReadRecordWithOffsetRandomFix(void *dst,
                                                      uint16_t recnum,
                                                      uint8_t len,
                                                      uint8_t off)
{
    DBInternalMemoryAddress = (uint16_t) dst;
    DBRecordNumber = recnum;
    DBLengthLo = len;
    DBRecordOffset = off;
    // This pointer can be modified.
    __useptr(dst);
#pragma asm_noflush
    CAR dbReadRecordRandomFix
#pragma endasm
}

void _inline _asmfunc dbReadRecordRandomVar(void *dst,
                                            uint16_t recnum,
                                            uint8_t len)
{
    DBInternalMemoryAddress = (uint16_t) dst;
    DBRecordNumber = recnum;
    DBLengthLo = len;

    // This pointer can be modified.
    __useptr(dst);
#pragma asm_noflush
    CAR dbReadRecordRandomVar
#pragma endasm
}

void _inline _asmfunc dbReadRecordWithOffsetRandomVar(void *dst,
                                                      uint16_t recnum,
                                                      uint8_t len,
                                                      uint8_t off)
{
    DBInternalMemoryAddress = (uint16_t) dst;
    DBRecordNumber = recnum;
    DBLengthLo = len;
    DBRecordOffset = off;
    // This pointer can be modified.
    __useptr(dst);
#pragma asm_noflush
    CAR dbReadRecordWithOffsetRandomVar
#pragma endasm
}

void _inline _asmfunc * dbRemoveRecordLinkList(void *head, void *rec)
{
    __use((void *, void *), (head, rec));
#pragma asm_noflush
    // FIXME
#pragma endasm
    return NULL;
}

void _inline _asmfunc * dbInsertRecordLinkList(void *head, void *rec)
{
    __use((void *, void *), (head, rec));
#pragma asm_noflush
    // FIXME
#pragma endasm
    return NULL;
}

void _inline _asmfunc * dbLocateInsertionBySizeLinkList(void *head, void *rec)
{
    __use((void *, void *), (head, rec));
#pragma asm_noflush
    // FIXME
#pragma endasm
    return NULL;
}

#endif
