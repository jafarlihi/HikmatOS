#include <stdint.h>
#include <string.h>

#include <arch/i386/idt.h>

extern void idt_flush(uint32_t);

typedef struct idt_entry {
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) idt_ptr_t;

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

static void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;
    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags = flags;
}

void init_idt() {
    idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_ptr.base = (uint32_t)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

    idt_flush((uint32_t)&idt_ptr);
}

