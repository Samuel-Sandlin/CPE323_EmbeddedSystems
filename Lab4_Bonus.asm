;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
		.data
str:		.cstring "I am Learning MSP430"	;
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
main:		mov.b	&str+1,	R4				; Move starting adress into R4

nextChar:	mov.b	@R4+,	R5				; Read first char into R5 | R4 ++
			cmp		#0	,	R5				; if(char == NULL) => END
			jeq		end						;
			cmp		#'a',	R5				; ***** IF (a <= R5 <= z) *****
            jl		nextChar				; if(R5 < 'a') => go next
			cmp		#'{',	R5				; if(R5 < '{') => toUpper
			jl		toUpper					; ELSE => go next
			jmp		nextChar				;
											;
toUpper:	sub		#0x20,	R5				; Offset lower to upper in ascii
			mov.b	R5,		-1(R4)			; Move offset R5 back into M[R4]
			jmp		nextChar				;
											;
end:		bis.w	#LPM4, SR				; Low Power Mode
			nop								;
;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
