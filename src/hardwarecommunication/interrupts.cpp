#include <hardwarecommunication/interrupts.h>

using namespace myos::common;
using namespace myos::hardwarecommunication;

void printf(char* str);
void printfHex(unit8_t);

InterruptHandler::InterruptHandler(unit8_t interruptNumber,InterruptManager* interruptManager){
    this->interruptNumber = interruptNumber;
    this->interruptManager = interruptManager;
    interruptManager->handlers[interruptNumber] = this;
}

InterruptHandler::~InterruptManager(){
    if(interruptManager->handlers[interruptNumber] == this){
        interruptManager->handlers[interruptNumber] = 0;
    }
}

unit32_t InterruptHandler::handleInterrupt(unit32_t esp){
    printf("INTERRUPT");
    return esp;
}

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];
InterruptManager InterruptManager::ActiveInterruptManager = 0;

void InterruptManager::SetInterruptDesciptorTableEntry(
    unit8_t interruptNumber,
    unit16_t codeSegmentSelectorOffset,
    void (*handler)(),
    unit8_t DescriptorPrivilegeLevel,
    unit8_t DescriptorType)
{
    const unit8_t IDT_DESC_PRESENT = 0X80;
    interruptDescriptorTable[interruptNumber].handlerAddressLowBits = ((unit32_t)handler) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].handlerAddressHighBits = (((unit32_t)handler) >> 16) & 0XFFFF; 
    interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
    interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrivilegeLevel&3)<<5);   
}

InterruptManager::InterruptManager(GlobalDescriptorTable* gdt)
: picMasterCommand(0x20),
  picMasterData(0x21),
  picSlaveCommand(0xA0),
  picSlaveData(0XA1)
{
    unit16_t CodeSegment = gdt->CodeSegmentSelector();
    const unit8_t IDT_INTERRUPT_GATE = 0xE;

    for(unit16_t i=0 ; i<256 ; i++)
    {
        handlers[i] = 0;
        SetInterruptDesciptorTableEntry(i,CodeSegment,&IgnoreInterruptRequest,0,IDT_INTERRUPT_GATE);
    }

    SetInterruptDesciptorTableEntry(0x20,CodeSegment,&HandleInterruptRequest0x00,0,IDT_INTERRUPT_GATE);
    SetInterruptDesciptorTableEntry(0x20,CodeSegment,&HandleInterruptRequest0x01,0,IDT_INTERRUPT_GATE);

    picMasterCommand.Write(0x11);
    picSlaveCommand.Write(0x11);

    picMasterData.Write(0x20);
    picSlaveData.Write(0x28);

    picMasterData.Write(0x04);
    picSlaveData.Write(0x02);

    picMasterData.Write(0x00);
    picSlaveData.Write(0x00);

    InterruptDescriptorTable idt;
    idt.size = 256 * sizeof(GateDescriptor) - 1;
    idt.base = (unit32_t)interruptDescriptorTable;
    asm volatile("lidt %0" : :"m"(idt));
}

InterruptManager::~InterruptManager()
{
}

void InterruptManager::Activate(){
    //如果中断管理器已经被设置，停用旧的
    if(ActiveInterruptManager!=0){
        ActiveInterruptManager->Deactivate();
        ActiveInterruptManager = this;
        asm("sti");
    }
}

void InterruptManager::Deactivate(){
    //如果中断管理器已经被设置，停用旧的
    if(ActiveInterruptManager == this){
        ActiveInterruptManager = 0;
        asm("cli");
    }
}

unit32_t InterruptManager::handleInterrupt(unit8_t interruptNumber,unit32_t esp)
{
    if(ActiveInterruptManager!=0)
        return ActiveInterruptManager->DoHandleInterrupt(interruptNumber,esp);
    return esp;
}

unit32_t InterruptManager::DoHandleInterrupt(unit8_t interruptNumber,unit32_t esp)
{
    if(handlers[interruptNumber] != 0){
        esp = handlers[interruptNumber]->HandleInterrupt(esp);
    }else if(interruptNumber != 0x20){
        char* foo = " UNHANDLED INTERRUPT 0X00";
        char* hex = "0123456789ABCDEF";
        foo[22] = hex[(interruptNumber >> 4)& 0x0F];
        foo[23] = hex[interruptNumber & 0x0F];
        printf(foo);
    }
    
    if(0x20 <= interruptNumber && interruptNumber < 0x30){
        picMasterCommand.Write(0x20);
        if(0x28 <= interruptNumber)
            picSlaveCommand.Write(0x20);
    }
    return esp;
}