#include <stdio.h>

#include <kernel/tty.h>
#include <arch/i386/multiboot.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <arch/i386/irq.h>
#include <arch/i386/timer.h>
#include <arch/i386/keyboard.h>
#include <arch/i386/mm.h>

void kernel_main(uint32_t mboot_magic, void *mboot_header) {
    if (mboot_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Error: We weren't booted by a compliant bootloader!\n");
        return;
    }

    multiboot_info_t *mboot_hdr = (multiboot_info_t *)mboot_header;

    if ((mboot_hdr->flags & (1<<6)) == 0) {
        printf("Error: No Multiboot memory map was provided!\n");
        return;
    }

    init_mm(mboot_hdr, (uint32_t)mboot_hdr, (uint32_t)(mboot_hdr + sizeof(multiboot_info_t)));

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

    uint32_t new_frame = allocate_frame();
    uint32_t new_frame_addr = mmap_read(new_frame, MMAP_GET_ADDR);
    printf("Frame allocated at: 0x%x\n", new_frame_addr);
    new_frame = allocate_frame();
    new_frame_addr = mmap_read(new_frame, MMAP_GET_ADDR);
    printf("Frame allocated at: 0x%x\n", new_frame_addr);
    new_frame = allocate_frame();
    new_frame_addr = mmap_read(new_frame, MMAP_GET_ADDR);
    printf("Frame allocated at: 0x%x\n", new_frame_addr);
    new_frame = allocate_frame();
    new_frame_addr = mmap_read(new_frame, MMAP_GET_ADDR);
    printf("Frame allocated at: 0x%x\n", new_frame_addr);
    new_frame = allocate_frame();
    new_frame_addr = mmap_read(new_frame, MMAP_GET_ADDR);
    printf("Frame allocated at: 0x%x\n", new_frame_addr);

    void *buffer = kalloc(20000);
    printf("Buffer allocated at: 0x%x\n", buffer);

    new_frame = allocate_frame();
    new_frame_addr = mmap_read(new_frame, MMAP_GET_ADDR);
    printf("Frame allocated at: 0x%x\n", new_frame_addr);

    while (1) {}
}
