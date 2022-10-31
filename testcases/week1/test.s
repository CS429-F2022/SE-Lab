	.arch armv8-a
	.text
	.align	2
start:
    // Give x0 a value
	movz 	x0, #0x1234
    // Print x0
    eor 	x5, x5, x5
	nop
	nop
	nop
	mvn 	x5, x5
	nop
	nop
	nop
	stur	x0, [x5]
	nop
	nop
	nop

	ret
	.size	start, .-start
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
