% Produced by CVXGEN, 2015-02-05 18:05:35 -0500.
% CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2012 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: cvxsolve.m.
% Description: Solution file, via cvx, for use with sample.m.
function [vars, status] = cvxsolve(params, settings)
PgMax = params.PgMax;
PgMin = params.PgMin;
Pg_N_avg_0 = params.Pg_N_avg_0;
if isfield(params, 'Pg_N_avg_1')
  Pg_N_avg_1 = params.Pg_N_avg_1;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_1 = params.Pg_N_avg{1};
else
  error 'could not find Pg_N_avg_1'
end
if isfield(params, 'Pg_N_avg_2')
  Pg_N_avg_2 = params.Pg_N_avg_2;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_2 = params.Pg_N_avg{2};
else
  error 'could not find Pg_N_avg_2'
end
if isfield(params, 'Pg_N_avg_3')
  Pg_N_avg_3 = params.Pg_N_avg_3;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_3 = params.Pg_N_avg{3};
else
  error 'could not find Pg_N_avg_3'
end
if isfield(params, 'Pg_N_avg_4')
  Pg_N_avg_4 = params.Pg_N_avg_4;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_4 = params.Pg_N_avg{4};
else
  error 'could not find Pg_N_avg_4'
end
if isfield(params, 'Pg_N_avg_5')
  Pg_N_avg_5 = params.Pg_N_avg_5;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_5 = params.Pg_N_avg{5};
else
  error 'could not find Pg_N_avg_5'
end
if isfield(params, 'Pg_N_avg_6')
  Pg_N_avg_6 = params.Pg_N_avg_6;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_6 = params.Pg_N_avg{6};
else
  error 'could not find Pg_N_avg_6'
end
if isfield(params, 'Pg_N_avg_7')
  Pg_N_avg_7 = params.Pg_N_avg_7;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_7 = params.Pg_N_avg{7};
else
  error 'could not find Pg_N_avg_7'
end
if isfield(params, 'Pg_N_avg_8')
  Pg_N_avg_8 = params.Pg_N_avg_8;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_8 = params.Pg_N_avg{8};
else
  error 'could not find Pg_N_avg_8'
end
if isfield(params, 'Pg_N_avg_9')
  Pg_N_avg_9 = params.Pg_N_avg_9;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_9 = params.Pg_N_avg{9};
else
  error 'could not find Pg_N_avg_9'
end
if isfield(params, 'Pg_N_avg_10')
  Pg_N_avg_10 = params.Pg_N_avg_10;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_10 = params.Pg_N_avg{10};
else
  error 'could not find Pg_N_avg_10'
end
Pg_N_init_0 = params.Pg_N_init_0;
if isfield(params, 'Pg_N_init_1')
  Pg_N_init_1 = params.Pg_N_init_1;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_1 = params.Pg_N_init{1};
else
  error 'could not find Pg_N_init_1'
end
if isfield(params, 'Pg_N_init_2')
  Pg_N_init_2 = params.Pg_N_init_2;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_2 = params.Pg_N_init{2};
else
  error 'could not find Pg_N_init_2'
end
if isfield(params, 'Pg_N_init_3')
  Pg_N_init_3 = params.Pg_N_init_3;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_3 = params.Pg_N_init{3};
else
  error 'could not find Pg_N_init_3'
end
if isfield(params, 'Pg_N_init_4')
  Pg_N_init_4 = params.Pg_N_init_4;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_4 = params.Pg_N_init{4};
else
  error 'could not find Pg_N_init_4'
end
if isfield(params, 'Pg_N_init_5')
  Pg_N_init_5 = params.Pg_N_init_5;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_5 = params.Pg_N_init{5};
else
  error 'could not find Pg_N_init_5'
end
if isfield(params, 'Pg_N_init_6')
  Pg_N_init_6 = params.Pg_N_init_6;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_6 = params.Pg_N_init{6};
else
  error 'could not find Pg_N_init_6'
end
if isfield(params, 'Pg_N_init_7')
  Pg_N_init_7 = params.Pg_N_init_7;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_7 = params.Pg_N_init{7};
else
  error 'could not find Pg_N_init_7'
end
if isfield(params, 'Pg_N_init_8')
  Pg_N_init_8 = params.Pg_N_init_8;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_8 = params.Pg_N_init{8};
else
  error 'could not find Pg_N_init_8'
end
if isfield(params, 'Pg_N_init_9')
  Pg_N_init_9 = params.Pg_N_init_9;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_9 = params.Pg_N_init{9};
else
  error 'could not find Pg_N_init_9'
end
if isfield(params, 'Pg_N_init_10')
  Pg_N_init_10 = params.Pg_N_init_10;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_10 = params.Pg_N_init{10};
else
  error 'could not find Pg_N_init_10'
end
Thetag_N_avg_0 = params.Thetag_N_avg_0;
if isfield(params, 'Thetag_N_avg_1')
  Thetag_N_avg_1 = params.Thetag_N_avg_1;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_1 = params.Thetag_N_avg{1};
else
  error 'could not find Thetag_N_avg_1'
end
if isfield(params, 'Thetag_N_avg_2')
  Thetag_N_avg_2 = params.Thetag_N_avg_2;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_2 = params.Thetag_N_avg{2};
else
  error 'could not find Thetag_N_avg_2'
end
if isfield(params, 'Thetag_N_avg_3')
  Thetag_N_avg_3 = params.Thetag_N_avg_3;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_3 = params.Thetag_N_avg{3};
else
  error 'could not find Thetag_N_avg_3'
end
if isfield(params, 'Thetag_N_avg_4')
  Thetag_N_avg_4 = params.Thetag_N_avg_4;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_4 = params.Thetag_N_avg{4};
else
  error 'could not find Thetag_N_avg_4'
end
if isfield(params, 'Thetag_N_avg_5')
  Thetag_N_avg_5 = params.Thetag_N_avg_5;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_5 = params.Thetag_N_avg{5};
else
  error 'could not find Thetag_N_avg_5'
end
if isfield(params, 'Thetag_N_avg_6')
  Thetag_N_avg_6 = params.Thetag_N_avg_6;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_6 = params.Thetag_N_avg{6};
else
  error 'could not find Thetag_N_avg_6'
end
if isfield(params, 'Thetag_N_avg_7')
  Thetag_N_avg_7 = params.Thetag_N_avg_7;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_7 = params.Thetag_N_avg{7};
else
  error 'could not find Thetag_N_avg_7'
end
if isfield(params, 'Thetag_N_avg_8')
  Thetag_N_avg_8 = params.Thetag_N_avg_8;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_8 = params.Thetag_N_avg{8};
else
  error 'could not find Thetag_N_avg_8'
end
if isfield(params, 'Thetag_N_avg_9')
  Thetag_N_avg_9 = params.Thetag_N_avg_9;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_9 = params.Thetag_N_avg{9};
else
  error 'could not find Thetag_N_avg_9'
end
if isfield(params, 'Thetag_N_avg_10')
  Thetag_N_avg_10 = params.Thetag_N_avg_10;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_10 = params.Thetag_N_avg{10};
else
  error 'could not find Thetag_N_avg_10'
end
Vg_N_avg_0 = params.Vg_N_avg_0;
if isfield(params, 'Vg_N_avg_1')
  Vg_N_avg_1 = params.Vg_N_avg_1;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_1 = params.Vg_N_avg{1};
else
  error 'could not find Vg_N_avg_1'
end
if isfield(params, 'Vg_N_avg_2')
  Vg_N_avg_2 = params.Vg_N_avg_2;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_2 = params.Vg_N_avg{2};
else
  error 'could not find Vg_N_avg_2'
end
if isfield(params, 'Vg_N_avg_3')
  Vg_N_avg_3 = params.Vg_N_avg_3;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_3 = params.Vg_N_avg{3};
else
  error 'could not find Vg_N_avg_3'
end
if isfield(params, 'Vg_N_avg_4')
  Vg_N_avg_4 = params.Vg_N_avg_4;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_4 = params.Vg_N_avg{4};
else
  error 'could not find Vg_N_avg_4'
end
if isfield(params, 'Vg_N_avg_5')
  Vg_N_avg_5 = params.Vg_N_avg_5;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_5 = params.Vg_N_avg{5};
else
  error 'could not find Vg_N_avg_5'
end
if isfield(params, 'Vg_N_avg_6')
  Vg_N_avg_6 = params.Vg_N_avg_6;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_6 = params.Vg_N_avg{6};
else
  error 'could not find Vg_N_avg_6'
end
if isfield(params, 'Vg_N_avg_7')
  Vg_N_avg_7 = params.Vg_N_avg_7;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_7 = params.Vg_N_avg{7};
else
  error 'could not find Vg_N_avg_7'
end
if isfield(params, 'Vg_N_avg_8')
  Vg_N_avg_8 = params.Vg_N_avg_8;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_8 = params.Vg_N_avg{8};
else
  error 'could not find Vg_N_avg_8'
end
if isfield(params, 'Vg_N_avg_9')
  Vg_N_avg_9 = params.Vg_N_avg_9;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_9 = params.Vg_N_avg{9};
else
  error 'could not find Vg_N_avg_9'
end
if isfield(params, 'Vg_N_avg_10')
  Vg_N_avg_10 = params.Vg_N_avg_10;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_10 = params.Vg_N_avg{10};
else
  error 'could not find Vg_N_avg_10'
end
c0 = params.c0;
c1 = params.c1;
c2 = params.c2;
rho = params.rho;
ug_N_0 = params.ug_N_0;
if isfield(params, 'ug_N_1')
  ug_N_1 = params.ug_N_1;
elseif isfield(params, 'ug_N')
  ug_N_1 = params.ug_N{1};
else
  error 'could not find ug_N_1'
end
if isfield(params, 'ug_N_2')
  ug_N_2 = params.ug_N_2;
elseif isfield(params, 'ug_N')
  ug_N_2 = params.ug_N{2};
else
  error 'could not find ug_N_2'
end
if isfield(params, 'ug_N_3')
  ug_N_3 = params.ug_N_3;
elseif isfield(params, 'ug_N')
  ug_N_3 = params.ug_N{3};
else
  error 'could not find ug_N_3'
end
if isfield(params, 'ug_N_4')
  ug_N_4 = params.ug_N_4;
elseif isfield(params, 'ug_N')
  ug_N_4 = params.ug_N{4};
else
  error 'could not find ug_N_4'
end
if isfield(params, 'ug_N_5')
  ug_N_5 = params.ug_N_5;
elseif isfield(params, 'ug_N')
  ug_N_5 = params.ug_N{5};
else
  error 'could not find ug_N_5'
end
if isfield(params, 'ug_N_6')
  ug_N_6 = params.ug_N_6;
elseif isfield(params, 'ug_N')
  ug_N_6 = params.ug_N{6};
else
  error 'could not find ug_N_6'
end
if isfield(params, 'ug_N_7')
  ug_N_7 = params.ug_N_7;
elseif isfield(params, 'ug_N')
  ug_N_7 = params.ug_N{7};
else
  error 'could not find ug_N_7'
end
if isfield(params, 'ug_N_8')
  ug_N_8 = params.ug_N_8;
elseif isfield(params, 'ug_N')
  ug_N_8 = params.ug_N{8};
else
  error 'could not find ug_N_8'
end
if isfield(params, 'ug_N_9')
  ug_N_9 = params.ug_N_9;
elseif isfield(params, 'ug_N')
  ug_N_9 = params.ug_N{9};
else
  error 'could not find ug_N_9'
end
if isfield(params, 'ug_N_10')
  ug_N_10 = params.ug_N_10;
elseif isfield(params, 'ug_N')
  ug_N_10 = params.ug_N{10};
else
  error 'could not find ug_N_10'
end
vg_N_0 = params.vg_N_0;
if isfield(params, 'vg_N_1')
  vg_N_1 = params.vg_N_1;
elseif isfield(params, 'vg_N')
  vg_N_1 = params.vg_N{1};
else
  error 'could not find vg_N_1'
end
if isfield(params, 'vg_N_2')
  vg_N_2 = params.vg_N_2;
elseif isfield(params, 'vg_N')
  vg_N_2 = params.vg_N{2};
else
  error 'could not find vg_N_2'
end
if isfield(params, 'vg_N_3')
  vg_N_3 = params.vg_N_3;
elseif isfield(params, 'vg_N')
  vg_N_3 = params.vg_N{3};
else
  error 'could not find vg_N_3'
end
if isfield(params, 'vg_N_4')
  vg_N_4 = params.vg_N_4;
elseif isfield(params, 'vg_N')
  vg_N_4 = params.vg_N{4};
else
  error 'could not find vg_N_4'
end
if isfield(params, 'vg_N_5')
  vg_N_5 = params.vg_N_5;
elseif isfield(params, 'vg_N')
  vg_N_5 = params.vg_N{5};
else
  error 'could not find vg_N_5'
end
if isfield(params, 'vg_N_6')
  vg_N_6 = params.vg_N_6;
elseif isfield(params, 'vg_N')
  vg_N_6 = params.vg_N{6};
else
  error 'could not find vg_N_6'
end
if isfield(params, 'vg_N_7')
  vg_N_7 = params.vg_N_7;
elseif isfield(params, 'vg_N')
  vg_N_7 = params.vg_N{7};
else
  error 'could not find vg_N_7'
end
if isfield(params, 'vg_N_8')
  vg_N_8 = params.vg_N_8;
elseif isfield(params, 'vg_N')
  vg_N_8 = params.vg_N{8};
else
  error 'could not find vg_N_8'
end
if isfield(params, 'vg_N_9')
  vg_N_9 = params.vg_N_9;
elseif isfield(params, 'vg_N')
  vg_N_9 = params.vg_N{9};
else
  error 'could not find vg_N_9'
end
if isfield(params, 'vg_N_10')
  vg_N_10 = params.vg_N_10;
elseif isfield(params, 'vg_N')
  vg_N_10 = params.vg_N{10};
else
  error 'could not find vg_N_10'
end
cvx_begin
  % Caution: automatically generated by cvxgen. May be incorrect.
  variable Pg;
  variable Thetag_0;
  variable Thetag_1;
  variable Thetag_2;
  variable Thetag_3;
  variable Thetag_4;
  variable Thetag_5;
  variable Thetag_6;
  variable Thetag_7;
  variable Thetag_8;
  variable Thetag_9;
  variable Thetag_10;

  minimize(c2*square(Pg) + c1*Pg + c0 + (rho/2)*(square(Pg - Pg_N_init_0 + Pg_N_avg_0 + ug_N_0) + square(Thetag_0 - Vg_N_avg_0 - Thetag_N_avg_0 + vg_N_0) + square(Pg - Pg_N_init_1 + Pg_N_avg_1 + ug_N_1) + square(Thetag_1 - Vg_N_avg_1 - Thetag_N_avg_1 + vg_N_1) + square(Pg - Pg_N_init_2 + Pg_N_avg_2 + ug_N_2) + square(Thetag_2 - Vg_N_avg_2 - Thetag_N_avg_2 + vg_N_2) + square(Pg - Pg_N_init_3 + Pg_N_avg_3 + ug_N_3) + square(Thetag_3 - Vg_N_avg_3 - Thetag_N_avg_3 + vg_N_3) + square(Pg - Pg_N_init_4 + Pg_N_avg_4 + ug_N_4) + square(Thetag_4 - Vg_N_avg_4 - Thetag_N_avg_4 + vg_N_4) + square(Pg - Pg_N_init_5 + Pg_N_avg_5 + ug_N_5) + square(Thetag_5 - Vg_N_avg_5 - Thetag_N_avg_5 + vg_N_5) + square(Pg - Pg_N_init_6 + Pg_N_avg_6 + ug_N_6) + square(Thetag_6 - Vg_N_avg_6 - Thetag_N_avg_6 + vg_N_6) + square(Pg - Pg_N_init_7 + Pg_N_avg_7 + ug_N_7) + square(Thetag_7 - Vg_N_avg_7 - Thetag_N_avg_7 + vg_N_7) + square(Pg - Pg_N_init_8 + Pg_N_avg_8 + ug_N_8) + square(Thetag_8 - Vg_N_avg_8 - Thetag_N_avg_8 + vg_N_8) + square(Pg - Pg_N_init_9 + Pg_N_avg_9 + ug_N_9) + square(Thetag_9 - Vg_N_avg_9 - Thetag_N_avg_9 + vg_N_9) + square(Pg - Pg_N_init_10 + Pg_N_avg_10 + ug_N_10) + square(Thetag_10 - Vg_N_avg_10 - Thetag_N_avg_10 + vg_N_10)));
  subject to
    PgMin <= Pg;
    Pg <= PgMax;
cvx_end
vars.Pg = Pg;
vars.Thetag_0 = Thetag_0;
vars.Thetag_1 = Thetag_1;
vars.Thetag{1} = Thetag_1;
vars.Thetag_2 = Thetag_2;
vars.Thetag{2} = Thetag_2;
vars.Thetag_3 = Thetag_3;
vars.Thetag{3} = Thetag_3;
vars.Thetag_4 = Thetag_4;
vars.Thetag{4} = Thetag_4;
vars.Thetag_5 = Thetag_5;
vars.Thetag{5} = Thetag_5;
vars.Thetag_6 = Thetag_6;
vars.Thetag{6} = Thetag_6;
vars.Thetag_7 = Thetag_7;
vars.Thetag{7} = Thetag_7;
vars.Thetag_8 = Thetag_8;
vars.Thetag{8} = Thetag_8;
vars.Thetag_9 = Thetag_9;
vars.Thetag{9} = Thetag_9;
vars.Thetag_10 = Thetag_10;
vars.Thetag{10} = Thetag_10;
status.cvx_status = cvx_status;
% Provide a drop-in replacement for csolve.
status.optval = cvx_optval;
status.converged = strcmp(cvx_status, 'Solved');
