#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"
#include "port.h"
#include "gct.h"

class InterruptManager
{
    public:
        InterruptManager(GDT* gdt);
        ~InterruptManager();
        static unit32_t HandleInterrupt(unit8_t InterruptNumber, unit32_t esp);
    protected:
        struct GateDescriptor
        {
            unit16_t HandeAddressLowBits;
            unit16_t gdt_codeSegmentSelector;
            unit8_t reserved;
            unit8_t access;
            unit16_t HandeAddressHighBits;
        }__attribute__((packed));
    static GateDescriptor InterruptDescriptorTable[256];

    struct InterruptDescriptorTablePointer
    {
        unit16_t size;
        unit32_t base;
    }__attribute__((packed));

    static void SetInterruptDescriptorTableEntry
    {
        unit8_t InterruptNumber,
        unit16_t codeSegmentSelectorOffset,
        void (*handler)(),
        unit8_t DescriptorPrivilegeLevel,
        unit8_t DescriptorType
    };
    static void IgnoreInterruptRequest()
    static void HandleInterruptRequest0X00();
    static void HandleInterruptRequest0x01();
    
    Port8BitSlow picMasterCommand;
    Port8BitSlow picMasterData;
    Port8BitSlow picSlaveCommand;
    Port8BitSlow picSlaveDra;
};

#endif