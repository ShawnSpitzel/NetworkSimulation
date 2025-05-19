#pragma once
#include "Devices.h"

class Event {
public:
	int scheduledTime;
	std::string type;
	int sourceDeviceId;
	int destinationDeviceId;
	Packet packet;
	int originalSourceTime;
	bool operator>(const Event& other) const {
		return scheduledTime > other.scheduledTime;
	}
	Event(int scheduledTime, std::string type, int sourceDeviceId, int destinationDeviceId, Packet packet, int originalSourceTime);
};