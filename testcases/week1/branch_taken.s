	.arch armv8-a
	.text
	.align	2
start:

    movz x0, #1
    movz x1, #1
    subs x3, x0, x1
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
    // correct: 65535
    // incorrect: 1
	ret
	
.helper:
    nop
    nop
    nop
    movz x0, #65535
    movz x1, #42069
    b .goback
    nop
    nop
    nop

    .size	start, .-start
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
