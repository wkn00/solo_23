// The memory related functions in this file are based on Per-Arne Andersen's implementation found at https://perara.notion.site/IKT218-Advanced-Operating-Systems-2024-bfa639380abd46389b5d69dcffda597a

extern "C" {
    #include <libc/stdio.h>
    #include <libc/string.h>
    #include <memory.h>
    #include <isr.h>
    #include <io.h>
    #include <libc/stdio.h>
    #include <keyboard.h>
    #include <pit.h>
    
    int kernel_main(void);
}


// Existing global operator new overloads
void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

// Existing global operator delete overloads
void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

// Add sized-deallocation functions
void operator delete(void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}


int kernel_main(){
    clrscr();
    printf("Starting kernel initialization");

    for (int i = 0; i < 3; i++){
        putc('.');
        sleep_interrupt(100);
    }

    printf("\nInitializing GDT");

    for (int i = 0; i < 10; i++){
        putc('.');
        sleep_interrupt(100);
    }

    printf("\nRemapping PIC");

    for (int i = 0; i < 13; i++){
        putc('.');
        sleep_interrupt(100);
    }

    printf("\nInitializing IDT");

    for (int i = 0; i < 10; i++){
        putc('.');
        sleep_interrupt(100);
    }

    printf("\nInitializing ISR");

    for (int i = 0; i < 10; i++){
        putc('.');
        sleep_interrupt(100);
    }

    printf("\nEnabling PIT interrupt");

    for (int i = 0; i < 4; i++){
        putc('.');
        sleep_interrupt(100);
    }

    printf("\nEnabling keyboard interrupt");

    for (int i = 0; i < 3; i++){
        putc('.');
        sleep_interrupt(100);
    }

    printf("\nInitializing kernel memory");

    for (int i = 0; i < 4; i++){
        putc('.');
        sleep_interrupt(100);
    }

    printf("\nInitializing  paging");

    for (int i = 0; i < 10; i++){
        putc('.');
        sleep_interrupt(100);
    }

    printf("\nSystem initialization complete.");

    printf("\nprinting memory layout");

    for (int i = 0; i < 10; i++){
        putc('.');
        sleep_interrupt(100);
    }

    printf("\n");

    print_memory_layout();  

    printf("\nLoading Kernel.");

    for (int i = 0; i < 20; i++){
        putc('.');
        sleep_interrupt(400);
    }
    
    clrscr();

    for (int i = 0; i < 60; i++){
        putc('*');
        sleep_interrupt(50);
    }

    printf("\n    W     W     aaaa    eeeee   LLL         OOO     SSSS  \n"); 
    printf("    W     W    a    a   e       LLL        O   O   S      \n"); 
    printf("    W  W  W    aaaaaa   eeee    LLL        O   O    SSS   \n"); 
    printf("    W W W W    a    a   e       LLL        O   O       S  \n"); 
    printf("     W   W     a    a   eeeee   LLLLLL      OOO    SSSS   \n"); 

    for (int i = 0; i < 60; i++){
        putc('*');
        sleep_interrupt(10);
    }

    printf("\n");
    
    print_memory_layout();  

    printf("\n");

    int* number = (int*) malloc(4);
    *number = 12345;
    printf("%d", number);


    printf("\nwael_os> "); 


    while(true);
}