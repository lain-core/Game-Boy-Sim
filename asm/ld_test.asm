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
;       LD [r16],A      ld [bc], a 
;       LD [n16],A      ld [$8000], a 
;       LDH [n16],A     ldh [$FFFE], a
;       LDH A, [n16]    ldh a, [$FFFE]
;       LDH [C], A      ld [$FF00+C], a 
;       LDH A,[C]       ld a, [$FF00+C]
;       LD A,[r16]      ld a, [bc]
;       LD A,[n16]      ld a, [$8000]
;       LD [HLI],A      ld [hli], a
;       LD A,[HLI]      ld a, [hli]
;       LD [HLD],A      ld [hld], a
;       LD A,[HLD]      ld a, [hld]
    ; commands not tested yet


    ; ; testing - ld [r16], A
    ; ld a, $f5
    ; ld hl, $8003
    ; ld [hl], $55    
    ; ld a, [hld]
    ; ld [hl], $66
    ; ld a, [hld]
    ; halt