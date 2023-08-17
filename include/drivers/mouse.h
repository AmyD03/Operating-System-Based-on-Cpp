#ifndef __MOUSE_H
#define __MOUSE_H

#include "types.h"
#include "interrupts.h"
#include "port.h"
#include "driver.h"

class MouseEventHandler
{
    int8_t x,y;
    public:
        MouseEventHandler();
        virtual void OnActivate();
        virtual void OnMouseDown(unit8_t button); //pressed
        virtual void OnMouseUp(unit8_t button); //released
        virtual void OnMouseMove(int x,int y);
}

class MouseDriver:public InterruptHandler,public Driver
{
    Port8Bit dataport;
    Port8Bit commandport;
    unit8_t buffer[3];
    unit8_t offset;
    unit8_t buttons;
    MouseEventHandler* handler;
public:
    MouseDriver(InterruptManager *mannager,MouseEventHandler* handler);
    ~MouseDriver();
    virtual unit32_t InterruptHandler(unit32_t esp);
    virtual void Activate();
};


#endif