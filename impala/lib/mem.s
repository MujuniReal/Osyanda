.code32
.text
.global memset

memset:

_memset:
    /* clear required registers */
    xor %eax,%eax
    xor %ecx,%ecx

    /* fetch parsed parameters */
    /* fetches 3 parameters from the stack */

    /* count up */
    mov 0xc(%esp),%ecx

    /* uint8 *c the character */
    movb 0x8(%esp),%al

    /* uint8 *dest */
    mov 0x4(%esp),%edi

    repnz stosb

    /* return value */
    mov 0x4(%esp),%eax
    ret

