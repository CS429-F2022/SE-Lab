	.arch armv8-a
	.text
	.align	2
start:
	movz x0, #74
    movz x1, #18

    nop
    nop
    nop

    // Add the two registers together
    adds x2, x0, x1

    nop
    nop
    nop

    // Print x2
    // correct: 92
    eor 	x5, x5, x5
    nop
    nop
    nop
	mvn 	x5, x5
    nop
    nop
    nop
	stur	x2, [x5]
    nop
    nop
    nop

	ret
	.size	start, .-start
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
