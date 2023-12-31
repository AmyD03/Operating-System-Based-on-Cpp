#ifndef __MYOS__DRIVERS__DRIVER_H
#define __MYOS__DRIVERS__DRIVER_H

namespace myos
{
    namespace drivers
    {
        class Driver
        {
            public:
                Driver();
                ~Driver();
            virtual void Activate();
            virtual int Reset(); //启动操作系统时会枚举硬件，但各硬件的状态未知，需要重置
            virtual void Deactivate();
        };

        class DriverManager
        {
            private:
                Driver* drivers[256];
                int numDrivers;
            public:
                DriverManager();
                void AddDriver(Driver*);
                VOID ActivateAll();
        }
    }
}
#endif