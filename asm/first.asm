INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    di
    scf
    ccf 
    cpl 
    ei 
    nop
    daa
    daa
    halt