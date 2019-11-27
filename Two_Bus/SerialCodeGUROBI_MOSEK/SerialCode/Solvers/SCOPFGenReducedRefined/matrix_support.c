/* Produced by CVXGEN, 2015-02-06 22:35:37 -0500.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: matrix_support.c. */
/* Description: Support functions for matrix multiplication and vector filling. */
#include "solver.h"
void multbymA(double *lhs, double *rhs) {
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
void multbymAT(double *lhs, double *rhs) {
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
  lhs[12] = 0;
  lhs[13] = 0;
  lhs[14] = 0;
  lhs[15] = 0;
  lhs[16] = 0;
  lhs[17] = 0;
  lhs[18] = 0;
  lhs[19] = 0;
  lhs[20] = 0;
}
void multbyP(double *lhs, double *rhs) {
  /* TODO use the fact that P is symmetric? */
  /* TODO check doubling / half factor etc. */
  lhs[0] = rhs[0]*(2*(params.c2[0]+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848));
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
}
void fillq(void) {
  work.q[0] = params.c1[0]+2*(-params.Pg_N_init[0]+params.Pg_N_avg[0]+params.ug_N[0])*work.frac_121674190848+2*(-params.Pg_N_init[1]+params.Pg_N_avg[1]+params.ug_N[1])*work.frac_121674190848+2*(-params.Pg_N_init[2]+params.Pg_N_avg[2]+params.ug_N[2])*work.frac_121674190848+2*(-params.Pg_N_init[3]+params.Pg_N_avg[3]+params.ug_N[3])*work.frac_121674190848+2*(-params.Pg_N_init[4]+params.Pg_N_avg[4]+params.ug_N[4])*work.frac_121674190848+2*(-params.Pg_N_init[5]+params.Pg_N_avg[5]+params.ug_N[5])*work.frac_121674190848+2*(-params.Pg_N_init[6]+params.Pg_N_avg[6]+params.ug_N[6])*work.frac_121674190848+2*(-params.Pg_N_init[7]+params.Pg_N_avg[7]+params.ug_N[7])*work.frac_121674190848+2*(-params.Pg_N_init[8]+params.Pg_N_avg[8]+params.ug_N[8])*work.frac_121674190848+2*(-params.Pg_N_init[9]+params.Pg_N_avg[9]+params.ug_N[9])*work.frac_121674190848;
  work.q[1] = 0;
  work.q[2] = 0;
  work.q[3] = 0;
  work.q[4] = 0;
  work.q[5] = 0;
  work.q[6] = 0;
  work.q[7] = 0;
  work.q[8] = 0;
  work.q[9] = 0;
  work.q[10] = 0;
  work.q[11] = 0;
  work.q[12] = 0;
  work.q[13] = 0;
  work.q[14] = 0;
  work.q[15] = 0;
  work.q[16] = 0;
  work.q[17] = 0;
  work.q[18] = 0;
  work.q[19] = 0;
  work.q[20] = 0;
}
void fillh(void) {
  work.h[0] = -params.PgMin[0];
  work.h[1] = params.PgMax[0];
}
void fillb(void) {
  work.b[0] = -(-params.Vg_N_avg[0]-params.Thetag_N_avg[0]+params.vg_N[0]);
  work.b[1] = -(-params.Vg_N_avg[1]-params.Thetag_N_avg[1]+params.vg_N[1]);
  work.b[2] = -(-params.Vg_N_avg[2]-params.Thetag_N_avg[2]+params.vg_N[2]);
  work.b[3] = -(-params.Vg_N_avg[3]-params.Thetag_N_avg[3]+params.vg_N[3]);
  work.b[4] = -(-params.Vg_N_avg[4]-params.Thetag_N_avg[4]+params.vg_N[4]);
  work.b[5] = -(-params.Vg_N_avg[5]-params.Thetag_N_avg[5]+params.vg_N[5]);
  work.b[6] = -(-params.Vg_N_avg[6]-params.Thetag_N_avg[6]+params.vg_N[6]);
  work.b[7] = -(-params.Vg_N_avg[7]-params.Thetag_N_avg[7]+params.vg_N[7]);
  work.b[8] = -(-params.Vg_N_avg[8]-params.Thetag_N_avg[8]+params.vg_N[8]);
  work.b[9] = -(-params.Vg_N_avg[9]-params.Thetag_N_avg[9]+params.vg_N[9]);
}
void pre_ops(void) {
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
