#pragma once
#include <iostream>
#include <string>
#include <vector>
class Packet {
public:
	unsigned int s_time;
	unsigned int deadline;
	unsigned int delay;
	int size;
	int priority;
	std::string packetMessage;
	Packet(unsigned int s_time, unsigned int deadline, unsigned int delay, int size, int priority, std::string packetMessage);
};
class Device {
public:
	std::string deviceName;
	std::string deviceType;
	int deviceNumber;
	Packet generatedPacket;
	bool isBusy;
	Device(std::string deviceName, std::string deviceType, int deviceNumber, Packet generatedPacket, bool isBusy);
	void deviceInfo() const;

};