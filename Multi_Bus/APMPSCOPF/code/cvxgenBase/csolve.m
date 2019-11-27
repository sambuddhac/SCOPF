% csolve  Solves a custom quadratic program very rapidly.
%
% [vars, status] = csolve(params, settings)
%
% solves the convex optimization problem
%
%   minimize(c2*square(Pg) + c1*Pg + c0 + (betaSC/2)*square(Pg - PgAPPSC) + gammaSC*sum(BSC*Pg) + sum(lambda_1SC*Pg) + (rho/2)*(square(Pg - Pg_N_init + Pg_N_avg + ug_N) + square(Thetag - Vg_N_avg - Thetag_N_avg + vg_N)))
%   subject to
%     PgMin <= Pg
%     Pg <= PgMax
%
% with variables
%       Pg   1 x 1
%   Thetag   1 x 1
%
% and parameters
%      BSC 500 x 1
%  PgAPPSC   1 x 1
%    PgMax   1 x 1    positive
%    PgMin   1 x 1    positive
% Pg_N_avg   1 x 1
% Pg_N_init   1 x 1
% Thetag_N_avg   1 x 1
% Vg_N_avg   1 x 1
%   betaSC   1 x 1    positive
%       c0   1 x 1    positive
%       c1   1 x 1    positive
%       c2   1 x 1    positive
%  gammaSC   1 x 1    positive
% lambda_1SC 500 x 1
%      rho   1 x 1    positive
%     ug_N   1 x 1
%     vg_N   1 x 1
%
% Note:
%   - Check status.converged, which will be 1 if optimization succeeded.
%   - You don't have to specify settings if you don't want to.
%   - To hide output, use settings.verbose = 0.
%   - To change iterations, use settings.max_iters = 20.
%   - You may wish to compare with cvxsolve to check the solver is correct.
%
% Specify params.BSC, ..., params.vg_N, then run
%   [vars, status] = csolve(params, settings)
% Produced by CVXGEN, 2017-08-04 19:28:12 -0400.
% CVXGEN is Copyright (C) 2006-2017 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2017 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: csolve.m.
% Description: Help file for the Matlab solver interface.
