#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include "squash.h"

int main(int argc, char **argv) {
    char *path;
    char buffer[PATH_MAX];

    if (argc == 1) {
        if (!fgets(buffer, PATH_MAX, stdin)) {
            fprintf(stderr, "Read from stdin failed\n");
            return 1;
        }
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n')
            buffer[length - 1] = '\0';
        path = buffer;
    } else if (argc == 2) {
        path = argv[1];
    } else {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return 2;
    }

    int result = squash_path(path);
    if (result == 0)
        puts(path);
    return result;
}
