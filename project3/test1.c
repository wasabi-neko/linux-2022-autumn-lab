#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SYS_GET_CPU_NUMBER 451

int main()
{
    int retval = 0;
    
    for (int i = 0; i < 10; i++) {
        retval = syscall(SYS_GET_CPU_NUMBER);
        printf("%d\n", retval);
        sleep(120);
    }

    return 0;
}