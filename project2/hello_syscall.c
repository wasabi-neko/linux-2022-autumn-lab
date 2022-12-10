#define _GNU_SOURCE     /* for RTLD_NEXT */
#include <stdio.h>
#include <dlfcn.h>

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int global = 1;

int main()
{
    int a = 10;
    int b = 10;

    long retval;
    unsigned long *vaddr = (unsigned long *) malloc(sizeof(unsigned long));
    unsigned long *paddr = (unsigned long *) malloc(sizeof(unsigned long));
    
    retval = syscall(449, 48763);
    printf("%ld\n", retval);

    *vaddr = (unsigned long) &a;
    retval = syscall(450, vaddr, 1, paddr);
    printf("%ld\n", retval);
    printf("vaddr: %014lx\npaddr: %014lx\n", *vaddr, *paddr);

    *vaddr = (unsigned long) &b;
    retval = syscall(450, vaddr, 1, paddr);
    printf("%ld\n", retval);
    printf("vaddr: %014lx\npaddr: %014lx\n", *vaddr, *paddr);

    *vaddr = (unsigned long) &global;
    retval = syscall(450, vaddr, 1, paddr);
    printf("%ld\n", retval);
    printf("vaddr: %014lx\npaddr: %014lx\n", *vaddr, *paddr);
    
    int *heap = (int*) malloc(sizeof(unsigned long));
    *vaddr = (unsigned long) heap;
    retval = syscall(450, vaddr, 1, paddr);
    printf("%ld\n", retval);
    printf("vaddr: %014lx\npaddr: %014lx\n", *vaddr, *paddr);
    free(heap);

    return 0;
}