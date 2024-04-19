#include <libc/stdint.h>
#include <libc/stdio.h>
#include <multiboot2.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <io.h>
#include <pic.h>
#include <keyboard.h>

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();



int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    printf("Starting kernel initialization...\n");
    
    printf("Initializing GDT...\n");
    // GDT
    GDT_Initialize();

    printf("Remapping PIC...\n");
    PIC_remap(0x20, 0x28);

    printf("Initializing IDT...\n");
    // IDT
    IDT_Initialize();

    printf("Initializing ISR...\n");
    // ISR
    ISR_Initialize();

    printf("Enabling keyboard interrupt...\n");

    IRQ_clear_mask(1); 

    printf("System initialization complete.\n Hello World!\n");

    //Keyboard
    init_timer();
    init_keyboard_input();
    asm volatile ("sti"); // Enable interrupts like PIT timer, keyboard etc.
    clrscr(); // Clear the screen

    printf("wael_os> "); 

    return kernel_main();
}
