#include <stdio.h>

#include <kernel/tty.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <arch/i386/irq.h>
#include <arch/i386/timer.h>
#include <arch/i386/keyboard.h>

void kernel_main(void) {
    terminal_initialize();
    init_gdt();
    printf("GDT initialized\n");
    init_idt();
    printf("IDT initialized\n");
    init_irq();
    printf("IRQ initialized\n");

    timer_phase(100);
    init_timer();
    printf("Timer initialized\n");

    init_keyboard();
    printf("Keyboard initialized\n");

    printf("Waiting 100 ticks\n");
    timer_wait(100);
    printf("Finished waiting\n");

    while (1) {}
}
