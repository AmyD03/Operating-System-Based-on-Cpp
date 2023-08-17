//kernel.cpp和bert.cpp一起编译成kernel.o
//使用8086汇编时，显示器或DOS窗口一行可以显示80个字符，总共25行，也就是说一个窗口可以显示80*25个字符，而这80*25个字符可以通过指定颜色属性的方式来做到彩色、高亮、闪烁、背景色等显示效果，80*25彩色字符模式显示缓冲区因此得名。
#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "keyboard.h"

void printf(char* str)
{
    (unit16_t*)VideoMemory = (unit16_t*)0xb8000;
    static unit8_t x=0,y=0;
    for(int i = 0; str[i] != '\0'; ++i){
        swtich(str[i]){
            case '\n':
                x=0;y++; //设置换行操作
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x])|str[i];
                x++;
                break;
        }
        
        if(x >= 80){
            y++;
            x=0;
        }
        if(y >= 25){ //如果y值超过25，遍历整个屏幕将所有内容置为空白
            for(y =0;y<25;y++){
                for(x=0;x<80;x++){
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x])|' ';
                    y=0;
                    x=0;
                }

            }
            
        }
    }
        
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


    KeyboardDriver keyboard(&interrupts);
    interrupts.Activate();
    //无限循环
    while(1);
}