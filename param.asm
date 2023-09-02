include "../timex.inc"
include "common.equ"

defsect ".param", data at __lc_ub_asm
sect    ".param"

    ;============================================================
    ; ACB offset mask.
    ;============================================================

    ; Application System Data is located in heap.
    ; Other ACB entries are located either in ROM or EEPROM.
    db      bCOREAppSystemDataOffset


    ;============================================================
    ; Number of resources required.
    ;============================================================

    db      00h                         ; TOD
    db      00h                         ; Backup
    db      00h                         ; Time Zone Check
    db      00h                         ; Timer Resource
    db      00h                         ; Stopwatch Resource
    db      00h                         ; Synchro Timer Resource

    ;============================================================
    ; Flag(s) ownership.
    ;============================================================

    db      0                           ; LCD Flags 1
    db      0                           ; LCD Flags 2

    ;============================================================
    ; Heap size requirements.
    ;============================================================

    dw      0000H                         ; Code
    dw      0                             ; ASD
    dw      0                             ; ADD

    ;============================================================
    ; Application Configuration Data Byte.
    ;============================================================

    db      COREACDEEPROMAPP            ; Code is external.


    ;============================================================
    ; Application Unique ID.
    ;============================================================

    db      COREAPPTYPECOUNTER          ; Application type
    db      00h                         ; Application instance number

    ;============================================================
    ; ACB Parameters.
    ;============================================================

    dw      0       ; ASD address offset.
    dw      0       ; ADD address offset.
    dw      __lc_ub_asm                 ; App state manager address (Absolute Address).
    dw      _background_handler         ; App background handler address (Absolute Address).
    dw      lcdBannerMsg_NOTE           ; App mode name function address (Absolute Address).

