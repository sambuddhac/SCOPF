// Main function for implementing ADMM Based Proximal Message Passing Algorithm for the simplest two bus SCOPF case in serial mode
#include <iostream>

using namespace std;

#include "network.h" // Network class definition

int main() // function main begins program execution
{
	int netID; // Network ID number to indicate the type of the system with specifying the number of buses
	cout << "\nEnter the number of nodes to initialize the network.\n";
	cin >> netID;

	cout << endl << "\n*** NETWORK INITIALIZATION STAGE BEGINS ***\n" << endl << endl;

	Network network( netID ); // create the network instance

	cout << "\n*** NETWORK INITIALIZATION STAGE ENDS ***\n" << endl;

	cout << endl << "\n*** ADMM BASED PROXIMAL MESSAGE PASSING SCOPF SIMULATION (SERIAL IMPLEMENTATION) BEGINS ***\n" << endl << endl;
	cout << endl << "\n*** SIMULATION IN PROGRESS; PLEASE DON'T CLOSE ANY WINDOW OR OPEN ANY OUTPUT FILE YET ... ***\n" << endl << endl;	
	network.runSimulation(); // start simulation

	cout << "\n*** SCOPF SIMULATION ENDS ***\n" << endl;

	return 0; // indicates successful program termination

} // end main
