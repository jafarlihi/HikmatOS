.global copy_page_physical
.type copy_page_physical, @function
copy_page_physical:
    push %ebx
    pushf

    cli

    mov 12(%esp), %ebx
    mov 16(%esp), %ecx

    mov %cr0, %edx
    and $0x7fffffff, %edx
    mov %edx, %cr0

    mov $1024, %edx

.loop:
    mov (%ebx), %eax
    mov %eax, (%ecx)
    add $4, %ebx
    add $4, %ebx
    dec %edx
    jnz .loop

    mov %cr0, %edx
    or  %edx, 0x80000000
    mov %edx, %cr0

    popf
    pop %ebx
    ret

