#include <libc/stdint.h>
#include <libc/stdio.h>
#include <multiboot2.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <io.h>
#include <pic.h>
#include <keyboard.h>
#include <memory.h>
#include <pit.h>

extern uint32_t end; 

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();


int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    
    // GDT
    GDT_Initialize();

    // PIC
    PIC_remap(0x20, 0x28);

    // IDT
    IDT_Initialize();

    // ISR
    ISR_Initialize();

    // IRQ
    IRQ_clear_mask(1); 

    // PIT
    PIT_Initialize();       

    // Keyboard
    KEYBOARD_Initialize();

    // Enable interrupts
    asm volatile ("sti"); 

    // Memory
    init_kernel_memory(&end);      

    // Paging
    Paging_Initialize();   

    return kernel_main();
}
