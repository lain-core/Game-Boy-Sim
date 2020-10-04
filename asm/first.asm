INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    di
    nop 
    scf
    ccf 
    cpl 
    daa
    ei 
    halt