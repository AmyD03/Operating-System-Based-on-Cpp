#include"port.h"

Port::Port(unit16_t portnumber)
{
    this->portnumber = portnumber; //存储端口号
}
Port::~Port()
{

}

Port8Bit::Port8Bit(unit16_t portnumber)
:Port(portnumber)
{
}

Port8Bit::~Port8Bit()
{   
}

void Port8Bit_slow::Write(unit8_t data)
{
    __asm__volatile("outb %0, %1"::"a"(data),"Nd"(portnumber));
}

unit8_t Port8Bit::Read()
{
    unit8_t result;
    __asm__volatile("inb %1, %0":"=a"(result):"Nd"(portnumber)); 
    return result;
}

Port8Bit_slow::Port8Bit_slow(unit16_t portnumber):Port(portnumber){}
Port8Bit_slow::~Port8Bit_slow(){}
void Port8Bit_slow::Write(unit8_t data)
{
    __asm__volatile("outb %0,%1\njmp 1f\nl:jmp 1f\n1:"::"a"(data),"Nd"(portnumber));
}

Port16Bit::Port16Bit(unit16_t portnumber)
:Port(portnumber)
{
}

Port16Bit::~Port16Bit()
{   
}

void Port16Bit_slow::Write(unit16_t data)
{
    __asm__volatile("outw %0, %1"::"a"(data),"Nd"(portnumber));
}

unit16_t Port16Bit::Read()
{
    unit16_t result;
    __asm__volatile("inw %1, %0":"=a"(result):"Nd"(portnumber)); 
    return result;
}

Port16Bit::Port32Bit(unit32_t portnumber)
:Port(portnumber)
{
}

Port32Bit::~Port32Bit()
{   
}

void Port32Bit_slow::Write(unit32_t data)
{
    __asm__volatile("outl %0, %1"::"a"(data),"Nd"(portnumber));
}

unit16_t Port32Bit::Read()
{
    unit32_t result;
    __asm__volatile("inl %1, %0":"=a"(result):"Nd"(portnumber)); 
    return result;
}