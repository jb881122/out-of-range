#include "config.h"

bootloader_config configs[] = {
    {
        .code_crc = 0x0DE7CE16,
        .name = "G730AUCUANE2",
        .img_base = 0x88E00000,
        .img_end = 0x89000000,
        .max_boot_img_size = 10485760,
        .mmc_boot_fifo_read = 0x88E05670,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEA,
        .mmc_boot_main = 0x88E06804,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E1383C,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E0FA28,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88EA5B30,
        .boot_name_ptr = 0x88E13AC8,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    },
    {
        .code_crc = 0x3FB96300,
        .name = "G730AUCUBNG4",
        .img_base = 0x88E00000,
        .img_end = 0x89000000,
        .max_boot_img_size = 10485760,
        .mmc_boot_fifo_read = 0x88E056AC,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xE8,
        .mmc_boot_main = 0x88E06850,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E13B2C,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E0FB4C,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88EBEB14,
        .boot_name_ptr = 0x88E14198,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    }
};

size_t num_configs = sizeof(configs) / sizeof(bootloader_config);
