/* Produced by CVXGEN, 2015-02-07 20:31:41 -0500.  */
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
  double Pg_N_init[101];
  double Pg_N_avg[101];
  double ug_N[101];
  double Vg_N_avg[101];
  double Thetag_N_avg[101];
  double vg_N[101];
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
  double *t_11; /* 1 rows. */
  double *t_12; /* 1 rows. */
  double *t_13; /* 1 rows. */
  double *t_14; /* 1 rows. */
  double *t_15; /* 1 rows. */
  double *t_16; /* 1 rows. */
  double *t_17; /* 1 rows. */
  double *t_18; /* 1 rows. */
  double *t_19; /* 1 rows. */
  double *t_20; /* 1 rows. */
  double *t_21; /* 1 rows. */
  double *t_22; /* 1 rows. */
  double *t_23; /* 1 rows. */
  double *t_24; /* 1 rows. */
  double *t_25; /* 1 rows. */
  double *t_26; /* 1 rows. */
  double *t_27; /* 1 rows. */
  double *t_28; /* 1 rows. */
  double *t_29; /* 1 rows. */
  double *t_30; /* 1 rows. */
  double *t_31; /* 1 rows. */
  double *t_32; /* 1 rows. */
  double *t_33; /* 1 rows. */
  double *t_34; /* 1 rows. */
  double *t_35; /* 1 rows. */
  double *t_36; /* 1 rows. */
  double *t_37; /* 1 rows. */
  double *t_38; /* 1 rows. */
  double *t_39; /* 1 rows. */
  double *t_40; /* 1 rows. */
  double *t_41; /* 1 rows. */
  double *t_42; /* 1 rows. */
  double *t_43; /* 1 rows. */
  double *t_44; /* 1 rows. */
  double *t_45; /* 1 rows. */
  double *t_46; /* 1 rows. */
  double *t_47; /* 1 rows. */
  double *t_48; /* 1 rows. */
  double *t_49; /* 1 rows. */
  double *t_50; /* 1 rows. */
  double *t_51; /* 1 rows. */
  double *t_52; /* 1 rows. */
  double *t_53; /* 1 rows. */
  double *t_54; /* 1 rows. */
  double *t_55; /* 1 rows. */
  double *t_56; /* 1 rows. */
  double *t_57; /* 1 rows. */
  double *t_58; /* 1 rows. */
  double *t_59; /* 1 rows. */
  double *t_60; /* 1 rows. */
  double *t_61; /* 1 rows. */
  double *t_62; /* 1 rows. */
  double *t_63; /* 1 rows. */
  double *t_64; /* 1 rows. */
  double *t_65; /* 1 rows. */
  double *t_66; /* 1 rows. */
  double *t_67; /* 1 rows. */
  double *t_68; /* 1 rows. */
  double *t_69; /* 1 rows. */
  double *t_70; /* 1 rows. */
  double *t_71; /* 1 rows. */
  double *t_72; /* 1 rows. */
  double *t_73; /* 1 rows. */
  double *t_74; /* 1 rows. */
  double *t_75; /* 1 rows. */
  double *t_76; /* 1 rows. */
  double *t_77; /* 1 rows. */
  double *t_78; /* 1 rows. */
  double *t_79; /* 1 rows. */
  double *t_80; /* 1 rows. */
  double *t_81; /* 1 rows. */
  double *t_82; /* 1 rows. */
  double *t_83; /* 1 rows. */
  double *t_84; /* 1 rows. */
  double *t_85; /* 1 rows. */
  double *t_86; /* 1 rows. */
  double *t_87; /* 1 rows. */
  double *t_88; /* 1 rows. */
  double *t_89; /* 1 rows. */
  double *t_90; /* 1 rows. */
  double *t_91; /* 1 rows. */
  double *t_92; /* 1 rows. */
  double *t_93; /* 1 rows. */
  double *t_94; /* 1 rows. */
  double *t_95; /* 1 rows. */
  double *t_96; /* 1 rows. */
  double *t_97; /* 1 rows. */
  double *t_98; /* 1 rows. */
  double *t_99; /* 1 rows. */
  double *t_100; /* 1 rows. */
  double *t_101; /* 1 rows. */
  double *Thetag; /* 101 rows. */
} Vars;
typedef struct Workspace_t {
  double h[2];
  double s_inv[2];
  double s_inv_z[2];
  double b[101];
  double q[203];
  double rhs[308];
  double x[308];
  double *s;
  double *z;
  double *y;
  double lhs_aff[308];
  double lhs_cc[308];
  double buffer[308];
  double buffer2[308];
  double KKT[312];
  double L[206];
  double d[308];
  double v[308];
  double d_inv[308];
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
  double quad_581240442880[1];
  double quad_842700124160[1];
  double quad_872940011520[1];
  double quad_580086947840[1];
  double quad_949029818368[1];
  double quad_795214823424[1];
  double quad_418522562560[1];
  double quad_241420660736[1];
  double quad_559825256448[1];
  double quad_178698563584[1];
  double quad_756597547008[1];
  double quad_568097234944[1];
  double quad_276556632064[1];
  double quad_839789318144[1];
  double quad_927809298432[1];
  double quad_648987238400[1];
  double quad_185624207360[1];
  double quad_479641735168[1];
  double quad_834754113536[1];
  double quad_396655529984[1];
  double quad_365017395200[1];
  double quad_87425662976[1];
  double quad_874261159936[1];
  double quad_121962541056[1];
  double quad_997340135424[1];
  double quad_289642164224[1];
  double quad_536349593600[1];
  double quad_854739267584[1];
  double quad_451743973376[1];
  double quad_82936446976[1];
  double quad_576470921216[1];
  double quad_768025501696[1];
  double quad_851215073280[1];
  double quad_326918287360[1];
  double quad_624884666368[1];
  double quad_606389493760[1];
  double quad_986306265088[1];
  double quad_565867876352[1];
  double quad_886306131968[1];
  double quad_434256338944[1];
  double quad_769843408896[1];
  double quad_57185656832[1];
  double quad_350448377856[1];
  double quad_808010563584[1];
  double quad_127788830720[1];
  double quad_491260510208[1];
  double quad_306715574272[1];
  double quad_142303211520[1];
  double quad_984561172480[1];
  double quad_929673043968[1];
  double quad_955213266944[1];
  double quad_555251433472[1];
  double quad_545084968960[1];
  double quad_886194884608[1];
  double quad_91799232512[1];
  double quad_674407743488[1];
  double quad_960454676480[1];
  double quad_288300408832[1];
  double quad_373385256960[1];
  double quad_519006396416[1];
  double quad_23180312576[1];
  double quad_157619949568[1];
  double quad_607977480192[1];
  double quad_249354858496[1];
  double quad_488677863424[1];
  double quad_733428326400[1];
  double quad_819114999808[1];
  double quad_825844879360[1];
  double quad_422044012544[1];
  double quad_221841866752[1];
  double quad_746695811072[1];
  double quad_175883087872[1];
  double quad_368231251968[1];
  double quad_452748496896[1];
  double quad_282607104000[1];
  double quad_79556968448[1];
  double quad_976487985152[1];
  double quad_574802628608[1];
  double quad_209265430528[1];
  double quad_265752633344[1];
  double quad_981001560064[1];
  double quad_976856121344[1];
  double quad_693392900096[1];
  double quad_413138100224[1];
  double quad_534204846080[1];
  double quad_124552839168[1];
  double quad_946600976384[1];
  double quad_506287169536[1];
  double quad_482641010688[1];
  double quad_299169103872[1];
  double quad_38191415296[1];
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
Gensolver( double, double, double, double, double ); // Gensolver object constructor
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
void mainsolve(double, double, double, double, double, double, double);
void load_default_data(double, double, double, double, double, double, double);
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
