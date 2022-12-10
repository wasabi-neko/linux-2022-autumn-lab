/* my_syscall.h */
#include <stdlib.h>

#ifndef HEADER_MY_SYSCALL_H
#define HEADER_MY_SYSCALL_H

#define NR_SYS_HELLO_WORLD 449
#define NR_SYS_MY_VIRT_PHY 450

long my_sys_hello_world(int val);
long my_sys_my_virt_phy(unsigned long *user_vaddrs, size_t len_vaddr, unsigned long *result);

#endif