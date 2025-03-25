//-----------------------------
// Title: TempController
//-----------------------------
// Purpose: To count up or down based on button pressed while being able to 
// reset
// Dependencies: NONE
// Compiler: Pic-as (v3.0)
// Author: Logan Cacy
// OUTPUTS: PORTD
// INPUTS: RB0, RB1
// Versions:
//  	V6.2: 3/22/2025 - First version 
//-----------------------------
;---------------------
; Initialization
;---------------------
#include "./MyConfigFile.inc"
#include <xc.inc>

;---------------------
; Program Inputs
;---------------------
Inner_loop  equ 70 // in decimal
Middle_loop equ 50
Outer_loop  equ 50
 
;---------------------
; Program Constants
;---------------------
REG10   equ     10h   // in HEX
REG11   equ     11h
REG12	equ     12h

;---------------------
; Definitions
;---------------------
#define SWITCH    PORTD,1  
#define LED0      PORTD,0
#define LED1      PORTB,0
   
;---------------------
; Main Program
;---------------------
    PSECT absdata,abs,ovrld        ; Do not change
    
    ORG          0                ;Reset vector
    GOTO        _initialization

    ORG          0020H           ; Begin assembly at 0020H
 
_initialization: 
    RCALL _setupPortD
    RCALL _setupPortB
    
_main:
    ;PortB=1 count up, thus RB0=1
    ;PORTB=2 count down, thus RB1=1
    
    ;initialize REG0-F with values here
    MOVLW 0x3F ;0
    MOVWF 0x00
    MOVLW 0x06 ;1
    MOVWF 0x01
    MOVLW 0x5B ;2
    MOVWF 0x02
    MOVLW 0x4F ;3
    MOVWF 0x03
    MOVLW 0x66 ;4
    MOVWF 0x04
    MOVLW 0x6D ;5
    MOVWF 0x05
    MOVLW 0x7D ;6
    MOVWF 0x06
    MOVLW 0x07 ;7
    MOVWF 0x07
    MOVLW 0x7F ;8
    MOVWF 0x08
    MOVLW 0x67 ;9
    MOVWF 0x09
    MOVLW 0x77 ;A
    MOVWF 0x0A
    MOVLW 0x7C ;B
    MOVWF 0x0B
    MOVLW 0x39 ;C
    MOVWF 0x0C
    MOVLW 0x5E ;D
    MOVWF 0x0D
    MOVLW 0x79 ;E
    MOVWF 0x0E
    MOVLW 0x71 ;F
    MOVWF 0x0F
    MOVLW 0
    MOVWF FSR0L
    MOVWF FSR0H
    MOVFF 0x00, PORTD
    
    
_Again:
    CALL    loopDelay
    MOVFF   PORTB, 0x20
    MOVLW   1
    SUBWF   0x20, w
    BZ	    _countUp
    MOVLW   2
    SUBWF   0x20, w
    BZ	    _countDown
    MOVLW   3
    SUBWF   0x20, w
    BZ	    _clear
    GOTO    _Again


_countUp:
    INCF  FSR0L, F
    BCF FSR0L, 4
    BCF FSR0L, 5
    BCF FSR0L, 6
    BCF FSR0L, 7
    MOVF INDF0, w
    MOVWF PORTD
    GOTO  _Again

_countDown:
    DECF  FSR0L, F
    BCF FSR0L, 4
    BCF FSR0L, 5
    BCF FSR0L, 6
    BCF FSR0L, 7
    MOVF INDF0, w
    MOVWF PORTD
    GOTO  _Again
    
_clear:
    MOVLW 0
    MOVWF FSR0L
    MOVF INDF0, w
    MOVWF PORTD
    GOTO _Again
    
_setupPortD:
    BANKSEL	PORTD ;
    CLRF	PORTD ;Init PORTA
    BANKSEL	LATD ;Data Latch
    CLRF	LATD ;
    BANKSEL	ANSELD ;
    CLRF	ANSELD ;digital I/O
    BANKSEL	TRISD ;
    MOVLW	0b00000000 ;Set RD[7:0] as outputs
    MOVWF	TRISD 
    RETURN
    
_setupPortB:
    BANKSEL	PORTB ;
    CLRF	PORTB ;Init PORTA
    BANKSEL	LATB ;Data Latch
    CLRF	LATB ;
    BANKSEL	ANSELB ;
    CLRF	ANSELB ;digital I/O
    BANKSEL	TRISB ;
    MOVLW	0b11111111 ;Set RD[7:0] as inputs
    MOVWF	TRISB 
    RETURN    
    
loopDelay: 
    MOVLW       Inner_loop
    MOVWF       REG10
    MOVLW       Middle_loop
    MOVWF       REG11
    MOVLW	Outer_loop
    MOVWF	REG12
_loop1:
    DECF        REG10,1
    BNZ         _loop1
    MOVLW       Inner_loop ; Re-initialize the inner loop for when the outer loop decrements.
    MOVWF       REG10
    DECF        REG11,1 // middle loop
    BNZ        _loop1
    MOVLW	Middle_loop
    MOVWF       REG11
    DECF        REG12,1 // outer loop
    BNZ        _loop1
    RETURN