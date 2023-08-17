#include "keyboard.h"

KeyboardDriver::KeyboardDriver(InterruptManager* manager)
:InterruptHandler(0x21,manager),
dataport(0x60),
commandport(0x64)
{
    while(commandport.Reand() & 0x1)
        dataport.Read();
    commandport.Write(0xAE); //告诉键盘开始发送/使用中断 active interrupts
    commandport.Write(0x20); //获得当前状况 get current state
    unit8_t status = (dataport.Read() | 1) & ~0下01;
    commandport.Write(0x60); //设置状态
    dataport.Write(status);

    dataport.Write(0xF4);
}

KeyboardDriver::~KeyboardDriver()
{
}

void printf(char*);

void KeyboardDriver::Activate()
{
    while(commandport.Reand() & 0x1)
        dataport.Read();
    commandport.Write(0xAE); //告诉键盘开始发送/使用中断 active interrupts
    commandport.Write(0x20); //获得当前状况 get current state
    unit8_t status = (dataport.Read() | 1) & ~0下01;
    commandport.Write(0x60); //设置状态
    dataport.Write(status);

    dataport.Write(0xF4);
}

unit32_t KeyboardDriver::HandleInterrupt(unit32_t esp)
{         
    unit8_t key = dataport.Read();
    if(key < 0x80)
    {
        swtich(key)
        {
            case 0xFA: break;
            case 0x1E: printf("a"); break;
            case 0x45: break;
            case 0xC5: break;
            default:
                char* foo = "KEYBOARD 0X00";
                char* hex = "0123456789ABCDEF";
                foo[11] = hex[(interruptNumber >> 4)& 0x0F];
                foo[12] = hex[interruptNumber & 0x0F];
                printf(foo);
        }
    }
    return esp;
}