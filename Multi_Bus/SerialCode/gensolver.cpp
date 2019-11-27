//solver.cpp
/* Produced by CVXGEN, 2015-03-30 04:02:40 -0400.  */
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
  settings.verbose = 0;
  settings.verbose_refinement = 0;
  settings.better_start = 1;
  settings.kkt_reg = 1e-7;
}
void Gensolver::setup_pointers(void) {
  work.y = work.x + 402;
  work.s = work.x + 402;
  work.z = work.x + 404;
  vars.Pg = work.x + 0;
  vars.Thetag = work.x + 1;
}
void Gensolver::setup_indexing(void) {
  setup_pointers();
}
void Gensolver::set_start(void) {
  int i;
  for (i = 0; i < 402; i++)
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
  for (i = 0; i < 402; i++)
    objv += work.x[i]*work.rhs[i];
  objv *= 0.5;
  for (i = 0; i < 402; i++)
    objv += work.q[i]*work.x[i];
  objv += params.c0[0]+work.quad_551453212672[0]+work.quad_591828860928[0];
  return objv;
}
void Gensolver::fillrhs_aff(void) {
  int i;
  double *r1, *r2, *r3, *r4;
  r1 = work.rhs;
  r2 = work.rhs + 402;
  r3 = work.rhs + 404;
  r4 = work.rhs + 406;
  /* r1 = -A^Ty - G^Tz - Px - q. */
  multbymAT(r1, work.y);
  multbymGT(work.buffer, work.z);
  for (i = 0; i < 402; i++)
    r1[i] += work.buffer[i];
  multbyP(work.buffer, work.x);
  for (i = 0; i < 402; i++)
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
  r2 = work.rhs + 402;
  ds_aff = work.lhs_aff + 402;
  dz_aff = work.lhs_aff + 404;
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
  for (i = 0; i < 402; i++)
    work.rhs[i] = 0;
  for (i = 404; i < 406; i++)
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
    for (i = 0; i < 406; i++) {
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
    for (i = 0; i < 406; i++) {
      var[i] -= new_var[i];
    }
  }
#ifndef ZERO_LIBRARY_MODE
  if (settings.verbose_refinement) {
    /* Check the residual once more, but only if we're reporting it, since */
    /* it's expensive. */
    norm2 = 0;
    matrix_multiply(residual, var);
    for (i = 0; i < 406; i++) {
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
  s = work.lhs_aff + 402;
  z = work.lhs_aff + 404;
  y = work.lhs_aff + 406;
  /* Just set x and y as is. */
  for (i = 0; i < 402; i++)
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
  r2 = work.rhs + 402;
  r3 = work.rhs + 404;
  r4 = work.rhs + 406;
  for (i = 0; i < 402; i++)
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
    for (i = 0; i < 406; i++)
      work.lhs_aff[i] += work.lhs_cc[i];
    /* Rename aff to reflect its new meaning. */
    dx = work.lhs_aff;
    ds = work.lhs_aff + 402;
    dz = work.lhs_aff + 404;
    dy = work.lhs_aff + 406;
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
    for (i = 0; i < 402; i++)
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

//util.cpp
/* Produced by CVXGEN, 2015-03-30 04:02:40 -0400.  */
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
/* Produced by CVXGEN, 2015-03-30 04:00:23 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: matrix_support.c. */
/* Description: Support functions for matrix multiplication and vector filling. */

void Gensolver::multbymA(double *lhs, double *rhs) {
}
void Gensolver::multbymAT(double *lhs, double *rhs) {
for ( int i =0; i <= 401; ++i ) 
  lhs[i] = 0;
}
void Gensolver::multbymG(double *lhs, double *rhs) {
  lhs[0] = -rhs[0]*(-1);
  lhs[1] = -rhs[0]*(1);
}
void Gensolver::multbymGT(double *lhs, double *rhs) {
  lhs[0] = -rhs[0]*(-1)-rhs[1]*(1);
for ( int i = 1; i <= 401; ++i )
  lhs[i] = 0;
}
void Gensolver::multbyP(double *lhs, double *rhs) {
  /* TODO use the fact that P is symmetric? */
  /* TODO check doubling / half factor etc. */
  lhs[0] = rhs[0]*(2*(params.c2[0]+work.quad_530423889920[0]+work.frac_121674190848*params.contNum[0]));
for ( int i = 1; i <= 401; ++i )
  lhs[i] = rhs[i]*(2*work.frac_121674190848);
}
void Gensolver::fillq(void) {
  work.q[0] = params.c1[0]+2*work.frac_121674190848*((-params.Pg_N_init[0]+params.Pg_N_avg[0]+params.ug_N[0])*params.ones[0]+(-params.Pg_N_init[1]+params.Pg_N_avg[1]+params.ug_N[1])*params.ones[1]+(-params.Pg_N_init[2]+params.Pg_N_avg[2]+params.ug_N[2])*params.ones[2]+(-params.Pg_N_init[3]+params.Pg_N_avg[3]+params.ug_N[3])*params.ones[3]+(-params.Pg_N_init[4]+params.Pg_N_avg[4]+params.ug_N[4])*params.ones[4]+(-params.Pg_N_init[5]+params.Pg_N_avg[5]+params.ug_N[5])*params.ones[5]+(-params.Pg_N_init[6]+params.Pg_N_avg[6]+params.ug_N[6])*params.ones[6]+(-params.Pg_N_init[7]+params.Pg_N_avg[7]+params.ug_N[7])*params.ones[7]+(-params.Pg_N_init[8]+params.Pg_N_avg[8]+params.ug_N[8])*params.ones[8]+(-params.Pg_N_init[9]+params.Pg_N_avg[9]+params.ug_N[9])*params.ones[9]+(-params.Pg_N_init[10]+params.Pg_N_avg[10]+params.ug_N[10])*params.ones[10]+(-params.Pg_N_init[11]+params.Pg_N_avg[11]+params.ug_N[11])*params.ones[11]+(-params.Pg_N_init[12]+params.Pg_N_avg[12]+params.ug_N[12])*params.ones[12]+(-params.Pg_N_init[13]+params.Pg_N_avg[13]+params.ug_N[13])*params.ones[13]+(-params.Pg_N_init[14]+params.Pg_N_avg[14]+params.ug_N[14])*params.ones[14]+(-params.Pg_N_init[15]+params.Pg_N_avg[15]+params.ug_N[15])*params.ones[15]+(-params.Pg_N_init[16]+params.Pg_N_avg[16]+params.ug_N[16])*params.ones[16]+(-params.Pg_N_init[17]+params.Pg_N_avg[17]+params.ug_N[17])*params.ones[17]+(-params.Pg_N_init[18]+params.Pg_N_avg[18]+params.ug_N[18])*params.ones[18]+(-params.Pg_N_init[19]+params.Pg_N_avg[19]+params.ug_N[19])*params.ones[19]+(-params.Pg_N_init[20]+params.Pg_N_avg[20]+params.ug_N[20])*params.ones[20]+(-params.Pg_N_init[21]+params.Pg_N_avg[21]+params.ug_N[21])*params.ones[21]+(-params.Pg_N_init[22]+params.Pg_N_avg[22]+params.ug_N[22])*params.ones[22]+(-params.Pg_N_init[23]+params.Pg_N_avg[23]+params.ug_N[23])*params.ones[23]+(-params.Pg_N_init[24]+params.Pg_N_avg[24]+params.ug_N[24])*params.ones[24]+(-params.Pg_N_init[25]+params.Pg_N_avg[25]+params.ug_N[25])*params.ones[25]+(-params.Pg_N_init[26]+params.Pg_N_avg[26]+params.ug_N[26])*params.ones[26]+(-params.Pg_N_init[27]+params.Pg_N_avg[27]+params.ug_N[27])*params.ones[27]+(-params.Pg_N_init[28]+params.Pg_N_avg[28]+params.ug_N[28])*params.ones[28]+(-params.Pg_N_init[29]+params.Pg_N_avg[29]+params.ug_N[29])*params.ones[29]+(-params.Pg_N_init[30]+params.Pg_N_avg[30]+params.ug_N[30])*params.ones[30]+(-params.Pg_N_init[31]+params.Pg_N_avg[31]+params.ug_N[31])*params.ones[31]+(-params.Pg_N_init[32]+params.Pg_N_avg[32]+params.ug_N[32])*params.ones[32]+(-params.Pg_N_init[33]+params.Pg_N_avg[33]+params.ug_N[33])*params.ones[33]+(-params.Pg_N_init[34]+params.Pg_N_avg[34]+params.ug_N[34])*params.ones[34]+(-params.Pg_N_init[35]+params.Pg_N_avg[35]+params.ug_N[35])*params.ones[35]+(-params.Pg_N_init[36]+params.Pg_N_avg[36]+params.ug_N[36])*params.ones[36]+(-params.Pg_N_init[37]+params.Pg_N_avg[37]+params.ug_N[37])*params.ones[37]+(-params.Pg_N_init[38]+params.Pg_N_avg[38]+params.ug_N[38])*params.ones[38]+(-params.Pg_N_init[39]+params.Pg_N_avg[39]+params.ug_N[39])*params.ones[39]+(-params.Pg_N_init[40]+params.Pg_N_avg[40]+params.ug_N[40])*params.ones[40]+(-params.Pg_N_init[41]+params.Pg_N_avg[41]+params.ug_N[41])*params.ones[41]+(-params.Pg_N_init[42]+params.Pg_N_avg[42]+params.ug_N[42])*params.ones[42]+(-params.Pg_N_init[43]+params.Pg_N_avg[43]+params.ug_N[43])*params.ones[43]+(-params.Pg_N_init[44]+params.Pg_N_avg[44]+params.ug_N[44])*params.ones[44]+(-params.Pg_N_init[45]+params.Pg_N_avg[45]+params.ug_N[45])*params.ones[45]+(-params.Pg_N_init[46]+params.Pg_N_avg[46]+params.ug_N[46])*params.ones[46]+(-params.Pg_N_init[47]+params.Pg_N_avg[47]+params.ug_N[47])*params.ones[47]+(-params.Pg_N_init[48]+params.Pg_N_avg[48]+params.ug_N[48])*params.ones[48]+(-params.Pg_N_init[49]+params.Pg_N_avg[49]+params.ug_N[49])*params.ones[49]+(-params.Pg_N_init[50]+params.Pg_N_avg[50]+params.ug_N[50])*params.ones[50]+(-params.Pg_N_init[51]+params.Pg_N_avg[51]+params.ug_N[51])*params.ones[51]+(-params.Pg_N_init[52]+params.Pg_N_avg[52]+params.ug_N[52])*params.ones[52]+(-params.Pg_N_init[53]+params.Pg_N_avg[53]+params.ug_N[53])*params.ones[53]+(-params.Pg_N_init[54]+params.Pg_N_avg[54]+params.ug_N[54])*params.ones[54]+(-params.Pg_N_init[55]+params.Pg_N_avg[55]+params.ug_N[55])*params.ones[55]+(-params.Pg_N_init[56]+params.Pg_N_avg[56]+params.ug_N[56])*params.ones[56]+(-params.Pg_N_init[57]+params.Pg_N_avg[57]+params.ug_N[57])*params.ones[57]+(-params.Pg_N_init[58]+params.Pg_N_avg[58]+params.ug_N[58])*params.ones[58]+(-params.Pg_N_init[59]+params.Pg_N_avg[59]+params.ug_N[59])*params.ones[59]+(-params.Pg_N_init[60]+params.Pg_N_avg[60]+params.ug_N[60])*params.ones[60]+(-params.Pg_N_init[61]+params.Pg_N_avg[61]+params.ug_N[61])*params.ones[61]+(-params.Pg_N_init[62]+params.Pg_N_avg[62]+params.ug_N[62])*params.ones[62]+(-params.Pg_N_init[63]+params.Pg_N_avg[63]+params.ug_N[63])*params.ones[63]+(-params.Pg_N_init[64]+params.Pg_N_avg[64]+params.ug_N[64])*params.ones[64]+(-params.Pg_N_init[65]+params.Pg_N_avg[65]+params.ug_N[65])*params.ones[65]+(-params.Pg_N_init[66]+params.Pg_N_avg[66]+params.ug_N[66])*params.ones[66]+(-params.Pg_N_init[67]+params.Pg_N_avg[67]+params.ug_N[67])*params.ones[67]+(-params.Pg_N_init[68]+params.Pg_N_avg[68]+params.ug_N[68])*params.ones[68]+(-params.Pg_N_init[69]+params.Pg_N_avg[69]+params.ug_N[69])*params.ones[69]+(-params.Pg_N_init[70]+params.Pg_N_avg[70]+params.ug_N[70])*params.ones[70]+(-params.Pg_N_init[71]+params.Pg_N_avg[71]+params.ug_N[71])*params.ones[71]+(-params.Pg_N_init[72]+params.Pg_N_avg[72]+params.ug_N[72])*params.ones[72]+(-params.Pg_N_init[73]+params.Pg_N_avg[73]+params.ug_N[73])*params.ones[73]+(-params.Pg_N_init[74]+params.Pg_N_avg[74]+params.ug_N[74])*params.ones[74]+(-params.Pg_N_init[75]+params.Pg_N_avg[75]+params.ug_N[75])*params.ones[75]+(-params.Pg_N_init[76]+params.Pg_N_avg[76]+params.ug_N[76])*params.ones[76]+(-params.Pg_N_init[77]+params.Pg_N_avg[77]+params.ug_N[77])*params.ones[77]+(-params.Pg_N_init[78]+params.Pg_N_avg[78]+params.ug_N[78])*params.ones[78]+(-params.Pg_N_init[79]+params.Pg_N_avg[79]+params.ug_N[79])*params.ones[79]+(-params.Pg_N_init[80]+params.Pg_N_avg[80]+params.ug_N[80])*params.ones[80]+(-params.Pg_N_init[81]+params.Pg_N_avg[81]+params.ug_N[81])*params.ones[81]+(-params.Pg_N_init[82]+params.Pg_N_avg[82]+params.ug_N[82])*params.ones[82]+(-params.Pg_N_init[83]+params.Pg_N_avg[83]+params.ug_N[83])*params.ones[83]+(-params.Pg_N_init[84]+params.Pg_N_avg[84]+params.ug_N[84])*params.ones[84]+(-params.Pg_N_init[85]+params.Pg_N_avg[85]+params.ug_N[85])*params.ones[85]+(-params.Pg_N_init[86]+params.Pg_N_avg[86]+params.ug_N[86])*params.ones[86]+(-params.Pg_N_init[87]+params.Pg_N_avg[87]+params.ug_N[87])*params.ones[87]+(-params.Pg_N_init[88]+params.Pg_N_avg[88]+params.ug_N[88])*params.ones[88]+(-params.Pg_N_init[89]+params.Pg_N_avg[89]+params.ug_N[89])*params.ones[89]+(-params.Pg_N_init[90]+params.Pg_N_avg[90]+params.ug_N[90])*params.ones[90]+(-params.Pg_N_init[91]+params.Pg_N_avg[91]+params.ug_N[91])*params.ones[91]+(-params.Pg_N_init[92]+params.Pg_N_avg[92]+params.ug_N[92])*params.ones[92]+(-params.Pg_N_init[93]+params.Pg_N_avg[93]+params.ug_N[93])*params.ones[93]+(-params.Pg_N_init[94]+params.Pg_N_avg[94]+params.ug_N[94])*params.ones[94]+(-params.Pg_N_init[95]+params.Pg_N_avg[95]+params.ug_N[95])*params.ones[95]+(-params.Pg_N_init[96]+params.Pg_N_avg[96]+params.ug_N[96])*params.ones[96]+(-params.Pg_N_init[97]+params.Pg_N_avg[97]+params.ug_N[97])*params.ones[97]+(-params.Pg_N_init[98]+params.Pg_N_avg[98]+params.ug_N[98])*params.ones[98]+(-params.Pg_N_init[99]+params.Pg_N_avg[99]+params.ug_N[99])*params.ones[99]+(-params.Pg_N_init[100]+params.Pg_N_avg[100]+params.ug_N[100])*params.ones[100]+(-params.Pg_N_init[101]+params.Pg_N_avg[101]+params.ug_N[101])*params.ones[101]+(-params.Pg_N_init[102]+params.Pg_N_avg[102]+params.ug_N[102])*params.ones[102]+(-params.Pg_N_init[103]+params.Pg_N_avg[103]+params.ug_N[103])*params.ones[103]+(-params.Pg_N_init[104]+params.Pg_N_avg[104]+params.ug_N[104])*params.ones[104]+(-params.Pg_N_init[105]+params.Pg_N_avg[105]+params.ug_N[105])*params.ones[105]+(-params.Pg_N_init[106]+params.Pg_N_avg[106]+params.ug_N[106])*params.ones[106]+(-params.Pg_N_init[107]+params.Pg_N_avg[107]+params.ug_N[107])*params.ones[107]+(-params.Pg_N_init[108]+params.Pg_N_avg[108]+params.ug_N[108])*params.ones[108]+(-params.Pg_N_init[109]+params.Pg_N_avg[109]+params.ug_N[109])*params.ones[109]+(-params.Pg_N_init[110]+params.Pg_N_avg[110]+params.ug_N[110])*params.ones[110]+(-params.Pg_N_init[111]+params.Pg_N_avg[111]+params.ug_N[111])*params.ones[111]+(-params.Pg_N_init[112]+params.Pg_N_avg[112]+params.ug_N[112])*params.ones[112]+(-params.Pg_N_init[113]+params.Pg_N_avg[113]+params.ug_N[113])*params.ones[113]+(-params.Pg_N_init[114]+params.Pg_N_avg[114]+params.ug_N[114])*params.ones[114]+(-params.Pg_N_init[115]+params.Pg_N_avg[115]+params.ug_N[115])*params.ones[115]+(-params.Pg_N_init[116]+params.Pg_N_avg[116]+params.ug_N[116])*params.ones[116]+(-params.Pg_N_init[117]+params.Pg_N_avg[117]+params.ug_N[117])*params.ones[117]+(-params.Pg_N_init[118]+params.Pg_N_avg[118]+params.ug_N[118])*params.ones[118]+(-params.Pg_N_init[119]+params.Pg_N_avg[119]+params.ug_N[119])*params.ones[119]+(-params.Pg_N_init[120]+params.Pg_N_avg[120]+params.ug_N[120])*params.ones[120]+(-params.Pg_N_init[121]+params.Pg_N_avg[121]+params.ug_N[121])*params.ones[121]+(-params.Pg_N_init[122]+params.Pg_N_avg[122]+params.ug_N[122])*params.ones[122]+(-params.Pg_N_init[123]+params.Pg_N_avg[123]+params.ug_N[123])*params.ones[123]+(-params.Pg_N_init[124]+params.Pg_N_avg[124]+params.ug_N[124])*params.ones[124]+(-params.Pg_N_init[125]+params.Pg_N_avg[125]+params.ug_N[125])*params.ones[125]+(-params.Pg_N_init[126]+params.Pg_N_avg[126]+params.ug_N[126])*params.ones[126]+(-params.Pg_N_init[127]+params.Pg_N_avg[127]+params.ug_N[127])*params.ones[127]+(-params.Pg_N_init[128]+params.Pg_N_avg[128]+params.ug_N[128])*params.ones[128]+(-params.Pg_N_init[129]+params.Pg_N_avg[129]+params.ug_N[129])*params.ones[129]+(-params.Pg_N_init[130]+params.Pg_N_avg[130]+params.ug_N[130])*params.ones[130]+(-params.Pg_N_init[131]+params.Pg_N_avg[131]+params.ug_N[131])*params.ones[131]+(-params.Pg_N_init[132]+params.Pg_N_avg[132]+params.ug_N[132])*params.ones[132]+(-params.Pg_N_init[133]+params.Pg_N_avg[133]+params.ug_N[133])*params.ones[133]+(-params.Pg_N_init[134]+params.Pg_N_avg[134]+params.ug_N[134])*params.ones[134]+(-params.Pg_N_init[135]+params.Pg_N_avg[135]+params.ug_N[135])*params.ones[135]+(-params.Pg_N_init[136]+params.Pg_N_avg[136]+params.ug_N[136])*params.ones[136]+(-params.Pg_N_init[137]+params.Pg_N_avg[137]+params.ug_N[137])*params.ones[137]+(-params.Pg_N_init[138]+params.Pg_N_avg[138]+params.ug_N[138])*params.ones[138]+(-params.Pg_N_init[139]+params.Pg_N_avg[139]+params.ug_N[139])*params.ones[139]+(-params.Pg_N_init[140]+params.Pg_N_avg[140]+params.ug_N[140])*params.ones[140]+(-params.Pg_N_init[141]+params.Pg_N_avg[141]+params.ug_N[141])*params.ones[141]+(-params.Pg_N_init[142]+params.Pg_N_avg[142]+params.ug_N[142])*params.ones[142]+(-params.Pg_N_init[143]+params.Pg_N_avg[143]+params.ug_N[143])*params.ones[143]+(-params.Pg_N_init[144]+params.Pg_N_avg[144]+params.ug_N[144])*params.ones[144]+(-params.Pg_N_init[145]+params.Pg_N_avg[145]+params.ug_N[145])*params.ones[145]+(-params.Pg_N_init[146]+params.Pg_N_avg[146]+params.ug_N[146])*params.ones[146]+(-params.Pg_N_init[147]+params.Pg_N_avg[147]+params.ug_N[147])*params.ones[147]+(-params.Pg_N_init[148]+params.Pg_N_avg[148]+params.ug_N[148])*params.ones[148]+(-params.Pg_N_init[149]+params.Pg_N_avg[149]+params.ug_N[149])*params.ones[149]+(-params.Pg_N_init[150]+params.Pg_N_avg[150]+params.ug_N[150])*params.ones[150]+(-params.Pg_N_init[151]+params.Pg_N_avg[151]+params.ug_N[151])*params.ones[151]+(-params.Pg_N_init[152]+params.Pg_N_avg[152]+params.ug_N[152])*params.ones[152]+(-params.Pg_N_init[153]+params.Pg_N_avg[153]+params.ug_N[153])*params.ones[153]+(-params.Pg_N_init[154]+params.Pg_N_avg[154]+params.ug_N[154])*params.ones[154]+(-params.Pg_N_init[155]+params.Pg_N_avg[155]+params.ug_N[155])*params.ones[155]+(-params.Pg_N_init[156]+params.Pg_N_avg[156]+params.ug_N[156])*params.ones[156]+(-params.Pg_N_init[157]+params.Pg_N_avg[157]+params.ug_N[157])*params.ones[157]+(-params.Pg_N_init[158]+params.Pg_N_avg[158]+params.ug_N[158])*params.ones[158]+(-params.Pg_N_init[159]+params.Pg_N_avg[159]+params.ug_N[159])*params.ones[159]+(-params.Pg_N_init[160]+params.Pg_N_avg[160]+params.ug_N[160])*params.ones[160]+(-params.Pg_N_init[161]+params.Pg_N_avg[161]+params.ug_N[161])*params.ones[161]+(-params.Pg_N_init[162]+params.Pg_N_avg[162]+params.ug_N[162])*params.ones[162]+(-params.Pg_N_init[163]+params.Pg_N_avg[163]+params.ug_N[163])*params.ones[163]+(-params.Pg_N_init[164]+params.Pg_N_avg[164]+params.ug_N[164])*params.ones[164]+(-params.Pg_N_init[165]+params.Pg_N_avg[165]+params.ug_N[165])*params.ones[165]+(-params.Pg_N_init[166]+params.Pg_N_avg[166]+params.ug_N[166])*params.ones[166]+(-params.Pg_N_init[167]+params.Pg_N_avg[167]+params.ug_N[167])*params.ones[167]+(-params.Pg_N_init[168]+params.Pg_N_avg[168]+params.ug_N[168])*params.ones[168]+(-params.Pg_N_init[169]+params.Pg_N_avg[169]+params.ug_N[169])*params.ones[169]+(-params.Pg_N_init[170]+params.Pg_N_avg[170]+params.ug_N[170])*params.ones[170]+(-params.Pg_N_init[171]+params.Pg_N_avg[171]+params.ug_N[171])*params.ones[171]+(-params.Pg_N_init[172]+params.Pg_N_avg[172]+params.ug_N[172])*params.ones[172]+(-params.Pg_N_init[173]+params.Pg_N_avg[173]+params.ug_N[173])*params.ones[173]+(-params.Pg_N_init[174]+params.Pg_N_avg[174]+params.ug_N[174])*params.ones[174]+(-params.Pg_N_init[175]+params.Pg_N_avg[175]+params.ug_N[175])*params.ones[175]+(-params.Pg_N_init[176]+params.Pg_N_avg[176]+params.ug_N[176])*params.ones[176]+(-params.Pg_N_init[177]+params.Pg_N_avg[177]+params.ug_N[177])*params.ones[177]+(-params.Pg_N_init[178]+params.Pg_N_avg[178]+params.ug_N[178])*params.ones[178]+(-params.Pg_N_init[179]+params.Pg_N_avg[179]+params.ug_N[179])*params.ones[179]+(-params.Pg_N_init[180]+params.Pg_N_avg[180]+params.ug_N[180])*params.ones[180]+(-params.Pg_N_init[181]+params.Pg_N_avg[181]+params.ug_N[181])*params.ones[181]+(-params.Pg_N_init[182]+params.Pg_N_avg[182]+params.ug_N[182])*params.ones[182]+(-params.Pg_N_init[183]+params.Pg_N_avg[183]+params.ug_N[183])*params.ones[183]+(-params.Pg_N_init[184]+params.Pg_N_avg[184]+params.ug_N[184])*params.ones[184]+(-params.Pg_N_init[185]+params.Pg_N_avg[185]+params.ug_N[185])*params.ones[185]+(-params.Pg_N_init[186]+params.Pg_N_avg[186]+params.ug_N[186])*params.ones[186]+(-params.Pg_N_init[187]+params.Pg_N_avg[187]+params.ug_N[187])*params.ones[187]+(-params.Pg_N_init[188]+params.Pg_N_avg[188]+params.ug_N[188])*params.ones[188]+(-params.Pg_N_init[189]+params.Pg_N_avg[189]+params.ug_N[189])*params.ones[189]+(-params.Pg_N_init[190]+params.Pg_N_avg[190]+params.ug_N[190])*params.ones[190]+(-params.Pg_N_init[191]+params.Pg_N_avg[191]+params.ug_N[191])*params.ones[191]+(-params.Pg_N_init[192]+params.Pg_N_avg[192]+params.ug_N[192])*params.ones[192]+(-params.Pg_N_init[193]+params.Pg_N_avg[193]+params.ug_N[193])*params.ones[193]+(-params.Pg_N_init[194]+params.Pg_N_avg[194]+params.ug_N[194])*params.ones[194]+(-params.Pg_N_init[195]+params.Pg_N_avg[195]+params.ug_N[195])*params.ones[195]+(-params.Pg_N_init[196]+params.Pg_N_avg[196]+params.ug_N[196])*params.ones[196]+(-params.Pg_N_init[197]+params.Pg_N_avg[197]+params.ug_N[197])*params.ones[197]+(-params.Pg_N_init[198]+params.Pg_N_avg[198]+params.ug_N[198])*params.ones[198]+(-params.Pg_N_init[199]+params.Pg_N_avg[199]+params.ug_N[199])*params.ones[199]+(-params.Pg_N_init[200]+params.Pg_N_avg[200]+params.ug_N[200])*params.ones[200]+(-params.Pg_N_init[201]+params.Pg_N_avg[201]+params.ug_N[201])*params.ones[201]+(-params.Pg_N_init[202]+params.Pg_N_avg[202]+params.ug_N[202])*params.ones[202]+(-params.Pg_N_init[203]+params.Pg_N_avg[203]+params.ug_N[203])*params.ones[203]+(-params.Pg_N_init[204]+params.Pg_N_avg[204]+params.ug_N[204])*params.ones[204]+(-params.Pg_N_init[205]+params.Pg_N_avg[205]+params.ug_N[205])*params.ones[205]+(-params.Pg_N_init[206]+params.Pg_N_avg[206]+params.ug_N[206])*params.ones[206]+(-params.Pg_N_init[207]+params.Pg_N_avg[207]+params.ug_N[207])*params.ones[207]+(-params.Pg_N_init[208]+params.Pg_N_avg[208]+params.ug_N[208])*params.ones[208]+(-params.Pg_N_init[209]+params.Pg_N_avg[209]+params.ug_N[209])*params.ones[209]+(-params.Pg_N_init[210]+params.Pg_N_avg[210]+params.ug_N[210])*params.ones[210]+(-params.Pg_N_init[211]+params.Pg_N_avg[211]+params.ug_N[211])*params.ones[211]+(-params.Pg_N_init[212]+params.Pg_N_avg[212]+params.ug_N[212])*params.ones[212]+(-params.Pg_N_init[213]+params.Pg_N_avg[213]+params.ug_N[213])*params.ones[213]+(-params.Pg_N_init[214]+params.Pg_N_avg[214]+params.ug_N[214])*params.ones[214]+(-params.Pg_N_init[215]+params.Pg_N_avg[215]+params.ug_N[215])*params.ones[215]+(-params.Pg_N_init[216]+params.Pg_N_avg[216]+params.ug_N[216])*params.ones[216]+(-params.Pg_N_init[217]+params.Pg_N_avg[217]+params.ug_N[217])*params.ones[217]+(-params.Pg_N_init[218]+params.Pg_N_avg[218]+params.ug_N[218])*params.ones[218]+(-params.Pg_N_init[219]+params.Pg_N_avg[219]+params.ug_N[219])*params.ones[219]+(-params.Pg_N_init[220]+params.Pg_N_avg[220]+params.ug_N[220])*params.ones[220]+(-params.Pg_N_init[221]+params.Pg_N_avg[221]+params.ug_N[221])*params.ones[221]+(-params.Pg_N_init[222]+params.Pg_N_avg[222]+params.ug_N[222])*params.ones[222]+(-params.Pg_N_init[223]+params.Pg_N_avg[223]+params.ug_N[223])*params.ones[223]+(-params.Pg_N_init[224]+params.Pg_N_avg[224]+params.ug_N[224])*params.ones[224]+(-params.Pg_N_init[225]+params.Pg_N_avg[225]+params.ug_N[225])*params.ones[225]+(-params.Pg_N_init[226]+params.Pg_N_avg[226]+params.ug_N[226])*params.ones[226]+(-params.Pg_N_init[227]+params.Pg_N_avg[227]+params.ug_N[227])*params.ones[227]+(-params.Pg_N_init[228]+params.Pg_N_avg[228]+params.ug_N[228])*params.ones[228]+(-params.Pg_N_init[229]+params.Pg_N_avg[229]+params.ug_N[229])*params.ones[229]+(-params.Pg_N_init[230]+params.Pg_N_avg[230]+params.ug_N[230])*params.ones[230]+(-params.Pg_N_init[231]+params.Pg_N_avg[231]+params.ug_N[231])*params.ones[231]+(-params.Pg_N_init[232]+params.Pg_N_avg[232]+params.ug_N[232])*params.ones[232]+(-params.Pg_N_init[233]+params.Pg_N_avg[233]+params.ug_N[233])*params.ones[233]+(-params.Pg_N_init[234]+params.Pg_N_avg[234]+params.ug_N[234])*params.ones[234]+(-params.Pg_N_init[235]+params.Pg_N_avg[235]+params.ug_N[235])*params.ones[235]+(-params.Pg_N_init[236]+params.Pg_N_avg[236]+params.ug_N[236])*params.ones[236]+(-params.Pg_N_init[237]+params.Pg_N_avg[237]+params.ug_N[237])*params.ones[237]+(-params.Pg_N_init[238]+params.Pg_N_avg[238]+params.ug_N[238])*params.ones[238]+(-params.Pg_N_init[239]+params.Pg_N_avg[239]+params.ug_N[239])*params.ones[239]+(-params.Pg_N_init[240]+params.Pg_N_avg[240]+params.ug_N[240])*params.ones[240]+(-params.Pg_N_init[241]+params.Pg_N_avg[241]+params.ug_N[241])*params.ones[241]+(-params.Pg_N_init[242]+params.Pg_N_avg[242]+params.ug_N[242])*params.ones[242]+(-params.Pg_N_init[243]+params.Pg_N_avg[243]+params.ug_N[243])*params.ones[243]+(-params.Pg_N_init[244]+params.Pg_N_avg[244]+params.ug_N[244])*params.ones[244]+(-params.Pg_N_init[245]+params.Pg_N_avg[245]+params.ug_N[245])*params.ones[245]+(-params.Pg_N_init[246]+params.Pg_N_avg[246]+params.ug_N[246])*params.ones[246]+(-params.Pg_N_init[247]+params.Pg_N_avg[247]+params.ug_N[247])*params.ones[247]+(-params.Pg_N_init[248]+params.Pg_N_avg[248]+params.ug_N[248])*params.ones[248]+(-params.Pg_N_init[249]+params.Pg_N_avg[249]+params.ug_N[249])*params.ones[249]+(-params.Pg_N_init[250]+params.Pg_N_avg[250]+params.ug_N[250])*params.ones[250]+(-params.Pg_N_init[251]+params.Pg_N_avg[251]+params.ug_N[251])*params.ones[251]+(-params.Pg_N_init[252]+params.Pg_N_avg[252]+params.ug_N[252])*params.ones[252]+(-params.Pg_N_init[253]+params.Pg_N_avg[253]+params.ug_N[253])*params.ones[253]+(-params.Pg_N_init[254]+params.Pg_N_avg[254]+params.ug_N[254])*params.ones[254]+(-params.Pg_N_init[255]+params.Pg_N_avg[255]+params.ug_N[255])*params.ones[255]+(-params.Pg_N_init[256]+params.Pg_N_avg[256]+params.ug_N[256])*params.ones[256]+(-params.Pg_N_init[257]+params.Pg_N_avg[257]+params.ug_N[257])*params.ones[257]+(-params.Pg_N_init[258]+params.Pg_N_avg[258]+params.ug_N[258])*params.ones[258]+(-params.Pg_N_init[259]+params.Pg_N_avg[259]+params.ug_N[259])*params.ones[259]+(-params.Pg_N_init[260]+params.Pg_N_avg[260]+params.ug_N[260])*params.ones[260]+(-params.Pg_N_init[261]+params.Pg_N_avg[261]+params.ug_N[261])*params.ones[261]+(-params.Pg_N_init[262]+params.Pg_N_avg[262]+params.ug_N[262])*params.ones[262]+(-params.Pg_N_init[263]+params.Pg_N_avg[263]+params.ug_N[263])*params.ones[263]+(-params.Pg_N_init[264]+params.Pg_N_avg[264]+params.ug_N[264])*params.ones[264]+(-params.Pg_N_init[265]+params.Pg_N_avg[265]+params.ug_N[265])*params.ones[265]+(-params.Pg_N_init[266]+params.Pg_N_avg[266]+params.ug_N[266])*params.ones[266]+(-params.Pg_N_init[267]+params.Pg_N_avg[267]+params.ug_N[267])*params.ones[267]+(-params.Pg_N_init[268]+params.Pg_N_avg[268]+params.ug_N[268])*params.ones[268]+(-params.Pg_N_init[269]+params.Pg_N_avg[269]+params.ug_N[269])*params.ones[269]+(-params.Pg_N_init[270]+params.Pg_N_avg[270]+params.ug_N[270])*params.ones[270]+(-params.Pg_N_init[271]+params.Pg_N_avg[271]+params.ug_N[271])*params.ones[271]+(-params.Pg_N_init[272]+params.Pg_N_avg[272]+params.ug_N[272])*params.ones[272]+(-params.Pg_N_init[273]+params.Pg_N_avg[273]+params.ug_N[273])*params.ones[273]+(-params.Pg_N_init[274]+params.Pg_N_avg[274]+params.ug_N[274])*params.ones[274]+(-params.Pg_N_init[275]+params.Pg_N_avg[275]+params.ug_N[275])*params.ones[275]+(-params.Pg_N_init[276]+params.Pg_N_avg[276]+params.ug_N[276])*params.ones[276]+(-params.Pg_N_init[277]+params.Pg_N_avg[277]+params.ug_N[277])*params.ones[277]+(-params.Pg_N_init[278]+params.Pg_N_avg[278]+params.ug_N[278])*params.ones[278]+(-params.Pg_N_init[279]+params.Pg_N_avg[279]+params.ug_N[279])*params.ones[279]+(-params.Pg_N_init[280]+params.Pg_N_avg[280]+params.ug_N[280])*params.ones[280]+(-params.Pg_N_init[281]+params.Pg_N_avg[281]+params.ug_N[281])*params.ones[281]+(-params.Pg_N_init[282]+params.Pg_N_avg[282]+params.ug_N[282])*params.ones[282]+(-params.Pg_N_init[283]+params.Pg_N_avg[283]+params.ug_N[283])*params.ones[283]+(-params.Pg_N_init[284]+params.Pg_N_avg[284]+params.ug_N[284])*params.ones[284]+(-params.Pg_N_init[285]+params.Pg_N_avg[285]+params.ug_N[285])*params.ones[285]+(-params.Pg_N_init[286]+params.Pg_N_avg[286]+params.ug_N[286])*params.ones[286]+(-params.Pg_N_init[287]+params.Pg_N_avg[287]+params.ug_N[287])*params.ones[287]+(-params.Pg_N_init[288]+params.Pg_N_avg[288]+params.ug_N[288])*params.ones[288]+(-params.Pg_N_init[289]+params.Pg_N_avg[289]+params.ug_N[289])*params.ones[289]+(-params.Pg_N_init[290]+params.Pg_N_avg[290]+params.ug_N[290])*params.ones[290]+(-params.Pg_N_init[291]+params.Pg_N_avg[291]+params.ug_N[291])*params.ones[291]+(-params.Pg_N_init[292]+params.Pg_N_avg[292]+params.ug_N[292])*params.ones[292]+(-params.Pg_N_init[293]+params.Pg_N_avg[293]+params.ug_N[293])*params.ones[293]+(-params.Pg_N_init[294]+params.Pg_N_avg[294]+params.ug_N[294])*params.ones[294]+(-params.Pg_N_init[295]+params.Pg_N_avg[295]+params.ug_N[295])*params.ones[295]+(-params.Pg_N_init[296]+params.Pg_N_avg[296]+params.ug_N[296])*params.ones[296]+(-params.Pg_N_init[297]+params.Pg_N_avg[297]+params.ug_N[297])*params.ones[297]+(-params.Pg_N_init[298]+params.Pg_N_avg[298]+params.ug_N[298])*params.ones[298]+(-params.Pg_N_init[299]+params.Pg_N_avg[299]+params.ug_N[299])*params.ones[299]+(-params.Pg_N_init[300]+params.Pg_N_avg[300]+params.ug_N[300])*params.ones[300]+(-params.Pg_N_init[301]+params.Pg_N_avg[301]+params.ug_N[301])*params.ones[301]+(-params.Pg_N_init[302]+params.Pg_N_avg[302]+params.ug_N[302])*params.ones[302]+(-params.Pg_N_init[303]+params.Pg_N_avg[303]+params.ug_N[303])*params.ones[303]+(-params.Pg_N_init[304]+params.Pg_N_avg[304]+params.ug_N[304])*params.ones[304]+(-params.Pg_N_init[305]+params.Pg_N_avg[305]+params.ug_N[305])*params.ones[305]+(-params.Pg_N_init[306]+params.Pg_N_avg[306]+params.ug_N[306])*params.ones[306]+(-params.Pg_N_init[307]+params.Pg_N_avg[307]+params.ug_N[307])*params.ones[307]+(-params.Pg_N_init[308]+params.Pg_N_avg[308]+params.ug_N[308])*params.ones[308]+(-params.Pg_N_init[309]+params.Pg_N_avg[309]+params.ug_N[309])*params.ones[309]+(-params.Pg_N_init[310]+params.Pg_N_avg[310]+params.ug_N[310])*params.ones[310]+(-params.Pg_N_init[311]+params.Pg_N_avg[311]+params.ug_N[311])*params.ones[311]+(-params.Pg_N_init[312]+params.Pg_N_avg[312]+params.ug_N[312])*params.ones[312]+(-params.Pg_N_init[313]+params.Pg_N_avg[313]+params.ug_N[313])*params.ones[313]+(-params.Pg_N_init[314]+params.Pg_N_avg[314]+params.ug_N[314])*params.ones[314]+(-params.Pg_N_init[315]+params.Pg_N_avg[315]+params.ug_N[315])*params.ones[315]+(-params.Pg_N_init[316]+params.Pg_N_avg[316]+params.ug_N[316])*params.ones[316]+(-params.Pg_N_init[317]+params.Pg_N_avg[317]+params.ug_N[317])*params.ones[317]+(-params.Pg_N_init[318]+params.Pg_N_avg[318]+params.ug_N[318])*params.ones[318]+(-params.Pg_N_init[319]+params.Pg_N_avg[319]+params.ug_N[319])*params.ones[319]+(-params.Pg_N_init[320]+params.Pg_N_avg[320]+params.ug_N[320])*params.ones[320]+(-params.Pg_N_init[321]+params.Pg_N_avg[321]+params.ug_N[321])*params.ones[321]+(-params.Pg_N_init[322]+params.Pg_N_avg[322]+params.ug_N[322])*params.ones[322]+(-params.Pg_N_init[323]+params.Pg_N_avg[323]+params.ug_N[323])*params.ones[323]+(-params.Pg_N_init[324]+params.Pg_N_avg[324]+params.ug_N[324])*params.ones[324]+(-params.Pg_N_init[325]+params.Pg_N_avg[325]+params.ug_N[325])*params.ones[325]+(-params.Pg_N_init[326]+params.Pg_N_avg[326]+params.ug_N[326])*params.ones[326]+(-params.Pg_N_init[327]+params.Pg_N_avg[327]+params.ug_N[327])*params.ones[327]+(-params.Pg_N_init[328]+params.Pg_N_avg[328]+params.ug_N[328])*params.ones[328]+(-params.Pg_N_init[329]+params.Pg_N_avg[329]+params.ug_N[329])*params.ones[329]+(-params.Pg_N_init[330]+params.Pg_N_avg[330]+params.ug_N[330])*params.ones[330]+(-params.Pg_N_init[331]+params.Pg_N_avg[331]+params.ug_N[331])*params.ones[331]+(-params.Pg_N_init[332]+params.Pg_N_avg[332]+params.ug_N[332])*params.ones[332]+(-params.Pg_N_init[333]+params.Pg_N_avg[333]+params.ug_N[333])*params.ones[333]+(-params.Pg_N_init[334]+params.Pg_N_avg[334]+params.ug_N[334])*params.ones[334]+(-params.Pg_N_init[335]+params.Pg_N_avg[335]+params.ug_N[335])*params.ones[335]+(-params.Pg_N_init[336]+params.Pg_N_avg[336]+params.ug_N[336])*params.ones[336]+(-params.Pg_N_init[337]+params.Pg_N_avg[337]+params.ug_N[337])*params.ones[337]+(-params.Pg_N_init[338]+params.Pg_N_avg[338]+params.ug_N[338])*params.ones[338]+(-params.Pg_N_init[339]+params.Pg_N_avg[339]+params.ug_N[339])*params.ones[339]+(-params.Pg_N_init[340]+params.Pg_N_avg[340]+params.ug_N[340])*params.ones[340]+(-params.Pg_N_init[341]+params.Pg_N_avg[341]+params.ug_N[341])*params.ones[341]+(-params.Pg_N_init[342]+params.Pg_N_avg[342]+params.ug_N[342])*params.ones[342]+(-params.Pg_N_init[343]+params.Pg_N_avg[343]+params.ug_N[343])*params.ones[343]+(-params.Pg_N_init[344]+params.Pg_N_avg[344]+params.ug_N[344])*params.ones[344]+(-params.Pg_N_init[345]+params.Pg_N_avg[345]+params.ug_N[345])*params.ones[345]+(-params.Pg_N_init[346]+params.Pg_N_avg[346]+params.ug_N[346])*params.ones[346]+(-params.Pg_N_init[347]+params.Pg_N_avg[347]+params.ug_N[347])*params.ones[347]+(-params.Pg_N_init[348]+params.Pg_N_avg[348]+params.ug_N[348])*params.ones[348]+(-params.Pg_N_init[349]+params.Pg_N_avg[349]+params.ug_N[349])*params.ones[349]+(-params.Pg_N_init[350]+params.Pg_N_avg[350]+params.ug_N[350])*params.ones[350]+(-params.Pg_N_init[351]+params.Pg_N_avg[351]+params.ug_N[351])*params.ones[351]+(-params.Pg_N_init[352]+params.Pg_N_avg[352]+params.ug_N[352])*params.ones[352]+(-params.Pg_N_init[353]+params.Pg_N_avg[353]+params.ug_N[353])*params.ones[353]+(-params.Pg_N_init[354]+params.Pg_N_avg[354]+params.ug_N[354])*params.ones[354]+(-params.Pg_N_init[355]+params.Pg_N_avg[355]+params.ug_N[355])*params.ones[355]+(-params.Pg_N_init[356]+params.Pg_N_avg[356]+params.ug_N[356])*params.ones[356]+(-params.Pg_N_init[357]+params.Pg_N_avg[357]+params.ug_N[357])*params.ones[357]+(-params.Pg_N_init[358]+params.Pg_N_avg[358]+params.ug_N[358])*params.ones[358]+(-params.Pg_N_init[359]+params.Pg_N_avg[359]+params.ug_N[359])*params.ones[359]+(-params.Pg_N_init[360]+params.Pg_N_avg[360]+params.ug_N[360])*params.ones[360]+(-params.Pg_N_init[361]+params.Pg_N_avg[361]+params.ug_N[361])*params.ones[361]+(-params.Pg_N_init[362]+params.Pg_N_avg[362]+params.ug_N[362])*params.ones[362]+(-params.Pg_N_init[363]+params.Pg_N_avg[363]+params.ug_N[363])*params.ones[363]+(-params.Pg_N_init[364]+params.Pg_N_avg[364]+params.ug_N[364])*params.ones[364]+(-params.Pg_N_init[365]+params.Pg_N_avg[365]+params.ug_N[365])*params.ones[365]+(-params.Pg_N_init[366]+params.Pg_N_avg[366]+params.ug_N[366])*params.ones[366]+(-params.Pg_N_init[367]+params.Pg_N_avg[367]+params.ug_N[367])*params.ones[367]+(-params.Pg_N_init[368]+params.Pg_N_avg[368]+params.ug_N[368])*params.ones[368]+(-params.Pg_N_init[369]+params.Pg_N_avg[369]+params.ug_N[369])*params.ones[369]+(-params.Pg_N_init[370]+params.Pg_N_avg[370]+params.ug_N[370])*params.ones[370]+(-params.Pg_N_init[371]+params.Pg_N_avg[371]+params.ug_N[371])*params.ones[371]+(-params.Pg_N_init[372]+params.Pg_N_avg[372]+params.ug_N[372])*params.ones[372]+(-params.Pg_N_init[373]+params.Pg_N_avg[373]+params.ug_N[373])*params.ones[373]+(-params.Pg_N_init[374]+params.Pg_N_avg[374]+params.ug_N[374])*params.ones[374]+(-params.Pg_N_init[375]+params.Pg_N_avg[375]+params.ug_N[375])*params.ones[375]+(-params.Pg_N_init[376]+params.Pg_N_avg[376]+params.ug_N[376])*params.ones[376]+(-params.Pg_N_init[377]+params.Pg_N_avg[377]+params.ug_N[377])*params.ones[377]+(-params.Pg_N_init[378]+params.Pg_N_avg[378]+params.ug_N[378])*params.ones[378]+(-params.Pg_N_init[379]+params.Pg_N_avg[379]+params.ug_N[379])*params.ones[379]+(-params.Pg_N_init[380]+params.Pg_N_avg[380]+params.ug_N[380])*params.ones[380]+(-params.Pg_N_init[381]+params.Pg_N_avg[381]+params.ug_N[381])*params.ones[381]+(-params.Pg_N_init[382]+params.Pg_N_avg[382]+params.ug_N[382])*params.ones[382]+(-params.Pg_N_init[383]+params.Pg_N_avg[383]+params.ug_N[383])*params.ones[383]+(-params.Pg_N_init[384]+params.Pg_N_avg[384]+params.ug_N[384])*params.ones[384]+(-params.Pg_N_init[385]+params.Pg_N_avg[385]+params.ug_N[385])*params.ones[385]+(-params.Pg_N_init[386]+params.Pg_N_avg[386]+params.ug_N[386])*params.ones[386]+(-params.Pg_N_init[387]+params.Pg_N_avg[387]+params.ug_N[387])*params.ones[387]+(-params.Pg_N_init[388]+params.Pg_N_avg[388]+params.ug_N[388])*params.ones[388]+(-params.Pg_N_init[389]+params.Pg_N_avg[389]+params.ug_N[389])*params.ones[389]+(-params.Pg_N_init[390]+params.Pg_N_avg[390]+params.ug_N[390])*params.ones[390]+(-params.Pg_N_init[391]+params.Pg_N_avg[391]+params.ug_N[391])*params.ones[391]+(-params.Pg_N_init[392]+params.Pg_N_avg[392]+params.ug_N[392])*params.ones[392]+(-params.Pg_N_init[393]+params.Pg_N_avg[393]+params.ug_N[393])*params.ones[393]+(-params.Pg_N_init[394]+params.Pg_N_avg[394]+params.ug_N[394])*params.ones[394]+(-params.Pg_N_init[395]+params.Pg_N_avg[395]+params.ug_N[395])*params.ones[395]+(-params.Pg_N_init[396]+params.Pg_N_avg[396]+params.ug_N[396])*params.ones[396]+(-params.Pg_N_init[397]+params.Pg_N_avg[397]+params.ug_N[397])*params.ones[397]+(-params.Pg_N_init[398]+params.Pg_N_avg[398]+params.ug_N[398])*params.ones[398]+(-params.Pg_N_init[399]+params.Pg_N_avg[399]+params.ug_N[399])*params.ones[399]+(-params.Pg_N_init[400]+params.Pg_N_avg[400]+params.ug_N[400])*params.ones[400]);
for ( int i = 1; i <= 401; ++i )
  work.q[i] = 2*work.frac_121674190848*(-params.Vg_N_avg[i-1]-params.Thetag_N_avg[i-1]+params.vg_N[i-1]);
}
void Gensolver::fillh(void) {
  work.h[0] = -params.PgMin[0];
  work.h[1] = params.PgMax[0];
}
void Gensolver::fillb(void) {
}
void Gensolver::pre_ops(void) {
  work.quad_530423889920[0] = work.frac_121674190848*(params.ones[0]*params.ones[0]+params.ones[1]*params.ones[1]+params.ones[2]*params.ones[2]+params.ones[3]*params.ones[3]+params.ones[4]*params.ones[4]+params.ones[5]*params.ones[5]+params.ones[6]*params.ones[6]+params.ones[7]*params.ones[7]+params.ones[8]*params.ones[8]+params.ones[9]*params.ones[9]+params.ones[10]*params.ones[10]+params.ones[11]*params.ones[11]+params.ones[12]*params.ones[12]+params.ones[13]*params.ones[13]+params.ones[14]*params.ones[14]+params.ones[15]*params.ones[15]+params.ones[16]*params.ones[16]+params.ones[17]*params.ones[17]+params.ones[18]*params.ones[18]+params.ones[19]*params.ones[19]+params.ones[20]*params.ones[20]+params.ones[21]*params.ones[21]+params.ones[22]*params.ones[22]+params.ones[23]*params.ones[23]+params.ones[24]*params.ones[24]+params.ones[25]*params.ones[25]+params.ones[26]*params.ones[26]+params.ones[27]*params.ones[27]+params.ones[28]*params.ones[28]+params.ones[29]*params.ones[29]+params.ones[30]*params.ones[30]+params.ones[31]*params.ones[31]+params.ones[32]*params.ones[32]+params.ones[33]*params.ones[33]+params.ones[34]*params.ones[34]+params.ones[35]*params.ones[35]+params.ones[36]*params.ones[36]+params.ones[37]*params.ones[37]+params.ones[38]*params.ones[38]+params.ones[39]*params.ones[39]+params.ones[40]*params.ones[40]+params.ones[41]*params.ones[41]+params.ones[42]*params.ones[42]+params.ones[43]*params.ones[43]+params.ones[44]*params.ones[44]+params.ones[45]*params.ones[45]+params.ones[46]*params.ones[46]+params.ones[47]*params.ones[47]+params.ones[48]*params.ones[48]+params.ones[49]*params.ones[49]+params.ones[50]*params.ones[50]+params.ones[51]*params.ones[51]+params.ones[52]*params.ones[52]+params.ones[53]*params.ones[53]+params.ones[54]*params.ones[54]+params.ones[55]*params.ones[55]+params.ones[56]*params.ones[56]+params.ones[57]*params.ones[57]+params.ones[58]*params.ones[58]+params.ones[59]*params.ones[59]+params.ones[60]*params.ones[60]+params.ones[61]*params.ones[61]+params.ones[62]*params.ones[62]+params.ones[63]*params.ones[63]+params.ones[64]*params.ones[64]+params.ones[65]*params.ones[65]+params.ones[66]*params.ones[66]+params.ones[67]*params.ones[67]+params.ones[68]*params.ones[68]+params.ones[69]*params.ones[69]+params.ones[70]*params.ones[70]+params.ones[71]*params.ones[71]+params.ones[72]*params.ones[72]+params.ones[73]*params.ones[73]+params.ones[74]*params.ones[74]+params.ones[75]*params.ones[75]+params.ones[76]*params.ones[76]+params.ones[77]*params.ones[77]+params.ones[78]*params.ones[78]+params.ones[79]*params.ones[79]+params.ones[80]*params.ones[80]+params.ones[81]*params.ones[81]+params.ones[82]*params.ones[82]+params.ones[83]*params.ones[83]+params.ones[84]*params.ones[84]+params.ones[85]*params.ones[85]+params.ones[86]*params.ones[86]+params.ones[87]*params.ones[87]+params.ones[88]*params.ones[88]+params.ones[89]*params.ones[89]+params.ones[90]*params.ones[90]+params.ones[91]*params.ones[91]+params.ones[92]*params.ones[92]+params.ones[93]*params.ones[93]+params.ones[94]*params.ones[94]+params.ones[95]*params.ones[95]+params.ones[96]*params.ones[96]+params.ones[97]*params.ones[97]+params.ones[98]*params.ones[98]+params.ones[99]*params.ones[99]+params.ones[100]*params.ones[100]+params.ones[101]*params.ones[101]+params.ones[102]*params.ones[102]+params.ones[103]*params.ones[103]+params.ones[104]*params.ones[104]+params.ones[105]*params.ones[105]+params.ones[106]*params.ones[106]+params.ones[107]*params.ones[107]+params.ones[108]*params.ones[108]+params.ones[109]*params.ones[109]+params.ones[110]*params.ones[110]+params.ones[111]*params.ones[111]+params.ones[112]*params.ones[112]+params.ones[113]*params.ones[113]+params.ones[114]*params.ones[114]+params.ones[115]*params.ones[115]+params.ones[116]*params.ones[116]+params.ones[117]*params.ones[117]+params.ones[118]*params.ones[118]+params.ones[119]*params.ones[119]+params.ones[120]*params.ones[120]+params.ones[121]*params.ones[121]+params.ones[122]*params.ones[122]+params.ones[123]*params.ones[123]+params.ones[124]*params.ones[124]+params.ones[125]*params.ones[125]+params.ones[126]*params.ones[126]+params.ones[127]*params.ones[127]+params.ones[128]*params.ones[128]+params.ones[129]*params.ones[129]+params.ones[130]*params.ones[130]+params.ones[131]*params.ones[131]+params.ones[132]*params.ones[132]+params.ones[133]*params.ones[133]+params.ones[134]*params.ones[134]+params.ones[135]*params.ones[135]+params.ones[136]*params.ones[136]+params.ones[137]*params.ones[137]+params.ones[138]*params.ones[138]+params.ones[139]*params.ones[139]+params.ones[140]*params.ones[140]+params.ones[141]*params.ones[141]+params.ones[142]*params.ones[142]+params.ones[143]*params.ones[143]+params.ones[144]*params.ones[144]+params.ones[145]*params.ones[145]+params.ones[146]*params.ones[146]+params.ones[147]*params.ones[147]+params.ones[148]*params.ones[148]+params.ones[149]*params.ones[149]+params.ones[150]*params.ones[150]+params.ones[151]*params.ones[151]+params.ones[152]*params.ones[152]+params.ones[153]*params.ones[153]+params.ones[154]*params.ones[154]+params.ones[155]*params.ones[155]+params.ones[156]*params.ones[156]+params.ones[157]*params.ones[157]+params.ones[158]*params.ones[158]+params.ones[159]*params.ones[159]+params.ones[160]*params.ones[160]+params.ones[161]*params.ones[161]+params.ones[162]*params.ones[162]+params.ones[163]*params.ones[163]+params.ones[164]*params.ones[164]+params.ones[165]*params.ones[165]+params.ones[166]*params.ones[166]+params.ones[167]*params.ones[167]+params.ones[168]*params.ones[168]+params.ones[169]*params.ones[169]+params.ones[170]*params.ones[170]+params.ones[171]*params.ones[171]+params.ones[172]*params.ones[172]+params.ones[173]*params.ones[173]+params.ones[174]*params.ones[174]+params.ones[175]*params.ones[175]+params.ones[176]*params.ones[176]+params.ones[177]*params.ones[177]+params.ones[178]*params.ones[178]+params.ones[179]*params.ones[179]+params.ones[180]*params.ones[180]+params.ones[181]*params.ones[181]+params.ones[182]*params.ones[182]+params.ones[183]*params.ones[183]+params.ones[184]*params.ones[184]+params.ones[185]*params.ones[185]+params.ones[186]*params.ones[186]+params.ones[187]*params.ones[187]+params.ones[188]*params.ones[188]+params.ones[189]*params.ones[189]+params.ones[190]*params.ones[190]+params.ones[191]*params.ones[191]+params.ones[192]*params.ones[192]+params.ones[193]*params.ones[193]+params.ones[194]*params.ones[194]+params.ones[195]*params.ones[195]+params.ones[196]*params.ones[196]+params.ones[197]*params.ones[197]+params.ones[198]*params.ones[198]+params.ones[199]*params.ones[199]+params.ones[200]*params.ones[200]+params.ones[201]*params.ones[201]+params.ones[202]*params.ones[202]+params.ones[203]*params.ones[203]+params.ones[204]*params.ones[204]+params.ones[205]*params.ones[205]+params.ones[206]*params.ones[206]+params.ones[207]*params.ones[207]+params.ones[208]*params.ones[208]+params.ones[209]*params.ones[209]+params.ones[210]*params.ones[210]+params.ones[211]*params.ones[211]+params.ones[212]*params.ones[212]+params.ones[213]*params.ones[213]+params.ones[214]*params.ones[214]+params.ones[215]*params.ones[215]+params.ones[216]*params.ones[216]+params.ones[217]*params.ones[217]+params.ones[218]*params.ones[218]+params.ones[219]*params.ones[219]+params.ones[220]*params.ones[220]+params.ones[221]*params.ones[221]+params.ones[222]*params.ones[222]+params.ones[223]*params.ones[223]+params.ones[224]*params.ones[224]+params.ones[225]*params.ones[225]+params.ones[226]*params.ones[226]+params.ones[227]*params.ones[227]+params.ones[228]*params.ones[228]+params.ones[229]*params.ones[229]+params.ones[230]*params.ones[230]+params.ones[231]*params.ones[231]+params.ones[232]*params.ones[232]+params.ones[233]*params.ones[233]+params.ones[234]*params.ones[234]+params.ones[235]*params.ones[235]+params.ones[236]*params.ones[236]+params.ones[237]*params.ones[237]+params.ones[238]*params.ones[238]+params.ones[239]*params.ones[239]+params.ones[240]*params.ones[240]+params.ones[241]*params.ones[241]+params.ones[242]*params.ones[242]+params.ones[243]*params.ones[243]+params.ones[244]*params.ones[244]+params.ones[245]*params.ones[245]+params.ones[246]*params.ones[246]+params.ones[247]*params.ones[247]+params.ones[248]*params.ones[248]+params.ones[249]*params.ones[249]+params.ones[250]*params.ones[250]+params.ones[251]*params.ones[251]+params.ones[252]*params.ones[252]+params.ones[253]*params.ones[253]+params.ones[254]*params.ones[254]+params.ones[255]*params.ones[255]+params.ones[256]*params.ones[256]+params.ones[257]*params.ones[257]+params.ones[258]*params.ones[258]+params.ones[259]*params.ones[259]+params.ones[260]*params.ones[260]+params.ones[261]*params.ones[261]+params.ones[262]*params.ones[262]+params.ones[263]*params.ones[263]+params.ones[264]*params.ones[264]+params.ones[265]*params.ones[265]+params.ones[266]*params.ones[266]+params.ones[267]*params.ones[267]+params.ones[268]*params.ones[268]+params.ones[269]*params.ones[269]+params.ones[270]*params.ones[270]+params.ones[271]*params.ones[271]+params.ones[272]*params.ones[272]+params.ones[273]*params.ones[273]+params.ones[274]*params.ones[274]+params.ones[275]*params.ones[275]+params.ones[276]*params.ones[276]+params.ones[277]*params.ones[277]+params.ones[278]*params.ones[278]+params.ones[279]*params.ones[279]+params.ones[280]*params.ones[280]+params.ones[281]*params.ones[281]+params.ones[282]*params.ones[282]+params.ones[283]*params.ones[283]+params.ones[284]*params.ones[284]+params.ones[285]*params.ones[285]+params.ones[286]*params.ones[286]+params.ones[287]*params.ones[287]+params.ones[288]*params.ones[288]+params.ones[289]*params.ones[289]+params.ones[290]*params.ones[290]+params.ones[291]*params.ones[291]+params.ones[292]*params.ones[292]+params.ones[293]*params.ones[293]+params.ones[294]*params.ones[294]+params.ones[295]*params.ones[295]+params.ones[296]*params.ones[296]+params.ones[297]*params.ones[297]+params.ones[298]*params.ones[298]+params.ones[299]*params.ones[299]+params.ones[300]*params.ones[300]+params.ones[301]*params.ones[301]+params.ones[302]*params.ones[302]+params.ones[303]*params.ones[303]+params.ones[304]*params.ones[304]+params.ones[305]*params.ones[305]+params.ones[306]*params.ones[306]+params.ones[307]*params.ones[307]+params.ones[308]*params.ones[308]+params.ones[309]*params.ones[309]+params.ones[310]*params.ones[310]+params.ones[311]*params.ones[311]+params.ones[312]*params.ones[312]+params.ones[313]*params.ones[313]+params.ones[314]*params.ones[314]+params.ones[315]*params.ones[315]+params.ones[316]*params.ones[316]+params.ones[317]*params.ones[317]+params.ones[318]*params.ones[318]+params.ones[319]*params.ones[319]+params.ones[320]*params.ones[320]+params.ones[321]*params.ones[321]+params.ones[322]*params.ones[322]+params.ones[323]*params.ones[323]+params.ones[324]*params.ones[324]+params.ones[325]*params.ones[325]+params.ones[326]*params.ones[326]+params.ones[327]*params.ones[327]+params.ones[328]*params.ones[328]+params.ones[329]*params.ones[329]+params.ones[330]*params.ones[330]+params.ones[331]*params.ones[331]+params.ones[332]*params.ones[332]+params.ones[333]*params.ones[333]+params.ones[334]*params.ones[334]+params.ones[335]*params.ones[335]+params.ones[336]*params.ones[336]+params.ones[337]*params.ones[337]+params.ones[338]*params.ones[338]+params.ones[339]*params.ones[339]+params.ones[340]*params.ones[340]+params.ones[341]*params.ones[341]+params.ones[342]*params.ones[342]+params.ones[343]*params.ones[343]+params.ones[344]*params.ones[344]+params.ones[345]*params.ones[345]+params.ones[346]*params.ones[346]+params.ones[347]*params.ones[347]+params.ones[348]*params.ones[348]+params.ones[349]*params.ones[349]+params.ones[350]*params.ones[350]+params.ones[351]*params.ones[351]+params.ones[352]*params.ones[352]+params.ones[353]*params.ones[353]+params.ones[354]*params.ones[354]+params.ones[355]*params.ones[355]+params.ones[356]*params.ones[356]+params.ones[357]*params.ones[357]+params.ones[358]*params.ones[358]+params.ones[359]*params.ones[359]+params.ones[360]*params.ones[360]+params.ones[361]*params.ones[361]+params.ones[362]*params.ones[362]+params.ones[363]*params.ones[363]+params.ones[364]*params.ones[364]+params.ones[365]*params.ones[365]+params.ones[366]*params.ones[366]+params.ones[367]*params.ones[367]+params.ones[368]*params.ones[368]+params.ones[369]*params.ones[369]+params.ones[370]*params.ones[370]+params.ones[371]*params.ones[371]+params.ones[372]*params.ones[372]+params.ones[373]*params.ones[373]+params.ones[374]*params.ones[374]+params.ones[375]*params.ones[375]+params.ones[376]*params.ones[376]+params.ones[377]*params.ones[377]+params.ones[378]*params.ones[378]+params.ones[379]*params.ones[379]+params.ones[380]*params.ones[380]+params.ones[381]*params.ones[381]+params.ones[382]*params.ones[382]+params.ones[383]*params.ones[383]+params.ones[384]*params.ones[384]+params.ones[385]*params.ones[385]+params.ones[386]*params.ones[386]+params.ones[387]*params.ones[387]+params.ones[388]*params.ones[388]+params.ones[389]*params.ones[389]+params.ones[390]*params.ones[390]+params.ones[391]*params.ones[391]+params.ones[392]*params.ones[392]+params.ones[393]*params.ones[393]+params.ones[394]*params.ones[394]+params.ones[395]*params.ones[395]+params.ones[396]*params.ones[396]+params.ones[397]*params.ones[397]+params.ones[398]*params.ones[398]+params.ones[399]*params.ones[399]+params.ones[400]*params.ones[400]);
  work.frac_121674190848 = params.rho[0];
  work.frac_121674190848 /= 2;
  work.quad_551453212672[0] = work.frac_121674190848*((-params.Pg_N_init[0]+params.Pg_N_avg[0]+params.ug_N[0])*(-params.Pg_N_init[0]+params.Pg_N_avg[0]+params.ug_N[0])+(-params.Pg_N_init[1]+params.Pg_N_avg[1]+params.ug_N[1])*(-params.Pg_N_init[1]+params.Pg_N_avg[1]+params.ug_N[1])+(-params.Pg_N_init[2]+params.Pg_N_avg[2]+params.ug_N[2])*(-params.Pg_N_init[2]+params.Pg_N_avg[2]+params.ug_N[2])+(-params.Pg_N_init[3]+params.Pg_N_avg[3]+params.ug_N[3])*(-params.Pg_N_init[3]+params.Pg_N_avg[3]+params.ug_N[3])+(-params.Pg_N_init[4]+params.Pg_N_avg[4]+params.ug_N[4])*(-params.Pg_N_init[4]+params.Pg_N_avg[4]+params.ug_N[4])+(-params.Pg_N_init[5]+params.Pg_N_avg[5]+params.ug_N[5])*(-params.Pg_N_init[5]+params.Pg_N_avg[5]+params.ug_N[5])+(-params.Pg_N_init[6]+params.Pg_N_avg[6]+params.ug_N[6])*(-params.Pg_N_init[6]+params.Pg_N_avg[6]+params.ug_N[6])+(-params.Pg_N_init[7]+params.Pg_N_avg[7]+params.ug_N[7])*(-params.Pg_N_init[7]+params.Pg_N_avg[7]+params.ug_N[7])+(-params.Pg_N_init[8]+params.Pg_N_avg[8]+params.ug_N[8])*(-params.Pg_N_init[8]+params.Pg_N_avg[8]+params.ug_N[8])+(-params.Pg_N_init[9]+params.Pg_N_avg[9]+params.ug_N[9])*(-params.Pg_N_init[9]+params.Pg_N_avg[9]+params.ug_N[9])+(-params.Pg_N_init[10]+params.Pg_N_avg[10]+params.ug_N[10])*(-params.Pg_N_init[10]+params.Pg_N_avg[10]+params.ug_N[10])+(-params.Pg_N_init[11]+params.Pg_N_avg[11]+params.ug_N[11])*(-params.Pg_N_init[11]+params.Pg_N_avg[11]+params.ug_N[11])+(-params.Pg_N_init[12]+params.Pg_N_avg[12]+params.ug_N[12])*(-params.Pg_N_init[12]+params.Pg_N_avg[12]+params.ug_N[12])+(-params.Pg_N_init[13]+params.Pg_N_avg[13]+params.ug_N[13])*(-params.Pg_N_init[13]+params.Pg_N_avg[13]+params.ug_N[13])+(-params.Pg_N_init[14]+params.Pg_N_avg[14]+params.ug_N[14])*(-params.Pg_N_init[14]+params.Pg_N_avg[14]+params.ug_N[14])+(-params.Pg_N_init[15]+params.Pg_N_avg[15]+params.ug_N[15])*(-params.Pg_N_init[15]+params.Pg_N_avg[15]+params.ug_N[15])+(-params.Pg_N_init[16]+params.Pg_N_avg[16]+params.ug_N[16])*(-params.Pg_N_init[16]+params.Pg_N_avg[16]+params.ug_N[16])+(-params.Pg_N_init[17]+params.Pg_N_avg[17]+params.ug_N[17])*(-params.Pg_N_init[17]+params.Pg_N_avg[17]+params.ug_N[17])+(-params.Pg_N_init[18]+params.Pg_N_avg[18]+params.ug_N[18])*(-params.Pg_N_init[18]+params.Pg_N_avg[18]+params.ug_N[18])+(-params.Pg_N_init[19]+params.Pg_N_avg[19]+params.ug_N[19])*(-params.Pg_N_init[19]+params.Pg_N_avg[19]+params.ug_N[19])+(-params.Pg_N_init[20]+params.Pg_N_avg[20]+params.ug_N[20])*(-params.Pg_N_init[20]+params.Pg_N_avg[20]+params.ug_N[20])+(-params.Pg_N_init[21]+params.Pg_N_avg[21]+params.ug_N[21])*(-params.Pg_N_init[21]+params.Pg_N_avg[21]+params.ug_N[21])+(-params.Pg_N_init[22]+params.Pg_N_avg[22]+params.ug_N[22])*(-params.Pg_N_init[22]+params.Pg_N_avg[22]+params.ug_N[22])+(-params.Pg_N_init[23]+params.Pg_N_avg[23]+params.ug_N[23])*(-params.Pg_N_init[23]+params.Pg_N_avg[23]+params.ug_N[23])+(-params.Pg_N_init[24]+params.Pg_N_avg[24]+params.ug_N[24])*(-params.Pg_N_init[24]+params.Pg_N_avg[24]+params.ug_N[24])+(-params.Pg_N_init[25]+params.Pg_N_avg[25]+params.ug_N[25])*(-params.Pg_N_init[25]+params.Pg_N_avg[25]+params.ug_N[25])+(-params.Pg_N_init[26]+params.Pg_N_avg[26]+params.ug_N[26])*(-params.Pg_N_init[26]+params.Pg_N_avg[26]+params.ug_N[26])+(-params.Pg_N_init[27]+params.Pg_N_avg[27]+params.ug_N[27])*(-params.Pg_N_init[27]+params.Pg_N_avg[27]+params.ug_N[27])+(-params.Pg_N_init[28]+params.Pg_N_avg[28]+params.ug_N[28])*(-params.Pg_N_init[28]+params.Pg_N_avg[28]+params.ug_N[28])+(-params.Pg_N_init[29]+params.Pg_N_avg[29]+params.ug_N[29])*(-params.Pg_N_init[29]+params.Pg_N_avg[29]+params.ug_N[29])+(-params.Pg_N_init[30]+params.Pg_N_avg[30]+params.ug_N[30])*(-params.Pg_N_init[30]+params.Pg_N_avg[30]+params.ug_N[30])+(-params.Pg_N_init[31]+params.Pg_N_avg[31]+params.ug_N[31])*(-params.Pg_N_init[31]+params.Pg_N_avg[31]+params.ug_N[31])+(-params.Pg_N_init[32]+params.Pg_N_avg[32]+params.ug_N[32])*(-params.Pg_N_init[32]+params.Pg_N_avg[32]+params.ug_N[32])+(-params.Pg_N_init[33]+params.Pg_N_avg[33]+params.ug_N[33])*(-params.Pg_N_init[33]+params.Pg_N_avg[33]+params.ug_N[33])+(-params.Pg_N_init[34]+params.Pg_N_avg[34]+params.ug_N[34])*(-params.Pg_N_init[34]+params.Pg_N_avg[34]+params.ug_N[34])+(-params.Pg_N_init[35]+params.Pg_N_avg[35]+params.ug_N[35])*(-params.Pg_N_init[35]+params.Pg_N_avg[35]+params.ug_N[35])+(-params.Pg_N_init[36]+params.Pg_N_avg[36]+params.ug_N[36])*(-params.Pg_N_init[36]+params.Pg_N_avg[36]+params.ug_N[36])+(-params.Pg_N_init[37]+params.Pg_N_avg[37]+params.ug_N[37])*(-params.Pg_N_init[37]+params.Pg_N_avg[37]+params.ug_N[37])+(-params.Pg_N_init[38]+params.Pg_N_avg[38]+params.ug_N[38])*(-params.Pg_N_init[38]+params.Pg_N_avg[38]+params.ug_N[38])+(-params.Pg_N_init[39]+params.Pg_N_avg[39]+params.ug_N[39])*(-params.Pg_N_init[39]+params.Pg_N_avg[39]+params.ug_N[39])+(-params.Pg_N_init[40]+params.Pg_N_avg[40]+params.ug_N[40])*(-params.Pg_N_init[40]+params.Pg_N_avg[40]+params.ug_N[40])+(-params.Pg_N_init[41]+params.Pg_N_avg[41]+params.ug_N[41])*(-params.Pg_N_init[41]+params.Pg_N_avg[41]+params.ug_N[41])+(-params.Pg_N_init[42]+params.Pg_N_avg[42]+params.ug_N[42])*(-params.Pg_N_init[42]+params.Pg_N_avg[42]+params.ug_N[42])+(-params.Pg_N_init[43]+params.Pg_N_avg[43]+params.ug_N[43])*(-params.Pg_N_init[43]+params.Pg_N_avg[43]+params.ug_N[43])+(-params.Pg_N_init[44]+params.Pg_N_avg[44]+params.ug_N[44])*(-params.Pg_N_init[44]+params.Pg_N_avg[44]+params.ug_N[44])+(-params.Pg_N_init[45]+params.Pg_N_avg[45]+params.ug_N[45])*(-params.Pg_N_init[45]+params.Pg_N_avg[45]+params.ug_N[45])+(-params.Pg_N_init[46]+params.Pg_N_avg[46]+params.ug_N[46])*(-params.Pg_N_init[46]+params.Pg_N_avg[46]+params.ug_N[46])+(-params.Pg_N_init[47]+params.Pg_N_avg[47]+params.ug_N[47])*(-params.Pg_N_init[47]+params.Pg_N_avg[47]+params.ug_N[47])+(-params.Pg_N_init[48]+params.Pg_N_avg[48]+params.ug_N[48])*(-params.Pg_N_init[48]+params.Pg_N_avg[48]+params.ug_N[48])+(-params.Pg_N_init[49]+params.Pg_N_avg[49]+params.ug_N[49])*(-params.Pg_N_init[49]+params.Pg_N_avg[49]+params.ug_N[49])+(-params.Pg_N_init[50]+params.Pg_N_avg[50]+params.ug_N[50])*(-params.Pg_N_init[50]+params.Pg_N_avg[50]+params.ug_N[50])+(-params.Pg_N_init[51]+params.Pg_N_avg[51]+params.ug_N[51])*(-params.Pg_N_init[51]+params.Pg_N_avg[51]+params.ug_N[51])+(-params.Pg_N_init[52]+params.Pg_N_avg[52]+params.ug_N[52])*(-params.Pg_N_init[52]+params.Pg_N_avg[52]+params.ug_N[52])+(-params.Pg_N_init[53]+params.Pg_N_avg[53]+params.ug_N[53])*(-params.Pg_N_init[53]+params.Pg_N_avg[53]+params.ug_N[53])+(-params.Pg_N_init[54]+params.Pg_N_avg[54]+params.ug_N[54])*(-params.Pg_N_init[54]+params.Pg_N_avg[54]+params.ug_N[54])+(-params.Pg_N_init[55]+params.Pg_N_avg[55]+params.ug_N[55])*(-params.Pg_N_init[55]+params.Pg_N_avg[55]+params.ug_N[55])+(-params.Pg_N_init[56]+params.Pg_N_avg[56]+params.ug_N[56])*(-params.Pg_N_init[56]+params.Pg_N_avg[56]+params.ug_N[56])+(-params.Pg_N_init[57]+params.Pg_N_avg[57]+params.ug_N[57])*(-params.Pg_N_init[57]+params.Pg_N_avg[57]+params.ug_N[57])+(-params.Pg_N_init[58]+params.Pg_N_avg[58]+params.ug_N[58])*(-params.Pg_N_init[58]+params.Pg_N_avg[58]+params.ug_N[58])+(-params.Pg_N_init[59]+params.Pg_N_avg[59]+params.ug_N[59])*(-params.Pg_N_init[59]+params.Pg_N_avg[59]+params.ug_N[59])+(-params.Pg_N_init[60]+params.Pg_N_avg[60]+params.ug_N[60])*(-params.Pg_N_init[60]+params.Pg_N_avg[60]+params.ug_N[60])+(-params.Pg_N_init[61]+params.Pg_N_avg[61]+params.ug_N[61])*(-params.Pg_N_init[61]+params.Pg_N_avg[61]+params.ug_N[61])+(-params.Pg_N_init[62]+params.Pg_N_avg[62]+params.ug_N[62])*(-params.Pg_N_init[62]+params.Pg_N_avg[62]+params.ug_N[62])+(-params.Pg_N_init[63]+params.Pg_N_avg[63]+params.ug_N[63])*(-params.Pg_N_init[63]+params.Pg_N_avg[63]+params.ug_N[63])+(-params.Pg_N_init[64]+params.Pg_N_avg[64]+params.ug_N[64])*(-params.Pg_N_init[64]+params.Pg_N_avg[64]+params.ug_N[64])+(-params.Pg_N_init[65]+params.Pg_N_avg[65]+params.ug_N[65])*(-params.Pg_N_init[65]+params.Pg_N_avg[65]+params.ug_N[65])+(-params.Pg_N_init[66]+params.Pg_N_avg[66]+params.ug_N[66])*(-params.Pg_N_init[66]+params.Pg_N_avg[66]+params.ug_N[66])+(-params.Pg_N_init[67]+params.Pg_N_avg[67]+params.ug_N[67])*(-params.Pg_N_init[67]+params.Pg_N_avg[67]+params.ug_N[67])+(-params.Pg_N_init[68]+params.Pg_N_avg[68]+params.ug_N[68])*(-params.Pg_N_init[68]+params.Pg_N_avg[68]+params.ug_N[68])+(-params.Pg_N_init[69]+params.Pg_N_avg[69]+params.ug_N[69])*(-params.Pg_N_init[69]+params.Pg_N_avg[69]+params.ug_N[69])+(-params.Pg_N_init[70]+params.Pg_N_avg[70]+params.ug_N[70])*(-params.Pg_N_init[70]+params.Pg_N_avg[70]+params.ug_N[70])+(-params.Pg_N_init[71]+params.Pg_N_avg[71]+params.ug_N[71])*(-params.Pg_N_init[71]+params.Pg_N_avg[71]+params.ug_N[71])+(-params.Pg_N_init[72]+params.Pg_N_avg[72]+params.ug_N[72])*(-params.Pg_N_init[72]+params.Pg_N_avg[72]+params.ug_N[72])+(-params.Pg_N_init[73]+params.Pg_N_avg[73]+params.ug_N[73])*(-params.Pg_N_init[73]+params.Pg_N_avg[73]+params.ug_N[73])+(-params.Pg_N_init[74]+params.Pg_N_avg[74]+params.ug_N[74])*(-params.Pg_N_init[74]+params.Pg_N_avg[74]+params.ug_N[74])+(-params.Pg_N_init[75]+params.Pg_N_avg[75]+params.ug_N[75])*(-params.Pg_N_init[75]+params.Pg_N_avg[75]+params.ug_N[75])+(-params.Pg_N_init[76]+params.Pg_N_avg[76]+params.ug_N[76])*(-params.Pg_N_init[76]+params.Pg_N_avg[76]+params.ug_N[76])+(-params.Pg_N_init[77]+params.Pg_N_avg[77]+params.ug_N[77])*(-params.Pg_N_init[77]+params.Pg_N_avg[77]+params.ug_N[77])+(-params.Pg_N_init[78]+params.Pg_N_avg[78]+params.ug_N[78])*(-params.Pg_N_init[78]+params.Pg_N_avg[78]+params.ug_N[78])+(-params.Pg_N_init[79]+params.Pg_N_avg[79]+params.ug_N[79])*(-params.Pg_N_init[79]+params.Pg_N_avg[79]+params.ug_N[79])+(-params.Pg_N_init[80]+params.Pg_N_avg[80]+params.ug_N[80])*(-params.Pg_N_init[80]+params.Pg_N_avg[80]+params.ug_N[80])+(-params.Pg_N_init[81]+params.Pg_N_avg[81]+params.ug_N[81])*(-params.Pg_N_init[81]+params.Pg_N_avg[81]+params.ug_N[81])+(-params.Pg_N_init[82]+params.Pg_N_avg[82]+params.ug_N[82])*(-params.Pg_N_init[82]+params.Pg_N_avg[82]+params.ug_N[82])+(-params.Pg_N_init[83]+params.Pg_N_avg[83]+params.ug_N[83])*(-params.Pg_N_init[83]+params.Pg_N_avg[83]+params.ug_N[83])+(-params.Pg_N_init[84]+params.Pg_N_avg[84]+params.ug_N[84])*(-params.Pg_N_init[84]+params.Pg_N_avg[84]+params.ug_N[84])+(-params.Pg_N_init[85]+params.Pg_N_avg[85]+params.ug_N[85])*(-params.Pg_N_init[85]+params.Pg_N_avg[85]+params.ug_N[85])+(-params.Pg_N_init[86]+params.Pg_N_avg[86]+params.ug_N[86])*(-params.Pg_N_init[86]+params.Pg_N_avg[86]+params.ug_N[86])+(-params.Pg_N_init[87]+params.Pg_N_avg[87]+params.ug_N[87])*(-params.Pg_N_init[87]+params.Pg_N_avg[87]+params.ug_N[87])+(-params.Pg_N_init[88]+params.Pg_N_avg[88]+params.ug_N[88])*(-params.Pg_N_init[88]+params.Pg_N_avg[88]+params.ug_N[88])+(-params.Pg_N_init[89]+params.Pg_N_avg[89]+params.ug_N[89])*(-params.Pg_N_init[89]+params.Pg_N_avg[89]+params.ug_N[89])+(-params.Pg_N_init[90]+params.Pg_N_avg[90]+params.ug_N[90])*(-params.Pg_N_init[90]+params.Pg_N_avg[90]+params.ug_N[90])+(-params.Pg_N_init[91]+params.Pg_N_avg[91]+params.ug_N[91])*(-params.Pg_N_init[91]+params.Pg_N_avg[91]+params.ug_N[91])+(-params.Pg_N_init[92]+params.Pg_N_avg[92]+params.ug_N[92])*(-params.Pg_N_init[92]+params.Pg_N_avg[92]+params.ug_N[92])+(-params.Pg_N_init[93]+params.Pg_N_avg[93]+params.ug_N[93])*(-params.Pg_N_init[93]+params.Pg_N_avg[93]+params.ug_N[93])+(-params.Pg_N_init[94]+params.Pg_N_avg[94]+params.ug_N[94])*(-params.Pg_N_init[94]+params.Pg_N_avg[94]+params.ug_N[94])+(-params.Pg_N_init[95]+params.Pg_N_avg[95]+params.ug_N[95])*(-params.Pg_N_init[95]+params.Pg_N_avg[95]+params.ug_N[95])+(-params.Pg_N_init[96]+params.Pg_N_avg[96]+params.ug_N[96])*(-params.Pg_N_init[96]+params.Pg_N_avg[96]+params.ug_N[96])+(-params.Pg_N_init[97]+params.Pg_N_avg[97]+params.ug_N[97])*(-params.Pg_N_init[97]+params.Pg_N_avg[97]+params.ug_N[97])+(-params.Pg_N_init[98]+params.Pg_N_avg[98]+params.ug_N[98])*(-params.Pg_N_init[98]+params.Pg_N_avg[98]+params.ug_N[98])+(-params.Pg_N_init[99]+params.Pg_N_avg[99]+params.ug_N[99])*(-params.Pg_N_init[99]+params.Pg_N_avg[99]+params.ug_N[99])+(-params.Pg_N_init[100]+params.Pg_N_avg[100]+params.ug_N[100])*(-params.Pg_N_init[100]+params.Pg_N_avg[100]+params.ug_N[100])+(-params.Pg_N_init[101]+params.Pg_N_avg[101]+params.ug_N[101])*(-params.Pg_N_init[101]+params.Pg_N_avg[101]+params.ug_N[101])+(-params.Pg_N_init[102]+params.Pg_N_avg[102]+params.ug_N[102])*(-params.Pg_N_init[102]+params.Pg_N_avg[102]+params.ug_N[102])+(-params.Pg_N_init[103]+params.Pg_N_avg[103]+params.ug_N[103])*(-params.Pg_N_init[103]+params.Pg_N_avg[103]+params.ug_N[103])+(-params.Pg_N_init[104]+params.Pg_N_avg[104]+params.ug_N[104])*(-params.Pg_N_init[104]+params.Pg_N_avg[104]+params.ug_N[104])+(-params.Pg_N_init[105]+params.Pg_N_avg[105]+params.ug_N[105])*(-params.Pg_N_init[105]+params.Pg_N_avg[105]+params.ug_N[105])+(-params.Pg_N_init[106]+params.Pg_N_avg[106]+params.ug_N[106])*(-params.Pg_N_init[106]+params.Pg_N_avg[106]+params.ug_N[106])+(-params.Pg_N_init[107]+params.Pg_N_avg[107]+params.ug_N[107])*(-params.Pg_N_init[107]+params.Pg_N_avg[107]+params.ug_N[107])+(-params.Pg_N_init[108]+params.Pg_N_avg[108]+params.ug_N[108])*(-params.Pg_N_init[108]+params.Pg_N_avg[108]+params.ug_N[108])+(-params.Pg_N_init[109]+params.Pg_N_avg[109]+params.ug_N[109])*(-params.Pg_N_init[109]+params.Pg_N_avg[109]+params.ug_N[109])+(-params.Pg_N_init[110]+params.Pg_N_avg[110]+params.ug_N[110])*(-params.Pg_N_init[110]+params.Pg_N_avg[110]+params.ug_N[110])+(-params.Pg_N_init[111]+params.Pg_N_avg[111]+params.ug_N[111])*(-params.Pg_N_init[111]+params.Pg_N_avg[111]+params.ug_N[111])+(-params.Pg_N_init[112]+params.Pg_N_avg[112]+params.ug_N[112])*(-params.Pg_N_init[112]+params.Pg_N_avg[112]+params.ug_N[112])+(-params.Pg_N_init[113]+params.Pg_N_avg[113]+params.ug_N[113])*(-params.Pg_N_init[113]+params.Pg_N_avg[113]+params.ug_N[113])+(-params.Pg_N_init[114]+params.Pg_N_avg[114]+params.ug_N[114])*(-params.Pg_N_init[114]+params.Pg_N_avg[114]+params.ug_N[114])+(-params.Pg_N_init[115]+params.Pg_N_avg[115]+params.ug_N[115])*(-params.Pg_N_init[115]+params.Pg_N_avg[115]+params.ug_N[115])+(-params.Pg_N_init[116]+params.Pg_N_avg[116]+params.ug_N[116])*(-params.Pg_N_init[116]+params.Pg_N_avg[116]+params.ug_N[116])+(-params.Pg_N_init[117]+params.Pg_N_avg[117]+params.ug_N[117])*(-params.Pg_N_init[117]+params.Pg_N_avg[117]+params.ug_N[117])+(-params.Pg_N_init[118]+params.Pg_N_avg[118]+params.ug_N[118])*(-params.Pg_N_init[118]+params.Pg_N_avg[118]+params.ug_N[118])+(-params.Pg_N_init[119]+params.Pg_N_avg[119]+params.ug_N[119])*(-params.Pg_N_init[119]+params.Pg_N_avg[119]+params.ug_N[119])+(-params.Pg_N_init[120]+params.Pg_N_avg[120]+params.ug_N[120])*(-params.Pg_N_init[120]+params.Pg_N_avg[120]+params.ug_N[120])+(-params.Pg_N_init[121]+params.Pg_N_avg[121]+params.ug_N[121])*(-params.Pg_N_init[121]+params.Pg_N_avg[121]+params.ug_N[121])+(-params.Pg_N_init[122]+params.Pg_N_avg[122]+params.ug_N[122])*(-params.Pg_N_init[122]+params.Pg_N_avg[122]+params.ug_N[122])+(-params.Pg_N_init[123]+params.Pg_N_avg[123]+params.ug_N[123])*(-params.Pg_N_init[123]+params.Pg_N_avg[123]+params.ug_N[123])+(-params.Pg_N_init[124]+params.Pg_N_avg[124]+params.ug_N[124])*(-params.Pg_N_init[124]+params.Pg_N_avg[124]+params.ug_N[124])+(-params.Pg_N_init[125]+params.Pg_N_avg[125]+params.ug_N[125])*(-params.Pg_N_init[125]+params.Pg_N_avg[125]+params.ug_N[125])+(-params.Pg_N_init[126]+params.Pg_N_avg[126]+params.ug_N[126])*(-params.Pg_N_init[126]+params.Pg_N_avg[126]+params.ug_N[126])+(-params.Pg_N_init[127]+params.Pg_N_avg[127]+params.ug_N[127])*(-params.Pg_N_init[127]+params.Pg_N_avg[127]+params.ug_N[127])+(-params.Pg_N_init[128]+params.Pg_N_avg[128]+params.ug_N[128])*(-params.Pg_N_init[128]+params.Pg_N_avg[128]+params.ug_N[128])+(-params.Pg_N_init[129]+params.Pg_N_avg[129]+params.ug_N[129])*(-params.Pg_N_init[129]+params.Pg_N_avg[129]+params.ug_N[129])+(-params.Pg_N_init[130]+params.Pg_N_avg[130]+params.ug_N[130])*(-params.Pg_N_init[130]+params.Pg_N_avg[130]+params.ug_N[130])+(-params.Pg_N_init[131]+params.Pg_N_avg[131]+params.ug_N[131])*(-params.Pg_N_init[131]+params.Pg_N_avg[131]+params.ug_N[131])+(-params.Pg_N_init[132]+params.Pg_N_avg[132]+params.ug_N[132])*(-params.Pg_N_init[132]+params.Pg_N_avg[132]+params.ug_N[132])+(-params.Pg_N_init[133]+params.Pg_N_avg[133]+params.ug_N[133])*(-params.Pg_N_init[133]+params.Pg_N_avg[133]+params.ug_N[133])+(-params.Pg_N_init[134]+params.Pg_N_avg[134]+params.ug_N[134])*(-params.Pg_N_init[134]+params.Pg_N_avg[134]+params.ug_N[134])+(-params.Pg_N_init[135]+params.Pg_N_avg[135]+params.ug_N[135])*(-params.Pg_N_init[135]+params.Pg_N_avg[135]+params.ug_N[135])+(-params.Pg_N_init[136]+params.Pg_N_avg[136]+params.ug_N[136])*(-params.Pg_N_init[136]+params.Pg_N_avg[136]+params.ug_N[136])+(-params.Pg_N_init[137]+params.Pg_N_avg[137]+params.ug_N[137])*(-params.Pg_N_init[137]+params.Pg_N_avg[137]+params.ug_N[137])+(-params.Pg_N_init[138]+params.Pg_N_avg[138]+params.ug_N[138])*(-params.Pg_N_init[138]+params.Pg_N_avg[138]+params.ug_N[138])+(-params.Pg_N_init[139]+params.Pg_N_avg[139]+params.ug_N[139])*(-params.Pg_N_init[139]+params.Pg_N_avg[139]+params.ug_N[139])+(-params.Pg_N_init[140]+params.Pg_N_avg[140]+params.ug_N[140])*(-params.Pg_N_init[140]+params.Pg_N_avg[140]+params.ug_N[140])+(-params.Pg_N_init[141]+params.Pg_N_avg[141]+params.ug_N[141])*(-params.Pg_N_init[141]+params.Pg_N_avg[141]+params.ug_N[141])+(-params.Pg_N_init[142]+params.Pg_N_avg[142]+params.ug_N[142])*(-params.Pg_N_init[142]+params.Pg_N_avg[142]+params.ug_N[142])+(-params.Pg_N_init[143]+params.Pg_N_avg[143]+params.ug_N[143])*(-params.Pg_N_init[143]+params.Pg_N_avg[143]+params.ug_N[143])+(-params.Pg_N_init[144]+params.Pg_N_avg[144]+params.ug_N[144])*(-params.Pg_N_init[144]+params.Pg_N_avg[144]+params.ug_N[144])+(-params.Pg_N_init[145]+params.Pg_N_avg[145]+params.ug_N[145])*(-params.Pg_N_init[145]+params.Pg_N_avg[145]+params.ug_N[145])+(-params.Pg_N_init[146]+params.Pg_N_avg[146]+params.ug_N[146])*(-params.Pg_N_init[146]+params.Pg_N_avg[146]+params.ug_N[146])+(-params.Pg_N_init[147]+params.Pg_N_avg[147]+params.ug_N[147])*(-params.Pg_N_init[147]+params.Pg_N_avg[147]+params.ug_N[147])+(-params.Pg_N_init[148]+params.Pg_N_avg[148]+params.ug_N[148])*(-params.Pg_N_init[148]+params.Pg_N_avg[148]+params.ug_N[148])+(-params.Pg_N_init[149]+params.Pg_N_avg[149]+params.ug_N[149])*(-params.Pg_N_init[149]+params.Pg_N_avg[149]+params.ug_N[149])+(-params.Pg_N_init[150]+params.Pg_N_avg[150]+params.ug_N[150])*(-params.Pg_N_init[150]+params.Pg_N_avg[150]+params.ug_N[150])+(-params.Pg_N_init[151]+params.Pg_N_avg[151]+params.ug_N[151])*(-params.Pg_N_init[151]+params.Pg_N_avg[151]+params.ug_N[151])+(-params.Pg_N_init[152]+params.Pg_N_avg[152]+params.ug_N[152])*(-params.Pg_N_init[152]+params.Pg_N_avg[152]+params.ug_N[152])+(-params.Pg_N_init[153]+params.Pg_N_avg[153]+params.ug_N[153])*(-params.Pg_N_init[153]+params.Pg_N_avg[153]+params.ug_N[153])+(-params.Pg_N_init[154]+params.Pg_N_avg[154]+params.ug_N[154])*(-params.Pg_N_init[154]+params.Pg_N_avg[154]+params.ug_N[154])+(-params.Pg_N_init[155]+params.Pg_N_avg[155]+params.ug_N[155])*(-params.Pg_N_init[155]+params.Pg_N_avg[155]+params.ug_N[155])+(-params.Pg_N_init[156]+params.Pg_N_avg[156]+params.ug_N[156])*(-params.Pg_N_init[156]+params.Pg_N_avg[156]+params.ug_N[156])+(-params.Pg_N_init[157]+params.Pg_N_avg[157]+params.ug_N[157])*(-params.Pg_N_init[157]+params.Pg_N_avg[157]+params.ug_N[157])+(-params.Pg_N_init[158]+params.Pg_N_avg[158]+params.ug_N[158])*(-params.Pg_N_init[158]+params.Pg_N_avg[158]+params.ug_N[158])+(-params.Pg_N_init[159]+params.Pg_N_avg[159]+params.ug_N[159])*(-params.Pg_N_init[159]+params.Pg_N_avg[159]+params.ug_N[159])+(-params.Pg_N_init[160]+params.Pg_N_avg[160]+params.ug_N[160])*(-params.Pg_N_init[160]+params.Pg_N_avg[160]+params.ug_N[160])+(-params.Pg_N_init[161]+params.Pg_N_avg[161]+params.ug_N[161])*(-params.Pg_N_init[161]+params.Pg_N_avg[161]+params.ug_N[161])+(-params.Pg_N_init[162]+params.Pg_N_avg[162]+params.ug_N[162])*(-params.Pg_N_init[162]+params.Pg_N_avg[162]+params.ug_N[162])+(-params.Pg_N_init[163]+params.Pg_N_avg[163]+params.ug_N[163])*(-params.Pg_N_init[163]+params.Pg_N_avg[163]+params.ug_N[163])+(-params.Pg_N_init[164]+params.Pg_N_avg[164]+params.ug_N[164])*(-params.Pg_N_init[164]+params.Pg_N_avg[164]+params.ug_N[164])+(-params.Pg_N_init[165]+params.Pg_N_avg[165]+params.ug_N[165])*(-params.Pg_N_init[165]+params.Pg_N_avg[165]+params.ug_N[165])+(-params.Pg_N_init[166]+params.Pg_N_avg[166]+params.ug_N[166])*(-params.Pg_N_init[166]+params.Pg_N_avg[166]+params.ug_N[166])+(-params.Pg_N_init[167]+params.Pg_N_avg[167]+params.ug_N[167])*(-params.Pg_N_init[167]+params.Pg_N_avg[167]+params.ug_N[167])+(-params.Pg_N_init[168]+params.Pg_N_avg[168]+params.ug_N[168])*(-params.Pg_N_init[168]+params.Pg_N_avg[168]+params.ug_N[168])+(-params.Pg_N_init[169]+params.Pg_N_avg[169]+params.ug_N[169])*(-params.Pg_N_init[169]+params.Pg_N_avg[169]+params.ug_N[169])+(-params.Pg_N_init[170]+params.Pg_N_avg[170]+params.ug_N[170])*(-params.Pg_N_init[170]+params.Pg_N_avg[170]+params.ug_N[170])+(-params.Pg_N_init[171]+params.Pg_N_avg[171]+params.ug_N[171])*(-params.Pg_N_init[171]+params.Pg_N_avg[171]+params.ug_N[171])+(-params.Pg_N_init[172]+params.Pg_N_avg[172]+params.ug_N[172])*(-params.Pg_N_init[172]+params.Pg_N_avg[172]+params.ug_N[172])+(-params.Pg_N_init[173]+params.Pg_N_avg[173]+params.ug_N[173])*(-params.Pg_N_init[173]+params.Pg_N_avg[173]+params.ug_N[173])+(-params.Pg_N_init[174]+params.Pg_N_avg[174]+params.ug_N[174])*(-params.Pg_N_init[174]+params.Pg_N_avg[174]+params.ug_N[174])+(-params.Pg_N_init[175]+params.Pg_N_avg[175]+params.ug_N[175])*(-params.Pg_N_init[175]+params.Pg_N_avg[175]+params.ug_N[175])+(-params.Pg_N_init[176]+params.Pg_N_avg[176]+params.ug_N[176])*(-params.Pg_N_init[176]+params.Pg_N_avg[176]+params.ug_N[176])+(-params.Pg_N_init[177]+params.Pg_N_avg[177]+params.ug_N[177])*(-params.Pg_N_init[177]+params.Pg_N_avg[177]+params.ug_N[177])+(-params.Pg_N_init[178]+params.Pg_N_avg[178]+params.ug_N[178])*(-params.Pg_N_init[178]+params.Pg_N_avg[178]+params.ug_N[178])+(-params.Pg_N_init[179]+params.Pg_N_avg[179]+params.ug_N[179])*(-params.Pg_N_init[179]+params.Pg_N_avg[179]+params.ug_N[179])+(-params.Pg_N_init[180]+params.Pg_N_avg[180]+params.ug_N[180])*(-params.Pg_N_init[180]+params.Pg_N_avg[180]+params.ug_N[180])+(-params.Pg_N_init[181]+params.Pg_N_avg[181]+params.ug_N[181])*(-params.Pg_N_init[181]+params.Pg_N_avg[181]+params.ug_N[181])+(-params.Pg_N_init[182]+params.Pg_N_avg[182]+params.ug_N[182])*(-params.Pg_N_init[182]+params.Pg_N_avg[182]+params.ug_N[182])+(-params.Pg_N_init[183]+params.Pg_N_avg[183]+params.ug_N[183])*(-params.Pg_N_init[183]+params.Pg_N_avg[183]+params.ug_N[183])+(-params.Pg_N_init[184]+params.Pg_N_avg[184]+params.ug_N[184])*(-params.Pg_N_init[184]+params.Pg_N_avg[184]+params.ug_N[184])+(-params.Pg_N_init[185]+params.Pg_N_avg[185]+params.ug_N[185])*(-params.Pg_N_init[185]+params.Pg_N_avg[185]+params.ug_N[185])+(-params.Pg_N_init[186]+params.Pg_N_avg[186]+params.ug_N[186])*(-params.Pg_N_init[186]+params.Pg_N_avg[186]+params.ug_N[186])+(-params.Pg_N_init[187]+params.Pg_N_avg[187]+params.ug_N[187])*(-params.Pg_N_init[187]+params.Pg_N_avg[187]+params.ug_N[187])+(-params.Pg_N_init[188]+params.Pg_N_avg[188]+params.ug_N[188])*(-params.Pg_N_init[188]+params.Pg_N_avg[188]+params.ug_N[188])+(-params.Pg_N_init[189]+params.Pg_N_avg[189]+params.ug_N[189])*(-params.Pg_N_init[189]+params.Pg_N_avg[189]+params.ug_N[189])+(-params.Pg_N_init[190]+params.Pg_N_avg[190]+params.ug_N[190])*(-params.Pg_N_init[190]+params.Pg_N_avg[190]+params.ug_N[190])+(-params.Pg_N_init[191]+params.Pg_N_avg[191]+params.ug_N[191])*(-params.Pg_N_init[191]+params.Pg_N_avg[191]+params.ug_N[191])+(-params.Pg_N_init[192]+params.Pg_N_avg[192]+params.ug_N[192])*(-params.Pg_N_init[192]+params.Pg_N_avg[192]+params.ug_N[192])+(-params.Pg_N_init[193]+params.Pg_N_avg[193]+params.ug_N[193])*(-params.Pg_N_init[193]+params.Pg_N_avg[193]+params.ug_N[193])+(-params.Pg_N_init[194]+params.Pg_N_avg[194]+params.ug_N[194])*(-params.Pg_N_init[194]+params.Pg_N_avg[194]+params.ug_N[194])+(-params.Pg_N_init[195]+params.Pg_N_avg[195]+params.ug_N[195])*(-params.Pg_N_init[195]+params.Pg_N_avg[195]+params.ug_N[195])+(-params.Pg_N_init[196]+params.Pg_N_avg[196]+params.ug_N[196])*(-params.Pg_N_init[196]+params.Pg_N_avg[196]+params.ug_N[196])+(-params.Pg_N_init[197]+params.Pg_N_avg[197]+params.ug_N[197])*(-params.Pg_N_init[197]+params.Pg_N_avg[197]+params.ug_N[197])+(-params.Pg_N_init[198]+params.Pg_N_avg[198]+params.ug_N[198])*(-params.Pg_N_init[198]+params.Pg_N_avg[198]+params.ug_N[198])+(-params.Pg_N_init[199]+params.Pg_N_avg[199]+params.ug_N[199])*(-params.Pg_N_init[199]+params.Pg_N_avg[199]+params.ug_N[199])+(-params.Pg_N_init[200]+params.Pg_N_avg[200]+params.ug_N[200])*(-params.Pg_N_init[200]+params.Pg_N_avg[200]+params.ug_N[200])+(-params.Pg_N_init[201]+params.Pg_N_avg[201]+params.ug_N[201])*(-params.Pg_N_init[201]+params.Pg_N_avg[201]+params.ug_N[201])+(-params.Pg_N_init[202]+params.Pg_N_avg[202]+params.ug_N[202])*(-params.Pg_N_init[202]+params.Pg_N_avg[202]+params.ug_N[202])+(-params.Pg_N_init[203]+params.Pg_N_avg[203]+params.ug_N[203])*(-params.Pg_N_init[203]+params.Pg_N_avg[203]+params.ug_N[203])+(-params.Pg_N_init[204]+params.Pg_N_avg[204]+params.ug_N[204])*(-params.Pg_N_init[204]+params.Pg_N_avg[204]+params.ug_N[204])+(-params.Pg_N_init[205]+params.Pg_N_avg[205]+params.ug_N[205])*(-params.Pg_N_init[205]+params.Pg_N_avg[205]+params.ug_N[205])+(-params.Pg_N_init[206]+params.Pg_N_avg[206]+params.ug_N[206])*(-params.Pg_N_init[206]+params.Pg_N_avg[206]+params.ug_N[206])+(-params.Pg_N_init[207]+params.Pg_N_avg[207]+params.ug_N[207])*(-params.Pg_N_init[207]+params.Pg_N_avg[207]+params.ug_N[207])+(-params.Pg_N_init[208]+params.Pg_N_avg[208]+params.ug_N[208])*(-params.Pg_N_init[208]+params.Pg_N_avg[208]+params.ug_N[208])+(-params.Pg_N_init[209]+params.Pg_N_avg[209]+params.ug_N[209])*(-params.Pg_N_init[209]+params.Pg_N_avg[209]+params.ug_N[209])+(-params.Pg_N_init[210]+params.Pg_N_avg[210]+params.ug_N[210])*(-params.Pg_N_init[210]+params.Pg_N_avg[210]+params.ug_N[210])+(-params.Pg_N_init[211]+params.Pg_N_avg[211]+params.ug_N[211])*(-params.Pg_N_init[211]+params.Pg_N_avg[211]+params.ug_N[211])+(-params.Pg_N_init[212]+params.Pg_N_avg[212]+params.ug_N[212])*(-params.Pg_N_init[212]+params.Pg_N_avg[212]+params.ug_N[212])+(-params.Pg_N_init[213]+params.Pg_N_avg[213]+params.ug_N[213])*(-params.Pg_N_init[213]+params.Pg_N_avg[213]+params.ug_N[213])+(-params.Pg_N_init[214]+params.Pg_N_avg[214]+params.ug_N[214])*(-params.Pg_N_init[214]+params.Pg_N_avg[214]+params.ug_N[214])+(-params.Pg_N_init[215]+params.Pg_N_avg[215]+params.ug_N[215])*(-params.Pg_N_init[215]+params.Pg_N_avg[215]+params.ug_N[215])+(-params.Pg_N_init[216]+params.Pg_N_avg[216]+params.ug_N[216])*(-params.Pg_N_init[216]+params.Pg_N_avg[216]+params.ug_N[216])+(-params.Pg_N_init[217]+params.Pg_N_avg[217]+params.ug_N[217])*(-params.Pg_N_init[217]+params.Pg_N_avg[217]+params.ug_N[217])+(-params.Pg_N_init[218]+params.Pg_N_avg[218]+params.ug_N[218])*(-params.Pg_N_init[218]+params.Pg_N_avg[218]+params.ug_N[218])+(-params.Pg_N_init[219]+params.Pg_N_avg[219]+params.ug_N[219])*(-params.Pg_N_init[219]+params.Pg_N_avg[219]+params.ug_N[219])+(-params.Pg_N_init[220]+params.Pg_N_avg[220]+params.ug_N[220])*(-params.Pg_N_init[220]+params.Pg_N_avg[220]+params.ug_N[220])+(-params.Pg_N_init[221]+params.Pg_N_avg[221]+params.ug_N[221])*(-params.Pg_N_init[221]+params.Pg_N_avg[221]+params.ug_N[221])+(-params.Pg_N_init[222]+params.Pg_N_avg[222]+params.ug_N[222])*(-params.Pg_N_init[222]+params.Pg_N_avg[222]+params.ug_N[222])+(-params.Pg_N_init[223]+params.Pg_N_avg[223]+params.ug_N[223])*(-params.Pg_N_init[223]+params.Pg_N_avg[223]+params.ug_N[223])+(-params.Pg_N_init[224]+params.Pg_N_avg[224]+params.ug_N[224])*(-params.Pg_N_init[224]+params.Pg_N_avg[224]+params.ug_N[224])+(-params.Pg_N_init[225]+params.Pg_N_avg[225]+params.ug_N[225])*(-params.Pg_N_init[225]+params.Pg_N_avg[225]+params.ug_N[225])+(-params.Pg_N_init[226]+params.Pg_N_avg[226]+params.ug_N[226])*(-params.Pg_N_init[226]+params.Pg_N_avg[226]+params.ug_N[226])+(-params.Pg_N_init[227]+params.Pg_N_avg[227]+params.ug_N[227])*(-params.Pg_N_init[227]+params.Pg_N_avg[227]+params.ug_N[227])+(-params.Pg_N_init[228]+params.Pg_N_avg[228]+params.ug_N[228])*(-params.Pg_N_init[228]+params.Pg_N_avg[228]+params.ug_N[228])+(-params.Pg_N_init[229]+params.Pg_N_avg[229]+params.ug_N[229])*(-params.Pg_N_init[229]+params.Pg_N_avg[229]+params.ug_N[229])+(-params.Pg_N_init[230]+params.Pg_N_avg[230]+params.ug_N[230])*(-params.Pg_N_init[230]+params.Pg_N_avg[230]+params.ug_N[230])+(-params.Pg_N_init[231]+params.Pg_N_avg[231]+params.ug_N[231])*(-params.Pg_N_init[231]+params.Pg_N_avg[231]+params.ug_N[231])+(-params.Pg_N_init[232]+params.Pg_N_avg[232]+params.ug_N[232])*(-params.Pg_N_init[232]+params.Pg_N_avg[232]+params.ug_N[232])+(-params.Pg_N_init[233]+params.Pg_N_avg[233]+params.ug_N[233])*(-params.Pg_N_init[233]+params.Pg_N_avg[233]+params.ug_N[233])+(-params.Pg_N_init[234]+params.Pg_N_avg[234]+params.ug_N[234])*(-params.Pg_N_init[234]+params.Pg_N_avg[234]+params.ug_N[234])+(-params.Pg_N_init[235]+params.Pg_N_avg[235]+params.ug_N[235])*(-params.Pg_N_init[235]+params.Pg_N_avg[235]+params.ug_N[235])+(-params.Pg_N_init[236]+params.Pg_N_avg[236]+params.ug_N[236])*(-params.Pg_N_init[236]+params.Pg_N_avg[236]+params.ug_N[236])+(-params.Pg_N_init[237]+params.Pg_N_avg[237]+params.ug_N[237])*(-params.Pg_N_init[237]+params.Pg_N_avg[237]+params.ug_N[237])+(-params.Pg_N_init[238]+params.Pg_N_avg[238]+params.ug_N[238])*(-params.Pg_N_init[238]+params.Pg_N_avg[238]+params.ug_N[238])+(-params.Pg_N_init[239]+params.Pg_N_avg[239]+params.ug_N[239])*(-params.Pg_N_init[239]+params.Pg_N_avg[239]+params.ug_N[239])+(-params.Pg_N_init[240]+params.Pg_N_avg[240]+params.ug_N[240])*(-params.Pg_N_init[240]+params.Pg_N_avg[240]+params.ug_N[240])+(-params.Pg_N_init[241]+params.Pg_N_avg[241]+params.ug_N[241])*(-params.Pg_N_init[241]+params.Pg_N_avg[241]+params.ug_N[241])+(-params.Pg_N_init[242]+params.Pg_N_avg[242]+params.ug_N[242])*(-params.Pg_N_init[242]+params.Pg_N_avg[242]+params.ug_N[242])+(-params.Pg_N_init[243]+params.Pg_N_avg[243]+params.ug_N[243])*(-params.Pg_N_init[243]+params.Pg_N_avg[243]+params.ug_N[243])+(-params.Pg_N_init[244]+params.Pg_N_avg[244]+params.ug_N[244])*(-params.Pg_N_init[244]+params.Pg_N_avg[244]+params.ug_N[244])+(-params.Pg_N_init[245]+params.Pg_N_avg[245]+params.ug_N[245])*(-params.Pg_N_init[245]+params.Pg_N_avg[245]+params.ug_N[245])+(-params.Pg_N_init[246]+params.Pg_N_avg[246]+params.ug_N[246])*(-params.Pg_N_init[246]+params.Pg_N_avg[246]+params.ug_N[246])+(-params.Pg_N_init[247]+params.Pg_N_avg[247]+params.ug_N[247])*(-params.Pg_N_init[247]+params.Pg_N_avg[247]+params.ug_N[247])+(-params.Pg_N_init[248]+params.Pg_N_avg[248]+params.ug_N[248])*(-params.Pg_N_init[248]+params.Pg_N_avg[248]+params.ug_N[248])+(-params.Pg_N_init[249]+params.Pg_N_avg[249]+params.ug_N[249])*(-params.Pg_N_init[249]+params.Pg_N_avg[249]+params.ug_N[249])+(-params.Pg_N_init[250]+params.Pg_N_avg[250]+params.ug_N[250])*(-params.Pg_N_init[250]+params.Pg_N_avg[250]+params.ug_N[250])+(-params.Pg_N_init[251]+params.Pg_N_avg[251]+params.ug_N[251])*(-params.Pg_N_init[251]+params.Pg_N_avg[251]+params.ug_N[251])+(-params.Pg_N_init[252]+params.Pg_N_avg[252]+params.ug_N[252])*(-params.Pg_N_init[252]+params.Pg_N_avg[252]+params.ug_N[252])+(-params.Pg_N_init[253]+params.Pg_N_avg[253]+params.ug_N[253])*(-params.Pg_N_init[253]+params.Pg_N_avg[253]+params.ug_N[253])+(-params.Pg_N_init[254]+params.Pg_N_avg[254]+params.ug_N[254])*(-params.Pg_N_init[254]+params.Pg_N_avg[254]+params.ug_N[254])+(-params.Pg_N_init[255]+params.Pg_N_avg[255]+params.ug_N[255])*(-params.Pg_N_init[255]+params.Pg_N_avg[255]+params.ug_N[255])+(-params.Pg_N_init[256]+params.Pg_N_avg[256]+params.ug_N[256])*(-params.Pg_N_init[256]+params.Pg_N_avg[256]+params.ug_N[256])+(-params.Pg_N_init[257]+params.Pg_N_avg[257]+params.ug_N[257])*(-params.Pg_N_init[257]+params.Pg_N_avg[257]+params.ug_N[257])+(-params.Pg_N_init[258]+params.Pg_N_avg[258]+params.ug_N[258])*(-params.Pg_N_init[258]+params.Pg_N_avg[258]+params.ug_N[258])+(-params.Pg_N_init[259]+params.Pg_N_avg[259]+params.ug_N[259])*(-params.Pg_N_init[259]+params.Pg_N_avg[259]+params.ug_N[259])+(-params.Pg_N_init[260]+params.Pg_N_avg[260]+params.ug_N[260])*(-params.Pg_N_init[260]+params.Pg_N_avg[260]+params.ug_N[260])+(-params.Pg_N_init[261]+params.Pg_N_avg[261]+params.ug_N[261])*(-params.Pg_N_init[261]+params.Pg_N_avg[261]+params.ug_N[261])+(-params.Pg_N_init[262]+params.Pg_N_avg[262]+params.ug_N[262])*(-params.Pg_N_init[262]+params.Pg_N_avg[262]+params.ug_N[262])+(-params.Pg_N_init[263]+params.Pg_N_avg[263]+params.ug_N[263])*(-params.Pg_N_init[263]+params.Pg_N_avg[263]+params.ug_N[263])+(-params.Pg_N_init[264]+params.Pg_N_avg[264]+params.ug_N[264])*(-params.Pg_N_init[264]+params.Pg_N_avg[264]+params.ug_N[264])+(-params.Pg_N_init[265]+params.Pg_N_avg[265]+params.ug_N[265])*(-params.Pg_N_init[265]+params.Pg_N_avg[265]+params.ug_N[265])+(-params.Pg_N_init[266]+params.Pg_N_avg[266]+params.ug_N[266])*(-params.Pg_N_init[266]+params.Pg_N_avg[266]+params.ug_N[266])+(-params.Pg_N_init[267]+params.Pg_N_avg[267]+params.ug_N[267])*(-params.Pg_N_init[267]+params.Pg_N_avg[267]+params.ug_N[267])+(-params.Pg_N_init[268]+params.Pg_N_avg[268]+params.ug_N[268])*(-params.Pg_N_init[268]+params.Pg_N_avg[268]+params.ug_N[268])+(-params.Pg_N_init[269]+params.Pg_N_avg[269]+params.ug_N[269])*(-params.Pg_N_init[269]+params.Pg_N_avg[269]+params.ug_N[269])+(-params.Pg_N_init[270]+params.Pg_N_avg[270]+params.ug_N[270])*(-params.Pg_N_init[270]+params.Pg_N_avg[270]+params.ug_N[270])+(-params.Pg_N_init[271]+params.Pg_N_avg[271]+params.ug_N[271])*(-params.Pg_N_init[271]+params.Pg_N_avg[271]+params.ug_N[271])+(-params.Pg_N_init[272]+params.Pg_N_avg[272]+params.ug_N[272])*(-params.Pg_N_init[272]+params.Pg_N_avg[272]+params.ug_N[272])+(-params.Pg_N_init[273]+params.Pg_N_avg[273]+params.ug_N[273])*(-params.Pg_N_init[273]+params.Pg_N_avg[273]+params.ug_N[273])+(-params.Pg_N_init[274]+params.Pg_N_avg[274]+params.ug_N[274])*(-params.Pg_N_init[274]+params.Pg_N_avg[274]+params.ug_N[274])+(-params.Pg_N_init[275]+params.Pg_N_avg[275]+params.ug_N[275])*(-params.Pg_N_init[275]+params.Pg_N_avg[275]+params.ug_N[275])+(-params.Pg_N_init[276]+params.Pg_N_avg[276]+params.ug_N[276])*(-params.Pg_N_init[276]+params.Pg_N_avg[276]+params.ug_N[276])+(-params.Pg_N_init[277]+params.Pg_N_avg[277]+params.ug_N[277])*(-params.Pg_N_init[277]+params.Pg_N_avg[277]+params.ug_N[277])+(-params.Pg_N_init[278]+params.Pg_N_avg[278]+params.ug_N[278])*(-params.Pg_N_init[278]+params.Pg_N_avg[278]+params.ug_N[278])+(-params.Pg_N_init[279]+params.Pg_N_avg[279]+params.ug_N[279])*(-params.Pg_N_init[279]+params.Pg_N_avg[279]+params.ug_N[279])+(-params.Pg_N_init[280]+params.Pg_N_avg[280]+params.ug_N[280])*(-params.Pg_N_init[280]+params.Pg_N_avg[280]+params.ug_N[280])+(-params.Pg_N_init[281]+params.Pg_N_avg[281]+params.ug_N[281])*(-params.Pg_N_init[281]+params.Pg_N_avg[281]+params.ug_N[281])+(-params.Pg_N_init[282]+params.Pg_N_avg[282]+params.ug_N[282])*(-params.Pg_N_init[282]+params.Pg_N_avg[282]+params.ug_N[282])+(-params.Pg_N_init[283]+params.Pg_N_avg[283]+params.ug_N[283])*(-params.Pg_N_init[283]+params.Pg_N_avg[283]+params.ug_N[283])+(-params.Pg_N_init[284]+params.Pg_N_avg[284]+params.ug_N[284])*(-params.Pg_N_init[284]+params.Pg_N_avg[284]+params.ug_N[284])+(-params.Pg_N_init[285]+params.Pg_N_avg[285]+params.ug_N[285])*(-params.Pg_N_init[285]+params.Pg_N_avg[285]+params.ug_N[285])+(-params.Pg_N_init[286]+params.Pg_N_avg[286]+params.ug_N[286])*(-params.Pg_N_init[286]+params.Pg_N_avg[286]+params.ug_N[286])+(-params.Pg_N_init[287]+params.Pg_N_avg[287]+params.ug_N[287])*(-params.Pg_N_init[287]+params.Pg_N_avg[287]+params.ug_N[287])+(-params.Pg_N_init[288]+params.Pg_N_avg[288]+params.ug_N[288])*(-params.Pg_N_init[288]+params.Pg_N_avg[288]+params.ug_N[288])+(-params.Pg_N_init[289]+params.Pg_N_avg[289]+params.ug_N[289])*(-params.Pg_N_init[289]+params.Pg_N_avg[289]+params.ug_N[289])+(-params.Pg_N_init[290]+params.Pg_N_avg[290]+params.ug_N[290])*(-params.Pg_N_init[290]+params.Pg_N_avg[290]+params.ug_N[290])+(-params.Pg_N_init[291]+params.Pg_N_avg[291]+params.ug_N[291])*(-params.Pg_N_init[291]+params.Pg_N_avg[291]+params.ug_N[291])+(-params.Pg_N_init[292]+params.Pg_N_avg[292]+params.ug_N[292])*(-params.Pg_N_init[292]+params.Pg_N_avg[292]+params.ug_N[292])+(-params.Pg_N_init[293]+params.Pg_N_avg[293]+params.ug_N[293])*(-params.Pg_N_init[293]+params.Pg_N_avg[293]+params.ug_N[293])+(-params.Pg_N_init[294]+params.Pg_N_avg[294]+params.ug_N[294])*(-params.Pg_N_init[294]+params.Pg_N_avg[294]+params.ug_N[294])+(-params.Pg_N_init[295]+params.Pg_N_avg[295]+params.ug_N[295])*(-params.Pg_N_init[295]+params.Pg_N_avg[295]+params.ug_N[295])+(-params.Pg_N_init[296]+params.Pg_N_avg[296]+params.ug_N[296])*(-params.Pg_N_init[296]+params.Pg_N_avg[296]+params.ug_N[296])+(-params.Pg_N_init[297]+params.Pg_N_avg[297]+params.ug_N[297])*(-params.Pg_N_init[297]+params.Pg_N_avg[297]+params.ug_N[297])+(-params.Pg_N_init[298]+params.Pg_N_avg[298]+params.ug_N[298])*(-params.Pg_N_init[298]+params.Pg_N_avg[298]+params.ug_N[298])+(-params.Pg_N_init[299]+params.Pg_N_avg[299]+params.ug_N[299])*(-params.Pg_N_init[299]+params.Pg_N_avg[299]+params.ug_N[299])+(-params.Pg_N_init[300]+params.Pg_N_avg[300]+params.ug_N[300])*(-params.Pg_N_init[300]+params.Pg_N_avg[300]+params.ug_N[300])+(-params.Pg_N_init[301]+params.Pg_N_avg[301]+params.ug_N[301])*(-params.Pg_N_init[301]+params.Pg_N_avg[301]+params.ug_N[301])+(-params.Pg_N_init[302]+params.Pg_N_avg[302]+params.ug_N[302])*(-params.Pg_N_init[302]+params.Pg_N_avg[302]+params.ug_N[302])+(-params.Pg_N_init[303]+params.Pg_N_avg[303]+params.ug_N[303])*(-params.Pg_N_init[303]+params.Pg_N_avg[303]+params.ug_N[303])+(-params.Pg_N_init[304]+params.Pg_N_avg[304]+params.ug_N[304])*(-params.Pg_N_init[304]+params.Pg_N_avg[304]+params.ug_N[304])+(-params.Pg_N_init[305]+params.Pg_N_avg[305]+params.ug_N[305])*(-params.Pg_N_init[305]+params.Pg_N_avg[305]+params.ug_N[305])+(-params.Pg_N_init[306]+params.Pg_N_avg[306]+params.ug_N[306])*(-params.Pg_N_init[306]+params.Pg_N_avg[306]+params.ug_N[306])+(-params.Pg_N_init[307]+params.Pg_N_avg[307]+params.ug_N[307])*(-params.Pg_N_init[307]+params.Pg_N_avg[307]+params.ug_N[307])+(-params.Pg_N_init[308]+params.Pg_N_avg[308]+params.ug_N[308])*(-params.Pg_N_init[308]+params.Pg_N_avg[308]+params.ug_N[308])+(-params.Pg_N_init[309]+params.Pg_N_avg[309]+params.ug_N[309])*(-params.Pg_N_init[309]+params.Pg_N_avg[309]+params.ug_N[309])+(-params.Pg_N_init[310]+params.Pg_N_avg[310]+params.ug_N[310])*(-params.Pg_N_init[310]+params.Pg_N_avg[310]+params.ug_N[310])+(-params.Pg_N_init[311]+params.Pg_N_avg[311]+params.ug_N[311])*(-params.Pg_N_init[311]+params.Pg_N_avg[311]+params.ug_N[311])+(-params.Pg_N_init[312]+params.Pg_N_avg[312]+params.ug_N[312])*(-params.Pg_N_init[312]+params.Pg_N_avg[312]+params.ug_N[312])+(-params.Pg_N_init[313]+params.Pg_N_avg[313]+params.ug_N[313])*(-params.Pg_N_init[313]+params.Pg_N_avg[313]+params.ug_N[313])+(-params.Pg_N_init[314]+params.Pg_N_avg[314]+params.ug_N[314])*(-params.Pg_N_init[314]+params.Pg_N_avg[314]+params.ug_N[314])+(-params.Pg_N_init[315]+params.Pg_N_avg[315]+params.ug_N[315])*(-params.Pg_N_init[315]+params.Pg_N_avg[315]+params.ug_N[315])+(-params.Pg_N_init[316]+params.Pg_N_avg[316]+params.ug_N[316])*(-params.Pg_N_init[316]+params.Pg_N_avg[316]+params.ug_N[316])+(-params.Pg_N_init[317]+params.Pg_N_avg[317]+params.ug_N[317])*(-params.Pg_N_init[317]+params.Pg_N_avg[317]+params.ug_N[317])+(-params.Pg_N_init[318]+params.Pg_N_avg[318]+params.ug_N[318])*(-params.Pg_N_init[318]+params.Pg_N_avg[318]+params.ug_N[318])+(-params.Pg_N_init[319]+params.Pg_N_avg[319]+params.ug_N[319])*(-params.Pg_N_init[319]+params.Pg_N_avg[319]+params.ug_N[319])+(-params.Pg_N_init[320]+params.Pg_N_avg[320]+params.ug_N[320])*(-params.Pg_N_init[320]+params.Pg_N_avg[320]+params.ug_N[320])+(-params.Pg_N_init[321]+params.Pg_N_avg[321]+params.ug_N[321])*(-params.Pg_N_init[321]+params.Pg_N_avg[321]+params.ug_N[321])+(-params.Pg_N_init[322]+params.Pg_N_avg[322]+params.ug_N[322])*(-params.Pg_N_init[322]+params.Pg_N_avg[322]+params.ug_N[322])+(-params.Pg_N_init[323]+params.Pg_N_avg[323]+params.ug_N[323])*(-params.Pg_N_init[323]+params.Pg_N_avg[323]+params.ug_N[323])+(-params.Pg_N_init[324]+params.Pg_N_avg[324]+params.ug_N[324])*(-params.Pg_N_init[324]+params.Pg_N_avg[324]+params.ug_N[324])+(-params.Pg_N_init[325]+params.Pg_N_avg[325]+params.ug_N[325])*(-params.Pg_N_init[325]+params.Pg_N_avg[325]+params.ug_N[325])+(-params.Pg_N_init[326]+params.Pg_N_avg[326]+params.ug_N[326])*(-params.Pg_N_init[326]+params.Pg_N_avg[326]+params.ug_N[326])+(-params.Pg_N_init[327]+params.Pg_N_avg[327]+params.ug_N[327])*(-params.Pg_N_init[327]+params.Pg_N_avg[327]+params.ug_N[327])+(-params.Pg_N_init[328]+params.Pg_N_avg[328]+params.ug_N[328])*(-params.Pg_N_init[328]+params.Pg_N_avg[328]+params.ug_N[328])+(-params.Pg_N_init[329]+params.Pg_N_avg[329]+params.ug_N[329])*(-params.Pg_N_init[329]+params.Pg_N_avg[329]+params.ug_N[329])+(-params.Pg_N_init[330]+params.Pg_N_avg[330]+params.ug_N[330])*(-params.Pg_N_init[330]+params.Pg_N_avg[330]+params.ug_N[330])+(-params.Pg_N_init[331]+params.Pg_N_avg[331]+params.ug_N[331])*(-params.Pg_N_init[331]+params.Pg_N_avg[331]+params.ug_N[331])+(-params.Pg_N_init[332]+params.Pg_N_avg[332]+params.ug_N[332])*(-params.Pg_N_init[332]+params.Pg_N_avg[332]+params.ug_N[332])+(-params.Pg_N_init[333]+params.Pg_N_avg[333]+params.ug_N[333])*(-params.Pg_N_init[333]+params.Pg_N_avg[333]+params.ug_N[333])+(-params.Pg_N_init[334]+params.Pg_N_avg[334]+params.ug_N[334])*(-params.Pg_N_init[334]+params.Pg_N_avg[334]+params.ug_N[334])+(-params.Pg_N_init[335]+params.Pg_N_avg[335]+params.ug_N[335])*(-params.Pg_N_init[335]+params.Pg_N_avg[335]+params.ug_N[335])+(-params.Pg_N_init[336]+params.Pg_N_avg[336]+params.ug_N[336])*(-params.Pg_N_init[336]+params.Pg_N_avg[336]+params.ug_N[336])+(-params.Pg_N_init[337]+params.Pg_N_avg[337]+params.ug_N[337])*(-params.Pg_N_init[337]+params.Pg_N_avg[337]+params.ug_N[337])+(-params.Pg_N_init[338]+params.Pg_N_avg[338]+params.ug_N[338])*(-params.Pg_N_init[338]+params.Pg_N_avg[338]+params.ug_N[338])+(-params.Pg_N_init[339]+params.Pg_N_avg[339]+params.ug_N[339])*(-params.Pg_N_init[339]+params.Pg_N_avg[339]+params.ug_N[339])+(-params.Pg_N_init[340]+params.Pg_N_avg[340]+params.ug_N[340])*(-params.Pg_N_init[340]+params.Pg_N_avg[340]+params.ug_N[340])+(-params.Pg_N_init[341]+params.Pg_N_avg[341]+params.ug_N[341])*(-params.Pg_N_init[341]+params.Pg_N_avg[341]+params.ug_N[341])+(-params.Pg_N_init[342]+params.Pg_N_avg[342]+params.ug_N[342])*(-params.Pg_N_init[342]+params.Pg_N_avg[342]+params.ug_N[342])+(-params.Pg_N_init[343]+params.Pg_N_avg[343]+params.ug_N[343])*(-params.Pg_N_init[343]+params.Pg_N_avg[343]+params.ug_N[343])+(-params.Pg_N_init[344]+params.Pg_N_avg[344]+params.ug_N[344])*(-params.Pg_N_init[344]+params.Pg_N_avg[344]+params.ug_N[344])+(-params.Pg_N_init[345]+params.Pg_N_avg[345]+params.ug_N[345])*(-params.Pg_N_init[345]+params.Pg_N_avg[345]+params.ug_N[345])+(-params.Pg_N_init[346]+params.Pg_N_avg[346]+params.ug_N[346])*(-params.Pg_N_init[346]+params.Pg_N_avg[346]+params.ug_N[346])+(-params.Pg_N_init[347]+params.Pg_N_avg[347]+params.ug_N[347])*(-params.Pg_N_init[347]+params.Pg_N_avg[347]+params.ug_N[347])+(-params.Pg_N_init[348]+params.Pg_N_avg[348]+params.ug_N[348])*(-params.Pg_N_init[348]+params.Pg_N_avg[348]+params.ug_N[348])+(-params.Pg_N_init[349]+params.Pg_N_avg[349]+params.ug_N[349])*(-params.Pg_N_init[349]+params.Pg_N_avg[349]+params.ug_N[349])+(-params.Pg_N_init[350]+params.Pg_N_avg[350]+params.ug_N[350])*(-params.Pg_N_init[350]+params.Pg_N_avg[350]+params.ug_N[350])+(-params.Pg_N_init[351]+params.Pg_N_avg[351]+params.ug_N[351])*(-params.Pg_N_init[351]+params.Pg_N_avg[351]+params.ug_N[351])+(-params.Pg_N_init[352]+params.Pg_N_avg[352]+params.ug_N[352])*(-params.Pg_N_init[352]+params.Pg_N_avg[352]+params.ug_N[352])+(-params.Pg_N_init[353]+params.Pg_N_avg[353]+params.ug_N[353])*(-params.Pg_N_init[353]+params.Pg_N_avg[353]+params.ug_N[353])+(-params.Pg_N_init[354]+params.Pg_N_avg[354]+params.ug_N[354])*(-params.Pg_N_init[354]+params.Pg_N_avg[354]+params.ug_N[354])+(-params.Pg_N_init[355]+params.Pg_N_avg[355]+params.ug_N[355])*(-params.Pg_N_init[355]+params.Pg_N_avg[355]+params.ug_N[355])+(-params.Pg_N_init[356]+params.Pg_N_avg[356]+params.ug_N[356])*(-params.Pg_N_init[356]+params.Pg_N_avg[356]+params.ug_N[356])+(-params.Pg_N_init[357]+params.Pg_N_avg[357]+params.ug_N[357])*(-params.Pg_N_init[357]+params.Pg_N_avg[357]+params.ug_N[357])+(-params.Pg_N_init[358]+params.Pg_N_avg[358]+params.ug_N[358])*(-params.Pg_N_init[358]+params.Pg_N_avg[358]+params.ug_N[358])+(-params.Pg_N_init[359]+params.Pg_N_avg[359]+params.ug_N[359])*(-params.Pg_N_init[359]+params.Pg_N_avg[359]+params.ug_N[359])+(-params.Pg_N_init[360]+params.Pg_N_avg[360]+params.ug_N[360])*(-params.Pg_N_init[360]+params.Pg_N_avg[360]+params.ug_N[360])+(-params.Pg_N_init[361]+params.Pg_N_avg[361]+params.ug_N[361])*(-params.Pg_N_init[361]+params.Pg_N_avg[361]+params.ug_N[361])+(-params.Pg_N_init[362]+params.Pg_N_avg[362]+params.ug_N[362])*(-params.Pg_N_init[362]+params.Pg_N_avg[362]+params.ug_N[362])+(-params.Pg_N_init[363]+params.Pg_N_avg[363]+params.ug_N[363])*(-params.Pg_N_init[363]+params.Pg_N_avg[363]+params.ug_N[363])+(-params.Pg_N_init[364]+params.Pg_N_avg[364]+params.ug_N[364])*(-params.Pg_N_init[364]+params.Pg_N_avg[364]+params.ug_N[364])+(-params.Pg_N_init[365]+params.Pg_N_avg[365]+params.ug_N[365])*(-params.Pg_N_init[365]+params.Pg_N_avg[365]+params.ug_N[365])+(-params.Pg_N_init[366]+params.Pg_N_avg[366]+params.ug_N[366])*(-params.Pg_N_init[366]+params.Pg_N_avg[366]+params.ug_N[366])+(-params.Pg_N_init[367]+params.Pg_N_avg[367]+params.ug_N[367])*(-params.Pg_N_init[367]+params.Pg_N_avg[367]+params.ug_N[367])+(-params.Pg_N_init[368]+params.Pg_N_avg[368]+params.ug_N[368])*(-params.Pg_N_init[368]+params.Pg_N_avg[368]+params.ug_N[368])+(-params.Pg_N_init[369]+params.Pg_N_avg[369]+params.ug_N[369])*(-params.Pg_N_init[369]+params.Pg_N_avg[369]+params.ug_N[369])+(-params.Pg_N_init[370]+params.Pg_N_avg[370]+params.ug_N[370])*(-params.Pg_N_init[370]+params.Pg_N_avg[370]+params.ug_N[370])+(-params.Pg_N_init[371]+params.Pg_N_avg[371]+params.ug_N[371])*(-params.Pg_N_init[371]+params.Pg_N_avg[371]+params.ug_N[371])+(-params.Pg_N_init[372]+params.Pg_N_avg[372]+params.ug_N[372])*(-params.Pg_N_init[372]+params.Pg_N_avg[372]+params.ug_N[372])+(-params.Pg_N_init[373]+params.Pg_N_avg[373]+params.ug_N[373])*(-params.Pg_N_init[373]+params.Pg_N_avg[373]+params.ug_N[373])+(-params.Pg_N_init[374]+params.Pg_N_avg[374]+params.ug_N[374])*(-params.Pg_N_init[374]+params.Pg_N_avg[374]+params.ug_N[374])+(-params.Pg_N_init[375]+params.Pg_N_avg[375]+params.ug_N[375])*(-params.Pg_N_init[375]+params.Pg_N_avg[375]+params.ug_N[375])+(-params.Pg_N_init[376]+params.Pg_N_avg[376]+params.ug_N[376])*(-params.Pg_N_init[376]+params.Pg_N_avg[376]+params.ug_N[376])+(-params.Pg_N_init[377]+params.Pg_N_avg[377]+params.ug_N[377])*(-params.Pg_N_init[377]+params.Pg_N_avg[377]+params.ug_N[377])+(-params.Pg_N_init[378]+params.Pg_N_avg[378]+params.ug_N[378])*(-params.Pg_N_init[378]+params.Pg_N_avg[378]+params.ug_N[378])+(-params.Pg_N_init[379]+params.Pg_N_avg[379]+params.ug_N[379])*(-params.Pg_N_init[379]+params.Pg_N_avg[379]+params.ug_N[379])+(-params.Pg_N_init[380]+params.Pg_N_avg[380]+params.ug_N[380])*(-params.Pg_N_init[380]+params.Pg_N_avg[380]+params.ug_N[380])+(-params.Pg_N_init[381]+params.Pg_N_avg[381]+params.ug_N[381])*(-params.Pg_N_init[381]+params.Pg_N_avg[381]+params.ug_N[381])+(-params.Pg_N_init[382]+params.Pg_N_avg[382]+params.ug_N[382])*(-params.Pg_N_init[382]+params.Pg_N_avg[382]+params.ug_N[382])+(-params.Pg_N_init[383]+params.Pg_N_avg[383]+params.ug_N[383])*(-params.Pg_N_init[383]+params.Pg_N_avg[383]+params.ug_N[383])+(-params.Pg_N_init[384]+params.Pg_N_avg[384]+params.ug_N[384])*(-params.Pg_N_init[384]+params.Pg_N_avg[384]+params.ug_N[384])+(-params.Pg_N_init[385]+params.Pg_N_avg[385]+params.ug_N[385])*(-params.Pg_N_init[385]+params.Pg_N_avg[385]+params.ug_N[385])+(-params.Pg_N_init[386]+params.Pg_N_avg[386]+params.ug_N[386])*(-params.Pg_N_init[386]+params.Pg_N_avg[386]+params.ug_N[386])+(-params.Pg_N_init[387]+params.Pg_N_avg[387]+params.ug_N[387])*(-params.Pg_N_init[387]+params.Pg_N_avg[387]+params.ug_N[387])+(-params.Pg_N_init[388]+params.Pg_N_avg[388]+params.ug_N[388])*(-params.Pg_N_init[388]+params.Pg_N_avg[388]+params.ug_N[388])+(-params.Pg_N_init[389]+params.Pg_N_avg[389]+params.ug_N[389])*(-params.Pg_N_init[389]+params.Pg_N_avg[389]+params.ug_N[389])+(-params.Pg_N_init[390]+params.Pg_N_avg[390]+params.ug_N[390])*(-params.Pg_N_init[390]+params.Pg_N_avg[390]+params.ug_N[390])+(-params.Pg_N_init[391]+params.Pg_N_avg[391]+params.ug_N[391])*(-params.Pg_N_init[391]+params.Pg_N_avg[391]+params.ug_N[391])+(-params.Pg_N_init[392]+params.Pg_N_avg[392]+params.ug_N[392])*(-params.Pg_N_init[392]+params.Pg_N_avg[392]+params.ug_N[392])+(-params.Pg_N_init[393]+params.Pg_N_avg[393]+params.ug_N[393])*(-params.Pg_N_init[393]+params.Pg_N_avg[393]+params.ug_N[393])+(-params.Pg_N_init[394]+params.Pg_N_avg[394]+params.ug_N[394])*(-params.Pg_N_init[394]+params.Pg_N_avg[394]+params.ug_N[394])+(-params.Pg_N_init[395]+params.Pg_N_avg[395]+params.ug_N[395])*(-params.Pg_N_init[395]+params.Pg_N_avg[395]+params.ug_N[395])+(-params.Pg_N_init[396]+params.Pg_N_avg[396]+params.ug_N[396])*(-params.Pg_N_init[396]+params.Pg_N_avg[396]+params.ug_N[396])+(-params.Pg_N_init[397]+params.Pg_N_avg[397]+params.ug_N[397])*(-params.Pg_N_init[397]+params.Pg_N_avg[397]+params.ug_N[397])+(-params.Pg_N_init[398]+params.Pg_N_avg[398]+params.ug_N[398])*(-params.Pg_N_init[398]+params.Pg_N_avg[398]+params.ug_N[398])+(-params.Pg_N_init[399]+params.Pg_N_avg[399]+params.ug_N[399])*(-params.Pg_N_init[399]+params.Pg_N_avg[399]+params.ug_N[399])+(-params.Pg_N_init[400]+params.Pg_N_avg[400]+params.ug_N[400])*(-params.Pg_N_init[400]+params.Pg_N_avg[400]+params.ug_N[400]));
  work.quad_591828860928[0] = work.frac_121674190848*((-params.Vg_N_avg[0]-params.Thetag_N_avg[0]+params.vg_N[0])*(-params.Vg_N_avg[0]-params.Thetag_N_avg[0]+params.vg_N[0])+(-params.Vg_N_avg[1]-params.Thetag_N_avg[1]+params.vg_N[1])*(-params.Vg_N_avg[1]-params.Thetag_N_avg[1]+params.vg_N[1])+(-params.Vg_N_avg[2]-params.Thetag_N_avg[2]+params.vg_N[2])*(-params.Vg_N_avg[2]-params.Thetag_N_avg[2]+params.vg_N[2])+(-params.Vg_N_avg[3]-params.Thetag_N_avg[3]+params.vg_N[3])*(-params.Vg_N_avg[3]-params.Thetag_N_avg[3]+params.vg_N[3])+(-params.Vg_N_avg[4]-params.Thetag_N_avg[4]+params.vg_N[4])*(-params.Vg_N_avg[4]-params.Thetag_N_avg[4]+params.vg_N[4])+(-params.Vg_N_avg[5]-params.Thetag_N_avg[5]+params.vg_N[5])*(-params.Vg_N_avg[5]-params.Thetag_N_avg[5]+params.vg_N[5])+(-params.Vg_N_avg[6]-params.Thetag_N_avg[6]+params.vg_N[6])*(-params.Vg_N_avg[6]-params.Thetag_N_avg[6]+params.vg_N[6])+(-params.Vg_N_avg[7]-params.Thetag_N_avg[7]+params.vg_N[7])*(-params.Vg_N_avg[7]-params.Thetag_N_avg[7]+params.vg_N[7])+(-params.Vg_N_avg[8]-params.Thetag_N_avg[8]+params.vg_N[8])*(-params.Vg_N_avg[8]-params.Thetag_N_avg[8]+params.vg_N[8])+(-params.Vg_N_avg[9]-params.Thetag_N_avg[9]+params.vg_N[9])*(-params.Vg_N_avg[9]-params.Thetag_N_avg[9]+params.vg_N[9])+(-params.Vg_N_avg[10]-params.Thetag_N_avg[10]+params.vg_N[10])*(-params.Vg_N_avg[10]-params.Thetag_N_avg[10]+params.vg_N[10])+(-params.Vg_N_avg[11]-params.Thetag_N_avg[11]+params.vg_N[11])*(-params.Vg_N_avg[11]-params.Thetag_N_avg[11]+params.vg_N[11])+(-params.Vg_N_avg[12]-params.Thetag_N_avg[12]+params.vg_N[12])*(-params.Vg_N_avg[12]-params.Thetag_N_avg[12]+params.vg_N[12])+(-params.Vg_N_avg[13]-params.Thetag_N_avg[13]+params.vg_N[13])*(-params.Vg_N_avg[13]-params.Thetag_N_avg[13]+params.vg_N[13])+(-params.Vg_N_avg[14]-params.Thetag_N_avg[14]+params.vg_N[14])*(-params.Vg_N_avg[14]-params.Thetag_N_avg[14]+params.vg_N[14])+(-params.Vg_N_avg[15]-params.Thetag_N_avg[15]+params.vg_N[15])*(-params.Vg_N_avg[15]-params.Thetag_N_avg[15]+params.vg_N[15])+(-params.Vg_N_avg[16]-params.Thetag_N_avg[16]+params.vg_N[16])*(-params.Vg_N_avg[16]-params.Thetag_N_avg[16]+params.vg_N[16])+(-params.Vg_N_avg[17]-params.Thetag_N_avg[17]+params.vg_N[17])*(-params.Vg_N_avg[17]-params.Thetag_N_avg[17]+params.vg_N[17])+(-params.Vg_N_avg[18]-params.Thetag_N_avg[18]+params.vg_N[18])*(-params.Vg_N_avg[18]-params.Thetag_N_avg[18]+params.vg_N[18])+(-params.Vg_N_avg[19]-params.Thetag_N_avg[19]+params.vg_N[19])*(-params.Vg_N_avg[19]-params.Thetag_N_avg[19]+params.vg_N[19])+(-params.Vg_N_avg[20]-params.Thetag_N_avg[20]+params.vg_N[20])*(-params.Vg_N_avg[20]-params.Thetag_N_avg[20]+params.vg_N[20])+(-params.Vg_N_avg[21]-params.Thetag_N_avg[21]+params.vg_N[21])*(-params.Vg_N_avg[21]-params.Thetag_N_avg[21]+params.vg_N[21])+(-params.Vg_N_avg[22]-params.Thetag_N_avg[22]+params.vg_N[22])*(-params.Vg_N_avg[22]-params.Thetag_N_avg[22]+params.vg_N[22])+(-params.Vg_N_avg[23]-params.Thetag_N_avg[23]+params.vg_N[23])*(-params.Vg_N_avg[23]-params.Thetag_N_avg[23]+params.vg_N[23])+(-params.Vg_N_avg[24]-params.Thetag_N_avg[24]+params.vg_N[24])*(-params.Vg_N_avg[24]-params.Thetag_N_avg[24]+params.vg_N[24])+(-params.Vg_N_avg[25]-params.Thetag_N_avg[25]+params.vg_N[25])*(-params.Vg_N_avg[25]-params.Thetag_N_avg[25]+params.vg_N[25])+(-params.Vg_N_avg[26]-params.Thetag_N_avg[26]+params.vg_N[26])*(-params.Vg_N_avg[26]-params.Thetag_N_avg[26]+params.vg_N[26])+(-params.Vg_N_avg[27]-params.Thetag_N_avg[27]+params.vg_N[27])*(-params.Vg_N_avg[27]-params.Thetag_N_avg[27]+params.vg_N[27])+(-params.Vg_N_avg[28]-params.Thetag_N_avg[28]+params.vg_N[28])*(-params.Vg_N_avg[28]-params.Thetag_N_avg[28]+params.vg_N[28])+(-params.Vg_N_avg[29]-params.Thetag_N_avg[29]+params.vg_N[29])*(-params.Vg_N_avg[29]-params.Thetag_N_avg[29]+params.vg_N[29])+(-params.Vg_N_avg[30]-params.Thetag_N_avg[30]+params.vg_N[30])*(-params.Vg_N_avg[30]-params.Thetag_N_avg[30]+params.vg_N[30])+(-params.Vg_N_avg[31]-params.Thetag_N_avg[31]+params.vg_N[31])*(-params.Vg_N_avg[31]-params.Thetag_N_avg[31]+params.vg_N[31])+(-params.Vg_N_avg[32]-params.Thetag_N_avg[32]+params.vg_N[32])*(-params.Vg_N_avg[32]-params.Thetag_N_avg[32]+params.vg_N[32])+(-params.Vg_N_avg[33]-params.Thetag_N_avg[33]+params.vg_N[33])*(-params.Vg_N_avg[33]-params.Thetag_N_avg[33]+params.vg_N[33])+(-params.Vg_N_avg[34]-params.Thetag_N_avg[34]+params.vg_N[34])*(-params.Vg_N_avg[34]-params.Thetag_N_avg[34]+params.vg_N[34])+(-params.Vg_N_avg[35]-params.Thetag_N_avg[35]+params.vg_N[35])*(-params.Vg_N_avg[35]-params.Thetag_N_avg[35]+params.vg_N[35])+(-params.Vg_N_avg[36]-params.Thetag_N_avg[36]+params.vg_N[36])*(-params.Vg_N_avg[36]-params.Thetag_N_avg[36]+params.vg_N[36])+(-params.Vg_N_avg[37]-params.Thetag_N_avg[37]+params.vg_N[37])*(-params.Vg_N_avg[37]-params.Thetag_N_avg[37]+params.vg_N[37])+(-params.Vg_N_avg[38]-params.Thetag_N_avg[38]+params.vg_N[38])*(-params.Vg_N_avg[38]-params.Thetag_N_avg[38]+params.vg_N[38])+(-params.Vg_N_avg[39]-params.Thetag_N_avg[39]+params.vg_N[39])*(-params.Vg_N_avg[39]-params.Thetag_N_avg[39]+params.vg_N[39])+(-params.Vg_N_avg[40]-params.Thetag_N_avg[40]+params.vg_N[40])*(-params.Vg_N_avg[40]-params.Thetag_N_avg[40]+params.vg_N[40])+(-params.Vg_N_avg[41]-params.Thetag_N_avg[41]+params.vg_N[41])*(-params.Vg_N_avg[41]-params.Thetag_N_avg[41]+params.vg_N[41])+(-params.Vg_N_avg[42]-params.Thetag_N_avg[42]+params.vg_N[42])*(-params.Vg_N_avg[42]-params.Thetag_N_avg[42]+params.vg_N[42])+(-params.Vg_N_avg[43]-params.Thetag_N_avg[43]+params.vg_N[43])*(-params.Vg_N_avg[43]-params.Thetag_N_avg[43]+params.vg_N[43])+(-params.Vg_N_avg[44]-params.Thetag_N_avg[44]+params.vg_N[44])*(-params.Vg_N_avg[44]-params.Thetag_N_avg[44]+params.vg_N[44])+(-params.Vg_N_avg[45]-params.Thetag_N_avg[45]+params.vg_N[45])*(-params.Vg_N_avg[45]-params.Thetag_N_avg[45]+params.vg_N[45])+(-params.Vg_N_avg[46]-params.Thetag_N_avg[46]+params.vg_N[46])*(-params.Vg_N_avg[46]-params.Thetag_N_avg[46]+params.vg_N[46])+(-params.Vg_N_avg[47]-params.Thetag_N_avg[47]+params.vg_N[47])*(-params.Vg_N_avg[47]-params.Thetag_N_avg[47]+params.vg_N[47])+(-params.Vg_N_avg[48]-params.Thetag_N_avg[48]+params.vg_N[48])*(-params.Vg_N_avg[48]-params.Thetag_N_avg[48]+params.vg_N[48])+(-params.Vg_N_avg[49]-params.Thetag_N_avg[49]+params.vg_N[49])*(-params.Vg_N_avg[49]-params.Thetag_N_avg[49]+params.vg_N[49])+(-params.Vg_N_avg[50]-params.Thetag_N_avg[50]+params.vg_N[50])*(-params.Vg_N_avg[50]-params.Thetag_N_avg[50]+params.vg_N[50])+(-params.Vg_N_avg[51]-params.Thetag_N_avg[51]+params.vg_N[51])*(-params.Vg_N_avg[51]-params.Thetag_N_avg[51]+params.vg_N[51])+(-params.Vg_N_avg[52]-params.Thetag_N_avg[52]+params.vg_N[52])*(-params.Vg_N_avg[52]-params.Thetag_N_avg[52]+params.vg_N[52])+(-params.Vg_N_avg[53]-params.Thetag_N_avg[53]+params.vg_N[53])*(-params.Vg_N_avg[53]-params.Thetag_N_avg[53]+params.vg_N[53])+(-params.Vg_N_avg[54]-params.Thetag_N_avg[54]+params.vg_N[54])*(-params.Vg_N_avg[54]-params.Thetag_N_avg[54]+params.vg_N[54])+(-params.Vg_N_avg[55]-params.Thetag_N_avg[55]+params.vg_N[55])*(-params.Vg_N_avg[55]-params.Thetag_N_avg[55]+params.vg_N[55])+(-params.Vg_N_avg[56]-params.Thetag_N_avg[56]+params.vg_N[56])*(-params.Vg_N_avg[56]-params.Thetag_N_avg[56]+params.vg_N[56])+(-params.Vg_N_avg[57]-params.Thetag_N_avg[57]+params.vg_N[57])*(-params.Vg_N_avg[57]-params.Thetag_N_avg[57]+params.vg_N[57])+(-params.Vg_N_avg[58]-params.Thetag_N_avg[58]+params.vg_N[58])*(-params.Vg_N_avg[58]-params.Thetag_N_avg[58]+params.vg_N[58])+(-params.Vg_N_avg[59]-params.Thetag_N_avg[59]+params.vg_N[59])*(-params.Vg_N_avg[59]-params.Thetag_N_avg[59]+params.vg_N[59])+(-params.Vg_N_avg[60]-params.Thetag_N_avg[60]+params.vg_N[60])*(-params.Vg_N_avg[60]-params.Thetag_N_avg[60]+params.vg_N[60])+(-params.Vg_N_avg[61]-params.Thetag_N_avg[61]+params.vg_N[61])*(-params.Vg_N_avg[61]-params.Thetag_N_avg[61]+params.vg_N[61])+(-params.Vg_N_avg[62]-params.Thetag_N_avg[62]+params.vg_N[62])*(-params.Vg_N_avg[62]-params.Thetag_N_avg[62]+params.vg_N[62])+(-params.Vg_N_avg[63]-params.Thetag_N_avg[63]+params.vg_N[63])*(-params.Vg_N_avg[63]-params.Thetag_N_avg[63]+params.vg_N[63])+(-params.Vg_N_avg[64]-params.Thetag_N_avg[64]+params.vg_N[64])*(-params.Vg_N_avg[64]-params.Thetag_N_avg[64]+params.vg_N[64])+(-params.Vg_N_avg[65]-params.Thetag_N_avg[65]+params.vg_N[65])*(-params.Vg_N_avg[65]-params.Thetag_N_avg[65]+params.vg_N[65])+(-params.Vg_N_avg[66]-params.Thetag_N_avg[66]+params.vg_N[66])*(-params.Vg_N_avg[66]-params.Thetag_N_avg[66]+params.vg_N[66])+(-params.Vg_N_avg[67]-params.Thetag_N_avg[67]+params.vg_N[67])*(-params.Vg_N_avg[67]-params.Thetag_N_avg[67]+params.vg_N[67])+(-params.Vg_N_avg[68]-params.Thetag_N_avg[68]+params.vg_N[68])*(-params.Vg_N_avg[68]-params.Thetag_N_avg[68]+params.vg_N[68])+(-params.Vg_N_avg[69]-params.Thetag_N_avg[69]+params.vg_N[69])*(-params.Vg_N_avg[69]-params.Thetag_N_avg[69]+params.vg_N[69])+(-params.Vg_N_avg[70]-params.Thetag_N_avg[70]+params.vg_N[70])*(-params.Vg_N_avg[70]-params.Thetag_N_avg[70]+params.vg_N[70])+(-params.Vg_N_avg[71]-params.Thetag_N_avg[71]+params.vg_N[71])*(-params.Vg_N_avg[71]-params.Thetag_N_avg[71]+params.vg_N[71])+(-params.Vg_N_avg[72]-params.Thetag_N_avg[72]+params.vg_N[72])*(-params.Vg_N_avg[72]-params.Thetag_N_avg[72]+params.vg_N[72])+(-params.Vg_N_avg[73]-params.Thetag_N_avg[73]+params.vg_N[73])*(-params.Vg_N_avg[73]-params.Thetag_N_avg[73]+params.vg_N[73])+(-params.Vg_N_avg[74]-params.Thetag_N_avg[74]+params.vg_N[74])*(-params.Vg_N_avg[74]-params.Thetag_N_avg[74]+params.vg_N[74])+(-params.Vg_N_avg[75]-params.Thetag_N_avg[75]+params.vg_N[75])*(-params.Vg_N_avg[75]-params.Thetag_N_avg[75]+params.vg_N[75])+(-params.Vg_N_avg[76]-params.Thetag_N_avg[76]+params.vg_N[76])*(-params.Vg_N_avg[76]-params.Thetag_N_avg[76]+params.vg_N[76])+(-params.Vg_N_avg[77]-params.Thetag_N_avg[77]+params.vg_N[77])*(-params.Vg_N_avg[77]-params.Thetag_N_avg[77]+params.vg_N[77])+(-params.Vg_N_avg[78]-params.Thetag_N_avg[78]+params.vg_N[78])*(-params.Vg_N_avg[78]-params.Thetag_N_avg[78]+params.vg_N[78])+(-params.Vg_N_avg[79]-params.Thetag_N_avg[79]+params.vg_N[79])*(-params.Vg_N_avg[79]-params.Thetag_N_avg[79]+params.vg_N[79])+(-params.Vg_N_avg[80]-params.Thetag_N_avg[80]+params.vg_N[80])*(-params.Vg_N_avg[80]-params.Thetag_N_avg[80]+params.vg_N[80])+(-params.Vg_N_avg[81]-params.Thetag_N_avg[81]+params.vg_N[81])*(-params.Vg_N_avg[81]-params.Thetag_N_avg[81]+params.vg_N[81])+(-params.Vg_N_avg[82]-params.Thetag_N_avg[82]+params.vg_N[82])*(-params.Vg_N_avg[82]-params.Thetag_N_avg[82]+params.vg_N[82])+(-params.Vg_N_avg[83]-params.Thetag_N_avg[83]+params.vg_N[83])*(-params.Vg_N_avg[83]-params.Thetag_N_avg[83]+params.vg_N[83])+(-params.Vg_N_avg[84]-params.Thetag_N_avg[84]+params.vg_N[84])*(-params.Vg_N_avg[84]-params.Thetag_N_avg[84]+params.vg_N[84])+(-params.Vg_N_avg[85]-params.Thetag_N_avg[85]+params.vg_N[85])*(-params.Vg_N_avg[85]-params.Thetag_N_avg[85]+params.vg_N[85])+(-params.Vg_N_avg[86]-params.Thetag_N_avg[86]+params.vg_N[86])*(-params.Vg_N_avg[86]-params.Thetag_N_avg[86]+params.vg_N[86])+(-params.Vg_N_avg[87]-params.Thetag_N_avg[87]+params.vg_N[87])*(-params.Vg_N_avg[87]-params.Thetag_N_avg[87]+params.vg_N[87])+(-params.Vg_N_avg[88]-params.Thetag_N_avg[88]+params.vg_N[88])*(-params.Vg_N_avg[88]-params.Thetag_N_avg[88]+params.vg_N[88])+(-params.Vg_N_avg[89]-params.Thetag_N_avg[89]+params.vg_N[89])*(-params.Vg_N_avg[89]-params.Thetag_N_avg[89]+params.vg_N[89])+(-params.Vg_N_avg[90]-params.Thetag_N_avg[90]+params.vg_N[90])*(-params.Vg_N_avg[90]-params.Thetag_N_avg[90]+params.vg_N[90])+(-params.Vg_N_avg[91]-params.Thetag_N_avg[91]+params.vg_N[91])*(-params.Vg_N_avg[91]-params.Thetag_N_avg[91]+params.vg_N[91])+(-params.Vg_N_avg[92]-params.Thetag_N_avg[92]+params.vg_N[92])*(-params.Vg_N_avg[92]-params.Thetag_N_avg[92]+params.vg_N[92])+(-params.Vg_N_avg[93]-params.Thetag_N_avg[93]+params.vg_N[93])*(-params.Vg_N_avg[93]-params.Thetag_N_avg[93]+params.vg_N[93])+(-params.Vg_N_avg[94]-params.Thetag_N_avg[94]+params.vg_N[94])*(-params.Vg_N_avg[94]-params.Thetag_N_avg[94]+params.vg_N[94])+(-params.Vg_N_avg[95]-params.Thetag_N_avg[95]+params.vg_N[95])*(-params.Vg_N_avg[95]-params.Thetag_N_avg[95]+params.vg_N[95])+(-params.Vg_N_avg[96]-params.Thetag_N_avg[96]+params.vg_N[96])*(-params.Vg_N_avg[96]-params.Thetag_N_avg[96]+params.vg_N[96])+(-params.Vg_N_avg[97]-params.Thetag_N_avg[97]+params.vg_N[97])*(-params.Vg_N_avg[97]-params.Thetag_N_avg[97]+params.vg_N[97])+(-params.Vg_N_avg[98]-params.Thetag_N_avg[98]+params.vg_N[98])*(-params.Vg_N_avg[98]-params.Thetag_N_avg[98]+params.vg_N[98])+(-params.Vg_N_avg[99]-params.Thetag_N_avg[99]+params.vg_N[99])*(-params.Vg_N_avg[99]-params.Thetag_N_avg[99]+params.vg_N[99])+(-params.Vg_N_avg[100]-params.Thetag_N_avg[100]+params.vg_N[100])*(-params.Vg_N_avg[100]-params.Thetag_N_avg[100]+params.vg_N[100])+(-params.Vg_N_avg[101]-params.Thetag_N_avg[101]+params.vg_N[101])*(-params.Vg_N_avg[101]-params.Thetag_N_avg[101]+params.vg_N[101])+(-params.Vg_N_avg[102]-params.Thetag_N_avg[102]+params.vg_N[102])*(-params.Vg_N_avg[102]-params.Thetag_N_avg[102]+params.vg_N[102])+(-params.Vg_N_avg[103]-params.Thetag_N_avg[103]+params.vg_N[103])*(-params.Vg_N_avg[103]-params.Thetag_N_avg[103]+params.vg_N[103])+(-params.Vg_N_avg[104]-params.Thetag_N_avg[104]+params.vg_N[104])*(-params.Vg_N_avg[104]-params.Thetag_N_avg[104]+params.vg_N[104])+(-params.Vg_N_avg[105]-params.Thetag_N_avg[105]+params.vg_N[105])*(-params.Vg_N_avg[105]-params.Thetag_N_avg[105]+params.vg_N[105])+(-params.Vg_N_avg[106]-params.Thetag_N_avg[106]+params.vg_N[106])*(-params.Vg_N_avg[106]-params.Thetag_N_avg[106]+params.vg_N[106])+(-params.Vg_N_avg[107]-params.Thetag_N_avg[107]+params.vg_N[107])*(-params.Vg_N_avg[107]-params.Thetag_N_avg[107]+params.vg_N[107])+(-params.Vg_N_avg[108]-params.Thetag_N_avg[108]+params.vg_N[108])*(-params.Vg_N_avg[108]-params.Thetag_N_avg[108]+params.vg_N[108])+(-params.Vg_N_avg[109]-params.Thetag_N_avg[109]+params.vg_N[109])*(-params.Vg_N_avg[109]-params.Thetag_N_avg[109]+params.vg_N[109])+(-params.Vg_N_avg[110]-params.Thetag_N_avg[110]+params.vg_N[110])*(-params.Vg_N_avg[110]-params.Thetag_N_avg[110]+params.vg_N[110])+(-params.Vg_N_avg[111]-params.Thetag_N_avg[111]+params.vg_N[111])*(-params.Vg_N_avg[111]-params.Thetag_N_avg[111]+params.vg_N[111])+(-params.Vg_N_avg[112]-params.Thetag_N_avg[112]+params.vg_N[112])*(-params.Vg_N_avg[112]-params.Thetag_N_avg[112]+params.vg_N[112])+(-params.Vg_N_avg[113]-params.Thetag_N_avg[113]+params.vg_N[113])*(-params.Vg_N_avg[113]-params.Thetag_N_avg[113]+params.vg_N[113])+(-params.Vg_N_avg[114]-params.Thetag_N_avg[114]+params.vg_N[114])*(-params.Vg_N_avg[114]-params.Thetag_N_avg[114]+params.vg_N[114])+(-params.Vg_N_avg[115]-params.Thetag_N_avg[115]+params.vg_N[115])*(-params.Vg_N_avg[115]-params.Thetag_N_avg[115]+params.vg_N[115])+(-params.Vg_N_avg[116]-params.Thetag_N_avg[116]+params.vg_N[116])*(-params.Vg_N_avg[116]-params.Thetag_N_avg[116]+params.vg_N[116])+(-params.Vg_N_avg[117]-params.Thetag_N_avg[117]+params.vg_N[117])*(-params.Vg_N_avg[117]-params.Thetag_N_avg[117]+params.vg_N[117])+(-params.Vg_N_avg[118]-params.Thetag_N_avg[118]+params.vg_N[118])*(-params.Vg_N_avg[118]-params.Thetag_N_avg[118]+params.vg_N[118])+(-params.Vg_N_avg[119]-params.Thetag_N_avg[119]+params.vg_N[119])*(-params.Vg_N_avg[119]-params.Thetag_N_avg[119]+params.vg_N[119])+(-params.Vg_N_avg[120]-params.Thetag_N_avg[120]+params.vg_N[120])*(-params.Vg_N_avg[120]-params.Thetag_N_avg[120]+params.vg_N[120])+(-params.Vg_N_avg[121]-params.Thetag_N_avg[121]+params.vg_N[121])*(-params.Vg_N_avg[121]-params.Thetag_N_avg[121]+params.vg_N[121])+(-params.Vg_N_avg[122]-params.Thetag_N_avg[122]+params.vg_N[122])*(-params.Vg_N_avg[122]-params.Thetag_N_avg[122]+params.vg_N[122])+(-params.Vg_N_avg[123]-params.Thetag_N_avg[123]+params.vg_N[123])*(-params.Vg_N_avg[123]-params.Thetag_N_avg[123]+params.vg_N[123])+(-params.Vg_N_avg[124]-params.Thetag_N_avg[124]+params.vg_N[124])*(-params.Vg_N_avg[124]-params.Thetag_N_avg[124]+params.vg_N[124])+(-params.Vg_N_avg[125]-params.Thetag_N_avg[125]+params.vg_N[125])*(-params.Vg_N_avg[125]-params.Thetag_N_avg[125]+params.vg_N[125])+(-params.Vg_N_avg[126]-params.Thetag_N_avg[126]+params.vg_N[126])*(-params.Vg_N_avg[126]-params.Thetag_N_avg[126]+params.vg_N[126])+(-params.Vg_N_avg[127]-params.Thetag_N_avg[127]+params.vg_N[127])*(-params.Vg_N_avg[127]-params.Thetag_N_avg[127]+params.vg_N[127])+(-params.Vg_N_avg[128]-params.Thetag_N_avg[128]+params.vg_N[128])*(-params.Vg_N_avg[128]-params.Thetag_N_avg[128]+params.vg_N[128])+(-params.Vg_N_avg[129]-params.Thetag_N_avg[129]+params.vg_N[129])*(-params.Vg_N_avg[129]-params.Thetag_N_avg[129]+params.vg_N[129])+(-params.Vg_N_avg[130]-params.Thetag_N_avg[130]+params.vg_N[130])*(-params.Vg_N_avg[130]-params.Thetag_N_avg[130]+params.vg_N[130])+(-params.Vg_N_avg[131]-params.Thetag_N_avg[131]+params.vg_N[131])*(-params.Vg_N_avg[131]-params.Thetag_N_avg[131]+params.vg_N[131])+(-params.Vg_N_avg[132]-params.Thetag_N_avg[132]+params.vg_N[132])*(-params.Vg_N_avg[132]-params.Thetag_N_avg[132]+params.vg_N[132])+(-params.Vg_N_avg[133]-params.Thetag_N_avg[133]+params.vg_N[133])*(-params.Vg_N_avg[133]-params.Thetag_N_avg[133]+params.vg_N[133])+(-params.Vg_N_avg[134]-params.Thetag_N_avg[134]+params.vg_N[134])*(-params.Vg_N_avg[134]-params.Thetag_N_avg[134]+params.vg_N[134])+(-params.Vg_N_avg[135]-params.Thetag_N_avg[135]+params.vg_N[135])*(-params.Vg_N_avg[135]-params.Thetag_N_avg[135]+params.vg_N[135])+(-params.Vg_N_avg[136]-params.Thetag_N_avg[136]+params.vg_N[136])*(-params.Vg_N_avg[136]-params.Thetag_N_avg[136]+params.vg_N[136])+(-params.Vg_N_avg[137]-params.Thetag_N_avg[137]+params.vg_N[137])*(-params.Vg_N_avg[137]-params.Thetag_N_avg[137]+params.vg_N[137])+(-params.Vg_N_avg[138]-params.Thetag_N_avg[138]+params.vg_N[138])*(-params.Vg_N_avg[138]-params.Thetag_N_avg[138]+params.vg_N[138])+(-params.Vg_N_avg[139]-params.Thetag_N_avg[139]+params.vg_N[139])*(-params.Vg_N_avg[139]-params.Thetag_N_avg[139]+params.vg_N[139])+(-params.Vg_N_avg[140]-params.Thetag_N_avg[140]+params.vg_N[140])*(-params.Vg_N_avg[140]-params.Thetag_N_avg[140]+params.vg_N[140])+(-params.Vg_N_avg[141]-params.Thetag_N_avg[141]+params.vg_N[141])*(-params.Vg_N_avg[141]-params.Thetag_N_avg[141]+params.vg_N[141])+(-params.Vg_N_avg[142]-params.Thetag_N_avg[142]+params.vg_N[142])*(-params.Vg_N_avg[142]-params.Thetag_N_avg[142]+params.vg_N[142])+(-params.Vg_N_avg[143]-params.Thetag_N_avg[143]+params.vg_N[143])*(-params.Vg_N_avg[143]-params.Thetag_N_avg[143]+params.vg_N[143])+(-params.Vg_N_avg[144]-params.Thetag_N_avg[144]+params.vg_N[144])*(-params.Vg_N_avg[144]-params.Thetag_N_avg[144]+params.vg_N[144])+(-params.Vg_N_avg[145]-params.Thetag_N_avg[145]+params.vg_N[145])*(-params.Vg_N_avg[145]-params.Thetag_N_avg[145]+params.vg_N[145])+(-params.Vg_N_avg[146]-params.Thetag_N_avg[146]+params.vg_N[146])*(-params.Vg_N_avg[146]-params.Thetag_N_avg[146]+params.vg_N[146])+(-params.Vg_N_avg[147]-params.Thetag_N_avg[147]+params.vg_N[147])*(-params.Vg_N_avg[147]-params.Thetag_N_avg[147]+params.vg_N[147])+(-params.Vg_N_avg[148]-params.Thetag_N_avg[148]+params.vg_N[148])*(-params.Vg_N_avg[148]-params.Thetag_N_avg[148]+params.vg_N[148])+(-params.Vg_N_avg[149]-params.Thetag_N_avg[149]+params.vg_N[149])*(-params.Vg_N_avg[149]-params.Thetag_N_avg[149]+params.vg_N[149])+(-params.Vg_N_avg[150]-params.Thetag_N_avg[150]+params.vg_N[150])*(-params.Vg_N_avg[150]-params.Thetag_N_avg[150]+params.vg_N[150])+(-params.Vg_N_avg[151]-params.Thetag_N_avg[151]+params.vg_N[151])*(-params.Vg_N_avg[151]-params.Thetag_N_avg[151]+params.vg_N[151])+(-params.Vg_N_avg[152]-params.Thetag_N_avg[152]+params.vg_N[152])*(-params.Vg_N_avg[152]-params.Thetag_N_avg[152]+params.vg_N[152])+(-params.Vg_N_avg[153]-params.Thetag_N_avg[153]+params.vg_N[153])*(-params.Vg_N_avg[153]-params.Thetag_N_avg[153]+params.vg_N[153])+(-params.Vg_N_avg[154]-params.Thetag_N_avg[154]+params.vg_N[154])*(-params.Vg_N_avg[154]-params.Thetag_N_avg[154]+params.vg_N[154])+(-params.Vg_N_avg[155]-params.Thetag_N_avg[155]+params.vg_N[155])*(-params.Vg_N_avg[155]-params.Thetag_N_avg[155]+params.vg_N[155])+(-params.Vg_N_avg[156]-params.Thetag_N_avg[156]+params.vg_N[156])*(-params.Vg_N_avg[156]-params.Thetag_N_avg[156]+params.vg_N[156])+(-params.Vg_N_avg[157]-params.Thetag_N_avg[157]+params.vg_N[157])*(-params.Vg_N_avg[157]-params.Thetag_N_avg[157]+params.vg_N[157])+(-params.Vg_N_avg[158]-params.Thetag_N_avg[158]+params.vg_N[158])*(-params.Vg_N_avg[158]-params.Thetag_N_avg[158]+params.vg_N[158])+(-params.Vg_N_avg[159]-params.Thetag_N_avg[159]+params.vg_N[159])*(-params.Vg_N_avg[159]-params.Thetag_N_avg[159]+params.vg_N[159])+(-params.Vg_N_avg[160]-params.Thetag_N_avg[160]+params.vg_N[160])*(-params.Vg_N_avg[160]-params.Thetag_N_avg[160]+params.vg_N[160])+(-params.Vg_N_avg[161]-params.Thetag_N_avg[161]+params.vg_N[161])*(-params.Vg_N_avg[161]-params.Thetag_N_avg[161]+params.vg_N[161])+(-params.Vg_N_avg[162]-params.Thetag_N_avg[162]+params.vg_N[162])*(-params.Vg_N_avg[162]-params.Thetag_N_avg[162]+params.vg_N[162])+(-params.Vg_N_avg[163]-params.Thetag_N_avg[163]+params.vg_N[163])*(-params.Vg_N_avg[163]-params.Thetag_N_avg[163]+params.vg_N[163])+(-params.Vg_N_avg[164]-params.Thetag_N_avg[164]+params.vg_N[164])*(-params.Vg_N_avg[164]-params.Thetag_N_avg[164]+params.vg_N[164])+(-params.Vg_N_avg[165]-params.Thetag_N_avg[165]+params.vg_N[165])*(-params.Vg_N_avg[165]-params.Thetag_N_avg[165]+params.vg_N[165])+(-params.Vg_N_avg[166]-params.Thetag_N_avg[166]+params.vg_N[166])*(-params.Vg_N_avg[166]-params.Thetag_N_avg[166]+params.vg_N[166])+(-params.Vg_N_avg[167]-params.Thetag_N_avg[167]+params.vg_N[167])*(-params.Vg_N_avg[167]-params.Thetag_N_avg[167]+params.vg_N[167])+(-params.Vg_N_avg[168]-params.Thetag_N_avg[168]+params.vg_N[168])*(-params.Vg_N_avg[168]-params.Thetag_N_avg[168]+params.vg_N[168])+(-params.Vg_N_avg[169]-params.Thetag_N_avg[169]+params.vg_N[169])*(-params.Vg_N_avg[169]-params.Thetag_N_avg[169]+params.vg_N[169])+(-params.Vg_N_avg[170]-params.Thetag_N_avg[170]+params.vg_N[170])*(-params.Vg_N_avg[170]-params.Thetag_N_avg[170]+params.vg_N[170])+(-params.Vg_N_avg[171]-params.Thetag_N_avg[171]+params.vg_N[171])*(-params.Vg_N_avg[171]-params.Thetag_N_avg[171]+params.vg_N[171])+(-params.Vg_N_avg[172]-params.Thetag_N_avg[172]+params.vg_N[172])*(-params.Vg_N_avg[172]-params.Thetag_N_avg[172]+params.vg_N[172])+(-params.Vg_N_avg[173]-params.Thetag_N_avg[173]+params.vg_N[173])*(-params.Vg_N_avg[173]-params.Thetag_N_avg[173]+params.vg_N[173])+(-params.Vg_N_avg[174]-params.Thetag_N_avg[174]+params.vg_N[174])*(-params.Vg_N_avg[174]-params.Thetag_N_avg[174]+params.vg_N[174])+(-params.Vg_N_avg[175]-params.Thetag_N_avg[175]+params.vg_N[175])*(-params.Vg_N_avg[175]-params.Thetag_N_avg[175]+params.vg_N[175])+(-params.Vg_N_avg[176]-params.Thetag_N_avg[176]+params.vg_N[176])*(-params.Vg_N_avg[176]-params.Thetag_N_avg[176]+params.vg_N[176])+(-params.Vg_N_avg[177]-params.Thetag_N_avg[177]+params.vg_N[177])*(-params.Vg_N_avg[177]-params.Thetag_N_avg[177]+params.vg_N[177])+(-params.Vg_N_avg[178]-params.Thetag_N_avg[178]+params.vg_N[178])*(-params.Vg_N_avg[178]-params.Thetag_N_avg[178]+params.vg_N[178])+(-params.Vg_N_avg[179]-params.Thetag_N_avg[179]+params.vg_N[179])*(-params.Vg_N_avg[179]-params.Thetag_N_avg[179]+params.vg_N[179])+(-params.Vg_N_avg[180]-params.Thetag_N_avg[180]+params.vg_N[180])*(-params.Vg_N_avg[180]-params.Thetag_N_avg[180]+params.vg_N[180])+(-params.Vg_N_avg[181]-params.Thetag_N_avg[181]+params.vg_N[181])*(-params.Vg_N_avg[181]-params.Thetag_N_avg[181]+params.vg_N[181])+(-params.Vg_N_avg[182]-params.Thetag_N_avg[182]+params.vg_N[182])*(-params.Vg_N_avg[182]-params.Thetag_N_avg[182]+params.vg_N[182])+(-params.Vg_N_avg[183]-params.Thetag_N_avg[183]+params.vg_N[183])*(-params.Vg_N_avg[183]-params.Thetag_N_avg[183]+params.vg_N[183])+(-params.Vg_N_avg[184]-params.Thetag_N_avg[184]+params.vg_N[184])*(-params.Vg_N_avg[184]-params.Thetag_N_avg[184]+params.vg_N[184])+(-params.Vg_N_avg[185]-params.Thetag_N_avg[185]+params.vg_N[185])*(-params.Vg_N_avg[185]-params.Thetag_N_avg[185]+params.vg_N[185])+(-params.Vg_N_avg[186]-params.Thetag_N_avg[186]+params.vg_N[186])*(-params.Vg_N_avg[186]-params.Thetag_N_avg[186]+params.vg_N[186])+(-params.Vg_N_avg[187]-params.Thetag_N_avg[187]+params.vg_N[187])*(-params.Vg_N_avg[187]-params.Thetag_N_avg[187]+params.vg_N[187])+(-params.Vg_N_avg[188]-params.Thetag_N_avg[188]+params.vg_N[188])*(-params.Vg_N_avg[188]-params.Thetag_N_avg[188]+params.vg_N[188])+(-params.Vg_N_avg[189]-params.Thetag_N_avg[189]+params.vg_N[189])*(-params.Vg_N_avg[189]-params.Thetag_N_avg[189]+params.vg_N[189])+(-params.Vg_N_avg[190]-params.Thetag_N_avg[190]+params.vg_N[190])*(-params.Vg_N_avg[190]-params.Thetag_N_avg[190]+params.vg_N[190])+(-params.Vg_N_avg[191]-params.Thetag_N_avg[191]+params.vg_N[191])*(-params.Vg_N_avg[191]-params.Thetag_N_avg[191]+params.vg_N[191])+(-params.Vg_N_avg[192]-params.Thetag_N_avg[192]+params.vg_N[192])*(-params.Vg_N_avg[192]-params.Thetag_N_avg[192]+params.vg_N[192])+(-params.Vg_N_avg[193]-params.Thetag_N_avg[193]+params.vg_N[193])*(-params.Vg_N_avg[193]-params.Thetag_N_avg[193]+params.vg_N[193])+(-params.Vg_N_avg[194]-params.Thetag_N_avg[194]+params.vg_N[194])*(-params.Vg_N_avg[194]-params.Thetag_N_avg[194]+params.vg_N[194])+(-params.Vg_N_avg[195]-params.Thetag_N_avg[195]+params.vg_N[195])*(-params.Vg_N_avg[195]-params.Thetag_N_avg[195]+params.vg_N[195])+(-params.Vg_N_avg[196]-params.Thetag_N_avg[196]+params.vg_N[196])*(-params.Vg_N_avg[196]-params.Thetag_N_avg[196]+params.vg_N[196])+(-params.Vg_N_avg[197]-params.Thetag_N_avg[197]+params.vg_N[197])*(-params.Vg_N_avg[197]-params.Thetag_N_avg[197]+params.vg_N[197])+(-params.Vg_N_avg[198]-params.Thetag_N_avg[198]+params.vg_N[198])*(-params.Vg_N_avg[198]-params.Thetag_N_avg[198]+params.vg_N[198])+(-params.Vg_N_avg[199]-params.Thetag_N_avg[199]+params.vg_N[199])*(-params.Vg_N_avg[199]-params.Thetag_N_avg[199]+params.vg_N[199])+(-params.Vg_N_avg[200]-params.Thetag_N_avg[200]+params.vg_N[200])*(-params.Vg_N_avg[200]-params.Thetag_N_avg[200]+params.vg_N[200])+(-params.Vg_N_avg[201]-params.Thetag_N_avg[201]+params.vg_N[201])*(-params.Vg_N_avg[201]-params.Thetag_N_avg[201]+params.vg_N[201])+(-params.Vg_N_avg[202]-params.Thetag_N_avg[202]+params.vg_N[202])*(-params.Vg_N_avg[202]-params.Thetag_N_avg[202]+params.vg_N[202])+(-params.Vg_N_avg[203]-params.Thetag_N_avg[203]+params.vg_N[203])*(-params.Vg_N_avg[203]-params.Thetag_N_avg[203]+params.vg_N[203])+(-params.Vg_N_avg[204]-params.Thetag_N_avg[204]+params.vg_N[204])*(-params.Vg_N_avg[204]-params.Thetag_N_avg[204]+params.vg_N[204])+(-params.Vg_N_avg[205]-params.Thetag_N_avg[205]+params.vg_N[205])*(-params.Vg_N_avg[205]-params.Thetag_N_avg[205]+params.vg_N[205])+(-params.Vg_N_avg[206]-params.Thetag_N_avg[206]+params.vg_N[206])*(-params.Vg_N_avg[206]-params.Thetag_N_avg[206]+params.vg_N[206])+(-params.Vg_N_avg[207]-params.Thetag_N_avg[207]+params.vg_N[207])*(-params.Vg_N_avg[207]-params.Thetag_N_avg[207]+params.vg_N[207])+(-params.Vg_N_avg[208]-params.Thetag_N_avg[208]+params.vg_N[208])*(-params.Vg_N_avg[208]-params.Thetag_N_avg[208]+params.vg_N[208])+(-params.Vg_N_avg[209]-params.Thetag_N_avg[209]+params.vg_N[209])*(-params.Vg_N_avg[209]-params.Thetag_N_avg[209]+params.vg_N[209])+(-params.Vg_N_avg[210]-params.Thetag_N_avg[210]+params.vg_N[210])*(-params.Vg_N_avg[210]-params.Thetag_N_avg[210]+params.vg_N[210])+(-params.Vg_N_avg[211]-params.Thetag_N_avg[211]+params.vg_N[211])*(-params.Vg_N_avg[211]-params.Thetag_N_avg[211]+params.vg_N[211])+(-params.Vg_N_avg[212]-params.Thetag_N_avg[212]+params.vg_N[212])*(-params.Vg_N_avg[212]-params.Thetag_N_avg[212]+params.vg_N[212])+(-params.Vg_N_avg[213]-params.Thetag_N_avg[213]+params.vg_N[213])*(-params.Vg_N_avg[213]-params.Thetag_N_avg[213]+params.vg_N[213])+(-params.Vg_N_avg[214]-params.Thetag_N_avg[214]+params.vg_N[214])*(-params.Vg_N_avg[214]-params.Thetag_N_avg[214]+params.vg_N[214])+(-params.Vg_N_avg[215]-params.Thetag_N_avg[215]+params.vg_N[215])*(-params.Vg_N_avg[215]-params.Thetag_N_avg[215]+params.vg_N[215])+(-params.Vg_N_avg[216]-params.Thetag_N_avg[216]+params.vg_N[216])*(-params.Vg_N_avg[216]-params.Thetag_N_avg[216]+params.vg_N[216])+(-params.Vg_N_avg[217]-params.Thetag_N_avg[217]+params.vg_N[217])*(-params.Vg_N_avg[217]-params.Thetag_N_avg[217]+params.vg_N[217])+(-params.Vg_N_avg[218]-params.Thetag_N_avg[218]+params.vg_N[218])*(-params.Vg_N_avg[218]-params.Thetag_N_avg[218]+params.vg_N[218])+(-params.Vg_N_avg[219]-params.Thetag_N_avg[219]+params.vg_N[219])*(-params.Vg_N_avg[219]-params.Thetag_N_avg[219]+params.vg_N[219])+(-params.Vg_N_avg[220]-params.Thetag_N_avg[220]+params.vg_N[220])*(-params.Vg_N_avg[220]-params.Thetag_N_avg[220]+params.vg_N[220])+(-params.Vg_N_avg[221]-params.Thetag_N_avg[221]+params.vg_N[221])*(-params.Vg_N_avg[221]-params.Thetag_N_avg[221]+params.vg_N[221])+(-params.Vg_N_avg[222]-params.Thetag_N_avg[222]+params.vg_N[222])*(-params.Vg_N_avg[222]-params.Thetag_N_avg[222]+params.vg_N[222])+(-params.Vg_N_avg[223]-params.Thetag_N_avg[223]+params.vg_N[223])*(-params.Vg_N_avg[223]-params.Thetag_N_avg[223]+params.vg_N[223])+(-params.Vg_N_avg[224]-params.Thetag_N_avg[224]+params.vg_N[224])*(-params.Vg_N_avg[224]-params.Thetag_N_avg[224]+params.vg_N[224])+(-params.Vg_N_avg[225]-params.Thetag_N_avg[225]+params.vg_N[225])*(-params.Vg_N_avg[225]-params.Thetag_N_avg[225]+params.vg_N[225])+(-params.Vg_N_avg[226]-params.Thetag_N_avg[226]+params.vg_N[226])*(-params.Vg_N_avg[226]-params.Thetag_N_avg[226]+params.vg_N[226])+(-params.Vg_N_avg[227]-params.Thetag_N_avg[227]+params.vg_N[227])*(-params.Vg_N_avg[227]-params.Thetag_N_avg[227]+params.vg_N[227])+(-params.Vg_N_avg[228]-params.Thetag_N_avg[228]+params.vg_N[228])*(-params.Vg_N_avg[228]-params.Thetag_N_avg[228]+params.vg_N[228])+(-params.Vg_N_avg[229]-params.Thetag_N_avg[229]+params.vg_N[229])*(-params.Vg_N_avg[229]-params.Thetag_N_avg[229]+params.vg_N[229])+(-params.Vg_N_avg[230]-params.Thetag_N_avg[230]+params.vg_N[230])*(-params.Vg_N_avg[230]-params.Thetag_N_avg[230]+params.vg_N[230])+(-params.Vg_N_avg[231]-params.Thetag_N_avg[231]+params.vg_N[231])*(-params.Vg_N_avg[231]-params.Thetag_N_avg[231]+params.vg_N[231])+(-params.Vg_N_avg[232]-params.Thetag_N_avg[232]+params.vg_N[232])*(-params.Vg_N_avg[232]-params.Thetag_N_avg[232]+params.vg_N[232])+(-params.Vg_N_avg[233]-params.Thetag_N_avg[233]+params.vg_N[233])*(-params.Vg_N_avg[233]-params.Thetag_N_avg[233]+params.vg_N[233])+(-params.Vg_N_avg[234]-params.Thetag_N_avg[234]+params.vg_N[234])*(-params.Vg_N_avg[234]-params.Thetag_N_avg[234]+params.vg_N[234])+(-params.Vg_N_avg[235]-params.Thetag_N_avg[235]+params.vg_N[235])*(-params.Vg_N_avg[235]-params.Thetag_N_avg[235]+params.vg_N[235])+(-params.Vg_N_avg[236]-params.Thetag_N_avg[236]+params.vg_N[236])*(-params.Vg_N_avg[236]-params.Thetag_N_avg[236]+params.vg_N[236])+(-params.Vg_N_avg[237]-params.Thetag_N_avg[237]+params.vg_N[237])*(-params.Vg_N_avg[237]-params.Thetag_N_avg[237]+params.vg_N[237])+(-params.Vg_N_avg[238]-params.Thetag_N_avg[238]+params.vg_N[238])*(-params.Vg_N_avg[238]-params.Thetag_N_avg[238]+params.vg_N[238])+(-params.Vg_N_avg[239]-params.Thetag_N_avg[239]+params.vg_N[239])*(-params.Vg_N_avg[239]-params.Thetag_N_avg[239]+params.vg_N[239])+(-params.Vg_N_avg[240]-params.Thetag_N_avg[240]+params.vg_N[240])*(-params.Vg_N_avg[240]-params.Thetag_N_avg[240]+params.vg_N[240])+(-params.Vg_N_avg[241]-params.Thetag_N_avg[241]+params.vg_N[241])*(-params.Vg_N_avg[241]-params.Thetag_N_avg[241]+params.vg_N[241])+(-params.Vg_N_avg[242]-params.Thetag_N_avg[242]+params.vg_N[242])*(-params.Vg_N_avg[242]-params.Thetag_N_avg[242]+params.vg_N[242])+(-params.Vg_N_avg[243]-params.Thetag_N_avg[243]+params.vg_N[243])*(-params.Vg_N_avg[243]-params.Thetag_N_avg[243]+params.vg_N[243])+(-params.Vg_N_avg[244]-params.Thetag_N_avg[244]+params.vg_N[244])*(-params.Vg_N_avg[244]-params.Thetag_N_avg[244]+params.vg_N[244])+(-params.Vg_N_avg[245]-params.Thetag_N_avg[245]+params.vg_N[245])*(-params.Vg_N_avg[245]-params.Thetag_N_avg[245]+params.vg_N[245])+(-params.Vg_N_avg[246]-params.Thetag_N_avg[246]+params.vg_N[246])*(-params.Vg_N_avg[246]-params.Thetag_N_avg[246]+params.vg_N[246])+(-params.Vg_N_avg[247]-params.Thetag_N_avg[247]+params.vg_N[247])*(-params.Vg_N_avg[247]-params.Thetag_N_avg[247]+params.vg_N[247])+(-params.Vg_N_avg[248]-params.Thetag_N_avg[248]+params.vg_N[248])*(-params.Vg_N_avg[248]-params.Thetag_N_avg[248]+params.vg_N[248])+(-params.Vg_N_avg[249]-params.Thetag_N_avg[249]+params.vg_N[249])*(-params.Vg_N_avg[249]-params.Thetag_N_avg[249]+params.vg_N[249])+(-params.Vg_N_avg[250]-params.Thetag_N_avg[250]+params.vg_N[250])*(-params.Vg_N_avg[250]-params.Thetag_N_avg[250]+params.vg_N[250])+(-params.Vg_N_avg[251]-params.Thetag_N_avg[251]+params.vg_N[251])*(-params.Vg_N_avg[251]-params.Thetag_N_avg[251]+params.vg_N[251])+(-params.Vg_N_avg[252]-params.Thetag_N_avg[252]+params.vg_N[252])*(-params.Vg_N_avg[252]-params.Thetag_N_avg[252]+params.vg_N[252])+(-params.Vg_N_avg[253]-params.Thetag_N_avg[253]+params.vg_N[253])*(-params.Vg_N_avg[253]-params.Thetag_N_avg[253]+params.vg_N[253])+(-params.Vg_N_avg[254]-params.Thetag_N_avg[254]+params.vg_N[254])*(-params.Vg_N_avg[254]-params.Thetag_N_avg[254]+params.vg_N[254])+(-params.Vg_N_avg[255]-params.Thetag_N_avg[255]+params.vg_N[255])*(-params.Vg_N_avg[255]-params.Thetag_N_avg[255]+params.vg_N[255])+(-params.Vg_N_avg[256]-params.Thetag_N_avg[256]+params.vg_N[256])*(-params.Vg_N_avg[256]-params.Thetag_N_avg[256]+params.vg_N[256])+(-params.Vg_N_avg[257]-params.Thetag_N_avg[257]+params.vg_N[257])*(-params.Vg_N_avg[257]-params.Thetag_N_avg[257]+params.vg_N[257])+(-params.Vg_N_avg[258]-params.Thetag_N_avg[258]+params.vg_N[258])*(-params.Vg_N_avg[258]-params.Thetag_N_avg[258]+params.vg_N[258])+(-params.Vg_N_avg[259]-params.Thetag_N_avg[259]+params.vg_N[259])*(-params.Vg_N_avg[259]-params.Thetag_N_avg[259]+params.vg_N[259])+(-params.Vg_N_avg[260]-params.Thetag_N_avg[260]+params.vg_N[260])*(-params.Vg_N_avg[260]-params.Thetag_N_avg[260]+params.vg_N[260])+(-params.Vg_N_avg[261]-params.Thetag_N_avg[261]+params.vg_N[261])*(-params.Vg_N_avg[261]-params.Thetag_N_avg[261]+params.vg_N[261])+(-params.Vg_N_avg[262]-params.Thetag_N_avg[262]+params.vg_N[262])*(-params.Vg_N_avg[262]-params.Thetag_N_avg[262]+params.vg_N[262])+(-params.Vg_N_avg[263]-params.Thetag_N_avg[263]+params.vg_N[263])*(-params.Vg_N_avg[263]-params.Thetag_N_avg[263]+params.vg_N[263])+(-params.Vg_N_avg[264]-params.Thetag_N_avg[264]+params.vg_N[264])*(-params.Vg_N_avg[264]-params.Thetag_N_avg[264]+params.vg_N[264])+(-params.Vg_N_avg[265]-params.Thetag_N_avg[265]+params.vg_N[265])*(-params.Vg_N_avg[265]-params.Thetag_N_avg[265]+params.vg_N[265])+(-params.Vg_N_avg[266]-params.Thetag_N_avg[266]+params.vg_N[266])*(-params.Vg_N_avg[266]-params.Thetag_N_avg[266]+params.vg_N[266])+(-params.Vg_N_avg[267]-params.Thetag_N_avg[267]+params.vg_N[267])*(-params.Vg_N_avg[267]-params.Thetag_N_avg[267]+params.vg_N[267])+(-params.Vg_N_avg[268]-params.Thetag_N_avg[268]+params.vg_N[268])*(-params.Vg_N_avg[268]-params.Thetag_N_avg[268]+params.vg_N[268])+(-params.Vg_N_avg[269]-params.Thetag_N_avg[269]+params.vg_N[269])*(-params.Vg_N_avg[269]-params.Thetag_N_avg[269]+params.vg_N[269])+(-params.Vg_N_avg[270]-params.Thetag_N_avg[270]+params.vg_N[270])*(-params.Vg_N_avg[270]-params.Thetag_N_avg[270]+params.vg_N[270])+(-params.Vg_N_avg[271]-params.Thetag_N_avg[271]+params.vg_N[271])*(-params.Vg_N_avg[271]-params.Thetag_N_avg[271]+params.vg_N[271])+(-params.Vg_N_avg[272]-params.Thetag_N_avg[272]+params.vg_N[272])*(-params.Vg_N_avg[272]-params.Thetag_N_avg[272]+params.vg_N[272])+(-params.Vg_N_avg[273]-params.Thetag_N_avg[273]+params.vg_N[273])*(-params.Vg_N_avg[273]-params.Thetag_N_avg[273]+params.vg_N[273])+(-params.Vg_N_avg[274]-params.Thetag_N_avg[274]+params.vg_N[274])*(-params.Vg_N_avg[274]-params.Thetag_N_avg[274]+params.vg_N[274])+(-params.Vg_N_avg[275]-params.Thetag_N_avg[275]+params.vg_N[275])*(-params.Vg_N_avg[275]-params.Thetag_N_avg[275]+params.vg_N[275])+(-params.Vg_N_avg[276]-params.Thetag_N_avg[276]+params.vg_N[276])*(-params.Vg_N_avg[276]-params.Thetag_N_avg[276]+params.vg_N[276])+(-params.Vg_N_avg[277]-params.Thetag_N_avg[277]+params.vg_N[277])*(-params.Vg_N_avg[277]-params.Thetag_N_avg[277]+params.vg_N[277])+(-params.Vg_N_avg[278]-params.Thetag_N_avg[278]+params.vg_N[278])*(-params.Vg_N_avg[278]-params.Thetag_N_avg[278]+params.vg_N[278])+(-params.Vg_N_avg[279]-params.Thetag_N_avg[279]+params.vg_N[279])*(-params.Vg_N_avg[279]-params.Thetag_N_avg[279]+params.vg_N[279])+(-params.Vg_N_avg[280]-params.Thetag_N_avg[280]+params.vg_N[280])*(-params.Vg_N_avg[280]-params.Thetag_N_avg[280]+params.vg_N[280])+(-params.Vg_N_avg[281]-params.Thetag_N_avg[281]+params.vg_N[281])*(-params.Vg_N_avg[281]-params.Thetag_N_avg[281]+params.vg_N[281])+(-params.Vg_N_avg[282]-params.Thetag_N_avg[282]+params.vg_N[282])*(-params.Vg_N_avg[282]-params.Thetag_N_avg[282]+params.vg_N[282])+(-params.Vg_N_avg[283]-params.Thetag_N_avg[283]+params.vg_N[283])*(-params.Vg_N_avg[283]-params.Thetag_N_avg[283]+params.vg_N[283])+(-params.Vg_N_avg[284]-params.Thetag_N_avg[284]+params.vg_N[284])*(-params.Vg_N_avg[284]-params.Thetag_N_avg[284]+params.vg_N[284])+(-params.Vg_N_avg[285]-params.Thetag_N_avg[285]+params.vg_N[285])*(-params.Vg_N_avg[285]-params.Thetag_N_avg[285]+params.vg_N[285])+(-params.Vg_N_avg[286]-params.Thetag_N_avg[286]+params.vg_N[286])*(-params.Vg_N_avg[286]-params.Thetag_N_avg[286]+params.vg_N[286])+(-params.Vg_N_avg[287]-params.Thetag_N_avg[287]+params.vg_N[287])*(-params.Vg_N_avg[287]-params.Thetag_N_avg[287]+params.vg_N[287])+(-params.Vg_N_avg[288]-params.Thetag_N_avg[288]+params.vg_N[288])*(-params.Vg_N_avg[288]-params.Thetag_N_avg[288]+params.vg_N[288])+(-params.Vg_N_avg[289]-params.Thetag_N_avg[289]+params.vg_N[289])*(-params.Vg_N_avg[289]-params.Thetag_N_avg[289]+params.vg_N[289])+(-params.Vg_N_avg[290]-params.Thetag_N_avg[290]+params.vg_N[290])*(-params.Vg_N_avg[290]-params.Thetag_N_avg[290]+params.vg_N[290])+(-params.Vg_N_avg[291]-params.Thetag_N_avg[291]+params.vg_N[291])*(-params.Vg_N_avg[291]-params.Thetag_N_avg[291]+params.vg_N[291])+(-params.Vg_N_avg[292]-params.Thetag_N_avg[292]+params.vg_N[292])*(-params.Vg_N_avg[292]-params.Thetag_N_avg[292]+params.vg_N[292])+(-params.Vg_N_avg[293]-params.Thetag_N_avg[293]+params.vg_N[293])*(-params.Vg_N_avg[293]-params.Thetag_N_avg[293]+params.vg_N[293])+(-params.Vg_N_avg[294]-params.Thetag_N_avg[294]+params.vg_N[294])*(-params.Vg_N_avg[294]-params.Thetag_N_avg[294]+params.vg_N[294])+(-params.Vg_N_avg[295]-params.Thetag_N_avg[295]+params.vg_N[295])*(-params.Vg_N_avg[295]-params.Thetag_N_avg[295]+params.vg_N[295])+(-params.Vg_N_avg[296]-params.Thetag_N_avg[296]+params.vg_N[296])*(-params.Vg_N_avg[296]-params.Thetag_N_avg[296]+params.vg_N[296])+(-params.Vg_N_avg[297]-params.Thetag_N_avg[297]+params.vg_N[297])*(-params.Vg_N_avg[297]-params.Thetag_N_avg[297]+params.vg_N[297])+(-params.Vg_N_avg[298]-params.Thetag_N_avg[298]+params.vg_N[298])*(-params.Vg_N_avg[298]-params.Thetag_N_avg[298]+params.vg_N[298])+(-params.Vg_N_avg[299]-params.Thetag_N_avg[299]+params.vg_N[299])*(-params.Vg_N_avg[299]-params.Thetag_N_avg[299]+params.vg_N[299])+(-params.Vg_N_avg[300]-params.Thetag_N_avg[300]+params.vg_N[300])*(-params.Vg_N_avg[300]-params.Thetag_N_avg[300]+params.vg_N[300])+(-params.Vg_N_avg[301]-params.Thetag_N_avg[301]+params.vg_N[301])*(-params.Vg_N_avg[301]-params.Thetag_N_avg[301]+params.vg_N[301])+(-params.Vg_N_avg[302]-params.Thetag_N_avg[302]+params.vg_N[302])*(-params.Vg_N_avg[302]-params.Thetag_N_avg[302]+params.vg_N[302])+(-params.Vg_N_avg[303]-params.Thetag_N_avg[303]+params.vg_N[303])*(-params.Vg_N_avg[303]-params.Thetag_N_avg[303]+params.vg_N[303])+(-params.Vg_N_avg[304]-params.Thetag_N_avg[304]+params.vg_N[304])*(-params.Vg_N_avg[304]-params.Thetag_N_avg[304]+params.vg_N[304])+(-params.Vg_N_avg[305]-params.Thetag_N_avg[305]+params.vg_N[305])*(-params.Vg_N_avg[305]-params.Thetag_N_avg[305]+params.vg_N[305])+(-params.Vg_N_avg[306]-params.Thetag_N_avg[306]+params.vg_N[306])*(-params.Vg_N_avg[306]-params.Thetag_N_avg[306]+params.vg_N[306])+(-params.Vg_N_avg[307]-params.Thetag_N_avg[307]+params.vg_N[307])*(-params.Vg_N_avg[307]-params.Thetag_N_avg[307]+params.vg_N[307])+(-params.Vg_N_avg[308]-params.Thetag_N_avg[308]+params.vg_N[308])*(-params.Vg_N_avg[308]-params.Thetag_N_avg[308]+params.vg_N[308])+(-params.Vg_N_avg[309]-params.Thetag_N_avg[309]+params.vg_N[309])*(-params.Vg_N_avg[309]-params.Thetag_N_avg[309]+params.vg_N[309])+(-params.Vg_N_avg[310]-params.Thetag_N_avg[310]+params.vg_N[310])*(-params.Vg_N_avg[310]-params.Thetag_N_avg[310]+params.vg_N[310])+(-params.Vg_N_avg[311]-params.Thetag_N_avg[311]+params.vg_N[311])*(-params.Vg_N_avg[311]-params.Thetag_N_avg[311]+params.vg_N[311])+(-params.Vg_N_avg[312]-params.Thetag_N_avg[312]+params.vg_N[312])*(-params.Vg_N_avg[312]-params.Thetag_N_avg[312]+params.vg_N[312])+(-params.Vg_N_avg[313]-params.Thetag_N_avg[313]+params.vg_N[313])*(-params.Vg_N_avg[313]-params.Thetag_N_avg[313]+params.vg_N[313])+(-params.Vg_N_avg[314]-params.Thetag_N_avg[314]+params.vg_N[314])*(-params.Vg_N_avg[314]-params.Thetag_N_avg[314]+params.vg_N[314])+(-params.Vg_N_avg[315]-params.Thetag_N_avg[315]+params.vg_N[315])*(-params.Vg_N_avg[315]-params.Thetag_N_avg[315]+params.vg_N[315])+(-params.Vg_N_avg[316]-params.Thetag_N_avg[316]+params.vg_N[316])*(-params.Vg_N_avg[316]-params.Thetag_N_avg[316]+params.vg_N[316])+(-params.Vg_N_avg[317]-params.Thetag_N_avg[317]+params.vg_N[317])*(-params.Vg_N_avg[317]-params.Thetag_N_avg[317]+params.vg_N[317])+(-params.Vg_N_avg[318]-params.Thetag_N_avg[318]+params.vg_N[318])*(-params.Vg_N_avg[318]-params.Thetag_N_avg[318]+params.vg_N[318])+(-params.Vg_N_avg[319]-params.Thetag_N_avg[319]+params.vg_N[319])*(-params.Vg_N_avg[319]-params.Thetag_N_avg[319]+params.vg_N[319])+(-params.Vg_N_avg[320]-params.Thetag_N_avg[320]+params.vg_N[320])*(-params.Vg_N_avg[320]-params.Thetag_N_avg[320]+params.vg_N[320])+(-params.Vg_N_avg[321]-params.Thetag_N_avg[321]+params.vg_N[321])*(-params.Vg_N_avg[321]-params.Thetag_N_avg[321]+params.vg_N[321])+(-params.Vg_N_avg[322]-params.Thetag_N_avg[322]+params.vg_N[322])*(-params.Vg_N_avg[322]-params.Thetag_N_avg[322]+params.vg_N[322])+(-params.Vg_N_avg[323]-params.Thetag_N_avg[323]+params.vg_N[323])*(-params.Vg_N_avg[323]-params.Thetag_N_avg[323]+params.vg_N[323])+(-params.Vg_N_avg[324]-params.Thetag_N_avg[324]+params.vg_N[324])*(-params.Vg_N_avg[324]-params.Thetag_N_avg[324]+params.vg_N[324])+(-params.Vg_N_avg[325]-params.Thetag_N_avg[325]+params.vg_N[325])*(-params.Vg_N_avg[325]-params.Thetag_N_avg[325]+params.vg_N[325])+(-params.Vg_N_avg[326]-params.Thetag_N_avg[326]+params.vg_N[326])*(-params.Vg_N_avg[326]-params.Thetag_N_avg[326]+params.vg_N[326])+(-params.Vg_N_avg[327]-params.Thetag_N_avg[327]+params.vg_N[327])*(-params.Vg_N_avg[327]-params.Thetag_N_avg[327]+params.vg_N[327])+(-params.Vg_N_avg[328]-params.Thetag_N_avg[328]+params.vg_N[328])*(-params.Vg_N_avg[328]-params.Thetag_N_avg[328]+params.vg_N[328])+(-params.Vg_N_avg[329]-params.Thetag_N_avg[329]+params.vg_N[329])*(-params.Vg_N_avg[329]-params.Thetag_N_avg[329]+params.vg_N[329])+(-params.Vg_N_avg[330]-params.Thetag_N_avg[330]+params.vg_N[330])*(-params.Vg_N_avg[330]-params.Thetag_N_avg[330]+params.vg_N[330])+(-params.Vg_N_avg[331]-params.Thetag_N_avg[331]+params.vg_N[331])*(-params.Vg_N_avg[331]-params.Thetag_N_avg[331]+params.vg_N[331])+(-params.Vg_N_avg[332]-params.Thetag_N_avg[332]+params.vg_N[332])*(-params.Vg_N_avg[332]-params.Thetag_N_avg[332]+params.vg_N[332])+(-params.Vg_N_avg[333]-params.Thetag_N_avg[333]+params.vg_N[333])*(-params.Vg_N_avg[333]-params.Thetag_N_avg[333]+params.vg_N[333])+(-params.Vg_N_avg[334]-params.Thetag_N_avg[334]+params.vg_N[334])*(-params.Vg_N_avg[334]-params.Thetag_N_avg[334]+params.vg_N[334])+(-params.Vg_N_avg[335]-params.Thetag_N_avg[335]+params.vg_N[335])*(-params.Vg_N_avg[335]-params.Thetag_N_avg[335]+params.vg_N[335])+(-params.Vg_N_avg[336]-params.Thetag_N_avg[336]+params.vg_N[336])*(-params.Vg_N_avg[336]-params.Thetag_N_avg[336]+params.vg_N[336])+(-params.Vg_N_avg[337]-params.Thetag_N_avg[337]+params.vg_N[337])*(-params.Vg_N_avg[337]-params.Thetag_N_avg[337]+params.vg_N[337])+(-params.Vg_N_avg[338]-params.Thetag_N_avg[338]+params.vg_N[338])*(-params.Vg_N_avg[338]-params.Thetag_N_avg[338]+params.vg_N[338])+(-params.Vg_N_avg[339]-params.Thetag_N_avg[339]+params.vg_N[339])*(-params.Vg_N_avg[339]-params.Thetag_N_avg[339]+params.vg_N[339])+(-params.Vg_N_avg[340]-params.Thetag_N_avg[340]+params.vg_N[340])*(-params.Vg_N_avg[340]-params.Thetag_N_avg[340]+params.vg_N[340])+(-params.Vg_N_avg[341]-params.Thetag_N_avg[341]+params.vg_N[341])*(-params.Vg_N_avg[341]-params.Thetag_N_avg[341]+params.vg_N[341])+(-params.Vg_N_avg[342]-params.Thetag_N_avg[342]+params.vg_N[342])*(-params.Vg_N_avg[342]-params.Thetag_N_avg[342]+params.vg_N[342])+(-params.Vg_N_avg[343]-params.Thetag_N_avg[343]+params.vg_N[343])*(-params.Vg_N_avg[343]-params.Thetag_N_avg[343]+params.vg_N[343])+(-params.Vg_N_avg[344]-params.Thetag_N_avg[344]+params.vg_N[344])*(-params.Vg_N_avg[344]-params.Thetag_N_avg[344]+params.vg_N[344])+(-params.Vg_N_avg[345]-params.Thetag_N_avg[345]+params.vg_N[345])*(-params.Vg_N_avg[345]-params.Thetag_N_avg[345]+params.vg_N[345])+(-params.Vg_N_avg[346]-params.Thetag_N_avg[346]+params.vg_N[346])*(-params.Vg_N_avg[346]-params.Thetag_N_avg[346]+params.vg_N[346])+(-params.Vg_N_avg[347]-params.Thetag_N_avg[347]+params.vg_N[347])*(-params.Vg_N_avg[347]-params.Thetag_N_avg[347]+params.vg_N[347])+(-params.Vg_N_avg[348]-params.Thetag_N_avg[348]+params.vg_N[348])*(-params.Vg_N_avg[348]-params.Thetag_N_avg[348]+params.vg_N[348])+(-params.Vg_N_avg[349]-params.Thetag_N_avg[349]+params.vg_N[349])*(-params.Vg_N_avg[349]-params.Thetag_N_avg[349]+params.vg_N[349])+(-params.Vg_N_avg[350]-params.Thetag_N_avg[350]+params.vg_N[350])*(-params.Vg_N_avg[350]-params.Thetag_N_avg[350]+params.vg_N[350])+(-params.Vg_N_avg[351]-params.Thetag_N_avg[351]+params.vg_N[351])*(-params.Vg_N_avg[351]-params.Thetag_N_avg[351]+params.vg_N[351])+(-params.Vg_N_avg[352]-params.Thetag_N_avg[352]+params.vg_N[352])*(-params.Vg_N_avg[352]-params.Thetag_N_avg[352]+params.vg_N[352])+(-params.Vg_N_avg[353]-params.Thetag_N_avg[353]+params.vg_N[353])*(-params.Vg_N_avg[353]-params.Thetag_N_avg[353]+params.vg_N[353])+(-params.Vg_N_avg[354]-params.Thetag_N_avg[354]+params.vg_N[354])*(-params.Vg_N_avg[354]-params.Thetag_N_avg[354]+params.vg_N[354])+(-params.Vg_N_avg[355]-params.Thetag_N_avg[355]+params.vg_N[355])*(-params.Vg_N_avg[355]-params.Thetag_N_avg[355]+params.vg_N[355])+(-params.Vg_N_avg[356]-params.Thetag_N_avg[356]+params.vg_N[356])*(-params.Vg_N_avg[356]-params.Thetag_N_avg[356]+params.vg_N[356])+(-params.Vg_N_avg[357]-params.Thetag_N_avg[357]+params.vg_N[357])*(-params.Vg_N_avg[357]-params.Thetag_N_avg[357]+params.vg_N[357])+(-params.Vg_N_avg[358]-params.Thetag_N_avg[358]+params.vg_N[358])*(-params.Vg_N_avg[358]-params.Thetag_N_avg[358]+params.vg_N[358])+(-params.Vg_N_avg[359]-params.Thetag_N_avg[359]+params.vg_N[359])*(-params.Vg_N_avg[359]-params.Thetag_N_avg[359]+params.vg_N[359])+(-params.Vg_N_avg[360]-params.Thetag_N_avg[360]+params.vg_N[360])*(-params.Vg_N_avg[360]-params.Thetag_N_avg[360]+params.vg_N[360])+(-params.Vg_N_avg[361]-params.Thetag_N_avg[361]+params.vg_N[361])*(-params.Vg_N_avg[361]-params.Thetag_N_avg[361]+params.vg_N[361])+(-params.Vg_N_avg[362]-params.Thetag_N_avg[362]+params.vg_N[362])*(-params.Vg_N_avg[362]-params.Thetag_N_avg[362]+params.vg_N[362])+(-params.Vg_N_avg[363]-params.Thetag_N_avg[363]+params.vg_N[363])*(-params.Vg_N_avg[363]-params.Thetag_N_avg[363]+params.vg_N[363])+(-params.Vg_N_avg[364]-params.Thetag_N_avg[364]+params.vg_N[364])*(-params.Vg_N_avg[364]-params.Thetag_N_avg[364]+params.vg_N[364])+(-params.Vg_N_avg[365]-params.Thetag_N_avg[365]+params.vg_N[365])*(-params.Vg_N_avg[365]-params.Thetag_N_avg[365]+params.vg_N[365])+(-params.Vg_N_avg[366]-params.Thetag_N_avg[366]+params.vg_N[366])*(-params.Vg_N_avg[366]-params.Thetag_N_avg[366]+params.vg_N[366])+(-params.Vg_N_avg[367]-params.Thetag_N_avg[367]+params.vg_N[367])*(-params.Vg_N_avg[367]-params.Thetag_N_avg[367]+params.vg_N[367])+(-params.Vg_N_avg[368]-params.Thetag_N_avg[368]+params.vg_N[368])*(-params.Vg_N_avg[368]-params.Thetag_N_avg[368]+params.vg_N[368])+(-params.Vg_N_avg[369]-params.Thetag_N_avg[369]+params.vg_N[369])*(-params.Vg_N_avg[369]-params.Thetag_N_avg[369]+params.vg_N[369])+(-params.Vg_N_avg[370]-params.Thetag_N_avg[370]+params.vg_N[370])*(-params.Vg_N_avg[370]-params.Thetag_N_avg[370]+params.vg_N[370])+(-params.Vg_N_avg[371]-params.Thetag_N_avg[371]+params.vg_N[371])*(-params.Vg_N_avg[371]-params.Thetag_N_avg[371]+params.vg_N[371])+(-params.Vg_N_avg[372]-params.Thetag_N_avg[372]+params.vg_N[372])*(-params.Vg_N_avg[372]-params.Thetag_N_avg[372]+params.vg_N[372])+(-params.Vg_N_avg[373]-params.Thetag_N_avg[373]+params.vg_N[373])*(-params.Vg_N_avg[373]-params.Thetag_N_avg[373]+params.vg_N[373])+(-params.Vg_N_avg[374]-params.Thetag_N_avg[374]+params.vg_N[374])*(-params.Vg_N_avg[374]-params.Thetag_N_avg[374]+params.vg_N[374])+(-params.Vg_N_avg[375]-params.Thetag_N_avg[375]+params.vg_N[375])*(-params.Vg_N_avg[375]-params.Thetag_N_avg[375]+params.vg_N[375])+(-params.Vg_N_avg[376]-params.Thetag_N_avg[376]+params.vg_N[376])*(-params.Vg_N_avg[376]-params.Thetag_N_avg[376]+params.vg_N[376])+(-params.Vg_N_avg[377]-params.Thetag_N_avg[377]+params.vg_N[377])*(-params.Vg_N_avg[377]-params.Thetag_N_avg[377]+params.vg_N[377])+(-params.Vg_N_avg[378]-params.Thetag_N_avg[378]+params.vg_N[378])*(-params.Vg_N_avg[378]-params.Thetag_N_avg[378]+params.vg_N[378])+(-params.Vg_N_avg[379]-params.Thetag_N_avg[379]+params.vg_N[379])*(-params.Vg_N_avg[379]-params.Thetag_N_avg[379]+params.vg_N[379])+(-params.Vg_N_avg[380]-params.Thetag_N_avg[380]+params.vg_N[380])*(-params.Vg_N_avg[380]-params.Thetag_N_avg[380]+params.vg_N[380])+(-params.Vg_N_avg[381]-params.Thetag_N_avg[381]+params.vg_N[381])*(-params.Vg_N_avg[381]-params.Thetag_N_avg[381]+params.vg_N[381])+(-params.Vg_N_avg[382]-params.Thetag_N_avg[382]+params.vg_N[382])*(-params.Vg_N_avg[382]-params.Thetag_N_avg[382]+params.vg_N[382])+(-params.Vg_N_avg[383]-params.Thetag_N_avg[383]+params.vg_N[383])*(-params.Vg_N_avg[383]-params.Thetag_N_avg[383]+params.vg_N[383])+(-params.Vg_N_avg[384]-params.Thetag_N_avg[384]+params.vg_N[384])*(-params.Vg_N_avg[384]-params.Thetag_N_avg[384]+params.vg_N[384])+(-params.Vg_N_avg[385]-params.Thetag_N_avg[385]+params.vg_N[385])*(-params.Vg_N_avg[385]-params.Thetag_N_avg[385]+params.vg_N[385])+(-params.Vg_N_avg[386]-params.Thetag_N_avg[386]+params.vg_N[386])*(-params.Vg_N_avg[386]-params.Thetag_N_avg[386]+params.vg_N[386])+(-params.Vg_N_avg[387]-params.Thetag_N_avg[387]+params.vg_N[387])*(-params.Vg_N_avg[387]-params.Thetag_N_avg[387]+params.vg_N[387])+(-params.Vg_N_avg[388]-params.Thetag_N_avg[388]+params.vg_N[388])*(-params.Vg_N_avg[388]-params.Thetag_N_avg[388]+params.vg_N[388])+(-params.Vg_N_avg[389]-params.Thetag_N_avg[389]+params.vg_N[389])*(-params.Vg_N_avg[389]-params.Thetag_N_avg[389]+params.vg_N[389])+(-params.Vg_N_avg[390]-params.Thetag_N_avg[390]+params.vg_N[390])*(-params.Vg_N_avg[390]-params.Thetag_N_avg[390]+params.vg_N[390])+(-params.Vg_N_avg[391]-params.Thetag_N_avg[391]+params.vg_N[391])*(-params.Vg_N_avg[391]-params.Thetag_N_avg[391]+params.vg_N[391])+(-params.Vg_N_avg[392]-params.Thetag_N_avg[392]+params.vg_N[392])*(-params.Vg_N_avg[392]-params.Thetag_N_avg[392]+params.vg_N[392])+(-params.Vg_N_avg[393]-params.Thetag_N_avg[393]+params.vg_N[393])*(-params.Vg_N_avg[393]-params.Thetag_N_avg[393]+params.vg_N[393])+(-params.Vg_N_avg[394]-params.Thetag_N_avg[394]+params.vg_N[394])*(-params.Vg_N_avg[394]-params.Thetag_N_avg[394]+params.vg_N[394])+(-params.Vg_N_avg[395]-params.Thetag_N_avg[395]+params.vg_N[395])*(-params.Vg_N_avg[395]-params.Thetag_N_avg[395]+params.vg_N[395])+(-params.Vg_N_avg[396]-params.Thetag_N_avg[396]+params.vg_N[396])*(-params.Vg_N_avg[396]-params.Thetag_N_avg[396]+params.vg_N[396])+(-params.Vg_N_avg[397]-params.Thetag_N_avg[397]+params.vg_N[397])*(-params.Vg_N_avg[397]-params.Thetag_N_avg[397]+params.vg_N[397])+(-params.Vg_N_avg[398]-params.Thetag_N_avg[398]+params.vg_N[398])*(-params.Vg_N_avg[398]-params.Thetag_N_avg[398]+params.vg_N[398])+(-params.Vg_N_avg[399]-params.Thetag_N_avg[399]+params.vg_N[399])*(-params.Vg_N_avg[399]-params.Thetag_N_avg[399]+params.vg_N[399])+(-params.Vg_N_avg[400]-params.Thetag_N_avg[400]+params.vg_N[400])*(-params.Vg_N_avg[400]-params.Thetag_N_avg[400]+params.vg_N[400]));
}

//ldl.cpp
/* Produced by CVXGEN, 2015-03-30 03:58:13 -0400.  */
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
  work.v[60] = target[61];
  work.v[61] = target[62];
  work.v[62] = target[63];
  work.v[63] = target[64];
  work.v[64] = target[65];
  work.v[65] = target[66];
  work.v[66] = target[67];
  work.v[67] = target[68];
  work.v[68] = target[69];
  work.v[69] = target[70];
  work.v[70] = target[71];
  work.v[71] = target[72];
  work.v[72] = target[73];
  work.v[73] = target[74];
  work.v[74] = target[75];
  work.v[75] = target[76];
  work.v[76] = target[77];
  work.v[77] = target[78];
  work.v[78] = target[79];
  work.v[79] = target[80];
  work.v[80] = target[81];
  work.v[81] = target[82];
  work.v[82] = target[83];
  work.v[83] = target[84];
  work.v[84] = target[85];
  work.v[85] = target[86];
  work.v[86] = target[87];
  work.v[87] = target[88];
  work.v[88] = target[89];
  work.v[89] = target[90];
  work.v[90] = target[91];
  work.v[91] = target[92];
  work.v[92] = target[93];
  work.v[93] = target[94];
  work.v[94] = target[95];
  work.v[95] = target[96];
  work.v[96] = target[97];
  work.v[97] = target[98];
  work.v[98] = target[99];
  work.v[99] = target[100];
  work.v[100] = target[101];
  work.v[101] = target[102];
  work.v[102] = target[103];
  work.v[103] = target[104];
  work.v[104] = target[105];
  work.v[105] = target[106];
  work.v[106] = target[107];
  work.v[107] = target[108];
  work.v[108] = target[109];
  work.v[109] = target[110];
  work.v[110] = target[111];
  work.v[111] = target[112];
  work.v[112] = target[113];
  work.v[113] = target[114];
  work.v[114] = target[115];
  work.v[115] = target[116];
  work.v[116] = target[117];
  work.v[117] = target[118];
  work.v[118] = target[119];
  work.v[119] = target[120];
  work.v[120] = target[121];
  work.v[121] = target[122];
  work.v[122] = target[123];
  work.v[123] = target[124];
  work.v[124] = target[125];
  work.v[125] = target[126];
  work.v[126] = target[127];
  work.v[127] = target[128];
  work.v[128] = target[129];
  work.v[129] = target[130];
  work.v[130] = target[131];
  work.v[131] = target[132];
  work.v[132] = target[133];
  work.v[133] = target[134];
  work.v[134] = target[135];
  work.v[135] = target[136];
  work.v[136] = target[137];
  work.v[137] = target[138];
  work.v[138] = target[139];
  work.v[139] = target[140];
  work.v[140] = target[141];
  work.v[141] = target[142];
  work.v[142] = target[143];
  work.v[143] = target[144];
  work.v[144] = target[145];
  work.v[145] = target[146];
  work.v[146] = target[147];
  work.v[147] = target[148];
  work.v[148] = target[149];
  work.v[149] = target[150];
  work.v[150] = target[151];
  work.v[151] = target[152];
  work.v[152] = target[153];
  work.v[153] = target[154];
  work.v[154] = target[155];
  work.v[155] = target[156];
  work.v[156] = target[157];
  work.v[157] = target[158];
  work.v[158] = target[159];
  work.v[159] = target[160];
  work.v[160] = target[161];
  work.v[161] = target[162];
  work.v[162] = target[163];
  work.v[163] = target[164];
  work.v[164] = target[165];
  work.v[165] = target[166];
  work.v[166] = target[167];
  work.v[167] = target[168];
  work.v[168] = target[169];
  work.v[169] = target[170];
  work.v[170] = target[171];
  work.v[171] = target[172];
  work.v[172] = target[173];
  work.v[173] = target[174];
  work.v[174] = target[175];
  work.v[175] = target[176];
  work.v[176] = target[177];
  work.v[177] = target[178];
  work.v[178] = target[179];
  work.v[179] = target[180];
  work.v[180] = target[181];
  work.v[181] = target[182];
  work.v[182] = target[183];
  work.v[183] = target[184];
  work.v[184] = target[185];
  work.v[185] = target[186];
  work.v[186] = target[187];
  work.v[187] = target[188];
  work.v[188] = target[189];
  work.v[189] = target[190];
  work.v[190] = target[191];
  work.v[191] = target[192];
  work.v[192] = target[193];
  work.v[193] = target[194];
  work.v[194] = target[195];
  work.v[195] = target[196];
  work.v[196] = target[197];
  work.v[197] = target[198];
  work.v[198] = target[199];
  work.v[199] = target[200];
  work.v[200] = target[201];
  work.v[201] = target[202];
  work.v[202] = target[203];
  work.v[203] = target[204];
  work.v[204] = target[205];
  work.v[205] = target[206];
  work.v[206] = target[207];
  work.v[207] = target[208];
  work.v[208] = target[209];
  work.v[209] = target[210];
  work.v[210] = target[211];
  work.v[211] = target[212];
  work.v[212] = target[213];
  work.v[213] = target[214];
  work.v[214] = target[215];
  work.v[215] = target[216];
  work.v[216] = target[217];
  work.v[217] = target[218];
  work.v[218] = target[219];
  work.v[219] = target[220];
  work.v[220] = target[221];
  work.v[221] = target[222];
  work.v[222] = target[223];
  work.v[223] = target[224];
  work.v[224] = target[225];
  work.v[225] = target[226];
  work.v[226] = target[227];
  work.v[227] = target[228];
  work.v[228] = target[229];
  work.v[229] = target[230];
  work.v[230] = target[231];
  work.v[231] = target[232];
  work.v[232] = target[233];
  work.v[233] = target[234];
  work.v[234] = target[235];
  work.v[235] = target[236];
  work.v[236] = target[237];
  work.v[237] = target[238];
  work.v[238] = target[239];
  work.v[239] = target[240];
  work.v[240] = target[241];
  work.v[241] = target[242];
  work.v[242] = target[243];
  work.v[243] = target[244];
  work.v[244] = target[245];
  work.v[245] = target[246];
  work.v[246] = target[247];
  work.v[247] = target[248];
  work.v[248] = target[249];
  work.v[249] = target[250];
  work.v[250] = target[251];
  work.v[251] = target[252];
  work.v[252] = target[253];
  work.v[253] = target[254];
  work.v[254] = target[255];
  work.v[255] = target[256];
  work.v[256] = target[257];
  work.v[257] = target[258];
  work.v[258] = target[259];
  work.v[259] = target[260];
  work.v[260] = target[261];
  work.v[261] = target[262];
  work.v[262] = target[263];
  work.v[263] = target[264];
  work.v[264] = target[265];
  work.v[265] = target[266];
  work.v[266] = target[267];
  work.v[267] = target[268];
  work.v[268] = target[269];
  work.v[269] = target[270];
  work.v[270] = target[271];
  work.v[271] = target[272];
  work.v[272] = target[273];
  work.v[273] = target[274];
  work.v[274] = target[275];
  work.v[275] = target[276];
  work.v[276] = target[277];
  work.v[277] = target[278];
  work.v[278] = target[279];
  work.v[279] = target[280];
  work.v[280] = target[281];
  work.v[281] = target[282];
  work.v[282] = target[283];
  work.v[283] = target[284];
  work.v[284] = target[285];
  work.v[285] = target[286];
  work.v[286] = target[287];
  work.v[287] = target[288];
  work.v[288] = target[289];
  work.v[289] = target[290];
  work.v[290] = target[291];
  work.v[291] = target[292];
  work.v[292] = target[293];
  work.v[293] = target[294];
  work.v[294] = target[295];
  work.v[295] = target[296];
  work.v[296] = target[297];
  work.v[297] = target[298];
  work.v[298] = target[299];
  work.v[299] = target[300];
  work.v[300] = target[301];
  work.v[301] = target[302];
  work.v[302] = target[303];
  work.v[303] = target[304];
  work.v[304] = target[305];
  work.v[305] = target[306];
  work.v[306] = target[307];
  work.v[307] = target[308];
  work.v[308] = target[309];
  work.v[309] = target[310];
  work.v[310] = target[311];
  work.v[311] = target[312];
  work.v[312] = target[313];
  work.v[313] = target[314];
  work.v[314] = target[315];
  work.v[315] = target[316];
  work.v[316] = target[317];
  work.v[317] = target[318];
  work.v[318] = target[319];
  work.v[319] = target[320];
  work.v[320] = target[321];
  work.v[321] = target[322];
  work.v[322] = target[323];
  work.v[323] = target[324];
  work.v[324] = target[325];
  work.v[325] = target[326];
  work.v[326] = target[327];
  work.v[327] = target[328];
  work.v[328] = target[329];
  work.v[329] = target[330];
  work.v[330] = target[331];
  work.v[331] = target[332];
  work.v[332] = target[333];
  work.v[333] = target[334];
  work.v[334] = target[335];
  work.v[335] = target[336];
  work.v[336] = target[337];
  work.v[337] = target[338];
  work.v[338] = target[339];
  work.v[339] = target[340];
  work.v[340] = target[341];
  work.v[341] = target[342];
  work.v[342] = target[343];
  work.v[343] = target[344];
  work.v[344] = target[345];
  work.v[345] = target[346];
  work.v[346] = target[347];
  work.v[347] = target[348];
  work.v[348] = target[349];
  work.v[349] = target[350];
  work.v[350] = target[351];
  work.v[351] = target[352];
  work.v[352] = target[353];
  work.v[353] = target[354];
  work.v[354] = target[355];
  work.v[355] = target[356];
  work.v[356] = target[357];
  work.v[357] = target[358];
  work.v[358] = target[359];
  work.v[359] = target[360];
  work.v[360] = target[361];
  work.v[361] = target[362];
  work.v[362] = target[363];
  work.v[363] = target[364];
  work.v[364] = target[365];
  work.v[365] = target[366];
  work.v[366] = target[367];
  work.v[367] = target[368];
  work.v[368] = target[369];
  work.v[369] = target[370];
  work.v[370] = target[371];
  work.v[371] = target[372];
  work.v[372] = target[373];
  work.v[373] = target[374];
  work.v[374] = target[375];
  work.v[375] = target[376];
  work.v[376] = target[377];
  work.v[377] = target[378];
  work.v[378] = target[379];
  work.v[379] = target[380];
  work.v[380] = target[381];
  work.v[381] = target[382];
  work.v[382] = target[383];
  work.v[383] = target[384];
  work.v[384] = target[385];
  work.v[385] = target[386];
  work.v[386] = target[387];
  work.v[387] = target[388];
  work.v[388] = target[389];
  work.v[389] = target[390];
  work.v[390] = target[391];
  work.v[391] = target[392];
  work.v[392] = target[393];
  work.v[393] = target[394];
  work.v[394] = target[395];
  work.v[395] = target[396];
  work.v[396] = target[397];
  work.v[397] = target[398];
  work.v[398] = target[399];
  work.v[399] = target[400];
  work.v[400] = target[401];
  work.v[401] = target[402];
  work.v[402] = target[403];
  work.v[403] = target[404]-work.L[0]*work.v[401];
  work.v[404] = target[0]-work.L[1]*work.v[403];
  work.v[405] = target[405]-work.L[2]*work.v[402]-work.L[3]*work.v[404];
  /* Diagonal scaling. Assume correctness of work.d_inv. */
  for (i = 0; i < 406; i++)
    work.v[i] *= work.d_inv[i];
  /* Back substitution */
  work.v[404] -= work.L[3]*work.v[405];
  work.v[403] -= work.L[1]*work.v[404];
  work.v[402] -= work.L[2]*work.v[405];
  work.v[401] -= work.L[0]*work.v[403];
  /* Unpermute the result, from v to var. */
  var[0] = work.v[404];
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
  var[62] = work.v[61];
  var[63] = work.v[62];
  var[64] = work.v[63];
  var[65] = work.v[64];
  var[66] = work.v[65];
  var[67] = work.v[66];
  var[68] = work.v[67];
  var[69] = work.v[68];
  var[70] = work.v[69];
  var[71] = work.v[70];
  var[72] = work.v[71];
  var[73] = work.v[72];
  var[74] = work.v[73];
  var[75] = work.v[74];
  var[76] = work.v[75];
  var[77] = work.v[76];
  var[78] = work.v[77];
  var[79] = work.v[78];
  var[80] = work.v[79];
  var[81] = work.v[80];
  var[82] = work.v[81];
  var[83] = work.v[82];
  var[84] = work.v[83];
  var[85] = work.v[84];
  var[86] = work.v[85];
  var[87] = work.v[86];
  var[88] = work.v[87];
  var[89] = work.v[88];
  var[90] = work.v[89];
  var[91] = work.v[90];
  var[92] = work.v[91];
  var[93] = work.v[92];
  var[94] = work.v[93];
  var[95] = work.v[94];
  var[96] = work.v[95];
  var[97] = work.v[96];
  var[98] = work.v[97];
  var[99] = work.v[98];
  var[100] = work.v[99];
  var[101] = work.v[100];
  var[102] = work.v[101];
  var[103] = work.v[102];
  var[104] = work.v[103];
  var[105] = work.v[104];
  var[106] = work.v[105];
  var[107] = work.v[106];
  var[108] = work.v[107];
  var[109] = work.v[108];
  var[110] = work.v[109];
  var[111] = work.v[110];
  var[112] = work.v[111];
  var[113] = work.v[112];
  var[114] = work.v[113];
  var[115] = work.v[114];
  var[116] = work.v[115];
  var[117] = work.v[116];
  var[118] = work.v[117];
  var[119] = work.v[118];
  var[120] = work.v[119];
  var[121] = work.v[120];
  var[122] = work.v[121];
  var[123] = work.v[122];
  var[124] = work.v[123];
  var[125] = work.v[124];
  var[126] = work.v[125];
  var[127] = work.v[126];
  var[128] = work.v[127];
  var[129] = work.v[128];
  var[130] = work.v[129];
  var[131] = work.v[130];
  var[132] = work.v[131];
  var[133] = work.v[132];
  var[134] = work.v[133];
  var[135] = work.v[134];
  var[136] = work.v[135];
  var[137] = work.v[136];
  var[138] = work.v[137];
  var[139] = work.v[138];
  var[140] = work.v[139];
  var[141] = work.v[140];
  var[142] = work.v[141];
  var[143] = work.v[142];
  var[144] = work.v[143];
  var[145] = work.v[144];
  var[146] = work.v[145];
  var[147] = work.v[146];
  var[148] = work.v[147];
  var[149] = work.v[148];
  var[150] = work.v[149];
  var[151] = work.v[150];
  var[152] = work.v[151];
  var[153] = work.v[152];
  var[154] = work.v[153];
  var[155] = work.v[154];
  var[156] = work.v[155];
  var[157] = work.v[156];
  var[158] = work.v[157];
  var[159] = work.v[158];
  var[160] = work.v[159];
  var[161] = work.v[160];
  var[162] = work.v[161];
  var[163] = work.v[162];
  var[164] = work.v[163];
  var[165] = work.v[164];
  var[166] = work.v[165];
  var[167] = work.v[166];
  var[168] = work.v[167];
  var[169] = work.v[168];
  var[170] = work.v[169];
  var[171] = work.v[170];
  var[172] = work.v[171];
  var[173] = work.v[172];
  var[174] = work.v[173];
  var[175] = work.v[174];
  var[176] = work.v[175];
  var[177] = work.v[176];
  var[178] = work.v[177];
  var[179] = work.v[178];
  var[180] = work.v[179];
  var[181] = work.v[180];
  var[182] = work.v[181];
  var[183] = work.v[182];
  var[184] = work.v[183];
  var[185] = work.v[184];
  var[186] = work.v[185];
  var[187] = work.v[186];
  var[188] = work.v[187];
  var[189] = work.v[188];
  var[190] = work.v[189];
  var[191] = work.v[190];
  var[192] = work.v[191];
  var[193] = work.v[192];
  var[194] = work.v[193];
  var[195] = work.v[194];
  var[196] = work.v[195];
  var[197] = work.v[196];
  var[198] = work.v[197];
  var[199] = work.v[198];
  var[200] = work.v[199];
  var[201] = work.v[200];
  var[202] = work.v[201];
  var[203] = work.v[202];
  var[204] = work.v[203];
  var[205] = work.v[204];
  var[206] = work.v[205];
  var[207] = work.v[206];
  var[208] = work.v[207];
  var[209] = work.v[208];
  var[210] = work.v[209];
  var[211] = work.v[210];
  var[212] = work.v[211];
  var[213] = work.v[212];
  var[214] = work.v[213];
  var[215] = work.v[214];
  var[216] = work.v[215];
  var[217] = work.v[216];
  var[218] = work.v[217];
  var[219] = work.v[218];
  var[220] = work.v[219];
  var[221] = work.v[220];
  var[222] = work.v[221];
  var[223] = work.v[222];
  var[224] = work.v[223];
  var[225] = work.v[224];
  var[226] = work.v[225];
  var[227] = work.v[226];
  var[228] = work.v[227];
  var[229] = work.v[228];
  var[230] = work.v[229];
  var[231] = work.v[230];
  var[232] = work.v[231];
  var[233] = work.v[232];
  var[234] = work.v[233];
  var[235] = work.v[234];
  var[236] = work.v[235];
  var[237] = work.v[236];
  var[238] = work.v[237];
  var[239] = work.v[238];
  var[240] = work.v[239];
  var[241] = work.v[240];
  var[242] = work.v[241];
  var[243] = work.v[242];
  var[244] = work.v[243];
  var[245] = work.v[244];
  var[246] = work.v[245];
  var[247] = work.v[246];
  var[248] = work.v[247];
  var[249] = work.v[248];
  var[250] = work.v[249];
  var[251] = work.v[250];
  var[252] = work.v[251];
  var[253] = work.v[252];
  var[254] = work.v[253];
  var[255] = work.v[254];
  var[256] = work.v[255];
  var[257] = work.v[256];
  var[258] = work.v[257];
  var[259] = work.v[258];
  var[260] = work.v[259];
  var[261] = work.v[260];
  var[262] = work.v[261];
  var[263] = work.v[262];
  var[264] = work.v[263];
  var[265] = work.v[264];
  var[266] = work.v[265];
  var[267] = work.v[266];
  var[268] = work.v[267];
  var[269] = work.v[268];
  var[270] = work.v[269];
  var[271] = work.v[270];
  var[272] = work.v[271];
  var[273] = work.v[272];
  var[274] = work.v[273];
  var[275] = work.v[274];
  var[276] = work.v[275];
  var[277] = work.v[276];
  var[278] = work.v[277];
  var[279] = work.v[278];
  var[280] = work.v[279];
  var[281] = work.v[280];
  var[282] = work.v[281];
  var[283] = work.v[282];
  var[284] = work.v[283];
  var[285] = work.v[284];
  var[286] = work.v[285];
  var[287] = work.v[286];
  var[288] = work.v[287];
  var[289] = work.v[288];
  var[290] = work.v[289];
  var[291] = work.v[290];
  var[292] = work.v[291];
  var[293] = work.v[292];
  var[294] = work.v[293];
  var[295] = work.v[294];
  var[296] = work.v[295];
  var[297] = work.v[296];
  var[298] = work.v[297];
  var[299] = work.v[298];
  var[300] = work.v[299];
  var[301] = work.v[300];
  var[302] = work.v[301];
  var[303] = work.v[302];
  var[304] = work.v[303];
  var[305] = work.v[304];
  var[306] = work.v[305];
  var[307] = work.v[306];
  var[308] = work.v[307];
  var[309] = work.v[308];
  var[310] = work.v[309];
  var[311] = work.v[310];
  var[312] = work.v[311];
  var[313] = work.v[312];
  var[314] = work.v[313];
  var[315] = work.v[314];
  var[316] = work.v[315];
  var[317] = work.v[316];
  var[318] = work.v[317];
  var[319] = work.v[318];
  var[320] = work.v[319];
  var[321] = work.v[320];
  var[322] = work.v[321];
  var[323] = work.v[322];
  var[324] = work.v[323];
  var[325] = work.v[324];
  var[326] = work.v[325];
  var[327] = work.v[326];
  var[328] = work.v[327];
  var[329] = work.v[328];
  var[330] = work.v[329];
  var[331] = work.v[330];
  var[332] = work.v[331];
  var[333] = work.v[332];
  var[334] = work.v[333];
  var[335] = work.v[334];
  var[336] = work.v[335];
  var[337] = work.v[336];
  var[338] = work.v[337];
  var[339] = work.v[338];
  var[340] = work.v[339];
  var[341] = work.v[340];
  var[342] = work.v[341];
  var[343] = work.v[342];
  var[344] = work.v[343];
  var[345] = work.v[344];
  var[346] = work.v[345];
  var[347] = work.v[346];
  var[348] = work.v[347];
  var[349] = work.v[348];
  var[350] = work.v[349];
  var[351] = work.v[350];
  var[352] = work.v[351];
  var[353] = work.v[352];
  var[354] = work.v[353];
  var[355] = work.v[354];
  var[356] = work.v[355];
  var[357] = work.v[356];
  var[358] = work.v[357];
  var[359] = work.v[358];
  var[360] = work.v[359];
  var[361] = work.v[360];
  var[362] = work.v[361];
  var[363] = work.v[362];
  var[364] = work.v[363];
  var[365] = work.v[364];
  var[366] = work.v[365];
  var[367] = work.v[366];
  var[368] = work.v[367];
  var[369] = work.v[368];
  var[370] = work.v[369];
  var[371] = work.v[370];
  var[372] = work.v[371];
  var[373] = work.v[372];
  var[374] = work.v[373];
  var[375] = work.v[374];
  var[376] = work.v[375];
  var[377] = work.v[376];
  var[378] = work.v[377];
  var[379] = work.v[378];
  var[380] = work.v[379];
  var[381] = work.v[380];
  var[382] = work.v[381];
  var[383] = work.v[382];
  var[384] = work.v[383];
  var[385] = work.v[384];
  var[386] = work.v[385];
  var[387] = work.v[386];
  var[388] = work.v[387];
  var[389] = work.v[388];
  var[390] = work.v[389];
  var[391] = work.v[390];
  var[392] = work.v[391];
  var[393] = work.v[392];
  var[394] = work.v[393];
  var[395] = work.v[394];
  var[396] = work.v[395];
  var[397] = work.v[396];
  var[398] = work.v[397];
  var[399] = work.v[398];
  var[400] = work.v[399];
  var[401] = work.v[400];
  var[402] = work.v[401];
  var[403] = work.v[402];
  var[404] = work.v[403];
  var[405] = work.v[405];
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
  work.v[59] = work.KKT[59];
  work.d[59] = work.v[59];
  if (work.d[59] < 0)
    work.d[59] = settings.kkt_reg;
  else
    work.d[59] += settings.kkt_reg;
  work.d_inv[59] = 1/work.d[59];
  work.v[60] = work.KKT[60];
  work.d[60] = work.v[60];
  if (work.d[60] < 0)
    work.d[60] = settings.kkt_reg;
  else
    work.d[60] += settings.kkt_reg;
  work.d_inv[60] = 1/work.d[60];
  work.v[61] = work.KKT[61];
  work.d[61] = work.v[61];
  if (work.d[61] < 0)
    work.d[61] = settings.kkt_reg;
  else
    work.d[61] += settings.kkt_reg;
  work.d_inv[61] = 1/work.d[61];
  work.v[62] = work.KKT[62];
  work.d[62] = work.v[62];
  if (work.d[62] < 0)
    work.d[62] = settings.kkt_reg;
  else
    work.d[62] += settings.kkt_reg;
  work.d_inv[62] = 1/work.d[62];
  work.v[63] = work.KKT[63];
  work.d[63] = work.v[63];
  if (work.d[63] < 0)
    work.d[63] = settings.kkt_reg;
  else
    work.d[63] += settings.kkt_reg;
  work.d_inv[63] = 1/work.d[63];
  work.v[64] = work.KKT[64];
  work.d[64] = work.v[64];
  if (work.d[64] < 0)
    work.d[64] = settings.kkt_reg;
  else
    work.d[64] += settings.kkt_reg;
  work.d_inv[64] = 1/work.d[64];
  work.v[65] = work.KKT[65];
  work.d[65] = work.v[65];
  if (work.d[65] < 0)
    work.d[65] = settings.kkt_reg;
  else
    work.d[65] += settings.kkt_reg;
  work.d_inv[65] = 1/work.d[65];
  work.v[66] = work.KKT[66];
  work.d[66] = work.v[66];
  if (work.d[66] < 0)
    work.d[66] = settings.kkt_reg;
  else
    work.d[66] += settings.kkt_reg;
  work.d_inv[66] = 1/work.d[66];
  work.v[67] = work.KKT[67];
  work.d[67] = work.v[67];
  if (work.d[67] < 0)
    work.d[67] = settings.kkt_reg;
  else
    work.d[67] += settings.kkt_reg;
  work.d_inv[67] = 1/work.d[67];
  work.v[68] = work.KKT[68];
  work.d[68] = work.v[68];
  if (work.d[68] < 0)
    work.d[68] = settings.kkt_reg;
  else
    work.d[68] += settings.kkt_reg;
  work.d_inv[68] = 1/work.d[68];
  work.v[69] = work.KKT[69];
  work.d[69] = work.v[69];
  if (work.d[69] < 0)
    work.d[69] = settings.kkt_reg;
  else
    work.d[69] += settings.kkt_reg;
  work.d_inv[69] = 1/work.d[69];
  work.v[70] = work.KKT[70];
  work.d[70] = work.v[70];
  if (work.d[70] < 0)
    work.d[70] = settings.kkt_reg;
  else
    work.d[70] += settings.kkt_reg;
  work.d_inv[70] = 1/work.d[70];
  work.v[71] = work.KKT[71];
  work.d[71] = work.v[71];
  if (work.d[71] < 0)
    work.d[71] = settings.kkt_reg;
  else
    work.d[71] += settings.kkt_reg;
  work.d_inv[71] = 1/work.d[71];
  work.v[72] = work.KKT[72];
  work.d[72] = work.v[72];
  if (work.d[72] < 0)
    work.d[72] = settings.kkt_reg;
  else
    work.d[72] += settings.kkt_reg;
  work.d_inv[72] = 1/work.d[72];
  work.v[73] = work.KKT[73];
  work.d[73] = work.v[73];
  if (work.d[73] < 0)
    work.d[73] = settings.kkt_reg;
  else
    work.d[73] += settings.kkt_reg;
  work.d_inv[73] = 1/work.d[73];
  work.v[74] = work.KKT[74];
  work.d[74] = work.v[74];
  if (work.d[74] < 0)
    work.d[74] = settings.kkt_reg;
  else
    work.d[74] += settings.kkt_reg;
  work.d_inv[74] = 1/work.d[74];
  work.v[75] = work.KKT[75];
  work.d[75] = work.v[75];
  if (work.d[75] < 0)
    work.d[75] = settings.kkt_reg;
  else
    work.d[75] += settings.kkt_reg;
  work.d_inv[75] = 1/work.d[75];
  work.v[76] = work.KKT[76];
  work.d[76] = work.v[76];
  if (work.d[76] < 0)
    work.d[76] = settings.kkt_reg;
  else
    work.d[76] += settings.kkt_reg;
  work.d_inv[76] = 1/work.d[76];
  work.v[77] = work.KKT[77];
  work.d[77] = work.v[77];
  if (work.d[77] < 0)
    work.d[77] = settings.kkt_reg;
  else
    work.d[77] += settings.kkt_reg;
  work.d_inv[77] = 1/work.d[77];
  work.v[78] = work.KKT[78];
  work.d[78] = work.v[78];
  if (work.d[78] < 0)
    work.d[78] = settings.kkt_reg;
  else
    work.d[78] += settings.kkt_reg;
  work.d_inv[78] = 1/work.d[78];
  work.v[79] = work.KKT[79];
  work.d[79] = work.v[79];
  if (work.d[79] < 0)
    work.d[79] = settings.kkt_reg;
  else
    work.d[79] += settings.kkt_reg;
  work.d_inv[79] = 1/work.d[79];
  work.v[80] = work.KKT[80];
  work.d[80] = work.v[80];
  if (work.d[80] < 0)
    work.d[80] = settings.kkt_reg;
  else
    work.d[80] += settings.kkt_reg;
  work.d_inv[80] = 1/work.d[80];
  work.v[81] = work.KKT[81];
  work.d[81] = work.v[81];
  if (work.d[81] < 0)
    work.d[81] = settings.kkt_reg;
  else
    work.d[81] += settings.kkt_reg;
  work.d_inv[81] = 1/work.d[81];
  work.v[82] = work.KKT[82];
  work.d[82] = work.v[82];
  if (work.d[82] < 0)
    work.d[82] = settings.kkt_reg;
  else
    work.d[82] += settings.kkt_reg;
  work.d_inv[82] = 1/work.d[82];
  work.v[83] = work.KKT[83];
  work.d[83] = work.v[83];
  if (work.d[83] < 0)
    work.d[83] = settings.kkt_reg;
  else
    work.d[83] += settings.kkt_reg;
  work.d_inv[83] = 1/work.d[83];
  work.v[84] = work.KKT[84];
  work.d[84] = work.v[84];
  if (work.d[84] < 0)
    work.d[84] = settings.kkt_reg;
  else
    work.d[84] += settings.kkt_reg;
  work.d_inv[84] = 1/work.d[84];
  work.v[85] = work.KKT[85];
  work.d[85] = work.v[85];
  if (work.d[85] < 0)
    work.d[85] = settings.kkt_reg;
  else
    work.d[85] += settings.kkt_reg;
  work.d_inv[85] = 1/work.d[85];
  work.v[86] = work.KKT[86];
  work.d[86] = work.v[86];
  if (work.d[86] < 0)
    work.d[86] = settings.kkt_reg;
  else
    work.d[86] += settings.kkt_reg;
  work.d_inv[86] = 1/work.d[86];
  work.v[87] = work.KKT[87];
  work.d[87] = work.v[87];
  if (work.d[87] < 0)
    work.d[87] = settings.kkt_reg;
  else
    work.d[87] += settings.kkt_reg;
  work.d_inv[87] = 1/work.d[87];
  work.v[88] = work.KKT[88];
  work.d[88] = work.v[88];
  if (work.d[88] < 0)
    work.d[88] = settings.kkt_reg;
  else
    work.d[88] += settings.kkt_reg;
  work.d_inv[88] = 1/work.d[88];
  work.v[89] = work.KKT[89];
  work.d[89] = work.v[89];
  if (work.d[89] < 0)
    work.d[89] = settings.kkt_reg;
  else
    work.d[89] += settings.kkt_reg;
  work.d_inv[89] = 1/work.d[89];
  work.v[90] = work.KKT[90];
  work.d[90] = work.v[90];
  if (work.d[90] < 0)
    work.d[90] = settings.kkt_reg;
  else
    work.d[90] += settings.kkt_reg;
  work.d_inv[90] = 1/work.d[90];
  work.v[91] = work.KKT[91];
  work.d[91] = work.v[91];
  if (work.d[91] < 0)
    work.d[91] = settings.kkt_reg;
  else
    work.d[91] += settings.kkt_reg;
  work.d_inv[91] = 1/work.d[91];
  work.v[92] = work.KKT[92];
  work.d[92] = work.v[92];
  if (work.d[92] < 0)
    work.d[92] = settings.kkt_reg;
  else
    work.d[92] += settings.kkt_reg;
  work.d_inv[92] = 1/work.d[92];
  work.v[93] = work.KKT[93];
  work.d[93] = work.v[93];
  if (work.d[93] < 0)
    work.d[93] = settings.kkt_reg;
  else
    work.d[93] += settings.kkt_reg;
  work.d_inv[93] = 1/work.d[93];
  work.v[94] = work.KKT[94];
  work.d[94] = work.v[94];
  if (work.d[94] < 0)
    work.d[94] = settings.kkt_reg;
  else
    work.d[94] += settings.kkt_reg;
  work.d_inv[94] = 1/work.d[94];
  work.v[95] = work.KKT[95];
  work.d[95] = work.v[95];
  if (work.d[95] < 0)
    work.d[95] = settings.kkt_reg;
  else
    work.d[95] += settings.kkt_reg;
  work.d_inv[95] = 1/work.d[95];
  work.v[96] = work.KKT[96];
  work.d[96] = work.v[96];
  if (work.d[96] < 0)
    work.d[96] = settings.kkt_reg;
  else
    work.d[96] += settings.kkt_reg;
  work.d_inv[96] = 1/work.d[96];
  work.v[97] = work.KKT[97];
  work.d[97] = work.v[97];
  if (work.d[97] < 0)
    work.d[97] = settings.kkt_reg;
  else
    work.d[97] += settings.kkt_reg;
  work.d_inv[97] = 1/work.d[97];
  work.v[98] = work.KKT[98];
  work.d[98] = work.v[98];
  if (work.d[98] < 0)
    work.d[98] = settings.kkt_reg;
  else
    work.d[98] += settings.kkt_reg;
  work.d_inv[98] = 1/work.d[98];
  work.v[99] = work.KKT[99];
  work.d[99] = work.v[99];
  if (work.d[99] < 0)
    work.d[99] = settings.kkt_reg;
  else
    work.d[99] += settings.kkt_reg;
  work.d_inv[99] = 1/work.d[99];
  work.v[100] = work.KKT[100];
  work.d[100] = work.v[100];
  if (work.d[100] < 0)
    work.d[100] = settings.kkt_reg;
  else
    work.d[100] += settings.kkt_reg;
  work.d_inv[100] = 1/work.d[100];
  work.v[101] = work.KKT[101];
  work.d[101] = work.v[101];
  if (work.d[101] < 0)
    work.d[101] = settings.kkt_reg;
  else
    work.d[101] += settings.kkt_reg;
  work.d_inv[101] = 1/work.d[101];
  work.v[102] = work.KKT[102];
  work.d[102] = work.v[102];
  if (work.d[102] < 0)
    work.d[102] = settings.kkt_reg;
  else
    work.d[102] += settings.kkt_reg;
  work.d_inv[102] = 1/work.d[102];
  work.v[103] = work.KKT[103];
  work.d[103] = work.v[103];
  if (work.d[103] < 0)
    work.d[103] = settings.kkt_reg;
  else
    work.d[103] += settings.kkt_reg;
  work.d_inv[103] = 1/work.d[103];
  work.v[104] = work.KKT[104];
  work.d[104] = work.v[104];
  if (work.d[104] < 0)
    work.d[104] = settings.kkt_reg;
  else
    work.d[104] += settings.kkt_reg;
  work.d_inv[104] = 1/work.d[104];
  work.v[105] = work.KKT[105];
  work.d[105] = work.v[105];
  if (work.d[105] < 0)
    work.d[105] = settings.kkt_reg;
  else
    work.d[105] += settings.kkt_reg;
  work.d_inv[105] = 1/work.d[105];
  work.v[106] = work.KKT[106];
  work.d[106] = work.v[106];
  if (work.d[106] < 0)
    work.d[106] = settings.kkt_reg;
  else
    work.d[106] += settings.kkt_reg;
  work.d_inv[106] = 1/work.d[106];
  work.v[107] = work.KKT[107];
  work.d[107] = work.v[107];
  if (work.d[107] < 0)
    work.d[107] = settings.kkt_reg;
  else
    work.d[107] += settings.kkt_reg;
  work.d_inv[107] = 1/work.d[107];
  work.v[108] = work.KKT[108];
  work.d[108] = work.v[108];
  if (work.d[108] < 0)
    work.d[108] = settings.kkt_reg;
  else
    work.d[108] += settings.kkt_reg;
  work.d_inv[108] = 1/work.d[108];
  work.v[109] = work.KKT[109];
  work.d[109] = work.v[109];
  if (work.d[109] < 0)
    work.d[109] = settings.kkt_reg;
  else
    work.d[109] += settings.kkt_reg;
  work.d_inv[109] = 1/work.d[109];
  work.v[110] = work.KKT[110];
  work.d[110] = work.v[110];
  if (work.d[110] < 0)
    work.d[110] = settings.kkt_reg;
  else
    work.d[110] += settings.kkt_reg;
  work.d_inv[110] = 1/work.d[110];
  work.v[111] = work.KKT[111];
  work.d[111] = work.v[111];
  if (work.d[111] < 0)
    work.d[111] = settings.kkt_reg;
  else
    work.d[111] += settings.kkt_reg;
  work.d_inv[111] = 1/work.d[111];
  work.v[112] = work.KKT[112];
  work.d[112] = work.v[112];
  if (work.d[112] < 0)
    work.d[112] = settings.kkt_reg;
  else
    work.d[112] += settings.kkt_reg;
  work.d_inv[112] = 1/work.d[112];
  work.v[113] = work.KKT[113];
  work.d[113] = work.v[113];
  if (work.d[113] < 0)
    work.d[113] = settings.kkt_reg;
  else
    work.d[113] += settings.kkt_reg;
  work.d_inv[113] = 1/work.d[113];
  work.v[114] = work.KKT[114];
  work.d[114] = work.v[114];
  if (work.d[114] < 0)
    work.d[114] = settings.kkt_reg;
  else
    work.d[114] += settings.kkt_reg;
  work.d_inv[114] = 1/work.d[114];
  work.v[115] = work.KKT[115];
  work.d[115] = work.v[115];
  if (work.d[115] < 0)
    work.d[115] = settings.kkt_reg;
  else
    work.d[115] += settings.kkt_reg;
  work.d_inv[115] = 1/work.d[115];
  work.v[116] = work.KKT[116];
  work.d[116] = work.v[116];
  if (work.d[116] < 0)
    work.d[116] = settings.kkt_reg;
  else
    work.d[116] += settings.kkt_reg;
  work.d_inv[116] = 1/work.d[116];
  work.v[117] = work.KKT[117];
  work.d[117] = work.v[117];
  if (work.d[117] < 0)
    work.d[117] = settings.kkt_reg;
  else
    work.d[117] += settings.kkt_reg;
  work.d_inv[117] = 1/work.d[117];
  work.v[118] = work.KKT[118];
  work.d[118] = work.v[118];
  if (work.d[118] < 0)
    work.d[118] = settings.kkt_reg;
  else
    work.d[118] += settings.kkt_reg;
  work.d_inv[118] = 1/work.d[118];
  work.v[119] = work.KKT[119];
  work.d[119] = work.v[119];
  if (work.d[119] < 0)
    work.d[119] = settings.kkt_reg;
  else
    work.d[119] += settings.kkt_reg;
  work.d_inv[119] = 1/work.d[119];
  work.v[120] = work.KKT[120];
  work.d[120] = work.v[120];
  if (work.d[120] < 0)
    work.d[120] = settings.kkt_reg;
  else
    work.d[120] += settings.kkt_reg;
  work.d_inv[120] = 1/work.d[120];
  work.v[121] = work.KKT[121];
  work.d[121] = work.v[121];
  if (work.d[121] < 0)
    work.d[121] = settings.kkt_reg;
  else
    work.d[121] += settings.kkt_reg;
  work.d_inv[121] = 1/work.d[121];
  work.v[122] = work.KKT[122];
  work.d[122] = work.v[122];
  if (work.d[122] < 0)
    work.d[122] = settings.kkt_reg;
  else
    work.d[122] += settings.kkt_reg;
  work.d_inv[122] = 1/work.d[122];
  work.v[123] = work.KKT[123];
  work.d[123] = work.v[123];
  if (work.d[123] < 0)
    work.d[123] = settings.kkt_reg;
  else
    work.d[123] += settings.kkt_reg;
  work.d_inv[123] = 1/work.d[123];
  work.v[124] = work.KKT[124];
  work.d[124] = work.v[124];
  if (work.d[124] < 0)
    work.d[124] = settings.kkt_reg;
  else
    work.d[124] += settings.kkt_reg;
  work.d_inv[124] = 1/work.d[124];
  work.v[125] = work.KKT[125];
  work.d[125] = work.v[125];
  if (work.d[125] < 0)
    work.d[125] = settings.kkt_reg;
  else
    work.d[125] += settings.kkt_reg;
  work.d_inv[125] = 1/work.d[125];
  work.v[126] = work.KKT[126];
  work.d[126] = work.v[126];
  if (work.d[126] < 0)
    work.d[126] = settings.kkt_reg;
  else
    work.d[126] += settings.kkt_reg;
  work.d_inv[126] = 1/work.d[126];
  work.v[127] = work.KKT[127];
  work.d[127] = work.v[127];
  if (work.d[127] < 0)
    work.d[127] = settings.kkt_reg;
  else
    work.d[127] += settings.kkt_reg;
  work.d_inv[127] = 1/work.d[127];
  work.v[128] = work.KKT[128];
  work.d[128] = work.v[128];
  if (work.d[128] < 0)
    work.d[128] = settings.kkt_reg;
  else
    work.d[128] += settings.kkt_reg;
  work.d_inv[128] = 1/work.d[128];
  work.v[129] = work.KKT[129];
  work.d[129] = work.v[129];
  if (work.d[129] < 0)
    work.d[129] = settings.kkt_reg;
  else
    work.d[129] += settings.kkt_reg;
  work.d_inv[129] = 1/work.d[129];
  work.v[130] = work.KKT[130];
  work.d[130] = work.v[130];
  if (work.d[130] < 0)
    work.d[130] = settings.kkt_reg;
  else
    work.d[130] += settings.kkt_reg;
  work.d_inv[130] = 1/work.d[130];
  work.v[131] = work.KKT[131];
  work.d[131] = work.v[131];
  if (work.d[131] < 0)
    work.d[131] = settings.kkt_reg;
  else
    work.d[131] += settings.kkt_reg;
  work.d_inv[131] = 1/work.d[131];
  work.v[132] = work.KKT[132];
  work.d[132] = work.v[132];
  if (work.d[132] < 0)
    work.d[132] = settings.kkt_reg;
  else
    work.d[132] += settings.kkt_reg;
  work.d_inv[132] = 1/work.d[132];
  work.v[133] = work.KKT[133];
  work.d[133] = work.v[133];
  if (work.d[133] < 0)
    work.d[133] = settings.kkt_reg;
  else
    work.d[133] += settings.kkt_reg;
  work.d_inv[133] = 1/work.d[133];
  work.v[134] = work.KKT[134];
  work.d[134] = work.v[134];
  if (work.d[134] < 0)
    work.d[134] = settings.kkt_reg;
  else
    work.d[134] += settings.kkt_reg;
  work.d_inv[134] = 1/work.d[134];
  work.v[135] = work.KKT[135];
  work.d[135] = work.v[135];
  if (work.d[135] < 0)
    work.d[135] = settings.kkt_reg;
  else
    work.d[135] += settings.kkt_reg;
  work.d_inv[135] = 1/work.d[135];
  work.v[136] = work.KKT[136];
  work.d[136] = work.v[136];
  if (work.d[136] < 0)
    work.d[136] = settings.kkt_reg;
  else
    work.d[136] += settings.kkt_reg;
  work.d_inv[136] = 1/work.d[136];
  work.v[137] = work.KKT[137];
  work.d[137] = work.v[137];
  if (work.d[137] < 0)
    work.d[137] = settings.kkt_reg;
  else
    work.d[137] += settings.kkt_reg;
  work.d_inv[137] = 1/work.d[137];
  work.v[138] = work.KKT[138];
  work.d[138] = work.v[138];
  if (work.d[138] < 0)
    work.d[138] = settings.kkt_reg;
  else
    work.d[138] += settings.kkt_reg;
  work.d_inv[138] = 1/work.d[138];
  work.v[139] = work.KKT[139];
  work.d[139] = work.v[139];
  if (work.d[139] < 0)
    work.d[139] = settings.kkt_reg;
  else
    work.d[139] += settings.kkt_reg;
  work.d_inv[139] = 1/work.d[139];
  work.v[140] = work.KKT[140];
  work.d[140] = work.v[140];
  if (work.d[140] < 0)
    work.d[140] = settings.kkt_reg;
  else
    work.d[140] += settings.kkt_reg;
  work.d_inv[140] = 1/work.d[140];
  work.v[141] = work.KKT[141];
  work.d[141] = work.v[141];
  if (work.d[141] < 0)
    work.d[141] = settings.kkt_reg;
  else
    work.d[141] += settings.kkt_reg;
  work.d_inv[141] = 1/work.d[141];
  work.v[142] = work.KKT[142];
  work.d[142] = work.v[142];
  if (work.d[142] < 0)
    work.d[142] = settings.kkt_reg;
  else
    work.d[142] += settings.kkt_reg;
  work.d_inv[142] = 1/work.d[142];
  work.v[143] = work.KKT[143];
  work.d[143] = work.v[143];
  if (work.d[143] < 0)
    work.d[143] = settings.kkt_reg;
  else
    work.d[143] += settings.kkt_reg;
  work.d_inv[143] = 1/work.d[143];
  work.v[144] = work.KKT[144];
  work.d[144] = work.v[144];
  if (work.d[144] < 0)
    work.d[144] = settings.kkt_reg;
  else
    work.d[144] += settings.kkt_reg;
  work.d_inv[144] = 1/work.d[144];
  work.v[145] = work.KKT[145];
  work.d[145] = work.v[145];
  if (work.d[145] < 0)
    work.d[145] = settings.kkt_reg;
  else
    work.d[145] += settings.kkt_reg;
  work.d_inv[145] = 1/work.d[145];
  work.v[146] = work.KKT[146];
  work.d[146] = work.v[146];
  if (work.d[146] < 0)
    work.d[146] = settings.kkt_reg;
  else
    work.d[146] += settings.kkt_reg;
  work.d_inv[146] = 1/work.d[146];
  work.v[147] = work.KKT[147];
  work.d[147] = work.v[147];
  if (work.d[147] < 0)
    work.d[147] = settings.kkt_reg;
  else
    work.d[147] += settings.kkt_reg;
  work.d_inv[147] = 1/work.d[147];
  work.v[148] = work.KKT[148];
  work.d[148] = work.v[148];
  if (work.d[148] < 0)
    work.d[148] = settings.kkt_reg;
  else
    work.d[148] += settings.kkt_reg;
  work.d_inv[148] = 1/work.d[148];
  work.v[149] = work.KKT[149];
  work.d[149] = work.v[149];
  if (work.d[149] < 0)
    work.d[149] = settings.kkt_reg;
  else
    work.d[149] += settings.kkt_reg;
  work.d_inv[149] = 1/work.d[149];
  work.v[150] = work.KKT[150];
  work.d[150] = work.v[150];
  if (work.d[150] < 0)
    work.d[150] = settings.kkt_reg;
  else
    work.d[150] += settings.kkt_reg;
  work.d_inv[150] = 1/work.d[150];
  work.v[151] = work.KKT[151];
  work.d[151] = work.v[151];
  if (work.d[151] < 0)
    work.d[151] = settings.kkt_reg;
  else
    work.d[151] += settings.kkt_reg;
  work.d_inv[151] = 1/work.d[151];
  work.v[152] = work.KKT[152];
  work.d[152] = work.v[152];
  if (work.d[152] < 0)
    work.d[152] = settings.kkt_reg;
  else
    work.d[152] += settings.kkt_reg;
  work.d_inv[152] = 1/work.d[152];
  work.v[153] = work.KKT[153];
  work.d[153] = work.v[153];
  if (work.d[153] < 0)
    work.d[153] = settings.kkt_reg;
  else
    work.d[153] += settings.kkt_reg;
  work.d_inv[153] = 1/work.d[153];
  work.v[154] = work.KKT[154];
  work.d[154] = work.v[154];
  if (work.d[154] < 0)
    work.d[154] = settings.kkt_reg;
  else
    work.d[154] += settings.kkt_reg;
  work.d_inv[154] = 1/work.d[154];
  work.v[155] = work.KKT[155];
  work.d[155] = work.v[155];
  if (work.d[155] < 0)
    work.d[155] = settings.kkt_reg;
  else
    work.d[155] += settings.kkt_reg;
  work.d_inv[155] = 1/work.d[155];
  work.v[156] = work.KKT[156];
  work.d[156] = work.v[156];
  if (work.d[156] < 0)
    work.d[156] = settings.kkt_reg;
  else
    work.d[156] += settings.kkt_reg;
  work.d_inv[156] = 1/work.d[156];
  work.v[157] = work.KKT[157];
  work.d[157] = work.v[157];
  if (work.d[157] < 0)
    work.d[157] = settings.kkt_reg;
  else
    work.d[157] += settings.kkt_reg;
  work.d_inv[157] = 1/work.d[157];
  work.v[158] = work.KKT[158];
  work.d[158] = work.v[158];
  if (work.d[158] < 0)
    work.d[158] = settings.kkt_reg;
  else
    work.d[158] += settings.kkt_reg;
  work.d_inv[158] = 1/work.d[158];
  work.v[159] = work.KKT[159];
  work.d[159] = work.v[159];
  if (work.d[159] < 0)
    work.d[159] = settings.kkt_reg;
  else
    work.d[159] += settings.kkt_reg;
  work.d_inv[159] = 1/work.d[159];
  work.v[160] = work.KKT[160];
  work.d[160] = work.v[160];
  if (work.d[160] < 0)
    work.d[160] = settings.kkt_reg;
  else
    work.d[160] += settings.kkt_reg;
  work.d_inv[160] = 1/work.d[160];
  work.v[161] = work.KKT[161];
  work.d[161] = work.v[161];
  if (work.d[161] < 0)
    work.d[161] = settings.kkt_reg;
  else
    work.d[161] += settings.kkt_reg;
  work.d_inv[161] = 1/work.d[161];
  work.v[162] = work.KKT[162];
  work.d[162] = work.v[162];
  if (work.d[162] < 0)
    work.d[162] = settings.kkt_reg;
  else
    work.d[162] += settings.kkt_reg;
  work.d_inv[162] = 1/work.d[162];
  work.v[163] = work.KKT[163];
  work.d[163] = work.v[163];
  if (work.d[163] < 0)
    work.d[163] = settings.kkt_reg;
  else
    work.d[163] += settings.kkt_reg;
  work.d_inv[163] = 1/work.d[163];
  work.v[164] = work.KKT[164];
  work.d[164] = work.v[164];
  if (work.d[164] < 0)
    work.d[164] = settings.kkt_reg;
  else
    work.d[164] += settings.kkt_reg;
  work.d_inv[164] = 1/work.d[164];
  work.v[165] = work.KKT[165];
  work.d[165] = work.v[165];
  if (work.d[165] < 0)
    work.d[165] = settings.kkt_reg;
  else
    work.d[165] += settings.kkt_reg;
  work.d_inv[165] = 1/work.d[165];
  work.v[166] = work.KKT[166];
  work.d[166] = work.v[166];
  if (work.d[166] < 0)
    work.d[166] = settings.kkt_reg;
  else
    work.d[166] += settings.kkt_reg;
  work.d_inv[166] = 1/work.d[166];
  work.v[167] = work.KKT[167];
  work.d[167] = work.v[167];
  if (work.d[167] < 0)
    work.d[167] = settings.kkt_reg;
  else
    work.d[167] += settings.kkt_reg;
  work.d_inv[167] = 1/work.d[167];
  work.v[168] = work.KKT[168];
  work.d[168] = work.v[168];
  if (work.d[168] < 0)
    work.d[168] = settings.kkt_reg;
  else
    work.d[168] += settings.kkt_reg;
  work.d_inv[168] = 1/work.d[168];
  work.v[169] = work.KKT[169];
  work.d[169] = work.v[169];
  if (work.d[169] < 0)
    work.d[169] = settings.kkt_reg;
  else
    work.d[169] += settings.kkt_reg;
  work.d_inv[169] = 1/work.d[169];
  work.v[170] = work.KKT[170];
  work.d[170] = work.v[170];
  if (work.d[170] < 0)
    work.d[170] = settings.kkt_reg;
  else
    work.d[170] += settings.kkt_reg;
  work.d_inv[170] = 1/work.d[170];
  work.v[171] = work.KKT[171];
  work.d[171] = work.v[171];
  if (work.d[171] < 0)
    work.d[171] = settings.kkt_reg;
  else
    work.d[171] += settings.kkt_reg;
  work.d_inv[171] = 1/work.d[171];
  work.v[172] = work.KKT[172];
  work.d[172] = work.v[172];
  if (work.d[172] < 0)
    work.d[172] = settings.kkt_reg;
  else
    work.d[172] += settings.kkt_reg;
  work.d_inv[172] = 1/work.d[172];
  work.v[173] = work.KKT[173];
  work.d[173] = work.v[173];
  if (work.d[173] < 0)
    work.d[173] = settings.kkt_reg;
  else
    work.d[173] += settings.kkt_reg;
  work.d_inv[173] = 1/work.d[173];
  work.v[174] = work.KKT[174];
  work.d[174] = work.v[174];
  if (work.d[174] < 0)
    work.d[174] = settings.kkt_reg;
  else
    work.d[174] += settings.kkt_reg;
  work.d_inv[174] = 1/work.d[174];
  work.v[175] = work.KKT[175];
  work.d[175] = work.v[175];
  if (work.d[175] < 0)
    work.d[175] = settings.kkt_reg;
  else
    work.d[175] += settings.kkt_reg;
  work.d_inv[175] = 1/work.d[175];
  work.v[176] = work.KKT[176];
  work.d[176] = work.v[176];
  if (work.d[176] < 0)
    work.d[176] = settings.kkt_reg;
  else
    work.d[176] += settings.kkt_reg;
  work.d_inv[176] = 1/work.d[176];
  work.v[177] = work.KKT[177];
  work.d[177] = work.v[177];
  if (work.d[177] < 0)
    work.d[177] = settings.kkt_reg;
  else
    work.d[177] += settings.kkt_reg;
  work.d_inv[177] = 1/work.d[177];
  work.v[178] = work.KKT[178];
  work.d[178] = work.v[178];
  if (work.d[178] < 0)
    work.d[178] = settings.kkt_reg;
  else
    work.d[178] += settings.kkt_reg;
  work.d_inv[178] = 1/work.d[178];
  work.v[179] = work.KKT[179];
  work.d[179] = work.v[179];
  if (work.d[179] < 0)
    work.d[179] = settings.kkt_reg;
  else
    work.d[179] += settings.kkt_reg;
  work.d_inv[179] = 1/work.d[179];
  work.v[180] = work.KKT[180];
  work.d[180] = work.v[180];
  if (work.d[180] < 0)
    work.d[180] = settings.kkt_reg;
  else
    work.d[180] += settings.kkt_reg;
  work.d_inv[180] = 1/work.d[180];
  work.v[181] = work.KKT[181];
  work.d[181] = work.v[181];
  if (work.d[181] < 0)
    work.d[181] = settings.kkt_reg;
  else
    work.d[181] += settings.kkt_reg;
  work.d_inv[181] = 1/work.d[181];
  work.v[182] = work.KKT[182];
  work.d[182] = work.v[182];
  if (work.d[182] < 0)
    work.d[182] = settings.kkt_reg;
  else
    work.d[182] += settings.kkt_reg;
  work.d_inv[182] = 1/work.d[182];
  work.v[183] = work.KKT[183];
  work.d[183] = work.v[183];
  if (work.d[183] < 0)
    work.d[183] = settings.kkt_reg;
  else
    work.d[183] += settings.kkt_reg;
  work.d_inv[183] = 1/work.d[183];
  work.v[184] = work.KKT[184];
  work.d[184] = work.v[184];
  if (work.d[184] < 0)
    work.d[184] = settings.kkt_reg;
  else
    work.d[184] += settings.kkt_reg;
  work.d_inv[184] = 1/work.d[184];
  work.v[185] = work.KKT[185];
  work.d[185] = work.v[185];
  if (work.d[185] < 0)
    work.d[185] = settings.kkt_reg;
  else
    work.d[185] += settings.kkt_reg;
  work.d_inv[185] = 1/work.d[185];
  work.v[186] = work.KKT[186];
  work.d[186] = work.v[186];
  if (work.d[186] < 0)
    work.d[186] = settings.kkt_reg;
  else
    work.d[186] += settings.kkt_reg;
  work.d_inv[186] = 1/work.d[186];
  work.v[187] = work.KKT[187];
  work.d[187] = work.v[187];
  if (work.d[187] < 0)
    work.d[187] = settings.kkt_reg;
  else
    work.d[187] += settings.kkt_reg;
  work.d_inv[187] = 1/work.d[187];
  work.v[188] = work.KKT[188];
  work.d[188] = work.v[188];
  if (work.d[188] < 0)
    work.d[188] = settings.kkt_reg;
  else
    work.d[188] += settings.kkt_reg;
  work.d_inv[188] = 1/work.d[188];
  work.v[189] = work.KKT[189];
  work.d[189] = work.v[189];
  if (work.d[189] < 0)
    work.d[189] = settings.kkt_reg;
  else
    work.d[189] += settings.kkt_reg;
  work.d_inv[189] = 1/work.d[189];
  work.v[190] = work.KKT[190];
  work.d[190] = work.v[190];
  if (work.d[190] < 0)
    work.d[190] = settings.kkt_reg;
  else
    work.d[190] += settings.kkt_reg;
  work.d_inv[190] = 1/work.d[190];
  work.v[191] = work.KKT[191];
  work.d[191] = work.v[191];
  if (work.d[191] < 0)
    work.d[191] = settings.kkt_reg;
  else
    work.d[191] += settings.kkt_reg;
  work.d_inv[191] = 1/work.d[191];
  work.v[192] = work.KKT[192];
  work.d[192] = work.v[192];
  if (work.d[192] < 0)
    work.d[192] = settings.kkt_reg;
  else
    work.d[192] += settings.kkt_reg;
  work.d_inv[192] = 1/work.d[192];
  work.v[193] = work.KKT[193];
  work.d[193] = work.v[193];
  if (work.d[193] < 0)
    work.d[193] = settings.kkt_reg;
  else
    work.d[193] += settings.kkt_reg;
  work.d_inv[193] = 1/work.d[193];
  work.v[194] = work.KKT[194];
  work.d[194] = work.v[194];
  if (work.d[194] < 0)
    work.d[194] = settings.kkt_reg;
  else
    work.d[194] += settings.kkt_reg;
  work.d_inv[194] = 1/work.d[194];
  work.v[195] = work.KKT[195];
  work.d[195] = work.v[195];
  if (work.d[195] < 0)
    work.d[195] = settings.kkt_reg;
  else
    work.d[195] += settings.kkt_reg;
  work.d_inv[195] = 1/work.d[195];
  work.v[196] = work.KKT[196];
  work.d[196] = work.v[196];
  if (work.d[196] < 0)
    work.d[196] = settings.kkt_reg;
  else
    work.d[196] += settings.kkt_reg;
  work.d_inv[196] = 1/work.d[196];
  work.v[197] = work.KKT[197];
  work.d[197] = work.v[197];
  if (work.d[197] < 0)
    work.d[197] = settings.kkt_reg;
  else
    work.d[197] += settings.kkt_reg;
  work.d_inv[197] = 1/work.d[197];
  work.v[198] = work.KKT[198];
  work.d[198] = work.v[198];
  if (work.d[198] < 0)
    work.d[198] = settings.kkt_reg;
  else
    work.d[198] += settings.kkt_reg;
  work.d_inv[198] = 1/work.d[198];
  work.v[199] = work.KKT[199];
  work.d[199] = work.v[199];
  if (work.d[199] < 0)
    work.d[199] = settings.kkt_reg;
  else
    work.d[199] += settings.kkt_reg;
  work.d_inv[199] = 1/work.d[199];
  work.v[200] = work.KKT[200];
  work.d[200] = work.v[200];
  if (work.d[200] < 0)
    work.d[200] = settings.kkt_reg;
  else
    work.d[200] += settings.kkt_reg;
  work.d_inv[200] = 1/work.d[200];
  work.v[201] = work.KKT[201];
  work.d[201] = work.v[201];
  if (work.d[201] < 0)
    work.d[201] = settings.kkt_reg;
  else
    work.d[201] += settings.kkt_reg;
  work.d_inv[201] = 1/work.d[201];
  work.v[202] = work.KKT[202];
  work.d[202] = work.v[202];
  if (work.d[202] < 0)
    work.d[202] = settings.kkt_reg;
  else
    work.d[202] += settings.kkt_reg;
  work.d_inv[202] = 1/work.d[202];
  work.v[203] = work.KKT[203];
  work.d[203] = work.v[203];
  if (work.d[203] < 0)
    work.d[203] = settings.kkt_reg;
  else
    work.d[203] += settings.kkt_reg;
  work.d_inv[203] = 1/work.d[203];
  work.v[204] = work.KKT[204];
  work.d[204] = work.v[204];
  if (work.d[204] < 0)
    work.d[204] = settings.kkt_reg;
  else
    work.d[204] += settings.kkt_reg;
  work.d_inv[204] = 1/work.d[204];
  work.v[205] = work.KKT[205];
  work.d[205] = work.v[205];
  if (work.d[205] < 0)
    work.d[205] = settings.kkt_reg;
  else
    work.d[205] += settings.kkt_reg;
  work.d_inv[205] = 1/work.d[205];
  work.v[206] = work.KKT[206];
  work.d[206] = work.v[206];
  if (work.d[206] < 0)
    work.d[206] = settings.kkt_reg;
  else
    work.d[206] += settings.kkt_reg;
  work.d_inv[206] = 1/work.d[206];
  work.v[207] = work.KKT[207];
  work.d[207] = work.v[207];
  if (work.d[207] < 0)
    work.d[207] = settings.kkt_reg;
  else
    work.d[207] += settings.kkt_reg;
  work.d_inv[207] = 1/work.d[207];
  work.v[208] = work.KKT[208];
  work.d[208] = work.v[208];
  if (work.d[208] < 0)
    work.d[208] = settings.kkt_reg;
  else
    work.d[208] += settings.kkt_reg;
  work.d_inv[208] = 1/work.d[208];
  work.v[209] = work.KKT[209];
  work.d[209] = work.v[209];
  if (work.d[209] < 0)
    work.d[209] = settings.kkt_reg;
  else
    work.d[209] += settings.kkt_reg;
  work.d_inv[209] = 1/work.d[209];
  work.v[210] = work.KKT[210];
  work.d[210] = work.v[210];
  if (work.d[210] < 0)
    work.d[210] = settings.kkt_reg;
  else
    work.d[210] += settings.kkt_reg;
  work.d_inv[210] = 1/work.d[210];
  work.v[211] = work.KKT[211];
  work.d[211] = work.v[211];
  if (work.d[211] < 0)
    work.d[211] = settings.kkt_reg;
  else
    work.d[211] += settings.kkt_reg;
  work.d_inv[211] = 1/work.d[211];
  work.v[212] = work.KKT[212];
  work.d[212] = work.v[212];
  if (work.d[212] < 0)
    work.d[212] = settings.kkt_reg;
  else
    work.d[212] += settings.kkt_reg;
  work.d_inv[212] = 1/work.d[212];
  work.v[213] = work.KKT[213];
  work.d[213] = work.v[213];
  if (work.d[213] < 0)
    work.d[213] = settings.kkt_reg;
  else
    work.d[213] += settings.kkt_reg;
  work.d_inv[213] = 1/work.d[213];
  work.v[214] = work.KKT[214];
  work.d[214] = work.v[214];
  if (work.d[214] < 0)
    work.d[214] = settings.kkt_reg;
  else
    work.d[214] += settings.kkt_reg;
  work.d_inv[214] = 1/work.d[214];
  work.v[215] = work.KKT[215];
  work.d[215] = work.v[215];
  if (work.d[215] < 0)
    work.d[215] = settings.kkt_reg;
  else
    work.d[215] += settings.kkt_reg;
  work.d_inv[215] = 1/work.d[215];
  work.v[216] = work.KKT[216];
  work.d[216] = work.v[216];
  if (work.d[216] < 0)
    work.d[216] = settings.kkt_reg;
  else
    work.d[216] += settings.kkt_reg;
  work.d_inv[216] = 1/work.d[216];
  work.v[217] = work.KKT[217];
  work.d[217] = work.v[217];
  if (work.d[217] < 0)
    work.d[217] = settings.kkt_reg;
  else
    work.d[217] += settings.kkt_reg;
  work.d_inv[217] = 1/work.d[217];
  work.v[218] = work.KKT[218];
  work.d[218] = work.v[218];
  if (work.d[218] < 0)
    work.d[218] = settings.kkt_reg;
  else
    work.d[218] += settings.kkt_reg;
  work.d_inv[218] = 1/work.d[218];
  work.v[219] = work.KKT[219];
  work.d[219] = work.v[219];
  if (work.d[219] < 0)
    work.d[219] = settings.kkt_reg;
  else
    work.d[219] += settings.kkt_reg;
  work.d_inv[219] = 1/work.d[219];
  work.v[220] = work.KKT[220];
  work.d[220] = work.v[220];
  if (work.d[220] < 0)
    work.d[220] = settings.kkt_reg;
  else
    work.d[220] += settings.kkt_reg;
  work.d_inv[220] = 1/work.d[220];
  work.v[221] = work.KKT[221];
  work.d[221] = work.v[221];
  if (work.d[221] < 0)
    work.d[221] = settings.kkt_reg;
  else
    work.d[221] += settings.kkt_reg;
  work.d_inv[221] = 1/work.d[221];
  work.v[222] = work.KKT[222];
  work.d[222] = work.v[222];
  if (work.d[222] < 0)
    work.d[222] = settings.kkt_reg;
  else
    work.d[222] += settings.kkt_reg;
  work.d_inv[222] = 1/work.d[222];
  work.v[223] = work.KKT[223];
  work.d[223] = work.v[223];
  if (work.d[223] < 0)
    work.d[223] = settings.kkt_reg;
  else
    work.d[223] += settings.kkt_reg;
  work.d_inv[223] = 1/work.d[223];
  work.v[224] = work.KKT[224];
  work.d[224] = work.v[224];
  if (work.d[224] < 0)
    work.d[224] = settings.kkt_reg;
  else
    work.d[224] += settings.kkt_reg;
  work.d_inv[224] = 1/work.d[224];
  work.v[225] = work.KKT[225];
  work.d[225] = work.v[225];
  if (work.d[225] < 0)
    work.d[225] = settings.kkt_reg;
  else
    work.d[225] += settings.kkt_reg;
  work.d_inv[225] = 1/work.d[225];
  work.v[226] = work.KKT[226];
  work.d[226] = work.v[226];
  if (work.d[226] < 0)
    work.d[226] = settings.kkt_reg;
  else
    work.d[226] += settings.kkt_reg;
  work.d_inv[226] = 1/work.d[226];
  work.v[227] = work.KKT[227];
  work.d[227] = work.v[227];
  if (work.d[227] < 0)
    work.d[227] = settings.kkt_reg;
  else
    work.d[227] += settings.kkt_reg;
  work.d_inv[227] = 1/work.d[227];
  work.v[228] = work.KKT[228];
  work.d[228] = work.v[228];
  if (work.d[228] < 0)
    work.d[228] = settings.kkt_reg;
  else
    work.d[228] += settings.kkt_reg;
  work.d_inv[228] = 1/work.d[228];
  work.v[229] = work.KKT[229];
  work.d[229] = work.v[229];
  if (work.d[229] < 0)
    work.d[229] = settings.kkt_reg;
  else
    work.d[229] += settings.kkt_reg;
  work.d_inv[229] = 1/work.d[229];
  work.v[230] = work.KKT[230];
  work.d[230] = work.v[230];
  if (work.d[230] < 0)
    work.d[230] = settings.kkt_reg;
  else
    work.d[230] += settings.kkt_reg;
  work.d_inv[230] = 1/work.d[230];
  work.v[231] = work.KKT[231];
  work.d[231] = work.v[231];
  if (work.d[231] < 0)
    work.d[231] = settings.kkt_reg;
  else
    work.d[231] += settings.kkt_reg;
  work.d_inv[231] = 1/work.d[231];
  work.v[232] = work.KKT[232];
  work.d[232] = work.v[232];
  if (work.d[232] < 0)
    work.d[232] = settings.kkt_reg;
  else
    work.d[232] += settings.kkt_reg;
  work.d_inv[232] = 1/work.d[232];
  work.v[233] = work.KKT[233];
  work.d[233] = work.v[233];
  if (work.d[233] < 0)
    work.d[233] = settings.kkt_reg;
  else
    work.d[233] += settings.kkt_reg;
  work.d_inv[233] = 1/work.d[233];
  work.v[234] = work.KKT[234];
  work.d[234] = work.v[234];
  if (work.d[234] < 0)
    work.d[234] = settings.kkt_reg;
  else
    work.d[234] += settings.kkt_reg;
  work.d_inv[234] = 1/work.d[234];
  work.v[235] = work.KKT[235];
  work.d[235] = work.v[235];
  if (work.d[235] < 0)
    work.d[235] = settings.kkt_reg;
  else
    work.d[235] += settings.kkt_reg;
  work.d_inv[235] = 1/work.d[235];
  work.v[236] = work.KKT[236];
  work.d[236] = work.v[236];
  if (work.d[236] < 0)
    work.d[236] = settings.kkt_reg;
  else
    work.d[236] += settings.kkt_reg;
  work.d_inv[236] = 1/work.d[236];
  work.v[237] = work.KKT[237];
  work.d[237] = work.v[237];
  if (work.d[237] < 0)
    work.d[237] = settings.kkt_reg;
  else
    work.d[237] += settings.kkt_reg;
  work.d_inv[237] = 1/work.d[237];
  work.v[238] = work.KKT[238];
  work.d[238] = work.v[238];
  if (work.d[238] < 0)
    work.d[238] = settings.kkt_reg;
  else
    work.d[238] += settings.kkt_reg;
  work.d_inv[238] = 1/work.d[238];
  work.v[239] = work.KKT[239];
  work.d[239] = work.v[239];
  if (work.d[239] < 0)
    work.d[239] = settings.kkt_reg;
  else
    work.d[239] += settings.kkt_reg;
  work.d_inv[239] = 1/work.d[239];
  work.v[240] = work.KKT[240];
  work.d[240] = work.v[240];
  if (work.d[240] < 0)
    work.d[240] = settings.kkt_reg;
  else
    work.d[240] += settings.kkt_reg;
  work.d_inv[240] = 1/work.d[240];
  work.v[241] = work.KKT[241];
  work.d[241] = work.v[241];
  if (work.d[241] < 0)
    work.d[241] = settings.kkt_reg;
  else
    work.d[241] += settings.kkt_reg;
  work.d_inv[241] = 1/work.d[241];
  work.v[242] = work.KKT[242];
  work.d[242] = work.v[242];
  if (work.d[242] < 0)
    work.d[242] = settings.kkt_reg;
  else
    work.d[242] += settings.kkt_reg;
  work.d_inv[242] = 1/work.d[242];
  work.v[243] = work.KKT[243];
  work.d[243] = work.v[243];
  if (work.d[243] < 0)
    work.d[243] = settings.kkt_reg;
  else
    work.d[243] += settings.kkt_reg;
  work.d_inv[243] = 1/work.d[243];
  work.v[244] = work.KKT[244];
  work.d[244] = work.v[244];
  if (work.d[244] < 0)
    work.d[244] = settings.kkt_reg;
  else
    work.d[244] += settings.kkt_reg;
  work.d_inv[244] = 1/work.d[244];
  work.v[245] = work.KKT[245];
  work.d[245] = work.v[245];
  if (work.d[245] < 0)
    work.d[245] = settings.kkt_reg;
  else
    work.d[245] += settings.kkt_reg;
  work.d_inv[245] = 1/work.d[245];
  work.v[246] = work.KKT[246];
  work.d[246] = work.v[246];
  if (work.d[246] < 0)
    work.d[246] = settings.kkt_reg;
  else
    work.d[246] += settings.kkt_reg;
  work.d_inv[246] = 1/work.d[246];
  work.v[247] = work.KKT[247];
  work.d[247] = work.v[247];
  if (work.d[247] < 0)
    work.d[247] = settings.kkt_reg;
  else
    work.d[247] += settings.kkt_reg;
  work.d_inv[247] = 1/work.d[247];
  work.v[248] = work.KKT[248];
  work.d[248] = work.v[248];
  if (work.d[248] < 0)
    work.d[248] = settings.kkt_reg;
  else
    work.d[248] += settings.kkt_reg;
  work.d_inv[248] = 1/work.d[248];
  work.v[249] = work.KKT[249];
  work.d[249] = work.v[249];
  if (work.d[249] < 0)
    work.d[249] = settings.kkt_reg;
  else
    work.d[249] += settings.kkt_reg;
  work.d_inv[249] = 1/work.d[249];
  work.v[250] = work.KKT[250];
  work.d[250] = work.v[250];
  if (work.d[250] < 0)
    work.d[250] = settings.kkt_reg;
  else
    work.d[250] += settings.kkt_reg;
  work.d_inv[250] = 1/work.d[250];
  work.v[251] = work.KKT[251];
  work.d[251] = work.v[251];
  if (work.d[251] < 0)
    work.d[251] = settings.kkt_reg;
  else
    work.d[251] += settings.kkt_reg;
  work.d_inv[251] = 1/work.d[251];
  work.v[252] = work.KKT[252];
  work.d[252] = work.v[252];
  if (work.d[252] < 0)
    work.d[252] = settings.kkt_reg;
  else
    work.d[252] += settings.kkt_reg;
  work.d_inv[252] = 1/work.d[252];
  work.v[253] = work.KKT[253];
  work.d[253] = work.v[253];
  if (work.d[253] < 0)
    work.d[253] = settings.kkt_reg;
  else
    work.d[253] += settings.kkt_reg;
  work.d_inv[253] = 1/work.d[253];
  work.v[254] = work.KKT[254];
  work.d[254] = work.v[254];
  if (work.d[254] < 0)
    work.d[254] = settings.kkt_reg;
  else
    work.d[254] += settings.kkt_reg;
  work.d_inv[254] = 1/work.d[254];
  work.v[255] = work.KKT[255];
  work.d[255] = work.v[255];
  if (work.d[255] < 0)
    work.d[255] = settings.kkt_reg;
  else
    work.d[255] += settings.kkt_reg;
  work.d_inv[255] = 1/work.d[255];
  work.v[256] = work.KKT[256];
  work.d[256] = work.v[256];
  if (work.d[256] < 0)
    work.d[256] = settings.kkt_reg;
  else
    work.d[256] += settings.kkt_reg;
  work.d_inv[256] = 1/work.d[256];
  work.v[257] = work.KKT[257];
  work.d[257] = work.v[257];
  if (work.d[257] < 0)
    work.d[257] = settings.kkt_reg;
  else
    work.d[257] += settings.kkt_reg;
  work.d_inv[257] = 1/work.d[257];
  work.v[258] = work.KKT[258];
  work.d[258] = work.v[258];
  if (work.d[258] < 0)
    work.d[258] = settings.kkt_reg;
  else
    work.d[258] += settings.kkt_reg;
  work.d_inv[258] = 1/work.d[258];
  work.v[259] = work.KKT[259];
  work.d[259] = work.v[259];
  if (work.d[259] < 0)
    work.d[259] = settings.kkt_reg;
  else
    work.d[259] += settings.kkt_reg;
  work.d_inv[259] = 1/work.d[259];
  work.v[260] = work.KKT[260];
  work.d[260] = work.v[260];
  if (work.d[260] < 0)
    work.d[260] = settings.kkt_reg;
  else
    work.d[260] += settings.kkt_reg;
  work.d_inv[260] = 1/work.d[260];
  work.v[261] = work.KKT[261];
  work.d[261] = work.v[261];
  if (work.d[261] < 0)
    work.d[261] = settings.kkt_reg;
  else
    work.d[261] += settings.kkt_reg;
  work.d_inv[261] = 1/work.d[261];
  work.v[262] = work.KKT[262];
  work.d[262] = work.v[262];
  if (work.d[262] < 0)
    work.d[262] = settings.kkt_reg;
  else
    work.d[262] += settings.kkt_reg;
  work.d_inv[262] = 1/work.d[262];
  work.v[263] = work.KKT[263];
  work.d[263] = work.v[263];
  if (work.d[263] < 0)
    work.d[263] = settings.kkt_reg;
  else
    work.d[263] += settings.kkt_reg;
  work.d_inv[263] = 1/work.d[263];
  work.v[264] = work.KKT[264];
  work.d[264] = work.v[264];
  if (work.d[264] < 0)
    work.d[264] = settings.kkt_reg;
  else
    work.d[264] += settings.kkt_reg;
  work.d_inv[264] = 1/work.d[264];
  work.v[265] = work.KKT[265];
  work.d[265] = work.v[265];
  if (work.d[265] < 0)
    work.d[265] = settings.kkt_reg;
  else
    work.d[265] += settings.kkt_reg;
  work.d_inv[265] = 1/work.d[265];
  work.v[266] = work.KKT[266];
  work.d[266] = work.v[266];
  if (work.d[266] < 0)
    work.d[266] = settings.kkt_reg;
  else
    work.d[266] += settings.kkt_reg;
  work.d_inv[266] = 1/work.d[266];
  work.v[267] = work.KKT[267];
  work.d[267] = work.v[267];
  if (work.d[267] < 0)
    work.d[267] = settings.kkt_reg;
  else
    work.d[267] += settings.kkt_reg;
  work.d_inv[267] = 1/work.d[267];
  work.v[268] = work.KKT[268];
  work.d[268] = work.v[268];
  if (work.d[268] < 0)
    work.d[268] = settings.kkt_reg;
  else
    work.d[268] += settings.kkt_reg;
  work.d_inv[268] = 1/work.d[268];
  work.v[269] = work.KKT[269];
  work.d[269] = work.v[269];
  if (work.d[269] < 0)
    work.d[269] = settings.kkt_reg;
  else
    work.d[269] += settings.kkt_reg;
  work.d_inv[269] = 1/work.d[269];
  work.v[270] = work.KKT[270];
  work.d[270] = work.v[270];
  if (work.d[270] < 0)
    work.d[270] = settings.kkt_reg;
  else
    work.d[270] += settings.kkt_reg;
  work.d_inv[270] = 1/work.d[270];
  work.v[271] = work.KKT[271];
  work.d[271] = work.v[271];
  if (work.d[271] < 0)
    work.d[271] = settings.kkt_reg;
  else
    work.d[271] += settings.kkt_reg;
  work.d_inv[271] = 1/work.d[271];
  work.v[272] = work.KKT[272];
  work.d[272] = work.v[272];
  if (work.d[272] < 0)
    work.d[272] = settings.kkt_reg;
  else
    work.d[272] += settings.kkt_reg;
  work.d_inv[272] = 1/work.d[272];
  work.v[273] = work.KKT[273];
  work.d[273] = work.v[273];
  if (work.d[273] < 0)
    work.d[273] = settings.kkt_reg;
  else
    work.d[273] += settings.kkt_reg;
  work.d_inv[273] = 1/work.d[273];
  work.v[274] = work.KKT[274];
  work.d[274] = work.v[274];
  if (work.d[274] < 0)
    work.d[274] = settings.kkt_reg;
  else
    work.d[274] += settings.kkt_reg;
  work.d_inv[274] = 1/work.d[274];
  work.v[275] = work.KKT[275];
  work.d[275] = work.v[275];
  if (work.d[275] < 0)
    work.d[275] = settings.kkt_reg;
  else
    work.d[275] += settings.kkt_reg;
  work.d_inv[275] = 1/work.d[275];
  work.v[276] = work.KKT[276];
  work.d[276] = work.v[276];
  if (work.d[276] < 0)
    work.d[276] = settings.kkt_reg;
  else
    work.d[276] += settings.kkt_reg;
  work.d_inv[276] = 1/work.d[276];
  work.v[277] = work.KKT[277];
  work.d[277] = work.v[277];
  if (work.d[277] < 0)
    work.d[277] = settings.kkt_reg;
  else
    work.d[277] += settings.kkt_reg;
  work.d_inv[277] = 1/work.d[277];
  work.v[278] = work.KKT[278];
  work.d[278] = work.v[278];
  if (work.d[278] < 0)
    work.d[278] = settings.kkt_reg;
  else
    work.d[278] += settings.kkt_reg;
  work.d_inv[278] = 1/work.d[278];
  work.v[279] = work.KKT[279];
  work.d[279] = work.v[279];
  if (work.d[279] < 0)
    work.d[279] = settings.kkt_reg;
  else
    work.d[279] += settings.kkt_reg;
  work.d_inv[279] = 1/work.d[279];
  work.v[280] = work.KKT[280];
  work.d[280] = work.v[280];
  if (work.d[280] < 0)
    work.d[280] = settings.kkt_reg;
  else
    work.d[280] += settings.kkt_reg;
  work.d_inv[280] = 1/work.d[280];
  work.v[281] = work.KKT[281];
  work.d[281] = work.v[281];
  if (work.d[281] < 0)
    work.d[281] = settings.kkt_reg;
  else
    work.d[281] += settings.kkt_reg;
  work.d_inv[281] = 1/work.d[281];
  work.v[282] = work.KKT[282];
  work.d[282] = work.v[282];
  if (work.d[282] < 0)
    work.d[282] = settings.kkt_reg;
  else
    work.d[282] += settings.kkt_reg;
  work.d_inv[282] = 1/work.d[282];
  work.v[283] = work.KKT[283];
  work.d[283] = work.v[283];
  if (work.d[283] < 0)
    work.d[283] = settings.kkt_reg;
  else
    work.d[283] += settings.kkt_reg;
  work.d_inv[283] = 1/work.d[283];
  work.v[284] = work.KKT[284];
  work.d[284] = work.v[284];
  if (work.d[284] < 0)
    work.d[284] = settings.kkt_reg;
  else
    work.d[284] += settings.kkt_reg;
  work.d_inv[284] = 1/work.d[284];
  work.v[285] = work.KKT[285];
  work.d[285] = work.v[285];
  if (work.d[285] < 0)
    work.d[285] = settings.kkt_reg;
  else
    work.d[285] += settings.kkt_reg;
  work.d_inv[285] = 1/work.d[285];
  work.v[286] = work.KKT[286];
  work.d[286] = work.v[286];
  if (work.d[286] < 0)
    work.d[286] = settings.kkt_reg;
  else
    work.d[286] += settings.kkt_reg;
  work.d_inv[286] = 1/work.d[286];
  work.v[287] = work.KKT[287];
  work.d[287] = work.v[287];
  if (work.d[287] < 0)
    work.d[287] = settings.kkt_reg;
  else
    work.d[287] += settings.kkt_reg;
  work.d_inv[287] = 1/work.d[287];
  work.v[288] = work.KKT[288];
  work.d[288] = work.v[288];
  if (work.d[288] < 0)
    work.d[288] = settings.kkt_reg;
  else
    work.d[288] += settings.kkt_reg;
  work.d_inv[288] = 1/work.d[288];
  work.v[289] = work.KKT[289];
  work.d[289] = work.v[289];
  if (work.d[289] < 0)
    work.d[289] = settings.kkt_reg;
  else
    work.d[289] += settings.kkt_reg;
  work.d_inv[289] = 1/work.d[289];
  work.v[290] = work.KKT[290];
  work.d[290] = work.v[290];
  if (work.d[290] < 0)
    work.d[290] = settings.kkt_reg;
  else
    work.d[290] += settings.kkt_reg;
  work.d_inv[290] = 1/work.d[290];
  work.v[291] = work.KKT[291];
  work.d[291] = work.v[291];
  if (work.d[291] < 0)
    work.d[291] = settings.kkt_reg;
  else
    work.d[291] += settings.kkt_reg;
  work.d_inv[291] = 1/work.d[291];
  work.v[292] = work.KKT[292];
  work.d[292] = work.v[292];
  if (work.d[292] < 0)
    work.d[292] = settings.kkt_reg;
  else
    work.d[292] += settings.kkt_reg;
  work.d_inv[292] = 1/work.d[292];
  work.v[293] = work.KKT[293];
  work.d[293] = work.v[293];
  if (work.d[293] < 0)
    work.d[293] = settings.kkt_reg;
  else
    work.d[293] += settings.kkt_reg;
  work.d_inv[293] = 1/work.d[293];
  work.v[294] = work.KKT[294];
  work.d[294] = work.v[294];
  if (work.d[294] < 0)
    work.d[294] = settings.kkt_reg;
  else
    work.d[294] += settings.kkt_reg;
  work.d_inv[294] = 1/work.d[294];
  work.v[295] = work.KKT[295];
  work.d[295] = work.v[295];
  if (work.d[295] < 0)
    work.d[295] = settings.kkt_reg;
  else
    work.d[295] += settings.kkt_reg;
  work.d_inv[295] = 1/work.d[295];
  work.v[296] = work.KKT[296];
  work.d[296] = work.v[296];
  if (work.d[296] < 0)
    work.d[296] = settings.kkt_reg;
  else
    work.d[296] += settings.kkt_reg;
  work.d_inv[296] = 1/work.d[296];
  work.v[297] = work.KKT[297];
  work.d[297] = work.v[297];
  if (work.d[297] < 0)
    work.d[297] = settings.kkt_reg;
  else
    work.d[297] += settings.kkt_reg;
  work.d_inv[297] = 1/work.d[297];
  work.v[298] = work.KKT[298];
  work.d[298] = work.v[298];
  if (work.d[298] < 0)
    work.d[298] = settings.kkt_reg;
  else
    work.d[298] += settings.kkt_reg;
  work.d_inv[298] = 1/work.d[298];
  work.v[299] = work.KKT[299];
  work.d[299] = work.v[299];
  if (work.d[299] < 0)
    work.d[299] = settings.kkt_reg;
  else
    work.d[299] += settings.kkt_reg;
  work.d_inv[299] = 1/work.d[299];
  work.v[300] = work.KKT[300];
  work.d[300] = work.v[300];
  if (work.d[300] < 0)
    work.d[300] = settings.kkt_reg;
  else
    work.d[300] += settings.kkt_reg;
  work.d_inv[300] = 1/work.d[300];
  work.v[301] = work.KKT[301];
  work.d[301] = work.v[301];
  if (work.d[301] < 0)
    work.d[301] = settings.kkt_reg;
  else
    work.d[301] += settings.kkt_reg;
  work.d_inv[301] = 1/work.d[301];
  work.v[302] = work.KKT[302];
  work.d[302] = work.v[302];
  if (work.d[302] < 0)
    work.d[302] = settings.kkt_reg;
  else
    work.d[302] += settings.kkt_reg;
  work.d_inv[302] = 1/work.d[302];
  work.v[303] = work.KKT[303];
  work.d[303] = work.v[303];
  if (work.d[303] < 0)
    work.d[303] = settings.kkt_reg;
  else
    work.d[303] += settings.kkt_reg;
  work.d_inv[303] = 1/work.d[303];
  work.v[304] = work.KKT[304];
  work.d[304] = work.v[304];
  if (work.d[304] < 0)
    work.d[304] = settings.kkt_reg;
  else
    work.d[304] += settings.kkt_reg;
  work.d_inv[304] = 1/work.d[304];
  work.v[305] = work.KKT[305];
  work.d[305] = work.v[305];
  if (work.d[305] < 0)
    work.d[305] = settings.kkt_reg;
  else
    work.d[305] += settings.kkt_reg;
  work.d_inv[305] = 1/work.d[305];
  work.v[306] = work.KKT[306];
  work.d[306] = work.v[306];
  if (work.d[306] < 0)
    work.d[306] = settings.kkt_reg;
  else
    work.d[306] += settings.kkt_reg;
  work.d_inv[306] = 1/work.d[306];
  work.v[307] = work.KKT[307];
  work.d[307] = work.v[307];
  if (work.d[307] < 0)
    work.d[307] = settings.kkt_reg;
  else
    work.d[307] += settings.kkt_reg;
  work.d_inv[307] = 1/work.d[307];
  work.v[308] = work.KKT[308];
  work.d[308] = work.v[308];
  if (work.d[308] < 0)
    work.d[308] = settings.kkt_reg;
  else
    work.d[308] += settings.kkt_reg;
  work.d_inv[308] = 1/work.d[308];
  work.v[309] = work.KKT[309];
  work.d[309] = work.v[309];
  if (work.d[309] < 0)
    work.d[309] = settings.kkt_reg;
  else
    work.d[309] += settings.kkt_reg;
  work.d_inv[309] = 1/work.d[309];
  work.v[310] = work.KKT[310];
  work.d[310] = work.v[310];
  if (work.d[310] < 0)
    work.d[310] = settings.kkt_reg;
  else
    work.d[310] += settings.kkt_reg;
  work.d_inv[310] = 1/work.d[310];
  work.v[311] = work.KKT[311];
  work.d[311] = work.v[311];
  if (work.d[311] < 0)
    work.d[311] = settings.kkt_reg;
  else
    work.d[311] += settings.kkt_reg;
  work.d_inv[311] = 1/work.d[311];
  work.v[312] = work.KKT[312];
  work.d[312] = work.v[312];
  if (work.d[312] < 0)
    work.d[312] = settings.kkt_reg;
  else
    work.d[312] += settings.kkt_reg;
  work.d_inv[312] = 1/work.d[312];
  work.v[313] = work.KKT[313];
  work.d[313] = work.v[313];
  if (work.d[313] < 0)
    work.d[313] = settings.kkt_reg;
  else
    work.d[313] += settings.kkt_reg;
  work.d_inv[313] = 1/work.d[313];
  work.v[314] = work.KKT[314];
  work.d[314] = work.v[314];
  if (work.d[314] < 0)
    work.d[314] = settings.kkt_reg;
  else
    work.d[314] += settings.kkt_reg;
  work.d_inv[314] = 1/work.d[314];
  work.v[315] = work.KKT[315];
  work.d[315] = work.v[315];
  if (work.d[315] < 0)
    work.d[315] = settings.kkt_reg;
  else
    work.d[315] += settings.kkt_reg;
  work.d_inv[315] = 1/work.d[315];
  work.v[316] = work.KKT[316];
  work.d[316] = work.v[316];
  if (work.d[316] < 0)
    work.d[316] = settings.kkt_reg;
  else
    work.d[316] += settings.kkt_reg;
  work.d_inv[316] = 1/work.d[316];
  work.v[317] = work.KKT[317];
  work.d[317] = work.v[317];
  if (work.d[317] < 0)
    work.d[317] = settings.kkt_reg;
  else
    work.d[317] += settings.kkt_reg;
  work.d_inv[317] = 1/work.d[317];
  work.v[318] = work.KKT[318];
  work.d[318] = work.v[318];
  if (work.d[318] < 0)
    work.d[318] = settings.kkt_reg;
  else
    work.d[318] += settings.kkt_reg;
  work.d_inv[318] = 1/work.d[318];
  work.v[319] = work.KKT[319];
  work.d[319] = work.v[319];
  if (work.d[319] < 0)
    work.d[319] = settings.kkt_reg;
  else
    work.d[319] += settings.kkt_reg;
  work.d_inv[319] = 1/work.d[319];
  work.v[320] = work.KKT[320];
  work.d[320] = work.v[320];
  if (work.d[320] < 0)
    work.d[320] = settings.kkt_reg;
  else
    work.d[320] += settings.kkt_reg;
  work.d_inv[320] = 1/work.d[320];
  work.v[321] = work.KKT[321];
  work.d[321] = work.v[321];
  if (work.d[321] < 0)
    work.d[321] = settings.kkt_reg;
  else
    work.d[321] += settings.kkt_reg;
  work.d_inv[321] = 1/work.d[321];
  work.v[322] = work.KKT[322];
  work.d[322] = work.v[322];
  if (work.d[322] < 0)
    work.d[322] = settings.kkt_reg;
  else
    work.d[322] += settings.kkt_reg;
  work.d_inv[322] = 1/work.d[322];
  work.v[323] = work.KKT[323];
  work.d[323] = work.v[323];
  if (work.d[323] < 0)
    work.d[323] = settings.kkt_reg;
  else
    work.d[323] += settings.kkt_reg;
  work.d_inv[323] = 1/work.d[323];
  work.v[324] = work.KKT[324];
  work.d[324] = work.v[324];
  if (work.d[324] < 0)
    work.d[324] = settings.kkt_reg;
  else
    work.d[324] += settings.kkt_reg;
  work.d_inv[324] = 1/work.d[324];
  work.v[325] = work.KKT[325];
  work.d[325] = work.v[325];
  if (work.d[325] < 0)
    work.d[325] = settings.kkt_reg;
  else
    work.d[325] += settings.kkt_reg;
  work.d_inv[325] = 1/work.d[325];
  work.v[326] = work.KKT[326];
  work.d[326] = work.v[326];
  if (work.d[326] < 0)
    work.d[326] = settings.kkt_reg;
  else
    work.d[326] += settings.kkt_reg;
  work.d_inv[326] = 1/work.d[326];
  work.v[327] = work.KKT[327];
  work.d[327] = work.v[327];
  if (work.d[327] < 0)
    work.d[327] = settings.kkt_reg;
  else
    work.d[327] += settings.kkt_reg;
  work.d_inv[327] = 1/work.d[327];
  work.v[328] = work.KKT[328];
  work.d[328] = work.v[328];
  if (work.d[328] < 0)
    work.d[328] = settings.kkt_reg;
  else
    work.d[328] += settings.kkt_reg;
  work.d_inv[328] = 1/work.d[328];
  work.v[329] = work.KKT[329];
  work.d[329] = work.v[329];
  if (work.d[329] < 0)
    work.d[329] = settings.kkt_reg;
  else
    work.d[329] += settings.kkt_reg;
  work.d_inv[329] = 1/work.d[329];
  work.v[330] = work.KKT[330];
  work.d[330] = work.v[330];
  if (work.d[330] < 0)
    work.d[330] = settings.kkt_reg;
  else
    work.d[330] += settings.kkt_reg;
  work.d_inv[330] = 1/work.d[330];
  work.v[331] = work.KKT[331];
  work.d[331] = work.v[331];
  if (work.d[331] < 0)
    work.d[331] = settings.kkt_reg;
  else
    work.d[331] += settings.kkt_reg;
  work.d_inv[331] = 1/work.d[331];
  work.v[332] = work.KKT[332];
  work.d[332] = work.v[332];
  if (work.d[332] < 0)
    work.d[332] = settings.kkt_reg;
  else
    work.d[332] += settings.kkt_reg;
  work.d_inv[332] = 1/work.d[332];
  work.v[333] = work.KKT[333];
  work.d[333] = work.v[333];
  if (work.d[333] < 0)
    work.d[333] = settings.kkt_reg;
  else
    work.d[333] += settings.kkt_reg;
  work.d_inv[333] = 1/work.d[333];
  work.v[334] = work.KKT[334];
  work.d[334] = work.v[334];
  if (work.d[334] < 0)
    work.d[334] = settings.kkt_reg;
  else
    work.d[334] += settings.kkt_reg;
  work.d_inv[334] = 1/work.d[334];
  work.v[335] = work.KKT[335];
  work.d[335] = work.v[335];
  if (work.d[335] < 0)
    work.d[335] = settings.kkt_reg;
  else
    work.d[335] += settings.kkt_reg;
  work.d_inv[335] = 1/work.d[335];
  work.v[336] = work.KKT[336];
  work.d[336] = work.v[336];
  if (work.d[336] < 0)
    work.d[336] = settings.kkt_reg;
  else
    work.d[336] += settings.kkt_reg;
  work.d_inv[336] = 1/work.d[336];
  work.v[337] = work.KKT[337];
  work.d[337] = work.v[337];
  if (work.d[337] < 0)
    work.d[337] = settings.kkt_reg;
  else
    work.d[337] += settings.kkt_reg;
  work.d_inv[337] = 1/work.d[337];
  work.v[338] = work.KKT[338];
  work.d[338] = work.v[338];
  if (work.d[338] < 0)
    work.d[338] = settings.kkt_reg;
  else
    work.d[338] += settings.kkt_reg;
  work.d_inv[338] = 1/work.d[338];
  work.v[339] = work.KKT[339];
  work.d[339] = work.v[339];
  if (work.d[339] < 0)
    work.d[339] = settings.kkt_reg;
  else
    work.d[339] += settings.kkt_reg;
  work.d_inv[339] = 1/work.d[339];
  work.v[340] = work.KKT[340];
  work.d[340] = work.v[340];
  if (work.d[340] < 0)
    work.d[340] = settings.kkt_reg;
  else
    work.d[340] += settings.kkt_reg;
  work.d_inv[340] = 1/work.d[340];
  work.v[341] = work.KKT[341];
  work.d[341] = work.v[341];
  if (work.d[341] < 0)
    work.d[341] = settings.kkt_reg;
  else
    work.d[341] += settings.kkt_reg;
  work.d_inv[341] = 1/work.d[341];
  work.v[342] = work.KKT[342];
  work.d[342] = work.v[342];
  if (work.d[342] < 0)
    work.d[342] = settings.kkt_reg;
  else
    work.d[342] += settings.kkt_reg;
  work.d_inv[342] = 1/work.d[342];
  work.v[343] = work.KKT[343];
  work.d[343] = work.v[343];
  if (work.d[343] < 0)
    work.d[343] = settings.kkt_reg;
  else
    work.d[343] += settings.kkt_reg;
  work.d_inv[343] = 1/work.d[343];
  work.v[344] = work.KKT[344];
  work.d[344] = work.v[344];
  if (work.d[344] < 0)
    work.d[344] = settings.kkt_reg;
  else
    work.d[344] += settings.kkt_reg;
  work.d_inv[344] = 1/work.d[344];
  work.v[345] = work.KKT[345];
  work.d[345] = work.v[345];
  if (work.d[345] < 0)
    work.d[345] = settings.kkt_reg;
  else
    work.d[345] += settings.kkt_reg;
  work.d_inv[345] = 1/work.d[345];
  work.v[346] = work.KKT[346];
  work.d[346] = work.v[346];
  if (work.d[346] < 0)
    work.d[346] = settings.kkt_reg;
  else
    work.d[346] += settings.kkt_reg;
  work.d_inv[346] = 1/work.d[346];
  work.v[347] = work.KKT[347];
  work.d[347] = work.v[347];
  if (work.d[347] < 0)
    work.d[347] = settings.kkt_reg;
  else
    work.d[347] += settings.kkt_reg;
  work.d_inv[347] = 1/work.d[347];
  work.v[348] = work.KKT[348];
  work.d[348] = work.v[348];
  if (work.d[348] < 0)
    work.d[348] = settings.kkt_reg;
  else
    work.d[348] += settings.kkt_reg;
  work.d_inv[348] = 1/work.d[348];
  work.v[349] = work.KKT[349];
  work.d[349] = work.v[349];
  if (work.d[349] < 0)
    work.d[349] = settings.kkt_reg;
  else
    work.d[349] += settings.kkt_reg;
  work.d_inv[349] = 1/work.d[349];
  work.v[350] = work.KKT[350];
  work.d[350] = work.v[350];
  if (work.d[350] < 0)
    work.d[350] = settings.kkt_reg;
  else
    work.d[350] += settings.kkt_reg;
  work.d_inv[350] = 1/work.d[350];
  work.v[351] = work.KKT[351];
  work.d[351] = work.v[351];
  if (work.d[351] < 0)
    work.d[351] = settings.kkt_reg;
  else
    work.d[351] += settings.kkt_reg;
  work.d_inv[351] = 1/work.d[351];
  work.v[352] = work.KKT[352];
  work.d[352] = work.v[352];
  if (work.d[352] < 0)
    work.d[352] = settings.kkt_reg;
  else
    work.d[352] += settings.kkt_reg;
  work.d_inv[352] = 1/work.d[352];
  work.v[353] = work.KKT[353];
  work.d[353] = work.v[353];
  if (work.d[353] < 0)
    work.d[353] = settings.kkt_reg;
  else
    work.d[353] += settings.kkt_reg;
  work.d_inv[353] = 1/work.d[353];
  work.v[354] = work.KKT[354];
  work.d[354] = work.v[354];
  if (work.d[354] < 0)
    work.d[354] = settings.kkt_reg;
  else
    work.d[354] += settings.kkt_reg;
  work.d_inv[354] = 1/work.d[354];
  work.v[355] = work.KKT[355];
  work.d[355] = work.v[355];
  if (work.d[355] < 0)
    work.d[355] = settings.kkt_reg;
  else
    work.d[355] += settings.kkt_reg;
  work.d_inv[355] = 1/work.d[355];
  work.v[356] = work.KKT[356];
  work.d[356] = work.v[356];
  if (work.d[356] < 0)
    work.d[356] = settings.kkt_reg;
  else
    work.d[356] += settings.kkt_reg;
  work.d_inv[356] = 1/work.d[356];
  work.v[357] = work.KKT[357];
  work.d[357] = work.v[357];
  if (work.d[357] < 0)
    work.d[357] = settings.kkt_reg;
  else
    work.d[357] += settings.kkt_reg;
  work.d_inv[357] = 1/work.d[357];
  work.v[358] = work.KKT[358];
  work.d[358] = work.v[358];
  if (work.d[358] < 0)
    work.d[358] = settings.kkt_reg;
  else
    work.d[358] += settings.kkt_reg;
  work.d_inv[358] = 1/work.d[358];
  work.v[359] = work.KKT[359];
  work.d[359] = work.v[359];
  if (work.d[359] < 0)
    work.d[359] = settings.kkt_reg;
  else
    work.d[359] += settings.kkt_reg;
  work.d_inv[359] = 1/work.d[359];
  work.v[360] = work.KKT[360];
  work.d[360] = work.v[360];
  if (work.d[360] < 0)
    work.d[360] = settings.kkt_reg;
  else
    work.d[360] += settings.kkt_reg;
  work.d_inv[360] = 1/work.d[360];
  work.v[361] = work.KKT[361];
  work.d[361] = work.v[361];
  if (work.d[361] < 0)
    work.d[361] = settings.kkt_reg;
  else
    work.d[361] += settings.kkt_reg;
  work.d_inv[361] = 1/work.d[361];
  work.v[362] = work.KKT[362];
  work.d[362] = work.v[362];
  if (work.d[362] < 0)
    work.d[362] = settings.kkt_reg;
  else
    work.d[362] += settings.kkt_reg;
  work.d_inv[362] = 1/work.d[362];
  work.v[363] = work.KKT[363];
  work.d[363] = work.v[363];
  if (work.d[363] < 0)
    work.d[363] = settings.kkt_reg;
  else
    work.d[363] += settings.kkt_reg;
  work.d_inv[363] = 1/work.d[363];
  work.v[364] = work.KKT[364];
  work.d[364] = work.v[364];
  if (work.d[364] < 0)
    work.d[364] = settings.kkt_reg;
  else
    work.d[364] += settings.kkt_reg;
  work.d_inv[364] = 1/work.d[364];
  work.v[365] = work.KKT[365];
  work.d[365] = work.v[365];
  if (work.d[365] < 0)
    work.d[365] = settings.kkt_reg;
  else
    work.d[365] += settings.kkt_reg;
  work.d_inv[365] = 1/work.d[365];
  work.v[366] = work.KKT[366];
  work.d[366] = work.v[366];
  if (work.d[366] < 0)
    work.d[366] = settings.kkt_reg;
  else
    work.d[366] += settings.kkt_reg;
  work.d_inv[366] = 1/work.d[366];
  work.v[367] = work.KKT[367];
  work.d[367] = work.v[367];
  if (work.d[367] < 0)
    work.d[367] = settings.kkt_reg;
  else
    work.d[367] += settings.kkt_reg;
  work.d_inv[367] = 1/work.d[367];
  work.v[368] = work.KKT[368];
  work.d[368] = work.v[368];
  if (work.d[368] < 0)
    work.d[368] = settings.kkt_reg;
  else
    work.d[368] += settings.kkt_reg;
  work.d_inv[368] = 1/work.d[368];
  work.v[369] = work.KKT[369];
  work.d[369] = work.v[369];
  if (work.d[369] < 0)
    work.d[369] = settings.kkt_reg;
  else
    work.d[369] += settings.kkt_reg;
  work.d_inv[369] = 1/work.d[369];
  work.v[370] = work.KKT[370];
  work.d[370] = work.v[370];
  if (work.d[370] < 0)
    work.d[370] = settings.kkt_reg;
  else
    work.d[370] += settings.kkt_reg;
  work.d_inv[370] = 1/work.d[370];
  work.v[371] = work.KKT[371];
  work.d[371] = work.v[371];
  if (work.d[371] < 0)
    work.d[371] = settings.kkt_reg;
  else
    work.d[371] += settings.kkt_reg;
  work.d_inv[371] = 1/work.d[371];
  work.v[372] = work.KKT[372];
  work.d[372] = work.v[372];
  if (work.d[372] < 0)
    work.d[372] = settings.kkt_reg;
  else
    work.d[372] += settings.kkt_reg;
  work.d_inv[372] = 1/work.d[372];
  work.v[373] = work.KKT[373];
  work.d[373] = work.v[373];
  if (work.d[373] < 0)
    work.d[373] = settings.kkt_reg;
  else
    work.d[373] += settings.kkt_reg;
  work.d_inv[373] = 1/work.d[373];
  work.v[374] = work.KKT[374];
  work.d[374] = work.v[374];
  if (work.d[374] < 0)
    work.d[374] = settings.kkt_reg;
  else
    work.d[374] += settings.kkt_reg;
  work.d_inv[374] = 1/work.d[374];
  work.v[375] = work.KKT[375];
  work.d[375] = work.v[375];
  if (work.d[375] < 0)
    work.d[375] = settings.kkt_reg;
  else
    work.d[375] += settings.kkt_reg;
  work.d_inv[375] = 1/work.d[375];
  work.v[376] = work.KKT[376];
  work.d[376] = work.v[376];
  if (work.d[376] < 0)
    work.d[376] = settings.kkt_reg;
  else
    work.d[376] += settings.kkt_reg;
  work.d_inv[376] = 1/work.d[376];
  work.v[377] = work.KKT[377];
  work.d[377] = work.v[377];
  if (work.d[377] < 0)
    work.d[377] = settings.kkt_reg;
  else
    work.d[377] += settings.kkt_reg;
  work.d_inv[377] = 1/work.d[377];
  work.v[378] = work.KKT[378];
  work.d[378] = work.v[378];
  if (work.d[378] < 0)
    work.d[378] = settings.kkt_reg;
  else
    work.d[378] += settings.kkt_reg;
  work.d_inv[378] = 1/work.d[378];
  work.v[379] = work.KKT[379];
  work.d[379] = work.v[379];
  if (work.d[379] < 0)
    work.d[379] = settings.kkt_reg;
  else
    work.d[379] += settings.kkt_reg;
  work.d_inv[379] = 1/work.d[379];
  work.v[380] = work.KKT[380];
  work.d[380] = work.v[380];
  if (work.d[380] < 0)
    work.d[380] = settings.kkt_reg;
  else
    work.d[380] += settings.kkt_reg;
  work.d_inv[380] = 1/work.d[380];
  work.v[381] = work.KKT[381];
  work.d[381] = work.v[381];
  if (work.d[381] < 0)
    work.d[381] = settings.kkt_reg;
  else
    work.d[381] += settings.kkt_reg;
  work.d_inv[381] = 1/work.d[381];
  work.v[382] = work.KKT[382];
  work.d[382] = work.v[382];
  if (work.d[382] < 0)
    work.d[382] = settings.kkt_reg;
  else
    work.d[382] += settings.kkt_reg;
  work.d_inv[382] = 1/work.d[382];
  work.v[383] = work.KKT[383];
  work.d[383] = work.v[383];
  if (work.d[383] < 0)
    work.d[383] = settings.kkt_reg;
  else
    work.d[383] += settings.kkt_reg;
  work.d_inv[383] = 1/work.d[383];
  work.v[384] = work.KKT[384];
  work.d[384] = work.v[384];
  if (work.d[384] < 0)
    work.d[384] = settings.kkt_reg;
  else
    work.d[384] += settings.kkt_reg;
  work.d_inv[384] = 1/work.d[384];
  work.v[385] = work.KKT[385];
  work.d[385] = work.v[385];
  if (work.d[385] < 0)
    work.d[385] = settings.kkt_reg;
  else
    work.d[385] += settings.kkt_reg;
  work.d_inv[385] = 1/work.d[385];
  work.v[386] = work.KKT[386];
  work.d[386] = work.v[386];
  if (work.d[386] < 0)
    work.d[386] = settings.kkt_reg;
  else
    work.d[386] += settings.kkt_reg;
  work.d_inv[386] = 1/work.d[386];
  work.v[387] = work.KKT[387];
  work.d[387] = work.v[387];
  if (work.d[387] < 0)
    work.d[387] = settings.kkt_reg;
  else
    work.d[387] += settings.kkt_reg;
  work.d_inv[387] = 1/work.d[387];
  work.v[388] = work.KKT[388];
  work.d[388] = work.v[388];
  if (work.d[388] < 0)
    work.d[388] = settings.kkt_reg;
  else
    work.d[388] += settings.kkt_reg;
  work.d_inv[388] = 1/work.d[388];
  work.v[389] = work.KKT[389];
  work.d[389] = work.v[389];
  if (work.d[389] < 0)
    work.d[389] = settings.kkt_reg;
  else
    work.d[389] += settings.kkt_reg;
  work.d_inv[389] = 1/work.d[389];
  work.v[390] = work.KKT[390];
  work.d[390] = work.v[390];
  if (work.d[390] < 0)
    work.d[390] = settings.kkt_reg;
  else
    work.d[390] += settings.kkt_reg;
  work.d_inv[390] = 1/work.d[390];
  work.v[391] = work.KKT[391];
  work.d[391] = work.v[391];
  if (work.d[391] < 0)
    work.d[391] = settings.kkt_reg;
  else
    work.d[391] += settings.kkt_reg;
  work.d_inv[391] = 1/work.d[391];
  work.v[392] = work.KKT[392];
  work.d[392] = work.v[392];
  if (work.d[392] < 0)
    work.d[392] = settings.kkt_reg;
  else
    work.d[392] += settings.kkt_reg;
  work.d_inv[392] = 1/work.d[392];
  work.v[393] = work.KKT[393];
  work.d[393] = work.v[393];
  if (work.d[393] < 0)
    work.d[393] = settings.kkt_reg;
  else
    work.d[393] += settings.kkt_reg;
  work.d_inv[393] = 1/work.d[393];
  work.v[394] = work.KKT[394];
  work.d[394] = work.v[394];
  if (work.d[394] < 0)
    work.d[394] = settings.kkt_reg;
  else
    work.d[394] += settings.kkt_reg;
  work.d_inv[394] = 1/work.d[394];
  work.v[395] = work.KKT[395];
  work.d[395] = work.v[395];
  if (work.d[395] < 0)
    work.d[395] = settings.kkt_reg;
  else
    work.d[395] += settings.kkt_reg;
  work.d_inv[395] = 1/work.d[395];
  work.v[396] = work.KKT[396];
  work.d[396] = work.v[396];
  if (work.d[396] < 0)
    work.d[396] = settings.kkt_reg;
  else
    work.d[396] += settings.kkt_reg;
  work.d_inv[396] = 1/work.d[396];
  work.v[397] = work.KKT[397];
  work.d[397] = work.v[397];
  if (work.d[397] < 0)
    work.d[397] = settings.kkt_reg;
  else
    work.d[397] += settings.kkt_reg;
  work.d_inv[397] = 1/work.d[397];
  work.v[398] = work.KKT[398];
  work.d[398] = work.v[398];
  if (work.d[398] < 0)
    work.d[398] = settings.kkt_reg;
  else
    work.d[398] += settings.kkt_reg;
  work.d_inv[398] = 1/work.d[398];
  work.v[399] = work.KKT[399];
  work.d[399] = work.v[399];
  if (work.d[399] < 0)
    work.d[399] = settings.kkt_reg;
  else
    work.d[399] += settings.kkt_reg;
  work.d_inv[399] = 1/work.d[399];
  work.v[400] = work.KKT[400];
  work.d[400] = work.v[400];
  if (work.d[400] < 0)
    work.d[400] = settings.kkt_reg;
  else
    work.d[400] += settings.kkt_reg;
  work.d_inv[400] = 1/work.d[400];
  work.v[401] = work.KKT[401];
  work.d[401] = work.v[401];
  if (work.d[401] < 0)
    work.d[401] = settings.kkt_reg;
  else
    work.d[401] += settings.kkt_reg;
  work.d_inv[401] = 1/work.d[401];
  work.L[0] = (work.KKT[402])*work.d_inv[401];
  work.v[402] = work.KKT[403];
  work.d[402] = work.v[402];
  if (work.d[402] < 0)
    work.d[402] = settings.kkt_reg;
  else
    work.d[402] += settings.kkt_reg;
  work.d_inv[402] = 1/work.d[402];
  work.L[2] = (work.KKT[404])*work.d_inv[402];
  work.v[401] = work.L[0]*work.d[401];
  work.v[403] = work.KKT[405]-work.L[0]*work.v[401];
  work.d[403] = work.v[403];
  if (work.d[403] > 0)
    work.d[403] = -settings.kkt_reg;
  else
    work.d[403] -= settings.kkt_reg;
  work.d_inv[403] = 1/work.d[403];
  work.L[1] = (work.KKT[406])*work.d_inv[403];
  work.v[403] = work.L[1]*work.d[403];
  work.v[404] = work.KKT[407]-work.L[1]*work.v[403];
  work.d[404] = work.v[404];
  if (work.d[404] < 0)
    work.d[404] = settings.kkt_reg;
  else
    work.d[404] += settings.kkt_reg;
  work.d_inv[404] = 1/work.d[404];
  work.L[3] = (work.KKT[408])*work.d_inv[404];
  work.v[402] = work.L[2]*work.d[402];
  work.v[404] = work.L[3]*work.d[404];
  work.v[405] = work.KKT[409]-work.L[2]*work.v[402]-work.L[3]*work.v[404];
  work.d[405] = work.v[405];
  if (work.d[405] > 0)
    work.d[405] = -settings.kkt_reg;
  else
    work.d[405] -= settings.kkt_reg;
  work.d_inv[405] = 1/work.d[405];
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
  temp = work.KKT[407]-1*work.d[404]*1-work.L[1]*work.d[403]*work.L[1];
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
  temp = work.KKT[59]-1*work.d[59]*1;
  residual += temp*temp;
  temp = work.KKT[60]-1*work.d[60]*1;
  residual += temp*temp;
  temp = work.KKT[61]-1*work.d[61]*1;
  residual += temp*temp;
  temp = work.KKT[62]-1*work.d[62]*1;
  residual += temp*temp;
  temp = work.KKT[63]-1*work.d[63]*1;
  residual += temp*temp;
  temp = work.KKT[64]-1*work.d[64]*1;
  residual += temp*temp;
  temp = work.KKT[65]-1*work.d[65]*1;
  residual += temp*temp;
  temp = work.KKT[66]-1*work.d[66]*1;
  residual += temp*temp;
  temp = work.KKT[67]-1*work.d[67]*1;
  residual += temp*temp;
  temp = work.KKT[68]-1*work.d[68]*1;
  residual += temp*temp;
  temp = work.KKT[69]-1*work.d[69]*1;
  residual += temp*temp;
  temp = work.KKT[70]-1*work.d[70]*1;
  residual += temp*temp;
  temp = work.KKT[71]-1*work.d[71]*1;
  residual += temp*temp;
  temp = work.KKT[72]-1*work.d[72]*1;
  residual += temp*temp;
  temp = work.KKT[73]-1*work.d[73]*1;
  residual += temp*temp;
  temp = work.KKT[74]-1*work.d[74]*1;
  residual += temp*temp;
  temp = work.KKT[75]-1*work.d[75]*1;
  residual += temp*temp;
  temp = work.KKT[76]-1*work.d[76]*1;
  residual += temp*temp;
  temp = work.KKT[77]-1*work.d[77]*1;
  residual += temp*temp;
  temp = work.KKT[78]-1*work.d[78]*1;
  residual += temp*temp;
  temp = work.KKT[79]-1*work.d[79]*1;
  residual += temp*temp;
  temp = work.KKT[80]-1*work.d[80]*1;
  residual += temp*temp;
  temp = work.KKT[81]-1*work.d[81]*1;
  residual += temp*temp;
  temp = work.KKT[82]-1*work.d[82]*1;
  residual += temp*temp;
  temp = work.KKT[83]-1*work.d[83]*1;
  residual += temp*temp;
  temp = work.KKT[84]-1*work.d[84]*1;
  residual += temp*temp;
  temp = work.KKT[85]-1*work.d[85]*1;
  residual += temp*temp;
  temp = work.KKT[86]-1*work.d[86]*1;
  residual += temp*temp;
  temp = work.KKT[87]-1*work.d[87]*1;
  residual += temp*temp;
  temp = work.KKT[88]-1*work.d[88]*1;
  residual += temp*temp;
  temp = work.KKT[89]-1*work.d[89]*1;
  residual += temp*temp;
  temp = work.KKT[90]-1*work.d[90]*1;
  residual += temp*temp;
  temp = work.KKT[91]-1*work.d[91]*1;
  residual += temp*temp;
  temp = work.KKT[92]-1*work.d[92]*1;
  residual += temp*temp;
  temp = work.KKT[93]-1*work.d[93]*1;
  residual += temp*temp;
  temp = work.KKT[94]-1*work.d[94]*1;
  residual += temp*temp;
  temp = work.KKT[95]-1*work.d[95]*1;
  residual += temp*temp;
  temp = work.KKT[96]-1*work.d[96]*1;
  residual += temp*temp;
  temp = work.KKT[97]-1*work.d[97]*1;
  residual += temp*temp;
  temp = work.KKT[98]-1*work.d[98]*1;
  residual += temp*temp;
  temp = work.KKT[99]-1*work.d[99]*1;
  residual += temp*temp;
  temp = work.KKT[100]-1*work.d[100]*1;
  residual += temp*temp;
  temp = work.KKT[101]-1*work.d[101]*1;
  residual += temp*temp;
  temp = work.KKT[102]-1*work.d[102]*1;
  residual += temp*temp;
  temp = work.KKT[103]-1*work.d[103]*1;
  residual += temp*temp;
  temp = work.KKT[104]-1*work.d[104]*1;
  residual += temp*temp;
  temp = work.KKT[105]-1*work.d[105]*1;
  residual += temp*temp;
  temp = work.KKT[106]-1*work.d[106]*1;
  residual += temp*temp;
  temp = work.KKT[107]-1*work.d[107]*1;
  residual += temp*temp;
  temp = work.KKT[108]-1*work.d[108]*1;
  residual += temp*temp;
  temp = work.KKT[109]-1*work.d[109]*1;
  residual += temp*temp;
  temp = work.KKT[110]-1*work.d[110]*1;
  residual += temp*temp;
  temp = work.KKT[111]-1*work.d[111]*1;
  residual += temp*temp;
  temp = work.KKT[112]-1*work.d[112]*1;
  residual += temp*temp;
  temp = work.KKT[113]-1*work.d[113]*1;
  residual += temp*temp;
  temp = work.KKT[114]-1*work.d[114]*1;
  residual += temp*temp;
  temp = work.KKT[115]-1*work.d[115]*1;
  residual += temp*temp;
  temp = work.KKT[116]-1*work.d[116]*1;
  residual += temp*temp;
  temp = work.KKT[117]-1*work.d[117]*1;
  residual += temp*temp;
  temp = work.KKT[118]-1*work.d[118]*1;
  residual += temp*temp;
  temp = work.KKT[119]-1*work.d[119]*1;
  residual += temp*temp;
  temp = work.KKT[120]-1*work.d[120]*1;
  residual += temp*temp;
  temp = work.KKT[121]-1*work.d[121]*1;
  residual += temp*temp;
  temp = work.KKT[122]-1*work.d[122]*1;
  residual += temp*temp;
  temp = work.KKT[123]-1*work.d[123]*1;
  residual += temp*temp;
  temp = work.KKT[124]-1*work.d[124]*1;
  residual += temp*temp;
  temp = work.KKT[125]-1*work.d[125]*1;
  residual += temp*temp;
  temp = work.KKT[126]-1*work.d[126]*1;
  residual += temp*temp;
  temp = work.KKT[127]-1*work.d[127]*1;
  residual += temp*temp;
  temp = work.KKT[128]-1*work.d[128]*1;
  residual += temp*temp;
  temp = work.KKT[129]-1*work.d[129]*1;
  residual += temp*temp;
  temp = work.KKT[130]-1*work.d[130]*1;
  residual += temp*temp;
  temp = work.KKT[131]-1*work.d[131]*1;
  residual += temp*temp;
  temp = work.KKT[132]-1*work.d[132]*1;
  residual += temp*temp;
  temp = work.KKT[133]-1*work.d[133]*1;
  residual += temp*temp;
  temp = work.KKT[134]-1*work.d[134]*1;
  residual += temp*temp;
  temp = work.KKT[135]-1*work.d[135]*1;
  residual += temp*temp;
  temp = work.KKT[136]-1*work.d[136]*1;
  residual += temp*temp;
  temp = work.KKT[137]-1*work.d[137]*1;
  residual += temp*temp;
  temp = work.KKT[138]-1*work.d[138]*1;
  residual += temp*temp;
  temp = work.KKT[139]-1*work.d[139]*1;
  residual += temp*temp;
  temp = work.KKT[140]-1*work.d[140]*1;
  residual += temp*temp;
  temp = work.KKT[141]-1*work.d[141]*1;
  residual += temp*temp;
  temp = work.KKT[142]-1*work.d[142]*1;
  residual += temp*temp;
  temp = work.KKT[143]-1*work.d[143]*1;
  residual += temp*temp;
  temp = work.KKT[144]-1*work.d[144]*1;
  residual += temp*temp;
  temp = work.KKT[145]-1*work.d[145]*1;
  residual += temp*temp;
  temp = work.KKT[146]-1*work.d[146]*1;
  residual += temp*temp;
  temp = work.KKT[147]-1*work.d[147]*1;
  residual += temp*temp;
  temp = work.KKT[148]-1*work.d[148]*1;
  residual += temp*temp;
  temp = work.KKT[149]-1*work.d[149]*1;
  residual += temp*temp;
  temp = work.KKT[150]-1*work.d[150]*1;
  residual += temp*temp;
  temp = work.KKT[151]-1*work.d[151]*1;
  residual += temp*temp;
  temp = work.KKT[152]-1*work.d[152]*1;
  residual += temp*temp;
  temp = work.KKT[153]-1*work.d[153]*1;
  residual += temp*temp;
  temp = work.KKT[154]-1*work.d[154]*1;
  residual += temp*temp;
  temp = work.KKT[155]-1*work.d[155]*1;
  residual += temp*temp;
  temp = work.KKT[156]-1*work.d[156]*1;
  residual += temp*temp;
  temp = work.KKT[157]-1*work.d[157]*1;
  residual += temp*temp;
  temp = work.KKT[158]-1*work.d[158]*1;
  residual += temp*temp;
  temp = work.KKT[159]-1*work.d[159]*1;
  residual += temp*temp;
  temp = work.KKT[160]-1*work.d[160]*1;
  residual += temp*temp;
  temp = work.KKT[161]-1*work.d[161]*1;
  residual += temp*temp;
  temp = work.KKT[162]-1*work.d[162]*1;
  residual += temp*temp;
  temp = work.KKT[163]-1*work.d[163]*1;
  residual += temp*temp;
  temp = work.KKT[164]-1*work.d[164]*1;
  residual += temp*temp;
  temp = work.KKT[165]-1*work.d[165]*1;
  residual += temp*temp;
  temp = work.KKT[166]-1*work.d[166]*1;
  residual += temp*temp;
  temp = work.KKT[167]-1*work.d[167]*1;
  residual += temp*temp;
  temp = work.KKT[168]-1*work.d[168]*1;
  residual += temp*temp;
  temp = work.KKT[169]-1*work.d[169]*1;
  residual += temp*temp;
  temp = work.KKT[170]-1*work.d[170]*1;
  residual += temp*temp;
  temp = work.KKT[171]-1*work.d[171]*1;
  residual += temp*temp;
  temp = work.KKT[172]-1*work.d[172]*1;
  residual += temp*temp;
  temp = work.KKT[173]-1*work.d[173]*1;
  residual += temp*temp;
  temp = work.KKT[174]-1*work.d[174]*1;
  residual += temp*temp;
  temp = work.KKT[175]-1*work.d[175]*1;
  residual += temp*temp;
  temp = work.KKT[176]-1*work.d[176]*1;
  residual += temp*temp;
  temp = work.KKT[177]-1*work.d[177]*1;
  residual += temp*temp;
  temp = work.KKT[178]-1*work.d[178]*1;
  residual += temp*temp;
  temp = work.KKT[179]-1*work.d[179]*1;
  residual += temp*temp;
  temp = work.KKT[180]-1*work.d[180]*1;
  residual += temp*temp;
  temp = work.KKT[181]-1*work.d[181]*1;
  residual += temp*temp;
  temp = work.KKT[182]-1*work.d[182]*1;
  residual += temp*temp;
  temp = work.KKT[183]-1*work.d[183]*1;
  residual += temp*temp;
  temp = work.KKT[184]-1*work.d[184]*1;
  residual += temp*temp;
  temp = work.KKT[185]-1*work.d[185]*1;
  residual += temp*temp;
  temp = work.KKT[186]-1*work.d[186]*1;
  residual += temp*temp;
  temp = work.KKT[187]-1*work.d[187]*1;
  residual += temp*temp;
  temp = work.KKT[188]-1*work.d[188]*1;
  residual += temp*temp;
  temp = work.KKT[189]-1*work.d[189]*1;
  residual += temp*temp;
  temp = work.KKT[190]-1*work.d[190]*1;
  residual += temp*temp;
  temp = work.KKT[191]-1*work.d[191]*1;
  residual += temp*temp;
  temp = work.KKT[192]-1*work.d[192]*1;
  residual += temp*temp;
  temp = work.KKT[193]-1*work.d[193]*1;
  residual += temp*temp;
  temp = work.KKT[194]-1*work.d[194]*1;
  residual += temp*temp;
  temp = work.KKT[195]-1*work.d[195]*1;
  residual += temp*temp;
  temp = work.KKT[196]-1*work.d[196]*1;
  residual += temp*temp;
  temp = work.KKT[197]-1*work.d[197]*1;
  residual += temp*temp;
  temp = work.KKT[198]-1*work.d[198]*1;
  residual += temp*temp;
  temp = work.KKT[199]-1*work.d[199]*1;
  residual += temp*temp;
  temp = work.KKT[200]-1*work.d[200]*1;
  residual += temp*temp;
  temp = work.KKT[201]-1*work.d[201]*1;
  residual += temp*temp;
  temp = work.KKT[202]-1*work.d[202]*1;
  residual += temp*temp;
  temp = work.KKT[203]-1*work.d[203]*1;
  residual += temp*temp;
  temp = work.KKT[204]-1*work.d[204]*1;
  residual += temp*temp;
  temp = work.KKT[205]-1*work.d[205]*1;
  residual += temp*temp;
  temp = work.KKT[206]-1*work.d[206]*1;
  residual += temp*temp;
  temp = work.KKT[207]-1*work.d[207]*1;
  residual += temp*temp;
  temp = work.KKT[208]-1*work.d[208]*1;
  residual += temp*temp;
  temp = work.KKT[209]-1*work.d[209]*1;
  residual += temp*temp;
  temp = work.KKT[210]-1*work.d[210]*1;
  residual += temp*temp;
  temp = work.KKT[211]-1*work.d[211]*1;
  residual += temp*temp;
  temp = work.KKT[212]-1*work.d[212]*1;
  residual += temp*temp;
  temp = work.KKT[213]-1*work.d[213]*1;
  residual += temp*temp;
  temp = work.KKT[214]-1*work.d[214]*1;
  residual += temp*temp;
  temp = work.KKT[215]-1*work.d[215]*1;
  residual += temp*temp;
  temp = work.KKT[216]-1*work.d[216]*1;
  residual += temp*temp;
  temp = work.KKT[217]-1*work.d[217]*1;
  residual += temp*temp;
  temp = work.KKT[218]-1*work.d[218]*1;
  residual += temp*temp;
  temp = work.KKT[219]-1*work.d[219]*1;
  residual += temp*temp;
  temp = work.KKT[220]-1*work.d[220]*1;
  residual += temp*temp;
  temp = work.KKT[221]-1*work.d[221]*1;
  residual += temp*temp;
  temp = work.KKT[222]-1*work.d[222]*1;
  residual += temp*temp;
  temp = work.KKT[223]-1*work.d[223]*1;
  residual += temp*temp;
  temp = work.KKT[224]-1*work.d[224]*1;
  residual += temp*temp;
  temp = work.KKT[225]-1*work.d[225]*1;
  residual += temp*temp;
  temp = work.KKT[226]-1*work.d[226]*1;
  residual += temp*temp;
  temp = work.KKT[227]-1*work.d[227]*1;
  residual += temp*temp;
  temp = work.KKT[228]-1*work.d[228]*1;
  residual += temp*temp;
  temp = work.KKT[229]-1*work.d[229]*1;
  residual += temp*temp;
  temp = work.KKT[230]-1*work.d[230]*1;
  residual += temp*temp;
  temp = work.KKT[231]-1*work.d[231]*1;
  residual += temp*temp;
  temp = work.KKT[232]-1*work.d[232]*1;
  residual += temp*temp;
  temp = work.KKT[233]-1*work.d[233]*1;
  residual += temp*temp;
  temp = work.KKT[234]-1*work.d[234]*1;
  residual += temp*temp;
  temp = work.KKT[235]-1*work.d[235]*1;
  residual += temp*temp;
  temp = work.KKT[236]-1*work.d[236]*1;
  residual += temp*temp;
  temp = work.KKT[237]-1*work.d[237]*1;
  residual += temp*temp;
  temp = work.KKT[238]-1*work.d[238]*1;
  residual += temp*temp;
  temp = work.KKT[239]-1*work.d[239]*1;
  residual += temp*temp;
  temp = work.KKT[240]-1*work.d[240]*1;
  residual += temp*temp;
  temp = work.KKT[241]-1*work.d[241]*1;
  residual += temp*temp;
  temp = work.KKT[242]-1*work.d[242]*1;
  residual += temp*temp;
  temp = work.KKT[243]-1*work.d[243]*1;
  residual += temp*temp;
  temp = work.KKT[244]-1*work.d[244]*1;
  residual += temp*temp;
  temp = work.KKT[245]-1*work.d[245]*1;
  residual += temp*temp;
  temp = work.KKT[246]-1*work.d[246]*1;
  residual += temp*temp;
  temp = work.KKT[247]-1*work.d[247]*1;
  residual += temp*temp;
  temp = work.KKT[248]-1*work.d[248]*1;
  residual += temp*temp;
  temp = work.KKT[249]-1*work.d[249]*1;
  residual += temp*temp;
  temp = work.KKT[250]-1*work.d[250]*1;
  residual += temp*temp;
  temp = work.KKT[251]-1*work.d[251]*1;
  residual += temp*temp;
  temp = work.KKT[252]-1*work.d[252]*1;
  residual += temp*temp;
  temp = work.KKT[253]-1*work.d[253]*1;
  residual += temp*temp;
  temp = work.KKT[254]-1*work.d[254]*1;
  residual += temp*temp;
  temp = work.KKT[255]-1*work.d[255]*1;
  residual += temp*temp;
  temp = work.KKT[256]-1*work.d[256]*1;
  residual += temp*temp;
  temp = work.KKT[257]-1*work.d[257]*1;
  residual += temp*temp;
  temp = work.KKT[258]-1*work.d[258]*1;
  residual += temp*temp;
  temp = work.KKT[259]-1*work.d[259]*1;
  residual += temp*temp;
  temp = work.KKT[260]-1*work.d[260]*1;
  residual += temp*temp;
  temp = work.KKT[261]-1*work.d[261]*1;
  residual += temp*temp;
  temp = work.KKT[262]-1*work.d[262]*1;
  residual += temp*temp;
  temp = work.KKT[263]-1*work.d[263]*1;
  residual += temp*temp;
  temp = work.KKT[264]-1*work.d[264]*1;
  residual += temp*temp;
  temp = work.KKT[265]-1*work.d[265]*1;
  residual += temp*temp;
  temp = work.KKT[266]-1*work.d[266]*1;
  residual += temp*temp;
  temp = work.KKT[267]-1*work.d[267]*1;
  residual += temp*temp;
  temp = work.KKT[268]-1*work.d[268]*1;
  residual += temp*temp;
  temp = work.KKT[269]-1*work.d[269]*1;
  residual += temp*temp;
  temp = work.KKT[270]-1*work.d[270]*1;
  residual += temp*temp;
  temp = work.KKT[271]-1*work.d[271]*1;
  residual += temp*temp;
  temp = work.KKT[272]-1*work.d[272]*1;
  residual += temp*temp;
  temp = work.KKT[273]-1*work.d[273]*1;
  residual += temp*temp;
  temp = work.KKT[274]-1*work.d[274]*1;
  residual += temp*temp;
  temp = work.KKT[275]-1*work.d[275]*1;
  residual += temp*temp;
  temp = work.KKT[276]-1*work.d[276]*1;
  residual += temp*temp;
  temp = work.KKT[277]-1*work.d[277]*1;
  residual += temp*temp;
  temp = work.KKT[278]-1*work.d[278]*1;
  residual += temp*temp;
  temp = work.KKT[279]-1*work.d[279]*1;
  residual += temp*temp;
  temp = work.KKT[280]-1*work.d[280]*1;
  residual += temp*temp;
  temp = work.KKT[281]-1*work.d[281]*1;
  residual += temp*temp;
  temp = work.KKT[282]-1*work.d[282]*1;
  residual += temp*temp;
  temp = work.KKT[283]-1*work.d[283]*1;
  residual += temp*temp;
  temp = work.KKT[284]-1*work.d[284]*1;
  residual += temp*temp;
  temp = work.KKT[285]-1*work.d[285]*1;
  residual += temp*temp;
  temp = work.KKT[286]-1*work.d[286]*1;
  residual += temp*temp;
  temp = work.KKT[287]-1*work.d[287]*1;
  residual += temp*temp;
  temp = work.KKT[288]-1*work.d[288]*1;
  residual += temp*temp;
  temp = work.KKT[289]-1*work.d[289]*1;
  residual += temp*temp;
  temp = work.KKT[290]-1*work.d[290]*1;
  residual += temp*temp;
  temp = work.KKT[291]-1*work.d[291]*1;
  residual += temp*temp;
  temp = work.KKT[292]-1*work.d[292]*1;
  residual += temp*temp;
  temp = work.KKT[293]-1*work.d[293]*1;
  residual += temp*temp;
  temp = work.KKT[294]-1*work.d[294]*1;
  residual += temp*temp;
  temp = work.KKT[295]-1*work.d[295]*1;
  residual += temp*temp;
  temp = work.KKT[296]-1*work.d[296]*1;
  residual += temp*temp;
  temp = work.KKT[297]-1*work.d[297]*1;
  residual += temp*temp;
  temp = work.KKT[298]-1*work.d[298]*1;
  residual += temp*temp;
  temp = work.KKT[299]-1*work.d[299]*1;
  residual += temp*temp;
  temp = work.KKT[300]-1*work.d[300]*1;
  residual += temp*temp;
  temp = work.KKT[301]-1*work.d[301]*1;
  residual += temp*temp;
  temp = work.KKT[302]-1*work.d[302]*1;
  residual += temp*temp;
  temp = work.KKT[303]-1*work.d[303]*1;
  residual += temp*temp;
  temp = work.KKT[304]-1*work.d[304]*1;
  residual += temp*temp;
  temp = work.KKT[305]-1*work.d[305]*1;
  residual += temp*temp;
  temp = work.KKT[306]-1*work.d[306]*1;
  residual += temp*temp;
  temp = work.KKT[307]-1*work.d[307]*1;
  residual += temp*temp;
  temp = work.KKT[308]-1*work.d[308]*1;
  residual += temp*temp;
  temp = work.KKT[309]-1*work.d[309]*1;
  residual += temp*temp;
  temp = work.KKT[310]-1*work.d[310]*1;
  residual += temp*temp;
  temp = work.KKT[311]-1*work.d[311]*1;
  residual += temp*temp;
  temp = work.KKT[312]-1*work.d[312]*1;
  residual += temp*temp;
  temp = work.KKT[313]-1*work.d[313]*1;
  residual += temp*temp;
  temp = work.KKT[314]-1*work.d[314]*1;
  residual += temp*temp;
  temp = work.KKT[315]-1*work.d[315]*1;
  residual += temp*temp;
  temp = work.KKT[316]-1*work.d[316]*1;
  residual += temp*temp;
  temp = work.KKT[317]-1*work.d[317]*1;
  residual += temp*temp;
  temp = work.KKT[318]-1*work.d[318]*1;
  residual += temp*temp;
  temp = work.KKT[319]-1*work.d[319]*1;
  residual += temp*temp;
  temp = work.KKT[320]-1*work.d[320]*1;
  residual += temp*temp;
  temp = work.KKT[321]-1*work.d[321]*1;
  residual += temp*temp;
  temp = work.KKT[322]-1*work.d[322]*1;
  residual += temp*temp;
  temp = work.KKT[323]-1*work.d[323]*1;
  residual += temp*temp;
  temp = work.KKT[324]-1*work.d[324]*1;
  residual += temp*temp;
  temp = work.KKT[325]-1*work.d[325]*1;
  residual += temp*temp;
  temp = work.KKT[326]-1*work.d[326]*1;
  residual += temp*temp;
  temp = work.KKT[327]-1*work.d[327]*1;
  residual += temp*temp;
  temp = work.KKT[328]-1*work.d[328]*1;
  residual += temp*temp;
  temp = work.KKT[329]-1*work.d[329]*1;
  residual += temp*temp;
  temp = work.KKT[330]-1*work.d[330]*1;
  residual += temp*temp;
  temp = work.KKT[331]-1*work.d[331]*1;
  residual += temp*temp;
  temp = work.KKT[332]-1*work.d[332]*1;
  residual += temp*temp;
  temp = work.KKT[333]-1*work.d[333]*1;
  residual += temp*temp;
  temp = work.KKT[334]-1*work.d[334]*1;
  residual += temp*temp;
  temp = work.KKT[335]-1*work.d[335]*1;
  residual += temp*temp;
  temp = work.KKT[336]-1*work.d[336]*1;
  residual += temp*temp;
  temp = work.KKT[337]-1*work.d[337]*1;
  residual += temp*temp;
  temp = work.KKT[338]-1*work.d[338]*1;
  residual += temp*temp;
  temp = work.KKT[339]-1*work.d[339]*1;
  residual += temp*temp;
  temp = work.KKT[340]-1*work.d[340]*1;
  residual += temp*temp;
  temp = work.KKT[341]-1*work.d[341]*1;
  residual += temp*temp;
  temp = work.KKT[342]-1*work.d[342]*1;
  residual += temp*temp;
  temp = work.KKT[343]-1*work.d[343]*1;
  residual += temp*temp;
  temp = work.KKT[344]-1*work.d[344]*1;
  residual += temp*temp;
  temp = work.KKT[345]-1*work.d[345]*1;
  residual += temp*temp;
  temp = work.KKT[346]-1*work.d[346]*1;
  residual += temp*temp;
  temp = work.KKT[347]-1*work.d[347]*1;
  residual += temp*temp;
  temp = work.KKT[348]-1*work.d[348]*1;
  residual += temp*temp;
  temp = work.KKT[349]-1*work.d[349]*1;
  residual += temp*temp;
  temp = work.KKT[350]-1*work.d[350]*1;
  residual += temp*temp;
  temp = work.KKT[351]-1*work.d[351]*1;
  residual += temp*temp;
  temp = work.KKT[352]-1*work.d[352]*1;
  residual += temp*temp;
  temp = work.KKT[353]-1*work.d[353]*1;
  residual += temp*temp;
  temp = work.KKT[354]-1*work.d[354]*1;
  residual += temp*temp;
  temp = work.KKT[355]-1*work.d[355]*1;
  residual += temp*temp;
  temp = work.KKT[356]-1*work.d[356]*1;
  residual += temp*temp;
  temp = work.KKT[357]-1*work.d[357]*1;
  residual += temp*temp;
  temp = work.KKT[358]-1*work.d[358]*1;
  residual += temp*temp;
  temp = work.KKT[359]-1*work.d[359]*1;
  residual += temp*temp;
  temp = work.KKT[360]-1*work.d[360]*1;
  residual += temp*temp;
  temp = work.KKT[361]-1*work.d[361]*1;
  residual += temp*temp;
  temp = work.KKT[362]-1*work.d[362]*1;
  residual += temp*temp;
  temp = work.KKT[363]-1*work.d[363]*1;
  residual += temp*temp;
  temp = work.KKT[364]-1*work.d[364]*1;
  residual += temp*temp;
  temp = work.KKT[365]-1*work.d[365]*1;
  residual += temp*temp;
  temp = work.KKT[366]-1*work.d[366]*1;
  residual += temp*temp;
  temp = work.KKT[367]-1*work.d[367]*1;
  residual += temp*temp;
  temp = work.KKT[368]-1*work.d[368]*1;
  residual += temp*temp;
  temp = work.KKT[369]-1*work.d[369]*1;
  residual += temp*temp;
  temp = work.KKT[370]-1*work.d[370]*1;
  residual += temp*temp;
  temp = work.KKT[371]-1*work.d[371]*1;
  residual += temp*temp;
  temp = work.KKT[372]-1*work.d[372]*1;
  residual += temp*temp;
  temp = work.KKT[373]-1*work.d[373]*1;
  residual += temp*temp;
  temp = work.KKT[374]-1*work.d[374]*1;
  residual += temp*temp;
  temp = work.KKT[375]-1*work.d[375]*1;
  residual += temp*temp;
  temp = work.KKT[376]-1*work.d[376]*1;
  residual += temp*temp;
  temp = work.KKT[377]-1*work.d[377]*1;
  residual += temp*temp;
  temp = work.KKT[378]-1*work.d[378]*1;
  residual += temp*temp;
  temp = work.KKT[379]-1*work.d[379]*1;
  residual += temp*temp;
  temp = work.KKT[380]-1*work.d[380]*1;
  residual += temp*temp;
  temp = work.KKT[381]-1*work.d[381]*1;
  residual += temp*temp;
  temp = work.KKT[382]-1*work.d[382]*1;
  residual += temp*temp;
  temp = work.KKT[383]-1*work.d[383]*1;
  residual += temp*temp;
  temp = work.KKT[384]-1*work.d[384]*1;
  residual += temp*temp;
  temp = work.KKT[385]-1*work.d[385]*1;
  residual += temp*temp;
  temp = work.KKT[386]-1*work.d[386]*1;
  residual += temp*temp;
  temp = work.KKT[387]-1*work.d[387]*1;
  residual += temp*temp;
  temp = work.KKT[388]-1*work.d[388]*1;
  residual += temp*temp;
  temp = work.KKT[389]-1*work.d[389]*1;
  residual += temp*temp;
  temp = work.KKT[390]-1*work.d[390]*1;
  residual += temp*temp;
  temp = work.KKT[391]-1*work.d[391]*1;
  residual += temp*temp;
  temp = work.KKT[392]-1*work.d[392]*1;
  residual += temp*temp;
  temp = work.KKT[393]-1*work.d[393]*1;
  residual += temp*temp;
  temp = work.KKT[394]-1*work.d[394]*1;
  residual += temp*temp;
  temp = work.KKT[395]-1*work.d[395]*1;
  residual += temp*temp;
  temp = work.KKT[396]-1*work.d[396]*1;
  residual += temp*temp;
  temp = work.KKT[397]-1*work.d[397]*1;
  residual += temp*temp;
  temp = work.KKT[398]-1*work.d[398]*1;
  residual += temp*temp;
  temp = work.KKT[399]-1*work.d[399]*1;
  residual += temp*temp;
  temp = work.KKT[400]-1*work.d[400]*1;
  residual += temp*temp;
  temp = work.KKT[401]-1*work.d[401]*1;
  residual += temp*temp;
  temp = work.KKT[403]-1*work.d[402]*1;
  residual += temp*temp;
  temp = work.KKT[402]-work.L[0]*work.d[401]*1;
  residual += temp*temp;
  temp = work.KKT[404]-work.L[2]*work.d[402]*1;
  residual += temp*temp;
  temp = work.KKT[405]-work.L[0]*work.d[401]*work.L[0]-1*work.d[403]*1;
  residual += temp*temp;
  temp = work.KKT[409]-work.L[2]*work.d[402]*work.L[2]-1*work.d[405]*1-work.L[3]*work.d[404]*work.L[3];
  residual += temp*temp;
  temp = work.KKT[406]-1*work.d[403]*work.L[1];
  residual += temp*temp;
  temp = work.KKT[408]-work.L[3]*work.d[404]*1;
  residual += temp*temp;
  return residual;
}
void Gensolver::matrix_multiply(double *result, double *source) {
  /* Finds result = A*source. */
  result[0] = work.KKT[407]*source[0]+work.KKT[406]*source[404]+work.KKT[408]*source[405];
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
  result[59] = work.KKT[58]*source[59];
  result[60] = work.KKT[59]*source[60];
  result[61] = work.KKT[60]*source[61];
  result[62] = work.KKT[61]*source[62];
  result[63] = work.KKT[62]*source[63];
  result[64] = work.KKT[63]*source[64];
  result[65] = work.KKT[64]*source[65];
  result[66] = work.KKT[65]*source[66];
  result[67] = work.KKT[66]*source[67];
  result[68] = work.KKT[67]*source[68];
  result[69] = work.KKT[68]*source[69];
  result[70] = work.KKT[69]*source[70];
  result[71] = work.KKT[70]*source[71];
  result[72] = work.KKT[71]*source[72];
  result[73] = work.KKT[72]*source[73];
  result[74] = work.KKT[73]*source[74];
  result[75] = work.KKT[74]*source[75];
  result[76] = work.KKT[75]*source[76];
  result[77] = work.KKT[76]*source[77];
  result[78] = work.KKT[77]*source[78];
  result[79] = work.KKT[78]*source[79];
  result[80] = work.KKT[79]*source[80];
  result[81] = work.KKT[80]*source[81];
  result[82] = work.KKT[81]*source[82];
  result[83] = work.KKT[82]*source[83];
  result[84] = work.KKT[83]*source[84];
  result[85] = work.KKT[84]*source[85];
  result[86] = work.KKT[85]*source[86];
  result[87] = work.KKT[86]*source[87];
  result[88] = work.KKT[87]*source[88];
  result[89] = work.KKT[88]*source[89];
  result[90] = work.KKT[89]*source[90];
  result[91] = work.KKT[90]*source[91];
  result[92] = work.KKT[91]*source[92];
  result[93] = work.KKT[92]*source[93];
  result[94] = work.KKT[93]*source[94];
  result[95] = work.KKT[94]*source[95];
  result[96] = work.KKT[95]*source[96];
  result[97] = work.KKT[96]*source[97];
  result[98] = work.KKT[97]*source[98];
  result[99] = work.KKT[98]*source[99];
  result[100] = work.KKT[99]*source[100];
  result[101] = work.KKT[100]*source[101];
  result[102] = work.KKT[101]*source[102];
  result[103] = work.KKT[102]*source[103];
  result[104] = work.KKT[103]*source[104];
  result[105] = work.KKT[104]*source[105];
  result[106] = work.KKT[105]*source[106];
  result[107] = work.KKT[106]*source[107];
  result[108] = work.KKT[107]*source[108];
  result[109] = work.KKT[108]*source[109];
  result[110] = work.KKT[109]*source[110];
  result[111] = work.KKT[110]*source[111];
  result[112] = work.KKT[111]*source[112];
  result[113] = work.KKT[112]*source[113];
  result[114] = work.KKT[113]*source[114];
  result[115] = work.KKT[114]*source[115];
  result[116] = work.KKT[115]*source[116];
  result[117] = work.KKT[116]*source[117];
  result[118] = work.KKT[117]*source[118];
  result[119] = work.KKT[118]*source[119];
  result[120] = work.KKT[119]*source[120];
  result[121] = work.KKT[120]*source[121];
  result[122] = work.KKT[121]*source[122];
  result[123] = work.KKT[122]*source[123];
  result[124] = work.KKT[123]*source[124];
  result[125] = work.KKT[124]*source[125];
  result[126] = work.KKT[125]*source[126];
  result[127] = work.KKT[126]*source[127];
  result[128] = work.KKT[127]*source[128];
  result[129] = work.KKT[128]*source[129];
  result[130] = work.KKT[129]*source[130];
  result[131] = work.KKT[130]*source[131];
  result[132] = work.KKT[131]*source[132];
  result[133] = work.KKT[132]*source[133];
  result[134] = work.KKT[133]*source[134];
  result[135] = work.KKT[134]*source[135];
  result[136] = work.KKT[135]*source[136];
  result[137] = work.KKT[136]*source[137];
  result[138] = work.KKT[137]*source[138];
  result[139] = work.KKT[138]*source[139];
  result[140] = work.KKT[139]*source[140];
  result[141] = work.KKT[140]*source[141];
  result[142] = work.KKT[141]*source[142];
  result[143] = work.KKT[142]*source[143];
  result[144] = work.KKT[143]*source[144];
  result[145] = work.KKT[144]*source[145];
  result[146] = work.KKT[145]*source[146];
  result[147] = work.KKT[146]*source[147];
  result[148] = work.KKT[147]*source[148];
  result[149] = work.KKT[148]*source[149];
  result[150] = work.KKT[149]*source[150];
  result[151] = work.KKT[150]*source[151];
  result[152] = work.KKT[151]*source[152];
  result[153] = work.KKT[152]*source[153];
  result[154] = work.KKT[153]*source[154];
  result[155] = work.KKT[154]*source[155];
  result[156] = work.KKT[155]*source[156];
  result[157] = work.KKT[156]*source[157];
  result[158] = work.KKT[157]*source[158];
  result[159] = work.KKT[158]*source[159];
  result[160] = work.KKT[159]*source[160];
  result[161] = work.KKT[160]*source[161];
  result[162] = work.KKT[161]*source[162];
  result[163] = work.KKT[162]*source[163];
  result[164] = work.KKT[163]*source[164];
  result[165] = work.KKT[164]*source[165];
  result[166] = work.KKT[165]*source[166];
  result[167] = work.KKT[166]*source[167];
  result[168] = work.KKT[167]*source[168];
  result[169] = work.KKT[168]*source[169];
  result[170] = work.KKT[169]*source[170];
  result[171] = work.KKT[170]*source[171];
  result[172] = work.KKT[171]*source[172];
  result[173] = work.KKT[172]*source[173];
  result[174] = work.KKT[173]*source[174];
  result[175] = work.KKT[174]*source[175];
  result[176] = work.KKT[175]*source[176];
  result[177] = work.KKT[176]*source[177];
  result[178] = work.KKT[177]*source[178];
  result[179] = work.KKT[178]*source[179];
  result[180] = work.KKT[179]*source[180];
  result[181] = work.KKT[180]*source[181];
  result[182] = work.KKT[181]*source[182];
  result[183] = work.KKT[182]*source[183];
  result[184] = work.KKT[183]*source[184];
  result[185] = work.KKT[184]*source[185];
  result[186] = work.KKT[185]*source[186];
  result[187] = work.KKT[186]*source[187];
  result[188] = work.KKT[187]*source[188];
  result[189] = work.KKT[188]*source[189];
  result[190] = work.KKT[189]*source[190];
  result[191] = work.KKT[190]*source[191];
  result[192] = work.KKT[191]*source[192];
  result[193] = work.KKT[192]*source[193];
  result[194] = work.KKT[193]*source[194];
  result[195] = work.KKT[194]*source[195];
  result[196] = work.KKT[195]*source[196];
  result[197] = work.KKT[196]*source[197];
  result[198] = work.KKT[197]*source[198];
  result[199] = work.KKT[198]*source[199];
  result[200] = work.KKT[199]*source[200];
  result[201] = work.KKT[200]*source[201];
  result[202] = work.KKT[201]*source[202];
  result[203] = work.KKT[202]*source[203];
  result[204] = work.KKT[203]*source[204];
  result[205] = work.KKT[204]*source[205];
  result[206] = work.KKT[205]*source[206];
  result[207] = work.KKT[206]*source[207];
  result[208] = work.KKT[207]*source[208];
  result[209] = work.KKT[208]*source[209];
  result[210] = work.KKT[209]*source[210];
  result[211] = work.KKT[210]*source[211];
  result[212] = work.KKT[211]*source[212];
  result[213] = work.KKT[212]*source[213];
  result[214] = work.KKT[213]*source[214];
  result[215] = work.KKT[214]*source[215];
  result[216] = work.KKT[215]*source[216];
  result[217] = work.KKT[216]*source[217];
  result[218] = work.KKT[217]*source[218];
  result[219] = work.KKT[218]*source[219];
  result[220] = work.KKT[219]*source[220];
  result[221] = work.KKT[220]*source[221];
  result[222] = work.KKT[221]*source[222];
  result[223] = work.KKT[222]*source[223];
  result[224] = work.KKT[223]*source[224];
  result[225] = work.KKT[224]*source[225];
  result[226] = work.KKT[225]*source[226];
  result[227] = work.KKT[226]*source[227];
  result[228] = work.KKT[227]*source[228];
  result[229] = work.KKT[228]*source[229];
  result[230] = work.KKT[229]*source[230];
  result[231] = work.KKT[230]*source[231];
  result[232] = work.KKT[231]*source[232];
  result[233] = work.KKT[232]*source[233];
  result[234] = work.KKT[233]*source[234];
  result[235] = work.KKT[234]*source[235];
  result[236] = work.KKT[235]*source[236];
  result[237] = work.KKT[236]*source[237];
  result[238] = work.KKT[237]*source[238];
  result[239] = work.KKT[238]*source[239];
  result[240] = work.KKT[239]*source[240];
  result[241] = work.KKT[240]*source[241];
  result[242] = work.KKT[241]*source[242];
  result[243] = work.KKT[242]*source[243];
  result[244] = work.KKT[243]*source[244];
  result[245] = work.KKT[244]*source[245];
  result[246] = work.KKT[245]*source[246];
  result[247] = work.KKT[246]*source[247];
  result[248] = work.KKT[247]*source[248];
  result[249] = work.KKT[248]*source[249];
  result[250] = work.KKT[249]*source[250];
  result[251] = work.KKT[250]*source[251];
  result[252] = work.KKT[251]*source[252];
  result[253] = work.KKT[252]*source[253];
  result[254] = work.KKT[253]*source[254];
  result[255] = work.KKT[254]*source[255];
  result[256] = work.KKT[255]*source[256];
  result[257] = work.KKT[256]*source[257];
  result[258] = work.KKT[257]*source[258];
  result[259] = work.KKT[258]*source[259];
  result[260] = work.KKT[259]*source[260];
  result[261] = work.KKT[260]*source[261];
  result[262] = work.KKT[261]*source[262];
  result[263] = work.KKT[262]*source[263];
  result[264] = work.KKT[263]*source[264];
  result[265] = work.KKT[264]*source[265];
  result[266] = work.KKT[265]*source[266];
  result[267] = work.KKT[266]*source[267];
  result[268] = work.KKT[267]*source[268];
  result[269] = work.KKT[268]*source[269];
  result[270] = work.KKT[269]*source[270];
  result[271] = work.KKT[270]*source[271];
  result[272] = work.KKT[271]*source[272];
  result[273] = work.KKT[272]*source[273];
  result[274] = work.KKT[273]*source[274];
  result[275] = work.KKT[274]*source[275];
  result[276] = work.KKT[275]*source[276];
  result[277] = work.KKT[276]*source[277];
  result[278] = work.KKT[277]*source[278];
  result[279] = work.KKT[278]*source[279];
  result[280] = work.KKT[279]*source[280];
  result[281] = work.KKT[280]*source[281];
  result[282] = work.KKT[281]*source[282];
  result[283] = work.KKT[282]*source[283];
  result[284] = work.KKT[283]*source[284];
  result[285] = work.KKT[284]*source[285];
  result[286] = work.KKT[285]*source[286];
  result[287] = work.KKT[286]*source[287];
  result[288] = work.KKT[287]*source[288];
  result[289] = work.KKT[288]*source[289];
  result[290] = work.KKT[289]*source[290];
  result[291] = work.KKT[290]*source[291];
  result[292] = work.KKT[291]*source[292];
  result[293] = work.KKT[292]*source[293];
  result[294] = work.KKT[293]*source[294];
  result[295] = work.KKT[294]*source[295];
  result[296] = work.KKT[295]*source[296];
  result[297] = work.KKT[296]*source[297];
  result[298] = work.KKT[297]*source[298];
  result[299] = work.KKT[298]*source[299];
  result[300] = work.KKT[299]*source[300];
  result[301] = work.KKT[300]*source[301];
  result[302] = work.KKT[301]*source[302];
  result[303] = work.KKT[302]*source[303];
  result[304] = work.KKT[303]*source[304];
  result[305] = work.KKT[304]*source[305];
  result[306] = work.KKT[305]*source[306];
  result[307] = work.KKT[306]*source[307];
  result[308] = work.KKT[307]*source[308];
  result[309] = work.KKT[308]*source[309];
  result[310] = work.KKT[309]*source[310];
  result[311] = work.KKT[310]*source[311];
  result[312] = work.KKT[311]*source[312];
  result[313] = work.KKT[312]*source[313];
  result[314] = work.KKT[313]*source[314];
  result[315] = work.KKT[314]*source[315];
  result[316] = work.KKT[315]*source[316];
  result[317] = work.KKT[316]*source[317];
  result[318] = work.KKT[317]*source[318];
  result[319] = work.KKT[318]*source[319];
  result[320] = work.KKT[319]*source[320];
  result[321] = work.KKT[320]*source[321];
  result[322] = work.KKT[321]*source[322];
  result[323] = work.KKT[322]*source[323];
  result[324] = work.KKT[323]*source[324];
  result[325] = work.KKT[324]*source[325];
  result[326] = work.KKT[325]*source[326];
  result[327] = work.KKT[326]*source[327];
  result[328] = work.KKT[327]*source[328];
  result[329] = work.KKT[328]*source[329];
  result[330] = work.KKT[329]*source[330];
  result[331] = work.KKT[330]*source[331];
  result[332] = work.KKT[331]*source[332];
  result[333] = work.KKT[332]*source[333];
  result[334] = work.KKT[333]*source[334];
  result[335] = work.KKT[334]*source[335];
  result[336] = work.KKT[335]*source[336];
  result[337] = work.KKT[336]*source[337];
  result[338] = work.KKT[337]*source[338];
  result[339] = work.KKT[338]*source[339];
  result[340] = work.KKT[339]*source[340];
  result[341] = work.KKT[340]*source[341];
  result[342] = work.KKT[341]*source[342];
  result[343] = work.KKT[342]*source[343];
  result[344] = work.KKT[343]*source[344];
  result[345] = work.KKT[344]*source[345];
  result[346] = work.KKT[345]*source[346];
  result[347] = work.KKT[346]*source[347];
  result[348] = work.KKT[347]*source[348];
  result[349] = work.KKT[348]*source[349];
  result[350] = work.KKT[349]*source[350];
  result[351] = work.KKT[350]*source[351];
  result[352] = work.KKT[351]*source[352];
  result[353] = work.KKT[352]*source[353];
  result[354] = work.KKT[353]*source[354];
  result[355] = work.KKT[354]*source[355];
  result[356] = work.KKT[355]*source[356];
  result[357] = work.KKT[356]*source[357];
  result[358] = work.KKT[357]*source[358];
  result[359] = work.KKT[358]*source[359];
  result[360] = work.KKT[359]*source[360];
  result[361] = work.KKT[360]*source[361];
  result[362] = work.KKT[361]*source[362];
  result[363] = work.KKT[362]*source[363];
  result[364] = work.KKT[363]*source[364];
  result[365] = work.KKT[364]*source[365];
  result[366] = work.KKT[365]*source[366];
  result[367] = work.KKT[366]*source[367];
  result[368] = work.KKT[367]*source[368];
  result[369] = work.KKT[368]*source[369];
  result[370] = work.KKT[369]*source[370];
  result[371] = work.KKT[370]*source[371];
  result[372] = work.KKT[371]*source[372];
  result[373] = work.KKT[372]*source[373];
  result[374] = work.KKT[373]*source[374];
  result[375] = work.KKT[374]*source[375];
  result[376] = work.KKT[375]*source[376];
  result[377] = work.KKT[376]*source[377];
  result[378] = work.KKT[377]*source[378];
  result[379] = work.KKT[378]*source[379];
  result[380] = work.KKT[379]*source[380];
  result[381] = work.KKT[380]*source[381];
  result[382] = work.KKT[381]*source[382];
  result[383] = work.KKT[382]*source[383];
  result[384] = work.KKT[383]*source[384];
  result[385] = work.KKT[384]*source[385];
  result[386] = work.KKT[385]*source[386];
  result[387] = work.KKT[386]*source[387];
  result[388] = work.KKT[387]*source[388];
  result[389] = work.KKT[388]*source[389];
  result[390] = work.KKT[389]*source[390];
  result[391] = work.KKT[390]*source[391];
  result[392] = work.KKT[391]*source[392];
  result[393] = work.KKT[392]*source[393];
  result[394] = work.KKT[393]*source[394];
  result[395] = work.KKT[394]*source[395];
  result[396] = work.KKT[395]*source[396];
  result[397] = work.KKT[396]*source[397];
  result[398] = work.KKT[397]*source[398];
  result[399] = work.KKT[398]*source[399];
  result[400] = work.KKT[399]*source[400];
  result[401] = work.KKT[400]*source[401];
  result[402] = work.KKT[401]*source[402]+work.KKT[402]*source[404];
  result[403] = work.KKT[403]*source[403]+work.KKT[404]*source[405];
  result[404] = work.KKT[402]*source[402]+work.KKT[405]*source[404]+work.KKT[406]*source[0];
  result[405] = work.KKT[404]*source[403]+work.KKT[409]*source[405]+work.KKT[408]*source[0];
}
double Gensolver::check_residual(double *target, double *multiplicand) {
  /* Returns the squared 2-norm of lhs - A*rhs. */
  /* Reuses v to find the residual. */
  int i;
  double residual;
  residual = 0;
  matrix_multiply(work.v, multiplicand);
  for (i = 0; i < 402; i++) {
    residual += (target[i] - work.v[i])*(target[i] - work.v[i]);
  }
  return residual;
}
void Gensolver::fill_KKT(void) {
  work.KKT[407] = 2*(params.c2[0]+work.quad_530423889920[0]+work.frac_121674190848*params.contNum[0]);
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
  work.KKT[58] = 2*work.frac_121674190848;
  work.KKT[59] = 2*work.frac_121674190848;
  work.KKT[60] = 2*work.frac_121674190848;
  work.KKT[61] = 2*work.frac_121674190848;
  work.KKT[62] = 2*work.frac_121674190848;
  work.KKT[63] = 2*work.frac_121674190848;
  work.KKT[64] = 2*work.frac_121674190848;
  work.KKT[65] = 2*work.frac_121674190848;
  work.KKT[66] = 2*work.frac_121674190848;
  work.KKT[67] = 2*work.frac_121674190848;
  work.KKT[68] = 2*work.frac_121674190848;
  work.KKT[69] = 2*work.frac_121674190848;
  work.KKT[70] = 2*work.frac_121674190848;
  work.KKT[71] = 2*work.frac_121674190848;
  work.KKT[72] = 2*work.frac_121674190848;
  work.KKT[73] = 2*work.frac_121674190848;
  work.KKT[74] = 2*work.frac_121674190848;
  work.KKT[75] = 2*work.frac_121674190848;
  work.KKT[76] = 2*work.frac_121674190848;
  work.KKT[77] = 2*work.frac_121674190848;
  work.KKT[78] = 2*work.frac_121674190848;
  work.KKT[79] = 2*work.frac_121674190848;
  work.KKT[80] = 2*work.frac_121674190848;
  work.KKT[81] = 2*work.frac_121674190848;
  work.KKT[82] = 2*work.frac_121674190848;
  work.KKT[83] = 2*work.frac_121674190848;
  work.KKT[84] = 2*work.frac_121674190848;
  work.KKT[85] = 2*work.frac_121674190848;
  work.KKT[86] = 2*work.frac_121674190848;
  work.KKT[87] = 2*work.frac_121674190848;
  work.KKT[88] = 2*work.frac_121674190848;
  work.KKT[89] = 2*work.frac_121674190848;
  work.KKT[90] = 2*work.frac_121674190848;
  work.KKT[91] = 2*work.frac_121674190848;
  work.KKT[92] = 2*work.frac_121674190848;
  work.KKT[93] = 2*work.frac_121674190848;
  work.KKT[94] = 2*work.frac_121674190848;
  work.KKT[95] = 2*work.frac_121674190848;
  work.KKT[96] = 2*work.frac_121674190848;
  work.KKT[97] = 2*work.frac_121674190848;
  work.KKT[98] = 2*work.frac_121674190848;
  work.KKT[99] = 2*work.frac_121674190848;
  work.KKT[100] = 2*work.frac_121674190848;
  work.KKT[101] = 2*work.frac_121674190848;
  work.KKT[102] = 2*work.frac_121674190848;
  work.KKT[103] = 2*work.frac_121674190848;
  work.KKT[104] = 2*work.frac_121674190848;
  work.KKT[105] = 2*work.frac_121674190848;
  work.KKT[106] = 2*work.frac_121674190848;
  work.KKT[107] = 2*work.frac_121674190848;
  work.KKT[108] = 2*work.frac_121674190848;
  work.KKT[109] = 2*work.frac_121674190848;
  work.KKT[110] = 2*work.frac_121674190848;
  work.KKT[111] = 2*work.frac_121674190848;
  work.KKT[112] = 2*work.frac_121674190848;
  work.KKT[113] = 2*work.frac_121674190848;
  work.KKT[114] = 2*work.frac_121674190848;
  work.KKT[115] = 2*work.frac_121674190848;
  work.KKT[116] = 2*work.frac_121674190848;
  work.KKT[117] = 2*work.frac_121674190848;
  work.KKT[118] = 2*work.frac_121674190848;
  work.KKT[119] = 2*work.frac_121674190848;
  work.KKT[120] = 2*work.frac_121674190848;
  work.KKT[121] = 2*work.frac_121674190848;
  work.KKT[122] = 2*work.frac_121674190848;
  work.KKT[123] = 2*work.frac_121674190848;
  work.KKT[124] = 2*work.frac_121674190848;
  work.KKT[125] = 2*work.frac_121674190848;
  work.KKT[126] = 2*work.frac_121674190848;
  work.KKT[127] = 2*work.frac_121674190848;
  work.KKT[128] = 2*work.frac_121674190848;
  work.KKT[129] = 2*work.frac_121674190848;
  work.KKT[130] = 2*work.frac_121674190848;
  work.KKT[131] = 2*work.frac_121674190848;
  work.KKT[132] = 2*work.frac_121674190848;
  work.KKT[133] = 2*work.frac_121674190848;
  work.KKT[134] = 2*work.frac_121674190848;
  work.KKT[135] = 2*work.frac_121674190848;
  work.KKT[136] = 2*work.frac_121674190848;
  work.KKT[137] = 2*work.frac_121674190848;
  work.KKT[138] = 2*work.frac_121674190848;
  work.KKT[139] = 2*work.frac_121674190848;
  work.KKT[140] = 2*work.frac_121674190848;
  work.KKT[141] = 2*work.frac_121674190848;
  work.KKT[142] = 2*work.frac_121674190848;
  work.KKT[143] = 2*work.frac_121674190848;
  work.KKT[144] = 2*work.frac_121674190848;
  work.KKT[145] = 2*work.frac_121674190848;
  work.KKT[146] = 2*work.frac_121674190848;
  work.KKT[147] = 2*work.frac_121674190848;
  work.KKT[148] = 2*work.frac_121674190848;
  work.KKT[149] = 2*work.frac_121674190848;
  work.KKT[150] = 2*work.frac_121674190848;
  work.KKT[151] = 2*work.frac_121674190848;
  work.KKT[152] = 2*work.frac_121674190848;
  work.KKT[153] = 2*work.frac_121674190848;
  work.KKT[154] = 2*work.frac_121674190848;
  work.KKT[155] = 2*work.frac_121674190848;
  work.KKT[156] = 2*work.frac_121674190848;
  work.KKT[157] = 2*work.frac_121674190848;
  work.KKT[158] = 2*work.frac_121674190848;
  work.KKT[159] = 2*work.frac_121674190848;
  work.KKT[160] = 2*work.frac_121674190848;
  work.KKT[161] = 2*work.frac_121674190848;
  work.KKT[162] = 2*work.frac_121674190848;
  work.KKT[163] = 2*work.frac_121674190848;
  work.KKT[164] = 2*work.frac_121674190848;
  work.KKT[165] = 2*work.frac_121674190848;
  work.KKT[166] = 2*work.frac_121674190848;
  work.KKT[167] = 2*work.frac_121674190848;
  work.KKT[168] = 2*work.frac_121674190848;
  work.KKT[169] = 2*work.frac_121674190848;
  work.KKT[170] = 2*work.frac_121674190848;
  work.KKT[171] = 2*work.frac_121674190848;
  work.KKT[172] = 2*work.frac_121674190848;
  work.KKT[173] = 2*work.frac_121674190848;
  work.KKT[174] = 2*work.frac_121674190848;
  work.KKT[175] = 2*work.frac_121674190848;
  work.KKT[176] = 2*work.frac_121674190848;
  work.KKT[177] = 2*work.frac_121674190848;
  work.KKT[178] = 2*work.frac_121674190848;
  work.KKT[179] = 2*work.frac_121674190848;
  work.KKT[180] = 2*work.frac_121674190848;
  work.KKT[181] = 2*work.frac_121674190848;
  work.KKT[182] = 2*work.frac_121674190848;
  work.KKT[183] = 2*work.frac_121674190848;
  work.KKT[184] = 2*work.frac_121674190848;
  work.KKT[185] = 2*work.frac_121674190848;
  work.KKT[186] = 2*work.frac_121674190848;
  work.KKT[187] = 2*work.frac_121674190848;
  work.KKT[188] = 2*work.frac_121674190848;
  work.KKT[189] = 2*work.frac_121674190848;
  work.KKT[190] = 2*work.frac_121674190848;
  work.KKT[191] = 2*work.frac_121674190848;
  work.KKT[192] = 2*work.frac_121674190848;
  work.KKT[193] = 2*work.frac_121674190848;
  work.KKT[194] = 2*work.frac_121674190848;
  work.KKT[195] = 2*work.frac_121674190848;
  work.KKT[196] = 2*work.frac_121674190848;
  work.KKT[197] = 2*work.frac_121674190848;
  work.KKT[198] = 2*work.frac_121674190848;
  work.KKT[199] = 2*work.frac_121674190848;
  work.KKT[200] = 2*work.frac_121674190848;
  work.KKT[201] = 2*work.frac_121674190848;
  work.KKT[202] = 2*work.frac_121674190848;
  work.KKT[203] = 2*work.frac_121674190848;
  work.KKT[204] = 2*work.frac_121674190848;
  work.KKT[205] = 2*work.frac_121674190848;
  work.KKT[206] = 2*work.frac_121674190848;
  work.KKT[207] = 2*work.frac_121674190848;
  work.KKT[208] = 2*work.frac_121674190848;
  work.KKT[209] = 2*work.frac_121674190848;
  work.KKT[210] = 2*work.frac_121674190848;
  work.KKT[211] = 2*work.frac_121674190848;
  work.KKT[212] = 2*work.frac_121674190848;
  work.KKT[213] = 2*work.frac_121674190848;
  work.KKT[214] = 2*work.frac_121674190848;
  work.KKT[215] = 2*work.frac_121674190848;
  work.KKT[216] = 2*work.frac_121674190848;
  work.KKT[217] = 2*work.frac_121674190848;
  work.KKT[218] = 2*work.frac_121674190848;
  work.KKT[219] = 2*work.frac_121674190848;
  work.KKT[220] = 2*work.frac_121674190848;
  work.KKT[221] = 2*work.frac_121674190848;
  work.KKT[222] = 2*work.frac_121674190848;
  work.KKT[223] = 2*work.frac_121674190848;
  work.KKT[224] = 2*work.frac_121674190848;
  work.KKT[225] = 2*work.frac_121674190848;
  work.KKT[226] = 2*work.frac_121674190848;
  work.KKT[227] = 2*work.frac_121674190848;
  work.KKT[228] = 2*work.frac_121674190848;
  work.KKT[229] = 2*work.frac_121674190848;
  work.KKT[230] = 2*work.frac_121674190848;
  work.KKT[231] = 2*work.frac_121674190848;
  work.KKT[232] = 2*work.frac_121674190848;
  work.KKT[233] = 2*work.frac_121674190848;
  work.KKT[234] = 2*work.frac_121674190848;
  work.KKT[235] = 2*work.frac_121674190848;
  work.KKT[236] = 2*work.frac_121674190848;
  work.KKT[237] = 2*work.frac_121674190848;
  work.KKT[238] = 2*work.frac_121674190848;
  work.KKT[239] = 2*work.frac_121674190848;
  work.KKT[240] = 2*work.frac_121674190848;
  work.KKT[241] = 2*work.frac_121674190848;
  work.KKT[242] = 2*work.frac_121674190848;
  work.KKT[243] = 2*work.frac_121674190848;
  work.KKT[244] = 2*work.frac_121674190848;
  work.KKT[245] = 2*work.frac_121674190848;
  work.KKT[246] = 2*work.frac_121674190848;
  work.KKT[247] = 2*work.frac_121674190848;
  work.KKT[248] = 2*work.frac_121674190848;
  work.KKT[249] = 2*work.frac_121674190848;
  work.KKT[250] = 2*work.frac_121674190848;
  work.KKT[251] = 2*work.frac_121674190848;
  work.KKT[252] = 2*work.frac_121674190848;
  work.KKT[253] = 2*work.frac_121674190848;
  work.KKT[254] = 2*work.frac_121674190848;
  work.KKT[255] = 2*work.frac_121674190848;
  work.KKT[256] = 2*work.frac_121674190848;
  work.KKT[257] = 2*work.frac_121674190848;
  work.KKT[258] = 2*work.frac_121674190848;
  work.KKT[259] = 2*work.frac_121674190848;
  work.KKT[260] = 2*work.frac_121674190848;
  work.KKT[261] = 2*work.frac_121674190848;
  work.KKT[262] = 2*work.frac_121674190848;
  work.KKT[263] = 2*work.frac_121674190848;
  work.KKT[264] = 2*work.frac_121674190848;
  work.KKT[265] = 2*work.frac_121674190848;
  work.KKT[266] = 2*work.frac_121674190848;
  work.KKT[267] = 2*work.frac_121674190848;
  work.KKT[268] = 2*work.frac_121674190848;
  work.KKT[269] = 2*work.frac_121674190848;
  work.KKT[270] = 2*work.frac_121674190848;
  work.KKT[271] = 2*work.frac_121674190848;
  work.KKT[272] = 2*work.frac_121674190848;
  work.KKT[273] = 2*work.frac_121674190848;
  work.KKT[274] = 2*work.frac_121674190848;
  work.KKT[275] = 2*work.frac_121674190848;
  work.KKT[276] = 2*work.frac_121674190848;
  work.KKT[277] = 2*work.frac_121674190848;
  work.KKT[278] = 2*work.frac_121674190848;
  work.KKT[279] = 2*work.frac_121674190848;
  work.KKT[280] = 2*work.frac_121674190848;
  work.KKT[281] = 2*work.frac_121674190848;
  work.KKT[282] = 2*work.frac_121674190848;
  work.KKT[283] = 2*work.frac_121674190848;
  work.KKT[284] = 2*work.frac_121674190848;
  work.KKT[285] = 2*work.frac_121674190848;
  work.KKT[286] = 2*work.frac_121674190848;
  work.KKT[287] = 2*work.frac_121674190848;
  work.KKT[288] = 2*work.frac_121674190848;
  work.KKT[289] = 2*work.frac_121674190848;
  work.KKT[290] = 2*work.frac_121674190848;
  work.KKT[291] = 2*work.frac_121674190848;
  work.KKT[292] = 2*work.frac_121674190848;
  work.KKT[293] = 2*work.frac_121674190848;
  work.KKT[294] = 2*work.frac_121674190848;
  work.KKT[295] = 2*work.frac_121674190848;
  work.KKT[296] = 2*work.frac_121674190848;
  work.KKT[297] = 2*work.frac_121674190848;
  work.KKT[298] = 2*work.frac_121674190848;
  work.KKT[299] = 2*work.frac_121674190848;
  work.KKT[300] = 2*work.frac_121674190848;
  work.KKT[301] = 2*work.frac_121674190848;
  work.KKT[302] = 2*work.frac_121674190848;
  work.KKT[303] = 2*work.frac_121674190848;
  work.KKT[304] = 2*work.frac_121674190848;
  work.KKT[305] = 2*work.frac_121674190848;
  work.KKT[306] = 2*work.frac_121674190848;
  work.KKT[307] = 2*work.frac_121674190848;
  work.KKT[308] = 2*work.frac_121674190848;
  work.KKT[309] = 2*work.frac_121674190848;
  work.KKT[310] = 2*work.frac_121674190848;
  work.KKT[311] = 2*work.frac_121674190848;
  work.KKT[312] = 2*work.frac_121674190848;
  work.KKT[313] = 2*work.frac_121674190848;
  work.KKT[314] = 2*work.frac_121674190848;
  work.KKT[315] = 2*work.frac_121674190848;
  work.KKT[316] = 2*work.frac_121674190848;
  work.KKT[317] = 2*work.frac_121674190848;
  work.KKT[318] = 2*work.frac_121674190848;
  work.KKT[319] = 2*work.frac_121674190848;
  work.KKT[320] = 2*work.frac_121674190848;
  work.KKT[321] = 2*work.frac_121674190848;
  work.KKT[322] = 2*work.frac_121674190848;
  work.KKT[323] = 2*work.frac_121674190848;
  work.KKT[324] = 2*work.frac_121674190848;
  work.KKT[325] = 2*work.frac_121674190848;
  work.KKT[326] = 2*work.frac_121674190848;
  work.KKT[327] = 2*work.frac_121674190848;
  work.KKT[328] = 2*work.frac_121674190848;
  work.KKT[329] = 2*work.frac_121674190848;
  work.KKT[330] = 2*work.frac_121674190848;
  work.KKT[331] = 2*work.frac_121674190848;
  work.KKT[332] = 2*work.frac_121674190848;
  work.KKT[333] = 2*work.frac_121674190848;
  work.KKT[334] = 2*work.frac_121674190848;
  work.KKT[335] = 2*work.frac_121674190848;
  work.KKT[336] = 2*work.frac_121674190848;
  work.KKT[337] = 2*work.frac_121674190848;
  work.KKT[338] = 2*work.frac_121674190848;
  work.KKT[339] = 2*work.frac_121674190848;
  work.KKT[340] = 2*work.frac_121674190848;
  work.KKT[341] = 2*work.frac_121674190848;
  work.KKT[342] = 2*work.frac_121674190848;
  work.KKT[343] = 2*work.frac_121674190848;
  work.KKT[344] = 2*work.frac_121674190848;
  work.KKT[345] = 2*work.frac_121674190848;
  work.KKT[346] = 2*work.frac_121674190848;
  work.KKT[347] = 2*work.frac_121674190848;
  work.KKT[348] = 2*work.frac_121674190848;
  work.KKT[349] = 2*work.frac_121674190848;
  work.KKT[350] = 2*work.frac_121674190848;
  work.KKT[351] = 2*work.frac_121674190848;
  work.KKT[352] = 2*work.frac_121674190848;
  work.KKT[353] = 2*work.frac_121674190848;
  work.KKT[354] = 2*work.frac_121674190848;
  work.KKT[355] = 2*work.frac_121674190848;
  work.KKT[356] = 2*work.frac_121674190848;
  work.KKT[357] = 2*work.frac_121674190848;
  work.KKT[358] = 2*work.frac_121674190848;
  work.KKT[359] = 2*work.frac_121674190848;
  work.KKT[360] = 2*work.frac_121674190848;
  work.KKT[361] = 2*work.frac_121674190848;
  work.KKT[362] = 2*work.frac_121674190848;
  work.KKT[363] = 2*work.frac_121674190848;
  work.KKT[364] = 2*work.frac_121674190848;
  work.KKT[365] = 2*work.frac_121674190848;
  work.KKT[366] = 2*work.frac_121674190848;
  work.KKT[367] = 2*work.frac_121674190848;
  work.KKT[368] = 2*work.frac_121674190848;
  work.KKT[369] = 2*work.frac_121674190848;
  work.KKT[370] = 2*work.frac_121674190848;
  work.KKT[371] = 2*work.frac_121674190848;
  work.KKT[372] = 2*work.frac_121674190848;
  work.KKT[373] = 2*work.frac_121674190848;
  work.KKT[374] = 2*work.frac_121674190848;
  work.KKT[375] = 2*work.frac_121674190848;
  work.KKT[376] = 2*work.frac_121674190848;
  work.KKT[377] = 2*work.frac_121674190848;
  work.KKT[378] = 2*work.frac_121674190848;
  work.KKT[379] = 2*work.frac_121674190848;
  work.KKT[380] = 2*work.frac_121674190848;
  work.KKT[381] = 2*work.frac_121674190848;
  work.KKT[382] = 2*work.frac_121674190848;
  work.KKT[383] = 2*work.frac_121674190848;
  work.KKT[384] = 2*work.frac_121674190848;
  work.KKT[385] = 2*work.frac_121674190848;
  work.KKT[386] = 2*work.frac_121674190848;
  work.KKT[387] = 2*work.frac_121674190848;
  work.KKT[388] = 2*work.frac_121674190848;
  work.KKT[389] = 2*work.frac_121674190848;
  work.KKT[390] = 2*work.frac_121674190848;
  work.KKT[391] = 2*work.frac_121674190848;
  work.KKT[392] = 2*work.frac_121674190848;
  work.KKT[393] = 2*work.frac_121674190848;
  work.KKT[394] = 2*work.frac_121674190848;
  work.KKT[395] = 2*work.frac_121674190848;
  work.KKT[396] = 2*work.frac_121674190848;
  work.KKT[397] = 2*work.frac_121674190848;
  work.KKT[398] = 2*work.frac_121674190848;
  work.KKT[399] = 2*work.frac_121674190848;
  work.KKT[400] = 2*work.frac_121674190848;
  work.KKT[401] = work.s_inv_z[0];
  work.KKT[403] = work.s_inv_z[1];
  work.KKT[402] = 1;
  work.KKT[404] = 1;
  work.KKT[405] = work.block_33[0];
  work.KKT[409] = work.block_33[0];
  work.KKT[406] = -1;
  work.KKT[408] = 1;
}

//testsolver.cpp
/* Produced by CVXGEN, 2015-03-30 04:02:40 -0400.  */
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
  params.caseNumber = numberOfCases;
  params.contNum[0] = 0.0;
  params.c2[0] = cost2;
  params.c1[0] = cost1;
  params.c0[0] = cost0;
  params.rho[0] = 1.0;
  params.PgMin[0] = PgenMin;
  params.PgMax[0] = PgenMax;
for ( int i = 0; i <= 400; ++i ) {
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
  /*for ( int i = 0; i <= 3; ++i ) {
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
 return *Piterate;
}

double Gensolver::getObj(void) {
 return (params.c2[0])*(*Piterate)*(*Piterate)+(params.c1[0])*(*Piterate)+(params.c0[0]);
}

double *Gensolver::getThetaPtr(void){
Thiterate = (vars.Thetag);
return Thiterate;
}

/*array<double, 4> Gensolver::getThetaSol(void) {
for ( int i = 0; i <= 3; ++i ) {
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
