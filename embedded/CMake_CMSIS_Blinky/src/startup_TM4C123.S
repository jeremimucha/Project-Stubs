/**************************************************************************//**
 * @file     startup_TM4C123.S
 * @brief    CMSIS Cortex-M# Core Device Startup File for
 *           Device TM4C123
 * @version  V5.3.1
 * @date     09. July 2018
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

                .syntax  unified
                .arch    armv7-m


/*
;<h> Stack Configuration
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>
*/
                .equ     Stack_Size, 0x00000400

                .section .stack
                .align   3
	            .globl   __StackTop
	            .globl   __StackLimit
__StackLimit:
                .space   Stack_Size
                .size    __StackLimit, . - __StackLimit
__StackTop:
                .size    __StackTop, . - __StackTop


/*
;<h> Heap Configuration
;  <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>
*/
                .equ     Heap_Size, 0x00000100

                .if      Heap_Size != 0                     /* Heap is provided */
                .section .heap
                .align   3
	            .globl   __HeapBase
	            .globl   __HeapLimit
__HeapBase:
                .space   Heap_Size
                .size    __HeapBase, . - __HeapBase
__HeapLimit:
                .size    __HeapLimit, . - __HeapLimit
                .endif


                .section .vectors
                .align   2
                .globl   __Vectors
                .globl   __Vectors_End
                .globl   __Vectors_Size
__Vectors:
                .long    __StackTop                         /*     Top of Stack */
                .long    Reset_Handler                      /*     Reset Handler */
                .long    NMI_Handler                        /* -14 NMI Handler */
                .long    HardFault_Handler                  /* -13 Hard Fault Handler */
                .long    MemManage_Handler                  /* -12 MPU Fault Handler */
                .long    BusFault_Handler                   /* -11 Bus Fault Handler */
                .long    UsageFault_Handler                 /* -10 Usage Fault Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    SVC_Handler                        /*  -5 SVCall Handler */
                .long    DebugMon_Handler                   /*  -4 Debug Monitor Handler */
                .long    0                                  /*     Reserved */
                .long    PendSV_Handler                     /*  -2 PendSV Handler */
                .long    SysTick_Handler                    /*  -1 SysTick Handler */
                .long    GPIOA_Handler                      /* 16 GPIO Port A */
                .long    GPIOB_Handler                      /* 17 GPIO Port B */
                .long    GPIOC_Handler                      /* 18 GPIO Port C */
                .long    GPIOD_Handler                      /* 19 GPIO Port D */
                .long    GPIOE_Handler                      /* 20 GPIO Port E */
                .long    UART0_Handler                      /* 21 UART0 */
                .long    UART1_Handler                      /* 22 UART1 */
                .long    SSI0_Handler                       /* 23 SSI0 */
                .long    I2C0_Handler                       /* 24 I2C0 */
                .long    PWM0_FAULT_Handler                 /* 25 PWM0 Fault */
                .long    PWM0_0_Handler                     /* 26 PWM0 Generator 0 */
                .long    PWM0_1_Handler                     /* 27 PWM0 Generator 1 */
                .long    PWM0_2_Handler                     /* 28 PWM0 Generator 2 */
                .long    QEI0_Handler                       /* 29 QEI0 */
                .long    ADC0SS0_Handler                    /* 30 ADC0 Sequence 0 */
                .long    ADC0SS1_Handler                    /* 31 ADC0 Sequence 1 */
                .long    ADC0SS2_Handler                    /* 32 ADC0 Sequence 2 */
                .long    ADC0SS3_Handler                    /* 33 ADC0 Sequence 3 */
                .long    WATCHDOG_Handler                   /* 34 Watchdog Timers 0 and 1 */
                .long    TIMER0A_Handler                    /* 35 16/32-Bit Timer 0A */
                .long    TIMER0B_Handler                    /* 36 16/32-Bit Timer 0B */
                .long    TIMER1A_Handler                    /* 37 16/32-Bit Timer 1A */
                .long    TIMER1B_Handler                    /* 38 16/32-Bit Timer 1B */
                .long    TIMER2A_Handler                    /* 39 16/32-Bit Timer 2A */
                .long    TIMER2B_Handler                    /* 40 16/32-Bit Timer 2B */
                .long    COMP0_Handler                      /* 41 Analog Comparator 0 */
                .long    COMP1_Handler                      /* 42 Analog Comparator 1 */
                .long    0                                  /* Reserved */
                .long    SYSCTL_Handler                     /* 44 System Control */
                .long    FLASH_Handler                      /* 45 Flash Memory Control and EEPROM */
                .long    GPIOF_Handler                      /* 46 GPIO Port F */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    UART2_Handler                      /* 49 UART2 */
                .long    SSI1_Handler                       /* 50 SSI1 */
                .long    TIMER3A_Handler                    /* 51 16/32-Bit Timer 3A */
                .long    TIMER3B_Handler                    /* 52 Timer 3B */
                .long    I2C1_Handler                       /* 53 I2C1 */
                .long    QEI1_Handler                       /* 54 QEI1 */
                .long    CAN0_Handler                       /* 55 CAN0 */
                .long    CAN1_Handler                       /* 56 CAN1 */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    HIBERNATE_Handler                  /* 59 Hibernation Module */
                .long    USB0_Handler                       /* 60 USB */
                .long    PWM0_3_Handler                     /* 61 PWM Generator 3 */
                .long    UDMA_Handler                       /* 62 uDMA Software */
                .long    UDMAERR_Handler                    /* 63 uDMA Error */
                .long    ADC1SS0_Handler                    /* 64 ADC1 Sequence 0 */
                .long    ADC1SS1_Handler                    /* 65 ADC1 Sequence 1 */
                .long    ADC1SS2_Handler                    /* 66 ADC1 Sequence 2 */
                .long    ADC1SS3_Handler                    /* 67 ADC1 Sequence 3 */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    SSI2_Handler                       /* 73 SSI2 */
                .long    SSI3_Handler                       /* 74 SSI3 */
                .long    UART3_Handler                      /* 75 UART3 */
                .long    UART4_Handler                      /* 76 UART4 */
                .long    UART5_Handler                      /* 77 UART5 */
                .long    UART6_Handler                      /* 78 UART6 */
                .long    UART7_Handler                      /* 79 UART7 */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    I2C2_Handler                       /* 84 I2C2 */
                .long    I2C3_Handler                       /* 85 I2C3 */
                .long    TIMER4A_Handler                    /* 86 16/32-Bit Timer 4A */
                .long    TIMER4B_Handler                    /* 87 16/32-Bit Timer 4B */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    TIMER5A_Handler                    /* 108 16/32-Bit Timer 5A */
                .long    TIMER5B_Handler                    /* 109 16/32-Bit Timer 5B */
                .long    WTIMER0A_Handler                   /* 110 32/64-Bit Timer 0A */
                .long    WTIMER0B_Handler                   /* 111 32/64-Bit Timer 0B */
                .long    WTIMER1A_Handler                   /* 112 32/64-Bit Timer 1A */
                .long    WTIMER1B_Handler                   /* 113 32/64-Bit Timer 1B */
                .long    WTIMER2A_Handler                   /* 114 32/64-Bit Timer 2A */
                .long    WTIMER2B_Handler                   /* 115 32/64-Bit Timer 2B */
                .long    WTIMER3A_Handler                   /* 116 32/64-Bit Timer 3A */
                .long    WTIMER3B_Handler                   /* 117 32/64-Bit Timer 3B */
                .long    WTIMER4A_Handler                   /* 118 32/64-Bit Timer 4A */
                .long    WTIMER4B_Handler                   /* 119 32/64-Bit Timer 4B */
                .long    WTIMER5A_Handler                   /* 120 32/64-Bit Timer 5A */
                .long    WTIMER5B_Handler                   /* 121 32/64-Bit Timer 5B */
                .long    SYSEXC_Handler                     /* 122 System Exception (imprecise) */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    0                                  /* Reserved */
                .long    PWM1_0_Handler                     /* 150 PWM1 Generator 0 */
                .long    PWM1_1_Handler                     /* 151 PWM1 Generator 1 */
                .long    PWM1_2_Handler                     /* 152 PWM1 Generator 2 */
                .long    PWM1_3_Handler                     /* 153 PWM1 Generator 3 */
                .long    PWM1_FAULT_Handler                 /* 154 PWM1 Fault */

__Vectors_End:
                .equ     __Vectors_Size, __Vectors_End - __Vectors
                .size    __Vectors, . - __Vectors


                .thumb
                .section .text
                .align   2

                .thumb_func
                .type    Reset_Handler, %function
                .globl   Reset_Handler
                .fnstart
Reset_Handler:
/* Firstly it copies data from read only memory to RAM.
 * There are two schemes to copy. One can copy more than one sections.
 * Another can copy only one section. The former scheme needs more
 * instructions and read-only data to implement than the latter.
 * Macro __STARTUP_COPY_MULTIPLE is used to choose between two schemes.
 */

#ifdef __STARTUP_COPY_MULTIPLE
/* Multiple sections scheme.
 *
 * Between symbol address __copy_table_start__ and __copy_table_end__,
 * there are array of triplets, each of which specify:
 *   offset 0: LMA of start of a section to copy from
 *   offset 4: VMA of start of a section to copy to
 *   offset 8: size of the section to copy. Must be multiply of 4
 *
 * All addresses must be aligned to 4 bytes boundary.
 */
                ldr      r4, =__copy_table_start__
                ldr      r5, =__copy_table_end__

.L_loop0:
                cmp      r4, r5
                bge      .L_loop0_done
                ldr      r1, [r4]
                ldr      r2, [r4, #4]
                ldr      r3, [r4, #8]

.L_loop0_0:
                subs     r3, #4
                ittt     ge
                ldrge    r0, [r1, r3]
                strge    r0, [r2, r3]
                bge      .L_loop0_0

                adds     r4, #12
                b        .L_loop0

.L_loop0_done:
#else
/* Single section scheme.
 *
 * The ranges of copy from/to are specified by following symbols
 *   __etext: LMA of start of the section to copy from. Usually end of text
 *   __data_start__: VMA of start of the section to copy to
 *   __data_end__: VMA of end of the section to copy to
 *
 * All addresses must be aligned to 4 bytes boundary.
 */
                ldr      r1, =__etext
                ldr      r2, =__data_start__
                ldr      r3, =__data_end__

.L_loop1:
                cmp      r2, r3
                ittt     lt
                ldrlt    r0, [r1], #4
                strlt    r0, [r2], #4
                blt      .L_loop1
#endif /*__STARTUP_COPY_MULTIPLE */

/* This part of work usually is done in C library startup code.
 * Otherwise, define this macro to enable it in this startup.
 *
 * There are two schemes too.
 * One can clear multiple BSS sections. Another can only clear one section.
 * The former is more size expensive than the latter.
 *
 * Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
 * Otherwise define macro __STARTUP_CLEAR_BSS to choose the later.
 */
#ifdef __STARTUP_CLEAR_BSS_MULTIPLE
/* Multiple sections scheme.
 *
 * Between symbol address __copy_table_start__ and __copy_table_end__,
 * there are array of tuples specifying:
 *   offset 0: Start of a BSS section
 *   offset 4: Size of this BSS section. Must be multiply of 4
 */
                ldr      r3, =__zero_table_start__
                ldr      r4, =__zero_table_end__

.L_loop2:
                cmp      r3, r4
                bge      .L_loop2_done
                ldr      r1, [r3]
                ldr      r2, [r3, #4]
                movs     r0, 0

.L_loop2_0:
                subs     r2, #4
                itt      ge
                strge    r0, [r1, r2]
                bge      .L_loop2_0

                adds     r3, #8
                b        .L_loop2
.L_loop2_done:
#elif defined (__STARTUP_CLEAR_BSS)
/* Single BSS section scheme.
 *
 * The BSS section is specified by following symbols
 *   __bss_start__: start of the BSS section.
 *   __bss_end__: end of the BSS section.
 *
 * Both addresses must be aligned to 4 bytes boundary.
 */
                ldr      r1, =__bss_start__
                ldr      r2, =__bss_end__

                movs     r0, 0
.L_loop3:
                cmp      r1, r2
                itt      lt
                strlt    r0, [r1], #4
                blt      .L_loop3
#endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */

                bl       SystemInit
/* If compiling with C libraries use _start as the entry point */
                bl       _start
/* If compiling with no libraries at all go directly to main */
                /* bl      main */

                .fnend
                .size    Reset_Handler, . - Reset_Handler


                .thumb_func
                .type    Default_Handler, %function
                .weak    Default_Handler
                .fnstart
Default_Handler:
                b        .
                .fnend
                .size    Default_Handler, . - Default_Handler

/* Macro to define default exception/interrupt handlers.
 * Default handler are weak symbols with an endless loop.
 * They can be overwritten by real handlers.
 */
                .macro   Set_Default_Handler  Handler_Name
                .weak    \Handler_Name
                .set     \Handler_Name, Default_Handler
                .endm


/* Default exception/interrupt handler */

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  HardFault_Handler
                Set_Default_Handler  MemManage_Handler
                Set_Default_Handler  BusFault_Handler
                Set_Default_Handler  UsageFault_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  DebugMon_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler
                Set_Default_Handler  GPIOA_Handler
                Set_Default_Handler  GPIOB_Handler
                Set_Default_Handler  GPIOC_Handler
                Set_Default_Handler  GPIOD_Handler
                Set_Default_Handler  GPIOE_Handler
                Set_Default_Handler  UART0_Handler
                Set_Default_Handler  UART1_Handler
                Set_Default_Handler  SSI0_Handler
                Set_Default_Handler  I2C0_Handler
                Set_Default_Handler  PWM0_FAULT_Handler
                Set_Default_Handler  PWM0_0_Handler
                Set_Default_Handler  PWM0_1_Handler
                Set_Default_Handler  PWM0_2_Handler
                Set_Default_Handler  QEI0_Handler
                Set_Default_Handler  ADC0SS0_Handler
                Set_Default_Handler  ADC0SS1_Handler
                Set_Default_Handler  ADC0SS2_Handler
                Set_Default_Handler  ADC0SS3_Handler
                Set_Default_Handler  WATCHDOG_Handler
                Set_Default_Handler  TIMER0A_Handler
                Set_Default_Handler  TIMER0B_Handler
                Set_Default_Handler  TIMER1A_Handler
                Set_Default_Handler  TIMER1B_Handler
                Set_Default_Handler  TIMER2A_Handler
                Set_Default_Handler  TIMER2B_Handler
                Set_Default_Handler  COMP0_Handler
                Set_Default_Handler  COMP1_Handler
                Set_Default_Handler  SYSCTL_Handler
                Set_Default_Handler  FLASH_Handler
                Set_Default_Handler  GPIOF_Handler
                Set_Default_Handler  UART2_Handler
                Set_Default_Handler  SSI1_Handler
                Set_Default_Handler  TIMER3A_Handler
                Set_Default_Handler  TIMER3B_Handler
                Set_Default_Handler  I2C1_Handler
                Set_Default_Handler  QEI1_Handler
                Set_Default_Handler  CAN0_Handler
                Set_Default_Handler  CAN1_Handler
                Set_Default_Handler  HIBERNATE_Handler
                Set_Default_Handler  USB0_Handler
                Set_Default_Handler  PWM0_3_Handler
                Set_Default_Handler  UDMA_Handler
                Set_Default_Handler  UDMAERR_Handler
                Set_Default_Handler  ADC1SS0_Handler
                Set_Default_Handler  ADC1SS1_Handler
                Set_Default_Handler  ADC1SS2_Handler
                Set_Default_Handler  ADC1SS3_Handler
                Set_Default_Handler  SSI2_Handler
                Set_Default_Handler  SSI3_Handler
                Set_Default_Handler  UART3_Handler
                Set_Default_Handler  UART4_Handler
                Set_Default_Handler  UART5_Handler
                Set_Default_Handler  UART6_Handler
                Set_Default_Handler  UART7_Handler
                Set_Default_Handler  I2C2_Handler
                Set_Default_Handler  I2C3_Handler
                Set_Default_Handler  TIMER4A_Handler
                Set_Default_Handler  TIMER4B_Handler
                Set_Default_Handler  TIMER5A_Handler
                Set_Default_Handler  TIMER5B_Handler
                Set_Default_Handler  WTIMER0A_Handler
                Set_Default_Handler  WTIMER0B_Handler
                Set_Default_Handler  WTIMER1A_Handler
                Set_Default_Handler  WTIMER1B_Handler
                Set_Default_Handler  WTIMER2A_Handler
                Set_Default_Handler  WTIMER2B_Handler
                Set_Default_Handler  WTIMER3A_Handler
                Set_Default_Handler  WTIMER3B_Handler
                Set_Default_Handler  WTIMER4A_Handler
                Set_Default_Handler  WTIMER4B_Handler
                Set_Default_Handler  WTIMER5A_Handler
                Set_Default_Handler  WTIMER5B_Handler
                Set_Default_Handler  SYSEXC_Handler
                Set_Default_Handler  PWM1_0_Handler
                Set_Default_Handler  PWM1_1_Handler
                Set_Default_Handler  PWM1_2_Handler
                Set_Default_Handler  PWM1_3_Handler
                Set_Default_Handler  PWM1_FAULT_Handler

                .end
