INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    ld de, $1100
    ld bc, $00AA
    ld hl, $a000
    halt