#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"
#include "port.h"
#include "gct.h"

class InterruptHandler
{
    protected:
        unit8_t interruptNumber;
        InterruptManager* interruptManager;
        InterruptHandler(unit8_t interruptNumber,InterruptManager* interruptManager);
        ~InterruptManager();
    public:
        virtual unit32_t HandleInterrupt(unit32_t esp);
};

class InterruptManager
{
    friend class InterruptHandler;
    public:
        InterruptManager(GDT* gdt); 
        ~InterruptManager();

        void Activate();
        void Deactivate();

        static unit32_t HandleInterrupt(unit8_t InterruptNumber, unit32_t esp);
        unit32_t DoHandleInterrupt(unit8_t InterruptNumber, unit32_t esp);
    
        static void IgnoreInterruptRequest();
        static void HandleInterruptRequest0x00();
        static void HandleInterruptRequest0x01();
        
    protected:
        static InterruptManager* ActiveInterruptManager; //只有一个active的中断管理器
        InterruptHandler* handlers[256];
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