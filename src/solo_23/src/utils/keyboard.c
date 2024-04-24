#include <keyboard.h>
#include <isr.h>
#include <libc/stdio.h>
#include <libc/stdbool.h>
#include <io.h>
#include <pic.h>

#define PS2_DATA 0x60
#define SCANCODE_KEY_RELEASE_BIT 0x80

enum SCANCODE_CONTROL {
    SCANCODE_CONTROL_LSHIFT = 0x2A,
    SCANCODE_CONTROL_RSHIFT = 0x36,
    SCANCODE_CONTROL_LCTRL = 0x1D,
    SCANCODE_CONTROL_RCTRL = 0xE01D, // Part of extended scancode sequence
    SCANCODE_CAPSLOCK = 0x3A,
    SCANCODE_BACKSPACE = 0x0E,
    SCANCODE_NEWLINE = 0x1C,
};

unsigned char kbdus[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
    '9', '0', '-', '=', '\b', /* Backspace */
    '\t', /* Tab */
    'q', 'w', 'e', 'r', /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0, /* 29 - Left Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
    '\'', '`', 0, /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
    'm', ',', '.', '/', 0, /* Right shift */
    '*',
    0, /* Alt */
    ' ', /* Space bar */
    0, /* Caps lock */
    0, 0, 0, 0, 0, 0, 0, 0,
    0, /* F1 to F10 */
    0, 0, /* 69 - Num lock, Scroll Lock */
    0, 0, 0, '-', 0, 0, '+',
    0, 0, 0, 0, 0, 0, 0, /* End to F12 */
    0, /* All other keys are undefined */
};

static bool ShiftActive = false;
static bool CapsLockActive = false;

// Checks if the character is an alphabetic letter
int isalpha(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Converts a character to uppercase if it's a lowercase letter
int toupper(int c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
}

void handle_key(uint8_t scancode, bool press) {
    if (scancode >= 128) return; // Ignore if scancode is out of bounds

    switch (scancode) {
        case SCANCODE_CONTROL_LSHIFT:
        case SCANCODE_CONTROL_RSHIFT:
            ShiftActive = press;
            break;
        case SCANCODE_BACKSPACE: // Scancode for Backspace
            if (press) {
                delete();  // Call your backspace function
            }
            break;
        case SCANCODE_NEWLINE:
            if (press) {
                printf("\nwael_os> ");
            }
            break;
        case SCANCODE_CAPSLOCK:
            if (press) CapsLockActive = !CapsLockActive;
            break;
        default:
            if (press && kbdus[scancode] != 0) {
                bool uppercase = (ShiftActive ^ CapsLockActive) && isalpha(kbdus[scancode]);
                char c = uppercase ? toupper(kbdus[scancode]) : kbdus[scancode];
                putc(c);
            }
            break;
    }
}

static bool extended_scancode = false;

void keyboard_handler(Registers* regs) {
    uint8_t scancode = inb(PS2_DATA);

    // Check for extended scancode prefix
    if (scancode == 0xE0) {
        extended_scancode = true;
    } else if (extended_scancode) {
        extended_scancode = false; // Reset flag for next key press
        // Handle extended scancode
        if (scancode == 0x53) {
            if (!(scancode & SCANCODE_KEY_RELEASE_BIT)) {
                delete();  // Call delete function
            }
        }
    } else {
        if (scancode & SCANCODE_KEY_RELEASE_BIT) {
            scancode &= ~(SCANCODE_KEY_RELEASE_BIT);
            handle_key(scancode, false);
        } else {
            handle_key(scancode, true);
        }
    }
}

void KEYBOARD_Initialize() {
    // Register the keyboard handler for interrupt 33
    ISR_RegisterHandler(33, keyboard_handler);
}

// This code here will run when the timer ticks. frequency is defined in init_timer()
void timer_handler(Registers* regs) {
}

void write_text(const char* str, unsigned char color) {
    volatile char* video = (volatile char*)0xB8000;  // Video memory start
    while (*str != 0) {
        *video++ = *str++;   // Character byte
        *video++ = color;    // Color byte
    }
}