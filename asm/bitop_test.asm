INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    add a,$C2
    inc b ;b will be incremented.
    set 2,a ;Value should now be C6.
    or a,b ;Value should now be C7.
    inc sp
    halt