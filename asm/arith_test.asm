INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    ; XOR A, r8
    ; INC r16 
    ; INC r8
    ; DEC r8
    ; CP A, r8
    ; SUB A, r8
    ; ADD A, [HL]
    ; CP A, [HL]
    
    ld a, $01
    ld hl, $8000
    ld [hl], $00
    cp a, [hl]
    halt
