INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    
    ld hl $FF40
    ld [hl] $81
    ld hl, $8800
    ld [hli], $12
    ld [hl], 34
    halt
