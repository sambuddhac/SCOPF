/* Produced by CVXGEN, 2017-08-04 19:28:12 -0400.  */
/* CVXGEN is Copyright (C) 2006-2017 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2017 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: ldl.c. */
/* Description: Basic test harness for solver.c. */
#include "solver.h"
/* Be sure to place ldl_solve first, so storage schemes are defined by it. */
void ldl_solve(double *target, double *var) {
  int i;
  /* Find var = (L*diag(work.d)*L') \ target, then unpermute. */
  /* Answer goes into var. */
  /* Forward substitution. */
  /* Include permutation as we retrieve from target. Use v so we can unpermute */
  /* later. */
  work.v[0] = target[1];
  work.v[1] = target[2];
  work.v[2] = target[3];
  work.v[3] = target[4]-work.L[0]*work.v[1];
  work.v[4] = target[0]-work.L[1]*work.v[3];
  work.v[5] = target[5]-work.L[2]*work.v[2]-work.L[3]*work.v[4];
  /* Diagonal scaling. Assume correctness of work.d_inv. */
  for (i = 0; i < 6; i++)
    work.v[i] *= work.d_inv[i];
  /* Back substitution */
  work.v[4] -= work.L[3]*work.v[5];
  work.v[3] -= work.L[1]*work.v[4];
  work.v[2] -= work.L[2]*work.v[5];
  work.v[1] -= work.L[0]*work.v[3];
  /* Unpermute the result, from v to var. */
  var[0] = work.v[4];
  var[1] = work.v[0];
  var[2] = work.v[1];
  var[3] = work.v[2];
  var[4] = work.v[3];
  var[5] = work.v[5];
#ifndef ZERO_LIBRARY_MODE
  if (settings.debug) {
    printf("Squared norm for solution is %.8g.\n", check_residual(target, var));
  }
#endif
}
void ldl_factor(void) {
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
  work.L[0] = (work.KKT[2])*work.d_inv[1];
  work.v[2] = work.KKT[3];
  work.d[2] = work.v[2];
  if (work.d[2] < 0)
    work.d[2] = settings.kkt_reg;
  else
    work.d[2] += settings.kkt_reg;
  work.d_inv[2] = 1/work.d[2];
  work.L[2] = (work.KKT[4])*work.d_inv[2];
  work.v[1] = work.L[0]*work.d[1];
  work.v[3] = work.KKT[5]-work.L[0]*work.v[1];
  work.d[3] = work.v[3];
  if (work.d[3] > 0)
    work.d[3] = -settings.kkt_reg;
  else
    work.d[3] -= settings.kkt_reg;
  work.d_inv[3] = 1/work.d[3];
  work.L[1] = (work.KKT[6])*work.d_inv[3];
  work.v[3] = work.L[1]*work.d[3];
  work.v[4] = work.KKT[7]-work.L[1]*work.v[3];
  work.d[4] = work.v[4];
  if (work.d[4] < 0)
    work.d[4] = settings.kkt_reg;
  else
    work.d[4] += settings.kkt_reg;
  work.d_inv[4] = 1/work.d[4];
  work.L[3] = (work.KKT[8])*work.d_inv[4];
  work.v[2] = work.L[2]*work.d[2];
  work.v[4] = work.L[3]*work.d[4];
  work.v[5] = work.KKT[9]-work.L[2]*work.v[2]-work.L[3]*work.v[4];
  work.d[5] = work.v[5];
  if (work.d[5] > 0)
    work.d[5] = -settings.kkt_reg;
  else
    work.d[5] -= settings.kkt_reg;
  work.d_inv[5] = 1/work.d[5];
#ifndef ZERO_LIBRARY_MODE
  if (settings.debug) {
    printf("Squared Frobenius for factorization is %.8g.\n", check_factorization());
  }
#endif
}
double check_factorization(void) {
  /* Returns the squared Frobenius norm of A - L*D*L'. */
  double temp, residual;
  /* Only check the lower triangle. */
  residual = 0;
  temp = work.KKT[7]-1*work.d[4]*1-work.L[1]*work.d[3]*work.L[1];
  residual += temp*temp;
  temp = work.KKT[0]-1*work.d[0]*1;
  residual += temp*temp;
  temp = work.KKT[1]-1*work.d[1]*1;
  residual += temp*temp;
  temp = work.KKT[3]-1*work.d[2]*1;
  residual += temp*temp;
  temp = work.KKT[2]-work.L[0]*work.d[1]*1;
  residual += temp*temp;
  temp = work.KKT[4]-work.L[2]*work.d[2]*1;
  residual += temp*temp;
  temp = work.KKT[5]-work.L[0]*work.d[1]*work.L[0]-1*work.d[3]*1;
  residual += temp*temp;
  temp = work.KKT[9]-work.L[2]*work.d[2]*work.L[2]-1*work.d[5]*1-work.L[3]*work.d[4]*work.L[3];
  residual += temp*temp;
  temp = work.KKT[6]-1*work.d[3]*work.L[1];
  residual += temp*temp;
  temp = work.KKT[8]-work.L[3]*work.d[4]*1;
  residual += temp*temp;
  return residual;
}
void matrix_multiply(double *result, double *source) {
  /* Finds result = A*source. */
  result[0] = work.KKT[7]*source[0]+work.KKT[6]*source[4]+work.KKT[8]*source[5];
  result[1] = work.KKT[0]*source[1];
  result[2] = work.KKT[1]*source[2]+work.KKT[2]*source[4];
  result[3] = work.KKT[3]*source[3]+work.KKT[4]*source[5];
  result[4] = work.KKT[2]*source[2]+work.KKT[5]*source[4]+work.KKT[6]*source[0];
  result[5] = work.KKT[4]*source[3]+work.KKT[9]*source[5]+work.KKT[8]*source[0];
}
double check_residual(double *target, double *multiplicand) {
  /* Returns the squared 2-norm of lhs - A*rhs. */
  /* Reuses v to find the residual. */
  int i;
  double residual;
  residual = 0;
  matrix_multiply(work.v, multiplicand);
  for (i = 0; i < 2; i++) {
    residual += (target[i] - work.v[i])*(target[i] - work.v[i]);
  }
  return residual;
}
void fill_KKT(void) {
  work.KKT[7] = 2*(params.c2[0]+work.frac_957443481600+work.frac_121674190848);
  work.KKT[0] = 2*work.frac_121674190848;
  work.KKT[1] = work.s_inv_z[0];
  work.KKT[3] = work.s_inv_z[1];
  work.KKT[2] = 1;
  work.KKT[4] = 1;
  work.KKT[5] = work.block_33[0];
  work.KKT[9] = work.block_33[0];
  work.KKT[6] = -1;
  work.KKT[8] = 1;
}
