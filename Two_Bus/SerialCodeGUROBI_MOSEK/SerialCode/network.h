// Network class definition.
#ifndef NETWORK_H
#define NETWORK_H

// include the definitions of classes, generator, load, loadcont, transmission line, tlinecont, and node
#include "generator.h"
#include "load.h"
#include "loadcont.h"
#include "transl.h"
#include "tlinecont.h"
#include "node.h"
#include <vector>

using namespace std;

class Network {

public:
	Network( int ); // constructor
	~Network(); // destructor
	void setNetworkVariables( int ); // sets variables of the network
	void runSimulation(); // runs the SCOPF simulation

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
	int solverChoice; // Choose a solver from amongst CVXGEN, GUROBI, or MOSEK
	bool Verbose; // Parameter to decide whether to display intermediate results or not
	void runSimGUROBI();
	int runSimGUROBI2();
	void runSimMOSEK();

	// Create vectors of Generators, Loads, Loads under contingency, Transmission lines, Transmission lines under contingency, and Nodes
	vector< Generator > genObject;
	vector< Load > loadObject;
	vector< loadContingency > loadContObject;
	vector< transmissionLine > translObject;
	vector< tlineContingency > tlineContObject;
	vector< Node > nodeObject;

}; // end class Network

#endif // NETWORK_H
