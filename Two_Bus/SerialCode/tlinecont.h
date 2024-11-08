// tlineContingency derived class definition
// Member functions defined in tlinecont.cpp
#ifndef TLINECONT_H
#define TLINECONT_H

#include "transl.h" // transmissionLine class definition

class tlineContingency : public transmissionLine {

private:
	int translCID; // ID number of the line corresponding to the outaged line
	double ptCMax = pow( 10.0, -100.0 ); // power transfer capacity corresponding to the outaged line
	double resCT = pow( 10.0, 100.0 ); // resistance corresponding to the outaged line
	double reacCT = pow( 10.0, 100.0 ); // reactance corresponding to the outaged line
	double Pt1C, Pt2C, Thetat1C, Thetat2C; // Iterates for power and angle in the outaged case
	double v1C, v2C; // voltage angle constraint Lagrange multipliers for outaged condition

public:
	tlineContingency( int, Node *, Node *, double, double, double, double, int );

}; // end class tlineContingency

#endif // TLINECONT_H
