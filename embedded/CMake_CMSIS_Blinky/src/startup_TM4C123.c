/**************************************************************************//**
 * @file     startup_TM4C123.c
 * @brief    CMSIS Core Device Startup File for
 *           TM4C123 Device
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
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

#include "TM4C123.h"


/*----------------------------------------------------------------------------
  Linker generated Symbols
 *----------------------------------------------------------------------------*/
extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __copy_table_start__;
extern uint32_t __copy_table_end__;
extern uint32_t __zero_table_start__;
extern uint32_t __zero_table_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __StackTop;


/*----------------------------------------------------------------------------
  Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void( *pFunc )( void );


/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern void _start     (void) __attribute__((noreturn)); /* Pre-Main (C library entry point) */
extern void main       (void) __attribute__((noreturn));


/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void Default_Handler(void) __attribute__ ((noreturn));
void Reset_Handler  (void) __attribute__ ((noreturn));


/*----------------------------------------------------------------------------
  User Initial Stack & Heap
 *----------------------------------------------------------------------------*/
//<h> Stack Configuration
//  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//</h>
#define  __STACK_SIZE  0x00000400
static uint8_t stack[__STACK_SIZE] __attribute__ ((aligned(8), used, section(".stack")));

//<h> Heap Configuration
//  <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
//</h>
#define  __HEAP_SIZE   0x00000100
#if __HEAP_SIZE > 0
static uint8_t heap[__HEAP_SIZE]   __attribute__ ((aligned(8), used, section(".heap")));
#endif


/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */
void NMI_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));

void  GPIOA_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  GPIOB_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  GPIOC_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  GPIOD_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  GPIOE_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  UART0_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  UART1_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  SSI0_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  I2C0_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  PWM0_FAULT_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));
void  PWM0_0_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void  PWM0_1_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void  PWM0_2_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void  QEI0_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  ADC0SS0_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  ADC0SS1_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  ADC0SS2_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  ADC0SS3_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  WATCHDOG_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void  TIMER0A_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  TIMER0B_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  TIMER1A_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  TIMER1B_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  TIMER2A_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  TIMER2B_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  COMP0_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  COMP1_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  SYSCTL_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void  FLASH_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  GPIOF_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  UART2_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  SSI1_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  TIMER3A_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  TIMER3B_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  I2C1_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  QEI1_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  CAN0_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  CAN1_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  HIBERNATE_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void  USB0_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  PWM0_3_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void  UDMA_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  UDMAERR_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  ADC1SS0_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  ADC1SS1_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  ADC1SS2_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  ADC1SS3_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  SSI2_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  SSI3_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  UART3_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  UART4_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  UART5_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  UART6_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  UART7_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void  I2C2_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  I2C3_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void  TIMER4A_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  TIMER4B_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  TIMER5A_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  TIMER5B_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void  WTIMER0A_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void  WTIMER0B_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void  WTIMER1A_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void  WTIMER1B_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void  WTIMER2A_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void  WTIMER2B_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void  WTIMER3A_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void  WTIMER3B_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void  WTIMER4A_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void  WTIMER4B_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void  WTIMER5A_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void  WTIMER5B_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void  SYSEXC_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void  PWM1_0_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void  PWM1_1_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void  PWM1_2_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void  PWM1_3_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void  PWM1_FAULT_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));


/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/
extern const pFunc __Vectors[240];
       const pFunc __Vectors[240] __attribute__ ((section(".vectors"))) = {
  (pFunc)(&__StackTop),                     /*     Initial Stack Pointer */
  Reset_Handler,                            /*     Reset Handler */
  NMI_Handler,                              /* -14 NMI Handler */
  HardFault_Handler,                        /* -13 Hard Fault Handler */
  MemManage_Handler,                        /* -12 MPU Fault Handler */
  BusFault_Handler,                         /* -11 Bus Fault Handler */
  UsageFault_Handler,                       /* -10 Usage Fault Handler */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  SVC_Handler,                              /*  -5 SVCall Handler */
  DebugMon_Handler,                         /*  -4 Debug Monitor Handler */
  0,                                        /*     Reserved */
  PendSV_Handler,                           /*  -2 PendSV Handler */
  SysTick_Handler,                          /*  -1 SysTick Handler */
  GPIOA_Handler,                            /* 16 GPIO Port A */
  GPIOB_Handler,                            /* 17 GPIO Port B */
  GPIOC_Handler,                            /* 18 GPIO Port C */
  GPIOD_Handler,                            /* 19 GPIO Port D */
  GPIOE_Handler,                            /* 20 GPIO Port E */
  UART0_Handler,                            /* 21 UART0 */
  UART1_Handler,                            /* 22 UART1 */
  SSI0_Handler,                            /* 23 SSI0 */
  I2C0_Handler,                            /* 24 I2C0 */
  PWM0_FAULT_Handler,                      /* 25 PWM0 Fault */
  PWM0_0_Handler,                          /* 26 PWM0 Generator 0 */
  PWM0_1_Handler,                          /* 27 PWM0 Generator 1 */
  PWM0_2_Handler,                          /* 28 PWM0 Generator 2 */
  QEI0_Handler,                            /* 29 QEI0 */
  ADC0SS0_Handler,                          /* 30 ADC0 Sequence 0 */
  ADC0SS1_Handler,                          /* 31 ADC0 Sequence 1 */
  ADC0SS2_Handler,                          /* 32 ADC0 Sequence 2 */
  ADC0SS3_Handler,                          /* 33 ADC0 Sequence 3 */
  WATCHDOG_Handler,                        /* 34 Watchdog Timers 0 and 1 */
  TIMER0A_Handler,                          /* 35 16/32-Bit Timer 0A */
  TIMER0B_Handler,                          /* 36 16/32-Bit Timer 0B */
  TIMER1A_Handler,                          /* 37 16/32-Bit Timer 1A */
  TIMER1B_Handler,                          /* 38 16/32-Bit Timer 1B */
  TIMER2A_Handler,                          /* 39 16/32-Bit Timer 2A */
  TIMER2B_Handler,                          /* 40 16/32-Bit Timer 2B */
  COMP0_Handler,                            /* 41 Analog Comparator 0 */
  COMP1_Handler,                            /* 42 Analog Comparator 1 */
  0,                                        /* Reserved */
  SYSCTL_Handler,                          /* 44 System Control */
  FLASH_Handler,                            /* 45 Flash Memory Control and EEPROM */
  GPIOF_Handler,                            /* 46 GPIO Port F */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  UART2_Handler,                            /* 49 UART2 */
  SSI1_Handler,                            /* 50 SSI1 */
  TIMER3A_Handler,                          /* 51 16/32-Bit Timer 3A */
  TIMER3B_Handler,                          /* 52 Timer 3B */
  I2C1_Handler,                            /* 53 I2C1 */
  QEI1_Handler,                            /* 54 QEI1 */
  CAN0_Handler,                            /* 55 CAN0 */
  CAN1_Handler,                            /* 56 CAN1 */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  HIBERNATE_Handler,                        /* 59 Hibernation Module */
  USB0_Handler,                            /* 60 USB */
  PWM0_3_Handler,                          /* 61 PWM Generator 3 */
  UDMA_Handler,                            /* 62 uDMA Software */
  UDMAERR_Handler,                          /* 63 uDMA Error */
  ADC1SS0_Handler,                          /* 64 ADC1 Sequence 0 */
  ADC1SS1_Handler,                          /* 65 ADC1 Sequence 1 */
  ADC1SS2_Handler,                          /* 66 ADC1 Sequence 2 */
  ADC1SS3_Handler,                          /* 67 ADC1 Sequence 3 */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  SSI2_Handler,                            /* 73 SSI2 */
  SSI3_Handler,                            /* 74 SSI3 */
  UART3_Handler,                            /* 75 UART3 */
  UART4_Handler,                            /* 76 UART4 */
  UART5_Handler,                            /* 77 UART5 */
  UART6_Handler,                            /* 78 UART6 */
  UART7_Handler,                            /* 79 UART7 */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  I2C2_Handler,                            /* 84 I2C2 */
  I2C3_Handler,                            /* 85 I2C3 */
  TIMER4A_Handler,                          /* 86 16/32-Bit Timer 4A */
  TIMER4B_Handler,                          /* 87 16/32-Bit Timer 4B */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  TIMER5A_Handler,                          /* 108 16/32-Bit Timer 5A */
  TIMER5B_Handler,                          /* 109 16/32-Bit Timer 5B */
  WTIMER0A_Handler,                        /* 110 32/64-Bit Timer 0A */
  WTIMER0B_Handler,                        /* 111 32/64-Bit Timer 0B */
  WTIMER1A_Handler,                        /* 112 32/64-Bit Timer 1A */
  WTIMER1B_Handler,                        /* 113 32/64-Bit Timer 1B */
  WTIMER2A_Handler,                        /* 114 32/64-Bit Timer 2A */
  WTIMER2B_Handler,                        /* 115 32/64-Bit Timer 2B */
  WTIMER3A_Handler,                        /* 116 32/64-Bit Timer 3A */
  WTIMER3B_Handler,                        /* 117 32/64-Bit Timer 3B */
  WTIMER4A_Handler,                        /* 118 32/64-Bit Timer 4A */
  WTIMER4B_Handler,                        /* 119 32/64-Bit Timer 4B */
  WTIMER5A_Handler,                        /* 120 32/64-Bit Timer 5A */
  WTIMER5B_Handler,                        /* 121 32/64-Bit Timer 5B */
  SYSEXC_Handler,                          /* 122 System Exception (imprecise) */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  0,                                        /* Reserved */
  PWM1_0_Handler,                          /* 150 PWM1 Generator 0 */
  PWM1_1_Handler,                          /* 151 PWM1 Generator 1 */
  PWM1_2_Handler,                          /* 152 PWM1 Generator 2 */
  PWM1_3_Handler,                          /* 153 PWM1 Generator 3 */
  PWM1_FAULT_Handler                      /* 154 PWM1 Fault */
                                            /* Interrupts 10 .. 224 are left out */
};


/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void) {
  uint32_t *pSrc, *pDest;
  uint32_t *pTable __attribute__((unused));

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
  pTable = &__copy_table_start__;

  for (; pTable < &__copy_table_end__; pTable = pTable + 3) {
    pSrc  = (uint32_t*)*(pTable + 0);
    pDest = (uint32_t*)*(pTable + 1);
    for (; pDest < (uint32_t*)(*(pTable + 1) + *(pTable + 2)) ; ) {
      *pDest++ = *pSrc++;
    }
  }
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
  pSrc  = &__etext;
  pDest = &__data_start__;

  for ( ; pDest < &__data_end__ ; ) {
    *pDest++ = *pSrc++;
  }
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
  pTable = &__zero_table_start__;

  for (; pTable < &__zero_table_end__; pTable = pTable + 2) {
    pDest = (uint32_t*)*(pTable + 0);
    for (; pDest < (uint32_t*)(*(pTable + 0) + *(pTable + 1)) ; ) {
      *pDest++ = 0;
    }
  }
#elif defined (__STARTUP_CLEAR_BSS)
/* Single BSS section scheme.
 *
 * The BSS section is specified by following symbols
 *   __bss_start__: start of the BSS section.
 *   __bss_end__: end of the BSS section.
 *
 * Both addresses must be aligned to 4 bytes boundary.
 */
  pDest = &__bss_start__;

  for ( ; pDest < &__bss_end__ ; ) {
    *pDest++ = 0UL;
  }
#endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */

  SystemInit();                             /* CMSIS System Initialization */
  // _start();                                 /* Enter PreeMain (C library entry point) */
  main();
}


/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void) {

  while(1);
}
