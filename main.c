#include <stdio.h>
#include "squash.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return 1;
    }

    int result = squash_path(argv[1]);
    if (result == 0)
        puts(argv[1]);
    return result;
}
