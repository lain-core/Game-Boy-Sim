INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    jr Demo1
Demo1End:
    scf
    jr nc, EntryPoint  ;should fail bc C is unset.
    ccf
    jr nc, End
    ;jr -1
    ;nop 
    ;nop
    nop
End:
    halt

Demo1:
    jr Demo1End
; working jump instructions
; call
; call cc
; ret
; reti
; jr
; jr c, n16
; jr z, n16
; jr nz, n16
; jr nc, n16
