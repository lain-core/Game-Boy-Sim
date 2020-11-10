INCLUDE "hardware.inc"
SECTION "Header", ROM0
EntryPoint:
    ; working commands as of NOV 9
;       LD r8,r8        ld a, a
;       LD r8,n8        ld a, $f0
;       LD r16,n16      ld bc, $f0f0
;       LD [HL],r8      ld [hl], b
;       LD [HL],n8      ld [hl], $0f
;       LD r8,[HL]      ld c, [hl]
;       LD [r16],A      ld [bc], a -- fixed
;       LD [n16],A      ld [$8000], a -- fixed
;       LDH [n16],A     ldh [$FFFE], a
;       LDH A, [n16]    ldh a, [$FFFE]
    
    ; commands not tested yet

    ;LDH [C],A
    ;LD A,[r16]
    ;LD A,[n16]
    ;LDH A,[C]
    ;LD [HLI],A
    ;LD [HLD],A
    ;LD A,[HLI]
    ;LD A,[HLD]

    ; testing - ld [r16], A
    ld a, $f5
    scf 
    ld [$FF00+C], a 
    halt