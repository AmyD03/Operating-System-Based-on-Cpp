#include "mouse.h"
 MouseDriver::MouseDriver(InterruptManager *mannager)
 :InterruptHandler(0x2C,mannager),
 dataport(0X60),
 commandport(0X64)
 {
   
 }

 MouseDriver::~MouseDriver()
 {
 }

 void printf(char*);
 
 void MouseDriver::Activate()
 {
   unit16_t* VideoMemory = (unit16_t*)0xb8000;
   offset = 0;
   buttons = 0;
   x = 40;
   y = 12;
   VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                        | (VideoMemory[80*y+x] & 0x0F00) >> 4
                        | (VideoMemory[80*y+x] & 0x00FF);
    commandport.Write(0xAB);
    commandport.Write(0x20);
    unit8_t status = dataport.Read() | 2;
    commandport.Write(0x60);
    dataport.Write(status);

    commandport.Write(0xD4);
    dataport.Write(0xF4);
    dataport.Read();
 }

 unit32_t MouseDriver::HandlerInterrupt(unit32_t esp )
 {
    unit8_t key=dataport.Read();
    return esp;
 }