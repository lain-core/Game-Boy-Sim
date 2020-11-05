INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    ld hl, $ff00
    add a, $de
    and a, $0
    ld [$ff00], a
    halt