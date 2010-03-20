/***********************************************************************
 * $Id:: lpc_arm922t_cp15_driver.h 6 2007-08-27 20:47:57Z kevinw       $
 *
 * Project: ARM926EJS CPU driver
 *
 * Description:
 *     This file contains driver support for the MMU and cache
 *     coprocessor (15) of the ARM926EJS.
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

#ifndef LPC_ARM926EJS_DRIVER_H
#define LPC_ARM926EJS_DRIVER_H

#include "lpc_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***********************************************************************
 * ARM 926EJS MMU Initialization typedefs
 **********************************************************************/

/* ARM 926EJS MMU Translation table structure */
typedef struct
{
  UNS_32 vidx[ARM926EJS_TT_ENTRIES];
} TRANSTABLE_T;

/* ARM 926EJS MMU Coarse page table type */
typedef struct
{
  UNS_32 vidx[ARM926EJS_CPT_ENTRIES];
} CPAGETABLE_T;

/* ARM 926EJS MMU Fine page table type */
typedef struct
{
  UNS_32 vidx[ARM926EJS_FPT_ENTRIES];
} FPAGETABLE_T;

/***********************************************************************
 * UNS_32 num_sections: number of 1MByte sections >=1 for all blocks
 *     except last; last = 0
 * UNS_32 virt_addr: as required, base Virtual address for block
 * UNS_32 phys_addr: as required, PT address or Section address
 * UNS_32 entry is composed of the following 'or'd' together:
 *     access_perm:  ARM926EJS_L1D_AP_x (x = SVC_ONLY, USR_RO, ALL)
 *     domain:   ARM926EJS_L1D_DOMAIN(n) as applicable
 *     cacheable:  ARM926EJS_L1D_CACHEABLE if applicable
 *     write_buffered:  ARM926EJS_L1D_BUFFERABLE if applicable
 *     descriptor_type: ARM926EJS_L1D_TYPE_x (x = FAULT, PAGE, SECTION)
 **********************************************************************/
typedef const struct
{
  UNS_32 num_sections; /* Number of 1MByte sections */
  UNS_32 virt_addr;    /* Virtual address of section */
  UNS_32 phys_addr;    /* Physical address of section */
  /* Section attributes - an 'OR'ed combination of ARM926EJS_L1D_AP_x,
     ARM926EJS_L1D_DOMAIN, ARM926EJS_L1D_CACHEABLE,
     ARM926EJS_L1D_BUFFERABLE, and ARM926EJS_L1D_TYPE_x */
  UNS_32 entry;
} TT_SECTION_BLOCK_T;

/***********************************************************************
 * ARM 926EJS CPU driver functions
 **********************************************************************/

/* Return a physical address for a passed virtual address */
UNS_32 arm926_map_virtual_to_physical(void *addr);

/* Get a virtual address from a passed physical address */
void * arm926_map_physical_to_virtual(UNS_32 addr);

/* Force cache coherence between memory and cache for the selected
   address range */
void arm926_force_cache_coherence(UNS_32 *start_adr,
                                  UNS_32 *end_adr);

/* Setup MMU page tables */
BOOL_32 arm926_init_mmu_trans_table(TRANSTABLE_T *tt,
                                    TT_SECTION_BLOCK_T *ttsbp);

/* Set the virtual address of the MMU table */
void arm926_set_vmmu_addr(UNS_32 *addr);

/* Return the physical address of the MMU translation table */
UNS_32 *arm926_get_ttb(void);

/* Force an data cache flush */
void arm926_dcache_flush(void);

/* Force an write buffer flush */
void arm926_write_buffer_flush(void);

/* Checks to see if the MMU is enabled */
BOOL_32 arm926_mmu_enabled(void);

/* Return the current value of MMU Coprocessor(CP15) Control register*/
UNS_32 arm926_get_mmu_control_reg(void);

/* Set MMU Coprocessor(CP15) Control register*/
void arm926_set_mmu_control_reg(UNS_32 mmu_reg);

/* Enable/Disable MMU */
void arm926_set_mmu(BOOL_32 enable);

/* Invalidates the Instruction and Data caches */
void arm926_invalidate_cache(void);

/* Invalidates the Translation Lookaside Buffers */
void arm926_invalidate_tlb(void);

/* Sets the first-level translation table base address */
void arm926_set_transtable_base(UNS_32 addr);

/* Enables or disables the instruction cache */
void arm926_set_icache(BOOL_32 enable);

/* Enables or disables the data cache */
void arm926_set_dcache(BOOL_32 enable);

/* Define the access permissions for the 16 MMU domains. */
void arm926_set_domain_access(UNS_32 dac);

#ifdef __cplusplus
}
#endif

#endif /* LPC_ARM926EJS_CP15_DRIVER_H */
