// Member functions for class Network
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
// include definitions for classes generator, load, transmission line, network and node
#include "generator.h"
#include "transl.h"
#include "tlinecont.h"
#include "load.h"
#include "loadcont.h"
#include "node.h"
#include "network.h"

using namespace std;

Network::Network( int val )
	: networkID( val ), // constructor begins; initialize networkID, Rho, and contingencyCount through constructor initializer list
	  Rho( 1.0 ),
	  contingencyCount( 0 )
{
	setNetworkVariables( networkID ); // sets the variables of the network

} // end constructor

// destructor
Network::~Network()
{	
	cout << "\nNetwork instance: " << networkID << " destroyed.\n" << endl;

} // end destructor

void Network::setNetworkVariables( int networkID ) // Function setNetworkVariables startsto initialize the parametersand variables
{
	do {

		nodeNumber = networkID; // set the number of nodes of the network

		// Nodes
		for ( int l = 0; l < nodeNumber; ++l ) {
			cout << "\nCreating the " << l + 1 << " -th Node:\n";
		
			Node nodeInstance( l + 1 ); // creates nodeInstance object with ID l + 1

			nodeObject.push_back( nodeInstance ); // pushes the nodeInstance object into the vector

		} // end initialization for Nodes

		// Transmission Lines
		ifstream matrixFirstFile( "Tran2.txt", ios::in ); // ifstream constructor opens the file of Transmission lines

		// exit program if ifstream could not open file
		if ( !matrixFirstFile ) {
			cerr << "\nFile for Transmission lines could not be opened\n" << endl;
			exit( 1 );
		} // end if
	
		matrixFirstFile >> translNumber >> translFields; // get the dimensions of the Transmission line matrix
		double matrixTran[ translNumber ][ translFields ]; // Transmission line matrix
		for ( int i = 0; i < translNumber; ++i ) {
			for ( int j = 0; j < translFields; ++j ) {
				matrixFirstFile >> matrixTran[ i ][ j ]; // read the Transmission line matrix
			}
		}

		// Count the total number of contingency scenarios
		for ( int k = 0; k < translNumber; ++k ) {
			contingencyCount += matrixTran[ k ][ 5 ]; // count the number of contingency scenarios
		}

		// Create Transmission Lines
		for ( int k = 0; k < translNumber; ++k ) {
			int l = 0;
			int tNodeID1, tNodeID2; // node object IDs to which the particular transmission line object is connected
			do {
				//node IDs of the node objects to which this transmission line is connected.
				tNodeID1 = matrixTran[ k ][ l ]; //From end
				tNodeID2 = matrixTran[ k ][ ( l + 1 ) ]; //To end
			} while ( ( tNodeID1 <= 0 ) || ( tNodeID1 > nodeNumber ) || ( tNodeID2 <= 0 ) || 
				( tNodeID2 > nodeNumber ) || ( tNodeID1 == tNodeID2) ); // validity check
			double resT, reacT, ptMax, ptMin; // Parameters for Transmission Line
			double contingencyIndex; // Parameter indicating consideration for contingency
			do {
				//Resistance:
				resT = matrixTran[ k ][ ( l + 2 ) ];
				//Reactance:
				reacT = matrixTran[ k ][ ( l + 3 ) ];
				//values of maximum allowable power flow on line in the forward and reverse direction:
				//Forward direction:
				ptMax = matrixTran[ k ][ ( l + 4 ) ];
				ptMin = -ptMax; //Reverse direction
				contingencyIndex = matrixTran[ k ][ ( l + 5 ) ]; // indicates whether the line needs to be considered for contingency analysis or not
			} while ( (resT <= 0 ) || ( reacT <= 0 ) || ( ptMax <= ptMin ) || ( contingencyIndex != 1.0 ) || ( contingencyIndex != 0.0 ) ); // check the bounds and validity of the parameter values

			//Transolver tlineParam( ptMin, ptMax, reacT ); // Instantiate the copy constructor for the Transmission Line solver object
			
			// creates transLineInstance object with ID k + 1
			transmissionLine transLineInstance( k + 1, &nodeObject[ tNodeID1 - 1 ], &nodeObject[ tNodeID2 - 1 ], ptMax, reacT, resT ); 
			for ( int counter = 0; counter < contingencyCount; ++counter ) {
				tlineContingency tlineContInstance( k + 1, &nodeObject[ tNodeID1 - 1 ], &nodeObject[ tNodeID2 - 1 ], ptMax, reacT, resT, contingencyIndex, ( counter + 1 ) );
				tlineContObject.push_back( tlineContInstance ); // creates the vector of transmission lines corr. to contingency
			}

			translObject.push_back( transLineInstance ); // pushes the transLineInstance object into the vector

		} // end initialization for Transmission Lines

		// Generators
		ifstream matrixSecondFile( "Gen2.txt", ios::in ); // ifstream constructor opens the file of Generators

		// exit program if ifstream could not open file
		if ( !matrixSecondFile ) {
			cerr << "\nFile for Generators could not be opened\n" << endl;
			exit( 1 );
		} // end if
	
		matrixSecondFile >> genNumber >> genFields; // get the dimensions of the Generator matrix
		double matrixGen[ genNumber ][ genFields ]; // Generator matrix
		for ( int i = 0; i < genNumber; ++i ) {
			for ( int j = 0; j < genFields; ++j ) {
				matrixSecondFile >> matrixGen[ i ][ j ]; // read the Generator matrix
			}
		}
		
		// Create Generators
		for ( int i = 0; i < genNumber; ++i ) {
			int j = 0; 
			int gNodeID; // node object ID to which the particular generator object is connected
			do {
				gNodeID = matrixGen[ i ][ j ];
			} while ( ( gNodeID <= 0 ) || ( gNodeID > nodeNumber ) ); // validity check

			double c2, c1, c0, PgMax, PgMin; // Parameters for Generator
			do {
				//Quadratic Coefficient: 
				c2 = matrixGen[ i ][ ( j + 1 ) ];
				//Linear coefficient: 
				c1 = matrixGen[ i ][ ( j + 2 ) ];
				//Constant term: 
				c0 = matrixGen[ i ][ ( j + 3 ) ];
				//Maximum Limit: 
				PgMax = matrixGen[ i ][ ( j + 4 ) ];
				//Minimum Limit: 
				PgMin = matrixGen[ i ][ ( j + 5 ) ];
			} while ( (c2 < 0 ) || ( c1 < 0 ) || ( PgMax <= 0 ) || ( PgMin < 0 ) || ( PgMax <= PgMin ) ); 
			// check the bounds and validity of the parameter values

			Gensolver genParam( c2, c1, c0, PgMax, PgMin, contingencyCount ); // Instantiate the copy constructor for the generator solver object
	
			Generator generatorInstance( i + 1, &nodeObject[ gNodeID - 1 ], genParam, contingencyCount ); // creates generatorInstance object with ID number i + 1

			genObject.push_back( generatorInstance ); // pushes the generatorInstance object into the vector

		} // end initialization for Generators
	
		// Loads
		ifstream matrixThirdFile( "Load2.txt", ios::in ); // ifstream constructor opens the file of Loads

		// exit program if ifstream could not open file
		if ( !matrixThirdFile ) {
			cerr << "\nFile for Loads could not be opened\n" << endl;
			exit( 1 );
		} // end if
	
		matrixThirdFile >> loadNumber >> loadFields; // get the dimensions of the Load matrix
		double matrixLoad[ loadNumber ][ loadFields ]; // Load matrix
		for ( int i = 0; i < loadNumber; ++i ) {
			for ( int j = 0; j < loadFields; ++j ) {
				matrixThirdFile >> matrixLoad[ i ][ j ]; // read the Load matrix
			}
		}
		// Create Loads
		for ( int j = 0; j < loadNumber; ++j ) {
			//cout << "\nEnter the parameters of the " << j + 1 << " -th Load:\n";
			int k = 0;
			int lNodeID; // node object ID to which the particular load object is connected
			do {
				//node ID of the node object to which this load object is connected.
				lNodeID = matrixLoad[ j ][ k ]; 
			} while ( ( lNodeID <= 0 ) || ( lNodeID > nodeNumber ) ); // validity check

			double P_Load; // Parameters for Load
			do {
				//value of allowable power consumption capability of load with a negative sign to indicate consumption:
				//Power Consumption:
				P_Load = matrixLoad[ j ][ ( k + 1 ) ];
			} while ( -P_Load <= 0 ); // check the bounds and validity of the parameter values

			//Loadsolver loadParam( P_Load );	// Instantiate the copy constructor for the load solver object
			Load loadInstance( j + 1, &nodeObject[ lNodeID - 1 ], P_Load ); // creates loadInstance object object with ID number j + 1
			for ( int counter = 0; counter < contingencyCount; ++counter ) {
				loadContingency loadContInstance( j + 1, &nodeObject[ lNodeID - 1 ], P_Load, ( counter + 1 ) );
				loadContObject.push_back( loadContInstance ); // creates the vector of transmission lines corr. to contingency
			}

			loadObject.push_back( loadInstance ); // pushes the loadInstance object into the vector

		} // end initialization for Loads

	} while ( (genNumber <= 0 ) || ( nodeNumber <= 0 ) || ( loadNumber <= 0 ) || ( translNumber <= 0 ) || (genFields <= 0 ) || ( loadFields <= 0 ) || ( translFields <= 0 ) );
	// check the bounds and validity of the parameter values
	
	deviceTermCount = genNumber + loadNumber + 2 * translNumber; // total number of device-terminals

} // end setNetworkVariables function

// runSimulation function definition
void Network::runSimulation() //Function runSimulation begins
{
	// Declaration of intermerdiate variables and parameters for running the simulation
	int iteration_count; // iteration counter

	double dualTol = 1.0; // initialize the dual tolerance
	double primalTol; // primal tolerance
	double ptolsq = 0.0; // initialize the primal tolerance square
	
	vector< int > iterationGraph; // vector of iteration counts
	vector< double > primTolGraph; // vector of primal tolerance
	vector< double > dualTolGraph; // vector of dual tolerance
	vector< double > objectiveValue; // vector of objective function values

	int bufferIndex; // index of the buffer to store past values of voltage iterate, power and angle iterate

	double V_avg[ nodeNumber ]; // array of average node angle imbalance price from last to last iterate
	double vBuffer1[ nodeNumber ]; // intermediate buffer for average node angle price from last to last iterate
	double vBuffer2[ nodeNumber ]; // intermediate buffer for average node angle price from last iterate

	double angleBuffer[ nodeNumber ]; // buffer for average node voltage angles from present iterate
	double angleBuffer1[ nodeNumber ]; // buffer for average node voltage angles from last iterate
	double angtildeBuffer[ deviceTermCount ]; // Thetatilde from present iterate

	double powerBuffer[ deviceTermCount ]; // Ptilde from present iterate
	double powerBuffer1[ deviceTermCount ]; // Ptilde from last iterate
	double pavBuffer[ nodeNumber ]; // Pav from present iterate
	double ptildeinitBuffer[ deviceTermCount ]; // Ptilde before iterations begin

	double uPrice[ deviceTermCount ]; // u parameter from previous iteration
	double vPrice[ deviceTermCount ]; // v parameter from previous iteration

	double Rho1 = 1.0; // Previous value of Rho from previous iteration
	double W, Wprev; // Present and previous values of W for the PID controller for modifying Rho
	double lambdaAdap = 0.0001; // Parameters of the PID controller for adjusting the ADMM tuning parameter
	double muAdap = 0.0005; // Parameters of the PID controller for adjusting the ADMM tuning parameter

	// Calculation of initial value of Primal Tolerance before the start of the iterations
	vector< Load >::iterator loadIterator;	
	for ( loadIterator = loadObject.begin(); loadIterator != loadObject.end(); loadIterator++ ) {
		ptolsq = ptolsq + pow( loadIterator->pinitMessage(), 2.0 ); // calls the node to divide by the number of devices connected
	}
	primalTol = sqrt( ptolsq ); // initial value of primal tolerance to kick-start the iterations

	// Calculation of initial value of Ptilde before the iterations start
	vector< Generator >::iterator generatorIterator;	
	for ( generatorIterator = genObject.begin(); generatorIterator != genObject.end(); generatorIterator++ ) {
		bufferIndex = generatorIterator->getGenID() - 1;
		ptildeinitBuffer[ bufferIndex ] = -generatorIterator->calcPavInit();
	}

	for ( loadIterator = loadObject.begin(); loadIterator != loadObject.end(); loadIterator++ ) {
		bufferIndex = genNumber + ( loadIterator->getLoadID() - 1 );
		ptildeinitBuffer[ bufferIndex ] = loadIterator->calcPavInit();
	}

	int temptrans1 = 0; // counter to make sure that two values of Ptilde are accounted for each line
	vector< transmissionLine >::iterator translIterator;	
	for ( translIterator = translObject.begin(); translIterator != translObject.end(); translIterator++ ) {
		bufferIndex = genNumber + loadNumber + ( translIterator->getTranslID() - 1 ) + temptrans1;
		ptildeinitBuffer[ bufferIndex ] = -translIterator->calcPavInit1(); // Ptilde corresponding to 'from' end
		ptildeinitBuffer[ ( bufferIndex + 1 ) ] = -translIterator->calcPavInit2(); // Ptilde corresponding to 'to' end
		temptrans1++;
	}

	ofstream matrixResultOut( "result.txt", ios::out ); // create a new file result.txt to output the results
	
	// exit program if unable to create file
	if ( !matrixResultOut ) {
		cerr << "File could not be opened" << endl;
		exit( 1 );
	}
	
	matrixResultOut << "\nThe initial value of primal tolerance to kick-start iterations is: " << primalTol << "\nThe initial value of dual tolerance to kick-start iterations is: " << dualTol << endl;
	
	clock_t start_s = clock(); // begin keeping track of the time

	// Starting of the ADMM Based Proximal Message Passing Algorithm Iterations
	for ( iteration_count = 1; ( iteration_count < 200 ); iteration_count++ ) {
		// ( primalTol >= 0.001 ) && ( dualTol >= 0.001 ) // ( iteration_count <= 122 )
	
		matrixResultOut << "\nThe value of primal tolerance before this iteration is: " << primalTol << "\nThe value of dual tolerance before this iteration is: " << dualTol << endl;
		matrixResultOut << "\n**********Start of " << iteration_count << " -th iteration***********\n";
				
		// Recording data for plotting graphs
		
		iterationGraph.push_back( iteration_count ); // stores the iteration count to be graphed
		primTolGraph.push_back( primalTol ); // stores the primal tolerance value to be graphed
		dualTolGraph.push_back( dualTol ); // stores the dual tolerance value to be graphed
		//Initialize the average node angle imbalance price (v) vector from last to last interation, V_avg
		//**if ( iteration_count <= 2 ) {
			for ( int i = 0; i < nodeNumber; i++ )
				V_avg[ i ] = 0.0; // initialize to zero for the first and second iterations
		//**}
		//**else {
			//**for ( int j = 0; j < nodeNumber; j++ )
				//**V_avg[ j ] = vBuffer1[ j ]; // initialize to the average node v from last to last iteration for 3rd iteration on
		
		//**}
		// Initialize average v, average theta, ptilde, average P before the start of a particular iteration
		if ( iteration_count >= 2 ) {
			for ( int i = 0; i < nodeNumber; i++ ) {
				//**vBuffer1[ i ] = vBuffer2[ i ]; // Save to vBuffer1, the average v from last iteration for use in next iteration
				angleBuffer1[ i ] = angleBuffer[ i ]; // Save to angleBuffer1, the average node voltage angle from last iteration
			}

			for ( int j = 0; j < deviceTermCount; j++ )
				powerBuffer1[ j ] = powerBuffer[ j ]; // Save to powerBuffer1, the Ptilde for each device term. from last itern

		}
		
		else {
			Wprev = 0.0; // for the first iteration
			for ( int i = 0; i < nodeNumber; i++ ) {
			
				angleBuffer1[ i ] = 0.0; // Set average node voltage angle to zero for 1st iteration
			}

			vector< Node >::iterator nodeIterator;
			for ( nodeIterator = nodeObject.begin(); nodeIterator != nodeObject.end(); nodeIterator++ ) {
				bufferIndex = nodeIterator->getNodeID() - 1;
				pavBuffer[ bufferIndex ] = nodeIterator->devpinitMessage(); // Average node power injection before 1st iteration
			}
			for ( int j = 0; j < deviceTermCount; j++ )
				powerBuffer1[ j ] = ptildeinitBuffer[ j ]; // Save to powerBuffer1, the Ptilde before the 1st iteration
		}

		//vector< Generator >::const_iterator generatorIterator; // Distributed Optimizations; Generators' Opt. Problems
		double calcObjective = 0.0;	// initialize the total generator cost for this iteration
		for ( generatorIterator = genObject.begin(); generatorIterator != genObject.end(); generatorIterator++ ) {
			double Pgit, PowerPrice, APrice; // Generator Power, Power Price, & Angle Price iterates from last iterations
			bufferIndex = generatorIterator->getGenID() - 1;
			int gnid = generatorIterator->getGenNodeID() - 1; // gets the ID number of connection node
			if ( iteration_count > 1 ) { // If 2nd or higher iterations, initialize to previous iterate values
				Pgit = generatorIterator->genPower();
				PowerPrice = uPrice[ bufferIndex ];
				APrice = vPrice[ bufferIndex ];
			}
			else { // If 1st iteration, initialize to zero
				Pgit = 0.0;
				PowerPrice = 0.0;
				APrice = 0.0; 
			}
			matrixResultOut << "\nStarting of Generator Optimization Iterations for Generator " << bufferIndex + 1 << "\n";
			matrixResultOut << "Previous power iterate (MW)\n" << Pgit << "\nPrevious average power (MW) for this node\n" << pavBuffer[ gnid ] << "\nPrevious power price ($/MWh, LMP)\n" << PowerPrice << "\nAngle price from last to last iterate\n" << V_avg[ gnid ] << "\nAngle value from last iterate\n" << angleBuffer1[ gnid ] << "\nPrevious angle price\n" << APrice << endl;
			generatorIterator->gpowerangleMessage( Rho, Pgit, pavBuffer[ gnid ], PowerPrice, V_avg[ gnid ], angleBuffer1[ gnid ], APrice ); // Solve the Optimization Problem
			calcObjective = calcObjective + generatorIterator->objectiveGen(); // calculate the total objective after this iteration
		}
		//vector< Load >::const_iterator loadIterator;	// Distributed Optimizations; Loads' Optimization Problems
		for ( loadIterator = loadObject.begin(); loadIterator != loadObject.end(); loadIterator++ ) {
			double APrice, PPrice; // Load Power Price and Angle Price from last iterations
			bufferIndex = genNumber + ( loadIterator->getLoadID() - 1 );
			int lnid = loadIterator->getLoadNodeID() - 1; // gets ID number of connection node
			if ( iteration_count > 1 ) { // If 2nd or higher iterations, initialize to previous iterate values
				APrice = vPrice[ bufferIndex ];
				PPrice = uPrice[ bufferIndex ];
			}
			else 
				APrice = 0.0; // If 1st iteration, initialize to zero
			matrixResultOut << "\nStarting of Load Optimization Iterations for Load " << loadIterator->getLoadNodeID() << "\n";
			matrixResultOut << "\nAngle price from last to last iterate\n" << V_avg[ lnid ] << "\nAngle value from last iterate\n" << angleBuffer1[ lnid ] << "\nPrevious angle price\n" << APrice << endl;
			loadIterator->lpowerangleMessage( Rho, V_avg[ lnid ], angleBuffer1[ lnid ], APrice ); // Solve the Optimization Problem
		}
		//vector< transmissionLine >::const_iterator translIterator;// Distributed Optimizations; TLine' Optimization Problems
		int temptrans2 = 0;	
		for ( translIterator = translObject.begin(); translIterator != translObject.end(); translIterator++ ) {
			double Ptit1, Ptit2, PowerPrice1, PowerPrice2, APrice1, APrice2; // Tline Power, Power price, Angle price at both ends
			bufferIndex = genNumber + loadNumber + ( translIterator->getTranslID() - 1 ) + temptrans2;
			int tnid1 = translIterator->getTranslNodeID1() - 1; // gets ID number of first conection node
			int tnid2 = translIterator->getTranslNodeID2() - 1; // gets ID number of second connection node
			if (iteration_count > 1 ) { // If 2nd or higher iterations, initialize to previous iterate values
				Ptit1 = translIterator->translPower1();
				Ptit2 = translIterator->translPower2();
				PowerPrice1 = uPrice[ bufferIndex ];
				PowerPrice2 = uPrice[ ( bufferIndex + 1 ) ];
				APrice1 = vPrice[ bufferIndex ];
				APrice2 = vPrice[ ( bufferIndex + 1 ) ];
			}
			else { // If 1st iteration, initialize to zero
				Ptit1 = 0.0;
				Ptit2 = 0.0;
				PowerPrice1 = 0.0;
				PowerPrice2 = 0.0;
				APrice1 = 0.0;
				APrice2 = 0.0;
			}
			matrixResultOut << "\nStarting of Transmission Line Optimization Iterations for Transmission line " << translIterator->getTranslID() << "\n";
			matrixResultOut << "Previous power iterate (MW) for end-1\n" << Ptit1 << "\nPrevious average power (MW) for end-1\n" << pavBuffer[ tnid1 ] << "\nPrevious power price ($/MWh, LMP) for end-1\n" << PowerPrice1 << "\nAngle price from last to last iterate for end-1\n" << V_avg[ tnid1 ] << "\nAngle value from last iterate for end-1\n" << angleBuffer1[ tnid1 ] << "\nPrevious angle price for end-1\n" << APrice1 << "\nPrevious power iterate (MW) for end-2\n" << Ptit2 << "\nPrevious average power (MW) for end-2\n" << pavBuffer[ tnid2 ] << "\nPrevious power price ($/MWh) for end-2\n" << PowerPrice2 << "\nAngle price from last to last iterate for end-2\n" << V_avg[ tnid2 ] << "\nAngle value from last iterate for end-2\n" << angleBuffer1[ tnid2 ] << "\nPrevious angle price for end-2\n" << APrice2 <<endl;				
			translIterator->tpowerangleMessage( Rho, Ptit1, pavBuffer[ tnid1 ], PowerPrice1, V_avg[ tnid1 ], angleBuffer1[ tnid1 ], APrice1, Ptit2, pavBuffer[ tnid2 ], PowerPrice2, V_avg[ tnid2 ], angleBuffer1[ tnid2 ], APrice2 ); // Solve the Opt. Problem
			temptrans2++; 
		}
		
		W = ( Rho ) * ( primalTol / dualTol ) - 1; // Definition of W for adaptive Rho
	 	//**W = 0.0; // Definition of W for fixed Rho
		// Calculation of Adaptive Rho
		Rho1 = Rho; // Store previous Rho
		Rho = ( Rho1 ) * ( exp( ( lambdaAdap * W ) + ( muAdap * ( W - Wprev ) ) ) ); // Next iterate value of Rho
		Wprev = W; // Buffering
		
		matrixResultOut << "\n*********Starting of Gather Operation************\n";
		vector< Node >::iterator nodeIterator; // Distributed Optimizations; Nodes' Optimization Problem; Gather Operation
		for ( nodeIterator = nodeObject.begin(); nodeIterator != nodeObject.end(); nodeIterator++ ) {
			bufferIndex = nodeIterator->getNodeID() - 1;
			//**vBuffer2[ bufferIndex ] = ( Rho1 / Rho ) * ( nodeIterator->vavMessage() ); // Gather & Calculate average v after present iteration/node
			angleBuffer[ bufferIndex ] = nodeIterator->ThetaavMessage(); // Calculate average angle after present iteration/node
			pavBuffer[ bufferIndex ] = nodeIterator->PavMessage(); // Calculate average power after present iteration/node
			matrixResultOut << "\nNode Number: " << bufferIndex + 1 /*<< "\nV_avg = " << vBuffer2[ bufferIndex ] */<< "\nTheta_avg = " << angleBuffer[ bufferIndex ] << "\nP_avg = " << pavBuffer[ bufferIndex ] << endl;
		}

		matrixResultOut << "\n*******Starting of Broadcast Operation*******\n";
		// vector< Generator >::const_iterator generatorIterator;	// Broadcast to Generators
		for ( generatorIterator = genObject.begin(); generatorIterator != genObject.end(); generatorIterator++ ) {
			bufferIndex = generatorIterator->getGenID() - 1;
			matrixResultOut << "\n***Generator: " << bufferIndex + 1 << " results***\n" << endl;
			powerBuffer[ bufferIndex ] = generatorIterator->calcPtilde();
			uPrice[ bufferIndex ] = ( Rho1 / Rho ) * ( generatorIterator->getu() );
			angtildeBuffer[ bufferIndex ] = generatorIterator->calcThetatilde();
			//generatorIterator->calcvtilde();
			vPrice[ bufferIndex ] = ( Rho1 / Rho ) * ( generatorIterator->getv() );
			matrixResultOut << "\nPower price after this iteration ($/MWh, LMP) is: " << uPrice[ bufferIndex ] << "\nAngle price after this iteration is: " << vPrice[ bufferIndex ] << "\nPtilde after this iteration is: " << powerBuffer[ bufferIndex ] << "\nThetatilde at the end of this iteration is: " << angtildeBuffer[ bufferIndex ] << endl;
		}

		// vector< Load >::const_iterator loadIterator;	// Broadcast to Loads
		for ( loadIterator = loadObject.begin(); loadIterator != loadObject.end(); loadIterator++ ) {
			bufferIndex = genNumber + ( loadIterator->getLoadID() - 1 );
			matrixResultOut << "\n***Load: " << loadIterator->getLoadID() << " results***\n" << endl;
			powerBuffer[ bufferIndex ] = loadIterator->calcPtilde();
			uPrice[ bufferIndex ] = ( Rho1 / Rho ) * ( loadIterator->getu() );
			angtildeBuffer[ bufferIndex ] = loadIterator->calcThetatilde();
			//loadIterator->calcvtilde();
			vPrice[ bufferIndex ] = ( Rho1 / Rho ) * ( loadIterator->getv() );
			matrixResultOut << "\nPower price after this iteration ($/MWh, LMP) is: " << uPrice[ bufferIndex ] << "\nAngle price after this iteration is: " << vPrice[ bufferIndex ] << "\nPtilde after this iteration is: " << powerBuffer[ bufferIndex ] << "\nThetatilde at the end of this iteration is: " << angtildeBuffer[ bufferIndex ] << endl;
		}

		int temptrans = 0; // temporary count of transmission lines to account for both the ends // Broadcast to Transmission Lines
		// vector< transmissionLine >::const_iterator translIterator;	
		for ( translIterator = translObject.begin(); translIterator != translObject.end(); translIterator++ ) {
			bufferIndex = genNumber + loadNumber + ( translIterator->getTranslID() - 1 ) + temptrans;
			matrixResultOut << "\n***Transmission Line: " << translIterator->getTranslID() << " results***\n" << endl;
			powerBuffer[ bufferIndex ] = translIterator->calcPtilde1();
			uPrice[ bufferIndex ] = ( Rho1 / Rho ) * ( translIterator->getu1() );
			angtildeBuffer[ bufferIndex ] = translIterator->calcThetatilde1();
			//translIterator->calcvtilde1();
			vPrice[ bufferIndex ] = ( Rho1 / Rho ) * ( translIterator->getv1() );
			powerBuffer[ ( bufferIndex + 1 ) ] = translIterator->calcPtilde2();
			uPrice[ ( bufferIndex + 1 ) ] = ( Rho1 / Rho ) * ( translIterator->getu2() );
			angtildeBuffer[ ( bufferIndex + 1 ) ] = translIterator->calcThetatilde2();
			//translIterator->calcvtilde2();
			vPrice[ ( bufferIndex + 1 ) ] = ( Rho1 / Rho ) * ( translIterator->getv2() );
			temptrans++;
			matrixResultOut << "\nPower price ($/MWh, LMP at end-1) after this iteration is: " << uPrice[ bufferIndex ] << "\nAngle price (end-1) after this iteration is: " << vPrice[ bufferIndex ] << "\nPtilde (end-1) after this iteration is: " << powerBuffer[ bufferIndex ] << "\nThetatilde (end-1) at the end of this iteration is: " << angtildeBuffer[ bufferIndex ] << "\nPower price ($/MWh, LMP at end-2) after this iteration is: " << uPrice[ ( bufferIndex + 1 ) ] << "\nAngle price (end-2) after this iteration is: " << vPrice[ ( bufferIndex + 1 ) ] << "\nPtilde (end-2) after this iteration is: " << powerBuffer[ ( bufferIndex + 1 ) ] << "\nThetatilde (end-2)  at the end of this iteration is: " << angtildeBuffer[ ( bufferIndex + 1 ) ] <<endl;
		}

		for ( nodeIterator = nodeObject.begin(); nodeIterator != nodeObject.end(); nodeIterator++ ) {
			nodeIterator->reset(); 
		}

		// Calculation of Primal Tolerance, primalTol at the end of this particular iteration
		double primsum = 0.0;
		for ( int i = 0; i < nodeNumber; i++ )
			primsum = primsum + pow( pavBuffer[ i ], 2.0 );
		for ( int j = 0; j < deviceTermCount; j++ )
			primsum = primsum + pow( angtildeBuffer[ j ], 2.0 );
		primalTol = sqrt( primsum );
		matrixResultOut << "\nPrimal Tolerance at the end of this iteration is: " << primalTol << endl;
		
		// Calculation of Dual Tolerance, dualTol at the end of this particular iteration
		double sum = 0.0;
		if ( iteration_count > 1 ) {
			for ( int k = 0; k < deviceTermCount; k++ ) {
				sum = sum + pow( ( powerBuffer[ k ] - powerBuffer1[ k ] ), 2.0 ); 
				//matrixResultOut << "\npowerBuffer: " << powerBuffer[ k ] << "\npowerBuffer1: " << powerBuffer1[ k ] << endl;
			}
			for ( int i = 0; i < nodeNumber; i++ ) {
				sum = sum + pow( ( angleBuffer[ i ] - angleBuffer1[ i ] ), 2.0 );
				//matrixResultOut << "\nangleBuffer: " << angleBuffer[ i ] << "\nangleBuffer1: " << angleBuffer1[ i ] << endl;
			}
		}
		else {
			for ( int i = 0; i < nodeNumber; i++ )
				sum = sum + pow( ( angleBuffer[ i ] ), 2.0 ); 
			for ( int k = 0; k < deviceTermCount; k++ )
				sum = sum + pow( ( powerBuffer[ k ] - ptildeinitBuffer[ k ] ), 2.0 );
		}
		
		dualTol = ( Rho ) * sqrt( sum );
		matrixResultOut << sqrt( sum ) << endl;
		matrixResultOut << "\nDual Tolerance at the end of this iteration is: " << dualTol << endl;
		matrixResultOut << "\nObjective value at the end of this iteration is ($): " << calcObjective << endl;
		matrixResultOut << "\n****************End of " << iteration_count << " -th iteration***********\n";
		objectiveValue.push_back( calcObjective ); // record the objective values

	} // end of one iteration
	
	clock_t stop_s = clock();  // end
	cout << "\nExecution time (s): " << static_cast<double>( stop_s - start_s ) / CLOCKS_PER_SEC << endl;

	ofstream iterationResultOut( "itresult.txt", ios::out ); // create a new file itresult.txt to output the results
	
	// exit program if unable to create file
	if ( !iterationResultOut ) {
		cerr << "File could not be opened" << endl;
		exit( 1 );
	}
	
	iterationResultOut << "\nIteration Count: " << endl;
	vector< int >::iterator iterationCountIterator; 
	for ( iterationCountIterator = iterationGraph.begin(); iterationCountIterator != iterationGraph.end(); iterationCountIterator++ )  		{
		iterationResultOut << *iterationCountIterator << endl;
	}

	ofstream objectiveResultOut( "objective.txt", ios::out ); // create a new file objective.txt to output the results
	
	// exit program if unable to create file
	if ( !objectiveResultOut ) {
		cerr << "File could not be opened" << endl;
		exit( 1 );
	}
	
	objectiveResultOut << "\nObjective value: " << endl;
	vector< double >::iterator objectiveIterator; 
	for ( objectiveIterator = objectiveValue.begin(); objectiveIterator != objectiveValue.end(); objectiveIterator++ )  {
		objectiveResultOut << *objectiveIterator << endl;
	}
	
	ofstream primalResultOut( "primresult.txt", ios::out ); // create a new file primresult.txt to output the results
	
	// exit program if unable to create file
	if ( !primalResultOut ) {
		cerr << "File could not be opened" << endl;
		exit( 1 );
	}
	
	primalResultOut << "\nPrimal Tolerance: " << endl;
	vector< double >::iterator primalToleranceIterator;
	for ( primalToleranceIterator = primTolGraph.begin(); primalToleranceIterator != primTolGraph.end(); primalToleranceIterator++ )  		{
		primalResultOut << *primalToleranceIterator << endl;
	}
	
	ofstream dualResultOut( "dualresult.txt", ios::out ); // create a new file dualresult.txt to output the results
	
	// exit program if unable to create file
	if ( !dualResultOut ) {
		cerr << "File could not be opened" << endl;
		exit( 1 );
	}
	
	dualResultOut << "\nDual Tolerance: " << endl;
	vector< double >::iterator dualToleranceIterator;
	for ( dualToleranceIterator = dualTolGraph.begin(); dualToleranceIterator != dualTolGraph.end(); dualToleranceIterator++ )  		
	{
		dualResultOut << *dualToleranceIterator << endl;
	}
} // end runSimulation

	




	

	
