// Main function for implementing APMP (Auxiliary Proximal Message Passing) Algorithm for the SCOPF in serial mode
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstring>
using namespace std;
#include "gurobi_c++.h" // includes definition of the GUROBI solver header file
#include "network.h" // Network class definition

int main() // function main begins program execution
{
	int netID; // Network ID number to indicate the type of the system with specifying the number of buses
	vector< Network* > contNetVector; // Vector of base-case and contingency scenario network objects
	cout << "\nEnter the number of nodes to initialize the network. (Allowed choices are 2, 3, 5, 14, 30, 48, 57, 118, and 300 Bus IEEE Test Bus Systems as of now. So, please restrict yourself to one of these)\n";
	cin >> netID;
	int solverChoice; // 1 for GUROBI, 2 for CVXGEN, 3 for GUROBI Centralized
	cout << "\nEnter the choice of the solver, 1 for GUROBI-APMP(ADMM/PMP+APP), 2 for CVXGEN-APMP(ADMM/PMP+APP), 3 for GUROBI centralized, and 4 for GUROBI APP Coarse Grained" << endl;
	cin >> solverChoice; 
	int setRhoTuning; // parameter to select adaptive rho, fixed rho, and type of adaptive rho
	if ((solverChoice==1) || (solverChoice==2)) { // APMP Fully distributed, Bi-layer (N-1) SCOPF Simulation 
		cout << "Enter the tuning mode; Enter 1 for maintaining Rho * primTol = dualTol; 2 for primTol = dualTol; anything else for Adaptive Rho (with mode-1 being implemented for the first 3000 iterations and then Rho is held constant).\n" << endl;
		cin >> setRhoTuning;
	}
	GRBEnv* environmentGUROBI = new GRBEnv("GUROBILogFile.log"); // GUROBI Environment object for storing the different optimization models
	cout << endl << "\n*** NETWORK INITIALIZATION STAGE BEGINS ***\n" << endl << endl;
	Network* network = new Network( netID, 0, 0, 0, solverChoice ); // create network object corresponding to the base case
	int numberOfCont = network->retContCount(); // gets the number of contingency scenarios in the variable numberOfCont
	contNetVector.push_back( network ); // push to the vector of network instances 
	for ( int i = 1; i <= numberOfCont; ++i ) {
		int lineOutaged = contNetVector[0]->indexOfLineOut(i); // gets the serial number of transmission line outaged in this scenario 
		Network* network = new Network( netID, i, lineOutaged, 1, solverChoice ); // create the network instances for the contingency scenarios, which includes as many networks as the number of contingency scenarios
		contNetVector.push_back( network ); // push to the vector of network instances
	}

	cout << "\n*** NETWORK INITIALIZATION STAGE ENDS ***\n" << endl;

	int numberOfGenerators = contNetVector[0]->getGenNumber(); // get the number of generators in the system
	int iterCountAPP = 1; // Iteration counter for APP coarse grain decomposition algorithm
	double alphaAPP = 100.0; // APP Parameter/Path-length
	int consLagDim = numberOfCont*numberOfGenerators; // Dimension of the vectors of APP Lagrange Multipliers and Power Generation Consensus	
	double lambdaAPP[consLagDim]; // Array of APP Lagrange Multipliers for achieving consensus among the values of power generated, as guessed by scenarios
	double powDiff[consLagDim]; // Array of lack of consensus between generation values, as guessed by scenarios
	for ( int i = 0; i < consLagDim; ++i ) {
		lambdaAPP[i] = 0.0; // Initialize lambdaAPP for the first iteration of APP and ADMM-PMP
		powDiff[i] = 0.0; // Initialize powDiff for the first iteration of APP and ADMM-PMP
	}
	double finTol = 1000.0; // Initial Guess of the Final tolerance of the APP iteration/Stopping criterion
	if ((solverChoice==1) || (solverChoice==2)) { // APMP Fully distributed, Bi-layer (N-1) SCOPF Simulation 
		string outputAPPFileName;
		if (solverChoice==1)
			outputAPPFileName = "/home/samie/code/ADMM_Based_Proximal_Message_Passing_Distributed_OPF/SCOPF/Multi_Bus/APMPSCOPF/output/ADMM_PMP_GUROBI/resultAPP-SCOPF.txt";
		if (solverChoice==2)
			outputAPPFileName = "/home/samie/code/ADMM_Based_Proximal_Message_Passing_Distributed_OPF/SCOPF/Multi_Bus/APMPSCOPF/output/ADMM_PMP_CVXGEN/resultAPP-SCOPF.txt";
		ofstream matrixResultAPPOut( outputAPPFileName, ios::out ); // create a new file result.txt to output the results

		// exit program if unable to create file
		if ( !matrixResultAPPOut ) {
			cerr << "File could not be opened" << endl;
			exit( 1 );
		}
		matrixResultAPPOut << endl << "\nInitial Value of the Tolerance to kick-start the APP outer iterations= " << finTol << "\n" << endl << endl;
		matrixResultAPPOut << "APP Itearion Count" << "\t" << "APP Tolerance" << "\n";	
		clock_t start_s = clock(); // begin keeping track of the time
		cout << endl << "\n*** APMP ALGORITHM BASED COARSE+FINE GRAINED BILAYER DECENTRALIZED/DISTRIBUTED SCOPF (SERIAL IMPLEMENTATION) BEGINS ***\n" << endl << endl;
		cout << endl << "\n*** SIMULATION IN PROGRESS; PLEASE DON'T CLOSE ANY WINDOW OR OPEN ANY OUTPUT FILE YET ... ***\n" << endl << endl;

		//*********************************************AUXILIARY PROBLEM PRINCIPLE (APP) COARSE GRAINED DECOMPOSITION COMPONENT******************************************************//	
		//do { // APP Coarse grain iterations start
		for ( iterCountAPP = 1; iterCountAPP <= 10; ++iterCountAPP ) {
			for ( int netSimCount = 0; netSimCount < (numberOfCont+1); ++netSimCount )
				contNetVector[netSimCount]->runSimulation(setRhoTuning, iterCountAPP, lambdaAPP, powDiff, environmentGUROBI); // start simulation
			for ( int i = 0; i < numberOfCont; ++i ) {
				for ( int j = 0; j < numberOfGenerators; ++j ) {
					powDiff[i*numberOfGenerators+j]=*(contNetVector[0]->getPowSelf()+j)-*(contNetVector[i+1]->getPowSelf()+j); // what base thinks about itself Vs. what contingency thinks about base
				}
			}
			for ( int i = 0; i < numberOfCont; ++i ) {
				for ( int j = 0; j < numberOfGenerators; ++j ) {
					lambdaAPP[i*numberOfGenerators+j] = lambdaAPP[i*numberOfGenerators+j] + alphaAPP * (powDiff[i*numberOfGenerators+j]); // what I think about myself Vs. what next door fellow thinks about me
				}
			}
			double tolAPP = 0.0;
			for ( int i = 0; i < consLagDim; ++i ) {
				tolAPP = tolAPP + pow(powDiff[i], 2);
			}
			finTol = sqrt(tolAPP);
			matrixResultAPPOut << iterCountAPP << "\t" << finTol << "\n";
			//++iterCountAPP; // increment the APP iteration counter
		//} while (finTol>=0.005); //Check the termination criterion of the APP iterations
		}
		//****************************************END OF AUXILIARY PROBLEM PRINCIPLE (APP) COARSE GRAINED DECOMPOSITION COMPONENT******************************************************//

		cout << "\n*** SCOPF SIMULATION ENDS ***\n" << endl;
		clock_t stop_s = clock();  // end
		matrixResultAPPOut << "\nExecution time (s): " << static_cast<double>( stop_s - start_s ) / CLOCKS_PER_SEC << endl;
		cout << "\nExecution time (s): " << static_cast<double>( stop_s - start_s ) / CLOCKS_PER_SEC << endl;
		cout << "\nFinal Value of APP Tolerance " << finTol << endl; 
	}
	if (solverChoice==3) { // Centralized (N-1) SCOPF Simulation
		cout << endl << "\n*** CENTRALIZED (N-1) SCOPF SIMULATION BEGINS ***\n" << endl << endl;
		cout << endl << "\n*** SIMULATION IN PROGRESS; PLEASE WAIT. PLEASE DON'T CLOSE ANY WINDOW OR OPEN ANY OUTPUT FILE ... ***\n" << endl << endl;
		contNetVector[0]->runSimulationCentral(environmentGUROBI); // start simulation
		cout << "\n*** (N-1) SCOPF SIMULATION ENDS ***\n" << endl;	
	}
//&*
	if (solverChoice==4) { // Centralized (N-1) SCOPF Simulation
		string outputAPPFileName = "/home/samie/code/ADMM_Based_Proximal_Message_Passing_Distributed_OPF/SCOPF/Multi_Bus/APMPSCOPF/output/APP_Quasi_Decent_GUROBI/resultAPP-SCOPF.txt";
		ofstream matrixResultAPPOut( outputAPPFileName, ios::out ); // create a new file result.txt to output the results

		// exit program if unable to create file
		if ( !matrixResultAPPOut ) {
			cerr << "File could not be opened" << endl;
			exit( 1 );
		}
		matrixResultAPPOut << endl << "\nInitial Value of the Tolerance to kick-start the APP outer iterations= " << finTol << "\n" << endl << endl;
		matrixResultAPPOut << "APP Itearion Count" << "\t" << "APP Tolerance" << "\n";	
		clock_t start_s = clock(); // begin keeping track of the time
		cout << endl << "\n*** COARSE GRAINED APP QUASI-DECENTRALIZED (N-1) SCOPF SIMULATION BEGINS ***\n" << endl << endl;
		cout << endl << "\n*** SIMULATION IN PROGRESS; PLEASE WAIT. PLEASE DON'T CLOSE ANY WINDOW OR OPEN ANY OUTPUT FILE ... ***\n" << endl << endl;
		//*********************************************AUXILIARY PROBLEM PRINCIPLE (APP) COARSE GRAINED DECOMPOSITION COMPONENT******************************************************/	
		//do { // APP Coarse grain iterations start
		for ( iterCountAPP = 1; iterCountAPP <= 100; ++iterCountAPP ) {
			for ( int i = 0; i < numberOfCont; ++i ) {
				for ( int j = 0; j < numberOfGenerators; ++j ) {
					if (iterCountAPP == 1)
						powDiff[i*numberOfGenerators+j]=0;
				}
			}
			for ( int i = 0; i < numberOfCont; ++i ) {
				for ( int j = 0; j < numberOfGenerators; ++j ) {
					if (iterCountAPP == 1)
						lambdaAPP[i*numberOfGenerators+j] = 0;

				}
			}
			contNetVector[0]->runSimAPPGurobiBase(iterCountAPP, lambdaAPP, powDiff, environmentGUROBI); // start simulation
			for ( int netSimCount = 1; netSimCount < (numberOfCont+1); ++netSimCount )
				contNetVector[netSimCount]->runSimAPPGurobiCont(iterCountAPP, lambdaAPP, powDiff, environmentGUROBI); // start simulation
			for ( int i = 0; i < numberOfCont; ++i ) {
				for ( int j = 0; j < numberOfGenerators; ++j ) {
					powDiff[i*numberOfGenerators+j]=*(contNetVector[0]->getPowSelfGUROBI()+j)-*(contNetVector[i+1]->getPowSelfGUROBI()+j); // what base thinks about itself Vs. what contingency thinks about base
				}
			}
			for ( int i = 0; i < numberOfCont; ++i ) {
				for ( int j = 0; j < numberOfGenerators; ++j ) {
					lambdaAPP[i*numberOfGenerators+j] = lambdaAPP[i*numberOfGenerators+j] + alphaAPP * (powDiff[i*numberOfGenerators+j]); // what I think about myself Vs. what next door fellow thinks about me

				}
			}
			double tolAPP = 0.0;
			for ( int i = 0; i < consLagDim; ++i ) {
				tolAPP = tolAPP + pow(powDiff[i], 2);
			}
			finTol = sqrt(tolAPP);
			matrixResultAPPOut << iterCountAPP << "\t" << finTol << "\n";
			//++iterCountAPP; // increment the APP iteration counter
		//} while (finTol>=0.05); //Check the termination criterion of the APP iterations
		}
		//****************************************END OF AUXILIARY PROBLEM PRINCIPLE (APP) COARSE GRAINED DECOMPOSITION COMPONENT******************************************************/

		cout << "\n*** SCOPF SIMULATION ENDS ***\n" << endl;
		clock_t stop_s = clock();  // end
		matrixResultAPPOut << "\nExecution time (s): " << static_cast<double>( stop_s - start_s ) / CLOCKS_PER_SEC << endl;
		cout << "\nExecution time (s): " << static_cast<double>( stop_s - start_s ) / CLOCKS_PER_SEC << endl;
		cout << "\nFinal Value of APP Tolerance " << finTol << endl; 
		cout << "\n*** (N-1) SCOPF SIMULATION ENDS ***\n" << endl;	
	}
	else
		cout << "\nInvalid choice of solution method and algorithm." << endl;
	delete environmentGUROBI; // Free the memory of the GUROBI environment object
	for ( int i = 0; i < (numberOfCont+1); ++i ) {
		delete contNetVector[i]; // destroy the vector of contingency case network instances
	}

	return 0; // indicates successful program termination

} // end main
