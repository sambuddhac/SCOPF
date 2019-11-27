/* Produced by CVXGEN, 2015-02-06 22:35:37 -0500.  */
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
  params.Pg_N_init[0] = 1.5717878173906188;
  params.Pg_N_init[1] = 1.5851723557337523;
  params.Pg_N_init[2] = -1.497658758144655;
  params.Pg_N_init[3] = -1.171028487447253;
  params.Pg_N_init[4] = -1.7941311867966805;
  params.Pg_N_init[5] = -0.23676062539745413;
  params.Pg_N_init[6] = -1.8804951564857322;
  params.Pg_N_init[7] = -0.17266710242115568;
  params.Pg_N_init[8] = 0.596576190459043;
  params.Pg_N_init[9] = -0.8860508694080989;
  params.Pg_N_avg[0] = 0.7050196079205251;
  params.Pg_N_avg[1] = 0.3634512696654033;
  params.Pg_N_avg[2] = -1.9040724704913385;
  params.Pg_N_avg[3] = 0.23541635196352795;
  params.Pg_N_avg[4] = -0.9629902123701384;
  params.Pg_N_avg[5] = -0.3395952119597214;
  params.Pg_N_avg[6] = -0.865899672914725;
  params.Pg_N_avg[7] = 0.7725516732519853;
  params.Pg_N_avg[8] = -0.23818512931704205;
  params.Pg_N_avg[9] = -1.372529046100147;
  params.ug_N[0] = 0.17859607212737894;
  params.ug_N[1] = 1.1212590580454682;
  params.ug_N[2] = -0.774545870495281;
  params.ug_N[3] = -1.1121684642712744;
  params.ug_N[4] = -0.44811496977740495;
  params.ug_N[5] = 1.7455345994417217;
  params.ug_N[6] = 1.9039816898917352;
  params.ug_N[7] = 0.6895347036512547;
  params.ug_N[8] = 1.6113364341535923;
  params.ug_N[9] = 1.383003485172717;
  params.Vg_N_avg[0] = -0.48802383468444344;
  params.Vg_N_avg[1] = -1.631131964513103;
  params.Vg_N_avg[2] = 0.6136436100941447;
  params.Vg_N_avg[3] = 0.2313630495538037;
  params.Vg_N_avg[4] = -0.5537409477496875;
  params.Vg_N_avg[5] = -1.0997819806406723;
  params.Vg_N_avg[6] = -0.3739203344950055;
  params.Vg_N_avg[7] = -0.12423900520332376;
  params.Vg_N_avg[8] = -0.923057686995755;
  params.Vg_N_avg[9] = -0.8328289030982696;
  params.Thetag_N_avg[0] = -0.16925440270808823;
  params.Thetag_N_avg[1] = 1.442135651787706;
  params.Thetag_N_avg[2] = 0.34501161787128565;
  params.Thetag_N_avg[3] = -0.8660485502711608;
  params.Thetag_N_avg[4] = -0.8880899735055947;
  params.Thetag_N_avg[5] = -0.1815116979122129;
  params.Thetag_N_avg[6] = -1.17835862158005;
  params.Thetag_N_avg[7] = -1.1944851558277074;
  params.Thetag_N_avg[8] = 0.05614023926976763;
  params.Thetag_N_avg[9] = -1.6510825248767813;
  params.vg_N[0] = -0.06565787059365391;
  params.vg_N[1] = -0.5512951504486665;
  params.vg_N[2] = 0.8307464872626844;
  params.vg_N[3] = 0.9869848924080182;
  params.vg_N[4] = 0.7643716874230573;
  params.vg_N[5] = 0.7567216550196565;
  params.vg_N[6] = -0.5055995034042868;
  params.vg_N[7] = 0.6725392189410702;
  params.vg_N[8] = -0.6406053441727284;
  params.vg_N[9] = 0.29117547947550015;
  params.PgMin[0] = 0.651614316129749;
  params.PgMax[0] = 0.8902900985270641;
}
