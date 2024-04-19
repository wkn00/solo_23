#include <isr.h>
#include <idt.h>
#include <gdt.h>
#include <io.h>
#include <libc/stdio.h>
#include <libc/stddef.h>


ISRHandler g_ISRHandlers[256];

static const char* const g_Exceptions[] = {
    "Divide by zero error",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception ",
    "",
    "",
    "",
    "",
    "",
    "",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    ""
};

void ISR_InitializeGates();

void ISR_Initialize()
{
    ISR_InitializeGates();
    for (int i = 0; i < 256; i++)
        IDT_EnableGate(i);
    IDT_DisableGate(0x80);
}

void __attribute__((cdecl)) ISR_Handler(Registers* regs) {
    // Check if a handler is registered and call it
    if (g_ISRHandlers[regs->interrupt] != NULL) {
        g_ISRHandlers[regs->interrupt](regs);
        outb(0x20, 0x20); // Acknowledge the interrupt
    } else {
        // Fallback: handle unregistered interrupts or print an error message
        printf("Unhandled exception %d %s\n", regs->interrupt, g_Exceptions[regs->interrupt]);
        printf("  interrupt=0x%x  errorcode=%x\n", regs->interrupt, regs->error);
        printf("KERNEL PANIC!\n");
        Panic();
    }
}

void ISR_RegisterHandler(int interrupt, ISRHandler handler)
{
    g_ISRHandlers[interrupt] = handler;
    IDT_EnableGate(interrupt);
}