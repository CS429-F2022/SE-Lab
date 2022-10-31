    .arch armv8-a
	.text
	.align	2
start:
    // x1 is stack pointer
    // x2 is limit
    // x3 is counter
    // x4 is junk register (no xzr)

    EOR x1, x1, x1
    ADD x1, sp, #0
    MOVZ x5, #16
    SUBS x1, x1, x5
    EOR x2, x2, x2
    MOVK x7, #26
    ADDS x2, x2, x7
    EOR x3, x3, x3 
    ADD x3, x3, #1

    // loop
.INPUT_LOOP:
    SUBS x4, x3, x2
    B.EQ .START_SUM
    STUR x3, [x1]
    ADD x3, x3, #1
    SUBS x1, x1, x5
    B .INPUT_LOOP

.START_SUM:
    // x0 is running sum (and eventual result)
    // x1 is stack pointer
    // x2 is load destination
    // x3 is counter
    // x4 is junk register (no xzr)

    EOR x0, x0, x0
    EOR x2, x2, x2
    EOR x3, x3, x3
    MOVK x7, #27
    ADDS x3, x3, x7

    EOR x6, x6, x6
    MOVZ x5, #16
    MOVZ x7, #1
    SUBS x7, x6, x7
    // loop
.SUM_LOOP:
    SUBS x4, x3, x6
    B.EQ .EXIT
    ADDS x1, x1, x5
    LDUR x2, [x1]
    ADDS x0, x0, x2
    EOR x2, x2, x2
    ADDS x3, x3, x7
    B .SUM_LOOP

.EXIT:
    // Print x0
    // correct: 325
    EOR 	x5, x5, x5
	MVN 	x5, x5
	STUR	x0, [x5]
	RET

	.size	start, .-start
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
