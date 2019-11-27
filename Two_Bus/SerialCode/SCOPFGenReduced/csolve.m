% csolve  Solves a custom quadratic program very rapidly.
%
% [vars, status] = csolve(params, settings)
%
% solves the convex optimization problem
%
%   minimize(c2*square(Pg) + c1*Pg + c0 + (rho/2)*(square(Pg - Pg_N_init_0 + Pg_N_avg_0 + ug_N_0) + square(Thetag_0 - Vg_N_avg_0 - Thetag_N_avg_0 + vg_N_0) + square(Pg - Pg_N_init_1 + Pg_N_avg_1 + ug_N_1) + square(Thetag_1 - Vg_N_avg_1 - Thetag_N_avg_1 + vg_N_1) + square(Pg - Pg_N_init_2 + Pg_N_avg_2 + ug_N_2) + square(Thetag_2 - Vg_N_avg_2 - Thetag_N_avg_2 + vg_N_2) + square(Pg - Pg_N_init_3 + Pg_N_avg_3 + ug_N_3) + square(Thetag_3 - Vg_N_avg_3 - Thetag_N_avg_3 + vg_N_3) + square(Pg - Pg_N_init_4 + Pg_N_avg_4 + ug_N_4) + square(Thetag_4 - Vg_N_avg_4 - Thetag_N_avg_4 + vg_N_4) + square(Pg - Pg_N_init_5 + Pg_N_avg_5 + ug_N_5) + square(Thetag_5 - Vg_N_avg_5 - Thetag_N_avg_5 + vg_N_5) + square(Pg - Pg_N_init_6 + Pg_N_avg_6 + ug_N_6) + square(Thetag_6 - Vg_N_avg_6 - Thetag_N_avg_6 + vg_N_6) + square(Pg - Pg_N_init_7 + Pg_N_avg_7 + ug_N_7) + square(Thetag_7 - Vg_N_avg_7 - Thetag_N_avg_7 + vg_N_7) + square(Pg - Pg_N_init_8 + Pg_N_avg_8 + ug_N_8) + square(Thetag_8 - Vg_N_avg_8 - Thetag_N_avg_8 + vg_N_8) + square(Pg - Pg_N_init_9 + Pg_N_avg_9 + ug_N_9) + square(Thetag_9 - Vg_N_avg_9 - Thetag_N_avg_9 + vg_N_9) + square(Pg - Pg_N_init_10 + Pg_N_avg_10 + ug_N_10) + square(Thetag_10 - Vg_N_avg_10 - Thetag_N_avg_10 + vg_N_10)))
%   subject to
%     PgMin <= Pg
%     Pg <= PgMax
%
% with variables
%       Pg   1 x 1
% Thetag_0   1 x 1
% Thetag_1   1 x 1
% Thetag_2   1 x 1
% Thetag_3   1 x 1
% Thetag_4   1 x 1
% Thetag_5   1 x 1
% Thetag_6   1 x 1
% Thetag_7   1 x 1
% Thetag_8   1 x 1
% Thetag_9   1 x 1
% Thetag_10   1 x 1
%
% and parameters
%    PgMax   1 x 1    positive
%    PgMin   1 x 1    positive
% Pg_N_avg_0   1 x 1
% Pg_N_avg_1   1 x 1
% Pg_N_avg_2   1 x 1
% Pg_N_avg_3   1 x 1
% Pg_N_avg_4   1 x 1
% Pg_N_avg_5   1 x 1
% Pg_N_avg_6   1 x 1
% Pg_N_avg_7   1 x 1
% Pg_N_avg_8   1 x 1
% Pg_N_avg_9   1 x 1
% Pg_N_avg_10   1 x 1
% Pg_N_init_0   1 x 1
% Pg_N_init_1   1 x 1
% Pg_N_init_2   1 x 1
% Pg_N_init_3   1 x 1
% Pg_N_init_4   1 x 1
% Pg_N_init_5   1 x 1
% Pg_N_init_6   1 x 1
% Pg_N_init_7   1 x 1
% Pg_N_init_8   1 x 1
% Pg_N_init_9   1 x 1
% Pg_N_init_10   1 x 1
% Thetag_N_avg_0   1 x 1
% Thetag_N_avg_1   1 x 1
% Thetag_N_avg_2   1 x 1
% Thetag_N_avg_3   1 x 1
% Thetag_N_avg_4   1 x 1
% Thetag_N_avg_5   1 x 1
% Thetag_N_avg_6   1 x 1
% Thetag_N_avg_7   1 x 1
% Thetag_N_avg_8   1 x 1
% Thetag_N_avg_9   1 x 1
% Thetag_N_avg_10   1 x 1
% Vg_N_avg_0   1 x 1
% Vg_N_avg_1   1 x 1
% Vg_N_avg_2   1 x 1
% Vg_N_avg_3   1 x 1
% Vg_N_avg_4   1 x 1
% Vg_N_avg_5   1 x 1
% Vg_N_avg_6   1 x 1
% Vg_N_avg_7   1 x 1
% Vg_N_avg_8   1 x 1
% Vg_N_avg_9   1 x 1
% Vg_N_avg_10   1 x 1
%       c0   1 x 1    positive
%       c1   1 x 1    positive
%       c2   1 x 1    positive
%      rho   1 x 1    positive
%   ug_N_0   1 x 1
%   ug_N_1   1 x 1
%   ug_N_2   1 x 1
%   ug_N_3   1 x 1
%   ug_N_4   1 x 1
%   ug_N_5   1 x 1
%   ug_N_6   1 x 1
%   ug_N_7   1 x 1
%   ug_N_8   1 x 1
%   ug_N_9   1 x 1
%  ug_N_10   1 x 1
%   vg_N_0   1 x 1
%   vg_N_1   1 x 1
%   vg_N_2   1 x 1
%   vg_N_3   1 x 1
%   vg_N_4   1 x 1
%   vg_N_5   1 x 1
%   vg_N_6   1 x 1
%   vg_N_7   1 x 1
%   vg_N_8   1 x 1
%   vg_N_9   1 x 1
%  vg_N_10   1 x 1
%
% Note:
%   - Check status.converged, which will be 1 if optimization succeeded.
%   - You don't have to specify settings if you don't want to.
%   - To hide output, use settings.verbose = 0.
%   - To change iterations, use settings.max_iters = 20.
%   - You may wish to compare with cvxsolve to check the solver is correct.
%
% Specify params.PgMax, ..., params.vg_N_10, then run
%   [vars, status] = csolve(params, settings)
% Produced by CVXGEN, 2015-02-05 18:05:35 -0500.
% CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2012 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: csolve.m.
% Description: Help file for the Matlab solver interface.
