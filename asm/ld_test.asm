INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    ld b, $04
    ;LD r8,r8
    ld a, b
    ;LD r8,n8
    ld a, $ff ;A should now contain 0xFF.
    ;LD r16,n16
    ld hl, $a000 ; HL should now contain 0xA000.
    ;LD [HL],r8
    ld [HL], a ; 0xA000 in memory should now contain 0xFF.
    ;LD [HL],n8
    ld [HL], $0A ; 0xA000 in memory should now contain 0x0A.
    ;LD r8,[HL]
    ld b, [hl] ;B should now contain 0x0A.
    ;LD [r16],A
    ;LD [n16],A
    ;LDH [n16],A
    ;LDH [C],A
    ;LD A,[r16]
    ;LD A,[n16]
    ;LDH A,[n16]
    ;LDH A,[C]
    ;LD [HLI],A
    ;LD [HLD],A
    ;LD A,[HLI]
    ;LD A,[HLD]
    halt