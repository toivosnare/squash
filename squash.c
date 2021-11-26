#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SQUASH_MALLOC(sz) malloc(sz)
#define SQUASH_FREE(ptr) free(ptr)

typedef struct node {
    char *start;
    size_t length;
    struct node *prev;
    struct node *next;
} node;

typedef enum {
    EMPTY,
    DOT,
    DOTDOT,
    NORMAL
} node_type;

#ifdef DEBUG
static void print_node_list(const node *n, bool backwards) {
    while (n != NULL) {
        for (char *c = n->start; c < n->start + n->length; ++c)
            putchar(*c);
        putchar('\n');
        n = backwards ? n->prev : n->next;
    }
}
#endif

static node_type type(const char *start, size_t length) {
    if (length == 0)
        return EMPTY;
    if (length == 1 && *start == '.')
        return DOT;
    if (length == 2 && start[0] == '.' && start[1] == '.')
        return DOTDOT;
    return NORMAL;
}

int squash_path(char *path) {
    if (strlen(path) == 0)
        return 0;
    if (path[0] != '/') {
        fprintf(stderr, "Path must be absolute.\n");
        return 2;
    }

    node *head = NULL;
    node *tail = NULL;
    char *start = path + 1;
    
    for (char *p = start; ; ++p) {
        if (*p != '/' && *p != '\0')
            continue;
        
        size_t length = p - start;
        switch (type(start, length))
        {
        case EMPTY:
        case DOT:
            break;
        case DOTDOT:
            if (tail) {
                node *old_tail = tail;
                tail = tail->prev;
                if (tail)
                    tail->next = NULL;
                else
                    head = NULL;
                SQUASH_FREE(old_tail);
            }
            break;
        case NORMAL:
            node *next = SQUASH_MALLOC(sizeof(node));
            if (!next) {
                fprintf(stderr, "Memory allocation failed!\n");
                return 3;
            }
            next->start = start;
            next->length = length;
            next->prev = tail;
            next->next = NULL;
            if (tail)
                tail->next = next;
            tail = next;
            if (!head)
                head = next;
            break;
        }
        if (*p == '\0')
            break;
        start = p + 1;
    }

#ifdef DEBUG
    print_node_list(head, false);
#endif

    node *n = head;
    char *p = path + 1;
    while (n != NULL) {
        if (p == n->start)
            p += n->length + 1;
        else {
            memcpy(p, n->start, n->length);
            p += n->length;
            *p++ = '/';
        }
        node *next = n->next;
        SQUASH_FREE(n);
        n = next;
    }
    *p = '\0';
    
    return 0;
}
