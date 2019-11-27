/* Produced by CVXGEN, 2015-02-05 18:05:36 -0500.  */
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
  params.Pg_N_init_0[0] = 1.5717878173906188;
  params.Pg_N_avg_0[0] = 1.5851723557337523;
  params.ug_N_0[0] = -1.497658758144655;
  params.Vg_N_avg_0[0] = -1.171028487447253;
  params.Thetag_N_avg_0[0] = -1.7941311867966805;
  params.vg_N_0[0] = -0.23676062539745413;
  params.Pg_N_init_1[0] = -1.8804951564857322;
  params.Pg_N_avg_1[0] = -0.17266710242115568;
  params.ug_N_1[0] = 0.596576190459043;
  params.Vg_N_avg_1[0] = -0.8860508694080989;
  params.Thetag_N_avg_1[0] = 0.7050196079205251;
  params.vg_N_1[0] = 0.3634512696654033;
  params.Pg_N_init_2[0] = -1.9040724704913385;
  params.Pg_N_avg_2[0] = 0.23541635196352795;
  params.ug_N_2[0] = -0.9629902123701384;
  params.Vg_N_avg_2[0] = -0.3395952119597214;
  params.Thetag_N_avg_2[0] = -0.865899672914725;
  params.vg_N_2[0] = 0.7725516732519853;
  params.Pg_N_init_3[0] = -0.23818512931704205;
  params.Pg_N_avg_3[0] = -1.372529046100147;
  params.ug_N_3[0] = 0.17859607212737894;
  params.Vg_N_avg_3[0] = 1.1212590580454682;
  params.Thetag_N_avg_3[0] = -0.774545870495281;
  params.vg_N_3[0] = -1.1121684642712744;
  params.Pg_N_init_4[0] = -0.44811496977740495;
  params.Pg_N_avg_4[0] = 1.7455345994417217;
  params.ug_N_4[0] = 1.9039816898917352;
  params.Vg_N_avg_4[0] = 0.6895347036512547;
  params.Thetag_N_avg_4[0] = 1.6113364341535923;
  params.vg_N_4[0] = 1.383003485172717;
  params.Pg_N_init_5[0] = -0.48802383468444344;
  params.Pg_N_avg_5[0] = -1.631131964513103;
  params.ug_N_5[0] = 0.6136436100941447;
  params.Vg_N_avg_5[0] = 0.2313630495538037;
  params.Thetag_N_avg_5[0] = -0.5537409477496875;
  params.vg_N_5[0] = -1.0997819806406723;
  params.Pg_N_init_6[0] = -0.3739203344950055;
  params.Pg_N_avg_6[0] = -0.12423900520332376;
  params.ug_N_6[0] = -0.923057686995755;
  params.Vg_N_avg_6[0] = -0.8328289030982696;
  params.Thetag_N_avg_6[0] = -0.16925440270808823;
  params.vg_N_6[0] = 1.442135651787706;
  params.Pg_N_init_7[0] = 0.34501161787128565;
  params.Pg_N_avg_7[0] = -0.8660485502711608;
  params.ug_N_7[0] = -0.8880899735055947;
  params.Vg_N_avg_7[0] = -0.1815116979122129;
  params.Thetag_N_avg_7[0] = -1.17835862158005;
  params.vg_N_7[0] = -1.1944851558277074;
  params.Pg_N_init_8[0] = 0.05614023926976763;
  params.Pg_N_avg_8[0] = -1.6510825248767813;
  params.ug_N_8[0] = -0.06565787059365391;
  params.Vg_N_avg_8[0] = -0.5512951504486665;
  params.Thetag_N_avg_8[0] = 0.8307464872626844;
  params.vg_N_8[0] = 0.9869848924080182;
  params.Pg_N_init_9[0] = 0.7643716874230573;
  params.Pg_N_avg_9[0] = 0.7567216550196565;
  params.ug_N_9[0] = -0.5055995034042868;
  params.Vg_N_avg_9[0] = 0.6725392189410702;
  params.Thetag_N_avg_9[0] = -0.6406053441727284;
  params.vg_N_9[0] = 0.29117547947550015;
  params.Pg_N_init_10[0] = -0.6967713677405021;
  params.Pg_N_avg_10[0] = -0.21941980294587182;
  params.ug_N_10[0] = -1.753884276680243;
  params.Vg_N_avg_10[0] = -1.0292983112626475;
  params.Thetag_N_avg_10[0] = 1.8864104246942706;
  params.vg_N_10[0] = -1.077663182579704;
  params.PgMin[0] = 1.3829550218946605;
  params.PgMax[0] = 1.3009537164274791;
}
