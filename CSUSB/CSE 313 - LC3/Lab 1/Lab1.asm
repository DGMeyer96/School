;Class:CSE 313 Machine Organization Lab
;Section: 02
;Instructor: Taline Georgiou
;Term: Summer 2019
;Name(s): Daniel Meyer
;Lab#1: ALU Operations
;Description:	This is the first lab assignment of the class.  For this
;	lab we were tasked with calculating a series of simple arithmatic
;	equations from addition and subtraction, to NOT and OR logic 
;	operands.
;		The lab helps familiarize with managing memory and 
;	registers.  The lab emphasized the use of the LDR load command
;	as well as the STR store command.  Another requirement of the 
;	lab was to store each result in specific memory locations.  The
;	lab also required we pull data from external files for use in the
;	main lab program.

	.ORIG x3000

	;Set initial X and Y
	LEA R2, xFF	;R2 <- x3000 + x1 + xFF (= x3100)
	LDR R1, R2, x0	;X is in x3100, R1 <- x3100(R2)
	LDR R3, R2, x1	;Y is in x3101, R3 <- x3100(R2) + x1

	;X + Y
	ADD R4, R1, R3	;X + Y -> R4
	STR R4, R2, x2	;Store contents of R4 into x3102 (x3100 + x2)
	

	;X AND Y
	AND R4, R1, R3	;X AND Y -> R4
	STR R4, R2, x3	;Store R4 into x3103

	;X OR Y
	NOT R5, R1	;NOT(X)
	NOT R6, R3	;NOT(Y)
	AND R4, R5, R6	;X AND Y
	NOT R4, R4	;X OR Y
	STR R4, R2, x4	;Store R4 into x3104

	;NOT(X)
	NOT R4, R1	;NOT(X) -> R4
	STR R4, R2, x5	;Store R4 into x3105

	;NOT(Y)
	NOT R4, R3	;NOT(Y) -> R4
	STR R4, R2, x6	;Store R4 into x3106

	;X + 3
	ADD R4, R1, #3	;X + 3 -> R4
	STR R4, R2, x7	;Store R4 into x3107

	;Y - 3
	ADD R4, R3, #-3	;Y - 3 -> R4
	STR R4, R2, x8	;Store R4 into x3108

	;Z = 0 if X is even, Z = 1 if X is odd
	AND R4, R1, x0001	;R4 will have least significant it of R1
	STR R4, R2, x9	;Store contents of R4 into x3109	

	HALT
	.END