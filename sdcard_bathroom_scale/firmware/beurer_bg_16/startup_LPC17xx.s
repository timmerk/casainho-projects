ARM GAS  startup_LPC17xx.s 			page 1


   1              	...
   1              	> .weak WDT_IRQHandler
   1              	> .set WDT_IRQHandler,Default_Handler
   1              	> .weak TIMER0_IRQHandler
   1              	> .set TIMER0_IRQHandler,Default_Handler
   1              	> .weak TIMER1_IRQHandler
   1              	> .set TIMER1_IRQHandler,Default_Handler
   1              	> .weak TIMER2_IRQHandler
   1              	> .set TIMER2_IRQHandler,Default_Handler
   1              	> .weak TIMER3_IRQHandler
   1              	> .set TIMER3_IRQHandler,Default_Handler
   1              	> .weak UART0_IRQHandler
   1              	> .set UART0_IRQHandler,Default_Handler
   1              	> .weak UART1_IRQHandler
   1              	> .set UART1_IRQHandler,Default_Handler
   1              	> .weak UART2_IRQHandler
   1              	> .set UART2_IRQHandler,Default_Handler
   1              	> .weak UART3_IRQHandler
   1              	> .set UART3_IRQHandler,Default_Handler
   1              	> .weak PWM1_IRQHandler
   1              	> .set PWM1_IRQHandler,Default_Handler
   1              	> .weak I2C0_IRQHandler
   1              	> .set I2C0_IRQHandler,Default_Handler
   1              	> .weak I2C1_IRQHandler
   1              	> .set I2C1_IRQHandler,Default_Handler
   1              	> .weak I2C2_IRQHandler
   1              	> .set I2C2_IRQHandler,Default_Handler
   1              	> .weak SPI_IRQHandler
   1              	> .set SPI_IRQHandler,Default_Handler
   1              	> .weak SSP0_IRQHandler
   1              	> .set SSP0_IRQHandler,Default_Handler
   1              	> .weak SSP1_IRQHandler
   1              	> .set SSP1_IRQHandler,Default_Handler
   1              	> .weak PLL0_IRQHandler
   1              	> .set PLL0_IRQHandler,Default_Handler
   1              	> .weak RTC_IRQHandler
   1              	> .set RTC_IRQHandler,Default_Handler
   1              	> .weak EINT0_IRQHandler
   1              	> .set EINT0_IRQHandler,Default_Handler
   1              	> .weak EINT1_IRQHandler
   1              	> .set EINT1_IRQHandler,Default_Handler
   1              	> .weak EINT2_IRQHandler
   1              	> .set EINT2_IRQHandler,Default_Handler
   1              	> .weak EINT3_IRQHandler
   1              	> .set EINT3_IRQHandler,Default_Handler
   1              	> .weak ADC_IRQHandler
   1              	> .set ADC_IRQHandler,Default_Handler
   1              	> .weak BOD_IRQHandler
   1              	> .set BOD_IRQHandler,Default_Handler
   1              	> .weak USB_IRQHandler
   1              	> .set USB_IRQHandler,Default_Handler
   1              	> .weak CAN_IRQHandler
   1              	> .set CAN_IRQHandler,Default_Handler
   1              	> .weak DMA_IRQHandler
   1              	> .set DMA_IRQHandler,Default_Handler
   1              	> .weak I2S_IRQHandler
   1              	> .set I2S_IRQHandler,Default_Handler
ARM GAS  startup_LPC17xx.s 			page 2


   1              	> .weak ENET_IRQHandler
   1              	> .set ENET_IRQHandler,Default_Handler
   1              	> .weak RIT_IRQHandler
   1              	> .set RIT_IRQHandler,Default_Handler
   1              	> .weak MCPWM_IRQHandler
   1              	> .set MCPWM_IRQHandler,Default_Handler
   1              	> .weak QEI_IRQHandler
   1              	> .set QEI_IRQHandler,Default_Handler
   1              	> .weak PLL1_IRQHandler
   1              	> .set PLL1_IRQHandler,Default_Handler
   1              	> .weak USBActivity_IRQHandler
   1              	> .set USBActivity_IRQHandler,Default_Handler
   1              	> .weak CANActivity_IRQHandler
   1              	> .set CANActivity_IRQHandler,Default_Handler
ARM GAS  startup_LPC17xx.s 			page 3


DEFINED SYMBOLS
   startup_LPC17xx.s:19     *ABS*:00000100 Stack_Size
   startup_LPC17xx.s:21     .stack:00000000 $d
   startup_LPC17xx.s:24     .stack:00000000 __cs3_stack_mem
                            *ABS*:00000100 __cs3_stack_size
   startup_LPC17xx.s:38     *ABS*:00001000 Heap_Size
   startup_LPC17xx.s:41     .heap:00000000 $d
   startup_LPC17xx.s:44     .heap:00000000 __cs3_heap_start
   startup_LPC17xx.s:48     .heap:00001000 __cs3_heap_end
   startup_LPC17xx.s:57     .cs3.interrupt_vector:00000000 __cs3_interrupt_vector_cortex_m
   startup_LPC17xx.s:141    .text:00000000 NMI_Handler
   startup_LPC17xx.s:147    .text:00000002 HardFault_Handler
   startup_LPC17xx.s:153    .text:00000004 MemManage_Handler
   startup_LPC17xx.s:159    .text:00000006 BusFault_Handler
   startup_LPC17xx.s:165    .text:00000008 UsageFault_Handler
   startup_LPC17xx.s:171    .text:0000000a SVC_Handler
   startup_LPC17xx.s:177    .text:0000000c DebugMon_Handler
   startup_LPC17xx.s:183    .text:0000000e PendSV_Handler
   startup_LPC17xx.s:189    .text:00000010 SysTick_Handler
   startup_LPC17xx.s:198    .text:00000012 WDT_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 TIMER0_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 TIMER1_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 TIMER2_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 TIMER3_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 UART0_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 UART1_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 UART2_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 UART3_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 PWM1_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 I2C0_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 I2C1_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 I2C2_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 SPI_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 SSP0_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 SSP1_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 PLL0_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 RTC_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 EINT0_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 EINT1_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 EINT2_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 EINT3_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 ADC_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 BOD_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 USB_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 CAN_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 DMA_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 I2S_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 ENET_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 RIT_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 MCPWM_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 QEI_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 PLL1_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 USBActivity_IRQHandler
   startup_LPC17xx.s:198    .text:00000012 CANActivity_IRQHandler
   startup_LPC17xx.s:124    .cs3.reset:00000000 __cs3_reset_cortex_m
   startup_LPC17xx.s:126    .cs3.reset:00000000 $t
   startup_LPC17xx.s:130    .cs3.reset:00000008 $d
ARM GAS  startup_LPC17xx.s 			page 4


             .ARM.exidx.cs3.reset:00000000 $d
   startup_LPC17xx.s:142    .text:00000000 $t
   startup_LPC17xx.s:198    .text:00000012 Default_Handler
                   .debug_aranges:0000000c $d

UNDEFINED SYMBOLS
__cs3_stack
__cs3_reset
SystemInit
_start
