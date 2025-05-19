#include "Devices.h"
#include "NetworkEngine.h"
#include <iostream>
//NOTES: 
	//Priority 1: Lowest, Priority 2: Medium, Priority 3: Highest
int main() {
	Device device1("Device1", "Talker", 0, Packet(0, 10, 5, 3, 10, "Hello from Talker!"), false);
	Device device2("Device2", "Switch", 1, Packet(NULL, NULL, NULL, NULL, NULL, ""),false);
	Device device3("Device3", "Listener", 2, Packet(NULL, NULL, NULL, NULL, NULL, ""), false);
	std::vector<Device> devices = { device1, device2, device3 };
	Network network(3, devices);
	NetworkEngine networkEngine(0, "TSN", "Star", network);
	networkEngine.networkConfiguration(devices);
	std::cout << std::endl;

	return 0;
}