/* Produced by CVXGEN, 2015-03-30 03:26:07 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: solver.h. */
/* Description: Header file with relevant definitions. */
#ifndef GENSOLVER_H
#define GENSOLVER_H
#include <ctime>
#include <cstdlib>
/* Uncomment the next line to remove all library dependencies. */
/*#define ZERO_LIBRARY_MODE */
#ifdef MATLAB_MEX_FILE
/* Matlab functions. MATLAB_MEX_FILE will be defined by the mex compiler. */
/* If you are not using the mex compiler, this functionality will not intrude, */
/* as it will be completely disabled at compile-time. */
//#include "mex.h"
#else
#ifndef ZERO_LIBRARY_MODE
#include <stdio.h>
#endif
#endif
/* Space must be allocated somewhere (testsolver.c, csolve.c or your own */
/* program) for the global variables vars, params, work and settings. */
/* At the bottom of this file, they are externed. */
#ifndef ZERO_LIBRARY_MODE
#include <math.h>
#define pm(A, m, n) printmatrix(#A, A, m, n, 1)
#endif
using namespace std;
class Gensolver {
private:
typedef struct Params_t {
  int caseNumber;
  double c2[1];
  double c1[1];
  double c0[1];
  double rho[1];
  double Pg_N_init_1[1];
  double Pg_N_avg_1[1];
  double ug_N_1[1];
  double Vg_N_avg_1[1];
  double Thetag_N_avg_1[1];
  double vg_N_1[1];
  double Pg_N_init_2[1];
  double Pg_N_avg_2[1];
  double ug_N_2[1];
  double Vg_N_avg_2[1];
  double Thetag_N_avg_2[1];
  double vg_N_2[1];
  double Pg_N_init_3[1];
  double Pg_N_avg_3[1];
  double ug_N_3[1];
  double Vg_N_avg_3[1];
  double Thetag_N_avg_3[1];
  double vg_N_3[1];
  double Pg_N_init_4[1];
  double Pg_N_avg_4[1];
  double ug_N_4[1];
  double Vg_N_avg_4[1];
  double Thetag_N_avg_4[1];
  double vg_N_4[1];
  double Pg_N_init_5[1];
  double Pg_N_avg_5[1];
  double ug_N_5[1];
  double Vg_N_avg_5[1];
  double Thetag_N_avg_5[1];
  double vg_N_5[1];
  double Pg_N_init_6[1];
  double Pg_N_avg_6[1];
  double ug_N_6[1];
  double Vg_N_avg_6[1];
  double Thetag_N_avg_6[1];
  double vg_N_6[1];
  double Pg_N_init_7[1];
  double Pg_N_avg_7[1];
  double ug_N_7[1];
  double Vg_N_avg_7[1];
  double Thetag_N_avg_7[1];
  double vg_N_7[1];
  double Pg_N_init_8[1];
  double Pg_N_avg_8[1];
  double ug_N_8[1];
  double Vg_N_avg_8[1];
  double Thetag_N_avg_8[1];
  double vg_N_8[1];
  double Pg_N_init_9[1];
  double Pg_N_avg_9[1];
  double ug_N_9[1];
  double Vg_N_avg_9[1];
  double Thetag_N_avg_9[1];
  double vg_N_9[1];
  double Pg_N_init_10[1];
  double Pg_N_avg_10[1];
  double ug_N_10[1];
  double Vg_N_avg_10[1];
  double Thetag_N_avg_10[1];
  double vg_N_10[1];
  double Pg_N_init_11[1];
  double Pg_N_avg_11[1];
  double ug_N_11[1];
  double Vg_N_avg_11[1];
  double Thetag_N_avg_11[1];
  double vg_N_11[1];
  double Pg_N_init_12[1];
  double Pg_N_avg_12[1];
  double ug_N_12[1];
  double Vg_N_avg_12[1];
  double Thetag_N_avg_12[1];
  double vg_N_12[1];
  double Pg_N_init_13[1];
  double Pg_N_avg_13[1];
  double ug_N_13[1];
  double Vg_N_avg_13[1];
  double Thetag_N_avg_13[1];
  double vg_N_13[1];
  double Pg_N_init_14[1];
  double Pg_N_avg_14[1];
  double ug_N_14[1];
  double Vg_N_avg_14[1];
  double Thetag_N_avg_14[1];
  double vg_N_14[1];
  double Pg_N_init_15[1];
  double Pg_N_avg_15[1];
  double ug_N_15[1];
  double Vg_N_avg_15[1];
  double Thetag_N_avg_15[1];
  double vg_N_15[1];
  double Pg_N_init_16[1];
  double Pg_N_avg_16[1];
  double ug_N_16[1];
  double Vg_N_avg_16[1];
  double Thetag_N_avg_16[1];
  double vg_N_16[1];
  double Pg_N_init_17[1];
  double Pg_N_avg_17[1];
  double ug_N_17[1];
  double Vg_N_avg_17[1];
  double Thetag_N_avg_17[1];
  double vg_N_17[1];
  double Pg_N_init_18[1];
  double Pg_N_avg_18[1];
  double ug_N_18[1];
  double Vg_N_avg_18[1];
  double Thetag_N_avg_18[1];
  double vg_N_18[1];
  double Pg_N_init_19[1];
  double Pg_N_avg_19[1];
  double ug_N_19[1];
  double Vg_N_avg_19[1];
  double Thetag_N_avg_19[1];
  double vg_N_19[1];
  double Pg_N_init_20[1];
  double Pg_N_avg_20[1];
  double ug_N_20[1];
  double Vg_N_avg_20[1];
  double Thetag_N_avg_20[1];
  double vg_N_20[1];
  double Pg_N_init_21[1];
  double Pg_N_avg_21[1];
  double ug_N_21[1];
  double Vg_N_avg_21[1];
  double Thetag_N_avg_21[1];
  double vg_N_21[1];
  double Pg_N_init_22[1];
  double Pg_N_avg_22[1];
  double ug_N_22[1];
  double Vg_N_avg_22[1];
  double Thetag_N_avg_22[1];
  double vg_N_22[1];
  double Pg_N_init_23[1];
  double Pg_N_avg_23[1];
  double ug_N_23[1];
  double Vg_N_avg_23[1];
  double Thetag_N_avg_23[1];
  double vg_N_23[1];
  double Pg_N_init_24[1];
  double Pg_N_avg_24[1];
  double ug_N_24[1];
  double Vg_N_avg_24[1];
  double Thetag_N_avg_24[1];
  double vg_N_24[1];
  double Pg_N_init_25[1];
  double Pg_N_avg_25[1];
  double ug_N_25[1];
  double Vg_N_avg_25[1];
  double Thetag_N_avg_25[1];
  double vg_N_25[1];
  double Pg_N_init_26[1];
  double Pg_N_avg_26[1];
  double ug_N_26[1];
  double Vg_N_avg_26[1];
  double Thetag_N_avg_26[1];
  double vg_N_26[1];
  double Pg_N_init_27[1];
  double Pg_N_avg_27[1];
  double ug_N_27[1];
  double Vg_N_avg_27[1];
  double Thetag_N_avg_27[1];
  double vg_N_27[1];
  double Pg_N_init_28[1];
  double Pg_N_avg_28[1];
  double ug_N_28[1];
  double Vg_N_avg_28[1];
  double Thetag_N_avg_28[1];
  double vg_N_28[1];
  double Pg_N_init_29[1];
  double Pg_N_avg_29[1];
  double ug_N_29[1];
  double Vg_N_avg_29[1];
  double Thetag_N_avg_29[1];
  double vg_N_29[1];
  double Pg_N_init_30[1];
  double Pg_N_avg_30[1];
  double ug_N_30[1];
  double Vg_N_avg_30[1];
  double Thetag_N_avg_30[1];
  double vg_N_30[1];
  double Pg_N_init_31[1];
  double Pg_N_avg_31[1];
  double ug_N_31[1];
  double Vg_N_avg_31[1];
  double Thetag_N_avg_31[1];
  double vg_N_31[1];
  double Pg_N_init_32[1];
  double Pg_N_avg_32[1];
  double ug_N_32[1];
  double Vg_N_avg_32[1];
  double Thetag_N_avg_32[1];
  double vg_N_32[1];
  double Pg_N_init_33[1];
  double Pg_N_avg_33[1];
  double ug_N_33[1];
  double Vg_N_avg_33[1];
  double Thetag_N_avg_33[1];
  double vg_N_33[1];
  double Pg_N_init_34[1];
  double Pg_N_avg_34[1];
  double ug_N_34[1];
  double Vg_N_avg_34[1];
  double Thetag_N_avg_34[1];
  double vg_N_34[1];
  double Pg_N_init_35[1];
  double Pg_N_avg_35[1];
  double ug_N_35[1];
  double Vg_N_avg_35[1];
  double Thetag_N_avg_35[1];
  double vg_N_35[1];
  double Pg_N_init_36[1];
  double Pg_N_avg_36[1];
  double ug_N_36[1];
  double Vg_N_avg_36[1];
  double Thetag_N_avg_36[1];
  double vg_N_36[1];
  double Pg_N_init_37[1];
  double Pg_N_avg_37[1];
  double ug_N_37[1];
  double Vg_N_avg_37[1];
  double Thetag_N_avg_37[1];
  double vg_N_37[1];
  double Pg_N_init_38[1];
  double Pg_N_avg_38[1];
  double ug_N_38[1];
  double Vg_N_avg_38[1];
  double Thetag_N_avg_38[1];
  double vg_N_38[1];
  double Pg_N_init_39[1];
  double Pg_N_avg_39[1];
  double ug_N_39[1];
  double Vg_N_avg_39[1];
  double Thetag_N_avg_39[1];
  double vg_N_39[1];
  double Pg_N_init_40[1];
  double Pg_N_avg_40[1];
  double ug_N_40[1];
  double Vg_N_avg_40[1];
  double Thetag_N_avg_40[1];
  double vg_N_40[1];
  double Pg_N_init_41[1];
  double Pg_N_avg_41[1];
  double ug_N_41[1];
  double Vg_N_avg_41[1];
  double Thetag_N_avg_41[1];
  double vg_N_41[1];
  double Pg_N_init_42[1];
  double Pg_N_avg_42[1];
  double ug_N_42[1];
  double Vg_N_avg_42[1];
  double Thetag_N_avg_42[1];
  double vg_N_42[1];
  double Pg_N_init_43[1];
  double Pg_N_avg_43[1];
  double ug_N_43[1];
  double Vg_N_avg_43[1];
  double Thetag_N_avg_43[1];
  double vg_N_43[1];
  double Pg_N_init_44[1];
  double Pg_N_avg_44[1];
  double ug_N_44[1];
  double Vg_N_avg_44[1];
  double Thetag_N_avg_44[1];
  double vg_N_44[1];
  double Pg_N_init_45[1];
  double Pg_N_avg_45[1];
  double ug_N_45[1];
  double Vg_N_avg_45[1];
  double Thetag_N_avg_45[1];
  double vg_N_45[1];
  double Pg_N_init_46[1];
  double Pg_N_avg_46[1];
  double ug_N_46[1];
  double Vg_N_avg_46[1];
  double Thetag_N_avg_46[1];
  double vg_N_46[1];
  double Pg_N_init_47[1];
  double Pg_N_avg_47[1];
  double ug_N_47[1];
  double Vg_N_avg_47[1];
  double Thetag_N_avg_47[1];
  double vg_N_47[1];
  double Pg_N_init_48[1];
  double Pg_N_avg_48[1];
  double ug_N_48[1];
  double Vg_N_avg_48[1];
  double Thetag_N_avg_48[1];
  double vg_N_48[1];
  double Pg_N_init_49[1];
  double Pg_N_avg_49[1];
  double ug_N_49[1];
  double Vg_N_avg_49[1];
  double Thetag_N_avg_49[1];
  double vg_N_49[1];
  double Pg_N_init_50[1];
  double Pg_N_avg_50[1];
  double ug_N_50[1];
  double Vg_N_avg_50[1];
  double Thetag_N_avg_50[1];
  double vg_N_50[1];
  double Pg_N_init_51[1];
  double Pg_N_avg_51[1];
  double ug_N_51[1];
  double Vg_N_avg_51[1];
  double Thetag_N_avg_51[1];
  double vg_N_51[1];
  double Pg_N_init_52[1];
  double Pg_N_avg_52[1];
  double ug_N_52[1];
  double Vg_N_avg_52[1];
  double Thetag_N_avg_52[1];
  double vg_N_52[1];
  double Pg_N_init_53[1];
  double Pg_N_avg_53[1];
  double ug_N_53[1];
  double Vg_N_avg_53[1];
  double Thetag_N_avg_53[1];
  double vg_N_53[1];
  double Pg_N_init_54[1];
  double Pg_N_avg_54[1];
  double ug_N_54[1];
  double Vg_N_avg_54[1];
  double Thetag_N_avg_54[1];
  double vg_N_54[1];
  double Pg_N_init_55[1];
  double Pg_N_avg_55[1];
  double ug_N_55[1];
  double Vg_N_avg_55[1];
  double Thetag_N_avg_55[1];
  double vg_N_55[1];
  double Pg_N_init_56[1];
  double Pg_N_avg_56[1];
  double ug_N_56[1];
  double Vg_N_avg_56[1];
  double Thetag_N_avg_56[1];
  double vg_N_56[1];
  double Pg_N_init_57[1];
  double Pg_N_avg_57[1];
  double ug_N_57[1];
  double Vg_N_avg_57[1];
  double Thetag_N_avg_57[1];
  double vg_N_57[1];
  double Pg_N_init_58[1];
  double Pg_N_avg_58[1];
  double ug_N_58[1];
  double Vg_N_avg_58[1];
  double Thetag_N_avg_58[1];
  double vg_N_58[1];
  double Pg_N_init_59[1];
  double Pg_N_avg_59[1];
  double ug_N_59[1];
  double Vg_N_avg_59[1];
  double Thetag_N_avg_59[1];
  double vg_N_59[1];
  double Pg_N_init_60[1];
  double Pg_N_avg_60[1];
  double ug_N_60[1];
  double Vg_N_avg_60[1];
  double Thetag_N_avg_60[1];
  double vg_N_60[1];
  double Pg_N_init_61[1];
  double Pg_N_avg_61[1];
  double ug_N_61[1];
  double Vg_N_avg_61[1];
  double Thetag_N_avg_61[1];
  double vg_N_61[1];
  double Pg_N_init_62[1];
  double Pg_N_avg_62[1];
  double ug_N_62[1];
  double Vg_N_avg_62[1];
  double Thetag_N_avg_62[1];
  double vg_N_62[1];
  double Pg_N_init_63[1];
  double Pg_N_avg_63[1];
  double ug_N_63[1];
  double Vg_N_avg_63[1];
  double Thetag_N_avg_63[1];
  double vg_N_63[1];
  double Pg_N_init_64[1];
  double Pg_N_avg_64[1];
  double ug_N_64[1];
  double Vg_N_avg_64[1];
  double Thetag_N_avg_64[1];
  double vg_N_64[1];
  double Pg_N_init_65[1];
  double Pg_N_avg_65[1];
  double ug_N_65[1];
  double Vg_N_avg_65[1];
  double Thetag_N_avg_65[1];
  double vg_N_65[1];
  double Pg_N_init_66[1];
  double Pg_N_avg_66[1];
  double ug_N_66[1];
  double Vg_N_avg_66[1];
  double Thetag_N_avg_66[1];
  double vg_N_66[1];
  double Pg_N_init_67[1];
  double Pg_N_avg_67[1];
  double ug_N_67[1];
  double Vg_N_avg_67[1];
  double Thetag_N_avg_67[1];
  double vg_N_67[1];
  double Pg_N_init_68[1];
  double Pg_N_avg_68[1];
  double ug_N_68[1];
  double Vg_N_avg_68[1];
  double Thetag_N_avg_68[1];
  double vg_N_68[1];
  double Pg_N_init_69[1];
  double Pg_N_avg_69[1];
  double ug_N_69[1];
  double Vg_N_avg_69[1];
  double Thetag_N_avg_69[1];
  double vg_N_69[1];
  double Pg_N_init_70[1];
  double Pg_N_avg_70[1];
  double ug_N_70[1];
  double Vg_N_avg_70[1];
  double Thetag_N_avg_70[1];
  double vg_N_70[1];
  double Pg_N_init_71[1];
  double Pg_N_avg_71[1];
  double ug_N_71[1];
  double Vg_N_avg_71[1];
  double Thetag_N_avg_71[1];
  double vg_N_71[1];
  double Pg_N_init_72[1];
  double Pg_N_avg_72[1];
  double ug_N_72[1];
  double Vg_N_avg_72[1];
  double Thetag_N_avg_72[1];
  double vg_N_72[1];
  double Pg_N_init_73[1];
  double Pg_N_avg_73[1];
  double ug_N_73[1];
  double Vg_N_avg_73[1];
  double Thetag_N_avg_73[1];
  double vg_N_73[1];
  double Pg_N_init_74[1];
  double Pg_N_avg_74[1];
  double ug_N_74[1];
  double Vg_N_avg_74[1];
  double Thetag_N_avg_74[1];
  double vg_N_74[1];
  double Pg_N_init_75[1];
  double Pg_N_avg_75[1];
  double ug_N_75[1];
  double Vg_N_avg_75[1];
  double Thetag_N_avg_75[1];
  double vg_N_75[1];
  double Pg_N_init_76[1];
  double Pg_N_avg_76[1];
  double ug_N_76[1];
  double Vg_N_avg_76[1];
  double Thetag_N_avg_76[1];
  double vg_N_76[1];
  double Pg_N_init_77[1];
  double Pg_N_avg_77[1];
  double ug_N_77[1];
  double Vg_N_avg_77[1];
  double Thetag_N_avg_77[1];
  double vg_N_77[1];
  double Pg_N_init_78[1];
  double Pg_N_avg_78[1];
  double ug_N_78[1];
  double Vg_N_avg_78[1];
  double Thetag_N_avg_78[1];
  double vg_N_78[1];
  double Pg_N_init_79[1];
  double Pg_N_avg_79[1];
  double ug_N_79[1];
  double Vg_N_avg_79[1];
  double Thetag_N_avg_79[1];
  double vg_N_79[1];
  double Pg_N_init_80[1];
  double Pg_N_avg_80[1];
  double ug_N_80[1];
  double Vg_N_avg_80[1];
  double Thetag_N_avg_80[1];
  double vg_N_80[1];
  double Pg_N_init_81[1];
  double Pg_N_avg_81[1];
  double ug_N_81[1];
  double Vg_N_avg_81[1];
  double Thetag_N_avg_81[1];
  double vg_N_81[1];
  double Pg_N_init_82[1];
  double Pg_N_avg_82[1];
  double ug_N_82[1];
  double Vg_N_avg_82[1];
  double Thetag_N_avg_82[1];
  double vg_N_82[1];
  double Pg_N_init_83[1];
  double Pg_N_avg_83[1];
  double ug_N_83[1];
  double Vg_N_avg_83[1];
  double Thetag_N_avg_83[1];
  double vg_N_83[1];
  double Pg_N_init_84[1];
  double Pg_N_avg_84[1];
  double ug_N_84[1];
  double Vg_N_avg_84[1];
  double Thetag_N_avg_84[1];
  double vg_N_84[1];
  double Pg_N_init_85[1];
  double Pg_N_avg_85[1];
  double ug_N_85[1];
  double Vg_N_avg_85[1];
  double Thetag_N_avg_85[1];
  double vg_N_85[1];
  double Pg_N_init_86[1];
  double Pg_N_avg_86[1];
  double ug_N_86[1];
  double Vg_N_avg_86[1];
  double Thetag_N_avg_86[1];
  double vg_N_86[1];
  double Pg_N_init_87[1];
  double Pg_N_avg_87[1];
  double ug_N_87[1];
  double Vg_N_avg_87[1];
  double Thetag_N_avg_87[1];
  double vg_N_87[1];
  double Pg_N_init_88[1];
  double Pg_N_avg_88[1];
  double ug_N_88[1];
  double Vg_N_avg_88[1];
  double Thetag_N_avg_88[1];
  double vg_N_88[1];
  double Pg_N_init_89[1];
  double Pg_N_avg_89[1];
  double ug_N_89[1];
  double Vg_N_avg_89[1];
  double Thetag_N_avg_89[1];
  double vg_N_89[1];
  double Pg_N_init_90[1];
  double Pg_N_avg_90[1];
  double ug_N_90[1];
  double Vg_N_avg_90[1];
  double Thetag_N_avg_90[1];
  double vg_N_90[1];
  double Pg_N_init_91[1];
  double Pg_N_avg_91[1];
  double ug_N_91[1];
  double Vg_N_avg_91[1];
  double Thetag_N_avg_91[1];
  double vg_N_91[1];
  double Pg_N_init_92[1];
  double Pg_N_avg_92[1];
  double ug_N_92[1];
  double Vg_N_avg_92[1];
  double Thetag_N_avg_92[1];
  double vg_N_92[1];
  double Pg_N_init_93[1];
  double Pg_N_avg_93[1];
  double ug_N_93[1];
  double Vg_N_avg_93[1];
  double Thetag_N_avg_93[1];
  double vg_N_93[1];
  double Pg_N_init_94[1];
  double Pg_N_avg_94[1];
  double ug_N_94[1];
  double Vg_N_avg_94[1];
  double Thetag_N_avg_94[1];
  double vg_N_94[1];
  double Pg_N_init_95[1];
  double Pg_N_avg_95[1];
  double ug_N_95[1];
  double Vg_N_avg_95[1];
  double Thetag_N_avg_95[1];
  double vg_N_95[1];
  double Pg_N_init_96[1];
  double Pg_N_avg_96[1];
  double ug_N_96[1];
  double Vg_N_avg_96[1];
  double Thetag_N_avg_96[1];
  double vg_N_96[1];
  double Pg_N_init_97[1];
  double Pg_N_avg_97[1];
  double ug_N_97[1];
  double Vg_N_avg_97[1];
  double Thetag_N_avg_97[1];
  double vg_N_97[1];
  double Pg_N_init_98[1];
  double Pg_N_avg_98[1];
  double ug_N_98[1];
  double Vg_N_avg_98[1];
  double Thetag_N_avg_98[1];
  double vg_N_98[1];
  double Pg_N_init_99[1];
  double Pg_N_avg_99[1];
  double ug_N_99[1];
  double Vg_N_avg_99[1];
  double Thetag_N_avg_99[1];
  double vg_N_99[1];
  double Pg_N_init_100[1];
  double Pg_N_avg_100[1];
  double ug_N_100[1];
  double Vg_N_avg_100[1];
  double Thetag_N_avg_100[1];
  double vg_N_100[1];
  double Pg_N_init_101[1];
  double Pg_N_avg_101[1];
  double ug_N_101[1];
  double Vg_N_avg_101[1];
  double Thetag_N_avg_101[1];
  double vg_N_101[1];
  double contNum[1];
  double PgMin[1];
  double PgMax[1];
  double *Pg_N_init[102];
  double *Pg_N_avg[102];
  double *ug_N[102];
  double *Vg_N_avg[102];
  double *Thetag_N_avg[102];
  double *vg_N[102];
} Params;
typedef struct Vars_t {
  double *Pg; /* 1 rows. */
  double *Thetag_1; /* 1 rows. */
  double *Thetag_2; /* 1 rows. */
  double *Thetag_3; /* 1 rows. */
  double *Thetag_4; /* 1 rows. */
  double *Thetag_5; /* 1 rows. */
  double *Thetag_6; /* 1 rows. */
  double *Thetag_7; /* 1 rows. */
  double *Thetag_8; /* 1 rows. */
  double *Thetag_9; /* 1 rows. */
  double *Thetag_10; /* 1 rows. */
  double *Thetag_11; /* 1 rows. */
  double *Thetag_12; /* 1 rows. */
  double *Thetag_13; /* 1 rows. */
  double *Thetag_14; /* 1 rows. */
  double *Thetag_15; /* 1 rows. */
  double *Thetag_16; /* 1 rows. */
  double *Thetag_17; /* 1 rows. */
  double *Thetag_18; /* 1 rows. */
  double *Thetag_19; /* 1 rows. */
  double *Thetag_20; /* 1 rows. */
  double *Thetag_21; /* 1 rows. */
  double *Thetag_22; /* 1 rows. */
  double *Thetag_23; /* 1 rows. */
  double *Thetag_24; /* 1 rows. */
  double *Thetag_25; /* 1 rows. */
  double *Thetag_26; /* 1 rows. */
  double *Thetag_27; /* 1 rows. */
  double *Thetag_28; /* 1 rows. */
  double *Thetag_29; /* 1 rows. */
  double *Thetag_30; /* 1 rows. */
  double *Thetag_31; /* 1 rows. */
  double *Thetag_32; /* 1 rows. */
  double *Thetag_33; /* 1 rows. */
  double *Thetag_34; /* 1 rows. */
  double *Thetag_35; /* 1 rows. */
  double *Thetag_36; /* 1 rows. */
  double *Thetag_37; /* 1 rows. */
  double *Thetag_38; /* 1 rows. */
  double *Thetag_39; /* 1 rows. */
  double *Thetag_40; /* 1 rows. */
  double *Thetag_41; /* 1 rows. */
  double *Thetag_42; /* 1 rows. */
  double *Thetag_43; /* 1 rows. */
  double *Thetag_44; /* 1 rows. */
  double *Thetag_45; /* 1 rows. */
  double *Thetag_46; /* 1 rows. */
  double *Thetag_47; /* 1 rows. */
  double *Thetag_48; /* 1 rows. */
  double *Thetag_49; /* 1 rows. */
  double *Thetag_50; /* 1 rows. */
  double *Thetag_51; /* 1 rows. */
  double *Thetag_52; /* 1 rows. */
  double *Thetag_53; /* 1 rows. */
  double *Thetag_54; /* 1 rows. */
  double *Thetag_55; /* 1 rows. */
  double *Thetag_56; /* 1 rows. */
  double *Thetag_57; /* 1 rows. */
  double *Thetag_58; /* 1 rows. */
  double *Thetag_59; /* 1 rows. */
  double *Thetag_60; /* 1 rows. */
  double *Thetag_61; /* 1 rows. */
  double *Thetag_62; /* 1 rows. */
  double *Thetag_63; /* 1 rows. */
  double *Thetag_64; /* 1 rows. */
  double *Thetag_65; /* 1 rows. */
  double *Thetag_66; /* 1 rows. */
  double *Thetag_67; /* 1 rows. */
  double *Thetag_68; /* 1 rows. */
  double *Thetag_69; /* 1 rows. */
  double *Thetag_70; /* 1 rows. */
  double *Thetag_71; /* 1 rows. */
  double *Thetag_72; /* 1 rows. */
  double *Thetag_73; /* 1 rows. */
  double *Thetag_74; /* 1 rows. */
  double *Thetag_75; /* 1 rows. */
  double *Thetag_76; /* 1 rows. */
  double *Thetag_77; /* 1 rows. */
  double *Thetag_78; /* 1 rows. */
  double *Thetag_79; /* 1 rows. */
  double *Thetag_80; /* 1 rows. */
  double *Thetag_81; /* 1 rows. */
  double *Thetag_82; /* 1 rows. */
  double *Thetag_83; /* 1 rows. */
  double *Thetag_84; /* 1 rows. */
  double *Thetag_85; /* 1 rows. */
  double *Thetag_86; /* 1 rows. */
  double *Thetag_87; /* 1 rows. */
  double *Thetag_88; /* 1 rows. */
  double *Thetag_89; /* 1 rows. */
  double *Thetag_90; /* 1 rows. */
  double *Thetag_91; /* 1 rows. */
  double *Thetag_92; /* 1 rows. */
  double *Thetag_93; /* 1 rows. */
  double *Thetag_94; /* 1 rows. */
  double *Thetag_95; /* 1 rows. */
  double *Thetag_96; /* 1 rows. */
  double *Thetag_97; /* 1 rows. */
  double *Thetag_98; /* 1 rows. */
  double *Thetag_99; /* 1 rows. */
  double *Thetag_100; /* 1 rows. */
  double *Thetag_101; /* 1 rows. */
  double *Thetag[102];
} Vars;
typedef struct Workspace_t {
  double h[2];
  double s_inv[2];
  double s_inv_z[2];
  double *b;
  double q[102];
  double rhs[106];
  double x[106];
  double *s;
  double *z;
  double *y;
  double lhs_aff[106];
  double lhs_cc[106];
  double buffer[106];
  double buffer2[106];
  double KKT[110];
  double L[4];
  double d[106];
  double v[106];
  double d_inv[106];
  double gap;
  double optval;
  double ineq_resid_squared;
  double eq_resid_squared;
  double block_33[1];
  /* Pre-op symbols. */
  double frac_121674190848;
  double quad_861253439488[1];
  double quad_335606009856[1];
  double quad_419630354432[1];
  double quad_300112478208[1];
  double quad_722335502336[1];
  double quad_863528128512[1];
  double quad_407892983808[1];
  double quad_53514031104[1];
  double quad_198013468672[1];
  double quad_48438943744[1];
  double quad_898365714432[1];
  double quad_934929342464[1];
  double quad_793422544896[1];
  double quad_183681134592[1];
  double quad_924824883200[1];
  double quad_774359400448[1];
  double quad_364793888768[1];
  double quad_831331065856[1];
  double quad_24379666432[1];
  double quad_47350718464[1];
  double quad_418591776768[1];
  double quad_358617378816[1];
  double quad_189427146752[1];
  double quad_811009290240[1];
  double quad_340342550528[1];
  double quad_861425090560[1];
  double quad_522812354560[1];
  double quad_347927187456[1];
  double quad_724215824384[1];
  double quad_488040783872[1];
  double quad_750720192512[1];
  double quad_575932559360[1];
  double quad_497126731776[1];
  double quad_446440656896[1];
  double quad_220748931072[1];
  double quad_576835772416[1];
  double quad_327014187008[1];
  double quad_77213671424[1];
  double quad_634046689280[1];
  double quad_376276512768[1];
  double quad_435014901760[1];
  double quad_194730110976[1];
  double quad_687358853120[1];
  double quad_748989894656[1];
  double quad_190680965120[1];
  double quad_274986213376[1];
  double quad_819154403328[1];
  double quad_211870208000[1];
  double quad_147546587136[1];
  double quad_31183937536[1];
  double quad_28386426880[1];
  double quad_476108271616[1];
  double quad_294418444288[1];
  double quad_169273020416[1];
  double quad_987523264512[1];
  double quad_55176798208[1];
  double quad_526459392000[1];
  double quad_938506014720[1];
  double quad_398236438528[1];
  double quad_408717836288[1];
  double quad_184308461568[1];
  double quad_330616233984[1];
  double quad_411712237568[1];
  double quad_642560991232[1];
  double quad_172000874496[1];
  double quad_877709885440[1];
  double quad_236200529920[1];
  double quad_953866592256[1];
  double quad_608829231104[1];
  double quad_265570734080[1];
  double quad_225263394816[1];
  double quad_434793504768[1];
  double quad_984017977344[1];
  double quad_526619181056[1];
  double quad_566099726336[1];
  double quad_879322742784[1];
  double quad_620654563328[1];
  double quad_485479587840[1];
  double quad_808293044224[1];
  double quad_468686970880[1];
  double quad_563134095360[1];
  double quad_370423967744[1];
  double quad_222369783808[1];
  double quad_83489009664[1];
  double quad_573775224832[1];
  double quad_81818914816[1];
  double quad_869895589888[1];
  double quad_456437583872[1];
  double quad_90734665728[1];
  double quad_165580480512[1];
  double quad_225093988352[1];
  double quad_944332083200[1];
  double quad_198883876864[1];
  double quad_30941691904[1];
  double quad_692068392960[1];
  double quad_404779089920[1];
  double quad_637665005568[1];
  double quad_719521869824[1];
  double quad_480708186112[1];
  double quad_109914923008[1];
  double quad_101608513536[1];
  double quad_199411765248[1];
  double quad_901289631744[1];
  double quad_594054291456[1];
  double quad_404078174208[1];
  double quad_244563038208[1];
  double quad_338757373952[1];
  double quad_655083196416[1];
  double quad_489744039936[1];
  double quad_259549028352[1];
  double quad_250154500096[1];
  double quad_283916939264[1];
  double quad_504322719744[1];
  double quad_996765118464[1];
  double quad_483569917952[1];
  double quad_158537359360[1];
  double quad_626608463872[1];
  double quad_927129829376[1];
  double quad_790822236160[1];
  double quad_918575378432[1];
  double quad_995595960320[1];
  double quad_529630486528[1];
  double quad_79251795968[1];
  double quad_475943071744[1];
  double quad_146468945920[1];
  double quad_86002155520[1];
  double quad_351835660288[1];
  double quad_898473287680[1];
  double quad_715947200512[1];
  double quad_824253415424[1];
  double quad_494006571008[1];
  double quad_185061429248[1];
  double quad_796629155840[1];
  double quad_449770254336[1];
  double quad_947342782464[1];
  double quad_604877107200[1];
  double quad_680640479232[1];
  double quad_9457143808[1];
  double quad_717531140096[1];
  double quad_634949398528[1];
  double quad_564056838144[1];
  double quad_946810548224[1];
  double quad_70571728896[1];
  double quad_286652420096[1];
  double quad_173991247872[1];
  double quad_474489081856[1];
  double quad_880120451072[1];
  double quad_782250987520[1];
  double quad_57536741376[1];
  double quad_849656963072[1];
  double quad_35205603328[1];
  double quad_658468995072[1];
  double quad_356423053312[1];
  double quad_283962642432[1];
  double quad_547807477760[1];
  double quad_382444605440[1];
  double quad_539754852352[1];
  double quad_230561599488[1];
  double quad_865930481664[1];
  double quad_541608677376[1];
  double quad_125357936640[1];
  double quad_619719733248[1];
  double quad_824211386368[1];
  double quad_394753474560[1];
  double quad_547133394944[1];
  double quad_209782870016[1];
  double quad_381733597184[1];
  double quad_152716124160[1];
  double quad_128809979904[1];
  double quad_335236542464[1];
  double quad_909988339712[1];
  double quad_852921757696[1];
  double quad_787442696192[1];
  double quad_961277771776[1];
  double quad_939277180928[1];
  double quad_429044678656[1];
  double quad_861783474176[1];
  double quad_340061249536[1];
  double quad_279979859968[1];
  double quad_869539332096[1];
  double quad_539265785856[1];
  double quad_872875143168[1];
  double quad_940092141568[1];
  double quad_320369504256[1];
  double quad_814284275712[1];
  double quad_850341859328[1];
  double quad_668125876224[1];
  double quad_768845512704[1];
  double quad_180052918272[1];
  double quad_637222821888[1];
  double quad_117911429120[1];
  double quad_793053450240[1];
  double quad_161320878080[1];
  double quad_502933229568[1];
  double quad_890543960064[1];
  double quad_620316852224[1];
  double quad_682189721600[1];
  double quad_367930048512[1];
  double quad_515601072128[1];
  double quad_600421740544[1];
  double quad_657550438400[1];
  double quad_478485061632[1];
  int converged;
} Workspace;
typedef struct Settings_t {
  double resid_tol;
  double eps;
  int max_iters;
  int refine_steps;
  int better_start;
  /* Better start obviates the need for s_init and z_init. */
  double s_init;
  double z_init;
  int verbose;
  /* Show extra details of the iterative refinement steps. */
  int verbose_refinement;
  int debug;
  /* For regularization. Minimum value of abs(D_ii) in the kkt D factor. */
  double kkt_reg;
} Settings;
Vars vars;
Params params;
Workspace work;
Settings settings;
long global_seed;
clock_t tic_timestart;
double *Piterate;
double *Thiterate;
public:
Gensolver( double, double, double, double, double, int ); // Gensolver object constructor
~Gensolver(); // Gensolver object destructor
/* Function definitions in ldl.c: */
void ldl_solve(double *target, double *var);
void ldl_factor(void);
double check_factorization(void);
void matrix_multiply(double *result, double *source);
double check_residual(double *target, double *multiplicand);
void fill_KKT(void);

/* Function definitions in matrix_support.c: */
void multbymA(double *lhs, double *rhs);
void multbymAT(double *lhs, double *rhs);
void multbymG(double *lhs, double *rhs);
void multbymGT(double *lhs, double *rhs);
void multbyP(double *lhs, double *rhs);
void fillq(void);
void fillh(void);
void fillb(void);
void pre_ops(void);

/* Function definitions in solver.c: */
double eval_gap(void);
void set_defaults(void);
void setup_pointers(void);
void setup_indexed_params(void);
void setup_indexed_optvars(void);
void setup_indexing(void);
void set_start(void);
double eval_objv(void);
void fillrhs_aff(void);
void fillrhs_cc(void);
void refine(double *target, double *var);
double calc_ineq_resid_squared(void);
double calc_eq_resid_squared(void);
void better_start(void);
void fillrhs_start(void);
long solve(void);

/* Function definitions in testsolver.c: */
void mainsolve(double, double, double, double, double, double, double);
void load_default_data(double, double, double, double, double, double, double);
double getPSol(void);
double getThetaSol(void);
double getObj(void);

/* Function definitions in util.c: */
void tic(void);
float toc(void);
float tocq(void);
void printmatrix(char *name, double *A, int m, int n, int sparse);
double unif(double lower, double upper);
float ran1(long*idum, int reset);
float randn_internal(long *idum, int reset);
double randn(void);
void reset_rand(void);
};

#endif
