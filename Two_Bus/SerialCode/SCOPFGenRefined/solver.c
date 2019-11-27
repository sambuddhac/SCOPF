/* Produced by CVXGEN, 2015-02-07 20:31:38 -0500.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: solver.c. */
/* Description: Main solver file. */
#include "solver.h"
double eval_gap(void) {
  int i;
  double gap;
  gap = 0;
  for (i = 0; i < 2; i++)
    gap += work.z[i]*work.s[i];
  return gap;
}
void set_defaults(void) {
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
void setup_pointers(void) {
  work.y = work.x + 203;
  work.s = work.x + 304;
  work.z = work.x + 306;
  vars.Pg = work.x + 0;
  vars.Thetag = work.x + 1;
}
void setup_indexing(void) {
  setup_pointers();
}
void set_start(void) {
  int i;
  for (i = 0; i < 203; i++)
    work.x[i] = 0;
  for (i = 0; i < 101; i++)
    work.y[i] = 0;
  for (i = 0; i < 2; i++)
    work.s[i] = (work.h[i] > 0) ? work.h[i] : settings.s_init;
  for (i = 0; i < 2; i++)
    work.z[i] = settings.z_init;
}
double eval_objv(void) {
  int i;
  double objv;
  /* Borrow space in work.rhs. */
  multbyP(work.rhs, work.x);
  objv = 0;
  for (i = 0; i < 203; i++)
    objv += work.x[i]*work.rhs[i];
  objv *= 0.5;
  for (i = 0; i < 203; i++)
    objv += work.q[i]*work.x[i];
  objv += params.c0[0]+work.quad_611769487360[0]+work.quad_445109895168[0]+work.quad_793880735744[0]+work.quad_428578906112[0]+work.quad_39707512832[0]+work.quad_355912712192[0]+work.quad_113495719936[0]+work.quad_916626804736[0]+work.quad_386017529856[0]+work.quad_727622279168[0]+work.quad_581240442880[0]+work.quad_842700124160[0]+work.quad_872940011520[0]+work.quad_580086947840[0]+work.quad_949029818368[0]+work.quad_795214823424[0]+work.quad_418522562560[0]+work.quad_241420660736[0]+work.quad_559825256448[0]+work.quad_178698563584[0]+work.quad_756597547008[0]+work.quad_568097234944[0]+work.quad_276556632064[0]+work.quad_839789318144[0]+work.quad_927809298432[0]+work.quad_648987238400[0]+work.quad_185624207360[0]+work.quad_479641735168[0]+work.quad_834754113536[0]+work.quad_396655529984[0]+work.quad_365017395200[0]+work.quad_87425662976[0]+work.quad_874261159936[0]+work.quad_121962541056[0]+work.quad_997340135424[0]+work.quad_289642164224[0]+work.quad_536349593600[0]+work.quad_854739267584[0]+work.quad_451743973376[0]+work.quad_82936446976[0]+work.quad_576470921216[0]+work.quad_768025501696[0]+work.quad_851215073280[0]+work.quad_326918287360[0]+work.quad_624884666368[0]+work.quad_606389493760[0]+work.quad_986306265088[0]+work.quad_565867876352[0]+work.quad_886306131968[0]+work.quad_434256338944[0]+work.quad_769843408896[0]+work.quad_57185656832[0]+work.quad_350448377856[0]+work.quad_808010563584[0]+work.quad_127788830720[0]+work.quad_491260510208[0]+work.quad_306715574272[0]+work.quad_142303211520[0]+work.quad_984561172480[0]+work.quad_929673043968[0]+work.quad_955213266944[0]+work.quad_555251433472[0]+work.quad_545084968960[0]+work.quad_886194884608[0]+work.quad_91799232512[0]+work.quad_674407743488[0]+work.quad_960454676480[0]+work.quad_288300408832[0]+work.quad_373385256960[0]+work.quad_519006396416[0]+work.quad_23180312576[0]+work.quad_157619949568[0]+work.quad_607977480192[0]+work.quad_249354858496[0]+work.quad_488677863424[0]+work.quad_733428326400[0]+work.quad_819114999808[0]+work.quad_825844879360[0]+work.quad_422044012544[0]+work.quad_221841866752[0]+work.quad_746695811072[0]+work.quad_175883087872[0]+work.quad_368231251968[0]+work.quad_452748496896[0]+work.quad_282607104000[0]+work.quad_79556968448[0]+work.quad_976487985152[0]+work.quad_574802628608[0]+work.quad_209265430528[0]+work.quad_265752633344[0]+work.quad_981001560064[0]+work.quad_976856121344[0]+work.quad_693392900096[0]+work.quad_413138100224[0]+work.quad_534204846080[0]+work.quad_124552839168[0]+work.quad_946600976384[0]+work.quad_506287169536[0]+work.quad_482641010688[0]+work.quad_299169103872[0]+work.quad_38191415296[0];
  return objv;
}
void fillrhs_aff(void) {
  int i;
  double *r1, *r2, *r3, *r4;
  r1 = work.rhs;
  r2 = work.rhs + 203;
  r3 = work.rhs + 205;
  r4 = work.rhs + 207;
  /* r1 = -A^Ty - G^Tz - Px - q. */
  multbymAT(r1, work.y);
  multbymGT(work.buffer, work.z);
  for (i = 0; i < 203; i++)
    r1[i] += work.buffer[i];
  multbyP(work.buffer, work.x);
  for (i = 0; i < 203; i++)
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
  for (i = 0; i < 101; i++)
    r4[i] += work.b[i];
}
void fillrhs_cc(void) {
  int i;
  double *r2;
  double *ds_aff, *dz_aff;
  double mu;
  double alpha;
  double sigma;
  double smu;
  double minval;
  r2 = work.rhs + 203;
  ds_aff = work.lhs_aff + 203;
  dz_aff = work.lhs_aff + 205;
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
  for (i = 0; i < 203; i++)
    work.rhs[i] = 0;
  for (i = 205; i < 308; i++)
    work.rhs[i] = 0;
  for (i = 0; i < 2; i++)
    r2[i] = work.s_inv[i]*(smu - ds_aff[i]*dz_aff[i]);
}
void refine(double *target, double *var) {
  int i, j;
  double *residual = work.buffer;
  double norm2;
  double *new_var = work.buffer2;
  for (j = 0; j < settings.refine_steps; j++) {
    norm2 = 0;
    matrix_multiply(residual, var);
    for (i = 0; i < 308; i++) {
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
    for (i = 0; i < 308; i++) {
      var[i] -= new_var[i];
    }
  }
#ifndef ZERO_LIBRARY_MODE
  if (settings.verbose_refinement) {
    /* Check the residual once more, but only if we're reporting it, since */
    /* it's expensive. */
    norm2 = 0;
    matrix_multiply(residual, var);
    for (i = 0; i < 308; i++) {
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
double calc_ineq_resid_squared(void) {
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
double calc_eq_resid_squared(void) {
  /* Calculates the norm ||-Ax + b||. */
  double norm2_squared;
  int i;
  /* Find -Ax. */
  multbymA(work.buffer, work.x);
  /* Add +b. */
  for (i = 0; i < 101; i++)
    work.buffer[i] += work.b[i];
  /* Now find the squared norm. */
  norm2_squared = 0;
  for (i = 0; i < 101; i++)
    norm2_squared += work.buffer[i]*work.buffer[i];
  return norm2_squared;
}
void better_start(void) {
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
  s = work.lhs_aff + 203;
  z = work.lhs_aff + 205;
  y = work.lhs_aff + 207;
  /* Just set x and y as is. */
  for (i = 0; i < 203; i++)
    work.x[i] = x[i];
  for (i = 0; i < 101; i++)
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
void fillrhs_start(void) {
  /* Fill rhs with (-q, 0, h, b). */
  int i;
  double *r1, *r2, *r3, *r4;
  r1 = work.rhs;
  r2 = work.rhs + 203;
  r3 = work.rhs + 205;
  r4 = work.rhs + 207;
  for (i = 0; i < 203; i++)
    r1[i] = -work.q[i];
  for (i = 0; i < 2; i++)
    r2[i] = 0;
  for (i = 0; i < 2; i++)
    r3[i] = work.h[i];
  for (i = 0; i < 101; i++)
    r4[i] = work.b[i];
}
long solve(void) {
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
    for (i = 0; i < 308; i++)
      work.lhs_aff[i] += work.lhs_cc[i];
    /* Rename aff to reflect its new meaning. */
    dx = work.lhs_aff;
    ds = work.lhs_aff + 203;
    dz = work.lhs_aff + 205;
    dy = work.lhs_aff + 207;
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
    for (i = 0; i < 203; i++)
      work.x[i] += alpha*dx[i];
    for (i = 0; i < 2; i++)
      work.s[i] += alpha*ds[i];
    for (i = 0; i < 2; i++)
      work.z[i] += alpha*dz[i];
    for (i = 0; i < 101; i++)
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
