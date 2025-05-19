#pragma once
#include "Event.h"
Event::Event(int scheduledTime, std::string type, int sourceDeviceId, int destinationDeviceId, Packet packet, int originalSourceTime) :
	scheduledTime(scheduledTime),
	type(type),
	sourceDeviceId(sourceDeviceId),
	destinationDeviceId(destinationDeviceId),
	packet(packet),
	originalSourceTime(originalSourceTime)
{}