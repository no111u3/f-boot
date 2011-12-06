/**
 * Startup for AT91RM9200
 */
/* Includes */
#include <AT91RM9200_inc.h>
/* Defines */
#define MEMEND 0x00004000
/** Stacks size */
#define IRQ_STACK_SIZE  0x100
#define FIQ_STACK_SIZE  0x04
#define ABT_STACK_SIZE  0x04
#define UND_STACK_SIZE  0x04
#define SVC_STACK_SIZE  0x100
#define USER_STACK_SIZE 0x400
/** arm core modes */
#define ARM_MODE_USER   0x10
#define ARM_MODE_FIQ    0x11
#define ARM_MODE_IRQ    0x12
#define ARM_MODE_SVC    0x13
#define ARM_MODE_ABORT  0x17
#define ARM_MODE_UNDEF  0x1B
#define ARM_MODE_SYS    0x1F
/** arm core control bits */
#define I_BIT           0x80
#define F_BIT           0x40
#define T_BIT           0x20
/* Code */
.section .text
/* Global entry point */
.global start_entry
/* Entry point */
start_entry:
/* AIC vectors */
        b           reset               /* reset */
        b           undefvec            /* Undefined Instruction */
        b           swivec              /* Software Interrupt */
        b           pabtvec             /* Prefetch Abort */
        b           dabtvec             /* Data Abort */
        b           rsvdvec             /* reserved */
        b           aicvec              /* IRQ : read the AIC */
        b           fiqvec              /* FIQ */
/* dummy AIC handlers */
undefvec:
swivec:
pabtvec:
dabtvec:
rsvdvec:
aicvec:
fiqvec:
        b       undefvec
/* reset vector */
reset:
/* Startup init code */
/** Enable led */
        mov     r0, #AT91C_PIO_PB27
        ldr     r1,= AT91C_BASE_PIOB
        str     r0, [r1, #PIO_PER]
        str     r0, [r1, #PIO_OER]
        str     r0, [r1, #PIO_CODR]
/* Setup stacks and modes */
        ldr     r0,= MEMEND
/** Set up Supervisor Mode and set Supervisor Mode Stack*/
        msr     CPSR_c, #ARM_MODE_SVC | I_BIT | F_BIT
        mov     r13, r0                     /* Init stack Undef*/
        sub     r0, r0, #SVC_STACK_SIZE

/** Set up Interrupt Mode and set IRQ Mode Stack*/
        msr     CPSR_c, #ARM_MODE_IRQ | I_BIT | F_BIT
        mov     r13, r0                     /* Init stack IRQ*/
        sub     r0, r0, #IRQ_STACK_SIZE

/** Set up Fast Interrupt Mode and set FIQ Mode Stack*/
        msr     CPSR_c, #ARM_MODE_FIQ | I_BIT | F_BIT
        mov     r13, r0                     /* Init stack FIQ*/
        sub     r0, r0, #FIQ_STACK_SIZE

/** Set up Abort Mode and set Abort Mode Stack*/
        msr     CPSR_c, #ARM_MODE_ABORT | I_BIT | F_BIT
        mov     r13, r0                     /* Init stack Abort*/
        sub     r0, r0, #ABT_STACK_SIZE

/** Set up Undefined Instruction Mode and set Undef Mode Stack*/
        msr     CPSR_c, #ARM_MODE_UNDEF | I_BIT | F_BIT
        mov     r13, r0                     /* Init stack Undef*/
        sub     r0, r0, #UND_STACK_SIZE

/** Set up user Mode and set System Mode Stack*/
        msr     CPSR_c, #ARM_MODE_SYS | I_BIT | F_BIT
        bic     r0, r0, #3                  /* Insure word alignement */
        mov     sp, r0                      /* Init stack System */
/* Run device init function */
        bl      dev_init
/* Modify cp15 control register */
		mrc     p15, 0, r0, c1, c0,0  /* read cp15 control register (cp15 r1) in r0 */
		ldr     r3,= 0xC0000080      /* Reset bit :Little Endian end fast bus mode */
		ldr     r4,= 0xC0001000      /* Set bit :Asynchronous clock mode, Not Fast Bus, I-Cache enable */
		bic     r0, r0, r3
		orr     r0, r0, r4
		mcr     p15, 0, r0, c1, c0,0 /* write r0 in cp15 control registre (cp15 r1) */
/* Enable interrupts */
		msr     CPSR_c, #ARM_MODE_SYS | F_BIT
/* Run main funtion */
        bl      sys_main
/* Infinity loop - end of app*/
end_app:
        b       end_app