#ifndef SYSCALLDISPATCHER_H
#define SYSCALLDISPATCHER_H

#include <stdint.h>

typedef struct
{
      uint64_t rax, rdi, rsi, rdx, r10, r8, r9;
} t_registers;

uint64_t sysCallDispatcher();

#endif