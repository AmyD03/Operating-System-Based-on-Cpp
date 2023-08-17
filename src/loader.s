;用于调用加载程序
;被编译成loader.o

.set MAGIC,0x1badb002  ;将MAGIC NUMBER放入文件中，以便引导加载程序将其作为内核接收
.set FLAGS,(1<<0 | 1<<1)
.set CHECKSUM, - (MAGIC + FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM
    
.section .text
;.section指示把代码划分成若干个段（Section）
;.text段保存代码
.extern kernelMain ;说明kernelMain是外部函数，调用时可以遍历所有文件找到该函数并使用它
.extern callConstructors
.global loader
loader:
    mov $kernel_stack, %esp ;将esp寄存器设置为的指针
    
    call callConstructors

    push %eax
    push %ebx
    call kernelMain
;无限循环
_stop:
    cli
    hlt
    jmp _stop
    ;cli :将IF置0，屏蔽掉“可屏蔽中断”，当可屏蔽中断到来时CPU不响应，继续执行原指令
    ;hlt:本指令是处理器“暂停”指令。
    ;jmp _stop : 命令跳转指令
    ;_stop:确保操作系统进入循环不会退出

.section .bss
.space 2*1024*1024 ;2MB
kernel_stack: