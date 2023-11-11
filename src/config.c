#include "config.h"

bootloader_config configs[] = {
    {
        .code_crc = 0x3572BE4A,
        .name = "G730AUCUAMH4",
        .img_base = 0x88E00000,
        .img_end = 0x89000000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x40000,
        .mmc_boot_fifo_read = 0x88E0564C,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEA,
        .mmc_boot_main = 0x88E067F0,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E136FC,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E0F994,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88EA5B00,
        .boot_name_ptr = 0x88E13988,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    },
    {
        .code_crc = 0x0DE7CE16,
        .name = "G730AUCUANE2",
        .img_base = 0x88E00000,
        .img_end = 0x89000000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x40000,
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
        .code_crc = 0x0185B80B,
        .name = "G730AUCUBNG3",
        .img_base = 0x88E00000,
        .img_end = 0x89000000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x40000,
        .mmc_boot_fifo_read = 0x88E056AC,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEA,
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
    },
    {
        .code_crc = 0x3FB96300,
        .name = "G730AUCUBNG4",
        .img_base = 0x88E00000,
        .img_end = 0x89000000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x40000,
        .mmc_boot_fifo_read = 0x88E056AC,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEA,
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
    },
    {
        .code_crc = 0xB62DCDC6,
        .name = "G730AUCSBNG5",
        .img_base = 0x88E00000,
        .img_end = 0x89000000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x40000,
        .mmc_boot_fifo_read = 0x88E056AC,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEA,
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
    },
    {
        .code_crc = 0x246AE13B,
        .name = "G730VVRUBNE2",
        .img_base = 0x88E00000,
        .img_end = 0x89000000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x40000,
        .mmc_boot_fifo_read = 0x88E056AC,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEA,
        .mmc_boot_main = 0x88E06850,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E13B2C,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E0FB4C,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88ECAB14,
        .boot_name_ptr = 0x88E14198,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    },
    {
        .code_crc = 0xD5DB08AD,
        .name = "G730VVRSBQA1",
        .img_base = 0x88E00000,
        .img_end = 0x89000000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x40000,
        .mmc_boot_fifo_read = 0x88E056AC,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEA,
        .mmc_boot_main = 0x88E06850,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E13B2C,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E0FB4C,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88ECAB14,
        .boot_name_ptr = 0x88E14198,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    },
    {
        .code_crc = 0xD9B200AB,
        .name = "I545VRUAME7",
        .img_base = 0x88E00000,
        .img_end = 0x89100000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x60000,
        .mmc_boot_fifo_read = 0x88E056A0,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEC,
        .mmc_boot_main = 0x88E06864,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E13F04,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E0FFF8,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88F39B10,
        .boot_name_ptr = 0x88E14554,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    },
    {
        .code_crc = 0x623207FE,
        .name = "I545VRUDMI1",
        .img_base = 0x88E00000,
        .img_end = 0x89100000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x60000,
        .mmc_boot_fifo_read = 0x88E056A0,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEC,
        .mmc_boot_main = 0x88E06864,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E1419C,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E1024C,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88F45B10,
        .boot_name_ptr = 0x88E14774,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    },
    {
        .code_crc = 0x743C810E,
        .name = "I545VRUEMJ7",
        .img_base = 0x88E00000,
        .img_end = 0x89100000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x60000,
        .mmc_boot_fifo_read = 0x88E056B8,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEC,
        .mmc_boot_main = 0x88E0687C,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E14274,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E102B8,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88F51B10,
        .boot_name_ptr = 0x88E1484C,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    },
    {
        .code_crc = 0x95210636,
        .name = "I545VRUEMK2",
        .img_base = 0x88E00000,
        .img_end = 0x89100000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x60000,
        .mmc_boot_fifo_read = 0x88E056B8,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEC,
        .mmc_boot_main = 0x88E0687C,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E14274,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E102B8,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88F51B10,
        .boot_name_ptr = 0x88E1484C,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    },
    {
        .code_crc = 0xCBB5AEC4,
        .name = "I545VRUFNC5",
        .img_base = 0x88E00000,
        .img_end = 0x89100000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x60000,
        .mmc_boot_fifo_read = 0x88E056BC,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEC,
        .mmc_boot_main = 0x88E06880,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E144A4,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E10400,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88F5EB10,
        .boot_name_ptr = 0x88E14AB0,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    },
    {
        .code_crc = 0x76912BE0,
        .name = "I545VRUFNG6",
        .img_base = 0x88E00000,
        .img_end = 0x89100000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x60000,
        .mmc_boot_fifo_read = 0x88E056DC,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEC,
        .mmc_boot_main = 0x88E068A0,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E144C4,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E10420,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88F5EB10,
        .boot_name_ptr = 0x88E14AD0,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    },
    {
        .code_crc = 0xE398ED56,
        .name = "I545VRUFNK1",
        .img_base = 0x88E00000,
        .img_end = 0x89100000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x60000,
        .mmc_boot_fifo_read = 0x88E056DC,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEC,
        .mmc_boot_main = 0x88E068A0,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E144C4,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E10420,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88F5EB10,
        .boot_name_ptr = 0x88E14AD0,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    },
    {
        .code_crc = 0x7ECC3B24,
        .name = "I545VRUGOC1",
        .img_base = 0x88E00000,
        .img_end = 0x89100000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x60000,
        .mmc_boot_fifo_read = 0x88E05700,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEC,
        .mmc_boot_main = 0x88E068D0,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E145F8,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E10420,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88F3AB40,
        .boot_name_ptr = 0x88E14BEC,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    },
    {
        .code_crc = 0xDD1037CA,
        .name = "I545VRUGOF1",
        .img_base = 0x88E00000,
        .img_end = 0x89100000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x60000,
        .mmc_boot_fifo_read = 0x88E05750,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEC,
        .mmc_boot_main = 0x88E06914,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E14758,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E106E8,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88F4AB10,
        .boot_name_ptr = 0x88E14D9C,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    },
    {
        .code_crc = 0x57B06CB6,
        .name = "I545VRSGPL1",
        .img_base = 0x88E00000,
        .img_end = 0x89100000,
        .max_boot_img_size = 10485760,
        .max_stored_code = 0x60000,
        .mmc_boot_fifo_read = 0x88E05750,
        .mmc_boot_fifo_read_instr = IT_THUMB,
        .mmc_boot_fifo_read_len = 0xEC,
        .mmc_boot_main = 0x88E06914,
        .mmc_boot_main_instr = IT_THUMB,
        .boot_linux_from_mmc = 0x88E14758,
        .boot_linux_from_mmc_instr = IT_THUMB,
        .check_sig = 0x88E106E8,
        .check_sig_instr = IT_THUMB,
        .boot_from_recovery = 0x88F4AB10,
        .boot_name_ptr = 0x88E14D9C,
        .kernel_load_ptr = 0x81000000,
        .scratch_addr = 0x90000000,
        .unified_addr = 0x88EFF000,
        .mmc_sdc1_base = 0x12400000
    }
};

size_t num_configs = sizeof(configs) / sizeof(bootloader_config);
