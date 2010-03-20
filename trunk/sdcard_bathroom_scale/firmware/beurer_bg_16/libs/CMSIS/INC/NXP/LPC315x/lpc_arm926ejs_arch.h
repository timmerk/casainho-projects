/***********************************************************************
 * $Id:: lpc_arm922t_arch.h 6 2007-08-27 20:47:57Z kevinw              $
 *
 * Project: General Utilities
 *
 * Description:
 *      This file contains constant and macro definitions specific
 *      to the ARM926EJS architecture.
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
#ifndef LPC_ARM926EJS_ARCH_H
#define LPC_ARM926EJS_ARCH_H


/***********************************************************************
 * MMU Control register fields
***********************************************************************/

/* ARM926EJS MMU control register MMU enable bit */
#define ARM926EJS_MMU_CONTROL_M       0x00000001
/* ARM926EJS MMU control register alignment fault bit */
#define ARM926EJS_MMU_CONTROL_A       0x00000002
/* ARM926EJS MMU control register data cache bit */
#define ARM926EJS_MMU_CONTROL_C       0x00000004
/* ARM926EJS MMU control register system protection bit */
#define ARM926EJS_MMU_CONTROL_S       0x00000100
/* ARM926EJS MMU control register ROM protection bit */
#define ARM926EJS_MMU_CONTROL_R       0x00000200
/* ARM926EJS MMU control register instruction cache bit */
#define ARM926EJS_MMU_CONTROL_I       0x00001000
/* ARM926EJS MMU control register vector relocation bit */
#define ARM926EJS_MMU_CONTROL_V       0x00002000
/* ARM926EJS MMU control register round robin replacement bit */
#define ARM926EJS_MMU_CONTROL_RR      0x00004000
/* ARM926EJS MMU control register L4 bit */
#define ARM926EJS_MMU_CONTROL_L4      0x00008000

/***********************************************************************
 * ARM920T/ARM926EJS MMU Cache type register fields
***********************************************************************/
/*  DCache Size */
#define ARM926EJS_MMU_DC_SIZE(n)      (((n) >> 18) & 0xF)
/*  ICache Size */
#define ARM926EJS_MMU_IC_SIZE(n)      (((n) >> 6) & 0xF)

/***********************************************************************
 * MMU Domain access control register fields
***********************************************************************/
/* ARM926EJS MMU domain register 'no access' ID field */
#define ARM926EJS_MMU_DN_NONE         0
/* ARM926EJS MMU domain register 'client access' ID field */
#define ARM926EJS_MMU_DN_CLIENT       1
/* ARM926EJS MMU domain register 'all access' ID field */
#define ARM926EJS_MMU_DN_MANAGER      3
/* ARM926EJS MMU domain register load macro for domain and access */
#define ARM926EJS_MMU_DN_ACCESS(n,m)  ((m & 0x3) << ((n) * 2))

/***********************************************************************
 * MMU fault status register fields
***********************************************************************/

/* ARM926EJS MMU fault status register fault domain load macro */
#define ARM926EJS_MMU_FSR_DOMAIN(n)   (((n) & 0xF0) >> 4)
/* ARM926EJS MMU fault status register fault type load macro */
#define ARM926EJS_MMU_FSR_TYPE(n)     ((n) & 0x0F)

/***********************************************************************
 * MMU Translation table register fields
***********************************************************************/

/* Number of entries in ARM926EJS Translation table */
#define ARM926EJS_TT_ENTRIES          4096
/* Size of the ARM926EJS Translation table */
#define ARM926EJS_TT_SIZE             (ARM926EJS_TT_ENTRIES * 4)
/* Number of entries in ARM926EJS coarse page table */
#define ARM926EJS_CPT_ENTRIES         256
/* Size of the ARM926EJS coarse page table */
#define ARM926EJS_CPT_SIZE            (ARM926EJS_CPT_ENTRIES * 4)
/* Mask to get the coarse page table index */
#define ARM926EJS_CPT_INDEX_MASK      (ARM926EJS_CPT_ENTRIES - 1)
/* Number of entries in ARM926EJS fine page table */
#define ARM926EJS_FPT_ENTRIES         1024
/* Size of the ARM926EJS fine page table */
#define ARM926EJS_FPT_SIZE            (ARM926EJS_FPT_ENTRIES * 4)
/* Mask to get the fine page table index */
#define ARM926EJS_FPT_INDEX_MASK      (ARM926EJS_FPT_ENTRIES - 1)
/* Level 1 translation table address mask */
#define ARM926EJS_TT_ADDR_MASK        0xFFFFC000

/***********************************************************************
 * MMU translating page table fields
***********************************************************************/

/* Level 1 Descriptor fields */
/* ARM926EJS MMU level 1 invalid page or section identifier */
#define ARM926EJS_L1D_TYPE_FAULT      0x00000000
/* ARM926EJS MMU level 1 coarse page identifier */
#define ARM926EJS_L1D_TYPE_CPAGE      0x00000001
/* ARM926EJS MMU level 1 fine page identifier */
#define ARM926EJS_L1D_TYPE_FPAGE      0x00000003
/* ARM926EJS MMU level 1 1MByte section identifier */
#define ARM926EJS_L1D_TYPE_SECTION    0x00000002
/* ARM926EJS MMU level 1 compatibility bit */
#define ARM926EJS_L1D_TYPE_PG_SN_MASK 0x00000003
/* ARM926EJS MMU level 1 page or section identifier */
#define ARM926EJS_L1D_COMP_BIT        0x00000010
/* ARM926EJS MMU level 1 page or section bufferable bit */
#define ARM926EJS_L1D_BUFFERABLE      0x00000004
/* ARM926EJS MMU level 1 page or section cacheable bit */
#define ARM926EJS_L1D_CACHEABLE       0x00000008
/* ARM926EJS MMU level 1 page or section domain load macro */
#define ARM926EJS_L1D_DOMAIN(n)       _SBF(5, ((n) & 0x0F))
/* ARM926EJS MMU level 1 section service access only bit */
#define ARM926EJS_L1D_AP_SVC_ONLY     0x00000400
/* ARM926EJS MMU level 1 section client read-only access only bit */
#define ARM926EJS_L1D_AP_USR_RO       0x00000800
/* ARM926EJS MMU level 1 section all access bit */
#define ARM926EJS_L1D_AP_ALL          0x00000C00
/* ARM926EJS MMU level 1 section address load macro */
#define ARM926EJS_L1D_SN_BASE_ADDR(n) _SBF(20, ((n) & 0x00000FFF))
/* ARM926EJS MMU level 2 large page address mask */
#define ARM926EJS_L2D_SN_BASE_MASK    0xFFF00000
/* ARM926EJS MMU level 1 coarse page address load macro */
#define ARM926EJS_L1D_CP_BASE_ADDR(n) _SBF(10, ((n) & 0x003FFFFF))
/* ARM926EJS MMU level 2 large page address mask */
#define ARM926EJS_L2D_CP_BASE_MASK    0xFFFFFC00
/* ARM926EJS MMU level 1 fine page address load macro */
#define ARM926EJS_L1D_FP_BASE_ADDR(n) _SBF(12, ((n) & 0x000FFFFF))
/* ARM926EJS MMU level 2 fine page address mask */
#define ARM926EJS_L2D_FP_BASE_MASK    0xFFFFF000

/* Level 2 Descriptor fields */
/* ARM926EJS MMU level 2 invalid page (fault) identifier */
#define ARM926EJS_L2D_TYPE_FAULT      0x00000000
/* ARM926EJS MMU level 2 large page (fault) identifier */
#define ARM926EJS_L2D_TYPE_LARGE_PAGE 0x00000001
/* ARM926EJS MMU level 2 small page (fault) identifier */
#define ARM926EJS_L2D_TYPE_SMALL_PAGE 0x00000002
/* ARM926EJS MMU level 2 tiny page (fault) identifier */
#define ARM926EJS_L2D_TYPE_TINY_PAGE  0x00000003
/* ARM926EJS MMU level 2 page mask */
#define ARM926EJS_L2D_TYPE_PAGE_MASK  0x00000003
/* ARM926EJS MMU level 2 page buffer enable bit */
#define ARM926EJS_L2D_BUFFERABLE      0x00000004
/* ARM926EJS MMU level 2 page cache enable bit */
#define ARM926EJS_L2D_CACHEABLE       0x00000008
/* ARM926EJS MMU level 2 section AP0 service access only bit */
#define ARM926EJS_L2D_AP0_SVC_ONLY    0x00000010
/* ARM926EJS MMU level 2 section AP0 client read-only access only bit */
#define ARM926EJS_L2D_AP0_USR_RO      0x00000020
/* ARM926EJS MMU level 2 section AP0 all access bit */
#define ARM926EJS_L2D_AP0_ALL         0x00000030
/* ARM926EJS MMU level 2 section AP1 service access only bit */
#define ARM926EJS_L2D_AP1_SVC_ONLY    0x00000040
/* ARM926EJS MMU level 2 section AP1 client read-only access only bit */
#define ARM926EJS_L2D_AP1_USR_RO      0x00000080
/* ARM926EJS MMU level 2 section AP1 all access bit */
#define ARM926EJS_L2D_AP1_ALL         0x000000C0
/* ARM926EJS MMU level 2 section AP2 service access only bit */
#define ARM926EJS_L2D_AP2_SVC_ONLY    _SBF(8,1)
/* ARM926EJS MMU level 2 section AP2 client read-only access only bit */
#define ARM926EJS_L2D_AP2_USR_RO      _SBF(8,2)
/* ARM926EJS MMU level 2 section AP2 all access bit */
#define ARM926EJS_L2D_AP2_ALL         _SBF(8,3)
/* ARM926EJS MMU level 3 section AP2 service access only bit */
#define ARM926EJS_L2D_AP3_SVC_ONLY    _SBF(10,1)
/* ARM926EJS MMU level 3 section AP2 client read-only access only bit */
#define ARM926EJS_L2D_AP3_USR_RO      _SBF(10,2)
/* ARM926EJS MMU level 3 section AP2 all access bit */
#define ARM926EJS_L2D_AP3_ALL         _SBF(10,3)
/* ARM926EJS MMU level 2 large page address load macro */
#define ARM926EJS_L2D_LPAGE_ADDR(n)   _SBF(16, ((n) & 0x0000FFFF)
/* ARM926EJS MMU level 2 large page address mask */
#define ARM926EJS_L2D_LPAGE_MASK      0xFFFF0000
/* ARM926EJS MMU level 2 small page address load macro */
#define ARM926EJS_L2D_SPAGE_ADDR(n)   _SBF(12, ((n) & 0x000FFFFF)
/* ARM926EJS MMU level 2 small page address mask */
#define ARM926EJS_L2D_SPAGE_MASK      0xFFFFF000
/* ARM926EJS MMU level 2 tiny page address load macro */
#define ARM926EJS_L2D_TPAGE_ADDR(n)   _SBF(10, ((n) & 0x003FFFFF)
/* ARM926EJS MMU level 2 tiny page address mask */
#define ARM926EJS_L2D_TPAGE_MASK      0xFFFFFC00

#endif /* LPC_ARM926EJS_ARCH_H */
