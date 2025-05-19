
#include "NetworkEngine.h"
#include "Network.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Event.h"
#define SIMULATION_LENGTH 1000 //Simulation time in ms
NetworkEngine::NetworkEngine(int networkDelay, std::string networkType, std::string networkTopology, Network network) :
	networkDelay(networkDelay),
	networkType(networkType),
	networkTopology(networkTopology),
	network(network)
{
	std::cout << "Network Engine created with delay: " << networkDelay << ", type: " << networkType <<", and topology: "<<networkTopology<< std::endl;
}
void NetworkEngine::setNetworkType(std::string networkType) {
	if (networkType == "TSN") {
		this->networkType = "TSN";
	}
	else if (networkType == "BE") {
		this->networkType = "BE";
	}
	else {
		std::cout << "Invalid network type!" << std::endl;
		return;
	}
	std::cout << "Network type set to: " << networkType << std::endl;
}
int NetworkEngine::findSwitchId(std::vector<Device> devices) {
	for (int i = 0; i < devices.size(); i++) {
		if (devices[i].deviceType == "Switch") {
			return devices[i].deviceNumber;
		}
	}
	std::cerr << "Error: No Switch found!" << std::endl;
	return -1;
}
Device NetworkEngine::findDeviceByNumber(std::vector<Device> devices, int number) {
	for (int i = 0; i < devices.size(); i++) {
		if (devices[i].deviceNumber == number) {
			return devices[i];
		}
	}
	std::cerr << "Error: No Device Found!" << std::endl;
}
int NetworkEngine::findListener(std::vector<Device> devices, int arrivingDeviceNumber, Network network) {
	for (int i = 0; i < devices.size(); i++) {
		if (devices[i].isBusy == false && devices[i].deviceType == "Listener") {
			return devices[i].deviceNumber;
		}
	}
	std::cerr << "Error: Couldn't find available listener!" << std::endl;
	return -1;
}
int NetworkEngine::setNetworkDelay() {
	if (networkType == "TSN") {
		networkDelay = 3;
	}
	else if (networkType == "BE") {
		networkDelay = rand() % 13;
	}
	else {
		std::cout << "Invalid network type!" << std::endl;
		return 0;
	}
	return networkDelay;
}
void NetworkEngine::deadlineCheck(int deadline, int latency, int elapsedTime, std::string packetMessage) {
	if (latency > deadline) {
		std::cout << "Packet deadline exceeded!" << std::endl;
	}
	else {
		std::cout << "Packet message: " << packetMessage << " receieved at time: " << elapsedTime << "ms" << std::endl;
	}
	return;
};
void NetworkEngine::priorityClockCycle(Device switchDevice) {
	//TODO:
		//If switch type is TAS, then check if the device is a switch. If so:
		// Time Slot High: 0ms-5ms, Time Slot Low: 5ms-10ms. 10ms in a cycle
		//Before transmitting packet to output port, check if the elapsed time fits between the available time slots for the packets priority.
		//If priority is high and fits within high time slot, proceed to output
		//If priority is high and fits within low time slot, wait until next cycle
		//If priority is low and fits within high time slot, wait for low time slot
		//If priority is low and fits within low time slot, proceed to output
}
void NetworkEngine::networkConfiguration(std::vector<Device> devices) {
	if (this->networkTopology == "Star") {
		int switchNum = 0;
		int listenerNum = 0;
		int talkerNum = 0;
		for (int i = 0; i < devices.size(); i++) {
			if (devices[i].deviceType == "Switch") {
				switchNum++;
			}
			else if (devices[i].deviceType == "Listener") {
				listenerNum++;
			}
			else if (devices[i].deviceType == "Talker") {
				talkerNum++;
			}
		}
		if (switchNum == 0 || listenerNum == 0 || talkerNum == 0) {
			std::cout << "Invalid network topology! Star topology requires at least one switch, one listener, and one talker." << std::endl;
			return;
		}
		else {
			std::cout << "Network topology set to: " << networkTopology << std::endl;
		}
	}
	else {
		std::cout << "Invalid network topology!" << std::endl;
		return;
	}
	networkCreation(devices);
}

void NetworkEngine::networkCreation(std::vector<Device> devices) {
	if (this->networkTopology == "Star") {
		network.addStarLinksFromArray(devices);
		network.printNetwork();
	}
	else {
		std::cout << "Invalid network topology!" << std::endl;
		return;
	}

	 
}
void NetworkEngine::startNetwork(std::vector<Device> devices) {
	int currentTime = 0;
	int switchId = findSwitchId(devices);
	Device switchDevice = findDeviceByNumber(devices, switchId);
	std::priority_queue<Event, std::vector<Event>, std::greater<Event>> eventQueue;

	//Initialization
	for (int i = 0; i < devices.size(); i++) {
		if (devices[i].deviceType == "Talker") {
			Event newEvent = Event(0, "TRANSMISSION_START", devices[i].deviceNumber, switchId, devices[i].generatedPacket, devices[i].generatedPacket.s_time);
			eventQueue.push(newEvent);
		}
	}
	std::cout << "Event Queue initialized" << std::endl;
	// Main simulation loop
	std::cout << "Simulation starting.." << std::endl;
	while ((currentTime < SIMULATION_LENGTH) && eventQueue.empty() == false) {
		//TODO: Use packet.priority to navigate priority queue
		Event currentEvent = eventQueue.top();
		currentTime = currentEvent.scheduledTime;
		if (currentEvent.type == "TRANSMISSION_START") {
			//TODO: Fix infinite loop bug, most likely stems from link finder
			std::cout << "Transmission started.." << std::endl;
			Device sourceDevice = findDeviceByNumber(devices, currentEvent.sourceDeviceId);
			sourceDevice.isBusy = true;
			int destinationDeviceId = currentEvent.destinationDeviceId;
			Device destinationDevice = findDeviceByNumber(devices, destinationDeviceId);
			network.addLink(sourceDevice, destinationDevice);
			std::cout << "Transmitting to device: " << destinationDevice.deviceType << std::endl;
			Packet packetToTransmit = currentEvent.packet;
			Link* link = network.findLinkBetween(sourceDevice.deviceNumber, destinationDeviceId);
			if (link) {
				std::cout << "Link found.. " << std::endl;
				int transmissionTime = packetToTransmit.size / link->bandwidth;
				int arrivalTime = currentTime + link->latency + transmissionTime;
				Event arrivalEvent = Event(arrivalTime, "PACKET_ARRIVAL", sourceDevice.deviceNumber, destinationDeviceId, packetToTransmit, packetToTransmit.s_time);
				eventQueue.push(arrivalEvent);
			}
			else {
				std::cout << "No link found.. " << std::endl;
			}
			sourceDevice.isBusy = false;
		}
		else if (currentEvent.type == "PACKET_ARRIVAL") {
			Device arrivingDevice = findDeviceByNumber(devices, currentEvent.destinationDeviceId);
			Packet arrivedPacket = currentEvent.packet;
			int originalSentTime = currentEvent.originalSourceTime;
			if (arrivingDevice.deviceType == "Switch") {
				std::cout << "Packet arrived at switch" << std::endl;
				int destinationId = findListener(devices, arrivingDevice.deviceNumber, network);
				Device listenerDevice = findDeviceByNumber(devices, destinationId);
				network.addLink(arrivingDevice, listenerDevice);
				listenerDevice.isBusy = true;
				if (destinationId) {
					Event nextTransmissionEvent = Event(currentTime, "TRANSMISSION_START", arrivingDevice.deviceNumber, destinationId, arrivedPacket, arrivedPacket.s_time);
					eventQueue.push(nextTransmissionEvent);
				}
				listenerDevice.isBusy = false;
			}
			else if (arrivingDevice.deviceType == "Listener") {
				int latency = currentTime - originalSentTime;
				deadlineCheck(arrivedPacket.deadline, latency, currentTime, arrivedPacket.packetMessage);
			}
		}
		if ((currentTime & 10) == 0) {
			priorityClockCycle(switchDevice);
		}
	}
	network.printNetwork();
	std::cout << eventQueue.size() << std::endl;
	std::cout << "Simulation over in: " << currentTime << " ms." << std::endl;
};