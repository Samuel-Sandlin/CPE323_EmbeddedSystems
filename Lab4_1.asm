;**********************************************************************************
; File       : Lab4_1.asm
; Function   : Counts the number of words and sentences in a string
; Description: Program traverses an input array of characters
;              to detect the number of words and sentences
; Input      : The input string is specified in string str
; Output     : NONE => Memory Browser
; Author     : Samuel Sandlin
; Date       : 9/18/2020
;**********************************************************************************
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            								;
;**********************************************************************************
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
str:	.cstring	"I am learning MSP430! I must count the words and sentences. Will I get it right?"											;
		.data
sent_count:		.int	0					; Variable for # of sentences in string
word_count:		.int	0					; Variable for # of words in string
;**********************************************************************************
											;
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.
											;
;**********************************************************************************
											;
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer
											;
;**********************************************************************************
; Main loop here
;**********************************************************************************
main:										;
			mov.w 	#str, R4				;	R4 <- Adress(str)
			clr.b	R6						;	Clear R6 ( word count register )
			clr.b	R7						; 	Clear R7 ( sentence count register )
											;
			mov.b	@R4+, R5				;	Prime Loop => provides initial check to see if string is
			cmp.b	#0, R5					; 	NULL string. Also acts as an offset correction since the
			jeq		end						; 	last word in any given sentence will not contain a space.
			inc.w	R6						;
			inc.w	word_count				;
											;
nextChar:	mov.b	@R4+, R5				;	R5 <- M[R4] , R4 ++ // Move character into R5 => increment R4
			cmp.b	#0, R5					; 	Check if NULL Char (end of string)
			jeq		end						; 	If null char => skip loop
											;	Also used as offset since the very last word will not have a space
			call	#checkW					; 	Call Subroutine to check if the
											; 	next char has completed a word.
;********************************************
;**********		CHECK WORD     ***************************************************
;********************************************
checkW:										; CHECK SPACE
			cmp.b	#' ', R5				; if( char == ' ') => increment words
			jne		checkP					; Else => check if sentence
			inc.w	R6						; Increment number of words => R++
			inc.w	word_count				;
			jmp		nextChar				; Go to next char
											;
;********************************************
;**********     CHECK SENTENCE     ***********************************************
;********************************************
checkP:										; CHECK PERIOD
			cmp.b	#'.', R5				; if( char == '.' ) => increment sentence
			jne		checkE					; Else => check if char is '!'
			inc.w	R7						;
			inc.w	sent_count				;
			jmp		nextChar				;
checkE:										; CHECK EXCLAMATION
			cmp.b	#'!', R5				; if( char == '!' ) => increment sentence
			jne		checkQ					; Else => check if char is '?'
			inc.w	R7						;
			inc.w	sent_count				;
			jmp		nextChar				;
checkQ:										; CHECK QUESTION
			cmp.b	#'?', R5				; if( char == '?' ) => increment sentence
			jne		nextChar				; Else => go to next char
			inc.w	R7						;
			inc.w	sent_count				;
			jmp		nextChar				; Found sentence => go to next char
			NOP								;
											;
;********************************************
;**********	INFINITE LOOP	******************************************************
;********************************************
end:		NOP								; Infinite Loop => END
			jmp		end						;
;*********************************************************************************
; Stack Pointer definition
;*********************************************************************************
            .global __STACK_END
            .sect   .stack
            
;*********************************************************************************
; Interrupt Vectors
;*********************************************************************************
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
