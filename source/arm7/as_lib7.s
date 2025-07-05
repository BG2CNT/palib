// desinterleave a stereo source (thanks to Thoduv for the code)

#include <nds/asminc.h>

    .syntax  unified

    .text
    .arm

@ desinterleave an mp3 stereo source
@ r0 = interleaved data, r1 = left, r2 = right, r3 = len
BEGIN_ASM_FUNC AS_StereoDesinterleave

    stmfd sp!, {r4-r11}

_loop:

    ldmia r0!, {r4-r12}

    strh r4, [r1], #2
    mov r4, r4, lsr #16
    strh  r4, [r2], #2
    subs r3, #1
    beq _done

    strh r5, [r1], #2
    mov r5, r5, lsr #16
    strh  r5, [r2], #2
    subs r3, #1
    beq _done

    strh r6, [r1], #2
    mov r6, r6, lsr #16
    strh  r6, [r2], #2
    subs r3, #1
    beq _done

    strh r7, [r1], #2
    mov r7, r7, lsr #16
    strh  r7, [r2], #2
    subs r3, #1
    beq _done

    strh r8, [r1], #2
    mov r8, r8, lsr #16
    strh  r8, [r2], #2
    subs r3, #1
    beq _done

    strh r9, [r1], #2
    mov r9, r9, lsr #16
    strh  r9, [r2], #2
    subs r3, #1
    beq _done

    strh r10, [r1], #2
    mov r10, r10, lsr #16
    strh  r10, [r2], #2
    subs r3, #1
    beq _done

    strh r11, [r1], #2
    mov r11, r11, lsr #16
    strh  r11, [r2], #2
    subs r3, #1
    beq _done

    strh r12, [r1], #2
    mov r12, r12, lsr #16
    strh  r12, [r2], #2
    subs r3, #1
    bne _loop
_done:

    ldmia sp!, {r4-r11}
    bx lr
