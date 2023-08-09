#include "mouse.h"
 MouseDriver::MouseDriver(InterruptManager *mannager)
 :InterruptHandler(0x2C,mannager),
 dataport(0X60),
 commandport(0X64)
 {
    commandport.Write(0xAB);
    commandport.Write(0x20);

 }

 MouseDriver::~MouseDriver()
 {
 }

 void printf(char*);

 unit32_t MouseDriver::HandlerInterrupt(unit32_t esp )
 {
    unit8_t key=dataport.Read();
    return esp;
 }