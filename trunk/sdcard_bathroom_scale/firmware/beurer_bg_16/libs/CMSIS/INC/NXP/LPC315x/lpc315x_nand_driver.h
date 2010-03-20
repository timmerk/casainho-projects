/***********************************************************************
 * $Id::$
 *
 * Project: LPC315x NAND controller driver
 *
 * Description:
 *     This file contains driver support for the LPC315x NAND
 *     controller.
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
 *********************************************************************/

#ifndef LPC315X_NAND_DRIVER_H
#define LPC315X_NAND_DRIVER_H

#include "lpc315x_nandc.h"
#include "lpc_nandflash_params.h"

#ifdef __cplusplus
extern "C"
{
#endif
/***********************************************************************
 * NAND device structure and it defines
 **********************************************************************/


/***********************************************************************
 * MCI device configuration commands (IOCTL commands and arguments)
 **********************************************************************/

/* MCI device commands (IOCTL commands) */
typedef enum
{
  NAND_GET_CSD,
  NAND_GET_EXT_CSD
} NAND_IOCTL_CMD_T;




/***********************************************************************
 * MCI driver API functions
 **********************************************************************/

/* Open the MCI */
INT_32 nand_open(void *ipbase, INT_32 arg);

/* Close the MCI */
STATUS nand_close(INT_32 devid);

/* MCI configuration block */
STATUS nand_ioctl(INT_32 devid,
                  INT_32 cmd,
                  INT_32 arg);

/* MCI read function - read all 16 data registers */
INT_32 nand_read_blocks(INT_32 devid,
                        void *buffer,
                        INT_32 start_block,
                        INT_32 end_block);

/* MCI write function - writes all 16 data registers */
INT_32 nand_write_blocks(INT_32 devid,
                         void *buffer,
                         INT_32 start_block,
                         INT_32 end_block);

/***********************************************************************
 * Other NAND driver functions
 **********************************************************************/


#ifdef __cplusplus
}
#endif

#endif /* LPC315X_NAND_DRIVER_H */
