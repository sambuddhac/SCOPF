// Network class definition.
#ifndef NETWORK_H
#define NETWORK_H

// include the definitions of classes, generator, load, transmission line, node
#include "generator.h"
#include "load.h"
#include "transl.h"
#include "node.h"
#include <vector>

using namespace std;

class Network {

public:
	Network( int ); // constructor
	~Network(); // destructor
	void setNetworkVariables( int ); // sets variables of the network
	void runSimulation(); // runs the OPF simulation

private:
	// Define the Network
	int networkID; // ID number of the network instance
	int genNumber, genFields; // Number of Generators & Fields
	int loadNumber, loadFields; // Number of Loads & Fields
	int translNumber, translFields; // Number of Transmission Lines & Fields
	int deviceTermCount; // Number of device terminals
	int nodeNumber; // Number of Nodes	
	double Rho; // ADMM Tuning Parameter
	int contingencyCount; // Total number of contingency scenarios

	// Create vectors of Generators, Loads, Loads under contingency, Transmission lines, Transmission lines under contingency, and Nodes
	vector< Generator > genObject;
	vector< Load > loadObject;
	vector< loadContingency > loadContObject;
	vector< transmissionLine > translObject;
	vector< tlineContingency > tlineContObject;
	vector< Node > nodeObject;

}; // end class Network

#endif // NETWORK_H
