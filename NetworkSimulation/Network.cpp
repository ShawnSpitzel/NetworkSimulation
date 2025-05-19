#pragma once
#include <iostream>
#include <vector>
#include "Network.h"
Link::Link(Device neighbor, int bandwidth, int latency) :
	neighbor(neighbor),
	bandwidth(bandwidth),
	latency(latency)
{
	std::cout << "Link created with bandwidth: " << bandwidth << " and latency: " << latency << std::endl;
};
Network::Network(int numDevices, std::vector<Device> devices) :
	numDevices(numDevices),
	adjacencyList(numDevices),
    devices(devices)
{
	std::cout << "Network created with " << numDevices << " devices." << std::endl;
};
int* Network::bandwidth_latency_generator(int bandwidth_latency_array[2]) {
    static int bandwidth;
    static int latency;

    bandwidth = rand() % 10 + 1;
    latency = rand() % 10 + 1;

    bandwidth_latency_array[0] = bandwidth;
    bandwidth_latency_array[1] = latency;

    return bandwidth_latency_array;
}
Link* Network::findLinkBetween(int source, int destination) {
    for (int i = 0; i < adjacencyList[source].size(); i++) {
        if (adjacencyList[source][i].neighbor.deviceNumber == destination) {
            return &adjacencyList[source][i];
        }
        else {
            std::cerr << "No link found" << std::endl;
        }
    }
}
std::vector<std::vector<Link>>& Network::returnAdjacencyList() {
    return adjacencyList;
}
void Network::addStarLinksFromArray(std::vector<Device> devices) {

	int* bandwidth_latency_array = new int[2];
	for (int i = 0; i < devices.size()-1; i++){
		bandwidth_latency_array = bandwidth_latency_generator(bandwidth_latency_array);
		adjacencyList[i].push_back(Link(devices[i+1], bandwidth_latency_array[0], bandwidth_latency_array[1]));
	}
};
void Network::addLink(Device device1, Device device2) {
    int* bandwidth_latency_array = new int[2];
    bandwidth_latency_array = bandwidth_latency_generator(bandwidth_latency_array);
	adjacencyList[device1.deviceNumber].push_back(Link(device2, bandwidth_latency_array[0], bandwidth_latency_array[1]));
};
void Network::printNetwork() const {
    for (int i = 0; i < numDevices; ++i) {
        std::cout << "Node: Device " << i << " (Type: " << devices[i].deviceType << ")" << std::endl;
        bool hasNeighbors = false;
        for (int j = 0; j < adjacencyList[i].size(); j++) {
            hasNeighbors = true;
            std::cout << "  --> Link (Bandwidth: " << adjacencyList[i][j].bandwidth << ", Latency: " << adjacencyList[i][j].latency << ") --> ";
            std::cout << "Neighbor: Device " << adjacencyList[i][j].neighbor.deviceNumber << " (Type: " << devices[adjacencyList[i][j].neighbor.deviceNumber].deviceType << ")" << std::endl;
        }
        if (!hasNeighbors) {
            std::cout << "  No outgoing links." << std::endl;
        }
        std::cout << std::endl;
    }
}