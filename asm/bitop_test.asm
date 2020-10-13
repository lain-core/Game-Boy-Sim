INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    add a,$C2
    bit 2,a ;Value should now be C3.
    halt