INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    ;ADD HL,SP
    add hl, sp      ;HL should now contain $FFFE.
    ;ADD SP,e8
    ;needs to be done
    ;DEC SP
    dec sp          ;SP should now contain $FFFD.
    ;INC SP
    inc sp          ;SP should now contain $FFFE.
    ;LD SP,n16
    ld sp, $FFF0    ;SP should now contain $FFF0.
    ;LD [n16],SP
    ld [$8010], SP  ;0x8010 in memory should now contain $FFF0.  
    ;LD HL,SP+e8
    ;needs to be done
    ;LD SP,HL
    scf             ;Sets carry flag.
    ;PUSH AF
    push af         ;Pushes the current state on to the stack. (C is set)
    ccf             ;Complements the carry flag.
    ;POP AF
    pop af          ;Pops the state off of the stack. (C should be set)
    
    ld de, $beef    ;DE should now contain $BEEF.
    ;PUSH r16
    push de         ;DE should be pushed onto the stack.
    ;POP r16
    pop bc          ;BC should now contain $BEEF.
    halt