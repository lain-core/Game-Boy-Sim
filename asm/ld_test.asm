INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    ;LD r8,r8
    ;LD r8,n8
    ld a, $ff ;A should now contain 0xFF.
    ;LD r16,n16
    ld bc, $ffff ; BC should now contain 0xFFFF.
    ;LD [HL],r8
    ;LD [HL],n8
    ;LD r8,[HL]
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