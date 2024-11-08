// Main function for implementing ADMM Based Proximal Message Passing Algorithm for the SCOPF case in serial mode
#include <iostream>

using namespace std;

#include "network.h" // Network class definition

int main() // function main begins program execution
{
	int netID; // Network ID number to indicate the type of the system with specifying the number of buses
	cout << "\nEnter the number of nodes to initialize the network. (Allowed choices are 3, 5, 14, 30, 48, 57, 118, and 300 Bus IEEE Test Bus Systems as of now. So, please restrict yourself to one of these)\n";
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
