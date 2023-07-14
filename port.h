#ifndef __PORT_H
#define __PORT_H

#include "types.h"

class Port
{
    protected:

    
}

class Port8Bit :public Port
{
    public:
        Port8Bit(unit16_t portnumber);
        ~Port8Bit();

        virtual void Write(unit8_t data);
        virtual unit8_t Read();
}

class Port8Bit_slow :public Port
{
    public:
        Port8Bit_slow(unit16_t portnumber);
        ~Port8Bit_slow();
        virtual void Write(unit8_t data);
}

class Port16Bit :public Port
{};

#endif