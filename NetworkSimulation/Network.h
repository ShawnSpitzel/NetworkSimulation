#pragma once
#include "Devices.h"
class Link {
public:
	Device neighbor;
	int bandwidth;
	int latency;
	Link(Device neighbor, int bandwidth, int latency);
};
class Network {
private:
	int numDevices;
	std::vector<Device> devices;
	std::vector<std::vector<Link>> adjacencyList; //adjacency list
public:
	Network(int numDevices, std::vector<Device> devices);
	int* bandwidth_latency_generator(int bandwidth_latency_array[2]);
	void addStarLinksFromArray(std::vector<Device> devices);
	Link* findLinkBetween(int source, int destination);
	std::vector<std::vector<Link>>& returnAdjacencyList();
	void addLink(Device device1, Device device2);
	void printNetwork() const;
};