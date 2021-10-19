	.code32
	.text
	.global memset
	.global memsetw


//memset(uint8*,uint8,uint32)
//memset(3,2,1) -- calling convention
memset:

_memset:
    /* clear required registers */
    xor %eax,%eax
    xor %ecx,%ecx

    /* fetch parsed parameters */
    /* fetches 3 parameters from the stack */

    /* looping */
    mov 0xc(%esp),%ecx

    /* uint8 *c the character */
    movb 0x8(%esp),%al

    /* uint8 *dest */
    mov 0x4(%esp),%edi

    repnz stosb

    /* return value */
    mov 0x4(%esp),%eax
    ret


memsetw:

_memsetw:
    /* clear required registers */
    xor %eax,%eax
    xor %ecx,%ecx

    /* fetch parsed parameters */
    /* fetches 3 parameters from the stack */

    /* looping */
    mov 0xc(%esp),%ecx

    /* uint16 *cc the two characters */
    movw 0x8(%esp),%ax

    /* uint8 *dest */
    mov 0x4(%esp),%edi

    repnz stosw

    /* return value */
    mov 0x4(%esp),%eax
    ret
