#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Devices.h"
#include "Network.h"
#include <stdlib.h> 
#define MAX_TIME 1000
class NetworkEngine {
public:
	int networkDelay;
	std::string networkType;
	std::string networkTopology;
	Network network;

	int setNetworkDelay();
	void deadlineCheck(int deadline, int latency, int elapsedTime, std::string packetMessage);
	void setNetworkType(std::string networkType);
	void startNetwork(std::vector<Device> devices);
	int findSwitchId(std::vector<Device> devices);
	Device findDeviceByNumber(std::vector<Device> devices, int number);
	int findListener(std::vector<Device> devices, int arrivingDeviceNumber, Network network);
	void priorityClockCycle(Device switchDevice);
	//If switch type is TAS, then check if the device is a switch. If so:
		// Time Slot High: 0ms-5ms, Time Slot Low: 5ms-10ms. 10ms in a cycle
		//Before transmitting packet to output port, check if the elapsed time fits between the available time slots for the packets priority.
		//If priority is high and fits within high time slot, proceed to output
		//If priority is high and fits within low time slot, wait until next cycle
		//If priority is low and fits within high time slot, wait for low time slot
		//If priority is low and fits within low time slot, proceed to output
	void networkConfiguration(std::vector<Device> devices);
	//Set the network topology (Either Star or Mesh)
	//Make necessary checks for network type (i.e Star needs a central network and atleast one device)
	//Call networkCreation() to create network graph
	void networkCreation(std::vector<Device> devices);
	//Given the number of devices & types of devices, create and set them as nodes (Graph vertex).
	//Link instances (Graph adjacency) with bandwitch and latency (Weighted edges)
	//Construct a graph and adjacency matrix where each device is a vertex and each edge is a link
	//Star graph means all devices share adjacency only with the central device

	//Initially populate event queue with first device information
	NetworkEngine(int networkDelay, std::string networkType, std::string networkTopology, Network network);
	//Device information is read from event queue
	//Every 10ms call priorityClockCycle()
	
	//Schedule packet transmission across adjacency for the given time (queue)
	//Calculate the transmission time based on packet_size and adjacency.bandwidth
	//Packet arrives at the destination in sent_time + adjacency.latency + transmission_time ms.
	//Destination then examines next available vertex to travel to

	//Schedule packet transmission time based on the current time (from destination to next vertex, queue)
	//Calculate the transmission time based on packet_size and adjacency.bandwidth
	//Packet arrives at the destination in sent_time + adjacency.latency + transmission_time ms.
	//Destination then examines next available vertex to travel to
	
	//If there is no next available vertex, and we are currently in a device of type listener, then packet has reached final destionation
	//Record arrival time and find delay (arrival_time - sent_time)
	//Check if delay is within the deadline
	//If delay is within the deadline, output message. If not, print error message
	
	//Device generates next packet, process continutes until simulation time (pre-determined) is reached
	//Once simulation is reached, output the average delay for all packets, and the packet loss (packets received/packets missed)
};