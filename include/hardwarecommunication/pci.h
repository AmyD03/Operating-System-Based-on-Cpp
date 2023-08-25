#ifndef __MYOS__HARDWARECOMMUNICATION__PCI_H
#define __MYOS__HARDWARECOMMUNICATION__PCI_H

#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>

class PeripheralComponentInterconnectDeviceDescriptor
{
    public:
        common::unit32_t portBase;
        common::unit32_t interrupt;

        common::unit16_t bus;
        common::unit16_t device;
        common::unit16_t function;

        common::unit16_t vendor_id;
        common::unit16_t device_id;

        common::unit8_t class_id;
        common::unit8_t subclass_id;
        common::unit8_t interface_id;

        common::unit8_t revision;

        PeripheralComponentInterconnectDeviceDescriptor();
        ~PeripheralComponentInterconnectDeviceDescriptor();

};

class PeripheralComponentInterconnectController
{
        Port32Bit dataPort;
        Port32Bit commandPort;
    public:
        PeripheralComponentInterconnectController();
        ~PeripheralComponentInterconnectController();

        common::unit32_t Read(common::unit16_t bus,common::unit16_t device,common::unit16_t function,common::unit32_t registeroffset);
        void Write(common::unit16_t bus,common::unit16_t device);
        bool DeviceHasFunctions(common::unit16_t bus,common::unit16_t device);
        
        void SelectDrivers(myos::DriverManager* driverManager);
};

#endif
