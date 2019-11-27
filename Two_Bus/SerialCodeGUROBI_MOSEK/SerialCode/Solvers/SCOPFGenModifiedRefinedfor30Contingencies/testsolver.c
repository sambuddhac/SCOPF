/* Produced by CVXGEN, 2015-09-15 18:49:39 -0400.  */
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
  params.ones[4] = -1.7941311867966805;
  params.ones[5] = -0.23676062539745413;
  params.ones[6] = -1.8804951564857322;
  params.ones[7] = -0.17266710242115568;
  params.ones[8] = 0.596576190459043;
  params.ones[9] = -0.8860508694080989;
  params.ones[10] = 0.7050196079205251;
  params.ones[11] = 0.3634512696654033;
  params.ones[12] = -1.9040724704913385;
  params.ones[13] = 0.23541635196352795;
  params.ones[14] = -0.9629902123701384;
  params.ones[15] = -0.3395952119597214;
  params.ones[16] = -0.865899672914725;
  params.ones[17] = 0.7725516732519853;
  params.ones[18] = -0.23818512931704205;
  params.ones[19] = -1.372529046100147;
  params.ones[20] = 0.17859607212737894;
  params.ones[21] = 1.1212590580454682;
  params.ones[22] = -0.774545870495281;
  params.ones[23] = -1.1121684642712744;
  params.ones[24] = -0.44811496977740495;
  params.ones[25] = 1.7455345994417217;
  params.ones[26] = 1.9039816898917352;
  params.ones[27] = 0.6895347036512547;
  params.ones[28] = 1.6113364341535923;
  params.ones[29] = 1.383003485172717;
  params.ones[30] = -0.48802383468444344;
  params.Pg_N_init[0] = -1.631131964513103;
  params.Pg_N_init[1] = 0.6136436100941447;
  params.Pg_N_init[2] = 0.2313630495538037;
  params.Pg_N_init[3] = -0.5537409477496875;
  params.Pg_N_init[4] = -1.0997819806406723;
  params.Pg_N_init[5] = -0.3739203344950055;
  params.Pg_N_init[6] = -0.12423900520332376;
  params.Pg_N_init[7] = -0.923057686995755;
  params.Pg_N_init[8] = -0.8328289030982696;
  params.Pg_N_init[9] = -0.16925440270808823;
  params.Pg_N_init[10] = 1.442135651787706;
  params.Pg_N_init[11] = 0.34501161787128565;
  params.Pg_N_init[12] = -0.8660485502711608;
  params.Pg_N_init[13] = -0.8880899735055947;
  params.Pg_N_init[14] = -0.1815116979122129;
  params.Pg_N_init[15] = -1.17835862158005;
  params.Pg_N_init[16] = -1.1944851558277074;
  params.Pg_N_init[17] = 0.05614023926976763;
  params.Pg_N_init[18] = -1.6510825248767813;
  params.Pg_N_init[19] = -0.06565787059365391;
  params.Pg_N_init[20] = -0.5512951504486665;
  params.Pg_N_init[21] = 0.8307464872626844;
  params.Pg_N_init[22] = 0.9869848924080182;
  params.Pg_N_init[23] = 0.7643716874230573;
  params.Pg_N_init[24] = 0.7567216550196565;
  params.Pg_N_init[25] = -0.5055995034042868;
  params.Pg_N_init[26] = 0.6725392189410702;
  params.Pg_N_init[27] = -0.6406053441727284;
  params.Pg_N_init[28] = 0.29117547947550015;
  params.Pg_N_init[29] = -0.6967713677405021;
  params.Pg_N_init[30] = -0.21941980294587182;
  params.Pg_N_avg[0] = -1.753884276680243;
  params.Pg_N_avg[1] = -1.0292983112626475;
  params.Pg_N_avg[2] = 1.8864104246942706;
  params.Pg_N_avg[3] = -1.077663182579704;
  params.Pg_N_avg[4] = 0.7659100437893209;
  params.Pg_N_avg[5] = 0.6019074328549583;
  params.Pg_N_avg[6] = 0.8957565577499285;
  params.Pg_N_avg[7] = -0.09964555746227477;
  params.Pg_N_avg[8] = 0.38665509840745127;
  params.Pg_N_avg[9] = -1.7321223042686946;
  params.Pg_N_avg[10] = -1.7097514487110663;
  params.Pg_N_avg[11] = -1.2040958948116867;
  params.Pg_N_avg[12] = -1.3925560119658358;
  params.Pg_N_avg[13] = -1.5995826216742213;
  params.Pg_N_avg[14] = -1.4828245415645833;
  params.Pg_N_avg[15] = 0.21311092723061398;
  params.Pg_N_avg[16] = -1.248740700304487;
  params.Pg_N_avg[17] = 1.808404972124833;
  params.Pg_N_avg[18] = 0.7264471152297065;
  params.Pg_N_avg[19] = 0.16407869343908477;
  params.Pg_N_avg[20] = 0.8287224032315907;
  params.Pg_N_avg[21] = -0.9444533161899464;
  params.Pg_N_avg[22] = 1.7069027370149112;
  params.Pg_N_avg[23] = 1.3567722311998827;
  params.Pg_N_avg[24] = 0.9052779937121489;
  params.Pg_N_avg[25] = -0.07904017565835986;
  params.Pg_N_avg[26] = 1.3684127435065871;
  params.Pg_N_avg[27] = 0.979009293697437;
  params.Pg_N_avg[28] = 0.6413036255984501;
  params.Pg_N_avg[29] = 1.6559010680237511;
  params.Pg_N_avg[30] = 0.5346622551502991;
  params.ug_N[0] = -0.5362376605895625;
  params.ug_N[1] = 0.2113782926017822;
  params.ug_N[2] = -1.2144776931994525;
  params.ug_N[3] = -1.2317108144255875;
  params.ug_N[4] = 0.9026784957312834;
  params.ug_N[5] = 1.1397468137245244;
  params.ug_N[6] = 1.8883934547350631;
  params.ug_N[7] = 1.4038856681660068;
  params.ug_N[8] = 0.17437730638329096;
  params.ug_N[9] = -1.6408365219077408;
  params.ug_N[10] = -0.04450702153554875;
  params.ug_N[11] = 1.7117453902485025;
  params.ug_N[12] = 1.1504727980139053;
  params.ug_N[13] = -0.05962309578364744;
  params.ug_N[14] = -0.1788825540764547;
  params.ug_N[15] = -1.1280569263625857;
  params.ug_N[16] = -1.2911464767927057;
  params.ug_N[17] = -1.7055053231225696;
  params.ug_N[18] = 1.56957275034837;
  params.ug_N[19] = 0.5607064675962357;
  params.ug_N[20] = -1.4266707301147146;
  params.ug_N[21] = -0.3434923211351708;
  params.ug_N[22] = -1.8035643024085055;
  params.ug_N[23] = -1.1625066019105454;
  params.ug_N[24] = 0.9228324965161532;
  params.ug_N[25] = 0.6044910817663975;
  params.ug_N[26] = -0.0840868104920891;
  params.ug_N[27] = -0.900877978017443;
  params.ug_N[28] = 0.608892500264739;
  params.ug_N[29] = 1.8257980452695217;
  params.ug_N[30] = -0.25791777529922877;
  params.Vg_N_avg[0] = -1.7194699796493191;
  params.Vg_N_avg[1] = -1.7690740487081298;
  params.Vg_N_avg[2] = -1.6685159248097703;
  params.Vg_N_avg[3] = 1.8388287490128845;
  params.Vg_N_avg[4] = 0.16304334474597537;
  params.Vg_N_avg[5] = 1.3498497306788897;
  params.Vg_N_avg[6] = -1.3198658230514613;
  params.Vg_N_avg[7] = -0.9586197090843394;
  params.Vg_N_avg[8] = 0.7679100474913709;
  params.Vg_N_avg[9] = 1.5822813125679343;
  params.Vg_N_avg[10] = -0.6372460621593619;
  params.Vg_N_avg[11] = -1.741307208038867;
  params.Vg_N_avg[12] = 1.456478677642575;
  params.Vg_N_avg[13] = -0.8365102166820959;
  params.Vg_N_avg[14] = 0.9643296255982503;
  params.Vg_N_avg[15] = -1.367865381194024;
  params.Vg_N_avg[16] = 0.7798537405635035;
  params.Vg_N_avg[17] = 1.3656784761245926;
  params.Vg_N_avg[18] = 0.9086083149868371;
  params.Vg_N_avg[19] = -0.5635699005460344;
  params.Vg_N_avg[20] = 0.9067590059607915;
  params.Vg_N_avg[21] = -1.4421315032701587;
  params.Vg_N_avg[22] = -0.7447235390671119;
  params.Vg_N_avg[23] = -0.32166897326822186;
  params.Vg_N_avg[24] = 1.5088481557772684;
  params.Vg_N_avg[25] = -1.385039165715428;
  params.Vg_N_avg[26] = 1.5204991609972622;
  params.Vg_N_avg[27] = 1.1958572768832156;
  params.Vg_N_avg[28] = 1.8864971883119228;
  params.Vg_N_avg[29] = -0.5291880667861584;
  params.Vg_N_avg[30] = -1.1802409243688836;
  params.Thetag_N_avg[0] = -1.037718718661604;
  params.Thetag_N_avg[1] = 1.3114512056856835;
  params.Thetag_N_avg[2] = 1.8609125943756615;
  params.Thetag_N_avg[3] = 0.7952399935216938;
  params.Thetag_N_avg[4] = -0.07001183290468038;
  params.Thetag_N_avg[5] = -0.8518009412754686;
  params.Thetag_N_avg[6] = 1.3347515373726386;
  params.Thetag_N_avg[7] = 1.4887180335977037;
  params.Thetag_N_avg[8] = -1.6314736327976336;
  params.Thetag_N_avg[9] = -1.1362021159208933;
  params.Thetag_N_avg[10] = 1.327044361831466;
  params.Thetag_N_avg[11] = 1.3932155883179842;
  params.Thetag_N_avg[12] = -0.7413880049440107;
  params.Thetag_N_avg[13] = -0.8828216126125747;
  params.Thetag_N_avg[14] = -0.27673991192616;
  params.Thetag_N_avg[15] = 0.15778600105866714;
  params.Thetag_N_avg[16] = -1.6177327399735457;
  params.Thetag_N_avg[17] = 1.3476485548544606;
  params.Thetag_N_avg[18] = 0.13893948140528378;
  params.Thetag_N_avg[19] = 1.0998712601636944;
  params.Thetag_N_avg[20] = -1.0766549376946926;
  params.Thetag_N_avg[21] = 1.8611734044254629;
  params.Thetag_N_avg[22] = 1.0041092292735172;
  params.Thetag_N_avg[23] = -0.6276245424321543;
  params.Thetag_N_avg[24] = 1.794110587839819;
  params.Thetag_N_avg[25] = 0.8020471158650913;
  params.Thetag_N_avg[26] = 1.362244341944948;
  params.Thetag_N_avg[27] = -1.8180107765765245;
  params.Thetag_N_avg[28] = -1.7774338357932473;
  params.Thetag_N_avg[29] = 0.9709490941985153;
  params.Thetag_N_avg[30] = -0.7812542682064318;
  params.vg_N[0] = 0.0671374633729811;
  params.vg_N[1] = -1.374950305314906;
  params.vg_N[2] = 1.9118096386279388;
  params.vg_N[3] = 0.011004190697677885;
  params.vg_N[4] = 1.3160043138989015;
  params.vg_N[5] = -1.7038488148800144;
  params.vg_N[6] = -0.08433819112864738;
  params.vg_N[7] = -1.7508820783768964;
  params.vg_N[8] = 1.536965724350949;
  params.vg_N[9] = -0.21675928514816478;
  params.vg_N[10] = -1.725800326952653;
  params.vg_N[11] = -1.6940148707361717;
  params.vg_N[12] = 0.15517063201268;
  params.vg_N[13] = -1.697734381979077;
  params.vg_N[14] = -1.264910727950229;
  params.vg_N[15] = -0.2545716633339441;
  params.vg_N[16] = -0.008868675926170244;
  params.vg_N[17] = 0.3332476609670296;
  params.vg_N[18] = 0.48205072561962936;
  params.vg_N[19] = -0.5087540014293261;
  params.vg_N[20] = 0.4749463319223195;
  params.vg_N[21] = -1.371021366459455;
  params.vg_N[22] = -0.8979660982652256;
  params.vg_N[23] = 1.194873082385242;
  params.vg_N[24] = -1.3876427970939353;
  params.vg_N[25] = -1.106708108457053;
  params.vg_N[26] = -1.0280872812241797;
  params.vg_N[27] = -0.08197078070773234;
  params.vg_N[28] = -1.9970179118324083;
  params.vg_N[29] = -1.878754557910134;
  params.vg_N[30] = -0.15380739340877803;
  params.PgMin[0] = 0.32504136973303854;
  params.PgMax[0] = 1.3590036075465703;
}
