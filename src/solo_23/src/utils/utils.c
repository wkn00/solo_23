#include <utils.h> //

unsigned long long __udivdi3(unsigned long long dividend, unsigned long long divisor) {
    unsigned long long quotient = 0, qbit = 1;
    if (divisor == 0) {
        return -1; // Handle division by zero appropriately
    }
    while (divisor < dividend && !(divisor & 0x8000000000000000)) {
        divisor <<= 1;
        qbit <<= 1;
    }
    while (qbit) {
        if (dividend >= divisor) {
            dividend -= divisor;
            quotient += qbit;
        }
        divisor >>= 1;
        qbit >>= 1;
    }
    return quotient;
}

unsigned long long __umoddi3(unsigned long long dividend, unsigned long long divisor) {
    unsigned long long remainder = dividend;
    unsigned long long quotient = __udivdi3(dividend, divisor);
    remainder -= quotient * divisor;
    return remainder;
}
