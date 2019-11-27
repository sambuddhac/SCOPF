/* Produced by CVXGEN, 2015-09-15 19:23:45 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: csolve.c. */
/* Description: mex-able file for running cvxgen solver. */
#include "mex.h"
#include "solver.h"
Vars vars;
Params params;
Workspace work;
Settings settings;
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  int i, j;
  mxArray *xm, *cell, *xm_cell;
  double *src;
  double *dest;
  double *dest_cell;
  int valid_vars;
  int steps;
  int this_var_errors;
  int warned_diags;
  int prepare_for_c = 0;
  int extra_solves;
  const char *status_names[] = {"optval", "gap", "steps", "converged"};
  mwSize dims1x1of1[1] = {1};
  mwSize dims[1];
  const char *var_names[] = {"Pg", "Thetag_1", "Thetag_2", "Thetag_3", "Thetag_4", "Thetag_5", "Thetag_6", "Thetag_7", "Thetag_8", "Thetag_9", "Thetag_10", "Thetag_11", "Thetag_12", "Thetag_13", "Thetag_14", "Thetag_15", "Thetag_16", "Thetag_17", "Thetag_18", "Thetag_19", "Thetag_20", "Thetag_21", "Thetag_22", "Thetag_23", "Thetag_24", "Thetag_25", "Thetag_26", "Thetag_27", "Thetag_28", "Thetag_29", "Thetag_30", "Thetag_31", "Thetag_32", "Thetag_33", "Thetag_34", "Thetag_35", "Thetag_36", "Thetag_37", "Thetag_38", "Thetag_39", "Thetag_40", "Thetag_41", "Thetag_42", "Thetag_43", "Thetag_44", "Thetag_45", "Thetag_46", "Thetag_47", "Thetag_48", "Thetag_49", "Thetag_50", "Thetag_51", "Thetag_52", "Thetag_53", "Thetag_54", "Thetag_55", "Thetag_56", "Thetag_57", "Thetag_58", "Thetag_59", "Thetag_60", "Thetag_61", "Thetag_62", "Thetag_63", "Thetag_64", "Thetag_65", "Thetag_66", "Thetag_67", "Thetag_68", "Thetag_69", "Thetag_70", "Thetag_71", "Thetag_72", "Thetag_73", "Thetag_74", "Thetag_75", "Thetag_76", "Thetag_77", "Thetag_78", "Thetag_79", "Thetag_80", "Thetag_81", "Thetag_82", "Thetag_83", "Thetag_84", "Thetag_85", "Thetag_86", "Thetag_87", "Thetag_88", "Thetag_89", "Thetag_90", "Thetag_91", "Thetag_92", "Thetag_93", "Thetag_94", "Thetag_95", "Thetag_96", "Thetag_97", "Thetag_98", "Thetag_99", "Thetag_100", "Thetag_101", "Thetag"};
  const int num_var_names = 103;
  /* Avoid compiler warnings of unused variables by using a dummy assignment. */
  warned_diags = j = 0;
  extra_solves = 0;
  set_defaults();
  /* Check we got the right number of arguments. */
  if (nrhs == 0)
    mexErrMsgTxt("Not enough arguments: You need to specify at least the parameters.\n");
  if (nrhs > 1) {
    /* Assume that the second argument is the settings. */
    if (mxGetField(prhs[1], 0, "eps") != NULL)
      settings.eps = *mxGetPr(mxGetField(prhs[1], 0, "eps"));
    if (mxGetField(prhs[1], 0, "max_iters") != NULL)
      settings.max_iters = *mxGetPr(mxGetField(prhs[1], 0, "max_iters"));
    if (mxGetField(prhs[1], 0, "refine_steps") != NULL)
      settings.refine_steps = *mxGetPr(mxGetField(prhs[1], 0, "refine_steps"));
    if (mxGetField(prhs[1], 0, "verbose") != NULL)
      settings.verbose = *mxGetPr(mxGetField(prhs[1], 0, "verbose"));
    if (mxGetField(prhs[1], 0, "better_start") != NULL)
      settings.better_start = *mxGetPr(mxGetField(prhs[1], 0, "better_start"));
    if (mxGetField(prhs[1], 0, "verbose_refinement") != NULL)
      settings.verbose_refinement = *mxGetPr(mxGetField(prhs[1], 0,
            "verbose_refinement"));
    if (mxGetField(prhs[1], 0, "debug") != NULL)
      settings.debug = *mxGetPr(mxGetField(prhs[1], 0, "debug"));
    if (mxGetField(prhs[1], 0, "kkt_reg") != NULL)
      settings.kkt_reg = *mxGetPr(mxGetField(prhs[1], 0, "kkt_reg"));
    if (mxGetField(prhs[1], 0, "s_init") != NULL)
      settings.s_init = *mxGetPr(mxGetField(prhs[1], 0, "s_init"));
    if (mxGetField(prhs[1], 0, "z_init") != NULL)
      settings.z_init = *mxGetPr(mxGetField(prhs[1], 0, "z_init"));
    if (mxGetField(prhs[1], 0, "resid_tol") != NULL)
      settings.resid_tol = *mxGetPr(mxGetField(prhs[1], 0, "resid_tol"));
    if (mxGetField(prhs[1], 0, "extra_solves") != NULL)
      extra_solves = *mxGetPr(mxGetField(prhs[1], 0, "extra_solves"));
    else
      extra_solves = 0;
    if (mxGetField(prhs[1], 0, "prepare_for_c") != NULL)
      prepare_for_c = *mxGetPr(mxGetField(prhs[1], 0, "prepare_for_c"));
  }
  valid_vars = 0;
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "PgMax");
  if (xm == NULL) {
    printf("could not find params.PgMax.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("PgMax must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter PgMax must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter PgMax must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter PgMax must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.PgMax;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "PgMin");
  if (xm == NULL) {
    printf("could not find params.PgMin.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("PgMin must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter PgMin must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter PgMin must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter PgMin must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.PgMin;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_1");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_1 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 0);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_1 or params.Pg_N_avg{1}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_1 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_1 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_1 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_1 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_1;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_2");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_2 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 1);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_2 or params.Pg_N_avg{2}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_2 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_2 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_2 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_2 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_2;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_3");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_3 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 2);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_3 or params.Pg_N_avg{3}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_3 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_3 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_3 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_3 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_3;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_4");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_4 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 3);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_4 or params.Pg_N_avg{4}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_4 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_4 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_4 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_4 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_4;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_5");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_5 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 4);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_5 or params.Pg_N_avg{5}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_5 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_5 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_5 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_5 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_5;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_6");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_6 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 5);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_6 or params.Pg_N_avg{6}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_6 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_6 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_6 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_6 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_6;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_7");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_7 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 6);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_7 or params.Pg_N_avg{7}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_7 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_7 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_7 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_7 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_7;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_8");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_8 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 7);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_8 or params.Pg_N_avg{8}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_8 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_8 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_8 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_8 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_8;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_9");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_9 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 8);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_9 or params.Pg_N_avg{9}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_9 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_9 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_9 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_9 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_9;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_10");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_10 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 9);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_10 or params.Pg_N_avg{10}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_10 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_10 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_10 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_10 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_10;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_11");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_11 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 10);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_11 or params.Pg_N_avg{11}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_11 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_11 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_11 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_11 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_11;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_12");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_12 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 11);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_12 or params.Pg_N_avg{12}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_12 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_12 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_12 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_12 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_12;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_13");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_13 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 12);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_13 or params.Pg_N_avg{13}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_13 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_13 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_13 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_13 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_13;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_14");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_14 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 13);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_14 or params.Pg_N_avg{14}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_14 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_14 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_14 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_14 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_14;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_15");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_15 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 14);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_15 or params.Pg_N_avg{15}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_15 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_15 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_15 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_15 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_15;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_16");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_16 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 15);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_16 or params.Pg_N_avg{16}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_16 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_16 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_16 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_16 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_16;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_17");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_17 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 16);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_17 or params.Pg_N_avg{17}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_17 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_17 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_17 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_17 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_17;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_18");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_18 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 17);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_18 or params.Pg_N_avg{18}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_18 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_18 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_18 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_18 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_18;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_19");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_19 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 18);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_19 or params.Pg_N_avg{19}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_19 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_19 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_19 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_19 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_19;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_20");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_20 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 19);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_20 or params.Pg_N_avg{20}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_20 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_20 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_20 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_20 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_20;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_21");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_21 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 20);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_21 or params.Pg_N_avg{21}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_21 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_21 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_21 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_21 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_21;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_22");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_22 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 21);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_22 or params.Pg_N_avg{22}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_22 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_22 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_22 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_22 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_22;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_23");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_23 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 22);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_23 or params.Pg_N_avg{23}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_23 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_23 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_23 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_23 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_23;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_24");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_24 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 23);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_24 or params.Pg_N_avg{24}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_24 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_24 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_24 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_24 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_24;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_25");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_25 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 24);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_25 or params.Pg_N_avg{25}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_25 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_25 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_25 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_25 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_25;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_26");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_26 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 25);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_26 or params.Pg_N_avg{26}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_26 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_26 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_26 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_26 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_26;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_27");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_27 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 26);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_27 or params.Pg_N_avg{27}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_27 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_27 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_27 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_27 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_27;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_28");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_28 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 27);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_28 or params.Pg_N_avg{28}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_28 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_28 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_28 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_28 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_28;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_29");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_29 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 28);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_29 or params.Pg_N_avg{29}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_29 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_29 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_29 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_29 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_29;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_30");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_30 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 29);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_30 or params.Pg_N_avg{30}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_30 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_30 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_30 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_30 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_30;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_31");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_31 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 30);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_31 or params.Pg_N_avg{31}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_31 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_31 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_31 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_31 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_31;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_32");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_32 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 31);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_32 or params.Pg_N_avg{32}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_32 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_32 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_32 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_32 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_32;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_33");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_33 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 32);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_33 or params.Pg_N_avg{33}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_33 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_33 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_33 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_33 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_33;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_34");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_34 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 33);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_34 or params.Pg_N_avg{34}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_34 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_34 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_34 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_34 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_34;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_35");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_35 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 34);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_35 or params.Pg_N_avg{35}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_35 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_35 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_35 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_35 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_35;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_36");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_36 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 35);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_36 or params.Pg_N_avg{36}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_36 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_36 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_36 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_36 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_36;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_37");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_37 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 36);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_37 or params.Pg_N_avg{37}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_37 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_37 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_37 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_37 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_37;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_38");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_38 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 37);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_38 or params.Pg_N_avg{38}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_38 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_38 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_38 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_38 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_38;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_39");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_39 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 38);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_39 or params.Pg_N_avg{39}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_39 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_39 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_39 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_39 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_39;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_40");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_40 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 39);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_40 or params.Pg_N_avg{40}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_40 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_40 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_40 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_40 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_40;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_41");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_41 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 40);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_41 or params.Pg_N_avg{41}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_41 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_41 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_41 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_41 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_41;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_42");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_42 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 41);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_42 or params.Pg_N_avg{42}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_42 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_42 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_42 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_42 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_42;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_43");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_43 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 42);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_43 or params.Pg_N_avg{43}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_43 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_43 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_43 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_43 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_43;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_44");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_44 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 43);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_44 or params.Pg_N_avg{44}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_44 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_44 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_44 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_44 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_44;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_45");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_45 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 44);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_45 or params.Pg_N_avg{45}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_45 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_45 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_45 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_45 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_45;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_46");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_46 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 45);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_46 or params.Pg_N_avg{46}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_46 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_46 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_46 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_46 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_46;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_47");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_47 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 46);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_47 or params.Pg_N_avg{47}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_47 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_47 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_47 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_47 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_47;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_48");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_48 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 47);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_48 or params.Pg_N_avg{48}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_48 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_48 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_48 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_48 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_48;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_49");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_49 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 48);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_49 or params.Pg_N_avg{49}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_49 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_49 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_49 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_49 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_49;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_50");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_50 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 49);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_50 or params.Pg_N_avg{50}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_50 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_50 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_50 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_50 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_50;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_51");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_51 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 50);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_51 or params.Pg_N_avg{51}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_51 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_51 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_51 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_51 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_51;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_52");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_52 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 51);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_52 or params.Pg_N_avg{52}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_52 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_52 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_52 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_52 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_52;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_53");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_53 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 52);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_53 or params.Pg_N_avg{53}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_53 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_53 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_53 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_53 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_53;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_54");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_54 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 53);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_54 or params.Pg_N_avg{54}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_54 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_54 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_54 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_54 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_54;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_55");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_55 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 54);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_55 or params.Pg_N_avg{55}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_55 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_55 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_55 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_55 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_55;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_56");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_56 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 55);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_56 or params.Pg_N_avg{56}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_56 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_56 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_56 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_56 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_56;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_57");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_57 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 56);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_57 or params.Pg_N_avg{57}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_57 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_57 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_57 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_57 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_57;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_58");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_58 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 57);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_58 or params.Pg_N_avg{58}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_58 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_58 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_58 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_58 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_58;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_59");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_59 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 58);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_59 or params.Pg_N_avg{59}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_59 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_59 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_59 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_59 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_59;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_60");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_60 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 59);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_60 or params.Pg_N_avg{60}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_60 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_60 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_60 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_60 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_60;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_61");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_61 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 60);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_61 or params.Pg_N_avg{61}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_61 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_61 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_61 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_61 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_61;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_62");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_62 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 61);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_62 or params.Pg_N_avg{62}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_62 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_62 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_62 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_62 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_62;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_63");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_63 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 62);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_63 or params.Pg_N_avg{63}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_63 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_63 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_63 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_63 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_63;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_64");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_64 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 63);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_64 or params.Pg_N_avg{64}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_64 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_64 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_64 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_64 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_64;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_65");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_65 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 64);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_65 or params.Pg_N_avg{65}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_65 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_65 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_65 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_65 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_65;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_66");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_66 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 65);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_66 or params.Pg_N_avg{66}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_66 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_66 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_66 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_66 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_66;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_67");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_67 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 66);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_67 or params.Pg_N_avg{67}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_67 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_67 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_67 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_67 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_67;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_68");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_68 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 67);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_68 or params.Pg_N_avg{68}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_68 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_68 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_68 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_68 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_68;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_69");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_69 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 68);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_69 or params.Pg_N_avg{69}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_69 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_69 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_69 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_69 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_69;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_70");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_70 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 69);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_70 or params.Pg_N_avg{70}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_70 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_70 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_70 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_70 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_70;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_71");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_71 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 70);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_71 or params.Pg_N_avg{71}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_71 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_71 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_71 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_71 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_71;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_72");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_72 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 71);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_72 or params.Pg_N_avg{72}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_72 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_72 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_72 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_72 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_72;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_73");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_73 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 72);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_73 or params.Pg_N_avg{73}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_73 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_73 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_73 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_73 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_73;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_74");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_74 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 73);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_74 or params.Pg_N_avg{74}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_74 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_74 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_74 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_74 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_74;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_75");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_75 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 74);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_75 or params.Pg_N_avg{75}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_75 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_75 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_75 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_75 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_75;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_76");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_76 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 75);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_76 or params.Pg_N_avg{76}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_76 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_76 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_76 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_76 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_76;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_77");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_77 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 76);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_77 or params.Pg_N_avg{77}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_77 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_77 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_77 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_77 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_77;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_78");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_78 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 77);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_78 or params.Pg_N_avg{78}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_78 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_78 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_78 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_78 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_78;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_79");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_79 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 78);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_79 or params.Pg_N_avg{79}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_79 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_79 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_79 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_79 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_79;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_80");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_80 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 79);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_80 or params.Pg_N_avg{80}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_80 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_80 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_80 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_80 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_80;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_81");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_81 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 80);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_81 or params.Pg_N_avg{81}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_81 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_81 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_81 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_81 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_81;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_82");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_82 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 81);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_82 or params.Pg_N_avg{82}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_82 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_82 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_82 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_82 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_82;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_83");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_83 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 82);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_83 or params.Pg_N_avg{83}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_83 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_83 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_83 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_83 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_83;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_84");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_84 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 83);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_84 or params.Pg_N_avg{84}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_84 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_84 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_84 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_84 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_84;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_85");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_85 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 84);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_85 or params.Pg_N_avg{85}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_85 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_85 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_85 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_85 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_85;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_86");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_86 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 85);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_86 or params.Pg_N_avg{86}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_86 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_86 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_86 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_86 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_86;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_87");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_87 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 86);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_87 or params.Pg_N_avg{87}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_87 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_87 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_87 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_87 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_87;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_88");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_88 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 87);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_88 or params.Pg_N_avg{88}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_88 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_88 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_88 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_88 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_88;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_89");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_89 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 88);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_89 or params.Pg_N_avg{89}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_89 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_89 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_89 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_89 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_89;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_90");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_90 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 89);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_90 or params.Pg_N_avg{90}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_90 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_90 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_90 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_90 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_90;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_91");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_91 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 90);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_91 or params.Pg_N_avg{91}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_91 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_91 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_91 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_91 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_91;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_92");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_92 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 91);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_92 or params.Pg_N_avg{92}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_92 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_92 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_92 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_92 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_92;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_93");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_93 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 92);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_93 or params.Pg_N_avg{93}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_93 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_93 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_93 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_93 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_93;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_94");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_94 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 93);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_94 or params.Pg_N_avg{94}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_94 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_94 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_94 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_94 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_94;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_95");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_95 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 94);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_95 or params.Pg_N_avg{95}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_95 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_95 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_95 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_95 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_95;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_96");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_96 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 95);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_96 or params.Pg_N_avg{96}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_96 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_96 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_96 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_96 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_96;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_97");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_97 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 96);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_97 or params.Pg_N_avg{97}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_97 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_97 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_97 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_97 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_97;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_98");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_98 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 97);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_98 or params.Pg_N_avg{98}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_98 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_98 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_98 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_98 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_98;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_99");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_99 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 98);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_99 or params.Pg_N_avg{99}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_99 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_99 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_99 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_99 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_99;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_100");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_100 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 99);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_100 or params.Pg_N_avg{100}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_100 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_100 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_100 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_100 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_100;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_avg_101");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_avg_101 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 100);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_avg_101 or params.Pg_N_avg{101}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_avg_101 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_avg_101 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_avg_101 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_avg_101 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_avg_101;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_1");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_1 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 0);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_1 or params.Pg_N_init{1}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_1 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_1 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_1 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_1 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_1;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_2");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_2 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 1);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_2 or params.Pg_N_init{2}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_2 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_2 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_2 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_2 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_2;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_3");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_3 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 2);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_3 or params.Pg_N_init{3}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_3 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_3 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_3 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_3 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_3;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_4");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_4 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 3);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_4 or params.Pg_N_init{4}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_4 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_4 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_4 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_4 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_4;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_5");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_5 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 4);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_5 or params.Pg_N_init{5}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_5 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_5 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_5 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_5 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_5;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_6");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_6 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 5);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_6 or params.Pg_N_init{6}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_6 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_6 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_6 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_6 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_6;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_7");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_7 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 6);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_7 or params.Pg_N_init{7}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_7 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_7 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_7 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_7 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_7;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_8");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_8 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 7);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_8 or params.Pg_N_init{8}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_8 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_8 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_8 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_8 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_8;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_9");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_9 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 8);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_9 or params.Pg_N_init{9}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_9 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_9 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_9 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_9 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_9;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_10");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_10 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 9);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_10 or params.Pg_N_init{10}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_10 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_10 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_10 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_10 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_10;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_11");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_11 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 10);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_11 or params.Pg_N_init{11}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_11 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_11 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_11 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_11 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_11;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_12");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_12 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 11);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_12 or params.Pg_N_init{12}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_12 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_12 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_12 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_12 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_12;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_13");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_13 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 12);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_13 or params.Pg_N_init{13}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_13 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_13 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_13 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_13 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_13;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_14");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_14 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 13);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_14 or params.Pg_N_init{14}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_14 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_14 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_14 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_14 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_14;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_15");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_15 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 14);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_15 or params.Pg_N_init{15}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_15 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_15 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_15 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_15 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_15;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_16");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_16 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 15);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_16 or params.Pg_N_init{16}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_16 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_16 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_16 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_16 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_16;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_17");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_17 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 16);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_17 or params.Pg_N_init{17}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_17 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_17 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_17 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_17 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_17;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_18");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_18 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 17);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_18 or params.Pg_N_init{18}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_18 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_18 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_18 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_18 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_18;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_19");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_19 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 18);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_19 or params.Pg_N_init{19}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_19 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_19 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_19 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_19 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_19;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_20");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_20 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 19);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_20 or params.Pg_N_init{20}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_20 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_20 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_20 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_20 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_20;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_21");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_21 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 20);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_21 or params.Pg_N_init{21}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_21 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_21 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_21 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_21 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_21;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_22");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_22 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 21);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_22 or params.Pg_N_init{22}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_22 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_22 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_22 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_22 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_22;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_23");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_23 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 22);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_23 or params.Pg_N_init{23}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_23 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_23 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_23 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_23 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_23;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_24");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_24 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 23);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_24 or params.Pg_N_init{24}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_24 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_24 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_24 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_24 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_24;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_25");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_25 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 24);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_25 or params.Pg_N_init{25}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_25 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_25 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_25 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_25 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_25;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_26");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_26 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 25);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_26 or params.Pg_N_init{26}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_26 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_26 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_26 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_26 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_26;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_27");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_27 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 26);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_27 or params.Pg_N_init{27}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_27 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_27 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_27 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_27 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_27;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_28");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_28 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 27);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_28 or params.Pg_N_init{28}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_28 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_28 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_28 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_28 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_28;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_29");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_29 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 28);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_29 or params.Pg_N_init{29}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_29 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_29 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_29 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_29 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_29;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_30");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_30 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 29);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_30 or params.Pg_N_init{30}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_30 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_30 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_30 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_30 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_30;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_31");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_31 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 30);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_31 or params.Pg_N_init{31}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_31 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_31 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_31 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_31 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_31;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_32");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_32 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 31);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_32 or params.Pg_N_init{32}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_32 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_32 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_32 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_32 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_32;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_33");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_33 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 32);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_33 or params.Pg_N_init{33}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_33 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_33 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_33 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_33 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_33;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_34");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_34 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 33);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_34 or params.Pg_N_init{34}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_34 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_34 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_34 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_34 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_34;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_35");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_35 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 34);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_35 or params.Pg_N_init{35}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_35 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_35 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_35 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_35 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_35;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_36");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_36 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 35);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_36 or params.Pg_N_init{36}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_36 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_36 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_36 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_36 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_36;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_37");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_37 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 36);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_37 or params.Pg_N_init{37}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_37 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_37 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_37 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_37 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_37;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_38");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_38 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 37);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_38 or params.Pg_N_init{38}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_38 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_38 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_38 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_38 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_38;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_39");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_39 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 38);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_39 or params.Pg_N_init{39}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_39 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_39 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_39 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_39 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_39;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_40");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_40 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 39);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_40 or params.Pg_N_init{40}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_40 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_40 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_40 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_40 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_40;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_41");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_41 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 40);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_41 or params.Pg_N_init{41}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_41 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_41 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_41 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_41 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_41;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_42");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_42 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 41);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_42 or params.Pg_N_init{42}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_42 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_42 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_42 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_42 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_42;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_43");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_43 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 42);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_43 or params.Pg_N_init{43}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_43 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_43 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_43 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_43 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_43;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_44");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_44 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 43);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_44 or params.Pg_N_init{44}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_44 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_44 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_44 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_44 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_44;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_45");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_45 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 44);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_45 or params.Pg_N_init{45}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_45 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_45 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_45 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_45 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_45;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_46");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_46 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 45);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_46 or params.Pg_N_init{46}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_46 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_46 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_46 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_46 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_46;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_47");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_47 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 46);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_47 or params.Pg_N_init{47}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_47 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_47 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_47 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_47 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_47;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_48");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_48 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 47);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_48 or params.Pg_N_init{48}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_48 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_48 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_48 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_48 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_48;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_49");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_49 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 48);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_49 or params.Pg_N_init{49}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_49 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_49 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_49 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_49 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_49;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_50");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_50 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 49);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_50 or params.Pg_N_init{50}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_50 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_50 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_50 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_50 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_50;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_51");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_51 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 50);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_51 or params.Pg_N_init{51}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_51 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_51 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_51 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_51 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_51;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_52");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_52 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 51);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_52 or params.Pg_N_init{52}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_52 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_52 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_52 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_52 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_52;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_53");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_53 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 52);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_53 or params.Pg_N_init{53}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_53 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_53 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_53 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_53 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_53;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_54");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_54 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 53);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_54 or params.Pg_N_init{54}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_54 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_54 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_54 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_54 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_54;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_55");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_55 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 54);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_55 or params.Pg_N_init{55}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_55 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_55 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_55 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_55 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_55;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_56");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_56 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 55);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_56 or params.Pg_N_init{56}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_56 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_56 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_56 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_56 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_56;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_57");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_57 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 56);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_57 or params.Pg_N_init{57}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_57 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_57 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_57 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_57 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_57;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_58");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_58 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 57);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_58 or params.Pg_N_init{58}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_58 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_58 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_58 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_58 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_58;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_59");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_59 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 58);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_59 or params.Pg_N_init{59}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_59 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_59 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_59 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_59 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_59;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_60");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_60 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 59);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_60 or params.Pg_N_init{60}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_60 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_60 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_60 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_60 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_60;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_61");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_61 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 60);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_61 or params.Pg_N_init{61}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_61 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_61 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_61 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_61 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_61;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_62");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_62 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 61);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_62 or params.Pg_N_init{62}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_62 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_62 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_62 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_62 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_62;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_63");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_63 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 62);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_63 or params.Pg_N_init{63}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_63 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_63 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_63 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_63 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_63;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_64");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_64 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 63);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_64 or params.Pg_N_init{64}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_64 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_64 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_64 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_64 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_64;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_65");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_65 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 64);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_65 or params.Pg_N_init{65}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_65 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_65 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_65 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_65 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_65;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_66");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_66 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 65);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_66 or params.Pg_N_init{66}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_66 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_66 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_66 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_66 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_66;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_67");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_67 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 66);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_67 or params.Pg_N_init{67}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_67 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_67 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_67 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_67 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_67;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_68");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_68 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 67);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_68 or params.Pg_N_init{68}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_68 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_68 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_68 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_68 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_68;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_69");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_69 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 68);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_69 or params.Pg_N_init{69}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_69 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_69 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_69 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_69 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_69;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_70");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_70 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 69);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_70 or params.Pg_N_init{70}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_70 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_70 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_70 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_70 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_70;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_71");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_71 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 70);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_71 or params.Pg_N_init{71}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_71 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_71 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_71 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_71 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_71;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_72");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_72 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 71);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_72 or params.Pg_N_init{72}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_72 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_72 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_72 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_72 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_72;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_73");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_73 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 72);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_73 or params.Pg_N_init{73}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_73 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_73 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_73 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_73 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_73;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_74");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_74 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 73);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_74 or params.Pg_N_init{74}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_74 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_74 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_74 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_74 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_74;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_75");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_75 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 74);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_75 or params.Pg_N_init{75}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_75 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_75 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_75 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_75 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_75;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_76");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_76 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 75);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_76 or params.Pg_N_init{76}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_76 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_76 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_76 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_76 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_76;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_77");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_77 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 76);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_77 or params.Pg_N_init{77}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_77 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_77 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_77 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_77 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_77;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_78");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_78 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 77);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_78 or params.Pg_N_init{78}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_78 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_78 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_78 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_78 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_78;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_79");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_79 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 78);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_79 or params.Pg_N_init{79}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_79 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_79 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_79 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_79 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_79;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_80");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_80 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 79);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_80 or params.Pg_N_init{80}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_80 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_80 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_80 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_80 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_80;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_81");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_81 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 80);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_81 or params.Pg_N_init{81}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_81 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_81 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_81 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_81 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_81;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_82");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_82 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 81);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_82 or params.Pg_N_init{82}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_82 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_82 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_82 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_82 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_82;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_83");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_83 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 82);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_83 or params.Pg_N_init{83}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_83 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_83 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_83 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_83 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_83;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_84");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_84 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 83);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_84 or params.Pg_N_init{84}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_84 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_84 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_84 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_84 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_84;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_85");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_85 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 84);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_85 or params.Pg_N_init{85}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_85 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_85 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_85 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_85 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_85;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_86");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_86 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 85);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_86 or params.Pg_N_init{86}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_86 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_86 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_86 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_86 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_86;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_87");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_87 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 86);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_87 or params.Pg_N_init{87}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_87 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_87 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_87 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_87 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_87;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_88");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_88 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 87);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_88 or params.Pg_N_init{88}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_88 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_88 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_88 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_88 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_88;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_89");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_89 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 88);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_89 or params.Pg_N_init{89}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_89 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_89 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_89 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_89 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_89;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_90");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_90 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 89);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_90 or params.Pg_N_init{90}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_90 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_90 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_90 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_90 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_90;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_91");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_91 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 90);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_91 or params.Pg_N_init{91}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_91 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_91 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_91 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_91 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_91;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_92");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_92 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 91);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_92 or params.Pg_N_init{92}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_92 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_92 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_92 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_92 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_92;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_93");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_93 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 92);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_93 or params.Pg_N_init{93}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_93 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_93 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_93 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_93 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_93;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_94");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_94 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 93);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_94 or params.Pg_N_init{94}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_94 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_94 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_94 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_94 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_94;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_95");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_95 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 94);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_95 or params.Pg_N_init{95}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_95 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_95 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_95 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_95 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_95;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_96");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_96 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 95);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_96 or params.Pg_N_init{96}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_96 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_96 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_96 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_96 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_96;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_97");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_97 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 96);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_97 or params.Pg_N_init{97}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_97 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_97 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_97 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_97 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_97;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_98");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_98 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 97);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_98 or params.Pg_N_init{98}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_98 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_98 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_98 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_98 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_98;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_99");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_99 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 98);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_99 or params.Pg_N_init{99}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_99 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_99 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_99 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_99 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_99;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_100");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_100 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 99);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_100 or params.Pg_N_init{100}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_100 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_100 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_100 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_100 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_100;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Pg_N_init_101");
  if (xm == NULL) {
    /* Attempt to pull Pg_N_init_101 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Pg_N_init");
    if (cell != NULL)
      xm = mxGetCell(cell, 100);
  }
  if (xm == NULL) {
    printf("could not find params.Pg_N_init_101 or params.Pg_N_init{101}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Pg_N_init_101 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Pg_N_init_101 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Pg_N_init_101 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Pg_N_init_101 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Pg_N_init_101;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_1");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_1 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 0);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_1 or params.Thetag_N_avg{1}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_1 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_1 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_1 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_1 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_1;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_2");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_2 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 1);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_2 or params.Thetag_N_avg{2}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_2 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_2 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_2 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_2 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_2;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_3");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_3 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 2);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_3 or params.Thetag_N_avg{3}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_3 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_3 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_3 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_3 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_3;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_4");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_4 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 3);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_4 or params.Thetag_N_avg{4}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_4 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_4 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_4 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_4 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_4;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_5");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_5 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 4);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_5 or params.Thetag_N_avg{5}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_5 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_5 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_5 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_5 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_5;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_6");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_6 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 5);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_6 or params.Thetag_N_avg{6}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_6 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_6 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_6 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_6 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_6;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_7");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_7 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 6);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_7 or params.Thetag_N_avg{7}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_7 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_7 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_7 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_7 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_7;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_8");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_8 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 7);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_8 or params.Thetag_N_avg{8}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_8 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_8 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_8 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_8 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_8;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_9");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_9 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 8);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_9 or params.Thetag_N_avg{9}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_9 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_9 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_9 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_9 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_9;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_10");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_10 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 9);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_10 or params.Thetag_N_avg{10}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_10 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_10 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_10 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_10 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_10;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_11");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_11 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 10);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_11 or params.Thetag_N_avg{11}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_11 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_11 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_11 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_11 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_11;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_12");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_12 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 11);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_12 or params.Thetag_N_avg{12}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_12 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_12 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_12 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_12 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_12;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_13");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_13 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 12);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_13 or params.Thetag_N_avg{13}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_13 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_13 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_13 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_13 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_13;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_14");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_14 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 13);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_14 or params.Thetag_N_avg{14}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_14 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_14 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_14 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_14 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_14;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_15");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_15 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 14);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_15 or params.Thetag_N_avg{15}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_15 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_15 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_15 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_15 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_15;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_16");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_16 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 15);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_16 or params.Thetag_N_avg{16}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_16 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_16 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_16 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_16 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_16;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_17");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_17 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 16);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_17 or params.Thetag_N_avg{17}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_17 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_17 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_17 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_17 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_17;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_18");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_18 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 17);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_18 or params.Thetag_N_avg{18}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_18 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_18 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_18 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_18 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_18;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_19");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_19 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 18);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_19 or params.Thetag_N_avg{19}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_19 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_19 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_19 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_19 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_19;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_20");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_20 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 19);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_20 or params.Thetag_N_avg{20}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_20 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_20 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_20 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_20 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_20;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_21");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_21 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 20);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_21 or params.Thetag_N_avg{21}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_21 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_21 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_21 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_21 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_21;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_22");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_22 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 21);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_22 or params.Thetag_N_avg{22}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_22 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_22 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_22 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_22 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_22;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_23");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_23 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 22);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_23 or params.Thetag_N_avg{23}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_23 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_23 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_23 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_23 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_23;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_24");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_24 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 23);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_24 or params.Thetag_N_avg{24}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_24 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_24 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_24 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_24 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_24;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_25");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_25 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 24);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_25 or params.Thetag_N_avg{25}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_25 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_25 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_25 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_25 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_25;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_26");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_26 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 25);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_26 or params.Thetag_N_avg{26}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_26 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_26 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_26 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_26 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_26;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_27");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_27 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 26);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_27 or params.Thetag_N_avg{27}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_27 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_27 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_27 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_27 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_27;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_28");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_28 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 27);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_28 or params.Thetag_N_avg{28}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_28 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_28 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_28 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_28 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_28;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_29");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_29 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 28);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_29 or params.Thetag_N_avg{29}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_29 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_29 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_29 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_29 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_29;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_30");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_30 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 29);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_30 or params.Thetag_N_avg{30}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_30 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_30 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_30 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_30 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_30;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_31");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_31 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 30);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_31 or params.Thetag_N_avg{31}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_31 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_31 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_31 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_31 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_31;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_32");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_32 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 31);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_32 or params.Thetag_N_avg{32}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_32 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_32 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_32 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_32 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_32;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_33");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_33 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 32);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_33 or params.Thetag_N_avg{33}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_33 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_33 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_33 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_33 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_33;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_34");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_34 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 33);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_34 or params.Thetag_N_avg{34}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_34 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_34 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_34 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_34 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_34;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_35");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_35 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 34);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_35 or params.Thetag_N_avg{35}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_35 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_35 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_35 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_35 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_35;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_36");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_36 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 35);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_36 or params.Thetag_N_avg{36}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_36 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_36 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_36 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_36 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_36;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_37");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_37 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 36);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_37 or params.Thetag_N_avg{37}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_37 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_37 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_37 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_37 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_37;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_38");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_38 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 37);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_38 or params.Thetag_N_avg{38}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_38 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_38 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_38 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_38 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_38;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_39");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_39 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 38);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_39 or params.Thetag_N_avg{39}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_39 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_39 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_39 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_39 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_39;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_40");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_40 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 39);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_40 or params.Thetag_N_avg{40}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_40 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_40 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_40 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_40 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_40;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_41");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_41 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 40);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_41 or params.Thetag_N_avg{41}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_41 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_41 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_41 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_41 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_41;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_42");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_42 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 41);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_42 or params.Thetag_N_avg{42}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_42 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_42 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_42 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_42 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_42;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_43");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_43 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 42);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_43 or params.Thetag_N_avg{43}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_43 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_43 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_43 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_43 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_43;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_44");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_44 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 43);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_44 or params.Thetag_N_avg{44}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_44 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_44 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_44 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_44 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_44;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_45");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_45 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 44);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_45 or params.Thetag_N_avg{45}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_45 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_45 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_45 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_45 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_45;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_46");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_46 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 45);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_46 or params.Thetag_N_avg{46}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_46 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_46 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_46 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_46 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_46;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_47");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_47 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 46);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_47 or params.Thetag_N_avg{47}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_47 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_47 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_47 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_47 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_47;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_48");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_48 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 47);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_48 or params.Thetag_N_avg{48}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_48 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_48 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_48 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_48 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_48;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_49");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_49 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 48);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_49 or params.Thetag_N_avg{49}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_49 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_49 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_49 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_49 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_49;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_50");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_50 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 49);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_50 or params.Thetag_N_avg{50}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_50 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_50 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_50 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_50 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_50;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_51");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_51 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 50);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_51 or params.Thetag_N_avg{51}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_51 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_51 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_51 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_51 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_51;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_52");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_52 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 51);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_52 or params.Thetag_N_avg{52}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_52 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_52 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_52 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_52 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_52;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_53");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_53 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 52);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_53 or params.Thetag_N_avg{53}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_53 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_53 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_53 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_53 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_53;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_54");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_54 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 53);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_54 or params.Thetag_N_avg{54}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_54 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_54 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_54 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_54 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_54;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_55");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_55 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 54);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_55 or params.Thetag_N_avg{55}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_55 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_55 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_55 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_55 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_55;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_56");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_56 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 55);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_56 or params.Thetag_N_avg{56}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_56 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_56 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_56 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_56 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_56;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_57");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_57 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 56);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_57 or params.Thetag_N_avg{57}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_57 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_57 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_57 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_57 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_57;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_58");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_58 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 57);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_58 or params.Thetag_N_avg{58}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_58 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_58 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_58 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_58 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_58;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_59");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_59 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 58);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_59 or params.Thetag_N_avg{59}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_59 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_59 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_59 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_59 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_59;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_60");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_60 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 59);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_60 or params.Thetag_N_avg{60}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_60 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_60 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_60 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_60 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_60;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_61");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_61 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 60);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_61 or params.Thetag_N_avg{61}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_61 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_61 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_61 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_61 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_61;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_62");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_62 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 61);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_62 or params.Thetag_N_avg{62}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_62 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_62 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_62 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_62 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_62;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_63");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_63 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 62);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_63 or params.Thetag_N_avg{63}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_63 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_63 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_63 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_63 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_63;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_64");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_64 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 63);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_64 or params.Thetag_N_avg{64}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_64 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_64 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_64 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_64 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_64;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_65");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_65 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 64);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_65 or params.Thetag_N_avg{65}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_65 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_65 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_65 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_65 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_65;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_66");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_66 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 65);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_66 or params.Thetag_N_avg{66}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_66 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_66 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_66 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_66 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_66;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_67");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_67 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 66);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_67 or params.Thetag_N_avg{67}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_67 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_67 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_67 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_67 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_67;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_68");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_68 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 67);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_68 or params.Thetag_N_avg{68}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_68 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_68 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_68 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_68 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_68;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_69");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_69 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 68);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_69 or params.Thetag_N_avg{69}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_69 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_69 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_69 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_69 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_69;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_70");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_70 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 69);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_70 or params.Thetag_N_avg{70}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_70 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_70 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_70 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_70 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_70;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_71");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_71 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 70);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_71 or params.Thetag_N_avg{71}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_71 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_71 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_71 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_71 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_71;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_72");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_72 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 71);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_72 or params.Thetag_N_avg{72}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_72 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_72 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_72 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_72 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_72;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_73");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_73 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 72);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_73 or params.Thetag_N_avg{73}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_73 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_73 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_73 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_73 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_73;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_74");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_74 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 73);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_74 or params.Thetag_N_avg{74}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_74 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_74 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_74 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_74 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_74;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_75");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_75 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 74);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_75 or params.Thetag_N_avg{75}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_75 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_75 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_75 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_75 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_75;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_76");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_76 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 75);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_76 or params.Thetag_N_avg{76}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_76 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_76 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_76 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_76 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_76;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_77");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_77 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 76);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_77 or params.Thetag_N_avg{77}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_77 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_77 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_77 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_77 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_77;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_78");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_78 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 77);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_78 or params.Thetag_N_avg{78}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_78 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_78 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_78 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_78 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_78;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_79");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_79 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 78);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_79 or params.Thetag_N_avg{79}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_79 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_79 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_79 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_79 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_79;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_80");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_80 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 79);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_80 or params.Thetag_N_avg{80}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_80 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_80 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_80 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_80 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_80;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_81");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_81 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 80);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_81 or params.Thetag_N_avg{81}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_81 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_81 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_81 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_81 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_81;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_82");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_82 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 81);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_82 or params.Thetag_N_avg{82}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_82 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_82 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_82 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_82 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_82;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_83");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_83 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 82);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_83 or params.Thetag_N_avg{83}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_83 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_83 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_83 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_83 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_83;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_84");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_84 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 83);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_84 or params.Thetag_N_avg{84}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_84 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_84 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_84 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_84 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_84;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_85");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_85 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 84);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_85 or params.Thetag_N_avg{85}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_85 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_85 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_85 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_85 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_85;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_86");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_86 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 85);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_86 or params.Thetag_N_avg{86}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_86 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_86 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_86 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_86 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_86;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_87");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_87 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 86);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_87 or params.Thetag_N_avg{87}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_87 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_87 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_87 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_87 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_87;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_88");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_88 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 87);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_88 or params.Thetag_N_avg{88}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_88 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_88 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_88 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_88 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_88;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_89");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_89 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 88);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_89 or params.Thetag_N_avg{89}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_89 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_89 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_89 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_89 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_89;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_90");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_90 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 89);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_90 or params.Thetag_N_avg{90}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_90 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_90 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_90 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_90 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_90;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_91");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_91 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 90);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_91 or params.Thetag_N_avg{91}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_91 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_91 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_91 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_91 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_91;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_92");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_92 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 91);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_92 or params.Thetag_N_avg{92}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_92 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_92 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_92 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_92 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_92;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_93");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_93 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 92);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_93 or params.Thetag_N_avg{93}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_93 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_93 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_93 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_93 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_93;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_94");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_94 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 93);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_94 or params.Thetag_N_avg{94}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_94 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_94 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_94 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_94 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_94;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_95");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_95 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 94);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_95 or params.Thetag_N_avg{95}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_95 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_95 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_95 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_95 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_95;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_96");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_96 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 95);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_96 or params.Thetag_N_avg{96}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_96 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_96 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_96 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_96 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_96;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_97");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_97 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 96);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_97 or params.Thetag_N_avg{97}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_97 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_97 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_97 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_97 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_97;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_98");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_98 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 97);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_98 or params.Thetag_N_avg{98}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_98 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_98 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_98 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_98 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_98;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_99");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_99 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 98);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_99 or params.Thetag_N_avg{99}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_99 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_99 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_99 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_99 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_99;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_100");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_100 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 99);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_100 or params.Thetag_N_avg{100}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_100 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_100 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_100 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_100 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_100;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Thetag_N_avg_101");
  if (xm == NULL) {
    /* Attempt to pull Thetag_N_avg_101 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Thetag_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 100);
  }
  if (xm == NULL) {
    printf("could not find params.Thetag_N_avg_101 or params.Thetag_N_avg{101}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Thetag_N_avg_101 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Thetag_N_avg_101 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Thetag_N_avg_101 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Thetag_N_avg_101 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Thetag_N_avg_101;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_1");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_1 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 0);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_1 or params.Vg_N_avg{1}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_1 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_1 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_1 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_1 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_1;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_2");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_2 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 1);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_2 or params.Vg_N_avg{2}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_2 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_2 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_2 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_2 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_2;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_3");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_3 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 2);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_3 or params.Vg_N_avg{3}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_3 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_3 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_3 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_3 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_3;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_4");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_4 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 3);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_4 or params.Vg_N_avg{4}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_4 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_4 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_4 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_4 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_4;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_5");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_5 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 4);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_5 or params.Vg_N_avg{5}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_5 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_5 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_5 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_5 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_5;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_6");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_6 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 5);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_6 or params.Vg_N_avg{6}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_6 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_6 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_6 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_6 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_6;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_7");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_7 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 6);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_7 or params.Vg_N_avg{7}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_7 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_7 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_7 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_7 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_7;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_8");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_8 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 7);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_8 or params.Vg_N_avg{8}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_8 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_8 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_8 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_8 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_8;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_9");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_9 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 8);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_9 or params.Vg_N_avg{9}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_9 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_9 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_9 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_9 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_9;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_10");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_10 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 9);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_10 or params.Vg_N_avg{10}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_10 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_10 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_10 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_10 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_10;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_11");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_11 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 10);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_11 or params.Vg_N_avg{11}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_11 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_11 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_11 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_11 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_11;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_12");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_12 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 11);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_12 or params.Vg_N_avg{12}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_12 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_12 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_12 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_12 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_12;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_13");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_13 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 12);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_13 or params.Vg_N_avg{13}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_13 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_13 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_13 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_13 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_13;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_14");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_14 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 13);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_14 or params.Vg_N_avg{14}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_14 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_14 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_14 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_14 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_14;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_15");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_15 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 14);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_15 or params.Vg_N_avg{15}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_15 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_15 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_15 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_15 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_15;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_16");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_16 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 15);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_16 or params.Vg_N_avg{16}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_16 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_16 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_16 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_16 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_16;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_17");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_17 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 16);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_17 or params.Vg_N_avg{17}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_17 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_17 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_17 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_17 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_17;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_18");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_18 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 17);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_18 or params.Vg_N_avg{18}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_18 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_18 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_18 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_18 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_18;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_19");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_19 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 18);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_19 or params.Vg_N_avg{19}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_19 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_19 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_19 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_19 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_19;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_20");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_20 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 19);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_20 or params.Vg_N_avg{20}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_20 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_20 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_20 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_20 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_20;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_21");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_21 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 20);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_21 or params.Vg_N_avg{21}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_21 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_21 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_21 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_21 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_21;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_22");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_22 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 21);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_22 or params.Vg_N_avg{22}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_22 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_22 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_22 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_22 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_22;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_23");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_23 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 22);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_23 or params.Vg_N_avg{23}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_23 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_23 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_23 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_23 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_23;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_24");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_24 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 23);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_24 or params.Vg_N_avg{24}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_24 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_24 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_24 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_24 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_24;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_25");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_25 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 24);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_25 or params.Vg_N_avg{25}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_25 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_25 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_25 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_25 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_25;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_26");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_26 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 25);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_26 or params.Vg_N_avg{26}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_26 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_26 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_26 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_26 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_26;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_27");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_27 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 26);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_27 or params.Vg_N_avg{27}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_27 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_27 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_27 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_27 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_27;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_28");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_28 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 27);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_28 or params.Vg_N_avg{28}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_28 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_28 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_28 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_28 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_28;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_29");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_29 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 28);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_29 or params.Vg_N_avg{29}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_29 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_29 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_29 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_29 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_29;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_30");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_30 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 29);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_30 or params.Vg_N_avg{30}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_30 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_30 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_30 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_30 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_30;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_31");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_31 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 30);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_31 or params.Vg_N_avg{31}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_31 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_31 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_31 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_31 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_31;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_32");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_32 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 31);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_32 or params.Vg_N_avg{32}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_32 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_32 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_32 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_32 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_32;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_33");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_33 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 32);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_33 or params.Vg_N_avg{33}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_33 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_33 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_33 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_33 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_33;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_34");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_34 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 33);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_34 or params.Vg_N_avg{34}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_34 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_34 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_34 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_34 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_34;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_35");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_35 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 34);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_35 or params.Vg_N_avg{35}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_35 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_35 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_35 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_35 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_35;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_36");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_36 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 35);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_36 or params.Vg_N_avg{36}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_36 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_36 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_36 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_36 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_36;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_37");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_37 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 36);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_37 or params.Vg_N_avg{37}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_37 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_37 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_37 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_37 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_37;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_38");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_38 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 37);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_38 or params.Vg_N_avg{38}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_38 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_38 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_38 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_38 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_38;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_39");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_39 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 38);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_39 or params.Vg_N_avg{39}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_39 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_39 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_39 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_39 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_39;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_40");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_40 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 39);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_40 or params.Vg_N_avg{40}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_40 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_40 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_40 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_40 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_40;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_41");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_41 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 40);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_41 or params.Vg_N_avg{41}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_41 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_41 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_41 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_41 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_41;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_42");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_42 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 41);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_42 or params.Vg_N_avg{42}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_42 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_42 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_42 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_42 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_42;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_43");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_43 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 42);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_43 or params.Vg_N_avg{43}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_43 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_43 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_43 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_43 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_43;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_44");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_44 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 43);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_44 or params.Vg_N_avg{44}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_44 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_44 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_44 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_44 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_44;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_45");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_45 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 44);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_45 or params.Vg_N_avg{45}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_45 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_45 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_45 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_45 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_45;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_46");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_46 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 45);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_46 or params.Vg_N_avg{46}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_46 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_46 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_46 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_46 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_46;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_47");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_47 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 46);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_47 or params.Vg_N_avg{47}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_47 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_47 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_47 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_47 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_47;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_48");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_48 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 47);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_48 or params.Vg_N_avg{48}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_48 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_48 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_48 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_48 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_48;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_49");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_49 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 48);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_49 or params.Vg_N_avg{49}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_49 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_49 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_49 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_49 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_49;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_50");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_50 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 49);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_50 or params.Vg_N_avg{50}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_50 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_50 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_50 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_50 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_50;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_51");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_51 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 50);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_51 or params.Vg_N_avg{51}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_51 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_51 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_51 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_51 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_51;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_52");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_52 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 51);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_52 or params.Vg_N_avg{52}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_52 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_52 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_52 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_52 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_52;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_53");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_53 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 52);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_53 or params.Vg_N_avg{53}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_53 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_53 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_53 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_53 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_53;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_54");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_54 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 53);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_54 or params.Vg_N_avg{54}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_54 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_54 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_54 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_54 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_54;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_55");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_55 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 54);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_55 or params.Vg_N_avg{55}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_55 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_55 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_55 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_55 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_55;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_56");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_56 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 55);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_56 or params.Vg_N_avg{56}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_56 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_56 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_56 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_56 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_56;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_57");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_57 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 56);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_57 or params.Vg_N_avg{57}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_57 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_57 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_57 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_57 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_57;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_58");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_58 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 57);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_58 or params.Vg_N_avg{58}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_58 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_58 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_58 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_58 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_58;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_59");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_59 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 58);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_59 or params.Vg_N_avg{59}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_59 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_59 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_59 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_59 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_59;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_60");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_60 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 59);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_60 or params.Vg_N_avg{60}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_60 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_60 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_60 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_60 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_60;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_61");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_61 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 60);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_61 or params.Vg_N_avg{61}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_61 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_61 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_61 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_61 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_61;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_62");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_62 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 61);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_62 or params.Vg_N_avg{62}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_62 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_62 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_62 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_62 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_62;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_63");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_63 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 62);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_63 or params.Vg_N_avg{63}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_63 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_63 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_63 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_63 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_63;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_64");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_64 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 63);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_64 or params.Vg_N_avg{64}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_64 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_64 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_64 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_64 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_64;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_65");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_65 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 64);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_65 or params.Vg_N_avg{65}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_65 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_65 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_65 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_65 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_65;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_66");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_66 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 65);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_66 or params.Vg_N_avg{66}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_66 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_66 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_66 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_66 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_66;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_67");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_67 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 66);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_67 or params.Vg_N_avg{67}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_67 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_67 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_67 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_67 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_67;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_68");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_68 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 67);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_68 or params.Vg_N_avg{68}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_68 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_68 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_68 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_68 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_68;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_69");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_69 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 68);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_69 or params.Vg_N_avg{69}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_69 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_69 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_69 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_69 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_69;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_70");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_70 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 69);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_70 or params.Vg_N_avg{70}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_70 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_70 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_70 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_70 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_70;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_71");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_71 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 70);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_71 or params.Vg_N_avg{71}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_71 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_71 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_71 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_71 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_71;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_72");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_72 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 71);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_72 or params.Vg_N_avg{72}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_72 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_72 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_72 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_72 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_72;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_73");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_73 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 72);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_73 or params.Vg_N_avg{73}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_73 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_73 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_73 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_73 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_73;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_74");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_74 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 73);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_74 or params.Vg_N_avg{74}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_74 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_74 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_74 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_74 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_74;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_75");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_75 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 74);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_75 or params.Vg_N_avg{75}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_75 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_75 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_75 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_75 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_75;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_76");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_76 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 75);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_76 or params.Vg_N_avg{76}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_76 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_76 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_76 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_76 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_76;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_77");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_77 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 76);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_77 or params.Vg_N_avg{77}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_77 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_77 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_77 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_77 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_77;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_78");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_78 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 77);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_78 or params.Vg_N_avg{78}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_78 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_78 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_78 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_78 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_78;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_79");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_79 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 78);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_79 or params.Vg_N_avg{79}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_79 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_79 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_79 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_79 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_79;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_80");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_80 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 79);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_80 or params.Vg_N_avg{80}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_80 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_80 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_80 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_80 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_80;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_81");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_81 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 80);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_81 or params.Vg_N_avg{81}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_81 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_81 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_81 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_81 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_81;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_82");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_82 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 81);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_82 or params.Vg_N_avg{82}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_82 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_82 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_82 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_82 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_82;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_83");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_83 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 82);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_83 or params.Vg_N_avg{83}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_83 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_83 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_83 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_83 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_83;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_84");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_84 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 83);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_84 or params.Vg_N_avg{84}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_84 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_84 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_84 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_84 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_84;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_85");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_85 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 84);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_85 or params.Vg_N_avg{85}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_85 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_85 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_85 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_85 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_85;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_86");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_86 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 85);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_86 or params.Vg_N_avg{86}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_86 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_86 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_86 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_86 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_86;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_87");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_87 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 86);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_87 or params.Vg_N_avg{87}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_87 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_87 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_87 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_87 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_87;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_88");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_88 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 87);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_88 or params.Vg_N_avg{88}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_88 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_88 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_88 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_88 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_88;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_89");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_89 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 88);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_89 or params.Vg_N_avg{89}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_89 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_89 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_89 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_89 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_89;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_90");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_90 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 89);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_90 or params.Vg_N_avg{90}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_90 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_90 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_90 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_90 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_90;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_91");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_91 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 90);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_91 or params.Vg_N_avg{91}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_91 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_91 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_91 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_91 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_91;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_92");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_92 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 91);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_92 or params.Vg_N_avg{92}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_92 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_92 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_92 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_92 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_92;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_93");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_93 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 92);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_93 or params.Vg_N_avg{93}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_93 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_93 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_93 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_93 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_93;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_94");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_94 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 93);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_94 or params.Vg_N_avg{94}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_94 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_94 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_94 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_94 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_94;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_95");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_95 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 94);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_95 or params.Vg_N_avg{95}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_95 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_95 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_95 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_95 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_95;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_96");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_96 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 95);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_96 or params.Vg_N_avg{96}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_96 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_96 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_96 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_96 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_96;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_97");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_97 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 96);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_97 or params.Vg_N_avg{97}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_97 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_97 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_97 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_97 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_97;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_98");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_98 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 97);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_98 or params.Vg_N_avg{98}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_98 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_98 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_98 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_98 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_98;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_99");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_99 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 98);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_99 or params.Vg_N_avg{99}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_99 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_99 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_99 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_99 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_99;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_100");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_100 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 99);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_100 or params.Vg_N_avg{100}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_100 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_100 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_100 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_100 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_100;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Vg_N_avg_101");
  if (xm == NULL) {
    /* Attempt to pull Vg_N_avg_101 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "Vg_N_avg");
    if (cell != NULL)
      xm = mxGetCell(cell, 100);
  }
  if (xm == NULL) {
    printf("could not find params.Vg_N_avg_101 or params.Vg_N_avg{101}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("Vg_N_avg_101 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Vg_N_avg_101 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Vg_N_avg_101 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Vg_N_avg_101 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Vg_N_avg_101;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "c0");
  if (xm == NULL) {
    printf("could not find params.c0.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("c0 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter c0 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter c0 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter c0 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.c0;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "c1");
  if (xm == NULL) {
    printf("could not find params.c1.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("c1 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter c1 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter c1 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter c1 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.c1;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "c2");
  if (xm == NULL) {
    printf("could not find params.c2.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("c2 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter c2 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter c2 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter c2 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.c2;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "contNum");
  if (xm == NULL) {
    printf("could not find params.contNum.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("contNum must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter contNum must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter contNum must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter contNum must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.contNum;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "rho");
  if (xm == NULL) {
    printf("could not find params.rho.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("rho must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter rho must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter rho must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter rho must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.rho;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_1");
  if (xm == NULL) {
    /* Attempt to pull ug_N_1 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 0);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_1 or params.ug_N{1}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_1 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_1 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_1 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_1 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_1;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_2");
  if (xm == NULL) {
    /* Attempt to pull ug_N_2 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 1);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_2 or params.ug_N{2}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_2 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_2 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_2 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_2 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_2;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_3");
  if (xm == NULL) {
    /* Attempt to pull ug_N_3 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 2);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_3 or params.ug_N{3}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_3 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_3 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_3 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_3 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_3;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_4");
  if (xm == NULL) {
    /* Attempt to pull ug_N_4 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 3);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_4 or params.ug_N{4}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_4 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_4 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_4 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_4 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_4;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_5");
  if (xm == NULL) {
    /* Attempt to pull ug_N_5 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 4);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_5 or params.ug_N{5}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_5 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_5 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_5 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_5 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_5;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_6");
  if (xm == NULL) {
    /* Attempt to pull ug_N_6 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 5);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_6 or params.ug_N{6}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_6 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_6 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_6 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_6 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_6;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_7");
  if (xm == NULL) {
    /* Attempt to pull ug_N_7 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 6);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_7 or params.ug_N{7}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_7 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_7 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_7 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_7 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_7;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_8");
  if (xm == NULL) {
    /* Attempt to pull ug_N_8 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 7);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_8 or params.ug_N{8}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_8 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_8 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_8 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_8 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_8;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_9");
  if (xm == NULL) {
    /* Attempt to pull ug_N_9 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 8);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_9 or params.ug_N{9}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_9 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_9 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_9 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_9 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_9;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_10");
  if (xm == NULL) {
    /* Attempt to pull ug_N_10 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 9);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_10 or params.ug_N{10}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_10 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_10 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_10 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_10 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_10;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_11");
  if (xm == NULL) {
    /* Attempt to pull ug_N_11 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 10);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_11 or params.ug_N{11}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_11 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_11 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_11 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_11 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_11;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_12");
  if (xm == NULL) {
    /* Attempt to pull ug_N_12 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 11);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_12 or params.ug_N{12}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_12 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_12 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_12 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_12 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_12;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_13");
  if (xm == NULL) {
    /* Attempt to pull ug_N_13 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 12);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_13 or params.ug_N{13}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_13 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_13 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_13 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_13 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_13;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_14");
  if (xm == NULL) {
    /* Attempt to pull ug_N_14 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 13);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_14 or params.ug_N{14}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_14 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_14 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_14 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_14 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_14;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_15");
  if (xm == NULL) {
    /* Attempt to pull ug_N_15 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 14);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_15 or params.ug_N{15}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_15 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_15 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_15 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_15 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_15;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_16");
  if (xm == NULL) {
    /* Attempt to pull ug_N_16 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 15);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_16 or params.ug_N{16}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_16 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_16 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_16 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_16 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_16;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_17");
  if (xm == NULL) {
    /* Attempt to pull ug_N_17 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 16);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_17 or params.ug_N{17}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_17 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_17 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_17 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_17 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_17;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_18");
  if (xm == NULL) {
    /* Attempt to pull ug_N_18 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 17);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_18 or params.ug_N{18}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_18 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_18 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_18 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_18 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_18;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_19");
  if (xm == NULL) {
    /* Attempt to pull ug_N_19 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 18);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_19 or params.ug_N{19}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_19 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_19 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_19 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_19 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_19;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_20");
  if (xm == NULL) {
    /* Attempt to pull ug_N_20 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 19);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_20 or params.ug_N{20}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_20 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_20 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_20 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_20 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_20;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_21");
  if (xm == NULL) {
    /* Attempt to pull ug_N_21 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 20);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_21 or params.ug_N{21}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_21 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_21 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_21 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_21 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_21;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_22");
  if (xm == NULL) {
    /* Attempt to pull ug_N_22 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 21);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_22 or params.ug_N{22}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_22 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_22 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_22 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_22 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_22;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_23");
  if (xm == NULL) {
    /* Attempt to pull ug_N_23 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 22);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_23 or params.ug_N{23}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_23 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_23 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_23 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_23 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_23;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_24");
  if (xm == NULL) {
    /* Attempt to pull ug_N_24 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 23);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_24 or params.ug_N{24}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_24 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_24 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_24 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_24 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_24;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_25");
  if (xm == NULL) {
    /* Attempt to pull ug_N_25 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 24);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_25 or params.ug_N{25}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_25 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_25 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_25 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_25 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_25;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_26");
  if (xm == NULL) {
    /* Attempt to pull ug_N_26 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 25);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_26 or params.ug_N{26}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_26 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_26 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_26 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_26 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_26;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_27");
  if (xm == NULL) {
    /* Attempt to pull ug_N_27 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 26);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_27 or params.ug_N{27}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_27 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_27 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_27 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_27 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_27;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_28");
  if (xm == NULL) {
    /* Attempt to pull ug_N_28 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 27);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_28 or params.ug_N{28}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_28 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_28 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_28 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_28 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_28;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_29");
  if (xm == NULL) {
    /* Attempt to pull ug_N_29 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 28);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_29 or params.ug_N{29}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_29 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_29 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_29 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_29 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_29;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_30");
  if (xm == NULL) {
    /* Attempt to pull ug_N_30 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 29);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_30 or params.ug_N{30}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_30 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_30 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_30 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_30 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_30;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_31");
  if (xm == NULL) {
    /* Attempt to pull ug_N_31 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 30);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_31 or params.ug_N{31}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_31 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_31 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_31 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_31 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_31;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_32");
  if (xm == NULL) {
    /* Attempt to pull ug_N_32 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 31);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_32 or params.ug_N{32}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_32 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_32 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_32 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_32 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_32;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_33");
  if (xm == NULL) {
    /* Attempt to pull ug_N_33 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 32);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_33 or params.ug_N{33}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_33 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_33 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_33 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_33 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_33;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_34");
  if (xm == NULL) {
    /* Attempt to pull ug_N_34 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 33);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_34 or params.ug_N{34}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_34 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_34 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_34 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_34 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_34;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_35");
  if (xm == NULL) {
    /* Attempt to pull ug_N_35 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 34);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_35 or params.ug_N{35}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_35 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_35 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_35 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_35 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_35;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_36");
  if (xm == NULL) {
    /* Attempt to pull ug_N_36 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 35);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_36 or params.ug_N{36}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_36 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_36 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_36 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_36 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_36;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_37");
  if (xm == NULL) {
    /* Attempt to pull ug_N_37 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 36);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_37 or params.ug_N{37}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_37 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_37 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_37 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_37 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_37;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_38");
  if (xm == NULL) {
    /* Attempt to pull ug_N_38 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 37);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_38 or params.ug_N{38}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_38 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_38 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_38 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_38 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_38;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_39");
  if (xm == NULL) {
    /* Attempt to pull ug_N_39 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 38);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_39 or params.ug_N{39}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_39 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_39 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_39 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_39 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_39;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_40");
  if (xm == NULL) {
    /* Attempt to pull ug_N_40 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 39);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_40 or params.ug_N{40}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_40 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_40 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_40 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_40 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_40;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_41");
  if (xm == NULL) {
    /* Attempt to pull ug_N_41 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 40);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_41 or params.ug_N{41}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_41 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_41 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_41 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_41 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_41;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_42");
  if (xm == NULL) {
    /* Attempt to pull ug_N_42 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 41);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_42 or params.ug_N{42}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_42 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_42 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_42 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_42 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_42;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_43");
  if (xm == NULL) {
    /* Attempt to pull ug_N_43 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 42);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_43 or params.ug_N{43}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_43 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_43 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_43 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_43 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_43;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_44");
  if (xm == NULL) {
    /* Attempt to pull ug_N_44 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 43);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_44 or params.ug_N{44}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_44 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_44 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_44 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_44 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_44;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_45");
  if (xm == NULL) {
    /* Attempt to pull ug_N_45 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 44);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_45 or params.ug_N{45}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_45 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_45 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_45 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_45 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_45;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_46");
  if (xm == NULL) {
    /* Attempt to pull ug_N_46 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 45);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_46 or params.ug_N{46}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_46 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_46 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_46 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_46 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_46;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_47");
  if (xm == NULL) {
    /* Attempt to pull ug_N_47 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 46);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_47 or params.ug_N{47}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_47 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_47 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_47 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_47 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_47;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_48");
  if (xm == NULL) {
    /* Attempt to pull ug_N_48 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 47);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_48 or params.ug_N{48}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_48 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_48 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_48 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_48 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_48;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_49");
  if (xm == NULL) {
    /* Attempt to pull ug_N_49 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 48);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_49 or params.ug_N{49}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_49 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_49 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_49 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_49 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_49;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_50");
  if (xm == NULL) {
    /* Attempt to pull ug_N_50 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 49);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_50 or params.ug_N{50}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_50 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_50 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_50 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_50 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_50;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_51");
  if (xm == NULL) {
    /* Attempt to pull ug_N_51 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 50);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_51 or params.ug_N{51}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_51 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_51 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_51 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_51 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_51;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_52");
  if (xm == NULL) {
    /* Attempt to pull ug_N_52 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 51);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_52 or params.ug_N{52}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_52 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_52 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_52 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_52 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_52;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_53");
  if (xm == NULL) {
    /* Attempt to pull ug_N_53 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 52);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_53 or params.ug_N{53}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_53 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_53 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_53 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_53 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_53;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_54");
  if (xm == NULL) {
    /* Attempt to pull ug_N_54 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 53);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_54 or params.ug_N{54}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_54 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_54 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_54 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_54 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_54;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_55");
  if (xm == NULL) {
    /* Attempt to pull ug_N_55 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 54);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_55 or params.ug_N{55}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_55 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_55 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_55 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_55 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_55;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_56");
  if (xm == NULL) {
    /* Attempt to pull ug_N_56 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 55);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_56 or params.ug_N{56}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_56 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_56 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_56 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_56 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_56;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_57");
  if (xm == NULL) {
    /* Attempt to pull ug_N_57 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 56);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_57 or params.ug_N{57}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_57 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_57 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_57 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_57 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_57;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_58");
  if (xm == NULL) {
    /* Attempt to pull ug_N_58 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 57);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_58 or params.ug_N{58}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_58 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_58 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_58 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_58 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_58;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_59");
  if (xm == NULL) {
    /* Attempt to pull ug_N_59 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 58);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_59 or params.ug_N{59}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_59 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_59 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_59 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_59 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_59;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_60");
  if (xm == NULL) {
    /* Attempt to pull ug_N_60 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 59);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_60 or params.ug_N{60}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_60 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_60 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_60 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_60 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_60;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_61");
  if (xm == NULL) {
    /* Attempt to pull ug_N_61 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 60);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_61 or params.ug_N{61}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_61 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_61 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_61 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_61 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_61;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_62");
  if (xm == NULL) {
    /* Attempt to pull ug_N_62 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 61);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_62 or params.ug_N{62}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_62 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_62 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_62 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_62 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_62;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_63");
  if (xm == NULL) {
    /* Attempt to pull ug_N_63 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 62);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_63 or params.ug_N{63}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_63 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_63 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_63 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_63 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_63;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_64");
  if (xm == NULL) {
    /* Attempt to pull ug_N_64 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 63);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_64 or params.ug_N{64}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_64 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_64 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_64 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_64 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_64;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_65");
  if (xm == NULL) {
    /* Attempt to pull ug_N_65 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 64);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_65 or params.ug_N{65}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_65 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_65 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_65 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_65 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_65;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_66");
  if (xm == NULL) {
    /* Attempt to pull ug_N_66 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 65);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_66 or params.ug_N{66}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_66 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_66 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_66 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_66 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_66;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_67");
  if (xm == NULL) {
    /* Attempt to pull ug_N_67 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 66);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_67 or params.ug_N{67}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_67 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_67 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_67 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_67 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_67;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_68");
  if (xm == NULL) {
    /* Attempt to pull ug_N_68 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 67);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_68 or params.ug_N{68}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_68 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_68 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_68 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_68 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_68;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_69");
  if (xm == NULL) {
    /* Attempt to pull ug_N_69 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 68);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_69 or params.ug_N{69}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_69 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_69 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_69 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_69 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_69;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_70");
  if (xm == NULL) {
    /* Attempt to pull ug_N_70 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 69);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_70 or params.ug_N{70}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_70 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_70 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_70 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_70 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_70;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_71");
  if (xm == NULL) {
    /* Attempt to pull ug_N_71 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 70);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_71 or params.ug_N{71}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_71 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_71 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_71 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_71 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_71;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_72");
  if (xm == NULL) {
    /* Attempt to pull ug_N_72 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 71);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_72 or params.ug_N{72}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_72 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_72 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_72 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_72 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_72;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_73");
  if (xm == NULL) {
    /* Attempt to pull ug_N_73 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 72);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_73 or params.ug_N{73}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_73 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_73 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_73 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_73 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_73;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_74");
  if (xm == NULL) {
    /* Attempt to pull ug_N_74 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 73);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_74 or params.ug_N{74}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_74 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_74 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_74 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_74 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_74;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_75");
  if (xm == NULL) {
    /* Attempt to pull ug_N_75 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 74);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_75 or params.ug_N{75}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_75 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_75 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_75 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_75 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_75;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_76");
  if (xm == NULL) {
    /* Attempt to pull ug_N_76 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 75);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_76 or params.ug_N{76}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_76 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_76 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_76 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_76 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_76;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_77");
  if (xm == NULL) {
    /* Attempt to pull ug_N_77 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 76);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_77 or params.ug_N{77}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_77 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_77 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_77 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_77 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_77;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_78");
  if (xm == NULL) {
    /* Attempt to pull ug_N_78 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 77);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_78 or params.ug_N{78}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_78 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_78 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_78 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_78 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_78;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_79");
  if (xm == NULL) {
    /* Attempt to pull ug_N_79 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 78);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_79 or params.ug_N{79}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_79 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_79 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_79 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_79 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_79;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_80");
  if (xm == NULL) {
    /* Attempt to pull ug_N_80 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 79);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_80 or params.ug_N{80}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_80 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_80 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_80 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_80 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_80;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_81");
  if (xm == NULL) {
    /* Attempt to pull ug_N_81 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 80);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_81 or params.ug_N{81}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_81 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_81 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_81 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_81 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_81;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_82");
  if (xm == NULL) {
    /* Attempt to pull ug_N_82 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 81);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_82 or params.ug_N{82}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_82 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_82 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_82 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_82 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_82;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_83");
  if (xm == NULL) {
    /* Attempt to pull ug_N_83 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 82);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_83 or params.ug_N{83}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_83 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_83 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_83 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_83 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_83;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_84");
  if (xm == NULL) {
    /* Attempt to pull ug_N_84 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 83);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_84 or params.ug_N{84}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_84 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_84 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_84 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_84 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_84;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_85");
  if (xm == NULL) {
    /* Attempt to pull ug_N_85 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 84);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_85 or params.ug_N{85}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_85 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_85 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_85 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_85 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_85;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_86");
  if (xm == NULL) {
    /* Attempt to pull ug_N_86 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 85);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_86 or params.ug_N{86}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_86 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_86 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_86 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_86 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_86;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_87");
  if (xm == NULL) {
    /* Attempt to pull ug_N_87 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 86);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_87 or params.ug_N{87}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_87 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_87 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_87 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_87 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_87;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_88");
  if (xm == NULL) {
    /* Attempt to pull ug_N_88 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 87);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_88 or params.ug_N{88}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_88 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_88 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_88 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_88 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_88;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_89");
  if (xm == NULL) {
    /* Attempt to pull ug_N_89 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 88);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_89 or params.ug_N{89}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_89 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_89 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_89 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_89 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_89;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_90");
  if (xm == NULL) {
    /* Attempt to pull ug_N_90 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 89);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_90 or params.ug_N{90}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_90 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_90 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_90 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_90 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_90;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_91");
  if (xm == NULL) {
    /* Attempt to pull ug_N_91 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 90);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_91 or params.ug_N{91}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_91 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_91 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_91 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_91 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_91;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_92");
  if (xm == NULL) {
    /* Attempt to pull ug_N_92 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 91);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_92 or params.ug_N{92}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_92 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_92 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_92 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_92 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_92;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_93");
  if (xm == NULL) {
    /* Attempt to pull ug_N_93 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 92);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_93 or params.ug_N{93}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_93 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_93 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_93 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_93 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_93;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_94");
  if (xm == NULL) {
    /* Attempt to pull ug_N_94 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 93);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_94 or params.ug_N{94}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_94 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_94 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_94 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_94 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_94;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_95");
  if (xm == NULL) {
    /* Attempt to pull ug_N_95 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 94);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_95 or params.ug_N{95}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_95 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_95 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_95 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_95 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_95;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_96");
  if (xm == NULL) {
    /* Attempt to pull ug_N_96 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 95);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_96 or params.ug_N{96}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_96 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_96 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_96 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_96 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_96;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_97");
  if (xm == NULL) {
    /* Attempt to pull ug_N_97 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 96);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_97 or params.ug_N{97}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_97 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_97 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_97 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_97 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_97;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_98");
  if (xm == NULL) {
    /* Attempt to pull ug_N_98 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 97);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_98 or params.ug_N{98}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_98 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_98 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_98 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_98 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_98;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_99");
  if (xm == NULL) {
    /* Attempt to pull ug_N_99 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 98);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_99 or params.ug_N{99}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_99 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_99 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_99 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_99 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_99;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_100");
  if (xm == NULL) {
    /* Attempt to pull ug_N_100 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 99);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_100 or params.ug_N{100}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_100 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_100 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_100 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_100 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_100;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "ug_N_101");
  if (xm == NULL) {
    /* Attempt to pull ug_N_101 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "ug_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 100);
  }
  if (xm == NULL) {
    printf("could not find params.ug_N_101 or params.ug_N{101}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("ug_N_101 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter ug_N_101 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter ug_N_101 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter ug_N_101 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.ug_N_101;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_1");
  if (xm == NULL) {
    /* Attempt to pull vg_N_1 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 0);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_1 or params.vg_N{1}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_1 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_1 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_1 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_1 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_1;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_2");
  if (xm == NULL) {
    /* Attempt to pull vg_N_2 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 1);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_2 or params.vg_N{2}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_2 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_2 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_2 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_2 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_2;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_3");
  if (xm == NULL) {
    /* Attempt to pull vg_N_3 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 2);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_3 or params.vg_N{3}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_3 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_3 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_3 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_3 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_3;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_4");
  if (xm == NULL) {
    /* Attempt to pull vg_N_4 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 3);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_4 or params.vg_N{4}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_4 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_4 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_4 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_4 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_4;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_5");
  if (xm == NULL) {
    /* Attempt to pull vg_N_5 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 4);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_5 or params.vg_N{5}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_5 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_5 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_5 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_5 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_5;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_6");
  if (xm == NULL) {
    /* Attempt to pull vg_N_6 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 5);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_6 or params.vg_N{6}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_6 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_6 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_6 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_6 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_6;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_7");
  if (xm == NULL) {
    /* Attempt to pull vg_N_7 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 6);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_7 or params.vg_N{7}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_7 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_7 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_7 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_7 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_7;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_8");
  if (xm == NULL) {
    /* Attempt to pull vg_N_8 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 7);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_8 or params.vg_N{8}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_8 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_8 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_8 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_8 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_8;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_9");
  if (xm == NULL) {
    /* Attempt to pull vg_N_9 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 8);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_9 or params.vg_N{9}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_9 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_9 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_9 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_9 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_9;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_10");
  if (xm == NULL) {
    /* Attempt to pull vg_N_10 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 9);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_10 or params.vg_N{10}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_10 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_10 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_10 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_10 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_10;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_11");
  if (xm == NULL) {
    /* Attempt to pull vg_N_11 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 10);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_11 or params.vg_N{11}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_11 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_11 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_11 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_11 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_11;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_12");
  if (xm == NULL) {
    /* Attempt to pull vg_N_12 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 11);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_12 or params.vg_N{12}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_12 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_12 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_12 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_12 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_12;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_13");
  if (xm == NULL) {
    /* Attempt to pull vg_N_13 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 12);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_13 or params.vg_N{13}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_13 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_13 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_13 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_13 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_13;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_14");
  if (xm == NULL) {
    /* Attempt to pull vg_N_14 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 13);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_14 or params.vg_N{14}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_14 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_14 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_14 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_14 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_14;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_15");
  if (xm == NULL) {
    /* Attempt to pull vg_N_15 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 14);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_15 or params.vg_N{15}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_15 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_15 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_15 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_15 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_15;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_16");
  if (xm == NULL) {
    /* Attempt to pull vg_N_16 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 15);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_16 or params.vg_N{16}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_16 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_16 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_16 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_16 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_16;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_17");
  if (xm == NULL) {
    /* Attempt to pull vg_N_17 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 16);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_17 or params.vg_N{17}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_17 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_17 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_17 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_17 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_17;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_18");
  if (xm == NULL) {
    /* Attempt to pull vg_N_18 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 17);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_18 or params.vg_N{18}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_18 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_18 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_18 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_18 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_18;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_19");
  if (xm == NULL) {
    /* Attempt to pull vg_N_19 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 18);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_19 or params.vg_N{19}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_19 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_19 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_19 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_19 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_19;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_20");
  if (xm == NULL) {
    /* Attempt to pull vg_N_20 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 19);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_20 or params.vg_N{20}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_20 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_20 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_20 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_20 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_20;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_21");
  if (xm == NULL) {
    /* Attempt to pull vg_N_21 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 20);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_21 or params.vg_N{21}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_21 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_21 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_21 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_21 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_21;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_22");
  if (xm == NULL) {
    /* Attempt to pull vg_N_22 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 21);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_22 or params.vg_N{22}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_22 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_22 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_22 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_22 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_22;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_23");
  if (xm == NULL) {
    /* Attempt to pull vg_N_23 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 22);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_23 or params.vg_N{23}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_23 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_23 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_23 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_23 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_23;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_24");
  if (xm == NULL) {
    /* Attempt to pull vg_N_24 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 23);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_24 or params.vg_N{24}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_24 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_24 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_24 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_24 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_24;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_25");
  if (xm == NULL) {
    /* Attempt to pull vg_N_25 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 24);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_25 or params.vg_N{25}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_25 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_25 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_25 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_25 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_25;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_26");
  if (xm == NULL) {
    /* Attempt to pull vg_N_26 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 25);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_26 or params.vg_N{26}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_26 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_26 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_26 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_26 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_26;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_27");
  if (xm == NULL) {
    /* Attempt to pull vg_N_27 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 26);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_27 or params.vg_N{27}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_27 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_27 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_27 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_27 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_27;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_28");
  if (xm == NULL) {
    /* Attempt to pull vg_N_28 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 27);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_28 or params.vg_N{28}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_28 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_28 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_28 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_28 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_28;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_29");
  if (xm == NULL) {
    /* Attempt to pull vg_N_29 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 28);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_29 or params.vg_N{29}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_29 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_29 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_29 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_29 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_29;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_30");
  if (xm == NULL) {
    /* Attempt to pull vg_N_30 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 29);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_30 or params.vg_N{30}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_30 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_30 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_30 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_30 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_30;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_31");
  if (xm == NULL) {
    /* Attempt to pull vg_N_31 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 30);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_31 or params.vg_N{31}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_31 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_31 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_31 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_31 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_31;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_32");
  if (xm == NULL) {
    /* Attempt to pull vg_N_32 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 31);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_32 or params.vg_N{32}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_32 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_32 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_32 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_32 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_32;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_33");
  if (xm == NULL) {
    /* Attempt to pull vg_N_33 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 32);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_33 or params.vg_N{33}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_33 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_33 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_33 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_33 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_33;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_34");
  if (xm == NULL) {
    /* Attempt to pull vg_N_34 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 33);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_34 or params.vg_N{34}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_34 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_34 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_34 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_34 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_34;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_35");
  if (xm == NULL) {
    /* Attempt to pull vg_N_35 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 34);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_35 or params.vg_N{35}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_35 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_35 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_35 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_35 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_35;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_36");
  if (xm == NULL) {
    /* Attempt to pull vg_N_36 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 35);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_36 or params.vg_N{36}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_36 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_36 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_36 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_36 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_36;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_37");
  if (xm == NULL) {
    /* Attempt to pull vg_N_37 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 36);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_37 or params.vg_N{37}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_37 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_37 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_37 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_37 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_37;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_38");
  if (xm == NULL) {
    /* Attempt to pull vg_N_38 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 37);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_38 or params.vg_N{38}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_38 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_38 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_38 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_38 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_38;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_39");
  if (xm == NULL) {
    /* Attempt to pull vg_N_39 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 38);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_39 or params.vg_N{39}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_39 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_39 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_39 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_39 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_39;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_40");
  if (xm == NULL) {
    /* Attempt to pull vg_N_40 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 39);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_40 or params.vg_N{40}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_40 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_40 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_40 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_40 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_40;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_41");
  if (xm == NULL) {
    /* Attempt to pull vg_N_41 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 40);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_41 or params.vg_N{41}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_41 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_41 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_41 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_41 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_41;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_42");
  if (xm == NULL) {
    /* Attempt to pull vg_N_42 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 41);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_42 or params.vg_N{42}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_42 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_42 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_42 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_42 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_42;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_43");
  if (xm == NULL) {
    /* Attempt to pull vg_N_43 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 42);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_43 or params.vg_N{43}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_43 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_43 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_43 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_43 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_43;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_44");
  if (xm == NULL) {
    /* Attempt to pull vg_N_44 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 43);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_44 or params.vg_N{44}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_44 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_44 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_44 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_44 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_44;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_45");
  if (xm == NULL) {
    /* Attempt to pull vg_N_45 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 44);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_45 or params.vg_N{45}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_45 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_45 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_45 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_45 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_45;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_46");
  if (xm == NULL) {
    /* Attempt to pull vg_N_46 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 45);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_46 or params.vg_N{46}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_46 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_46 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_46 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_46 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_46;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_47");
  if (xm == NULL) {
    /* Attempt to pull vg_N_47 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 46);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_47 or params.vg_N{47}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_47 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_47 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_47 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_47 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_47;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_48");
  if (xm == NULL) {
    /* Attempt to pull vg_N_48 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 47);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_48 or params.vg_N{48}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_48 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_48 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_48 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_48 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_48;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_49");
  if (xm == NULL) {
    /* Attempt to pull vg_N_49 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 48);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_49 or params.vg_N{49}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_49 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_49 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_49 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_49 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_49;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_50");
  if (xm == NULL) {
    /* Attempt to pull vg_N_50 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 49);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_50 or params.vg_N{50}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_50 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_50 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_50 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_50 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_50;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_51");
  if (xm == NULL) {
    /* Attempt to pull vg_N_51 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 50);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_51 or params.vg_N{51}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_51 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_51 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_51 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_51 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_51;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_52");
  if (xm == NULL) {
    /* Attempt to pull vg_N_52 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 51);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_52 or params.vg_N{52}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_52 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_52 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_52 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_52 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_52;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_53");
  if (xm == NULL) {
    /* Attempt to pull vg_N_53 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 52);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_53 or params.vg_N{53}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_53 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_53 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_53 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_53 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_53;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_54");
  if (xm == NULL) {
    /* Attempt to pull vg_N_54 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 53);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_54 or params.vg_N{54}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_54 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_54 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_54 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_54 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_54;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_55");
  if (xm == NULL) {
    /* Attempt to pull vg_N_55 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 54);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_55 or params.vg_N{55}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_55 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_55 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_55 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_55 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_55;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_56");
  if (xm == NULL) {
    /* Attempt to pull vg_N_56 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 55);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_56 or params.vg_N{56}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_56 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_56 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_56 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_56 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_56;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_57");
  if (xm == NULL) {
    /* Attempt to pull vg_N_57 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 56);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_57 or params.vg_N{57}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_57 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_57 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_57 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_57 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_57;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_58");
  if (xm == NULL) {
    /* Attempt to pull vg_N_58 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 57);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_58 or params.vg_N{58}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_58 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_58 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_58 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_58 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_58;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_59");
  if (xm == NULL) {
    /* Attempt to pull vg_N_59 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 58);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_59 or params.vg_N{59}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_59 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_59 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_59 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_59 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_59;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_60");
  if (xm == NULL) {
    /* Attempt to pull vg_N_60 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 59);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_60 or params.vg_N{60}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_60 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_60 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_60 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_60 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_60;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_61");
  if (xm == NULL) {
    /* Attempt to pull vg_N_61 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 60);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_61 or params.vg_N{61}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_61 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_61 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_61 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_61 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_61;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_62");
  if (xm == NULL) {
    /* Attempt to pull vg_N_62 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 61);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_62 or params.vg_N{62}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_62 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_62 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_62 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_62 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_62;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_63");
  if (xm == NULL) {
    /* Attempt to pull vg_N_63 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 62);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_63 or params.vg_N{63}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_63 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_63 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_63 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_63 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_63;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_64");
  if (xm == NULL) {
    /* Attempt to pull vg_N_64 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 63);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_64 or params.vg_N{64}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_64 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_64 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_64 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_64 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_64;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_65");
  if (xm == NULL) {
    /* Attempt to pull vg_N_65 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 64);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_65 or params.vg_N{65}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_65 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_65 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_65 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_65 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_65;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_66");
  if (xm == NULL) {
    /* Attempt to pull vg_N_66 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 65);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_66 or params.vg_N{66}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_66 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_66 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_66 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_66 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_66;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_67");
  if (xm == NULL) {
    /* Attempt to pull vg_N_67 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 66);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_67 or params.vg_N{67}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_67 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_67 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_67 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_67 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_67;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_68");
  if (xm == NULL) {
    /* Attempt to pull vg_N_68 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 67);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_68 or params.vg_N{68}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_68 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_68 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_68 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_68 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_68;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_69");
  if (xm == NULL) {
    /* Attempt to pull vg_N_69 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 68);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_69 or params.vg_N{69}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_69 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_69 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_69 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_69 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_69;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_70");
  if (xm == NULL) {
    /* Attempt to pull vg_N_70 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 69);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_70 or params.vg_N{70}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_70 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_70 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_70 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_70 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_70;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_71");
  if (xm == NULL) {
    /* Attempt to pull vg_N_71 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 70);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_71 or params.vg_N{71}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_71 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_71 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_71 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_71 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_71;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_72");
  if (xm == NULL) {
    /* Attempt to pull vg_N_72 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 71);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_72 or params.vg_N{72}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_72 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_72 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_72 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_72 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_72;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_73");
  if (xm == NULL) {
    /* Attempt to pull vg_N_73 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 72);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_73 or params.vg_N{73}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_73 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_73 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_73 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_73 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_73;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_74");
  if (xm == NULL) {
    /* Attempt to pull vg_N_74 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 73);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_74 or params.vg_N{74}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_74 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_74 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_74 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_74 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_74;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_75");
  if (xm == NULL) {
    /* Attempt to pull vg_N_75 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 74);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_75 or params.vg_N{75}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_75 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_75 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_75 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_75 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_75;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_76");
  if (xm == NULL) {
    /* Attempt to pull vg_N_76 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 75);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_76 or params.vg_N{76}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_76 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_76 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_76 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_76 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_76;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_77");
  if (xm == NULL) {
    /* Attempt to pull vg_N_77 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 76);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_77 or params.vg_N{77}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_77 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_77 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_77 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_77 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_77;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_78");
  if (xm == NULL) {
    /* Attempt to pull vg_N_78 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 77);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_78 or params.vg_N{78}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_78 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_78 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_78 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_78 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_78;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_79");
  if (xm == NULL) {
    /* Attempt to pull vg_N_79 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 78);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_79 or params.vg_N{79}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_79 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_79 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_79 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_79 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_79;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_80");
  if (xm == NULL) {
    /* Attempt to pull vg_N_80 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 79);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_80 or params.vg_N{80}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_80 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_80 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_80 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_80 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_80;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_81");
  if (xm == NULL) {
    /* Attempt to pull vg_N_81 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 80);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_81 or params.vg_N{81}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_81 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_81 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_81 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_81 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_81;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_82");
  if (xm == NULL) {
    /* Attempt to pull vg_N_82 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 81);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_82 or params.vg_N{82}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_82 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_82 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_82 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_82 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_82;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_83");
  if (xm == NULL) {
    /* Attempt to pull vg_N_83 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 82);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_83 or params.vg_N{83}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_83 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_83 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_83 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_83 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_83;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_84");
  if (xm == NULL) {
    /* Attempt to pull vg_N_84 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 83);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_84 or params.vg_N{84}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_84 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_84 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_84 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_84 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_84;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_85");
  if (xm == NULL) {
    /* Attempt to pull vg_N_85 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 84);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_85 or params.vg_N{85}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_85 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_85 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_85 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_85 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_85;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_86");
  if (xm == NULL) {
    /* Attempt to pull vg_N_86 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 85);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_86 or params.vg_N{86}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_86 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_86 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_86 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_86 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_86;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_87");
  if (xm == NULL) {
    /* Attempt to pull vg_N_87 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 86);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_87 or params.vg_N{87}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_87 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_87 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_87 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_87 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_87;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_88");
  if (xm == NULL) {
    /* Attempt to pull vg_N_88 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 87);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_88 or params.vg_N{88}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_88 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_88 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_88 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_88 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_88;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_89");
  if (xm == NULL) {
    /* Attempt to pull vg_N_89 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 88);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_89 or params.vg_N{89}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_89 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_89 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_89 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_89 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_89;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_90");
  if (xm == NULL) {
    /* Attempt to pull vg_N_90 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 89);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_90 or params.vg_N{90}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_90 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_90 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_90 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_90 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_90;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_91");
  if (xm == NULL) {
    /* Attempt to pull vg_N_91 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 90);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_91 or params.vg_N{91}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_91 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_91 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_91 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_91 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_91;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_92");
  if (xm == NULL) {
    /* Attempt to pull vg_N_92 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 91);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_92 or params.vg_N{92}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_92 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_92 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_92 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_92 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_92;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_93");
  if (xm == NULL) {
    /* Attempt to pull vg_N_93 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 92);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_93 or params.vg_N{93}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_93 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_93 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_93 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_93 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_93;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_94");
  if (xm == NULL) {
    /* Attempt to pull vg_N_94 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 93);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_94 or params.vg_N{94}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_94 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_94 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_94 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_94 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_94;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_95");
  if (xm == NULL) {
    /* Attempt to pull vg_N_95 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 94);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_95 or params.vg_N{95}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_95 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_95 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_95 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_95 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_95;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_96");
  if (xm == NULL) {
    /* Attempt to pull vg_N_96 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 95);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_96 or params.vg_N{96}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_96 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_96 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_96 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_96 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_96;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_97");
  if (xm == NULL) {
    /* Attempt to pull vg_N_97 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 96);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_97 or params.vg_N{97}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_97 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_97 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_97 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_97 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_97;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_98");
  if (xm == NULL) {
    /* Attempt to pull vg_N_98 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 97);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_98 or params.vg_N{98}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_98 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_98 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_98 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_98 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_98;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_99");
  if (xm == NULL) {
    /* Attempt to pull vg_N_99 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 98);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_99 or params.vg_N{99}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_99 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_99 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_99 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_99 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_99;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_100");
  if (xm == NULL) {
    /* Attempt to pull vg_N_100 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 99);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_100 or params.vg_N{100}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_100 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_100 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_100 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_100 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_100;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "vg_N_101");
  if (xm == NULL) {
    /* Attempt to pull vg_N_101 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "vg_N");
    if (cell != NULL)
      xm = mxGetCell(cell, 100);
  }
  if (xm == NULL) {
    printf("could not find params.vg_N_101 or params.vg_N{101}.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("vg_N_101 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter vg_N_101 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter vg_N_101 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter vg_N_101 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.vg_N_101;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  if (valid_vars != 613) {
    printf("Error: %d parameters are invalid.\n", 613 - valid_vars);
    mexErrMsgTxt("invalid parameters found.");
  }
  if (prepare_for_c) {
    printf("settings.prepare_for_c == 1. thus, outputting for C.\n");
    for (i = 0; i < 1; i++)
      printf("  params.c2[%d] = %.6g;\n", i, params.c2[i]);
    for (i = 0; i < 1; i++)
      printf("  params.c1[%d] = %.6g;\n", i, params.c1[i]);
    for (i = 0; i < 1; i++)
      printf("  params.c0[%d] = %.6g;\n", i, params.c0[i]);
    for (i = 0; i < 1; i++)
      printf("  params.rho[%d] = %.6g;\n", i, params.rho[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_1[%d] = %.6g;\n", i, params.Pg_N_init_1[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_1[%d] = %.6g;\n", i, params.Pg_N_avg_1[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_1[%d] = %.6g;\n", i, params.ug_N_1[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_1[%d] = %.6g;\n", i, params.Vg_N_avg_1[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_1[%d] = %.6g;\n", i, params.Thetag_N_avg_1[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_1[%d] = %.6g;\n", i, params.vg_N_1[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_2[%d] = %.6g;\n", i, params.Pg_N_init_2[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_2[%d] = %.6g;\n", i, params.Pg_N_avg_2[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_2[%d] = %.6g;\n", i, params.ug_N_2[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_2[%d] = %.6g;\n", i, params.Vg_N_avg_2[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_2[%d] = %.6g;\n", i, params.Thetag_N_avg_2[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_2[%d] = %.6g;\n", i, params.vg_N_2[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_3[%d] = %.6g;\n", i, params.Pg_N_init_3[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_3[%d] = %.6g;\n", i, params.Pg_N_avg_3[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_3[%d] = %.6g;\n", i, params.ug_N_3[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_3[%d] = %.6g;\n", i, params.Vg_N_avg_3[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_3[%d] = %.6g;\n", i, params.Thetag_N_avg_3[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_3[%d] = %.6g;\n", i, params.vg_N_3[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_4[%d] = %.6g;\n", i, params.Pg_N_init_4[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_4[%d] = %.6g;\n", i, params.Pg_N_avg_4[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_4[%d] = %.6g;\n", i, params.ug_N_4[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_4[%d] = %.6g;\n", i, params.Vg_N_avg_4[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_4[%d] = %.6g;\n", i, params.Thetag_N_avg_4[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_4[%d] = %.6g;\n", i, params.vg_N_4[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_5[%d] = %.6g;\n", i, params.Pg_N_init_5[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_5[%d] = %.6g;\n", i, params.Pg_N_avg_5[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_5[%d] = %.6g;\n", i, params.ug_N_5[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_5[%d] = %.6g;\n", i, params.Vg_N_avg_5[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_5[%d] = %.6g;\n", i, params.Thetag_N_avg_5[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_5[%d] = %.6g;\n", i, params.vg_N_5[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_6[%d] = %.6g;\n", i, params.Pg_N_init_6[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_6[%d] = %.6g;\n", i, params.Pg_N_avg_6[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_6[%d] = %.6g;\n", i, params.ug_N_6[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_6[%d] = %.6g;\n", i, params.Vg_N_avg_6[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_6[%d] = %.6g;\n", i, params.Thetag_N_avg_6[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_6[%d] = %.6g;\n", i, params.vg_N_6[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_7[%d] = %.6g;\n", i, params.Pg_N_init_7[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_7[%d] = %.6g;\n", i, params.Pg_N_avg_7[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_7[%d] = %.6g;\n", i, params.ug_N_7[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_7[%d] = %.6g;\n", i, params.Vg_N_avg_7[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_7[%d] = %.6g;\n", i, params.Thetag_N_avg_7[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_7[%d] = %.6g;\n", i, params.vg_N_7[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_8[%d] = %.6g;\n", i, params.Pg_N_init_8[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_8[%d] = %.6g;\n", i, params.Pg_N_avg_8[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_8[%d] = %.6g;\n", i, params.ug_N_8[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_8[%d] = %.6g;\n", i, params.Vg_N_avg_8[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_8[%d] = %.6g;\n", i, params.Thetag_N_avg_8[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_8[%d] = %.6g;\n", i, params.vg_N_8[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_9[%d] = %.6g;\n", i, params.Pg_N_init_9[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_9[%d] = %.6g;\n", i, params.Pg_N_avg_9[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_9[%d] = %.6g;\n", i, params.ug_N_9[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_9[%d] = %.6g;\n", i, params.Vg_N_avg_9[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_9[%d] = %.6g;\n", i, params.Thetag_N_avg_9[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_9[%d] = %.6g;\n", i, params.vg_N_9[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_10[%d] = %.6g;\n", i, params.Pg_N_init_10[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_10[%d] = %.6g;\n", i, params.Pg_N_avg_10[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_10[%d] = %.6g;\n", i, params.ug_N_10[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_10[%d] = %.6g;\n", i, params.Vg_N_avg_10[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_10[%d] = %.6g;\n", i, params.Thetag_N_avg_10[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_10[%d] = %.6g;\n", i, params.vg_N_10[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_11[%d] = %.6g;\n", i, params.Pg_N_init_11[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_11[%d] = %.6g;\n", i, params.Pg_N_avg_11[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_11[%d] = %.6g;\n", i, params.ug_N_11[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_11[%d] = %.6g;\n", i, params.Vg_N_avg_11[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_11[%d] = %.6g;\n", i, params.Thetag_N_avg_11[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_11[%d] = %.6g;\n", i, params.vg_N_11[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_12[%d] = %.6g;\n", i, params.Pg_N_init_12[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_12[%d] = %.6g;\n", i, params.Pg_N_avg_12[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_12[%d] = %.6g;\n", i, params.ug_N_12[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_12[%d] = %.6g;\n", i, params.Vg_N_avg_12[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_12[%d] = %.6g;\n", i, params.Thetag_N_avg_12[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_12[%d] = %.6g;\n", i, params.vg_N_12[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_13[%d] = %.6g;\n", i, params.Pg_N_init_13[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_13[%d] = %.6g;\n", i, params.Pg_N_avg_13[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_13[%d] = %.6g;\n", i, params.ug_N_13[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_13[%d] = %.6g;\n", i, params.Vg_N_avg_13[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_13[%d] = %.6g;\n", i, params.Thetag_N_avg_13[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_13[%d] = %.6g;\n", i, params.vg_N_13[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_14[%d] = %.6g;\n", i, params.Pg_N_init_14[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_14[%d] = %.6g;\n", i, params.Pg_N_avg_14[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_14[%d] = %.6g;\n", i, params.ug_N_14[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_14[%d] = %.6g;\n", i, params.Vg_N_avg_14[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_14[%d] = %.6g;\n", i, params.Thetag_N_avg_14[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_14[%d] = %.6g;\n", i, params.vg_N_14[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_15[%d] = %.6g;\n", i, params.Pg_N_init_15[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_15[%d] = %.6g;\n", i, params.Pg_N_avg_15[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_15[%d] = %.6g;\n", i, params.ug_N_15[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_15[%d] = %.6g;\n", i, params.Vg_N_avg_15[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_15[%d] = %.6g;\n", i, params.Thetag_N_avg_15[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_15[%d] = %.6g;\n", i, params.vg_N_15[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_16[%d] = %.6g;\n", i, params.Pg_N_init_16[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_16[%d] = %.6g;\n", i, params.Pg_N_avg_16[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_16[%d] = %.6g;\n", i, params.ug_N_16[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_16[%d] = %.6g;\n", i, params.Vg_N_avg_16[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_16[%d] = %.6g;\n", i, params.Thetag_N_avg_16[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_16[%d] = %.6g;\n", i, params.vg_N_16[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_17[%d] = %.6g;\n", i, params.Pg_N_init_17[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_17[%d] = %.6g;\n", i, params.Pg_N_avg_17[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_17[%d] = %.6g;\n", i, params.ug_N_17[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_17[%d] = %.6g;\n", i, params.Vg_N_avg_17[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_17[%d] = %.6g;\n", i, params.Thetag_N_avg_17[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_17[%d] = %.6g;\n", i, params.vg_N_17[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_18[%d] = %.6g;\n", i, params.Pg_N_init_18[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_18[%d] = %.6g;\n", i, params.Pg_N_avg_18[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_18[%d] = %.6g;\n", i, params.ug_N_18[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_18[%d] = %.6g;\n", i, params.Vg_N_avg_18[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_18[%d] = %.6g;\n", i, params.Thetag_N_avg_18[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_18[%d] = %.6g;\n", i, params.vg_N_18[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_19[%d] = %.6g;\n", i, params.Pg_N_init_19[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_19[%d] = %.6g;\n", i, params.Pg_N_avg_19[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_19[%d] = %.6g;\n", i, params.ug_N_19[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_19[%d] = %.6g;\n", i, params.Vg_N_avg_19[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_19[%d] = %.6g;\n", i, params.Thetag_N_avg_19[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_19[%d] = %.6g;\n", i, params.vg_N_19[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_20[%d] = %.6g;\n", i, params.Pg_N_init_20[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_20[%d] = %.6g;\n", i, params.Pg_N_avg_20[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_20[%d] = %.6g;\n", i, params.ug_N_20[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_20[%d] = %.6g;\n", i, params.Vg_N_avg_20[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_20[%d] = %.6g;\n", i, params.Thetag_N_avg_20[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_20[%d] = %.6g;\n", i, params.vg_N_20[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_21[%d] = %.6g;\n", i, params.Pg_N_init_21[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_21[%d] = %.6g;\n", i, params.Pg_N_avg_21[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_21[%d] = %.6g;\n", i, params.ug_N_21[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_21[%d] = %.6g;\n", i, params.Vg_N_avg_21[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_21[%d] = %.6g;\n", i, params.Thetag_N_avg_21[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_21[%d] = %.6g;\n", i, params.vg_N_21[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_22[%d] = %.6g;\n", i, params.Pg_N_init_22[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_22[%d] = %.6g;\n", i, params.Pg_N_avg_22[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_22[%d] = %.6g;\n", i, params.ug_N_22[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_22[%d] = %.6g;\n", i, params.Vg_N_avg_22[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_22[%d] = %.6g;\n", i, params.Thetag_N_avg_22[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_22[%d] = %.6g;\n", i, params.vg_N_22[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_23[%d] = %.6g;\n", i, params.Pg_N_init_23[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_23[%d] = %.6g;\n", i, params.Pg_N_avg_23[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_23[%d] = %.6g;\n", i, params.ug_N_23[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_23[%d] = %.6g;\n", i, params.Vg_N_avg_23[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_23[%d] = %.6g;\n", i, params.Thetag_N_avg_23[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_23[%d] = %.6g;\n", i, params.vg_N_23[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_24[%d] = %.6g;\n", i, params.Pg_N_init_24[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_24[%d] = %.6g;\n", i, params.Pg_N_avg_24[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_24[%d] = %.6g;\n", i, params.ug_N_24[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_24[%d] = %.6g;\n", i, params.Vg_N_avg_24[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_24[%d] = %.6g;\n", i, params.Thetag_N_avg_24[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_24[%d] = %.6g;\n", i, params.vg_N_24[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_25[%d] = %.6g;\n", i, params.Pg_N_init_25[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_25[%d] = %.6g;\n", i, params.Pg_N_avg_25[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_25[%d] = %.6g;\n", i, params.ug_N_25[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_25[%d] = %.6g;\n", i, params.Vg_N_avg_25[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_25[%d] = %.6g;\n", i, params.Thetag_N_avg_25[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_25[%d] = %.6g;\n", i, params.vg_N_25[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_26[%d] = %.6g;\n", i, params.Pg_N_init_26[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_26[%d] = %.6g;\n", i, params.Pg_N_avg_26[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_26[%d] = %.6g;\n", i, params.ug_N_26[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_26[%d] = %.6g;\n", i, params.Vg_N_avg_26[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_26[%d] = %.6g;\n", i, params.Thetag_N_avg_26[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_26[%d] = %.6g;\n", i, params.vg_N_26[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_27[%d] = %.6g;\n", i, params.Pg_N_init_27[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_27[%d] = %.6g;\n", i, params.Pg_N_avg_27[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_27[%d] = %.6g;\n", i, params.ug_N_27[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_27[%d] = %.6g;\n", i, params.Vg_N_avg_27[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_27[%d] = %.6g;\n", i, params.Thetag_N_avg_27[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_27[%d] = %.6g;\n", i, params.vg_N_27[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_28[%d] = %.6g;\n", i, params.Pg_N_init_28[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_28[%d] = %.6g;\n", i, params.Pg_N_avg_28[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_28[%d] = %.6g;\n", i, params.ug_N_28[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_28[%d] = %.6g;\n", i, params.Vg_N_avg_28[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_28[%d] = %.6g;\n", i, params.Thetag_N_avg_28[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_28[%d] = %.6g;\n", i, params.vg_N_28[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_29[%d] = %.6g;\n", i, params.Pg_N_init_29[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_29[%d] = %.6g;\n", i, params.Pg_N_avg_29[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_29[%d] = %.6g;\n", i, params.ug_N_29[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_29[%d] = %.6g;\n", i, params.Vg_N_avg_29[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_29[%d] = %.6g;\n", i, params.Thetag_N_avg_29[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_29[%d] = %.6g;\n", i, params.vg_N_29[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_30[%d] = %.6g;\n", i, params.Pg_N_init_30[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_30[%d] = %.6g;\n", i, params.Pg_N_avg_30[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_30[%d] = %.6g;\n", i, params.ug_N_30[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_30[%d] = %.6g;\n", i, params.Vg_N_avg_30[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_30[%d] = %.6g;\n", i, params.Thetag_N_avg_30[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_30[%d] = %.6g;\n", i, params.vg_N_30[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_31[%d] = %.6g;\n", i, params.Pg_N_init_31[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_31[%d] = %.6g;\n", i, params.Pg_N_avg_31[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_31[%d] = %.6g;\n", i, params.ug_N_31[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_31[%d] = %.6g;\n", i, params.Vg_N_avg_31[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_31[%d] = %.6g;\n", i, params.Thetag_N_avg_31[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_31[%d] = %.6g;\n", i, params.vg_N_31[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_32[%d] = %.6g;\n", i, params.Pg_N_init_32[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_32[%d] = %.6g;\n", i, params.Pg_N_avg_32[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_32[%d] = %.6g;\n", i, params.ug_N_32[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_32[%d] = %.6g;\n", i, params.Vg_N_avg_32[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_32[%d] = %.6g;\n", i, params.Thetag_N_avg_32[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_32[%d] = %.6g;\n", i, params.vg_N_32[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_33[%d] = %.6g;\n", i, params.Pg_N_init_33[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_33[%d] = %.6g;\n", i, params.Pg_N_avg_33[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_33[%d] = %.6g;\n", i, params.ug_N_33[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_33[%d] = %.6g;\n", i, params.Vg_N_avg_33[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_33[%d] = %.6g;\n", i, params.Thetag_N_avg_33[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_33[%d] = %.6g;\n", i, params.vg_N_33[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_34[%d] = %.6g;\n", i, params.Pg_N_init_34[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_34[%d] = %.6g;\n", i, params.Pg_N_avg_34[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_34[%d] = %.6g;\n", i, params.ug_N_34[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_34[%d] = %.6g;\n", i, params.Vg_N_avg_34[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_34[%d] = %.6g;\n", i, params.Thetag_N_avg_34[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_34[%d] = %.6g;\n", i, params.vg_N_34[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_35[%d] = %.6g;\n", i, params.Pg_N_init_35[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_35[%d] = %.6g;\n", i, params.Pg_N_avg_35[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_35[%d] = %.6g;\n", i, params.ug_N_35[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_35[%d] = %.6g;\n", i, params.Vg_N_avg_35[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_35[%d] = %.6g;\n", i, params.Thetag_N_avg_35[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_35[%d] = %.6g;\n", i, params.vg_N_35[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_36[%d] = %.6g;\n", i, params.Pg_N_init_36[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_36[%d] = %.6g;\n", i, params.Pg_N_avg_36[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_36[%d] = %.6g;\n", i, params.ug_N_36[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_36[%d] = %.6g;\n", i, params.Vg_N_avg_36[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_36[%d] = %.6g;\n", i, params.Thetag_N_avg_36[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_36[%d] = %.6g;\n", i, params.vg_N_36[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_37[%d] = %.6g;\n", i, params.Pg_N_init_37[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_37[%d] = %.6g;\n", i, params.Pg_N_avg_37[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_37[%d] = %.6g;\n", i, params.ug_N_37[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_37[%d] = %.6g;\n", i, params.Vg_N_avg_37[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_37[%d] = %.6g;\n", i, params.Thetag_N_avg_37[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_37[%d] = %.6g;\n", i, params.vg_N_37[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_38[%d] = %.6g;\n", i, params.Pg_N_init_38[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_38[%d] = %.6g;\n", i, params.Pg_N_avg_38[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_38[%d] = %.6g;\n", i, params.ug_N_38[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_38[%d] = %.6g;\n", i, params.Vg_N_avg_38[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_38[%d] = %.6g;\n", i, params.Thetag_N_avg_38[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_38[%d] = %.6g;\n", i, params.vg_N_38[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_39[%d] = %.6g;\n", i, params.Pg_N_init_39[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_39[%d] = %.6g;\n", i, params.Pg_N_avg_39[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_39[%d] = %.6g;\n", i, params.ug_N_39[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_39[%d] = %.6g;\n", i, params.Vg_N_avg_39[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_39[%d] = %.6g;\n", i, params.Thetag_N_avg_39[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_39[%d] = %.6g;\n", i, params.vg_N_39[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_40[%d] = %.6g;\n", i, params.Pg_N_init_40[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_40[%d] = %.6g;\n", i, params.Pg_N_avg_40[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_40[%d] = %.6g;\n", i, params.ug_N_40[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_40[%d] = %.6g;\n", i, params.Vg_N_avg_40[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_40[%d] = %.6g;\n", i, params.Thetag_N_avg_40[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_40[%d] = %.6g;\n", i, params.vg_N_40[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_41[%d] = %.6g;\n", i, params.Pg_N_init_41[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_41[%d] = %.6g;\n", i, params.Pg_N_avg_41[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_41[%d] = %.6g;\n", i, params.ug_N_41[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_41[%d] = %.6g;\n", i, params.Vg_N_avg_41[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_41[%d] = %.6g;\n", i, params.Thetag_N_avg_41[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_41[%d] = %.6g;\n", i, params.vg_N_41[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_42[%d] = %.6g;\n", i, params.Pg_N_init_42[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_42[%d] = %.6g;\n", i, params.Pg_N_avg_42[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_42[%d] = %.6g;\n", i, params.ug_N_42[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_42[%d] = %.6g;\n", i, params.Vg_N_avg_42[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_42[%d] = %.6g;\n", i, params.Thetag_N_avg_42[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_42[%d] = %.6g;\n", i, params.vg_N_42[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_43[%d] = %.6g;\n", i, params.Pg_N_init_43[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_43[%d] = %.6g;\n", i, params.Pg_N_avg_43[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_43[%d] = %.6g;\n", i, params.ug_N_43[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_43[%d] = %.6g;\n", i, params.Vg_N_avg_43[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_43[%d] = %.6g;\n", i, params.Thetag_N_avg_43[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_43[%d] = %.6g;\n", i, params.vg_N_43[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_44[%d] = %.6g;\n", i, params.Pg_N_init_44[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_44[%d] = %.6g;\n", i, params.Pg_N_avg_44[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_44[%d] = %.6g;\n", i, params.ug_N_44[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_44[%d] = %.6g;\n", i, params.Vg_N_avg_44[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_44[%d] = %.6g;\n", i, params.Thetag_N_avg_44[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_44[%d] = %.6g;\n", i, params.vg_N_44[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_45[%d] = %.6g;\n", i, params.Pg_N_init_45[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_45[%d] = %.6g;\n", i, params.Pg_N_avg_45[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_45[%d] = %.6g;\n", i, params.ug_N_45[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_45[%d] = %.6g;\n", i, params.Vg_N_avg_45[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_45[%d] = %.6g;\n", i, params.Thetag_N_avg_45[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_45[%d] = %.6g;\n", i, params.vg_N_45[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_46[%d] = %.6g;\n", i, params.Pg_N_init_46[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_46[%d] = %.6g;\n", i, params.Pg_N_avg_46[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_46[%d] = %.6g;\n", i, params.ug_N_46[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_46[%d] = %.6g;\n", i, params.Vg_N_avg_46[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_46[%d] = %.6g;\n", i, params.Thetag_N_avg_46[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_46[%d] = %.6g;\n", i, params.vg_N_46[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_47[%d] = %.6g;\n", i, params.Pg_N_init_47[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_47[%d] = %.6g;\n", i, params.Pg_N_avg_47[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_47[%d] = %.6g;\n", i, params.ug_N_47[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_47[%d] = %.6g;\n", i, params.Vg_N_avg_47[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_47[%d] = %.6g;\n", i, params.Thetag_N_avg_47[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_47[%d] = %.6g;\n", i, params.vg_N_47[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_48[%d] = %.6g;\n", i, params.Pg_N_init_48[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_48[%d] = %.6g;\n", i, params.Pg_N_avg_48[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_48[%d] = %.6g;\n", i, params.ug_N_48[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_48[%d] = %.6g;\n", i, params.Vg_N_avg_48[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_48[%d] = %.6g;\n", i, params.Thetag_N_avg_48[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_48[%d] = %.6g;\n", i, params.vg_N_48[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_49[%d] = %.6g;\n", i, params.Pg_N_init_49[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_49[%d] = %.6g;\n", i, params.Pg_N_avg_49[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_49[%d] = %.6g;\n", i, params.ug_N_49[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_49[%d] = %.6g;\n", i, params.Vg_N_avg_49[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_49[%d] = %.6g;\n", i, params.Thetag_N_avg_49[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_49[%d] = %.6g;\n", i, params.vg_N_49[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_50[%d] = %.6g;\n", i, params.Pg_N_init_50[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_50[%d] = %.6g;\n", i, params.Pg_N_avg_50[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_50[%d] = %.6g;\n", i, params.ug_N_50[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_50[%d] = %.6g;\n", i, params.Vg_N_avg_50[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_50[%d] = %.6g;\n", i, params.Thetag_N_avg_50[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_50[%d] = %.6g;\n", i, params.vg_N_50[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_51[%d] = %.6g;\n", i, params.Pg_N_init_51[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_51[%d] = %.6g;\n", i, params.Pg_N_avg_51[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_51[%d] = %.6g;\n", i, params.ug_N_51[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_51[%d] = %.6g;\n", i, params.Vg_N_avg_51[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_51[%d] = %.6g;\n", i, params.Thetag_N_avg_51[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_51[%d] = %.6g;\n", i, params.vg_N_51[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_52[%d] = %.6g;\n", i, params.Pg_N_init_52[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_52[%d] = %.6g;\n", i, params.Pg_N_avg_52[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_52[%d] = %.6g;\n", i, params.ug_N_52[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_52[%d] = %.6g;\n", i, params.Vg_N_avg_52[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_52[%d] = %.6g;\n", i, params.Thetag_N_avg_52[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_52[%d] = %.6g;\n", i, params.vg_N_52[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_53[%d] = %.6g;\n", i, params.Pg_N_init_53[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_53[%d] = %.6g;\n", i, params.Pg_N_avg_53[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_53[%d] = %.6g;\n", i, params.ug_N_53[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_53[%d] = %.6g;\n", i, params.Vg_N_avg_53[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_53[%d] = %.6g;\n", i, params.Thetag_N_avg_53[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_53[%d] = %.6g;\n", i, params.vg_N_53[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_54[%d] = %.6g;\n", i, params.Pg_N_init_54[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_54[%d] = %.6g;\n", i, params.Pg_N_avg_54[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_54[%d] = %.6g;\n", i, params.ug_N_54[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_54[%d] = %.6g;\n", i, params.Vg_N_avg_54[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_54[%d] = %.6g;\n", i, params.Thetag_N_avg_54[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_54[%d] = %.6g;\n", i, params.vg_N_54[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_55[%d] = %.6g;\n", i, params.Pg_N_init_55[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_55[%d] = %.6g;\n", i, params.Pg_N_avg_55[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_55[%d] = %.6g;\n", i, params.ug_N_55[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_55[%d] = %.6g;\n", i, params.Vg_N_avg_55[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_55[%d] = %.6g;\n", i, params.Thetag_N_avg_55[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_55[%d] = %.6g;\n", i, params.vg_N_55[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_56[%d] = %.6g;\n", i, params.Pg_N_init_56[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_56[%d] = %.6g;\n", i, params.Pg_N_avg_56[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_56[%d] = %.6g;\n", i, params.ug_N_56[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_56[%d] = %.6g;\n", i, params.Vg_N_avg_56[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_56[%d] = %.6g;\n", i, params.Thetag_N_avg_56[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_56[%d] = %.6g;\n", i, params.vg_N_56[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_57[%d] = %.6g;\n", i, params.Pg_N_init_57[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_57[%d] = %.6g;\n", i, params.Pg_N_avg_57[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_57[%d] = %.6g;\n", i, params.ug_N_57[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_57[%d] = %.6g;\n", i, params.Vg_N_avg_57[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_57[%d] = %.6g;\n", i, params.Thetag_N_avg_57[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_57[%d] = %.6g;\n", i, params.vg_N_57[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_58[%d] = %.6g;\n", i, params.Pg_N_init_58[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_58[%d] = %.6g;\n", i, params.Pg_N_avg_58[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_58[%d] = %.6g;\n", i, params.ug_N_58[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_58[%d] = %.6g;\n", i, params.Vg_N_avg_58[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_58[%d] = %.6g;\n", i, params.Thetag_N_avg_58[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_58[%d] = %.6g;\n", i, params.vg_N_58[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_59[%d] = %.6g;\n", i, params.Pg_N_init_59[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_59[%d] = %.6g;\n", i, params.Pg_N_avg_59[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_59[%d] = %.6g;\n", i, params.ug_N_59[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_59[%d] = %.6g;\n", i, params.Vg_N_avg_59[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_59[%d] = %.6g;\n", i, params.Thetag_N_avg_59[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_59[%d] = %.6g;\n", i, params.vg_N_59[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_60[%d] = %.6g;\n", i, params.Pg_N_init_60[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_60[%d] = %.6g;\n", i, params.Pg_N_avg_60[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_60[%d] = %.6g;\n", i, params.ug_N_60[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_60[%d] = %.6g;\n", i, params.Vg_N_avg_60[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_60[%d] = %.6g;\n", i, params.Thetag_N_avg_60[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_60[%d] = %.6g;\n", i, params.vg_N_60[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_61[%d] = %.6g;\n", i, params.Pg_N_init_61[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_61[%d] = %.6g;\n", i, params.Pg_N_avg_61[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_61[%d] = %.6g;\n", i, params.ug_N_61[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_61[%d] = %.6g;\n", i, params.Vg_N_avg_61[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_61[%d] = %.6g;\n", i, params.Thetag_N_avg_61[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_61[%d] = %.6g;\n", i, params.vg_N_61[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_62[%d] = %.6g;\n", i, params.Pg_N_init_62[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_62[%d] = %.6g;\n", i, params.Pg_N_avg_62[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_62[%d] = %.6g;\n", i, params.ug_N_62[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_62[%d] = %.6g;\n", i, params.Vg_N_avg_62[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_62[%d] = %.6g;\n", i, params.Thetag_N_avg_62[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_62[%d] = %.6g;\n", i, params.vg_N_62[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_63[%d] = %.6g;\n", i, params.Pg_N_init_63[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_63[%d] = %.6g;\n", i, params.Pg_N_avg_63[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_63[%d] = %.6g;\n", i, params.ug_N_63[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_63[%d] = %.6g;\n", i, params.Vg_N_avg_63[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_63[%d] = %.6g;\n", i, params.Thetag_N_avg_63[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_63[%d] = %.6g;\n", i, params.vg_N_63[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_64[%d] = %.6g;\n", i, params.Pg_N_init_64[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_64[%d] = %.6g;\n", i, params.Pg_N_avg_64[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_64[%d] = %.6g;\n", i, params.ug_N_64[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_64[%d] = %.6g;\n", i, params.Vg_N_avg_64[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_64[%d] = %.6g;\n", i, params.Thetag_N_avg_64[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_64[%d] = %.6g;\n", i, params.vg_N_64[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_65[%d] = %.6g;\n", i, params.Pg_N_init_65[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_65[%d] = %.6g;\n", i, params.Pg_N_avg_65[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_65[%d] = %.6g;\n", i, params.ug_N_65[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_65[%d] = %.6g;\n", i, params.Vg_N_avg_65[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_65[%d] = %.6g;\n", i, params.Thetag_N_avg_65[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_65[%d] = %.6g;\n", i, params.vg_N_65[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_66[%d] = %.6g;\n", i, params.Pg_N_init_66[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_66[%d] = %.6g;\n", i, params.Pg_N_avg_66[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_66[%d] = %.6g;\n", i, params.ug_N_66[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_66[%d] = %.6g;\n", i, params.Vg_N_avg_66[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_66[%d] = %.6g;\n", i, params.Thetag_N_avg_66[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_66[%d] = %.6g;\n", i, params.vg_N_66[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_67[%d] = %.6g;\n", i, params.Pg_N_init_67[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_67[%d] = %.6g;\n", i, params.Pg_N_avg_67[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_67[%d] = %.6g;\n", i, params.ug_N_67[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_67[%d] = %.6g;\n", i, params.Vg_N_avg_67[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_67[%d] = %.6g;\n", i, params.Thetag_N_avg_67[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_67[%d] = %.6g;\n", i, params.vg_N_67[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_68[%d] = %.6g;\n", i, params.Pg_N_init_68[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_68[%d] = %.6g;\n", i, params.Pg_N_avg_68[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_68[%d] = %.6g;\n", i, params.ug_N_68[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_68[%d] = %.6g;\n", i, params.Vg_N_avg_68[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_68[%d] = %.6g;\n", i, params.Thetag_N_avg_68[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_68[%d] = %.6g;\n", i, params.vg_N_68[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_69[%d] = %.6g;\n", i, params.Pg_N_init_69[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_69[%d] = %.6g;\n", i, params.Pg_N_avg_69[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_69[%d] = %.6g;\n", i, params.ug_N_69[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_69[%d] = %.6g;\n", i, params.Vg_N_avg_69[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_69[%d] = %.6g;\n", i, params.Thetag_N_avg_69[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_69[%d] = %.6g;\n", i, params.vg_N_69[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_70[%d] = %.6g;\n", i, params.Pg_N_init_70[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_70[%d] = %.6g;\n", i, params.Pg_N_avg_70[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_70[%d] = %.6g;\n", i, params.ug_N_70[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_70[%d] = %.6g;\n", i, params.Vg_N_avg_70[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_70[%d] = %.6g;\n", i, params.Thetag_N_avg_70[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_70[%d] = %.6g;\n", i, params.vg_N_70[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_71[%d] = %.6g;\n", i, params.Pg_N_init_71[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_71[%d] = %.6g;\n", i, params.Pg_N_avg_71[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_71[%d] = %.6g;\n", i, params.ug_N_71[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_71[%d] = %.6g;\n", i, params.Vg_N_avg_71[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_71[%d] = %.6g;\n", i, params.Thetag_N_avg_71[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_71[%d] = %.6g;\n", i, params.vg_N_71[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_72[%d] = %.6g;\n", i, params.Pg_N_init_72[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_72[%d] = %.6g;\n", i, params.Pg_N_avg_72[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_72[%d] = %.6g;\n", i, params.ug_N_72[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_72[%d] = %.6g;\n", i, params.Vg_N_avg_72[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_72[%d] = %.6g;\n", i, params.Thetag_N_avg_72[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_72[%d] = %.6g;\n", i, params.vg_N_72[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_73[%d] = %.6g;\n", i, params.Pg_N_init_73[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_73[%d] = %.6g;\n", i, params.Pg_N_avg_73[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_73[%d] = %.6g;\n", i, params.ug_N_73[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_73[%d] = %.6g;\n", i, params.Vg_N_avg_73[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_73[%d] = %.6g;\n", i, params.Thetag_N_avg_73[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_73[%d] = %.6g;\n", i, params.vg_N_73[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_74[%d] = %.6g;\n", i, params.Pg_N_init_74[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_74[%d] = %.6g;\n", i, params.Pg_N_avg_74[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_74[%d] = %.6g;\n", i, params.ug_N_74[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_74[%d] = %.6g;\n", i, params.Vg_N_avg_74[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_74[%d] = %.6g;\n", i, params.Thetag_N_avg_74[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_74[%d] = %.6g;\n", i, params.vg_N_74[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_75[%d] = %.6g;\n", i, params.Pg_N_init_75[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_75[%d] = %.6g;\n", i, params.Pg_N_avg_75[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_75[%d] = %.6g;\n", i, params.ug_N_75[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_75[%d] = %.6g;\n", i, params.Vg_N_avg_75[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_75[%d] = %.6g;\n", i, params.Thetag_N_avg_75[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_75[%d] = %.6g;\n", i, params.vg_N_75[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_76[%d] = %.6g;\n", i, params.Pg_N_init_76[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_76[%d] = %.6g;\n", i, params.Pg_N_avg_76[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_76[%d] = %.6g;\n", i, params.ug_N_76[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_76[%d] = %.6g;\n", i, params.Vg_N_avg_76[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_76[%d] = %.6g;\n", i, params.Thetag_N_avg_76[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_76[%d] = %.6g;\n", i, params.vg_N_76[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_77[%d] = %.6g;\n", i, params.Pg_N_init_77[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_77[%d] = %.6g;\n", i, params.Pg_N_avg_77[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_77[%d] = %.6g;\n", i, params.ug_N_77[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_77[%d] = %.6g;\n", i, params.Vg_N_avg_77[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_77[%d] = %.6g;\n", i, params.Thetag_N_avg_77[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_77[%d] = %.6g;\n", i, params.vg_N_77[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_78[%d] = %.6g;\n", i, params.Pg_N_init_78[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_78[%d] = %.6g;\n", i, params.Pg_N_avg_78[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_78[%d] = %.6g;\n", i, params.ug_N_78[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_78[%d] = %.6g;\n", i, params.Vg_N_avg_78[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_78[%d] = %.6g;\n", i, params.Thetag_N_avg_78[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_78[%d] = %.6g;\n", i, params.vg_N_78[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_79[%d] = %.6g;\n", i, params.Pg_N_init_79[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_79[%d] = %.6g;\n", i, params.Pg_N_avg_79[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_79[%d] = %.6g;\n", i, params.ug_N_79[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_79[%d] = %.6g;\n", i, params.Vg_N_avg_79[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_79[%d] = %.6g;\n", i, params.Thetag_N_avg_79[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_79[%d] = %.6g;\n", i, params.vg_N_79[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_80[%d] = %.6g;\n", i, params.Pg_N_init_80[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_80[%d] = %.6g;\n", i, params.Pg_N_avg_80[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_80[%d] = %.6g;\n", i, params.ug_N_80[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_80[%d] = %.6g;\n", i, params.Vg_N_avg_80[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_80[%d] = %.6g;\n", i, params.Thetag_N_avg_80[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_80[%d] = %.6g;\n", i, params.vg_N_80[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_81[%d] = %.6g;\n", i, params.Pg_N_init_81[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_81[%d] = %.6g;\n", i, params.Pg_N_avg_81[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_81[%d] = %.6g;\n", i, params.ug_N_81[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_81[%d] = %.6g;\n", i, params.Vg_N_avg_81[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_81[%d] = %.6g;\n", i, params.Thetag_N_avg_81[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_81[%d] = %.6g;\n", i, params.vg_N_81[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_82[%d] = %.6g;\n", i, params.Pg_N_init_82[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_82[%d] = %.6g;\n", i, params.Pg_N_avg_82[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_82[%d] = %.6g;\n", i, params.ug_N_82[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_82[%d] = %.6g;\n", i, params.Vg_N_avg_82[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_82[%d] = %.6g;\n", i, params.Thetag_N_avg_82[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_82[%d] = %.6g;\n", i, params.vg_N_82[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_83[%d] = %.6g;\n", i, params.Pg_N_init_83[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_83[%d] = %.6g;\n", i, params.Pg_N_avg_83[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_83[%d] = %.6g;\n", i, params.ug_N_83[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_83[%d] = %.6g;\n", i, params.Vg_N_avg_83[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_83[%d] = %.6g;\n", i, params.Thetag_N_avg_83[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_83[%d] = %.6g;\n", i, params.vg_N_83[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_84[%d] = %.6g;\n", i, params.Pg_N_init_84[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_84[%d] = %.6g;\n", i, params.Pg_N_avg_84[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_84[%d] = %.6g;\n", i, params.ug_N_84[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_84[%d] = %.6g;\n", i, params.Vg_N_avg_84[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_84[%d] = %.6g;\n", i, params.Thetag_N_avg_84[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_84[%d] = %.6g;\n", i, params.vg_N_84[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_85[%d] = %.6g;\n", i, params.Pg_N_init_85[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_85[%d] = %.6g;\n", i, params.Pg_N_avg_85[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_85[%d] = %.6g;\n", i, params.ug_N_85[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_85[%d] = %.6g;\n", i, params.Vg_N_avg_85[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_85[%d] = %.6g;\n", i, params.Thetag_N_avg_85[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_85[%d] = %.6g;\n", i, params.vg_N_85[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_86[%d] = %.6g;\n", i, params.Pg_N_init_86[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_86[%d] = %.6g;\n", i, params.Pg_N_avg_86[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_86[%d] = %.6g;\n", i, params.ug_N_86[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_86[%d] = %.6g;\n", i, params.Vg_N_avg_86[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_86[%d] = %.6g;\n", i, params.Thetag_N_avg_86[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_86[%d] = %.6g;\n", i, params.vg_N_86[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_87[%d] = %.6g;\n", i, params.Pg_N_init_87[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_87[%d] = %.6g;\n", i, params.Pg_N_avg_87[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_87[%d] = %.6g;\n", i, params.ug_N_87[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_87[%d] = %.6g;\n", i, params.Vg_N_avg_87[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_87[%d] = %.6g;\n", i, params.Thetag_N_avg_87[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_87[%d] = %.6g;\n", i, params.vg_N_87[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_88[%d] = %.6g;\n", i, params.Pg_N_init_88[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_88[%d] = %.6g;\n", i, params.Pg_N_avg_88[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_88[%d] = %.6g;\n", i, params.ug_N_88[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_88[%d] = %.6g;\n", i, params.Vg_N_avg_88[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_88[%d] = %.6g;\n", i, params.Thetag_N_avg_88[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_88[%d] = %.6g;\n", i, params.vg_N_88[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_89[%d] = %.6g;\n", i, params.Pg_N_init_89[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_89[%d] = %.6g;\n", i, params.Pg_N_avg_89[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_89[%d] = %.6g;\n", i, params.ug_N_89[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_89[%d] = %.6g;\n", i, params.Vg_N_avg_89[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_89[%d] = %.6g;\n", i, params.Thetag_N_avg_89[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_89[%d] = %.6g;\n", i, params.vg_N_89[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_90[%d] = %.6g;\n", i, params.Pg_N_init_90[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_90[%d] = %.6g;\n", i, params.Pg_N_avg_90[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_90[%d] = %.6g;\n", i, params.ug_N_90[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_90[%d] = %.6g;\n", i, params.Vg_N_avg_90[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_90[%d] = %.6g;\n", i, params.Thetag_N_avg_90[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_90[%d] = %.6g;\n", i, params.vg_N_90[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_91[%d] = %.6g;\n", i, params.Pg_N_init_91[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_91[%d] = %.6g;\n", i, params.Pg_N_avg_91[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_91[%d] = %.6g;\n", i, params.ug_N_91[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_91[%d] = %.6g;\n", i, params.Vg_N_avg_91[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_91[%d] = %.6g;\n", i, params.Thetag_N_avg_91[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_91[%d] = %.6g;\n", i, params.vg_N_91[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_92[%d] = %.6g;\n", i, params.Pg_N_init_92[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_92[%d] = %.6g;\n", i, params.Pg_N_avg_92[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_92[%d] = %.6g;\n", i, params.ug_N_92[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_92[%d] = %.6g;\n", i, params.Vg_N_avg_92[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_92[%d] = %.6g;\n", i, params.Thetag_N_avg_92[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_92[%d] = %.6g;\n", i, params.vg_N_92[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_93[%d] = %.6g;\n", i, params.Pg_N_init_93[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_93[%d] = %.6g;\n", i, params.Pg_N_avg_93[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_93[%d] = %.6g;\n", i, params.ug_N_93[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_93[%d] = %.6g;\n", i, params.Vg_N_avg_93[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_93[%d] = %.6g;\n", i, params.Thetag_N_avg_93[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_93[%d] = %.6g;\n", i, params.vg_N_93[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_94[%d] = %.6g;\n", i, params.Pg_N_init_94[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_94[%d] = %.6g;\n", i, params.Pg_N_avg_94[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_94[%d] = %.6g;\n", i, params.ug_N_94[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_94[%d] = %.6g;\n", i, params.Vg_N_avg_94[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_94[%d] = %.6g;\n", i, params.Thetag_N_avg_94[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_94[%d] = %.6g;\n", i, params.vg_N_94[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_95[%d] = %.6g;\n", i, params.Pg_N_init_95[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_95[%d] = %.6g;\n", i, params.Pg_N_avg_95[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_95[%d] = %.6g;\n", i, params.ug_N_95[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_95[%d] = %.6g;\n", i, params.Vg_N_avg_95[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_95[%d] = %.6g;\n", i, params.Thetag_N_avg_95[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_95[%d] = %.6g;\n", i, params.vg_N_95[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_96[%d] = %.6g;\n", i, params.Pg_N_init_96[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_96[%d] = %.6g;\n", i, params.Pg_N_avg_96[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_96[%d] = %.6g;\n", i, params.ug_N_96[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_96[%d] = %.6g;\n", i, params.Vg_N_avg_96[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_96[%d] = %.6g;\n", i, params.Thetag_N_avg_96[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_96[%d] = %.6g;\n", i, params.vg_N_96[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_97[%d] = %.6g;\n", i, params.Pg_N_init_97[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_97[%d] = %.6g;\n", i, params.Pg_N_avg_97[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_97[%d] = %.6g;\n", i, params.ug_N_97[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_97[%d] = %.6g;\n", i, params.Vg_N_avg_97[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_97[%d] = %.6g;\n", i, params.Thetag_N_avg_97[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_97[%d] = %.6g;\n", i, params.vg_N_97[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_98[%d] = %.6g;\n", i, params.Pg_N_init_98[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_98[%d] = %.6g;\n", i, params.Pg_N_avg_98[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_98[%d] = %.6g;\n", i, params.ug_N_98[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_98[%d] = %.6g;\n", i, params.Vg_N_avg_98[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_98[%d] = %.6g;\n", i, params.Thetag_N_avg_98[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_98[%d] = %.6g;\n", i, params.vg_N_98[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_99[%d] = %.6g;\n", i, params.Pg_N_init_99[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_99[%d] = %.6g;\n", i, params.Pg_N_avg_99[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_99[%d] = %.6g;\n", i, params.ug_N_99[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_99[%d] = %.6g;\n", i, params.Vg_N_avg_99[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_99[%d] = %.6g;\n", i, params.Thetag_N_avg_99[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_99[%d] = %.6g;\n", i, params.vg_N_99[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_100[%d] = %.6g;\n", i, params.Pg_N_init_100[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_100[%d] = %.6g;\n", i, params.Pg_N_avg_100[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_100[%d] = %.6g;\n", i, params.ug_N_100[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_100[%d] = %.6g;\n", i, params.Vg_N_avg_100[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_100[%d] = %.6g;\n", i, params.Thetag_N_avg_100[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_100[%d] = %.6g;\n", i, params.vg_N_100[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_init_101[%d] = %.6g;\n", i, params.Pg_N_init_101[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Pg_N_avg_101[%d] = %.6g;\n", i, params.Pg_N_avg_101[i]);
    for (i = 0; i < 1; i++)
      printf("  params.ug_N_101[%d] = %.6g;\n", i, params.ug_N_101[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Vg_N_avg_101[%d] = %.6g;\n", i, params.Vg_N_avg_101[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Thetag_N_avg_101[%d] = %.6g;\n", i, params.Thetag_N_avg_101[i]);
    for (i = 0; i < 1; i++)
      printf("  params.vg_N_101[%d] = %.6g;\n", i, params.vg_N_101[i]);
    for (i = 0; i < 1; i++)
      printf("  params.contNum[%d] = %.6g;\n", i, params.contNum[i]);
    for (i = 0; i < 1; i++)
      printf("  params.PgMin[%d] = %.6g;\n", i, params.PgMin[i]);
    for (i = 0; i < 1; i++)
      printf("  params.PgMax[%d] = %.6g;\n", i, params.PgMax[i]);
  }
  /* Perform the actual solve in here. */
  steps = solve();
  /* For profiling purposes, allow extra silent solves if desired. */
  settings.verbose = 0;
  for (i = 0; i < extra_solves; i++)
    solve();
  /* Update the status variables. */
  plhs[1] = mxCreateStructArray(1, dims1x1of1, 4, status_names);
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[1], 0, "optval", xm);
  *mxGetPr(xm) = work.optval;
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[1], 0, "gap", xm);
  *mxGetPr(xm) = work.gap;
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[1], 0, "steps", xm);
  *mxGetPr(xm) = steps;
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[1], 0, "converged", xm);
  *mxGetPr(xm) = work.converged;
  /* Extract variable values. */
  plhs[0] = mxCreateStructArray(1, dims1x1of1, num_var_names, var_names);
  /* Create cell arrays for indexed variables. */
  dims[0] = 101;
  cell = mxCreateCellArray(1, dims);
  mxSetField(plhs[0], 0, "Thetag", cell);
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Pg", xm);
  dest = mxGetPr(xm);
  src = vars.Pg;
  for (i = 0; i < 1; i++) {
    *dest++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_1", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 0, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_1;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_2", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 1, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_2;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_3", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 2, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_3;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_4", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 3, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_4;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_5", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 4, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_5;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_6", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 5, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_6;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_7", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 6, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_7;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_8", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 7, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_8;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_9", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 8, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_9;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_10", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 9, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_10;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_11", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 10, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_11;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_12", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 11, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_12;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_13", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 12, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_13;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_14", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 13, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_14;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_15", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 14, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_15;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_16", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 15, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_16;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_17", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 16, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_17;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_18", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 17, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_18;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_19", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 18, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_19;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_20", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 19, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_20;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_21", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 20, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_21;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_22", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 21, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_22;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_23", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 22, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_23;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_24", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 23, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_24;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_25", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 24, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_25;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_26", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 25, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_26;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_27", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 26, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_27;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_28", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 27, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_28;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_29", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 28, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_29;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_30", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 29, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_30;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_31", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 30, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_31;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_32", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 31, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_32;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_33", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 32, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_33;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_34", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 33, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_34;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_35", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 34, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_35;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_36", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 35, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_36;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_37", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 36, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_37;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_38", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 37, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_38;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_39", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 38, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_39;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_40", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 39, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_40;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_41", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 40, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_41;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_42", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 41, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_42;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_43", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 42, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_43;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_44", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 43, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_44;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_45", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 44, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_45;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_46", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 45, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_46;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_47", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 46, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_47;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_48", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 47, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_48;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_49", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 48, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_49;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_50", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 49, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_50;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_51", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 50, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_51;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_52", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 51, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_52;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_53", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 52, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_53;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_54", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 53, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_54;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_55", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 54, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_55;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_56", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 55, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_56;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_57", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 56, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_57;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_58", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 57, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_58;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_59", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 58, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_59;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_60", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 59, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_60;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_61", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 60, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_61;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_62", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 61, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_62;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_63", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 62, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_63;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_64", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 63, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_64;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_65", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 64, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_65;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_66", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 65, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_66;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_67", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 66, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_67;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_68", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 67, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_68;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_69", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 68, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_69;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_70", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 69, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_70;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_71", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 70, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_71;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_72", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 71, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_72;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_73", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 72, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_73;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_74", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 73, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_74;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_75", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 74, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_75;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_76", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 75, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_76;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_77", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 76, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_77;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_78", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 77, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_78;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_79", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 78, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_79;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_80", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 79, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_80;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_81", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 80, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_81;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_82", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 81, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_82;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_83", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 82, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_83;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_84", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 83, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_84;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_85", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 84, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_85;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_86", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 85, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_86;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_87", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 86, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_87;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_88", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 87, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_88;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_89", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 88, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_89;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_90", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 89, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_90;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_91", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 90, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_91;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_92", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 91, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_92;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_93", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 92, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_93;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_94", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 93, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_94;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_95", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 94, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_95;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_96", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 95, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_96;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_97", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 96, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_97;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_98", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 97, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_98;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_99", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 98, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_99;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_100", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 99, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_100;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "Thetag_101", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "Thetag");
  mxSetCell(cell, 100, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.Thetag_101;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
}
