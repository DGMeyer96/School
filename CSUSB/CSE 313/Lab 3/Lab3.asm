;Class:CSE 313 Machine Organization Lab
;Section: 02
;Instructor: Taline Georgiou
;Term: Summer 2019
;Name(s): Daniel Meyer
;Lab#3: Days of the Week
;Description:	This prgram prompts for an integer between 0 and 6
;and returns the day of the week that corresponds to the integer
;supplied by the user.  Text is dispalyed to the console using PUTS
;and character input is retrieved using GETC.  If the integer 
;given given by the user is out of bounds, the program ends, if not
;the program will continue to loop.
;
;		In order to execute the program you must load
;Lab3.asm.  Once loaded run the program and you will be prompted to
;enter a number.  Once the number is provided, the program will 
;convert the number from its ASCII value into an integer and then
;check the number to see if it is less than 7.  If it is, the 
;program will dispaly the corresponding day of the week, loop and
;prompt for another integer.  If it is greater than or equal to 7
;the program will jump to HALT and end.  All data is stored after 
;HALT and before .END.


	.ORIG x3000
RESTART	LEA R0, PROMPT	;Found in 3.2.2
	PUTS		;Print to console
	GETC		;Get one char input, stored in R0
	
	;Change char input to actual value
	ADD R3, R0, #0	;
	ADD R3, R3, #-16;
	ADD R3, R3, #-16;
	ADD R3, R3, #-16;Subtract 48, ASCII value of 0

	;Check if number entered was >=7
	;If >=7 jump to HALT
	AND R4, R4, #0	;Clear R4 since program loops
	ADD R4, R4, #-7	;R4 = -7
	AND R5, R5, #0	;Clear R5 since program loops
	ADD R5, R3, R4	;Check if input is >=7 (input - 7, neg < 7, zero/pos >=7)
	BRzp BAD	;Break to end if >=7

	;Load list of days
	LEA R0, DAYS	;R0 <- Sunday
	ADD R3, R3, 0	;Sunday = 0
LOOP	BRz DISPLAY	;Break to display day on screen
	ADD R0, R0, #10	;R0 <- Next Day
	ADD R3, R3, #-1	;Decrement loop
	BR LOOP		;Trigger loop

DISPLAY	PUTS		;Display the day of the week
	LEA R0, LF	;Blank Line Feed
	PUTS		;Print blank line

	BR RESTART	;Go back to beginning of program

BAD	HALT

PROMPT	.STRINGZ "Please enter number: "
	;Adding blank spaces so that each date has same length (9 + 1 for NULL)
DAYS	.STRINGZ "Sunday   "
	.STRINGZ "Monday   "
	.STRINGZ "Tuesday  "
	.STRINGZ "Wednesday"
	.STRINGZ "Thursday "
	.STRINGZ "Friday   "
	.STRINGZ "Saturday "
LF	.FILL x000A

	.END