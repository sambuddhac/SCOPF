/* Produced by CVXGEN, 2015-09-15 18:04:40 -0400.  */
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
  params.Pg_N_init[0] = -1.497658758144655;
  params.Pg_N_init[1] = -1.171028487447253;
  params.Pg_N_avg[0] = -1.7941311867966805;
  params.Pg_N_avg[1] = -0.23676062539745413;
  params.ug_N[0] = -1.8804951564857322;
  params.ug_N[1] = -0.17266710242115568;
  params.Vg_N_avg[0] = 0.596576190459043;
  params.Vg_N_avg[1] = -0.8860508694080989;
  params.Thetag_N_avg[0] = 0.7050196079205251;
  params.Thetag_N_avg[1] = 0.3634512696654033;
  params.vg_N[0] = -1.9040724704913385;
  params.vg_N[1] = 0.23541635196352795;
  params.PgMin[0] = 0.5185048938149308;
  params.PgMax[0] = 0.8302023940201393;
}
