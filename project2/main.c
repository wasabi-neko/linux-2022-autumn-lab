#include <stdio.h>
#include "my_syscall.h"
#include "get_layout.h"


int main()
{
    struct layout_var *var, *phy_var;

    var = get_layout_var();
    if (!var) {
        printf("layout_var malloc failed\n");
        return -1;
    }

    phy_var = layout_var_to_phy(var);
    if (!phy_var) {
        free(var);
        printf("get physical failed\n");
        return -1;
    }


    printf("----- virtual address: ----------\n");
    print_layout_var(var);
    printf("------------------------------\n");

    printf("----- physical address: ----------\n");
    print_layout_var(phy_var);
    printf("------------------------------\n");

    free(var);
    free(phy_var);
    return 0;
}