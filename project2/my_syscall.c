/*my_syscall.c*/
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include "my_syscall.h"

long my_sys_hello_world(int val)
{
    return syscall(NR_SYS_HELLO_WORLD, val);
}

long my_sys_my_virt_phy(unsigned long *user_vaddrs, size_t len_vaddr, unsigned long *result)
{
    return syscall(NR_SYS_MY_VIRT_PHY, user_vaddrs, len_vaddr, result);

}