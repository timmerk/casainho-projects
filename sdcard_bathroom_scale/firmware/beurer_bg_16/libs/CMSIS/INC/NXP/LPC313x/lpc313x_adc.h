/***********************************************************************
* $Id:: lpc313x_adc.h 1180 2008-09-11 19:32:40Z pdurgesh              $
*
* Project: LPC313X 10-bit Analog-to-Digital Converter definitions
*
* Description:
*     This file contains the structure definitions and manifest
*     constants for the LPC313x chip family component:
*         10-bit Analog-to-Digital Converter (ADC 10B)
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/

#ifndef LPC313X_ADC_H
#define LPC313X_ADC_H

#include "lpc_types.h"
#include "lpc313x_chip.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***********************************************************************
* 10-bit Analog-to-Digital Converter (ADC 10B) Register Structures
**********************************************************************/

/* 10-bit Analog-to-Digital Converter Module Register Structure */
typedef volatile struct
{

  volatile UNS_32  r0_reg;              // 0x00: Digital conversion data with respect to analog input channel
  volatile UNS_32  r1_reg;              // 0x04: Digital conversion data with respect to analog input channel
  volatile UNS_32  r2_reg;              // 0x08: Digital conversion data with respect to analog input channel
  volatile UNS_32  r3_reg;              // 0x0C: Digital conversion data with respect to analog input channel
  volatile UNS_32  r4_reg;              // 0x10: Digital conversion data with respect to analog input channel
  volatile UNS_32  r5_reg;              // 0x14: Digital conversion data with respect to analog input channel
  volatile UNS_32  r6_reg;              // 0x18: Digital conversion data with respect to analog input channel
  volatile UNS_32  r7_reg;              // 0x1C: Digital conversion data with respect to analog input channel
  volatile UNS_32  con_reg;             // 0x20: ADC Control register
  volatile UNS_32  csel_res_reg;        // 0x24: ADC Channel Selection and Resolution register
  volatile UNS_32  int_enable_reg;      // 0x28: ADC Interrupt Enable register
  volatile UNS_32  int_status_reg;      // 0x2C: ADC Interrupt Status register
  volatile UNS_32  int_clear_reg;       // 0x30: ADC Interrupt Clear register
  volatile UNS_32  _d3;                     // 0x34: Dummy regs

} ADC_REGS_T;

#ifdef __cplusplus
}
#endif

#endif /* LPC313X_ADC_H */
