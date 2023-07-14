/*连接kernel.o和loader.o并给到kernel.bin*/
ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

 /*从不同的文件中选择各节，将他们组合成新的section*/
SECTIONS
{
    . = 0X0100000;
    .text :
    {
        *(.multiboot)
        *(.boot*)
        *(.rodata)
    }

    .data :
    {
        start_ctors= .;
        KEEP(*( .init_array ));
        KEEP(*(SORT_BY_INTI_PRIORITY( .init_array.*)));
        end_ctors= .;

        *(.data)
    }

    .bss :
    {
        *(.bss)
    }
    /DISCARD/ :
    {
        *(.fini_array*)
        *(.comment)
    }
}