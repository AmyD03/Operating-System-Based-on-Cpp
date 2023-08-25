#ifndef __MYOS__GDT_H
#define __MYOS__GDT_H
#include <common/types.h>

namespace myos
{
    class GlobalDescriptorTable
    {
        public:
            class SegmentDescriptor
            {
                private:
                    myos::common::unit16_t limit_lo;
                    myos::common::unit16_t base_lo;
                    myos::common::unit8_t base_hi;
                    myos::common::unit8_t type;
                    myos::common::unit8_t flags_limit_hi;
                    myos::common::unit8_t base_vhi;
                public:
                    SegmentDescriptor(myos::common::unit32_t base, myos::common::unit32_t limit, myos::common::unit8_t type);
                    myos::common::unit32_t Base();
                    myos::common::unit32_t Limit();
            } __attribute__((packed));
            
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;
        public:
            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            myos::common::unit16_t codeSegmentSelector();
            myos::common::unit16_t DataSegmentSelector();
    };
}

#endif