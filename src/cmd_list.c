#include "cmd_list.h"
#include "config.h"

#include <stdio.h>
#include <stddef.h>

int cmd_list_main(int argc, char *argv[]) {
    /* Unused arguments */
    (void)argc;
    (void)argv;

    printf("Supported bootloaders: ");
    for(size_t i = 0; i < num_configs; i++) {
        printf("%s", configs[i].name);
        if(i != num_configs - 1) {
            printf(", ");
        }
    }
    printf("\n");

    return 0;
}
