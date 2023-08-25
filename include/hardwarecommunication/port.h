/*
CPU中有MUX和DEMUX
outb里面有两个参数：零件号和想传输的数据
*/
#ifndef __MYOS__HARDWARECOMMUNICATION__PORT_H
#define __MYOS__HARDWARECOMMUNICATION__PORT_H

#include <common/types.h>

namespace myos
{
    namespace hardwarecommunication
    {
        class Port
        {
            protected:
                myos::common::unit16_t portnumber;//零件号
                Port(myos::common::unit16_t portnumber);
                ~Port();
        }

        class Port8Bit :public Port
        {
            public:
                Port8Bit(myos::common::unit16_t portnumber);
                ~Port8Bit();
                virtual void Write(myos::common::unit8_t data);
                virtual myos::common::unit8_t Read();
            
            protected:
                static inline myos::common::unit8_t Read8(myos::common::unit16_t _port)
                {
                    myos::common::unit8_t result;
                    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }
                static inline void Write8(myos::common::unit16_t _port,myos::common::unit8_t _data)
                {
                    __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
                }
        }

        class Port8Bit_slow :public Port
        {
            public:
                Port8Bit_slow(myos::common::unit16_t portnumber);
                ~Port8Bit_slow();
                virtual void Write(myos::common::unit8_t data);
            protected:
                static inline void Write8Slow(myos::common::unit16_t _port,myos::common::unit8_t _data)
                {
                    __asm__ volatile("outb %0, %1\njmp lf\nl:jmp lf\nl:": :"a" (_data), "Nd" (_port));
                }
        }

        class Port16Bit :public Port
        {
            public:
                Port16Bit(myos::common::unit16_t portnumber);
                ~Port16Bit();
                virtual void Write(myos::common::unit16_t data);
                virtual myos::common::unit16_t Read();
            protected:
                static inline myos::common::unit16_t Read16(myos::common::unit16_t _port)
                {
                    myos::common::unit16_t result;
                    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }
                static inline void Write16(myos::common::unit16_t _port,myos::common::unit16_t _data)
                {
                    __asm__ volatile("outw %0, %1" : : "a" (_data) , "Nd" (_port));
                }
        };

        class Port32Bit :public Port
        {
            public:
                Port32Bit(myos::common::unit16_t portnumber);
                ~Port32Bit();

                virtual void Write(myos::common::unit32_t data);
                virtual myos::common::unit32_t Read();
            protected:
                static inline myos::common::unit32_t Read32(myos::common::unit16_t _port)
                {
                    myos::common::unit32_t result;
                    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }
                static inline void Write32(myos::common::unit16_t _port,myos::common::unit32_t _data)
                {
                    __asm__ volatile("outl %0, %1" : : "a" (_data) , "Nd" (_port));
                }
        };
    }
}

#endif