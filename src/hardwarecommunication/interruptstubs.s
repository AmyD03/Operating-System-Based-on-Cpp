.set IRQ_BASE, 0X20

.section .text

.extern _ZN4myos21hardwarecommunication16InterruptManager15HandlerInterruptEhj

.macro HandleException num


int_bottom:
    pushl %esp
    push (interruptnumber)
    call _ZN4myos21hardwarecommunication16InterruptManager15HandlerInterruptEhj
    