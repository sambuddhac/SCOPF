/* Produced by CVXGEN, 2017-08-04 19:30:31 -0400.  */
/* CVXGEN is Copyright (C) 2006-2017 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2017 Jacob Mattingley. */
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
  params.betaSC[0] = 1.021655210395326;
  params.PgAPPSC[0] = 1.5717878173906188;
  params.gammaSC[0] = 1.7925861778668761;
  params.BSC[0] = -1.497658758144655;
  params.lambda_2SC[0] = -1.171028487447253;
  params.rho[0] = 0.10293440660165976;
  params.Pg_N_init[0] = -0.23676062539745413;
  params.Pg_N_avg[0] = -1.8804951564857322;
  params.ug_N[0] = -0.17266710242115568;
  params.Vg_N_avg[0] = 0.596576190459043;
  params.Thetag_N_avg[0] = -0.8860508694080989;
  params.vg_N[0] = 0.7050196079205251;
  params.PgMin[0] = 1.1817256348327017;
  params.PgMax[0] = 0.04796376475433073;
}
