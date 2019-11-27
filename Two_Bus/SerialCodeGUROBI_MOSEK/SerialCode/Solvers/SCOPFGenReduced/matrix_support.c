/* Produced by CVXGEN, 2015-02-05 18:05:35 -0500.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: matrix_support.c. */
/* Description: Support functions for matrix multiplication and vector filling. */
#include "solver.h"
void multbymA(double *lhs, double *rhs) {
}
void multbymAT(double *lhs, double *rhs) {
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
}
void multbymG(double *lhs, double *rhs) {
  lhs[0] = -rhs[0]*(-1);
  lhs[1] = -rhs[0]*(1);
}
void multbymGT(double *lhs, double *rhs) {
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
}
void multbyP(double *lhs, double *rhs) {
  /* TODO use the fact that P is symmetric? */
  /* TODO check doubling / half factor etc. */
  lhs[0] = rhs[0]*(2*(params.c2[0]+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848));
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
}
void fillq(void) {
  work.q[0] = params.c1[0]+2*(-params.Pg_N_init_0[0]+params.Pg_N_avg_0[0]+params.ug_N_0[0])*work.frac_121674190848+2*(-params.Pg_N_init_1[0]+params.Pg_N_avg_1[0]+params.ug_N_1[0])*work.frac_121674190848+2*(-params.Pg_N_init_2[0]+params.Pg_N_avg_2[0]+params.ug_N_2[0])*work.frac_121674190848+2*(-params.Pg_N_init_3[0]+params.Pg_N_avg_3[0]+params.ug_N_3[0])*work.frac_121674190848+2*(-params.Pg_N_init_4[0]+params.Pg_N_avg_4[0]+params.ug_N_4[0])*work.frac_121674190848+2*(-params.Pg_N_init_5[0]+params.Pg_N_avg_5[0]+params.ug_N_5[0])*work.frac_121674190848+2*(-params.Pg_N_init_6[0]+params.Pg_N_avg_6[0]+params.ug_N_6[0])*work.frac_121674190848+2*(-params.Pg_N_init_7[0]+params.Pg_N_avg_7[0]+params.ug_N_7[0])*work.frac_121674190848+2*(-params.Pg_N_init_8[0]+params.Pg_N_avg_8[0]+params.ug_N_8[0])*work.frac_121674190848+2*(-params.Pg_N_init_9[0]+params.Pg_N_avg_9[0]+params.ug_N_9[0])*work.frac_121674190848+2*(-params.Pg_N_init_10[0]+params.Pg_N_avg_10[0]+params.ug_N_10[0])*work.frac_121674190848;
  work.q[1] = 2*(-params.Vg_N_avg_0[0]-params.Thetag_N_avg_0[0]+params.vg_N_0[0])*work.frac_121674190848;
  work.q[2] = 2*(-params.Vg_N_avg_1[0]-params.Thetag_N_avg_1[0]+params.vg_N_1[0])*work.frac_121674190848;
  work.q[3] = 2*(-params.Vg_N_avg_2[0]-params.Thetag_N_avg_2[0]+params.vg_N_2[0])*work.frac_121674190848;
  work.q[4] = 2*(-params.Vg_N_avg_3[0]-params.Thetag_N_avg_3[0]+params.vg_N_3[0])*work.frac_121674190848;
  work.q[5] = 2*(-params.Vg_N_avg_4[0]-params.Thetag_N_avg_4[0]+params.vg_N_4[0])*work.frac_121674190848;
  work.q[6] = 2*(-params.Vg_N_avg_5[0]-params.Thetag_N_avg_5[0]+params.vg_N_5[0])*work.frac_121674190848;
  work.q[7] = 2*(-params.Vg_N_avg_6[0]-params.Thetag_N_avg_6[0]+params.vg_N_6[0])*work.frac_121674190848;
  work.q[8] = 2*(-params.Vg_N_avg_7[0]-params.Thetag_N_avg_7[0]+params.vg_N_7[0])*work.frac_121674190848;
  work.q[9] = 2*(-params.Vg_N_avg_8[0]-params.Thetag_N_avg_8[0]+params.vg_N_8[0])*work.frac_121674190848;
  work.q[10] = 2*(-params.Vg_N_avg_9[0]-params.Thetag_N_avg_9[0]+params.vg_N_9[0])*work.frac_121674190848;
  work.q[11] = 2*(-params.Vg_N_avg_10[0]-params.Thetag_N_avg_10[0]+params.vg_N_10[0])*work.frac_121674190848;
}
void fillh(void) {
  work.h[0] = -params.PgMin[0];
  work.h[1] = params.PgMax[0];
}
void fillb(void) {
}
void pre_ops(void) {
  work.frac_121674190848 = params.rho[0];
  work.frac_121674190848 /= 2;
  work.quad_600014270464[0] = (-params.Pg_N_init_0[0]+params.Pg_N_avg_0[0]+params.ug_N_0[0])*work.frac_121674190848*(-params.Pg_N_init_0[0]+params.Pg_N_avg_0[0]+params.ug_N_0[0]);
  work.quad_631547887616[0] = (-params.Vg_N_avg_0[0]-params.Thetag_N_avg_0[0]+params.vg_N_0[0])*work.frac_121674190848*(-params.Vg_N_avg_0[0]-params.Thetag_N_avg_0[0]+params.vg_N_0[0]);
  work.quad_861253439488[0] = (-params.Pg_N_init_1[0]+params.Pg_N_avg_1[0]+params.ug_N_1[0])*work.frac_121674190848*(-params.Pg_N_init_1[0]+params.Pg_N_avg_1[0]+params.ug_N_1[0]);
  work.quad_335606009856[0] = (-params.Vg_N_avg_1[0]-params.Thetag_N_avg_1[0]+params.vg_N_1[0])*work.frac_121674190848*(-params.Vg_N_avg_1[0]-params.Thetag_N_avg_1[0]+params.vg_N_1[0]);
  work.quad_419630354432[0] = (-params.Pg_N_init_2[0]+params.Pg_N_avg_2[0]+params.ug_N_2[0])*work.frac_121674190848*(-params.Pg_N_init_2[0]+params.Pg_N_avg_2[0]+params.ug_N_2[0]);
  work.quad_300112478208[0] = (-params.Vg_N_avg_2[0]-params.Thetag_N_avg_2[0]+params.vg_N_2[0])*work.frac_121674190848*(-params.Vg_N_avg_2[0]-params.Thetag_N_avg_2[0]+params.vg_N_2[0]);
  work.quad_722335502336[0] = (-params.Pg_N_init_3[0]+params.Pg_N_avg_3[0]+params.ug_N_3[0])*work.frac_121674190848*(-params.Pg_N_init_3[0]+params.Pg_N_avg_3[0]+params.ug_N_3[0]);
  work.quad_863528128512[0] = (-params.Vg_N_avg_3[0]-params.Thetag_N_avg_3[0]+params.vg_N_3[0])*work.frac_121674190848*(-params.Vg_N_avg_3[0]-params.Thetag_N_avg_3[0]+params.vg_N_3[0]);
  work.quad_407892983808[0] = (-params.Pg_N_init_4[0]+params.Pg_N_avg_4[0]+params.ug_N_4[0])*work.frac_121674190848*(-params.Pg_N_init_4[0]+params.Pg_N_avg_4[0]+params.ug_N_4[0]);
  work.quad_53514031104[0] = (-params.Vg_N_avg_4[0]-params.Thetag_N_avg_4[0]+params.vg_N_4[0])*work.frac_121674190848*(-params.Vg_N_avg_4[0]-params.Thetag_N_avg_4[0]+params.vg_N_4[0]);
  work.quad_198013468672[0] = (-params.Pg_N_init_5[0]+params.Pg_N_avg_5[0]+params.ug_N_5[0])*work.frac_121674190848*(-params.Pg_N_init_5[0]+params.Pg_N_avg_5[0]+params.ug_N_5[0]);
  work.quad_48438943744[0] = (-params.Vg_N_avg_5[0]-params.Thetag_N_avg_5[0]+params.vg_N_5[0])*work.frac_121674190848*(-params.Vg_N_avg_5[0]-params.Thetag_N_avg_5[0]+params.vg_N_5[0]);
  work.quad_898365714432[0] = (-params.Pg_N_init_6[0]+params.Pg_N_avg_6[0]+params.ug_N_6[0])*work.frac_121674190848*(-params.Pg_N_init_6[0]+params.Pg_N_avg_6[0]+params.ug_N_6[0]);
  work.quad_934929342464[0] = (-params.Vg_N_avg_6[0]-params.Thetag_N_avg_6[0]+params.vg_N_6[0])*work.frac_121674190848*(-params.Vg_N_avg_6[0]-params.Thetag_N_avg_6[0]+params.vg_N_6[0]);
  work.quad_793422544896[0] = (-params.Pg_N_init_7[0]+params.Pg_N_avg_7[0]+params.ug_N_7[0])*work.frac_121674190848*(-params.Pg_N_init_7[0]+params.Pg_N_avg_7[0]+params.ug_N_7[0]);
  work.quad_183681134592[0] = (-params.Vg_N_avg_7[0]-params.Thetag_N_avg_7[0]+params.vg_N_7[0])*work.frac_121674190848*(-params.Vg_N_avg_7[0]-params.Thetag_N_avg_7[0]+params.vg_N_7[0]);
  work.quad_924824883200[0] = (-params.Pg_N_init_8[0]+params.Pg_N_avg_8[0]+params.ug_N_8[0])*work.frac_121674190848*(-params.Pg_N_init_8[0]+params.Pg_N_avg_8[0]+params.ug_N_8[0]);
  work.quad_774359400448[0] = (-params.Vg_N_avg_8[0]-params.Thetag_N_avg_8[0]+params.vg_N_8[0])*work.frac_121674190848*(-params.Vg_N_avg_8[0]-params.Thetag_N_avg_8[0]+params.vg_N_8[0]);
  work.quad_364793888768[0] = (-params.Pg_N_init_9[0]+params.Pg_N_avg_9[0]+params.ug_N_9[0])*work.frac_121674190848*(-params.Pg_N_init_9[0]+params.Pg_N_avg_9[0]+params.ug_N_9[0]);
  work.quad_831331065856[0] = (-params.Vg_N_avg_9[0]-params.Thetag_N_avg_9[0]+params.vg_N_9[0])*work.frac_121674190848*(-params.Vg_N_avg_9[0]-params.Thetag_N_avg_9[0]+params.vg_N_9[0]);
  work.quad_24379666432[0] = (-params.Pg_N_init_10[0]+params.Pg_N_avg_10[0]+params.ug_N_10[0])*work.frac_121674190848*(-params.Pg_N_init_10[0]+params.Pg_N_avg_10[0]+params.ug_N_10[0]);
  work.quad_47350718464[0] = (-params.Vg_N_avg_10[0]-params.Thetag_N_avg_10[0]+params.vg_N_10[0])*work.frac_121674190848*(-params.Vg_N_avg_10[0]-params.Thetag_N_avg_10[0]+params.vg_N_10[0]);
}
