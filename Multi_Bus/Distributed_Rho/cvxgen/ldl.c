/* Produced by CVXGEN, 2017-07-25 19:37:09 -0400.  */
/* CVXGEN is Copyright (C) 2006-2017 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2017 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: ldl.c. */
/* Description: Basic test harness for solver.c. */
#include "solver.h"
/* Be sure to place ldl_solve first, so storage schemes are defined by it. */
void ldl_solve(double *target, double *var) {
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
  work.v[103] = target[104];
  work.v[104] = target[105];
  work.v[105] = target[106];
  work.v[106] = target[107];
  work.v[107] = target[108];
  work.v[108] = target[109];
  work.v[109] = target[110];
  work.v[110] = target[111];
  work.v[111] = target[112];
  work.v[112] = target[113];
  work.v[113] = target[114];
  work.v[114] = target[115];
  work.v[115] = target[116];
  work.v[116] = target[117];
  work.v[117] = target[118];
  work.v[118] = target[119];
  work.v[119] = target[120];
  work.v[120] = target[121];
  work.v[121] = target[122];
  work.v[122] = target[123];
  work.v[123] = target[124];
  work.v[124] = target[125];
  work.v[125] = target[126];
  work.v[126] = target[127];
  work.v[127] = target[128];
  work.v[128] = target[129];
  work.v[129] = target[130];
  work.v[130] = target[131];
  work.v[131] = target[132];
  work.v[132] = target[133];
  work.v[133] = target[134];
  work.v[134] = target[135];
  work.v[135] = target[136];
  work.v[136] = target[137];
  work.v[137] = target[138];
  work.v[138] = target[139];
  work.v[139] = target[140];
  work.v[140] = target[141];
  work.v[141] = target[142];
  work.v[142] = target[143];
  work.v[143] = target[144];
  work.v[144] = target[145];
  work.v[145] = target[146];
  work.v[146] = target[147];
  work.v[147] = target[148];
  work.v[148] = target[149];
  work.v[149] = target[150];
  work.v[150] = target[151];
  work.v[151] = target[152];
  work.v[152] = target[153];
  work.v[153] = target[154];
  work.v[154] = target[155];
  work.v[155] = target[156];
  work.v[156] = target[157];
  work.v[157] = target[158];
  work.v[158] = target[159];
  work.v[159] = target[160];
  work.v[160] = target[161];
  work.v[161] = target[162];
  work.v[162] = target[163];
  work.v[163] = target[164];
  work.v[164] = target[165];
  work.v[165] = target[166];
  work.v[166] = target[167];
  work.v[167] = target[168];
  work.v[168] = target[169];
  work.v[169] = target[170];
  work.v[170] = target[171];
  work.v[171] = target[172];
  work.v[172] = target[173];
  work.v[173] = target[174];
  work.v[174] = target[175];
  work.v[175] = target[176];
  work.v[176] = target[177];
  work.v[177] = target[178];
  work.v[178] = target[179];
  work.v[179] = target[180];
  work.v[180] = target[181];
  work.v[181] = target[182];
  work.v[182] = target[183];
  work.v[183] = target[184];
  work.v[184] = target[185];
  work.v[185] = target[186];
  work.v[186] = target[187];
  work.v[187] = target[188];
  work.v[188] = target[189];
  work.v[189] = target[190];
  work.v[190] = target[191];
  work.v[191] = target[192];
  work.v[192] = target[193];
  work.v[193] = target[194];
  work.v[194] = target[195];
  work.v[195] = target[196];
  work.v[196] = target[197];
  work.v[197] = target[198];
  work.v[198] = target[199];
  work.v[199] = target[200];
  work.v[200] = target[201];
  work.v[201] = target[202];
  work.v[202] = target[203];
  work.v[203] = target[204]-work.L[0]*work.v[201];
  work.v[204] = target[0]-work.L[1]*work.v[203];
  work.v[205] = target[205]-work.L[2]*work.v[202]-work.L[3]*work.v[204];
  /* Diagonal scaling. Assume correctness of work.d_inv. */
  for (i = 0; i < 206; i++)
    work.v[i] *= work.d_inv[i];
  /* Back substitution */
  work.v[204] -= work.L[3]*work.v[205];
  work.v[203] -= work.L[1]*work.v[204];
  work.v[202] -= work.L[2]*work.v[205];
  work.v[201] -= work.L[0]*work.v[203];
  /* Unpermute the result, from v to var. */
  var[0] = work.v[204];
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
  var[105] = work.v[104];
  var[106] = work.v[105];
  var[107] = work.v[106];
  var[108] = work.v[107];
  var[109] = work.v[108];
  var[110] = work.v[109];
  var[111] = work.v[110];
  var[112] = work.v[111];
  var[113] = work.v[112];
  var[114] = work.v[113];
  var[115] = work.v[114];
  var[116] = work.v[115];
  var[117] = work.v[116];
  var[118] = work.v[117];
  var[119] = work.v[118];
  var[120] = work.v[119];
  var[121] = work.v[120];
  var[122] = work.v[121];
  var[123] = work.v[122];
  var[124] = work.v[123];
  var[125] = work.v[124];
  var[126] = work.v[125];
  var[127] = work.v[126];
  var[128] = work.v[127];
  var[129] = work.v[128];
  var[130] = work.v[129];
  var[131] = work.v[130];
  var[132] = work.v[131];
  var[133] = work.v[132];
  var[134] = work.v[133];
  var[135] = work.v[134];
  var[136] = work.v[135];
  var[137] = work.v[136];
  var[138] = work.v[137];
  var[139] = work.v[138];
  var[140] = work.v[139];
  var[141] = work.v[140];
  var[142] = work.v[141];
  var[143] = work.v[142];
  var[144] = work.v[143];
  var[145] = work.v[144];
  var[146] = work.v[145];
  var[147] = work.v[146];
  var[148] = work.v[147];
  var[149] = work.v[148];
  var[150] = work.v[149];
  var[151] = work.v[150];
  var[152] = work.v[151];
  var[153] = work.v[152];
  var[154] = work.v[153];
  var[155] = work.v[154];
  var[156] = work.v[155];
  var[157] = work.v[156];
  var[158] = work.v[157];
  var[159] = work.v[158];
  var[160] = work.v[159];
  var[161] = work.v[160];
  var[162] = work.v[161];
  var[163] = work.v[162];
  var[164] = work.v[163];
  var[165] = work.v[164];
  var[166] = work.v[165];
  var[167] = work.v[166];
  var[168] = work.v[167];
  var[169] = work.v[168];
  var[170] = work.v[169];
  var[171] = work.v[170];
  var[172] = work.v[171];
  var[173] = work.v[172];
  var[174] = work.v[173];
  var[175] = work.v[174];
  var[176] = work.v[175];
  var[177] = work.v[176];
  var[178] = work.v[177];
  var[179] = work.v[178];
  var[180] = work.v[179];
  var[181] = work.v[180];
  var[182] = work.v[181];
  var[183] = work.v[182];
  var[184] = work.v[183];
  var[185] = work.v[184];
  var[186] = work.v[185];
  var[187] = work.v[186];
  var[188] = work.v[187];
  var[189] = work.v[188];
  var[190] = work.v[189];
  var[191] = work.v[190];
  var[192] = work.v[191];
  var[193] = work.v[192];
  var[194] = work.v[193];
  var[195] = work.v[194];
  var[196] = work.v[195];
  var[197] = work.v[196];
  var[198] = work.v[197];
  var[199] = work.v[198];
  var[200] = work.v[199];
  var[201] = work.v[200];
  var[202] = work.v[201];
  var[203] = work.v[202];
  var[204] = work.v[203];
  var[205] = work.v[205];
#ifndef ZERO_LIBRARY_MODE
  if (settings.debug) {
    printf("Squared norm for solution is %.8g.\n", check_residual(target, var));
  }
#endif
}
void ldl_factor(void) {
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
  work.v[102] = work.KKT[102];
  work.d[102] = work.v[102];
  if (work.d[102] < 0)
    work.d[102] = settings.kkt_reg;
  else
    work.d[102] += settings.kkt_reg;
  work.d_inv[102] = 1/work.d[102];
  work.v[103] = work.KKT[103];
  work.d[103] = work.v[103];
  if (work.d[103] < 0)
    work.d[103] = settings.kkt_reg;
  else
    work.d[103] += settings.kkt_reg;
  work.d_inv[103] = 1/work.d[103];
  work.v[104] = work.KKT[104];
  work.d[104] = work.v[104];
  if (work.d[104] < 0)
    work.d[104] = settings.kkt_reg;
  else
    work.d[104] += settings.kkt_reg;
  work.d_inv[104] = 1/work.d[104];
  work.v[105] = work.KKT[105];
  work.d[105] = work.v[105];
  if (work.d[105] < 0)
    work.d[105] = settings.kkt_reg;
  else
    work.d[105] += settings.kkt_reg;
  work.d_inv[105] = 1/work.d[105];
  work.v[106] = work.KKT[106];
  work.d[106] = work.v[106];
  if (work.d[106] < 0)
    work.d[106] = settings.kkt_reg;
  else
    work.d[106] += settings.kkt_reg;
  work.d_inv[106] = 1/work.d[106];
  work.v[107] = work.KKT[107];
  work.d[107] = work.v[107];
  if (work.d[107] < 0)
    work.d[107] = settings.kkt_reg;
  else
    work.d[107] += settings.kkt_reg;
  work.d_inv[107] = 1/work.d[107];
  work.v[108] = work.KKT[108];
  work.d[108] = work.v[108];
  if (work.d[108] < 0)
    work.d[108] = settings.kkt_reg;
  else
    work.d[108] += settings.kkt_reg;
  work.d_inv[108] = 1/work.d[108];
  work.v[109] = work.KKT[109];
  work.d[109] = work.v[109];
  if (work.d[109] < 0)
    work.d[109] = settings.kkt_reg;
  else
    work.d[109] += settings.kkt_reg;
  work.d_inv[109] = 1/work.d[109];
  work.v[110] = work.KKT[110];
  work.d[110] = work.v[110];
  if (work.d[110] < 0)
    work.d[110] = settings.kkt_reg;
  else
    work.d[110] += settings.kkt_reg;
  work.d_inv[110] = 1/work.d[110];
  work.v[111] = work.KKT[111];
  work.d[111] = work.v[111];
  if (work.d[111] < 0)
    work.d[111] = settings.kkt_reg;
  else
    work.d[111] += settings.kkt_reg;
  work.d_inv[111] = 1/work.d[111];
  work.v[112] = work.KKT[112];
  work.d[112] = work.v[112];
  if (work.d[112] < 0)
    work.d[112] = settings.kkt_reg;
  else
    work.d[112] += settings.kkt_reg;
  work.d_inv[112] = 1/work.d[112];
  work.v[113] = work.KKT[113];
  work.d[113] = work.v[113];
  if (work.d[113] < 0)
    work.d[113] = settings.kkt_reg;
  else
    work.d[113] += settings.kkt_reg;
  work.d_inv[113] = 1/work.d[113];
  work.v[114] = work.KKT[114];
  work.d[114] = work.v[114];
  if (work.d[114] < 0)
    work.d[114] = settings.kkt_reg;
  else
    work.d[114] += settings.kkt_reg;
  work.d_inv[114] = 1/work.d[114];
  work.v[115] = work.KKT[115];
  work.d[115] = work.v[115];
  if (work.d[115] < 0)
    work.d[115] = settings.kkt_reg;
  else
    work.d[115] += settings.kkt_reg;
  work.d_inv[115] = 1/work.d[115];
  work.v[116] = work.KKT[116];
  work.d[116] = work.v[116];
  if (work.d[116] < 0)
    work.d[116] = settings.kkt_reg;
  else
    work.d[116] += settings.kkt_reg;
  work.d_inv[116] = 1/work.d[116];
  work.v[117] = work.KKT[117];
  work.d[117] = work.v[117];
  if (work.d[117] < 0)
    work.d[117] = settings.kkt_reg;
  else
    work.d[117] += settings.kkt_reg;
  work.d_inv[117] = 1/work.d[117];
  work.v[118] = work.KKT[118];
  work.d[118] = work.v[118];
  if (work.d[118] < 0)
    work.d[118] = settings.kkt_reg;
  else
    work.d[118] += settings.kkt_reg;
  work.d_inv[118] = 1/work.d[118];
  work.v[119] = work.KKT[119];
  work.d[119] = work.v[119];
  if (work.d[119] < 0)
    work.d[119] = settings.kkt_reg;
  else
    work.d[119] += settings.kkt_reg;
  work.d_inv[119] = 1/work.d[119];
  work.v[120] = work.KKT[120];
  work.d[120] = work.v[120];
  if (work.d[120] < 0)
    work.d[120] = settings.kkt_reg;
  else
    work.d[120] += settings.kkt_reg;
  work.d_inv[120] = 1/work.d[120];
  work.v[121] = work.KKT[121];
  work.d[121] = work.v[121];
  if (work.d[121] < 0)
    work.d[121] = settings.kkt_reg;
  else
    work.d[121] += settings.kkt_reg;
  work.d_inv[121] = 1/work.d[121];
  work.v[122] = work.KKT[122];
  work.d[122] = work.v[122];
  if (work.d[122] < 0)
    work.d[122] = settings.kkt_reg;
  else
    work.d[122] += settings.kkt_reg;
  work.d_inv[122] = 1/work.d[122];
  work.v[123] = work.KKT[123];
  work.d[123] = work.v[123];
  if (work.d[123] < 0)
    work.d[123] = settings.kkt_reg;
  else
    work.d[123] += settings.kkt_reg;
  work.d_inv[123] = 1/work.d[123];
  work.v[124] = work.KKT[124];
  work.d[124] = work.v[124];
  if (work.d[124] < 0)
    work.d[124] = settings.kkt_reg;
  else
    work.d[124] += settings.kkt_reg;
  work.d_inv[124] = 1/work.d[124];
  work.v[125] = work.KKT[125];
  work.d[125] = work.v[125];
  if (work.d[125] < 0)
    work.d[125] = settings.kkt_reg;
  else
    work.d[125] += settings.kkt_reg;
  work.d_inv[125] = 1/work.d[125];
  work.v[126] = work.KKT[126];
  work.d[126] = work.v[126];
  if (work.d[126] < 0)
    work.d[126] = settings.kkt_reg;
  else
    work.d[126] += settings.kkt_reg;
  work.d_inv[126] = 1/work.d[126];
  work.v[127] = work.KKT[127];
  work.d[127] = work.v[127];
  if (work.d[127] < 0)
    work.d[127] = settings.kkt_reg;
  else
    work.d[127] += settings.kkt_reg;
  work.d_inv[127] = 1/work.d[127];
  work.v[128] = work.KKT[128];
  work.d[128] = work.v[128];
  if (work.d[128] < 0)
    work.d[128] = settings.kkt_reg;
  else
    work.d[128] += settings.kkt_reg;
  work.d_inv[128] = 1/work.d[128];
  work.v[129] = work.KKT[129];
  work.d[129] = work.v[129];
  if (work.d[129] < 0)
    work.d[129] = settings.kkt_reg;
  else
    work.d[129] += settings.kkt_reg;
  work.d_inv[129] = 1/work.d[129];
  work.v[130] = work.KKT[130];
  work.d[130] = work.v[130];
  if (work.d[130] < 0)
    work.d[130] = settings.kkt_reg;
  else
    work.d[130] += settings.kkt_reg;
  work.d_inv[130] = 1/work.d[130];
  work.v[131] = work.KKT[131];
  work.d[131] = work.v[131];
  if (work.d[131] < 0)
    work.d[131] = settings.kkt_reg;
  else
    work.d[131] += settings.kkt_reg;
  work.d_inv[131] = 1/work.d[131];
  work.v[132] = work.KKT[132];
  work.d[132] = work.v[132];
  if (work.d[132] < 0)
    work.d[132] = settings.kkt_reg;
  else
    work.d[132] += settings.kkt_reg;
  work.d_inv[132] = 1/work.d[132];
  work.v[133] = work.KKT[133];
  work.d[133] = work.v[133];
  if (work.d[133] < 0)
    work.d[133] = settings.kkt_reg;
  else
    work.d[133] += settings.kkt_reg;
  work.d_inv[133] = 1/work.d[133];
  work.v[134] = work.KKT[134];
  work.d[134] = work.v[134];
  if (work.d[134] < 0)
    work.d[134] = settings.kkt_reg;
  else
    work.d[134] += settings.kkt_reg;
  work.d_inv[134] = 1/work.d[134];
  work.v[135] = work.KKT[135];
  work.d[135] = work.v[135];
  if (work.d[135] < 0)
    work.d[135] = settings.kkt_reg;
  else
    work.d[135] += settings.kkt_reg;
  work.d_inv[135] = 1/work.d[135];
  work.v[136] = work.KKT[136];
  work.d[136] = work.v[136];
  if (work.d[136] < 0)
    work.d[136] = settings.kkt_reg;
  else
    work.d[136] += settings.kkt_reg;
  work.d_inv[136] = 1/work.d[136];
  work.v[137] = work.KKT[137];
  work.d[137] = work.v[137];
  if (work.d[137] < 0)
    work.d[137] = settings.kkt_reg;
  else
    work.d[137] += settings.kkt_reg;
  work.d_inv[137] = 1/work.d[137];
  work.v[138] = work.KKT[138];
  work.d[138] = work.v[138];
  if (work.d[138] < 0)
    work.d[138] = settings.kkt_reg;
  else
    work.d[138] += settings.kkt_reg;
  work.d_inv[138] = 1/work.d[138];
  work.v[139] = work.KKT[139];
  work.d[139] = work.v[139];
  if (work.d[139] < 0)
    work.d[139] = settings.kkt_reg;
  else
    work.d[139] += settings.kkt_reg;
  work.d_inv[139] = 1/work.d[139];
  work.v[140] = work.KKT[140];
  work.d[140] = work.v[140];
  if (work.d[140] < 0)
    work.d[140] = settings.kkt_reg;
  else
    work.d[140] += settings.kkt_reg;
  work.d_inv[140] = 1/work.d[140];
  work.v[141] = work.KKT[141];
  work.d[141] = work.v[141];
  if (work.d[141] < 0)
    work.d[141] = settings.kkt_reg;
  else
    work.d[141] += settings.kkt_reg;
  work.d_inv[141] = 1/work.d[141];
  work.v[142] = work.KKT[142];
  work.d[142] = work.v[142];
  if (work.d[142] < 0)
    work.d[142] = settings.kkt_reg;
  else
    work.d[142] += settings.kkt_reg;
  work.d_inv[142] = 1/work.d[142];
  work.v[143] = work.KKT[143];
  work.d[143] = work.v[143];
  if (work.d[143] < 0)
    work.d[143] = settings.kkt_reg;
  else
    work.d[143] += settings.kkt_reg;
  work.d_inv[143] = 1/work.d[143];
  work.v[144] = work.KKT[144];
  work.d[144] = work.v[144];
  if (work.d[144] < 0)
    work.d[144] = settings.kkt_reg;
  else
    work.d[144] += settings.kkt_reg;
  work.d_inv[144] = 1/work.d[144];
  work.v[145] = work.KKT[145];
  work.d[145] = work.v[145];
  if (work.d[145] < 0)
    work.d[145] = settings.kkt_reg;
  else
    work.d[145] += settings.kkt_reg;
  work.d_inv[145] = 1/work.d[145];
  work.v[146] = work.KKT[146];
  work.d[146] = work.v[146];
  if (work.d[146] < 0)
    work.d[146] = settings.kkt_reg;
  else
    work.d[146] += settings.kkt_reg;
  work.d_inv[146] = 1/work.d[146];
  work.v[147] = work.KKT[147];
  work.d[147] = work.v[147];
  if (work.d[147] < 0)
    work.d[147] = settings.kkt_reg;
  else
    work.d[147] += settings.kkt_reg;
  work.d_inv[147] = 1/work.d[147];
  work.v[148] = work.KKT[148];
  work.d[148] = work.v[148];
  if (work.d[148] < 0)
    work.d[148] = settings.kkt_reg;
  else
    work.d[148] += settings.kkt_reg;
  work.d_inv[148] = 1/work.d[148];
  work.v[149] = work.KKT[149];
  work.d[149] = work.v[149];
  if (work.d[149] < 0)
    work.d[149] = settings.kkt_reg;
  else
    work.d[149] += settings.kkt_reg;
  work.d_inv[149] = 1/work.d[149];
  work.v[150] = work.KKT[150];
  work.d[150] = work.v[150];
  if (work.d[150] < 0)
    work.d[150] = settings.kkt_reg;
  else
    work.d[150] += settings.kkt_reg;
  work.d_inv[150] = 1/work.d[150];
  work.v[151] = work.KKT[151];
  work.d[151] = work.v[151];
  if (work.d[151] < 0)
    work.d[151] = settings.kkt_reg;
  else
    work.d[151] += settings.kkt_reg;
  work.d_inv[151] = 1/work.d[151];
  work.v[152] = work.KKT[152];
  work.d[152] = work.v[152];
  if (work.d[152] < 0)
    work.d[152] = settings.kkt_reg;
  else
    work.d[152] += settings.kkt_reg;
  work.d_inv[152] = 1/work.d[152];
  work.v[153] = work.KKT[153];
  work.d[153] = work.v[153];
  if (work.d[153] < 0)
    work.d[153] = settings.kkt_reg;
  else
    work.d[153] += settings.kkt_reg;
  work.d_inv[153] = 1/work.d[153];
  work.v[154] = work.KKT[154];
  work.d[154] = work.v[154];
  if (work.d[154] < 0)
    work.d[154] = settings.kkt_reg;
  else
    work.d[154] += settings.kkt_reg;
  work.d_inv[154] = 1/work.d[154];
  work.v[155] = work.KKT[155];
  work.d[155] = work.v[155];
  if (work.d[155] < 0)
    work.d[155] = settings.kkt_reg;
  else
    work.d[155] += settings.kkt_reg;
  work.d_inv[155] = 1/work.d[155];
  work.v[156] = work.KKT[156];
  work.d[156] = work.v[156];
  if (work.d[156] < 0)
    work.d[156] = settings.kkt_reg;
  else
    work.d[156] += settings.kkt_reg;
  work.d_inv[156] = 1/work.d[156];
  work.v[157] = work.KKT[157];
  work.d[157] = work.v[157];
  if (work.d[157] < 0)
    work.d[157] = settings.kkt_reg;
  else
    work.d[157] += settings.kkt_reg;
  work.d_inv[157] = 1/work.d[157];
  work.v[158] = work.KKT[158];
  work.d[158] = work.v[158];
  if (work.d[158] < 0)
    work.d[158] = settings.kkt_reg;
  else
    work.d[158] += settings.kkt_reg;
  work.d_inv[158] = 1/work.d[158];
  work.v[159] = work.KKT[159];
  work.d[159] = work.v[159];
  if (work.d[159] < 0)
    work.d[159] = settings.kkt_reg;
  else
    work.d[159] += settings.kkt_reg;
  work.d_inv[159] = 1/work.d[159];
  work.v[160] = work.KKT[160];
  work.d[160] = work.v[160];
  if (work.d[160] < 0)
    work.d[160] = settings.kkt_reg;
  else
    work.d[160] += settings.kkt_reg;
  work.d_inv[160] = 1/work.d[160];
  work.v[161] = work.KKT[161];
  work.d[161] = work.v[161];
  if (work.d[161] < 0)
    work.d[161] = settings.kkt_reg;
  else
    work.d[161] += settings.kkt_reg;
  work.d_inv[161] = 1/work.d[161];
  work.v[162] = work.KKT[162];
  work.d[162] = work.v[162];
  if (work.d[162] < 0)
    work.d[162] = settings.kkt_reg;
  else
    work.d[162] += settings.kkt_reg;
  work.d_inv[162] = 1/work.d[162];
  work.v[163] = work.KKT[163];
  work.d[163] = work.v[163];
  if (work.d[163] < 0)
    work.d[163] = settings.kkt_reg;
  else
    work.d[163] += settings.kkt_reg;
  work.d_inv[163] = 1/work.d[163];
  work.v[164] = work.KKT[164];
  work.d[164] = work.v[164];
  if (work.d[164] < 0)
    work.d[164] = settings.kkt_reg;
  else
    work.d[164] += settings.kkt_reg;
  work.d_inv[164] = 1/work.d[164];
  work.v[165] = work.KKT[165];
  work.d[165] = work.v[165];
  if (work.d[165] < 0)
    work.d[165] = settings.kkt_reg;
  else
    work.d[165] += settings.kkt_reg;
  work.d_inv[165] = 1/work.d[165];
  work.v[166] = work.KKT[166];
  work.d[166] = work.v[166];
  if (work.d[166] < 0)
    work.d[166] = settings.kkt_reg;
  else
    work.d[166] += settings.kkt_reg;
  work.d_inv[166] = 1/work.d[166];
  work.v[167] = work.KKT[167];
  work.d[167] = work.v[167];
  if (work.d[167] < 0)
    work.d[167] = settings.kkt_reg;
  else
    work.d[167] += settings.kkt_reg;
  work.d_inv[167] = 1/work.d[167];
  work.v[168] = work.KKT[168];
  work.d[168] = work.v[168];
  if (work.d[168] < 0)
    work.d[168] = settings.kkt_reg;
  else
    work.d[168] += settings.kkt_reg;
  work.d_inv[168] = 1/work.d[168];
  work.v[169] = work.KKT[169];
  work.d[169] = work.v[169];
  if (work.d[169] < 0)
    work.d[169] = settings.kkt_reg;
  else
    work.d[169] += settings.kkt_reg;
  work.d_inv[169] = 1/work.d[169];
  work.v[170] = work.KKT[170];
  work.d[170] = work.v[170];
  if (work.d[170] < 0)
    work.d[170] = settings.kkt_reg;
  else
    work.d[170] += settings.kkt_reg;
  work.d_inv[170] = 1/work.d[170];
  work.v[171] = work.KKT[171];
  work.d[171] = work.v[171];
  if (work.d[171] < 0)
    work.d[171] = settings.kkt_reg;
  else
    work.d[171] += settings.kkt_reg;
  work.d_inv[171] = 1/work.d[171];
  work.v[172] = work.KKT[172];
  work.d[172] = work.v[172];
  if (work.d[172] < 0)
    work.d[172] = settings.kkt_reg;
  else
    work.d[172] += settings.kkt_reg;
  work.d_inv[172] = 1/work.d[172];
  work.v[173] = work.KKT[173];
  work.d[173] = work.v[173];
  if (work.d[173] < 0)
    work.d[173] = settings.kkt_reg;
  else
    work.d[173] += settings.kkt_reg;
  work.d_inv[173] = 1/work.d[173];
  work.v[174] = work.KKT[174];
  work.d[174] = work.v[174];
  if (work.d[174] < 0)
    work.d[174] = settings.kkt_reg;
  else
    work.d[174] += settings.kkt_reg;
  work.d_inv[174] = 1/work.d[174];
  work.v[175] = work.KKT[175];
  work.d[175] = work.v[175];
  if (work.d[175] < 0)
    work.d[175] = settings.kkt_reg;
  else
    work.d[175] += settings.kkt_reg;
  work.d_inv[175] = 1/work.d[175];
  work.v[176] = work.KKT[176];
  work.d[176] = work.v[176];
  if (work.d[176] < 0)
    work.d[176] = settings.kkt_reg;
  else
    work.d[176] += settings.kkt_reg;
  work.d_inv[176] = 1/work.d[176];
  work.v[177] = work.KKT[177];
  work.d[177] = work.v[177];
  if (work.d[177] < 0)
    work.d[177] = settings.kkt_reg;
  else
    work.d[177] += settings.kkt_reg;
  work.d_inv[177] = 1/work.d[177];
  work.v[178] = work.KKT[178];
  work.d[178] = work.v[178];
  if (work.d[178] < 0)
    work.d[178] = settings.kkt_reg;
  else
    work.d[178] += settings.kkt_reg;
  work.d_inv[178] = 1/work.d[178];
  work.v[179] = work.KKT[179];
  work.d[179] = work.v[179];
  if (work.d[179] < 0)
    work.d[179] = settings.kkt_reg;
  else
    work.d[179] += settings.kkt_reg;
  work.d_inv[179] = 1/work.d[179];
  work.v[180] = work.KKT[180];
  work.d[180] = work.v[180];
  if (work.d[180] < 0)
    work.d[180] = settings.kkt_reg;
  else
    work.d[180] += settings.kkt_reg;
  work.d_inv[180] = 1/work.d[180];
  work.v[181] = work.KKT[181];
  work.d[181] = work.v[181];
  if (work.d[181] < 0)
    work.d[181] = settings.kkt_reg;
  else
    work.d[181] += settings.kkt_reg;
  work.d_inv[181] = 1/work.d[181];
  work.v[182] = work.KKT[182];
  work.d[182] = work.v[182];
  if (work.d[182] < 0)
    work.d[182] = settings.kkt_reg;
  else
    work.d[182] += settings.kkt_reg;
  work.d_inv[182] = 1/work.d[182];
  work.v[183] = work.KKT[183];
  work.d[183] = work.v[183];
  if (work.d[183] < 0)
    work.d[183] = settings.kkt_reg;
  else
    work.d[183] += settings.kkt_reg;
  work.d_inv[183] = 1/work.d[183];
  work.v[184] = work.KKT[184];
  work.d[184] = work.v[184];
  if (work.d[184] < 0)
    work.d[184] = settings.kkt_reg;
  else
    work.d[184] += settings.kkt_reg;
  work.d_inv[184] = 1/work.d[184];
  work.v[185] = work.KKT[185];
  work.d[185] = work.v[185];
  if (work.d[185] < 0)
    work.d[185] = settings.kkt_reg;
  else
    work.d[185] += settings.kkt_reg;
  work.d_inv[185] = 1/work.d[185];
  work.v[186] = work.KKT[186];
  work.d[186] = work.v[186];
  if (work.d[186] < 0)
    work.d[186] = settings.kkt_reg;
  else
    work.d[186] += settings.kkt_reg;
  work.d_inv[186] = 1/work.d[186];
  work.v[187] = work.KKT[187];
  work.d[187] = work.v[187];
  if (work.d[187] < 0)
    work.d[187] = settings.kkt_reg;
  else
    work.d[187] += settings.kkt_reg;
  work.d_inv[187] = 1/work.d[187];
  work.v[188] = work.KKT[188];
  work.d[188] = work.v[188];
  if (work.d[188] < 0)
    work.d[188] = settings.kkt_reg;
  else
    work.d[188] += settings.kkt_reg;
  work.d_inv[188] = 1/work.d[188];
  work.v[189] = work.KKT[189];
  work.d[189] = work.v[189];
  if (work.d[189] < 0)
    work.d[189] = settings.kkt_reg;
  else
    work.d[189] += settings.kkt_reg;
  work.d_inv[189] = 1/work.d[189];
  work.v[190] = work.KKT[190];
  work.d[190] = work.v[190];
  if (work.d[190] < 0)
    work.d[190] = settings.kkt_reg;
  else
    work.d[190] += settings.kkt_reg;
  work.d_inv[190] = 1/work.d[190];
  work.v[191] = work.KKT[191];
  work.d[191] = work.v[191];
  if (work.d[191] < 0)
    work.d[191] = settings.kkt_reg;
  else
    work.d[191] += settings.kkt_reg;
  work.d_inv[191] = 1/work.d[191];
  work.v[192] = work.KKT[192];
  work.d[192] = work.v[192];
  if (work.d[192] < 0)
    work.d[192] = settings.kkt_reg;
  else
    work.d[192] += settings.kkt_reg;
  work.d_inv[192] = 1/work.d[192];
  work.v[193] = work.KKT[193];
  work.d[193] = work.v[193];
  if (work.d[193] < 0)
    work.d[193] = settings.kkt_reg;
  else
    work.d[193] += settings.kkt_reg;
  work.d_inv[193] = 1/work.d[193];
  work.v[194] = work.KKT[194];
  work.d[194] = work.v[194];
  if (work.d[194] < 0)
    work.d[194] = settings.kkt_reg;
  else
    work.d[194] += settings.kkt_reg;
  work.d_inv[194] = 1/work.d[194];
  work.v[195] = work.KKT[195];
  work.d[195] = work.v[195];
  if (work.d[195] < 0)
    work.d[195] = settings.kkt_reg;
  else
    work.d[195] += settings.kkt_reg;
  work.d_inv[195] = 1/work.d[195];
  work.v[196] = work.KKT[196];
  work.d[196] = work.v[196];
  if (work.d[196] < 0)
    work.d[196] = settings.kkt_reg;
  else
    work.d[196] += settings.kkt_reg;
  work.d_inv[196] = 1/work.d[196];
  work.v[197] = work.KKT[197];
  work.d[197] = work.v[197];
  if (work.d[197] < 0)
    work.d[197] = settings.kkt_reg;
  else
    work.d[197] += settings.kkt_reg;
  work.d_inv[197] = 1/work.d[197];
  work.v[198] = work.KKT[198];
  work.d[198] = work.v[198];
  if (work.d[198] < 0)
    work.d[198] = settings.kkt_reg;
  else
    work.d[198] += settings.kkt_reg;
  work.d_inv[198] = 1/work.d[198];
  work.v[199] = work.KKT[199];
  work.d[199] = work.v[199];
  if (work.d[199] < 0)
    work.d[199] = settings.kkt_reg;
  else
    work.d[199] += settings.kkt_reg;
  work.d_inv[199] = 1/work.d[199];
  work.v[200] = work.KKT[200];
  work.d[200] = work.v[200];
  if (work.d[200] < 0)
    work.d[200] = settings.kkt_reg;
  else
    work.d[200] += settings.kkt_reg;
  work.d_inv[200] = 1/work.d[200];
  work.v[201] = work.KKT[201];
  work.d[201] = work.v[201];
  if (work.d[201] < 0)
    work.d[201] = settings.kkt_reg;
  else
    work.d[201] += settings.kkt_reg;
  work.d_inv[201] = 1/work.d[201];
  work.L[0] = (work.KKT[202])*work.d_inv[201];
  work.v[202] = work.KKT[203];
  work.d[202] = work.v[202];
  if (work.d[202] < 0)
    work.d[202] = settings.kkt_reg;
  else
    work.d[202] += settings.kkt_reg;
  work.d_inv[202] = 1/work.d[202];
  work.L[2] = (work.KKT[204])*work.d_inv[202];
  work.v[201] = work.L[0]*work.d[201];
  work.v[203] = work.KKT[205]-work.L[0]*work.v[201];
  work.d[203] = work.v[203];
  if (work.d[203] > 0)
    work.d[203] = -settings.kkt_reg;
  else
    work.d[203] -= settings.kkt_reg;
  work.d_inv[203] = 1/work.d[203];
  work.L[1] = (work.KKT[206])*work.d_inv[203];
  work.v[203] = work.L[1]*work.d[203];
  work.v[204] = work.KKT[207]-work.L[1]*work.v[203];
  work.d[204] = work.v[204];
  if (work.d[204] < 0)
    work.d[204] = settings.kkt_reg;
  else
    work.d[204] += settings.kkt_reg;
  work.d_inv[204] = 1/work.d[204];
  work.L[3] = (work.KKT[208])*work.d_inv[204];
  work.v[202] = work.L[2]*work.d[202];
  work.v[204] = work.L[3]*work.d[204];
  work.v[205] = work.KKT[209]-work.L[2]*work.v[202]-work.L[3]*work.v[204];
  work.d[205] = work.v[205];
  if (work.d[205] > 0)
    work.d[205] = -settings.kkt_reg;
  else
    work.d[205] -= settings.kkt_reg;
  work.d_inv[205] = 1/work.d[205];
#ifndef ZERO_LIBRARY_MODE
  if (settings.debug) {
    printf("Squared Frobenius for factorization is %.8g.\n", check_factorization());
  }
#endif
}
double check_factorization(void) {
  /* Returns the squared Frobenius norm of A - L*D*L'. */
  double temp, residual;
  /* Only check the lower triangle. */
  residual = 0;
  temp = work.KKT[207]-1*work.d[204]*1-work.L[1]*work.d[203]*work.L[1];
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
  temp = work.KKT[102]-1*work.d[102]*1;
  residual += temp*temp;
  temp = work.KKT[103]-1*work.d[103]*1;
  residual += temp*temp;
  temp = work.KKT[104]-1*work.d[104]*1;
  residual += temp*temp;
  temp = work.KKT[105]-1*work.d[105]*1;
  residual += temp*temp;
  temp = work.KKT[106]-1*work.d[106]*1;
  residual += temp*temp;
  temp = work.KKT[107]-1*work.d[107]*1;
  residual += temp*temp;
  temp = work.KKT[108]-1*work.d[108]*1;
  residual += temp*temp;
  temp = work.KKT[109]-1*work.d[109]*1;
  residual += temp*temp;
  temp = work.KKT[110]-1*work.d[110]*1;
  residual += temp*temp;
  temp = work.KKT[111]-1*work.d[111]*1;
  residual += temp*temp;
  temp = work.KKT[112]-1*work.d[112]*1;
  residual += temp*temp;
  temp = work.KKT[113]-1*work.d[113]*1;
  residual += temp*temp;
  temp = work.KKT[114]-1*work.d[114]*1;
  residual += temp*temp;
  temp = work.KKT[115]-1*work.d[115]*1;
  residual += temp*temp;
  temp = work.KKT[116]-1*work.d[116]*1;
  residual += temp*temp;
  temp = work.KKT[117]-1*work.d[117]*1;
  residual += temp*temp;
  temp = work.KKT[118]-1*work.d[118]*1;
  residual += temp*temp;
  temp = work.KKT[119]-1*work.d[119]*1;
  residual += temp*temp;
  temp = work.KKT[120]-1*work.d[120]*1;
  residual += temp*temp;
  temp = work.KKT[121]-1*work.d[121]*1;
  residual += temp*temp;
  temp = work.KKT[122]-1*work.d[122]*1;
  residual += temp*temp;
  temp = work.KKT[123]-1*work.d[123]*1;
  residual += temp*temp;
  temp = work.KKT[124]-1*work.d[124]*1;
  residual += temp*temp;
  temp = work.KKT[125]-1*work.d[125]*1;
  residual += temp*temp;
  temp = work.KKT[126]-1*work.d[126]*1;
  residual += temp*temp;
  temp = work.KKT[127]-1*work.d[127]*1;
  residual += temp*temp;
  temp = work.KKT[128]-1*work.d[128]*1;
  residual += temp*temp;
  temp = work.KKT[129]-1*work.d[129]*1;
  residual += temp*temp;
  temp = work.KKT[130]-1*work.d[130]*1;
  residual += temp*temp;
  temp = work.KKT[131]-1*work.d[131]*1;
  residual += temp*temp;
  temp = work.KKT[132]-1*work.d[132]*1;
  residual += temp*temp;
  temp = work.KKT[133]-1*work.d[133]*1;
  residual += temp*temp;
  temp = work.KKT[134]-1*work.d[134]*1;
  residual += temp*temp;
  temp = work.KKT[135]-1*work.d[135]*1;
  residual += temp*temp;
  temp = work.KKT[136]-1*work.d[136]*1;
  residual += temp*temp;
  temp = work.KKT[137]-1*work.d[137]*1;
  residual += temp*temp;
  temp = work.KKT[138]-1*work.d[138]*1;
  residual += temp*temp;
  temp = work.KKT[139]-1*work.d[139]*1;
  residual += temp*temp;
  temp = work.KKT[140]-1*work.d[140]*1;
  residual += temp*temp;
  temp = work.KKT[141]-1*work.d[141]*1;
  residual += temp*temp;
  temp = work.KKT[142]-1*work.d[142]*1;
  residual += temp*temp;
  temp = work.KKT[143]-1*work.d[143]*1;
  residual += temp*temp;
  temp = work.KKT[144]-1*work.d[144]*1;
  residual += temp*temp;
  temp = work.KKT[145]-1*work.d[145]*1;
  residual += temp*temp;
  temp = work.KKT[146]-1*work.d[146]*1;
  residual += temp*temp;
  temp = work.KKT[147]-1*work.d[147]*1;
  residual += temp*temp;
  temp = work.KKT[148]-1*work.d[148]*1;
  residual += temp*temp;
  temp = work.KKT[149]-1*work.d[149]*1;
  residual += temp*temp;
  temp = work.KKT[150]-1*work.d[150]*1;
  residual += temp*temp;
  temp = work.KKT[151]-1*work.d[151]*1;
  residual += temp*temp;
  temp = work.KKT[152]-1*work.d[152]*1;
  residual += temp*temp;
  temp = work.KKT[153]-1*work.d[153]*1;
  residual += temp*temp;
  temp = work.KKT[154]-1*work.d[154]*1;
  residual += temp*temp;
  temp = work.KKT[155]-1*work.d[155]*1;
  residual += temp*temp;
  temp = work.KKT[156]-1*work.d[156]*1;
  residual += temp*temp;
  temp = work.KKT[157]-1*work.d[157]*1;
  residual += temp*temp;
  temp = work.KKT[158]-1*work.d[158]*1;
  residual += temp*temp;
  temp = work.KKT[159]-1*work.d[159]*1;
  residual += temp*temp;
  temp = work.KKT[160]-1*work.d[160]*1;
  residual += temp*temp;
  temp = work.KKT[161]-1*work.d[161]*1;
  residual += temp*temp;
  temp = work.KKT[162]-1*work.d[162]*1;
  residual += temp*temp;
  temp = work.KKT[163]-1*work.d[163]*1;
  residual += temp*temp;
  temp = work.KKT[164]-1*work.d[164]*1;
  residual += temp*temp;
  temp = work.KKT[165]-1*work.d[165]*1;
  residual += temp*temp;
  temp = work.KKT[166]-1*work.d[166]*1;
  residual += temp*temp;
  temp = work.KKT[167]-1*work.d[167]*1;
  residual += temp*temp;
  temp = work.KKT[168]-1*work.d[168]*1;
  residual += temp*temp;
  temp = work.KKT[169]-1*work.d[169]*1;
  residual += temp*temp;
  temp = work.KKT[170]-1*work.d[170]*1;
  residual += temp*temp;
  temp = work.KKT[171]-1*work.d[171]*1;
  residual += temp*temp;
  temp = work.KKT[172]-1*work.d[172]*1;
  residual += temp*temp;
  temp = work.KKT[173]-1*work.d[173]*1;
  residual += temp*temp;
  temp = work.KKT[174]-1*work.d[174]*1;
  residual += temp*temp;
  temp = work.KKT[175]-1*work.d[175]*1;
  residual += temp*temp;
  temp = work.KKT[176]-1*work.d[176]*1;
  residual += temp*temp;
  temp = work.KKT[177]-1*work.d[177]*1;
  residual += temp*temp;
  temp = work.KKT[178]-1*work.d[178]*1;
  residual += temp*temp;
  temp = work.KKT[179]-1*work.d[179]*1;
  residual += temp*temp;
  temp = work.KKT[180]-1*work.d[180]*1;
  residual += temp*temp;
  temp = work.KKT[181]-1*work.d[181]*1;
  residual += temp*temp;
  temp = work.KKT[182]-1*work.d[182]*1;
  residual += temp*temp;
  temp = work.KKT[183]-1*work.d[183]*1;
  residual += temp*temp;
  temp = work.KKT[184]-1*work.d[184]*1;
  residual += temp*temp;
  temp = work.KKT[185]-1*work.d[185]*1;
  residual += temp*temp;
  temp = work.KKT[186]-1*work.d[186]*1;
  residual += temp*temp;
  temp = work.KKT[187]-1*work.d[187]*1;
  residual += temp*temp;
  temp = work.KKT[188]-1*work.d[188]*1;
  residual += temp*temp;
  temp = work.KKT[189]-1*work.d[189]*1;
  residual += temp*temp;
  temp = work.KKT[190]-1*work.d[190]*1;
  residual += temp*temp;
  temp = work.KKT[191]-1*work.d[191]*1;
  residual += temp*temp;
  temp = work.KKT[192]-1*work.d[192]*1;
  residual += temp*temp;
  temp = work.KKT[193]-1*work.d[193]*1;
  residual += temp*temp;
  temp = work.KKT[194]-1*work.d[194]*1;
  residual += temp*temp;
  temp = work.KKT[195]-1*work.d[195]*1;
  residual += temp*temp;
  temp = work.KKT[196]-1*work.d[196]*1;
  residual += temp*temp;
  temp = work.KKT[197]-1*work.d[197]*1;
  residual += temp*temp;
  temp = work.KKT[198]-1*work.d[198]*1;
  residual += temp*temp;
  temp = work.KKT[199]-1*work.d[199]*1;
  residual += temp*temp;
  temp = work.KKT[200]-1*work.d[200]*1;
  residual += temp*temp;
  temp = work.KKT[201]-1*work.d[201]*1;
  residual += temp*temp;
  temp = work.KKT[203]-1*work.d[202]*1;
  residual += temp*temp;
  temp = work.KKT[202]-work.L[0]*work.d[201]*1;
  residual += temp*temp;
  temp = work.KKT[204]-work.L[2]*work.d[202]*1;
  residual += temp*temp;
  temp = work.KKT[205]-work.L[0]*work.d[201]*work.L[0]-1*work.d[203]*1;
  residual += temp*temp;
  temp = work.KKT[209]-work.L[2]*work.d[202]*work.L[2]-1*work.d[205]*1-work.L[3]*work.d[204]*work.L[3];
  residual += temp*temp;
  temp = work.KKT[206]-1*work.d[203]*work.L[1];
  residual += temp*temp;
  temp = work.KKT[208]-work.L[3]*work.d[204]*1;
  residual += temp*temp;
  return residual;
}
void matrix_multiply(double *result, double *source) {
  /* Finds result = A*source. */
  result[0] = work.KKT[207]*source[0]+work.KKT[206]*source[204]+work.KKT[208]*source[205];
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
  result[102] = work.KKT[101]*source[102];
  result[103] = work.KKT[102]*source[103];
  result[104] = work.KKT[103]*source[104];
  result[105] = work.KKT[104]*source[105];
  result[106] = work.KKT[105]*source[106];
  result[107] = work.KKT[106]*source[107];
  result[108] = work.KKT[107]*source[108];
  result[109] = work.KKT[108]*source[109];
  result[110] = work.KKT[109]*source[110];
  result[111] = work.KKT[110]*source[111];
  result[112] = work.KKT[111]*source[112];
  result[113] = work.KKT[112]*source[113];
  result[114] = work.KKT[113]*source[114];
  result[115] = work.KKT[114]*source[115];
  result[116] = work.KKT[115]*source[116];
  result[117] = work.KKT[116]*source[117];
  result[118] = work.KKT[117]*source[118];
  result[119] = work.KKT[118]*source[119];
  result[120] = work.KKT[119]*source[120];
  result[121] = work.KKT[120]*source[121];
  result[122] = work.KKT[121]*source[122];
  result[123] = work.KKT[122]*source[123];
  result[124] = work.KKT[123]*source[124];
  result[125] = work.KKT[124]*source[125];
  result[126] = work.KKT[125]*source[126];
  result[127] = work.KKT[126]*source[127];
  result[128] = work.KKT[127]*source[128];
  result[129] = work.KKT[128]*source[129];
  result[130] = work.KKT[129]*source[130];
  result[131] = work.KKT[130]*source[131];
  result[132] = work.KKT[131]*source[132];
  result[133] = work.KKT[132]*source[133];
  result[134] = work.KKT[133]*source[134];
  result[135] = work.KKT[134]*source[135];
  result[136] = work.KKT[135]*source[136];
  result[137] = work.KKT[136]*source[137];
  result[138] = work.KKT[137]*source[138];
  result[139] = work.KKT[138]*source[139];
  result[140] = work.KKT[139]*source[140];
  result[141] = work.KKT[140]*source[141];
  result[142] = work.KKT[141]*source[142];
  result[143] = work.KKT[142]*source[143];
  result[144] = work.KKT[143]*source[144];
  result[145] = work.KKT[144]*source[145];
  result[146] = work.KKT[145]*source[146];
  result[147] = work.KKT[146]*source[147];
  result[148] = work.KKT[147]*source[148];
  result[149] = work.KKT[148]*source[149];
  result[150] = work.KKT[149]*source[150];
  result[151] = work.KKT[150]*source[151];
  result[152] = work.KKT[151]*source[152];
  result[153] = work.KKT[152]*source[153];
  result[154] = work.KKT[153]*source[154];
  result[155] = work.KKT[154]*source[155];
  result[156] = work.KKT[155]*source[156];
  result[157] = work.KKT[156]*source[157];
  result[158] = work.KKT[157]*source[158];
  result[159] = work.KKT[158]*source[159];
  result[160] = work.KKT[159]*source[160];
  result[161] = work.KKT[160]*source[161];
  result[162] = work.KKT[161]*source[162];
  result[163] = work.KKT[162]*source[163];
  result[164] = work.KKT[163]*source[164];
  result[165] = work.KKT[164]*source[165];
  result[166] = work.KKT[165]*source[166];
  result[167] = work.KKT[166]*source[167];
  result[168] = work.KKT[167]*source[168];
  result[169] = work.KKT[168]*source[169];
  result[170] = work.KKT[169]*source[170];
  result[171] = work.KKT[170]*source[171];
  result[172] = work.KKT[171]*source[172];
  result[173] = work.KKT[172]*source[173];
  result[174] = work.KKT[173]*source[174];
  result[175] = work.KKT[174]*source[175];
  result[176] = work.KKT[175]*source[176];
  result[177] = work.KKT[176]*source[177];
  result[178] = work.KKT[177]*source[178];
  result[179] = work.KKT[178]*source[179];
  result[180] = work.KKT[179]*source[180];
  result[181] = work.KKT[180]*source[181];
  result[182] = work.KKT[181]*source[182];
  result[183] = work.KKT[182]*source[183];
  result[184] = work.KKT[183]*source[184];
  result[185] = work.KKT[184]*source[185];
  result[186] = work.KKT[185]*source[186];
  result[187] = work.KKT[186]*source[187];
  result[188] = work.KKT[187]*source[188];
  result[189] = work.KKT[188]*source[189];
  result[190] = work.KKT[189]*source[190];
  result[191] = work.KKT[190]*source[191];
  result[192] = work.KKT[191]*source[192];
  result[193] = work.KKT[192]*source[193];
  result[194] = work.KKT[193]*source[194];
  result[195] = work.KKT[194]*source[195];
  result[196] = work.KKT[195]*source[196];
  result[197] = work.KKT[196]*source[197];
  result[198] = work.KKT[197]*source[198];
  result[199] = work.KKT[198]*source[199];
  result[200] = work.KKT[199]*source[200];
  result[201] = work.KKT[200]*source[201];
  result[202] = work.KKT[201]*source[202]+work.KKT[202]*source[204];
  result[203] = work.KKT[203]*source[203]+work.KKT[204]*source[205];
  result[204] = work.KKT[202]*source[202]+work.KKT[205]*source[204]+work.KKT[206]*source[0];
  result[205] = work.KKT[204]*source[203]+work.KKT[209]*source[205]+work.KKT[208]*source[0];
}
double check_residual(double *target, double *multiplicand) {
  /* Returns the squared 2-norm of lhs - A*rhs. */
  /* Reuses v to find the residual. */
  int i;
  double residual;
  residual = 0;
  matrix_multiply(work.v, multiplicand);
  for (i = 0; i < 202; i++) {
    residual += (target[i] - work.v[i])*(target[i] - work.v[i]);
  }
  return residual;
}
void fill_KKT(void) {
  work.KKT[207] = 2*(params.c2[0]+work.quad_812002893824[0]);
  work.KKT[0] = params.rho[0];
  work.KKT[1] = params.rho[1];
  work.KKT[2] = params.rho[2];
  work.KKT[3] = params.rho[3];
  work.KKT[4] = params.rho[4];
  work.KKT[5] = params.rho[5];
  work.KKT[6] = params.rho[6];
  work.KKT[7] = params.rho[7];
  work.KKT[8] = params.rho[8];
  work.KKT[9] = params.rho[9];
  work.KKT[10] = params.rho[10];
  work.KKT[11] = params.rho[11];
  work.KKT[12] = params.rho[12];
  work.KKT[13] = params.rho[13];
  work.KKT[14] = params.rho[14];
  work.KKT[15] = params.rho[15];
  work.KKT[16] = params.rho[16];
  work.KKT[17] = params.rho[17];
  work.KKT[18] = params.rho[18];
  work.KKT[19] = params.rho[19];
  work.KKT[20] = params.rho[20];
  work.KKT[21] = params.rho[21];
  work.KKT[22] = params.rho[22];
  work.KKT[23] = params.rho[23];
  work.KKT[24] = params.rho[24];
  work.KKT[25] = params.rho[25];
  work.KKT[26] = params.rho[26];
  work.KKT[27] = params.rho[27];
  work.KKT[28] = params.rho[28];
  work.KKT[29] = params.rho[29];
  work.KKT[30] = params.rho[30];
  work.KKT[31] = params.rho[31];
  work.KKT[32] = params.rho[32];
  work.KKT[33] = params.rho[33];
  work.KKT[34] = params.rho[34];
  work.KKT[35] = params.rho[35];
  work.KKT[36] = params.rho[36];
  work.KKT[37] = params.rho[37];
  work.KKT[38] = params.rho[38];
  work.KKT[39] = params.rho[39];
  work.KKT[40] = params.rho[40];
  work.KKT[41] = params.rho[41];
  work.KKT[42] = params.rho[42];
  work.KKT[43] = params.rho[43];
  work.KKT[44] = params.rho[44];
  work.KKT[45] = params.rho[45];
  work.KKT[46] = params.rho[46];
  work.KKT[47] = params.rho[47];
  work.KKT[48] = params.rho[48];
  work.KKT[49] = params.rho[49];
  work.KKT[50] = params.rho[50];
  work.KKT[51] = params.rho[51];
  work.KKT[52] = params.rho[52];
  work.KKT[53] = params.rho[53];
  work.KKT[54] = params.rho[54];
  work.KKT[55] = params.rho[55];
  work.KKT[56] = params.rho[56];
  work.KKT[57] = params.rho[57];
  work.KKT[58] = params.rho[58];
  work.KKT[59] = params.rho[59];
  work.KKT[60] = params.rho[60];
  work.KKT[61] = params.rho[61];
  work.KKT[62] = params.rho[62];
  work.KKT[63] = params.rho[63];
  work.KKT[64] = params.rho[64];
  work.KKT[65] = params.rho[65];
  work.KKT[66] = params.rho[66];
  work.KKT[67] = params.rho[67];
  work.KKT[68] = params.rho[68];
  work.KKT[69] = params.rho[69];
  work.KKT[70] = params.rho[70];
  work.KKT[71] = params.rho[71];
  work.KKT[72] = params.rho[72];
  work.KKT[73] = params.rho[73];
  work.KKT[74] = params.rho[74];
  work.KKT[75] = params.rho[75];
  work.KKT[76] = params.rho[76];
  work.KKT[77] = params.rho[77];
  work.KKT[78] = params.rho[78];
  work.KKT[79] = params.rho[79];
  work.KKT[80] = params.rho[80];
  work.KKT[81] = params.rho[81];
  work.KKT[82] = params.rho[82];
  work.KKT[83] = params.rho[83];
  work.KKT[84] = params.rho[84];
  work.KKT[85] = params.rho[85];
  work.KKT[86] = params.rho[86];
  work.KKT[87] = params.rho[87];
  work.KKT[88] = params.rho[88];
  work.KKT[89] = params.rho[89];
  work.KKT[90] = params.rho[90];
  work.KKT[91] = params.rho[91];
  work.KKT[92] = params.rho[92];
  work.KKT[93] = params.rho[93];
  work.KKT[94] = params.rho[94];
  work.KKT[95] = params.rho[95];
  work.KKT[96] = params.rho[96];
  work.KKT[97] = params.rho[97];
  work.KKT[98] = params.rho[98];
  work.KKT[99] = params.rho[99];
  work.KKT[100] = params.rho[100];
  work.KKT[101] = params.rho[101];
  work.KKT[102] = params.rho[102];
  work.KKT[103] = params.rho[103];
  work.KKT[104] = params.rho[104];
  work.KKT[105] = params.rho[105];
  work.KKT[106] = params.rho[106];
  work.KKT[107] = params.rho[107];
  work.KKT[108] = params.rho[108];
  work.KKT[109] = params.rho[109];
  work.KKT[110] = params.rho[110];
  work.KKT[111] = params.rho[111];
  work.KKT[112] = params.rho[112];
  work.KKT[113] = params.rho[113];
  work.KKT[114] = params.rho[114];
  work.KKT[115] = params.rho[115];
  work.KKT[116] = params.rho[116];
  work.KKT[117] = params.rho[117];
  work.KKT[118] = params.rho[118];
  work.KKT[119] = params.rho[119];
  work.KKT[120] = params.rho[120];
  work.KKT[121] = params.rho[121];
  work.KKT[122] = params.rho[122];
  work.KKT[123] = params.rho[123];
  work.KKT[124] = params.rho[124];
  work.KKT[125] = params.rho[125];
  work.KKT[126] = params.rho[126];
  work.KKT[127] = params.rho[127];
  work.KKT[128] = params.rho[128];
  work.KKT[129] = params.rho[129];
  work.KKT[130] = params.rho[130];
  work.KKT[131] = params.rho[131];
  work.KKT[132] = params.rho[132];
  work.KKT[133] = params.rho[133];
  work.KKT[134] = params.rho[134];
  work.KKT[135] = params.rho[135];
  work.KKT[136] = params.rho[136];
  work.KKT[137] = params.rho[137];
  work.KKT[138] = params.rho[138];
  work.KKT[139] = params.rho[139];
  work.KKT[140] = params.rho[140];
  work.KKT[141] = params.rho[141];
  work.KKT[142] = params.rho[142];
  work.KKT[143] = params.rho[143];
  work.KKT[144] = params.rho[144];
  work.KKT[145] = params.rho[145];
  work.KKT[146] = params.rho[146];
  work.KKT[147] = params.rho[147];
  work.KKT[148] = params.rho[148];
  work.KKT[149] = params.rho[149];
  work.KKT[150] = params.rho[150];
  work.KKT[151] = params.rho[151];
  work.KKT[152] = params.rho[152];
  work.KKT[153] = params.rho[153];
  work.KKT[154] = params.rho[154];
  work.KKT[155] = params.rho[155];
  work.KKT[156] = params.rho[156];
  work.KKT[157] = params.rho[157];
  work.KKT[158] = params.rho[158];
  work.KKT[159] = params.rho[159];
  work.KKT[160] = params.rho[160];
  work.KKT[161] = params.rho[161];
  work.KKT[162] = params.rho[162];
  work.KKT[163] = params.rho[163];
  work.KKT[164] = params.rho[164];
  work.KKT[165] = params.rho[165];
  work.KKT[166] = params.rho[166];
  work.KKT[167] = params.rho[167];
  work.KKT[168] = params.rho[168];
  work.KKT[169] = params.rho[169];
  work.KKT[170] = params.rho[170];
  work.KKT[171] = params.rho[171];
  work.KKT[172] = params.rho[172];
  work.KKT[173] = params.rho[173];
  work.KKT[174] = params.rho[174];
  work.KKT[175] = params.rho[175];
  work.KKT[176] = params.rho[176];
  work.KKT[177] = params.rho[177];
  work.KKT[178] = params.rho[178];
  work.KKT[179] = params.rho[179];
  work.KKT[180] = params.rho[180];
  work.KKT[181] = params.rho[181];
  work.KKT[182] = params.rho[182];
  work.KKT[183] = params.rho[183];
  work.KKT[184] = params.rho[184];
  work.KKT[185] = params.rho[185];
  work.KKT[186] = params.rho[186];
  work.KKT[187] = params.rho[187];
  work.KKT[188] = params.rho[188];
  work.KKT[189] = params.rho[189];
  work.KKT[190] = params.rho[190];
  work.KKT[191] = params.rho[191];
  work.KKT[192] = params.rho[192];
  work.KKT[193] = params.rho[193];
  work.KKT[194] = params.rho[194];
  work.KKT[195] = params.rho[195];
  work.KKT[196] = params.rho[196];
  work.KKT[197] = params.rho[197];
  work.KKT[198] = params.rho[198];
  work.KKT[199] = params.rho[199];
  work.KKT[200] = params.rho[200];
  work.KKT[201] = work.s_inv_z[0];
  work.KKT[203] = work.s_inv_z[1];
  work.KKT[202] = 1;
  work.KKT[204] = 1;
  work.KKT[205] = work.block_33[0];
  work.KKT[209] = work.block_33[0];
  work.KKT[206] = -1;
  work.KKT[208] = 1;
}
