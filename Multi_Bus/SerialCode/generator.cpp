// Member functions for class Generator.
#include <iostream>
#include <vector>
#include <array>
#include <stdio.h>
// include Generator class definition from generator.h
#include "generator.h"
// Include definition of Node class 
#include "node.h"
// Include Generator solver class defintion
#include "gensolver.h"
#include "gurobi_c++.h"
//#include "mosek.h"

using namespace std;

Generator::Generator( int idOfGen, Node *nodeConng, Gensolver &paramOfGen, int countOfContingency ) // constructor begins
	: genID( idOfGen ),
	  connNodegPtr( nodeConng ),
	  genSolver( paramOfGen ),
	  contCountGen( countOfContingency ),
	  deviceNature( 1 )
{
	connNodegPtr->setgConn(); // increments the generation connection variable to node
	setGenData(); // calls setGenData member function to set the parameter values

} // constructor ends

Generator::~Generator() // destructor
{
	//cout << "\nThe generator object having ID " << genID << " have been destroyed.\n";

} // end of destructor

int Generator::getGenID() // function getGenID begins
{
	return genID; // returns the ID of the generator object
} // end of 7getGenID function

int Generator::getGenNodeID() // function getGenNodeID begins
{
	return connNodegPtr->getNodeID(); // returns the ID number of the node to which the generator object is connected
} // end of getGenNodeID function

void Generator::setGenData() // start setGenData function
{
	Pg = 0.0; // Initialize power iterate
	Thetag = new double[ ( contCountGen + 1 ) ];
	//Thetag = genSolver.getThetaPtr(); // Initialize angle iterate
	for (int i = 0; i < ( contCountGen + 1 ); ++i ) {
		Thetag[ i ] = 0.0; // Initialize angle iterate
	}
	v = new double[ ( contCountGen + 1 ) ];
	for (int i = 0; i < ( contCountGen + 1 ); ++i ) {
		v[ i ] = 0.0; // Initialize the Lagrange multiplier corresponding voltage angle constraint to zero
	}
	
} // end of setGenData function

void Generator::gpowerangleMessage( double gRho, double Pprevit[], double Pnetavg[], double uprev[], double vprevavg[], double Aprevavg[], double vprev[] ) // function gpowerangleMessage begins
{
	genSolver.mainsolve( gRho, Pprevit, Pnetavg, uprev, vprevavg, Aprevavg, vprev ); // calls the Generator optimization solver
	Pg = genSolver.getPSol(); // get the Generator Power iterate
	//Thetag = genSolver.getThetaPtr(); // get the Generator voltage angle iterate
	for ( int i = 0; i <= contCountGen; ++i ) {
		Thetag[ i ] = *( genSolver.getThetaPtr() + i );
	}
	connNodegPtr->powerangleMessage( Pg, v, Thetag, deviceNature, contCountGen ); // passes to node object the corresponding iterates of power, angle, v, and number of scenarios
} // function gpowerangleMessage ends


/*void Generator::genOptMosek( double gRho, double Pprevit[], double Pnetavg[], double uprev[], double vprevavg[], double Aprevavg[], double vprev[] ) // function genOptGurobiSparse begins
{
  	double c[(2+contCountGen)];
	for ( int i = 0; i <= contCountGen + 1; ++i )
	{
		if ( i == 0 )
		{
			c[ i ] = genSolver.getLinCoeff();
			for ( int j = 0; j <= contCountGen; ++j ) 
				c[ i ] = c[ i ] - 2 * (gRho / 2.0 ) * ( Previt[ j ] - Pnetavg[ j ] - uprev[ j ] );
		}
		else
			c[ i ] = -2 * (gRho / 2.0 ) * ( vprevavg[ i ] + Aprevavg[ i ] - vprev[ i ] );
	}

  	MSKboundkeye  bkc[] = {MSK_BK_LO};
  	double        blc[] = {1.0};
  	double        buc[] = {+MSK_INFINITY}; 
    
  	MSKboundkeye  bkx[] = {MSK_BK_LO,
                         MSK_BK_LO,
                         MSK_BK_LO};
  	double        blx[] = {0.0,
                         0.0,
                         0.0};
  	double        bux[] = {+MSK_INFINITY,
                         +MSK_INFINITY,
                         +MSK_INFINITY};
  
  	MSKint32t     aptrb[] = {0,   1,   2},
                	aptre[] = {1,   2,   3},
                	asub[]  = {0,   0,   0};
  	double        aval[]  = {1.0, 1.0, 1.0};
  
  	MSKint32t     qsubi[(2+contCountGen)];
  	MSKint32t     qsubj[(2+contCountGen)];
  	double        qval[(2+contCountGen)];
  
  	MSKint32t     i,j;
  	double        xx[(2+contCountGen)];

  	MSKenv_t      env = NULL;
  	MSKtask_t     task = NULL;
  	MSKrescodee   r;
  
  	// Create the mosek environment. 
  	r = MSK_makeenv(&env,NULL);

  	if ( r==MSK_RES_OK )
  	{ 
    		// Create the optimization task. 
    		r = MSK_maketask(env,2,(2+contCountGen),&task);

    		if ( r==MSK_RES_OK )
    		{
      			r = MSK_linkfunctotaskstream(task,MSK_STREAM_LOG,NULL,printstr);
  
      			// Append 'NUMCON' empty constraints.
       			//The constraints will initially have no bounds. 
      			if ( r == MSK_RES_OK )
        			r = MSK_appendcons(task,2);
  
      			// Append 'NUMVAR' variables.
       			//The variables will initially be fixed at zero (x=0). 
      			if ( r == MSK_RES_OK )
        			r = MSK_appendvars(task,(2+contCountGen));
  
      			// Optionally add a constant term to the objective. 
      			if ( r ==MSK_RES_OK )
        			r = MSK_putcfix(task,0.0);
      			for(j=0; j<NUMVAR && r == MSK_RES_OK; ++j)
      			{
        			// Set the linear term c_j in the objective.
        			if(r == MSK_RES_OK)
          				r = MSK_putcj(task,j,c[j]);
  
        			// Set the bounds on variable j.
         			//blx[j] <= x_j <= bux[j] 
        			if(r == MSK_RES_OK)
          				r = MSK_putvarbound(task,
                              					j,           // Index of variable.
                              					bkx[j],      // Bound key.
                              					blx[j],      // Numerical value of lower bound.
                              					bux[j]);     // Numerical value of upper bound.
  
        			// Input column j of A    
        			if(r == MSK_RES_OK)
          				r = MSK_putacol(task,
                          				j,                 // Variable (column) index.
                          				aptre[j]-aptrb[j], // Number of non-zeros in column j.
                          				asub+aptrb[j],     // Pointer to row indexes of column j.
                          				aval+aptrb[j]);    // Pointer to Values of column j.
        
      			}
  
      			// Set the bounds on constraints.
         		for i=1, ...,NUMCON : blc[i] <= constraint i <= buc[i] 
      			for(i=0; i<NUMCON && r==MSK_RES_OK; ++i)
        		r = MSK_putconbound(task,
                            			i,           // Index of constraint.
                            			bkc[i],      // Bound key.
                            			blc[i],      // Numerical value of lower bound.
                            			buc[i]);     // Numerical value of upper bound.

      			if ( r==MSK_RES_OK )
      			{
        			//
         			// The lower triangular part of the Q
         			// matrix in the objective is specified.
         			

        			qsubi[0] = 0;   qsubj[0] = 0;  qval[0] = 2.0;
        			qsubi[1] = 1;   qsubj[1] = 1;  qval[1] = 0.2;
        			qsubi[2] = 2;   qsubj[2] = 0;  qval[2] = -1.0;
        			qsubi[3] = 2;   qsubj[3] = 2;  qval[3] = 2.0;

        			// Input the Q for the objective. 

        			r = MSK_putqobj(task,NUMQNZ,qsubi,qsubj,qval);
      			}

      			if ( r==MSK_RES_OK )
      			{
        			MSKrescodee trmcode;
        
        			// Run optimizer 
        			r = MSK_optimizetrm(task,&trmcode);

        			// Print a summary containing information
           			//about the solution for debugging purposes
        			MSK_solutionsummary (task,MSK_STREAM_MSG);
        
        			if ( r==MSK_RES_OK )
        			{
          				MSKsolstae solsta;
          				int j;
          
          				MSK_getsolsta (task,MSK_SOL_ITR,&solsta);
          
          				switch(solsta)
          				{
            					case MSK_SOL_STA_OPTIMAL:   
           					case MSK_SOL_STA_NEAR_OPTIMAL:
              						MSK_getxx(task,
                       						MSK_SOL_ITR,    // Request the interior solution. 
                       						xx);
              
              						printf("Optimal primal solution\n");
              						for(j=0; j<NUMVAR; ++j)
                						printf("x[%d]: %e\n",j,xx[j]);
              		
              						break;
            					case MSK_SOL_STA_DUAL_INFEAS_CER:
            					case MSK_SOL_STA_PRIM_INFEAS_CER:
            					case MSK_SOL_STA_NEAR_DUAL_INFEAS_CER:
            					case MSK_SOL_STA_NEAR_PRIM_INFEAS_CER:  
              						printf("Primal or dual infeasibility certificate found.\n");
              						break;
              
            					case MSK_SOL_STA_UNKNOWN:
              						printf("The status of the solution could not be determined.\n");
              						break;
            					default:
              						printf("Other solution status.");
              						break;
          				}
        			}
        			else
        			{
          				printf("Error while optimizing.\n");
        			}
      			}
    
      			if (r != MSK_RES_OK)
      			{
        			// In case of an error print error code and description.      
        			char symname[MSK_MAX_STR_LEN];
        			char desc[MSK_MAX_STR_LEN];
        
        			printf("An error occurred while optimizing.\n");     
        			MSK_getcodedesc (r,
                         			symname,
                         			desc);
        			printf("Error %s - '%s'\n",symname,desc);
      			}
    		}
    		MSK_deletetask(&task);
  	}
  	MSK_deleteenv(&env);

  	return (r);
} 

void Generator::genOptGurobiSparse( double gRho, double Pprevit[], double Pnetavg[], double uprev[], double vprevavg[], double Aprevavg[], double vprev[], GRBEnv* environmentGUROBI ) // function genOptGurobiSparse begins
{
	try {

    		GRBModel *modelGenQP = new GRBModel(*environmentGUROBI);
    		modelGenQP->set(GRB_StringAttr_ModelName, "genQP" + to_string(genID));
		GRBVar decvar[dimCol+1];
		cout << "\nGurobi decision variables created" << endl;
		double z; // variable to store the objective value
	
		// SPECIFICATION OF PROBLEM PARAMETERS //
		// Dummy Decision Variable //
		cout << "\nGurobi decision variables to be assigned" << endl;
		decvar[0] = modelSubnetQP->addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS);
		//Decision Variable Definitions, Bounds, and Objective Function Co-efficients//
		cout << "\nGurobi dummy decision variable created" << endl;
		int colCount = 1;
    		// Create variables

    		GRBVar Powg = model.addVar(-1e20, 1e20, 0.0, GRB_CONTINUOUS, "Powg");
		GRBVar* Thetg;
		for ( int i = 0; i <= contCountGen; ++i )
    			Thetg[ i ] = model.addVar(-1e20, 1e20, 0.0, GRB_CONTINUOUS, "ThetgScen");

    		// Integrate new variables

    		model.update();

    		// Set objective
		
		double ThetQuad = 0.0;
		double ThetLin = 0.0;
		double PowLin = getlinCoeff();
		double Const = getconstCoeff();
		for ( int i = 0; i <= contCountGen; ++i ) 
		{
			Const += ( gRho / 2.0 ) * ( pow( ( Pprevit[ i ] - Pnetavg[ i ] - uprev[ i ] ), 2.0 ) + pow( ( vprevavg[ i ] + Aprevavg[ i ] - vprev[ i ] ), 2.0 ) );
		}
		for ( int i = 0; i <= contCountGen; ++i )
		{
			PowLin -= ( gRho ) * ( Pprevit[ i ] - Pnetavg[ i ] - uprev[ i ] );
		}
		for ( int i = 0; i <= contCountGen; ++i )
		{
			ThetLin -= ( gRho ) * ( vprevavg[ i ] + Aprevavg[ i ] - vprev[ i ] ) * Thetg[ i ];
		}
		for ( int i = 0; i <= contCountGen; ++i )
		{
			ThetQuad += ( gRho ) * Thetg[ i ] * Thetg[ i ];
		}
			
    		GRBQuadExpr obj = ( getquadCoeff() + ( gRho / 2 ) * ( contCountGen + 1 ) ) * Powg * Powg + ThetQuad + ThetLin + PowLin * Powg + Const;
    		model.setObjective(obj);

    		// Add constraint: Powg >= getPmin()

    		model.addConstr(Powg >= getPmin(), "c0");

    		// Add constraint: Powg <= getPmax()

    		model.addConstr(Powg <= getPmax(), "c1");

    		// Optimize model

    		model.optimize();

    		cout << Powg.get(GRB_StringAttr_VarName) << " " << Powg.get(GRB_DoubleAttr_X) << endl;
		for ( int i = 0; i <= contCountGen; ++i )
    			cout << Thetg[ i ].get(GRB_StringAttr_VarName) << " " << Thetg[ i ].get(GRB_DoubleAttr_X) << endl;

    		cout << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << endl;

		Pg = Powg.get(GRB_DoubleAttr_X); // get the Generator Power iterate
		double ThetaG[ 1 + contCountGen ];
		for ( int i = 0; i <= contCountGen; ++i )
			ThetaG[ i ] = Thetg[ i ].get(GRB_DoubleAttr_X);
		connNodegPtr->powerangleMessage( Pg, v, ThetaG, deviceNature, contCountGen ); // passes to node object the corresponding iterates of power, angle, v, and number of scenarios

  	} catch(GRBException e) {
    		cout << "Error code = " << e.getErrorCode() << endl;
    		cout << e.getMessage() << endl;
  	} catch(...) {
    		cout << "Exception during optimization" << endl;
  	}
}

static bool Generator::genOptGurobi(GRBEnv* env,
               int     rows,
               int     cols,
               double* c,     // linear portion of objective function 
               double* Q,     // quadratic portion of objective function 
               double* A,     // constraint matrix 
               char*   sense, // constraint senses 
               double* rhs,   // RHS vector 
               double* lb,    // variable lower bounds 
               double* ub,    // variable upper bounds 
               char*   vtype, // variable types (continuous, binary, etc.) 
               double* solution,
               double* objvalP)
{
  GRBModel model = GRBModel(*env);
  int i, j;
  bool success = false;

  // Add variables to the model 

  GRBVar* vars = model.addVars(lb, ub, NULL, vtype, NULL, cols);
  model.update();

  // Populate A matrix 

  for (i = 0; i < rows; i++) {
    GRBLinExpr lhs = 0;
    for (j = 0; j < cols; j++)
      if (A[i*cols+j] != 0)
        lhs += A[i*cols+j]*vars[j];
    model.addConstr(lhs, sense[i], rhs[i]);
  }

  GRBQuadExpr obj = 0;

  for (j = 0; j < cols; j++)
    obj += c[j]*vars[j];
  for (i = 0; i < cols; i++)
    for (j = 0; j < cols; j++)
      if (Q[i*cols+j] != 0)
        obj += Q[i*cols+j]*vars[i]*vars[j];

  model.setObjective(obj);

  model.update();
  model.write("dense.lp");

  model.optimize();

  if (model.get(GRB_IntAttr_Status) == GRB_OPTIMAL) {
    *objvalP = model.get(GRB_DoubleAttr_ObjVal);
    for (i = 0; i < cols; i++)
      solution[i] = vars[i].get(GRB_DoubleAttr_X);
    success = true;
  }

  delete[] vars;

  return success;
}*/

double Generator::genPower() // function genPower begins
{
	return Pg; // returns the Pg iterate
} // function genPower ends

double Generator::objectiveGen() // function objectiveGen begins
{
	return genSolver.getObj(); //returns the evaluated objective
} // function objectiveGen ends

double Generator::calcPtilde( int contin ) // function calcPtilde begins
{
	double P_avg = connNodegPtr->PavMessageCont( contin ); // Gets average power from the corresponding node object
	double Ptilde = Pg - P_avg; // calculates the difference between power iterate and average
	return Ptilde; // returns the difference
} // function calcPtilde ends

double Generator::calcPavInit() const // function calcPavInit begins
{
	return connNodegPtr->devpinitMessage(); // seeks the initial Ptilde from the node
} // function calcPavInit ends

double Generator::calcPavInitc( int contin ) const // function calcPavInitc begins
{
	return connNodegPtr->devpinitMessageCont( contin ); // seeks the initial Ptilde from the node under contingency
} // function calcPavInitc ends

double Generator::getu( int contin ) const // function getu begins
{
	double u = connNodegPtr->uMessage( contin ); // gets the value of the price corresponding to power balance from node
	return u; // returns the price
} // function getu ends

double Generator::calcThetatilde( int contin ) // function calcThetatilde begins
{
	double Theta_avg = connNodegPtr->ThetaavMessageCont( contin ); // get the average voltage angle at the particular node
	double Theta_tilde = Thetag[ contin ] - Theta_avg; // claculate the deviation between the voltage angle of the device and the average
	return Theta_tilde; // return the deviation
} // function calcThetatilde ends

double Generator::calcvtilde( int contin ) const // function calcvtilde begins
{
	double v_avg = connNodegPtr->vavMessage(); // get the average of the Lagrange multiplier corresponding to voltage angle balance
	double v_tilde = v[ contin ] - v_avg; // calculate the deviation of the node Lagrange multiplier to the average
	return v_tilde; // return the deviation
} // function calcvtilde ends

double Generator::getv( int contin ) // function getv begins
{
	v[ contin ] = v[ contin ] + calcThetatilde( contin ); // Calculate the value of the Lagrange multiplier corresponding to angle constraint
	return v[ contin ]; // Calculate the value of the Lagrange multiplier corresponding to angle constraint
} // function getv ends		
	
double Generator::getPmax() // start of getPmax function
{
	return genSolver.getPMax();
} // end of getPmax

double Generator::getPmin() // start of getPmin function
{
	return genSolver.getPMin();
} // end of getPmin

double Generator::getquadCoeff() // start of getquadCoeff function
{
	return genSolver.getQuadCoeff();
} // end of getquadCoeff

double Generator::getlinCoeff() // start of getlinCoeff function
{
	return genSolver.getLinCoeff();
} // end of getlinCoeff

double Generator::getconstCoeff() // start of getconstCoeff function
{
	return genSolver.getConstCoeff();
} // end of getconstCoeff
