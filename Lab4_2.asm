;-------------------------------------------------------------------------------
; File       : Lab4_2.asm
; Function   :
; Description: Program traverses an input array of characters
;              to detect a character 'E'; exits when a NULL is detected
; Input      : The input string is specified in myStr
; Output     : The port P1OUT displays the number of E's in the string
; Author     : Samuel Sandlin
; Date       : 9/18/2020
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
str:		.cstring "4+2-1";

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
;--------------------------------------------****************************************
											;* R4 => memory of next char in expression
											;* R5 => Read from R4, used for comparison
											;* R6 => accumulator
											;****************************************
main:		mov.w	#str, R4				; Move expression into R4 | R4 <- M[str]
			clr.b	R6						;
            								; Read first char in expression
      		jmp		addition				; (Assumed to be positive)
											;
getNext:	mov.b	@R4+, R5				; Read next char in string from R4 into R5
			cmp		#0 , R5					; is R5 = NULL?
			jeq		end						; If(R5 == NULL) => end subroutine
			cmp		#'+', R5				; Is R5 a plus(+) in ASCII???
			jeq		addition				; If(R5 = '+') => Go to addition
			cmp		#'-', R5				; Is r5 a minus(-) in ASCII???
			jeq		subtract				; If(R5 = '-') => Go to subtract
											;
addition:	mov.b	@R4+, R5				; Read next char into R5 | R4++
			add.b	R5, R6					; R6 <- R6 + R5
			jmp		getNext					; get next char
											;
subtract:	mov.b	@R4+, R5				; Read next char into R5 | R4++
			sub.b	R5, R6					; R6 <- R6 - R5
			jmp		getNext					; get next char
											;
end:		sub.b	#0x30, R6				; Offset 30 from hex to ascii
			mov.b 	R6, &P2OUT				; mov R6 to P2OUT
			bis.w	#LPM4, SR				; Low Power Mode
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
            
