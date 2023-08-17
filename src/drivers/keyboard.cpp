#include "keyboard.h"

class KeyboardEventHandler:: KeyboardEventHandler()
{

}
void  KeyboardEventHandler::OnKeyDown(char)
{

}
void  KeyboardEventHandler::OnKeyUp(char)
{

}

KeyboardDriver::KeyboardDriver(InterruptManager* manager,KeyboardEventHandler* handler)
:InterruptHandler(0x21,manager),
dataport(0x60),
commandport(0x64)
{
    this->handler = handler;
    /*while(commandport.Reand() & 0x1)
        dataport.Read();
    commandport.Write(0xAE); //告诉键盘开始发送/使用中断 active interrupts
    commandport.Write(0x20); //获得当前状况 get current state
    unit8_t status = (dataport.Read() | 1) & ~0下01;
    commandport.Write(0x60); //设置状态
    dataport.Write(status);

    dataport.Write(0xF4);*/
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
    if(handler == 0){
        return esp;
    }

    if(key < 0x80)
    {
        swtich(key)
        {
            case 0xFA: break;
            case 0x45: break;
            case 0xC5: break;
            case 0x1E: handler->OnKeyDown('a'); break;
            case 0x1F: handler->OnKeyDown('s'); break;
            case 0x20: handler->OnKeyDown('d'); break;
            case 0x21: handler->OnKeyDown('f'); break;
            case 0x22: handler->OnKeyDown('g'); break;
            case 0x23: handler->OnKeyDown('h'); break;
            case 0x24: handler->OnKeyDown('j'); break;
            case 0x25: handler->OnKeyDown('k'); break;
            case 0x26: handler->OnKeyDown('l'); break;
            
            case 0x2C: handler->OnKeyDown('y'); break;
            case 0x2D: handler->OnKeyDown('x'); break;
            case 0x2E: handler->OnKeyDown('c'); break;
            case 0x2F: handler->OnKeyDown('V'); break;
            case 0x30: handler->OnKeyDown('b'); break;
            case 0x31: handler->OnKeyDown('n'); break;
            case 0x32: handler->OnKeyDown('m'); break;
            case 0x33: handler->OnKeyDown(','); break;
            case 0x34: handler->OnKeyDown('.'); break;
            case 0x35: handler->OnKeyDown('-'); break;

            case 0x1C: handler->OnKeyDown('\n'); break;
            case 0x39: handler->OnKeyDown(' '); break;


            default:
                printf("KEYBOARD 0x");
                printfHex(key);
                break;
        }
    }
    return esp;
}