#include <stdio.h>

#include <kernel/tty.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>

void kernel_main(void) {
    terminal_initialize();
    init_gdt();
    printf("GDT initialized\n");
    init_idt();
    printf("IDT initialized\n");
}
