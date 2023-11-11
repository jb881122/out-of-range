#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
    IT_THUMB,
    IT_ARM
} instr_type;

typedef struct bootloader_config {
    /* The output of running `oor -c` on the aboot image */
    uint32_t code_crc;

    /* The name of this bootloader version */
    char *name;

    /* The load address for the code
       Can be found in the aboot image header */
    uint32_t img_base;

    /* The address just after the end of aboot's memory range
       This is found in the range checks within boot_linux_from_mmc */
    uint32_t img_end;

    /* The size in bytes of the boot partition on this device */
    uint32_t max_boot_img_size;

    /* The size in bytes of the maximum amount of aboot code to store in
         a patched image
       It can be nice to shorten this to limit how much larger the patched
         image is than the original. However, shortening it too much will
         result in bugs as some code ends up corrupted
       For a conservative, reliable approach, store the entirety of the code by
         setting this very large, e.g. 0x10000000 */
    uint32_t max_stored_code;

    /* The address of the mmc_boot_fifo_read function
       Look for where the following string is printed:
         "Error No.%d: Failure on data transfer from the                 Card(RCA:%x)"
       The function whose return value is checked just before this should
         be it, having some loops and no function calls of its own */
    uint32_t mmc_boot_fifo_read;

    /* Whether the mmc_boot_fifo_read function uses ARM (all 4-byte) or Thumb
         (mostly 2-byte, some 4-byte) instructions */
    instr_type mmc_boot_fifo_read_instr;

    /* The code size in bytes of the mmc_boot_fifo_read function
       Found by taking the address just after the end of this function and
         subtracting the beginning address */
    uint32_t mmc_boot_fifo_read_len;

    /* The address of the mmc_boot_main function
       Look for where the following two strings are printed:
         "MMC Boot: Error Initializing MMC Card!!!"
         "MMC Boot: Failed detecting MMC/SDC @ slot%d"
       The function where these are printed should be the correct function */
    uint32_t mmc_boot_main;

    /* Whether the mmc_boot_main function uses ARM or Thumb instructions */
    instr_type mmc_boot_main_instr;

    /* The address of the boot_linux_from_mmc function
       This is where the following string is printed:
         "ERROR: Not valid address of boot-header" */
    uint32_t boot_linux_from_mmc;

    /* Whether the boot_linux_from_mmc function uses ARM or Thumb instructions */
    instr_type boot_linux_from_mmc_instr;

    /* The address of the check_sig function
       The boot_linux_from_mmc function prints the following string after
         checking the return value of two different functions:
         "kernel secure check fail."
       The check_sig function is the first of these two (where returning 0 = success) */
    uint32_t check_sig;

    /* Whether the check_sig function uses ARM or Thumb instructions */
    instr_type check_sig_instr;

    /* The address of the boot_from_recovery variable
       This is the variable checked by boot_linux_from_mmc before branching out to
         get the offset of either the "boot" or "recovery" partition */
    uint32_t boot_from_recovery;

    /* The location of the address constant that points to the boot partition name
       Not the address of the string itself, but the address of the word in
         boot_linux_from_mmc that contains its address */
    uint32_t boot_name_ptr;

    /* A valid address for loading a kernel
       This can be found in the header of an original boot image */
    uint32_t kernel_load_ptr;

    /* An out-of-the-way address to put things
       After boot_linux_from_mmc finds a valid "ANDROID!" magic string (not for
         unified boot, but the normal way), the next function that is called
         should simply return a fixed value
       That value is most likely the scratch address for the bootloader */
    uint32_t scratch_addr;

    /* The address where the boot_linux_from_mmc checks for a boot header
         for unified boot mode (usually img_base + 0xFF000) */
    uint32_t unified_addr;

    /* This value is dependent on the phone's SoC
       At several points in the bootloader, mmc_boot_main should be called with
         1 in r0 and this value in r1 */
    uint32_t mmc_sdc1_base;
} bootloader_config;

extern bootloader_config configs[];
extern size_t num_configs;

#endif
