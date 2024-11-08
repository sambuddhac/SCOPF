/* Produced by CVXGEN, 2015-09-15 19:24:07 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: util.c. */
/* Description: Common utility file for all cvxgen code. */
#include "gensolver.h"
#include <array>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;
void Gensolver::tic(void) {
  tic_timestart = clock();
}
float Gensolver::toc(void) {
  clock_t tic_timestop;
  tic_timestop = clock();
  printf("time: %8.2f.\n", (float)(tic_timestop - tic_timestart) / CLOCKS_PER_SEC);
  return (float)(tic_timestop - tic_timestart) / CLOCKS_PER_SEC;
}
float Gensolver::tocq(void) {
  clock_t tic_timestop;
  tic_timestop = clock();
  return (float)(tic_timestop - tic_timestart) / CLOCKS_PER_SEC;
}
void Gensolver::printmatrix(char *name, double *A, int m, int n, int sparse) {
  int i, j;
  printf("%s = [...\n", name);
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++)
      if ((sparse == 1) && (A[i+j*m] == 0))
        printf("         0");
      else
        printf("  % 9.4f", A[i+j*m]);
    printf(",\n");
  }
  printf("];\n");
}
double Gensolver::unif(double lower, double upper) {
  return lower + ((upper - lower)*rand())/RAND_MAX;
}
/* Next function is from numerical recipes in C. */
#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)
float Gensolver::ran1(long*idum, int reset) {
  int j;
  long k;
  static long iy=0;
  static long iv[NTAB];
  float temp;
  if (reset) {
    iy = 0;
  }
  if (*idum<=0||!iy) {
    if (-(*idum)<1)*idum=1;
    else *idum=-(*idum);
    for (j=NTAB+7; j>=0; j--) {
      k = (*idum)/IQ;
      *idum=IA*(*idum-k*IQ)-IR*k;
      if (*idum<0)*idum+=IM;
      if (j<NTAB)iv[j]=*idum;
    }
    iy = iv[0];
  }
  k = (*idum)/IQ;
  *idum = IA*(*idum-k*IQ)-IR*k;
  if (*idum<0)*idum += IM;
  j = iy/NDIV;
  iy = iv[j];
  iv[j] = *idum;
  if ((temp=AM*iy)> RNMX) return RNMX;
  else return temp;
}
/* Next function is from numerical recipes in C. */
float Gensolver::randn_internal(long *idum, int reset) {
  static int iset=0;
  static float gset;
  float fac, rsq, v1, v2;
  if (reset) {
    iset = 0;
  }
  if (iset==0) {
    do {
      v1 = 2.0*ran1(idum, reset)-1.0;
      v2 = 2.0*ran1(idum, reset)-1.0;
      rsq = v1*v1+v2*v2;
    } while(rsq >= 1.0 || rsq == 0.0);
    fac = sqrt(-2.0*log(rsq)/rsq);
    gset = v1*fac;
    iset = 1;
    return v2*fac;
  } else {
    iset = 0;
    return gset;
  }
}
double Gensolver::randn(void) {
  return randn_internal(&global_seed, 0);
}
void Gensolver::reset_rand(void) {
  srand(15);
  global_seed = 1;
  randn_internal(&global_seed, 1);
}
/* Produced by CVXGEN, 2015-09-15 19:24:07 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: testsolver.c. */
/* Description: Basic test harness for solver.c. */
Gensolver::Gensolver( int numberOfCases, double cost2, double cost1, double cost0, double PgenMax, double PgenMin ) {
  params.caseNumber = numberOfCases;
  params.contNum[0] = 0.0;
  params.c2[0] = cost2;
  params.c1[0] = cost1;
  params.c0[0] = cost0;
  params.rho[0] = 1.0;
  params.PgMin[0] = PgenMin;
  params.PgMax[0] = PgenMax;
for ( int i = 0; i <= 400; ++i ) {
  params.ones[i] = 0.0;
  params.Pg_N_init[i] = 0.0;
  params.Pg_N_avg[i] = 0.0;
  params.ug_N[i] = 0.0;
  params.Vg_N_avg[i] = 0.0;
  params.Thetag_N_avg[i] = 0.0;
  params.vg_N[i] = 0.0;
}
  global_seed = 1;
  Piterate = NULL;
  for ( int i = 0; i <= 400; ++i ) {
   Thiterate[i] = 0.0;
  }
  set_defaults();
  setup_indexing();
}
Gensolver::~Gensolver() {
}
#define NUMTESTS 0
void Gensolver::mainsolve(double gsRho, double Pgprev[], double Pgavrg[], double Pprice[], double Apriceavg[], double Aavg[], double Aprice[]) {
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
void Gensolver::load_default_data(void) {
  params.c2[0] = 1.101595805149151;
  params.c1[0] = 1.4162956452362097;
  params.c0[0] = 0.5818094778258887;
  params.rho[0] = 1.021655210395326;
  params.Pg_N_init_1[0] = 1.5717878173906188;
  params.Pg_N_avg_1[0] = 1.5851723557337523;
  params.ug_N_1[0] = -1.497658758144655;
  params.Vg_N_avg_1[0] = -1.171028487447253;
  params.Thetag_N_avg_1[0] = -1.7941311867966805;
  params.vg_N_1[0] = -0.23676062539745413;
  params.Pg_N_init_2[0] = -1.8804951564857322;
  params.Pg_N_avg_2[0] = -0.17266710242115568;
  params.ug_N_2[0] = 0.596576190459043;
  params.Vg_N_avg_2[0] = -0.8860508694080989;
  params.Thetag_N_avg_2[0] = 0.7050196079205251;
  params.vg_N_2[0] = 0.3634512696654033;
  params.Pg_N_init_3[0] = -1.9040724704913385;
  params.Pg_N_avg_3[0] = 0.23541635196352795;
  params.ug_N_3[0] = -0.9629902123701384;
  params.Vg_N_avg_3[0] = -0.3395952119597214;
  params.Thetag_N_avg_3[0] = -0.865899672914725;
  params.vg_N_3[0] = 0.7725516732519853;
  params.Pg_N_init_4[0] = -0.23818512931704205;
  params.Pg_N_avg_4[0] = -1.372529046100147;
  params.ug_N_4[0] = 0.17859607212737894;
  params.Vg_N_avg_4[0] = 1.1212590580454682;
  params.Thetag_N_avg_4[0] = -0.774545870495281;
  params.vg_N_4[0] = -1.1121684642712744;
  params.Pg_N_init_5[0] = -0.44811496977740495;
  params.Pg_N_avg_5[0] = 1.7455345994417217;
  params.ug_N_5[0] = 1.9039816898917352;
  params.Vg_N_avg_5[0] = 0.6895347036512547;
  params.Thetag_N_avg_5[0] = 1.6113364341535923;
  params.vg_N_5[0] = 1.383003485172717;
  params.Pg_N_init_6[0] = -0.48802383468444344;
  params.Pg_N_avg_6[0] = -1.631131964513103;
  params.ug_N_6[0] = 0.6136436100941447;
  params.Vg_N_avg_6[0] = 0.2313630495538037;
  params.Thetag_N_avg_6[0] = -0.5537409477496875;
  params.vg_N_6[0] = -1.0997819806406723;
  params.Pg_N_init_7[0] = -0.3739203344950055;
  params.Pg_N_avg_7[0] = -0.12423900520332376;
  params.ug_N_7[0] = -0.923057686995755;
  params.Vg_N_avg_7[0] = -0.8328289030982696;
  params.Thetag_N_avg_7[0] = -0.16925440270808823;
  params.vg_N_7[0] = 1.442135651787706;
  params.Pg_N_init_8[0] = 0.34501161787128565;
  params.Pg_N_avg_8[0] = -0.8660485502711608;
  params.ug_N_8[0] = -0.8880899735055947;
  params.Vg_N_avg_8[0] = -0.1815116979122129;
  params.Thetag_N_avg_8[0] = -1.17835862158005;
  params.vg_N_8[0] = -1.1944851558277074;
  params.Pg_N_init_9[0] = 0.05614023926976763;
  params.Pg_N_avg_9[0] = -1.6510825248767813;
  params.ug_N_9[0] = -0.06565787059365391;
  params.Vg_N_avg_9[0] = -0.5512951504486665;
  params.Thetag_N_avg_9[0] = 0.8307464872626844;
  params.vg_N_9[0] = 0.9869848924080182;
  params.Pg_N_init_10[0] = 0.7643716874230573;
  params.Pg_N_avg_10[0] = 0.7567216550196565;
  params.ug_N_10[0] = -0.5055995034042868;
  params.Vg_N_avg_10[0] = 0.6725392189410702;
  params.Thetag_N_avg_10[0] = -0.6406053441727284;
  params.vg_N_10[0] = 0.29117547947550015;
  params.Pg_N_init_11[0] = -0.6967713677405021;
  params.Pg_N_avg_11[0] = -0.21941980294587182;
  params.ug_N_11[0] = -1.753884276680243;
  params.Vg_N_avg_11[0] = -1.0292983112626475;
  params.Thetag_N_avg_11[0] = 1.8864104246942706;
  params.vg_N_11[0] = -1.077663182579704;
  params.Pg_N_init_12[0] = 0.7659100437893209;
  params.Pg_N_avg_12[0] = 0.6019074328549583;
  params.ug_N_12[0] = 0.8957565577499285;
  params.Vg_N_avg_12[0] = -0.09964555746227477;
  params.Thetag_N_avg_12[0] = 0.38665509840745127;
  params.vg_N_12[0] = -1.7321223042686946;
  params.Pg_N_init_13[0] = -1.7097514487110663;
  params.Pg_N_avg_13[0] = -1.2040958948116867;
  params.ug_N_13[0] = -1.3925560119658358;
  params.Vg_N_avg_13[0] = -1.5995826216742213;
  params.Thetag_N_avg_13[0] = -1.4828245415645833;
  params.vg_N_13[0] = 0.21311092723061398;
  params.Pg_N_init_14[0] = -1.248740700304487;
  params.Pg_N_avg_14[0] = 1.808404972124833;
  params.ug_N_14[0] = 0.7264471152297065;
  params.Vg_N_avg_14[0] = 0.16407869343908477;
  params.Thetag_N_avg_14[0] = 0.8287224032315907;
  params.vg_N_14[0] = -0.9444533161899464;
  params.Pg_N_init_15[0] = 1.7069027370149112;
  params.Pg_N_avg_15[0] = 1.3567722311998827;
  params.ug_N_15[0] = 0.9052779937121489;
  params.Vg_N_avg_15[0] = -0.07904017565835986;
  params.Thetag_N_avg_15[0] = 1.3684127435065871;
  params.vg_N_15[0] = 0.979009293697437;
  params.Pg_N_init_16[0] = 0.6413036255984501;
  params.Pg_N_avg_16[0] = 1.6559010680237511;
  params.ug_N_16[0] = 0.5346622551502991;
  params.Vg_N_avg_16[0] = -0.5362376605895625;
  params.Thetag_N_avg_16[0] = 0.2113782926017822;
  params.vg_N_16[0] = -1.2144776931994525;
  params.Pg_N_init_17[0] = -1.2317108144255875;
  params.Pg_N_avg_17[0] = 0.9026784957312834;
  params.ug_N_17[0] = 1.1397468137245244;
  params.Vg_N_avg_17[0] = 1.8883934547350631;
  params.Thetag_N_avg_17[0] = 1.4038856681660068;
  params.vg_N_17[0] = 0.17437730638329096;
  params.Pg_N_init_18[0] = -1.6408365219077408;
  params.Pg_N_avg_18[0] = -0.04450702153554875;
  params.ug_N_18[0] = 1.7117453902485025;
  params.Vg_N_avg_18[0] = 1.1504727980139053;
  params.Thetag_N_avg_18[0] = -0.05962309578364744;
  params.vg_N_18[0] = -0.1788825540764547;
  params.Pg_N_init_19[0] = -1.1280569263625857;
  params.Pg_N_avg_19[0] = -1.2911464767927057;
  params.ug_N_19[0] = -1.7055053231225696;
  params.Vg_N_avg_19[0] = 1.56957275034837;
  params.Thetag_N_avg_19[0] = 0.5607064675962357;
  params.vg_N_19[0] = -1.4266707301147146;
  params.Pg_N_init_20[0] = -0.3434923211351708;
  params.Pg_N_avg_20[0] = -1.8035643024085055;
  params.ug_N_20[0] = -1.1625066019105454;
  params.Vg_N_avg_20[0] = 0.9228324965161532;
  params.Thetag_N_avg_20[0] = 0.6044910817663975;
  params.vg_N_20[0] = -0.0840868104920891;
  params.Pg_N_init_21[0] = -0.900877978017443;
  params.Pg_N_avg_21[0] = 0.608892500264739;
  params.ug_N_21[0] = 1.8257980452695217;
  params.Vg_N_avg_21[0] = -0.25791777529922877;
  params.Thetag_N_avg_21[0] = -1.7194699796493191;
  params.vg_N_21[0] = -1.7690740487081298;
  params.Pg_N_init_22[0] = -1.6685159248097703;
  params.Pg_N_avg_22[0] = 1.8388287490128845;
  params.ug_N_22[0] = 0.16304334474597537;
  params.Vg_N_avg_22[0] = 1.3498497306788897;
  params.Thetag_N_avg_22[0] = -1.3198658230514613;
  params.vg_N_22[0] = -0.9586197090843394;
  params.Pg_N_init_23[0] = 0.7679100474913709;
  params.Pg_N_avg_23[0] = 1.5822813125679343;
  params.ug_N_23[0] = -0.6372460621593619;
  params.Vg_N_avg_23[0] = -1.741307208038867;
  params.Thetag_N_avg_23[0] = 1.456478677642575;
  params.vg_N_23[0] = -0.8365102166820959;
  params.Pg_N_init_24[0] = 0.9643296255982503;
  params.Pg_N_avg_24[0] = -1.367865381194024;
  params.ug_N_24[0] = 0.7798537405635035;
  params.Vg_N_avg_24[0] = 1.3656784761245926;
  params.Thetag_N_avg_24[0] = 0.9086083149868371;
  params.vg_N_24[0] = -0.5635699005460344;
  params.Pg_N_init_25[0] = 0.9067590059607915;
  params.Pg_N_avg_25[0] = -1.4421315032701587;
  params.ug_N_25[0] = -0.7447235390671119;
  params.Vg_N_avg_25[0] = -0.32166897326822186;
  params.Thetag_N_avg_25[0] = 1.5088481557772684;
  params.vg_N_25[0] = -1.385039165715428;
  params.Pg_N_init_26[0] = 1.5204991609972622;
  params.Pg_N_avg_26[0] = 1.1958572768832156;
  params.ug_N_26[0] = 1.8864971883119228;
  params.Vg_N_avg_26[0] = -0.5291880667861584;
  params.Thetag_N_avg_26[0] = -1.1802409243688836;
  params.vg_N_26[0] = -1.037718718661604;
  params.Pg_N_init_27[0] = 1.3114512056856835;
  params.Pg_N_avg_27[0] = 1.8609125943756615;
  params.ug_N_27[0] = 0.7952399935216938;
  params.Vg_N_avg_27[0] = -0.07001183290468038;
  params.Thetag_N_avg_27[0] = -0.8518009412754686;
  params.vg_N_27[0] = 1.3347515373726386;
  params.Pg_N_init_28[0] = 1.4887180335977037;
  params.Pg_N_avg_28[0] = -1.6314736327976336;
  params.ug_N_28[0] = -1.1362021159208933;
  params.Vg_N_avg_28[0] = 1.327044361831466;
  params.Thetag_N_avg_28[0] = 1.3932155883179842;
  params.vg_N_28[0] = -0.7413880049440107;
  params.Pg_N_init_29[0] = -0.8828216126125747;
  params.Pg_N_avg_29[0] = -0.27673991192616;
  params.ug_N_29[0] = 0.15778600105866714;
  params.Vg_N_avg_29[0] = -1.6177327399735457;
  params.Thetag_N_avg_29[0] = 1.3476485548544606;
  params.vg_N_29[0] = 0.13893948140528378;
  params.Pg_N_init_30[0] = 1.0998712601636944;
  params.Pg_N_avg_30[0] = -1.0766549376946926;
  params.ug_N_30[0] = 1.8611734044254629;
  params.Vg_N_avg_30[0] = 1.0041092292735172;
  params.Thetag_N_avg_30[0] = -0.6276245424321543;
  params.vg_N_30[0] = 1.794110587839819;
  params.Pg_N_init_31[0] = 0.8020471158650913;
  params.Pg_N_avg_31[0] = 1.362244341944948;
  params.ug_N_31[0] = -1.8180107765765245;
  params.Vg_N_avg_31[0] = -1.7774338357932473;
  params.Thetag_N_avg_31[0] = 0.9709490941985153;
  params.vg_N_31[0] = -0.7812542682064318;
  params.Pg_N_init_32[0] = 0.0671374633729811;
  params.Pg_N_avg_32[0] = -1.374950305314906;
  params.ug_N_32[0] = 1.9118096386279388;
  params.Vg_N_avg_32[0] = 0.011004190697677885;
  params.Thetag_N_avg_32[0] = 1.3160043138989015;
  params.vg_N_32[0] = -1.7038488148800144;
  params.Pg_N_init_33[0] = -0.08433819112864738;
  params.Pg_N_avg_33[0] = -1.7508820783768964;
  params.ug_N_33[0] = 1.536965724350949;
  params.Vg_N_avg_33[0] = -0.21675928514816478;
  params.Thetag_N_avg_33[0] = -1.725800326952653;
  params.vg_N_33[0] = -1.6940148707361717;
  params.Pg_N_init_34[0] = 0.15517063201268;
  params.Pg_N_avg_34[0] = -1.697734381979077;
  params.ug_N_34[0] = -1.264910727950229;
  params.Vg_N_avg_34[0] = -0.2545716633339441;
  params.Thetag_N_avg_34[0] = -0.008868675926170244;
  params.vg_N_34[0] = 0.3332476609670296;
  params.Pg_N_init_35[0] = 0.48205072561962936;
  params.Pg_N_avg_35[0] = -0.5087540014293261;
  params.ug_N_35[0] = 0.4749463319223195;
  params.Vg_N_avg_35[0] = -1.371021366459455;
  params.Thetag_N_avg_35[0] = -0.8979660982652256;
  params.vg_N_35[0] = 1.194873082385242;
  params.Pg_N_init_36[0] = -1.3876427970939353;
  params.Pg_N_avg_36[0] = -1.106708108457053;
  params.ug_N_36[0] = -1.0280872812241797;
  params.Vg_N_avg_36[0] = -0.08197078070773234;
  params.Thetag_N_avg_36[0] = -1.9970179118324083;
  params.vg_N_36[0] = -1.878754557910134;
  params.Pg_N_init_37[0] = -0.15380739340877803;
  params.Pg_N_avg_37[0] = -1.349917260533923;
  params.ug_N_37[0] = 0.7180072150931407;
  params.Vg_N_avg_37[0] = 1.1808183487065538;
  params.Thetag_N_avg_37[0] = 0.31265343495084075;
  params.vg_N_37[0] = 0.7790599086928229;
  params.Pg_N_init_38[0] = -0.4361679370644853;
  params.Pg_N_avg_38[0] = -1.8148151880282066;
  params.ug_N_38[0] = -0.24231386948140266;
  params.Vg_N_avg_38[0] = -0.5120787511622411;
  params.Thetag_N_avg_38[0] = 0.3880129688013203;
  params.vg_N_38[0] = -1.4631273212038676;
  params.Pg_N_init_39[0] = -1.0891484131126563;
  params.Pg_N_avg_39[0] = 1.2591296661091191;
  params.ug_N_39[0] = -0.9426978934391474;
  params.Vg_N_avg_39[0] = -0.358719180371347;
  params.Thetag_N_avg_39[0] = 1.7438887059831263;
  params.vg_N_39[0] = -0.8977901479165817;
  params.Pg_N_init_40[0] = -1.4188401645857445;
  params.Pg_N_avg_40[0] = 0.8080805173258092;
  params.ug_N_40[0] = 0.2682662017650985;
  params.Vg_N_avg_40[0] = 0.44637534218638786;
  params.Thetag_N_avg_40[0] = -1.8318765960257055;
  params.vg_N_40[0] = -0.3309324209710929;
  params.Pg_N_init_41[0] = -1.9829342633313622;
  params.Pg_N_avg_41[0] = -1.013858124556442;
  params.ug_N_41[0] = 0.8242247343360254;
  params.Vg_N_avg_41[0] = -1.753837136317201;
  params.Thetag_N_avg_41[0] = -0.8212260055868805;
  params.vg_N_41[0] = 1.9524510112487126;
  params.Pg_N_init_42[0] = 1.884888920907902;
  params.Pg_N_avg_42[0] = -0.0726144452811801;
  params.ug_N_42[0] = 0.9427735461129836;
  params.Vg_N_avg_42[0] = 0.5306230967445558;
  params.Thetag_N_avg_42[0] = -0.1372277142250531;
  params.vg_N_42[0] = 1.4282657305652786;
  params.Pg_N_init_43[0] = -1.309926991335284;
  params.Pg_N_avg_43[0] = 1.3137276889764422;
  params.ug_N_43[0] = -1.8317219061667278;
  params.Vg_N_avg_43[0] = 1.4678147672511939;
  params.Thetag_N_avg_43[0] = 0.703986349872991;
  params.vg_N_43[0] = -0.2163435603565258;
  params.Pg_N_init_44[0] = 0.6862809905371079;
  params.Pg_N_avg_44[0] = -0.15852598444303245;
  params.ug_N_44[0] = 1.1200128895143409;
  params.Vg_N_avg_44[0] = -1.5462236645435308;
  params.Thetag_N_avg_44[0] = 0.0326297153944215;
  params.vg_N_44[0] = 1.4859581597754916;
  params.Pg_N_init_45[0] = 1.71011710324809;
  params.Pg_N_avg_45[0] = -1.1186546738067493;
  params.ug_N_45[0] = -0.9922787897815244;
  params.Vg_N_avg_45[0] = 1.6160498864359547;
  params.Thetag_N_avg_45[0] = -0.6179306451394861;
  params.vg_N_45[0] = -1.7725097038051376;
  params.Pg_N_init_46[0] = 0.8595466884481313;
  params.Pg_N_avg_46[0] = -0.3423245633865686;
  params.ug_N_46[0] = 0.9412967499805762;
  params.Vg_N_avg_46[0] = -0.09163346622652258;
  params.Thetag_N_avg_46[0] = 0.002262217745727657;
  params.vg_N_46[0] = -0.3297523583656421;
  params.Pg_N_init_47[0] = -0.8380604158593941;
  params.Pg_N_avg_47[0] = 1.6028434695494038;
  params.ug_N_47[0] = 0.675150311940429;
  params.Vg_N_avg_47[0] = 1.1553293733718686;
  params.Thetag_N_avg_47[0] = 1.5829581243724693;
  params.vg_N_47[0] = -0.9992442304425597;
  params.Pg_N_init_48[0] = 1.6792824558896897;
  params.Pg_N_avg_48[0] = 1.4504203490342324;
  params.ug_N_48[0] = 0.02434104849994556;
  params.Vg_N_avg_48[0] = 0.27160869657612263;
  params.Thetag_N_avg_48[0] = -1.5402710478528858;
  params.vg_N_48[0] = 1.0484633622310744;
  params.Pg_N_init_49[0] = -1.3070999712627054;
  params.Pg_N_avg_49[0] = 0.13534416402363814;
  params.ug_N_49[0] = -1.4942507790851232;
  params.Vg_N_avg_49[0] = -1.708331625671371;
  params.Thetag_N_avg_49[0] = 0.436109775042258;
  params.vg_N_49[0] = -0.03518748153727991;
  params.Pg_N_init_50[0] = 0.6992397389570906;
  params.Pg_N_avg_50[0] = 1.1634167322171374;
  params.ug_N_50[0] = 1.9307499705822648;
  params.Vg_N_avg_50[0] = -1.6636772756932747;
  params.Thetag_N_avg_50[0] = 0.5248484497343218;
  params.vg_N_50[0] = 0.30789958152579144;
  params.Pg_N_init_51[0] = 0.602568707166812;
  params.Pg_N_avg_51[0] = 0.17271781925751872;
  params.ug_N_51[0] = 0.2294695501208066;
  params.Vg_N_avg_51[0] = 1.4742185345619543;
  params.Thetag_N_avg_51[0] = -0.1919535345136989;
  params.vg_N_51[0] = 0.13990231452144553;
  params.Pg_N_init_52[0] = 0.7638548150610602;
  params.Pg_N_avg_52[0] = -1.6420200344195646;
  params.ug_N_52[0] = -0.27229872445076087;
  params.Vg_N_avg_52[0] = -1.5914631171820468;
  params.Thetag_N_avg_52[0] = -1.4487604283558668;
  params.vg_N_52[0] = -1.991497766136364;
  params.Pg_N_init_53[0] = -1.1611742553535152;
  params.Pg_N_avg_53[0] = -1.133450950247063;
  params.ug_N_53[0] = 0.06497792493777155;
  params.Vg_N_avg_53[0] = 0.28083295396097263;
  params.Thetag_N_avg_53[0] = 1.2958447220129887;
  params.vg_N_53[0] = -0.05315524470737154;
  params.Pg_N_init_54[0] = 1.5658183956871667;
  params.Pg_N_avg_54[0] = -0.41975684089933685;
  params.ug_N_54[0] = 0.97844578833777;
  params.Vg_N_avg_54[0] = 0.2110290496695293;
  params.Thetag_N_avg_54[0] = 0.4953003430893044;
  params.vg_N_54[0] = -0.9184320124667495;
  params.Pg_N_init_55[0] = 1.750380031759156;
  params.Pg_N_avg_55[0] = 1.0786188614315915;
  params.ug_N_55[0] = -1.4176198837203735;
  params.Vg_N_avg_55[0] = 0.149737479778294;
  params.Thetag_N_avg_55[0] = 1.9831452222223418;
  params.vg_N_55[0] = -1.8037746699794734;
  params.Pg_N_init_56[0] = -0.7887206483295461;
  params.Pg_N_avg_56[0] = 0.9632534854086652;
  params.ug_N_56[0] = -1.8425542093895406;
  params.Vg_N_avg_56[0] = 0.986684363969033;
  params.Thetag_N_avg_56[0] = 0.2936851199350441;
  params.vg_N_56[0] = 0.9268227022482662;
  params.Pg_N_init_57[0] = 0.20333038350653299;
  params.Pg_N_avg_57[0] = 1.7576139132046351;
  params.ug_N_57[0] = -0.614393188398918;
  params.Vg_N_avg_57[0] = 0.297877839744912;
  params.Thetag_N_avg_57[0] = -1.796880083990895;
  params.vg_N_57[0] = 0.21373133661742738;
  params.Pg_N_init_58[0] = -0.32242822540825156;
  params.Pg_N_avg_58[0] = 1.9326471511608059;
  params.ug_N_58[0] = 1.7824292753481785;
  params.Vg_N_avg_58[0] = -1.4468823405675986;
  params.Thetag_N_avg_58[0] = -1.8335374338761512;
  params.vg_N_58[0] = -1.5172997317243713;
  params.Pg_N_init_59[0] = -1.229012129120719;
  params.Pg_N_avg_59[0] = 0.9046719772422094;
  params.ug_N_59[0] = 0.17591181415489432;
  params.Vg_N_avg_59[0] = 0.13970133814112584;
  params.Thetag_N_avg_59[0] = -0.14185208214985234;
  params.vg_N_59[0] = -1.9732231264739348;
  params.Pg_N_init_60[0] = -0.4301123458221334;
  params.Pg_N_avg_60[0] = 1.9957537650387742;
  params.ug_N_60[0] = 1.2811648216477893;
  params.Vg_N_avg_60[0] = 0.2914428437588219;
  params.Thetag_N_avg_60[0] = -1.214148157218884;
  params.vg_N_60[0] = 1.6818776980374155;
  params.Pg_N_init_61[0] = -0.30341101038214635;
  params.Pg_N_avg_61[0] = 0.47730909231793106;
  params.ug_N_61[0] = -1.187569373035299;
  params.Vg_N_avg_61[0] = -0.6877370247915531;
  params.Thetag_N_avg_61[0] = -0.6201861482616171;
  params.vg_N_61[0] = -0.4209925183921568;
  params.Pg_N_init_62[0] = -1.9110724537712471;
  params.Pg_N_avg_62[0] = 0.6413882087807936;
  params.ug_N_62[0] = -1.3200399280087032;
  params.Vg_N_avg_62[0] = 0.41320105301312626;
  params.Thetag_N_avg_62[0] = 0.4783213861392275;
  params.vg_N_62[0] = 0.7916189857293743;
  params.Pg_N_init_63[0] = -0.8322752558146558;
  params.Pg_N_avg_63[0] = -0.8318720537426154;
  params.ug_N_63[0] = 1.0221179076113445;
  params.Vg_N_avg_63[0] = -0.4471032189262627;
  params.Thetag_N_avg_63[0] = -1.3901469561676985;
  params.vg_N_63[0] = 1.6210596051208572;
  params.Pg_N_init_64[0] = -1.9476687601912737;
  params.Pg_N_avg_64[0] = 1.5459376306231292;
  params.ug_N_64[0] = -0.830972896191656;
  params.Vg_N_avg_64[0] = -0.47269983955176276;
  params.Thetag_N_avg_64[0] = 1.913620609584223;
  params.vg_N_64[0] = -0.25329703423935124;
  params.Pg_N_init_65[0] = 0.8635279149674653;
  params.Pg_N_avg_65[0] = -0.35046893227111564;
  params.ug_N_65[0] = 1.6541432486772365;
  params.Vg_N_avg_65[0] = 0.8779619968413503;
  params.Thetag_N_avg_65[0] = -0.07723284625844862;
  params.vg_N_65[0] = -1.6631134040635196;
  params.Pg_N_init_66[0] = -0.54546452868516;
  params.Pg_N_avg_66[0] = -0.03757319061095998;
  params.ug_N_66[0] = -0.864543266194465;
  params.Vg_N_avg_66[0] = 0.13856203767859343;
  params.Thetag_N_avg_66[0] = -1.1613957272733684;
  params.vg_N_66[0] = -0.022681697832835024;
  params.Pg_N_init_67[0] = 0.11202078062843634;
  params.Pg_N_avg_67[0] = 0.6934385624164641;
  params.ug_N_67[0] = 0.9814633803279791;
  params.Vg_N_avg_67[0] = 0.9198949681022897;
  params.Thetag_N_avg_67[0] = -0.3035363988458051;
  params.vg_N_67[0] = -0.1761906755724203;
  params.Pg_N_init_68[0] = 1.4940284058791686;
  params.Pg_N_avg_68[0] = -0.5488483097174393;
  params.ug_N_68[0] = 0.9521313238305416;
  params.Vg_N_avg_68[0] = 1.9762689267600413;
  params.Thetag_N_avg_68[0] = 1.6992335341478482;
  params.vg_N_68[0] = 0.1969474711697119;
  params.Pg_N_init_69[0] = -0.7795544525014559;
  params.Pg_N_avg_69[0] = 0.4892505434034007;
  params.ug_N_69[0] = 0.7372066729248594;
  params.Vg_N_avg_69[0] = 0.10784901966517557;
  params.Thetag_N_avg_69[0] = -0.6340934767066218;
  params.vg_N_69[0] = -0.17829371464242083;
  params.Pg_N_init_70[0] = -1.6728370279392784;
  params.Pg_N_avg_70[0] = -0.8348711800042916;
  params.ug_N_70[0] = -1.4204129800590897;
  params.Vg_N_avg_70[0] = 0.6659229232859376;
  params.Thetag_N_avg_70[0] = 1.8369365661533168;
  params.vg_N_70[0] = -1.371061267737546;
  params.Pg_N_init_71[0] = -1.8868237125934915;
  params.Pg_N_avg_71[0] = 0.9654286768651104;
  params.ug_N_71[0] = -0.5833420409292005;
  params.Vg_N_avg_71[0] = 0.02386510653728502;
  params.Thetag_N_avg_71[0] = -1.7558076992858345;
  params.vg_N_71[0] = -1.2889402130475411;
  params.Pg_N_init_72[0] = 0.7820251677632606;
  params.Pg_N_avg_72[0] = 0.4208424784688227;
  params.ug_N_72[0] = 1.4136448896755982;
  params.Vg_N_avg_72[0] = 1.8516928541530757;
  params.Thetag_N_avg_72[0] = -0.5615396035790421;
  params.vg_N_72[0] = 0.4809940266433177;
  params.Pg_N_init_73[0] = -0.20929035114697303;
  params.Pg_N_avg_73[0] = 0.022387850798402553;
  params.ug_N_73[0] = -0.43399296564115764;
  params.Vg_N_avg_73[0] = 1.9095769077945013;
  params.Thetag_N_avg_73[0] = 0.4945512698336847;
  params.vg_N_73[0] = -1.4324582900293557;
  params.Pg_N_init_74[0] = 0.790913765746676;
  params.Pg_N_avg_74[0] = 1.8630250293383734;
  params.ug_N_74[0] = 1.5793975466121069;
  params.Vg_N_avg_74[0] = 0.2320163334712646;
  params.Thetag_N_avg_74[0] = -1.9411408650055968;
  params.vg_N_74[0] = 1.2221853270725478;
  params.Pg_N_init_75[0] = 1.7274453600045607;
  params.Pg_N_avg_75[0] = 0.9357159281665783;
  params.ug_N_75[0] = -0.2841874908331623;
  params.Vg_N_avg_75[0] = -0.4766355664552626;
  params.Thetag_N_avg_75[0] = 0.9784190546201912;
  params.vg_N_75[0] = -1.5685956114005477;
  params.Pg_N_init_76[0] = 1.1387833891036;
  params.Pg_N_avg_76[0] = -0.004779126480003892;
  params.ug_N_76[0] = -1.7195239474925414;
  params.Vg_N_avg_76[0] = 1.2921808565147272;
  params.Thetag_N_avg_76[0] = -0.43317009071966606;
  params.vg_N_76[0] = -1.572940257279357;
  params.Pg_N_init_77[0] = -1.3048062231674988;
  params.Pg_N_avg_77[0] = 1.4377304631579175;
  params.ug_N_77[0] = -1.3090328020145874;
  params.Vg_N_avg_77[0] = 1.1370018620707785;
  params.Thetag_N_avg_77[0] = 1.2164644012668289;
  params.vg_N_77[0] = -1.6539274174499985;
  params.Pg_N_init_78[0] = -0.25845368809725544;
  params.Pg_N_avg_78[0] = 1.1486358936399745;
  params.ug_N_78[0] = -0.03975647517318137;
  params.Vg_N_avg_78[0] = 1.4640632749164326;
  params.Thetag_N_avg_78[0] = -0.48111499989733186;
  params.vg_N_78[0] = 0.5132576752843594;
  params.Pg_N_init_79[0] = -1.1459189400462249;
  params.Pg_N_avg_79[0] = 1.3690255364554855;
  params.ug_N_79[0] = 1.3574291456003253;
  params.Vg_N_avg_79[0] = 0.26333733823037253;
  params.Thetag_N_avg_79[0] = -0.7076462135286032;
  params.vg_N_79[0] = -0.6097272363453645;
  params.Pg_N_init_80[0] = 0.37873096815108465;
  params.Pg_N_avg_80[0] = -1.4863636934585411;
  params.ug_N_80[0] = 0.04189135833804869;
  params.Vg_N_avg_80[0] = -0.8182949160834703;
  params.Thetag_N_avg_80[0] = -0.6336865828985854;
  params.vg_N_80[0] = -0.7126437991119396;
  params.Pg_N_init_81[0] = 1.3381487344587226;
  params.Pg_N_avg_81[0] = -1.2979975504895949;
  params.ug_N_81[0] = -1.0542097271412714;
  params.Vg_N_avg_81[0] = -1.3421003125955435;
  params.Thetag_N_avg_81[0] = -1.9395969070507038;
  params.vg_N_81[0] = -0.29758108058547306;
  params.Pg_N_init_82[0] = 1.3757899684264032;
  params.Pg_N_avg_82[0] = 1.6109970296148042;
  params.ug_N_82[0] = -0.050537352418498216;
  params.Vg_N_avg_82[0] = -0.3144945653528741;
  params.Thetag_N_avg_82[0] = 1.4726689240031474;
  params.vg_N_82[0] = 0.11397910876468265;
  params.Pg_N_init_83[0] = 0.19466869962815858;
  params.Pg_N_avg_83[0] = 0.5972476722406035;
  params.ug_N_83[0] = -1.6815490772221828;
  params.Vg_N_avg_83[0] = 1.3540223072599735;
  params.Thetag_N_avg_83[0] = -1.577027832358222;
  params.vg_N_83[0] = 0.12928618615237353;
  params.Pg_N_init_84[0] = 1.704038169667271;
  params.Pg_N_avg_84[0] = 0.19482725189070793;
  params.ug_N_84[0] = -0.6311686254597215;
  params.Vg_N_avg_84[0] = 0.9065234706582928;
  params.Thetag_N_avg_84[0] = 1.604058201281767;
  params.vg_N_84[0] = 0.4649414640474294;
  params.Pg_N_init_85[0] = -1.7764554290993346;
  params.Pg_N_avg_85[0] = 1.5152343936830337;
  params.ug_N_85[0] = -1.9280901945449935;
  params.Vg_N_avg_85[0] = 0.7129569482366098;
  params.Thetag_N_avg_85[0] = 1.6001840923928201;
  params.vg_N_85[0] = -1.3702177446733126;
  params.Pg_N_init_86[0] = 0.11266051920028186;
  params.Pg_N_avg_86[0] = 0.8202183589903962;
  params.ug_N_86[0] = -1.297953481011172;
  params.Vg_N_avg_86[0] = -1.0192096617939002;
  params.Thetag_N_avg_86[0] = -1.7337200441949867;
  params.vg_N_86[0] = -1.3639899659742465;
  params.Pg_N_init_87[0] = -1.5273517222086332;
  params.Pg_N_avg_87[0] = -0.8374302703303731;
  params.ug_N_87[0] = 1.00229367551592;
  params.Vg_N_avg_87[0] = 0.7747378843920099;
  params.Thetag_N_avg_87[0] = 1.0504096866871468;
  params.vg_N_87[0] = 0.638655773812761;
  params.Pg_N_init_88[0] = 1.176936790033046;
  params.Pg_N_avg_88[0] = -1.4041747524796162;
  params.ug_N_88[0] = 0.21725437512222667;
  params.Vg_N_avg_88[0] = -1.9141609882936188;
  params.Thetag_N_avg_88[0] = -0.03334441105363828;
  params.vg_N_88[0] = 1.3736673884387467;
  params.Pg_N_init_89[0] = -0.11085150689269163;
  params.Pg_N_avg_89[0] = -0.8176560931958075;
  params.ug_N_89[0] = -0.9013799953302866;
  params.Vg_N_avg_89[0] = -0.42583422050124753;
  params.Thetag_N_avg_89[0] = 1.6552920005330618;
  params.vg_N_89[0] = 1.8971842560697287;
  params.Pg_N_init_90[0] = 0.9935321777966784;
  params.Pg_N_avg_90[0] = 1.9500402929402196;
  params.ug_N_90[0] = 1.0489535977170181;
  params.Vg_N_avg_90[0] = -0.8630392743714372;
  params.Thetag_N_avg_90[0] = -0.25967183338596733;
  params.vg_N_90[0] = 0.8925966402843359;
  params.Pg_N_init_91[0] = 0.8373600738876834;
  params.Pg_N_avg_91[0] = 0.7125001994938436;
  params.ug_N_91[0] = -0.048447588572545275;
  params.Vg_N_avg_91[0] = -1.4274714856193604;
  params.Thetag_N_avg_91[0] = 1.8385542904833923;
  params.vg_N_91[0] = -1.1195070325474288;
  params.Pg_N_init_92[0] = 1.9175373793884956;
  params.Pg_N_avg_92[0] = -1.49030500627704;
  params.ug_N_92[0] = 1.9213425364706396;
  params.Vg_N_avg_92[0] = -0.49553546476315047;
  params.Thetag_N_avg_92[0] = 1.2437464435895134;
  params.vg_N_92[0] = -1.970831509470568;
  params.Pg_N_init_93[0] = -0.219996830259797;
  params.Pg_N_avg_93[0] = -1.0042329091607591;
  params.ug_N_93[0] = 0.7781008085794774;
  params.Vg_N_avg_93[0] = 0.65210699599452;
  params.Thetag_N_avg_93[0] = -0.152326999732443;
  params.vg_N_93[0] = 0.8265434509993406;
  params.Pg_N_init_94[0] = 1.9130464561754126;
  params.Pg_N_avg_94[0] = -1.6270096836882288;
  params.ug_N_94[0] = 0.2507042290048189;
  params.Vg_N_avg_94[0] = 0.7038441998600256;
  params.Thetag_N_avg_94[0] = 0.5328743207925606;
  params.vg_N_94[0] = -0.9509907719589208;
  params.Pg_N_init_95[0] = 1.499815178589135;
  params.Pg_N_avg_95[0] = -1.0178753663037017;
  params.ug_N_95[0] = 1.3798461831617561;
  params.Vg_N_avg_95[0] = -0.11708553759234386;
  params.Thetag_N_avg_95[0] = -1.4276299186218124;
  params.vg_N_95[0] = 1.296518419303864;
  params.Pg_N_init_96[0] = -1.6872707956138546;
  params.Pg_N_avg_96[0] = 1.1799585157870145;
  params.ug_N_96[0] = 0.4000488706320535;
  params.Vg_N_avg_96[0] = 1.506638004200894;
  params.Thetag_N_avg_96[0] = 1.2128180682740366;
  params.vg_N_96[0] = -0.39211699471717854;
  params.Pg_N_init_97[0] = -1.4592313874139302;
  params.Pg_N_avg_97[0] = -0.9352340128154211;
  params.ug_N_97[0] = -1.994709862977336;
  params.Vg_N_avg_97[0] = 0.6136129920637026;
  params.Thetag_N_avg_97[0] = -1.6579503948780245;
  params.vg_N_97[0] = -1.2828456921062488;
  params.Pg_N_init_98[0] = -1.0200938896697522;
  params.Pg_N_avg_98[0] = -0.3755900704115436;
  params.ug_N_98[0] = 0.747199791836243;
  params.Vg_N_avg_98[0] = -0.22212974213441683;
  params.Thetag_N_avg_98[0] = 0.015082263441096089;
  params.vg_N_98[0] = -1.6271688108937168;
  params.Pg_N_init_99[0] = -0.6472903955867526;
  params.Pg_N_avg_99[0] = -1.1733258209627806;
  params.ug_N_99[0] = 0.9565501943340924;
  params.Vg_N_avg_99[0] = -1.929389541307601;
  params.Thetag_N_avg_99[0] = 0.4671837668673531;
  params.vg_N_99[0] = 0.7915477026785647;
  params.Pg_N_init_100[0] = 0.018572068486599758;
  params.Pg_N_avg_100[0] = -1.8220899973808726;
  params.ug_N_100[0] = -0.995629851336445;
  params.Vg_N_avg_100[0] = -1.0486975119711213;
  params.Thetag_N_avg_100[0] = -0.9289312699596386;
  params.vg_N_100[0] = -0.9472402942019333;
  params.Pg_N_init_101[0] = 1.8908619466142156;
  params.Pg_N_avg_101[0] = 1.164645007668001;
  params.ug_N_101[0] = 1.5636429264767182;
  params.Vg_N_avg_101[0] = 0.8540115800503387;
  params.Thetag_N_avg_101[0] = -0.6133530465568309;
  params.vg_N_101[0] = 1.7674136894457204;
  params.contNum[0] = 0.9689102990936438;
  params.PgMin[0] = 0.37086987968978935;
  params.PgMax[0] = 1.4589984392387918;
}
void Gensolver::load_default_data(double gsRho, double Pgenprev[], double Pgenavg[], double Powerprice[], double Angpriceavg[], double Angavg[], double Angprice[]) {
  params.rho[0] = gsRho;
for ( int i = 0; i <= params.caseNumber; ++i ) {
  params.ones[i] = 1.0;
  params.Pg_N_init[i] = Pgenprev[i];
  params.Pg_N_avg[i] = Pgenavg[i];
  params.ug_N[i] = Powerprice[i];
  params.Vg_N_avg[i] = Angpriceavg[i];
  params.Thetag_N_avg[i] = Angavg[i];
  params.vg_N[i] = Angprice[i];
}
  set_defaults();
  setup_indexing();
}

double Gensolver::getPSol(void) {
 Piterate = (vars.Pg);
 cout << "\nPiterate from the solver: " << *Piterate << endl;
 return *Piterate;
}

double Gensolver::getObj(void) {
 return (params.c2[0])*(*Piterate)*(*Piterate)+(params.c1[0])*(*Piterate)+(params.c0[0]);
}

double *Gensolver::getThetaPtr(void){
//for ( int i = 0; i < 401; ++i )
	//cout << "\nThiterate: " << *(vars.Thetag+i) << endl;
return vars.Thetag;
}

array<double, 401> Gensolver::getThetaSol(void) {
for ( int i = 0; i <= 400; ++i ) {
 Thiterate[i] = *((vars.Thetag)+i);
 //cout << "\nThiterate: " << *Thiterate[i] << endl;
}
 return Thiterate;
}
	
double Gensolver::getPMax() // start of getPMax function
{
	return params.PgMax[0];
} // end of getMax

double Gensolver::getPMin() // start of getPMin function
{
	return params.PgMin[0];
} // end of getPMin

double Gensolver::getQuadCoeff() // start of getQuadCoeff function
{
	return params.c2[0]; 
} // end of getQuadCoeff

double Gensolver::getLinCoeff() // start of getLinCoeff function
{
	return params.c1[0]; 
} // end of getLinCoeff

double Gensolver::getConstCoeff() // start of getConstCoeff function
{
	return params.c0[0]; 
} // end of getConstCoeff
/* Produced by CVXGEN, 2015-09-15 19:24:02 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: solver.c. */
/* Description: Main solver file. */
double Gensolver::eval_gap(void) {
  int i;
  double gap;
  gap = 0;
  for (i = 0; i < 2; i++)
    gap += work.z[i]*work.s[i];
  return gap;
}
void Gensolver::set_defaults(void) {
  settings.resid_tol = 1e-6;
  settings.eps = 1e-4;
  settings.max_iters = 25;
  settings.refine_steps = 1;
  settings.s_init = 1;
  settings.z_init = 1;
  settings.debug = 0;
  settings.verbose = 1;
  settings.verbose_refinement = 0;
  settings.better_start = 1;
  settings.kkt_reg = 1e-7;
}
void Gensolver::setup_pointers(void) {
  work.y = work.x + 102;
  work.s = work.x + 102;
  work.z = work.x + 104;
  vars.Pg = work.x + 0;
  vars.Thetag_1 = work.x + 1;
  vars.Thetag_2 = work.x + 2;
  vars.Thetag_3 = work.x + 3;
  vars.Thetag_4 = work.x + 4;
  vars.Thetag_5 = work.x + 5;
  vars.Thetag_6 = work.x + 6;
  vars.Thetag_7 = work.x + 7;
  vars.Thetag_8 = work.x + 8;
  vars.Thetag_9 = work.x + 9;
  vars.Thetag_10 = work.x + 10;
  vars.Thetag_11 = work.x + 11;
  vars.Thetag_12 = work.x + 12;
  vars.Thetag_13 = work.x + 13;
  vars.Thetag_14 = work.x + 14;
  vars.Thetag_15 = work.x + 15;
  vars.Thetag_16 = work.x + 16;
  vars.Thetag_17 = work.x + 17;
  vars.Thetag_18 = work.x + 18;
  vars.Thetag_19 = work.x + 19;
  vars.Thetag_20 = work.x + 20;
  vars.Thetag_21 = work.x + 21;
  vars.Thetag_22 = work.x + 22;
  vars.Thetag_23 = work.x + 23;
  vars.Thetag_24 = work.x + 24;
  vars.Thetag_25 = work.x + 25;
  vars.Thetag_26 = work.x + 26;
  vars.Thetag_27 = work.x + 27;
  vars.Thetag_28 = work.x + 28;
  vars.Thetag_29 = work.x + 29;
  vars.Thetag_30 = work.x + 30;
  vars.Thetag_31 = work.x + 31;
  vars.Thetag_32 = work.x + 32;
  vars.Thetag_33 = work.x + 33;
  vars.Thetag_34 = work.x + 34;
  vars.Thetag_35 = work.x + 35;
  vars.Thetag_36 = work.x + 36;
  vars.Thetag_37 = work.x + 37;
  vars.Thetag_38 = work.x + 38;
  vars.Thetag_39 = work.x + 39;
  vars.Thetag_40 = work.x + 40;
  vars.Thetag_41 = work.x + 41;
  vars.Thetag_42 = work.x + 42;
  vars.Thetag_43 = work.x + 43;
  vars.Thetag_44 = work.x + 44;
  vars.Thetag_45 = work.x + 45;
  vars.Thetag_46 = work.x + 46;
  vars.Thetag_47 = work.x + 47;
  vars.Thetag_48 = work.x + 48;
  vars.Thetag_49 = work.x + 49;
  vars.Thetag_50 = work.x + 50;
  vars.Thetag_51 = work.x + 51;
  vars.Thetag_52 = work.x + 52;
  vars.Thetag_53 = work.x + 53;
  vars.Thetag_54 = work.x + 54;
  vars.Thetag_55 = work.x + 55;
  vars.Thetag_56 = work.x + 56;
  vars.Thetag_57 = work.x + 57;
  vars.Thetag_58 = work.x + 58;
  vars.Thetag_59 = work.x + 59;
  vars.Thetag_60 = work.x + 60;
  vars.Thetag_61 = work.x + 61;
  vars.Thetag_62 = work.x + 62;
  vars.Thetag_63 = work.x + 63;
  vars.Thetag_64 = work.x + 64;
  vars.Thetag_65 = work.x + 65;
  vars.Thetag_66 = work.x + 66;
  vars.Thetag_67 = work.x + 67;
  vars.Thetag_68 = work.x + 68;
  vars.Thetag_69 = work.x + 69;
  vars.Thetag_70 = work.x + 70;
  vars.Thetag_71 = work.x + 71;
  vars.Thetag_72 = work.x + 72;
  vars.Thetag_73 = work.x + 73;
  vars.Thetag_74 = work.x + 74;
  vars.Thetag_75 = work.x + 75;
  vars.Thetag_76 = work.x + 76;
  vars.Thetag_77 = work.x + 77;
  vars.Thetag_78 = work.x + 78;
  vars.Thetag_79 = work.x + 79;
  vars.Thetag_80 = work.x + 80;
  vars.Thetag_81 = work.x + 81;
  vars.Thetag_82 = work.x + 82;
  vars.Thetag_83 = work.x + 83;
  vars.Thetag_84 = work.x + 84;
  vars.Thetag_85 = work.x + 85;
  vars.Thetag_86 = work.x + 86;
  vars.Thetag_87 = work.x + 87;
  vars.Thetag_88 = work.x + 88;
  vars.Thetag_89 = work.x + 89;
  vars.Thetag_90 = work.x + 90;
  vars.Thetag_91 = work.x + 91;
  vars.Thetag_92 = work.x + 92;
  vars.Thetag_93 = work.x + 93;
  vars.Thetag_94 = work.x + 94;
  vars.Thetag_95 = work.x + 95;
  vars.Thetag_96 = work.x + 96;
  vars.Thetag_97 = work.x + 97;
  vars.Thetag_98 = work.x + 98;
  vars.Thetag_99 = work.x + 99;
  vars.Thetag_100 = work.x + 100;
  vars.Thetag_101 = work.x + 101;
}
void Gensolver::setup_indexed_params(void) {
  /* In CVXGEN, you can say */
  /*   parameters */
  /*     A[i] (5,3), i=1..4 */
  /*   end */
  /* This function sets up A[2] to be a pointer to A_2, which is a length-15 */
  /* vector of doubles. */
  /* If you access parameters that you haven't defined in CVXGEN, the result */
  /* is undefined. */
  params.Pg_N_init[1] = params.Pg_N_init_1;
  params.Pg_N_avg[1] = params.Pg_N_avg_1;
  params.ug_N[1] = params.ug_N_1;
  params.Vg_N_avg[1] = params.Vg_N_avg_1;
  params.Thetag_N_avg[1] = params.Thetag_N_avg_1;
  params.vg_N[1] = params.vg_N_1;
  params.Pg_N_init[2] = params.Pg_N_init_2;
  params.Pg_N_avg[2] = params.Pg_N_avg_2;
  params.ug_N[2] = params.ug_N_2;
  params.Vg_N_avg[2] = params.Vg_N_avg_2;
  params.Thetag_N_avg[2] = params.Thetag_N_avg_2;
  params.vg_N[2] = params.vg_N_2;
  params.Pg_N_init[3] = params.Pg_N_init_3;
  params.Pg_N_avg[3] = params.Pg_N_avg_3;
  params.ug_N[3] = params.ug_N_3;
  params.Vg_N_avg[3] = params.Vg_N_avg_3;
  params.Thetag_N_avg[3] = params.Thetag_N_avg_3;
  params.vg_N[3] = params.vg_N_3;
  params.Pg_N_init[4] = params.Pg_N_init_4;
  params.Pg_N_avg[4] = params.Pg_N_avg_4;
  params.ug_N[4] = params.ug_N_4;
  params.Vg_N_avg[4] = params.Vg_N_avg_4;
  params.Thetag_N_avg[4] = params.Thetag_N_avg_4;
  params.vg_N[4] = params.vg_N_4;
  params.Pg_N_init[5] = params.Pg_N_init_5;
  params.Pg_N_avg[5] = params.Pg_N_avg_5;
  params.ug_N[5] = params.ug_N_5;
  params.Vg_N_avg[5] = params.Vg_N_avg_5;
  params.Thetag_N_avg[5] = params.Thetag_N_avg_5;
  params.vg_N[5] = params.vg_N_5;
  params.Pg_N_init[6] = params.Pg_N_init_6;
  params.Pg_N_avg[6] = params.Pg_N_avg_6;
  params.ug_N[6] = params.ug_N_6;
  params.Vg_N_avg[6] = params.Vg_N_avg_6;
  params.Thetag_N_avg[6] = params.Thetag_N_avg_6;
  params.vg_N[6] = params.vg_N_6;
  params.Pg_N_init[7] = params.Pg_N_init_7;
  params.Pg_N_avg[7] = params.Pg_N_avg_7;
  params.ug_N[7] = params.ug_N_7;
  params.Vg_N_avg[7] = params.Vg_N_avg_7;
  params.Thetag_N_avg[7] = params.Thetag_N_avg_7;
  params.vg_N[7] = params.vg_N_7;
  params.Pg_N_init[8] = params.Pg_N_init_8;
  params.Pg_N_avg[8] = params.Pg_N_avg_8;
  params.ug_N[8] = params.ug_N_8;
  params.Vg_N_avg[8] = params.Vg_N_avg_8;
  params.Thetag_N_avg[8] = params.Thetag_N_avg_8;
  params.vg_N[8] = params.vg_N_8;
  params.Pg_N_init[9] = params.Pg_N_init_9;
  params.Pg_N_avg[9] = params.Pg_N_avg_9;
  params.ug_N[9] = params.ug_N_9;
  params.Vg_N_avg[9] = params.Vg_N_avg_9;
  params.Thetag_N_avg[9] = params.Thetag_N_avg_9;
  params.vg_N[9] = params.vg_N_9;
  params.Pg_N_init[10] = params.Pg_N_init_10;
  params.Pg_N_avg[10] = params.Pg_N_avg_10;
  params.ug_N[10] = params.ug_N_10;
  params.Vg_N_avg[10] = params.Vg_N_avg_10;
  params.Thetag_N_avg[10] = params.Thetag_N_avg_10;
  params.vg_N[10] = params.vg_N_10;
  params.Pg_N_init[11] = params.Pg_N_init_11;
  params.Pg_N_avg[11] = params.Pg_N_avg_11;
  params.ug_N[11] = params.ug_N_11;
  params.Vg_N_avg[11] = params.Vg_N_avg_11;
  params.Thetag_N_avg[11] = params.Thetag_N_avg_11;
  params.vg_N[11] = params.vg_N_11;
  params.Pg_N_init[12] = params.Pg_N_init_12;
  params.Pg_N_avg[12] = params.Pg_N_avg_12;
  params.ug_N[12] = params.ug_N_12;
  params.Vg_N_avg[12] = params.Vg_N_avg_12;
  params.Thetag_N_avg[12] = params.Thetag_N_avg_12;
  params.vg_N[12] = params.vg_N_12;
  params.Pg_N_init[13] = params.Pg_N_init_13;
  params.Pg_N_avg[13] = params.Pg_N_avg_13;
  params.ug_N[13] = params.ug_N_13;
  params.Vg_N_avg[13] = params.Vg_N_avg_13;
  params.Thetag_N_avg[13] = params.Thetag_N_avg_13;
  params.vg_N[13] = params.vg_N_13;
  params.Pg_N_init[14] = params.Pg_N_init_14;
  params.Pg_N_avg[14] = params.Pg_N_avg_14;
  params.ug_N[14] = params.ug_N_14;
  params.Vg_N_avg[14] = params.Vg_N_avg_14;
  params.Thetag_N_avg[14] = params.Thetag_N_avg_14;
  params.vg_N[14] = params.vg_N_14;
  params.Pg_N_init[15] = params.Pg_N_init_15;
  params.Pg_N_avg[15] = params.Pg_N_avg_15;
  params.ug_N[15] = params.ug_N_15;
  params.Vg_N_avg[15] = params.Vg_N_avg_15;
  params.Thetag_N_avg[15] = params.Thetag_N_avg_15;
  params.vg_N[15] = params.vg_N_15;
  params.Pg_N_init[16] = params.Pg_N_init_16;
  params.Pg_N_avg[16] = params.Pg_N_avg_16;
  params.ug_N[16] = params.ug_N_16;
  params.Vg_N_avg[16] = params.Vg_N_avg_16;
  params.Thetag_N_avg[16] = params.Thetag_N_avg_16;
  params.vg_N[16] = params.vg_N_16;
  params.Pg_N_init[17] = params.Pg_N_init_17;
  params.Pg_N_avg[17] = params.Pg_N_avg_17;
  params.ug_N[17] = params.ug_N_17;
  params.Vg_N_avg[17] = params.Vg_N_avg_17;
  params.Thetag_N_avg[17] = params.Thetag_N_avg_17;
  params.vg_N[17] = params.vg_N_17;
  params.Pg_N_init[18] = params.Pg_N_init_18;
  params.Pg_N_avg[18] = params.Pg_N_avg_18;
  params.ug_N[18] = params.ug_N_18;
  params.Vg_N_avg[18] = params.Vg_N_avg_18;
  params.Thetag_N_avg[18] = params.Thetag_N_avg_18;
  params.vg_N[18] = params.vg_N_18;
  params.Pg_N_init[19] = params.Pg_N_init_19;
  params.Pg_N_avg[19] = params.Pg_N_avg_19;
  params.ug_N[19] = params.ug_N_19;
  params.Vg_N_avg[19] = params.Vg_N_avg_19;
  params.Thetag_N_avg[19] = params.Thetag_N_avg_19;
  params.vg_N[19] = params.vg_N_19;
  params.Pg_N_init[20] = params.Pg_N_init_20;
  params.Pg_N_avg[20] = params.Pg_N_avg_20;
  params.ug_N[20] = params.ug_N_20;
  params.Vg_N_avg[20] = params.Vg_N_avg_20;
  params.Thetag_N_avg[20] = params.Thetag_N_avg_20;
  params.vg_N[20] = params.vg_N_20;
  params.Pg_N_init[21] = params.Pg_N_init_21;
  params.Pg_N_avg[21] = params.Pg_N_avg_21;
  params.ug_N[21] = params.ug_N_21;
  params.Vg_N_avg[21] = params.Vg_N_avg_21;
  params.Thetag_N_avg[21] = params.Thetag_N_avg_21;
  params.vg_N[21] = params.vg_N_21;
  params.Pg_N_init[22] = params.Pg_N_init_22;
  params.Pg_N_avg[22] = params.Pg_N_avg_22;
  params.ug_N[22] = params.ug_N_22;
  params.Vg_N_avg[22] = params.Vg_N_avg_22;
  params.Thetag_N_avg[22] = params.Thetag_N_avg_22;
  params.vg_N[22] = params.vg_N_22;
  params.Pg_N_init[23] = params.Pg_N_init_23;
  params.Pg_N_avg[23] = params.Pg_N_avg_23;
  params.ug_N[23] = params.ug_N_23;
  params.Vg_N_avg[23] = params.Vg_N_avg_23;
  params.Thetag_N_avg[23] = params.Thetag_N_avg_23;
  params.vg_N[23] = params.vg_N_23;
  params.Pg_N_init[24] = params.Pg_N_init_24;
  params.Pg_N_avg[24] = params.Pg_N_avg_24;
  params.ug_N[24] = params.ug_N_24;
  params.Vg_N_avg[24] = params.Vg_N_avg_24;
  params.Thetag_N_avg[24] = params.Thetag_N_avg_24;
  params.vg_N[24] = params.vg_N_24;
  params.Pg_N_init[25] = params.Pg_N_init_25;
  params.Pg_N_avg[25] = params.Pg_N_avg_25;
  params.ug_N[25] = params.ug_N_25;
  params.Vg_N_avg[25] = params.Vg_N_avg_25;
  params.Thetag_N_avg[25] = params.Thetag_N_avg_25;
  params.vg_N[25] = params.vg_N_25;
  params.Pg_N_init[26] = params.Pg_N_init_26;
  params.Pg_N_avg[26] = params.Pg_N_avg_26;
  params.ug_N[26] = params.ug_N_26;
  params.Vg_N_avg[26] = params.Vg_N_avg_26;
  params.Thetag_N_avg[26] = params.Thetag_N_avg_26;
  params.vg_N[26] = params.vg_N_26;
  params.Pg_N_init[27] = params.Pg_N_init_27;
  params.Pg_N_avg[27] = params.Pg_N_avg_27;
  params.ug_N[27] = params.ug_N_27;
  params.Vg_N_avg[27] = params.Vg_N_avg_27;
  params.Thetag_N_avg[27] = params.Thetag_N_avg_27;
  params.vg_N[27] = params.vg_N_27;
  params.Pg_N_init[28] = params.Pg_N_init_28;
  params.Pg_N_avg[28] = params.Pg_N_avg_28;
  params.ug_N[28] = params.ug_N_28;
  params.Vg_N_avg[28] = params.Vg_N_avg_28;
  params.Thetag_N_avg[28] = params.Thetag_N_avg_28;
  params.vg_N[28] = params.vg_N_28;
  params.Pg_N_init[29] = params.Pg_N_init_29;
  params.Pg_N_avg[29] = params.Pg_N_avg_29;
  params.ug_N[29] = params.ug_N_29;
  params.Vg_N_avg[29] = params.Vg_N_avg_29;
  params.Thetag_N_avg[29] = params.Thetag_N_avg_29;
  params.vg_N[29] = params.vg_N_29;
  params.Pg_N_init[30] = params.Pg_N_init_30;
  params.Pg_N_avg[30] = params.Pg_N_avg_30;
  params.ug_N[30] = params.ug_N_30;
  params.Vg_N_avg[30] = params.Vg_N_avg_30;
  params.Thetag_N_avg[30] = params.Thetag_N_avg_30;
  params.vg_N[30] = params.vg_N_30;
  params.Pg_N_init[31] = params.Pg_N_init_31;
  params.Pg_N_avg[31] = params.Pg_N_avg_31;
  params.ug_N[31] = params.ug_N_31;
  params.Vg_N_avg[31] = params.Vg_N_avg_31;
  params.Thetag_N_avg[31] = params.Thetag_N_avg_31;
  params.vg_N[31] = params.vg_N_31;
  params.Pg_N_init[32] = params.Pg_N_init_32;
  params.Pg_N_avg[32] = params.Pg_N_avg_32;
  params.ug_N[32] = params.ug_N_32;
  params.Vg_N_avg[32] = params.Vg_N_avg_32;
  params.Thetag_N_avg[32] = params.Thetag_N_avg_32;
  params.vg_N[32] = params.vg_N_32;
  params.Pg_N_init[33] = params.Pg_N_init_33;
  params.Pg_N_avg[33] = params.Pg_N_avg_33;
  params.ug_N[33] = params.ug_N_33;
  params.Vg_N_avg[33] = params.Vg_N_avg_33;
  params.Thetag_N_avg[33] = params.Thetag_N_avg_33;
  params.vg_N[33] = params.vg_N_33;
  params.Pg_N_init[34] = params.Pg_N_init_34;
  params.Pg_N_avg[34] = params.Pg_N_avg_34;
  params.ug_N[34] = params.ug_N_34;
  params.Vg_N_avg[34] = params.Vg_N_avg_34;
  params.Thetag_N_avg[34] = params.Thetag_N_avg_34;
  params.vg_N[34] = params.vg_N_34;
  params.Pg_N_init[35] = params.Pg_N_init_35;
  params.Pg_N_avg[35] = params.Pg_N_avg_35;
  params.ug_N[35] = params.ug_N_35;
  params.Vg_N_avg[35] = params.Vg_N_avg_35;
  params.Thetag_N_avg[35] = params.Thetag_N_avg_35;
  params.vg_N[35] = params.vg_N_35;
  params.Pg_N_init[36] = params.Pg_N_init_36;
  params.Pg_N_avg[36] = params.Pg_N_avg_36;
  params.ug_N[36] = params.ug_N_36;
  params.Vg_N_avg[36] = params.Vg_N_avg_36;
  params.Thetag_N_avg[36] = params.Thetag_N_avg_36;
  params.vg_N[36] = params.vg_N_36;
  params.Pg_N_init[37] = params.Pg_N_init_37;
  params.Pg_N_avg[37] = params.Pg_N_avg_37;
  params.ug_N[37] = params.ug_N_37;
  params.Vg_N_avg[37] = params.Vg_N_avg_37;
  params.Thetag_N_avg[37] = params.Thetag_N_avg_37;
  params.vg_N[37] = params.vg_N_37;
  params.Pg_N_init[38] = params.Pg_N_init_38;
  params.Pg_N_avg[38] = params.Pg_N_avg_38;
  params.ug_N[38] = params.ug_N_38;
  params.Vg_N_avg[38] = params.Vg_N_avg_38;
  params.Thetag_N_avg[38] = params.Thetag_N_avg_38;
  params.vg_N[38] = params.vg_N_38;
  params.Pg_N_init[39] = params.Pg_N_init_39;
  params.Pg_N_avg[39] = params.Pg_N_avg_39;
  params.ug_N[39] = params.ug_N_39;
  params.Vg_N_avg[39] = params.Vg_N_avg_39;
  params.Thetag_N_avg[39] = params.Thetag_N_avg_39;
  params.vg_N[39] = params.vg_N_39;
  params.Pg_N_init[40] = params.Pg_N_init_40;
  params.Pg_N_avg[40] = params.Pg_N_avg_40;
  params.ug_N[40] = params.ug_N_40;
  params.Vg_N_avg[40] = params.Vg_N_avg_40;
  params.Thetag_N_avg[40] = params.Thetag_N_avg_40;
  params.vg_N[40] = params.vg_N_40;
  params.Pg_N_init[41] = params.Pg_N_init_41;
  params.Pg_N_avg[41] = params.Pg_N_avg_41;
  params.ug_N[41] = params.ug_N_41;
  params.Vg_N_avg[41] = params.Vg_N_avg_41;
  params.Thetag_N_avg[41] = params.Thetag_N_avg_41;
  params.vg_N[41] = params.vg_N_41;
  params.Pg_N_init[42] = params.Pg_N_init_42;
  params.Pg_N_avg[42] = params.Pg_N_avg_42;
  params.ug_N[42] = params.ug_N_42;
  params.Vg_N_avg[42] = params.Vg_N_avg_42;
  params.Thetag_N_avg[42] = params.Thetag_N_avg_42;
  params.vg_N[42] = params.vg_N_42;
  params.Pg_N_init[43] = params.Pg_N_init_43;
  params.Pg_N_avg[43] = params.Pg_N_avg_43;
  params.ug_N[43] = params.ug_N_43;
  params.Vg_N_avg[43] = params.Vg_N_avg_43;
  params.Thetag_N_avg[43] = params.Thetag_N_avg_43;
  params.vg_N[43] = params.vg_N_43;
  params.Pg_N_init[44] = params.Pg_N_init_44;
  params.Pg_N_avg[44] = params.Pg_N_avg_44;
  params.ug_N[44] = params.ug_N_44;
  params.Vg_N_avg[44] = params.Vg_N_avg_44;
  params.Thetag_N_avg[44] = params.Thetag_N_avg_44;
  params.vg_N[44] = params.vg_N_44;
  params.Pg_N_init[45] = params.Pg_N_init_45;
  params.Pg_N_avg[45] = params.Pg_N_avg_45;
  params.ug_N[45] = params.ug_N_45;
  params.Vg_N_avg[45] = params.Vg_N_avg_45;
  params.Thetag_N_avg[45] = params.Thetag_N_avg_45;
  params.vg_N[45] = params.vg_N_45;
  params.Pg_N_init[46] = params.Pg_N_init_46;
  params.Pg_N_avg[46] = params.Pg_N_avg_46;
  params.ug_N[46] = params.ug_N_46;
  params.Vg_N_avg[46] = params.Vg_N_avg_46;
  params.Thetag_N_avg[46] = params.Thetag_N_avg_46;
  params.vg_N[46] = params.vg_N_46;
  params.Pg_N_init[47] = params.Pg_N_init_47;
  params.Pg_N_avg[47] = params.Pg_N_avg_47;
  params.ug_N[47] = params.ug_N_47;
  params.Vg_N_avg[47] = params.Vg_N_avg_47;
  params.Thetag_N_avg[47] = params.Thetag_N_avg_47;
  params.vg_N[47] = params.vg_N_47;
  params.Pg_N_init[48] = params.Pg_N_init_48;
  params.Pg_N_avg[48] = params.Pg_N_avg_48;
  params.ug_N[48] = params.ug_N_48;
  params.Vg_N_avg[48] = params.Vg_N_avg_48;
  params.Thetag_N_avg[48] = params.Thetag_N_avg_48;
  params.vg_N[48] = params.vg_N_48;
  params.Pg_N_init[49] = params.Pg_N_init_49;
  params.Pg_N_avg[49] = params.Pg_N_avg_49;
  params.ug_N[49] = params.ug_N_49;
  params.Vg_N_avg[49] = params.Vg_N_avg_49;
  params.Thetag_N_avg[49] = params.Thetag_N_avg_49;
  params.vg_N[49] = params.vg_N_49;
  params.Pg_N_init[50] = params.Pg_N_init_50;
  params.Pg_N_avg[50] = params.Pg_N_avg_50;
  params.ug_N[50] = params.ug_N_50;
  params.Vg_N_avg[50] = params.Vg_N_avg_50;
  params.Thetag_N_avg[50] = params.Thetag_N_avg_50;
  params.vg_N[50] = params.vg_N_50;
  params.Pg_N_init[51] = params.Pg_N_init_51;
  params.Pg_N_avg[51] = params.Pg_N_avg_51;
  params.ug_N[51] = params.ug_N_51;
  params.Vg_N_avg[51] = params.Vg_N_avg_51;
  params.Thetag_N_avg[51] = params.Thetag_N_avg_51;
  params.vg_N[51] = params.vg_N_51;
  params.Pg_N_init[52] = params.Pg_N_init_52;
  params.Pg_N_avg[52] = params.Pg_N_avg_52;
  params.ug_N[52] = params.ug_N_52;
  params.Vg_N_avg[52] = params.Vg_N_avg_52;
  params.Thetag_N_avg[52] = params.Thetag_N_avg_52;
  params.vg_N[52] = params.vg_N_52;
  params.Pg_N_init[53] = params.Pg_N_init_53;
  params.Pg_N_avg[53] = params.Pg_N_avg_53;
  params.ug_N[53] = params.ug_N_53;
  params.Vg_N_avg[53] = params.Vg_N_avg_53;
  params.Thetag_N_avg[53] = params.Thetag_N_avg_53;
  params.vg_N[53] = params.vg_N_53;
  params.Pg_N_init[54] = params.Pg_N_init_54;
  params.Pg_N_avg[54] = params.Pg_N_avg_54;
  params.ug_N[54] = params.ug_N_54;
  params.Vg_N_avg[54] = params.Vg_N_avg_54;
  params.Thetag_N_avg[54] = params.Thetag_N_avg_54;
  params.vg_N[54] = params.vg_N_54;
  params.Pg_N_init[55] = params.Pg_N_init_55;
  params.Pg_N_avg[55] = params.Pg_N_avg_55;
  params.ug_N[55] = params.ug_N_55;
  params.Vg_N_avg[55] = params.Vg_N_avg_55;
  params.Thetag_N_avg[55] = params.Thetag_N_avg_55;
  params.vg_N[55] = params.vg_N_55;
  params.Pg_N_init[56] = params.Pg_N_init_56;
  params.Pg_N_avg[56] = params.Pg_N_avg_56;
  params.ug_N[56] = params.ug_N_56;
  params.Vg_N_avg[56] = params.Vg_N_avg_56;
  params.Thetag_N_avg[56] = params.Thetag_N_avg_56;
  params.vg_N[56] = params.vg_N_56;
  params.Pg_N_init[57] = params.Pg_N_init_57;
  params.Pg_N_avg[57] = params.Pg_N_avg_57;
  params.ug_N[57] = params.ug_N_57;
  params.Vg_N_avg[57] = params.Vg_N_avg_57;
  params.Thetag_N_avg[57] = params.Thetag_N_avg_57;
  params.vg_N[57] = params.vg_N_57;
  params.Pg_N_init[58] = params.Pg_N_init_58;
  params.Pg_N_avg[58] = params.Pg_N_avg_58;
  params.ug_N[58] = params.ug_N_58;
  params.Vg_N_avg[58] = params.Vg_N_avg_58;
  params.Thetag_N_avg[58] = params.Thetag_N_avg_58;
  params.vg_N[58] = params.vg_N_58;
  params.Pg_N_init[59] = params.Pg_N_init_59;
  params.Pg_N_avg[59] = params.Pg_N_avg_59;
  params.ug_N[59] = params.ug_N_59;
  params.Vg_N_avg[59] = params.Vg_N_avg_59;
  params.Thetag_N_avg[59] = params.Thetag_N_avg_59;
  params.vg_N[59] = params.vg_N_59;
  params.Pg_N_init[60] = params.Pg_N_init_60;
  params.Pg_N_avg[60] = params.Pg_N_avg_60;
  params.ug_N[60] = params.ug_N_60;
  params.Vg_N_avg[60] = params.Vg_N_avg_60;
  params.Thetag_N_avg[60] = params.Thetag_N_avg_60;
  params.vg_N[60] = params.vg_N_60;
  params.Pg_N_init[61] = params.Pg_N_init_61;
  params.Pg_N_avg[61] = params.Pg_N_avg_61;
  params.ug_N[61] = params.ug_N_61;
  params.Vg_N_avg[61] = params.Vg_N_avg_61;
  params.Thetag_N_avg[61] = params.Thetag_N_avg_61;
  params.vg_N[61] = params.vg_N_61;
  params.Pg_N_init[62] = params.Pg_N_init_62;
  params.Pg_N_avg[62] = params.Pg_N_avg_62;
  params.ug_N[62] = params.ug_N_62;
  params.Vg_N_avg[62] = params.Vg_N_avg_62;
  params.Thetag_N_avg[62] = params.Thetag_N_avg_62;
  params.vg_N[62] = params.vg_N_62;
  params.Pg_N_init[63] = params.Pg_N_init_63;
  params.Pg_N_avg[63] = params.Pg_N_avg_63;
  params.ug_N[63] = params.ug_N_63;
  params.Vg_N_avg[63] = params.Vg_N_avg_63;
  params.Thetag_N_avg[63] = params.Thetag_N_avg_63;
  params.vg_N[63] = params.vg_N_63;
  params.Pg_N_init[64] = params.Pg_N_init_64;
  params.Pg_N_avg[64] = params.Pg_N_avg_64;
  params.ug_N[64] = params.ug_N_64;
  params.Vg_N_avg[64] = params.Vg_N_avg_64;
  params.Thetag_N_avg[64] = params.Thetag_N_avg_64;
  params.vg_N[64] = params.vg_N_64;
  params.Pg_N_init[65] = params.Pg_N_init_65;
  params.Pg_N_avg[65] = params.Pg_N_avg_65;
  params.ug_N[65] = params.ug_N_65;
  params.Vg_N_avg[65] = params.Vg_N_avg_65;
  params.Thetag_N_avg[65] = params.Thetag_N_avg_65;
  params.vg_N[65] = params.vg_N_65;
  params.Pg_N_init[66] = params.Pg_N_init_66;
  params.Pg_N_avg[66] = params.Pg_N_avg_66;
  params.ug_N[66] = params.ug_N_66;
  params.Vg_N_avg[66] = params.Vg_N_avg_66;
  params.Thetag_N_avg[66] = params.Thetag_N_avg_66;
  params.vg_N[66] = params.vg_N_66;
  params.Pg_N_init[67] = params.Pg_N_init_67;
  params.Pg_N_avg[67] = params.Pg_N_avg_67;
  params.ug_N[67] = params.ug_N_67;
  params.Vg_N_avg[67] = params.Vg_N_avg_67;
  params.Thetag_N_avg[67] = params.Thetag_N_avg_67;
  params.vg_N[67] = params.vg_N_67;
  params.Pg_N_init[68] = params.Pg_N_init_68;
  params.Pg_N_avg[68] = params.Pg_N_avg_68;
  params.ug_N[68] = params.ug_N_68;
  params.Vg_N_avg[68] = params.Vg_N_avg_68;
  params.Thetag_N_avg[68] = params.Thetag_N_avg_68;
  params.vg_N[68] = params.vg_N_68;
  params.Pg_N_init[69] = params.Pg_N_init_69;
  params.Pg_N_avg[69] = params.Pg_N_avg_69;
  params.ug_N[69] = params.ug_N_69;
  params.Vg_N_avg[69] = params.Vg_N_avg_69;
  params.Thetag_N_avg[69] = params.Thetag_N_avg_69;
  params.vg_N[69] = params.vg_N_69;
  params.Pg_N_init[70] = params.Pg_N_init_70;
  params.Pg_N_avg[70] = params.Pg_N_avg_70;
  params.ug_N[70] = params.ug_N_70;
  params.Vg_N_avg[70] = params.Vg_N_avg_70;
  params.Thetag_N_avg[70] = params.Thetag_N_avg_70;
  params.vg_N[70] = params.vg_N_70;
  params.Pg_N_init[71] = params.Pg_N_init_71;
  params.Pg_N_avg[71] = params.Pg_N_avg_71;
  params.ug_N[71] = params.ug_N_71;
  params.Vg_N_avg[71] = params.Vg_N_avg_71;
  params.Thetag_N_avg[71] = params.Thetag_N_avg_71;
  params.vg_N[71] = params.vg_N_71;
  params.Pg_N_init[72] = params.Pg_N_init_72;
  params.Pg_N_avg[72] = params.Pg_N_avg_72;
  params.ug_N[72] = params.ug_N_72;
  params.Vg_N_avg[72] = params.Vg_N_avg_72;
  params.Thetag_N_avg[72] = params.Thetag_N_avg_72;
  params.vg_N[72] = params.vg_N_72;
  params.Pg_N_init[73] = params.Pg_N_init_73;
  params.Pg_N_avg[73] = params.Pg_N_avg_73;
  params.ug_N[73] = params.ug_N_73;
  params.Vg_N_avg[73] = params.Vg_N_avg_73;
  params.Thetag_N_avg[73] = params.Thetag_N_avg_73;
  params.vg_N[73] = params.vg_N_73;
  params.Pg_N_init[74] = params.Pg_N_init_74;
  params.Pg_N_avg[74] = params.Pg_N_avg_74;
  params.ug_N[74] = params.ug_N_74;
  params.Vg_N_avg[74] = params.Vg_N_avg_74;
  params.Thetag_N_avg[74] = params.Thetag_N_avg_74;
  params.vg_N[74] = params.vg_N_74;
  params.Pg_N_init[75] = params.Pg_N_init_75;
  params.Pg_N_avg[75] = params.Pg_N_avg_75;
  params.ug_N[75] = params.ug_N_75;
  params.Vg_N_avg[75] = params.Vg_N_avg_75;
  params.Thetag_N_avg[75] = params.Thetag_N_avg_75;
  params.vg_N[75] = params.vg_N_75;
  params.Pg_N_init[76] = params.Pg_N_init_76;
  params.Pg_N_avg[76] = params.Pg_N_avg_76;
  params.ug_N[76] = params.ug_N_76;
  params.Vg_N_avg[76] = params.Vg_N_avg_76;
  params.Thetag_N_avg[76] = params.Thetag_N_avg_76;
  params.vg_N[76] = params.vg_N_76;
  params.Pg_N_init[77] = params.Pg_N_init_77;
  params.Pg_N_avg[77] = params.Pg_N_avg_77;
  params.ug_N[77] = params.ug_N_77;
  params.Vg_N_avg[77] = params.Vg_N_avg_77;
  params.Thetag_N_avg[77] = params.Thetag_N_avg_77;
  params.vg_N[77] = params.vg_N_77;
  params.Pg_N_init[78] = params.Pg_N_init_78;
  params.Pg_N_avg[78] = params.Pg_N_avg_78;
  params.ug_N[78] = params.ug_N_78;
  params.Vg_N_avg[78] = params.Vg_N_avg_78;
  params.Thetag_N_avg[78] = params.Thetag_N_avg_78;
  params.vg_N[78] = params.vg_N_78;
  params.Pg_N_init[79] = params.Pg_N_init_79;
  params.Pg_N_avg[79] = params.Pg_N_avg_79;
  params.ug_N[79] = params.ug_N_79;
  params.Vg_N_avg[79] = params.Vg_N_avg_79;
  params.Thetag_N_avg[79] = params.Thetag_N_avg_79;
  params.vg_N[79] = params.vg_N_79;
  params.Pg_N_init[80] = params.Pg_N_init_80;
  params.Pg_N_avg[80] = params.Pg_N_avg_80;
  params.ug_N[80] = params.ug_N_80;
  params.Vg_N_avg[80] = params.Vg_N_avg_80;
  params.Thetag_N_avg[80] = params.Thetag_N_avg_80;
  params.vg_N[80] = params.vg_N_80;
  params.Pg_N_init[81] = params.Pg_N_init_81;
  params.Pg_N_avg[81] = params.Pg_N_avg_81;
  params.ug_N[81] = params.ug_N_81;
  params.Vg_N_avg[81] = params.Vg_N_avg_81;
  params.Thetag_N_avg[81] = params.Thetag_N_avg_81;
  params.vg_N[81] = params.vg_N_81;
  params.Pg_N_init[82] = params.Pg_N_init_82;
  params.Pg_N_avg[82] = params.Pg_N_avg_82;
  params.ug_N[82] = params.ug_N_82;
  params.Vg_N_avg[82] = params.Vg_N_avg_82;
  params.Thetag_N_avg[82] = params.Thetag_N_avg_82;
  params.vg_N[82] = params.vg_N_82;
  params.Pg_N_init[83] = params.Pg_N_init_83;
  params.Pg_N_avg[83] = params.Pg_N_avg_83;
  params.ug_N[83] = params.ug_N_83;
  params.Vg_N_avg[83] = params.Vg_N_avg_83;
  params.Thetag_N_avg[83] = params.Thetag_N_avg_83;
  params.vg_N[83] = params.vg_N_83;
  params.Pg_N_init[84] = params.Pg_N_init_84;
  params.Pg_N_avg[84] = params.Pg_N_avg_84;
  params.ug_N[84] = params.ug_N_84;
  params.Vg_N_avg[84] = params.Vg_N_avg_84;
  params.Thetag_N_avg[84] = params.Thetag_N_avg_84;
  params.vg_N[84] = params.vg_N_84;
  params.Pg_N_init[85] = params.Pg_N_init_85;
  params.Pg_N_avg[85] = params.Pg_N_avg_85;
  params.ug_N[85] = params.ug_N_85;
  params.Vg_N_avg[85] = params.Vg_N_avg_85;
  params.Thetag_N_avg[85] = params.Thetag_N_avg_85;
  params.vg_N[85] = params.vg_N_85;
  params.Pg_N_init[86] = params.Pg_N_init_86;
  params.Pg_N_avg[86] = params.Pg_N_avg_86;
  params.ug_N[86] = params.ug_N_86;
  params.Vg_N_avg[86] = params.Vg_N_avg_86;
  params.Thetag_N_avg[86] = params.Thetag_N_avg_86;
  params.vg_N[86] = params.vg_N_86;
  params.Pg_N_init[87] = params.Pg_N_init_87;
  params.Pg_N_avg[87] = params.Pg_N_avg_87;
  params.ug_N[87] = params.ug_N_87;
  params.Vg_N_avg[87] = params.Vg_N_avg_87;
  params.Thetag_N_avg[87] = params.Thetag_N_avg_87;
  params.vg_N[87] = params.vg_N_87;
  params.Pg_N_init[88] = params.Pg_N_init_88;
  params.Pg_N_avg[88] = params.Pg_N_avg_88;
  params.ug_N[88] = params.ug_N_88;
  params.Vg_N_avg[88] = params.Vg_N_avg_88;
  params.Thetag_N_avg[88] = params.Thetag_N_avg_88;
  params.vg_N[88] = params.vg_N_88;
  params.Pg_N_init[89] = params.Pg_N_init_89;
  params.Pg_N_avg[89] = params.Pg_N_avg_89;
  params.ug_N[89] = params.ug_N_89;
  params.Vg_N_avg[89] = params.Vg_N_avg_89;
  params.Thetag_N_avg[89] = params.Thetag_N_avg_89;
  params.vg_N[89] = params.vg_N_89;
  params.Pg_N_init[90] = params.Pg_N_init_90;
  params.Pg_N_avg[90] = params.Pg_N_avg_90;
  params.ug_N[90] = params.ug_N_90;
  params.Vg_N_avg[90] = params.Vg_N_avg_90;
  params.Thetag_N_avg[90] = params.Thetag_N_avg_90;
  params.vg_N[90] = params.vg_N_90;
  params.Pg_N_init[91] = params.Pg_N_init_91;
  params.Pg_N_avg[91] = params.Pg_N_avg_91;
  params.ug_N[91] = params.ug_N_91;
  params.Vg_N_avg[91] = params.Vg_N_avg_91;
  params.Thetag_N_avg[91] = params.Thetag_N_avg_91;
  params.vg_N[91] = params.vg_N_91;
  params.Pg_N_init[92] = params.Pg_N_init_92;
  params.Pg_N_avg[92] = params.Pg_N_avg_92;
  params.ug_N[92] = params.ug_N_92;
  params.Vg_N_avg[92] = params.Vg_N_avg_92;
  params.Thetag_N_avg[92] = params.Thetag_N_avg_92;
  params.vg_N[92] = params.vg_N_92;
  params.Pg_N_init[93] = params.Pg_N_init_93;
  params.Pg_N_avg[93] = params.Pg_N_avg_93;
  params.ug_N[93] = params.ug_N_93;
  params.Vg_N_avg[93] = params.Vg_N_avg_93;
  params.Thetag_N_avg[93] = params.Thetag_N_avg_93;
  params.vg_N[93] = params.vg_N_93;
  params.Pg_N_init[94] = params.Pg_N_init_94;
  params.Pg_N_avg[94] = params.Pg_N_avg_94;
  params.ug_N[94] = params.ug_N_94;
  params.Vg_N_avg[94] = params.Vg_N_avg_94;
  params.Thetag_N_avg[94] = params.Thetag_N_avg_94;
  params.vg_N[94] = params.vg_N_94;
  params.Pg_N_init[95] = params.Pg_N_init_95;
  params.Pg_N_avg[95] = params.Pg_N_avg_95;
  params.ug_N[95] = params.ug_N_95;
  params.Vg_N_avg[95] = params.Vg_N_avg_95;
  params.Thetag_N_avg[95] = params.Thetag_N_avg_95;
  params.vg_N[95] = params.vg_N_95;
  params.Pg_N_init[96] = params.Pg_N_init_96;
  params.Pg_N_avg[96] = params.Pg_N_avg_96;
  params.ug_N[96] = params.ug_N_96;
  params.Vg_N_avg[96] = params.Vg_N_avg_96;
  params.Thetag_N_avg[96] = params.Thetag_N_avg_96;
  params.vg_N[96] = params.vg_N_96;
  params.Pg_N_init[97] = params.Pg_N_init_97;
  params.Pg_N_avg[97] = params.Pg_N_avg_97;
  params.ug_N[97] = params.ug_N_97;
  params.Vg_N_avg[97] = params.Vg_N_avg_97;
  params.Thetag_N_avg[97] = params.Thetag_N_avg_97;
  params.vg_N[97] = params.vg_N_97;
  params.Pg_N_init[98] = params.Pg_N_init_98;
  params.Pg_N_avg[98] = params.Pg_N_avg_98;
  params.ug_N[98] = params.ug_N_98;
  params.Vg_N_avg[98] = params.Vg_N_avg_98;
  params.Thetag_N_avg[98] = params.Thetag_N_avg_98;
  params.vg_N[98] = params.vg_N_98;
  params.Pg_N_init[99] = params.Pg_N_init_99;
  params.Pg_N_avg[99] = params.Pg_N_avg_99;
  params.ug_N[99] = params.ug_N_99;
  params.Vg_N_avg[99] = params.Vg_N_avg_99;
  params.Thetag_N_avg[99] = params.Thetag_N_avg_99;
  params.vg_N[99] = params.vg_N_99;
  params.Pg_N_init[100] = params.Pg_N_init_100;
  params.Pg_N_avg[100] = params.Pg_N_avg_100;
  params.ug_N[100] = params.ug_N_100;
  params.Vg_N_avg[100] = params.Vg_N_avg_100;
  params.Thetag_N_avg[100] = params.Thetag_N_avg_100;
  params.vg_N[100] = params.vg_N_100;
  params.Pg_N_init[101] = params.Pg_N_init_101;
  params.Pg_N_avg[101] = params.Pg_N_avg_101;
  params.ug_N[101] = params.ug_N_101;
  params.Vg_N_avg[101] = params.Vg_N_avg_101;
  params.Thetag_N_avg[101] = params.Thetag_N_avg_101;
  params.vg_N[101] = params.vg_N_101;
}
void Gensolver::setup_indexed_optvars(void) {
  /* In CVXGEN, you can say */
  /*   variables */
  /*     x[i] (5), i=2..4 */
  /*   end */
  /* This function sets up x[3] to be a pointer to x_3, which is a length-5 */
  /* vector of doubles. */
  /* If you access variables that you haven't defined in CVXGEN, the result */
  /* is undefined. */
  vars.Thetag[1] = vars.Thetag_1;
  vars.Thetag[2] = vars.Thetag_2;
  vars.Thetag[3] = vars.Thetag_3;
  vars.Thetag[4] = vars.Thetag_4;
  vars.Thetag[5] = vars.Thetag_5;
  vars.Thetag[6] = vars.Thetag_6;
  vars.Thetag[7] = vars.Thetag_7;
  vars.Thetag[8] = vars.Thetag_8;
  vars.Thetag[9] = vars.Thetag_9;
  vars.Thetag[10] = vars.Thetag_10;
  vars.Thetag[11] = vars.Thetag_11;
  vars.Thetag[12] = vars.Thetag_12;
  vars.Thetag[13] = vars.Thetag_13;
  vars.Thetag[14] = vars.Thetag_14;
  vars.Thetag[15] = vars.Thetag_15;
  vars.Thetag[16] = vars.Thetag_16;
  vars.Thetag[17] = vars.Thetag_17;
  vars.Thetag[18] = vars.Thetag_18;
  vars.Thetag[19] = vars.Thetag_19;
  vars.Thetag[20] = vars.Thetag_20;
  vars.Thetag[21] = vars.Thetag_21;
  vars.Thetag[22] = vars.Thetag_22;
  vars.Thetag[23] = vars.Thetag_23;
  vars.Thetag[24] = vars.Thetag_24;
  vars.Thetag[25] = vars.Thetag_25;
  vars.Thetag[26] = vars.Thetag_26;
  vars.Thetag[27] = vars.Thetag_27;
  vars.Thetag[28] = vars.Thetag_28;
  vars.Thetag[29] = vars.Thetag_29;
  vars.Thetag[30] = vars.Thetag_30;
  vars.Thetag[31] = vars.Thetag_31;
  vars.Thetag[32] = vars.Thetag_32;
  vars.Thetag[33] = vars.Thetag_33;
  vars.Thetag[34] = vars.Thetag_34;
  vars.Thetag[35] = vars.Thetag_35;
  vars.Thetag[36] = vars.Thetag_36;
  vars.Thetag[37] = vars.Thetag_37;
  vars.Thetag[38] = vars.Thetag_38;
  vars.Thetag[39] = vars.Thetag_39;
  vars.Thetag[40] = vars.Thetag_40;
  vars.Thetag[41] = vars.Thetag_41;
  vars.Thetag[42] = vars.Thetag_42;
  vars.Thetag[43] = vars.Thetag_43;
  vars.Thetag[44] = vars.Thetag_44;
  vars.Thetag[45] = vars.Thetag_45;
  vars.Thetag[46] = vars.Thetag_46;
  vars.Thetag[47] = vars.Thetag_47;
  vars.Thetag[48] = vars.Thetag_48;
  vars.Thetag[49] = vars.Thetag_49;
  vars.Thetag[50] = vars.Thetag_50;
  vars.Thetag[51] = vars.Thetag_51;
  vars.Thetag[52] = vars.Thetag_52;
  vars.Thetag[53] = vars.Thetag_53;
  vars.Thetag[54] = vars.Thetag_54;
  vars.Thetag[55] = vars.Thetag_55;
  vars.Thetag[56] = vars.Thetag_56;
  vars.Thetag[57] = vars.Thetag_57;
  vars.Thetag[58] = vars.Thetag_58;
  vars.Thetag[59] = vars.Thetag_59;
  vars.Thetag[60] = vars.Thetag_60;
  vars.Thetag[61] = vars.Thetag_61;
  vars.Thetag[62] = vars.Thetag_62;
  vars.Thetag[63] = vars.Thetag_63;
  vars.Thetag[64] = vars.Thetag_64;
  vars.Thetag[65] = vars.Thetag_65;
  vars.Thetag[66] = vars.Thetag_66;
  vars.Thetag[67] = vars.Thetag_67;
  vars.Thetag[68] = vars.Thetag_68;
  vars.Thetag[69] = vars.Thetag_69;
  vars.Thetag[70] = vars.Thetag_70;
  vars.Thetag[71] = vars.Thetag_71;
  vars.Thetag[72] = vars.Thetag_72;
  vars.Thetag[73] = vars.Thetag_73;
  vars.Thetag[74] = vars.Thetag_74;
  vars.Thetag[75] = vars.Thetag_75;
  vars.Thetag[76] = vars.Thetag_76;
  vars.Thetag[77] = vars.Thetag_77;
  vars.Thetag[78] = vars.Thetag_78;
  vars.Thetag[79] = vars.Thetag_79;
  vars.Thetag[80] = vars.Thetag_80;
  vars.Thetag[81] = vars.Thetag_81;
  vars.Thetag[82] = vars.Thetag_82;
  vars.Thetag[83] = vars.Thetag_83;
  vars.Thetag[84] = vars.Thetag_84;
  vars.Thetag[85] = vars.Thetag_85;
  vars.Thetag[86] = vars.Thetag_86;
  vars.Thetag[87] = vars.Thetag_87;
  vars.Thetag[88] = vars.Thetag_88;
  vars.Thetag[89] = vars.Thetag_89;
  vars.Thetag[90] = vars.Thetag_90;
  vars.Thetag[91] = vars.Thetag_91;
  vars.Thetag[92] = vars.Thetag_92;
  vars.Thetag[93] = vars.Thetag_93;
  vars.Thetag[94] = vars.Thetag_94;
  vars.Thetag[95] = vars.Thetag_95;
  vars.Thetag[96] = vars.Thetag_96;
  vars.Thetag[97] = vars.Thetag_97;
  vars.Thetag[98] = vars.Thetag_98;
  vars.Thetag[99] = vars.Thetag_99;
  vars.Thetag[100] = vars.Thetag_100;
  vars.Thetag[101] = vars.Thetag_101;
}
void Gensolver::setup_indexing(void) {
  setup_pointers();
  setup_indexed_params();
  setup_indexed_optvars();
}
void Gensolver::set_start(void) {
  int i;
  for (i = 0; i < 102; i++)
    work.x[i] = 0;
  for (i = 0; i < 0; i++)
    work.y[i] = 0;
  for (i = 0; i < 2; i++)
    work.s[i] = (work.h[i] > 0) ? work.h[i] : settings.s_init;
  for (i = 0; i < 2; i++)
    work.z[i] = settings.z_init;
}
double Gensolver::eval_objv(void) {
  int i;
  double objv;
  /* Borrow space in work.rhs. */
  multbyP(work.rhs, work.x);
  objv = 0;
  for (i = 0; i < 102; i++)
    objv += work.x[i]*work.rhs[i];
  objv *= 0.5;
  for (i = 0; i < 102; i++)
    objv += work.q[i]*work.x[i];
  objv += params.c0[0]+work.quad_861253439488[0]+work.quad_335606009856[0]+work.quad_419630354432[0]+work.quad_300112478208[0]+work.quad_722335502336[0]+work.quad_863528128512[0]+work.quad_407892983808[0]+work.quad_53514031104[0]+work.quad_198013468672[0]+work.quad_48438943744[0]+work.quad_898365714432[0]+work.quad_934929342464[0]+work.quad_793422544896[0]+work.quad_183681134592[0]+work.quad_924824883200[0]+work.quad_774359400448[0]+work.quad_364793888768[0]+work.quad_831331065856[0]+work.quad_24379666432[0]+work.quad_47350718464[0]+work.quad_418591776768[0]+work.quad_358617378816[0]+work.quad_189427146752[0]+work.quad_811009290240[0]+work.quad_340342550528[0]+work.quad_861425090560[0]+work.quad_522812354560[0]+work.quad_347927187456[0]+work.quad_724215824384[0]+work.quad_488040783872[0]+work.quad_750720192512[0]+work.quad_575932559360[0]+work.quad_497126731776[0]+work.quad_446440656896[0]+work.quad_220748931072[0]+work.quad_576835772416[0]+work.quad_327014187008[0]+work.quad_77213671424[0]+work.quad_634046689280[0]+work.quad_376276512768[0]+work.quad_435014901760[0]+work.quad_194730110976[0]+work.quad_687358853120[0]+work.quad_748989894656[0]+work.quad_190680965120[0]+work.quad_274986213376[0]+work.quad_819154403328[0]+work.quad_211870208000[0]+work.quad_147546587136[0]+work.quad_31183937536[0]+work.quad_28386426880[0]+work.quad_476108271616[0]+work.quad_294418444288[0]+work.quad_169273020416[0]+work.quad_987523264512[0]+work.quad_55176798208[0]+work.quad_526459392000[0]+work.quad_938506014720[0]+work.quad_398236438528[0]+work.quad_408717836288[0]+work.quad_184308461568[0]+work.quad_330616233984[0]+work.quad_411712237568[0]+work.quad_642560991232[0]+work.quad_172000874496[0]+work.quad_877709885440[0]+work.quad_236200529920[0]+work.quad_953866592256[0]+work.quad_608829231104[0]+work.quad_265570734080[0]+work.quad_225263394816[0]+work.quad_434793504768[0]+work.quad_984017977344[0]+work.quad_526619181056[0]+work.quad_566099726336[0]+work.quad_879322742784[0]+work.quad_620654563328[0]+work.quad_485479587840[0]+work.quad_808293044224[0]+work.quad_468686970880[0]+work.quad_563134095360[0]+work.quad_370423967744[0]+work.quad_222369783808[0]+work.quad_83489009664[0]+work.quad_573775224832[0]+work.quad_81818914816[0]+work.quad_869895589888[0]+work.quad_456437583872[0]+work.quad_90734665728[0]+work.quad_165580480512[0]+work.quad_225093988352[0]+work.quad_944332083200[0]+work.quad_198883876864[0]+work.quad_30941691904[0]+work.quad_692068392960[0]+work.quad_404779089920[0]+work.quad_637665005568[0]+work.quad_719521869824[0]+work.quad_480708186112[0]+work.quad_109914923008[0]+work.quad_101608513536[0]+work.quad_199411765248[0]+work.quad_901289631744[0]+work.quad_594054291456[0]+work.quad_404078174208[0]+work.quad_244563038208[0]+work.quad_338757373952[0]+work.quad_655083196416[0]+work.quad_489744039936[0]+work.quad_259549028352[0]+work.quad_250154500096[0]+work.quad_283916939264[0]+work.quad_504322719744[0]+work.quad_996765118464[0]+work.quad_483569917952[0]+work.quad_158537359360[0]+work.quad_626608463872[0]+work.quad_927129829376[0]+work.quad_790822236160[0]+work.quad_918575378432[0]+work.quad_995595960320[0]+work.quad_529630486528[0]+work.quad_79251795968[0]+work.quad_475943071744[0]+work.quad_146468945920[0]+work.quad_86002155520[0]+work.quad_351835660288[0]+work.quad_898473287680[0]+work.quad_715947200512[0]+work.quad_824253415424[0]+work.quad_494006571008[0]+work.quad_185061429248[0]+work.quad_796629155840[0]+work.quad_449770254336[0]+work.quad_947342782464[0]+work.quad_604877107200[0]+work.quad_680640479232[0]+work.quad_9457143808[0]+work.quad_717531140096[0]+work.quad_634949398528[0]+work.quad_564056838144[0]+work.quad_946810548224[0]+work.quad_70571728896[0]+work.quad_286652420096[0]+work.quad_173991247872[0]+work.quad_474489081856[0]+work.quad_880120451072[0]+work.quad_782250987520[0]+work.quad_57536741376[0]+work.quad_849656963072[0]+work.quad_35205603328[0]+work.quad_658468995072[0]+work.quad_356423053312[0]+work.quad_283962642432[0]+work.quad_547807477760[0]+work.quad_382444605440[0]+work.quad_539754852352[0]+work.quad_230561599488[0]+work.quad_865930481664[0]+work.quad_541608677376[0]+work.quad_125357936640[0]+work.quad_619719733248[0]+work.quad_824211386368[0]+work.quad_394753474560[0]+work.quad_547133394944[0]+work.quad_209782870016[0]+work.quad_381733597184[0]+work.quad_152716124160[0]+work.quad_128809979904[0]+work.quad_335236542464[0]+work.quad_909988339712[0]+work.quad_852921757696[0]+work.quad_787442696192[0]+work.quad_961277771776[0]+work.quad_939277180928[0]+work.quad_429044678656[0]+work.quad_861783474176[0]+work.quad_340061249536[0]+work.quad_279979859968[0]+work.quad_869539332096[0]+work.quad_539265785856[0]+work.quad_872875143168[0]+work.quad_940092141568[0]+work.quad_320369504256[0]+work.quad_814284275712[0]+work.quad_850341859328[0]+work.quad_668125876224[0]+work.quad_768845512704[0]+work.quad_180052918272[0]+work.quad_637222821888[0]+work.quad_117911429120[0]+work.quad_793053450240[0]+work.quad_161320878080[0]+work.quad_502933229568[0]+work.quad_890543960064[0]+work.quad_620316852224[0]+work.quad_682189721600[0]+work.quad_367930048512[0]+work.quad_515601072128[0]+work.quad_600421740544[0]+work.quad_657550438400[0]+work.quad_478485061632[0];
  return objv;
}
void Gensolver::fillrhs_aff(void) {
  int i;
  double *r1, *r2, *r3, *r4;
  r1 = work.rhs;
  r2 = work.rhs + 102;
  r3 = work.rhs + 104;
  r4 = work.rhs + 106;
  /* r1 = -A^Ty - G^Tz - Px - q. */
  multbymAT(r1, work.y);
  multbymGT(work.buffer, work.z);
  for (i = 0; i < 102; i++)
    r1[i] += work.buffer[i];
  multbyP(work.buffer, work.x);
  for (i = 0; i < 102; i++)
    r1[i] -= work.buffer[i] + work.q[i];
  /* r2 = -z. */
  for (i = 0; i < 2; i++)
    r2[i] = -work.z[i];
  /* r3 = -Gx - s + h. */
  multbymG(r3, work.x);
  for (i = 0; i < 2; i++)
    r3[i] += -work.s[i] + work.h[i];
  /* r4 = -Ax + b. */
  multbymA(r4, work.x);
  for (i = 0; i < 0; i++)
    r4[i] += work.b[i];
}
void Gensolver::fillrhs_cc(void) {
  int i;
  double *r2;
  double *ds_aff, *dz_aff;
  double mu;
  double alpha;
  double sigma;
  double smu;
  double minval;
  r2 = work.rhs + 102;
  ds_aff = work.lhs_aff + 102;
  dz_aff = work.lhs_aff + 104;
  mu = 0;
  for (i = 0; i < 2; i++)
    mu += work.s[i]*work.z[i];
  /* Don't finish calculating mu quite yet. */
  /* Find min(min(ds./s), min(dz./z)). */
  minval = 0;
  for (i = 0; i < 2; i++)
    if (ds_aff[i] < minval*work.s[i])
      minval = ds_aff[i]/work.s[i];
  for (i = 0; i < 2; i++)
    if (dz_aff[i] < minval*work.z[i])
      minval = dz_aff[i]/work.z[i];
  /* Find alpha. */
  if (-1 < minval)
      alpha = 1;
  else
      alpha = -1/minval;
  sigma = 0;
  for (i = 0; i < 2; i++)
    sigma += (work.s[i] + alpha*ds_aff[i])*
      (work.z[i] + alpha*dz_aff[i]);
  sigma /= mu;
  sigma = sigma*sigma*sigma;
  /* Finish calculating mu now. */
  mu *= 0.5;
  smu = sigma*mu;
  /* Fill-in the rhs. */
  for (i = 0; i < 102; i++)
    work.rhs[i] = 0;
  for (i = 104; i < 106; i++)
    work.rhs[i] = 0;
  for (i = 0; i < 2; i++)
    r2[i] = work.s_inv[i]*(smu - ds_aff[i]*dz_aff[i]);
}
void Gensolver::refine(double *target, double *var) {
  int i, j;
  double *residual = work.buffer;
  double norm2;
  double *new_var = work.buffer2;
  for (j = 0; j < settings.refine_steps; j++) {
    norm2 = 0;
    matrix_multiply(residual, var);
    for (i = 0; i < 106; i++) {
      residual[i] = residual[i] - target[i];
      norm2 += residual[i]*residual[i];
    }
#ifndef ZERO_LIBRARY_MODE
    if (settings.verbose_refinement) {
      if (j == 0)
        printf("Initial residual before refinement has norm squared %.6g.\n", norm2);
      else
        printf("After refinement we get squared norm %.6g.\n", norm2);
    }
#endif
    /* Solve to find new_var = KKT \ (target - A*var). */
    ldl_solve(residual, new_var);
    /* Update var += new_var, or var += KKT \ (target - A*var). */
    for (i = 0; i < 106; i++) {
      var[i] -= new_var[i];
    }
  }
#ifndef ZERO_LIBRARY_MODE
  if (settings.verbose_refinement) {
    /* Check the residual once more, but only if we're reporting it, since */
    /* it's expensive. */
    norm2 = 0;
    matrix_multiply(residual, var);
    for (i = 0; i < 106; i++) {
      residual[i] = residual[i] - target[i];
      norm2 += residual[i]*residual[i];
    }
    if (j == 0)
      printf("Initial residual before refinement has norm squared %.6g.\n", norm2);
    else
      printf("After refinement we get squared norm %.6g.\n", norm2);
  }
#endif
}
double Gensolver::calc_ineq_resid_squared(void) {
  /* Calculates the norm ||-Gx - s + h||. */
  double norm2_squared;
  int i;
  /* Find -Gx. */
  multbymG(work.buffer, work.x);
  /* Add -s + h. */
  for (i = 0; i < 2; i++)
    work.buffer[i] += -work.s[i] + work.h[i];
  /* Now find the squared norm. */
  norm2_squared = 0;
  for (i = 0; i < 2; i++)
    norm2_squared += work.buffer[i]*work.buffer[i];
  return norm2_squared;
}
double Gensolver::calc_eq_resid_squared(void) {
  /* Calculates the norm ||-Ax + b||. */
  double norm2_squared;
  int i;
  /* Find -Ax. */
  multbymA(work.buffer, work.x);
  /* Add +b. */
  for (i = 0; i < 0; i++)
    work.buffer[i] += work.b[i];
  /* Now find the squared norm. */
  norm2_squared = 0;
  for (i = 0; i < 0; i++)
    norm2_squared += work.buffer[i]*work.buffer[i];
  return norm2_squared;
}
void Gensolver::better_start(void) {
  /* Calculates a better starting point, using a similar approach to CVXOPT. */
  /* Not yet speed optimized. */
  int i;
  double *x, *s, *z, *y;
  double alpha;
  work.block_33[0] = -1;
  /* Make sure sinvz is 1 to make hijacked KKT system ok. */
  for (i = 0; i < 2; i++)
    work.s_inv_z[i] = 1;
  fill_KKT();
  ldl_factor();
  fillrhs_start();
  /* Borrow work.lhs_aff for the solution. */
  ldl_solve(work.rhs, work.lhs_aff);
  /* Don't do any refinement for now. Precision doesn't matter too much. */
  x = work.lhs_aff;
  s = work.lhs_aff + 102;
  z = work.lhs_aff + 104;
  y = work.lhs_aff + 106;
  /* Just set x and y as is. */
  for (i = 0; i < 102; i++)
    work.x[i] = x[i];
  for (i = 0; i < 0; i++)
    work.y[i] = y[i];
  /* Now complete the initialization. Start with s. */
  /* Must have alpha > max(z). */
  alpha = -1e99;
  for (i = 0; i < 2; i++)
    if (alpha < z[i])
      alpha = z[i];
  if (alpha < 0) {
    for (i = 0; i < 2; i++)
      work.s[i] = -z[i];
  } else {
    alpha += 1;
    for (i = 0; i < 2; i++)
      work.s[i] = -z[i] + alpha;
  }
  /* Now initialize z. */
  /* Now must have alpha > max(-z). */
  alpha = -1e99;
  for (i = 0; i < 2; i++)
    if (alpha < -z[i])
      alpha = -z[i];
  if (alpha < 0) {
    for (i = 0; i < 2; i++)
      work.z[i] = z[i];
  } else {
    alpha += 1;
    for (i = 0; i < 2; i++)
      work.z[i] = z[i] + alpha;
  }
}
void Gensolver::fillrhs_start(void) {
  /* Fill rhs with (-q, 0, h, b). */
  int i;
  double *r1, *r2, *r3, *r4;
  r1 = work.rhs;
  r2 = work.rhs + 102;
  r3 = work.rhs + 104;
  r4 = work.rhs + 106;
  for (i = 0; i < 102; i++)
    r1[i] = -work.q[i];
  for (i = 0; i < 2; i++)
    r2[i] = 0;
  for (i = 0; i < 2; i++)
    r3[i] = work.h[i];
  for (i = 0; i < 0; i++)
    r4[i] = work.b[i];
}
long Gensolver::solve(void) {
  int i;
  int iter;
  double *dx, *ds, *dy, *dz;
  double minval;
  double alpha;
  work.converged = 0;
  setup_pointers();
  pre_ops();
#ifndef ZERO_LIBRARY_MODE
  if (settings.verbose)
    printf("iter     objv        gap       |Ax-b|    |Gx+s-h|    step\n");
#endif
  fillq();
  fillh();
  fillb();
  if (settings.better_start)
    better_start();
  else
    set_start();
  for (iter = 0; iter < settings.max_iters; iter++) {
    for (i = 0; i < 2; i++) {
      work.s_inv[i] = 1.0 / work.s[i];
      work.s_inv_z[i] = work.s_inv[i]*work.z[i];
    }
    work.block_33[0] = 0;
    fill_KKT();
    ldl_factor();
    /* Affine scaling directions. */
    fillrhs_aff();
    ldl_solve(work.rhs, work.lhs_aff);
    refine(work.rhs, work.lhs_aff);
    /* Centering plus corrector directions. */
    fillrhs_cc();
    ldl_solve(work.rhs, work.lhs_cc);
    refine(work.rhs, work.lhs_cc);
    /* Add the two together and store in aff. */
    for (i = 0; i < 106; i++)
      work.lhs_aff[i] += work.lhs_cc[i];
    /* Rename aff to reflect its new meaning. */
    dx = work.lhs_aff;
    ds = work.lhs_aff + 102;
    dz = work.lhs_aff + 104;
    dy = work.lhs_aff + 106;
    /* Find min(min(ds./s), min(dz./z)). */
    minval = 0;
    for (i = 0; i < 2; i++)
      if (ds[i] < minval*work.s[i])
        minval = ds[i]/work.s[i];
    for (i = 0; i < 2; i++)
      if (dz[i] < minval*work.z[i])
        minval = dz[i]/work.z[i];
    /* Find alpha. */
    if (-0.99 < minval)
      alpha = 1;
    else
      alpha = -0.99/minval;
    /* Update the primal and dual variables. */
    for (i = 0; i < 102; i++)
      work.x[i] += alpha*dx[i];
    for (i = 0; i < 2; i++)
      work.s[i] += alpha*ds[i];
    for (i = 0; i < 2; i++)
      work.z[i] += alpha*dz[i];
    for (i = 0; i < 0; i++)
      work.y[i] += alpha*dy[i];
    work.gap = eval_gap();
    work.eq_resid_squared = calc_eq_resid_squared();
    work.ineq_resid_squared = calc_ineq_resid_squared();
#ifndef ZERO_LIBRARY_MODE
    if (settings.verbose) {
      work.optval = eval_objv();
      printf("%3d   %10.3e  %9.2e  %9.2e  %9.2e  % 6.4f\n",
          iter+1, work.optval, work.gap, sqrt(work.eq_resid_squared),
          sqrt(work.ineq_resid_squared), alpha);
    }
#endif
    /* Test termination conditions. Requires optimality, and satisfied */
    /* constraints. */
    if (   (work.gap < settings.eps)
        && (work.eq_resid_squared <= settings.resid_tol*settings.resid_tol)
        && (work.ineq_resid_squared <= settings.resid_tol*settings.resid_tol)
       ) {
      work.converged = 1;
      work.optval = eval_objv();
      return iter+1;
    }
  }
  return iter;
}
/* Produced by CVXGEN, 2015-09-15 19:23:47 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: matrix_support.c. */
/* Description: Support functions for matrix multiplication and vector filling. */
void Gensolver::multbymA(double *lhs, double *rhs) {
}
void Gensolver::multbymAT(double *lhs, double *rhs) {
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
  lhs[32] = 0;
  lhs[33] = 0;
  lhs[34] = 0;
  lhs[35] = 0;
  lhs[36] = 0;
  lhs[37] = 0;
  lhs[38] = 0;
  lhs[39] = 0;
  lhs[40] = 0;
  lhs[41] = 0;
  lhs[42] = 0;
  lhs[43] = 0;
  lhs[44] = 0;
  lhs[45] = 0;
  lhs[46] = 0;
  lhs[47] = 0;
  lhs[48] = 0;
  lhs[49] = 0;
  lhs[50] = 0;
  lhs[51] = 0;
  lhs[52] = 0;
  lhs[53] = 0;
  lhs[54] = 0;
  lhs[55] = 0;
  lhs[56] = 0;
  lhs[57] = 0;
  lhs[58] = 0;
  lhs[59] = 0;
  lhs[60] = 0;
  lhs[61] = 0;
  lhs[62] = 0;
  lhs[63] = 0;
  lhs[64] = 0;
  lhs[65] = 0;
  lhs[66] = 0;
  lhs[67] = 0;
  lhs[68] = 0;
  lhs[69] = 0;
  lhs[70] = 0;
  lhs[71] = 0;
  lhs[72] = 0;
  lhs[73] = 0;
  lhs[74] = 0;
  lhs[75] = 0;
  lhs[76] = 0;
  lhs[77] = 0;
  lhs[78] = 0;
  lhs[79] = 0;
  lhs[80] = 0;
  lhs[81] = 0;
  lhs[82] = 0;
  lhs[83] = 0;
  lhs[84] = 0;
  lhs[85] = 0;
  lhs[86] = 0;
  lhs[87] = 0;
  lhs[88] = 0;
  lhs[89] = 0;
  lhs[90] = 0;
  lhs[91] = 0;
  lhs[92] = 0;
  lhs[93] = 0;
  lhs[94] = 0;
  lhs[95] = 0;
  lhs[96] = 0;
  lhs[97] = 0;
  lhs[98] = 0;
  lhs[99] = 0;
  lhs[100] = 0;
  lhs[101] = 0;
}
void Gensolver::multbymG(double *lhs, double *rhs) {
  lhs[0] = -rhs[0]*(-1);
  lhs[1] = -rhs[0]*(1);
}
void Gensolver::multbymGT(double *lhs, double *rhs) {
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
  lhs[32] = 0;
  lhs[33] = 0;
  lhs[34] = 0;
  lhs[35] = 0;
  lhs[36] = 0;
  lhs[37] = 0;
  lhs[38] = 0;
  lhs[39] = 0;
  lhs[40] = 0;
  lhs[41] = 0;
  lhs[42] = 0;
  lhs[43] = 0;
  lhs[44] = 0;
  lhs[45] = 0;
  lhs[46] = 0;
  lhs[47] = 0;
  lhs[48] = 0;
  lhs[49] = 0;
  lhs[50] = 0;
  lhs[51] = 0;
  lhs[52] = 0;
  lhs[53] = 0;
  lhs[54] = 0;
  lhs[55] = 0;
  lhs[56] = 0;
  lhs[57] = 0;
  lhs[58] = 0;
  lhs[59] = 0;
  lhs[60] = 0;
  lhs[61] = 0;
  lhs[62] = 0;
  lhs[63] = 0;
  lhs[64] = 0;
  lhs[65] = 0;
  lhs[66] = 0;
  lhs[67] = 0;
  lhs[68] = 0;
  lhs[69] = 0;
  lhs[70] = 0;
  lhs[71] = 0;
  lhs[72] = 0;
  lhs[73] = 0;
  lhs[74] = 0;
  lhs[75] = 0;
  lhs[76] = 0;
  lhs[77] = 0;
  lhs[78] = 0;
  lhs[79] = 0;
  lhs[80] = 0;
  lhs[81] = 0;
  lhs[82] = 0;
  lhs[83] = 0;
  lhs[84] = 0;
  lhs[85] = 0;
  lhs[86] = 0;
  lhs[87] = 0;
  lhs[88] = 0;
  lhs[89] = 0;
  lhs[90] = 0;
  lhs[91] = 0;
  lhs[92] = 0;
  lhs[93] = 0;
  lhs[94] = 0;
  lhs[95] = 0;
  lhs[96] = 0;
  lhs[97] = 0;
  lhs[98] = 0;
  lhs[99] = 0;
  lhs[100] = 0;
  lhs[101] = 0;
}
void Gensolver::multbyP(double *lhs, double *rhs) {
  /* TODO use the fact that P is symmetric? */
  /* TODO check doubling / half factor etc. */
  lhs[0] = rhs[0]*(2*(params.c2[0]+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848*params.contNum[0]));
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
  lhs[32] = rhs[32]*(2*work.frac_121674190848);
  lhs[33] = rhs[33]*(2*work.frac_121674190848);
  lhs[34] = rhs[34]*(2*work.frac_121674190848);
  lhs[35] = rhs[35]*(2*work.frac_121674190848);
  lhs[36] = rhs[36]*(2*work.frac_121674190848);
  lhs[37] = rhs[37]*(2*work.frac_121674190848);
  lhs[38] = rhs[38]*(2*work.frac_121674190848);
  lhs[39] = rhs[39]*(2*work.frac_121674190848);
  lhs[40] = rhs[40]*(2*work.frac_121674190848);
  lhs[41] = rhs[41]*(2*work.frac_121674190848);
  lhs[42] = rhs[42]*(2*work.frac_121674190848);
  lhs[43] = rhs[43]*(2*work.frac_121674190848);
  lhs[44] = rhs[44]*(2*work.frac_121674190848);
  lhs[45] = rhs[45]*(2*work.frac_121674190848);
  lhs[46] = rhs[46]*(2*work.frac_121674190848);
  lhs[47] = rhs[47]*(2*work.frac_121674190848);
  lhs[48] = rhs[48]*(2*work.frac_121674190848);
  lhs[49] = rhs[49]*(2*work.frac_121674190848);
  lhs[50] = rhs[50]*(2*work.frac_121674190848);
  lhs[51] = rhs[51]*(2*work.frac_121674190848);
  lhs[52] = rhs[52]*(2*work.frac_121674190848);
  lhs[53] = rhs[53]*(2*work.frac_121674190848);
  lhs[54] = rhs[54]*(2*work.frac_121674190848);
  lhs[55] = rhs[55]*(2*work.frac_121674190848);
  lhs[56] = rhs[56]*(2*work.frac_121674190848);
  lhs[57] = rhs[57]*(2*work.frac_121674190848);
  lhs[58] = rhs[58]*(2*work.frac_121674190848);
  lhs[59] = rhs[59]*(2*work.frac_121674190848);
  lhs[60] = rhs[60]*(2*work.frac_121674190848);
  lhs[61] = rhs[61]*(2*work.frac_121674190848);
  lhs[62] = rhs[62]*(2*work.frac_121674190848);
  lhs[63] = rhs[63]*(2*work.frac_121674190848);
  lhs[64] = rhs[64]*(2*work.frac_121674190848);
  lhs[65] = rhs[65]*(2*work.frac_121674190848);
  lhs[66] = rhs[66]*(2*work.frac_121674190848);
  lhs[67] = rhs[67]*(2*work.frac_121674190848);
  lhs[68] = rhs[68]*(2*work.frac_121674190848);
  lhs[69] = rhs[69]*(2*work.frac_121674190848);
  lhs[70] = rhs[70]*(2*work.frac_121674190848);
  lhs[71] = rhs[71]*(2*work.frac_121674190848);
  lhs[72] = rhs[72]*(2*work.frac_121674190848);
  lhs[73] = rhs[73]*(2*work.frac_121674190848);
  lhs[74] = rhs[74]*(2*work.frac_121674190848);
  lhs[75] = rhs[75]*(2*work.frac_121674190848);
  lhs[76] = rhs[76]*(2*work.frac_121674190848);
  lhs[77] = rhs[77]*(2*work.frac_121674190848);
  lhs[78] = rhs[78]*(2*work.frac_121674190848);
  lhs[79] = rhs[79]*(2*work.frac_121674190848);
  lhs[80] = rhs[80]*(2*work.frac_121674190848);
  lhs[81] = rhs[81]*(2*work.frac_121674190848);
  lhs[82] = rhs[82]*(2*work.frac_121674190848);
  lhs[83] = rhs[83]*(2*work.frac_121674190848);
  lhs[84] = rhs[84]*(2*work.frac_121674190848);
  lhs[85] = rhs[85]*(2*work.frac_121674190848);
  lhs[86] = rhs[86]*(2*work.frac_121674190848);
  lhs[87] = rhs[87]*(2*work.frac_121674190848);
  lhs[88] = rhs[88]*(2*work.frac_121674190848);
  lhs[89] = rhs[89]*(2*work.frac_121674190848);
  lhs[90] = rhs[90]*(2*work.frac_121674190848);
  lhs[91] = rhs[91]*(2*work.frac_121674190848);
  lhs[92] = rhs[92]*(2*work.frac_121674190848);
  lhs[93] = rhs[93]*(2*work.frac_121674190848);
  lhs[94] = rhs[94]*(2*work.frac_121674190848);
  lhs[95] = rhs[95]*(2*work.frac_121674190848);
  lhs[96] = rhs[96]*(2*work.frac_121674190848);
  lhs[97] = rhs[97]*(2*work.frac_121674190848);
  lhs[98] = rhs[98]*(2*work.frac_121674190848);
  lhs[99] = rhs[99]*(2*work.frac_121674190848);
  lhs[100] = rhs[100]*(2*work.frac_121674190848);
  lhs[101] = rhs[101]*(2*work.frac_121674190848);
}
void Gensolver::fillq(void) {
  work.q[0] = params.c1[0]+2*(-params.Pg_N_init_1[0]+params.Pg_N_avg_1[0]+params.ug_N_1[0])*work.frac_121674190848+2*(-params.Pg_N_init_2[0]+params.Pg_N_avg_2[0]+params.ug_N_2[0])*work.frac_121674190848+2*(-params.Pg_N_init_3[0]+params.Pg_N_avg_3[0]+params.ug_N_3[0])*work.frac_121674190848+2*(-params.Pg_N_init_4[0]+params.Pg_N_avg_4[0]+params.ug_N_4[0])*work.frac_121674190848+2*(-params.Pg_N_init_5[0]+params.Pg_N_avg_5[0]+params.ug_N_5[0])*work.frac_121674190848+2*(-params.Pg_N_init_6[0]+params.Pg_N_avg_6[0]+params.ug_N_6[0])*work.frac_121674190848+2*(-params.Pg_N_init_7[0]+params.Pg_N_avg_7[0]+params.ug_N_7[0])*work.frac_121674190848+2*(-params.Pg_N_init_8[0]+params.Pg_N_avg_8[0]+params.ug_N_8[0])*work.frac_121674190848+2*(-params.Pg_N_init_9[0]+params.Pg_N_avg_9[0]+params.ug_N_9[0])*work.frac_121674190848+2*(-params.Pg_N_init_10[0]+params.Pg_N_avg_10[0]+params.ug_N_10[0])*work.frac_121674190848+2*(-params.Pg_N_init_11[0]+params.Pg_N_avg_11[0]+params.ug_N_11[0])*work.frac_121674190848+2*(-params.Pg_N_init_12[0]+params.Pg_N_avg_12[0]+params.ug_N_12[0])*work.frac_121674190848+2*(-params.Pg_N_init_13[0]+params.Pg_N_avg_13[0]+params.ug_N_13[0])*work.frac_121674190848+2*(-params.Pg_N_init_14[0]+params.Pg_N_avg_14[0]+params.ug_N_14[0])*work.frac_121674190848+2*(-params.Pg_N_init_15[0]+params.Pg_N_avg_15[0]+params.ug_N_15[0])*work.frac_121674190848+2*(-params.Pg_N_init_16[0]+params.Pg_N_avg_16[0]+params.ug_N_16[0])*work.frac_121674190848+2*(-params.Pg_N_init_17[0]+params.Pg_N_avg_17[0]+params.ug_N_17[0])*work.frac_121674190848+2*(-params.Pg_N_init_18[0]+params.Pg_N_avg_18[0]+params.ug_N_18[0])*work.frac_121674190848+2*(-params.Pg_N_init_19[0]+params.Pg_N_avg_19[0]+params.ug_N_19[0])*work.frac_121674190848+2*(-params.Pg_N_init_20[0]+params.Pg_N_avg_20[0]+params.ug_N_20[0])*work.frac_121674190848+2*(-params.Pg_N_init_21[0]+params.Pg_N_avg_21[0]+params.ug_N_21[0])*work.frac_121674190848+2*(-params.Pg_N_init_22[0]+params.Pg_N_avg_22[0]+params.ug_N_22[0])*work.frac_121674190848+2*(-params.Pg_N_init_23[0]+params.Pg_N_avg_23[0]+params.ug_N_23[0])*work.frac_121674190848+2*(-params.Pg_N_init_24[0]+params.Pg_N_avg_24[0]+params.ug_N_24[0])*work.frac_121674190848+2*(-params.Pg_N_init_25[0]+params.Pg_N_avg_25[0]+params.ug_N_25[0])*work.frac_121674190848+2*(-params.Pg_N_init_26[0]+params.Pg_N_avg_26[0]+params.ug_N_26[0])*work.frac_121674190848+2*(-params.Pg_N_init_27[0]+params.Pg_N_avg_27[0]+params.ug_N_27[0])*work.frac_121674190848+2*(-params.Pg_N_init_28[0]+params.Pg_N_avg_28[0]+params.ug_N_28[0])*work.frac_121674190848+2*(-params.Pg_N_init_29[0]+params.Pg_N_avg_29[0]+params.ug_N_29[0])*work.frac_121674190848+2*(-params.Pg_N_init_30[0]+params.Pg_N_avg_30[0]+params.ug_N_30[0])*work.frac_121674190848+2*(-params.Pg_N_init_31[0]+params.Pg_N_avg_31[0]+params.ug_N_31[0])*work.frac_121674190848+2*(-params.Pg_N_init_32[0]+params.Pg_N_avg_32[0]+params.ug_N_32[0])*work.frac_121674190848+2*(-params.Pg_N_init_33[0]+params.Pg_N_avg_33[0]+params.ug_N_33[0])*work.frac_121674190848+2*(-params.Pg_N_init_34[0]+params.Pg_N_avg_34[0]+params.ug_N_34[0])*work.frac_121674190848+2*(-params.Pg_N_init_35[0]+params.Pg_N_avg_35[0]+params.ug_N_35[0])*work.frac_121674190848+2*(-params.Pg_N_init_36[0]+params.Pg_N_avg_36[0]+params.ug_N_36[0])*work.frac_121674190848+2*(-params.Pg_N_init_37[0]+params.Pg_N_avg_37[0]+params.ug_N_37[0])*work.frac_121674190848+2*(-params.Pg_N_init_38[0]+params.Pg_N_avg_38[0]+params.ug_N_38[0])*work.frac_121674190848+2*(-params.Pg_N_init_39[0]+params.Pg_N_avg_39[0]+params.ug_N_39[0])*work.frac_121674190848+2*(-params.Pg_N_init_40[0]+params.Pg_N_avg_40[0]+params.ug_N_40[0])*work.frac_121674190848+2*(-params.Pg_N_init_41[0]+params.Pg_N_avg_41[0]+params.ug_N_41[0])*work.frac_121674190848+2*(-params.Pg_N_init_42[0]+params.Pg_N_avg_42[0]+params.ug_N_42[0])*work.frac_121674190848+2*(-params.Pg_N_init_43[0]+params.Pg_N_avg_43[0]+params.ug_N_43[0])*work.frac_121674190848+2*(-params.Pg_N_init_44[0]+params.Pg_N_avg_44[0]+params.ug_N_44[0])*work.frac_121674190848+2*(-params.Pg_N_init_45[0]+params.Pg_N_avg_45[0]+params.ug_N_45[0])*work.frac_121674190848+2*(-params.Pg_N_init_46[0]+params.Pg_N_avg_46[0]+params.ug_N_46[0])*work.frac_121674190848+2*(-params.Pg_N_init_47[0]+params.Pg_N_avg_47[0]+params.ug_N_47[0])*work.frac_121674190848+2*(-params.Pg_N_init_48[0]+params.Pg_N_avg_48[0]+params.ug_N_48[0])*work.frac_121674190848+2*(-params.Pg_N_init_49[0]+params.Pg_N_avg_49[0]+params.ug_N_49[0])*work.frac_121674190848+2*(-params.Pg_N_init_50[0]+params.Pg_N_avg_50[0]+params.ug_N_50[0])*work.frac_121674190848+2*(-params.Pg_N_init_51[0]+params.Pg_N_avg_51[0]+params.ug_N_51[0])*work.frac_121674190848+2*(-params.Pg_N_init_52[0]+params.Pg_N_avg_52[0]+params.ug_N_52[0])*work.frac_121674190848+2*(-params.Pg_N_init_53[0]+params.Pg_N_avg_53[0]+params.ug_N_53[0])*work.frac_121674190848+2*(-params.Pg_N_init_54[0]+params.Pg_N_avg_54[0]+params.ug_N_54[0])*work.frac_121674190848+2*(-params.Pg_N_init_55[0]+params.Pg_N_avg_55[0]+params.ug_N_55[0])*work.frac_121674190848+2*(-params.Pg_N_init_56[0]+params.Pg_N_avg_56[0]+params.ug_N_56[0])*work.frac_121674190848+2*(-params.Pg_N_init_57[0]+params.Pg_N_avg_57[0]+params.ug_N_57[0])*work.frac_121674190848+2*(-params.Pg_N_init_58[0]+params.Pg_N_avg_58[0]+params.ug_N_58[0])*work.frac_121674190848+2*(-params.Pg_N_init_59[0]+params.Pg_N_avg_59[0]+params.ug_N_59[0])*work.frac_121674190848+2*(-params.Pg_N_init_60[0]+params.Pg_N_avg_60[0]+params.ug_N_60[0])*work.frac_121674190848+2*(-params.Pg_N_init_61[0]+params.Pg_N_avg_61[0]+params.ug_N_61[0])*work.frac_121674190848+2*(-params.Pg_N_init_62[0]+params.Pg_N_avg_62[0]+params.ug_N_62[0])*work.frac_121674190848+2*(-params.Pg_N_init_63[0]+params.Pg_N_avg_63[0]+params.ug_N_63[0])*work.frac_121674190848+2*(-params.Pg_N_init_64[0]+params.Pg_N_avg_64[0]+params.ug_N_64[0])*work.frac_121674190848+2*(-params.Pg_N_init_65[0]+params.Pg_N_avg_65[0]+params.ug_N_65[0])*work.frac_121674190848+2*(-params.Pg_N_init_66[0]+params.Pg_N_avg_66[0]+params.ug_N_66[0])*work.frac_121674190848+2*(-params.Pg_N_init_67[0]+params.Pg_N_avg_67[0]+params.ug_N_67[0])*work.frac_121674190848+2*(-params.Pg_N_init_68[0]+params.Pg_N_avg_68[0]+params.ug_N_68[0])*work.frac_121674190848+2*(-params.Pg_N_init_69[0]+params.Pg_N_avg_69[0]+params.ug_N_69[0])*work.frac_121674190848+2*(-params.Pg_N_init_70[0]+params.Pg_N_avg_70[0]+params.ug_N_70[0])*work.frac_121674190848+2*(-params.Pg_N_init_71[0]+params.Pg_N_avg_71[0]+params.ug_N_71[0])*work.frac_121674190848+2*(-params.Pg_N_init_72[0]+params.Pg_N_avg_72[0]+params.ug_N_72[0])*work.frac_121674190848+2*(-params.Pg_N_init_73[0]+params.Pg_N_avg_73[0]+params.ug_N_73[0])*work.frac_121674190848+2*(-params.Pg_N_init_74[0]+params.Pg_N_avg_74[0]+params.ug_N_74[0])*work.frac_121674190848+2*(-params.Pg_N_init_75[0]+params.Pg_N_avg_75[0]+params.ug_N_75[0])*work.frac_121674190848+2*(-params.Pg_N_init_76[0]+params.Pg_N_avg_76[0]+params.ug_N_76[0])*work.frac_121674190848+2*(-params.Pg_N_init_77[0]+params.Pg_N_avg_77[0]+params.ug_N_77[0])*work.frac_121674190848+2*(-params.Pg_N_init_78[0]+params.Pg_N_avg_78[0]+params.ug_N_78[0])*work.frac_121674190848+2*(-params.Pg_N_init_79[0]+params.Pg_N_avg_79[0]+params.ug_N_79[0])*work.frac_121674190848+2*(-params.Pg_N_init_80[0]+params.Pg_N_avg_80[0]+params.ug_N_80[0])*work.frac_121674190848+2*(-params.Pg_N_init_81[0]+params.Pg_N_avg_81[0]+params.ug_N_81[0])*work.frac_121674190848+2*(-params.Pg_N_init_82[0]+params.Pg_N_avg_82[0]+params.ug_N_82[0])*work.frac_121674190848+2*(-params.Pg_N_init_83[0]+params.Pg_N_avg_83[0]+params.ug_N_83[0])*work.frac_121674190848+2*(-params.Pg_N_init_84[0]+params.Pg_N_avg_84[0]+params.ug_N_84[0])*work.frac_121674190848+2*(-params.Pg_N_init_85[0]+params.Pg_N_avg_85[0]+params.ug_N_85[0])*work.frac_121674190848+2*(-params.Pg_N_init_86[0]+params.Pg_N_avg_86[0]+params.ug_N_86[0])*work.frac_121674190848+2*(-params.Pg_N_init_87[0]+params.Pg_N_avg_87[0]+params.ug_N_87[0])*work.frac_121674190848+2*(-params.Pg_N_init_88[0]+params.Pg_N_avg_88[0]+params.ug_N_88[0])*work.frac_121674190848+2*(-params.Pg_N_init_89[0]+params.Pg_N_avg_89[0]+params.ug_N_89[0])*work.frac_121674190848+2*(-params.Pg_N_init_90[0]+params.Pg_N_avg_90[0]+params.ug_N_90[0])*work.frac_121674190848+2*(-params.Pg_N_init_91[0]+params.Pg_N_avg_91[0]+params.ug_N_91[0])*work.frac_121674190848+2*(-params.Pg_N_init_92[0]+params.Pg_N_avg_92[0]+params.ug_N_92[0])*work.frac_121674190848+2*(-params.Pg_N_init_93[0]+params.Pg_N_avg_93[0]+params.ug_N_93[0])*work.frac_121674190848+2*(-params.Pg_N_init_94[0]+params.Pg_N_avg_94[0]+params.ug_N_94[0])*work.frac_121674190848+2*(-params.Pg_N_init_95[0]+params.Pg_N_avg_95[0]+params.ug_N_95[0])*work.frac_121674190848+2*(-params.Pg_N_init_96[0]+params.Pg_N_avg_96[0]+params.ug_N_96[0])*work.frac_121674190848+2*(-params.Pg_N_init_97[0]+params.Pg_N_avg_97[0]+params.ug_N_97[0])*work.frac_121674190848+2*(-params.Pg_N_init_98[0]+params.Pg_N_avg_98[0]+params.ug_N_98[0])*work.frac_121674190848+2*(-params.Pg_N_init_99[0]+params.Pg_N_avg_99[0]+params.ug_N_99[0])*work.frac_121674190848+2*(-params.Pg_N_init_100[0]+params.Pg_N_avg_100[0]+params.ug_N_100[0])*work.frac_121674190848+2*(-params.Pg_N_init_101[0]+params.Pg_N_avg_101[0]+params.ug_N_101[0])*work.frac_121674190848;
  work.q[1] = 2*(-params.Vg_N_avg_1[0]-params.Thetag_N_avg_1[0]+params.vg_N_1[0])*work.frac_121674190848;
  work.q[2] = 2*(-params.Vg_N_avg_2[0]-params.Thetag_N_avg_2[0]+params.vg_N_2[0])*work.frac_121674190848;
  work.q[3] = 2*(-params.Vg_N_avg_3[0]-params.Thetag_N_avg_3[0]+params.vg_N_3[0])*work.frac_121674190848;
  work.q[4] = 2*(-params.Vg_N_avg_4[0]-params.Thetag_N_avg_4[0]+params.vg_N_4[0])*work.frac_121674190848;
  work.q[5] = 2*(-params.Vg_N_avg_5[0]-params.Thetag_N_avg_5[0]+params.vg_N_5[0])*work.frac_121674190848;
  work.q[6] = 2*(-params.Vg_N_avg_6[0]-params.Thetag_N_avg_6[0]+params.vg_N_6[0])*work.frac_121674190848;
  work.q[7] = 2*(-params.Vg_N_avg_7[0]-params.Thetag_N_avg_7[0]+params.vg_N_7[0])*work.frac_121674190848;
  work.q[8] = 2*(-params.Vg_N_avg_8[0]-params.Thetag_N_avg_8[0]+params.vg_N_8[0])*work.frac_121674190848;
  work.q[9] = 2*(-params.Vg_N_avg_9[0]-params.Thetag_N_avg_9[0]+params.vg_N_9[0])*work.frac_121674190848;
  work.q[10] = 2*(-params.Vg_N_avg_10[0]-params.Thetag_N_avg_10[0]+params.vg_N_10[0])*work.frac_121674190848;
  work.q[11] = 2*(-params.Vg_N_avg_11[0]-params.Thetag_N_avg_11[0]+params.vg_N_11[0])*work.frac_121674190848;
  work.q[12] = 2*(-params.Vg_N_avg_12[0]-params.Thetag_N_avg_12[0]+params.vg_N_12[0])*work.frac_121674190848;
  work.q[13] = 2*(-params.Vg_N_avg_13[0]-params.Thetag_N_avg_13[0]+params.vg_N_13[0])*work.frac_121674190848;
  work.q[14] = 2*(-params.Vg_N_avg_14[0]-params.Thetag_N_avg_14[0]+params.vg_N_14[0])*work.frac_121674190848;
  work.q[15] = 2*(-params.Vg_N_avg_15[0]-params.Thetag_N_avg_15[0]+params.vg_N_15[0])*work.frac_121674190848;
  work.q[16] = 2*(-params.Vg_N_avg_16[0]-params.Thetag_N_avg_16[0]+params.vg_N_16[0])*work.frac_121674190848;
  work.q[17] = 2*(-params.Vg_N_avg_17[0]-params.Thetag_N_avg_17[0]+params.vg_N_17[0])*work.frac_121674190848;
  work.q[18] = 2*(-params.Vg_N_avg_18[0]-params.Thetag_N_avg_18[0]+params.vg_N_18[0])*work.frac_121674190848;
  work.q[19] = 2*(-params.Vg_N_avg_19[0]-params.Thetag_N_avg_19[0]+params.vg_N_19[0])*work.frac_121674190848;
  work.q[20] = 2*(-params.Vg_N_avg_20[0]-params.Thetag_N_avg_20[0]+params.vg_N_20[0])*work.frac_121674190848;
  work.q[21] = 2*(-params.Vg_N_avg_21[0]-params.Thetag_N_avg_21[0]+params.vg_N_21[0])*work.frac_121674190848;
  work.q[22] = 2*(-params.Vg_N_avg_22[0]-params.Thetag_N_avg_22[0]+params.vg_N_22[0])*work.frac_121674190848;
  work.q[23] = 2*(-params.Vg_N_avg_23[0]-params.Thetag_N_avg_23[0]+params.vg_N_23[0])*work.frac_121674190848;
  work.q[24] = 2*(-params.Vg_N_avg_24[0]-params.Thetag_N_avg_24[0]+params.vg_N_24[0])*work.frac_121674190848;
  work.q[25] = 2*(-params.Vg_N_avg_25[0]-params.Thetag_N_avg_25[0]+params.vg_N_25[0])*work.frac_121674190848;
  work.q[26] = 2*(-params.Vg_N_avg_26[0]-params.Thetag_N_avg_26[0]+params.vg_N_26[0])*work.frac_121674190848;
  work.q[27] = 2*(-params.Vg_N_avg_27[0]-params.Thetag_N_avg_27[0]+params.vg_N_27[0])*work.frac_121674190848;
  work.q[28] = 2*(-params.Vg_N_avg_28[0]-params.Thetag_N_avg_28[0]+params.vg_N_28[0])*work.frac_121674190848;
  work.q[29] = 2*(-params.Vg_N_avg_29[0]-params.Thetag_N_avg_29[0]+params.vg_N_29[0])*work.frac_121674190848;
  work.q[30] = 2*(-params.Vg_N_avg_30[0]-params.Thetag_N_avg_30[0]+params.vg_N_30[0])*work.frac_121674190848;
  work.q[31] = 2*(-params.Vg_N_avg_31[0]-params.Thetag_N_avg_31[0]+params.vg_N_31[0])*work.frac_121674190848;
  work.q[32] = 2*(-params.Vg_N_avg_32[0]-params.Thetag_N_avg_32[0]+params.vg_N_32[0])*work.frac_121674190848;
  work.q[33] = 2*(-params.Vg_N_avg_33[0]-params.Thetag_N_avg_33[0]+params.vg_N_33[0])*work.frac_121674190848;
  work.q[34] = 2*(-params.Vg_N_avg_34[0]-params.Thetag_N_avg_34[0]+params.vg_N_34[0])*work.frac_121674190848;
  work.q[35] = 2*(-params.Vg_N_avg_35[0]-params.Thetag_N_avg_35[0]+params.vg_N_35[0])*work.frac_121674190848;
  work.q[36] = 2*(-params.Vg_N_avg_36[0]-params.Thetag_N_avg_36[0]+params.vg_N_36[0])*work.frac_121674190848;
  work.q[37] = 2*(-params.Vg_N_avg_37[0]-params.Thetag_N_avg_37[0]+params.vg_N_37[0])*work.frac_121674190848;
  work.q[38] = 2*(-params.Vg_N_avg_38[0]-params.Thetag_N_avg_38[0]+params.vg_N_38[0])*work.frac_121674190848;
  work.q[39] = 2*(-params.Vg_N_avg_39[0]-params.Thetag_N_avg_39[0]+params.vg_N_39[0])*work.frac_121674190848;
  work.q[40] = 2*(-params.Vg_N_avg_40[0]-params.Thetag_N_avg_40[0]+params.vg_N_40[0])*work.frac_121674190848;
  work.q[41] = 2*(-params.Vg_N_avg_41[0]-params.Thetag_N_avg_41[0]+params.vg_N_41[0])*work.frac_121674190848;
  work.q[42] = 2*(-params.Vg_N_avg_42[0]-params.Thetag_N_avg_42[0]+params.vg_N_42[0])*work.frac_121674190848;
  work.q[43] = 2*(-params.Vg_N_avg_43[0]-params.Thetag_N_avg_43[0]+params.vg_N_43[0])*work.frac_121674190848;
  work.q[44] = 2*(-params.Vg_N_avg_44[0]-params.Thetag_N_avg_44[0]+params.vg_N_44[0])*work.frac_121674190848;
  work.q[45] = 2*(-params.Vg_N_avg_45[0]-params.Thetag_N_avg_45[0]+params.vg_N_45[0])*work.frac_121674190848;
  work.q[46] = 2*(-params.Vg_N_avg_46[0]-params.Thetag_N_avg_46[0]+params.vg_N_46[0])*work.frac_121674190848;
  work.q[47] = 2*(-params.Vg_N_avg_47[0]-params.Thetag_N_avg_47[0]+params.vg_N_47[0])*work.frac_121674190848;
  work.q[48] = 2*(-params.Vg_N_avg_48[0]-params.Thetag_N_avg_48[0]+params.vg_N_48[0])*work.frac_121674190848;
  work.q[49] = 2*(-params.Vg_N_avg_49[0]-params.Thetag_N_avg_49[0]+params.vg_N_49[0])*work.frac_121674190848;
  work.q[50] = 2*(-params.Vg_N_avg_50[0]-params.Thetag_N_avg_50[0]+params.vg_N_50[0])*work.frac_121674190848;
  work.q[51] = 2*(-params.Vg_N_avg_51[0]-params.Thetag_N_avg_51[0]+params.vg_N_51[0])*work.frac_121674190848;
  work.q[52] = 2*(-params.Vg_N_avg_52[0]-params.Thetag_N_avg_52[0]+params.vg_N_52[0])*work.frac_121674190848;
  work.q[53] = 2*(-params.Vg_N_avg_53[0]-params.Thetag_N_avg_53[0]+params.vg_N_53[0])*work.frac_121674190848;
  work.q[54] = 2*(-params.Vg_N_avg_54[0]-params.Thetag_N_avg_54[0]+params.vg_N_54[0])*work.frac_121674190848;
  work.q[55] = 2*(-params.Vg_N_avg_55[0]-params.Thetag_N_avg_55[0]+params.vg_N_55[0])*work.frac_121674190848;
  work.q[56] = 2*(-params.Vg_N_avg_56[0]-params.Thetag_N_avg_56[0]+params.vg_N_56[0])*work.frac_121674190848;
  work.q[57] = 2*(-params.Vg_N_avg_57[0]-params.Thetag_N_avg_57[0]+params.vg_N_57[0])*work.frac_121674190848;
  work.q[58] = 2*(-params.Vg_N_avg_58[0]-params.Thetag_N_avg_58[0]+params.vg_N_58[0])*work.frac_121674190848;
  work.q[59] = 2*(-params.Vg_N_avg_59[0]-params.Thetag_N_avg_59[0]+params.vg_N_59[0])*work.frac_121674190848;
  work.q[60] = 2*(-params.Vg_N_avg_60[0]-params.Thetag_N_avg_60[0]+params.vg_N_60[0])*work.frac_121674190848;
  work.q[61] = 2*(-params.Vg_N_avg_61[0]-params.Thetag_N_avg_61[0]+params.vg_N_61[0])*work.frac_121674190848;
  work.q[62] = 2*(-params.Vg_N_avg_62[0]-params.Thetag_N_avg_62[0]+params.vg_N_62[0])*work.frac_121674190848;
  work.q[63] = 2*(-params.Vg_N_avg_63[0]-params.Thetag_N_avg_63[0]+params.vg_N_63[0])*work.frac_121674190848;
  work.q[64] = 2*(-params.Vg_N_avg_64[0]-params.Thetag_N_avg_64[0]+params.vg_N_64[0])*work.frac_121674190848;
  work.q[65] = 2*(-params.Vg_N_avg_65[0]-params.Thetag_N_avg_65[0]+params.vg_N_65[0])*work.frac_121674190848;
  work.q[66] = 2*(-params.Vg_N_avg_66[0]-params.Thetag_N_avg_66[0]+params.vg_N_66[0])*work.frac_121674190848;
  work.q[67] = 2*(-params.Vg_N_avg_67[0]-params.Thetag_N_avg_67[0]+params.vg_N_67[0])*work.frac_121674190848;
  work.q[68] = 2*(-params.Vg_N_avg_68[0]-params.Thetag_N_avg_68[0]+params.vg_N_68[0])*work.frac_121674190848;
  work.q[69] = 2*(-params.Vg_N_avg_69[0]-params.Thetag_N_avg_69[0]+params.vg_N_69[0])*work.frac_121674190848;
  work.q[70] = 2*(-params.Vg_N_avg_70[0]-params.Thetag_N_avg_70[0]+params.vg_N_70[0])*work.frac_121674190848;
  work.q[71] = 2*(-params.Vg_N_avg_71[0]-params.Thetag_N_avg_71[0]+params.vg_N_71[0])*work.frac_121674190848;
  work.q[72] = 2*(-params.Vg_N_avg_72[0]-params.Thetag_N_avg_72[0]+params.vg_N_72[0])*work.frac_121674190848;
  work.q[73] = 2*(-params.Vg_N_avg_73[0]-params.Thetag_N_avg_73[0]+params.vg_N_73[0])*work.frac_121674190848;
  work.q[74] = 2*(-params.Vg_N_avg_74[0]-params.Thetag_N_avg_74[0]+params.vg_N_74[0])*work.frac_121674190848;
  work.q[75] = 2*(-params.Vg_N_avg_75[0]-params.Thetag_N_avg_75[0]+params.vg_N_75[0])*work.frac_121674190848;
  work.q[76] = 2*(-params.Vg_N_avg_76[0]-params.Thetag_N_avg_76[0]+params.vg_N_76[0])*work.frac_121674190848;
  work.q[77] = 2*(-params.Vg_N_avg_77[0]-params.Thetag_N_avg_77[0]+params.vg_N_77[0])*work.frac_121674190848;
  work.q[78] = 2*(-params.Vg_N_avg_78[0]-params.Thetag_N_avg_78[0]+params.vg_N_78[0])*work.frac_121674190848;
  work.q[79] = 2*(-params.Vg_N_avg_79[0]-params.Thetag_N_avg_79[0]+params.vg_N_79[0])*work.frac_121674190848;
  work.q[80] = 2*(-params.Vg_N_avg_80[0]-params.Thetag_N_avg_80[0]+params.vg_N_80[0])*work.frac_121674190848;
  work.q[81] = 2*(-params.Vg_N_avg_81[0]-params.Thetag_N_avg_81[0]+params.vg_N_81[0])*work.frac_121674190848;
  work.q[82] = 2*(-params.Vg_N_avg_82[0]-params.Thetag_N_avg_82[0]+params.vg_N_82[0])*work.frac_121674190848;
  work.q[83] = 2*(-params.Vg_N_avg_83[0]-params.Thetag_N_avg_83[0]+params.vg_N_83[0])*work.frac_121674190848;
  work.q[84] = 2*(-params.Vg_N_avg_84[0]-params.Thetag_N_avg_84[0]+params.vg_N_84[0])*work.frac_121674190848;
  work.q[85] = 2*(-params.Vg_N_avg_85[0]-params.Thetag_N_avg_85[0]+params.vg_N_85[0])*work.frac_121674190848;
  work.q[86] = 2*(-params.Vg_N_avg_86[0]-params.Thetag_N_avg_86[0]+params.vg_N_86[0])*work.frac_121674190848;
  work.q[87] = 2*(-params.Vg_N_avg_87[0]-params.Thetag_N_avg_87[0]+params.vg_N_87[0])*work.frac_121674190848;
  work.q[88] = 2*(-params.Vg_N_avg_88[0]-params.Thetag_N_avg_88[0]+params.vg_N_88[0])*work.frac_121674190848;
  work.q[89] = 2*(-params.Vg_N_avg_89[0]-params.Thetag_N_avg_89[0]+params.vg_N_89[0])*work.frac_121674190848;
  work.q[90] = 2*(-params.Vg_N_avg_90[0]-params.Thetag_N_avg_90[0]+params.vg_N_90[0])*work.frac_121674190848;
  work.q[91] = 2*(-params.Vg_N_avg_91[0]-params.Thetag_N_avg_91[0]+params.vg_N_91[0])*work.frac_121674190848;
  work.q[92] = 2*(-params.Vg_N_avg_92[0]-params.Thetag_N_avg_92[0]+params.vg_N_92[0])*work.frac_121674190848;
  work.q[93] = 2*(-params.Vg_N_avg_93[0]-params.Thetag_N_avg_93[0]+params.vg_N_93[0])*work.frac_121674190848;
  work.q[94] = 2*(-params.Vg_N_avg_94[0]-params.Thetag_N_avg_94[0]+params.vg_N_94[0])*work.frac_121674190848;
  work.q[95] = 2*(-params.Vg_N_avg_95[0]-params.Thetag_N_avg_95[0]+params.vg_N_95[0])*work.frac_121674190848;
  work.q[96] = 2*(-params.Vg_N_avg_96[0]-params.Thetag_N_avg_96[0]+params.vg_N_96[0])*work.frac_121674190848;
  work.q[97] = 2*(-params.Vg_N_avg_97[0]-params.Thetag_N_avg_97[0]+params.vg_N_97[0])*work.frac_121674190848;
  work.q[98] = 2*(-params.Vg_N_avg_98[0]-params.Thetag_N_avg_98[0]+params.vg_N_98[0])*work.frac_121674190848;
  work.q[99] = 2*(-params.Vg_N_avg_99[0]-params.Thetag_N_avg_99[0]+params.vg_N_99[0])*work.frac_121674190848;
  work.q[100] = 2*(-params.Vg_N_avg_100[0]-params.Thetag_N_avg_100[0]+params.vg_N_100[0])*work.frac_121674190848;
  work.q[101] = 2*(-params.Vg_N_avg_101[0]-params.Thetag_N_avg_101[0]+params.vg_N_101[0])*work.frac_121674190848;
}
void Gensolver::fillh(void) {
  work.h[0] = -params.PgMin[0];
  work.h[1] = params.PgMax[0];
}
void Gensolver::fillb(void) {
}
void Gensolver::pre_ops(void) {
  work.frac_121674190848 = params.rho[0];
  work.frac_121674190848 /= 2;
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
  work.quad_418591776768[0] = (-params.Pg_N_init_11[0]+params.Pg_N_avg_11[0]+params.ug_N_11[0])*work.frac_121674190848*(-params.Pg_N_init_11[0]+params.Pg_N_avg_11[0]+params.ug_N_11[0]);
  work.quad_358617378816[0] = (-params.Vg_N_avg_11[0]-params.Thetag_N_avg_11[0]+params.vg_N_11[0])*work.frac_121674190848*(-params.Vg_N_avg_11[0]-params.Thetag_N_avg_11[0]+params.vg_N_11[0]);
  work.quad_189427146752[0] = (-params.Pg_N_init_12[0]+params.Pg_N_avg_12[0]+params.ug_N_12[0])*work.frac_121674190848*(-params.Pg_N_init_12[0]+params.Pg_N_avg_12[0]+params.ug_N_12[0]);
  work.quad_811009290240[0] = (-params.Vg_N_avg_12[0]-params.Thetag_N_avg_12[0]+params.vg_N_12[0])*work.frac_121674190848*(-params.Vg_N_avg_12[0]-params.Thetag_N_avg_12[0]+params.vg_N_12[0]);
  work.quad_340342550528[0] = (-params.Pg_N_init_13[0]+params.Pg_N_avg_13[0]+params.ug_N_13[0])*work.frac_121674190848*(-params.Pg_N_init_13[0]+params.Pg_N_avg_13[0]+params.ug_N_13[0]);
  work.quad_861425090560[0] = (-params.Vg_N_avg_13[0]-params.Thetag_N_avg_13[0]+params.vg_N_13[0])*work.frac_121674190848*(-params.Vg_N_avg_13[0]-params.Thetag_N_avg_13[0]+params.vg_N_13[0]);
  work.quad_522812354560[0] = (-params.Pg_N_init_14[0]+params.Pg_N_avg_14[0]+params.ug_N_14[0])*work.frac_121674190848*(-params.Pg_N_init_14[0]+params.Pg_N_avg_14[0]+params.ug_N_14[0]);
  work.quad_347927187456[0] = (-params.Vg_N_avg_14[0]-params.Thetag_N_avg_14[0]+params.vg_N_14[0])*work.frac_121674190848*(-params.Vg_N_avg_14[0]-params.Thetag_N_avg_14[0]+params.vg_N_14[0]);
  work.quad_724215824384[0] = (-params.Pg_N_init_15[0]+params.Pg_N_avg_15[0]+params.ug_N_15[0])*work.frac_121674190848*(-params.Pg_N_init_15[0]+params.Pg_N_avg_15[0]+params.ug_N_15[0]);
  work.quad_488040783872[0] = (-params.Vg_N_avg_15[0]-params.Thetag_N_avg_15[0]+params.vg_N_15[0])*work.frac_121674190848*(-params.Vg_N_avg_15[0]-params.Thetag_N_avg_15[0]+params.vg_N_15[0]);
  work.quad_750720192512[0] = (-params.Pg_N_init_16[0]+params.Pg_N_avg_16[0]+params.ug_N_16[0])*work.frac_121674190848*(-params.Pg_N_init_16[0]+params.Pg_N_avg_16[0]+params.ug_N_16[0]);
  work.quad_575932559360[0] = (-params.Vg_N_avg_16[0]-params.Thetag_N_avg_16[0]+params.vg_N_16[0])*work.frac_121674190848*(-params.Vg_N_avg_16[0]-params.Thetag_N_avg_16[0]+params.vg_N_16[0]);
  work.quad_497126731776[0] = (-params.Pg_N_init_17[0]+params.Pg_N_avg_17[0]+params.ug_N_17[0])*work.frac_121674190848*(-params.Pg_N_init_17[0]+params.Pg_N_avg_17[0]+params.ug_N_17[0]);
  work.quad_446440656896[0] = (-params.Vg_N_avg_17[0]-params.Thetag_N_avg_17[0]+params.vg_N_17[0])*work.frac_121674190848*(-params.Vg_N_avg_17[0]-params.Thetag_N_avg_17[0]+params.vg_N_17[0]);
  work.quad_220748931072[0] = (-params.Pg_N_init_18[0]+params.Pg_N_avg_18[0]+params.ug_N_18[0])*work.frac_121674190848*(-params.Pg_N_init_18[0]+params.Pg_N_avg_18[0]+params.ug_N_18[0]);
  work.quad_576835772416[0] = (-params.Vg_N_avg_18[0]-params.Thetag_N_avg_18[0]+params.vg_N_18[0])*work.frac_121674190848*(-params.Vg_N_avg_18[0]-params.Thetag_N_avg_18[0]+params.vg_N_18[0]);
  work.quad_327014187008[0] = (-params.Pg_N_init_19[0]+params.Pg_N_avg_19[0]+params.ug_N_19[0])*work.frac_121674190848*(-params.Pg_N_init_19[0]+params.Pg_N_avg_19[0]+params.ug_N_19[0]);
  work.quad_77213671424[0] = (-params.Vg_N_avg_19[0]-params.Thetag_N_avg_19[0]+params.vg_N_19[0])*work.frac_121674190848*(-params.Vg_N_avg_19[0]-params.Thetag_N_avg_19[0]+params.vg_N_19[0]);
  work.quad_634046689280[0] = (-params.Pg_N_init_20[0]+params.Pg_N_avg_20[0]+params.ug_N_20[0])*work.frac_121674190848*(-params.Pg_N_init_20[0]+params.Pg_N_avg_20[0]+params.ug_N_20[0]);
  work.quad_376276512768[0] = (-params.Vg_N_avg_20[0]-params.Thetag_N_avg_20[0]+params.vg_N_20[0])*work.frac_121674190848*(-params.Vg_N_avg_20[0]-params.Thetag_N_avg_20[0]+params.vg_N_20[0]);
  work.quad_435014901760[0] = (-params.Pg_N_init_21[0]+params.Pg_N_avg_21[0]+params.ug_N_21[0])*work.frac_121674190848*(-params.Pg_N_init_21[0]+params.Pg_N_avg_21[0]+params.ug_N_21[0]);
  work.quad_194730110976[0] = (-params.Vg_N_avg_21[0]-params.Thetag_N_avg_21[0]+params.vg_N_21[0])*work.frac_121674190848*(-params.Vg_N_avg_21[0]-params.Thetag_N_avg_21[0]+params.vg_N_21[0]);
  work.quad_687358853120[0] = (-params.Pg_N_init_22[0]+params.Pg_N_avg_22[0]+params.ug_N_22[0])*work.frac_121674190848*(-params.Pg_N_init_22[0]+params.Pg_N_avg_22[0]+params.ug_N_22[0]);
  work.quad_748989894656[0] = (-params.Vg_N_avg_22[0]-params.Thetag_N_avg_22[0]+params.vg_N_22[0])*work.frac_121674190848*(-params.Vg_N_avg_22[0]-params.Thetag_N_avg_22[0]+params.vg_N_22[0]);
  work.quad_190680965120[0] = (-params.Pg_N_init_23[0]+params.Pg_N_avg_23[0]+params.ug_N_23[0])*work.frac_121674190848*(-params.Pg_N_init_23[0]+params.Pg_N_avg_23[0]+params.ug_N_23[0]);
  work.quad_274986213376[0] = (-params.Vg_N_avg_23[0]-params.Thetag_N_avg_23[0]+params.vg_N_23[0])*work.frac_121674190848*(-params.Vg_N_avg_23[0]-params.Thetag_N_avg_23[0]+params.vg_N_23[0]);
  work.quad_819154403328[0] = (-params.Pg_N_init_24[0]+params.Pg_N_avg_24[0]+params.ug_N_24[0])*work.frac_121674190848*(-params.Pg_N_init_24[0]+params.Pg_N_avg_24[0]+params.ug_N_24[0]);
  work.quad_211870208000[0] = (-params.Vg_N_avg_24[0]-params.Thetag_N_avg_24[0]+params.vg_N_24[0])*work.frac_121674190848*(-params.Vg_N_avg_24[0]-params.Thetag_N_avg_24[0]+params.vg_N_24[0]);
  work.quad_147546587136[0] = (-params.Pg_N_init_25[0]+params.Pg_N_avg_25[0]+params.ug_N_25[0])*work.frac_121674190848*(-params.Pg_N_init_25[0]+params.Pg_N_avg_25[0]+params.ug_N_25[0]);
  work.quad_31183937536[0] = (-params.Vg_N_avg_25[0]-params.Thetag_N_avg_25[0]+params.vg_N_25[0])*work.frac_121674190848*(-params.Vg_N_avg_25[0]-params.Thetag_N_avg_25[0]+params.vg_N_25[0]);
  work.quad_28386426880[0] = (-params.Pg_N_init_26[0]+params.Pg_N_avg_26[0]+params.ug_N_26[0])*work.frac_121674190848*(-params.Pg_N_init_26[0]+params.Pg_N_avg_26[0]+params.ug_N_26[0]);
  work.quad_476108271616[0] = (-params.Vg_N_avg_26[0]-params.Thetag_N_avg_26[0]+params.vg_N_26[0])*work.frac_121674190848*(-params.Vg_N_avg_26[0]-params.Thetag_N_avg_26[0]+params.vg_N_26[0]);
  work.quad_294418444288[0] = (-params.Pg_N_init_27[0]+params.Pg_N_avg_27[0]+params.ug_N_27[0])*work.frac_121674190848*(-params.Pg_N_init_27[0]+params.Pg_N_avg_27[0]+params.ug_N_27[0]);
  work.quad_169273020416[0] = (-params.Vg_N_avg_27[0]-params.Thetag_N_avg_27[0]+params.vg_N_27[0])*work.frac_121674190848*(-params.Vg_N_avg_27[0]-params.Thetag_N_avg_27[0]+params.vg_N_27[0]);
  work.quad_987523264512[0] = (-params.Pg_N_init_28[0]+params.Pg_N_avg_28[0]+params.ug_N_28[0])*work.frac_121674190848*(-params.Pg_N_init_28[0]+params.Pg_N_avg_28[0]+params.ug_N_28[0]);
  work.quad_55176798208[0] = (-params.Vg_N_avg_28[0]-params.Thetag_N_avg_28[0]+params.vg_N_28[0])*work.frac_121674190848*(-params.Vg_N_avg_28[0]-params.Thetag_N_avg_28[0]+params.vg_N_28[0]);
  work.quad_526459392000[0] = (-params.Pg_N_init_29[0]+params.Pg_N_avg_29[0]+params.ug_N_29[0])*work.frac_121674190848*(-params.Pg_N_init_29[0]+params.Pg_N_avg_29[0]+params.ug_N_29[0]);
  work.quad_938506014720[0] = (-params.Vg_N_avg_29[0]-params.Thetag_N_avg_29[0]+params.vg_N_29[0])*work.frac_121674190848*(-params.Vg_N_avg_29[0]-params.Thetag_N_avg_29[0]+params.vg_N_29[0]);
  work.quad_398236438528[0] = (-params.Pg_N_init_30[0]+params.Pg_N_avg_30[0]+params.ug_N_30[0])*work.frac_121674190848*(-params.Pg_N_init_30[0]+params.Pg_N_avg_30[0]+params.ug_N_30[0]);
  work.quad_408717836288[0] = (-params.Vg_N_avg_30[0]-params.Thetag_N_avg_30[0]+params.vg_N_30[0])*work.frac_121674190848*(-params.Vg_N_avg_30[0]-params.Thetag_N_avg_30[0]+params.vg_N_30[0]);
  work.quad_184308461568[0] = (-params.Pg_N_init_31[0]+params.Pg_N_avg_31[0]+params.ug_N_31[0])*work.frac_121674190848*(-params.Pg_N_init_31[0]+params.Pg_N_avg_31[0]+params.ug_N_31[0]);
  work.quad_330616233984[0] = (-params.Vg_N_avg_31[0]-params.Thetag_N_avg_31[0]+params.vg_N_31[0])*work.frac_121674190848*(-params.Vg_N_avg_31[0]-params.Thetag_N_avg_31[0]+params.vg_N_31[0]);
  work.quad_411712237568[0] = (-params.Pg_N_init_32[0]+params.Pg_N_avg_32[0]+params.ug_N_32[0])*work.frac_121674190848*(-params.Pg_N_init_32[0]+params.Pg_N_avg_32[0]+params.ug_N_32[0]);
  work.quad_642560991232[0] = (-params.Vg_N_avg_32[0]-params.Thetag_N_avg_32[0]+params.vg_N_32[0])*work.frac_121674190848*(-params.Vg_N_avg_32[0]-params.Thetag_N_avg_32[0]+params.vg_N_32[0]);
  work.quad_172000874496[0] = (-params.Pg_N_init_33[0]+params.Pg_N_avg_33[0]+params.ug_N_33[0])*work.frac_121674190848*(-params.Pg_N_init_33[0]+params.Pg_N_avg_33[0]+params.ug_N_33[0]);
  work.quad_877709885440[0] = (-params.Vg_N_avg_33[0]-params.Thetag_N_avg_33[0]+params.vg_N_33[0])*work.frac_121674190848*(-params.Vg_N_avg_33[0]-params.Thetag_N_avg_33[0]+params.vg_N_33[0]);
  work.quad_236200529920[0] = (-params.Pg_N_init_34[0]+params.Pg_N_avg_34[0]+params.ug_N_34[0])*work.frac_121674190848*(-params.Pg_N_init_34[0]+params.Pg_N_avg_34[0]+params.ug_N_34[0]);
  work.quad_953866592256[0] = (-params.Vg_N_avg_34[0]-params.Thetag_N_avg_34[0]+params.vg_N_34[0])*work.frac_121674190848*(-params.Vg_N_avg_34[0]-params.Thetag_N_avg_34[0]+params.vg_N_34[0]);
  work.quad_608829231104[0] = (-params.Pg_N_init_35[0]+params.Pg_N_avg_35[0]+params.ug_N_35[0])*work.frac_121674190848*(-params.Pg_N_init_35[0]+params.Pg_N_avg_35[0]+params.ug_N_35[0]);
  work.quad_265570734080[0] = (-params.Vg_N_avg_35[0]-params.Thetag_N_avg_35[0]+params.vg_N_35[0])*work.frac_121674190848*(-params.Vg_N_avg_35[0]-params.Thetag_N_avg_35[0]+params.vg_N_35[0]);
  work.quad_225263394816[0] = (-params.Pg_N_init_36[0]+params.Pg_N_avg_36[0]+params.ug_N_36[0])*work.frac_121674190848*(-params.Pg_N_init_36[0]+params.Pg_N_avg_36[0]+params.ug_N_36[0]);
  work.quad_434793504768[0] = (-params.Vg_N_avg_36[0]-params.Thetag_N_avg_36[0]+params.vg_N_36[0])*work.frac_121674190848*(-params.Vg_N_avg_36[0]-params.Thetag_N_avg_36[0]+params.vg_N_36[0]);
  work.quad_984017977344[0] = (-params.Pg_N_init_37[0]+params.Pg_N_avg_37[0]+params.ug_N_37[0])*work.frac_121674190848*(-params.Pg_N_init_37[0]+params.Pg_N_avg_37[0]+params.ug_N_37[0]);
  work.quad_526619181056[0] = (-params.Vg_N_avg_37[0]-params.Thetag_N_avg_37[0]+params.vg_N_37[0])*work.frac_121674190848*(-params.Vg_N_avg_37[0]-params.Thetag_N_avg_37[0]+params.vg_N_37[0]);
  work.quad_566099726336[0] = (-params.Pg_N_init_38[0]+params.Pg_N_avg_38[0]+params.ug_N_38[0])*work.frac_121674190848*(-params.Pg_N_init_38[0]+params.Pg_N_avg_38[0]+params.ug_N_38[0]);
  work.quad_879322742784[0] = (-params.Vg_N_avg_38[0]-params.Thetag_N_avg_38[0]+params.vg_N_38[0])*work.frac_121674190848*(-params.Vg_N_avg_38[0]-params.Thetag_N_avg_38[0]+params.vg_N_38[0]);
  work.quad_620654563328[0] = (-params.Pg_N_init_39[0]+params.Pg_N_avg_39[0]+params.ug_N_39[0])*work.frac_121674190848*(-params.Pg_N_init_39[0]+params.Pg_N_avg_39[0]+params.ug_N_39[0]);
  work.quad_485479587840[0] = (-params.Vg_N_avg_39[0]-params.Thetag_N_avg_39[0]+params.vg_N_39[0])*work.frac_121674190848*(-params.Vg_N_avg_39[0]-params.Thetag_N_avg_39[0]+params.vg_N_39[0]);
  work.quad_808293044224[0] = (-params.Pg_N_init_40[0]+params.Pg_N_avg_40[0]+params.ug_N_40[0])*work.frac_121674190848*(-params.Pg_N_init_40[0]+params.Pg_N_avg_40[0]+params.ug_N_40[0]);
  work.quad_468686970880[0] = (-params.Vg_N_avg_40[0]-params.Thetag_N_avg_40[0]+params.vg_N_40[0])*work.frac_121674190848*(-params.Vg_N_avg_40[0]-params.Thetag_N_avg_40[0]+params.vg_N_40[0]);
  work.quad_563134095360[0] = (-params.Pg_N_init_41[0]+params.Pg_N_avg_41[0]+params.ug_N_41[0])*work.frac_121674190848*(-params.Pg_N_init_41[0]+params.Pg_N_avg_41[0]+params.ug_N_41[0]);
  work.quad_370423967744[0] = (-params.Vg_N_avg_41[0]-params.Thetag_N_avg_41[0]+params.vg_N_41[0])*work.frac_121674190848*(-params.Vg_N_avg_41[0]-params.Thetag_N_avg_41[0]+params.vg_N_41[0]);
  work.quad_222369783808[0] = (-params.Pg_N_init_42[0]+params.Pg_N_avg_42[0]+params.ug_N_42[0])*work.frac_121674190848*(-params.Pg_N_init_42[0]+params.Pg_N_avg_42[0]+params.ug_N_42[0]);
  work.quad_83489009664[0] = (-params.Vg_N_avg_42[0]-params.Thetag_N_avg_42[0]+params.vg_N_42[0])*work.frac_121674190848*(-params.Vg_N_avg_42[0]-params.Thetag_N_avg_42[0]+params.vg_N_42[0]);
  work.quad_573775224832[0] = (-params.Pg_N_init_43[0]+params.Pg_N_avg_43[0]+params.ug_N_43[0])*work.frac_121674190848*(-params.Pg_N_init_43[0]+params.Pg_N_avg_43[0]+params.ug_N_43[0]);
  work.quad_81818914816[0] = (-params.Vg_N_avg_43[0]-params.Thetag_N_avg_43[0]+params.vg_N_43[0])*work.frac_121674190848*(-params.Vg_N_avg_43[0]-params.Thetag_N_avg_43[0]+params.vg_N_43[0]);
  work.quad_869895589888[0] = (-params.Pg_N_init_44[0]+params.Pg_N_avg_44[0]+params.ug_N_44[0])*work.frac_121674190848*(-params.Pg_N_init_44[0]+params.Pg_N_avg_44[0]+params.ug_N_44[0]);
  work.quad_456437583872[0] = (-params.Vg_N_avg_44[0]-params.Thetag_N_avg_44[0]+params.vg_N_44[0])*work.frac_121674190848*(-params.Vg_N_avg_44[0]-params.Thetag_N_avg_44[0]+params.vg_N_44[0]);
  work.quad_90734665728[0] = (-params.Pg_N_init_45[0]+params.Pg_N_avg_45[0]+params.ug_N_45[0])*work.frac_121674190848*(-params.Pg_N_init_45[0]+params.Pg_N_avg_45[0]+params.ug_N_45[0]);
  work.quad_165580480512[0] = (-params.Vg_N_avg_45[0]-params.Thetag_N_avg_45[0]+params.vg_N_45[0])*work.frac_121674190848*(-params.Vg_N_avg_45[0]-params.Thetag_N_avg_45[0]+params.vg_N_45[0]);
  work.quad_225093988352[0] = (-params.Pg_N_init_46[0]+params.Pg_N_avg_46[0]+params.ug_N_46[0])*work.frac_121674190848*(-params.Pg_N_init_46[0]+params.Pg_N_avg_46[0]+params.ug_N_46[0]);
  work.quad_944332083200[0] = (-params.Vg_N_avg_46[0]-params.Thetag_N_avg_46[0]+params.vg_N_46[0])*work.frac_121674190848*(-params.Vg_N_avg_46[0]-params.Thetag_N_avg_46[0]+params.vg_N_46[0]);
  work.quad_198883876864[0] = (-params.Pg_N_init_47[0]+params.Pg_N_avg_47[0]+params.ug_N_47[0])*work.frac_121674190848*(-params.Pg_N_init_47[0]+params.Pg_N_avg_47[0]+params.ug_N_47[0]);
  work.quad_30941691904[0] = (-params.Vg_N_avg_47[0]-params.Thetag_N_avg_47[0]+params.vg_N_47[0])*work.frac_121674190848*(-params.Vg_N_avg_47[0]-params.Thetag_N_avg_47[0]+params.vg_N_47[0]);
  work.quad_692068392960[0] = (-params.Pg_N_init_48[0]+params.Pg_N_avg_48[0]+params.ug_N_48[0])*work.frac_121674190848*(-params.Pg_N_init_48[0]+params.Pg_N_avg_48[0]+params.ug_N_48[0]);
  work.quad_404779089920[0] = (-params.Vg_N_avg_48[0]-params.Thetag_N_avg_48[0]+params.vg_N_48[0])*work.frac_121674190848*(-params.Vg_N_avg_48[0]-params.Thetag_N_avg_48[0]+params.vg_N_48[0]);
  work.quad_637665005568[0] = (-params.Pg_N_init_49[0]+params.Pg_N_avg_49[0]+params.ug_N_49[0])*work.frac_121674190848*(-params.Pg_N_init_49[0]+params.Pg_N_avg_49[0]+params.ug_N_49[0]);
  work.quad_719521869824[0] = (-params.Vg_N_avg_49[0]-params.Thetag_N_avg_49[0]+params.vg_N_49[0])*work.frac_121674190848*(-params.Vg_N_avg_49[0]-params.Thetag_N_avg_49[0]+params.vg_N_49[0]);
  work.quad_480708186112[0] = (-params.Pg_N_init_50[0]+params.Pg_N_avg_50[0]+params.ug_N_50[0])*work.frac_121674190848*(-params.Pg_N_init_50[0]+params.Pg_N_avg_50[0]+params.ug_N_50[0]);
  work.quad_109914923008[0] = (-params.Vg_N_avg_50[0]-params.Thetag_N_avg_50[0]+params.vg_N_50[0])*work.frac_121674190848*(-params.Vg_N_avg_50[0]-params.Thetag_N_avg_50[0]+params.vg_N_50[0]);
  work.quad_101608513536[0] = (-params.Pg_N_init_51[0]+params.Pg_N_avg_51[0]+params.ug_N_51[0])*work.frac_121674190848*(-params.Pg_N_init_51[0]+params.Pg_N_avg_51[0]+params.ug_N_51[0]);
  work.quad_199411765248[0] = (-params.Vg_N_avg_51[0]-params.Thetag_N_avg_51[0]+params.vg_N_51[0])*work.frac_121674190848*(-params.Vg_N_avg_51[0]-params.Thetag_N_avg_51[0]+params.vg_N_51[0]);
  work.quad_901289631744[0] = (-params.Pg_N_init_52[0]+params.Pg_N_avg_52[0]+params.ug_N_52[0])*work.frac_121674190848*(-params.Pg_N_init_52[0]+params.Pg_N_avg_52[0]+params.ug_N_52[0]);
  work.quad_594054291456[0] = (-params.Vg_N_avg_52[0]-params.Thetag_N_avg_52[0]+params.vg_N_52[0])*work.frac_121674190848*(-params.Vg_N_avg_52[0]-params.Thetag_N_avg_52[0]+params.vg_N_52[0]);
  work.quad_404078174208[0] = (-params.Pg_N_init_53[0]+params.Pg_N_avg_53[0]+params.ug_N_53[0])*work.frac_121674190848*(-params.Pg_N_init_53[0]+params.Pg_N_avg_53[0]+params.ug_N_53[0]);
  work.quad_244563038208[0] = (-params.Vg_N_avg_53[0]-params.Thetag_N_avg_53[0]+params.vg_N_53[0])*work.frac_121674190848*(-params.Vg_N_avg_53[0]-params.Thetag_N_avg_53[0]+params.vg_N_53[0]);
  work.quad_338757373952[0] = (-params.Pg_N_init_54[0]+params.Pg_N_avg_54[0]+params.ug_N_54[0])*work.frac_121674190848*(-params.Pg_N_init_54[0]+params.Pg_N_avg_54[0]+params.ug_N_54[0]);
  work.quad_655083196416[0] = (-params.Vg_N_avg_54[0]-params.Thetag_N_avg_54[0]+params.vg_N_54[0])*work.frac_121674190848*(-params.Vg_N_avg_54[0]-params.Thetag_N_avg_54[0]+params.vg_N_54[0]);
  work.quad_489744039936[0] = (-params.Pg_N_init_55[0]+params.Pg_N_avg_55[0]+params.ug_N_55[0])*work.frac_121674190848*(-params.Pg_N_init_55[0]+params.Pg_N_avg_55[0]+params.ug_N_55[0]);
  work.quad_259549028352[0] = (-params.Vg_N_avg_55[0]-params.Thetag_N_avg_55[0]+params.vg_N_55[0])*work.frac_121674190848*(-params.Vg_N_avg_55[0]-params.Thetag_N_avg_55[0]+params.vg_N_55[0]);
  work.quad_250154500096[0] = (-params.Pg_N_init_56[0]+params.Pg_N_avg_56[0]+params.ug_N_56[0])*work.frac_121674190848*(-params.Pg_N_init_56[0]+params.Pg_N_avg_56[0]+params.ug_N_56[0]);
  work.quad_283916939264[0] = (-params.Vg_N_avg_56[0]-params.Thetag_N_avg_56[0]+params.vg_N_56[0])*work.frac_121674190848*(-params.Vg_N_avg_56[0]-params.Thetag_N_avg_56[0]+params.vg_N_56[0]);
  work.quad_504322719744[0] = (-params.Pg_N_init_57[0]+params.Pg_N_avg_57[0]+params.ug_N_57[0])*work.frac_121674190848*(-params.Pg_N_init_57[0]+params.Pg_N_avg_57[0]+params.ug_N_57[0]);
  work.quad_996765118464[0] = (-params.Vg_N_avg_57[0]-params.Thetag_N_avg_57[0]+params.vg_N_57[0])*work.frac_121674190848*(-params.Vg_N_avg_57[0]-params.Thetag_N_avg_57[0]+params.vg_N_57[0]);
  work.quad_483569917952[0] = (-params.Pg_N_init_58[0]+params.Pg_N_avg_58[0]+params.ug_N_58[0])*work.frac_121674190848*(-params.Pg_N_init_58[0]+params.Pg_N_avg_58[0]+params.ug_N_58[0]);
  work.quad_158537359360[0] = (-params.Vg_N_avg_58[0]-params.Thetag_N_avg_58[0]+params.vg_N_58[0])*work.frac_121674190848*(-params.Vg_N_avg_58[0]-params.Thetag_N_avg_58[0]+params.vg_N_58[0]);
  work.quad_626608463872[0] = (-params.Pg_N_init_59[0]+params.Pg_N_avg_59[0]+params.ug_N_59[0])*work.frac_121674190848*(-params.Pg_N_init_59[0]+params.Pg_N_avg_59[0]+params.ug_N_59[0]);
  work.quad_927129829376[0] = (-params.Vg_N_avg_59[0]-params.Thetag_N_avg_59[0]+params.vg_N_59[0])*work.frac_121674190848*(-params.Vg_N_avg_59[0]-params.Thetag_N_avg_59[0]+params.vg_N_59[0]);
  work.quad_790822236160[0] = (-params.Pg_N_init_60[0]+params.Pg_N_avg_60[0]+params.ug_N_60[0])*work.frac_121674190848*(-params.Pg_N_init_60[0]+params.Pg_N_avg_60[0]+params.ug_N_60[0]);
  work.quad_918575378432[0] = (-params.Vg_N_avg_60[0]-params.Thetag_N_avg_60[0]+params.vg_N_60[0])*work.frac_121674190848*(-params.Vg_N_avg_60[0]-params.Thetag_N_avg_60[0]+params.vg_N_60[0]);
  work.quad_995595960320[0] = (-params.Pg_N_init_61[0]+params.Pg_N_avg_61[0]+params.ug_N_61[0])*work.frac_121674190848*(-params.Pg_N_init_61[0]+params.Pg_N_avg_61[0]+params.ug_N_61[0]);
  work.quad_529630486528[0] = (-params.Vg_N_avg_61[0]-params.Thetag_N_avg_61[0]+params.vg_N_61[0])*work.frac_121674190848*(-params.Vg_N_avg_61[0]-params.Thetag_N_avg_61[0]+params.vg_N_61[0]);
  work.quad_79251795968[0] = (-params.Pg_N_init_62[0]+params.Pg_N_avg_62[0]+params.ug_N_62[0])*work.frac_121674190848*(-params.Pg_N_init_62[0]+params.Pg_N_avg_62[0]+params.ug_N_62[0]);
  work.quad_475943071744[0] = (-params.Vg_N_avg_62[0]-params.Thetag_N_avg_62[0]+params.vg_N_62[0])*work.frac_121674190848*(-params.Vg_N_avg_62[0]-params.Thetag_N_avg_62[0]+params.vg_N_62[0]);
  work.quad_146468945920[0] = (-params.Pg_N_init_63[0]+params.Pg_N_avg_63[0]+params.ug_N_63[0])*work.frac_121674190848*(-params.Pg_N_init_63[0]+params.Pg_N_avg_63[0]+params.ug_N_63[0]);
  work.quad_86002155520[0] = (-params.Vg_N_avg_63[0]-params.Thetag_N_avg_63[0]+params.vg_N_63[0])*work.frac_121674190848*(-params.Vg_N_avg_63[0]-params.Thetag_N_avg_63[0]+params.vg_N_63[0]);
  work.quad_351835660288[0] = (-params.Pg_N_init_64[0]+params.Pg_N_avg_64[0]+params.ug_N_64[0])*work.frac_121674190848*(-params.Pg_N_init_64[0]+params.Pg_N_avg_64[0]+params.ug_N_64[0]);
  work.quad_898473287680[0] = (-params.Vg_N_avg_64[0]-params.Thetag_N_avg_64[0]+params.vg_N_64[0])*work.frac_121674190848*(-params.Vg_N_avg_64[0]-params.Thetag_N_avg_64[0]+params.vg_N_64[0]);
  work.quad_715947200512[0] = (-params.Pg_N_init_65[0]+params.Pg_N_avg_65[0]+params.ug_N_65[0])*work.frac_121674190848*(-params.Pg_N_init_65[0]+params.Pg_N_avg_65[0]+params.ug_N_65[0]);
  work.quad_824253415424[0] = (-params.Vg_N_avg_65[0]-params.Thetag_N_avg_65[0]+params.vg_N_65[0])*work.frac_121674190848*(-params.Vg_N_avg_65[0]-params.Thetag_N_avg_65[0]+params.vg_N_65[0]);
  work.quad_494006571008[0] = (-params.Pg_N_init_66[0]+params.Pg_N_avg_66[0]+params.ug_N_66[0])*work.frac_121674190848*(-params.Pg_N_init_66[0]+params.Pg_N_avg_66[0]+params.ug_N_66[0]);
  work.quad_185061429248[0] = (-params.Vg_N_avg_66[0]-params.Thetag_N_avg_66[0]+params.vg_N_66[0])*work.frac_121674190848*(-params.Vg_N_avg_66[0]-params.Thetag_N_avg_66[0]+params.vg_N_66[0]);
  work.quad_796629155840[0] = (-params.Pg_N_init_67[0]+params.Pg_N_avg_67[0]+params.ug_N_67[0])*work.frac_121674190848*(-params.Pg_N_init_67[0]+params.Pg_N_avg_67[0]+params.ug_N_67[0]);
  work.quad_449770254336[0] = (-params.Vg_N_avg_67[0]-params.Thetag_N_avg_67[0]+params.vg_N_67[0])*work.frac_121674190848*(-params.Vg_N_avg_67[0]-params.Thetag_N_avg_67[0]+params.vg_N_67[0]);
  work.quad_947342782464[0] = (-params.Pg_N_init_68[0]+params.Pg_N_avg_68[0]+params.ug_N_68[0])*work.frac_121674190848*(-params.Pg_N_init_68[0]+params.Pg_N_avg_68[0]+params.ug_N_68[0]);
  work.quad_604877107200[0] = (-params.Vg_N_avg_68[0]-params.Thetag_N_avg_68[0]+params.vg_N_68[0])*work.frac_121674190848*(-params.Vg_N_avg_68[0]-params.Thetag_N_avg_68[0]+params.vg_N_68[0]);
  work.quad_680640479232[0] = (-params.Pg_N_init_69[0]+params.Pg_N_avg_69[0]+params.ug_N_69[0])*work.frac_121674190848*(-params.Pg_N_init_69[0]+params.Pg_N_avg_69[0]+params.ug_N_69[0]);
  work.quad_9457143808[0] = (-params.Vg_N_avg_69[0]-params.Thetag_N_avg_69[0]+params.vg_N_69[0])*work.frac_121674190848*(-params.Vg_N_avg_69[0]-params.Thetag_N_avg_69[0]+params.vg_N_69[0]);
  work.quad_717531140096[0] = (-params.Pg_N_init_70[0]+params.Pg_N_avg_70[0]+params.ug_N_70[0])*work.frac_121674190848*(-params.Pg_N_init_70[0]+params.Pg_N_avg_70[0]+params.ug_N_70[0]);
  work.quad_634949398528[0] = (-params.Vg_N_avg_70[0]-params.Thetag_N_avg_70[0]+params.vg_N_70[0])*work.frac_121674190848*(-params.Vg_N_avg_70[0]-params.Thetag_N_avg_70[0]+params.vg_N_70[0]);
  work.quad_564056838144[0] = (-params.Pg_N_init_71[0]+params.Pg_N_avg_71[0]+params.ug_N_71[0])*work.frac_121674190848*(-params.Pg_N_init_71[0]+params.Pg_N_avg_71[0]+params.ug_N_71[0]);
  work.quad_946810548224[0] = (-params.Vg_N_avg_71[0]-params.Thetag_N_avg_71[0]+params.vg_N_71[0])*work.frac_121674190848*(-params.Vg_N_avg_71[0]-params.Thetag_N_avg_71[0]+params.vg_N_71[0]);
  work.quad_70571728896[0] = (-params.Pg_N_init_72[0]+params.Pg_N_avg_72[0]+params.ug_N_72[0])*work.frac_121674190848*(-params.Pg_N_init_72[0]+params.Pg_N_avg_72[0]+params.ug_N_72[0]);
  work.quad_286652420096[0] = (-params.Vg_N_avg_72[0]-params.Thetag_N_avg_72[0]+params.vg_N_72[0])*work.frac_121674190848*(-params.Vg_N_avg_72[0]-params.Thetag_N_avg_72[0]+params.vg_N_72[0]);
  work.quad_173991247872[0] = (-params.Pg_N_init_73[0]+params.Pg_N_avg_73[0]+params.ug_N_73[0])*work.frac_121674190848*(-params.Pg_N_init_73[0]+params.Pg_N_avg_73[0]+params.ug_N_73[0]);
  work.quad_474489081856[0] = (-params.Vg_N_avg_73[0]-params.Thetag_N_avg_73[0]+params.vg_N_73[0])*work.frac_121674190848*(-params.Vg_N_avg_73[0]-params.Thetag_N_avg_73[0]+params.vg_N_73[0]);
  work.quad_880120451072[0] = (-params.Pg_N_init_74[0]+params.Pg_N_avg_74[0]+params.ug_N_74[0])*work.frac_121674190848*(-params.Pg_N_init_74[0]+params.Pg_N_avg_74[0]+params.ug_N_74[0]);
  work.quad_782250987520[0] = (-params.Vg_N_avg_74[0]-params.Thetag_N_avg_74[0]+params.vg_N_74[0])*work.frac_121674190848*(-params.Vg_N_avg_74[0]-params.Thetag_N_avg_74[0]+params.vg_N_74[0]);
  work.quad_57536741376[0] = (-params.Pg_N_init_75[0]+params.Pg_N_avg_75[0]+params.ug_N_75[0])*work.frac_121674190848*(-params.Pg_N_init_75[0]+params.Pg_N_avg_75[0]+params.ug_N_75[0]);
  work.quad_849656963072[0] = (-params.Vg_N_avg_75[0]-params.Thetag_N_avg_75[0]+params.vg_N_75[0])*work.frac_121674190848*(-params.Vg_N_avg_75[0]-params.Thetag_N_avg_75[0]+params.vg_N_75[0]);
  work.quad_35205603328[0] = (-params.Pg_N_init_76[0]+params.Pg_N_avg_76[0]+params.ug_N_76[0])*work.frac_121674190848*(-params.Pg_N_init_76[0]+params.Pg_N_avg_76[0]+params.ug_N_76[0]);
  work.quad_658468995072[0] = (-params.Vg_N_avg_76[0]-params.Thetag_N_avg_76[0]+params.vg_N_76[0])*work.frac_121674190848*(-params.Vg_N_avg_76[0]-params.Thetag_N_avg_76[0]+params.vg_N_76[0]);
  work.quad_356423053312[0] = (-params.Pg_N_init_77[0]+params.Pg_N_avg_77[0]+params.ug_N_77[0])*work.frac_121674190848*(-params.Pg_N_init_77[0]+params.Pg_N_avg_77[0]+params.ug_N_77[0]);
  work.quad_283962642432[0] = (-params.Vg_N_avg_77[0]-params.Thetag_N_avg_77[0]+params.vg_N_77[0])*work.frac_121674190848*(-params.Vg_N_avg_77[0]-params.Thetag_N_avg_77[0]+params.vg_N_77[0]);
  work.quad_547807477760[0] = (-params.Pg_N_init_78[0]+params.Pg_N_avg_78[0]+params.ug_N_78[0])*work.frac_121674190848*(-params.Pg_N_init_78[0]+params.Pg_N_avg_78[0]+params.ug_N_78[0]);
  work.quad_382444605440[0] = (-params.Vg_N_avg_78[0]-params.Thetag_N_avg_78[0]+params.vg_N_78[0])*work.frac_121674190848*(-params.Vg_N_avg_78[0]-params.Thetag_N_avg_78[0]+params.vg_N_78[0]);
  work.quad_539754852352[0] = (-params.Pg_N_init_79[0]+params.Pg_N_avg_79[0]+params.ug_N_79[0])*work.frac_121674190848*(-params.Pg_N_init_79[0]+params.Pg_N_avg_79[0]+params.ug_N_79[0]);
  work.quad_230561599488[0] = (-params.Vg_N_avg_79[0]-params.Thetag_N_avg_79[0]+params.vg_N_79[0])*work.frac_121674190848*(-params.Vg_N_avg_79[0]-params.Thetag_N_avg_79[0]+params.vg_N_79[0]);
  work.quad_865930481664[0] = (-params.Pg_N_init_80[0]+params.Pg_N_avg_80[0]+params.ug_N_80[0])*work.frac_121674190848*(-params.Pg_N_init_80[0]+params.Pg_N_avg_80[0]+params.ug_N_80[0]);
  work.quad_541608677376[0] = (-params.Vg_N_avg_80[0]-params.Thetag_N_avg_80[0]+params.vg_N_80[0])*work.frac_121674190848*(-params.Vg_N_avg_80[0]-params.Thetag_N_avg_80[0]+params.vg_N_80[0]);
  work.quad_125357936640[0] = (-params.Pg_N_init_81[0]+params.Pg_N_avg_81[0]+params.ug_N_81[0])*work.frac_121674190848*(-params.Pg_N_init_81[0]+params.Pg_N_avg_81[0]+params.ug_N_81[0]);
  work.quad_619719733248[0] = (-params.Vg_N_avg_81[0]-params.Thetag_N_avg_81[0]+params.vg_N_81[0])*work.frac_121674190848*(-params.Vg_N_avg_81[0]-params.Thetag_N_avg_81[0]+params.vg_N_81[0]);
  work.quad_824211386368[0] = (-params.Pg_N_init_82[0]+params.Pg_N_avg_82[0]+params.ug_N_82[0])*work.frac_121674190848*(-params.Pg_N_init_82[0]+params.Pg_N_avg_82[0]+params.ug_N_82[0]);
  work.quad_394753474560[0] = (-params.Vg_N_avg_82[0]-params.Thetag_N_avg_82[0]+params.vg_N_82[0])*work.frac_121674190848*(-params.Vg_N_avg_82[0]-params.Thetag_N_avg_82[0]+params.vg_N_82[0]);
  work.quad_547133394944[0] = (-params.Pg_N_init_83[0]+params.Pg_N_avg_83[0]+params.ug_N_83[0])*work.frac_121674190848*(-params.Pg_N_init_83[0]+params.Pg_N_avg_83[0]+params.ug_N_83[0]);
  work.quad_209782870016[0] = (-params.Vg_N_avg_83[0]-params.Thetag_N_avg_83[0]+params.vg_N_83[0])*work.frac_121674190848*(-params.Vg_N_avg_83[0]-params.Thetag_N_avg_83[0]+params.vg_N_83[0]);
  work.quad_381733597184[0] = (-params.Pg_N_init_84[0]+params.Pg_N_avg_84[0]+params.ug_N_84[0])*work.frac_121674190848*(-params.Pg_N_init_84[0]+params.Pg_N_avg_84[0]+params.ug_N_84[0]);
  work.quad_152716124160[0] = (-params.Vg_N_avg_84[0]-params.Thetag_N_avg_84[0]+params.vg_N_84[0])*work.frac_121674190848*(-params.Vg_N_avg_84[0]-params.Thetag_N_avg_84[0]+params.vg_N_84[0]);
  work.quad_128809979904[0] = (-params.Pg_N_init_85[0]+params.Pg_N_avg_85[0]+params.ug_N_85[0])*work.frac_121674190848*(-params.Pg_N_init_85[0]+params.Pg_N_avg_85[0]+params.ug_N_85[0]);
  work.quad_335236542464[0] = (-params.Vg_N_avg_85[0]-params.Thetag_N_avg_85[0]+params.vg_N_85[0])*work.frac_121674190848*(-params.Vg_N_avg_85[0]-params.Thetag_N_avg_85[0]+params.vg_N_85[0]);
  work.quad_909988339712[0] = (-params.Pg_N_init_86[0]+params.Pg_N_avg_86[0]+params.ug_N_86[0])*work.frac_121674190848*(-params.Pg_N_init_86[0]+params.Pg_N_avg_86[0]+params.ug_N_86[0]);
  work.quad_852921757696[0] = (-params.Vg_N_avg_86[0]-params.Thetag_N_avg_86[0]+params.vg_N_86[0])*work.frac_121674190848*(-params.Vg_N_avg_86[0]-params.Thetag_N_avg_86[0]+params.vg_N_86[0]);
  work.quad_787442696192[0] = (-params.Pg_N_init_87[0]+params.Pg_N_avg_87[0]+params.ug_N_87[0])*work.frac_121674190848*(-params.Pg_N_init_87[0]+params.Pg_N_avg_87[0]+params.ug_N_87[0]);
  work.quad_961277771776[0] = (-params.Vg_N_avg_87[0]-params.Thetag_N_avg_87[0]+params.vg_N_87[0])*work.frac_121674190848*(-params.Vg_N_avg_87[0]-params.Thetag_N_avg_87[0]+params.vg_N_87[0]);
  work.quad_939277180928[0] = (-params.Pg_N_init_88[0]+params.Pg_N_avg_88[0]+params.ug_N_88[0])*work.frac_121674190848*(-params.Pg_N_init_88[0]+params.Pg_N_avg_88[0]+params.ug_N_88[0]);
  work.quad_429044678656[0] = (-params.Vg_N_avg_88[0]-params.Thetag_N_avg_88[0]+params.vg_N_88[0])*work.frac_121674190848*(-params.Vg_N_avg_88[0]-params.Thetag_N_avg_88[0]+params.vg_N_88[0]);
  work.quad_861783474176[0] = (-params.Pg_N_init_89[0]+params.Pg_N_avg_89[0]+params.ug_N_89[0])*work.frac_121674190848*(-params.Pg_N_init_89[0]+params.Pg_N_avg_89[0]+params.ug_N_89[0]);
  work.quad_340061249536[0] = (-params.Vg_N_avg_89[0]-params.Thetag_N_avg_89[0]+params.vg_N_89[0])*work.frac_121674190848*(-params.Vg_N_avg_89[0]-params.Thetag_N_avg_89[0]+params.vg_N_89[0]);
  work.quad_279979859968[0] = (-params.Pg_N_init_90[0]+params.Pg_N_avg_90[0]+params.ug_N_90[0])*work.frac_121674190848*(-params.Pg_N_init_90[0]+params.Pg_N_avg_90[0]+params.ug_N_90[0]);
  work.quad_869539332096[0] = (-params.Vg_N_avg_90[0]-params.Thetag_N_avg_90[0]+params.vg_N_90[0])*work.frac_121674190848*(-params.Vg_N_avg_90[0]-params.Thetag_N_avg_90[0]+params.vg_N_90[0]);
  work.quad_539265785856[0] = (-params.Pg_N_init_91[0]+params.Pg_N_avg_91[0]+params.ug_N_91[0])*work.frac_121674190848*(-params.Pg_N_init_91[0]+params.Pg_N_avg_91[0]+params.ug_N_91[0]);
  work.quad_872875143168[0] = (-params.Vg_N_avg_91[0]-params.Thetag_N_avg_91[0]+params.vg_N_91[0])*work.frac_121674190848*(-params.Vg_N_avg_91[0]-params.Thetag_N_avg_91[0]+params.vg_N_91[0]);
  work.quad_940092141568[0] = (-params.Pg_N_init_92[0]+params.Pg_N_avg_92[0]+params.ug_N_92[0])*work.frac_121674190848*(-params.Pg_N_init_92[0]+params.Pg_N_avg_92[0]+params.ug_N_92[0]);
  work.quad_320369504256[0] = (-params.Vg_N_avg_92[0]-params.Thetag_N_avg_92[0]+params.vg_N_92[0])*work.frac_121674190848*(-params.Vg_N_avg_92[0]-params.Thetag_N_avg_92[0]+params.vg_N_92[0]);
  work.quad_814284275712[0] = (-params.Pg_N_init_93[0]+params.Pg_N_avg_93[0]+params.ug_N_93[0])*work.frac_121674190848*(-params.Pg_N_init_93[0]+params.Pg_N_avg_93[0]+params.ug_N_93[0]);
  work.quad_850341859328[0] = (-params.Vg_N_avg_93[0]-params.Thetag_N_avg_93[0]+params.vg_N_93[0])*work.frac_121674190848*(-params.Vg_N_avg_93[0]-params.Thetag_N_avg_93[0]+params.vg_N_93[0]);
  work.quad_668125876224[0] = (-params.Pg_N_init_94[0]+params.Pg_N_avg_94[0]+params.ug_N_94[0])*work.frac_121674190848*(-params.Pg_N_init_94[0]+params.Pg_N_avg_94[0]+params.ug_N_94[0]);
  work.quad_768845512704[0] = (-params.Vg_N_avg_94[0]-params.Thetag_N_avg_94[0]+params.vg_N_94[0])*work.frac_121674190848*(-params.Vg_N_avg_94[0]-params.Thetag_N_avg_94[0]+params.vg_N_94[0]);
  work.quad_180052918272[0] = (-params.Pg_N_init_95[0]+params.Pg_N_avg_95[0]+params.ug_N_95[0])*work.frac_121674190848*(-params.Pg_N_init_95[0]+params.Pg_N_avg_95[0]+params.ug_N_95[0]);
  work.quad_637222821888[0] = (-params.Vg_N_avg_95[0]-params.Thetag_N_avg_95[0]+params.vg_N_95[0])*work.frac_121674190848*(-params.Vg_N_avg_95[0]-params.Thetag_N_avg_95[0]+params.vg_N_95[0]);
  work.quad_117911429120[0] = (-params.Pg_N_init_96[0]+params.Pg_N_avg_96[0]+params.ug_N_96[0])*work.frac_121674190848*(-params.Pg_N_init_96[0]+params.Pg_N_avg_96[0]+params.ug_N_96[0]);
  work.quad_793053450240[0] = (-params.Vg_N_avg_96[0]-params.Thetag_N_avg_96[0]+params.vg_N_96[0])*work.frac_121674190848*(-params.Vg_N_avg_96[0]-params.Thetag_N_avg_96[0]+params.vg_N_96[0]);
  work.quad_161320878080[0] = (-params.Pg_N_init_97[0]+params.Pg_N_avg_97[0]+params.ug_N_97[0])*work.frac_121674190848*(-params.Pg_N_init_97[0]+params.Pg_N_avg_97[0]+params.ug_N_97[0]);
  work.quad_502933229568[0] = (-params.Vg_N_avg_97[0]-params.Thetag_N_avg_97[0]+params.vg_N_97[0])*work.frac_121674190848*(-params.Vg_N_avg_97[0]-params.Thetag_N_avg_97[0]+params.vg_N_97[0]);
  work.quad_890543960064[0] = (-params.Pg_N_init_98[0]+params.Pg_N_avg_98[0]+params.ug_N_98[0])*work.frac_121674190848*(-params.Pg_N_init_98[0]+params.Pg_N_avg_98[0]+params.ug_N_98[0]);
  work.quad_620316852224[0] = (-params.Vg_N_avg_98[0]-params.Thetag_N_avg_98[0]+params.vg_N_98[0])*work.frac_121674190848*(-params.Vg_N_avg_98[0]-params.Thetag_N_avg_98[0]+params.vg_N_98[0]);
  work.quad_682189721600[0] = (-params.Pg_N_init_99[0]+params.Pg_N_avg_99[0]+params.ug_N_99[0])*work.frac_121674190848*(-params.Pg_N_init_99[0]+params.Pg_N_avg_99[0]+params.ug_N_99[0]);
  work.quad_367930048512[0] = (-params.Vg_N_avg_99[0]-params.Thetag_N_avg_99[0]+params.vg_N_99[0])*work.frac_121674190848*(-params.Vg_N_avg_99[0]-params.Thetag_N_avg_99[0]+params.vg_N_99[0]);
  work.quad_515601072128[0] = (-params.Pg_N_init_100[0]+params.Pg_N_avg_100[0]+params.ug_N_100[0])*work.frac_121674190848*(-params.Pg_N_init_100[0]+params.Pg_N_avg_100[0]+params.ug_N_100[0]);
  work.quad_600421740544[0] = (-params.Vg_N_avg_100[0]-params.Thetag_N_avg_100[0]+params.vg_N_100[0])*work.frac_121674190848*(-params.Vg_N_avg_100[0]-params.Thetag_N_avg_100[0]+params.vg_N_100[0]);
  work.quad_657550438400[0] = (-params.Pg_N_init_101[0]+params.Pg_N_avg_101[0]+params.ug_N_101[0])*work.frac_121674190848*(-params.Pg_N_init_101[0]+params.Pg_N_avg_101[0]+params.ug_N_101[0]);
  work.quad_478485061632[0] = (-params.Vg_N_avg_101[0]-params.Thetag_N_avg_101[0]+params.vg_N_101[0])*work.frac_121674190848*(-params.Vg_N_avg_101[0]-params.Thetag_N_avg_101[0]+params.vg_N_101[0]);
}
/* Produced by CVXGEN, 2015-09-15 19:23:47 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: ldl.c. */
/* Description: Basic test harness for solver.c. */
/* Be sure to place ldl_solve first, so storage schemes are defined by it. */
void Gensolver::ldl_solve(double *target, double *var) {
  int i;
  /* Find var = (L*diag(work.d)*L') \ target, then unpermute. */
  /* Answer goes into var. */
  /* Forward substitution. */
  /* Include permutation as we retrieve from target. Use v so we can unpermute */
  /* later. */
  work.v[0] = target[1];
  work.v[1] = target[2];
  work.v[2] = target[3];
  work.v[3] = target[4];
  work.v[4] = target[5];
  work.v[5] = target[6];
  work.v[6] = target[7];
  work.v[7] = target[8];
  work.v[8] = target[9];
  work.v[9] = target[10];
  work.v[10] = target[11];
  work.v[11] = target[12];
  work.v[12] = target[13];
  work.v[13] = target[14];
  work.v[14] = target[15];
  work.v[15] = target[16];
  work.v[16] = target[17];
  work.v[17] = target[18];
  work.v[18] = target[19];
  work.v[19] = target[20];
  work.v[20] = target[21];
  work.v[21] = target[22];
  work.v[22] = target[23];
  work.v[23] = target[24];
  work.v[24] = target[25];
  work.v[25] = target[26];
  work.v[26] = target[27];
  work.v[27] = target[28];
  work.v[28] = target[29];
  work.v[29] = target[30];
  work.v[30] = target[31];
  work.v[31] = target[32];
  work.v[32] = target[33];
  work.v[33] = target[34];
  work.v[34] = target[35];
  work.v[35] = target[36];
  work.v[36] = target[37];
  work.v[37] = target[38];
  work.v[38] = target[39];
  work.v[39] = target[40];
  work.v[40] = target[41];
  work.v[41] = target[42];
  work.v[42] = target[43];
  work.v[43] = target[44];
  work.v[44] = target[45];
  work.v[45] = target[46];
  work.v[46] = target[47];
  work.v[47] = target[48];
  work.v[48] = target[49];
  work.v[49] = target[50];
  work.v[50] = target[51];
  work.v[51] = target[52];
  work.v[52] = target[53];
  work.v[53] = target[54];
  work.v[54] = target[55];
  work.v[55] = target[56];
  work.v[56] = target[57];
  work.v[57] = target[58];
  work.v[58] = target[59];
  work.v[59] = target[60];
  work.v[60] = target[61];
  work.v[61] = target[62];
  work.v[62] = target[63];
  work.v[63] = target[64];
  work.v[64] = target[65];
  work.v[65] = target[66];
  work.v[66] = target[67];
  work.v[67] = target[68];
  work.v[68] = target[69];
  work.v[69] = target[70];
  work.v[70] = target[71];
  work.v[71] = target[72];
  work.v[72] = target[73];
  work.v[73] = target[74];
  work.v[74] = target[75];
  work.v[75] = target[76];
  work.v[76] = target[77];
  work.v[77] = target[78];
  work.v[78] = target[79];
  work.v[79] = target[80];
  work.v[80] = target[81];
  work.v[81] = target[82];
  work.v[82] = target[83];
  work.v[83] = target[84];
  work.v[84] = target[85];
  work.v[85] = target[86];
  work.v[86] = target[87];
  work.v[87] = target[88];
  work.v[88] = target[89];
  work.v[89] = target[90];
  work.v[90] = target[91];
  work.v[91] = target[92];
  work.v[92] = target[93];
  work.v[93] = target[94];
  work.v[94] = target[95];
  work.v[95] = target[96];
  work.v[96] = target[97];
  work.v[97] = target[98];
  work.v[98] = target[99];
  work.v[99] = target[100];
  work.v[100] = target[101];
  work.v[101] = target[102];
  work.v[102] = target[103];
  work.v[103] = target[104]-work.L[0]*work.v[101];
  work.v[104] = target[0]-work.L[1]*work.v[103];
  work.v[105] = target[105]-work.L[2]*work.v[102]-work.L[3]*work.v[104];
  /* Diagonal scaling. Assume correctness of work.d_inv. */
  for (i = 0; i < 106; i++)
    work.v[i] *= work.d_inv[i];
  /* Back substitution */
  work.v[104] -= work.L[3]*work.v[105];
  work.v[103] -= work.L[1]*work.v[104];
  work.v[102] -= work.L[2]*work.v[105];
  work.v[101] -= work.L[0]*work.v[103];
  /* Unpermute the result, from v to var. */
  var[0] = work.v[104];
  var[1] = work.v[0];
  var[2] = work.v[1];
  var[3] = work.v[2];
  var[4] = work.v[3];
  var[5] = work.v[4];
  var[6] = work.v[5];
  var[7] = work.v[6];
  var[8] = work.v[7];
  var[9] = work.v[8];
  var[10] = work.v[9];
  var[11] = work.v[10];
  var[12] = work.v[11];
  var[13] = work.v[12];
  var[14] = work.v[13];
  var[15] = work.v[14];
  var[16] = work.v[15];
  var[17] = work.v[16];
  var[18] = work.v[17];
  var[19] = work.v[18];
  var[20] = work.v[19];
  var[21] = work.v[20];
  var[22] = work.v[21];
  var[23] = work.v[22];
  var[24] = work.v[23];
  var[25] = work.v[24];
  var[26] = work.v[25];
  var[27] = work.v[26];
  var[28] = work.v[27];
  var[29] = work.v[28];
  var[30] = work.v[29];
  var[31] = work.v[30];
  var[32] = work.v[31];
  var[33] = work.v[32];
  var[34] = work.v[33];
  var[35] = work.v[34];
  var[36] = work.v[35];
  var[37] = work.v[36];
  var[38] = work.v[37];
  var[39] = work.v[38];
  var[40] = work.v[39];
  var[41] = work.v[40];
  var[42] = work.v[41];
  var[43] = work.v[42];
  var[44] = work.v[43];
  var[45] = work.v[44];
  var[46] = work.v[45];
  var[47] = work.v[46];
  var[48] = work.v[47];
  var[49] = work.v[48];
  var[50] = work.v[49];
  var[51] = work.v[50];
  var[52] = work.v[51];
  var[53] = work.v[52];
  var[54] = work.v[53];
  var[55] = work.v[54];
  var[56] = work.v[55];
  var[57] = work.v[56];
  var[58] = work.v[57];
  var[59] = work.v[58];
  var[60] = work.v[59];
  var[61] = work.v[60];
  var[62] = work.v[61];
  var[63] = work.v[62];
  var[64] = work.v[63];
  var[65] = work.v[64];
  var[66] = work.v[65];
  var[67] = work.v[66];
  var[68] = work.v[67];
  var[69] = work.v[68];
  var[70] = work.v[69];
  var[71] = work.v[70];
  var[72] = work.v[71];
  var[73] = work.v[72];
  var[74] = work.v[73];
  var[75] = work.v[74];
  var[76] = work.v[75];
  var[77] = work.v[76];
  var[78] = work.v[77];
  var[79] = work.v[78];
  var[80] = work.v[79];
  var[81] = work.v[80];
  var[82] = work.v[81];
  var[83] = work.v[82];
  var[84] = work.v[83];
  var[85] = work.v[84];
  var[86] = work.v[85];
  var[87] = work.v[86];
  var[88] = work.v[87];
  var[89] = work.v[88];
  var[90] = work.v[89];
  var[91] = work.v[90];
  var[92] = work.v[91];
  var[93] = work.v[92];
  var[94] = work.v[93];
  var[95] = work.v[94];
  var[96] = work.v[95];
  var[97] = work.v[96];
  var[98] = work.v[97];
  var[99] = work.v[98];
  var[100] = work.v[99];
  var[101] = work.v[100];
  var[102] = work.v[101];
  var[103] = work.v[102];
  var[104] = work.v[103];
  var[105] = work.v[105];
#ifndef ZERO_LIBRARY_MODE
  if (settings.debug) {
    printf("Squared norm for solution is %.8g.\n", check_residual(target, var));
  }
#endif
}
void Gensolver::ldl_factor(void) {
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
  work.v[2] = work.KKT[2];
  work.d[2] = work.v[2];
  if (work.d[2] < 0)
    work.d[2] = settings.kkt_reg;
  else
    work.d[2] += settings.kkt_reg;
  work.d_inv[2] = 1/work.d[2];
  work.v[3] = work.KKT[3];
  work.d[3] = work.v[3];
  if (work.d[3] < 0)
    work.d[3] = settings.kkt_reg;
  else
    work.d[3] += settings.kkt_reg;
  work.d_inv[3] = 1/work.d[3];
  work.v[4] = work.KKT[4];
  work.d[4] = work.v[4];
  if (work.d[4] < 0)
    work.d[4] = settings.kkt_reg;
  else
    work.d[4] += settings.kkt_reg;
  work.d_inv[4] = 1/work.d[4];
  work.v[5] = work.KKT[5];
  work.d[5] = work.v[5];
  if (work.d[5] < 0)
    work.d[5] = settings.kkt_reg;
  else
    work.d[5] += settings.kkt_reg;
  work.d_inv[5] = 1/work.d[5];
  work.v[6] = work.KKT[6];
  work.d[6] = work.v[6];
  if (work.d[6] < 0)
    work.d[6] = settings.kkt_reg;
  else
    work.d[6] += settings.kkt_reg;
  work.d_inv[6] = 1/work.d[6];
  work.v[7] = work.KKT[7];
  work.d[7] = work.v[7];
  if (work.d[7] < 0)
    work.d[7] = settings.kkt_reg;
  else
    work.d[7] += settings.kkt_reg;
  work.d_inv[7] = 1/work.d[7];
  work.v[8] = work.KKT[8];
  work.d[8] = work.v[8];
  if (work.d[8] < 0)
    work.d[8] = settings.kkt_reg;
  else
    work.d[8] += settings.kkt_reg;
  work.d_inv[8] = 1/work.d[8];
  work.v[9] = work.KKT[9];
  work.d[9] = work.v[9];
  if (work.d[9] < 0)
    work.d[9] = settings.kkt_reg;
  else
    work.d[9] += settings.kkt_reg;
  work.d_inv[9] = 1/work.d[9];
  work.v[10] = work.KKT[10];
  work.d[10] = work.v[10];
  if (work.d[10] < 0)
    work.d[10] = settings.kkt_reg;
  else
    work.d[10] += settings.kkt_reg;
  work.d_inv[10] = 1/work.d[10];
  work.v[11] = work.KKT[11];
  work.d[11] = work.v[11];
  if (work.d[11] < 0)
    work.d[11] = settings.kkt_reg;
  else
    work.d[11] += settings.kkt_reg;
  work.d_inv[11] = 1/work.d[11];
  work.v[12] = work.KKT[12];
  work.d[12] = work.v[12];
  if (work.d[12] < 0)
    work.d[12] = settings.kkt_reg;
  else
    work.d[12] += settings.kkt_reg;
  work.d_inv[12] = 1/work.d[12];
  work.v[13] = work.KKT[13];
  work.d[13] = work.v[13];
  if (work.d[13] < 0)
    work.d[13] = settings.kkt_reg;
  else
    work.d[13] += settings.kkt_reg;
  work.d_inv[13] = 1/work.d[13];
  work.v[14] = work.KKT[14];
  work.d[14] = work.v[14];
  if (work.d[14] < 0)
    work.d[14] = settings.kkt_reg;
  else
    work.d[14] += settings.kkt_reg;
  work.d_inv[14] = 1/work.d[14];
  work.v[15] = work.KKT[15];
  work.d[15] = work.v[15];
  if (work.d[15] < 0)
    work.d[15] = settings.kkt_reg;
  else
    work.d[15] += settings.kkt_reg;
  work.d_inv[15] = 1/work.d[15];
  work.v[16] = work.KKT[16];
  work.d[16] = work.v[16];
  if (work.d[16] < 0)
    work.d[16] = settings.kkt_reg;
  else
    work.d[16] += settings.kkt_reg;
  work.d_inv[16] = 1/work.d[16];
  work.v[17] = work.KKT[17];
  work.d[17] = work.v[17];
  if (work.d[17] < 0)
    work.d[17] = settings.kkt_reg;
  else
    work.d[17] += settings.kkt_reg;
  work.d_inv[17] = 1/work.d[17];
  work.v[18] = work.KKT[18];
  work.d[18] = work.v[18];
  if (work.d[18] < 0)
    work.d[18] = settings.kkt_reg;
  else
    work.d[18] += settings.kkt_reg;
  work.d_inv[18] = 1/work.d[18];
  work.v[19] = work.KKT[19];
  work.d[19] = work.v[19];
  if (work.d[19] < 0)
    work.d[19] = settings.kkt_reg;
  else
    work.d[19] += settings.kkt_reg;
  work.d_inv[19] = 1/work.d[19];
  work.v[20] = work.KKT[20];
  work.d[20] = work.v[20];
  if (work.d[20] < 0)
    work.d[20] = settings.kkt_reg;
  else
    work.d[20] += settings.kkt_reg;
  work.d_inv[20] = 1/work.d[20];
  work.v[21] = work.KKT[21];
  work.d[21] = work.v[21];
  if (work.d[21] < 0)
    work.d[21] = settings.kkt_reg;
  else
    work.d[21] += settings.kkt_reg;
  work.d_inv[21] = 1/work.d[21];
  work.v[22] = work.KKT[22];
  work.d[22] = work.v[22];
  if (work.d[22] < 0)
    work.d[22] = settings.kkt_reg;
  else
    work.d[22] += settings.kkt_reg;
  work.d_inv[22] = 1/work.d[22];
  work.v[23] = work.KKT[23];
  work.d[23] = work.v[23];
  if (work.d[23] < 0)
    work.d[23] = settings.kkt_reg;
  else
    work.d[23] += settings.kkt_reg;
  work.d_inv[23] = 1/work.d[23];
  work.v[24] = work.KKT[24];
  work.d[24] = work.v[24];
  if (work.d[24] < 0)
    work.d[24] = settings.kkt_reg;
  else
    work.d[24] += settings.kkt_reg;
  work.d_inv[24] = 1/work.d[24];
  work.v[25] = work.KKT[25];
  work.d[25] = work.v[25];
  if (work.d[25] < 0)
    work.d[25] = settings.kkt_reg;
  else
    work.d[25] += settings.kkt_reg;
  work.d_inv[25] = 1/work.d[25];
  work.v[26] = work.KKT[26];
  work.d[26] = work.v[26];
  if (work.d[26] < 0)
    work.d[26] = settings.kkt_reg;
  else
    work.d[26] += settings.kkt_reg;
  work.d_inv[26] = 1/work.d[26];
  work.v[27] = work.KKT[27];
  work.d[27] = work.v[27];
  if (work.d[27] < 0)
    work.d[27] = settings.kkt_reg;
  else
    work.d[27] += settings.kkt_reg;
  work.d_inv[27] = 1/work.d[27];
  work.v[28] = work.KKT[28];
  work.d[28] = work.v[28];
  if (work.d[28] < 0)
    work.d[28] = settings.kkt_reg;
  else
    work.d[28] += settings.kkt_reg;
  work.d_inv[28] = 1/work.d[28];
  work.v[29] = work.KKT[29];
  work.d[29] = work.v[29];
  if (work.d[29] < 0)
    work.d[29] = settings.kkt_reg;
  else
    work.d[29] += settings.kkt_reg;
  work.d_inv[29] = 1/work.d[29];
  work.v[30] = work.KKT[30];
  work.d[30] = work.v[30];
  if (work.d[30] < 0)
    work.d[30] = settings.kkt_reg;
  else
    work.d[30] += settings.kkt_reg;
  work.d_inv[30] = 1/work.d[30];
  work.v[31] = work.KKT[31];
  work.d[31] = work.v[31];
  if (work.d[31] < 0)
    work.d[31] = settings.kkt_reg;
  else
    work.d[31] += settings.kkt_reg;
  work.d_inv[31] = 1/work.d[31];
  work.v[32] = work.KKT[32];
  work.d[32] = work.v[32];
  if (work.d[32] < 0)
    work.d[32] = settings.kkt_reg;
  else
    work.d[32] += settings.kkt_reg;
  work.d_inv[32] = 1/work.d[32];
  work.v[33] = work.KKT[33];
  work.d[33] = work.v[33];
  if (work.d[33] < 0)
    work.d[33] = settings.kkt_reg;
  else
    work.d[33] += settings.kkt_reg;
  work.d_inv[33] = 1/work.d[33];
  work.v[34] = work.KKT[34];
  work.d[34] = work.v[34];
  if (work.d[34] < 0)
    work.d[34] = settings.kkt_reg;
  else
    work.d[34] += settings.kkt_reg;
  work.d_inv[34] = 1/work.d[34];
  work.v[35] = work.KKT[35];
  work.d[35] = work.v[35];
  if (work.d[35] < 0)
    work.d[35] = settings.kkt_reg;
  else
    work.d[35] += settings.kkt_reg;
  work.d_inv[35] = 1/work.d[35];
  work.v[36] = work.KKT[36];
  work.d[36] = work.v[36];
  if (work.d[36] < 0)
    work.d[36] = settings.kkt_reg;
  else
    work.d[36] += settings.kkt_reg;
  work.d_inv[36] = 1/work.d[36];
  work.v[37] = work.KKT[37];
  work.d[37] = work.v[37];
  if (work.d[37] < 0)
    work.d[37] = settings.kkt_reg;
  else
    work.d[37] += settings.kkt_reg;
  work.d_inv[37] = 1/work.d[37];
  work.v[38] = work.KKT[38];
  work.d[38] = work.v[38];
  if (work.d[38] < 0)
    work.d[38] = settings.kkt_reg;
  else
    work.d[38] += settings.kkt_reg;
  work.d_inv[38] = 1/work.d[38];
  work.v[39] = work.KKT[39];
  work.d[39] = work.v[39];
  if (work.d[39] < 0)
    work.d[39] = settings.kkt_reg;
  else
    work.d[39] += settings.kkt_reg;
  work.d_inv[39] = 1/work.d[39];
  work.v[40] = work.KKT[40];
  work.d[40] = work.v[40];
  if (work.d[40] < 0)
    work.d[40] = settings.kkt_reg;
  else
    work.d[40] += settings.kkt_reg;
  work.d_inv[40] = 1/work.d[40];
  work.v[41] = work.KKT[41];
  work.d[41] = work.v[41];
  if (work.d[41] < 0)
    work.d[41] = settings.kkt_reg;
  else
    work.d[41] += settings.kkt_reg;
  work.d_inv[41] = 1/work.d[41];
  work.v[42] = work.KKT[42];
  work.d[42] = work.v[42];
  if (work.d[42] < 0)
    work.d[42] = settings.kkt_reg;
  else
    work.d[42] += settings.kkt_reg;
  work.d_inv[42] = 1/work.d[42];
  work.v[43] = work.KKT[43];
  work.d[43] = work.v[43];
  if (work.d[43] < 0)
    work.d[43] = settings.kkt_reg;
  else
    work.d[43] += settings.kkt_reg;
  work.d_inv[43] = 1/work.d[43];
  work.v[44] = work.KKT[44];
  work.d[44] = work.v[44];
  if (work.d[44] < 0)
    work.d[44] = settings.kkt_reg;
  else
    work.d[44] += settings.kkt_reg;
  work.d_inv[44] = 1/work.d[44];
  work.v[45] = work.KKT[45];
  work.d[45] = work.v[45];
  if (work.d[45] < 0)
    work.d[45] = settings.kkt_reg;
  else
    work.d[45] += settings.kkt_reg;
  work.d_inv[45] = 1/work.d[45];
  work.v[46] = work.KKT[46];
  work.d[46] = work.v[46];
  if (work.d[46] < 0)
    work.d[46] = settings.kkt_reg;
  else
    work.d[46] += settings.kkt_reg;
  work.d_inv[46] = 1/work.d[46];
  work.v[47] = work.KKT[47];
  work.d[47] = work.v[47];
  if (work.d[47] < 0)
    work.d[47] = settings.kkt_reg;
  else
    work.d[47] += settings.kkt_reg;
  work.d_inv[47] = 1/work.d[47];
  work.v[48] = work.KKT[48];
  work.d[48] = work.v[48];
  if (work.d[48] < 0)
    work.d[48] = settings.kkt_reg;
  else
    work.d[48] += settings.kkt_reg;
  work.d_inv[48] = 1/work.d[48];
  work.v[49] = work.KKT[49];
  work.d[49] = work.v[49];
  if (work.d[49] < 0)
    work.d[49] = settings.kkt_reg;
  else
    work.d[49] += settings.kkt_reg;
  work.d_inv[49] = 1/work.d[49];
  work.v[50] = work.KKT[50];
  work.d[50] = work.v[50];
  if (work.d[50] < 0)
    work.d[50] = settings.kkt_reg;
  else
    work.d[50] += settings.kkt_reg;
  work.d_inv[50] = 1/work.d[50];
  work.v[51] = work.KKT[51];
  work.d[51] = work.v[51];
  if (work.d[51] < 0)
    work.d[51] = settings.kkt_reg;
  else
    work.d[51] += settings.kkt_reg;
  work.d_inv[51] = 1/work.d[51];
  work.v[52] = work.KKT[52];
  work.d[52] = work.v[52];
  if (work.d[52] < 0)
    work.d[52] = settings.kkt_reg;
  else
    work.d[52] += settings.kkt_reg;
  work.d_inv[52] = 1/work.d[52];
  work.v[53] = work.KKT[53];
  work.d[53] = work.v[53];
  if (work.d[53] < 0)
    work.d[53] = settings.kkt_reg;
  else
    work.d[53] += settings.kkt_reg;
  work.d_inv[53] = 1/work.d[53];
  work.v[54] = work.KKT[54];
  work.d[54] = work.v[54];
  if (work.d[54] < 0)
    work.d[54] = settings.kkt_reg;
  else
    work.d[54] += settings.kkt_reg;
  work.d_inv[54] = 1/work.d[54];
  work.v[55] = work.KKT[55];
  work.d[55] = work.v[55];
  if (work.d[55] < 0)
    work.d[55] = settings.kkt_reg;
  else
    work.d[55] += settings.kkt_reg;
  work.d_inv[55] = 1/work.d[55];
  work.v[56] = work.KKT[56];
  work.d[56] = work.v[56];
  if (work.d[56] < 0)
    work.d[56] = settings.kkt_reg;
  else
    work.d[56] += settings.kkt_reg;
  work.d_inv[56] = 1/work.d[56];
  work.v[57] = work.KKT[57];
  work.d[57] = work.v[57];
  if (work.d[57] < 0)
    work.d[57] = settings.kkt_reg;
  else
    work.d[57] += settings.kkt_reg;
  work.d_inv[57] = 1/work.d[57];
  work.v[58] = work.KKT[58];
  work.d[58] = work.v[58];
  if (work.d[58] < 0)
    work.d[58] = settings.kkt_reg;
  else
    work.d[58] += settings.kkt_reg;
  work.d_inv[58] = 1/work.d[58];
  work.v[59] = work.KKT[59];
  work.d[59] = work.v[59];
  if (work.d[59] < 0)
    work.d[59] = settings.kkt_reg;
  else
    work.d[59] += settings.kkt_reg;
  work.d_inv[59] = 1/work.d[59];
  work.v[60] = work.KKT[60];
  work.d[60] = work.v[60];
  if (work.d[60] < 0)
    work.d[60] = settings.kkt_reg;
  else
    work.d[60] += settings.kkt_reg;
  work.d_inv[60] = 1/work.d[60];
  work.v[61] = work.KKT[61];
  work.d[61] = work.v[61];
  if (work.d[61] < 0)
    work.d[61] = settings.kkt_reg;
  else
    work.d[61] += settings.kkt_reg;
  work.d_inv[61] = 1/work.d[61];
  work.v[62] = work.KKT[62];
  work.d[62] = work.v[62];
  if (work.d[62] < 0)
    work.d[62] = settings.kkt_reg;
  else
    work.d[62] += settings.kkt_reg;
  work.d_inv[62] = 1/work.d[62];
  work.v[63] = work.KKT[63];
  work.d[63] = work.v[63];
  if (work.d[63] < 0)
    work.d[63] = settings.kkt_reg;
  else
    work.d[63] += settings.kkt_reg;
  work.d_inv[63] = 1/work.d[63];
  work.v[64] = work.KKT[64];
  work.d[64] = work.v[64];
  if (work.d[64] < 0)
    work.d[64] = settings.kkt_reg;
  else
    work.d[64] += settings.kkt_reg;
  work.d_inv[64] = 1/work.d[64];
  work.v[65] = work.KKT[65];
  work.d[65] = work.v[65];
  if (work.d[65] < 0)
    work.d[65] = settings.kkt_reg;
  else
    work.d[65] += settings.kkt_reg;
  work.d_inv[65] = 1/work.d[65];
  work.v[66] = work.KKT[66];
  work.d[66] = work.v[66];
  if (work.d[66] < 0)
    work.d[66] = settings.kkt_reg;
  else
    work.d[66] += settings.kkt_reg;
  work.d_inv[66] = 1/work.d[66];
  work.v[67] = work.KKT[67];
  work.d[67] = work.v[67];
  if (work.d[67] < 0)
    work.d[67] = settings.kkt_reg;
  else
    work.d[67] += settings.kkt_reg;
  work.d_inv[67] = 1/work.d[67];
  work.v[68] = work.KKT[68];
  work.d[68] = work.v[68];
  if (work.d[68] < 0)
    work.d[68] = settings.kkt_reg;
  else
    work.d[68] += settings.kkt_reg;
  work.d_inv[68] = 1/work.d[68];
  work.v[69] = work.KKT[69];
  work.d[69] = work.v[69];
  if (work.d[69] < 0)
    work.d[69] = settings.kkt_reg;
  else
    work.d[69] += settings.kkt_reg;
  work.d_inv[69] = 1/work.d[69];
  work.v[70] = work.KKT[70];
  work.d[70] = work.v[70];
  if (work.d[70] < 0)
    work.d[70] = settings.kkt_reg;
  else
    work.d[70] += settings.kkt_reg;
  work.d_inv[70] = 1/work.d[70];
  work.v[71] = work.KKT[71];
  work.d[71] = work.v[71];
  if (work.d[71] < 0)
    work.d[71] = settings.kkt_reg;
  else
    work.d[71] += settings.kkt_reg;
  work.d_inv[71] = 1/work.d[71];
  work.v[72] = work.KKT[72];
  work.d[72] = work.v[72];
  if (work.d[72] < 0)
    work.d[72] = settings.kkt_reg;
  else
    work.d[72] += settings.kkt_reg;
  work.d_inv[72] = 1/work.d[72];
  work.v[73] = work.KKT[73];
  work.d[73] = work.v[73];
  if (work.d[73] < 0)
    work.d[73] = settings.kkt_reg;
  else
    work.d[73] += settings.kkt_reg;
  work.d_inv[73] = 1/work.d[73];
  work.v[74] = work.KKT[74];
  work.d[74] = work.v[74];
  if (work.d[74] < 0)
    work.d[74] = settings.kkt_reg;
  else
    work.d[74] += settings.kkt_reg;
  work.d_inv[74] = 1/work.d[74];
  work.v[75] = work.KKT[75];
  work.d[75] = work.v[75];
  if (work.d[75] < 0)
    work.d[75] = settings.kkt_reg;
  else
    work.d[75] += settings.kkt_reg;
  work.d_inv[75] = 1/work.d[75];
  work.v[76] = work.KKT[76];
  work.d[76] = work.v[76];
  if (work.d[76] < 0)
    work.d[76] = settings.kkt_reg;
  else
    work.d[76] += settings.kkt_reg;
  work.d_inv[76] = 1/work.d[76];
  work.v[77] = work.KKT[77];
  work.d[77] = work.v[77];
  if (work.d[77] < 0)
    work.d[77] = settings.kkt_reg;
  else
    work.d[77] += settings.kkt_reg;
  work.d_inv[77] = 1/work.d[77];
  work.v[78] = work.KKT[78];
  work.d[78] = work.v[78];
  if (work.d[78] < 0)
    work.d[78] = settings.kkt_reg;
  else
    work.d[78] += settings.kkt_reg;
  work.d_inv[78] = 1/work.d[78];
  work.v[79] = work.KKT[79];
  work.d[79] = work.v[79];
  if (work.d[79] < 0)
    work.d[79] = settings.kkt_reg;
  else
    work.d[79] += settings.kkt_reg;
  work.d_inv[79] = 1/work.d[79];
  work.v[80] = work.KKT[80];
  work.d[80] = work.v[80];
  if (work.d[80] < 0)
    work.d[80] = settings.kkt_reg;
  else
    work.d[80] += settings.kkt_reg;
  work.d_inv[80] = 1/work.d[80];
  work.v[81] = work.KKT[81];
  work.d[81] = work.v[81];
  if (work.d[81] < 0)
    work.d[81] = settings.kkt_reg;
  else
    work.d[81] += settings.kkt_reg;
  work.d_inv[81] = 1/work.d[81];
  work.v[82] = work.KKT[82];
  work.d[82] = work.v[82];
  if (work.d[82] < 0)
    work.d[82] = settings.kkt_reg;
  else
    work.d[82] += settings.kkt_reg;
  work.d_inv[82] = 1/work.d[82];
  work.v[83] = work.KKT[83];
  work.d[83] = work.v[83];
  if (work.d[83] < 0)
    work.d[83] = settings.kkt_reg;
  else
    work.d[83] += settings.kkt_reg;
  work.d_inv[83] = 1/work.d[83];
  work.v[84] = work.KKT[84];
  work.d[84] = work.v[84];
  if (work.d[84] < 0)
    work.d[84] = settings.kkt_reg;
  else
    work.d[84] += settings.kkt_reg;
  work.d_inv[84] = 1/work.d[84];
  work.v[85] = work.KKT[85];
  work.d[85] = work.v[85];
  if (work.d[85] < 0)
    work.d[85] = settings.kkt_reg;
  else
    work.d[85] += settings.kkt_reg;
  work.d_inv[85] = 1/work.d[85];
  work.v[86] = work.KKT[86];
  work.d[86] = work.v[86];
  if (work.d[86] < 0)
    work.d[86] = settings.kkt_reg;
  else
    work.d[86] += settings.kkt_reg;
  work.d_inv[86] = 1/work.d[86];
  work.v[87] = work.KKT[87];
  work.d[87] = work.v[87];
  if (work.d[87] < 0)
    work.d[87] = settings.kkt_reg;
  else
    work.d[87] += settings.kkt_reg;
  work.d_inv[87] = 1/work.d[87];
  work.v[88] = work.KKT[88];
  work.d[88] = work.v[88];
  if (work.d[88] < 0)
    work.d[88] = settings.kkt_reg;
  else
    work.d[88] += settings.kkt_reg;
  work.d_inv[88] = 1/work.d[88];
  work.v[89] = work.KKT[89];
  work.d[89] = work.v[89];
  if (work.d[89] < 0)
    work.d[89] = settings.kkt_reg;
  else
    work.d[89] += settings.kkt_reg;
  work.d_inv[89] = 1/work.d[89];
  work.v[90] = work.KKT[90];
  work.d[90] = work.v[90];
  if (work.d[90] < 0)
    work.d[90] = settings.kkt_reg;
  else
    work.d[90] += settings.kkt_reg;
  work.d_inv[90] = 1/work.d[90];
  work.v[91] = work.KKT[91];
  work.d[91] = work.v[91];
  if (work.d[91] < 0)
    work.d[91] = settings.kkt_reg;
  else
    work.d[91] += settings.kkt_reg;
  work.d_inv[91] = 1/work.d[91];
  work.v[92] = work.KKT[92];
  work.d[92] = work.v[92];
  if (work.d[92] < 0)
    work.d[92] = settings.kkt_reg;
  else
    work.d[92] += settings.kkt_reg;
  work.d_inv[92] = 1/work.d[92];
  work.v[93] = work.KKT[93];
  work.d[93] = work.v[93];
  if (work.d[93] < 0)
    work.d[93] = settings.kkt_reg;
  else
    work.d[93] += settings.kkt_reg;
  work.d_inv[93] = 1/work.d[93];
  work.v[94] = work.KKT[94];
  work.d[94] = work.v[94];
  if (work.d[94] < 0)
    work.d[94] = settings.kkt_reg;
  else
    work.d[94] += settings.kkt_reg;
  work.d_inv[94] = 1/work.d[94];
  work.v[95] = work.KKT[95];
  work.d[95] = work.v[95];
  if (work.d[95] < 0)
    work.d[95] = settings.kkt_reg;
  else
    work.d[95] += settings.kkt_reg;
  work.d_inv[95] = 1/work.d[95];
  work.v[96] = work.KKT[96];
  work.d[96] = work.v[96];
  if (work.d[96] < 0)
    work.d[96] = settings.kkt_reg;
  else
    work.d[96] += settings.kkt_reg;
  work.d_inv[96] = 1/work.d[96];
  work.v[97] = work.KKT[97];
  work.d[97] = work.v[97];
  if (work.d[97] < 0)
    work.d[97] = settings.kkt_reg;
  else
    work.d[97] += settings.kkt_reg;
  work.d_inv[97] = 1/work.d[97];
  work.v[98] = work.KKT[98];
  work.d[98] = work.v[98];
  if (work.d[98] < 0)
    work.d[98] = settings.kkt_reg;
  else
    work.d[98] += settings.kkt_reg;
  work.d_inv[98] = 1/work.d[98];
  work.v[99] = work.KKT[99];
  work.d[99] = work.v[99];
  if (work.d[99] < 0)
    work.d[99] = settings.kkt_reg;
  else
    work.d[99] += settings.kkt_reg;
  work.d_inv[99] = 1/work.d[99];
  work.v[100] = work.KKT[100];
  work.d[100] = work.v[100];
  if (work.d[100] < 0)
    work.d[100] = settings.kkt_reg;
  else
    work.d[100] += settings.kkt_reg;
  work.d_inv[100] = 1/work.d[100];
  work.v[101] = work.KKT[101];
  work.d[101] = work.v[101];
  if (work.d[101] < 0)
    work.d[101] = settings.kkt_reg;
  else
    work.d[101] += settings.kkt_reg;
  work.d_inv[101] = 1/work.d[101];
  work.L[0] = (work.KKT[102])*work.d_inv[101];
  work.v[102] = work.KKT[103];
  work.d[102] = work.v[102];
  if (work.d[102] < 0)
    work.d[102] = settings.kkt_reg;
  else
    work.d[102] += settings.kkt_reg;
  work.d_inv[102] = 1/work.d[102];
  work.L[2] = (work.KKT[104])*work.d_inv[102];
  work.v[101] = work.L[0]*work.d[101];
  work.v[103] = work.KKT[105]-work.L[0]*work.v[101];
  work.d[103] = work.v[103];
  if (work.d[103] > 0)
    work.d[103] = -settings.kkt_reg;
  else
    work.d[103] -= settings.kkt_reg;
  work.d_inv[103] = 1/work.d[103];
  work.L[1] = (work.KKT[106])*work.d_inv[103];
  work.v[103] = work.L[1]*work.d[103];
  work.v[104] = work.KKT[107]-work.L[1]*work.v[103];
  work.d[104] = work.v[104];
  if (work.d[104] < 0)
    work.d[104] = settings.kkt_reg;
  else
    work.d[104] += settings.kkt_reg;
  work.d_inv[104] = 1/work.d[104];
  work.L[3] = (work.KKT[108])*work.d_inv[104];
  work.v[102] = work.L[2]*work.d[102];
  work.v[104] = work.L[3]*work.d[104];
  work.v[105] = work.KKT[109]-work.L[2]*work.v[102]-work.L[3]*work.v[104];
  work.d[105] = work.v[105];
  if (work.d[105] > 0)
    work.d[105] = -settings.kkt_reg;
  else
    work.d[105] -= settings.kkt_reg;
  work.d_inv[105] = 1/work.d[105];
#ifndef ZERO_LIBRARY_MODE
  if (settings.debug) {
    printf("Squared Frobenius for factorization is %.8g.\n", check_factorization());
  }
#endif
}
double Gensolver::check_factorization(void) {
  /* Returns the squared Frobenius norm of A - L*D*L'. */
  double temp, residual;
  /* Only check the lower triangle. */
  residual = 0;
  temp = work.KKT[107]-1*work.d[104]*1-work.L[1]*work.d[103]*work.L[1];
  residual += temp*temp;
  temp = work.KKT[0]-1*work.d[0]*1;
  residual += temp*temp;
  temp = work.KKT[1]-1*work.d[1]*1;
  residual += temp*temp;
  temp = work.KKT[2]-1*work.d[2]*1;
  residual += temp*temp;
  temp = work.KKT[3]-1*work.d[3]*1;
  residual += temp*temp;
  temp = work.KKT[4]-1*work.d[4]*1;
  residual += temp*temp;
  temp = work.KKT[5]-1*work.d[5]*1;
  residual += temp*temp;
  temp = work.KKT[6]-1*work.d[6]*1;
  residual += temp*temp;
  temp = work.KKT[7]-1*work.d[7]*1;
  residual += temp*temp;
  temp = work.KKT[8]-1*work.d[8]*1;
  residual += temp*temp;
  temp = work.KKT[9]-1*work.d[9]*1;
  residual += temp*temp;
  temp = work.KKT[10]-1*work.d[10]*1;
  residual += temp*temp;
  temp = work.KKT[11]-1*work.d[11]*1;
  residual += temp*temp;
  temp = work.KKT[12]-1*work.d[12]*1;
  residual += temp*temp;
  temp = work.KKT[13]-1*work.d[13]*1;
  residual += temp*temp;
  temp = work.KKT[14]-1*work.d[14]*1;
  residual += temp*temp;
  temp = work.KKT[15]-1*work.d[15]*1;
  residual += temp*temp;
  temp = work.KKT[16]-1*work.d[16]*1;
  residual += temp*temp;
  temp = work.KKT[17]-1*work.d[17]*1;
  residual += temp*temp;
  temp = work.KKT[18]-1*work.d[18]*1;
  residual += temp*temp;
  temp = work.KKT[19]-1*work.d[19]*1;
  residual += temp*temp;
  temp = work.KKT[20]-1*work.d[20]*1;
  residual += temp*temp;
  temp = work.KKT[21]-1*work.d[21]*1;
  residual += temp*temp;
  temp = work.KKT[22]-1*work.d[22]*1;
  residual += temp*temp;
  temp = work.KKT[23]-1*work.d[23]*1;
  residual += temp*temp;
  temp = work.KKT[24]-1*work.d[24]*1;
  residual += temp*temp;
  temp = work.KKT[25]-1*work.d[25]*1;
  residual += temp*temp;
  temp = work.KKT[26]-1*work.d[26]*1;
  residual += temp*temp;
  temp = work.KKT[27]-1*work.d[27]*1;
  residual += temp*temp;
  temp = work.KKT[28]-1*work.d[28]*1;
  residual += temp*temp;
  temp = work.KKT[29]-1*work.d[29]*1;
  residual += temp*temp;
  temp = work.KKT[30]-1*work.d[30]*1;
  residual += temp*temp;
  temp = work.KKT[31]-1*work.d[31]*1;
  residual += temp*temp;
  temp = work.KKT[32]-1*work.d[32]*1;
  residual += temp*temp;
  temp = work.KKT[33]-1*work.d[33]*1;
  residual += temp*temp;
  temp = work.KKT[34]-1*work.d[34]*1;
  residual += temp*temp;
  temp = work.KKT[35]-1*work.d[35]*1;
  residual += temp*temp;
  temp = work.KKT[36]-1*work.d[36]*1;
  residual += temp*temp;
  temp = work.KKT[37]-1*work.d[37]*1;
  residual += temp*temp;
  temp = work.KKT[38]-1*work.d[38]*1;
  residual += temp*temp;
  temp = work.KKT[39]-1*work.d[39]*1;
  residual += temp*temp;
  temp = work.KKT[40]-1*work.d[40]*1;
  residual += temp*temp;
  temp = work.KKT[41]-1*work.d[41]*1;
  residual += temp*temp;
  temp = work.KKT[42]-1*work.d[42]*1;
  residual += temp*temp;
  temp = work.KKT[43]-1*work.d[43]*1;
  residual += temp*temp;
  temp = work.KKT[44]-1*work.d[44]*1;
  residual += temp*temp;
  temp = work.KKT[45]-1*work.d[45]*1;
  residual += temp*temp;
  temp = work.KKT[46]-1*work.d[46]*1;
  residual += temp*temp;
  temp = work.KKT[47]-1*work.d[47]*1;
  residual += temp*temp;
  temp = work.KKT[48]-1*work.d[48]*1;
  residual += temp*temp;
  temp = work.KKT[49]-1*work.d[49]*1;
  residual += temp*temp;
  temp = work.KKT[50]-1*work.d[50]*1;
  residual += temp*temp;
  temp = work.KKT[51]-1*work.d[51]*1;
  residual += temp*temp;
  temp = work.KKT[52]-1*work.d[52]*1;
  residual += temp*temp;
  temp = work.KKT[53]-1*work.d[53]*1;
  residual += temp*temp;
  temp = work.KKT[54]-1*work.d[54]*1;
  residual += temp*temp;
  temp = work.KKT[55]-1*work.d[55]*1;
  residual += temp*temp;
  temp = work.KKT[56]-1*work.d[56]*1;
  residual += temp*temp;
  temp = work.KKT[57]-1*work.d[57]*1;
  residual += temp*temp;
  temp = work.KKT[58]-1*work.d[58]*1;
  residual += temp*temp;
  temp = work.KKT[59]-1*work.d[59]*1;
  residual += temp*temp;
  temp = work.KKT[60]-1*work.d[60]*1;
  residual += temp*temp;
  temp = work.KKT[61]-1*work.d[61]*1;
  residual += temp*temp;
  temp = work.KKT[62]-1*work.d[62]*1;
  residual += temp*temp;
  temp = work.KKT[63]-1*work.d[63]*1;
  residual += temp*temp;
  temp = work.KKT[64]-1*work.d[64]*1;
  residual += temp*temp;
  temp = work.KKT[65]-1*work.d[65]*1;
  residual += temp*temp;
  temp = work.KKT[66]-1*work.d[66]*1;
  residual += temp*temp;
  temp = work.KKT[67]-1*work.d[67]*1;
  residual += temp*temp;
  temp = work.KKT[68]-1*work.d[68]*1;
  residual += temp*temp;
  temp = work.KKT[69]-1*work.d[69]*1;
  residual += temp*temp;
  temp = work.KKT[70]-1*work.d[70]*1;
  residual += temp*temp;
  temp = work.KKT[71]-1*work.d[71]*1;
  residual += temp*temp;
  temp = work.KKT[72]-1*work.d[72]*1;
  residual += temp*temp;
  temp = work.KKT[73]-1*work.d[73]*1;
  residual += temp*temp;
  temp = work.KKT[74]-1*work.d[74]*1;
  residual += temp*temp;
  temp = work.KKT[75]-1*work.d[75]*1;
  residual += temp*temp;
  temp = work.KKT[76]-1*work.d[76]*1;
  residual += temp*temp;
  temp = work.KKT[77]-1*work.d[77]*1;
  residual += temp*temp;
  temp = work.KKT[78]-1*work.d[78]*1;
  residual += temp*temp;
  temp = work.KKT[79]-1*work.d[79]*1;
  residual += temp*temp;
  temp = work.KKT[80]-1*work.d[80]*1;
  residual += temp*temp;
  temp = work.KKT[81]-1*work.d[81]*1;
  residual += temp*temp;
  temp = work.KKT[82]-1*work.d[82]*1;
  residual += temp*temp;
  temp = work.KKT[83]-1*work.d[83]*1;
  residual += temp*temp;
  temp = work.KKT[84]-1*work.d[84]*1;
  residual += temp*temp;
  temp = work.KKT[85]-1*work.d[85]*1;
  residual += temp*temp;
  temp = work.KKT[86]-1*work.d[86]*1;
  residual += temp*temp;
  temp = work.KKT[87]-1*work.d[87]*1;
  residual += temp*temp;
  temp = work.KKT[88]-1*work.d[88]*1;
  residual += temp*temp;
  temp = work.KKT[89]-1*work.d[89]*1;
  residual += temp*temp;
  temp = work.KKT[90]-1*work.d[90]*1;
  residual += temp*temp;
  temp = work.KKT[91]-1*work.d[91]*1;
  residual += temp*temp;
  temp = work.KKT[92]-1*work.d[92]*1;
  residual += temp*temp;
  temp = work.KKT[93]-1*work.d[93]*1;
  residual += temp*temp;
  temp = work.KKT[94]-1*work.d[94]*1;
  residual += temp*temp;
  temp = work.KKT[95]-1*work.d[95]*1;
  residual += temp*temp;
  temp = work.KKT[96]-1*work.d[96]*1;
  residual += temp*temp;
  temp = work.KKT[97]-1*work.d[97]*1;
  residual += temp*temp;
  temp = work.KKT[98]-1*work.d[98]*1;
  residual += temp*temp;
  temp = work.KKT[99]-1*work.d[99]*1;
  residual += temp*temp;
  temp = work.KKT[100]-1*work.d[100]*1;
  residual += temp*temp;
  temp = work.KKT[101]-1*work.d[101]*1;
  residual += temp*temp;
  temp = work.KKT[103]-1*work.d[102]*1;
  residual += temp*temp;
  temp = work.KKT[102]-work.L[0]*work.d[101]*1;
  residual += temp*temp;
  temp = work.KKT[104]-work.L[2]*work.d[102]*1;
  residual += temp*temp;
  temp = work.KKT[105]-work.L[0]*work.d[101]*work.L[0]-1*work.d[103]*1;
  residual += temp*temp;
  temp = work.KKT[109]-work.L[2]*work.d[102]*work.L[2]-1*work.d[105]*1-work.L[3]*work.d[104]*work.L[3];
  residual += temp*temp;
  temp = work.KKT[106]-1*work.d[103]*work.L[1];
  residual += temp*temp;
  temp = work.KKT[108]-work.L[3]*work.d[104]*1;
  residual += temp*temp;
  return residual;
}
void Gensolver::matrix_multiply(double *result, double *source) {
  /* Finds result = A*source. */
  result[0] = work.KKT[107]*source[0]+work.KKT[106]*source[104]+work.KKT[108]*source[105];
  result[1] = work.KKT[0]*source[1];
  result[2] = work.KKT[1]*source[2];
  result[3] = work.KKT[2]*source[3];
  result[4] = work.KKT[3]*source[4];
  result[5] = work.KKT[4]*source[5];
  result[6] = work.KKT[5]*source[6];
  result[7] = work.KKT[6]*source[7];
  result[8] = work.KKT[7]*source[8];
  result[9] = work.KKT[8]*source[9];
  result[10] = work.KKT[9]*source[10];
  result[11] = work.KKT[10]*source[11];
  result[12] = work.KKT[11]*source[12];
  result[13] = work.KKT[12]*source[13];
  result[14] = work.KKT[13]*source[14];
  result[15] = work.KKT[14]*source[15];
  result[16] = work.KKT[15]*source[16];
  result[17] = work.KKT[16]*source[17];
  result[18] = work.KKT[17]*source[18];
  result[19] = work.KKT[18]*source[19];
  result[20] = work.KKT[19]*source[20];
  result[21] = work.KKT[20]*source[21];
  result[22] = work.KKT[21]*source[22];
  result[23] = work.KKT[22]*source[23];
  result[24] = work.KKT[23]*source[24];
  result[25] = work.KKT[24]*source[25];
  result[26] = work.KKT[25]*source[26];
  result[27] = work.KKT[26]*source[27];
  result[28] = work.KKT[27]*source[28];
  result[29] = work.KKT[28]*source[29];
  result[30] = work.KKT[29]*source[30];
  result[31] = work.KKT[30]*source[31];
  result[32] = work.KKT[31]*source[32];
  result[33] = work.KKT[32]*source[33];
  result[34] = work.KKT[33]*source[34];
  result[35] = work.KKT[34]*source[35];
  result[36] = work.KKT[35]*source[36];
  result[37] = work.KKT[36]*source[37];
  result[38] = work.KKT[37]*source[38];
  result[39] = work.KKT[38]*source[39];
  result[40] = work.KKT[39]*source[40];
  result[41] = work.KKT[40]*source[41];
  result[42] = work.KKT[41]*source[42];
  result[43] = work.KKT[42]*source[43];
  result[44] = work.KKT[43]*source[44];
  result[45] = work.KKT[44]*source[45];
  result[46] = work.KKT[45]*source[46];
  result[47] = work.KKT[46]*source[47];
  result[48] = work.KKT[47]*source[48];
  result[49] = work.KKT[48]*source[49];
  result[50] = work.KKT[49]*source[50];
  result[51] = work.KKT[50]*source[51];
  result[52] = work.KKT[51]*source[52];
  result[53] = work.KKT[52]*source[53];
  result[54] = work.KKT[53]*source[54];
  result[55] = work.KKT[54]*source[55];
  result[56] = work.KKT[55]*source[56];
  result[57] = work.KKT[56]*source[57];
  result[58] = work.KKT[57]*source[58];
  result[59] = work.KKT[58]*source[59];
  result[60] = work.KKT[59]*source[60];
  result[61] = work.KKT[60]*source[61];
  result[62] = work.KKT[61]*source[62];
  result[63] = work.KKT[62]*source[63];
  result[64] = work.KKT[63]*source[64];
  result[65] = work.KKT[64]*source[65];
  result[66] = work.KKT[65]*source[66];
  result[67] = work.KKT[66]*source[67];
  result[68] = work.KKT[67]*source[68];
  result[69] = work.KKT[68]*source[69];
  result[70] = work.KKT[69]*source[70];
  result[71] = work.KKT[70]*source[71];
  result[72] = work.KKT[71]*source[72];
  result[73] = work.KKT[72]*source[73];
  result[74] = work.KKT[73]*source[74];
  result[75] = work.KKT[74]*source[75];
  result[76] = work.KKT[75]*source[76];
  result[77] = work.KKT[76]*source[77];
  result[78] = work.KKT[77]*source[78];
  result[79] = work.KKT[78]*source[79];
  result[80] = work.KKT[79]*source[80];
  result[81] = work.KKT[80]*source[81];
  result[82] = work.KKT[81]*source[82];
  result[83] = work.KKT[82]*source[83];
  result[84] = work.KKT[83]*source[84];
  result[85] = work.KKT[84]*source[85];
  result[86] = work.KKT[85]*source[86];
  result[87] = work.KKT[86]*source[87];
  result[88] = work.KKT[87]*source[88];
  result[89] = work.KKT[88]*source[89];
  result[90] = work.KKT[89]*source[90];
  result[91] = work.KKT[90]*source[91];
  result[92] = work.KKT[91]*source[92];
  result[93] = work.KKT[92]*source[93];
  result[94] = work.KKT[93]*source[94];
  result[95] = work.KKT[94]*source[95];
  result[96] = work.KKT[95]*source[96];
  result[97] = work.KKT[96]*source[97];
  result[98] = work.KKT[97]*source[98];
  result[99] = work.KKT[98]*source[99];
  result[100] = work.KKT[99]*source[100];
  result[101] = work.KKT[100]*source[101];
  result[102] = work.KKT[101]*source[102]+work.KKT[102]*source[104];
  result[103] = work.KKT[103]*source[103]+work.KKT[104]*source[105];
  result[104] = work.KKT[102]*source[102]+work.KKT[105]*source[104]+work.KKT[106]*source[0];
  result[105] = work.KKT[104]*source[103]+work.KKT[109]*source[105]+work.KKT[108]*source[0];
}
double Gensolver::check_residual(double *target, double *multiplicand) {
  /* Returns the squared 2-norm of lhs - A*rhs. */
  /* Reuses v to find the residual. */
  int i;
  double residual;
  residual = 0;
  matrix_multiply(work.v, multiplicand);
  for (i = 0; i < 102; i++) {
    residual += (target[i] - work.v[i])*(target[i] - work.v[i]);
  }
  return residual;
}
void Gensolver::fill_KKT(void) {
  work.KKT[107] = 2*(params.c2[0]+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848+work.frac_121674190848*params.contNum[0]);
  work.KKT[0] = 2*work.frac_121674190848;
  work.KKT[1] = 2*work.frac_121674190848;
  work.KKT[2] = 2*work.frac_121674190848;
  work.KKT[3] = 2*work.frac_121674190848;
  work.KKT[4] = 2*work.frac_121674190848;
  work.KKT[5] = 2*work.frac_121674190848;
  work.KKT[6] = 2*work.frac_121674190848;
  work.KKT[7] = 2*work.frac_121674190848;
  work.KKT[8] = 2*work.frac_121674190848;
  work.KKT[9] = 2*work.frac_121674190848;
  work.KKT[10] = 2*work.frac_121674190848;
  work.KKT[11] = 2*work.frac_121674190848;
  work.KKT[12] = 2*work.frac_121674190848;
  work.KKT[13] = 2*work.frac_121674190848;
  work.KKT[14] = 2*work.frac_121674190848;
  work.KKT[15] = 2*work.frac_121674190848;
  work.KKT[16] = 2*work.frac_121674190848;
  work.KKT[17] = 2*work.frac_121674190848;
  work.KKT[18] = 2*work.frac_121674190848;
  work.KKT[19] = 2*work.frac_121674190848;
  work.KKT[20] = 2*work.frac_121674190848;
  work.KKT[21] = 2*work.frac_121674190848;
  work.KKT[22] = 2*work.frac_121674190848;
  work.KKT[23] = 2*work.frac_121674190848;
  work.KKT[24] = 2*work.frac_121674190848;
  work.KKT[25] = 2*work.frac_121674190848;
  work.KKT[26] = 2*work.frac_121674190848;
  work.KKT[27] = 2*work.frac_121674190848;
  work.KKT[28] = 2*work.frac_121674190848;
  work.KKT[29] = 2*work.frac_121674190848;
  work.KKT[30] = 2*work.frac_121674190848;
  work.KKT[31] = 2*work.frac_121674190848;
  work.KKT[32] = 2*work.frac_121674190848;
  work.KKT[33] = 2*work.frac_121674190848;
  work.KKT[34] = 2*work.frac_121674190848;
  work.KKT[35] = 2*work.frac_121674190848;
  work.KKT[36] = 2*work.frac_121674190848;
  work.KKT[37] = 2*work.frac_121674190848;
  work.KKT[38] = 2*work.frac_121674190848;
  work.KKT[39] = 2*work.frac_121674190848;
  work.KKT[40] = 2*work.frac_121674190848;
  work.KKT[41] = 2*work.frac_121674190848;
  work.KKT[42] = 2*work.frac_121674190848;
  work.KKT[43] = 2*work.frac_121674190848;
  work.KKT[44] = 2*work.frac_121674190848;
  work.KKT[45] = 2*work.frac_121674190848;
  work.KKT[46] = 2*work.frac_121674190848;
  work.KKT[47] = 2*work.frac_121674190848;
  work.KKT[48] = 2*work.frac_121674190848;
  work.KKT[49] = 2*work.frac_121674190848;
  work.KKT[50] = 2*work.frac_121674190848;
  work.KKT[51] = 2*work.frac_121674190848;
  work.KKT[52] = 2*work.frac_121674190848;
  work.KKT[53] = 2*work.frac_121674190848;
  work.KKT[54] = 2*work.frac_121674190848;
  work.KKT[55] = 2*work.frac_121674190848;
  work.KKT[56] = 2*work.frac_121674190848;
  work.KKT[57] = 2*work.frac_121674190848;
  work.KKT[58] = 2*work.frac_121674190848;
  work.KKT[59] = 2*work.frac_121674190848;
  work.KKT[60] = 2*work.frac_121674190848;
  work.KKT[61] = 2*work.frac_121674190848;
  work.KKT[62] = 2*work.frac_121674190848;
  work.KKT[63] = 2*work.frac_121674190848;
  work.KKT[64] = 2*work.frac_121674190848;
  work.KKT[65] = 2*work.frac_121674190848;
  work.KKT[66] = 2*work.frac_121674190848;
  work.KKT[67] = 2*work.frac_121674190848;
  work.KKT[68] = 2*work.frac_121674190848;
  work.KKT[69] = 2*work.frac_121674190848;
  work.KKT[70] = 2*work.frac_121674190848;
  work.KKT[71] = 2*work.frac_121674190848;
  work.KKT[72] = 2*work.frac_121674190848;
  work.KKT[73] = 2*work.frac_121674190848;
  work.KKT[74] = 2*work.frac_121674190848;
  work.KKT[75] = 2*work.frac_121674190848;
  work.KKT[76] = 2*work.frac_121674190848;
  work.KKT[77] = 2*work.frac_121674190848;
  work.KKT[78] = 2*work.frac_121674190848;
  work.KKT[79] = 2*work.frac_121674190848;
  work.KKT[80] = 2*work.frac_121674190848;
  work.KKT[81] = 2*work.frac_121674190848;
  work.KKT[82] = 2*work.frac_121674190848;
  work.KKT[83] = 2*work.frac_121674190848;
  work.KKT[84] = 2*work.frac_121674190848;
  work.KKT[85] = 2*work.frac_121674190848;
  work.KKT[86] = 2*work.frac_121674190848;
  work.KKT[87] = 2*work.frac_121674190848;
  work.KKT[88] = 2*work.frac_121674190848;
  work.KKT[89] = 2*work.frac_121674190848;
  work.KKT[90] = 2*work.frac_121674190848;
  work.KKT[91] = 2*work.frac_121674190848;
  work.KKT[92] = 2*work.frac_121674190848;
  work.KKT[93] = 2*work.frac_121674190848;
  work.KKT[94] = 2*work.frac_121674190848;
  work.KKT[95] = 2*work.frac_121674190848;
  work.KKT[96] = 2*work.frac_121674190848;
  work.KKT[97] = 2*work.frac_121674190848;
  work.KKT[98] = 2*work.frac_121674190848;
  work.KKT[99] = 2*work.frac_121674190848;
  work.KKT[100] = 2*work.frac_121674190848;
  work.KKT[101] = work.s_inv_z[0];
  work.KKT[103] = work.s_inv_z[1];
  work.KKT[102] = 1;
  work.KKT[104] = 1;
  work.KKT[105] = work.block_33[0];
  work.KKT[109] = work.block_33[0];
  work.KKT[106] = -1;
  work.KKT[108] = 1;
}

