#include"port.h"

Port::Port(unit16_t portnumber)
{
    this->portnumber = portnumber;
}
Port::~Port(){}

Port8Bit::Port8Bit(unit16_t portnumber):Port(portnumber){}
Port8Bit::~Port8Bit(){}

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