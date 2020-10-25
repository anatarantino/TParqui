#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

uint64_t syscalls(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);

#endif