/*
CPU中有MUX和DEMUX
outb里面有两个参数：零件号和想传输的数据
*/
#ifndef __PORT_H
#define __PORT_H

#include "types.h"

class Port
{
    protected:
        unit16_t portnumber;//零件号
        Port(unit16_t portnumber);
        ~Port();
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
{
    public:
        Port16Bit(unit16_t portnumber);
        ~Port16Bit();
        virtual void Write(unit16_t data);
        virtual unit16_t Read();
};

class Port32Bit :public Port
{
    public:
        Port32Bit(unit32_t portnumber);
        ~Port32Bit();
        virtual void Write(unit32_t data);
        virtual unit32_t Read();
};
#endif