/* Produced by CVXGEN, 2015-03-30 03:26:02 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: solver.c. */
/* Description: Main solver file. */
#include "solver.h"
double eval_gap(void) {
  int i;
  double gap;
  gap = 0;
  for (i = 0; i < 2; i++)
    gap += work.z[i]*work.s[i];
  return gap;
}
void set_defaults(void) {
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
void setup_pointers(void) {
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
void setup_indexed_params(void) {
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
void setup_indexed_optvars(void) {
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
void setup_indexing(void) {
  setup_pointers();
  setup_indexed_params();
  setup_indexed_optvars();
}
void set_start(void) {
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
double eval_objv(void) {
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
void fillrhs_aff(void) {
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
void fillrhs_cc(void) {
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
void refine(double *target, double *var) {
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
double calc_ineq_resid_squared(void) {
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
double calc_eq_resid_squared(void) {
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
void better_start(void) {
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
void fillrhs_start(void) {
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
long solve(void) {
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
