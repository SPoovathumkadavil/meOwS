
#include "system/timer.h"
#include "system/inlasm.h"
#include <system/cpu/isr.h>
#include <nstd/avoidance.h>

uint32_t tick = 0;

static void timer_callback(registers_t *regs)
{
    tick++;
    UNUSED(regs);
}

void init_timer(uint32_t frequency)
{
    // Firstly, register our timer callback.
    register_interrupt_handler(IRQ0, &timer_callback);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    unsigned int divisor = 1193180 / frequency;

    // Send the command byte.
    outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    unsigned char l = (unsigned char)(divisor & 0xFF);
    unsigned char h = (unsigned char)((divisor >> 8) & 0xFF);

    // Send the frequency divisor.
    outb(0x40, l);
    outb(0x40, h);
}
