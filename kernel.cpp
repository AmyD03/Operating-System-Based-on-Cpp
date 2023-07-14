//kernel.cpp和bert.cpp一起编译成kernel.o
void printf(char* str)
{
    (unit16_t*)VideoMemory = (unit16_t*)0xb8000;
    for(int i = 0; str[i] != '\0'; ++i)
        VideoMemory[i] = str[i];
}
typedef void(*constructor){};
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructiors()
{
    for( constructor* i = &start_ctors; i != end_ctors; i++)
        (*i)();
}

/*extern "C":
    extern "C"的主要作用就是为了能够正确实现C++代码调用其他C语言代码。
    加上extern "C"后，会指示编译器这部分代码按C语言（而不是C++）的方式进行编译。
    由于C++支持函数重载，因此编译器编译函数的过程中会将函数的参数类型也加到编译后的代码中，而不仅仅是函数名；
    而C语言并不支持函数重载，因此编译C语言代码的函数时不会带上函数的参数类型，一般只包括函数名。
*/
extern "C" void kernelMain(void *multiboot_structure, unsigned int magicnumber)
{
    printf("Hello World!");
    //无限循环
    while(1);
}