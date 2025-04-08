_check_keypad:
    movf what_button, w			;	we want to copy our last digit that was pressed into w

    bsf PORTB, 0			;	lets scan the first column of keys
    btfsc PORTB, 3			;	has the 1 key been pressed? if yes then
    movlw 1				;	copy decimal number 01 into w. but if not then continue on.
    btfsc PORTB, 4			;	has the 4 key been pressed? if yes then
    movlw 4				;	copy decimal number 04 into w. but if not then continue on.
    btfsc PORTB, 7			;	has the 7 key been pressed? if yes then
    movlw 7				;	copy decimal number 07 into w. but if not then continue on.
    btfsc PORTB, 6			;	has the * key been pressed? if yes then
    movlw 10				;	copy the decimal number 10 into w. but if not then continue on.
    bcf PORTB, 0			;	now we have finished scanning the first column of keys

    bsf PORTB, 1			;	let's scan the middle column of keys
    btfsc PORTB, 3			;	has the 2 key been pressed? if yes then
    movlw 2				;	copy decimal number 02 into w. but if not then continue on.
    btfsc PORTB, 4			;	has the 5 key been pressed? if yes then
    movlw 5				;	copy decimal number 05 into w. but if not then continue on.
    btfsc PORTB, 7			;	has the 8 key been pressed? if yes then
    movlw 8				;	copy the decimal number 08 into w. but if not then continue on.
    btfsc PORTB, 6			;	has the 0 key been pressed? if yes then
    movlw 0				;	copy decimal number 00 into w. but if not then continue on.
    bcf PORTB, 1			;	now we have finished scanning the middle column of keys

    bsf PORTB, 2			;	let's scan the last column of keys
    btfsc PORTB, 3			;	has the 3 key been pressed? if yes then
    movlw 3				;	copy decimal number 03 into w. but if not then continue on.
    btfsc PORTB, 4			;	has the 6 key been pressed? if yes then
    movlw 6				;	copy decimal number 06 into w. but if not then continue on.
    btfsc PORTB, 7			;	has the 9 key been pressed? if yes then
    movlw 9				;	copy decimal number 09 into w. but if not then continue on.
    btfsc PORTB, 6			;	has the # key been pressed? if yes then
    movlw 11				;	copy the decimal number 11 into w. but if not then continue on.
    bcf PORTB, 2			;	now we have finished scanning the last column of keys

    movwf what_button	
return			


