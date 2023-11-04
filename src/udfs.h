#ifndef _UDFS_H
#define _UDFS_H

#define UDF(x) (0xE7F000F0 + ((x) & 0xF) + (((x) & 0xFFF0) << 4))

/* mmc_boot_fifo_read_ptr */
#define UDF_MBFRP 0

/* mmc_boot_fifo_read_len */
#define UDF_MBFRL 1

/* undef_inst_handler_ptr */
#define UDF_UIHP 2

/* undef_inst_handler_orig */
#define UDF_UIHO 3

/* loaded_boot_img */
#define UDF_LBI 4

/* boot_img_len */
#define UDF_BIL 5

/* scratch_addr */
#define UDF_SA 6

/* unified_addr */
#define UDF_UA 7

/* mmc_boot_fifo_read */
#define UDF_MBFR 8

/* mmc_boot_main */
#define UDF_MBM 9

/* boot_linux_from_mmc */
#define UDF_BLFM 10

/* mmc_sdc1_base */
#define UDF_MSB 11

/* boot_from_recovery */
#define UDF_BFR 12

/* boot_name_ptr */
#define UDF_BNP 13

/* check_sig_ptr */
#define UDF_CSP 14

/* check_sig_patch_len */
#define UDF_CSPL 15

/* check_sig_patch */
#define UDF_CSP1 16
#define UDF_CSP2 17

/* orig_bytes */
#define UDF_OB 18

#define NUM_UDFS 19

#endif
