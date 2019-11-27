/* Produced by CVXGEN, 2015-09-15 18:19:17 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: testsolver.c. */
/* Description: Basic test harness for solver.c. */
#include "solver.h"
Vars vars;
Params params;
Workspace work;
Settings settings;
#define NUMTESTS 0
int main(int argc, char **argv) {
  int num_iters;
#if (NUMTESTS > 0)
  int i;
  double time;
  double time_per;
#endif
  set_defaults();
  setup_indexing();
  load_default_data();
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
  return 0;
}
void load_default_data(void) {
  params.c2[0] = 1.101595805149151;
  params.c1[0] = 1.4162956452362097;
  params.c0[0] = 0.5818094778258887;
  params.rho[0] = 1.021655210395326;
  params.ones[0] = 1.5717878173906188;
  params.ones[1] = 1.5851723557337523;
  params.ones[2] = -1.497658758144655;
  params.ones[3] = -1.171028487447253;
  params.Pg_N_init[0] = -1.7941311867966805;
  params.Pg_N_init[1] = -0.23676062539745413;
  params.Pg_N_init[2] = -1.8804951564857322;
  params.Pg_N_init[3] = -0.17266710242115568;
  params.Pg_N_avg[0] = 0.596576190459043;
  params.Pg_N_avg[1] = -0.8860508694080989;
  params.Pg_N_avg[2] = 0.7050196079205251;
  params.Pg_N_avg[3] = 0.3634512696654033;
  params.ug_N[0] = -1.9040724704913385;
  params.ug_N[1] = 0.23541635196352795;
  params.ug_N[2] = -0.9629902123701384;
  params.ug_N[3] = -0.3395952119597214;
  params.Vg_N_avg[0] = -0.865899672914725;
  params.Vg_N_avg[1] = 0.7725516732519853;
  params.Vg_N_avg[2] = -0.23818512931704205;
  params.Vg_N_avg[3] = -1.372529046100147;
  params.Thetag_N_avg[0] = 0.17859607212737894;
  params.Thetag_N_avg[1] = 1.1212590580454682;
  params.Thetag_N_avg[2] = -0.774545870495281;
  params.Thetag_N_avg[3] = -1.1121684642712744;
  params.vg_N[0] = -0.44811496977740495;
  params.vg_N[1] = 1.7455345994417217;
  params.vg_N[2] = 1.9039816898917352;
  params.vg_N[3] = 0.6895347036512547;
  params.PgMin[0] = 1.8056682170767961;
  params.PgMax[0] = 1.6915017425863585;
}
