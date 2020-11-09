INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    ld a, $f0       ;load ff into register a 
    ld b,a          ;copy contents of register a into b
    ld bc, $0b0c    ;load ff into registers d and e
    ld de, $0d0e    ;load ff into registers d and e
    ld hl, $8010    ;load ff into registers d and e
    ld [hl], a      ;store value in register d into byte pointed to by register d
    inc l 
    ld [hl], $ab
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