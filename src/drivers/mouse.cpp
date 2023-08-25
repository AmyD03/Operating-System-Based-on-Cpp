#include <drivers/mouse.h>

using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;

MouseEventHandler::MouseEventHandler()
{
}

void MouseEventHandler::OnActivate()
{

}

void MouseEventHandler::OnMouseDown(unit8_t button)
{
}

void OnMouseUp(unit8_t button)
{
}
void OnMouseMove(int x,int y)
{
}

 MouseDriver::MouseDriver(InterruptManager *mannager,MouseEventHandler* handler)
 :InterruptHandler(0x2C,mannager),
 dataport(0X60),
 commandport(0X64)
 {
   this->handler = handler;
 }

 MouseDriver::~MouseDriver()
 {
 }

 void printf(char*);
 
 void MouseDriver::Activate()
 {
   offset = 0;
   buttons = 0;
   commandport.Write(0xAB);
   commandport.Write(0x20);
   unit8_t status = dataport.Read() | 2;
   commandport.Write(0x60);
   dataport.Write(status);

   commandport.Write(0xD4);
   dataport.Write(0xF4);
   dataport.Read();
 }

 unit32_t MouseDriver::HandlerInterrupt(unit32_t esp)
 {
   unit8_t key=commandport.Read();
   if(!(status & 0x20))
      return esp;

   buffer[offset] = dataport.Read();

   if(handler == 0)
         return esp;

   offset = (offset+1)%3;
   if(offset == 0)
   {
      if(buffer[1]!=0 || buffer[2]!=0)
      {
         handler->OnMouseMove(buffer[1],-buffer[2]);
      }
      for(unit8_t i=0;i<3;i++)
      {
         if((buffer[0] & (0x1<<1)) !=(button &(0x1<<1)))
         {
            if(buttons & (0x1<<1))
               handler->OnMouseUp(i+1);
            else
               handler->OnMouseDown(i+1);
         }
      }
      buttons = buffer[0];
   }
   return esp;
 }