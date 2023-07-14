#include "gdt.h"
//GDT代表GlobalDescriptorTable
GDT::GDT()
:nullSegmentSelector(0,0,0),
unusedSegmentSelector(0,0,0),
codeSegmentSelector(0,64*1024*1024, 0x9A),
dataSegmentSelector(0,64*1024*1024, 0x92)
{
    unit32_t i[2];
    i[0] = (unit32_t)this;
    i[1] = sizeof(GDT) <<16;

    asm volatile("lgdt (%0)": :"p"(((unit8_t *)i)+2));
}

GDT::~GDT(){}

unit16_t GDT::DataSegmentSelector()
{
    return (unit8_t*)&dataSegmentSelector - (unit8_t*)this;
}

unit16_t GDT::CodeSegmentSelector()
{
    return (unit8_t*)&codeSegmentSelector - (unit8_t*)this;
}

GDT::SegmentDescriptor::SegmentDescriptor(unit32_t base,unit32_t limit,unit8_t type)
{
    unit8_t* target = (unit8_t*)this;

    if(limit <= 65535) target[6] = 0x40;
    else{
        if((limit&0xfff) != 0xfff) limit = (limit >> 12)-1;
        else limit = (limit >> 12);
        target[6] = 0xc0;
    }
    target[0] = limit & 0xff;
    target[1] = (limit >> 8) & 0xff;

    target[6] |= (limit>>16) &0xFF;

    target[2] = base & 0xff;
    target[3] = (base>>8) & 0xff;
    target[4] = (base>>16) & 0xff;
    target[7] = (base>>24) & 0xff;

    target[5] = type;

}

unit32_t GDT::SegmentDescriptor::Base()
{
    unit8_t* target = (unit8_t*)this;
    unit32_t result = target[7];

    result = (result<< 8) + target[4];
    result = (result<< 8) + target[3];
    result = (result<< 8) + target[2];
    return result;
}

unit32_t GDT::SegmentDescriptor::Limit()
{
    unit8_t* target = (unit8_t*)this;
    unit32_t result = target[6]& 0xf;

    result = (result << 8) + target[1];
    result = (result << 8) + target[0];

    if((target[6] & 0xc0) == 0xc0){
        result = ( result << 12 ) | 0xfff;
    }
    return result;
}