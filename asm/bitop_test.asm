INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    ;Bit Ops for r8.
    ;SET u3,r8
    set 7,b ;B should now contain 0x80.
    ;SWAP r8
    swap b ;B should now contain 0x08.
    ;BIT u3,r8
    bit 3,b ;Should unset Z.
    bit 7,b ;Should set Z.
    ;RES u3,r8
    res 3,b ;B should now contain 0.

    ;Bit Ops for [HL].
    ld hl, $8010 ;HL should contain 0x8010
    ld [hl], $f5 ;0x8010 in memory should contain 0xF5.
    ;SET u3,[HL]
    set 1,[HL] ;0x8010 in memory should now contain 0xF7.
    ;SWAP HL
    swap [hl] ;0x8010 in memory should now contain 0x7F.
    ;BIT u3,[HL]
    bit 0, [HL] ;Should unset Z flag.
    bit 7, [HL] ;Should set Z flag.
    ;RES u3,[HL]
    res 4, [HL] ;0x8010 should contain 0x6F.
    halt