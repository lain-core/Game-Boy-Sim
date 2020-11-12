INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    nop 
    nop 
    call Demo1 ;Should call and return.
    ; nop 
    ; nop
    ; scf ;Sets Carry Flag.
    ; nop 
    ; call c, Demo2 ;Should call to Demo2 and ret                  urn with RETI
    ; jp c, Demo1   ;Should call to Demo1 and return.
    ; ;jr c, 2       ;Should jump over the NOP to ccf.
    ; nop
    ; ccf 
    ; call c, Demo1 ;Should fail to call Demo1.
    ; jp c, Demo1   ;Should fail to call Demo1.
    ; ;jr c, 2       ;should fail to jump.
    ; ld hl, Demo1  ;load the address of Demo1 into HL.
    ; jp hl         ;should jump to Demo1 and return.
    ; jp Demo1      ;should jump directly to Demo1.
    ; ;;jr 2          ;should jump over NOP onto next jump.          
    ; nop
    ; rst $30
    halt
    
Demo1:
    ret
; Demo2:
;     reti
;     halt