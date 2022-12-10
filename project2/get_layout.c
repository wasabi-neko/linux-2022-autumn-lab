#include <stdio.h>
#include <stdlib.h>
#include "get_layout.h"
#include "my_syscall.h"

struct layout_var {
    unsigned long code;
    unsigned long data;
    unsigned long bss;
    unsigned long lib;
    unsigned long stack;

    char _end_member;
};

char bss_var[10];
char data_var[] = "uuwuu";

void foo() {
    puts("Foo!\n");
}

void print_layout_var(struct layout_var *var)
{
    printf( \
        "code:  0x%014lx\n"
        "bss:   0x%014lx\n"
        "data:  0x%014lx\n"
        "stack: 0x%014lx\n"
        "lib:   0x%014lx\n",
        var->code,
        var->bss,
        var->data,
        var->stack,
        var->lib
    );
}

struct layout_var *get_layout_var()
{
    char stack_var = 1;
    char *heap_var = (char*) malloc(1);

    struct layout_var *result = (struct layout_var*) malloc(sizeof(struct layout_var));
    if (!result) {
        free(heap_var);
        return NULL;
    }

    result->code = (unsigned long) foo;
    result->bss = (unsigned long) bss_var;
    result->data = (unsigned long) data_var;
    result->stack = (unsigned long) &stack_var;
    result->lib = (unsigned long) puts;

    free(heap_var);
    return result;
}

struct layout_var *layout_var_to_phy(struct layout_var *var)
{
    struct layout_var *result = (struct layout_var*) malloc(sizeof(struct layout_var));
    if (!result)
        return NULL;
    
    size_t len = ((unsigned long)&(var->_end_member) - (unsigned long) var) / sizeof(unsigned long);
    if (my_sys_my_virt_phy(&var->code, len, &result->code)) {
        free(result);
        return NULL;
    }

    return result;
}
