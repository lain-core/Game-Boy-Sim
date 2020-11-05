INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    ;Bit Ops for r8.
    ;SET u3,r8
    set 7,b ;B should now contain 0x80.
    ;SWAP r8
    swap b ;B should now contain 0x08.
    ;BIT u3,r8
    bit 7,b ;Should set Z.
    bit 3,b ;Should unzet Z.
    ;RES u3,r8
    ;res 4,b ;B should now contain 0.

    ;Bit Ops for [HL].
    ;SET u3,[HL]
    ;SWAP HL
    ;BIT u3,[HL]
    ;RES u3,[HL]
    halt