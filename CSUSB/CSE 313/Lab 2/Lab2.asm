;Class:CSE 313 Machine Organization Lab
;Section: 02
;Instructor: Taline Georgiou
;Term: Summer 2019
;Name(s): Daniel Meyer
;Lab#2: Arithmetic Functions
;Description:	This lab introduces basic arithmetic functions
;	such as absolute value and subtraction.  Subtraction 
;	is done by adding the 2's complement of the value to
;	be subtracted as there is no subtract function in LC-3.
;	Absolute value uses the Break function when the value 
;	is positive, and the 2's complement is used when
;	the value is negative.
;		The results are store in memory locations x3120
;	thru x3125.  There are 5 data sets for testings.  These
;	Data#.asm files should be loaded prior to Lab2.asm.  
;	Once both files are loaded results of each function are
;	stored in x3122 thru x3125 with the data values for X 
;	and Y stored in x3120 and x3121 respectively.

	.ORIG x3000
	LDI R0, X	;
	LDI R1, Y	;

	;X - Y
	NOT R3, R1	;2's complement
	ADD R3, R3, #1	;-Y
	ADD R3, R0, R3	;X + (-Y)
	STI R3, XSUBY	;Store result

	;|X|
	ADD R2, R0, #0	;
	BRzp abs1	;Break if >=0
	NOT R2, R2	;2's complement
	ADD R2, R2, #1	;|X|
	STI R2, absX	;Store result

abs1	STI R2, absX	;

	;|Y|
	ADD R3, R1, #0	;
	BRzp abs2	;Break if >=0
	NOT R3, R3	;2's complement
	ADD R3, R3, #1	;|Y|
	STI R3, absY	;Store result

abs2	STI R3, absY	;

	;|X| - |Y|
	NOT R4, R3	;2's complement
	ADD R4, R4, #1	;-|Y|
	ADD R4, R2, R4	;|X| + (-|Y|)
	BRz store	;if =0, Z = 0
	BRp pos		;if >0, go to pos
	;Negative
	AND R4, R4, #0	;clear R4
	ADD R4, R4, #2	;R4 = 2, Z = 2
	BR store	;Break to store

	;Positive
pos	AND R4, R4, #0	;clear R4
	ADD R4, R4, #1	;R4 = 1, Z = 1
	
store	STI R4, Z	;Z = R4

	HALT

X	.FILL x3120
Y	.FILL x3121
XSUBY	.FILL x3122
absX	.FILL x3123
absY	.FILL x3124
Z	.FILL x3125

	.END