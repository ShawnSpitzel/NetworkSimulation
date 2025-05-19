#include "Devices.h"  
#include <iostream>  
Packet::Packet(unsigned int s_time, unsigned int deadline, unsigned int delay, int size, int priority, std::string packetMessage) :
	s_time(s_time),
	deadline(deadline),
	delay(delay),
	size(size),
	priority(priority),
	packetMessage(packetMessage)
{
	std::cout << "Packet created with s_time: " << s_time << ", deadline: " << deadline << ", delay: " << delay << ", message: " << packetMessage << std::endl;
}
Device::Device(std::string deviceName, std::string deviceType, int deviceNumber, Packet generatedPacket, bool isBusy) :
	deviceName(deviceName),
	deviceType(deviceType),
	deviceNumber(deviceNumber),
	generatedPacket(generatedPacket),
	isBusy(isBusy)
{
	std::cout << "Device created: " << deviceName << std::endl;
}
   void Device::deviceInfo() const {
	   std::cout << "Device Name: " << deviceName << std::endl;
	   std::cout << "Device Type: " << deviceType << std::endl;
	   std::cout << "Device Number: " << deviceNumber << std::endl;
	   std::cout << "Generated Packet: " << generatedPacket.packetMessage << std::endl;
   };