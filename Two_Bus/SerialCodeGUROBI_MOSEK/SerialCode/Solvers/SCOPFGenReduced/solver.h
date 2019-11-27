/* Produced by CVXGEN, 2015-02-05 18:05:36 -0500.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: solver.h. */
/* Description: Header file with relevant definitions. */
#ifndef SOLVER_H
#define SOLVER_H
/* Uncomment the next line to remove all library dependencies. */
/*#define ZERO_LIBRARY_MODE */
#ifdef MATLAB_MEX_FILE
/* Matlab functions. MATLAB_MEX_FILE will be defined by the mex compiler. */
/* If you are not using the mex compiler, this functionality will not intrude, */
/* as it will be completely disabled at compile-time. */
#include "mex.h"
#else
#ifndef ZERO_LIBRARY_MODE
#include <stdio.h>
#endif
#endif
/* Space must be allocated somewhere (testsolver.c, csolve.c or your own */
/* program) for the global variables vars, params, work and settings. */
/* At the bottom of this file, they are externed. */
#ifndef ZERO_LIBRARY_MODE
#include <math.h>
#define pm(A, m, n) printmatrix(#A, A, m, n, 1)
#endif
typedef struct Params_t {
  double c2[1];
  double c1[1];
  double c0[1];
  double rho[1];
  double Pg_N_init_0[1];
  double Pg_N_avg_0[1];
  double ug_N_0[1];
  double Vg_N_avg_0[1];
  double Thetag_N_avg_0[1];
  double vg_N_0[1];
  double Pg_N_init_1[1];
  double Pg_N_avg_1[1];
  double ug_N_1[1];
  double Vg_N_avg_1[1];
  double Thetag_N_avg_1[1];
  double vg_N_1[1];
  double Pg_N_init_2[1];
  double Pg_N_avg_2[1];
  double ug_N_2[1];
  double Vg_N_avg_2[1];
  double Thetag_N_avg_2[1];
  double vg_N_2[1];
  double Pg_N_init_3[1];
  double Pg_N_avg_3[1];
  double ug_N_3[1];
  double Vg_N_avg_3[1];
  double Thetag_N_avg_3[1];
  double vg_N_3[1];
  double Pg_N_init_4[1];
  double Pg_N_avg_4[1];
  double ug_N_4[1];
  double Vg_N_avg_4[1];
  double Thetag_N_avg_4[1];
  double vg_N_4[1];
  double Pg_N_init_5[1];
  double Pg_N_avg_5[1];
  double ug_N_5[1];
  double Vg_N_avg_5[1];
  double Thetag_N_avg_5[1];
  double vg_N_5[1];
  double Pg_N_init_6[1];
  double Pg_N_avg_6[1];
  double ug_N_6[1];
  double Vg_N_avg_6[1];
  double Thetag_N_avg_6[1];
  double vg_N_6[1];
  double Pg_N_init_7[1];
  double Pg_N_avg_7[1];
  double ug_N_7[1];
  double Vg_N_avg_7[1];
  double Thetag_N_avg_7[1];
  double vg_N_7[1];
  double Pg_N_init_8[1];
  double Pg_N_avg_8[1];
  double ug_N_8[1];
  double Vg_N_avg_8[1];
  double Thetag_N_avg_8[1];
  double vg_N_8[1];
  double Pg_N_init_9[1];
  double Pg_N_avg_9[1];
  double ug_N_9[1];
  double Vg_N_avg_9[1];
  double Thetag_N_avg_9[1];
  double vg_N_9[1];
  double Pg_N_init_10[1];
  double Pg_N_avg_10[1];
  double ug_N_10[1];
  double Vg_N_avg_10[1];
  double Thetag_N_avg_10[1];
  double vg_N_10[1];
  double PgMin[1];
  double PgMax[1];
  double *Pg_N_init[11];
  double *Pg_N_avg[11];
  double *ug_N[11];
  double *Vg_N_avg[11];
  double *Thetag_N_avg[11];
  double *vg_N[11];
} Params;
typedef struct Vars_t {
  double *Pg; /* 1 rows. */
  double *Thetag_0; /* 1 rows. */
  double *Thetag_1; /* 1 rows. */
  double *Thetag_2; /* 1 rows. */
  double *Thetag_3; /* 1 rows. */
  double *Thetag_4; /* 1 rows. */
  double *Thetag_5; /* 1 rows. */
  double *Thetag_6; /* 1 rows. */
  double *Thetag_7; /* 1 rows. */
  double *Thetag_8; /* 1 rows. */
  double *Thetag_9; /* 1 rows. */
  double *Thetag_10; /* 1 rows. */
  double *Thetag[11];
} Vars;
typedef struct Workspace_t {
  double h[2];
  double s_inv[2];
  double s_inv_z[2];
  double *b;
  double q[12];
  double rhs[16];
  double x[16];
  double *s;
  double *z;
  double *y;
  double lhs_aff[16];
  double lhs_cc[16];
  double buffer[16];
  double buffer2[16];
  double KKT[20];
  double L[4];
  double d[16];
  double v[16];
  double d_inv[16];
  double gap;
  double optval;
  double ineq_resid_squared;
  double eq_resid_squared;
  double block_33[1];
  /* Pre-op symbols. */
  double frac_121674190848;
  double quad_600014270464[1];
  double quad_631547887616[1];
  double quad_861253439488[1];
  double quad_335606009856[1];
  double quad_419630354432[1];
  double quad_300112478208[1];
  double quad_722335502336[1];
  double quad_863528128512[1];
  double quad_407892983808[1];
  double quad_53514031104[1];
  double quad_198013468672[1];
  double quad_48438943744[1];
  double quad_898365714432[1];
  double quad_934929342464[1];
  double quad_793422544896[1];
  double quad_183681134592[1];
  double quad_924824883200[1];
  double quad_774359400448[1];
  double quad_364793888768[1];
  double quad_831331065856[1];
  double quad_24379666432[1];
  double quad_47350718464[1];
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
extern Vars vars;
extern Params params;
extern Workspace work;
extern Settings settings;
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
void setup_indexed_params(void);
void setup_indexed_optvars(void);
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
int main(int argc, char **argv);
void load_default_data(void);

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

#endif
