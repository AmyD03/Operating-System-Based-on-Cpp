#ifndef __MOUSE_H
#define __MOUSE_H

#include "types.h"
#include "interrupts.h"
#include "port.h"

class MouseDriver:public InterruptHandler
{
    Port8Bit dataport;
    Port8Bit commandport;
    unit8_t buffer[3];
    unit8_t offset;
    unit8_t buttons;
public:
    MouseDriver(InterruptManager *mannager);
    ~MouseDriver();
    virtual unit32_t InterruptHandler(unit32_t esp);
};


#endif