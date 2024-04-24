#include <pit.h>
#include <isr.h>
#include <io.h>
#include <libc/stdio.h>
#include <libc/stdint.h>


volatile uint32_t tick = 0;                  

// The PIT handler
void pitHandler(Registers* regs) {
    tick++;                                     
}

// Returns the current tick
uint32_t getCurrentTick() {
    return tick;
}

// Initializes the PIT
void PIT_Initialize() {
    printf("Initializing PIT\n");
    outb(PIT_CMD_PORT, 0x36);                                      
    outb(PIT_CHANNEL0_PORT, (uint8_t)(DIVIDER & 0xFF));       
    outb(PIT_CHANNEL0_PORT, (uint8_t)((DIVIDER >> 8) & 0xFF));      

    ISR_RegisterHandler(32, pitHandler);
}


// Sleeps using busy-waiting
void sleep_busy(uint32_t ms) {
    uint32_t startTick = getCurrentTick();      
    uint32_t ticksToWait = ms * TICKS_PER_MS;   
    uint32_t endTick = startTick + ticksToWait; 

    if (endTick < startTick) {              
        
        while (getCurrentTick() >= startTick) { 
            
        }
        while (getCurrentTick() < endTick) {    
           
        }
    } else {                                  
        while (getCurrentTick() < endTick) {
           
        }
    }
}

// Sleeps using interrupts
void sleep_interrupt(uint32_t ms) {
    uint32_t startTick = getCurrentTick();     
    uint32_t ticksToWait = ms * TICKS_PER_MS;   
    uint32_t endTick = startTick + ticksToWait; 

    if (endTick < startTick) {                      
        
        while (getCurrentTick() >= startTick) {        
            asm volatile (
                "sti\n\t"                         
                "hlt\n\t"                            
            );
        }
        while (getCurrentTick() < endTick) {          
            asm volatile (
                "sti\n\t"                            
                "hlt\n\t"                           
            );
        }
    } else {                                           
        while (getCurrentTick() < endTick) {
            asm volatile (
                "sti\n\t"                              
                "hlt\n\t"                             
            );
        }
    }
}
