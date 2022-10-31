	.arch armv8-a
	.text
	.align	2
start:

    movz x0, #1
    movz x1, #2
    nop
    nop
    subs x3, x0, x1
    nop
    nop
    b.eq .helper

.goback:
    nop
    nop
    nop

    // Print x0
    eor 	x5, x5, x5
    nop
    nop
    nop
	mvn 	x5, x5
    nop
    nop
    nop
	stur	x4, [x5]
    nop
    nop
    nop
    // correct: 1
    // incorrect: 65535
	ret

.helper:
    nop
    nop
    nop
    movz x0, #65535
    movz x1, #42069
    b .goback

	.size	start, .-start
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
