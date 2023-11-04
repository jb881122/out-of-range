#include "udfs.h"

.text

start:
    /* Fix the bytes we clobbered getting here */
    ldr r9, mmc_boot_fifo_read_ptr
    adr r10, orig_bytes
    ldr r7, mmc_boot_fifo_read_len
    bl copy_bytes

    /* Restore the undefined opcode handler as well */
    ldr r9, undef_inst_handler_ptr
    ldr r8, undef_inst_handler_orig
    str r8, [r9]

    /* Finish the stalled MMC read in a scratch location */
    ldr r0, scratch_addr
    mov r1, #0x04000000  /* 64 MB, way larger than any known aboot range */
    mov r2, #0
    ldr r9, mmc_boot_fifo_read
    blx r9

    /* Re-initialize the MMC controller */
    mov r0, #1
    ldr r1, mmc_sdc1_base
    ldr r9, mmc_boot_main
    blx r9

    /* Check if we're loading from another partition or not */
    ldr r10, loaded_boot_img
    ldrb r8, [r10, #3]
    cmp r8, #2
    beq new_partition

    /* Fix the boot header magic */
    ldr r9, loaded_boot_img
    adr r10, boot_magic
    mov r7, #8
    bl copy_bytes

    /* Copy the boot image to an out-of-the-way address */
    ldr r9, scratch_addr
    ldr r10, loaded_boot_img
    ldr r7, boot_img_len
    bl copy_bytes

    /* Copy the boot header to the unified location */
    ldr r9, unified_addr
    mov r6, r9
    ldr r10, scratch_addr
    mov r7, #0x800
    bl copy_bytes

    /* Copy the kernel to its proper location */
    ldr r9, [r6, #0xC]
    ldr r7, [r6, #0x8]
    bl page_boundary
    bl copy_bytes

    /* Copy the ramdisk to its proper location */
    ldr r9, [r6, #0x14]
    ldr r7, [r6, #0x10]
    bl page_boundary
    bl copy_bytes

    /* Copy the second image to its proper location */
    ldr r9, [r6, #0x1C]
    ldr r7, [r6, #0x18]
    bl page_boundary
    bl copy_bytes

    /* Merge paths and finish booting */
    b finish_boot

new_partition:
    /* Don't boot to recovery (we're not patching that name) */
    ldr r9, boot_from_recovery
    mov r8, #0
    str r8, [r9]

    /* Patch boot partition name */
    ldr r9, boot_name_ptr
    ldr r8, loaded_boot_img
    add r8, #8
    str r8, [r9]

    /* Patch check_sig to always succeed */
    ldr r9, check_sig_ptr
    adr r10, check_sig_patch
    ldr r7, check_sig_patch_len
    bl copy_bytes

finish_boot:
    /* Call the bootloader */
    ldr r9, boot_linux_from_mmc
    blx r9

    /* If it returned, it failed. Hang here */
    b .

/* r7 = # of bytes, r9 = dest, r10 = src */
copy_bytes:
    cmp r7, #0
    beq copy_bytes_done
copy_bytes_loop:
    ldrb r8, [r10], #1
    strb r8, [r9], #1
    subs r7, #1
    bne copy_bytes_loop
copy_bytes_done:
    bx lr

/* This assumes the page size is 0x800 */
/* r7 = byte offset */
page_boundary:
    cmp r7, #0
    beq page_boundary_done
    sub r7, r7, #1
    mov r7, r7, LSR #11
    add r7, r7, #1
    mov r7, r7, LSL #11
page_boundary_done:
    bx lr

/* These variables are known at assemble-time */
boot_magic:
    .ascii "ANDROID!"

.align

/* These variables will be filled out when the code is inserted into a boot image */
mmc_boot_fifo_read_ptr:
    .word UDF(UDF_MBFRP)
mmc_boot_fifo_read_len:
    .word UDF(UDF_MBFRL)
undef_inst_handler_ptr:
    .word UDF(UDF_UIHP)
undef_inst_handler_orig:
    .word UDF(UDF_UIHO)
loaded_boot_img:
    .word UDF(UDF_LBI)
boot_img_len:
    .word UDF(UDF_BIL)
scratch_addr:
    .word UDF(UDF_SA)
unified_addr:
    .word UDF(UDF_UA)
mmc_boot_fifo_read:
    .word UDF(UDF_MBFR)
mmc_boot_main:
    .word UDF(UDF_MBM)
boot_linux_from_mmc:
    .word UDF(UDF_BLFM)
mmc_sdc1_base:
    .word UDF(UDF_MSB)
boot_from_recovery:
    .word UDF(UDF_BFR)
boot_name_ptr:
    .word UDF(UDF_BNP)
check_sig_ptr:
    .word UDF(UDF_CSP)
check_sig_patch_len:
    .word UDF(UDF_CSPL)
check_sig_patch:
    .word UDF(UDF_CSP1), UDF(UDF_CSP2)

/* This should be at the end, since the length varies */
orig_bytes:
    .word UDF(UDF_OB)
