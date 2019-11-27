//solver.cpp
/* Produced by CVXGEN, 2015-02-06 22:35:37 -0500.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: solver.c. */
/* Description: Main solver file. */
#include "gensolver.h"
#include <array>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;
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
  settings.verbose = 1;
  settings.verbose_refinement = 0;
  settings.better_start = 1;
  settings.kkt_reg = 1e-7;
}
void Gensolver::setup_pointers(void) {
  work.y = work.x + 21;
  work.s = work.x + 31;
  work.z = work.x + 33;
  vars.Pg = work.x + 0;
  vars.Thetag = work.x + 1;
}
void Gensolver::setup_indexing(void) {
  setup_pointers();
}
void Gensolver::set_start(void) {
  int i;
  for (i = 0; i < 21; i++)
    work.x[i] = 0;
  for (i = 0; i < 10; i++)
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
  for (i = 0; i < 21; i++)
    objv += work.x[i]*work.rhs[i];
  objv *= 0.5;
  for (i = 0; i < 21; i++)
    objv += work.q[i]*work.x[i];
  objv += params.c0[0]+work.quad_611769487360[0]+work.quad_445109895168[0]+work.quad_793880735744[0]+work.quad_428578906112[0]+work.quad_39707512832[0]+work.quad_355912712192[0]+work.quad_113495719936[0]+work.quad_916626804736[0]+work.quad_386017529856[0]+work.quad_727622279168[0];
  return objv;
}
void Gensolver::fillrhs_aff(void) {
  int i;
  double *r1, *r2, *r3, *r4;
  r1 = work.rhs;
  r2 = work.rhs + 21;
  r3 = work.rhs + 23;
  r4 = work.rhs + 25;
  /* r1 = -A^Ty - G^Tz - Px - q. */
  multbymAT(r1, work.y);
  multbymGT(work.buffer, work.z);
  for (i = 0; i < 21; i++)
    r1[i] += work.buffer[i];
  multbyP(work.buffer, work.x);
  for (i = 0; i < 21; i++)
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
  for (i = 0; i < 10; i++)
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
  r2 = work.rhs + 21;
  ds_aff = work.lhs_aff + 21;
  dz_aff = work.lhs_aff + 23;
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
  for (i = 0; i < 21; i++)
    work.rhs[i] = 0;
  for (i = 23; i < 35; i++)
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
    for (i = 0; i < 35; i++) {
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
    for (i = 0; i < 35; i++) {
      var[i] -= new_var[i];
    }
  }
#ifndef ZERO_LIBRARY_MODE
  if (settings.verbose_refinement) {
    /* Check the residual once more, but only if we're reporting it, since */
    /* it's expensive. */
    norm2 = 0;
    matrix_multiply(residual, var);
    for (i = 0; i < 35; i++) {
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
  for (i = 0; i < 10; i++)
    work.buffer[i] += work.b[i];
  /* Now find the squared norm. */
  norm2_squared = 0;
  for (i = 0; i < 10; i++)
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
  s = work.lhs_aff + 21;
  z = work.lhs_aff + 23;
  y = work.lhs_aff + 25;
  /* Just set x and y as is. */
  for (i = 0; i < 21; i++)
    work.x[i] = x[i];
  for (i = 0; i < 10; i++)
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
  r2 = work.rhs + 21;
  r3 = work.rhs + 23;
  r4 = work.rhs + 25;
  for (i = 0; i < 21; i++)
    r1[i] = -work.q[i];
  for (i = 0; i < 2; i++)
    r2[i] = 0;
  for (i = 0; i < 2; i++)
    r3[i] = work.h[i];
  for (i = 0; i < 10; i++)
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
    for (i = 0; i < 35; i++)
      work.lhs_aff[i] += work.lhs_cc[i];
    /* Rename aff to reflect its new meaning. */
    dx = work.lhs_aff;
    ds = work.lhs_aff + 21;
    dz = work.lhs_aff + 23;
    dy = work.lhs_aff + 25;
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
    for (i = 0; i < 21; i++)
      work.x[i] += alpha*dx[i];
    for (i = 0; i < 2; i++)
      work.s[i] += alpha*ds[i];
    for (i = 0; i < 2; i++)
      work.z[i] += alpha*dz[i];
    for (i = 0; i < 10; i++)
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

//util.cpp
/* Produced by CVXGEN, 2015-02-06 22:35:37 -0500.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: util.c. */
/* Description: Common utility file for all cvxgen code. */

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

//matrix_support.cpp
/* Produced by CVXGEN, 2015-02-06 22:35:37 -0500.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: matrix_support.c. */
/* Description: Support functions for matrix multiplication and vector filling. */

void Gensolver::multbymA(double *lhs, double *rhs) {
  lhs[0] = -rhs[1]*(1)-rhs[11]*(-1);
  lhs[1] = -rhs[2]*(1)-rhs[12]*(-1);
  lhs[2] = -rhs[3]*(1)-rhs[13]*(-1);
  lhs[3] = -rhs[4]*(1)-rhs[14]*(-1);
  lhs[4] = -rhs[5]*(1)-rhs[15]*(-1);
  lhs[5] = -rhs[6]*(1)-rhs[16]*(-1);
  lhs[6] = -rhs[7]*(1)-rhs[17]*(-1);
  lhs[7] = -rhs[8]*(1)-rhs[18]*(-1);
  lhs[8] = -rhs[9]*(1)-rhs[19]*(-1);
  lhs[9] = -rhs[10]*(1)-rhs[20]*(-1);
}
void Gensolver::multbymAT(double *lhs, double *rhs) {
  lhs[0] = 0;
  lhs[1] = -rhs[0]*(1);
  lhs[2] = -rhs[1]*(1);
  lhs[3] = -rhs[2]*(1);
  lhs[4] = -rhs[3]*(1);
  lhs[5] = -rhs[4]*(1);
  lhs[6] = -rhs[5]*(1);
  lhs[7] = -rhs[6]*(1);
  lhs[8] = -rhs[7]*(1);
  lhs[9] = -rhs[8]*(1);
  lhs[10] = -rhs[9]*(1);
  lhs[11] = -rhs[0]*(-1);
  lhs[12] = -rhs[1]*(-1);
  lhs[13] = -rhs[2]*(-1);
  lhs[14] = -rhs[3]*(-1);
  lhs[15] = -rhs[4]*(-1);
  lhs[16] = -rhs[5]*(-1);
  lhs[17] = -rhs[6]*(-1);
  lhs[18] = -rhs[7]*(-1);
  lhs[19] = -rhs[8]*(-1);
  lhs[20] = -rhs[9]*(-1);
}
void Gensolver::multbymG(double *lhs, double *rhs) {
  lhs[0] = -rhs[0]*(-1);
  lhs[1] = -rhs[0]*(1);
}
void Gensolver::multbymGT(double *lhs, double *rhs) {
  lhs[0] = -rhs[0]*(-1)-rhs[1]*(1);
for ( int i = 1; i <= 20; ++i )
  lhs[i] = 0;
}
void Gensolver::multbyP(double *lhs, double *rhs) {
  /* TODO use the fact that P is symmetric? */
  /* TODO check doubling / half factor etc. */
  lhs[0] = rhs[0]*(2*(params.c2[0]+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848));
for ( int i = 1; i <= 10; ++i )
  lhs[i] = 0;
for ( int i = 11; i <= 20; ++i )
  lhs[i] = rhs[i]*(2*work.frac_121674190848);
}
void Gensolver::fillq(void) {
  work.q[0] = params.c1[0]+2*(-params.Pg_N_init[0]+params.Pg_N_avg[0]+params.ug_N[0])*work.frac_121674190848+2*(-params.Pg_N_init[1]+params.Pg_N_avg[1]+params.ug_N[1])*work.frac_121674190848+2*(-params.Pg_N_init[2]+params.Pg_N_avg[2]+params.ug_N[2])*work.frac_121674190848+2*(-params.Pg_N_init[3]+params.Pg_N_avg[3]+params.ug_N[3])*work.frac_121674190848+2*(-params.Pg_N_init[4]+params.Pg_N_avg[4]+params.ug_N[4])*work.frac_121674190848+2*(-params.Pg_N_init[5]+params.Pg_N_avg[5]+params.ug_N[5])*work.frac_121674190848+2*(-params.Pg_N_init[6]+params.Pg_N_avg[6]+params.ug_N[6])*work.frac_121674190848+2*(-params.Pg_N_init[7]+params.Pg_N_avg[7]+params.ug_N[7])*work.frac_121674190848+2*(-params.Pg_N_init[8]+params.Pg_N_avg[8]+params.ug_N[8])*work.frac_121674190848+2*(-params.Pg_N_init[9]+params.Pg_N_avg[9]+params.ug_N[9])*work.frac_121674190848;
for ( int i = 1; i <= 20; ++i )
  work.q[i] = 0;
}
void Gensolver::fillh(void) {
  work.h[0] = -params.PgMin[0];
  work.h[1] = params.PgMax[0];
}
void Gensolver::fillb(void) {
for ( int i = 0; i <= 9; ++i )
  work.b[i] = -(-params.Vg_N_avg[i]-params.Thetag_N_avg[i]+params.vg_N[i]);
}
void Gensolver::pre_ops(void) {
  work.frac_121674190848 = params.rho[0];
  work.frac_121674190848 /= 2;
  work.quad_611769487360[0] = (-params.Pg_N_init[0]+params.Pg_N_avg[0]+params.ug_N[0])*work.frac_121674190848*(-params.Pg_N_init[0]+params.Pg_N_avg[0]+params.ug_N[0]);
  work.quad_445109895168[0] = (-params.Pg_N_init[1]+params.Pg_N_avg[1]+params.ug_N[1])*work.frac_121674190848*(-params.Pg_N_init[1]+params.Pg_N_avg[1]+params.ug_N[1]);
  work.quad_793880735744[0] = (-params.Pg_N_init[2]+params.Pg_N_avg[2]+params.ug_N[2])*work.frac_121674190848*(-params.Pg_N_init[2]+params.Pg_N_avg[2]+params.ug_N[2]);
  work.quad_428578906112[0] = (-params.Pg_N_init[3]+params.Pg_N_avg[3]+params.ug_N[3])*work.frac_121674190848*(-params.Pg_N_init[3]+params.Pg_N_avg[3]+params.ug_N[3]);
  work.quad_39707512832[0] = (-params.Pg_N_init[4]+params.Pg_N_avg[4]+params.ug_N[4])*work.frac_121674190848*(-params.Pg_N_init[4]+params.Pg_N_avg[4]+params.ug_N[4]);
  work.quad_355912712192[0] = (-params.Pg_N_init[5]+params.Pg_N_avg[5]+params.ug_N[5])*work.frac_121674190848*(-params.Pg_N_init[5]+params.Pg_N_avg[5]+params.ug_N[5]);
  work.quad_113495719936[0] = (-params.Pg_N_init[6]+params.Pg_N_avg[6]+params.ug_N[6])*work.frac_121674190848*(-params.Pg_N_init[6]+params.Pg_N_avg[6]+params.ug_N[6]);
  work.quad_916626804736[0] = (-params.Pg_N_init[7]+params.Pg_N_avg[7]+params.ug_N[7])*work.frac_121674190848*(-params.Pg_N_init[7]+params.Pg_N_avg[7]+params.ug_N[7]);
  work.quad_386017529856[0] = (-params.Pg_N_init[8]+params.Pg_N_avg[8]+params.ug_N[8])*work.frac_121674190848*(-params.Pg_N_init[8]+params.Pg_N_avg[8]+params.ug_N[8]);
  work.quad_727622279168[0] = (-params.Pg_N_init[9]+params.Pg_N_avg[9]+params.ug_N[9])*work.frac_121674190848*(-params.Pg_N_init[9]+params.Pg_N_avg[9]+params.ug_N[9]);
}

//ldl.cpp
/* Produced by CVXGEN, 2015-02-06 22:35:37 -0500.  */
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
  work.v[0] = target[21];
  work.v[1] = target[22];
  work.v[2] = target[23]-work.L[0]*work.v[0];
  work.v[3] = target[0]-work.L[1]*work.v[2];
  work.v[4] = target[24]-work.L[2]*work.v[1]-work.L[3]*work.v[3];
  work.v[5] = target[1];
  work.v[6] = target[11];
  work.v[7] = target[25]-work.L[4]*work.v[5]-work.L[5]*work.v[6];
  work.v[8] = target[2];
  work.v[9] = target[12];
  work.v[10] = target[26]-work.L[6]*work.v[8]-work.L[7]*work.v[9];
  work.v[11] = target[3];
  work.v[12] = target[13];
  work.v[13] = target[27]-work.L[8]*work.v[11]-work.L[9]*work.v[12];
  work.v[14] = target[4];
  work.v[15] = target[14];
  work.v[16] = target[28]-work.L[10]*work.v[14]-work.L[11]*work.v[15];
  work.v[17] = target[5];
  work.v[18] = target[15];
  work.v[19] = target[29]-work.L[12]*work.v[17]-work.L[13]*work.v[18];
  work.v[20] = target[6];
  work.v[21] = target[16];
  work.v[22] = target[30]-work.L[14]*work.v[20]-work.L[15]*work.v[21];
  work.v[23] = target[7];
  work.v[24] = target[17];
  work.v[25] = target[31]-work.L[16]*work.v[23]-work.L[17]*work.v[24];
  work.v[26] = target[8];
  work.v[27] = target[18];
  work.v[28] = target[32]-work.L[18]*work.v[26]-work.L[19]*work.v[27];
  work.v[29] = target[9];
  work.v[30] = target[19];
  work.v[31] = target[33]-work.L[20]*work.v[29]-work.L[21]*work.v[30];
  work.v[32] = target[10];
  work.v[33] = target[20];
  work.v[34] = target[34]-work.L[22]*work.v[32]-work.L[23]*work.v[33];
  /* Diagonal scaling. Assume correctness of work.d_inv. */
  for (i = 0; i < 35; i++)
    work.v[i] *= work.d_inv[i];
  /* Back substitution */
  work.v[33] -= work.L[23]*work.v[34];
  work.v[32] -= work.L[22]*work.v[34];
  work.v[30] -= work.L[21]*work.v[31];
  work.v[29] -= work.L[20]*work.v[31];
  work.v[27] -= work.L[19]*work.v[28];
  work.v[26] -= work.L[18]*work.v[28];
  work.v[24] -= work.L[17]*work.v[25];
  work.v[23] -= work.L[16]*work.v[25];
  work.v[21] -= work.L[15]*work.v[22];
  work.v[20] -= work.L[14]*work.v[22];
  work.v[18] -= work.L[13]*work.v[19];
  work.v[17] -= work.L[12]*work.v[19];
  work.v[15] -= work.L[11]*work.v[16];
  work.v[14] -= work.L[10]*work.v[16];
  work.v[12] -= work.L[9]*work.v[13];
  work.v[11] -= work.L[8]*work.v[13];
  work.v[9] -= work.L[7]*work.v[10];
  work.v[8] -= work.L[6]*work.v[10];
  work.v[6] -= work.L[5]*work.v[7];
  work.v[5] -= work.L[4]*work.v[7];
  work.v[3] -= work.L[3]*work.v[4];
  work.v[2] -= work.L[1]*work.v[3];
  work.v[1] -= work.L[2]*work.v[4];
  work.v[0] -= work.L[0]*work.v[2];
  /* Unpermute the result, from v to var. */
  var[0] = work.v[3];
  var[1] = work.v[5];
  var[2] = work.v[8];
  var[3] = work.v[11];
  var[4] = work.v[14];
  var[5] = work.v[17];
  var[6] = work.v[20];
  var[7] = work.v[23];
  var[8] = work.v[26];
  var[9] = work.v[29];
  var[10] = work.v[32];
  var[11] = work.v[6];
  var[12] = work.v[9];
  var[13] = work.v[12];
  var[14] = work.v[15];
  var[15] = work.v[18];
  var[16] = work.v[21];
  var[17] = work.v[24];
  var[18] = work.v[27];
  var[19] = work.v[30];
  var[20] = work.v[33];
  var[21] = work.v[0];
  var[22] = work.v[1];
  var[23] = work.v[2];
  var[24] = work.v[4];
  var[25] = work.v[7];
  var[26] = work.v[10];
  var[27] = work.v[13];
  var[28] = work.v[16];
  var[29] = work.v[19];
  var[30] = work.v[22];
  var[31] = work.v[25];
  var[32] = work.v[28];
  var[33] = work.v[31];
  var[34] = work.v[34];
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
  work.L[0] = work.KKT[1]*work.d_inv[0];
  work.v[1] = work.KKT[2];
  work.d[1] = work.v[1];
  if (work.d[1] < 0)
    work.d[1] = settings.kkt_reg;
  else
    work.d[1] += settings.kkt_reg;
  work.d_inv[1] = 1/work.d[1];
  work.L[2] = (work.KKT[3])*work.d_inv[1];
  work.v[0] = work.L[0]*work.d[0];
  work.v[2] = work.KKT[4]-work.L[0]*work.v[0];
  work.d[2] = work.v[2];
  if (work.d[2] > 0)
    work.d[2] = -settings.kkt_reg;
  else
    work.d[2] -= settings.kkt_reg;
  work.d_inv[2] = 1/work.d[2];
  work.L[1] = (work.KKT[5])*work.d_inv[2];
  work.v[2] = work.L[1]*work.d[2];
  work.v[3] = work.KKT[6]-work.L[1]*work.v[2];
  work.d[3] = work.v[3];
  if (work.d[3] < 0)
    work.d[3] = settings.kkt_reg;
  else
    work.d[3] += settings.kkt_reg;
  work.d_inv[3] = 1/work.d[3];
  work.L[3] = (work.KKT[7])*work.d_inv[3];
  work.v[1] = work.L[2]*work.d[1];
  work.v[3] = work.L[3]*work.d[3];
  work.v[4] = work.KKT[8]-work.L[2]*work.v[1]-work.L[3]*work.v[3];
  work.d[4] = work.v[4];
  if (work.d[4] > 0)
    work.d[4] = -settings.kkt_reg;
  else
    work.d[4] -= settings.kkt_reg;
  work.d_inv[4] = 1/work.d[4];
  work.v[5] = 0;
  work.d[5] = work.v[5];
  if (work.d[5] < 0)
    work.d[5] = settings.kkt_reg;
  else
    work.d[5] += settings.kkt_reg;
  work.d_inv[5] = 1/work.d[5];
  work.L[4] = (work.KKT[9])*work.d_inv[5];
  work.v[6] = work.KKT[10];
  work.d[6] = work.v[6];
  if (work.d[6] < 0)
    work.d[6] = settings.kkt_reg;
  else
    work.d[6] += settings.kkt_reg;
  work.d_inv[6] = 1/work.d[6];
  work.L[5] = (work.KKT[11])*work.d_inv[6];
  work.v[5] = work.L[4]*work.d[5];
  work.v[6] = work.L[5]*work.d[6];
  work.v[7] = 0-work.L[4]*work.v[5]-work.L[5]*work.v[6];
  work.d[7] = work.v[7];
  if (work.d[7] > 0)
    work.d[7] = -settings.kkt_reg;
  else
    work.d[7] -= settings.kkt_reg;
  work.d_inv[7] = 1/work.d[7];
  work.v[8] = 0;
  work.d[8] = work.v[8];
  if (work.d[8] < 0)
    work.d[8] = settings.kkt_reg;
  else
    work.d[8] += settings.kkt_reg;
  work.d_inv[8] = 1/work.d[8];
  work.L[6] = (work.KKT[12])*work.d_inv[8];
  work.v[9] = work.KKT[13];
  work.d[9] = work.v[9];
  if (work.d[9] < 0)
    work.d[9] = settings.kkt_reg;
  else
    work.d[9] += settings.kkt_reg;
  work.d_inv[9] = 1/work.d[9];
  work.L[7] = (work.KKT[14])*work.d_inv[9];
  work.v[8] = work.L[6]*work.d[8];
  work.v[9] = work.L[7]*work.d[9];
  work.v[10] = 0-work.L[6]*work.v[8]-work.L[7]*work.v[9];
  work.d[10] = work.v[10];
  if (work.d[10] > 0)
    work.d[10] = -settings.kkt_reg;
  else
    work.d[10] -= settings.kkt_reg;
  work.d_inv[10] = 1/work.d[10];
  work.v[11] = 0;
  work.d[11] = work.v[11];
  if (work.d[11] < 0)
    work.d[11] = settings.kkt_reg;
  else
    work.d[11] += settings.kkt_reg;
  work.d_inv[11] = 1/work.d[11];
  work.L[8] = (work.KKT[15])*work.d_inv[11];
  work.v[12] = work.KKT[16];
  work.d[12] = work.v[12];
  if (work.d[12] < 0)
    work.d[12] = settings.kkt_reg;
  else
    work.d[12] += settings.kkt_reg;
  work.d_inv[12] = 1/work.d[12];
  work.L[9] = (work.KKT[17])*work.d_inv[12];
  work.v[11] = work.L[8]*work.d[11];
  work.v[12] = work.L[9]*work.d[12];
  work.v[13] = 0-work.L[8]*work.v[11]-work.L[9]*work.v[12];
  work.d[13] = work.v[13];
  if (work.d[13] > 0)
    work.d[13] = -settings.kkt_reg;
  else
    work.d[13] -= settings.kkt_reg;
  work.d_inv[13] = 1/work.d[13];
  work.v[14] = 0;
  work.d[14] = work.v[14];
  if (work.d[14] < 0)
    work.d[14] = settings.kkt_reg;
  else
    work.d[14] += settings.kkt_reg;
  work.d_inv[14] = 1/work.d[14];
  work.L[10] = (work.KKT[18])*work.d_inv[14];
  work.v[15] = work.KKT[19];
  work.d[15] = work.v[15];
  if (work.d[15] < 0)
    work.d[15] = settings.kkt_reg;
  else
    work.d[15] += settings.kkt_reg;
  work.d_inv[15] = 1/work.d[15];
  work.L[11] = (work.KKT[20])*work.d_inv[15];
  work.v[14] = work.L[10]*work.d[14];
  work.v[15] = work.L[11]*work.d[15];
  work.v[16] = 0-work.L[10]*work.v[14]-work.L[11]*work.v[15];
  work.d[16] = work.v[16];
  if (work.d[16] > 0)
    work.d[16] = -settings.kkt_reg;
  else
    work.d[16] -= settings.kkt_reg;
  work.d_inv[16] = 1/work.d[16];
  work.v[17] = 0;
  work.d[17] = work.v[17];
  if (work.d[17] < 0)
    work.d[17] = settings.kkt_reg;
  else
    work.d[17] += settings.kkt_reg;
  work.d_inv[17] = 1/work.d[17];
  work.L[12] = (work.KKT[21])*work.d_inv[17];
  work.v[18] = work.KKT[22];
  work.d[18] = work.v[18];
  if (work.d[18] < 0)
    work.d[18] = settings.kkt_reg;
  else
    work.d[18] += settings.kkt_reg;
  work.d_inv[18] = 1/work.d[18];
  work.L[13] = (work.KKT[23])*work.d_inv[18];
  work.v[17] = work.L[12]*work.d[17];
  work.v[18] = work.L[13]*work.d[18];
  work.v[19] = 0-work.L[12]*work.v[17]-work.L[13]*work.v[18];
  work.d[19] = work.v[19];
  if (work.d[19] > 0)
    work.d[19] = -settings.kkt_reg;
  else
    work.d[19] -= settings.kkt_reg;
  work.d_inv[19] = 1/work.d[19];
  work.v[20] = 0;
  work.d[20] = work.v[20];
  if (work.d[20] < 0)
    work.d[20] = settings.kkt_reg;
  else
    work.d[20] += settings.kkt_reg;
  work.d_inv[20] = 1/work.d[20];
  work.L[14] = (work.KKT[24])*work.d_inv[20];
  work.v[21] = work.KKT[25];
  work.d[21] = work.v[21];
  if (work.d[21] < 0)
    work.d[21] = settings.kkt_reg;
  else
    work.d[21] += settings.kkt_reg;
  work.d_inv[21] = 1/work.d[21];
  work.L[15] = (work.KKT[26])*work.d_inv[21];
  work.v[20] = work.L[14]*work.d[20];
  work.v[21] = work.L[15]*work.d[21];
  work.v[22] = 0-work.L[14]*work.v[20]-work.L[15]*work.v[21];
  work.d[22] = work.v[22];
  if (work.d[22] > 0)
    work.d[22] = -settings.kkt_reg;
  else
    work.d[22] -= settings.kkt_reg;
  work.d_inv[22] = 1/work.d[22];
  work.v[23] = 0;
  work.d[23] = work.v[23];
  if (work.d[23] < 0)
    work.d[23] = settings.kkt_reg;
  else
    work.d[23] += settings.kkt_reg;
  work.d_inv[23] = 1/work.d[23];
  work.L[16] = (work.KKT[27])*work.d_inv[23];
  work.v[24] = work.KKT[28];
  work.d[24] = work.v[24];
  if (work.d[24] < 0)
    work.d[24] = settings.kkt_reg;
  else
    work.d[24] += settings.kkt_reg;
  work.d_inv[24] = 1/work.d[24];
  work.L[17] = (work.KKT[29])*work.d_inv[24];
  work.v[23] = work.L[16]*work.d[23];
  work.v[24] = work.L[17]*work.d[24];
  work.v[25] = 0-work.L[16]*work.v[23]-work.L[17]*work.v[24];
  work.d[25] = work.v[25];
  if (work.d[25] > 0)
    work.d[25] = -settings.kkt_reg;
  else
    work.d[25] -= settings.kkt_reg;
  work.d_inv[25] = 1/work.d[25];
  work.v[26] = 0;
  work.d[26] = work.v[26];
  if (work.d[26] < 0)
    work.d[26] = settings.kkt_reg;
  else
    work.d[26] += settings.kkt_reg;
  work.d_inv[26] = 1/work.d[26];
  work.L[18] = (work.KKT[30])*work.d_inv[26];
  work.v[27] = work.KKT[31];
  work.d[27] = work.v[27];
  if (work.d[27] < 0)
    work.d[27] = settings.kkt_reg;
  else
    work.d[27] += settings.kkt_reg;
  work.d_inv[27] = 1/work.d[27];
  work.L[19] = (work.KKT[32])*work.d_inv[27];
  work.v[26] = work.L[18]*work.d[26];
  work.v[27] = work.L[19]*work.d[27];
  work.v[28] = 0-work.L[18]*work.v[26]-work.L[19]*work.v[27];
  work.d[28] = work.v[28];
  if (work.d[28] > 0)
    work.d[28] = -settings.kkt_reg;
  else
    work.d[28] -= settings.kkt_reg;
  work.d_inv[28] = 1/work.d[28];
  work.v[29] = 0;
  work.d[29] = work.v[29];
  if (work.d[29] < 0)
    work.d[29] = settings.kkt_reg;
  else
    work.d[29] += settings.kkt_reg;
  work.d_inv[29] = 1/work.d[29];
  work.L[20] = (work.KKT[33])*work.d_inv[29];
  work.v[30] = work.KKT[34];
  work.d[30] = work.v[30];
  if (work.d[30] < 0)
    work.d[30] = settings.kkt_reg;
  else
    work.d[30] += settings.kkt_reg;
  work.d_inv[30] = 1/work.d[30];
  work.L[21] = (work.KKT[35])*work.d_inv[30];
  work.v[29] = work.L[20]*work.d[29];
  work.v[30] = work.L[21]*work.d[30];
  work.v[31] = 0-work.L[20]*work.v[29]-work.L[21]*work.v[30];
  work.d[31] = work.v[31];
  if (work.d[31] > 0)
    work.d[31] = -settings.kkt_reg;
  else
    work.d[31] -= settings.kkt_reg;
  work.d_inv[31] = 1/work.d[31];
  work.v[32] = 0;
  work.d[32] = work.v[32];
  if (work.d[32] < 0)
    work.d[32] = settings.kkt_reg;
  else
    work.d[32] += settings.kkt_reg;
  work.d_inv[32] = 1/work.d[32];
  work.L[22] = (work.KKT[36])*work.d_inv[32];
  work.v[33] = work.KKT[37];
  work.d[33] = work.v[33];
  if (work.d[33] < 0)
    work.d[33] = settings.kkt_reg;
  else
    work.d[33] += settings.kkt_reg;
  work.d_inv[33] = 1/work.d[33];
  work.L[23] = (work.KKT[38])*work.d_inv[33];
  work.v[32] = work.L[22]*work.d[32];
  work.v[33] = work.L[23]*work.d[33];
  work.v[34] = 0-work.L[22]*work.v[32]-work.L[23]*work.v[33];
  work.d[34] = work.v[34];
  if (work.d[34] > 0)
    work.d[34] = -settings.kkt_reg;
  else
    work.d[34] -= settings.kkt_reg;
  work.d_inv[34] = 1/work.d[34];
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
  temp = work.KKT[6]-1*work.d[3]*1-work.L[1]*work.d[2]*work.L[1];
  residual += temp*temp;
  temp = work.KKT[10]-1*work.d[6]*1;
  residual += temp*temp;
  temp = work.KKT[13]-1*work.d[9]*1;
  residual += temp*temp;
  temp = work.KKT[16]-1*work.d[12]*1;
  residual += temp*temp;
  temp = work.KKT[19]-1*work.d[15]*1;
  residual += temp*temp;
  temp = work.KKT[22]-1*work.d[18]*1;
  residual += temp*temp;
  temp = work.KKT[25]-1*work.d[21]*1;
  residual += temp*temp;
  temp = work.KKT[28]-1*work.d[24]*1;
  residual += temp*temp;
  temp = work.KKT[31]-1*work.d[27]*1;
  residual += temp*temp;
  temp = work.KKT[34]-1*work.d[30]*1;
  residual += temp*temp;
  temp = work.KKT[37]-1*work.d[33]*1;
  residual += temp*temp;
  temp = work.KKT[0]-1*work.d[0]*1;
  residual += temp*temp;
  temp = work.KKT[2]-1*work.d[1]*1;
  residual += temp*temp;
  temp = work.KKT[1]-work.L[0]*work.d[0]*1;
  residual += temp*temp;
  temp = work.KKT[3]-work.L[2]*work.d[1]*1;
  residual += temp*temp;
  temp = work.KKT[4]-work.L[0]*work.d[0]*work.L[0]-1*work.d[2]*1;
  residual += temp*temp;
  temp = work.KKT[8]-work.L[2]*work.d[1]*work.L[2]-1*work.d[4]*1-work.L[3]*work.d[3]*work.L[3];
  residual += temp*temp;
  temp = work.KKT[5]-1*work.d[2]*work.L[1];
  residual += temp*temp;
  temp = work.KKT[7]-work.L[3]*work.d[3]*1;
  residual += temp*temp;
  temp = work.KKT[9]-work.L[4]*work.d[5]*1;
  residual += temp*temp;
  temp = work.KKT[11]-work.L[5]*work.d[6]*1;
  residual += temp*temp;
  temp = work.KKT[12]-work.L[6]*work.d[8]*1;
  residual += temp*temp;
  temp = work.KKT[14]-work.L[7]*work.d[9]*1;
  residual += temp*temp;
  temp = work.KKT[15]-work.L[8]*work.d[11]*1;
  residual += temp*temp;
  temp = work.KKT[17]-work.L[9]*work.d[12]*1;
  residual += temp*temp;
  temp = work.KKT[18]-work.L[10]*work.d[14]*1;
  residual += temp*temp;
  temp = work.KKT[20]-work.L[11]*work.d[15]*1;
  residual += temp*temp;
  temp = work.KKT[21]-work.L[12]*work.d[17]*1;
  residual += temp*temp;
  temp = work.KKT[23]-work.L[13]*work.d[18]*1;
  residual += temp*temp;
  temp = work.KKT[24]-work.L[14]*work.d[20]*1;
  residual += temp*temp;
  temp = work.KKT[26]-work.L[15]*work.d[21]*1;
  residual += temp*temp;
  temp = work.KKT[27]-work.L[16]*work.d[23]*1;
  residual += temp*temp;
  temp = work.KKT[29]-work.L[17]*work.d[24]*1;
  residual += temp*temp;
  temp = work.KKT[30]-work.L[18]*work.d[26]*1;
  residual += temp*temp;
  temp = work.KKT[32]-work.L[19]*work.d[27]*1;
  residual += temp*temp;
  temp = work.KKT[33]-work.L[20]*work.d[29]*1;
  residual += temp*temp;
  temp = work.KKT[35]-work.L[21]*work.d[30]*1;
  residual += temp*temp;
  temp = work.KKT[36]-work.L[22]*work.d[32]*1;
  residual += temp*temp;
  temp = work.KKT[38]-work.L[23]*work.d[33]*1;
  residual += temp*temp;
  return residual;
}
void Gensolver::matrix_multiply(double *result, double *source) {
  /* Finds result = A*source. */
  result[0] = work.KKT[6]*source[0]+work.KKT[5]*source[23]+work.KKT[7]*source[24];
  result[1] = work.KKT[9]*source[25];
  result[2] = work.KKT[12]*source[26];
  result[3] = work.KKT[15]*source[27];
  result[4] = work.KKT[18]*source[28];
  result[5] = work.KKT[21]*source[29];
  result[6] = work.KKT[24]*source[30];
  result[7] = work.KKT[27]*source[31];
  result[8] = work.KKT[30]*source[32];
  result[9] = work.KKT[33]*source[33];
  result[10] = work.KKT[36]*source[34];
  result[11] = work.KKT[10]*source[11]+work.KKT[11]*source[25];
  result[12] = work.KKT[13]*source[12]+work.KKT[14]*source[26];
  result[13] = work.KKT[16]*source[13]+work.KKT[17]*source[27];
  result[14] = work.KKT[19]*source[14]+work.KKT[20]*source[28];
  result[15] = work.KKT[22]*source[15]+work.KKT[23]*source[29];
  result[16] = work.KKT[25]*source[16]+work.KKT[26]*source[30];
  result[17] = work.KKT[28]*source[17]+work.KKT[29]*source[31];
  result[18] = work.KKT[31]*source[18]+work.KKT[32]*source[32];
  result[19] = work.KKT[34]*source[19]+work.KKT[35]*source[33];
  result[20] = work.KKT[37]*source[20]+work.KKT[38]*source[34];
  result[21] = work.KKT[0]*source[21]+work.KKT[1]*source[23];
  result[22] = work.KKT[2]*source[22]+work.KKT[3]*source[24];
  result[23] = work.KKT[1]*source[21]+work.KKT[4]*source[23]+work.KKT[5]*source[0];
  result[24] = work.KKT[3]*source[22]+work.KKT[8]*source[24]+work.KKT[7]*source[0];
  result[25] = work.KKT[9]*source[1]+work.KKT[11]*source[11];
  result[26] = work.KKT[12]*source[2]+work.KKT[14]*source[12];
  result[27] = work.KKT[15]*source[3]+work.KKT[17]*source[13];
  result[28] = work.KKT[18]*source[4]+work.KKT[20]*source[14];
  result[29] = work.KKT[21]*source[5]+work.KKT[23]*source[15];
  result[30] = work.KKT[24]*source[6]+work.KKT[26]*source[16];
  result[31] = work.KKT[27]*source[7]+work.KKT[29]*source[17];
  result[32] = work.KKT[30]*source[8]+work.KKT[32]*source[18];
  result[33] = work.KKT[33]*source[9]+work.KKT[35]*source[19];
  result[34] = work.KKT[36]*source[10]+work.KKT[38]*source[20];
}
double Gensolver::check_residual(double *target, double *multiplicand) {
  /* Returns the squared 2-norm of lhs - A*rhs. */
  /* Reuses v to find the residual. */
  int i;
  double residual;
  residual = 0;
  matrix_multiply(work.v, multiplicand);
  for (i = 0; i < 21; i++) {
    residual += (target[i] - work.v[i])*(target[i] - work.v[i]);
  }
  return residual;
}
void Gensolver::fill_KKT(void) {
  work.KKT[6] = 2*(params.c2[0]+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848);
  work.KKT[10] = 2*work.frac_121674190848;
  work.KKT[13] = 2*work.frac_121674190848;
  work.KKT[16] = 2*work.frac_121674190848;
  work.KKT[19] = 2*work.frac_121674190848;
  work.KKT[22] = 2*work.frac_121674190848;
  work.KKT[25] = 2*work.frac_121674190848;
  work.KKT[28] = 2*work.frac_121674190848;
  work.KKT[31] = 2*work.frac_121674190848;
  work.KKT[34] = 2*work.frac_121674190848;
  work.KKT[37] = 2*work.frac_121674190848;
  work.KKT[0] = work.s_inv_z[0];
  work.KKT[2] = work.s_inv_z[1];
  work.KKT[1] = 1;
  work.KKT[3] = 1;
  work.KKT[4] = work.block_33[0];
  work.KKT[8] = work.block_33[0];
  work.KKT[5] = -1;
  work.KKT[7] = 1;
  work.KKT[9] = 1;
  work.KKT[11] = -1;
  work.KKT[12] = 1;
  work.KKT[14] = -1;
  work.KKT[15] = 1;
  work.KKT[17] = -1;
  work.KKT[18] = 1;
  work.KKT[20] = -1;
  work.KKT[21] = 1;
  work.KKT[23] = -1;
  work.KKT[24] = 1;
  work.KKT[26] = -1;
  work.KKT[27] = 1;
  work.KKT[29] = -1;
  work.KKT[30] = 1;
  work.KKT[32] = -1;
  work.KKT[33] = 1;
  work.KKT[35] = -1;
  work.KKT[36] = 1;
  work.KKT[38] = -1;
}

//testsolver.cpp
/* Produced by CVXGEN, 2015-02-06 22:35:37 -0500.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: testsolver.c. */
/* Description: Basic test harness for solver.c. */

//Vars vars;
//Params params;
//Workspace work;
//Settings settings;
Gensolver::Gensolver( int numberOfCases, double cost2, double cost1, double cost0, double PgenMax, double PgenMin ) {
  params.caseNumber = numberOfCases; // for future
  params.c2[0] = cost2;
  params.c1[0] = cost1;
  params.c0[0] = cost0;
  params.rho[0] = 1.0;
  params.PgMin[0] = PgenMin;
  params.PgMax[0] = PgenMax;
for ( int i = 0; i <= 9; ++i ) {
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
  load_default_data(gsRho, Pgprev, Pgavrg, Pprice, Apriceavg, Aavg, Aprice);
  /* Solve problem instance for the record. */
  settings.verbose = 1;
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
for ( int i = 0; i <= 9; ++i ) {
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
 //cout << "\nPiterate: " << *Piterate << endl;
 return *Piterate;
}

double Gensolver::getObj(void) {
 return (params.c2[0])*(*Piterate)*(*Piterate)+(params.c1[0])*(*Piterate)+(params.c0[0]);
}

double Gensolver::getThetaSol(void) {
 Thiterate = (vars.Thetag);
 //cout << "\nThiterate: " << *Thiterate << endl;
 return *Thiterate;
}