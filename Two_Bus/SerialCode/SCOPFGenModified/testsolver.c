/* Produced by CVXGEN, 2015-03-17 17:44:57 -0400.  */
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
