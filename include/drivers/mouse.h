#ifndef __MYOS__DRIVERS__MOUSE_H
#define __MYOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>

namespace myos
{
    namespace drivers
    {
        class MouseEventHandler
        {
            int8_t x,y;
            public:
                MouseEventHandler();
                virtual void OnActivate();
                virtual void OnMouseDown(myos::common::unit8_t button); //pressed
                virtual void OnMouseUp(myos::common::unit8_t button); //released
                virtual void OnMouseMove(int x,int y);
        }

        class MouseDriver:public myos::hardwarecommunication::InterruptHandler,public Driver
        {
            myos::hardwarecommunication::Port8Bit dataport;
            myos::hardwarecommunication::Port8Bit commandport;
            myos::common::unit8_t buffer[3];
            myos::common::unit8_t offset;
            myos::common::unit8_t buttons;
            MouseEventHandler* handler;
        public:
            MouseDriver(myos::hardwarecommunication::InterruptManager *mannager,MouseEventHandler* handler);
            ~MouseDriver();
            virtual unit32_t InterruptHandler(unit32_t esp);
            virtual void Activate();
        };
    }
}

#endif