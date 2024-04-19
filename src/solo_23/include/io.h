#pragma once
#include <libc/stdint.h>

void __attribute__((cdecl)) outb(uint16_t port, uint8_t value);
uint8_t __attribute__((cdecl)) inb(uint16_t port);

uint8_t __attribute__((cdecl)) EnableInterrupts();
uint8_t __attribute__((cdecl)) DisableInterrupts();

void io_wait(void);

void __attribute__((cdecl)) Panic();
void __attribute__((cdecl)) crash_me();
