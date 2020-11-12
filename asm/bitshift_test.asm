INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    nop 
    ld a, $FE
    rla
    halt