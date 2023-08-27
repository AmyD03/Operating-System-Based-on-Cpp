#ifndef __MYOS__HARDWARECOMMUNICATION__INTERRUPTS_H
#define __MYOS__HARDWARECOMMUNICATION__INTERRUPTS_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <gdt.h>

namespace myos
{
    namespace hardwarecommunication
    {
        class InterruptHandler
        {
            protected:
                myos::common::unit8_t interruptNumber;
                InterruptManager* interruptManager;
                InterruptHandler(InterruptManager* interruptManager ,myos::common::unit8_t interruptNumber);
                ~InterruptManager();
            public:
                virtual myos::common::unit32_t HandleInterrupt(myos::common::unit32_t esp);
        };

        class InterruptManager
        {
            friend class InterruptHandler;
            public:
                InterruptManager(myos::common::unit16_t hardwareInterruptOffset, myos::GlobalDescriptorTable* globalDescriptorTable); 
                ~InterruptManager();
                myos::common::unit16_t HandleInterruptOffset;
                void Activate();
                void Deactivate();
                
                static unit32_t handleInterrupt(unit8_t InterruptNumber, unit32_t esp);
                unit32_t DoHandleInterrupt(unit8_t InterruptNumber, unit32_t esp);
            
                
            protected:
                static InterruptManager* ActiveInterruptManager; //只有一个active的中断管理器
                InterruptHandler* handlers[256];
                struct GateDescriptor
                {
                    myos::common::unit16_t HandeAddressLowBits;
                    myos::common::unit16_t gdt_codeSegmentSelector;
                    myos::common::unit8_t reserved;
                    myos::common::unit8_t access;
                    myos::common::unit16_t HandeAddressHighBits;
                }__attribute__((packed));
            static GateDescriptor InterruptDescriptorTable[256];

            struct InterruptDescriptorTablePointer
            {
                myos::common::unit16_t size;
                myos::common::unit32_t base;
            }__attribute__((packed));

            myos::common::unit16_t HandleInterruptOffset;
            static void SetInterruptDescriptorTableEntry(myos::common::unit8_t InterruptNumber,
                myos::common::unit16_t codeSegmentSelectorOffset,void (*handler)(),
                myos::common::unit8_t DescriptorPrivilegeLevel,myos::common::unit8_t DescriptorType);
            static void IgnoreInterruptRequest()
            static void HandleInterruptRequest0X00();
            static void HandleInterruptRequest0x02();
            static void HandleInterruptRequest0x03();
            static void HandleInterruptRequest0x04();
            static void HandleInterruptRequest0x05();
            static void HandleInterruptRequest0x06();
            static void HandleInterruptRequest0x07();
            static void HandleInterruptRequest0x08();
            static void HandleInterruptRequest0x09();
            static void HandleInterruptRequest0x0A();
            static void HandleInterruptRequest0x0B();
            static void HandleInterruptRequest0x0C();
            static void HandleInterruptRequest0x0D();
            static void HandleInterruptRequest0x0E();
            static void HandleInterruptRequest0x0F();
            static void HandleInterruptRequest0x10();
            static void HandleInterruptRequest0x11();
            static void HandleInterruptRequest0x12();
            static void HandleInterruptRequest0x13();

            static myos::common::unit32_t HandleInterrupt(myos::common::unit8_t interrupt, myos::common::unit32_t esp);
            myos::common::unit32_t DoHandleInterrupt(myos::common::unit8_t interrupt, myos::common::unit32_t esp);

            Port8BitSlow programmableInterruptControllerMasterCommandPort;
            Port8BitSlow programmableInterruptControllerMasterDataPort;
            Port8BitSlow programmableInterruptControllerSlaveCommandPort;
            Port8BitSlow programmableInterruptControllerSlaveDataPort;
        };
    }
}

#endif