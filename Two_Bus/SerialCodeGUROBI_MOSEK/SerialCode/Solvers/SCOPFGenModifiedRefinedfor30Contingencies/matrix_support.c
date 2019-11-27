/* Produced by CVXGEN, 2015-09-15 18:49:39 -0400.  */
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
}
void multbyP(double *lhs, double *rhs) {
  /* TODO use the fact that P is symmetric? */
  /* TODO check doubling / half factor etc. */
  lhs[0] = rhs[0]*(2*(params.c2[0]+work.frac_121674190848*work.quad_745157136384[0]));
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
}
void fillq(void) {
  work.q[0] = params.c1[0]+2*work.frac_121674190848*((-params.Pg_N_init[0]+params.Pg_N_avg[0]+params.ug_N[0])*params.ones[0]+(-params.Pg_N_init[1]+params.Pg_N_avg[1]+params.ug_N[1])*params.ones[1]+(-params.Pg_N_init[2]+params.Pg_N_avg[2]+params.ug_N[2])*params.ones[2]+(-params.Pg_N_init[3]+params.Pg_N_avg[3]+params.ug_N[3])*params.ones[3]+(-params.Pg_N_init[4]+params.Pg_N_avg[4]+params.ug_N[4])*params.ones[4]+(-params.Pg_N_init[5]+params.Pg_N_avg[5]+params.ug_N[5])*params.ones[5]+(-params.Pg_N_init[6]+params.Pg_N_avg[6]+params.ug_N[6])*params.ones[6]+(-params.Pg_N_init[7]+params.Pg_N_avg[7]+params.ug_N[7])*params.ones[7]+(-params.Pg_N_init[8]+params.Pg_N_avg[8]+params.ug_N[8])*params.ones[8]+(-params.Pg_N_init[9]+params.Pg_N_avg[9]+params.ug_N[9])*params.ones[9]+(-params.Pg_N_init[10]+params.Pg_N_avg[10]+params.ug_N[10])*params.ones[10]+(-params.Pg_N_init[11]+params.Pg_N_avg[11]+params.ug_N[11])*params.ones[11]+(-params.Pg_N_init[12]+params.Pg_N_avg[12]+params.ug_N[12])*params.ones[12]+(-params.Pg_N_init[13]+params.Pg_N_avg[13]+params.ug_N[13])*params.ones[13]+(-params.Pg_N_init[14]+params.Pg_N_avg[14]+params.ug_N[14])*params.ones[14]+(-params.Pg_N_init[15]+params.Pg_N_avg[15]+params.ug_N[15])*params.ones[15]+(-params.Pg_N_init[16]+params.Pg_N_avg[16]+params.ug_N[16])*params.ones[16]+(-params.Pg_N_init[17]+params.Pg_N_avg[17]+params.ug_N[17])*params.ones[17]+(-params.Pg_N_init[18]+params.Pg_N_avg[18]+params.ug_N[18])*params.ones[18]+(-params.Pg_N_init[19]+params.Pg_N_avg[19]+params.ug_N[19])*params.ones[19]+(-params.Pg_N_init[20]+params.Pg_N_avg[20]+params.ug_N[20])*params.ones[20]+(-params.Pg_N_init[21]+params.Pg_N_avg[21]+params.ug_N[21])*params.ones[21]+(-params.Pg_N_init[22]+params.Pg_N_avg[22]+params.ug_N[22])*params.ones[22]+(-params.Pg_N_init[23]+params.Pg_N_avg[23]+params.ug_N[23])*params.ones[23]+(-params.Pg_N_init[24]+params.Pg_N_avg[24]+params.ug_N[24])*params.ones[24]+(-params.Pg_N_init[25]+params.Pg_N_avg[25]+params.ug_N[25])*params.ones[25]+(-params.Pg_N_init[26]+params.Pg_N_avg[26]+params.ug_N[26])*params.ones[26]+(-params.Pg_N_init[27]+params.Pg_N_avg[27]+params.ug_N[27])*params.ones[27]+(-params.Pg_N_init[28]+params.Pg_N_avg[28]+params.ug_N[28])*params.ones[28]+(-params.Pg_N_init[29]+params.Pg_N_avg[29]+params.ug_N[29])*params.ones[29]+(-params.Pg_N_init[30]+params.Pg_N_avg[30]+params.ug_N[30])*params.ones[30]);
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
  work.quad_745157136384[0] = params.ones[0]*params.ones[0]+params.ones[1]*params.ones[1]+params.ones[2]*params.ones[2]+params.ones[3]*params.ones[3]+params.ones[4]*params.ones[4]+params.ones[5]*params.ones[5]+params.ones[6]*params.ones[6]+params.ones[7]*params.ones[7]+params.ones[8]*params.ones[8]+params.ones[9]*params.ones[9]+params.ones[10]*params.ones[10]+params.ones[11]*params.ones[11]+params.ones[12]*params.ones[12]+params.ones[13]*params.ones[13]+params.ones[14]*params.ones[14]+params.ones[15]*params.ones[15]+params.ones[16]*params.ones[16]+params.ones[17]*params.ones[17]+params.ones[18]*params.ones[18]+params.ones[19]*params.ones[19]+params.ones[20]*params.ones[20]+params.ones[21]*params.ones[21]+params.ones[22]*params.ones[22]+params.ones[23]*params.ones[23]+params.ones[24]*params.ones[24]+params.ones[25]*params.ones[25]+params.ones[26]*params.ones[26]+params.ones[27]*params.ones[27]+params.ones[28]*params.ones[28]+params.ones[29]*params.ones[29]+params.ones[30]*params.ones[30];
  work.quad_539813191680[0] = ((-params.Pg_N_init[0]+params.Pg_N_avg[0]+params.ug_N[0])*(-params.Pg_N_init[0]+params.Pg_N_avg[0]+params.ug_N[0])+(-params.Pg_N_init[1]+params.Pg_N_avg[1]+params.ug_N[1])*(-params.Pg_N_init[1]+params.Pg_N_avg[1]+params.ug_N[1])+(-params.Pg_N_init[2]+params.Pg_N_avg[2]+params.ug_N[2])*(-params.Pg_N_init[2]+params.Pg_N_avg[2]+params.ug_N[2])+(-params.Pg_N_init[3]+params.Pg_N_avg[3]+params.ug_N[3])*(-params.Pg_N_init[3]+params.Pg_N_avg[3]+params.ug_N[3])+(-params.Pg_N_init[4]+params.Pg_N_avg[4]+params.ug_N[4])*(-params.Pg_N_init[4]+params.Pg_N_avg[4]+params.ug_N[4])+(-params.Pg_N_init[5]+params.Pg_N_avg[5]+params.ug_N[5])*(-params.Pg_N_init[5]+params.Pg_N_avg[5]+params.ug_N[5])+(-params.Pg_N_init[6]+params.Pg_N_avg[6]+params.ug_N[6])*(-params.Pg_N_init[6]+params.Pg_N_avg[6]+params.ug_N[6])+(-params.Pg_N_init[7]+params.Pg_N_avg[7]+params.ug_N[7])*(-params.Pg_N_init[7]+params.Pg_N_avg[7]+params.ug_N[7])+(-params.Pg_N_init[8]+params.Pg_N_avg[8]+params.ug_N[8])*(-params.Pg_N_init[8]+params.Pg_N_avg[8]+params.ug_N[8])+(-params.Pg_N_init[9]+params.Pg_N_avg[9]+params.ug_N[9])*(-params.Pg_N_init[9]+params.Pg_N_avg[9]+params.ug_N[9])+(-params.Pg_N_init[10]+params.Pg_N_avg[10]+params.ug_N[10])*(-params.Pg_N_init[10]+params.Pg_N_avg[10]+params.ug_N[10])+(-params.Pg_N_init[11]+params.Pg_N_avg[11]+params.ug_N[11])*(-params.Pg_N_init[11]+params.Pg_N_avg[11]+params.ug_N[11])+(-params.Pg_N_init[12]+params.Pg_N_avg[12]+params.ug_N[12])*(-params.Pg_N_init[12]+params.Pg_N_avg[12]+params.ug_N[12])+(-params.Pg_N_init[13]+params.Pg_N_avg[13]+params.ug_N[13])*(-params.Pg_N_init[13]+params.Pg_N_avg[13]+params.ug_N[13])+(-params.Pg_N_init[14]+params.Pg_N_avg[14]+params.ug_N[14])*(-params.Pg_N_init[14]+params.Pg_N_avg[14]+params.ug_N[14])+(-params.Pg_N_init[15]+params.Pg_N_avg[15]+params.ug_N[15])*(-params.Pg_N_init[15]+params.Pg_N_avg[15]+params.ug_N[15])+(-params.Pg_N_init[16]+params.Pg_N_avg[16]+params.ug_N[16])*(-params.Pg_N_init[16]+params.Pg_N_avg[16]+params.ug_N[16])+(-params.Pg_N_init[17]+params.Pg_N_avg[17]+params.ug_N[17])*(-params.Pg_N_init[17]+params.Pg_N_avg[17]+params.ug_N[17])+(-params.Pg_N_init[18]+params.Pg_N_avg[18]+params.ug_N[18])*(-params.Pg_N_init[18]+params.Pg_N_avg[18]+params.ug_N[18])+(-params.Pg_N_init[19]+params.Pg_N_avg[19]+params.ug_N[19])*(-params.Pg_N_init[19]+params.Pg_N_avg[19]+params.ug_N[19])+(-params.Pg_N_init[20]+params.Pg_N_avg[20]+params.ug_N[20])*(-params.Pg_N_init[20]+params.Pg_N_avg[20]+params.ug_N[20])+(-params.Pg_N_init[21]+params.Pg_N_avg[21]+params.ug_N[21])*(-params.Pg_N_init[21]+params.Pg_N_avg[21]+params.ug_N[21])+(-params.Pg_N_init[22]+params.Pg_N_avg[22]+params.ug_N[22])*(-params.Pg_N_init[22]+params.Pg_N_avg[22]+params.ug_N[22])+(-params.Pg_N_init[23]+params.Pg_N_avg[23]+params.ug_N[23])*(-params.Pg_N_init[23]+params.Pg_N_avg[23]+params.ug_N[23])+(-params.Pg_N_init[24]+params.Pg_N_avg[24]+params.ug_N[24])*(-params.Pg_N_init[24]+params.Pg_N_avg[24]+params.ug_N[24])+(-params.Pg_N_init[25]+params.Pg_N_avg[25]+params.ug_N[25])*(-params.Pg_N_init[25]+params.Pg_N_avg[25]+params.ug_N[25])+(-params.Pg_N_init[26]+params.Pg_N_avg[26]+params.ug_N[26])*(-params.Pg_N_init[26]+params.Pg_N_avg[26]+params.ug_N[26])+(-params.Pg_N_init[27]+params.Pg_N_avg[27]+params.ug_N[27])*(-params.Pg_N_init[27]+params.Pg_N_avg[27]+params.ug_N[27])+(-params.Pg_N_init[28]+params.Pg_N_avg[28]+params.ug_N[28])*(-params.Pg_N_init[28]+params.Pg_N_avg[28]+params.ug_N[28])+(-params.Pg_N_init[29]+params.Pg_N_avg[29]+params.ug_N[29])*(-params.Pg_N_init[29]+params.Pg_N_avg[29]+params.ug_N[29])+(-params.Pg_N_init[30]+params.Pg_N_avg[30]+params.ug_N[30])*(-params.Pg_N_init[30]+params.Pg_N_avg[30]+params.ug_N[30]));
  work.quad_931161325568[0] = ((-params.Vg_N_avg[0]-params.Thetag_N_avg[0]+params.vg_N[0])*(-params.Vg_N_avg[0]-params.Thetag_N_avg[0]+params.vg_N[0])+(-params.Vg_N_avg[1]-params.Thetag_N_avg[1]+params.vg_N[1])*(-params.Vg_N_avg[1]-params.Thetag_N_avg[1]+params.vg_N[1])+(-params.Vg_N_avg[2]-params.Thetag_N_avg[2]+params.vg_N[2])*(-params.Vg_N_avg[2]-params.Thetag_N_avg[2]+params.vg_N[2])+(-params.Vg_N_avg[3]-params.Thetag_N_avg[3]+params.vg_N[3])*(-params.Vg_N_avg[3]-params.Thetag_N_avg[3]+params.vg_N[3])+(-params.Vg_N_avg[4]-params.Thetag_N_avg[4]+params.vg_N[4])*(-params.Vg_N_avg[4]-params.Thetag_N_avg[4]+params.vg_N[4])+(-params.Vg_N_avg[5]-params.Thetag_N_avg[5]+params.vg_N[5])*(-params.Vg_N_avg[5]-params.Thetag_N_avg[5]+params.vg_N[5])+(-params.Vg_N_avg[6]-params.Thetag_N_avg[6]+params.vg_N[6])*(-params.Vg_N_avg[6]-params.Thetag_N_avg[6]+params.vg_N[6])+(-params.Vg_N_avg[7]-params.Thetag_N_avg[7]+params.vg_N[7])*(-params.Vg_N_avg[7]-params.Thetag_N_avg[7]+params.vg_N[7])+(-params.Vg_N_avg[8]-params.Thetag_N_avg[8]+params.vg_N[8])*(-params.Vg_N_avg[8]-params.Thetag_N_avg[8]+params.vg_N[8])+(-params.Vg_N_avg[9]-params.Thetag_N_avg[9]+params.vg_N[9])*(-params.Vg_N_avg[9]-params.Thetag_N_avg[9]+params.vg_N[9])+(-params.Vg_N_avg[10]-params.Thetag_N_avg[10]+params.vg_N[10])*(-params.Vg_N_avg[10]-params.Thetag_N_avg[10]+params.vg_N[10])+(-params.Vg_N_avg[11]-params.Thetag_N_avg[11]+params.vg_N[11])*(-params.Vg_N_avg[11]-params.Thetag_N_avg[11]+params.vg_N[11])+(-params.Vg_N_avg[12]-params.Thetag_N_avg[12]+params.vg_N[12])*(-params.Vg_N_avg[12]-params.Thetag_N_avg[12]+params.vg_N[12])+(-params.Vg_N_avg[13]-params.Thetag_N_avg[13]+params.vg_N[13])*(-params.Vg_N_avg[13]-params.Thetag_N_avg[13]+params.vg_N[13])+(-params.Vg_N_avg[14]-params.Thetag_N_avg[14]+params.vg_N[14])*(-params.Vg_N_avg[14]-params.Thetag_N_avg[14]+params.vg_N[14])+(-params.Vg_N_avg[15]-params.Thetag_N_avg[15]+params.vg_N[15])*(-params.Vg_N_avg[15]-params.Thetag_N_avg[15]+params.vg_N[15])+(-params.Vg_N_avg[16]-params.Thetag_N_avg[16]+params.vg_N[16])*(-params.Vg_N_avg[16]-params.Thetag_N_avg[16]+params.vg_N[16])+(-params.Vg_N_avg[17]-params.Thetag_N_avg[17]+params.vg_N[17])*(-params.Vg_N_avg[17]-params.Thetag_N_avg[17]+params.vg_N[17])+(-params.Vg_N_avg[18]-params.Thetag_N_avg[18]+params.vg_N[18])*(-params.Vg_N_avg[18]-params.Thetag_N_avg[18]+params.vg_N[18])+(-params.Vg_N_avg[19]-params.Thetag_N_avg[19]+params.vg_N[19])*(-params.Vg_N_avg[19]-params.Thetag_N_avg[19]+params.vg_N[19])+(-params.Vg_N_avg[20]-params.Thetag_N_avg[20]+params.vg_N[20])*(-params.Vg_N_avg[20]-params.Thetag_N_avg[20]+params.vg_N[20])+(-params.Vg_N_avg[21]-params.Thetag_N_avg[21]+params.vg_N[21])*(-params.Vg_N_avg[21]-params.Thetag_N_avg[21]+params.vg_N[21])+(-params.Vg_N_avg[22]-params.Thetag_N_avg[22]+params.vg_N[22])*(-params.Vg_N_avg[22]-params.Thetag_N_avg[22]+params.vg_N[22])+(-params.Vg_N_avg[23]-params.Thetag_N_avg[23]+params.vg_N[23])*(-params.Vg_N_avg[23]-params.Thetag_N_avg[23]+params.vg_N[23])+(-params.Vg_N_avg[24]-params.Thetag_N_avg[24]+params.vg_N[24])*(-params.Vg_N_avg[24]-params.Thetag_N_avg[24]+params.vg_N[24])+(-params.Vg_N_avg[25]-params.Thetag_N_avg[25]+params.vg_N[25])*(-params.Vg_N_avg[25]-params.Thetag_N_avg[25]+params.vg_N[25])+(-params.Vg_N_avg[26]-params.Thetag_N_avg[26]+params.vg_N[26])*(-params.Vg_N_avg[26]-params.Thetag_N_avg[26]+params.vg_N[26])+(-params.Vg_N_avg[27]-params.Thetag_N_avg[27]+params.vg_N[27])*(-params.Vg_N_avg[27]-params.Thetag_N_avg[27]+params.vg_N[27])+(-params.Vg_N_avg[28]-params.Thetag_N_avg[28]+params.vg_N[28])*(-params.Vg_N_avg[28]-params.Thetag_N_avg[28]+params.vg_N[28])+(-params.Vg_N_avg[29]-params.Thetag_N_avg[29]+params.vg_N[29])*(-params.Vg_N_avg[29]-params.Thetag_N_avg[29]+params.vg_N[29])+(-params.Vg_N_avg[30]-params.Thetag_N_avg[30]+params.vg_N[30])*(-params.Vg_N_avg[30]-params.Thetag_N_avg[30]+params.vg_N[30]));
}
