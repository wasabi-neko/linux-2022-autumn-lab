#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int retval = 0;
    
    for (int i = 0; i < 10; i++) {
        retval = syscall(451);
        printf("%d\n", retval);
        sleep(2);
    }

    return 0;
}