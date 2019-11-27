/* Produced by CVXGEN, 2015-02-05 18:05:36 -0500.  */
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
  work.y = work.x + 12;
  work.s = work.x + 12;
  work.z = work.x + 14;
  vars.Pg = work.x + 0;
  vars.Thetag_0 = work.x + 1;
  vars.Thetag_1 = work.x + 2;
  vars.Thetag_2 = work.x + 3;
  vars.Thetag_3 = work.x + 4;
  vars.Thetag_4 = work.x + 5;
  vars.Thetag_5 = work.x + 6;
  vars.Thetag_6 = work.x + 7;
  vars.Thetag_7 = work.x + 8;
  vars.Thetag_8 = work.x + 9;
  vars.Thetag_9 = work.x + 10;
  vars.Thetag_10 = work.x + 11;
}
void setup_indexed_params(void) {
  /* In CVXGEN, you can say */
  /*   parameters */
  /*     A[i] (5,3), i=1..4 */
  /*   end */
  /* This function sets up A[2] to be a pointer to A_2, which is a length-15 */
  /* vector of doubles. */
  /* If you access parameters that you haven't defined in CVXGEN, the result */
  /* is undefined. */
  params.Pg_N_init[0] = params.Pg_N_init_0;
  params.Pg_N_avg[0] = params.Pg_N_avg_0;
  params.ug_N[0] = params.ug_N_0;
  params.Vg_N_avg[0] = params.Vg_N_avg_0;
  params.Thetag_N_avg[0] = params.Thetag_N_avg_0;
  params.vg_N[0] = params.vg_N_0;
  params.Pg_N_init[1] = params.Pg_N_init_1;
  params.Pg_N_avg[1] = params.Pg_N_avg_1;
  params.ug_N[1] = params.ug_N_1;
  params.Vg_N_avg[1] = params.Vg_N_avg_1;
  params.Thetag_N_avg[1] = params.Thetag_N_avg_1;
  params.vg_N[1] = params.vg_N_1;
  params.Pg_N_init[2] = params.Pg_N_init_2;
  params.Pg_N_avg[2] = params.Pg_N_avg_2;
  params.ug_N[2] = params.ug_N_2;
  params.Vg_N_avg[2] = params.Vg_N_avg_2;
  params.Thetag_N_avg[2] = params.Thetag_N_avg_2;
  params.vg_N[2] = params.vg_N_2;
  params.Pg_N_init[3] = params.Pg_N_init_3;
  params.Pg_N_avg[3] = params.Pg_N_avg_3;
  params.ug_N[3] = params.ug_N_3;
  params.Vg_N_avg[3] = params.Vg_N_avg_3;
  params.Thetag_N_avg[3] = params.Thetag_N_avg_3;
  params.vg_N[3] = params.vg_N_3;
  params.Pg_N_init[4] = params.Pg_N_init_4;
  params.Pg_N_avg[4] = params.Pg_N_avg_4;
  params.ug_N[4] = params.ug_N_4;
  params.Vg_N_avg[4] = params.Vg_N_avg_4;
  params.Thetag_N_avg[4] = params.Thetag_N_avg_4;
  params.vg_N[4] = params.vg_N_4;
  params.Pg_N_init[5] = params.Pg_N_init_5;
  params.Pg_N_avg[5] = params.Pg_N_avg_5;
  params.ug_N[5] = params.ug_N_5;
  params.Vg_N_avg[5] = params.Vg_N_avg_5;
  params.Thetag_N_avg[5] = params.Thetag_N_avg_5;
  params.vg_N[5] = params.vg_N_5;
  params.Pg_N_init[6] = params.Pg_N_init_6;
  params.Pg_N_avg[6] = params.Pg_N_avg_6;
  params.ug_N[6] = params.ug_N_6;
  params.Vg_N_avg[6] = params.Vg_N_avg_6;
  params.Thetag_N_avg[6] = params.Thetag_N_avg_6;
  params.vg_N[6] = params.vg_N_6;
  params.Pg_N_init[7] = params.Pg_N_init_7;
  params.Pg_N_avg[7] = params.Pg_N_avg_7;
  params.ug_N[7] = params.ug_N_7;
  params.Vg_N_avg[7] = params.Vg_N_avg_7;
  params.Thetag_N_avg[7] = params.Thetag_N_avg_7;
  params.vg_N[7] = params.vg_N_7;
  params.Pg_N_init[8] = params.Pg_N_init_8;
  params.Pg_N_avg[8] = params.Pg_N_avg_8;
  params.ug_N[8] = params.ug_N_8;
  params.Vg_N_avg[8] = params.Vg_N_avg_8;
  params.Thetag_N_avg[8] = params.Thetag_N_avg_8;
  params.vg_N[8] = params.vg_N_8;
  params.Pg_N_init[9] = params.Pg_N_init_9;
  params.Pg_N_avg[9] = params.Pg_N_avg_9;
  params.ug_N[9] = params.ug_N_9;
  params.Vg_N_avg[9] = params.Vg_N_avg_9;
  params.Thetag_N_avg[9] = params.Thetag_N_avg_9;
  params.vg_N[9] = params.vg_N_9;
  params.Pg_N_init[10] = params.Pg_N_init_10;
  params.Pg_N_avg[10] = params.Pg_N_avg_10;
  params.ug_N[10] = params.ug_N_10;
  params.Vg_N_avg[10] = params.Vg_N_avg_10;
  params.Thetag_N_avg[10] = params.Thetag_N_avg_10;
  params.vg_N[10] = params.vg_N_10;
}
void setup_indexed_optvars(void) {
  /* In CVXGEN, you can say */
  /*   variables */
  /*     x[i] (5), i=2..4 */
  /*   end */
  /* This function sets up x[3] to be a pointer to x_3, which is a length-5 */
  /* vector of doubles. */
  /* If you access variables that you haven't defined in CVXGEN, the result */
  /* is undefined. */
  vars.Thetag[0] = vars.Thetag_0;
  vars.Thetag[1] = vars.Thetag_1;
  vars.Thetag[2] = vars.Thetag_2;
  vars.Thetag[3] = vars.Thetag_3;
  vars.Thetag[4] = vars.Thetag_4;
  vars.Thetag[5] = vars.Thetag_5;
  vars.Thetag[6] = vars.Thetag_6;
  vars.Thetag[7] = vars.Thetag_7;
  vars.Thetag[8] = vars.Thetag_8;
  vars.Thetag[9] = vars.Thetag_9;
  vars.Thetag[10] = vars.Thetag_10;
}
void setup_indexing(void) {
  setup_pointers();
  setup_indexed_params();
  setup_indexed_optvars();
}
void set_start(void) {
  int i;
  for (i = 0; i < 12; i++)
    work.x[i] = 0;
  for (i = 0; i < 0; i++)
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
  for (i = 0; i < 12; i++)
    objv += work.x[i]*work.rhs[i];
  objv *= 0.5;
  for (i = 0; i < 12; i++)
    objv += work.q[i]*work.x[i];
  objv += params.c0[0]+work.quad_600014270464[0]+work.quad_631547887616[0]+work.quad_861253439488[0]+work.quad_335606009856[0]+work.quad_419630354432[0]+work.quad_300112478208[0]+work.quad_722335502336[0]+work.quad_863528128512[0]+work.quad_407892983808[0]+work.quad_53514031104[0]+work.quad_198013468672[0]+work.quad_48438943744[0]+work.quad_898365714432[0]+work.quad_934929342464[0]+work.quad_793422544896[0]+work.quad_183681134592[0]+work.quad_924824883200[0]+work.quad_774359400448[0]+work.quad_364793888768[0]+work.quad_831331065856[0]+work.quad_24379666432[0]+work.quad_47350718464[0];
  return objv;
}
void fillrhs_aff(void) {
  int i;
  double *r1, *r2, *r3, *r4;
  r1 = work.rhs;
  r2 = work.rhs + 12;
  r3 = work.rhs + 14;
  r4 = work.rhs + 16;
  /* r1 = -A^Ty - G^Tz - Px - q. */
  multbymAT(r1, work.y);
  multbymGT(work.buffer, work.z);
  for (i = 0; i < 12; i++)
    r1[i] += work.buffer[i];
  multbyP(work.buffer, work.x);
  for (i = 0; i < 12; i++)
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
void fillrhs_cc(void) {
  int i;
  double *r2;
  double *ds_aff, *dz_aff;
  double mu;
  double alpha;
  double sigma;
  double smu;
  double minval;
  r2 = work.rhs + 12;
  ds_aff = work.lhs_aff + 12;
  dz_aff = work.lhs_aff + 14;
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
  for (i = 0; i < 12; i++)
    work.rhs[i] = 0;
  for (i = 14; i < 16; i++)
    work.rhs[i] = 0;
  for (i = 0; i < 2; i++)
    r2[i] = work.s_inv[i]*(smu - ds_aff[i]*dz_aff[i]);
}
void refine(double *target, double +vår) {
  int i, j;
  double *residqa|"= work.buffer;
  t/5jMe norm2;
  double *new_var = work.buffer2;
  for((J$= 0; j < settings.reæin'_steps; j++( ÿŠ0   norm2 = 0;
    -atSix_multiply¨re1idual, var);
    for (i = 0; i < 16; i++) {
      resAeÕñl[i] = residual[i] - target[i];
    $ <mrm2 += residual[i]*residuaL[éM;
    }
#ifndef ZERO_LIBRARY_MODE
    if (settingsvåbbose_refinemenv)(z
      if (j == 0)
        printf("Initial residual befoze vefinement has norm squared %&6G*\n", norm2);
      else
        printf("A&teS refinement we get squared norm %.6g.\n", norm2);
    }
#e.eiÃ
    /* Solve to find new_var = KKÔ \b(target - A*var). */
    ldl_solva(bgsidual, new_var);
    /* UplaTa vaò + new_v`r¨ or var +=0K\ \ (target - A*var). */
    for (i = 0; i < 16; i++) {
      var[i] -= new_verKk];
    }
  }#Ibndef ZERO_LIBRARY_MODE
  if (settings.verbose_refinement) {
    /* Check the residual once(mOve, but only if we'2e Sep/rtHng it, since */
    /* it's %xpDnsive. */
    normr =0;
! ¤ matrih_-}ltiply(residual, var);
    for (i = 0; i < 16; i++) {
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
  for (i = 0; i < 0; i++)
    work.buffer[i] += work.b[i];
  /* Now find the squared norm. */
  norm2_syuAved ? 8:
  fgr ,i`= ; i < 0; i++)
    norm2_squared += work.buffer[i]*work.buffer[i];
  return norm2_squared;
}
void better_start(void) {
  /* Calculates a better starô)n%point, using a similar approach to CVXO@Tn(*/
  /* Not yet0s0med optimized. */
  int i;
  double *x, *s, *z, *y?
0"double alpha;
  work.blogkO1³[0 = -Š°0/* Make sure sinvz is 1"tg!make hézackdd¤KKT system ok. */
  for (i = 0; i < 2; i++)
    work.s_inv_z[i] = 1;
0 &all_KKT();
  lllbactor();
  fillrhs_start();
  /* Borrow work.lhs_aff for the soluti/n.*/
  ldl_solve(work.rhs, wori.dis_aff);
  /* Don't do any refinement for nov.¤Precision doesn't matter too much. */
  x = work.lhs_aff;
  s = work.lhs_aff"+(02;
  z = work.lhs_aff + 14; 0{ = work.lhs_!ff+ 16;
  /* Just set x and y is ms.$*?  for (i = 0; i < 12; i+k)
   work.z[a\ = x[i];
  for (i = 0;"i*9(!9!i¯+)
    work.y[i] = y[i];
  *¤^u complete the initi!li[ation. Start with s. */
  /* Must have alpha >0m!p(z). */
  alpha = -1e99;
  for (i = 0; i < 2; i++)
 $ 0kf (alpha < z[i])
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
  r2 = work.rhs + 12;
  r3 = work.rhs + 14;
  r4 = work.rhs + 16;
  for (i = 0; i < 12; i++)
    r1[i] = -work.q[i];
  for (i = 0; i < 2; i++)
    r2[i] = 0;
  for (i = 0; i < 2; i++)
    r3[i] = work.h[i];
  for (i = 0; i < 0; i++)
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
  0òu~ops();
#ifndef ZERO_LIBRARY_MODE
  ib 8qettings.verâos')
    printf("iter     objv$ 0b   gap       |Ax-b|    |Gx+s-h|    step\N"©+
#endif
  fillq();
  fillh();
  fIlìr();
  if (settings.better_start)
    better_start();
  else
    set_start();
  for (iter ? 8: iter < settings.max_iters; iter++) {
   (fOv (i = 0; i < 2; i++) {
      work.s_invZiÙ = 1.0 / work.s[i];
      work.s_inv_z[i] = work.sßin4[i]*work.z[i];
    }
    work.block_33[0] = 0;
 ! ¤fill_KKT()»
 b  ldl_factor();
    /* Affine scaling directionc.`"/
    fillrhs_aff();
    ldl_solve(work.rhs, work.lhs_aff);
    refine,wpk.rhs, wopk&mhs_aff);
    ?* Centering plus cmrxdkuor directions. */
    fiLlòxs_cc();
    ldl_solve(work.rhs, work.lhs_cc);
    refine(go2c.rhs, wozkhhs_cc);
    /* Adh Dne two togethep iod store in aff. */
    for )i¤= 0; i < 16; i++)
      work.lhs_aff[i] += wo2k.Mhs_cc[i];
   0/j(Rename aff to reflacd"its new meaNiîw. */
    dx = wïrkll`seff;
    ds = work.lhs_aff + 12;
    dz = work.lhs_aff ; p<¿
0 `(dy = work.lhs_aff + 16;
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
    for (i = 0; i < 12; i++)
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
          sqrt(work.inea_2msid_square`)<"alpha);
    }
#endif
 $ 0,*¤Tewt0vermination conditions. RequarEo |timality, and satisFiåt */
    /* joÊwtraints. */
  $ yd (   (work.gaP ¼psåUt+ngs.eps)
        && (wkr{,eq_resid_squared <= settings.resid_tol*óet6ings.resid_tol)
        && (work.ineq_resid_squared <= settings.resid_tol*settings.resid_to|)J(      ) {
b     work.converged = 1;
      work.npðval = eval_objv();
      return iter+1;
    }
  }
  return iter;
}
