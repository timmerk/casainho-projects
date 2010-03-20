/******************************************************************************
 * @file:    MPS_CM3.h
 * @purpose: CMSIS Cortex-M3 Core Peripheral Access Layer Header File for 
 *           ARM 'Microcontroller Prototyping System' 
 * @version: V1.02
 * @date:    19. Aug. 2009
 *----------------------------------------------------------------------------
 *
 * Copyright (C) 2008-2009 ARM Limited. All rights reserved.
 *
 * ARM Limited (ARM) is supplying this software for use with Cortex-M3 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#ifndef __MPS_CM3_H__
#define __MPS_CM3_H__

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn           = -14,      /*!< 2 Non Maskable Interrupt                         */
  HardFault_IRQn                = -13,      /*!< 3 Cortex-M3 HardFault Interrupt                  */
  MemoryManagement_IRQn         = -12,      /*!< 4 Cortex-M3 Memory Management Interrupt          */
  BusFault_IRQn                 = -11,      /*!< 5 Cortex-M3 Bus Fault Interrupt                  */
  UsageFault_IRQn               = -10,      /*!< 6 Cortex-M3 Usage Fault Interrupt                */
  SVCall_IRQn                   = -5,       /*!< 11 Cortex-M3 SV Call Interrupt                   */
  DebugMonitor_IRQn             = -4,       /*!< 12 Cortex-M3 Debug Monitor Interrupt             */
  PendSV_IRQn                   = -2,       /*!< 14 Cortex-M3 Pend SV Interrupt                   */
  SysTick_IRQn                  = -1,       /*!< 15 Cortex-M3 System Tick Interrupt               */

/******  ARM MPS Specific Interrupt Numbers *******************************************************/
  WDT_IRQn                      = 0,        /*!< Watchdog Timer Interrupt                         */
  RTC_IRQn                      = 1,        /*!< Real Time Clock Interrupt                        */
  TIM0_IRQn                     = 2,        /*!< Timer0 / Timer1 Interrupt                        */
  TIM2_IRQn                     = 3,        /*!< Timer2 / Timer3 Interrupt                        */
  MCIA_IRQn                     = 4,        /*!< MCIa Interrupt                                   */
  MCIB_IRQn                     = 5,        /*!< MCIb Interrupt                                   */
  UART0_IRQn                    = 6,        /*!< UART0 Interrupt                                  */
  UART1_IRQn                    = 7,        /*!< UART1 Interrupt                                  */
  UART2_IRQn                    = 8,        /*!< UART2 Interrupt                                  */
  UART4_IRQn                    = 9,        /*!< UART4 Interrupt                                  */
  AACI_IRQn                     = 10,       /*!< AACI / AC97 Interrupt                            */
  CLCD_IRQn                     = 11,       /*!< CLCD Combined Interrupt                          */
  ENET_IRQn                     = 12,       /*!< Ethernet Interrupt                               */
  USBDC_IRQn                    = 13,       /*!< USB Device Interrupt                             */
  USBHC_IRQn                    = 14,       /*!< USB Host Controller Interrupt                    */
  CHLCD_IRQn                    = 15,       /*!< Character LCD Interrupt                          */
  FLEXRAY_IRQn                  = 16,       /*!< Flexray Interrupt                                */
  CAN_IRQn                      = 17,       /*!< CAN Interrupt                                    */
  LIN_IRQn                      = 18,       /*!< LIN Interrupt                                    */
  I2C_IRQn                      = 19,       /*!< I2C ADC/DAC Interrupt                            */
  CPU_CLCD_IRQn                 = 28,       /*!< CPU CLCD Combined Interrupt                      */
  UART3_IRQn                    = 30,       /*!< UART3 Interrupt                                  */
  SPI_IRQn                      = 31,       /*!< SPI Touchscreen Interrupt                        */
} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M3 Processor and Core Peripherals */
#define __MPU_PRESENT             1         /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS          3         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */


#include <core_cm3.h>                       /* Cortex-M3 processor and core peripherals           */
#include "system_MPS.h"                     /* MPS System                                         */


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

#pragma anon_unions

/*------------- CPU FPGA System (CPU_SYS) ------------------------------------*/
// <g> CPU FPGA System (CPU_SYS)
typedef struct
{
  __I  uint32_t ID;           // <h> Board and FPGA Identifier
                              //   <o.28..31> REV: Board revision (0...15) <r>
                              //   <o.16..27> BOARD: HBI board number (0...4095) <r>
                              //   <o.12..15> VARIANT: Build variant of board (0..15) <r>
                              //   <o.8..11>  ARCH: Bus architecture (0..15) <r>
                              //   <o.0..7>   BUILD: FPGA build (0..255) <r>
                              // </h>
  __IO uint32_t MEMCFG;       // <h> Remap and Alias Memory Control
                              //   <o.1>      ALIAS: Alias Flash
                              //   <o.0>      REMAP: Remap SSRAM
                              // </h>
  __I  uint32_t SW;           // <h> Switch States
                              //   <o.0..7>   USER_SWITCH: User switches value (0..255) <r>
                              // </h>
  __IO uint32_t LED;          // <h> LED Output States
                              //   <o.0..7>   LED: LED value (0..255)
                              // </h>
  __I  uint32_t TS;           // <h> Touchscreen Register
                              //   <o.1>      TS_INT: Touchscreen external interrupt <r>
                              //   <o.0>      TS_BUSY: Touchscreen external busy signal <r>
                              // </h>
  __IO uint32_t CTRL1;        // <h> Misc Control Functions
                              //   <o.1>      VIDEO_SEL: Video source selection (0..1)
                              //   <o.0>      LED_FUNC: LED function sel (0..1)
                              // </h>
       uint32_t RESERVED0[2];
  __IO uint32_t CLKCFG;       // <h> System Clock Configuration
                              //   <o.0..3>   CLKCFG: Processor Clock (1..13)
                              // </h>
  __IO uint32_t WSCFG;        // <h> Flash Waitstate Configuration
                              //   <o.0..1>   WSCFG: Processor Clock (0..3)
                              // </h>
  __IO uint32_t CPUCFG;       // <h> Processor Configuration
                              //   <o.0..15>  CPUCFG: Reserved for Processor Configuration (0..65535)
                              // </h>
       uint32_t RESERVED1[3];
  __IO uint32_t BASE;         // <h> ROM Table base Address
  __IO uint32_t ID2;          // <h> Reserved Secondary Identification Register
                              // </h>
} CPU_SYS_TypeDef;
// </g>

/*------------- DUT FPGA System (DUT_SYS) ------------------------------------*/
// <g> DUT FPGA System (DUT_SYS)
typedef struct
{
  __I  uint32_t ID;           // <h> Board and FPGA Identifier
                              //   <o.28..31> REV: Board revision (0...15) <r>
                              //   <o.16..27> BOARD: HBI board number (0...4095) <r>
                              //   <o.12..15> VARIANT: Build variant of board (0..15) <r>
                              //   <o.8..11>  ARCH: Bus architecture (0..15) <r>
                              //   <o.0..7>   BUILD: FPGA build (0..255) <r>
                              // </h>
  __IO uint32_t PERCFG;       // <h> Peripheral Control Signals
                              //   <o.8..10>  HUMI_MODE: Operation mode of HUMI multiplexer
                              //                <0=> 0: Round robin scheduler
                              //                <1=> 1: LEDs
                              //                <2=> 2: 7-seg 0 only
                              //                <3=> 3: 7-seg 1 only
                              //                <4=> 4: 7-seg 2 only
                              //                <5=> 5: 7-seg 3 only
                              //                <6=> 6: LCD only
                              //                <7=> 7: Reserved
                              //   <o.7>      USB_HC_WAKE: Status of USB Host Wake/Suspend signal <r>
                              //   <o.6>      USB_DC_WAKE: Status of USB Device Wake/Suspend signal <r>
                              //   <o.4>      LCD_BLON: LCD backlight power
                              //   <o.3>      LCD_PWR: LCD power supply
                              //   <o.1>      WPROT: Status of MCI WPROT bit <r>
                              //   <o.0>      CARDIN: Status of MCI Card present <r>
                              // </h>
  __I  uint32_t SW;           // <h> Switch States
                              //   <o.4..7>   USER_BUT: User buttons value (0..15) <r>
                              //   <o.0..3>   USER_SW: User switches value (0..15) <r>
                              // </h>
  __IO uint32_t LED;          // <h> LED Output States
                              //   <o.0..7>   LED: LED value (0..255)
                              // </h>
  __IO uint32_t SEG7;         // <h> 7-segment LED Output States
                              //   <o.24..31> DISP3: Segments for display 3 (0..255)
                              //   <o.16..23> DISP2: Segments for display 2 (0..255)
                              //   <o.8..15>  DISP1: Segments for display 1 (0..255)
                              //   <o.0..7>   DISP0: Segments for display 0 (0..255)
                              // </h>
  __I  uint32_t CNT25MHz;     // <h> Freerunning counter incrementing at 25MHz <r>
                              // </h>
  __I  uint32_t CNT100Hz;     // <h> Freerunning counter incrementing at 100Hz <r>
                              // </h>
} DUT_SYS_TypeDef;
// </g>

/*------------- Timer (TIM) --------------------------------------------------*/
// <g> Timer (TIM)
typedef struct
{
  __IO uint32_t Timer1Load;   // <h> Timer 1 Load </h>
  __I  uint32_t Timer1Value;  // <h> Timer 1 Counter Current Value <r></h>
  __IO uint32_t Timer1Control;// <h> Timer 1 Control
                              //   <o.7> TimerEn: Timer Enable
                              //   <o.6> TimerMode: Timer Mode
                              //     <0=> Freerunning-mode 
                              //     <1=> Periodic mode 
                              //   <o.5> IntEnable: Interrupt Enable
                              //   <o.2..3> TimerPre: Timer Prescale
                              //     <0=> / 1 
                              //     <1=> / 16 
                              //     <2=> / 256 
                              //     <3=> Undefined! 
                              //   <o.1> TimerSize: Timer Size
                              //     <0=> 16-bit counter
                              //     <1=> 32-bit counter 
                              //   <o.0> OneShot: One-shoot mode
                              //     <0=> Wrapping mode
                              //     <1=> One-shot mode 
                              // </h>
  __O  uint32_t Timer1IntClr; // <h> Timer 1 Interrupt Clear <w></h>
  __I  uint32_t Timer1RIS;    // <h> Timer 1 Raw Interrupt Status <r></h>
  __I  uint32_t Timer1MIS;    // <h> Timer 1 Masked Interrupt Status <r></h>
  __IO uint32_t Timer1BGLoad; // <h> Background Load Register </h>
       uint32_t RESERVED0;
  __IO uint32_t Timer2Load;   // <h> Timer 2 Load </h>
  __I  uint32_t Timer2Value;  // <h> Timer 2 Counter Current Value <r></h>
  __IO uint32_t Timer2Control;// <h> Timer 2 Control
                              //   <o.7> TimerEn: Timer Enable
                              //   <o.6> TimerMode: Timer Mode
                              //     <0=> Freerunning-mode 
                              //     <1=> Periodic mode 
                              //   <o.5> IntEnable: Interrupt Enable
                              //   <o.2..3> TimerPre: Timer Prescale
                              //     <0=> / 1 
                              //     <1=> / 16 
                              //     <2=> / 256 
                              //     <3=> Undefined! 
                              //   <o.1> TimerSize: Timer Size
                              //     <0=> 16-bit counter
                              //     <1=> 32-bit counter 
                              //   <o.0> OneShot: One-shoot mode
                              //     <0=> Wrapping mode
                              //     <1=> One-shot mode 
                              // </h>
  __O  uint32_t Timer2IntClr; // <h> Timer 2 Interrupt Clear <w></h>
  __I  uint32_t Timer2RIS;    // <h> Timer 2 Raw Interrupt Status <r></h>
  __I  uint32_t Timer2MIS;    // <h> Timer 2 Masked Interrupt Status <r></h>
  __IO uint32_t Timer2BGLoad; // <h> Background Load Register </h>
} TIM_TypeDef;
// </g>

/*------------- Universal Asyncronous Receiver / Transmitter (UART) ----------*/
// <g> UART
typedef struct
{
  __IO uint32_t UARTDR;       // <h> Data 
                              //   <o.11>   OE: Overrun error <r>
                              //   <o.10>   BE: Break error <r>
                              //   <o.9>    PE: Parity error <r>
                              //   <o.8>    FE: Framing error <r>
                              //   <o.0..7> DATA: Received or Transmitting data (0..255)
                              // </h>
  union {
  __I  uint32_t UARTRSR;      // <h> Receive Status <r>
                              //   <o.3>    OE: Overrun error <r>
                              //   <o.2>    BE: Break error <r>
                              //   <o.1>    PE: Parity error <r>
                              //   <o.0>    FE: Framing error <r>
                              // </h>
  __O  uint32_t UARTECR;      // <h> Error Clear <w>
                              //   <o.3>    OE: Overrun error <w>
                              //   <o.2>    BE: Break error <w>
                              //   <o.1>    PE: Parity error <w>
                              //   <o.0>    FE: Framing error <w>
                              // </h>
  };
       uint32_t RESERVED0[4];
  __IO uint32_t UARTFR;       // <h> Flags <r>
                              //   <o.8>    RI: Ring indicator <r>
                              //   <o.7>    TXFE: Transmit FIFO empty <r>
                              //   <o.6>    RXFF: Receive FIFO full <r>
                              //   <o.5>    TXFF: Transmit FIFO full <r>
                              //   <o.4>    RXFE: Receive FIFO empty <r>
                              //   <o.3>    BUSY: UART busy <r>
                              //   <o.2>    DCD: Data carrier detect <r>
                              //   <o.1>    DSR: Data set ready <r>
                              //   <o.0>    CTS: Clear to send <r>
                              // </h>
       uint32_t RESERVED1;
  __IO uint32_t UARTILPR;     // <h> IrDA Low-power Counter
                              //   <o.0..7> ILPDVSR: 8-bit low-power divisor value (0..255)
                              // </h>
  __IO uint32_t UARTIBRD;     // <h> Interger Baud Rate
                              //   <o.0..15> BAUD DIVINT: Integer baud rate divisior (0..65535)
                              // </h>
  __IO uint32_t UARTFBRD;     // <h> Fractional Baud Rate
                              //   <o.0..5> BAUD DIVFRAC: Fractional baud rate divisior (0..63)
                              // </h>
  __IO uint32_t UARTLCR_H;    // <h> Line Control
                              //   <o.8>    SPS: Stick parity select
                              //   <o.5..6> WLEN: Word length
                              //     <0=> 5 bits 
                              //     <1=> 6 bits 
                              //     <2=> 7 bits 
                              //     <3=> 8 bits 
                              //   <o.4>    FEN: Enable FIFOs
                              //   <o.3>    STP2: Two stop bits select
                              //   <o.2>    EPS: Even parity select
                              //   <o.1>    PEN: Parity enable
                              //   <o.0>    BRK: Send break
                              // </h>
  __IO uint32_t UARTCR;       // <h> Control
                              //   <o.15>   CTSEn: CTS hardware flow control enable
                              //   <o.14>   RTSEn: RTS hardware flow control enable
                              //   <o.13>   Out2: Complement of Out2 modem status output
                              //   <o.12>   Out1: Complement of Out1 modem status output
                              //   <o.11>   RTS: Request to send
                              //   <o.10>   DTR: Data transmit ready
                              //   <o.9>    RXE: Receive enable
                              //   <o.8>    TXE: Transmit enable
                              //   <o.7>    LBE: Loop-back enable 
                              //   <o.2>    SIRLP: IrDA SIR low power mode
                              //   <o.1>    SIREN: SIR enable
                              //   <o.0>    UARTEN: UART enable
                              // </h>
  __IO uint32_t UARTIFLS;     // <h> Interrupt FIFO Level Select
                              //   <o.3..5> RXIFLSEL: Receive interrupt FIFO level select
                              //     <0=> >= 1/8 full 
                              //     <1=> >= 1/4 full 
                              //     <2=> >= 1/2 full 
                              //     <3=> >= 3/4 full 
                              //     <4=> >= 7/8 full 
                              //     <5=> reserved 
                              //     <6=> reserved 
                              //     <7=> reserved 
                              //   <o.0..2> TXIFLSEL: Transmit interrupt FIFO level select
                              //     <0=> <= 1/8 full 
                              //     <1=> <= 1/4 full 
                              //     <2=> <= 1/2 full 
                              //     <3=> <= 3/4 full 
                              //     <4=> <= 7/8 full 
                              //     <5=> reserved 
                              //     <6=> reserved 
                              //     <7=> reserved 
                              // </h>
  __IO uint32_t UARTIMSC;     // <h> Interrupt Mask Set / Clear
                              //   <o.10>   OEIM: Overrun error interrupt mask
                              //   <o.9>    BEIM: Break error interrupt mask
                              //   <o.8>    PEIM: Parity error interrupt mask
                              //   <o.7>    FEIM: Framing error interrupt mask
                              //   <o.6>    RTIM: Receive interrupt mask
                              //   <o.5>    TXIM: Transmit interrupt mask
                              //   <o.4>    RXIM: Receive interrupt mask
                              //   <o.3>    DSRMIM: nUARTDSR modem interrupt mask
                              //   <o.2>    DCDMIM: nUARTDCD modem interrupt mask
                              //   <o.1>    CTSMIM: nUARTCTS modem interrupt mask
                              //   <o.0>    RIMIM: nUARTRI modem interrupt mask
                              // </h>
  __IO uint32_t UARTRIS;      // <h> Raw Interrupt Status <r>
                              //   <o.10>   OERIS: Overrun error interrupt status <r>
                              //   <o.9>    BERIS: Break error interrupt status <r>
                              //   <o.8>    PERIS: Parity error interrupt status <r>
                              //   <o.7>    FERIS: Framing error interrupt status <r>
                              //   <o.6>    RTRIS: Receive timeout interrupt status <r>
                              //   <o.5>    TXRIS: Transmit interrupt status <r>
                              //   <o.4>    RXRIS: Receive interrupt status <r>
                              //   <o.3>    DSRRMIS: nUARTDSR modem interrupt status <r>
                              //   <o.2>    DCDRMIS: nUARTDCD modem interrupt status <r>
                              //   <o.1>    CTSRMIS: nUARTCTS modem interrupt status <r>
                              //   <o.0>    RIRMIS: nUARTRI modem interrupt status <r>
                              // </h>
  __IO uint32_t UARTMIS;      // <h> Masked Interrupt Status <r>
                              //   <o.10>   OEMIS: Overrun error masked interrupt status <r>
                              //   <o.9>    BEMIS: Break error masked interrupt status <r>
                              //   <o.8>    PEMIS: Parity error masked interrupt status <r>
                              //   <o.7>    FEMIS: Framing error masked interrupt status <r>
                              //   <o.6>    RTMIS: Receive timeout masked interrupt status <r>
                              //   <o.5>    TXMIS: Transmit masked interrupt status <r>
                              //   <o.4>    RXMIS: Receive masked interrupt status <r>
                              //   <o.3>    DSRMMIS: nUARTDSR modem masked interrupt status <r>
                              //   <o.2>    DCDMMIS: nUARTDCD modem masked interrupt status <r>
                              //   <o.1>    CTSMMIS: nUARTCTS modem masked interrupt status <r>
                              //   <o.0>    RIMMIS: nUARTRI modem masked interrupt status <r>
                              // </h>
  __O  uint32_t UARTICR;      // <h> Interrupt Clear <w>
                              //   <o.10>   OEIC: Overrun error interrupt clear <w>
                              //   <o.9>    BEIC: Break error interrupt clear <w>
                              //   <o.8>    PEIC: Parity error interrupt clear <w>
                              //   <o.7>    FEIC: Framing error interrupt clear <w>
                              //   <o.6>    RTIC: Receive timeout interrupt clear <w>
                              //   <o.5>    TXIC: Transmit interrupt clear <w>
                              //   <o.4>    RXIC: Receive interrupt clear <w>
                              //   <o.3>    DSRMIC: nUARTDSR modem interrupt clear <w>
                              //   <o.2>    DCDMIC: nUARTDCD modem interrupt clear <w>
                              //   <o.1>    CTSMIC: nUARTCTS modem interrupt clear <w>
                              //   <o.0>    RIMIC: nUARTRI modem interrupt clear <w>
                              // </h>
  __IO uint32_t UARTDMACR;    // <h> DMA Control
                              //   <o.2>    DMAONERR: DMA on error
                              //   <o.1>    TXDMAE: Transmit DMA enable
                              //   <o.0>    RXDMAE: Receive DMA enable
                              // </h>
} UART_TypeDef;
// </g>

#pragma no_anon_unions


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/*------------------------- CPU FPGA memory map ------------------------------*/
#define FLASH_BASE            (0x00000000UL)
#define RAM_BASE              (0x20000000UL)
#define RAM_FPGA_BASE         (0x1EFF0000UL)
#define CPU_CFG_BASE          (0xDFFF0000UL)

#define CPU_SYS_BASE          (CPU_CFG_BASE  + 0x00000)
#define UART3_BASE            (CPU_CFG_BASE  + 0x05000)

/*------------------------- DUT FPGA memory map ------------------------------*/
#define APB_BASE              (0x40000000UL)
#define AHB_BASE              (0x4FF00000UL)
#define DMC_BASE              (0x60000000UL)
#define SMC_BASE              (0xA0000000UL)

#define TIM0_BASE             (APB_BASE      + 0x02000)
#define TIM2_BASE             (APB_BASE      + 0x03000)
#define DUT_SYS_BASE          (APB_BASE      + 0x04000)
#define UART0_BASE            (APB_BASE      + 0x06000)
#define UART1_BASE            (APB_BASE      + 0x07000)
#define UART2_BASE            (APB_BASE      + 0x08000)
#define UART4_BASE            (APB_BASE      + 0x09000)


/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
/*------------------------- CPU FPGA Peripherals -----------------------------*/
#define CPU_SYS               ((CPU_SYS_TypeDef *)  CPU_SYS_BASE)
#define UART3                 ((   UART_TypeDef *)    UART3_BASE)
/*------------------------- DUT FPGA Peripherals -----------------------------*/
#define DUT_SYS               ((DUT_SYS_TypeDef *)  DUT_SYS_BASE)
#define TIM0                  ((    TIM_TypeDef *)     TIM0_BASE)
#define TIM2                  ((    TIM_TypeDef *)     TIM2_BASE)
#define UART0                 ((   UART_TypeDef *)    UART0_BASE)
#define UART1                 ((   UART_TypeDef *)    UART1_BASE)
#define UART2                 ((   UART_TypeDef *)    UART2_BASE)
#define UART4                 ((   UART_TypeDef *)    UART4_BASE)

#endif  // __MPS_CM3_H__
