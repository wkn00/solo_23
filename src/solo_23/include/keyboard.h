#pragma once
#include <libc/stdint.h>
#include <pic.h>

void init_keyboard_input();
void init_timer();
void write_text(const char* str, unsigned char color);

#define ISR0 0 // Division by zero exception
#define ISR1 1 // Debug exception
#define ISR2 2 // Non maskable interrupt
#define ISR3 3 // Breakpoint exception
#define ISR4 4 // 'Into detected overflow'
#define ISR5 5 // Out of bounds exception
#define ISR6 6 // Invalid opcode exception
#define ISR7 7 // No coprocessor exception
#define ISR8 8 // Double fault (pushes an error code)
#define ISR9 9 // Coprocessor segment overrun
#define ISR10 10 // Bad TSS (pushes an error code)
#define ISR11 11 // Segment not present (pushes an error code)
#define ISR12 12 // Stack fault (pushes an error code)
#define ISR13 13 // General protection fault (pushes an error code)
#define ISR14 14 // Page fault (pushes an error code)
#define ISR15 15 // Unknown interrupt exception
#define ISR16 16 // Coprocessor fault
#define ISR17 17 // Alignment check exception
#define ISR18 18 // Machine check exception

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47