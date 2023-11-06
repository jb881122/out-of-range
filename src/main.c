#include "cmd_patch.h"
#include "cmd_redirect.h"
#include "cmd_undo.h"
#include "cmd_verify.h"
#include "cmd_crc.h"
#include "cmd_list.h"

#include <stdio.h>
#include <string.h>
#include <stddef.h>

typedef struct {
    char *cmd_switch;
    char *description;
    char *syntax;
    int (*main_func)(int, char *[]);
} command;

int main(int argc, char *argv[]);

command commands[] = {
    {
        .cmd_switch = "-p",
        .description = "Patch a boot/recovery image to be bootable using a given bootloader",
        .syntax = "<aboot image> <boot image> <output file>",
        .main_func = cmd_patch_main
    },
    {
        .cmd_switch = "-r",
        .description = "Create an image telling the bootloader to boot from a different partition",
        .syntax = "<aboot image> <partition name> <output file>",
        .main_func = cmd_redirect_main
    },
    {
        .cmd_switch = "-u",
        .description = "Get the original boot image from an already-patched file",
        .syntax = "<patched image> <output file>",
        .main_func = cmd_undo_main
    },
    {
        .cmd_switch = "-v",
        .description = "Verify that the given image is patched for the given bootloader",
        .syntax = "<aboot image> <boot image>",
        .main_func = cmd_verify_main
    },
    {
        .cmd_switch = "-c",
        .description = "Get the CRC32 checksum of the code in an aboot image",
        .syntax = "<aboot image>",
        .main_func = cmd_crc_main
    },
    {
        .cmd_switch = "-l",
        .description = "List all supported bootloader versions",
        .syntax = "",
        .main_func = cmd_list_main
    }
};

size_t num_commands = sizeof(commands) / sizeof(command);

void print_help() {
    printf("OutOfRange: Load unsigned boot images on some Android devices with locked bootloaders\n");

    printf("\nCommands:\n");
    for(size_t i = 0; i < num_commands; i++) {
        printf("    %s: %s\n", commands[i].cmd_switch, commands[i].description);
    }

    printf("\nSyntax:\n");
    for(size_t i = 0; i < num_commands; i++) {
        printf("    oor %s %s\n", commands[i].cmd_switch, commands[i].syntax);
    }
}

int main(int argc, char *argv[]) {
    int ret = -2;

    if(argc < 2) {
        print_help();
        goto out;
    }

    for(size_t i = 0; i < num_commands; i++) {
        if(!strcmp(commands[i].cmd_switch, argv[1])) {
            ret = commands[i].main_func(argc, argv);
            goto out;
        }
    }

    print_help();

out:
    return ret;
}
