#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SYS_N_START 452
#define SYS_N_STOP 453

unsigned long long fib(unsigned long long n)
{
    if (n <= 1) {
        return 1;
    } else {
        return fib(n-1) + fib(n-2);
    }
}

int main()
{
    struct timespec ts;
    ts.tv_nsec = 1000;
    ts.tv_sec = 0;

    long retval = 0;
    unsigned long long b = 1;

    syscall(SYS_N_START);

    for (int i = 0; i < 10000; i++) {
        nanosleep(&ts, &ts);
        b = fib(26);
    }

    printf("%llu\n", b);
    retval = syscall(SYS_N_STOP);

    printf("\n\nnum: %ld\n", retval);

    return 0;
}