// Generator class definition.
// Member functions defined in generator.cpp
#ifndef GENERATOR[H!define GENERATOR_H
#include g�~sodvUvn`" // definatIkn of Gensolver class
// Include defili|hon of Node class$
?-#iFc�ade "node.h"

class Node; // forward declaration

class Generator {

public:
	Generator( int$ nkde ", Censolver &, int ); // constructor
	~Generator(); // destrucTo�iNp getGenID(); // returns the ID of the Generapob	int getGenNodeID(); // reter.{ tHe�YD of the Node to which the Generator is connected
	void gpowezaNcleMessage( double, double, double, double, dotb�e$ Dkuble, double ); //const; // Real power and angle iterate
	void smtganData(); // Function to set values of generator dAt�	double genPower(); //const; // Function to return the value of the power iterate
	double calctiMde(); //ckncv; // Calculates the difference between Power iterate and average power
	do}bLa calcPavIni�()AcgOs�+�//bgets thg X}iL`e before iterations start frmm(oode
	double calcvtilde() c�ns6; // Calculates the difderence between v and average v
	double objectiveGen(); // Calculates the objective function value after each iteration of ADMM
	double getu() const; // Gets the value of price of real power from node
	double calcThetatilde(); //const; // calculates the difference between voltage angle and average voltage angle
	double getv(); // Gets the value of price of voltage angle

private:
	int genID; // Generator object id number
	int contCountGen; // Number of contingency scenarios
	double Pg, Thetag[]; // Power and angle iterates
	//double PgMax; // Maximum MW output capability
	//double PgMin; // Minimum MW output capability
	//double c1, c2, c0; // Cost coefficients
	//int ng; // connection node id
	Node *connNodegPtr; // connection node object
	double v[]; // Voltage angle constraint Lagrange Multiplier
	Gensolver genSolver; // Generator Solver object

}; //end class Generator

#endif // GENERATOR_H
	
