% Produced by CVXGEN, 2015-03-30 03:25:41 -0400.
% CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2012 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: cvxsolve.m.
% Description: Solution file, via cvx, for use with sample.m.
function [vars, status] = cvxsolve(params, settings)
PgMax = params.PgMax;
PgMin = params.PgMin;
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
if isfield(params, 'Pg_N_avg_11')
  Pg_N_avg_11 = params.Pg_N_avg_11;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_11 = params.Pg_N_avg{11};
else
  error 'could not find Pg_N_avg_11'
end
if isfield(params, 'Pg_N_avg_12')
  Pg_N_avg_12 = params.Pg_N_avg_12;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_12 = params.Pg_N_avg{12};
else
  error 'could not find Pg_N_avg_12'
end
if isfield(params, 'Pg_N_avg_13')
  Pg_N_avg_13 = params.Pg_N_avg_13;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_13 = params.Pg_N_avg{13};
else
  error 'could not find Pg_N_avg_13'
end
if isfield(params, 'Pg_N_avg_14')
  Pg_N_avg_14 = params.Pg_N_avg_14;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_14 = params.Pg_N_avg{14};
else
  error 'could not find Pg_N_avg_14'
end
if isfield(params, 'Pg_N_avg_15')
  Pg_N_avg_15 = params.Pg_N_avg_15;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_15 = params.Pg_N_avg{15};
else
  error 'could not find Pg_N_avg_15'
end
if isfield(params, 'Pg_N_avg_16')
  Pg_N_avg_16 = params.Pg_N_avg_16;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_16 = params.Pg_N_avg{16};
else
  error 'could not find Pg_N_avg_16'
end
if isfield(params, 'Pg_N_avg_17')
  Pg_N_avg_17 = params.Pg_N_avg_17;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_17 = params.Pg_N_avg{17};
else
  error 'could not find Pg_N_avg_17'
end
if isfield(params, 'Pg_N_avg_18')
  Pg_N_avg_18 = params.Pg_N_avg_18;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_18 = params.Pg_N_avg{18};
else
  error 'could not find Pg_N_avg_18'
end
if isfield(params, 'Pg_N_avg_19')
  Pg_N_avg_19 = params.Pg_N_avg_19;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_19 = params.Pg_N_avg{19};
else
  error 'could not find Pg_N_avg_19'
end
if isfield(params, 'Pg_N_avg_20')
  Pg_N_avg_20 = params.Pg_N_avg_20;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_20 = params.Pg_N_avg{20};
else
  error 'could not find Pg_N_avg_20'
end
if isfield(params, 'Pg_N_avg_21')
  Pg_N_avg_21 = params.Pg_N_avg_21;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_21 = params.Pg_N_avg{21};
else
  error 'could not find Pg_N_avg_21'
end
if isfield(params, 'Pg_N_avg_22')
  Pg_N_avg_22 = params.Pg_N_avg_22;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_22 = params.Pg_N_avg{22};
else
  error 'could not find Pg_N_avg_22'
end
if isfield(params, 'Pg_N_avg_23')
  Pg_N_avg_23 = params.Pg_N_avg_23;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_23 = params.Pg_N_avg{23};
else
  error 'could not find Pg_N_avg_23'
end
if isfield(params, 'Pg_N_avg_24')
  Pg_N_avg_24 = params.Pg_N_avg_24;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_24 = params.Pg_N_avg{24};
else
  error 'could not find Pg_N_avg_24'
end
if isfield(params, 'Pg_N_avg_25')
  Pg_N_avg_25 = params.Pg_N_avg_25;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_25 = params.Pg_N_avg{25};
else
  error 'could not find Pg_N_avg_25'
end
if isfield(params, 'Pg_N_avg_26')
  Pg_N_avg_26 = params.Pg_N_avg_26;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_26 = params.Pg_N_avg{26};
else
  error 'could not find Pg_N_avg_26'
end
if isfield(params, 'Pg_N_avg_27')
  Pg_N_avg_27 = params.Pg_N_avg_27;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_27 = params.Pg_N_avg{27};
else
  error 'could not find Pg_N_avg_27'
end
if isfield(params, 'Pg_N_avg_28')
  Pg_N_avg_28 = params.Pg_N_avg_28;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_28 = params.Pg_N_avg{28};
else
  error 'could not find Pg_N_avg_28'
end
if isfield(params, 'Pg_N_avg_29')
  Pg_N_avg_29 = params.Pg_N_avg_29;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_29 = params.Pg_N_avg{29};
else
  error 'could not find Pg_N_avg_29'
end
if isfield(params, 'Pg_N_avg_30')
  Pg_N_avg_30 = params.Pg_N_avg_30;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_30 = params.Pg_N_avg{30};
else
  error 'could not find Pg_N_avg_30'
end
if isfield(params, 'Pg_N_avg_31')
  Pg_N_avg_31 = params.Pg_N_avg_31;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_31 = params.Pg_N_avg{31};
else
  error 'could not find Pg_N_avg_31'
end
if isfield(params, 'Pg_N_avg_32')
  Pg_N_avg_32 = params.Pg_N_avg_32;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_32 = params.Pg_N_avg{32};
else
  error 'could not find Pg_N_avg_32'
end
if isfield(params, 'Pg_N_avg_33')
  Pg_N_avg_33 = params.Pg_N_avg_33;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_33 = params.Pg_N_avg{33};
else
  error 'could not find Pg_N_avg_33'
end
if isfield(params, 'Pg_N_avg_34')
  Pg_N_avg_34 = params.Pg_N_avg_34;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_34 = params.Pg_N_avg{34};
else
  error 'could not find Pg_N_avg_34'
end
if isfield(params, 'Pg_N_avg_35')
  Pg_N_avg_35 = params.Pg_N_avg_35;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_35 = params.Pg_N_avg{35};
else
  error 'could not find Pg_N_avg_35'
end
if isfield(params, 'Pg_N_avg_36')
  Pg_N_avg_36 = params.Pg_N_avg_36;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_36 = params.Pg_N_avg{36};
else
  error 'could not find Pg_N_avg_36'
end
if isfield(params, 'Pg_N_avg_37')
  Pg_N_avg_37 = params.Pg_N_avg_37;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_37 = params.Pg_N_avg{37};
else
  error 'could not find Pg_N_avg_37'
end
if isfield(params, 'Pg_N_avg_38')
  Pg_N_avg_38 = params.Pg_N_avg_38;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_38 = params.Pg_N_avg{38};
else
  error 'could not find Pg_N_avg_38'
end
if isfield(params, 'Pg_N_avg_39')
  Pg_N_avg_39 = params.Pg_N_avg_39;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_39 = params.Pg_N_avg{39};
else
  error 'could not find Pg_N_avg_39'
end
if isfield(params, 'Pg_N_avg_40')
  Pg_N_avg_40 = params.Pg_N_avg_40;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_40 = params.Pg_N_avg{40};
else
  error 'could not find Pg_N_avg_40'
end
if isfield(params, 'Pg_N_avg_41')
  Pg_N_avg_41 = params.Pg_N_avg_41;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_41 = params.Pg_N_avg{41};
else
  error 'could not find Pg_N_avg_41'
end
if isfield(params, 'Pg_N_avg_42')
  Pg_N_avg_42 = params.Pg_N_avg_42;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_42 = params.Pg_N_avg{42};
else
  error 'could not find Pg_N_avg_42'
end
if isfield(params, 'Pg_N_avg_43')
  Pg_N_avg_43 = params.Pg_N_avg_43;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_43 = params.Pg_N_avg{43};
else
  error 'could not find Pg_N_avg_43'
end
if isfield(params, 'Pg_N_avg_44')
  Pg_N_avg_44 = params.Pg_N_avg_44;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_44 = params.Pg_N_avg{44};
else
  error 'could not find Pg_N_avg_44'
end
if isfield(params, 'Pg_N_avg_45')
  Pg_N_avg_45 = params.Pg_N_avg_45;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_45 = params.Pg_N_avg{45};
else
  error 'could not find Pg_N_avg_45'
end
if isfield(params, 'Pg_N_avg_46')
  Pg_N_avg_46 = params.Pg_N_avg_46;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_46 = params.Pg_N_avg{46};
else
  error 'could not find Pg_N_avg_46'
end
if isfield(params, 'Pg_N_avg_47')
  Pg_N_avg_47 = params.Pg_N_avg_47;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_47 = params.Pg_N_avg{47};
else
  error 'could not find Pg_N_avg_47'
end
if isfield(params, 'Pg_N_avg_48')
  Pg_N_avg_48 = params.Pg_N_avg_48;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_48 = params.Pg_N_avg{48};
else
  error 'could not find Pg_N_avg_48'
end
if isfield(params, 'Pg_N_avg_49')
  Pg_N_avg_49 = params.Pg_N_avg_49;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_49 = params.Pg_N_avg{49};
else
  error 'could not find Pg_N_avg_49'
end
if isfield(params, 'Pg_N_avg_50')
  Pg_N_avg_50 = params.Pg_N_avg_50;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_50 = params.Pg_N_avg{50};
else
  error 'could not find Pg_N_avg_50'
end
if isfield(params, 'Pg_N_avg_51')
  Pg_N_avg_51 = params.Pg_N_avg_51;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_51 = params.Pg_N_avg{51};
else
  error 'could not find Pg_N_avg_51'
end
if isfield(params, 'Pg_N_avg_52')
  Pg_N_avg_52 = params.Pg_N_avg_52;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_52 = params.Pg_N_avg{52};
else
  error 'could not find Pg_N_avg_52'
end
if isfield(params, 'Pg_N_avg_53')
  Pg_N_avg_53 = params.Pg_N_avg_53;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_53 = params.Pg_N_avg{53};
else
  error 'could not find Pg_N_avg_53'
end
if isfield(params, 'Pg_N_avg_54')
  Pg_N_avg_54 = params.Pg_N_avg_54;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_54 = params.Pg_N_avg{54};
else
  error 'could not find Pg_N_avg_54'
end
if isfield(params, 'Pg_N_avg_55')
  Pg_N_avg_55 = params.Pg_N_avg_55;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_55 = params.Pg_N_avg{55};
else
  error 'could not find Pg_N_avg_55'
end
if isfield(params, 'Pg_N_avg_56')
  Pg_N_avg_56 = params.Pg_N_avg_56;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_56 = params.Pg_N_avg{56};
else
  error 'could not find Pg_N_avg_56'
end
if isfield(params, 'Pg_N_avg_57')
  Pg_N_avg_57 = params.Pg_N_avg_57;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_57 = params.Pg_N_avg{57};
else
  error 'could not find Pg_N_avg_57'
end
if isfield(params, 'Pg_N_avg_58')
  Pg_N_avg_58 = params.Pg_N_avg_58;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_58 = params.Pg_N_avg{58};
else
  error 'could not find Pg_N_avg_58'
end
if isfield(params, 'Pg_N_avg_59')
  Pg_N_avg_59 = params.Pg_N_avg_59;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_59 = params.Pg_N_avg{59};
else
  error 'could not find Pg_N_avg_59'
end
if isfield(params, 'Pg_N_avg_60')
  Pg_N_avg_60 = params.Pg_N_avg_60;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_60 = params.Pg_N_avg{60};
else
  error 'could not find Pg_N_avg_60'
end
if isfield(params, 'Pg_N_avg_61')
  Pg_N_avg_61 = params.Pg_N_avg_61;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_61 = params.Pg_N_avg{61};
else
  error 'could not find Pg_N_avg_61'
end
if isfield(params, 'Pg_N_avg_62')
  Pg_N_avg_62 = params.Pg_N_avg_62;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_62 = params.Pg_N_avg{62};
else
  error 'could not find Pg_N_avg_62'
end
if isfield(params, 'Pg_N_avg_63')
  Pg_N_avg_63 = params.Pg_N_avg_63;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_63 = params.Pg_N_avg{63};
else
  error 'could not find Pg_N_avg_63'
end
if isfield(params, 'Pg_N_avg_64')
  Pg_N_avg_64 = params.Pg_N_avg_64;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_64 = params.Pg_N_avg{64};
else
  error 'could not find Pg_N_avg_64'
end
if isfield(params, 'Pg_N_avg_65')
  Pg_N_avg_65 = params.Pg_N_avg_65;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_65 = params.Pg_N_avg{65};
else
  error 'could not find Pg_N_avg_65'
end
if isfield(params, 'Pg_N_avg_66')
  Pg_N_avg_66 = params.Pg_N_avg_66;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_66 = params.Pg_N_avg{66};
else
  error 'could not find Pg_N_avg_66'
end
if isfield(params, 'Pg_N_avg_67')
  Pg_N_avg_67 = params.Pg_N_avg_67;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_67 = params.Pg_N_avg{67};
else
  error 'could not find Pg_N_avg_67'
end
if isfield(params, 'Pg_N_avg_68')
  Pg_N_avg_68 = params.Pg_N_avg_68;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_68 = params.Pg_N_avg{68};
else
  error 'could not find Pg_N_avg_68'
end
if isfield(params, 'Pg_N_avg_69')
  Pg_N_avg_69 = params.Pg_N_avg_69;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_69 = params.Pg_N_avg{69};
else
  error 'could not find Pg_N_avg_69'
end
if isfield(params, 'Pg_N_avg_70')
  Pg_N_avg_70 = params.Pg_N_avg_70;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_70 = params.Pg_N_avg{70};
else
  error 'could not find Pg_N_avg_70'
end
if isfield(params, 'Pg_N_avg_71')
  Pg_N_avg_71 = params.Pg_N_avg_71;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_71 = params.Pg_N_avg{71};
else
  error 'could not find Pg_N_avg_71'
end
if isfield(params, 'Pg_N_avg_72')
  Pg_N_avg_72 = params.Pg_N_avg_72;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_72 = params.Pg_N_avg{72};
else
  error 'could not find Pg_N_avg_72'
end
if isfield(params, 'Pg_N_avg_73')
  Pg_N_avg_73 = params.Pg_N_avg_73;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_73 = params.Pg_N_avg{73};
else
  error 'could not find Pg_N_avg_73'
end
if isfield(params, 'Pg_N_avg_74')
  Pg_N_avg_74 = params.Pg_N_avg_74;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_74 = params.Pg_N_avg{74};
else
  error 'could not find Pg_N_avg_74'
end
if isfield(params, 'Pg_N_avg_75')
  Pg_N_avg_75 = params.Pg_N_avg_75;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_75 = params.Pg_N_avg{75};
else
  error 'could not find Pg_N_avg_75'
end
if isfield(params, 'Pg_N_avg_76')
  Pg_N_avg_76 = params.Pg_N_avg_76;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_76 = params.Pg_N_avg{76};
else
  error 'could not find Pg_N_avg_76'
end
if isfield(params, 'Pg_N_avg_77')
  Pg_N_avg_77 = params.Pg_N_avg_77;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_77 = params.Pg_N_avg{77};
else
  error 'could not find Pg_N_avg_77'
end
if isfield(params, 'Pg_N_avg_78')
  Pg_N_avg_78 = params.Pg_N_avg_78;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_78 = params.Pg_N_avg{78};
else
  error 'could not find Pg_N_avg_78'
end
if isfield(params, 'Pg_N_avg_79')
  Pg_N_avg_79 = params.Pg_N_avg_79;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_79 = params.Pg_N_avg{79};
else
  error 'could not find Pg_N_avg_79'
end
if isfield(params, 'Pg_N_avg_80')
  Pg_N_avg_80 = params.Pg_N_avg_80;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_80 = params.Pg_N_avg{80};
else
  error 'could not find Pg_N_avg_80'
end
if isfield(params, 'Pg_N_avg_81')
  Pg_N_avg_81 = params.Pg_N_avg_81;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_81 = params.Pg_N_avg{81};
else
  error 'could not find Pg_N_avg_81'
end
if isfield(params, 'Pg_N_avg_82')
  Pg_N_avg_82 = params.Pg_N_avg_82;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_82 = params.Pg_N_avg{82};
else
  error 'could not find Pg_N_avg_82'
end
if isfield(params, 'Pg_N_avg_83')
  Pg_N_avg_83 = params.Pg_N_avg_83;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_83 = params.Pg_N_avg{83};
else
  error 'could not find Pg_N_avg_83'
end
if isfield(params, 'Pg_N_avg_84')
  Pg_N_avg_84 = params.Pg_N_avg_84;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_84 = params.Pg_N_avg{84};
else
  error 'could not find Pg_N_avg_84'
end
if isfield(params, 'Pg_N_avg_85')
  Pg_N_avg_85 = params.Pg_N_avg_85;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_85 = params.Pg_N_avg{85};
else
  error 'could not find Pg_N_avg_85'
end
if isfield(params, 'Pg_N_avg_86')
  Pg_N_avg_86 = params.Pg_N_avg_86;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_86 = params.Pg_N_avg{86};
else
  error 'could not find Pg_N_avg_86'
end
if isfield(params, 'Pg_N_avg_87')
  Pg_N_avg_87 = params.Pg_N_avg_87;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_87 = params.Pg_N_avg{87};
else
  error 'could not find Pg_N_avg_87'
end
if isfield(params, 'Pg_N_avg_88')
  Pg_N_avg_88 = params.Pg_N_avg_88;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_88 = params.Pg_N_avg{88};
else
  error 'could not find Pg_N_avg_88'
end
if isfield(params, 'Pg_N_avg_89')
  Pg_N_avg_89 = params.Pg_N_avg_89;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_89 = params.Pg_N_avg{89};
else
  error 'could not find Pg_N_avg_89'
end
if isfield(params, 'Pg_N_avg_90')
  Pg_N_avg_90 = params.Pg_N_avg_90;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_90 = params.Pg_N_avg{90};
else
  error 'could not find Pg_N_avg_90'
end
if isfield(params, 'Pg_N_avg_91')
  Pg_N_avg_91 = params.Pg_N_avg_91;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_91 = params.Pg_N_avg{91};
else
  error 'could not find Pg_N_avg_91'
end
if isfield(params, 'Pg_N_avg_92')
  Pg_N_avg_92 = params.Pg_N_avg_92;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_92 = params.Pg_N_avg{92};
else
  error 'could not find Pg_N_avg_92'
end
if isfield(params, 'Pg_N_avg_93')
  Pg_N_avg_93 = params.Pg_N_avg_93;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_93 = params.Pg_N_avg{93};
else
  error 'could not find Pg_N_avg_93'
end
if isfield(params, 'Pg_N_avg_94')
  Pg_N_avg_94 = params.Pg_N_avg_94;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_94 = params.Pg_N_avg{94};
else
  error 'could not find Pg_N_avg_94'
end
if isfield(params, 'Pg_N_avg_95')
  Pg_N_avg_95 = params.Pg_N_avg_95;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_95 = params.Pg_N_avg{95};
else
  error 'could not find Pg_N_avg_95'
end
if isfield(params, 'Pg_N_avg_96')
  Pg_N_avg_96 = params.Pg_N_avg_96;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_96 = params.Pg_N_avg{96};
else
  error 'could not find Pg_N_avg_96'
end
if isfield(params, 'Pg_N_avg_97')
  Pg_N_avg_97 = params.Pg_N_avg_97;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_97 = params.Pg_N_avg{97};
else
  error 'could not find Pg_N_avg_97'
end
if isfield(params, 'Pg_N_avg_98')
  Pg_N_avg_98 = params.Pg_N_avg_98;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_98 = params.Pg_N_avg{98};
else
  error 'could not find Pg_N_avg_98'
end
if isfield(params, 'Pg_N_avg_99')
  Pg_N_avg_99 = params.Pg_N_avg_99;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_99 = params.Pg_N_avg{99};
else
  error 'could not find Pg_N_avg_99'
end
if isfield(params, 'Pg_N_avg_100')
  Pg_N_avg_100 = params.Pg_N_avg_100;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_100 = params.Pg_N_avg{100};
else
  error 'could not find Pg_N_avg_100'
end
if isfield(params, 'Pg_N_avg_101')
  Pg_N_avg_101 = params.Pg_N_avg_101;
elseif isfield(params, 'Pg_N_avg')
  Pg_N_avg_101 = params.Pg_N_avg{101};
else
  error 'could not find Pg_N_avg_101'
end
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
if isfield(params, 'Pg_N_init_11')
  Pg_N_init_11 = params.Pg_N_init_11;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_11 = params.Pg_N_init{11};
else
  error 'could not find Pg_N_init_11'
end
if isfield(params, 'Pg_N_init_12')
  Pg_N_init_12 = params.Pg_N_init_12;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_12 = params.Pg_N_init{12};
else
  error 'could not find Pg_N_init_12'
end
if isfield(params, 'Pg_N_init_13')
  Pg_N_init_13 = params.Pg_N_init_13;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_13 = params.Pg_N_init{13};
else
  error 'could not find Pg_N_init_13'
end
if isfield(params, 'Pg_N_init_14')
  Pg_N_init_14 = params.Pg_N_init_14;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_14 = params.Pg_N_init{14};
else
  error 'could not find Pg_N_init_14'
end
if isfield(params, 'Pg_N_init_15')
  Pg_N_init_15 = params.Pg_N_init_15;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_15 = params.Pg_N_init{15};
else
  error 'could not find Pg_N_init_15'
end
if isfield(params, 'Pg_N_init_16')
  Pg_N_init_16 = params.Pg_N_init_16;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_16 = params.Pg_N_init{16};
else
  error 'could not find Pg_N_init_16'
end
if isfield(params, 'Pg_N_init_17')
  Pg_N_init_17 = params.Pg_N_init_17;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_17 = params.Pg_N_init{17};
else
  error 'could not find Pg_N_init_17'
end
if isfield(params, 'Pg_N_init_18')
  Pg_N_init_18 = params.Pg_N_init_18;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_18 = params.Pg_N_init{18};
else
  error 'could not find Pg_N_init_18'
end
if isfield(params, 'Pg_N_init_19')
  Pg_N_init_19 = params.Pg_N_init_19;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_19 = params.Pg_N_init{19};
else
  error 'could not find Pg_N_init_19'
end
if isfield(params, 'Pg_N_init_20')
  Pg_N_init_20 = params.Pg_N_init_20;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_20 = params.Pg_N_init{20};
else
  error 'could not find Pg_N_init_20'
end
if isfield(params, 'Pg_N_init_21')
  Pg_N_init_21 = params.Pg_N_init_21;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_21 = params.Pg_N_init{21};
else
  error 'could not find Pg_N_init_21'
end
if isfield(params, 'Pg_N_init_22')
  Pg_N_init_22 = params.Pg_N_init_22;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_22 = params.Pg_N_init{22};
else
  error 'could not find Pg_N_init_22'
end
if isfield(params, 'Pg_N_init_23')
  Pg_N_init_23 = params.Pg_N_init_23;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_23 = params.Pg_N_init{23};
else
  error 'could not find Pg_N_init_23'
end
if isfield(params, 'Pg_N_init_24')
  Pg_N_init_24 = params.Pg_N_init_24;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_24 = params.Pg_N_init{24};
else
  error 'could not find Pg_N_init_24'
end
if isfield(params, 'Pg_N_init_25')
  Pg_N_init_25 = params.Pg_N_init_25;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_25 = params.Pg_N_init{25};
else
  error 'could not find Pg_N_init_25'
end
if isfield(params, 'Pg_N_init_26')
  Pg_N_init_26 = params.Pg_N_init_26;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_26 = params.Pg_N_init{26};
else
  error 'could not find Pg_N_init_26'
end
if isfield(params, 'Pg_N_init_27')
  Pg_N_init_27 = params.Pg_N_init_27;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_27 = params.Pg_N_init{27};
else
  error 'could not find Pg_N_init_27'
end
if isfield(params, 'Pg_N_init_28')
  Pg_N_init_28 = params.Pg_N_init_28;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_28 = params.Pg_N_init{28};
else
  error 'could not find Pg_N_init_28'
end
if isfield(params, 'Pg_N_init_29')
  Pg_N_init_29 = params.Pg_N_init_29;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_29 = params.Pg_N_init{29};
else
  error 'could not find Pg_N_init_29'
end
if isfield(params, 'Pg_N_init_30')
  Pg_N_init_30 = params.Pg_N_init_30;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_30 = params.Pg_N_init{30};
else
  error 'could not find Pg_N_init_30'
end
if isfield(params, 'Pg_N_init_31')
  Pg_N_init_31 = params.Pg_N_init_31;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_31 = params.Pg_N_init{31};
else
  error 'could not find Pg_N_init_31'
end
if isfield(params, 'Pg_N_init_32')
  Pg_N_init_32 = params.Pg_N_init_32;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_32 = params.Pg_N_init{32};
else
  error 'could not find Pg_N_init_32'
end
if isfield(params, 'Pg_N_init_33')
  Pg_N_init_33 = params.Pg_N_init_33;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_33 = params.Pg_N_init{33};
else
  error 'could not find Pg_N_init_33'
end
if isfield(params, 'Pg_N_init_34')
  Pg_N_init_34 = params.Pg_N_init_34;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_34 = params.Pg_N_init{34};
else
  error 'could not find Pg_N_init_34'
end
if isfield(params, 'Pg_N_init_35')
  Pg_N_init_35 = params.Pg_N_init_35;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_35 = params.Pg_N_init{35};
else
  error 'could not find Pg_N_init_35'
end
if isfield(params, 'Pg_N_init_36')
  Pg_N_init_36 = params.Pg_N_init_36;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_36 = params.Pg_N_init{36};
else
  error 'could not find Pg_N_init_36'
end
if isfield(params, 'Pg_N_init_37')
  Pg_N_init_37 = params.Pg_N_init_37;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_37 = params.Pg_N_init{37};
else
  error 'could not find Pg_N_init_37'
end
if isfield(params, 'Pg_N_init_38')
  Pg_N_init_38 = params.Pg_N_init_38;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_38 = params.Pg_N_init{38};
else
  error 'could not find Pg_N_init_38'
end
if isfield(params, 'Pg_N_init_39')
  Pg_N_init_39 = params.Pg_N_init_39;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_39 = params.Pg_N_init{39};
else
  error 'could not find Pg_N_init_39'
end
if isfield(params, 'Pg_N_init_40')
  Pg_N_init_40 = params.Pg_N_init_40;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_40 = params.Pg_N_init{40};
else
  error 'could not find Pg_N_init_40'
end
if isfield(params, 'Pg_N_init_41')
  Pg_N_init_41 = params.Pg_N_init_41;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_41 = params.Pg_N_init{41};
else
  error 'could not find Pg_N_init_41'
end
if isfield(params, 'Pg_N_init_42')
  Pg_N_init_42 = params.Pg_N_init_42;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_42 = params.Pg_N_init{42};
else
  error 'could not find Pg_N_init_42'
end
if isfield(params, 'Pg_N_init_43')
  Pg_N_init_43 = params.Pg_N_init_43;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_43 = params.Pg_N_init{43};
else
  error 'could not find Pg_N_init_43'
end
if isfield(params, 'Pg_N_init_44')
  Pg_N_init_44 = params.Pg_N_init_44;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_44 = params.Pg_N_init{44};
else
  error 'could not find Pg_N_init_44'
end
if isfield(params, 'Pg_N_init_45')
  Pg_N_init_45 = params.Pg_N_init_45;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_45 = params.Pg_N_init{45};
else
  error 'could not find Pg_N_init_45'
end
if isfield(params, 'Pg_N_init_46')
  Pg_N_init_46 = params.Pg_N_init_46;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_46 = params.Pg_N_init{46};
else
  error 'could not find Pg_N_init_46'
end
if isfield(params, 'Pg_N_init_47')
  Pg_N_init_47 = params.Pg_N_init_47;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_47 = params.Pg_N_init{47};
else
  error 'could not find Pg_N_init_47'
end
if isfield(params, 'Pg_N_init_48')
  Pg_N_init_48 = params.Pg_N_init_48;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_48 = params.Pg_N_init{48};
else
  error 'could not find Pg_N_init_48'
end
if isfield(params, 'Pg_N_init_49')
  Pg_N_init_49 = params.Pg_N_init_49;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_49 = params.Pg_N_init{49};
else
  error 'could not find Pg_N_init_49'
end
if isfield(params, 'Pg_N_init_50')
  Pg_N_init_50 = params.Pg_N_init_50;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_50 = params.Pg_N_init{50};
else
  error 'could not find Pg_N_init_50'
end
if isfield(params, 'Pg_N_init_51')
  Pg_N_init_51 = params.Pg_N_init_51;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_51 = params.Pg_N_init{51};
else
  error 'could not find Pg_N_init_51'
end
if isfield(params, 'Pg_N_init_52')
  Pg_N_init_52 = params.Pg_N_init_52;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_52 = params.Pg_N_init{52};
else
  error 'could not find Pg_N_init_52'
end
if isfield(params, 'Pg_N_init_53')
  Pg_N_init_53 = params.Pg_N_init_53;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_53 = params.Pg_N_init{53};
else
  error 'could not find Pg_N_init_53'
end
if isfield(params, 'Pg_N_init_54')
  Pg_N_init_54 = params.Pg_N_init_54;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_54 = params.Pg_N_init{54};
else
  error 'could not find Pg_N_init_54'
end
if isfield(params, 'Pg_N_init_55')
  Pg_N_init_55 = params.Pg_N_init_55;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_55 = params.Pg_N_init{55};
else
  error 'could not find Pg_N_init_55'
end
if isfield(params, 'Pg_N_init_56')
  Pg_N_init_56 = params.Pg_N_init_56;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_56 = params.Pg_N_init{56};
else
  error 'could not find Pg_N_init_56'
end
if isfield(params, 'Pg_N_init_57')
  Pg_N_init_57 = params.Pg_N_init_57;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_57 = params.Pg_N_init{57};
else
  error 'could not find Pg_N_init_57'
end
if isfield(params, 'Pg_N_init_58')
  Pg_N_init_58 = params.Pg_N_init_58;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_58 = params.Pg_N_init{58};
else
  error 'could not find Pg_N_init_58'
end
if isfield(params, 'Pg_N_init_59')
  Pg_N_init_59 = params.Pg_N_init_59;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_59 = params.Pg_N_init{59};
else
  error 'could not find Pg_N_init_59'
end
if isfield(params, 'Pg_N_init_60')
  Pg_N_init_60 = params.Pg_N_init_60;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_60 = params.Pg_N_init{60};
else
  error 'could not find Pg_N_init_60'
end
if isfield(params, 'Pg_N_init_61')
  Pg_N_init_61 = params.Pg_N_init_61;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_61 = params.Pg_N_init{61};
else
  error 'could not find Pg_N_init_61'
end
if isfield(params, 'Pg_N_init_62')
  Pg_N_init_62 = params.Pg_N_init_62;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_62 = params.Pg_N_init{62};
else
  error 'could not find Pg_N_init_62'
end
if isfield(params, 'Pg_N_init_63')
  Pg_N_init_63 = params.Pg_N_init_63;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_63 = params.Pg_N_init{63};
else
  error 'could not find Pg_N_init_63'
end
if isfield(params, 'Pg_N_init_64')
  Pg_N_init_64 = params.Pg_N_init_64;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_64 = params.Pg_N_init{64};
else
  error 'could not find Pg_N_init_64'
end
if isfield(params, 'Pg_N_init_65')
  Pg_N_init_65 = params.Pg_N_init_65;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_65 = params.Pg_N_init{65};
else
  error 'could not find Pg_N_init_65'
end
if isfield(params, 'Pg_N_init_66')
  Pg_N_init_66 = params.Pg_N_init_66;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_66 = params.Pg_N_init{66};
else
  error 'could not find Pg_N_init_66'
end
if isfield(params, 'Pg_N_init_67')
  Pg_N_init_67 = params.Pg_N_init_67;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_67 = params.Pg_N_init{67};
else
  error 'could not find Pg_N_init_67'
end
if isfield(params, 'Pg_N_init_68')
  Pg_N_init_68 = params.Pg_N_init_68;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_68 = params.Pg_N_init{68};
else
  error 'could not find Pg_N_init_68'
end
if isfield(params, 'Pg_N_init_69')
  Pg_N_init_69 = params.Pg_N_init_69;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_69 = params.Pg_N_init{69};
else
  error 'could not find Pg_N_init_69'
end
if isfield(params, 'Pg_N_init_70')
  Pg_N_init_70 = params.Pg_N_init_70;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_70 = params.Pg_N_init{70};
else
  error 'could not find Pg_N_init_70'
end
if isfield(params, 'Pg_N_init_71')
  Pg_N_init_71 = params.Pg_N_init_71;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_71 = params.Pg_N_init{71};
else
  error 'could not find Pg_N_init_71'
end
if isfield(params, 'Pg_N_init_72')
  Pg_N_init_72 = params.Pg_N_init_72;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_72 = params.Pg_N_init{72};
else
  error 'could not find Pg_N_init_72'
end
if isfield(params, 'Pg_N_init_73')
  Pg_N_init_73 = params.Pg_N_init_73;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_73 = params.Pg_N_init{73};
else
  error 'could not find Pg_N_init_73'
end
if isfield(params, 'Pg_N_init_74')
  Pg_N_init_74 = params.Pg_N_init_74;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_74 = params.Pg_N_init{74};
else
  error 'could not find Pg_N_init_74'
end
if isfield(params, 'Pg_N_init_75')
  Pg_N_init_75 = params.Pg_N_init_75;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_75 = params.Pg_N_init{75};
else
  error 'could not find Pg_N_init_75'
end
if isfield(params, 'Pg_N_init_76')
  Pg_N_init_76 = params.Pg_N_init_76;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_76 = params.Pg_N_init{76};
else
  error 'could not find Pg_N_init_76'
end
if isfield(params, 'Pg_N_init_77')
  Pg_N_init_77 = params.Pg_N_init_77;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_77 = params.Pg_N_init{77};
else
  error 'could not find Pg_N_init_77'
end
if isfield(params, 'Pg_N_init_78')
  Pg_N_init_78 = params.Pg_N_init_78;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_78 = params.Pg_N_init{78};
else
  error 'could not find Pg_N_init_78'
end
if isfield(params, 'Pg_N_init_79')
  Pg_N_init_79 = params.Pg_N_init_79;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_79 = params.Pg_N_init{79};
else
  error 'could not find Pg_N_init_79'
end
if isfield(params, 'Pg_N_init_80')
  Pg_N_init_80 = params.Pg_N_init_80;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_80 = params.Pg_N_init{80};
else
  error 'could not find Pg_N_init_80'
end
if isfield(params, 'Pg_N_init_81')
  Pg_N_init_81 = params.Pg_N_init_81;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_81 = params.Pg_N_init{81};
else
  error 'could not find Pg_N_init_81'
end
if isfield(params, 'Pg_N_init_82')
  Pg_N_init_82 = params.Pg_N_init_82;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_82 = params.Pg_N_init{82};
else
  error 'could not find Pg_N_init_82'
end
if isfield(params, 'Pg_N_init_83')
  Pg_N_init_83 = params.Pg_N_init_83;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_83 = params.Pg_N_init{83};
else
  error 'could not find Pg_N_init_83'
end
if isfield(params, 'Pg_N_init_84')
  Pg_N_init_84 = params.Pg_N_init_84;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_84 = params.Pg_N_init{84};
else
  error 'could not find Pg_N_init_84'
end
if isfield(params, 'Pg_N_init_85')
  Pg_N_init_85 = params.Pg_N_init_85;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_85 = params.Pg_N_init{85};
else
  error 'could not find Pg_N_init_85'
end
if isfield(params, 'Pg_N_init_86')
  Pg_N_init_86 = params.Pg_N_init_86;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_86 = params.Pg_N_init{86};
else
  error 'could not find Pg_N_init_86'
end
if isfield(params, 'Pg_N_init_87')
  Pg_N_init_87 = params.Pg_N_init_87;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_87 = params.Pg_N_init{87};
else
  error 'could not find Pg_N_init_87'
end
if isfield(params, 'Pg_N_init_88')
  Pg_N_init_88 = params.Pg_N_init_88;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_88 = params.Pg_N_init{88};
else
  error 'could not find Pg_N_init_88'
end
if isfield(params, 'Pg_N_init_89')
  Pg_N_init_89 = params.Pg_N_init_89;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_89 = params.Pg_N_init{89};
else
  error 'could not find Pg_N_init_89'
end
if isfield(params, 'Pg_N_init_90')
  Pg_N_init_90 = params.Pg_N_init_90;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_90 = params.Pg_N_init{90};
else
  error 'could not find Pg_N_init_90'
end
if isfield(params, 'Pg_N_init_91')
  Pg_N_init_91 = params.Pg_N_init_91;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_91 = params.Pg_N_init{91};
else
  error 'could not find Pg_N_init_91'
end
if isfield(params, 'Pg_N_init_92')
  Pg_N_init_92 = params.Pg_N_init_92;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_92 = params.Pg_N_init{92};
else
  error 'could not find Pg_N_init_92'
end
if isfield(params, 'Pg_N_init_93')
  Pg_N_init_93 = params.Pg_N_init_93;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_93 = params.Pg_N_init{93};
else
  error 'could not find Pg_N_init_93'
end
if isfield(params, 'Pg_N_init_94')
  Pg_N_init_94 = params.Pg_N_init_94;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_94 = params.Pg_N_init{94};
else
  error 'could not find Pg_N_init_94'
end
if isfield(params, 'Pg_N_init_95')
  Pg_N_init_95 = params.Pg_N_init_95;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_95 = params.Pg_N_init{95};
else
  error 'could not find Pg_N_init_95'
end
if isfield(params, 'Pg_N_init_96')
  Pg_N_init_96 = params.Pg_N_init_96;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_96 = params.Pg_N_init{96};
else
  error 'could not find Pg_N_init_96'
end
if isfield(params, 'Pg_N_init_97')
  Pg_N_init_97 = params.Pg_N_init_97;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_97 = params.Pg_N_init{97};
else
  error 'could not find Pg_N_init_97'
end
if isfield(params, 'Pg_N_init_98')
  Pg_N_init_98 = params.Pg_N_init_98;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_98 = params.Pg_N_init{98};
else
  error 'could not find Pg_N_init_98'
end
if isfield(params, 'Pg_N_init_99')
  Pg_N_init_99 = params.Pg_N_init_99;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_99 = params.Pg_N_init{99};
else
  error 'could not find Pg_N_init_99'
end
if isfield(params, 'Pg_N_init_100')
  Pg_N_init_100 = params.Pg_N_init_100;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_100 = params.Pg_N_init{100};
else
  error 'could not find Pg_N_init_100'
end
if isfield(params, 'Pg_N_init_101')
  Pg_N_init_101 = params.Pg_N_init_101;
elseif isfield(params, 'Pg_N_init')
  Pg_N_init_101 = params.Pg_N_init{101};
else
  error 'could not find Pg_N_init_101'
end
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
if isfield(params, 'Thetag_N_avg_11')
  Thetag_N_avg_11 = params.Thetag_N_avg_11;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_11 = params.Thetag_N_avg{11};
else
  error 'could not find Thetag_N_avg_11'
end
if isfield(params, 'Thetag_N_avg_12')
  Thetag_N_avg_12 = params.Thetag_N_avg_12;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_12 = params.Thetag_N_avg{12};
else
  error 'could not find Thetag_N_avg_12'
end
if isfield(params, 'Thetag_N_avg_13')
  Thetag_N_avg_13 = params.Thetag_N_avg_13;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_13 = params.Thetag_N_avg{13};
else
  error 'could not find Thetag_N_avg_13'
end
if isfield(params, 'Thetag_N_avg_14')
  Thetag_N_avg_14 = params.Thetag_N_avg_14;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_14 = params.Thetag_N_avg{14};
else
  error 'could not find Thetag_N_avg_14'
end
if isfield(params, 'Thetag_N_avg_15')
  Thetag_N_avg_15 = params.Thetag_N_avg_15;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_15 = params.Thetag_N_avg{15};
else
  error 'could not find Thetag_N_avg_15'
end
if isfield(params, 'Thetag_N_avg_16')
  Thetag_N_avg_16 = params.Thetag_N_avg_16;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_16 = params.Thetag_N_avg{16};
else
  error 'could not find Thetag_N_avg_16'
end
if isfield(params, 'Thetag_N_avg_17')
  Thetag_N_avg_17 = params.Thetag_N_avg_17;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_17 = params.Thetag_N_avg{17};
else
  error 'could not find Thetag_N_avg_17'
end
if isfield(params, 'Thetag_N_avg_18')
  Thetag_N_avg_18 = params.Thetag_N_avg_18;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_18 = params.Thetag_N_avg{18};
else
  error 'could not find Thetag_N_avg_18'
end
if isfield(params, 'Thetag_N_avg_19')
  Thetag_N_avg_19 = params.Thetag_N_avg_19;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_19 = params.Thetag_N_avg{19};
else
  error 'could not find Thetag_N_avg_19'
end
if isfield(params, 'Thetag_N_avg_20')
  Thetag_N_avg_20 = params.Thetag_N_avg_20;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_20 = params.Thetag_N_avg{20};
else
  error 'could not find Thetag_N_avg_20'
end
if isfield(params, 'Thetag_N_avg_21')
  Thetag_N_avg_21 = params.Thetag_N_avg_21;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_21 = params.Thetag_N_avg{21};
else
  error 'could not find Thetag_N_avg_21'
end
if isfield(params, 'Thetag_N_avg_22')
  Thetag_N_avg_22 = params.Thetag_N_avg_22;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_22 = params.Thetag_N_avg{22};
else
  error 'could not find Thetag_N_avg_22'
end
if isfield(params, 'Thetag_N_avg_23')
  Thetag_N_avg_23 = params.Thetag_N_avg_23;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_23 = params.Thetag_N_avg{23};
else
  error 'could not find Thetag_N_avg_23'
end
if isfield(params, 'Thetag_N_avg_24')
  Thetag_N_avg_24 = params.Thetag_N_avg_24;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_24 = params.Thetag_N_avg{24};
else
  error 'could not find Thetag_N_avg_24'
end
if isfield(params, 'Thetag_N_avg_25')
  Thetag_N_avg_25 = params.Thetag_N_avg_25;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_25 = params.Thetag_N_avg{25};
else
  error 'could not find Thetag_N_avg_25'
end
if isfield(params, 'Thetag_N_avg_26')
  Thetag_N_avg_26 = params.Thetag_N_avg_26;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_26 = params.Thetag_N_avg{26};
else
  error 'could not find Thetag_N_avg_26'
end
if isfield(params, 'Thetag_N_avg_27')
  Thetag_N_avg_27 = params.Thetag_N_avg_27;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_27 = params.Thetag_N_avg{27};
else
  error 'could not find Thetag_N_avg_27'
end
if isfield(params, 'Thetag_N_avg_28')
  Thetag_N_avg_28 = params.Thetag_N_avg_28;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_28 = params.Thetag_N_avg{28};
else
  error 'could not find Thetag_N_avg_28'
end
if isfield(params, 'Thetag_N_avg_29')
  Thetag_N_avg_29 = params.Thetag_N_avg_29;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_29 = params.Thetag_N_avg{29};
else
  error 'could not find Thetag_N_avg_29'
end
if isfield(params, 'Thetag_N_avg_30')
  Thetag_N_avg_30 = params.Thetag_N_avg_30;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_30 = params.Thetag_N_avg{30};
else
  error 'could not find Thetag_N_avg_30'
end
if isfield(params, 'Thetag_N_avg_31')
  Thetag_N_avg_31 = params.Thetag_N_avg_31;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_31 = params.Thetag_N_avg{31};
else
  error 'could not find Thetag_N_avg_31'
end
if isfield(params, 'Thetag_N_avg_32')
  Thetag_N_avg_32 = params.Thetag_N_avg_32;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_32 = params.Thetag_N_avg{32};
else
  error 'could not find Thetag_N_avg_32'
end
if isfield(params, 'Thetag_N_avg_33')
  Thetag_N_avg_33 = params.Thetag_N_avg_33;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_33 = params.Thetag_N_avg{33};
else
  error 'could not find Thetag_N_avg_33'
end
if isfield(params, 'Thetag_N_avg_34')
  Thetag_N_avg_34 = params.Thetag_N_avg_34;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_34 = params.Thetag_N_avg{34};
else
  error 'could not find Thetag_N_avg_34'
end
if isfield(params, 'Thetag_N_avg_35')
  Thetag_N_avg_35 = params.Thetag_N_avg_35;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_35 = params.Thetag_N_avg{35};
else
  error 'could not find Thetag_N_avg_35'
end
if isfield(params, 'Thetag_N_avg_36')
  Thetag_N_avg_36 = params.Thetag_N_avg_36;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_36 = params.Thetag_N_avg{36};
else
  error 'could not find Thetag_N_avg_36'
end
if isfield(params, 'Thetag_N_avg_37')
  Thetag_N_avg_37 = params.Thetag_N_avg_37;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_37 = params.Thetag_N_avg{37};
else
  error 'could not find Thetag_N_avg_37'
end
if isfield(params, 'Thetag_N_avg_38')
  Thetag_N_avg_38 = params.Thetag_N_avg_38;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_38 = params.Thetag_N_avg{38};
else
  error 'could not find Thetag_N_avg_38'
end
if isfield(params, 'Thetag_N_avg_39')
  Thetag_N_avg_39 = params.Thetag_N_avg_39;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_39 = params.Thetag_N_avg{39};
else
  error 'could not find Thetag_N_avg_39'
end
if isfield(params, 'Thetag_N_avg_40')
  Thetag_N_avg_40 = params.Thetag_N_avg_40;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_40 = params.Thetag_N_avg{40};
else
  error 'could not find Thetag_N_avg_40'
end
if isfield(params, 'Thetag_N_avg_41')
  Thetag_N_avg_41 = params.Thetag_N_avg_41;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_41 = params.Thetag_N_avg{41};
else
  error 'could not find Thetag_N_avg_41'
end
if isfield(params, 'Thetag_N_avg_42')
  Thetag_N_avg_42 = params.Thetag_N_avg_42;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_42 = params.Thetag_N_avg{42};
else
  error 'could not find Thetag_N_avg_42'
end
if isfield(params, 'Thetag_N_avg_43')
  Thetag_N_avg_43 = params.Thetag_N_avg_43;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_43 = params.Thetag_N_avg{43};
else
  error 'could not find Thetag_N_avg_43'
end
if isfield(params, 'Thetag_N_avg_44')
  Thetag_N_avg_44 = params.Thetag_N_avg_44;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_44 = params.Thetag_N_avg{44};
else
  error 'could not find Thetag_N_avg_44'
end
if isfield(params, 'Thetag_N_avg_45')
  Thetag_N_avg_45 = params.Thetag_N_avg_45;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_45 = params.Thetag_N_avg{45};
else
  error 'could not find Thetag_N_avg_45'
end
if isfield(params, 'Thetag_N_avg_46')
  Thetag_N_avg_46 = params.Thetag_N_avg_46;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_46 = params.Thetag_N_avg{46};
else
  error 'could not find Thetag_N_avg_46'
end
if isfield(params, 'Thetag_N_avg_47')
  Thetag_N_avg_47 = params.Thetag_N_avg_47;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_47 = params.Thetag_N_avg{47};
else
  error 'could not find Thetag_N_avg_47'
end
if isfield(params, 'Thetag_N_avg_48')
  Thetag_N_avg_48 = params.Thetag_N_avg_48;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_48 = params.Thetag_N_avg{48};
else
  error 'could not find Thetag_N_avg_48'
end
if isfield(params, 'Thetag_N_avg_49')
  Thetag_N_avg_49 = params.Thetag_N_avg_49;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_49 = params.Thetag_N_avg{49};
else
  error 'could not find Thetag_N_avg_49'
end
if isfield(params, 'Thetag_N_avg_50')
  Thetag_N_avg_50 = params.Thetag_N_avg_50;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_50 = params.Thetag_N_avg{50};
else
  error 'could not find Thetag_N_avg_50'
end
if isfield(params, 'Thetag_N_avg_51')
  Thetag_N_avg_51 = params.Thetag_N_avg_51;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_51 = params.Thetag_N_avg{51};
else
  error 'could not find Thetag_N_avg_51'
end
if isfield(params, 'Thetag_N_avg_52')
  Thetag_N_avg_52 = params.Thetag_N_avg_52;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_52 = params.Thetag_N_avg{52};
else
  error 'could not find Thetag_N_avg_52'
end
if isfield(params, 'Thetag_N_avg_53')
  Thetag_N_avg_53 = params.Thetag_N_avg_53;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_53 = params.Thetag_N_avg{53};
else
  error 'could not find Thetag_N_avg_53'
end
if isfield(params, 'Thetag_N_avg_54')
  Thetag_N_avg_54 = params.Thetag_N_avg_54;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_54 = params.Thetag_N_avg{54};
else
  error 'could not find Thetag_N_avg_54'
end
if isfield(params, 'Thetag_N_avg_55')
  Thetag_N_avg_55 = params.Thetag_N_avg_55;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_55 = params.Thetag_N_avg{55};
else
  error 'could not find Thetag_N_avg_55'
end
if isfield(params, 'Thetag_N_avg_56')
  Thetag_N_avg_56 = params.Thetag_N_avg_56;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_56 = params.Thetag_N_avg{56};
else
  error 'could not find Thetag_N_avg_56'
end
if isfield(params, 'Thetag_N_avg_57')
  Thetag_N_avg_57 = params.Thetag_N_avg_57;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_57 = params.Thetag_N_avg{57};
else
  error 'could not find Thetag_N_avg_57'
end
if isfield(params, 'Thetag_N_avg_58')
  Thetag_N_avg_58 = params.Thetag_N_avg_58;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_58 = params.Thetag_N_avg{58};
else
  error 'could not find Thetag_N_avg_58'
end
if isfield(params, 'Thetag_N_avg_59')
  Thetag_N_avg_59 = params.Thetag_N_avg_59;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_59 = params.Thetag_N_avg{59};
else
  error 'could not find Thetag_N_avg_59'
end
if isfield(params, 'Thetag_N_avg_60')
  Thetag_N_avg_60 = params.Thetag_N_avg_60;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_60 = params.Thetag_N_avg{60};
else
  error 'could not find Thetag_N_avg_60'
end
if isfield(params, 'Thetag_N_avg_61')
  Thetag_N_avg_61 = params.Thetag_N_avg_61;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_61 = params.Thetag_N_avg{61};
else
  error 'could not find Thetag_N_avg_61'
end
if isfield(params, 'Thetag_N_avg_62')
  Thetag_N_avg_62 = params.Thetag_N_avg_62;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_62 = params.Thetag_N_avg{62};
else
  error 'could not find Thetag_N_avg_62'
end
if isfield(params, 'Thetag_N_avg_63')
  Thetag_N_avg_63 = params.Thetag_N_avg_63;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_63 = params.Thetag_N_avg{63};
else
  error 'could not find Thetag_N_avg_63'
end
if isfield(params, 'Thetag_N_avg_64')
  Thetag_N_avg_64 = params.Thetag_N_avg_64;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_64 = params.Thetag_N_avg{64};
else
  error 'could not find Thetag_N_avg_64'
end
if isfield(params, 'Thetag_N_avg_65')
  Thetag_N_avg_65 = params.Thetag_N_avg_65;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_65 = params.Thetag_N_avg{65};
else
  error 'could not find Thetag_N_avg_65'
end
if isfield(params, 'Thetag_N_avg_66')
  Thetag_N_avg_66 = params.Thetag_N_avg_66;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_66 = params.Thetag_N_avg{66};
else
  error 'could not find Thetag_N_avg_66'
end
if isfield(params, 'Thetag_N_avg_67')
  Thetag_N_avg_67 = params.Thetag_N_avg_67;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_67 = params.Thetag_N_avg{67};
else
  error 'could not find Thetag_N_avg_67'
end
if isfield(params, 'Thetag_N_avg_68')
  Thetag_N_avg_68 = params.Thetag_N_avg_68;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_68 = params.Thetag_N_avg{68};
else
  error 'could not find Thetag_N_avg_68'
end
if isfield(params, 'Thetag_N_avg_69')
  Thetag_N_avg_69 = params.Thetag_N_avg_69;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_69 = params.Thetag_N_avg{69};
else
  error 'could not find Thetag_N_avg_69'
end
if isfield(params, 'Thetag_N_avg_70')
  Thetag_N_avg_70 = params.Thetag_N_avg_70;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_70 = params.Thetag_N_avg{70};
else
  error 'could not find Thetag_N_avg_70'
end
if isfield(params, 'Thetag_N_avg_71')
  Thetag_N_avg_71 = params.Thetag_N_avg_71;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_71 = params.Thetag_N_avg{71};
else
  error 'could not find Thetag_N_avg_71'
end
if isfield(params, 'Thetag_N_avg_72')
  Thetag_N_avg_72 = params.Thetag_N_avg_72;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_72 = params.Thetag_N_avg{72};
else
  error 'could not find Thetag_N_avg_72'
end
if isfield(params, 'Thetag_N_avg_73')
  Thetag_N_avg_73 = params.Thetag_N_avg_73;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_73 = params.Thetag_N_avg{73};
else
  error 'could not find Thetag_N_avg_73'
end
if isfield(params, 'Thetag_N_avg_74')
  Thetag_N_avg_74 = params.Thetag_N_avg_74;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_74 = params.Thetag_N_avg{74};
else
  error 'could not find Thetag_N_avg_74'
end
if isfield(params, 'Thetag_N_avg_75')
  Thetag_N_avg_75 = params.Thetag_N_avg_75;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_75 = params.Thetag_N_avg{75};
else
  error 'could not find Thetag_N_avg_75'
end
if isfield(params, 'Thetag_N_avg_76')
  Thetag_N_avg_76 = params.Thetag_N_avg_76;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_76 = params.Thetag_N_avg{76};
else
  error 'could not find Thetag_N_avg_76'
end
if isfield(params, 'Thetag_N_avg_77')
  Thetag_N_avg_77 = params.Thetag_N_avg_77;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_77 = params.Thetag_N_avg{77};
else
  error 'could not find Thetag_N_avg_77'
end
if isfield(params, 'Thetag_N_avg_78')
  Thetag_N_avg_78 = params.Thetag_N_avg_78;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_78 = params.Thetag_N_avg{78};
else
  error 'could not find Thetag_N_avg_78'
end
if isfield(params, 'Thetag_N_avg_79')
  Thetag_N_avg_79 = params.Thetag_N_avg_79;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_79 = params.Thetag_N_avg{79};
else
  error 'could not find Thetag_N_avg_79'
end
if isfield(params, 'Thetag_N_avg_80')
  Thetag_N_avg_80 = params.Thetag_N_avg_80;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_80 = params.Thetag_N_avg{80};
else
  error 'could not find Thetag_N_avg_80'
end
if isfield(params, 'Thetag_N_avg_81')
  Thetag_N_avg_81 = params.Thetag_N_avg_81;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_81 = params.Thetag_N_avg{81};
else
  error 'could not find Thetag_N_avg_81'
end
if isfield(params, 'Thetag_N_avg_82')
  Thetag_N_avg_82 = params.Thetag_N_avg_82;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_82 = params.Thetag_N_avg{82};
else
  error 'could not find Thetag_N_avg_82'
end
if isfield(params, 'Thetag_N_avg_83')
  Thetag_N_avg_83 = params.Thetag_N_avg_83;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_83 = params.Thetag_N_avg{83};
else
  error 'could not find Thetag_N_avg_83'
end
if isfield(params, 'Thetag_N_avg_84')
  Thetag_N_avg_84 = params.Thetag_N_avg_84;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_84 = params.Thetag_N_avg{84};
else
  error 'could not find Thetag_N_avg_84'
end
if isfield(params, 'Thetag_N_avg_85')
  Thetag_N_avg_85 = params.Thetag_N_avg_85;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_85 = params.Thetag_N_avg{85};
else
  error 'could not find Thetag_N_avg_85'
end
if isfield(params, 'Thetag_N_avg_86')
  Thetag_N_avg_86 = params.Thetag_N_avg_86;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_86 = params.Thetag_N_avg{86};
else
  error 'could not find Thetag_N_avg_86'
end
if isfield(params, 'Thetag_N_avg_87')
  Thetag_N_avg_87 = params.Thetag_N_avg_87;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_87 = params.Thetag_N_avg{87};
else
  error 'could not find Thetag_N_avg_87'
end
if isfield(params, 'Thetag_N_avg_88')
  Thetag_N_avg_88 = params.Thetag_N_avg_88;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_88 = params.Thetag_N_avg{88};
else
  error 'could not find Thetag_N_avg_88'
end
if isfield(params, 'Thetag_N_avg_89')
  Thetag_N_avg_89 = params.Thetag_N_avg_89;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_89 = params.Thetag_N_avg{89};
else
  error 'could not find Thetag_N_avg_89'
end
if isfield(params, 'Thetag_N_avg_90')
  Thetag_N_avg_90 = params.Thetag_N_avg_90;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_90 = params.Thetag_N_avg{90};
else
  error 'could not find Thetag_N_avg_90'
end
if isfield(params, 'Thetag_N_avg_91')
  Thetag_N_avg_91 = params.Thetag_N_avg_91;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_91 = params.Thetag_N_avg{91};
else
  error 'could not find Thetag_N_avg_91'
end
if isfield(params, 'Thetag_N_avg_92')
  Thetag_N_avg_92 = params.Thetag_N_avg_92;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_92 = params.Thetag_N_avg{92};
else
  error 'could not find Thetag_N_avg_92'
end
if isfield(params, 'Thetag_N_avg_93')
  Thetag_N_avg_93 = params.Thetag_N_avg_93;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_93 = params.Thetag_N_avg{93};
else
  error 'could not find Thetag_N_avg_93'
end
if isfield(params, 'Thetag_N_avg_94')
  Thetag_N_avg_94 = params.Thetag_N_avg_94;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_94 = params.Thetag_N_avg{94};
else
  error 'could not find Thetag_N_avg_94'
end
if isfield(params, 'Thetag_N_avg_95')
  Thetag_N_avg_95 = params.Thetag_N_avg_95;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_95 = params.Thetag_N_avg{95};
else
  error 'could not find Thetag_N_avg_95'
end
if isfield(params, 'Thetag_N_avg_96')
  Thetag_N_avg_96 = params.Thetag_N_avg_96;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_96 = params.Thetag_N_avg{96};
else
  error 'could not find Thetag_N_avg_96'
end
if isfield(params, 'Thetag_N_avg_97')
  Thetag_N_avg_97 = params.Thetag_N_avg_97;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_97 = params.Thetag_N_avg{97};
else
  error 'could not find Thetag_N_avg_97'
end
if isfield(params, 'Thetag_N_avg_98')
  Thetag_N_avg_98 = params.Thetag_N_avg_98;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_98 = params.Thetag_N_avg{98};
else
  error 'could not find Thetag_N_avg_98'
end
if isfield(params, 'Thetag_N_avg_99')
  Thetag_N_avg_99 = params.Thetag_N_avg_99;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_99 = params.Thetag_N_avg{99};
else
  error 'could not find Thetag_N_avg_99'
end
if isfield(params, 'Thetag_N_avg_100')
  Thetag_N_avg_100 = params.Thetag_N_avg_100;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_100 = params.Thetag_N_avg{100};
else
  error 'could not find Thetag_N_avg_100'
end
if isfield(params, 'Thetag_N_avg_101')
  Thetag_N_avg_101 = params.Thetag_N_avg_101;
elseif isfield(params, 'Thetag_N_avg')
  Thetag_N_avg_101 = params.Thetag_N_avg{101};
else
  error 'could not find Thetag_N_avg_101'
end
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
if isfield(params, 'Vg_N_avg_11')
  Vg_N_avg_11 = params.Vg_N_avg_11;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_11 = params.Vg_N_avg{11};
else
  error 'could not find Vg_N_avg_11'
end
if isfield(params, 'Vg_N_avg_12')
  Vg_N_avg_12 = params.Vg_N_avg_12;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_12 = params.Vg_N_avg{12};
else
  error 'could not find Vg_N_avg_12'
end
if isfield(params, 'Vg_N_avg_13')
  Vg_N_avg_13 = params.Vg_N_avg_13;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_13 = params.Vg_N_avg{13};
else
  error 'could not find Vg_N_avg_13'
end
if isfield(params, 'Vg_N_avg_14')
  Vg_N_avg_14 = params.Vg_N_avg_14;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_14 = params.Vg_N_avg{14};
else
  error 'could not find Vg_N_avg_14'
end
if isfield(params, 'Vg_N_avg_15')
  Vg_N_avg_15 = params.Vg_N_avg_15;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_15 = params.Vg_N_avg{15};
else
  error 'could not find Vg_N_avg_15'
end
if isfield(params, 'Vg_N_avg_16')
  Vg_N_avg_16 = params.Vg_N_avg_16;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_16 = params.Vg_N_avg{16};
else
  error 'could not find Vg_N_avg_16'
end
if isfield(params, 'Vg_N_avg_17')
  Vg_N_avg_17 = params.Vg_N_avg_17;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_17 = params.Vg_N_avg{17};
else
  error 'could not find Vg_N_avg_17'
end
if isfield(params, 'Vg_N_avg_18')
  Vg_N_avg_18 = params.Vg_N_avg_18;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_18 = params.Vg_N_avg{18};
else
  error 'could not find Vg_N_avg_18'
end
if isfield(params, 'Vg_N_avg_19')
  Vg_N_avg_19 = params.Vg_N_avg_19;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_19 = params.Vg_N_avg{19};
else
  error 'could not find Vg_N_avg_19'
end
if isfield(params, 'Vg_N_avg_20')
  Vg_N_avg_20 = params.Vg_N_avg_20;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_20 = params.Vg_N_avg{20};
else
  error 'could not find Vg_N_avg_20'
end
if isfield(params, 'Vg_N_avg_21')
  Vg_N_avg_21 = params.Vg_N_avg_21;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_21 = params.Vg_N_avg{21};
else
  error 'could not find Vg_N_avg_21'
end
if isfield(params, 'Vg_N_avg_22')
  Vg_N_avg_22 = params.Vg_N_avg_22;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_22 = params.Vg_N_avg{22};
else
  error 'could not find Vg_N_avg_22'
end
if isfield(params, 'Vg_N_avg_23')
  Vg_N_avg_23 = params.Vg_N_avg_23;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_23 = params.Vg_N_avg{23};
else
  error 'could not find Vg_N_avg_23'
end
if isfield(params, 'Vg_N_avg_24')
  Vg_N_avg_24 = params.Vg_N_avg_24;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_24 = params.Vg_N_avg{24};
else
  error 'could not find Vg_N_avg_24'
end
if isfield(params, 'Vg_N_avg_25')
  Vg_N_avg_25 = params.Vg_N_avg_25;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_25 = params.Vg_N_avg{25};
else
  error 'could not find Vg_N_avg_25'
end
if isfield(params, 'Vg_N_avg_26')
  Vg_N_avg_26 = params.Vg_N_avg_26;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_26 = params.Vg_N_avg{26};
else
  error 'could not find Vg_N_avg_26'
end
if isfield(params, 'Vg_N_avg_27')
  Vg_N_avg_27 = params.Vg_N_avg_27;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_27 = params.Vg_N_avg{27};
else
  error 'could not find Vg_N_avg_27'
end
if isfield(params, 'Vg_N_avg_28')
  Vg_N_avg_28 = params.Vg_N_avg_28;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_28 = params.Vg_N_avg{28};
else
  error 'could not find Vg_N_avg_28'
end
if isfield(params, 'Vg_N_avg_29')
  Vg_N_avg_29 = params.Vg_N_avg_29;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_29 = params.Vg_N_avg{29};
else
  error 'could not find Vg_N_avg_29'
end
if isfield(params, 'Vg_N_avg_30')
  Vg_N_avg_30 = params.Vg_N_avg_30;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_30 = params.Vg_N_avg{30};
else
  error 'could not find Vg_N_avg_30'
end
if isfield(params, 'Vg_N_avg_31')
  Vg_N_avg_31 = params.Vg_N_avg_31;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_31 = params.Vg_N_avg{31};
else
  error 'could not find Vg_N_avg_31'
end
if isfield(params, 'Vg_N_avg_32')
  Vg_N_avg_32 = params.Vg_N_avg_32;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_32 = params.Vg_N_avg{32};
else
  error 'could not find Vg_N_avg_32'
end
if isfield(params, 'Vg_N_avg_33')
  Vg_N_avg_33 = params.Vg_N_avg_33;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_33 = params.Vg_N_avg{33};
else
  error 'could not find Vg_N_avg_33'
end
if isfield(params, 'Vg_N_avg_34')
  Vg_N_avg_34 = params.Vg_N_avg_34;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_34 = params.Vg_N_avg{34};
else
  error 'could not find Vg_N_avg_34'
end
if isfield(params, 'Vg_N_avg_35')
  Vg_N_avg_35 = params.Vg_N_avg_35;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_35 = params.Vg_N_avg{35};
else
  error 'could not find Vg_N_avg_35'
end
if isfield(params, 'Vg_N_avg_36')
  Vg_N_avg_36 = params.Vg_N_avg_36;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_36 = params.Vg_N_avg{36};
else
  error 'could not find Vg_N_avg_36'
end
if isfield(params, 'Vg_N_avg_37')
  Vg_N_avg_37 = params.Vg_N_avg_37;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_37 = params.Vg_N_avg{37};
else
  error 'could not find Vg_N_avg_37'
end
if isfield(params, 'Vg_N_avg_38')
  Vg_N_avg_38 = params.Vg_N_avg_38;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_38 = params.Vg_N_avg{38};
else
  error 'could not find Vg_N_avg_38'
end
if isfield(params, 'Vg_N_avg_39')
  Vg_N_avg_39 = params.Vg_N_avg_39;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_39 = params.Vg_N_avg{39};
else
  error 'could not find Vg_N_avg_39'
end
if isfield(params, 'Vg_N_avg_40')
  Vg_N_avg_40 = params.Vg_N_avg_40;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_40 = params.Vg_N_avg{40};
else
  error 'could not find Vg_N_avg_40'
end
if isfield(params, 'Vg_N_avg_41')
  Vg_N_avg_41 = params.Vg_N_avg_41;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_41 = params.Vg_N_avg{41};
else
  error 'could not find Vg_N_avg_41'
end
if isfield(params, 'Vg_N_avg_42')
  Vg_N_avg_42 = params.Vg_N_avg_42;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_42 = params.Vg_N_avg{42};
else
  error 'could not find Vg_N_avg_42'
end
if isfield(params, 'Vg_N_avg_43')
  Vg_N_avg_43 = params.Vg_N_avg_43;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_43 = params.Vg_N_avg{43};
else
  error 'could not find Vg_N_avg_43'
end
if isfield(params, 'Vg_N_avg_44')
  Vg_N_avg_44 = params.Vg_N_avg_44;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_44 = params.Vg_N_avg{44};
else
  error 'could not find Vg_N_avg_44'
end
if isfield(params, 'Vg_N_avg_45')
  Vg_N_avg_45 = params.Vg_N_avg_45;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_45 = params.Vg_N_avg{45};
else
  error 'could not find Vg_N_avg_45'
end
if isfield(params, 'Vg_N_avg_46')
  Vg_N_avg_46 = params.Vg_N_avg_46;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_46 = params.Vg_N_avg{46};
else
  error 'could not find Vg_N_avg_46'
end
if isfield(params, 'Vg_N_avg_47')
  Vg_N_avg_47 = params.Vg_N_avg_47;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_47 = params.Vg_N_avg{47};
else
  error 'could not find Vg_N_avg_47'
end
if isfield(params, 'Vg_N_avg_48')
  Vg_N_avg_48 = params.Vg_N_avg_48;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_48 = params.Vg_N_avg{48};
else
  error 'could not find Vg_N_avg_48'
end
if isfield(params, 'Vg_N_avg_49')
  Vg_N_avg_49 = params.Vg_N_avg_49;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_49 = params.Vg_N_avg{49};
else
  error 'could not find Vg_N_avg_49'
end
if isfield(params, 'Vg_N_avg_50')
  Vg_N_avg_50 = params.Vg_N_avg_50;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_50 = params.Vg_N_avg{50};
else
  error 'could not find Vg_N_avg_50'
end
if isfield(params, 'Vg_N_avg_51')
  Vg_N_avg_51 = params.Vg_N_avg_51;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_51 = params.Vg_N_avg{51};
else
  error 'could not find Vg_N_avg_51'
end
if isfield(params, 'Vg_N_avg_52')
  Vg_N_avg_52 = params.Vg_N_avg_52;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_52 = params.Vg_N_avg{52};
else
  error 'could not find Vg_N_avg_52'
end
if isfield(params, 'Vg_N_avg_53')
  Vg_N_avg_53 = params.Vg_N_avg_53;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_53 = params.Vg_N_avg{53};
else
  error 'could not find Vg_N_avg_53'
end
if isfield(params, 'Vg_N_avg_54')
  Vg_N_avg_54 = params.Vg_N_avg_54;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_54 = params.Vg_N_avg{54};
else
  error 'could not find Vg_N_avg_54'
end
if isfield(params, 'Vg_N_avg_55')
  Vg_N_avg_55 = params.Vg_N_avg_55;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_55 = params.Vg_N_avg{55};
else
  error 'could not find Vg_N_avg_55'
end
if isfield(params, 'Vg_N_avg_56')
  Vg_N_avg_56 = params.Vg_N_avg_56;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_56 = params.Vg_N_avg{56};
else
  error 'could not find Vg_N_avg_56'
end
if isfield(params, 'Vg_N_avg_57')
  Vg_N_avg_57 = params.Vg_N_avg_57;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_57 = params.Vg_N_avg{57};
else
  error 'could not find Vg_N_avg_57'
end
if isfield(params, 'Vg_N_avg_58')
  Vg_N_avg_58 = params.Vg_N_avg_58;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_58 = params.Vg_N_avg{58};
else
  error 'could not find Vg_N_avg_58'
end
if isfield(params, 'Vg_N_avg_59')
  Vg_N_avg_59 = params.Vg_N_avg_59;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_59 = params.Vg_N_avg{59};
else
  error 'could not find Vg_N_avg_59'
end
if isfield(params, 'Vg_N_avg_60')
  Vg_N_avg_60 = params.Vg_N_avg_60;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_60 = params.Vg_N_avg{60};
else
  error 'could not find Vg_N_avg_60'
end
if isfield(params, 'Vg_N_avg_61')
  Vg_N_avg_61 = params.Vg_N_avg_61;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_61 = params.Vg_N_avg{61};
else
  error 'could not find Vg_N_avg_61'
end
if isfield(params, 'Vg_N_avg_62')
  Vg_N_avg_62 = params.Vg_N_avg_62;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_62 = params.Vg_N_avg{62};
else
  error 'could not find Vg_N_avg_62'
end
if isfield(params, 'Vg_N_avg_63')
  Vg_N_avg_63 = params.Vg_N_avg_63;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_63 = params.Vg_N_avg{63};
else
  error 'could not find Vg_N_avg_63'
end
if isfield(params, 'Vg_N_avg_64')
  Vg_N_avg_64 = params.Vg_N_avg_64;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_64 = params.Vg_N_avg{64};
else
  error 'could not find Vg_N_avg_64'
end
if isfield(params, 'Vg_N_avg_65')
  Vg_N_avg_65 = params.Vg_N_avg_65;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_65 = params.Vg_N_avg{65};
else
  error 'could not find Vg_N_avg_65'
end
if isfield(params, 'Vg_N_avg_66')
  Vg_N_avg_66 = params.Vg_N_avg_66;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_66 = params.Vg_N_avg{66};
else
  error 'could not find Vg_N_avg_66'
end
if isfield(params, 'Vg_N_avg_67')
  Vg_N_avg_67 = params.Vg_N_avg_67;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_67 = params.Vg_N_avg{67};
else
  error 'could not find Vg_N_avg_67'
end
if isfield(params, 'Vg_N_avg_68')
  Vg_N_avg_68 = params.Vg_N_avg_68;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_68 = params.Vg_N_avg{68};
else
  error 'could not find Vg_N_avg_68'
end
if isfield(params, 'Vg_N_avg_69')
  Vg_N_avg_69 = params.Vg_N_avg_69;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_69 = params.Vg_N_avg{69};
else
  error 'could not find Vg_N_avg_69'
end
if isfield(params, 'Vg_N_avg_70')
  Vg_N_avg_70 = params.Vg_N_avg_70;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_70 = params.Vg_N_avg{70};
else
  error 'could not find Vg_N_avg_70'
end
if isfield(params, 'Vg_N_avg_71')
  Vg_N_avg_71 = params.Vg_N_avg_71;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_71 = params.Vg_N_avg{71};
else
  error 'could not find Vg_N_avg_71'
end
if isfield(params, 'Vg_N_avg_72')
  Vg_N_avg_72 = params.Vg_N_avg_72;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_72 = params.Vg_N_avg{72};
else
  error 'could not find Vg_N_avg_72'
end
if isfield(params, 'Vg_N_avg_73')
  Vg_N_avg_73 = params.Vg_N_avg_73;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_73 = params.Vg_N_avg{73};
else
  error 'could not find Vg_N_avg_73'
end
if isfield(params, 'Vg_N_avg_74')
  Vg_N_avg_74 = params.Vg_N_avg_74;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_74 = params.Vg_N_avg{74};
else
  error 'could not find Vg_N_avg_74'
end
if isfield(params, 'Vg_N_avg_75')
  Vg_N_avg_75 = params.Vg_N_avg_75;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_75 = params.Vg_N_avg{75};
else
  error 'could not find Vg_N_avg_75'
end
if isfield(params, 'Vg_N_avg_76')
  Vg_N_avg_76 = params.Vg_N_avg_76;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_76 = params.Vg_N_avg{76};
else
  error 'could not find Vg_N_avg_76'
end
if isfield(params, 'Vg_N_avg_77')
  Vg_N_avg_77 = params.Vg_N_avg_77;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_77 = params.Vg_N_avg{77};
else
  error 'could not find Vg_N_avg_77'
end
if isfield(params, 'Vg_N_avg_78')
  Vg_N_avg_78 = params.Vg_N_avg_78;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_78 = params.Vg_N_avg{78};
else
  error 'could not find Vg_N_avg_78'
end
if isfield(params, 'Vg_N_avg_79')
  Vg_N_avg_79 = params.Vg_N_avg_79;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_79 = params.Vg_N_avg{79};
else
  error 'could not find Vg_N_avg_79'
end
if isfield(params, 'Vg_N_avg_80')
  Vg_N_avg_80 = params.Vg_N_avg_80;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_80 = params.Vg_N_avg{80};
else
  error 'could not find Vg_N_avg_80'
end
if isfield(params, 'Vg_N_avg_81')
  Vg_N_avg_81 = params.Vg_N_avg_81;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_81 = params.Vg_N_avg{81};
else
  error 'could not find Vg_N_avg_81'
end
if isfield(params, 'Vg_N_avg_82')
  Vg_N_avg_82 = params.Vg_N_avg_82;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_82 = params.Vg_N_avg{82};
else
  error 'could not find Vg_N_avg_82'
end
if isfield(params, 'Vg_N_avg_83')
  Vg_N_avg_83 = params.Vg_N_avg_83;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_83 = params.Vg_N_avg{83};
else
  error 'could not find Vg_N_avg_83'
end
if isfield(params, 'Vg_N_avg_84')
  Vg_N_avg_84 = params.Vg_N_avg_84;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_84 = params.Vg_N_avg{84};
else
  error 'could not find Vg_N_avg_84'
end
if isfield(params, 'Vg_N_avg_85')
  Vg_N_avg_85 = params.Vg_N_avg_85;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_85 = params.Vg_N_avg{85};
else
  error 'could not find Vg_N_avg_85'
end
if isfield(params, 'Vg_N_avg_86')
  Vg_N_avg_86 = params.Vg_N_avg_86;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_86 = params.Vg_N_avg{86};
else
  error 'could not find Vg_N_avg_86'
end
if isfield(params, 'Vg_N_avg_87')
  Vg_N_avg_87 = params.Vg_N_avg_87;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_87 = params.Vg_N_avg{87};
else
  error 'could not find Vg_N_avg_87'
end
if isfield(params, 'Vg_N_avg_88')
  Vg_N_avg_88 = params.Vg_N_avg_88;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_88 = params.Vg_N_avg{88};
else
  error 'could not find Vg_N_avg_88'
end
if isfield(params, 'Vg_N_avg_89')
  Vg_N_avg_89 = params.Vg_N_avg_89;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_89 = params.Vg_N_avg{89};
else
  error 'could not find Vg_N_avg_89'
end
if isfield(params, 'Vg_N_avg_90')
  Vg_N_avg_90 = params.Vg_N_avg_90;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_90 = params.Vg_N_avg{90};
else
  error 'could not find Vg_N_avg_90'
end
if isfield(params, 'Vg_N_avg_91')
  Vg_N_avg_91 = params.Vg_N_avg_91;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_91 = params.Vg_N_avg{91};
else
  error 'could not find Vg_N_avg_91'
end
if isfield(params, 'Vg_N_avg_92')
  Vg_N_avg_92 = params.Vg_N_avg_92;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_92 = params.Vg_N_avg{92};
else
  error 'could not find Vg_N_avg_92'
end
if isfield(params, 'Vg_N_avg_93')
  Vg_N_avg_93 = params.Vg_N_avg_93;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_93 = params.Vg_N_avg{93};
else
  error 'could not find Vg_N_avg_93'
end
if isfield(params, 'Vg_N_avg_94')
  Vg_N_avg_94 = params.Vg_N_avg_94;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_94 = params.Vg_N_avg{94};
else
  error 'could not find Vg_N_avg_94'
end
if isfield(params, 'Vg_N_avg_95')
  Vg_N_avg_95 = params.Vg_N_avg_95;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_95 = params.Vg_N_avg{95};
else
  error 'could not find Vg_N_avg_95'
end
if isfield(params, 'Vg_N_avg_96')
  Vg_N_avg_96 = params.Vg_N_avg_96;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_96 = params.Vg_N_avg{96};
else
  error 'could not find Vg_N_avg_96'
end
if isfield(params, 'Vg_N_avg_97')
  Vg_N_avg_97 = params.Vg_N_avg_97;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_97 = params.Vg_N_avg{97};
else
  error 'could not find Vg_N_avg_97'
end
if isfield(params, 'Vg_N_avg_98')
  Vg_N_avg_98 = params.Vg_N_avg_98;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_98 = params.Vg_N_avg{98};
else
  error 'could not find Vg_N_avg_98'
end
if isfield(params, 'Vg_N_avg_99')
  Vg_N_avg_99 = params.Vg_N_avg_99;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_99 = params.Vg_N_avg{99};
else
  error 'could not find Vg_N_avg_99'
end
if isfield(params, 'Vg_N_avg_100')
  Vg_N_avg_100 = params.Vg_N_avg_100;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_100 = params.Vg_N_avg{100};
else
  error 'could not find Vg_N_avg_100'
end
if isfield(params, 'Vg_N_avg_101')
  Vg_N_avg_101 = params.Vg_N_avg_101;
elseif isfield(params, 'Vg_N_avg')
  Vg_N_avg_101 = params.Vg_N_avg{101};
else
  error 'could not find Vg_N_avg_101'
end
c0 = params.c0;
c1 = params.c1;
c2 = params.c2;
contNum = params.contNum;
rho = params.rho;
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
if isfield(params, 'ug_N_11')
  ug_N_11 = params.ug_N_11;
elseif isfield(params, 'ug_N')
  ug_N_11 = params.ug_N{11};
else
  error 'could not find ug_N_11'
end
if isfield(params, 'ug_N_12')
  ug_N_12 = params.ug_N_12;
elseif isfield(params, 'ug_N')
  ug_N_12 = params.ug_N{12};
else
  error 'could not find ug_N_12'
end
if isfield(params, 'ug_N_13')
  ug_N_13 = params.ug_N_13;
elseif isfield(params, 'ug_N')
  ug_N_13 = params.ug_N{13};
else
  error 'could not find ug_N_13'
end
if isfield(params, 'ug_N_14')
  ug_N_14 = params.ug_N_14;
elseif isfield(params, 'ug_N')
  ug_N_14 = params.ug_N{14};
else
  error 'could not find ug_N_14'
end
if isfield(params, 'ug_N_15')
  ug_N_15 = params.ug_N_15;
elseif isfield(params, 'ug_N')
  ug_N_15 = params.ug_N{15};
else
  error 'could not find ug_N_15'
end
if isfield(params, 'ug_N_16')
  ug_N_16 = params.ug_N_16;
elseif isfield(params, 'ug_N')
  ug_N_16 = params.ug_N{16};
else
  error 'could not find ug_N_16'
end
if isfield(params, 'ug_N_17')
  ug_N_17 = params.ug_N_17;
elseif isfield(params, 'ug_N')
  ug_N_17 = params.ug_N{17};
else
  error 'could not find ug_N_17'
end
if isfield(params, 'ug_N_18')
  ug_N_18 = params.ug_N_18;
elseif isfield(params, 'ug_N')
  ug_N_18 = params.ug_N{18};
else
  error 'could not find ug_N_18'
end
if isfield(params, 'ug_N_19')
  ug_N_19 = params.ug_N_19;
elseif isfield(params, 'ug_N')
  ug_N_19 = params.ug_N{19};
else
  error 'could not find ug_N_19'
end
if isfield(params, 'ug_N_20')
  ug_N_20 = params.ug_N_20;
elseif isfield(params, 'ug_N')
  ug_N_20 = params.ug_N{20};
else
  error 'could not find ug_N_20'
end
if isfield(params, 'ug_N_21')
  ug_N_21 = params.ug_N_21;
elseif isfield(params, 'ug_N')
  ug_N_21 = params.ug_N{21};
else
  error 'could not find ug_N_21'
end
if isfield(params, 'ug_N_22')
  ug_N_22 = params.ug_N_22;
elseif isfield(params, 'ug_N')
  ug_N_22 = params.ug_N{22};
else
  error 'could not find ug_N_22'
end
if isfield(params, 'ug_N_23')
  ug_N_23 = params.ug_N_23;
elseif isfield(params, 'ug_N')
  ug_N_23 = params.ug_N{23};
else
  error 'could not find ug_N_23'
end
if isfield(params, 'ug_N_24')
  ug_N_24 = params.ug_N_24;
elseif isfield(params, 'ug_N')
  ug_N_24 = params.ug_N{24};
else
  error 'could not find ug_N_24'
end
if isfield(params, 'ug_N_25')
  ug_N_25 = params.ug_N_25;
elseif isfield(params, 'ug_N')
  ug_N_25 = params.ug_N{25};
else
  error 'could not find ug_N_25'
end
if isfield(params, 'ug_N_26')
  ug_N_26 = params.ug_N_26;
elseif isfield(params, 'ug_N')
  ug_N_26 = params.ug_N{26};
else
  error 'could not find ug_N_26'
end
if isfield(params, 'ug_N_27')
  ug_N_27 = params.ug_N_27;
elseif isfield(params, 'ug_N')
  ug_N_27 = params.ug_N{27};
else
  error 'could not find ug_N_27'
end
if isfield(params, 'ug_N_28')
  ug_N_28 = params.ug_N_28;
elseif isfield(params, 'ug_N')
  ug_N_28 = params.ug_N{28};
else
  error 'could not find ug_N_28'
end
if isfield(params, 'ug_N_29')
  ug_N_29 = params.ug_N_29;
elseif isfield(params, 'ug_N')
  ug_N_29 = params.ug_N{29};
else
  error 'could not find ug_N_29'
end
if isfield(params, 'ug_N_30')
  ug_N_30 = params.ug_N_30;
elseif isfield(params, 'ug_N')
  ug_N_30 = params.ug_N{30};
else
  error 'could not find ug_N_30'
end
if isfield(params, 'ug_N_31')
  ug_N_31 = params.ug_N_31;
elseif isfield(params, 'ug_N')
  ug_N_31 = params.ug_N{31};
else
  error 'could not find ug_N_31'
end
if isfield(params, 'ug_N_32')
  ug_N_32 = params.ug_N_32;
elseif isfield(params, 'ug_N')
  ug_N_32 = params.ug_N{32};
else
  error 'could not find ug_N_32'
end
if isfield(params, 'ug_N_33')
  ug_N_33 = params.ug_N_33;
elseif isfield(params, 'ug_N')
  ug_N_33 = params.ug_N{33};
else
  error 'could not find ug_N_33'
end
if isfield(params, 'ug_N_34')
  ug_N_34 = params.ug_N_34;
elseif isfield(params, 'ug_N')
  ug_N_34 = params.ug_N{34};
else
  error 'could not find ug_N_34'
end
if isfield(params, 'ug_N_35')
  ug_N_35 = params.ug_N_35;
elseif isfield(params, 'ug_N')
  ug_N_35 = params.ug_N{35};
else
  error 'could not find ug_N_35'
end
if isfield(params, 'ug_N_36')
  ug_N_36 = params.ug_N_36;
elseif isfield(params, 'ug_N')
  ug_N_36 = params.ug_N{36};
else
  error 'could not find ug_N_36'
end
if isfield(params, 'ug_N_37')
  ug_N_37 = params.ug_N_37;
elseif isfield(params, 'ug_N')
  ug_N_37 = params.ug_N{37};
else
  error 'could not find ug_N_37'
end
if isfield(params, 'ug_N_38')
  ug_N_38 = params.ug_N_38;
elseif isfield(params, 'ug_N')
  ug_N_38 = params.ug_N{38};
else
  error 'could not find ug_N_38'
end
if isfield(params, 'ug_N_39')
  ug_N_39 = params.ug_N_39;
elseif isfield(params, 'ug_N')
  ug_N_39 = params.ug_N{39};
else
  error 'could not find ug_N_39'
end
if isfield(params, 'ug_N_40')
  ug_N_40 = params.ug_N_40;
elseif isfield(params, 'ug_N')
  ug_N_40 = params.ug_N{40};
else
  error 'could not find ug_N_40'
end
if isfield(params, 'ug_N_41')
  ug_N_41 = params.ug_N_41;
elseif isfield(params, 'ug_N')
  ug_N_41 = params.ug_N{41};
else
  error 'could not find ug_N_41'
end
if isfield(params, 'ug_N_42')
  ug_N_42 = params.ug_N_42;
elseif isfield(params, 'ug_N')
  ug_N_42 = params.ug_N{42};
else
  error 'could not find ug_N_42'
end
if isfield(params, 'ug_N_43')
  ug_N_43 = params.ug_N_43;
elseif isfield(params, 'ug_N')
  ug_N_43 = params.ug_N{43};
else
  error 'could not find ug_N_43'
end
if isfield(params, 'ug_N_44')
  ug_N_44 = params.ug_N_44;
elseif isfield(params, 'ug_N')
  ug_N_44 = params.ug_N{44};
else
  error 'could not find ug_N_44'
end
if isfield(params, 'ug_N_45')
  ug_N_45 = params.ug_N_45;
elseif isfield(params, 'ug_N')
  ug_N_45 = params.ug_N{45};
else
  error 'could not find ug_N_45'
end
if isfield(params, 'ug_N_46')
  ug_N_46 = params.ug_N_46;
elseif isfield(params, 'ug_N')
  ug_N_46 = params.ug_N{46};
else
  error 'could not find ug_N_46'
end
if isfield(params, 'ug_N_47')
  ug_N_47 = params.ug_N_47;
elseif isfield(params, 'ug_N')
  ug_N_47 = params.ug_N{47};
else
  error 'could not find ug_N_47'
end
if isfield(params, 'ug_N_48')
  ug_N_48 = params.ug_N_48;
elseif isfield(params, 'ug_N')
  ug_N_48 = params.ug_N{48};
else
  error 'could not find ug_N_48'
end
if isfield(params, 'ug_N_49')
  ug_N_49 = params.ug_N_49;
elseif isfield(params, 'ug_N')
  ug_N_49 = params.ug_N{49};
else
  error 'could not find ug_N_49'
end
if isfield(params, 'ug_N_50')
  ug_N_50 = params.ug_N_50;
elseif isfield(params, 'ug_N')
  ug_N_50 = params.ug_N{50};
else
  error 'could not find ug_N_50'
end
if isfield(params, 'ug_N_51')
  ug_N_51 = params.ug_N_51;
elseif isfield(params, 'ug_N')
  ug_N_51 = params.ug_N{51};
else
  error 'could not find ug_N_51'
end
if isfield(params, 'ug_N_52')
  ug_N_52 = params.ug_N_52;
elseif isfield(params, 'ug_N')
  ug_N_52 = params.ug_N{52};
else
  error 'could not find ug_N_52'
end
if isfield(params, 'ug_N_53')
  ug_N_53 = params.ug_N_53;
elseif isfield(params, 'ug_N')
  ug_N_53 = params.ug_N{53};
else
  error 'could not find ug_N_53'
end
if isfield(params, 'ug_N_54')
  ug_N_54 = params.ug_N_54;
elseif isfield(params, 'ug_N')
  ug_N_54 = params.ug_N{54};
else
  error 'could not find ug_N_54'
end
if isfield(params, 'ug_N_55')
  ug_N_55 = params.ug_N_55;
elseif isfield(params, 'ug_N')
  ug_N_55 = params.ug_N{55};
else
  error 'could not find ug_N_55'
end
if isfield(params, 'ug_N_56')
  ug_N_56 = params.ug_N_56;
elseif isfield(params, 'ug_N')
  ug_N_56 = params.ug_N{56};
else
  error 'could not find ug_N_56'
end
if isfield(params, 'ug_N_57')
  ug_N_57 = params.ug_N_57;
elseif isfield(params, 'ug_N')
  ug_N_57 = params.ug_N{57};
else
  error 'could not find ug_N_57'
end
if isfield(params, 'ug_N_58')
  ug_N_58 = params.ug_N_58;
elseif isfield(params, 'ug_N')
  ug_N_58 = params.ug_N{58};
else
  error 'could not find ug_N_58'
end
if isfield(params, 'ug_N_59')
  ug_N_59 = params.ug_N_59;
elseif isfield(params, 'ug_N')
  ug_N_59 = params.ug_N{59};
else
  error 'could not find ug_N_59'
end
if isfield(params, 'ug_N_60')
  ug_N_60 = params.ug_N_60;
elseif isfield(params, 'ug_N')
  ug_N_60 = params.ug_N{60};
else
  error 'could not find ug_N_60'
end
if isfield(params, 'ug_N_61')
  ug_N_61 = params.ug_N_61;
elseif isfield(params, 'ug_N')
  ug_N_61 = params.ug_N{61};
else
  error 'could not find ug_N_61'
end
if isfield(params, 'ug_N_62')
  ug_N_62 = params.ug_N_62;
elseif isfield(params, 'ug_N')
  ug_N_62 = params.ug_N{62};
else
  error 'could not find ug_N_62'
end
if isfield(params, 'ug_N_63')
  ug_N_63 = params.ug_N_63;
elseif isfield(params, 'ug_N')
  ug_N_63 = params.ug_N{63};
else
  error 'could not find ug_N_63'
end
if isfield(params, 'ug_N_64')
  ug_N_64 = params.ug_N_64;
elseif isfield(params, 'ug_N')
  ug_N_64 = params.ug_N{64};
else
  error 'could not find ug_N_64'
end
if isfield(params, 'ug_N_65')
  ug_N_65 = params.ug_N_65;
elseif isfield(params, 'ug_N')
  ug_N_65 = params.ug_N{65};
else
  error 'could not find ug_N_65'
end
if isfield(params, 'ug_N_66')
  ug_N_66 = params.ug_N_66;
elseif isfield(params, 'ug_N')
  ug_N_66 = params.ug_N{66};
else
  error 'could not find ug_N_66'
end
if isfield(params, 'ug_N_67')
  ug_N_67 = params.ug_N_67;
elseif isfield(params, 'ug_N')
  ug_N_67 = params.ug_N{67};
else
  error 'could not find ug_N_67'
end
if isfield(params, 'ug_N_68')
  ug_N_68 = params.ug_N_68;
elseif isfield(params, 'ug_N')
  ug_N_68 = params.ug_N{68};
else
  error 'could not find ug_N_68'
end
if isfield(params, 'ug_N_69')
  ug_N_69 = params.ug_N_69;
elseif isfield(params, 'ug_N')
  ug_N_69 = params.ug_N{69};
else
  error 'could not find ug_N_69'
end
if isfield(params, 'ug_N_70')
  ug_N_70 = params.ug_N_70;
elseif isfield(params, 'ug_N')
  ug_N_70 = params.ug_N{70};
else
  error 'could not find ug_N_70'
end
if isfield(params, 'ug_N_71')
  ug_N_71 = params.ug_N_71;
elseif isfield(params, 'ug_N')
  ug_N_71 = params.ug_N{71};
else
  error 'could not find ug_N_71'
end
if isfield(params, 'ug_N_72')
  ug_N_72 = params.ug_N_72;
elseif isfield(params, 'ug_N')
  ug_N_72 = params.ug_N{72};
else
  error 'could not find ug_N_72'
end
if isfield(params, 'ug_N_73')
  ug_N_73 = params.ug_N_73;
elseif isfield(params, 'ug_N')
  ug_N_73 = params.ug_N{73};
else
  error 'could not find ug_N_73'
end
if isfield(params, 'ug_N_74')
  ug_N_74 = params.ug_N_74;
elseif isfield(params, 'ug_N')
  ug_N_74 = params.ug_N{74};
else
  error 'could not find ug_N_74'
end
if isfield(params, 'ug_N_75')
  ug_N_75 = params.ug_N_75;
elseif isfield(params, 'ug_N')
  ug_N_75 = params.ug_N{75};
else
  error 'could not find ug_N_75'
end
if isfield(params, 'ug_N_76')
  ug_N_76 = params.ug_N_76;
elseif isfield(params, 'ug_N')
  ug_N_76 = params.ug_N{76};
else
  error 'could not find ug_N_76'
end
if isfield(params, 'ug_N_77')
  ug_N_77 = params.ug_N_77;
elseif isfield(params, 'ug_N')
  ug_N_77 = params.ug_N{77};
else
  error 'could not find ug_N_77'
end
if isfield(params, 'ug_N_78')
  ug_N_78 = params.ug_N_78;
elseif isfield(params, 'ug_N')
  ug_N_78 = params.ug_N{78};
else
  error 'could not find ug_N_78'
end
if isfield(params, 'ug_N_79')
  ug_N_79 = params.ug_N_79;
elseif isfield(params, 'ug_N')
  ug_N_79 = params.ug_N{79};
else
  error 'could not find ug_N_79'
end
if isfield(params, 'ug_N_80')
  ug_N_80 = params.ug_N_80;
elseif isfield(params, 'ug_N')
  ug_N_80 = params.ug_N{80};
else
  error 'could not find ug_N_80'
end
if isfield(params, 'ug_N_81')
  ug_N_81 = params.ug_N_81;
elseif isfield(params, 'ug_N')
  ug_N_81 = params.ug_N{81};
else
  error 'could not find ug_N_81'
end
if isfield(params, 'ug_N_82')
  ug_N_82 = params.ug_N_82;
elseif isfield(params, 'ug_N')
  ug_N_82 = params.ug_N{82};
else
  error 'could not find ug_N_82'
end
if isfield(params, 'ug_N_83')
  ug_N_83 = params.ug_N_83;
elseif isfield(params, 'ug_N')
  ug_N_83 = params.ug_N{83};
else
  error 'could not find ug_N_83'
end
if isfield(params, 'ug_N_84')
  ug_N_84 = params.ug_N_84;
elseif isfield(params, 'ug_N')
  ug_N_84 = params.ug_N{84};
else
  error 'could not find ug_N_84'
end
if isfield(params, 'ug_N_85')
  ug_N_85 = params.ug_N_85;
elseif isfield(params, 'ug_N')
  ug_N_85 = params.ug_N{85};
else
  error 'could not find ug_N_85'
end
if isfield(params, 'ug_N_86')
  ug_N_86 = params.ug_N_86;
elseif isfield(params, 'ug_N')
  ug_N_86 = params.ug_N{86};
else
  error 'could not find ug_N_86'
end
if isfield(params, 'ug_N_87')
  ug_N_87 = params.ug_N_87;
elseif isfield(params, 'ug_N')
  ug_N_87 = params.ug_N{87};
else
  error 'could not find ug_N_87'
end
if isfield(params, 'ug_N_88')
  ug_N_88 = params.ug_N_88;
elseif isfield(params, 'ug_N')
  ug_N_88 = params.ug_N{88};
else
  error 'could not find ug_N_88'
end
if isfield(params, 'ug_N_89')
  ug_N_89 = params.ug_N_89;
elseif isfield(params, 'ug_N')
  ug_N_89 = params.ug_N{89};
else
  error 'could not find ug_N_89'
end
if isfield(params, 'ug_N_90')
  ug_N_90 = params.ug_N_90;
elseif isfield(params, 'ug_N')
  ug_N_90 = params.ug_N{90};
else
  error 'could not find ug_N_90'
end
if isfield(params, 'ug_N_91')
  ug_N_91 = params.ug_N_91;
elseif isfield(params, 'ug_N')
  ug_N_91 = params.ug_N{91};
else
  error 'could not find ug_N_91'
end
if isfield(params, 'ug_N_92')
  ug_N_92 = params.ug_N_92;
elseif isfield(params, 'ug_N')
  ug_N_92 = params.ug_N{92};
else
  error 'could not find ug_N_92'
end
if isfield(params, 'ug_N_93')
  ug_N_93 = params.ug_N_93;
elseif isfield(params, 'ug_N')
  ug_N_93 = params.ug_N{93};
else
  error 'could not find ug_N_93'
end
if isfield(params, 'ug_N_94')
  ug_N_94 = params.ug_N_94;
elseif isfield(params, 'ug_N')
  ug_N_94 = params.ug_N{94};
else
  error 'could not find ug_N_94'
end
if isfield(params, 'ug_N_95')
  ug_N_95 = params.ug_N_95;
elseif isfield(params, 'ug_N')
  ug_N_95 = params.ug_N{95};
else
  error 'could not find ug_N_95'
end
if isfield(params, 'ug_N_96')
  ug_N_96 = params.ug_N_96;
elseif isfield(params, 'ug_N')
  ug_N_96 = params.ug_N{96};
else
  error 'could not find ug_N_96'
end
if isfield(params, 'ug_N_97')
  ug_N_97 = params.ug_N_97;
elseif isfield(params, 'ug_N')
  ug_N_97 = params.ug_N{97};
else
  error 'could not find ug_N_97'
end
if isfield(params, 'ug_N_98')
  ug_N_98 = params.ug_N_98;
elseif isfield(params, 'ug_N')
  ug_N_98 = params.ug_N{98};
else
  error 'could not find ug_N_98'
end
if isfield(params, 'ug_N_99')
  ug_N_99 = params.ug_N_99;
elseif isfield(params, 'ug_N')
  ug_N_99 = params.ug_N{99};
else
  error 'could not find ug_N_99'
end
if isfield(params, 'ug_N_100')
  ug_N_100 = params.ug_N_100;
elseif isfield(params, 'ug_N')
  ug_N_100 = params.ug_N{100};
else
  error 'could not find ug_N_100'
end
if isfield(params, 'ug_N_101')
  ug_N_101 = params.ug_N_101;
elseif isfield(params, 'ug_N')
  ug_N_101 = params.ug_N{101};
else
  error 'could not find ug_N_101'
end
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
if isfield(params, 'vg_N_11')
  vg_N_11 = params.vg_N_11;
elseif isfield(params, 'vg_N')
  vg_N_11 = params.vg_N{11};
else
  error 'could not find vg_N_11'
end
if isfield(params, 'vg_N_12')
  vg_N_12 = params.vg_N_12;
elseif isfield(params, 'vg_N')
  vg_N_12 = params.vg_N{12};
else
  error 'could not find vg_N_12'
end
if isfield(params, 'vg_N_13')
  vg_N_13 = params.vg_N_13;
elseif isfield(params, 'vg_N')
  vg_N_13 = params.vg_N{13};
else
  error 'could not find vg_N_13'
end
if isfield(params, 'vg_N_14')
  vg_N_14 = params.vg_N_14;
elseif isfield(params, 'vg_N')
  vg_N_14 = params.vg_N{14};
else
  error 'could not find vg_N_14'
end
if isfield(params, 'vg_N_15')
  vg_N_15 = params.vg_N_15;
elseif isfield(params, 'vg_N')
  vg_N_15 = params.vg_N{15};
else
  error 'could not find vg_N_15'
end
if isfield(params, 'vg_N_16')
  vg_N_16 = params.vg_N_16;
elseif isfield(params, 'vg_N')
  vg_N_16 = params.vg_N{16};
else
  error 'could not find vg_N_16'
end
if isfield(params, 'vg_N_17')
  vg_N_17 = params.vg_N_17;
elseif isfield(params, 'vg_N')
  vg_N_17 = params.vg_N{17};
else
  error 'could not find vg_N_17'
end
if isfield(params, 'vg_N_18')
  vg_N_18 = params.vg_N_18;
elseif isfield(params, 'vg_N')
  vg_N_18 = params.vg_N{18};
else
  error 'could not find vg_N_18'
end
if isfield(params, 'vg_N_19')
  vg_N_19 = params.vg_N_19;
elseif isfield(params, 'vg_N')
  vg_N_19 = params.vg_N{19};
else
  error 'could not find vg_N_19'
end
if isfield(params, 'vg_N_20')
  vg_N_20 = params.vg_N_20;
elseif isfield(params, 'vg_N')
  vg_N_20 = params.vg_N{20};
else
  error 'could not find vg_N_20'
end
if isfield(params, 'vg_N_21')
  vg_N_21 = params.vg_N_21;
elseif isfield(params, 'vg_N')
  vg_N_21 = params.vg_N{21};
else
  error 'could not find vg_N_21'
end
if isfield(params, 'vg_N_22')
  vg_N_22 = params.vg_N_22;
elseif isfield(params, 'vg_N')
  vg_N_22 = params.vg_N{22};
else
  error 'could not find vg_N_22'
end
if isfield(params, 'vg_N_23')
  vg_N_23 = params.vg_N_23;
elseif isfield(params, 'vg_N')
  vg_N_23 = params.vg_N{23};
else
  error 'could not find vg_N_23'
end
if isfield(params, 'vg_N_24')
  vg_N_24 = params.vg_N_24;
elseif isfield(params, 'vg_N')
  vg_N_24 = params.vg_N{24};
else
  error 'could not find vg_N_24'
end
if isfield(params, 'vg_N_25')
  vg_N_25 = params.vg_N_25;
elseif isfield(params, 'vg_N')
  vg_N_25 = params.vg_N{25};
else
  error 'could not find vg_N_25'
end
if isfield(params, 'vg_N_26')
  vg_N_26 = params.vg_N_26;
elseif isfield(params, 'vg_N')
  vg_N_26 = params.vg_N{26};
else
  error 'could not find vg_N_26'
end
if isfield(params, 'vg_N_27')
  vg_N_27 = params.vg_N_27;
elseif isfield(params, 'vg_N')
  vg_N_27 = params.vg_N{27};
else
  error 'could not find vg_N_27'
end
if isfield(params, 'vg_N_28')
  vg_N_28 = params.vg_N_28;
elseif isfield(params, 'vg_N')
  vg_N_28 = params.vg_N{28};
else
  error 'could not find vg_N_28'
end
if isfield(params, 'vg_N_29')
  vg_N_29 = params.vg_N_29;
elseif isfield(params, 'vg_N')
  vg_N_29 = params.vg_N{29};
else
  error 'could not find vg_N_29'
end
if isfield(params, 'vg_N_30')
  vg_N_30 = params.vg_N_30;
elseif isfield(params, 'vg_N')
  vg_N_30 = params.vg_N{30};
else
  error 'could not find vg_N_30'
end
if isfield(params, 'vg_N_31')
  vg_N_31 = params.vg_N_31;
elseif isfield(params, 'vg_N')
  vg_N_31 = params.vg_N{31};
else
  error 'could not find vg_N_31'
end
if isfield(params, 'vg_N_32')
  vg_N_32 = params.vg_N_32;
elseif isfield(params, 'vg_N')
  vg_N_32 = params.vg_N{32};
else
  error 'could not find vg_N_32'
end
if isfield(params, 'vg_N_33')
  vg_N_33 = params.vg_N_33;
elseif isfield(params, 'vg_N')
  vg_N_33 = params.vg_N{33};
else
  error 'could not find vg_N_33'
end
if isfield(params, 'vg_N_34')
  vg_N_34 = params.vg_N_34;
elseif isfield(params, 'vg_N')
  vg_N_34 = params.vg_N{34};
else
  error 'could not find vg_N_34'
end
if isfield(params, 'vg_N_35')
  vg_N_35 = params.vg_N_35;
elseif isfield(params, 'vg_N')
  vg_N_35 = params.vg_N{35};
else
  error 'could not find vg_N_35'
end
if isfield(params, 'vg_N_36')
  vg_N_36 = params.vg_N_36;
elseif isfield(params, 'vg_N')
  vg_N_36 = params.vg_N{36};
else
  error 'could not find vg_N_36'
end
if isfield(params, 'vg_N_37')
  vg_N_37 = params.vg_N_37;
elseif isfield(params, 'vg_N')
  vg_N_37 = params.vg_N{37};
else
  error 'could not find vg_N_37'
end
if isfield(params, 'vg_N_38')
  vg_N_38 = params.vg_N_38;
elseif isfield(params, 'vg_N')
  vg_N_38 = params.vg_N{38};
else
  error 'could not find vg_N_38'
end
if isfield(params, 'vg_N_39')
  vg_N_39 = params.vg_N_39;
elseif isfield(params, 'vg_N')
  vg_N_39 = params.vg_N{39};
else
  error 'could not find vg_N_39'
end
if isfield(params, 'vg_N_40')
  vg_N_40 = params.vg_N_40;
elseif isfield(params, 'vg_N')
  vg_N_40 = params.vg_N{40};
else
  error 'could not find vg_N_40'
end
if isfield(params, 'vg_N_41')
  vg_N_41 = params.vg_N_41;
elseif isfield(params, 'vg_N')
  vg_N_41 = params.vg_N{41};
else
  error 'could not find vg_N_41'
end
if isfield(params, 'vg_N_42')
  vg_N_42 = params.vg_N_42;
elseif isfield(params, 'vg_N')
  vg_N_42 = params.vg_N{42};
else
  error 'could not find vg_N_42'
end
if isfield(params, 'vg_N_43')
  vg_N_43 = params.vg_N_43;
elseif isfield(params, 'vg_N')
  vg_N_43 = params.vg_N{43};
else
  error 'could not find vg_N_43'
end
if isfield(params, 'vg_N_44')
  vg_N_44 = params.vg_N_44;
elseif isfield(params, 'vg_N')
  vg_N_44 = params.vg_N{44};
else
  error 'could not find vg_N_44'
end
if isfield(params, 'vg_N_45')
  vg_N_45 = params.vg_N_45;
elseif isfield(params, 'vg_N')
  vg_N_45 = params.vg_N{45};
else
  error 'could not find vg_N_45'
end
if isfield(params, 'vg_N_46')
  vg_N_46 = params.vg_N_46;
elseif isfield(params, 'vg_N')
  vg_N_46 = params.vg_N{46};
else
  error 'could not find vg_N_46'
end
if isfield(params, 'vg_N_47')
  vg_N_47 = params.vg_N_47;
elseif isfield(params, 'vg_N')
  vg_N_47 = params.vg_N{47};
else
  error 'could not find vg_N_47'
end
if isfield(params, 'vg_N_48')
  vg_N_48 = params.vg_N_48;
elseif isfield(params, 'vg_N')
  vg_N_48 = params.vg_N{48};
else
  error 'could not find vg_N_48'
end
if isfield(params, 'vg_N_49')
  vg_N_49 = params.vg_N_49;
elseif isfield(params, 'vg_N')
  vg_N_49 = params.vg_N{49};
else
  error 'could not find vg_N_49'
end
if isfield(params, 'vg_N_50')
  vg_N_50 = params.vg_N_50;
elseif isfield(params, 'vg_N')
  vg_N_50 = params.vg_N{50};
else
  error 'could not find vg_N_50'
end
if isfield(params, 'vg_N_51')
  vg_N_51 = params.vg_N_51;
elseif isfield(params, 'vg_N')
  vg_N_51 = params.vg_N{51};
else
  error 'could not find vg_N_51'
end
if isfield(params, 'vg_N_52')
  vg_N_52 = params.vg_N_52;
elseif isfield(params, 'vg_N')
  vg_N_52 = params.vg_N{52};
else
  error 'could not find vg_N_52'
end
if isfield(params, 'vg_N_53')
  vg_N_53 = params.vg_N_53;
elseif isfield(params, 'vg_N')
  vg_N_53 = params.vg_N{53};
else
  error 'could not find vg_N_53'
end
if isfield(params, 'vg_N_54')
  vg_N_54 = params.vg_N_54;
elseif isfield(params, 'vg_N')
  vg_N_54 = params.vg_N{54};
else
  error 'could not find vg_N_54'
end
if isfield(params, 'vg_N_55')
  vg_N_55 = params.vg_N_55;
elseif isfield(params, 'vg_N')
  vg_N_55 = params.vg_N{55};
else
  error 'could not find vg_N_55'
end
if isfield(params, 'vg_N_56')
  vg_N_56 = params.vg_N_56;
elseif isfield(params, 'vg_N')
  vg_N_56 = params.vg_N{56};
else
  error 'could not find vg_N_56'
end
if isfield(params, 'vg_N_57')
  vg_N_57 = params.vg_N_57;
elseif isfield(params, 'vg_N')
  vg_N_57 = params.vg_N{57};
else
  error 'could not find vg_N_57'
end
if isfield(params, 'vg_N_58')
  vg_N_58 = params.vg_N_58;
elseif isfield(params, 'vg_N')
  vg_N_58 = params.vg_N{58};
else
  error 'could not find vg_N_58'
end
if isfield(params, 'vg_N_59')
  vg_N_59 = params.vg_N_59;
elseif isfield(params, 'vg_N')
  vg_N_59 = params.vg_N{59};
else
  error 'could not find vg_N_59'
end
if isfield(params, 'vg_N_60')
  vg_N_60 = params.vg_N_60;
elseif isfield(params, 'vg_N')
  vg_N_60 = params.vg_N{60};
else
  error 'could not find vg_N_60'
end
if isfield(params, 'vg_N_61')
  vg_N_61 = params.vg_N_61;
elseif isfield(params, 'vg_N')
  vg_N_61 = params.vg_N{61};
else
  error 'could not find vg_N_61'
end
if isfield(params, 'vg_N_62')
  vg_N_62 = params.vg_N_62;
elseif isfield(params, 'vg_N')
  vg_N_62 = params.vg_N{62};
else
  error 'could not find vg_N_62'
end
if isfield(params, 'vg_N_63')
  vg_N_63 = params.vg_N_63;
elseif isfield(params, 'vg_N')
  vg_N_63 = params.vg_N{63};
else
  error 'could not find vg_N_63'
end
if isfield(params, 'vg_N_64')
  vg_N_64 = params.vg_N_64;
elseif isfield(params, 'vg_N')
  vg_N_64 = params.vg_N{64};
else
  error 'could not find vg_N_64'
end
if isfield(params, 'vg_N_65')
  vg_N_65 = params.vg_N_65;
elseif isfield(params, 'vg_N')
  vg_N_65 = params.vg_N{65};
else
  error 'could not find vg_N_65'
end
if isfield(params, 'vg_N_66')
  vg_N_66 = params.vg_N_66;
elseif isfield(params, 'vg_N')
  vg_N_66 = params.vg_N{66};
else
  error 'could not find vg_N_66'
end
if isfield(params, 'vg_N_67')
  vg_N_67 = params.vg_N_67;
elseif isfield(params, 'vg_N')
  vg_N_67 = params.vg_N{67};
else
  error 'could not find vg_N_67'
end
if isfield(params, 'vg_N_68')
  vg_N_68 = params.vg_N_68;
elseif isfield(params, 'vg_N')
  vg_N_68 = params.vg_N{68};
else
  error 'could not find vg_N_68'
end
if isfield(params, 'vg_N_69')
  vg_N_69 = params.vg_N_69;
elseif isfield(params, 'vg_N')
  vg_N_69 = params.vg_N{69};
else
  error 'could not find vg_N_69'
end
if isfield(params, 'vg_N_70')
  vg_N_70 = params.vg_N_70;
elseif isfield(params, 'vg_N')
  vg_N_70 = params.vg_N{70};
else
  error 'could not find vg_N_70'
end
if isfield(params, 'vg_N_71')
  vg_N_71 = params.vg_N_71;
elseif isfield(params, 'vg_N')
  vg_N_71 = params.vg_N{71};
else
  error 'could not find vg_N_71'
end
if isfield(params, 'vg_N_72')
  vg_N_72 = params.vg_N_72;
elseif isfield(params, 'vg_N')
  vg_N_72 = params.vg_N{72};
else
  error 'could not find vg_N_72'
end
if isfield(params, 'vg_N_73')
  vg_N_73 = params.vg_N_73;
elseif isfield(params, 'vg_N')
  vg_N_73 = params.vg_N{73};
else
  error 'could not find vg_N_73'
end
if isfield(params, 'vg_N_74')
  vg_N_74 = params.vg_N_74;
elseif isfield(params, 'vg_N')
  vg_N_74 = params.vg_N{74};
else
  error 'could not find vg_N_74'
end
if isfield(params, 'vg_N_75')
  vg_N_75 = params.vg_N_75;
elseif isfield(params, 'vg_N')
  vg_N_75 = params.vg_N{75};
else
  error 'could not find vg_N_75'
end
if isfield(params, 'vg_N_76')
  vg_N_76 = params.vg_N_76;
elseif isfield(params, 'vg_N')
  vg_N_76 = params.vg_N{76};
else
  error 'could not find vg_N_76'
end
if isfield(params, 'vg_N_77')
  vg_N_77 = params.vg_N_77;
elseif isfield(params, 'vg_N')
  vg_N_77 = params.vg_N{77};
else
  error 'could not find vg_N_77'
end
if isfield(params, 'vg_N_78')
  vg_N_78 = params.vg_N_78;
elseif isfield(params, 'vg_N')
  vg_N_78 = params.vg_N{78};
else
  error 'could not find vg_N_78'
end
if isfield(params, 'vg_N_79')
  vg_N_79 = params.vg_N_79;
elseif isfield(params, 'vg_N')
  vg_N_79 = params.vg_N{79};
else
  error 'could not find vg_N_79'
end
if isfield(params, 'vg_N_80')
  vg_N_80 = params.vg_N_80;
elseif isfield(params, 'vg_N')
  vg_N_80 = params.vg_N{80};
else
  error 'could not find vg_N_80'
end
if isfield(params, 'vg_N_81')
  vg_N_81 = params.vg_N_81;
elseif isfield(params, 'vg_N')
  vg_N_81 = params.vg_N{81};
else
  error 'could not find vg_N_81'
end
if isfield(params, 'vg_N_82')
  vg_N_82 = params.vg_N_82;
elseif isfield(params, 'vg_N')
  vg_N_82 = params.vg_N{82};
else
  error 'could not find vg_N_82'
end
if isfield(params, 'vg_N_83')
  vg_N_83 = params.vg_N_83;
elseif isfield(params, 'vg_N')
  vg_N_83 = params.vg_N{83};
else
  error 'could not find vg_N_83'
end
if isfield(params, 'vg_N_84')
  vg_N_84 = params.vg_N_84;
elseif isfield(params, 'vg_N')
  vg_N_84 = params.vg_N{84};
else
  error 'could not find vg_N_84'
end
if isfield(params, 'vg_N_85')
  vg_N_85 = params.vg_N_85;
elseif isfield(params, 'vg_N')
  vg_N_85 = params.vg_N{85};
else
  error 'could not find vg_N_85'
end
if isfield(params, 'vg_N_86')
  vg_N_86 = params.vg_N_86;
elseif isfield(params, 'vg_N')
  vg_N_86 = params.vg_N{86};
else
  error 'could not find vg_N_86'
end
if isfield(params, 'vg_N_87')
  vg_N_87 = params.vg_N_87;
elseif isfield(params, 'vg_N')
  vg_N_87 = params.vg_N{87};
else
  error 'could not find vg_N_87'
end
if isfield(params, 'vg_N_88')
  vg_N_88 = params.vg_N_88;
elseif isfield(params, 'vg_N')
  vg_N_88 = params.vg_N{88};
else
  error 'could not find vg_N_88'
end
if isfield(params, 'vg_N_89')
  vg_N_89 = params.vg_N_89;
elseif isfield(params, 'vg_N')
  vg_N_89 = params.vg_N{89};
else
  error 'could not find vg_N_89'
end
if isfield(params, 'vg_N_90')
  vg_N_90 = params.vg_N_90;
elseif isfield(params, 'vg_N')
  vg_N_90 = params.vg_N{90};
else
  error 'could not find vg_N_90'
end
if isfield(params, 'vg_N_91')
  vg_N_91 = params.vg_N_91;
elseif isfield(params, 'vg_N')
  vg_N_91 = params.vg_N{91};
else
  error 'could not find vg_N_91'
end
if isfield(params, 'vg_N_92')
  vg_N_92 = params.vg_N_92;
elseif isfield(params, 'vg_N')
  vg_N_92 = params.vg_N{92};
else
  error 'could not find vg_N_92'
end
if isfield(params, 'vg_N_93')
  vg_N_93 = params.vg_N_93;
elseif isfield(params, 'vg_N')
  vg_N_93 = params.vg_N{93};
else
  error 'could not find vg_N_93'
end
if isfield(params, 'vg_N_94')
  vg_N_94 = params.vg_N_94;
elseif isfield(params, 'vg_N')
  vg_N_94 = params.vg_N{94};
else
  error 'could not find vg_N_94'
end
if isfield(params, 'vg_N_95')
  vg_N_95 = params.vg_N_95;
elseif isfield(params, 'vg_N')
  vg_N_95 = params.vg_N{95};
else
  error 'could not find vg_N_95'
end
if isfield(params, 'vg_N_96')
  vg_N_96 = params.vg_N_96;
elseif isfield(params, 'vg_N')
  vg_N_96 = params.vg_N{96};
else
  error 'could not find vg_N_96'
end
if isfield(params, 'vg_N_97')
  vg_N_97 = params.vg_N_97;
elseif isfield(params, 'vg_N')
  vg_N_97 = params.vg_N{97};
else
  error 'could not find vg_N_97'
end
if isfield(params, 'vg_N_98')
  vg_N_98 = params.vg_N_98;
elseif isfield(params, 'vg_N')
  vg_N_98 = params.vg_N{98};
else
  error 'could not find vg_N_98'
end
if isfield(params, 'vg_N_99')
  vg_N_99 = params.vg_N_99;
elseif isfield(params, 'vg_N')
  vg_N_99 = params.vg_N{99};
else
  error 'could not find vg_N_99'
end
if isfield(params, 'vg_N_100')
  vg_N_100 = params.vg_N_100;
elseif isfield(params, 'vg_N')
  vg_N_100 = params.vg_N{100};
else
  error 'could not find vg_N_100'
end
if isfield(params, 'vg_N_101')
  vg_N_101 = params.vg_N_101;
elseif isfield(params, 'vg_N')
  vg_N_101 = params.vg_N{101};
else
  error 'could not find vg_N_101'
end
cvx_begin
  % Caution: automatically generated by cvxgen. May be incorrect.
  variable Pg;
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
  variable Thetag_11;
  variable Thetag_12;
  variable Thetag_13;
  variable Thetag_14;
  variable Thetag_15;
  variable Thetag_16;
  variable Thetag_17;
  variable Thetag_18;
  variable Thetag_19;
  variable Thetag_20;
  variable Thetag_21;
  variable Thetag_22;
  variable Thetag_23;
  variable Thetag_24;
  variable Thetag_25;
  variable Thetag_26;
  variable Thetag_27;
  variable Thetag_28;
  variable Thetag_29;
  variable Thetag_30;
  variable Thetag_31;
  variable Thetag_32;
  variable Thetag_33;
  variable Thetag_34;
  variable Thetag_35;
  variable Thetag_36;
  variable Thetag_37;
  variable Thetag_38;
  variable Thetag_39;
  variable Thetag_40;
  variable Thetag_41;
  variable Thetag_42;
  variable Thetag_43;
  variable Thetag_44;
  variable Thetag_45;
  variable Thetag_46;
  variable Thetag_47;
  variable Thetag_48;
  variable Thetag_49;
  variable Thetag_50;
  variable Thetag_51;
  variable Thetag_52;
  variable Thetag_53;
  variable Thetag_54;
  variable Thetag_55;
  variable Thetag_56;
  variable Thetag_57;
  variable Thetag_58;
  variable Thetag_59;
  variable Thetag_60;
  variable Thetag_61;
  variable Thetag_62;
  variable Thetag_63;
  variable Thetag_64;
  variable Thetag_65;
  variable Thetag_66;
  variable Thetag_67;
  variable Thetag_68;
  variable Thetag_69;
  variable Thetag_70;
  variable Thetag_71;
  variable Thetag_72;
  variable Thetag_73;
  variable Thetag_74;
  variable Thetag_75;
  variable Thetag_76;
  variable Thetag_77;
  variable Thetag_78;
  variable Thetag_79;
  variable Thetag_80;
  variable Thetag_81;
  variable Thetag_82;
  variable Thetag_83;
  variable Thetag_84;
  variable Thetag_85;
  variable Thetag_86;
  variable Thetag_87;
  variable Thetag_88;
  variable Thetag_89;
  variable Thetag_90;
  variable Thetag_91;
  variable Thetag_92;
  variable Thetag_93;
  variable Thetag_94;
  variable Thetag_95;
  variable Thetag_96;
  variable Thetag_97;
  variable Thetag_98;
  variable Thetag_99;
  variable Thetag_100;
  variable Thetag_101;

  minimize(c2*square(Pg) + c1*Pg + c0 + (rho/2)*(square(Pg - Pg_N_init_1 + Pg_N_avg_1 + ug_N_1) + square(Thetag_1 - Vg_N_avg_1 - Thetag_N_avg_1 + vg_N_1) + square(Pg - Pg_N_init_2 + Pg_N_avg_2 + ug_N_2) + square(Thetag_2 - Vg_N_avg_2 - Thetag_N_avg_2 + vg_N_2) + square(Pg - Pg_N_init_3 + Pg_N_avg_3 + ug_N_3) + square(Thetag_3 - Vg_N_avg_3 - Thetag_N_avg_3 + vg_N_3) + square(Pg - Pg_N_init_4 + Pg_N_avg_4 + ug_N_4) + square(Thetag_4 - Vg_N_avg_4 - Thetag_N_avg_4 + vg_N_4) + square(Pg - Pg_N_init_5 + Pg_N_avg_5 + ug_N_5) + square(Thetag_5 - Vg_N_avg_5 - Thetag_N_avg_5 + vg_N_5) + square(Pg - Pg_N_init_6 + Pg_N_avg_6 + ug_N_6) + square(Thetag_6 - Vg_N_avg_6 - Thetag_N_avg_6 + vg_N_6) + square(Pg - Pg_N_init_7 + Pg_N_avg_7 + ug_N_7) + square(Thetag_7 - Vg_N_avg_7 - Thetag_N_avg_7 + vg_N_7) + square(Pg - Pg_N_init_8 + Pg_N_avg_8 + ug_N_8) + square(Thetag_8 - Vg_N_avg_8 - Thetag_N_avg_8 + vg_N_8) + square(Pg - Pg_N_init_9 + Pg_N_avg_9 + ug_N_9) + square(Thetag_9 - Vg_N_avg_9 - Thetag_N_avg_9 + vg_N_9) + square(Pg - Pg_N_init_10 + Pg_N_avg_10 + ug_N_10) + square(Thetag_10 - Vg_N_avg_10 - Thetag_N_avg_10 + vg_N_10) + square(Pg - Pg_N_init_11 + Pg_N_avg_11 + ug_N_11) + square(Thetag_11 - Vg_N_avg_11 - Thetag_N_avg_11 + vg_N_11) + square(Pg - Pg_N_init_12 + Pg_N_avg_12 + ug_N_12) + square(Thetag_12 - Vg_N_avg_12 - Thetag_N_avg_12 + vg_N_12) + square(Pg - Pg_N_init_13 + Pg_N_avg_13 + ug_N_13) + square(Thetag_13 - Vg_N_avg_13 - Thetag_N_avg_13 + vg_N_13) + square(Pg - Pg_N_init_14 + Pg_N_avg_14 + ug_N_14) + square(Thetag_14 - Vg_N_avg_14 - Thetag_N_avg_14 + vg_N_14) + square(Pg - Pg_N_init_15 + Pg_N_avg_15 + ug_N_15) + square(Thetag_15 - Vg_N_avg_15 - Thetag_N_avg_15 + vg_N_15) + square(Pg - Pg_N_init_16 + Pg_N_avg_16 + ug_N_16) + square(Thetag_16 - Vg_N_avg_16 - Thetag_N_avg_16 + vg_N_16) + square(Pg - Pg_N_init_17 + Pg_N_avg_17 + ug_N_17) + square(Thetag_17 - Vg_N_avg_17 - Thetag_N_avg_17 + vg_N_17) + square(Pg - Pg_N_init_18 + Pg_N_avg_18 + ug_N_18) + square(Thetag_18 - Vg_N_avg_18 - Thetag_N_avg_18 + vg_N_18) + square(Pg - Pg_N_init_19 + Pg_N_avg_19 + ug_N_19) + square(Thetag_19 - Vg_N_avg_19 - Thetag_N_avg_19 + vg_N_19) + square(Pg - Pg_N_init_20 + Pg_N_avg_20 + ug_N_20) + square(Thetag_20 - Vg_N_avg_20 - Thetag_N_avg_20 + vg_N_20) + square(Pg - Pg_N_init_21 + Pg_N_avg_21 + ug_N_21) + square(Thetag_21 - Vg_N_avg_21 - Thetag_N_avg_21 + vg_N_21) + square(Pg - Pg_N_init_22 + Pg_N_avg_22 + ug_N_22) + square(Thetag_22 - Vg_N_avg_22 - Thetag_N_avg_22 + vg_N_22) + square(Pg - Pg_N_init_23 + Pg_N_avg_23 + ug_N_23) + square(Thetag_23 - Vg_N_avg_23 - Thetag_N_avg_23 + vg_N_23) + square(Pg - Pg_N_init_24 + Pg_N_avg_24 + ug_N_24) + square(Thetag_24 - Vg_N_avg_24 - Thetag_N_avg_24 + vg_N_24) + square(Pg - Pg_N_init_25 + Pg_N_avg_25 + ug_N_25) + square(Thetag_25 - Vg_N_avg_25 - Thetag_N_avg_25 + vg_N_25) + square(Pg - Pg_N_init_26 + Pg_N_avg_26 + ug_N_26) + square(Thetag_26 - Vg_N_avg_26 - Thetag_N_avg_26 + vg_N_26) + square(Pg - Pg_N_init_27 + Pg_N_avg_27 + ug_N_27) + square(Thetag_27 - Vg_N_avg_27 - Thetag_N_avg_27 + vg_N_27) + square(Pg - Pg_N_init_28 + Pg_N_avg_28 + ug_N_28) + square(Thetag_28 - Vg_N_avg_28 - Thetag_N_avg_28 + vg_N_28) + square(Pg - Pg_N_init_29 + Pg_N_avg_29 + ug_N_29) + square(Thetag_29 - Vg_N_avg_29 - Thetag_N_avg_29 + vg_N_29) + square(Pg - Pg_N_init_30 + Pg_N_avg_30 + ug_N_30) + square(Thetag_30 - Vg_N_avg_30 - Thetag_N_avg_30 + vg_N_30) + square(Pg - Pg_N_init_31 + Pg_N_avg_31 + ug_N_31) + square(Thetag_31 - Vg_N_avg_31 - Thetag_N_avg_31 + vg_N_31) + square(Pg - Pg_N_init_32 + Pg_N_avg_32 + ug_N_32) + square(Thetag_32 - Vg_N_avg_32 - Thetag_N_avg_32 + vg_N_32) + square(Pg - Pg_N_init_33 + Pg_N_avg_33 + ug_N_33) + square(Thetag_33 - Vg_N_avg_33 - Thetag_N_avg_33 + vg_N_33) + square(Pg - Pg_N_init_34 + Pg_N_avg_34 + ug_N_34) + square(Thetag_34 - Vg_N_avg_34 - Thetag_N_avg_34 + vg_N_34) + square(Pg - Pg_N_init_35 + Pg_N_avg_35 + ug_N_35) + square(Thetag_35 - Vg_N_avg_35 - Thetag_N_avg_35 + vg_N_35) + square(Pg - Pg_N_init_36 + Pg_N_avg_36 + ug_N_36) + square(Thetag_36 - Vg_N_avg_36 - Thetag_N_avg_36 + vg_N_36) + square(Pg - Pg_N_init_37 + Pg_N_avg_37 + ug_N_37) + square(Thetag_37 - Vg_N_avg_37 - Thetag_N_avg_37 + vg_N_37) + square(Pg - Pg_N_init_38 + Pg_N_avg_38 + ug_N_38) + square(Thetag_38 - Vg_N_avg_38 - Thetag_N_avg_38 + vg_N_38) + square(Pg - Pg_N_init_39 + Pg_N_avg_39 + ug_N_39) + square(Thetag_39 - Vg_N_avg_39 - Thetag_N_avg_39 + vg_N_39) + square(Pg - Pg_N_init_40 + Pg_N_avg_40 + ug_N_40) + square(Thetag_40 - Vg_N_avg_40 - Thetag_N_avg_40 + vg_N_40) + square(Pg - Pg_N_init_41 + Pg_N_avg_41 + ug_N_41) + square(Thetag_41 - Vg_N_avg_41 - Thetag_N_avg_41 + vg_N_41) + square(Pg - Pg_N_init_42 + Pg_N_avg_42 + ug_N_42) + square(Thetag_42 - Vg_N_avg_42 - Thetag_N_avg_42 + vg_N_42) + square(Pg - Pg_N_init_43 + Pg_N_avg_43 + ug_N_43) + square(Thetag_43 - Vg_N_avg_43 - Thetag_N_avg_43 + vg_N_43) + square(Pg - Pg_N_init_44 + Pg_N_avg_44 + ug_N_44) + square(Thetag_44 - Vg_N_avg_44 - Thetag_N_avg_44 + vg_N_44) + square(Pg - Pg_N_init_45 + Pg_N_avg_45 + ug_N_45) + square(Thetag_45 - Vg_N_avg_45 - Thetag_N_avg_45 + vg_N_45) + square(Pg - Pg_N_init_46 + Pg_N_avg_46 + ug_N_46) + square(Thetag_46 - Vg_N_avg_46 - Thetag_N_avg_46 + vg_N_46) + square(Pg - Pg_N_init_47 + Pg_N_avg_47 + ug_N_47) + square(Thetag_47 - Vg_N_avg_47 - Thetag_N_avg_47 + vg_N_47) + square(Pg - Pg_N_init_48 + Pg_N_avg_48 + ug_N_48) + square(Thetag_48 - Vg_N_avg_48 - Thetag_N_avg_48 + vg_N_48) + square(Pg - Pg_N_init_49 + Pg_N_avg_49 + ug_N_49) + square(Thetag_49 - Vg_N_avg_49 - Thetag_N_avg_49 + vg_N_49) + square(Pg - Pg_N_init_50 + Pg_N_avg_50 + ug_N_50) + square(Thetag_50 - Vg_N_avg_50 - Thetag_N_avg_50 + vg_N_50) + square(Pg - Pg_N_init_51 + Pg_N_avg_51 + ug_N_51) + square(Thetag_51 - Vg_N_avg_51 - Thetag_N_avg_51 + vg_N_51) + square(Pg - Pg_N_init_52 + Pg_N_avg_52 + ug_N_52) + square(Thetag_52 - Vg_N_avg_52 - Thetag_N_avg_52 + vg_N_52) + square(Pg - Pg_N_init_53 + Pg_N_avg_53 + ug_N_53) + square(Thetag_53 - Vg_N_avg_53 - Thetag_N_avg_53 + vg_N_53) + square(Pg - Pg_N_init_54 + Pg_N_avg_54 + ug_N_54) + square(Thetag_54 - Vg_N_avg_54 - Thetag_N_avg_54 + vg_N_54) + square(Pg - Pg_N_init_55 + Pg_N_avg_55 + ug_N_55) + square(Thetag_55 - Vg_N_avg_55 - Thetag_N_avg_55 + vg_N_55) + square(Pg - Pg_N_init_56 + Pg_N_avg_56 + ug_N_56) + square(Thetag_56 - Vg_N_avg_56 - Thetag_N_avg_56 + vg_N_56) + square(Pg - Pg_N_init_57 + Pg_N_avg_57 + ug_N_57) + square(Thetag_57 - Vg_N_avg_57 - Thetag_N_avg_57 + vg_N_57) + square(Pg - Pg_N_init_58 + Pg_N_avg_58 + ug_N_58) + square(Thetag_58 - Vg_N_avg_58 - Thetag_N_avg_58 + vg_N_58) + square(Pg - Pg_N_init_59 + Pg_N_avg_59 + ug_N_59) + square(Thetag_59 - Vg_N_avg_59 - Thetag_N_avg_59 + vg_N_59) + square(Pg - Pg_N_init_60 + Pg_N_avg_60 + ug_N_60) + square(Thetag_60 - Vg_N_avg_60 - Thetag_N_avg_60 + vg_N_60) + square(Pg - Pg_N_init_61 + Pg_N_avg_61 + ug_N_61) + square(Thetag_61 - Vg_N_avg_61 - Thetag_N_avg_61 + vg_N_61) + square(Pg - Pg_N_init_62 + Pg_N_avg_62 + ug_N_62) + square(Thetag_62 - Vg_N_avg_62 - Thetag_N_avg_62 + vg_N_62) + square(Pg - Pg_N_init_63 + Pg_N_avg_63 + ug_N_63) + square(Thetag_63 - Vg_N_avg_63 - Thetag_N_avg_63 + vg_N_63) + square(Pg - Pg_N_init_64 + Pg_N_avg_64 + ug_N_64) + square(Thetag_64 - Vg_N_avg_64 - Thetag_N_avg_64 + vg_N_64) + square(Pg - Pg_N_init_65 + Pg_N_avg_65 + ug_N_65) + square(Thetag_65 - Vg_N_avg_65 - Thetag_N_avg_65 + vg_N_65) + square(Pg - Pg_N_init_66 + Pg_N_avg_66 + ug_N_66) + square(Thetag_66 - Vg_N_avg_66 - Thetag_N_avg_66 + vg_N_66) + square(Pg - Pg_N_init_67 + Pg_N_avg_67 + ug_N_67) + square(Thetag_67 - Vg_N_avg_67 - Thetag_N_avg_67 + vg_N_67) + square(Pg - Pg_N_init_68 + Pg_N_avg_68 + ug_N_68) + square(Thetag_68 - Vg_N_avg_68 - Thetag_N_avg_68 + vg_N_68) + square(Pg - Pg_N_init_69 + Pg_N_avg_69 + ug_N_69) + square(Thetag_69 - Vg_N_avg_69 - Thetag_N_avg_69 + vg_N_69) + square(Pg - Pg_N_init_70 + Pg_N_avg_70 + ug_N_70) + square(Thetag_70 - Vg_N_avg_70 - Thetag_N_avg_70 + vg_N_70) + square(Pg - Pg_N_init_71 + Pg_N_avg_71 + ug_N_71) + square(Thetag_71 - Vg_N_avg_71 - Thetag_N_avg_71 + vg_N_71) + square(Pg - Pg_N_init_72 + Pg_N_avg_72 + ug_N_72) + square(Thetag_72 - Vg_N_avg_72 - Thetag_N_avg_72 + vg_N_72) + square(Pg - Pg_N_init_73 + Pg_N_avg_73 + ug_N_73) + square(Thetag_73 - Vg_N_avg_73 - Thetag_N_avg_73 + vg_N_73) + square(Pg - Pg_N_init_74 + Pg_N_avg_74 + ug_N_74) + square(Thetag_74 - Vg_N_avg_74 - Thetag_N_avg_74 + vg_N_74) + square(Pg - Pg_N_init_75 + Pg_N_avg_75 + ug_N_75) + square(Thetag_75 - Vg_N_avg_75 - Thetag_N_avg_75 + vg_N_75) + square(Pg - Pg_N_init_76 + Pg_N_avg_76 + ug_N_76) + square(Thetag_76 - Vg_N_avg_76 - Thetag_N_avg_76 + vg_N_76) + square(Pg - Pg_N_init_77 + Pg_N_avg_77 + ug_N_77) + square(Thetag_77 - Vg_N_avg_77 - Thetag_N_avg_77 + vg_N_77) + square(Pg - Pg_N_init_78 + Pg_N_avg_78 + ug_N_78) + square(Thetag_78 - Vg_N_avg_78 - Thetag_N_avg_78 + vg_N_78) + square(Pg - Pg_N_init_79 + Pg_N_avg_79 + ug_N_79) + square(Thetag_79 - Vg_N_avg_79 - Thetag_N_avg_79 + vg_N_79) + square(Pg - Pg_N_init_80 + Pg_N_avg_80 + ug_N_80) + square(Thetag_80 - Vg_N_avg_80 - Thetag_N_avg_80 + vg_N_80) + square(Pg - Pg_N_init_81 + Pg_N_avg_81 + ug_N_81) + square(Thetag_81 - Vg_N_avg_81 - Thetag_N_avg_81 + vg_N_81) + square(Pg - Pg_N_init_82 + Pg_N_avg_82 + ug_N_82) + square(Thetag_82 - Vg_N_avg_82 - Thetag_N_avg_82 + vg_N_82) + square(Pg - Pg_N_init_83 + Pg_N_avg_83 + ug_N_83) + square(Thetag_83 - Vg_N_avg_83 - Thetag_N_avg_83 + vg_N_83) + square(Pg - Pg_N_init_84 + Pg_N_avg_84 + ug_N_84) + square(Thetag_84 - Vg_N_avg_84 - Thetag_N_avg_84 + vg_N_84) + square(Pg - Pg_N_init_85 + Pg_N_avg_85 + ug_N_85) + square(Thetag_85 - Vg_N_avg_85 - Thetag_N_avg_85 + vg_N_85) + square(Pg - Pg_N_init_86 + Pg_N_avg_86 + ug_N_86) + square(Thetag_86 - Vg_N_avg_86 - Thetag_N_avg_86 + vg_N_86) + square(Pg - Pg_N_init_87 + Pg_N_avg_87 + ug_N_87) + square(Thetag_87 - Vg_N_avg_87 - Thetag_N_avg_87 + vg_N_87) + square(Pg - Pg_N_init_88 + Pg_N_avg_88 + ug_N_88) + square(Thetag_88 - Vg_N_avg_88 - Thetag_N_avg_88 + vg_N_88) + square(Pg - Pg_N_init_89 + Pg_N_avg_89 + ug_N_89) + square(Thetag_89 - Vg_N_avg_89 - Thetag_N_avg_89 + vg_N_89) + square(Pg - Pg_N_init_90 + Pg_N_avg_90 + ug_N_90) + square(Thetag_90 - Vg_N_avg_90 - Thetag_N_avg_90 + vg_N_90) + square(Pg - Pg_N_init_91 + Pg_N_avg_91 + ug_N_91) + square(Thetag_91 - Vg_N_avg_91 - Thetag_N_avg_91 + vg_N_91) + square(Pg - Pg_N_init_92 + Pg_N_avg_92 + ug_N_92) + square(Thetag_92 - Vg_N_avg_92 - Thetag_N_avg_92 + vg_N_92) + square(Pg - Pg_N_init_93 + Pg_N_avg_93 + ug_N_93) + square(Thetag_93 - Vg_N_avg_93 - Thetag_N_avg_93 + vg_N_93) + square(Pg - Pg_N_init_94 + Pg_N_avg_94 + ug_N_94) + square(Thetag_94 - Vg_N_avg_94 - Thetag_N_avg_94 + vg_N_94) + square(Pg - Pg_N_init_95 + Pg_N_avg_95 + ug_N_95) + square(Thetag_95 - Vg_N_avg_95 - Thetag_N_avg_95 + vg_N_95) + square(Pg - Pg_N_init_96 + Pg_N_avg_96 + ug_N_96) + square(Thetag_96 - Vg_N_avg_96 - Thetag_N_avg_96 + vg_N_96) + square(Pg - Pg_N_init_97 + Pg_N_avg_97 + ug_N_97) + square(Thetag_97 - Vg_N_avg_97 - Thetag_N_avg_97 + vg_N_97) + square(Pg - Pg_N_init_98 + Pg_N_avg_98 + ug_N_98) + square(Thetag_98 - Vg_N_avg_98 - Thetag_N_avg_98 + vg_N_98) + square(Pg - Pg_N_init_99 + Pg_N_avg_99 + ug_N_99) + square(Thetag_99 - Vg_N_avg_99 - Thetag_N_avg_99 + vg_N_99) + square(Pg - Pg_N_init_100 + Pg_N_avg_100 + ug_N_100) + square(Thetag_100 - Vg_N_avg_100 - Thetag_N_avg_100 + vg_N_100) + square(Pg - Pg_N_init_101 + Pg_N_avg_101 + ug_N_101) + square(Thetag_101 - Vg_N_avg_101 - Thetag_N_avg_101 + vg_N_101) + contNum*square(Pg)));
  subject to
    PgMin <= Pg;
    Pg <= PgMax;
cvx_end
vars.Pg = Pg;
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
vars.Thetag_11 = Thetag_11;
vars.Thetag{11} = Thetag_11;
vars.Thetag_12 = Thetag_12;
vars.Thetag{12} = Thetag_12;
vars.Thetag_13 = Thetag_13;
vars.Thetag{13} = Thetag_13;
vars.Thetag_14 = Thetag_14;
vars.Thetag{14} = Thetag_14;
vars.Thetag_15 = Thetag_15;
vars.Thetag{15} = Thetag_15;
vars.Thetag_16 = Thetag_16;
vars.Thetag{16} = Thetag_16;
vars.Thetag_17 = Thetag_17;
vars.Thetag{17} = Thetag_17;
vars.Thetag_18 = Thetag_18;
vars.Thetag{18} = Thetag_18;
vars.Thetag_19 = Thetag_19;
vars.Thetag{19} = Thetag_19;
vars.Thetag_20 = Thetag_20;
vars.Thetag{20} = Thetag_20;
vars.Thetag_21 = Thetag_21;
vars.Thetag{21} = Thetag_21;
vars.Thetag_22 = Thetag_22;
vars.Thetag{22} = Thetag_22;
vars.Thetag_23 = Thetag_23;
vars.Thetag{23} = Thetag_23;
vars.Thetag_24 = Thetag_24;
vars.Thetag{24} = Thetag_24;
vars.Thetag_25 = Thetag_25;
vars.Thetag{25} = Thetag_25;
vars.Thetag_26 = Thetag_26;
vars.Thetag{26} = Thetag_26;
vars.Thetag_27 = Thetag_27;
vars.Thetag{27} = Thetag_27;
vars.Thetag_28 = Thetag_28;
vars.Thetag{28} = Thetag_28;
vars.Thetag_29 = Thetag_29;
vars.Thetag{29} = Thetag_29;
vars.Thetag_30 = Thetag_30;
vars.Thetag{30} = Thetag_30;
vars.Thetag_31 = Thetag_31;
vars.Thetag{31} = Thetag_31;
vars.Thetag_32 = Thetag_32;
vars.Thetag{32} = Thetag_32;
vars.Thetag_33 = Thetag_33;
vars.Thetag{33} = Thetag_33;
vars.Thetag_34 = Thetag_34;
vars.Thetag{34} = Thetag_34;
vars.Thetag_35 = Thetag_35;
vars.Thetag{35} = Thetag_35;
vars.Thetag_36 = Thetag_36;
vars.Thetag{36} = Thetag_36;
vars.Thetag_37 = Thetag_37;
vars.Thetag{37} = Thetag_37;
vars.Thetag_38 = Thetag_38;
vars.Thetag{38} = Thetag_38;
vars.Thetag_39 = Thetag_39;
vars.Thetag{39} = Thetag_39;
vars.Thetag_40 = Thetag_40;
vars.Thetag{40} = Thetag_40;
vars.Thetag_41 = Thetag_41;
vars.Thetag{41} = Thetag_41;
vars.Thetag_42 = Thetag_42;
vars.Thetag{42} = Thetag_42;
vars.Thetag_43 = Thetag_43;
vars.Thetag{43} = Thetag_43;
vars.Thetag_44 = Thetag_44;
vars.Thetag{44} = Thetag_44;
vars.Thetag_45 = Thetag_45;
vars.Thetag{45} = Thetag_45;
vars.Thetag_46 = Thetag_46;
vars.Thetag{46} = Thetag_46;
vars.Thetag_47 = Thetag_47;
vars.Thetag{47} = Thetag_47;
vars.Thetag_48 = Thetag_48;
vars.Thetag{48} = Thetag_48;
vars.Thetag_49 = Thetag_49;
vars.Thetag{49} = Thetag_49;
vars.Thetag_50 = Thetag_50;
vars.Thetag{50} = Thetag_50;
vars.Thetag_51 = Thetag_51;
vars.Thetag{51} = Thetag_51;
vars.Thetag_52 = Thetag_52;
vars.Thetag{52} = Thetag_52;
vars.Thetag_53 = Thetag_53;
vars.Thetag{53} = Thetag_53;
vars.Thetag_54 = Thetag_54;
vars.Thetag{54} = Thetag_54;
vars.Thetag_55 = Thetag_55;
vars.Thetag{55} = Thetag_55;
vars.Thetag_56 = Thetag_56;
vars.Thetag{56} = Thetag_56;
vars.Thetag_57 = Thetag_57;
vars.Thetag{57} = Thetag_57;
vars.Thetag_58 = Thetag_58;
vars.Thetag{58} = Thetag_58;
vars.Thetag_59 = Thetag_59;
vars.Thetag{59} = Thetag_59;
vars.Thetag_60 = Thetag_60;
vars.Thetag{60} = Thetag_60;
vars.Thetag_61 = Thetag_61;
vars.Thetag{61} = Thetag_61;
vars.Thetag_62 = Thetag_62;
vars.Thetag{62} = Thetag_62;
vars.Thetag_63 = Thetag_63;
vars.Thetag{63} = Thetag_63;
vars.Thetag_64 = Thetag_64;
vars.Thetag{64} = Thetag_64;
vars.Thetag_65 = Thetag_65;
vars.Thetag{65} = Thetag_65;
vars.Thetag_66 = Thetag_66;
vars.Thetag{66} = Thetag_66;
vars.Thetag_67 = Thetag_67;
vars.Thetag{67} = Thetag_67;
vars.Thetag_68 = Thetag_68;
vars.Thetag{68} = Thetag_68;
vars.Thetag_69 = Thetag_69;
vars.Thetag{69} = Thetag_69;
vars.Thetag_70 = Thetag_70;
vars.Thetag{70} = Thetag_70;
vars.Thetag_71 = Thetag_71;
vars.Thetag{71} = Thetag_71;
vars.Thetag_72 = Thetag_72;
vars.Thetag{72} = Thetag_72;
vars.Thetag_73 = Thetag_73;
vars.Thetag{73} = Thetag_73;
vars.Thetag_74 = Thetag_74;
vars.Thetag{74} = Thetag_74;
vars.Thetag_75 = Thetag_75;
vars.Thetag{75} = Thetag_75;
vars.Thetag_76 = Thetag_76;
vars.Thetag{76} = Thetag_76;
vars.Thetag_77 = Thetag_77;
vars.Thetag{77} = Thetag_77;
vars.Thetag_78 = Thetag_78;
vars.Thetag{78} = Thetag_78;
vars.Thetag_79 = Thetag_79;
vars.Thetag{79} = Thetag_79;
vars.Thetag_80 = Thetag_80;
vars.Thetag{80} = Thetag_80;
vars.Thetag_81 = Thetag_81;
vars.Thetag{81} = Thetag_81;
vars.Thetag_82 = Thetag_82;
vars.Thetag{82} = Thetag_82;
vars.Thetag_83 = Thetag_83;
vars.Thetag{83} = Thetag_83;
vars.Thetag_84 = Thetag_84;
vars.Thetag{84} = Thetag_84;
vars.Thetag_85 = Thetag_85;
vars.Thetag{85} = Thetag_85;
vars.Thetag_86 = Thetag_86;
vars.Thetag{86} = Thetag_86;
vars.Thetag_87 = Thetag_87;
vars.Thetag{87} = Thetag_87;
vars.Thetag_88 = Thetag_88;
vars.Thetag{88} = Thetag_88;
vars.Thetag_89 = Thetag_89;
vars.Thetag{89} = Thetag_89;
vars.Thetag_90 = Thetag_90;
vars.Thetag{90} = Thetag_90;
vars.Thetag_91 = Thetag_91;
vars.Thetag{91} = Thetag_91;
vars.Thetag_92 = Thetag_92;
vars.Thetag{92} = Thetag_92;
vars.Thetag_93 = Thetag_93;
vars.Thetag{93} = Thetag_93;
vars.Thetag_94 = Thetag_94;
vars.Thetag{94} = Thetag_94;
vars.Thetag_95 = Thetag_95;
vars.Thetag{95} = Thetag_95;
vars.Thetag_96 = Thetag_96;
vars.Thetag{96} = Thetag_96;
vars.Thetag_97 = Thetag_97;
vars.Thetag{97} = Thetag_97;
vars.Thetag_98 = Thetag_98;
vars.Thetag{98} = Thetag_98;
vars.Thetag_99 = Thetag_99;
vars.Thetag{99} = Thetag_99;
vars.Thetag_100 = Thetag_100;
vars.Thetag{100} = Thetag_100;
vars.Thetag_101 = Thetag_101;
vars.Thetag{101} = Thetag_101;
status.cvx_status = cvx_status;
% Provide a drop-in replacement for csolve.
status.optval = cvx_optval;
status.converged = strcmp(cvx_status, 'Solved');
