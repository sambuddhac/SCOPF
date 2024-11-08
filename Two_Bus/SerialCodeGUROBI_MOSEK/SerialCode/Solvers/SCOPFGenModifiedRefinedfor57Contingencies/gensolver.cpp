/* Produced by CVXGEN, 2015-09-15 18:52:16 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: util.c. */
/* Description: Common utility file for all cvxgen code. */
#include "gensolver.h"
#include <array>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;
void Gensolver::tic(void) {
  tic_timestart = clock();
}
float Gensolver::toc(void) {
  clock_t tic_timestop;
  tic_timestop = clock();
  printf("time: %8.2f.\n", (float)(tic_timestop - tic_timestart) / CLOCKS_PER_SEC);
  return (float)(tic_timestop - tic_timestart) / CLOCKS_PER_SEC;
}
float Gensolver::tocq(void) {
  clock_t tic_timestop;
  tic_timestop = clock();
  return (float)(tic_timestop - tic_timestart) / CLOCKS_PER_SEC;
}
void Gensolver::printmatrix(char *name, double *A, int m, int n, int sparse) {
  int i, j;
  printf("%s = [...\n", name);
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++)
      if ((sparse == 1) && (A[i+j*m] == 0))
        printf("         0");
      else
        printf("  % 9.4f", A[i+j*m]);
    printf(",\n");
  }
  printf("];\n");
}
double Gensolver::unif(double lower, double upper) {
  return lower + ((upper - lower)*rand())/RAND_MAX;
}
/* Next function is from numerical recipes in C. */
#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)
float Gensolver::ran1(long*idum, int reset) {
  int j;
  long k;
  static long iy=0;
  static long iv[NTAB];
  float temp;
  if (reset) {
    iy = 0;
  }
  if (*idum<=0||!iy) {
    if (-(*idum)<1)*idum=1;
    else *idum=-(*idum);
    for (j=NTAB+7; j>=0; j--) {
      k = (*idum)/IQ;
      *idum=IA*(*idum-k*IQ)-IR*k;
      if (*idum<0)*idum+=IM;
      if (j<NTAB)iv[j]=*idum;
    }
    iy = iv[0];
  }
  k = (*idum)/IQ;
  *idum = IA*(*idum-k*IQ)-IR*k;
  if (*idum<0)*idum += IM;
  j = iy/NDIV;
  iy = iv[j];
  iv[j] = *idum;
  if ((temp=AM*iy)> RNMX) return RNMX;
  else return temp;
}
/* Next function is from numerical recipes in C. */
float Gensolver::randn_internal(long *idum, int reset) {
  static int iset=0;
  static float gset;
  float fac, rsq, v1, v2;
  if (reset) {
    iset = 0;
  }
  if (iset==0) {
    do {
      v1 = 2.0*ran1(idum, reset)-1.0;
      v2 = 2.0*ran1(idum, reset)-1.0;
      rsq = v1*v1+v2*v2;
    } while(rsq >= 1.0 || rsq == 0.0);
    fac = sqrt(-2.0*log(rsq)/rsq);
    gset = v1*fac;
    iset = 1;
    return v2*fac;
  } else {
    iset = 0;
    return gset;
  }
}
double Gensolver::randn(void) {
  return randn_internal(&global_seed, 0);
}
void Gensolver::reset_rand(void) {
  srand(15);
  global_seed = 1;
  randn_internal(&global_seed, 1);
}
/* Produced by CVXGEN, 2015-09-15 18:52:16 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: testsolver.c. */
/* Description: Basic test harness for solver.c. */
Gensolver::Gensolver( int numberOfCases, double cost2, double cost1, double cost0, double PgenMax, double PgenMin ) {
  params.caseNumber = numberOfCases;
  params.c2[0] = cost2;
  params.c1[0] = cost1;
  params.c0[0] = cost0;
  params.rho[0] = 1.0;
  params.PgMin[0] = PgenMin;
  params.PgMax[0] = PgenMax;
for ( int i = 0; i <= 57; ++i ) {
  params.ones[i] = 0.0;
  params.Pg_N_init[i] = 0.0;
  params.Pg_N_avg[i] = 0.0;
  params.ug_N[i] = 0.0;
  params.Vg_N_avg[i] = 0.0;
  params.Thetag_N_avg[i] = 0.0;
  params.vg_N[i] = 0.0;
}
  global_seed = 1;
  Piterate = NULL;
  Thiterate = NULL;
  /*for ( int i = 0; i <= 57; ++i ) {
   Thiterate[i] = 0.0;
  }*/
  set_defaults();
  setup_indexing();
}
Gensolver::~Gensolver() {
}
#define NUMTESTS 0
void Gensolver::mainsolve(double gsRho, double Pgprev[], double Pgavrg[], double Pprice[], double Apriceavg[], double Aavg[], double Aprice[]) {
  int num_iters;
#if (NUMTESTS > 0)
  int i;
  double time;
  double time_per;
#endif
  set_defaults();
  setup_indexing();
  load_default_data(gsRho, Pgprev, Pgavrg, Pprice, Apriceavg, Aavg, Aprice);
  /* Solve problem instance for the record. */
  settings.verbose = 0;
  num_iters = solve();
#ifndef ZERO_LIBRARY_MODE
#if (NUMTESTS > 0)
  /* Now solve multiple problem instances for timing purposes. */
  settings.verbose = 0;
  tic();
  for (i = 0; i < NUMTESTS; i++) {
    solve();
  }
  time = tocq();
  printf("Timed %d solves over %.3f seconds.\n", NUMTESTS, time);
  time_per = time / NUMTESTS;
  if (time_per > 1) {
    printf("Actual time taken per solve: %.3g s.\n", time_per);
  } else if (time_per > 1e-3) {
    printf("Actual time taken per solve: %.3g ms.\n", 1e3*time_per);
  } else {
    printf("Actual time taken per solve: %.3g us.\n", 1e6*time_per);
  }
#endif
#endif
}
void Gensolver::load_default_data(double gsRho, double Pgenprev[], double Pgenavg[], double Powerprice[], double Angpriceavg[], double Angavg[], double Angprice[]) {
  params.rho[0] = gsRho;
for ( int i = 0; i <= params.caseNumber; ++i ) {
  params.ones[i] = 1.0;
  params.Pg_N_init[i] = Pgenprev[i];
  params.Pg_N_avg[i] = Pgenavg[i];
  params.ug_N[i] = Powerprice[i];
  params.Vg_N_avg[i] = Angpriceavg[i];
  params.Thetag_N_avg[i] = Angavg[i];
  params.vg_N[i] = Angprice[i];
}
  set_defaults();
  setup_indexing();
}

double Gensolver::getPSol(void) {
 Piterate = (vars.Pg);
 //*cout << "\nPiterate from the solver: " << *Piterate << endl;
 return *Piterate;
}

double Gensolver::getObj(void) {
 return (params.c2[0])*(*Piterate)*(*Piterate)+(params.c1[0])*(*Piterate)+(params.c0[0]);
}

double *Gensolver::getThetaPtr(void){
Thiterate = (vars.Thetag);
//for ( int i = 0; i < 401; ++i )
	//cout << "\nThiterate: " << *(vars.Thetag+i) << endl;
return Thiterate;
}

/*array<double, 58> Gensolver::getThetaSol(void) {
for ( int i = 0; i <= 57; ++i ) {
 Thiterate[i] = *((vars.Thetag)+i);
 //cout << "\nThiterate: " << *Thiterate[i] << endl;
}
 return Thiterate;
}*/
	
double Gensolver::getPMax() // start of getPMax function
{
	return params.PgMax[0];
} // end of getMax

double Gensolver::getPMin() // start of getPMin function
{
	return params.PgMin[0];
} // end of getPMin

double Gensolver::getQuadCoeff() // start of getQuadCoeff function
{
	return params.c2[0]; 
} // end of getQuadCoeff

double Gensolver::getLinCoeff() // start of getLinCoeff function
{
	return params.c1[0]; 
} // end of getLinCoeff

double Gensolver::getConstCoeff() // start of getConstCoeff function
{
	return params.c0[0]; 
} // end of getConstCoeff
/* Produced by CVXGEN, 2015-09-15 18:52:16 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: solver.c. */
/* Description: Main solver file. */
double Gensolver::eval_gap(void) {
  int i;
  double gap;
  gap = 0;
  for (i = 0; i < 2; i++)
    gap += work.z[i]*work.s[i];
  return gap;
}
void Gensolver::set_defaults(void) {
  settings.resid_tol = 1e-6;
  settings.eps = 1e-4;
  settings.max_iters = 25;
  settings.refine_steps = 1;
  settings.s_init = 1;
  settings.z_init = 1;
  settings.debug = 0;
  settings.verbose = 0;
  settings.verbose_refinement = 0;
  settings.better_start = 1;
  settings.kkt_reg = 1e-7;
}
void Gensolver::setup_pointers(void) {
  work.y = work.x + 59;
  work.s = work.x + 59;
  work.z = work.x + 61;
  vars.Pg = work.x + 0;
  vars.Thetag = work.x + 1;
}
void Gensolver::setup_indexing(void) {
  setup_pointers();
}
void Gensolver::set_start(void) {
  int i;
  for (i = 0; i < 59; i++)
    work.x[i] = 0;
  for (i = 0; i < 0; i++)
    work.y[i] = 0;
  for (i = 0; i < 2; i++)
    work.s[i] = (work.h[i] > 0) ? work.h[i] : settings.s_init;
  for (i = 0; i < 2; i++)
    work.z[i] = settings.z_init;
}
double Gensolver::eval_objv(void) {
  int i;
  double objv;
  /* Borrow space in work.rhs. */
  multbyP(work.rhs, work.x);
  objv = 0;
  for (i = 0; i < 59; i++)
    objv += work.x[i]*work.rhs[i];
  objv *= 0.5;
  for (i = 0; i < 59; i++)
    objv += work.q[i]*work.x[i];
  objv += params.c0[0]+work.frac_121674190848*(work.quad_112957349888[0]+work.quad_676450217984[0]);
  return objv;
}
void Gensolver::fillrhs_aff(void) {
  int i;
  double *r1, *r2, *r3, *r4;
  r1 = work.rhs;
  r2 = work.rhs + 59;
  r3 = work.rhs + 61;
  r4 = work.rhs + 63;
  /* r1 = -A^Ty - G^Tz - Px - q. */
  multbymAT(r1, work.y);
  multbymGT(work.buffer, work.z);
  for (i = 0; i < 59; i++)
    r1[i] += work.buffer[i];
  multbyP(work.buffer, work.x);
  for (i = 0; i < 59; i++)
    r1[i] -= work.buffer[i] + work.q[i];
  /* r2 = -z. */
  for (i = 0; i < 2; i++)
    r2[i] = -work.z[i];
  /* r3 = -Gx - s + h. */
  multbymG(r3, work.x);
  for (i = 0; i < 2; i++)
    r3[i] += -work.s[i] + work.h[i];
  /* r4 = -Ax + b. */
  multbymA(r4, work.x);
  for (i = 0; i < 0; i++)
    r4[i] += work.b[i];
}
void Gensolver::fillrhs_cc(void) {
  int i;
  double *r2;
  double *ds_aff, *dz_aff;
  double mu;
  double alpha;
  double sigma;
  double smu;
  double minval;
  r2 = work.rhs + 59;
  ds_aff = work.lhs_aff + 59;
  dz_aff = work.lhs_aff + 61;
  mu = 0;
  for (i = 0; i < 2; i++)
    mu += work.s[i]*work.z[i];
  /* Don't finish calculating mu quite yet. */
  /* Find min(min(ds./s), min(dz./z)). */
  minval = 0;
  for (i = 0; i < 2; i++)
    if (ds_aff[i] < minval*work.s[i])
      minval = ds_aff[i]/work.s[i];
  for (i = 0; i < 2; i++)
    if (dz_aff[i] < minval*work.z[i])
      minval = dz_aff[i]/work.z[i];
  /* Find alpha. */
  if (-1 < minval)
      alpha = 1;
  else
      alpha = -1/minval;
  sigma = 0;
  for (i = 0; i < 2; i++)
    sigma += (work.s[i] + alpha*ds_aff[i])*
      (work.z[i] + alpha*dz_aff[i]);
  sigma /= mu;
  sigma = sigma*sigma*sigma;
  /* Finish calculating mu now. */
  mu *= 0.5;
  smu = sigma*mu;
  /* Fill-in the rhs. */
  for (i = 0; i < 59; i++)
    work.rhs[i] = 0;
  for (i = 61; i < 63; i++)
    work.rhs[i] = 0;
  for (i = 0; i < 2; i++)
    r2[i] = work.s_inv[i]*(smu - ds_aff[i]*dz_aff[i]);
}
void Gensolver::refine(double *target, double *var) {
  int i, j;
  double *residual = work.buffer;
  double norm2;
  double *new_var = work.buffer2;
  for (j = 0; j < settings.refine_steps; j++) {
    norm2 = 0;
    matrix_multiply(residual, var);
    for (i = 0; i < 63; i++) {
      residual[i] = residual[i] - target[i];
      norm2 += residual[i]*residual[i];
    }
#ifndef ZERO_LIBRARY_MODE
    if (settings.verbose_refinement) {
      if (j == 0)
        printf("Initial residual before refinement has norm squared %.6g.\n", norm2);
      else
        printf("After refinement we get squared norm %.6g.\n", norm2);
    }
#endif
    /* Solve to find new_var = KKT \ (target - A*var). */
    ldl_solve(residual, new_var);
    /* Update var += new_var, or var += KKT \ (target - A*var). */
    for (i = 0; i < 63; i++) {
      var[i] -= new_var[i];
    }
  }
#ifndef ZERO_LIBRARY_MODE
  if (settings.verbose_refinement) {
    /* Check the residual once more, but only if we're reporting it, since */
    /* it's expensive. */
    norm2 = 0;
    matrix_multiply(residual, var);
    for (i = 0; i < 63; i++) {
      residual[i] = residual[i] - target[i];
      norm2 += residual[i]*residual[i];
    }
    if (j == 0)
      printf("Initial residual before refinement has norm squared %.6g.\n", norm2);
    else
      printf("After refinement we get squared norm %.6g.\n", norm2);
  }
#endif
}
double Gensolver::calc_ineq_resid_squared(void) {
  /* Calculates the norm ||-Gx - s + h||. */
  double norm2_squared;
  int i;
  /* Find -Gx. */
  multbymG(work.buffer, work.x);
  /* Add -s + h. */
  for (i = 0; i < 2; i++)
    work.buffer[i] += -work.s[i] + work.h[i];
  /* Now find the squared norm. */
  norm2_squared = 0;
  for (i = 0; i < 2; i++)
    norm2_squared += work.buffer[i]*work.buffer[i];
  return norm2_squared;
}
double Gensolver::calc_eq_resid_squared(void) {
  /* Calculates the norm ||-Ax + b||. */
  double norm2_squared;
  int i;
  /* Find -Ax. */
  multbymA(work.buffer, work.x);
  /* Add +b. */
  for (i = 0; i < 0; i++)
    work.buffer[i] += work.b[i];
  /* Now find the squared norm. */
  norm2_squared = 0;
  for (i = 0; i < 0; i++)
    norm2_squared += work.buffer[i]*work.buffer[i];
  return norm2_squared;
}
void Gensolver::better_start(void) {
  /* Calculates a better starting point, using a similar approach to CVXOPT. */
  /* Not yet speed optimized. */
  int i;
  double *x, *s, *z, *y;
  double alpha;
  work.block_33[0] = -1;
  /* Make sure sinvz is 1 to make hijacked KKT system ok. */
  for (i = 0; i < 2; i++)
    work.s_inv_z[i] = 1;
  fill_KKT();
  ldl_factor();
  fillrhs_start();
  /* Borrow work.lhs_aff for the solution. */
  ldl_solve(work.rhs, work.lhs_aff);
  /* Don't do any refinement for now. Precision doesn't matter too much. */
  x = work.lhs_aff;
  s = work.lhs_aff + 59;
  z = work.lhs_aff + 61;
  y = work.lhs_aff + 63;
  /* Just set x and y as is. */
  for (i = 0; i < 59; i++)
    work.x[i] = x[i];
  for (i = 0; i < 0; i++)
    work.y[i] = y[i];
  /* Now complete the initialization. Start with s. */
  /* Must have alpha > max(z). */
  alpha = -1e99;
  for (i = 0; i < 2; i++)
    if (alpha < z[i])
      alpha = z[i];
  if (alpha < 0) {
    for (i = 0; i < 2; i++)
      work.s[i] = -z[i];
  } else {
    alpha += 1;
    for (i = 0; i < 2; i++)
      work.s[i] = -z[i] + alpha;
  }
  /* Now initialize z. */
  /* Now must have alpha > max(-z). */
  alpha = -1e99;
  for (i = 0; i < 2; i++)
    if (alpha < -z[i])
      alpha = -z[i];
  if (alpha < 0) {
    for (i = 0; i < 2; i++)
      work.z[i] = z[i];
  } else {
    alpha += 1;
    for (i = 0; i < 2; i++)
      work.z[i] = z[i] + alpha;
  }
}
void Gensolver::fillrhs_start(void) {
  /* Fill rhs with (-q, 0, h, b). */
  int i;
  double *r1, *r2, *r3, *r4;
  r1 = work.rhs;
  r2 = work.rhs + 59;
  r3 = work.rhs + 61;
  r4 = work.rhs + 63;
  for (i = 0; i < 59; i++)
    r1[i] = -work.q[i];
  for (i = 0; i < 2; i++)
    r2[i] = 0;
  for (i = 0; i < 2; i++)
    r3[i] = work.h[i];
  for (i = 0; i < 0; i++)
    r4[i] = work.b[i];
}
long Gensolver::solve(void) {
  int i;
  int iter;
  double *dx, *ds, *dy, *dz;
  double minval;
  double alpha;
  work.converged = 0;
  setup_pointers();
  pre_ops();
#ifndef ZERO_LIBRARY_MODE
  if (settings.verbose)
    printf("iter     objv        gap       |Ax-b|    |Gx+s-h|    step\n");
#endif
  fillq();
  fillh();
  fillb();
  if (settings.better_start)
    better_start();
  else
    set_start();
  for (iter = 0; iter < settings.max_iters; iter++) {
    for (i = 0; i < 2; i++) {
      work.s_inv[i] = 1.0 / work.s[i];
      work.s_inv_z[i] = work.s_inv[i]*work.z[i];
    }
    work.block_33[0] = 0;
    fill_KKT();
    ldl_factor();
    /* Affine scaling directions. */
    fillrhs_aff();
    ldl_solve(work.rhs, work.lhs_aff);
    refine(work.rhs, work.lhs_aff);
    /* Centering plus corrector directions. */
    fillrhs_cc();
    ldl_solve(work.rhs, work.lhs_cc);
    refine(work.rhs, work.lhs_cc);
    /* Add the two together and store in aff. */
    for (i = 0; i < 63; i++)
      work.lhs_aff[i] += work.lhs_cc[i];
    /* Rename aff to reflect its new meaning. */
    dx = work.lhs_aff;
    ds = work.lhs_aff + 59;
    dz = work.lhs_aff + 61;
    dy = work.lhs_aff + 63;
    /* Find min(min(ds./s), min(dz./z)). */
    minval = 0;
    for (i = 0; i < 2; i++)
      if (ds[i] < minval*work.s[i])
        minval = ds[i]/work.s[i];
    for (i = 0; i < 2; i++)
      if (dz[i] < minval*work.z[i])
        minval = dz[i]/work.z[i];
    /* Find alpha. */
    if (-0.99 < minval)
      alpha = 1;
    else
      alpha = -0.99/minval;
    /* Update the primal and dual variables. */
    for (i = 0; i < 59; i++)
      work.x[i] += alpha*dx[i];
    for (i = 0; i < 2; i++)
      work.s[i] += alpha*ds[i];
    for (i = 0; i < 2; i++)
      work.z[i] += alpha*dz[i];
    for (i = 0; i < 0; i++)
      work.y[i] += alpha*dy[i];
    work.gap = eval_gap();
    work.eq_resid_squared = calc_eq_resid_squared();
    work.ineq_resid_squared = calc_ineq_resid_squared();
#ifndef ZERO_LIBRARY_MODE
    if (settings.verbose) {
      work.optval = eval_objv();
      printf("%3d   %10.3e  %9.2e  %9.2e  %9.2e  % 6.4f\n",
          iter+1, work.optval, work.gap, sqrt(work.eq_resid_squared),
          sqrt(work.ineq_resid_squared), alpha);
    }
#endif
    /* Test termination conditions. Requires optimality, and satisfied */
    /* constraints. */
    if (   (work.gap < settings.eps)
        && (work.eq_resid_squared <= settings.resid_tol*settings.resid_tol)
        && (work.ineq_resid_squared <= settings.resid_tol*settings.resid_tol)
       ) {
      work.converged = 1;
      work.optval = eval_objv();
      return iter+1;
    }
  }
  return iter;
}
/* Produced by CVXGEN, 2015-09-15 18:52:15 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: matrix_support.c. */
/* Description: Support functions for matrix multiplication and vector filling. */
void Gensolver::multbymA(double *lhs, double *rhs) {
}
void Gensolver::multbymAT(double *lhs, double *rhs) {
  lhs[0] = 0;
  lhs[1] = 0;
  lhs[2] = 0;
  lhs[3] = 0;
  lhs[4] = 0;
  lhs[5] = 0;
  lhs[6] = 0;
  lhs[7] = 0;
  lhs[8] = 0;
  lhs[9] = 0;
  lhs[10] = 0;
  lhs[11] = 0;
  lhs[12] = 0;
  lhs[13] = 0;
  lhs[14] = 0;
  lhs[15] = 0;
  lhs[16] = 0;
  lhs[17] = 0;
  lhs[18] = 0;
  lhs[19] = 0;
  lhs[20] = 0;
  lhs[21] = 0;
  lhs[22] = 0;
  lhs[23] = 0;
  lhs[24] = 0;
  lhs[25] = 0;
  lhs[26] = 0;
  lhs[27] = 0;
  lhs[28] = 0;
  lhs[29] = 0;
  lhs[30] = 0;
  lhs[31] = 0;
  lhs[32] = 0;
  lhs[33] = 0;
  lhs[34] = 0;
  lhs[35] = 0;
  lhs[36] = 0;
  lhs[37] = 0;
  lhs[38] = 0;
  lhs[39] = 0;
  lhs[40] = 0;
  lhs[41] = 0;
  lhs[42] = 0;
  lhs[43] = 0;
  lhs[44] = 0;
  lhs[45] = 0;
  lhs[46] = 0;
  lhs[47] = 0;
  lhs[48] = 0;
  lhs[49] = 0;
  lhs[50] = 0;
  lhs[51] = 0;
  lhs[52] = 0;
  lhs[53] = 0;
  lhs[54] = 0;
  lhs[55] = 0;
  lhs[56] = 0;
  lhs[57] = 0;
  lhs[58] = 0;
}
void Gensolver::multbymG(double *lhs, double *rhs) {
  lhs[0] = -rhs[0]*(-1);
  lhs[1] = -rhs[0]*(1);
}
void Gensolver::multbymGT(double *lhs, double *rhs) {
  lhs[0] = -rhs[0]*(-1)-rhs[1]*(1);
  lhs[1] = 0;
  lhs[2] = 0;
  lhs[3] = 0;
  lhs[4] = 0;
  lhs[5] = 0;
  lhs[6] = 0;
  lhs[7] = 0;
  lhs[8] = 0;
  lhs[9] = 0;
  lhs[10] = 0;
  lhs[11] = 0;
  lhs[12] = 0;
  lhs[13] = 0;
  lhs[14] = 0;
  lhs[15] = 0;
  lhs[16] = 0;
  lhs[17] = 0;
  lhs[18] = 0;
  lhs[19] = 0;
  lhs[20] = 0;
  lhs[21] = 0;
  lhs[22] = 0;
  lhs[23] = 0;
  lhs[24] = 0;
  lhs[25] = 0;
  lhs[26] = 0;
  lhs[27] = 0;
  lhs[28] = 0;
  lhs[29] = 0;
  lhs[30] = 0;
  lhs[31] = 0;
  lhs[32] = 0;
  lhs[33] = 0;
  lhs[34] = 0;
  lhs[35] = 0;
  lhs[36] = 0;
  lhs[37] = 0;
  lhs[38] = 0;
  lhs[39] = 0;
  lhs[40] = 0;
  lhs[41] = 0;
  lhs[42] = 0;
  lhs[43] = 0;
  lhs[44] = 0;
  lhs[45] = 0;
  lhs[46] = 0;
  lhs[47] = 0;
  lhs[48] = 0;
  lhs[49] = 0;
  lhs[50] = 0;
  lhs[51] = 0;
  lhs[52] = 0;
  lhs[53] = 0;
  lhs[54] = 0;
  lhs[55] = 0;
  lhs[56] = 0;
  lhs[57] = 0;
  lhs[58] = 0;
}
void Gensolver::multbyP(double *lhs, double *rhs) {
  /* TODO use the fact that P is symmetric? */
  /* TODO check doubling / half factor etc. */
  lhs[0] = rhs[0]*(2*(params.c2[0]+work.frac_121674190848*work.quad_839165739008[0]));
  lhs[1] = rhs[1]*(2*work.frac_121674190848);
  lhs[2] = rhs[2]*(2*work.frac_121674190848);
  lhs[3] = rhs[3]*(2*work.frac_121674190848);
  lhs[4] = rhs[4]*(2*work.frac_121674190848);
  lhs[5] = rhs[5]*(2*work.frac_121674190848);
  lhs[6] = rhs[6]*(2*work.frac_121674190848);
  lhs[7] = rhs[7]*(2*work.frac_121674190848);
  lhs[8] = rhs[8]*(2*work.frac_121674190848);
  lhs[9] = rhs[9]*(2*work.frac_121674190848);
  lhs[10] = rhs[10]*(2*work.frac_121674190848);
  lhs[11] = rhs[11]*(2*work.frac_121674190848);
  lhs[12] = rhs[12]*(2*work.frac_121674190848);
  lhs[13] = rhs[13]*(2*work.frac_121674190848);
  lhs[14] = rhs[14]*(2*work.frac_121674190848);
  lhs[15] = rhs[15]*(2*work.frac_121674190848);
  lhs[16] = rhs[16]*(2*work.frac_121674190848);
  lhs[17] = rhs[17]*(2*work.frac_121674190848);
  lhs[18] = rhs[18]*(2*work.frac_121674190848);
  lhs[19] = rhs[19]*(2*work.frac_121674190848);
  lhs[20] = rhs[20]*(2*work.frac_121674190848);
  lhs[21] = rhs[21]*(2*work.frac_121674190848);
  lhs[22] = rhs[22]*(2*work.frac_121674190848);
  lhs[23] = rhs[23]*(2*work.frac_121674190848);
  lhs[24] = rhs[24]*(2*work.frac_121674190848);
  lhs[25] = rhs[25]*(2*work.frac_121674190848);
  lhs[26] = rhs[26]*(2*work.frac_121674190848);
  lhs[27] = rhs[27]*(2*work.frac_121674190848);
  lhs[28] = rhs[28]*(2*work.frac_121674190848);
  lhs[29] = rhs[29]*(2*work.frac_121674190848);
  lhs[30] = rhs[30]*(2*work.frac_121674190848);
  lhs[31] = rhs[31]*(2*work.frac_121674190848);
  lhs[32] = rhs[32]*(2*work.frac_121674190848);
  lhs[33] = rhs[33]*(2*work.frac_121674190848);
  lhs[34] = rhs[34]*(2*work.frac_121674190848);
  lhs[35] = rhs[35]*(2*work.frac_121674190848);
  lhs[36] = rhs[36]*(2*work.frac_121674190848);
  lhs[37] = rhs[37]*(2*work.frac_121674190848);
  lhs[38] = rhs[38]*(2*work.frac_121674190848);
  lhs[39] = rhs[39]*(2*work.frac_121674190848);
  lhs[40] = rhs[40]*(2*work.frac_121674190848);
  lhs[41] = rhs[41]*(2*work.frac_121674190848);
  lhs[42] = rhs[42]*(2*work.frac_121674190848);
  lhs[43] = rhs[43]*(2*work.frac_121674190848);
  lhs[44] = rhs[44]*(2*work.frac_121674190848);
  lhs[45] = rhs[45]*(2*work.frac_121674190848);
  lhs[46] = rhs[46]*(2*work.frac_121674190848);
  lhs[47] = rhs[47]*(2*work.frac_121674190848);
  lhs[48] = rhs[48]*(2*work.frac_121674190848);
  lhs[49] = rhs[49]*(2*work.frac_121674190848);
  lhs[50] = rhs[50]*(2*work.frac_121674190848);
  lhs[51] = rhs[51]*(2*work.frac_121674190848);
  lhs[52] = rhs[52]*(2*work.frac_121674190848);
  lhs[53] = rhs[53]*(2*work.frac_121674190848);
  lhs[54] = rhs[54]*(2*work.frac_121674190848);
  lhs[55] = rhs[55]*(2*work.frac_121674190848);
  lhs[56] = rhs[56]*(2*work.frac_121674190848);
  lhs[57] = rhs[57]*(2*work.frac_121674190848);
  lhs[58] = rhs[58]*(2*work.frac_121674190848);
}
void Gensolver::fillq(void) {
  work.q[0] = params.c1[0]+2*work.frac_121674190848*((-params.Pg_N_init[0]+params.Pg_N_avg[0]+params.ug_N[0])*params.ones[0]+(-params.Pg_N_init[1]+params.Pg_N_avg[1]+params.ug_N[1])*params.ones[1]+(-params.Pg_N_init[2]+params.Pg_N_avg[2]+params.ug_N[2])*params.ones[2]+(-params.Pg_N_init[3]+params.Pg_N_avg[3]+params.ug_N[3])*params.ones[3]+(-params.Pg_N_init[4]+params.Pg_N_avg[4]+params.ug_N[4])*params.ones[4]+(-params.Pg_N_init[5]+params.Pg_N_avg[5]+params.ug_N[5])*params.ones[5]+(-params.Pg_N_init[6]+params.Pg_N_avg[6]+params.ug_N[6])*params.ones[6]+(-params.Pg_N_init[7]+params.Pg_N_avg[7]+params.ug_N[7])*params.ones[7]+(-params.Pg_N_init[8]+params.Pg_N_avg[8]+params.ug_N[8])*params.ones[8]+(-params.Pg_N_init[9]+params.Pg_N_avg[9]+params.ug_N[9])*params.ones[9]+(-params.Pg_N_init[10]+params.Pg_N_avg[10]+params.ug_N[10])*params.ones[10]+(-params.Pg_N_init[11]+params.Pg_N_avg[11]+params.ug_N[11])*params.ones[11]+(-params.Pg_N_init[12]+params.Pg_N_avg[12]+params.ug_N[12])*params.ones[12]+(-params.Pg_N_init[13]+params.Pg_N_avg[13]+params.ug_N[13])*params.ones[13]+(-params.Pg_N_init[14]+params.Pg_N_avg[14]+params.ug_N[14])*params.ones[14]+(-params.Pg_N_init[15]+params.Pg_N_avg[15]+params.ug_N[15])*params.ones[15]+(-params.Pg_N_init[16]+params.Pg_N_avg[16]+params.ug_N[16])*params.ones[16]+(-params.Pg_N_init[17]+params.Pg_N_avg[17]+params.ug_N[17])*params.ones[17]+(-params.Pg_N_init[18]+params.Pg_N_avg[18]+params.ug_N[18])*params.ones[18]+(-params.Pg_N_init[19]+params.Pg_N_avg[19]+params.ug_N[19])*params.ones[19]+(-params.Pg_N_init[20]+params.Pg_N_avg[20]+params.ug_N[20])*params.ones[20]+(-params.Pg_N_init[21]+params.Pg_N_avg[21]+params.ug_N[21])*params.ones[21]+(-params.Pg_N_init[22]+params.Pg_N_avg[22]+params.ug_N[22])*params.ones[22]+(-params.Pg_N_init[23]+params.Pg_N_avg[23]+params.ug_N[23])*params.ones[23]+(-params.Pg_N_init[24]+params.Pg_N_avg[24]+params.ug_N[24])*params.ones[24]+(-params.Pg_N_init[25]+params.Pg_N_avg[25]+params.ug_N[25])*params.ones[25]+(-params.Pg_N_init[26]+params.Pg_N_avg[26]+params.ug_N[26])*params.ones[26]+(-params.Pg_N_init[27]+params.Pg_N_avg[27]+params.ug_N[27])*params.ones[27]+(-params.Pg_N_init[28]+params.Pg_N_avg[28]+params.ug_N[28])*params.ones[28]+(-params.Pg_N_init[29]+params.Pg_N_avg[29]+params.ug_N[29])*params.ones[29]+(-params.Pg_N_init[30]+params.Pg_N_avg[30]+params.ug_N[30])*params.ones[30]+(-params.Pg_N_init[31]+params.Pg_N_avg[31]+params.ug_N[31])*params.ones[31]+(-params.Pg_N_init[32]+params.Pg_N_avg[32]+params.ug_N[32])*params.ones[32]+(-params.Pg_N_init[33]+params.Pg_N_avg[33]+params.ug_N[33])*params.ones[33]+(-params.Pg_N_init[34]+params.Pg_N_avg[34]+params.ug_N[34])*params.ones[34]+(-params.Pg_N_init[35]+params.Pg_N_avg[35]+params.ug_N[35])*params.ones[35]+(-params.Pg_N_init[36]+params.Pg_N_avg[36]+params.ug_N[36])*params.ones[36]+(-params.Pg_N_init[37]+params.Pg_N_avg[37]+params.ug_N[37])*params.ones[37]+(-params.Pg_N_init[38]+params.Pg_N_avg[38]+params.ug_N[38])*params.ones[38]+(-params.Pg_N_init[39]+params.Pg_N_avg[39]+params.ug_N[39])*params.ones[39]+(-params.Pg_N_init[40]+params.Pg_N_avg[40]+params.ug_N[40])*params.ones[40]+(-params.Pg_N_init[41]+params.Pg_N_avg[41]+params.ug_N[41])*params.ones[41]+(-params.Pg_N_init[42]+params.Pg_N_avg[42]+params.ug_N[42])*params.ones[42]+(-params.Pg_N_init[43]+params.Pg_N_avg[43]+params.ug_N[43])*params.ones[43]+(-params.Pg_N_init[44]+params.Pg_N_avg[44]+params.ug_N[44])*params.ones[44]+(-params.Pg_N_init[45]+params.Pg_N_avg[45]+params.ug_N[45])*params.ones[45]+(-params.Pg_N_init[46]+params.Pg_N_avg[46]+params.ug_N[46])*params.ones[46]+(-params.Pg_N_init[47]+params.Pg_N_avg[47]+params.ug_N[47])*params.ones[47]+(-params.Pg_N_init[48]+params.Pg_N_avg[48]+params.ug_N[48])*params.ones[48]+(-params.Pg_N_init[49]+params.Pg_N_avg[49]+params.ug_N[49])*params.ones[49]+(-params.Pg_N_init[50]+params.Pg_N_avg[50]+params.ug_N[50])*params.ones[50]+(-params.Pg_N_init[51]+params.Pg_N_avg[51]+params.ug_N[51])*params.ones[51]+(-params.Pg_N_init[52]+params.Pg_N_avg[52]+params.ug_N[52])*params.ones[52]+(-params.Pg_N_init[53]+params.Pg_N_avg[53]+params.ug_N[53])*params.ones[53]+(-params.Pg_N_init[54]+params.Pg_N_avg[54]+params.ug_N[54])*params.ones[54]+(-params.Pg_N_init[55]+params.Pg_N_avg[55]+params.ug_N[55])*params.ones[55]+(-params.Pg_N_init[56]+params.Pg_N_avg[56]+params.ug_N[56])*params.ones[56]+(-params.Pg_N_init[57]+params.Pg_N_avg[57]+params.ug_N[57])*params.ones[57]);
  work.q[1] = 2*work.frac_121674190848*(-params.Vg_N_avg[0]-params.Thetag_N_avg[0]+params.vg_N[0]);
  work.q[2] = 2*work.frac_121674190848*(-params.Vg_N_avg[1]-params.Thetag_N_avg[1]+params.vg_N[1]);
  work.q[3] = 2*work.frac_121674190848*(-params.Vg_N_avg[2]-params.Thetag_N_avg[2]+params.vg_N[2]);
  work.q[4] = 2*work.frac_121674190848*(-params.Vg_N_avg[3]-params.Thetag_N_avg[3]+params.vg_N[3]);
  work.q[5] = 2*work.frac_121674190848*(-params.Vg_N_avg[4]-params.Thetag_N_avg[4]+params.vg_N[4]);
  work.q[6] = 2*work.frac_121674190848*(-params.Vg_N_avg[5]-params.Thetag_N_avg[5]+params.vg_N[5]);
  work.q[7] = 2*work.frac_121674190848*(-params.Vg_N_avg[6]-params.Thetag_N_avg[6]+params.vg_N[6]);
  work.q[8] = 2*work.frac_121674190848*(-params.Vg_N_avg[7]-params.Thetag_N_avg[7]+params.vg_N[7]);
  work.q[9] = 2*work.frac_121674190848*(-params.Vg_N_avg[8]-params.Thetag_N_avg[8]+params.vg_N[8]);
  work.q[10] = 2*work.frac_121674190848*(-params.Vg_N_avg[9]-params.Thetag_N_avg[9]+params.vg_N[9]);
  work.q[11] = 2*work.frac_121674190848*(-params.Vg_N_avg[10]-params.Thetag_N_avg[10]+params.vg_N[10]);
  work.q[12] = 2*work.frac_121674190848*(-params.Vg_N_avg[11]-params.Thetag_N_avg[11]+params.vg_N[11]);
  work.q[13] = 2*work.frac_121674190848*(-params.Vg_N_avg[12]-params.Thetag_N_avg[12]+params.vg_N[12]);
  work.q[14] = 2*work.frac_121674190848*(-params.Vg_N_avg[13]-params.Thetag_N_avg[13]+params.vg_N[13]);
  work.q[15] = 2*work.frac_121674190848*(-params.Vg_N_avg[14]-params.Thetag_N_avg[14]+params.vg_N[14]);
  work.q[16] = 2*work.frac_121674190848*(-params.Vg_N_avg[15]-params.Thetag_N_avg[15]+params.vg_N[15]);
  work.q[17] = 2*work.frac_121674190848*(-params.Vg_N_avg[16]-params.Thetag_N_avg[16]+params.vg_N[16]);
  work.q[18] = 2*work.frac_121674190848*(-params.Vg_N_avg[17]-params.Thetag_N_avg[17]+params.vg_N[17]);
  work.q[19] = 2*work.frac_121674190848*(-params.Vg_N_avg[18]-params.Thetag_N_avg[18]+params.vg_N[18]);
  work.q[20] = 2*work.frac_121674190848*(-params.Vg_N_avg[19]-params.Thetag_N_avg[19]+params.vg_N[19]);
  work.q[21] = 2*work.frac_121674190848*(-params.Vg_N_avg[20]-params.Thetag_N_avg[20]+params.vg_N[20]);
  work.q[22] = 2*work.frac_121674190848*(-params.Vg_N_avg[21]-params.Thetag_N_avg[21]+params.vg_N[21]);
  work.q[23] = 2*work.frac_121674190848*(-params.Vg_N_avg[22]-params.Thetag_N_avg[22]+params.vg_N[22]);
  work.q[24] = 2*work.frac_121674190848*(-params.Vg_N_avg[23]-params.Thetag_N_avg[23]+params.vg_N[23]);
  work.q[25] = 2*work.frac_121674190848*(-params.Vg_N_avg[24]-params.Thetag_N_avg[24]+params.vg_N[24]);
  work.q[26] = 2*work.frac_121674190848*(-params.Vg_N_avg[25]-params.Thetag_N_avg[25]+params.vg_N[25]);
  work.q[27] = 2*work.frac_121674190848*(-params.Vg_N_avg[26]-params.Thetag_N_avg[26]+params.vg_N[26]);
  work.q[28] = 2*work.frac_121674190848*(-params.Vg_N_avg[27]-params.Thetag_N_avg[27]+params.vg_N[27]);
  work.q[29] = 2*work.frac_121674190848*(-params.Vg_N_avg[28]-params.Thetag_N_avg[28]+params.vg_N[28]);
  work.q[30] = 2*work.frac_121674190848*(-params.Vg_N_avg[29]-params.Thetag_N_avg[29]+params.vg_N[29]);
  work.q[31] = 2*work.frac_121674190848*(-params.Vg_N_avg[30]-params.Thetag_N_avg[30]+params.vg_N[30]);
  work.q[32] = 2*work.frac_121674190848*(-params.Vg_N_avg[31]-params.Thetag_N_avg[31]+params.vg_N[31]);
  work.q[33] = 2*work.frac_121674190848*(-params.Vg_N_avg[32]-params.Thetag_N_avg[32]+params.vg_N[32]);
  work.q[34] = 2*work.frac_121674190848*(-params.Vg_N_avg[33]-params.Thetag_N_avg[33]+params.vg_N[33]);
  work.q[35] = 2*work.frac_121674190848*(-params.Vg_N_avg[34]-params.Thetag_N_avg[34]+params.vg_N[34]);
  work.q[36] = 2*work.frac_121674190848*(-params.Vg_N_avg[35]-params.Thetag_N_avg[35]+params.vg_N[35]);
  work.q[37] = 2*work.frac_121674190848*(-params.Vg_N_avg[36]-params.Thetag_N_avg[36]+params.vg_N[36]);
  work.q[38] = 2*work.frac_121674190848*(-params.Vg_N_avg[37]-params.Thetag_N_avg[37]+params.vg_N[37]);
  work.q[39] = 2*work.frac_121674190848*(-params.Vg_N_avg[38]-params.Thetag_N_avg[38]+params.vg_N[38]);
  work.q[40] = 2*work.frac_121674190848*(-params.Vg_N_avg[39]-params.Thetag_N_avg[39]+params.vg_N[39]);
  work.q[41] = 2*work.frac_121674190848*(-params.Vg_N_avg[40]-params.Thetag_N_avg[40]+params.vg_N[40]);
  work.q[42] = 2*work.frac_121674190848*(-params.Vg_N_avg[41]-params.Thetag_N_avg[41]+params.vg_N[41]);
  work.q[43] = 2*work.frac_121674190848*(-params.Vg_N_avg[42]-params.Thetag_N_avg[42]+params.vg_N[42]);
  work.q[44] = 2*work.frac_121674190848*(-params.Vg_N_avg[43]-params.Thetag_N_avg[43]+params.vg_N[43]);
  work.q[45] = 2*work.frac_121674190848*(-params.Vg_N_avg[44]-params.Thetag_N_avg[44]+params.vg_N[44]);
  work.q[46] = 2*work.frac_121674190848*(-params.Vg_N_avg[45]-params.Thetag_N_avg[45]+params.vg_N[45]);
  work.q[47] = 2*work.frac_121674190848*(-params.Vg_N_avg[46]-params.Thetag_N_avg[46]+params.vg_N[46]);
  work.q[48] = 2*work.frac_121674190848*(-params.Vg_N_avg[47]-params.Thetag_N_avg[47]+params.vg_N[47]);
  work.q[49] = 2*work.frac_121674190848*(-params.Vg_N_avg[48]-params.Thetag_N_avg[48]+params.vg_N[48]);
  work.q[50] = 2*work.frac_121674190848*(-params.Vg_N_avg[49]-params.Thetag_N_avg[49]+params.vg_N[49]);
  work.q[51] = 2*work.frac_121674190848*(-params.Vg_N_avg[50]-params.Thetag_N_avg[50]+params.vg_N[50]);
  work.q[52] = 2*work.frac_121674190848*(-params.Vg_N_avg[51]-params.Thetag_N_avg[51]+params.vg_N[51]);
  work.q[53] = 2*work.frac_121674190848*(-params.Vg_N_avg[52]-params.Thetag_N_avg[52]+params.vg_N[52]);
  work.q[54] = 2*work.frac_121674190848*(-params.Vg_N_avg[53]-params.Thetag_N_avg[53]+params.vg_N[53]);
  work.q[55] = 2*work.frac_121674190848*(-params.Vg_N_avg[54]-params.Thetag_N_avg[54]+params.vg_N[54]);
  work.q[56] = 2*work.frac_121674190848*(-params.Vg_N_avg[55]-params.Thetag_N_avg[55]+params.vg_N[55]);
  work.q[57] = 2*work.frac_121674190848*(-params.Vg_N_avg[56]-params.Thetag_N_avg[56]+params.vg_N[56]);
  work.q[58] = 2*work.frac_121674190848*(-params.Vg_N_avg[57]-params.Thetag_N_avg[57]+params.vg_N[57]);
}
void Gensolver::fillh(void) {
  work.h[0] = -params.PgMin[0];
  work.h[1] = params.PgMax[0];
}
void Gensolver::fillb(void) {
}
void Gensolver::pre_ops(void) {
  work.frac_121674190848 = params.rho[0];
  work.frac_121674190848 /= 2;
  work.quad_839165739008[0] = params.ones[0]*params.ones[0]+params.ones[1]*params.ones[1]+params.ones[2]*params.ones[2]+params.ones[3]*params.ones[3]+params.ones[4]*params.ones[4]+params.ones[5]*params.ones[5]+params.ones[6]*params.ones[6]+params.ones[7]*params.ones[7]+params.ones[8]*params.ones[8]+params.ones[9]*params.ones[9]+params.ones[10]*params.ones[10]+params.ones[11]*params.ones[11]+params.ones[12]*params.ones[12]+params.ones[13]*params.ones[13]+params.ones[14]*params.ones[14]+params.ones[15]*params.ones[15]+params.ones[16]*params.ones[16]+params.ones[17]*params.ones[17]+params.ones[18]*params.ones[18]+params.ones[19]*params.ones[19]+params.ones[20]*params.ones[20]+params.ones[21]*params.ones[21]+params.ones[22]*params.ones[22]+params.ones[23]*params.ones[23]+params.ones[24]*params.ones[24]+params.ones[25]*params.ones[25]+params.ones[26]*params.ones[26]+params.ones[27]*params.ones[27]+params.ones[28]*params.ones[28]+params.ones[29]*params.ones[29]+params.ones[30]*params.ones[30]+params.ones[31]*params.ones[31]+params.ones[32]*params.ones[32]+params.ones[33]*params.ones[33]+params.ones[34]*params.ones[34]+params.ones[35]*params.ones[35]+params.ones[36]*params.ones[36]+params.ones[37]*params.ones[37]+params.ones[38]*params.ones[38]+params.ones[39]*params.ones[39]+params.ones[40]*params.ones[40]+params.ones[41]*params.ones[41]+params.ones[42]*params.ones[42]+params.ones[43]*params.ones[43]+params.ones[44]*params.ones[44]+params.ones[45]*params.ones[45]+params.ones[46]*params.ones[46]+params.ones[47]*params.ones[47]+params.ones[48]*params.ones[48]+params.ones[49]*params.ones[49]+params.ones[50]*params.ones[50]+params.ones[51]*params.ones[51]+params.ones[52]*params.ones[52]+params.ones[53]*params.ones[53]+params.ones[54]*params.ones[54]+params.ones[55]*params.ones[55]+params.ones[56]*params.ones[56]+params.ones[57]*params.ones[57];
  work.quad_112957349888[0] = ((-params.Pg_N_init[0]+params.Pg_N_avg[0]+params.ug_N[0])*(-params.Pg_N_init[0]+params.Pg_N_avg[0]+params.ug_N[0])+(-params.Pg_N_init[1]+params.Pg_N_avg[1]+params.ug_N[1])*(-params.Pg_N_init[1]+params.Pg_N_avg[1]+params.ug_N[1])+(-params.Pg_N_init[2]+params.Pg_N_avg[2]+params.ug_N[2])*(-params.Pg_N_init[2]+params.Pg_N_avg[2]+params.ug_N[2])+(-params.Pg_N_init[3]+params.Pg_N_avg[3]+params.ug_N[3])*(-params.Pg_N_init[3]+params.Pg_N_avg[3]+params.ug_N[3])+(-params.Pg_N_init[4]+params.Pg_N_avg[4]+params.ug_N[4])*(-params.Pg_N_init[4]+params.Pg_N_avg[4]+params.ug_N[4])+(-params.Pg_N_init[5]+params.Pg_N_avg[5]+params.ug_N[5])*(-params.Pg_N_init[5]+params.Pg_N_avg[5]+params.ug_N[5])+(-params.Pg_N_init[6]+params.Pg_N_avg[6]+params.ug_N[6])*(-params.Pg_N_init[6]+params.Pg_N_avg[6]+params.ug_N[6])+(-params.Pg_N_init[7]+params.Pg_N_avg[7]+params.ug_N[7])*(-params.Pg_N_init[7]+params.Pg_N_avg[7]+params.ug_N[7])+(-params.Pg_N_init[8]+params.Pg_N_avg[8]+params.ug_N[8])*(-params.Pg_N_init[8]+params.Pg_N_avg[8]+params.ug_N[8])+(-params.Pg_N_init[9]+params.Pg_N_avg[9]+params.ug_N[9])*(-params.Pg_N_init[9]+params.Pg_N_avg[9]+params.ug_N[9])+(-params.Pg_N_init[10]+params.Pg_N_avg[10]+params.ug_N[10])*(-params.Pg_N_init[10]+params.Pg_N_avg[10]+params.ug_N[10])+(-params.Pg_N_init[11]+params.Pg_N_avg[11]+params.ug_N[11])*(-params.Pg_N_init[11]+params.Pg_N_avg[11]+params.ug_N[11])+(-params.Pg_N_init[12]+params.Pg_N_avg[12]+params.ug_N[12])*(-params.Pg_N_init[12]+params.Pg_N_avg[12]+params.ug_N[12])+(-params.Pg_N_init[13]+params.Pg_N_avg[13]+params.ug_N[13])*(-params.Pg_N_init[13]+params.Pg_N_avg[13]+params.ug_N[13])+(-params.Pg_N_init[14]+params.Pg_N_avg[14]+params.ug_N[14])*(-params.Pg_N_init[14]+params.Pg_N_avg[14]+params.ug_N[14])+(-params.Pg_N_init[15]+params.Pg_N_avg[15]+params.ug_N[15])*(-params.Pg_N_init[15]+params.Pg_N_avg[15]+params.ug_N[15])+(-params.Pg_N_init[16]+params.Pg_N_avg[16]+params.ug_N[16])*(-params.Pg_N_init[16]+params.Pg_N_avg[16]+params.ug_N[16])+(-params.Pg_N_init[17]+params.Pg_N_avg[17]+params.ug_N[17])*(-params.Pg_N_init[17]+params.Pg_N_avg[17]+params.ug_N[17])+(-params.Pg_N_init[18]+params.Pg_N_avg[18]+params.ug_N[18])*(-params.Pg_N_init[18]+params.Pg_N_avg[18]+params.ug_N[18])+(-params.Pg_N_init[19]+params.Pg_N_avg[19]+params.ug_N[19])*(-params.Pg_N_init[19]+params.Pg_N_avg[19]+params.ug_N[19])+(-params.Pg_N_init[20]+params.Pg_N_avg[20]+params.ug_N[20])*(-params.Pg_N_init[20]+params.Pg_N_avg[20]+params.ug_N[20])+(-params.Pg_N_init[21]+params.Pg_N_avg[21]+params.ug_N[21])*(-params.Pg_N_init[21]+params.Pg_N_avg[21]+params.ug_N[21])+(-params.Pg_N_init[22]+params.Pg_N_avg[22]+params.ug_N[22])*(-params.Pg_N_init[22]+params.Pg_N_avg[22]+params.ug_N[22])+(-params.Pg_N_init[23]+params.Pg_N_avg[23]+params.ug_N[23])*(-params.Pg_N_init[23]+params.Pg_N_avg[23]+params.ug_N[23])+(-params.Pg_N_init[24]+params.Pg_N_avg[24]+params.ug_N[24])*(-params.Pg_N_init[24]+params.Pg_N_avg[24]+params.ug_N[24])+(-params.Pg_N_init[25]+params.Pg_N_avg[25]+params.ug_N[25])*(-params.Pg_N_init[25]+params.Pg_N_avg[25]+params.ug_N[25])+(-params.Pg_N_init[26]+params.Pg_N_avg[26]+params.ug_N[26])*(-params.Pg_N_init[26]+params.Pg_N_avg[26]+params.ug_N[26])+(-params.Pg_N_init[27]+params.Pg_N_avg[27]+params.ug_N[27])*(-params.Pg_N_init[27]+params.Pg_N_avg[27]+params.ug_N[27])+(-params.Pg_N_init[28]+params.Pg_N_avg[28]+params.ug_N[28])*(-params.Pg_N_init[28]+params.Pg_N_avg[28]+params.ug_N[28])+(-params.Pg_N_init[29]+params.Pg_N_avg[29]+params.ug_N[29])*(-params.Pg_N_init[29]+params.Pg_N_avg[29]+params.ug_N[29])+(-params.Pg_N_init[30]+params.Pg_N_avg[30]+params.ug_N[30])*(-params.Pg_N_init[30]+params.Pg_N_avg[30]+params.ug_N[30])+(-params.Pg_N_init[31]+params.Pg_N_avg[31]+params.ug_N[31])*(-params.Pg_N_init[31]+params.Pg_N_avg[31]+params.ug_N[31])+(-params.Pg_N_init[32]+params.Pg_N_avg[32]+params.ug_N[32])*(-params.Pg_N_init[32]+params.Pg_N_avg[32]+params.ug_N[32])+(-params.Pg_N_init[33]+params.Pg_N_avg[33]+params.ug_N[33])*(-params.Pg_N_init[33]+params.Pg_N_avg[33]+params.ug_N[33])+(-params.Pg_N_init[34]+params.Pg_N_avg[34]+params.ug_N[34])*(-params.Pg_N_init[34]+params.Pg_N_avg[34]+params.ug_N[34])+(-params.Pg_N_init[35]+params.Pg_N_avg[35]+params.ug_N[35])*(-params.Pg_N_init[35]+params.Pg_N_avg[35]+params.ug_N[35])+(-params.Pg_N_init[36]+params.Pg_N_avg[36]+params.ug_N[36])*(-params.Pg_N_init[36]+params.Pg_N_avg[36]+params.ug_N[36])+(-params.Pg_N_init[37]+params.Pg_N_avg[37]+params.ug_N[37])*(-params.Pg_N_init[37]+params.Pg_N_avg[37]+params.ug_N[37])+(-params.Pg_N_init[38]+params.Pg_N_avg[38]+params.ug_N[38])*(-params.Pg_N_init[38]+params.Pg_N_avg[38]+params.ug_N[38])+(-params.Pg_N_init[39]+params.Pg_N_avg[39]+params.ug_N[39])*(-params.Pg_N_init[39]+params.Pg_N_avg[39]+params.ug_N[39])+(-params.Pg_N_init[40]+params.Pg_N_avg[40]+params.ug_N[40])*(-params.Pg_N_init[40]+params.Pg_N_avg[40]+params.ug_N[40])+(-params.Pg_N_init[41]+params.Pg_N_avg[41]+params.ug_N[41])*(-params.Pg_N_init[41]+params.Pg_N_avg[41]+params.ug_N[41])+(-params.Pg_N_init[42]+params.Pg_N_avg[42]+params.ug_N[42])*(-params.Pg_N_init[42]+params.Pg_N_avg[42]+params.ug_N[42])+(-params.Pg_N_init[43]+params.Pg_N_avg[43]+params.ug_N[43])*(-params.Pg_N_init[43]+params.Pg_N_avg[43]+params.ug_N[43])+(-params.Pg_N_init[44]+params.Pg_N_avg[44]+params.ug_N[44])*(-params.Pg_N_init[44]+params.Pg_N_avg[44]+params.ug_N[44])+(-params.Pg_N_init[45]+params.Pg_N_avg[45]+params.ug_N[45])*(-params.Pg_N_init[45]+params.Pg_N_avg[45]+params.ug_N[45])+(-params.Pg_N_init[46]+params.Pg_N_avg[46]+params.ug_N[46])*(-params.Pg_N_init[46]+params.Pg_N_avg[46]+params.ug_N[46])+(-params.Pg_N_init[47]+params.Pg_N_avg[47]+params.ug_N[47])*(-params.Pg_N_init[47]+params.Pg_N_avg[47]+params.ug_N[47])+(-params.Pg_N_init[48]+params.Pg_N_avg[48]+params.ug_N[48])*(-params.Pg_N_init[48]+params.Pg_N_avg[48]+params.ug_N[48])+(-params.Pg_N_init[49]+params.Pg_N_avg[49]+params.ug_N[49])*(-params.Pg_N_init[49]+params.Pg_N_avg[49]+params.ug_N[49])+(-params.Pg_N_init[50]+params.Pg_N_avg[50]+params.ug_N[50])*(-params.Pg_N_init[50]+params.Pg_N_avg[50]+params.ug_N[50])+(-params.Pg_N_init[51]+params.Pg_N_avg[51]+params.ug_N[51])*(-params.Pg_N_init[51]+params.Pg_N_avg[51]+params.ug_N[51])+(-params.Pg_N_init[52]+params.Pg_N_avg[52]+params.ug_N[52])*(-params.Pg_N_init[52]+params.Pg_N_avg[52]+params.ug_N[52])+(-params.Pg_N_init[53]+params.Pg_N_avg[53]+params.ug_N[53])*(-params.Pg_N_init[53]+params.Pg_N_avg[53]+params.ug_N[53])+(-params.Pg_N_init[54]+params.Pg_N_avg[54]+params.ug_N[54])*(-params.Pg_N_init[54]+params.Pg_N_avg[54]+params.ug_N[54])+(-params.Pg_N_init[55]+params.Pg_N_avg[55]+params.ug_N[55])*(-params.Pg_N_init[55]+params.Pg_N_avg[55]+params.ug_N[55])+(-params.Pg_N_init[56]+params.Pg_N_avg[56]+params.ug_N[56])*(-params.Pg_N_init[56]+params.Pg_N_avg[56]+params.ug_N[56])+(-params.Pg_N_init[57]+params.Pg_N_avg[57]+params.ug_N[57])*(-params.Pg_N_init[57]+params.Pg_N_avg[57]+params.ug_N[57]));
  work.quad_676450217984[0] = ((-params.Vg_N_avg[0]-params.Thetag_N_avg[0]+params.vg_N[0])*(-params.Vg_N_avg[0]-params.Thetag_N_avg[0]+params.vg_N[0])+(-params.Vg_N_avg[1]-params.Thetag_N_avg[1]+params.vg_N[1])*(-params.Vg_N_avg[1]-params.Thetag_N_avg[1]+params.vg_N[1])+(-params.Vg_N_avg[2]-params.Thetag_N_avg[2]+params.vg_N[2])*(-params.Vg_N_avg[2]-params.Thetag_N_avg[2]+params.vg_N[2])+(-params.Vg_N_avg[3]-params.Thetag_N_avg[3]+params.vg_N[3])*(-params.Vg_N_avg[3]-params.Thetag_N_avg[3]+params.vg_N[3])+(-params.Vg_N_avg[4]-params.Thetag_N_avg[4]+params.vg_N[4])*(-params.Vg_N_avg[4]-params.Thetag_N_avg[4]+params.vg_N[4])+(-params.Vg_N_avg[5]-params.Thetag_N_avg[5]+params.vg_N[5])*(-params.Vg_N_avg[5]-params.Thetag_N_avg[5]+params.vg_N[5])+(-params.Vg_N_avg[6]-params.Thetag_N_avg[6]+params.vg_N[6])*(-params.Vg_N_avg[6]-params.Thetag_N_avg[6]+params.vg_N[6])+(-params.Vg_N_avg[7]-params.Thetag_N_avg[7]+params.vg_N[7])*(-params.Vg_N_avg[7]-params.Thetag_N_avg[7]+params.vg_N[7])+(-params.Vg_N_avg[8]-params.Thetag_N_avg[8]+params.vg_N[8])*(-params.Vg_N_avg[8]-params.Thetag_N_avg[8]+params.vg_N[8])+(-params.Vg_N_avg[9]-params.Thetag_N_avg[9]+params.vg_N[9])*(-params.Vg_N_avg[9]-params.Thetag_N_avg[9]+params.vg_N[9])+(-params.Vg_N_avg[10]-params.Thetag_N_avg[10]+params.vg_N[10])*(-params.Vg_N_avg[10]-params.Thetag_N_avg[10]+params.vg_N[10])+(-params.Vg_N_avg[11]-params.Thetag_N_avg[11]+params.vg_N[11])*(-params.Vg_N_avg[11]-params.Thetag_N_avg[11]+params.vg_N[11])+(-params.Vg_N_avg[12]-params.Thetag_N_avg[12]+params.vg_N[12])*(-params.Vg_N_avg[12]-params.Thetag_N_avg[12]+params.vg_N[12])+(-params.Vg_N_avg[13]-params.Thetag_N_avg[13]+params.vg_N[13])*(-params.Vg_N_avg[13]-params.Thetag_N_avg[13]+params.vg_N[13])+(-params.Vg_N_avg[14]-params.Thetag_N_avg[14]+params.vg_N[14])*(-params.Vg_N_avg[14]-params.Thetag_N_avg[14]+params.vg_N[14])+(-params.Vg_N_avg[15]-params.Thetag_N_avg[15]+params.vg_N[15])*(-params.Vg_N_avg[15]-params.Thetag_N_avg[15]+params.vg_N[15])+(-params.Vg_N_avg[16]-params.Thetag_N_avg[16]+params.vg_N[16])*(-params.Vg_N_avg[16]-params.Thetag_N_avg[16]+params.vg_N[16])+(-params.Vg_N_avg[17]-params.Thetag_N_avg[17]+params.vg_N[17])*(-params.Vg_N_avg[17]-params.Thetag_N_avg[17]+params.vg_N[17])+(-params.Vg_N_avg[18]-params.Thetag_N_avg[18]+params.vg_N[18])*(-params.Vg_N_avg[18]-params.Thetag_N_avg[18]+params.vg_N[18])+(-params.Vg_N_avg[19]-params.Thetag_N_avg[19]+params.vg_N[19])*(-params.Vg_N_avg[19]-params.Thetag_N_avg[19]+params.vg_N[19])+(-params.Vg_N_avg[20]-params.Thetag_N_avg[20]+params.vg_N[20])*(-params.Vg_N_avg[20]-params.Thetag_N_avg[20]+params.vg_N[20])+(-params.Vg_N_avg[21]-params.Thetag_N_avg[21]+params.vg_N[21])*(-params.Vg_N_avg[21]-params.Thetag_N_avg[21]+params.vg_N[21])+(-params.Vg_N_avg[22]-params.Thetag_N_avg[22]+params.vg_N[22])*(-params.Vg_N_avg[22]-params.Thetag_N_avg[22]+params.vg_N[22])+(-params.Vg_N_avg[23]-params.Thetag_N_avg[23]+params.vg_N[23])*(-params.Vg_N_avg[23]-params.Thetag_N_avg[23]+params.vg_N[23])+(-params.Vg_N_avg[24]-params.Thetag_N_avg[24]+params.vg_N[24])*(-params.Vg_N_avg[24]-params.Thetag_N_avg[24]+params.vg_N[24])+(-params.Vg_N_avg[25]-params.Thetag_N_avg[25]+params.vg_N[25])*(-params.Vg_N_avg[25]-params.Thetag_N_avg[25]+params.vg_N[25])+(-params.Vg_N_avg[26]-params.Thetag_N_avg[26]+params.vg_N[26])*(-params.Vg_N_avg[26]-params.Thetag_N_avg[26]+params.vg_N[26])+(-params.Vg_N_avg[27]-params.Thetag_N_avg[27]+params.vg_N[27])*(-params.Vg_N_avg[27]-params.Thetag_N_avg[27]+params.vg_N[27])+(-params.Vg_N_avg[28]-params.Thetag_N_avg[28]+params.vg_N[28])*(-params.Vg_N_avg[28]-params.Thetag_N_avg[28]+params.vg_N[28])+(-params.Vg_N_avg[29]-params.Thetag_N_avg[29]+params.vg_N[29])*(-params.Vg_N_avg[29]-params.Thetag_N_avg[29]+params.vg_N[29])+(-params.Vg_N_avg[30]-params.Thetag_N_avg[30]+params.vg_N[30])*(-params.Vg_N_avg[30]-params.Thetag_N_avg[30]+params.vg_N[30])+(-params.Vg_N_avg[31]-params.Thetag_N_avg[31]+params.vg_N[31])*(-params.Vg_N_avg[31]-params.Thetag_N_avg[31]+params.vg_N[31])+(-params.Vg_N_avg[32]-params.Thetag_N_avg[32]+params.vg_N[32])*(-params.Vg_N_avg[32]-params.Thetag_N_avg[32]+params.vg_N[32])+(-params.Vg_N_avg[33]-params.Thetag_N_avg[33]+params.vg_N[33])*(-params.Vg_N_avg[33]-params.Thetag_N_avg[33]+params.vg_N[33])+(-params.Vg_N_avg[34]-params.Thetag_N_avg[34]+params.vg_N[34])*(-params.Vg_N_avg[34]-params.Thetag_N_avg[34]+params.vg_N[34])+(-params.Vg_N_avg[35]-params.Thetag_N_avg[35]+params.vg_N[35])*(-params.Vg_N_avg[35]-params.Thetag_N_avg[35]+params.vg_N[35])+(-params.Vg_N_avg[36]-params.Thetag_N_avg[36]+params.vg_N[36])*(-params.Vg_N_avg[36]-params.Thetag_N_avg[36]+params.vg_N[36])+(-params.Vg_N_avg[37]-params.Thetag_N_avg[37]+params.vg_N[37])*(-params.Vg_N_avg[37]-params.Thetag_N_avg[37]+params.vg_N[37])+(-params.Vg_N_avg[38]-params.Thetag_N_avg[38]+params.vg_N[38])*(-params.Vg_N_avg[38]-params.Thetag_N_avg[38]+params.vg_N[38])+(-params.Vg_N_avg[39]-params.Thetag_N_avg[39]+params.vg_N[39])*(-params.Vg_N_avg[39]-params.Thetag_N_avg[39]+params.vg_N[39])+(-params.Vg_N_avg[40]-params.Thetag_N_avg[40]+params.vg_N[40])*(-params.Vg_N_avg[40]-params.Thetag_N_avg[40]+params.vg_N[40])+(-params.Vg_N_avg[41]-params.Thetag_N_avg[41]+params.vg_N[41])*(-params.Vg_N_avg[41]-params.Thetag_N_avg[41]+params.vg_N[41])+(-params.Vg_N_avg[42]-params.Thetag_N_avg[42]+params.vg_N[42])*(-params.Vg_N_avg[42]-params.Thetag_N_avg[42]+params.vg_N[42])+(-params.Vg_N_avg[43]-params.Thetag_N_avg[43]+params.vg_N[43])*(-params.Vg_N_avg[43]-params.Thetag_N_avg[43]+params.vg_N[43])+(-params.Vg_N_avg[44]-params.Thetag_N_avg[44]+params.vg_N[44])*(-params.Vg_N_avg[44]-params.Thetag_N_avg[44]+params.vg_N[44])+(-params.Vg_N_avg[45]-params.Thetag_N_avg[45]+params.vg_N[45])*(-params.Vg_N_avg[45]-params.Thetag_N_avg[45]+params.vg_N[45])+(-params.Vg_N_avg[46]-params.Thetag_N_avg[46]+params.vg_N[46])*(-params.Vg_N_avg[46]-params.Thetag_N_avg[46]+params.vg_N[46])+(-params.Vg_N_avg[47]-params.Thetag_N_avg[47]+params.vg_N[47])*(-params.Vg_N_avg[47]-params.Thetag_N_avg[47]+params.vg_N[47])+(-params.Vg_N_avg[48]-params.Thetag_N_avg[48]+params.vg_N[48])*(-params.Vg_N_avg[48]-params.Thetag_N_avg[48]+params.vg_N[48])+(-params.Vg_N_avg[49]-params.Thetag_N_avg[49]+params.vg_N[49])*(-params.Vg_N_avg[49]-params.Thetag_N_avg[49]+params.vg_N[49])+(-params.Vg_N_avg[50]-params.Thetag_N_avg[50]+params.vg_N[50])*(-params.Vg_N_avg[50]-params.Thetag_N_avg[50]+params.vg_N[50])+(-params.Vg_N_avg[51]-params.Thetag_N_avg[51]+params.vg_N[51])*(-params.Vg_N_avg[51]-params.Thetag_N_avg[51]+params.vg_N[51])+(-params.Vg_N_avg[52]-params.Thetag_N_avg[52]+params.vg_N[52])*(-params.Vg_N_avg[52]-params.Thetag_N_avg[52]+params.vg_N[52])+(-params.Vg_N_avg[53]-params.Thetag_N_avg[53]+params.vg_N[53])*(-params.Vg_N_avg[53]-params.Thetag_N_avg[53]+params.vg_N[53])+(-params.Vg_N_avg[54]-params.Thetag_N_avg[54]+params.vg_N[54])*(-params.Vg_N_avg[54]-params.Thetag_N_avg[54]+params.vg_N[54])+(-params.Vg_N_avg[55]-params.Thetag_N_avg[55]+params.vg_N[55])*(-params.Vg_N_avg[55]-params.Thetag_N_avg[55]+params.vg_N[55])+(-params.Vg_N_avg[56]-params.Thetag_N_avg[56]+params.vg_N[56])*(-params.Vg_N_avg[56]-params.Thetag_N_avg[56]+params.vg_N[56])+(-params.Vg_N_avg[57]-params.Thetag_N_avg[57]+params.vg_N[57])*(-params.Vg_N_avg[57]-params.Thetag_N_avg[57]+params.vg_N[57]));
}
/* Produced by CVXGEN, 2015-09-15 18:52:15 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: ldl.c. */
/* Description: Basic test harness for solver.c. */
/* Be sure to place ldl_solve first, so storage schemes are defined by it. */
void Gensolver::ldl_solve(double *target, double *var) {
  int i;
  /* Find var = (L*diag(work.d)*L') \ target, then unpermute. */
  /* Answer goes into var. */
  /* Forward substitution. */
  /* Include permutation as we retrieve from target. Use v so we can unpermute */
  /* later. */
  work.v[0] = target[1];
  work.v[1] = target[2];
  work.v[2] = target[3];
  work.v[3] = target[4];
  work.v[4] = target[5];
  work.v[5] = target[6];
  work.v[6] = target[7];
  work.v[7] = target[8];
  work.v[8] = target[9];
  work.v[9] = target[10];
  work.v[10] = target[11];
  work.v[11] = target[12];
  work.v[12] = target[13];
  work.v[13] = target[14];
  work.v[14] = target[15];
  work.v[15] = target[16];
  work.v[16] = target[17];
  work.v[17] = target[18];
  work.v[18] = target[19];
  work.v[19] = target[20];
  work.v[20] = target[21];
  work.v[21] = target[22];
  work.v[22] = target[23];
  work.v[23] = target[24];
  work.v[24] = target[25];
  work.v[25] = target[26];
  work.v[26] = target[27];
  work.v[27] = target[28];
  work.v[28] = target[29];
  work.v[29] = target[30];
  work.v[30] = target[31];
  work.v[31] = target[32];
  work.v[32] = target[33];
  work.v[33] = target[34];
  work.v[34] = target[35];
  work.v[35] = target[36];
  work.v[36] = target[37];
  work.v[37] = target[38];
  work.v[38] = target[39];
  work.v[39] = target[40];
  work.v[40] = target[41];
  work.v[41] = target[42];
  work.v[42] = target[43];
  work.v[43] = target[44];
  work.v[44] = target[45];
  work.v[45] = target[46];
  work.v[46] = target[47];
  work.v[47] = target[48];
  work.v[48] = target[49];
  work.v[49] = target[50];
  work.v[50] = target[51];
  work.v[51] = target[52];
  work.v[52] = target[53];
  work.v[53] = target[54];
  work.v[54] = target[55];
  work.v[55] = target[56];
  work.v[56] = target[57];
  work.v[57] = target[58];
  work.v[58] = target[59];
  work.v[59] = target[60];
  work.v[60] = target[61]-work.L[0]*work.v[58];
  work.v[61] = target[0]-work.L[1]*work.v[60];
  work.v[62] = target[62]-work.L[2]*work.v[59]-work.L[3]*work.v[61];
  /* Diagonal scaling. Assume correctness of work.d_inv. */
  for (i = 0; i < 63; i++)
    work.v[i] *= work.d_inv[i];
  /* Back substitution */
  work.v[61] -= work.L[3]*work.v[62];
  work.v[60] -= work.L[1]*work.v[61];
  work.v[59] -= work.L[2]*work.v[62];
  work.v[58] -= work.L[0]*work.v[60];
  /* Unpermute the result, from v to var. */
  var[0] = work.v[61];
  var[1] = work.v[0];
  var[2] = work.v[1];
  var[3] = work.v[2];
  var[4] = work.v[3];
  var[5] = work.v[4];
  var[6] = work.v[5];
  var[7] = work.v[6];
  var[8] = work.v[7];
  var[9] = work.v[8];
  var[10] = work.v[9];
  var[11] = work.v[10];
  var[12] = work.v[11];
  var[13] = work.v[12];
  var[14] = work.v[13];
  var[15] = work.v[14];
  var[16] = work.v[15];
  var[17] = work.v[16];
  var[18] = work.v[17];
  var[19] = work.v[18];
  var[20] = work.v[19];
  var[21] = work.v[20];
  var[22] = work.v[21];
  var[23] = work.v[22];
  var[24] = work.v[23];
  var[25] = work.v[24];
  var[26] = work.v[25];
  var[27] = work.v[26];
  var[28] = work.v[27];
  var[29] = work.v[28];
  var[30] = work.v[29];
  var[31] = work.v[30];
  var[32] = work.v[31];
  var[33] = work.v[32];
  var[34] = work.v[33];
  var[35] = work.v[34];
  var[36] = work.v[35];
  var[37] = work.v[36];
  var[38] = work.v[37];
  var[39] = work.v[38];
  var[40] = work.v[39];
  var[41] = work.v[40];
  var[42] = work.v[41];
  var[43] = work.v[42];
  var[44] = work.v[43];
  var[45] = work.v[44];
  var[46] = work.v[45];
  var[47] = work.v[46];
  var[48] = work.v[47];
  var[49] = work.v[48];
  var[50] = work.v[49];
  var[51] = work.v[50];
  var[52] = work.v[51];
  var[53] = work.v[52];
  var[54] = work.v[53];
  var[55] = work.v[54];
  var[56] = work.v[55];
  var[57] = work.v[56];
  var[58] = work.v[57];
  var[59] = work.v[58];
  var[60] = work.v[59];
  var[61] = work.v[60];
  var[62] = work.v[62];
#ifndef ZERO_LIBRARY_MODE
  if (settings.debug) {
    printf("Squared norm for solution is %.8g.\n", check_residual(target, var));
  }
#endif
}
void Gensolver::ldl_factor(void) {
  work.d[0] = work.KKT[0];
  if (work.d[0] < 0)
    work.d[0] = settings.kkt_reg;
  else
    work.d[0] += settings.kkt_reg;
  work.d_inv[0] = 1/work.d[0];
  work.v[1] = work.KKT[1];
  work.d[1] = work.v[1];
  if (work.d[1] < 0)
    work.d[1] = settings.kkt_reg;
  else
    work.d[1] += settings.kkt_reg;
  work.d_inv[1] = 1/work.d[1];
  work.v[2] = work.KKT[2];
  work.d[2] = work.v[2];
  if (work.d[2] < 0)
    work.d[2] = settings.kkt_reg;
  else
    work.d[2] += settings.kkt_reg;
  work.d_inv[2] = 1/work.d[2];
  work.v[3] = work.KKT[3];
  work.d[3] = work.v[3];
  if (work.d[3] < 0)
    work.d[3] = settings.kkt_reg;
  else
    work.d[3] += settings.kkt_reg;
  work.d_inv[3] = 1/work.d[3];
  work.v[4] = work.KKT[4];
  work.d[4] = work.v[4];
  if (work.d[4] < 0)
    work.d[4] = settings.kkt_reg;
  else
    work.d[4] += settings.kkt_reg;
  work.d_inv[4] = 1/work.d[4];
  work.v[5] = work.KKT[5];
  work.d[5] = work.v[5];
  if (work.d[5] < 0)
    work.d[5] = settings.kkt_reg;
  else
    work.d[5] += settings.kkt_reg;
  work.d_inv[5] = 1/work.d[5];
  work.v[6] = work.KKT[6];
  work.d[6] = work.v[6];
  if (work.d[6] < 0)
    work.d[6] = settings.kkt_reg;
  else
    work.d[6] += settings.kkt_reg;
  work.d_inv[6] = 1/work.d[6];
  work.v[7] = work.KKT[7];
  work.d[7] = work.v[7];
  if (work.d[7] < 0)
    work.d[7] = settings.kkt_reg;
  else
    work.d[7] += settings.kkt_reg;
  work.d_inv[7] = 1/work.d[7];
  work.v[8] = work.KKT[8];
  work.d[8] = work.v[8];
  if (work.d[8] < 0)
    work.d[8] = settings.kkt_reg;
  else
    work.d[8] += settings.kkt_reg;
  work.d_inv[8] = 1/work.d[8];
  work.v[9] = work.KKT[9];
  work.d[9] = work.v[9];
  if (work.d[9] < 0)
    work.d[9] = settings.kkt_reg;
  else
    work.d[9] += settings.kkt_reg;
  work.d_inv[9] = 1/work.d[9];
  work.v[10] = work.KKT[10];
  work.d[10] = work.v[10];
  if (work.d[10] < 0)
    work.d[10] = settings.kkt_reg;
  else
    work.d[10] += settings.kkt_reg;
  work.d_inv[10] = 1/work.d[10];
  work.v[11] = work.KKT[11];
  work.d[11] = work.v[11];
  if (work.d[11] < 0)
    work.d[11] = settings.kkt_reg;
  else
    work.d[11] += settings.kkt_reg;
  work.d_inv[11] = 1/work.d[11];
  work.v[12] = work.KKT[12];
  work.d[12] = work.v[12];
  if (work.d[12] < 0)
    work.d[12] = settings.kkt_reg;
  else
    work.d[12] += settings.kkt_reg;
  work.d_inv[12] = 1/work.d[12];
  work.v[13] = work.KKT[13];
  work.d[13] = work.v[13];
  if (work.d[13] < 0)
    work.d[13] = settings.kkt_reg;
  else
    work.d[13] += settings.kkt_reg;
  work.d_inv[13] = 1/work.d[13];
  work.v[14] = work.KKT[14];
  work.d[14] = work.v[14];
  if (work.d[14] < 0)
    work.d[14] = settings.kkt_reg;
  else
    work.d[14] += settings.kkt_reg;
  work.d_inv[14] = 1/work.d[14];
  work.v[15] = work.KKT[15];
  work.d[15] = work.v[15];
  if (work.d[15] < 0)
    work.d[15] = settings.kkt_reg;
  else
    work.d[15] += settings.kkt_reg;
  work.d_inv[15] = 1/work.d[15];
  work.v[16] = work.KKT[16];
  work.d[16] = work.v[16];
  if (work.d[16] < 0)
    work.d[16] = settings.kkt_reg;
  else
    work.d[16] += settings.kkt_reg;
  work.d_inv[16] = 1/work.d[16];
  work.v[17] = work.KKT[17];
  work.d[17] = work.v[17];
  if (work.d[17] < 0)
    work.d[17] = settings.kkt_reg;
  else
    work.d[17] += settings.kkt_reg;
  work.d_inv[17] = 1/work.d[17];
  work.v[18] = work.KKT[18];
  work.d[18] = work.v[18];
  if (work.d[18] < 0)
    work.d[18] = settings.kkt_reg;
  else
    work.d[18] += settings.kkt_reg;
  work.d_inv[18] = 1/work.d[18];
  work.v[19] = work.KKT[19];
  work.d[19] = work.v[19];
  if (work.d[19] < 0)
    work.d[19] = settings.kkt_reg;
  else
    work.d[19] += settings.kkt_reg;
  work.d_inv[19] = 1/work.d[19];
  work.v[20] = work.KKT[20];
  work.d[20] = work.v[20];
  if (work.d[20] < 0)
    work.d[20] = settings.kkt_reg;
  else
    work.d[20] += settings.kkt_reg;
  work.d_inv[20] = 1/work.d[20];
  work.v[21] = work.KKT[21];
  work.d[21] = work.v[21];
  if (work.d[21] < 0)
    work.d[21] = settings.kkt_reg;
  else
    work.d[21] += settings.kkt_reg;
  work.d_inv[21] = 1/work.d[21];
  work.v[22] = work.KKT[22];
  work.d[22] = work.v[22];
  if (work.d[22] < 0)
    work.d[22] = settings.kkt_reg;
  else
    work.d[22] += settings.kkt_reg;
  work.d_inv[22] = 1/work.d[22];
  work.v[23] = work.KKT[23];
  work.d[23] = work.v[23];
  if (work.d[23] < 0)
    work.d[23] = settings.kkt_reg;
  else
    work.d[23] += settings.kkt_reg;
  work.d_inv[23] = 1/work.d[23];
  work.v[24] = work.KKT[24];
  work.d[24] = work.v[24];
  if (work.d[24] < 0)
    work.d[24] = settings.kkt_reg;
  else
    work.d[24] += settings.kkt_reg;
  work.d_inv[24] = 1/work.d[24];
  work.v[25] = work.KKT[25];
  work.d[25] = work.v[25];
  if (work.d[25] < 0)
    work.d[25] = settings.kkt_reg;
  else
    work.d[25] += settings.kkt_reg;
  work.d_inv[25] = 1/work.d[25];
  work.v[26] = work.KKT[26];
  work.d[26] = work.v[26];
  if (work.d[26] < 0)
    work.d[26] = settings.kkt_reg;
  else
    work.d[26] += settings.kkt_reg;
  work.d_inv[26] = 1/work.d[26];
  work.v[27] = work.KKT[27];
  work.d[27] = work.v[27];
  if (work.d[27] < 0)
    work.d[27] = settings.kkt_reg;
  else
    work.d[27] += settings.kkt_reg;
  work.d_inv[27] = 1/work.d[27];
  work.v[28] = work.KKT[28];
  work.d[28] = work.v[28];
  if (work.d[28] < 0)
    work.d[28] = settings.kkt_reg;
  else
    work.d[28] += settings.kkt_reg;
  work.d_inv[28] = 1/work.d[28];
  work.v[29] = work.KKT[29];
  work.d[29] = work.v[29];
  if (work.d[29] < 0)
    work.d[29] = settings.kkt_reg;
  else
    work.d[29] += settings.kkt_reg;
  work.d_inv[29] = 1/work.d[29];
  work.v[30] = work.KKT[30];
  work.d[30] = work.v[30];
  if (work.d[30] < 0)
    work.d[30] = settings.kkt_reg;
  else
    work.d[30] += settings.kkt_reg;
  work.d_inv[30] = 1/work.d[30];
  work.v[31] = work.KKT[31];
  work.d[31] = work.v[31];
  if (work.d[31] < 0)
    work.d[31] = settings.kkt_reg;
  else
    work.d[31] += settings.kkt_reg;
  work.d_inv[31] = 1/work.d[31];
  work.v[32] = work.KKT[32];
  work.d[32] = work.v[32];
  if (work.d[32] < 0)
    work.d[32] = settings.kkt_reg;
  else
    work.d[32] += settings.kkt_reg;
  work.d_inv[32] = 1/work.d[32];
  work.v[33] = work.KKT[33];
  work.d[33] = work.v[33];
  if (work.d[33] < 0)
    work.d[33] = settings.kkt_reg;
  else
    work.d[33] += settings.kkt_reg;
  work.d_inv[33] = 1/work.d[33];
  work.v[34] = work.KKT[34];
  work.d[34] = work.v[34];
  if (work.d[34] < 0)
    work.d[34] = settings.kkt_reg;
  else
    work.d[34] += settings.kkt_reg;
  work.d_inv[34] = 1/work.d[34];
  work.v[35] = work.KKT[35];
  work.d[35] = work.v[35];
  if (work.d[35] < 0)
    work.d[35] = settings.kkt_reg;
  else
    work.d[35] += settings.kkt_reg;
  work.d_inv[35] = 1/work.d[35];
  work.v[36] = work.KKT[36];
  work.d[36] = work.v[36];
  if (work.d[36] < 0)
    work.d[36] = settings.kkt_reg;
  else
    work.d[36] += settings.kkt_reg;
  work.d_inv[36] = 1/work.d[36];
  work.v[37] = work.KKT[37];
  work.d[37] = work.v[37];
  if (work.d[37] < 0)
    work.d[37] = settings.kkt_reg;
  else
    work.d[37] += settings.kkt_reg;
  work.d_inv[37] = 1/work.d[37];
  work.v[38] = work.KKT[38];
  work.d[38] = work.v[38];
  if (work.d[38] < 0)
    work.d[38] = settings.kkt_reg;
  else
    work.d[38] += settings.kkt_reg;
  work.d_inv[38] = 1/work.d[38];
  work.v[39] = work.KKT[39];
  work.d[39] = work.v[39];
  if (work.d[39] < 0)
    work.d[39] = settings.kkt_reg;
  else
    work.d[39] += settings.kkt_reg;
  work.d_inv[39] = 1/work.d[39];
  work.v[40] = work.KKT[40];
  work.d[40] = work.v[40];
  if (work.d[40] < 0)
    work.d[40] = settings.kkt_reg;
  else
    work.d[40] += settings.kkt_reg;
  work.d_inv[40] = 1/work.d[40];
  work.v[41] = work.KKT[41];
  work.d[41] = work.v[41];
  if (work.d[41] < 0)
    work.d[41] = settings.kkt_reg;
  else
    work.d[41] += settings.kkt_reg;
  work.d_inv[41] = 1/work.d[41];
  work.v[42] = work.KKT[42];
  work.d[42] = work.v[42];
  if (work.d[42] < 0)
    work.d[42] = settings.kkt_reg;
  else
    work.d[42] += settings.kkt_reg;
  work.d_inv[42] = 1/work.d[42];
  work.v[43] = work.KKT[43];
  work.d[43] = work.v[43];
  if (work.d[43] < 0)
    work.d[43] = settings.kkt_reg;
  else
    work.d[43] += settings.kkt_reg;
  work.d_inv[43] = 1/work.d[43];
  work.v[44] = work.KKT[44];
  work.d[44] = work.v[44];
  if (work.d[44] < 0)
    work.d[44] = settings.kkt_reg;
  else
    work.d[44] += settings.kkt_reg;
  work.d_inv[44] = 1/work.d[44];
  work.v[45] = work.KKT[45];
  work.d[45] = work.v[45];
  if (work.d[45] < 0)
    work.d[45] = settings.kkt_reg;
  else
    work.d[45] += settings.kkt_reg;
  work.d_inv[45] = 1/work.d[45];
  work.v[46] = work.KKT[46];
  work.d[46] = work.v[46];
  if (work.d[46] < 0)
    work.d[46] = settings.kkt_reg;
  else
    work.d[46] += settings.kkt_reg;
  work.d_inv[46] = 1/work.d[46];
  work.v[47] = work.KKT[47];
  work.d[47] = work.v[47];
  if (work.d[47] < 0)
    work.d[47] = settings.kkt_reg;
  else
    work.d[47] += settings.kkt_reg;
  work.d_inv[47] = 1/work.d[47];
  work.v[48] = work.KKT[48];
  work.d[48] = work.v[48];
  if (work.d[48] < 0)
    work.d[48] = settings.kkt_reg;
  else
    work.d[48] += settings.kkt_reg;
  work.d_inv[48] = 1/work.d[48];
  work.v[49] = work.KKT[49];
  work.d[49] = work.v[49];
  if (work.d[49] < 0)
    work.d[49] = settings.kkt_reg;
  else
    work.d[49] += settings.kkt_reg;
  work.d_inv[49] = 1/work.d[49];
  work.v[50] = work.KKT[50];
  work.d[50] = work.v[50];
  if (work.d[50] < 0)
    work.d[50] = settings.kkt_reg;
  else
    work.d[50] += settings.kkt_reg;
  work.d_inv[50] = 1/work.d[50];
  work.v[51] = work.KKT[51];
  work.d[51] = work.v[51];
  if (work.d[51] < 0)
    work.d[51] = settings.kkt_reg;
  else
    work.d[51] += settings.kkt_reg;
  work.d_inv[51] = 1/work.d[51];
  work.v[52] = work.KKT[52];
  work.d[52] = work.v[52];
  if (work.d[52] < 0)
    work.d[52] = settings.kkt_reg;
  else
    work.d[52] += settings.kkt_reg;
  work.d_inv[52] = 1/work.d[52];
  work.v[53] = work.KKT[53];
  work.d[53] = work.v[53];
  if (work.d[53] < 0)
    work.d[53] = settings.kkt_reg;
  else
    work.d[53] += settings.kkt_reg;
  work.d_inv[53] = 1/work.d[53];
  work.v[54] = work.KKT[54];
  work.d[54] = work.v[54];
  if (work.d[54] < 0)
    work.d[54] = settings.kkt_reg;
  else
    work.d[54] += settings.kkt_reg;
  work.d_inv[54] = 1/work.d[54];
  work.v[55] = work.KKT[55];
  work.d[55] = work.v[55];
  if (work.d[55] < 0)
    work.d[55] = settings.kkt_reg;
  else
    work.d[55] += settings.kkt_reg;
  work.d_inv[55] = 1/work.d[55];
  work.v[56] = work.KKT[56];
  work.d[56] = work.v[56];
  if (work.d[56] < 0)
    work.d[56] = settings.kkt_reg;
  else
    work.d[56] += settings.kkt_reg;
  work.d_inv[56] = 1/work.d[56];
  work.v[57] = work.KKT[57];
  work.d[57] = work.v[57];
  if (work.d[57] < 0)
    work.d[57] = settings.kkt_reg;
  else
    work.d[57] += settings.kkt_reg;
  work.d_inv[57] = 1/work.d[57];
  work.v[58] = work.KKT[58];
  work.d[58] = work.v[58];
  if (work.d[58] < 0)
    work.d[58] = settings.kkt_reg;
  else
    work.d[58] += settings.kkt_reg;
  work.d_inv[58] = 1/work.d[58];
  work.L[0] = (work.KKT[59])*work.d_inv[58];
  work.v[59] = work.KKT[60];
  work.d[59] = work.v[59];
  if (work.d[59] < 0)
    work.d[59] = settings.kkt_reg;
  else
    work.d[59] += settings.kkt_reg;
  work.d_inv[59] = 1/work.d[59];
  work.L[2] = (work.KKT[61])*work.d_inv[59];
  work.v[58] = work.L[0]*work.d[58];
  work.v[60] = work.KKT[62]-work.L[0]*work.v[58];
  work.d[60] = work.v[60];
  if (work.d[60] > 0)
    work.d[60] = -settings.kkt_reg;
  else
    work.d[60] -= settings.kkt_reg;
  work.d_inv[60] = 1/work.d[60];
  work.L[1] = (work.KKT[63])*work.d_inv[60];
  work.v[60] = work.L[1]*work.d[60];
  work.v[61] = work.KKT[64]-work.L[1]*work.v[60];
  work.d[61] = work.v[61];
  if (work.d[61] < 0)
    work.d[61] = settings.kkt_reg;
  else
    work.d[61] += settings.kkt_reg;
  work.d_inv[61] = 1/work.d[61];
  work.L[3] = (work.KKT[65])*work.d_inv[61];
  work.v[59] = work.L[2]*work.d[59];
  work.v[61] = work.L[3]*work.d[61];
  work.v[62] = work.KKT[66]-work.L[2]*work.v[59]-work.L[3]*work.v[61];
  work.d[62] = work.v[62];
  if (work.d[62] > 0)
    work.d[62] = -settings.kkt_reg;
  else
    work.d[62] -= settings.kkt_reg;
  work.d_inv[62] = 1/work.d[62];
#ifndef ZERO_LIBRARY_MODE
  if (settings.debug) {
    printf("Squared Frobenius for factorization is %.8g.\n", check_factorization());
  }
#endif
}
double Gensolver::check_factorization(void) {
  /* Returns the squared Frobenius norm of A - L*D*L'. */
  double temp, residual;
  /* Only check the lower triangle. */
  residual = 0;
  temp = work.KKT[64]-1*work.d[61]*1-work.L[1]*work.d[60]*work.L[1];
  residual += temp*temp;
  temp = work.KKT[0]-1*work.d[0]*1;
  residual += temp*temp;
  temp = work.KKT[1]-1*work.d[1]*1;
  residual += temp*temp;
  temp = work.KKT[2]-1*work.d[2]*1;
  residual += temp*temp;
  temp = work.KKT[3]-1*work.d[3]*1;
  residual += temp*temp;
  temp = work.KKT[4]-1*work.d[4]*1;
  residual += temp*temp;
  temp = work.KKT[5]-1*work.d[5]*1;
  residual += temp*temp;
  temp = work.KKT[6]-1*work.d[6]*1;
  residual += temp*temp;
  temp = work.KKT[7]-1*work.d[7]*1;
  residual += temp*temp;
  temp = work.KKT[8]-1*work.d[8]*1;
  residual += temp*temp;
  temp = work.KKT[9]-1*work.d[9]*1;
  residual += temp*temp;
  temp = work.KKT[10]-1*work.d[10]*1;
  residual += temp*temp;
  temp = work.KKT[11]-1*work.d[11]*1;
  residual += temp*temp;
  temp = work.KKT[12]-1*work.d[12]*1;
  residual += temp*temp;
  temp = work.KKT[13]-1*work.d[13]*1;
  residual += temp*temp;
  temp = work.KKT[14]-1*work.d[14]*1;
  residual += temp*temp;
  temp = work.KKT[15]-1*work.d[15]*1;
  residual += temp*temp;
  temp = work.KKT[16]-1*work.d[16]*1;
  residual += temp*temp;
  temp = work.KKT[17]-1*work.d[17]*1;
  residual += temp*temp;
  temp = work.KKT[18]-1*work.d[18]*1;
  residual += temp*temp;
  temp = work.KKT[19]-1*work.d[19]*1;
  residual += temp*temp;
  temp = work.KKT[20]-1*work.d[20]*1;
  residual += temp*temp;
  temp = work.KKT[21]-1*work.d[21]*1;
  residual += temp*temp;
  temp = work.KKT[22]-1*work.d[22]*1;
  residual += temp*temp;
  temp = work.KKT[23]-1*work.d[23]*1;
  residual += temp*temp;
  temp = work.KKT[24]-1*work.d[24]*1;
  residual += temp*temp;
  temp = work.KKT[25]-1*work.d[25]*1;
  residual += temp*temp;
  temp = work.KKT[26]-1*work.d[26]*1;
  residual += temp*temp;
  temp = work.KKT[27]-1*work.d[27]*1;
  residual += temp*temp;
  temp = work.KKT[28]-1*work.d[28]*1;
  residual += temp*temp;
  temp = work.KKT[29]-1*work.d[29]*1;
  residual += temp*temp;
  temp = work.KKT[30]-1*work.d[30]*1;
  residual += temp*temp;
  temp = work.KKT[31]-1*work.d[31]*1;
  residual += temp*temp;
  temp = work.KKT[32]-1*work.d[32]*1;
  residual += temp*temp;
  temp = work.KKT[33]-1*work.d[33]*1;
  residual += temp*temp;
  temp = work.KKT[34]-1*work.d[34]*1;
  residual += temp*temp;
  temp = work.KKT[35]-1*work.d[35]*1;
  residual += temp*temp;
  temp = work.KKT[36]-1*work.d[36]*1;
  residual += temp*temp;
  temp = work.KKT[37]-1*work.d[37]*1;
  residual += temp*temp;
  temp = work.KKT[38]-1*work.d[38]*1;
  residual += temp*temp;
  temp = work.KKT[39]-1*work.d[39]*1;
  residual += temp*temp;
  temp = work.KKT[40]-1*work.d[40]*1;
  residual += temp*temp;
  temp = work.KKT[41]-1*work.d[41]*1;
  residual += temp*temp;
  temp = work.KKT[42]-1*work.d[42]*1;
  residual += temp*temp;
  temp = work.KKT[43]-1*work.d[43]*1;
  residual += temp*temp;
  temp = work.KKT[44]-1*work.d[44]*1;
  residual += temp*temp;
  temp = work.KKT[45]-1*work.d[45]*1;
  residual += temp*temp;
  temp = work.KKT[46]-1*work.d[46]*1;
  residual += temp*temp;
  temp = work.KKT[47]-1*work.d[47]*1;
  residual += temp*temp;
  temp = work.KKT[48]-1*work.d[48]*1;
  residual += temp*temp;
  temp = work.KKT[49]-1*work.d[49]*1;
  residual += temp*temp;
  temp = work.KKT[50]-1*work.d[50]*1;
  residual += temp*temp;
  temp = work.KKT[51]-1*work.d[51]*1;
  residual += temp*temp;
  temp = work.KKT[52]-1*work.d[52]*1;
  residual += temp*temp;
  temp = work.KKT[53]-1*work.d[53]*1;
  residual += temp*temp;
  temp = work.KKT[54]-1*work.d[54]*1;
  residual += temp*temp;
  temp = work.KKT[55]-1*work.d[55]*1;
  residual += temp*temp;
  temp = work.KKT[56]-1*work.d[56]*1;
  residual += temp*temp;
  temp = work.KKT[57]-1*work.d[57]*1;
  residual += temp*temp;
  temp = work.KKT[58]-1*work.d[58]*1;
  residual += temp*temp;
  temp = work.KKT[60]-1*work.d[59]*1;
  residual += temp*temp;
  temp = work.KKT[59]-work.L[0]*work.d[58]*1;
  residual += temp*temp;
  temp = work.KKT[61]-work.L[2]*work.d[59]*1;
  residual += temp*temp;
  temp = work.KKT[62]-work.L[0]*work.d[58]*work.L[0]-1*work.d[60]*1;
  residual += temp*temp;
  temp = work.KKT[66]-work.L[2]*work.d[59]*work.L[2]-1*work.d[62]*1-work.L[3]*work.d[61]*work.L[3];
  residual += temp*temp;
  temp = work.KKT[63]-1*work.d[60]*work.L[1];
  residual += temp*temp;
  temp = work.KKT[65]-work.L[3]*work.d[61]*1;
  residual += temp*temp;
  return residual;
}
void Gensolver::matrix_multiply(double *result, double *source) {
  /* Finds result = A*source. */
  result[0] = work.KKT[64]*source[0]+work.KKT[63]*source[61]+work.KKT[65]*source[62];
  result[1] = work.KKT[0]*source[1];
  result[2] = work.KKT[1]*source[2];
  result[3] = work.KKT[2]*source[3];
  result[4] = work.KKT[3]*source[4];
  result[5] = work.KKT[4]*source[5];
  result[6] = work.KKT[5]*source[6];
  result[7] = work.KKT[6]*source[7];
  result[8] = work.KKT[7]*source[8];
  result[9] = work.KKT[8]*source[9];
  result[10] = work.KKT[9]*source[10];
  result[11] = work.KKT[10]*source[11];
  result[12] = work.KKT[11]*source[12];
  result[13] = work.KKT[12]*source[13];
  result[14] = work.KKT[13]*source[14];
  result[15] = work.KKT[14]*source[15];
  result[16] = work.KKT[15]*source[16];
  result[17] = work.KKT[16]*source[17];
  result[18] = work.KKT[17]*source[18];
  result[19] = work.KKT[18]*source[19];
  result[20] = work.KKT[19]*source[20];
  result[21] = work.KKT[20]*source[21];
  result[22] = work.KKT[21]*source[22];
  result[23] = work.KKT[22]*source[23];
  result[24] = work.KKT[23]*source[24];
  result[25] = work.KKT[24]*source[25];
  result[26] = work.KKT[25]*source[26];
  result[27] = work.KKT[26]*source[27];
  result[28] = work.KKT[27]*source[28];
  result[29] = work.KKT[28]*source[29];
  result[30] = work.KKT[29]*source[30];
  result[31] = work.KKT[30]*source[31];
  result[32] = work.KKT[31]*source[32];
  result[33] = work.KKT[32]*source[33];
  result[34] = work.KKT[33]*source[34];
  result[35] = work.KKT[34]*source[35];
  result[36] = work.KKT[35]*source[36];
  result[37] = work.KKT[36]*source[37];
  result[38] = work.KKT[37]*source[38];
  result[39] = work.KKT[38]*source[39];
  result[40] = work.KKT[39]*source[40];
  result[41] = work.KKT[40]*source[41];
  result[42] = work.KKT[41]*source[42];
  result[43] = work.KKT[42]*source[43];
  result[44] = work.KKT[43]*source[44];
  result[45] = work.KKT[44]*source[45];
  result[46] = work.KKT[45]*source[46];
  result[47] = work.KKT[46]*source[47];
  result[48] = work.KKT[47]*source[48];
  result[49] = work.KKT[48]*source[49];
  result[50] = work.KKT[49]*source[50];
  result[51] = work.KKT[50]*source[51];
  result[52] = work.KKT[51]*source[52];
  result[53] = work.KKT[52]*source[53];
  result[54] = work.KKT[53]*source[54];
  result[55] = work.KKT[54]*source[55];
  result[56] = work.KKT[55]*source[56];
  result[57] = work.KKT[56]*source[57];
  result[58] = work.KKT[57]*source[58];
  result[59] = work.KKT[58]*source[59]+work.KKT[59]*source[61];
  result[60] = work.KKT[60]*source[60]+work.KKT[61]*source[62];
  result[61] = work.KKT[59]*source[59]+work.KKT[62]*source[61]+work.KKT[63]*source[0];
  result[62] = work.KKT[61]*source[60]+work.KKT[66]*source[62]+work.KKT[65]*source[0];
}
double Gensolver::check_residual(double *target, double *multiplicand) {
  /* Returns the squared 2-norm of lhs - A*rhs. */
  /* Reuses v to find the residual. */
  int i;
  double residual;
  residual = 0;
  matrix_multiply(work.v, multiplicand);
  for (i = 0; i < 59; i++) {
    residual += (target[i] - work.v[i])*(target[i] - work.v[i]);
  }
  return residual;
}
void Gensolver::fill_KKT(void) {
  work.KKT[64] = 2*(params.c2[0]+work.frac_121674190848*work.quad_839165739008[0]);
  work.KKT[0] = 2*work.frac_121674190848;
  work.KKT[1] = 2*work.frac_121674190848;
  work.KKT[2] = 2*work.frac_121674190848;
  work.KKT[3] = 2*work.frac_121674190848;
  work.KKT[4] = 2*work.frac_121674190848;
  work.KKT[5] = 2*work.frac_121674190848;
  work.KKT[6] = 2*work.frac_121674190848;
  work.KKT[7] = 2*work.frac_121674190848;
  work.KKT[8] = 2*work.frac_121674190848;
  work.KKT[9] = 2*work.frac_121674190848;
  work.KKT[10] = 2*work.frac_121674190848;
  work.KKT[11] = 2*work.frac_121674190848;
  work.KKT[12] = 2*work.frac_121674190848;
  work.KKT[13] = 2*work.frac_121674190848;
  work.KKT[14] = 2*work.frac_121674190848;
  work.KKT[15] = 2*work.frac_121674190848;
  work.KKT[16] = 2*work.frac_121674190848;
  work.KKT[17] = 2*work.frac_121674190848;
  work.KKT[18] = 2*work.frac_121674190848;
  work.KKT[19] = 2*work.frac_121674190848;
  work.KKT[20] = 2*work.frac_121674190848;
  work.KKT[21] = 2*work.frac_121674190848;
  work.KKT[22] = 2*work.frac_121674190848;
  work.KKT[23] = 2*work.frac_121674190848;
  work.KKT[24] = 2*work.frac_121674190848;
  work.KKT[25] = 2*work.frac_121674190848;
  work.KKT[26] = 2*work.frac_121674190848;
  work.KKT[27] = 2*work.frac_121674190848;
  work.KKT[28] = 2*work.frac_121674190848;
  work.KKT[29] = 2*work.frac_121674190848;
  work.KKT[30] = 2*work.frac_121674190848;
  work.KKT[31] = 2*work.frac_121674190848;
  work.KKT[32] = 2*work.frac_121674190848;
  work.KKT[33] = 2*work.frac_121674190848;
  work.KKT[34] = 2*work.frac_121674190848;
  work.KKT[35] = 2*work.frac_121674190848;
  work.KKT[36] = 2*work.frac_121674190848;
  work.KKT[37] = 2*work.frac_121674190848;
  work.KKT[38] = 2*work.frac_121674190848;
  work.KKT[39] = 2*work.frac_121674190848;
  work.KKT[40] = 2*work.frac_121674190848;
  work.KKT[41] = 2*work.frac_121674190848;
  work.KKT[42] = 2*work.frac_121674190848;
  work.KKT[43] = 2*work.frac_121674190848;
  work.KKT[44] = 2*work.frac_121674190848;
  work.KKT[45] = 2*work.frac_121674190848;
  work.KKT[46] = 2*work.frac_121674190848;
  work.KKT[47] = 2*work.frac_121674190848;
  work.KKT[48] = 2*work.frac_121674190848;
  work.KKT[49] = 2*work.frac_121674190848;
  work.KKT[50] = 2*work.frac_121674190848;
  work.KKT[51] = 2*work.frac_121674190848;
  work.KKT[52] = 2*work.frac_121674190848;
  work.KKT[53] = 2*work.frac_121674190848;
  work.KKT[54] = 2*work.frac_121674190848;
  work.KKT[55] = 2*work.frac_121674190848;
  work.KKT[56] = 2*work.frac_121674190848;
  work.KKT[57] = 2*work.frac_121674190848;
  work.KKT[58] = work.s_inv_z[0];
  work.KKT[60] = work.s_inv_z[1];
  work.KKT[59] = 1;
  work.KKT[61] = 1;
  work.KKT[62] = work.block_33[0];
  work.KKT[66] = work.block_33[0];
  work.KKT[63] = -1;
  work.KKT[65] = 1;
}

