#include <libc/stdint.h>
#include <libc/stdio.h>
#include <multiboot2.h>
#include <gdt.h>
#include <io.h>


struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {

    GDT_Initialize();

    printf("Hello World!\n");

    return kernel_main();
}
