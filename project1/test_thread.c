#define _GNU_SOURCE     /* for RTLD_NEXT */
#include <dlfcn.h>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

const int global_constant = 0xc8763; // .rodataa
char global_str[] = "Global Str.";  // Data segment
char global_var;  // Bss segment
void (*func_ptr)();

void foo() {  // Text segment
    printf("foo func here!\n");
}

void* func4thread1(void *arg) 
{
    unsigned long *vaddr = (unsigned long *) malloc(sizeof(unsigned long));
    unsigned long *paddr = (unsigned long *) malloc(sizeof(unsigned long));
    
    *vaddr = (unsigned long) malloc(1);
    long retval = syscall(450, vaddr, 1, paddr);
    printf("%ld\n", retval);
    printf("t1 heap: vaddr: %014lx\npaddr: %014lx\n", *vaddr, *paddr);
    fflush(stdout);

    pthread_exit(NULL);
    return 0;
}

void* func4thread2(void *arg) 
{
    unsigned long *vaddr = (unsigned long *) malloc(sizeof(unsigned long));
    unsigned long *paddr = (unsigned long *) malloc(sizeof(unsigned long));
    
    *vaddr = (unsigned long) malloc(1);
    long retval = syscall(450, vaddr, 1, paddr);
    printf("%ld\n", retval);
    printf("t2 heap: vaddr: %014lx\npaddr: %014lx\n", *vaddr, *paddr);
    fflush(stdout);

    pthread_exit(NULL);
    return 0;
}

int main(int argc, char **argv)
{

    pthread_t t1, t2;
    pthread_create(&t1, NULL, func4thread1, NULL);
    pthread_create(&t2, NULL, func4thread2, NULL);

    unsigned long *vaddr = (unsigned long *) malloc(sizeof(unsigned long));
    unsigned long *paddr = (unsigned long *) malloc(sizeof(unsigned long));
    
    *vaddr = (unsigned long) malloc(1);
    long retval = syscall(450, vaddr, 1, paddr);
    printf("%ld\n", retval);
    printf("main heap: vaddr: %014lx\npaddr: %014lx\n", *vaddr, *paddr);
    fflush(stdout);

    *vaddr = (unsigned long) malloc(1);
    retval = syscall(450, vaddr, 1, paddr);
    printf("%ld\n", retval);
    printf("main heap: vaddr: %014lx\npaddr: %014lx\n", *vaddr, *paddr);
    fflush(stdout);

    *vaddr = (unsigned long) malloc(1);
    retval = syscall(450, vaddr, 1, paddr);
    printf("%ld\n", retval);
    printf("main heap: vaddr: %014lx\npaddr: %014lx\n", *vaddr, *paddr);
    fflush(stdout);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

    return 0;
}