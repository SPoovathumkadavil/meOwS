
#ifndef _IRQ_H_
#define _IRQ_H_

#include <system/system.h>
#include <stddef.h>

extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();

static irq_handler_t irq_routines[16] = {NULL};

/*
 * Install an interupt handler for a hardware device.
 */
void irq_install_handler(int irq, irq_handler_t handler);

/*
 * Remove an interrupt handler for a hardware device.
 */
void irq_uninstall_handler(int irq);

/*
 * Remap interrupt handlers
 */
void irq_remap();

void irq_gates();

/*
 * Set up interrupt handler for hardware devices.
 */
void irq_install();

void irq_ack(int irq_no);

void irq_handler(struct regs *r);

#endif // _IRQ_H_
