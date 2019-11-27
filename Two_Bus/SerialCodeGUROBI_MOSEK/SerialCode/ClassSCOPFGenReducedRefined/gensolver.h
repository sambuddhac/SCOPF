/* Produced by CVXGEN, 2015-02-06 22:35:37 -0500.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: solver.h. */
/* Description: Header file with relevant definitions. */
#ifndef GENSOLVER_H
#define GENSOLVER_H
#include <ctime>
#include <cstdlib>
/* Uncomment the next line to remove all library dependencies. */
/*#define ZERO_LIBRARY_MODE */
#ifdef MATLAB_MEX_FILE
/* Matlab functions. MATLAB_MEX_FILE will be defined by the mex compiler. */
/* If you are not using the mex compiler, this functionality will not intrude, */
/* as it will be completely disabled at compile-time. */
//#include "mex.h"
#else
#ifndef ZERO_LIBRARY_MODE
#include <stdio.h>
#endif
#endif
/* Space must be allocated somewhere (testsolver.c, csolve.c or your own */
/* program) for the global variables vars, params, work and settings. */
/* At the bottom of this file, they are externed. */
#ifndef ZERO_LIBRARY_MODE
#include <cmath>
#define pm(A, m, n) printmatrix(#A, A, m, n, 1)
#endif
using namespace std;
class Gensolver {
private:
typedef struct Params_t {
  int caseNumber; 
  double c2[1];
  double c1[1];
  double c0[1];
  double rho[1];
  double Pg_N_init[10];
  double Pg_N_avg[10];
  double ug_N[10];
  double Vg_N_avg[10];
  double Thetag_N_avg[10];
  double vg_N[10];
  double PgMin[1];
  double PgMax[1];
} Params;
typedef struct Vars_t {
  double *Pg; /* 1 rows. */
  double *t_01; /* 1 rows. */
  double *t_02; /* 1 rows. */
  double *t_03; /* 1 rows. */
  double *t_04; /* 1 rows. */
  double *t_05; /* 1 rows. */
  double *t_06; /* 1 rows. */
  double *t_07; /* 1 rows. */
  double *t_08; /* 1 rows. */
  double *t_09; /* 1 rows. */
  double *t_10; /* 1 rows. */
  double *Thetag; /* 10 rows. */
} Vars;
typedef struct Workspace_t {
  double h[2];
  double s_inv[2];
  double s_inv_z[2];
  double b[10];
  double q[21];
  double rhs[35];
  double x[35];
  double *s;
  double *z;
  double *y;
  double lhs_aff[35];
  double lhs_cc[35];
  double buffer[35];
  double buffer2[35];
  double KKT[39];
  double L[24];
  double d[35];
  double v[35];
  double d_inv[35];
  double gap;
  double optval;
  double ineq_resid_squared;
  double eq_resid_squared;
  double block_33[1];
  /* Pre-op symbols. */
  double frac_121674190848;
  double quad_611769487360[1];
  double quad_445109895168[1];
  double quad_793880735744[1];
  double quad_428578906112[1];
  double quad_39707512832[1];
  double quad_355912712192[1];
  double quad_113495719936[1];
  double quad_916626804736[1];
  double quad_386017529856[1];
  double quad_727622279168[1];
  int converged;
} Workspace;
typedef struct Settings_t {
  double resid_tol;
  double eps;
  int max_iters;
  int refine_steps;
  int better_start;
  /* Better start obviates the need for s_init and z_init. */
  double s_init;
  double z_init;
  int verbose;
  /* Show extra details of the iterative refinement steps. */
  int verbose_refinement;
  int debug;
  /* For regularization. Minimum value of abs(D_ii) in the kkt D factor. */
  double kkt_reg;
} Settings;
Vars vars;
Params params;
Workspace work;
Settings settings;
long global_seed;
clock_t tic_timestart;
double *Piterate;
double *Thiterate;
public:
Gensolver( int, double, double, double, double, double ); // Gensolver object constructor
~Gensolver(); // Gensolver object destructor
/* Function definitions in ldl.c: */
void ldl_solve(double *target, double *var);
void ldl_factor(void);
double check_factorization(void);
void matrix_multiply(double *result, double *source);
double check_residual(double *target, double *multiplicand);
void fill_KKT(void);

/* Function definitions in matrix_support.c: */
void multbymA(double *lhs, double *rhs);
void multbymAT(double *lhs, double *rhs);
void multbymG(double *lhs, double *rhs);
void multbymGT(double *lhs, double *rhs);
void multbyP(double *lhs, double *rhs);
void fillq(void);
void fillh(void);
void fillb(void);
void pre_ops(void);

/* Function definitions in solver.c: */
double eval_gap(void);
void set_defaults(void);
void setup_pointers(void);
void setup_indexing(void);
void set_start(void);
double eval_objv(void);
void fillrhs_aff(void);
void fillrhs_cc(void);
void refine(double *target, double *var);
double calc_ineq_resid_squared(void);
double calc_eq_resid_squared(void);
void better_start(void);
void fillrhs_start(void);
long solve(void);

/* Function definitions in testsolver.c: */
void mainsolve(double, double [], double [], double [], double [], double [], double []);
void load_default_data(double, double [], double [], double [], double [], double [], double []);
double getPSol(void);
double getThetaSol(void);
double getObj(void);

/* Function definitions in util.c: */
void tic(void);
float toc(void);
float tocq(void);
void printmatrix(char *name, double *A, int m, int n, int sparse);
double unif(double lower, double upper);
float ran1(long*idum, int reset);
float randn_internal(long *idum, int reset);
double randn(void);
void reset_rand(void);
};

#endif
