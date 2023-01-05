#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SYS_N_START 452
#define SYS_N_STOP 453

int main()
{
    struct timespec ts;
    ts.tv_nsec = 1000;
    ts.tv_sec = 0;

    long retval = 0;
    int b = 1;

    syscall(SYS_N_START);

    for (int i = 0; i < 1000000; i++) {
        printf("%d", b++);
        fflush(stdout);
        nanosleep(&ts, &ts);
    }

    retval = syscall(SYS_N_STOP);

    printf("\n\nnum: %ld\n", retval);

    return 0;
}