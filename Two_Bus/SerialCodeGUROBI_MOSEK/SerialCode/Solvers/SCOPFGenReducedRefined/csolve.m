% csolve  Solves a custom quadratic program very rapidly.
%
% [vars, status] = csolve(params, settings)
%
% solves the convex optimization problem
%
%   minimize(c2*square(Pg) + c1*Pg + c0 + (rho/2)*(square(Pg - Pg_N_init(1) + Pg_N_avg(1) + ug_N(1)) + square(Thetag(1) - Vg_N_avg(1) - Thetag_N_avg(1) + vg_N(1)) + square(Pg - Pg_N_init(2) + Pg_N_avg(2) + ug_N(2)) + square(Thetag(2) - Vg_N_avg(2) - Thetag_N_avg(2) + vg_N(2)) + square(Pg - Pg_N_init(3) + Pg_N_avg(3) + ug_N(3)) + square(Thetag(3) - Vg_N_avg(3) - Thetag_N_avg(3) + vg_N(3)) + square(Pg - Pg_N_init(4) + Pg_N_avg(4) + ug_N(4)) + square(Thetag(4) - Vg_N_avg(4) - Thetag_N_avg(4) + vg_N(4)) + square(Pg - Pg_N_init(5) + Pg_N_avg(5) + ug_N(5)) + square(Thetag(5) - Vg_N_avg(5) - Thetag_N_avg(5) + vg_N(5)) + square(Pg - Pg_N_init(6) + Pg_N_avg(6) + ug_N(6)) + square(Thetag(6) - Vg_N_avg(6) - Thetag_N_avg(6) + vg_N(6)) + square(Pg - Pg_N_init(7) + Pg_N_avg(7) + ug_N(7)) + square(Thetag(7) - Vg_N_avg(7) - Thetag_N_avg(7) + vg_N(7)) + square(Pg - Pg_N_init(8) + Pg_N_avg(8) + ug_N(8)) + square(Thetag(8) - Vg_N_avg(8) - Thetag_N_avg(8) + vg_N(8)) + square(Pg - Pg_N_init(9) + Pg_N_avg(9) + ug_N(9)) + square(Thetag(9) - Vg_N_avg(9) - Thetag_N_avg(9) + vg_N(9)) + square(Pg - Pg_N_init(10) + Pg_N_avg(10) + ug_N(10)) + square(Thetag(10) - Vg_N_avg(10) - Thetag_N_avg(10) + vg_N(10))))
%   subject to
%     PgMin <= Pg
%     Pg <= PgMax
%
% with variables
%       Pg   1 x 1
%   Thetag  10 x 1
%
% and parameters
%    PgMax   1 x 1    positive
%    PgMin   1 x 1    positive
% Pg_N_avg  10 x 1
% Pg_N_init  10 x 1
% Thetag_N_avg  10 x 1
% Vg_N_avg  10 x 1
%       c0   1 x 1    positive
%       c1   1 x 1    positive
%       c2   1 x 1    positive
%      rho   1 x 1    positive
%     ug_N  10 x 1
%     vg_N  10 x 1
%
% Note:
%   - Check status.converged, which will be 1 if optimization succeeded.
%   - You don't have to specify settings if you don't want to.
%   - To hide output, use settings.verbose = 0.
%   - To change iterations, use settings.max_iters = 20.
%   - You may wish to compare with cvxsolve to check the solver is correct.
%
% Specify params.PgMax, ..., params.vg_N, then run
%   [vars, status] = csolve(params, settings)
% Produced by CVXGEN, 2015-02-06 22:35:37 -0500.
% CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2012 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: csolve.m.
% Description: Help file for the Matlab solver interface.
