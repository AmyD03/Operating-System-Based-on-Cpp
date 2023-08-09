#include "interrupts.h"

InterruptManager InterruptManager::ActiveInterruptManager=0;


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
    printf(" INTERRUPT");
    return esp;
}