% csolve  Solves a custom quadratic program very rapidly.
%
% [vars, status] = csolve(params, settings)
%
% solves the convex optimization problem
%
%   minimize(c2*square(Pg) + c1*Pg + c0 + (rho/2)*(square(Pg - Pg_N_init_0 + Pg_N_avg_0 + ug_N_0) + square(Thetag_0 - Vg_N_avg_0 - Thetag_N_avg_0 + vg_N_0) + square(Pg - Pg_N_init_1 + Pg_N_avg_1 + ug_N_1) + square(Thetag_1 - Vg_N_avg_1 - Thetag_N_avg_1 + vg_N_1) + square(Pg - Pg_N_init_2 + Pg_N_avg_2 + ug_N_2) + square(Thetag_2 - Vg_N_avg_2 - Thetag_N_avg_2 + vg_N_2) + square(Pg - Pg_N_init_3 + Pg_N_avg_3 + ug_N_3) + square(Thetag_3 - Vg_N_avg_3 - Thetag_N_avg_3 + vg_N_3) + square(Pg - Pg_N_init_4 + Pg_N_avg_4 + ug_N_4) + square(Thetag_4 - Vg_N_avg_4 - Thetag_N_avg_4 + vg_N_4) + square(Pg - Pg_N_init_5 + Pg_N_avg_5 + ug_N_5) + square(Thetag_5 - Vg_N_avg_5 - Thetag_N_avg_5 + vg_N_5) + square(Pg - Pg_N_init_6 + Pg_N_avg_6 + ug_N_6) + square(Thetag_6 - Vg_N_avg_6 - Thetag_N_avg_6 + vg_N_6) + square(Pg - Pg_N_init_7 + Pg_N_avg_7 + ug_N_7) + square(Thetag_7 - Vg_N_avg_7 - Thetag_N_avg_7 + vg_N_7) + square(Pg - Pg_N_init_8 + Pg_N_avg_8 + ug_N_8) + square(Thetag_8 - Vg_N_avg_8 - Thetag_N_avg_8 + vg_N_8) + square(Pg - Pg_N_init_9 + Pg_N_avg_9 + ug_N_9) + square(Thetag_9 - Vg_N_avg_9 - Thetag_N_avg_9 + vg_N_9) + square(Pg - Pg_N_init_10 + Pg_N_avg_10 + ug_N_10) + square(Thetag_10 - Vg_N_avg_10 - Thetag_N_avg_10 + vg_N_10) + square(Pg - Pg_N_init_11 + Pg_N_avg_11 + ug_N_11) + square(Thetag_11 - Vg_N_avg_11 - Thetag_N_avg_11 + vg_N_11) + square(Pg - Pg_N_init_12 + Pg_N_avg_12 + ug_N_12) + square(Thetag_12 - Vg_N_avg_12 - Thetag_N_avg_12 + vg_N_12) + square(Pg - Pg_N_init_13 + Pg_N_avg_13 + ug_N_13) + square(Thetag_13 - Vg_N_avg_13 - Thetag_N_avg_13 + vg_N_13) + square(Pg - Pg_N_init_14 + Pg_N_avg_14 + ug_N_14) + square(Thetag_14 - Vg_N_avg_14 - Thetag_N_avg_14 + vg_N_14) + square(Pg - Pg_N_init_15 + Pg_N_avg_15 + ug_N_15) + square(Thetag_15 - Vg_N_avg_15 - Thetag_N_avg_15 + vg_N_15) + square(Pg - Pg_N_init_16 + Pg_N_avg_16 + ug_N_16) + square(Thetag_16 - Vg_N_avg_16 - Thetag_N_avg_16 + vg_N_16) + square(Pg - Pg_N_init_17 + Pg_N_avg_17 + ug_N_17) + square(Thetag_17 - Vg_N_avg_17 - Thetag_N_avg_17 + vg_N_17) + square(Pg - Pg_N_init_18 + Pg_N_avg_18 + ug_N_18) + square(Thetag_18 - Vg_N_avg_18 - Thetag_N_avg_18 + vg_N_18) + square(Pg - Pg_N_init_19 + Pg_N_avg_19 + ug_N_19) + square(Thetag_19 - Vg_N_avg_19 - Thetag_N_avg_19 + vg_N_19) + square(Pg - Pg_N_init_20 + Pg_N_avg_20 + ug_N_20) + square(Thetag_20 - Vg_N_avg_20 - Thetag_N_avg_20 + vg_N_20) + square(Pg - Pg_N_init_21 + Pg_N_avg_21 + ug_N_21) + square(Thetag_21 - Vg_N_avg_21 - Thetag_N_avg_21 + vg_N_21) + square(Pg - Pg_N_init_22 + Pg_N_avg_22 + ug_N_22) + square(Thetag_22 - Vg_N_avg_22 - Thetag_N_avg_22 + vg_N_22) + square(Pg - Pg_N_init_23 + Pg_N_avg_23 + ug_N_23) + square(Thetag_23 - Vg_N_avg_23 - Thetag_N_avg_23 + vg_N_23) + square(Pg - Pg_N_init_24 + Pg_N_avg_24 + ug_N_24) + square(Thetag_24 - Vg_N_avg_24 - Thetag_N_avg_24 + vg_N_24) + square(Pg - Pg_N_init_25 + Pg_N_avg_25 + ug_N_25) + square(Thetag_25 - Vg_N_avg_25 - Thetag_N_avg_25 + vg_N_25) + square(Pg - Pg_N_init_26 + Pg_N_avg_26 + ug_N_26) + square(Thetag_26 - Vg_N_avg_26 - Thetag_N_avg_26 + vg_N_26) + square(Pg - Pg_N_init_27 + Pg_N_avg_27 + ug_N_27) + square(Thetag_27 - Vg_N_avg_27 - Thetag_N_avg_27 + vg_N_27) + square(Pg - Pg_N_init_28 + Pg_N_avg_28 + ug_N_28) + square(Thetag_28 - Vg_N_avg_28 - Thetag_N_avg_28 + vg_N_28) + square(Pg - Pg_N_init_29 + Pg_N_avg_29 + ug_N_29) + square(Thetag_29 - Vg_N_avg_29 - Thetag_N_avg_29 + vg_N_29) + square(Pg - Pg_N_init_30 + Pg_N_avg_30 + ug_N_30) + square(Thetag_30 - Vg_N_avg_30 - Thetag_N_avg_30 + vg_N_30) + square(Pg - Pg_N_init_31 + Pg_N_avg_31 + ug_N_31) + square(Thetag_31 - Vg_N_avg_31 - Thetag_N_avg_31 + vg_N_31) + square(Pg - Pg_N_init_32 + Pg_N_avg_32 + ug_N_32) + square(Thetag_32 - Vg_N_avg_32 - Thetag_N_avg_32 + vg_N_32) + square(Pg - Pg_N_init_33 + Pg_N_avg_33 + ug_N_33) + square(Thetag_33 - Vg_N_avg_33 - Thetag_N_avg_33 + vg_N_33) + square(Pg - Pg_N_init_34 + Pg_N_avg_34 + ug_N_34) + square(Thetag_34 - Vg_N_avg_34 - Thetag_N_avg_34 + vg_N_34) + square(Pg - Pg_N_init_35 + Pg_N_avg_35 + ug_N_35) + square(Thetag_35 - Vg_N_avg_35 - Thetag_N_avg_35 + vg_N_35) + square(Pg - Pg_N_init_36 + Pg_N_avg_36 + ug_N_36) + square(Thetag_36 - Vg_N_avg_36 - Thetag_N_avg_36 + vg_N_36) + square(Pg - Pg_N_init_37 + Pg_N_avg_37 + ug_N_37) + square(Thetag_37 - Vg_N_avg_37 - Thetag_N_avg_37 + vg_N_37) + square(Pg - Pg_N_init_38 + Pg_N_avg_38 + ug_N_38) + square(Thetag_38 - Vg_N_avg_38 - Thetag_N_avg_38 + vg_N_38) + square(Pg - Pg_N_init_39 + Pg_N_avg_39 + ug_N_39) + square(Thetag_39 - Vg_N_avg_39 - Thetag_N_avg_39 + vg_N_39) + square(Pg - Pg_N_init_40 + Pg_N_avg_40 + ug_N_40) + square(Thetag_40 - Vg_N_avg_40 - Thetag_N_avg_40 + vg_N_40) + square(Pg - Pg_N_init_41 + Pg_N_avg_41 + ug_N_41) + square(Thetag_41 - Vg_N_avg_41 - Thetag_N_avg_41 + vg_N_41) + square(Pg - Pg_N_init_42 + Pg_N_avg_42 + ug_N_42) + square(Thetag_42 - Vg_N_avg_42 - Thetag_N_avg_42 + vg_N_42) + square(Pg - Pg_N_init_43 + Pg_N_avg_43 + ug_N_43) + square(Thetag_43 - Vg_N_avg_43 - Thetag_N_avg_43 + vg_N_43) + square(Pg - Pg_N_init_44 + Pg_N_avg_44 + ug_N_44) + square(Thetag_44 - Vg_N_avg_44 - Thetag_N_avg_44 + vg_N_44) + square(Pg - Pg_N_init_45 + Pg_N_avg_45 + ug_N_45) + square(Thetag_45 - Vg_N_avg_45 - Thetag_N_avg_45 + vg_N_45) + square(Pg - Pg_N_init_46 + Pg_N_avg_46 + ug_N_46) + square(Thetag_46 - Vg_N_avg_46 - Thetag_N_avg_46 + vg_N_46) + square(Pg - Pg_N_init_47 + Pg_N_avg_47 + ug_N_47) + square(Thetag_47 - Vg_N_avg_47 - Thetag_N_avg_47 + vg_N_47) + square(Pg - Pg_N_init_48 + Pg_N_avg_48 + ug_N_48) + square(Thetag_48 - Vg_N_avg_48 - Thetag_N_avg_48 + vg_N_48) + square(Pg - Pg_N_init_49 + Pg_N_avg_49 + ug_N_49) + square(Thetag_49 - Vg_N_avg_49 - Thetag_N_avg_49 + vg_N_49) + square(Pg - Pg_N_init_50 + Pg_N_avg_50 + ug_N_50) + square(Thetag_50 - Vg_N_avg_50 - Thetag_N_avg_50 + vg_N_50) + square(Pg - Pg_N_init_51 + Pg_N_avg_51 + ug_N_51) + square(Thetag_51 - Vg_N_avg_51 - Thetag_N_avg_51 + vg_N_51) + square(Pg - Pg_N_init_52 + Pg_N_avg_52 + ug_N_52) + square(Thetag_52 - Vg_N_avg_52 - ThetagONkvo^52 + vg_N_52) + square(Pg - Pg_N_init_53 + Pg_N_avg_53 + ug_N_5�) i square(Thetag_53 - Vg_N]a~f_53 - Thetag_N_evw]53 + vgN�%3+ #!sq}aRa(Pg - Pg_N_init_54 + Pg_N_avg_54 + ug_N_54) + square(Thetag_54 
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
% Thetag_11   1 x 1
% Thetag_12   1 x 1
% Thetag_13   1 x 1
% Thetag_14   1 x 1
% Thetag_15   1 x 1
% Thetag_16   1 x 1
% Thetag_17   1 x 1
% Thetag_18   1 x 1
% Thetag_19   1 x 1
% Thetag_20   1 x 1
% Thetag_21   1 x 1
% Thetag_22   1 x 1
% Thetag_23   1 x 1
% Thetag_24   1 x 1
% Thetag_25   1 x 1
% Thetag_26   1 x 1
% Thetag_27   1 x 1
% Thetag_28   1 x 1
% Thetag_29   1 x 1
% Thetag_30   1 x 1
% Thetag_31   1 x 1
% Thetag_32   1 x 1
% Thetag_33   1 x 1
% Thetag_34   1 x 1
% Thetag_35   1 x 1
% Thetag_36   1 x 1
% Thetag_37   1 x 1
% Thetag_38   1 x 1
% Thetag_39   1 x 1
% Thetag_40   1 x 1
% Thetag_41   1 x 1
% Thetag_42   1 x 1
% Thetag_43   1 x 1
% Thetag_44   1 x 1
% Thetag_45   1 x 1
% Thetag_46   1 x 1
% Thetag_47   1 x 1
% Thetag_48   1 x 1
% Thetag_49   1 x 1
% Thetag_50   1 x 1
% Thetag_51   1 x 1
% Thetag_52   1 x 1
% Thetag_53   1 x 1
% Thetag_54   1 x 1
% Thetag_55   1 x 1
% Thetag_56   1 x 1
% Thetag_57   1 x 1
% Thetag_58   1 x 1
% Thetag_59   1 x 1
% Thetag_60   1 x 1
% Thetag_61   1 x 1
% Thetag_62   1 x 1
% Thetag_63   1 x 1
% Thetag_64   1 x 1
% Thetag_65   1 x 1
% Thetag_66   1 x 1
% Thetag_67   1 x 1
% Thetag_68   1 x 1
% Thetag_69   1 x 1
% Thetag_70   1 x 1
% Thetag_71   1 x 1
% Thetag_72   1 x 1
% Thetag_73   1 x 1
% Thetag_74   1 x 1
% Thetag_75   1 x 1
% Thetag_76   1 x 1
% Thetag_77   1 x 1
% Thetag_78   1 x 1
% Thetag_79   1 x 1
% Thetag_80   1 x 1
% Thetag_81   1 x 1
% Thetag_82   1 x 1
% Thetag_83   1 x 1
% Thetag_84   1 x 1
% Thetag_85   1 x 1
% Thetag_86   1 x 1
% Thetag_87   1 x 1
% Thetag_88   1 x 1
% Thetag_89   1 x 1
% Thetag_90   1 x 1
% Thetag_91   1 x 1
% Thetag_92   1 x 1
% Thetag_93   1 x 1
% Thetag_94   1 x 1
% Thetag_95   1 x 1
% Thetag_96   1 x 1
% Thetag_97   1 x 1
% Thetag_98   1 x 1
% Thetag_99   1 x 1
% Thetag_100   1 x 1
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
% Pg_N_avg_11   1 x 1
% Pg_N_avg_12   1 x 1
% Pg_N_avg_13   1 x 1
% Pg_N_avg_14   1 x 1
% Pg_N_avg_15   1 x 1
% Pg_N_avg_16   1 x 1
% Pg_N_avg_17   1 x 1
% Pg_N_avg_18   1 x 1
% Pg_N_avg_19   1 x 1
% Pg_N_avg_20   1 x 1
% Pg_N_avg_21   1 x 1
% Pg_N_avg_22   1 x 1
% Pg_N_avg_23   1 x 1
% Pg_N_avg_24   1 x 1
% Pg_N_avg_25   1 x 1
% Pg_N_avg_26   1 x 1
% Pg_N_avg_27   1 x 1
% Pg_N_avg_28   1 x 1
% Pg_N_avg_29   1 x 1
% Pg_N_avg_30   1 x 1
% Pg_N_avg_31   1 x 1
% Pg_N_avg_32   1 x 1
% Pg_N_avg_33   1 x 1
% Pg_N_avg_34   1 x 1
% Pg_N_avg_35   1 x 1
% Pg_N_avg_36   1 x 1
% Pg_N_avg_37   1 x 1
% Pg_N_avg_38   1 x 1
% Pg_N_avg_39   1 x 1
% Pg_N_avg_40   1 x 1
% Pg_N_avg_41   1 x 1
% Pg_N_avg_42   1 x 1
% Pg_N_avg_43   1 x 1
% Pg_N_avg_44   1 x 1
% Pg_N_avg_45   1 x 1
% Pg_N_avg_46   1 x 1
% Pg_N_avg_47   1 x 1
% Pg_N_avg_48   1 x 1
% Pg_N_avg_49   1 x 1
% Pg_N_avg_50   1 x 1
% Pg_N_avg_51   1 x 1
% Pg_N_avg_52   1 x 1
% Pg_N_avg_53   1 x 1
% Pg_N_avg_54   1 x 1
% Pg_N_avg_55   1 x 1
% Pg_N_avg_56   1 x 1
% Pg_N_avg_57   1 x 1
% Pg_N_avg_58   1 x 1
% Pg_N_avg_59   1 x 1
% Pg_N_avg_60   1 x 1
% Pg_N_avg_61   1 x 1
% Pg_N_avg_62   1 x 1
% Pg_N_avg_63   1 x 1
% Pg_N_avg_64   1 x 1
% Pg_N_avg_65   1 x 1
% Pg_N_avg_66   1 x 1
% Pg_N_avg_67   1 x 1
% Pg_N_avg_68   1 x 1
% Pg_N_avg_69   1 x 1
% Pg_N_avg_70   1 x 1
% Pg_N_avg_71   1 x 1
% Pg_N_avg_72   1 x 1
% Pg_N_avg_73   1 x 1
% Pg_N_avg_74   1 x 1
% Pg_N_avg_75   1 x 1
% Pg_N_avg_76   1 x 1
% Pg_N_avg_77   1 x 1
% Pg_N_avg_78   1 x 1
% Pg_N_avg_79   1 x 1
% Pg_N_avg_80   1 x 1
% Pg_N_avg_81   1 x 1
% Pg_N_avg_82   1 x 1
% Pg_N_avg_83   1 x 1
% Pg_N_avg_84   1 x 1
% Pg_N_avg_85   1 x 1
% Pg_N_avg_86   1 x 1
% Pg_N_avg_87   1 x 1
% Pg_N_avg_88   1 x 1
% Pg_N_avg_89   1 x 1
% Pg_N_avg_90   1 x 1
% Pg_N_avg_91   1 x 1
% Pg_N_avg_92   1 x 1
% Pg_N_avg_93   1 x 1
% Pg_N_avg_94   1 x 1
% Pg_N_avg_95   1 x 1
% Pg_N_avg_96   1 x 1
% Pg_N_avg_97   1 x 1
% Pg_N_avg_98   1 x 1
% Pg_N_avg_99   1 x 1
% Pg_N_avg_100   1 x 1
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
% Pg_N_init_11   1 x 1
% Pg_N_init_12   1 x 1
% Pg_N_init_13   1 x 1
% Pg_N_init_14   1 x 1
% Pg_N_init_15   1 x 1
% Pg_N_init_16   1 x 1
% Pg_N_init_17   1 x 1
% Pg_N_init_18   1 x 1
% Pg_N_init_19   1 x 1
% Pg_N_init_20   1 x 1
% Pg_N_init_21   1 x 1
% Pg_N_init_22   1 x 1
% Pg_N_init_23   1 x 1
% Pg_N_init_24   1 x 1
% Pg_N_init_25   1 x 1
% Pg_N_init_26   1 x 1
% Pg_N_init_27   1 x 1
% Pg_N_init_28   1 x 1
% Pg_N_init_29   1 x 1
% Pg_N_init_30   1 x 1
% Pg_N_init_31   1 x 1
% Pg_N_init_32   1 x 1
% Pg_N_init_33   1 x 1
% Pg_N_init_34   1 x 1
% Pg_N_init_35   1 x 1
% Pg_N_init_36   1 x 1
% Pg_N_init_37   1 x 1
% Pg_N_init_38   1 x 1
% Pg_N_init_39   1 x 1
% Pg_N_init_40   1 x 1
% Pg_N_init_41   1 x 1
% Pg_N_init_42   1 x 1
% Pg_N_init_43   1 x 1
% Pg_N_init_44   1 x 1
% Pg_N_init_45   1 x 1
% Pg_N_init_46   1 x 1
% Pg_N_init_47   1 x 1
% Pg_N_init_48   1 x 1
% Pg_N_init_49   1 x 1
% Pg_N_init_50   1 x 1
% Pg_N_init_51   1 x 1
% Pg_N_init_52   1 x 1
% Pg_N_init_53   1 x 1
% Pg_N_init_54   1 x 1
% Pg_N_init_55   1 x 1
% Pg_N_init_56   1 x 1
% Pg_N_init_57   1 x 1
% Pg_N_init_58   1 x 1
% Pg_N_init_59   1 x 1
% Pg_N_init_60   1 x 1
% Pg_N_init_61   1 x 1
% Pg_N_init_62   1 x 1
% Pg_N_init_63   1 x 1
% Pg_N_init_64   1 x 1
% Pg_N_init_65   1 x 1
% Pg_N_init_66   1 x 1
% Pg_N_init_67   1 x 1
% Pg_N_init_68   1 x 1
% Pg_N_init_69   1 x 1
% Pg_N_init_70   1 x 1
% Pg_N_init_71   1 x 1
% Pg_N_init_72   1 x 1
% Pg_N_init_73   1 x 1
% Pg_N_init_74   1 x 1
% Pg_N_init_75   1 x 1
% Pg_N_init_76   1 x 1
% Pg_N_init_77   1 x 1
% Pg_N_init_78   1 x 1
% Pg_N_init_79   1 x 1
% Pg_N_init_80   1 x 1
% Pg_N_init_81   1 x 1
% Pg_N_init_82   1 x 1
% Pg_N_init_83   1 x 1
% Pg_N_init_84   1 x 1
% Pg_N_init_85   1 x 1
% Pg_N_init_86   1 x 1
% Pg_N_init_87   1 x 1
% Pg_N_init_88   1 x 1
% Pg_N_init_89   1 x 1
% Pg_N_init_90   1 x 1
% Pg_N_init_91   1 x 1
% Pg_N_init_92   1 x 1
% Pg_N_init_93   1 x 1
% Pg_N_init_94   1 x 1
% Pg_N_init_95   1 x 1
% Pg_N_init_96   1 x 1
% Pg_N_init_97   1 x 1
% Pg_N_init_98   1 x 1
% Pg_N_init_99   1 x 1
% Pg_N_init_100   1 x 1
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
% Thetag_N_avg_11   1 x 1
% Thetag_N_avg_12   1 x 1
% Thetag_N_avg_13   1 x 1
% Thetag_N_avg_14   1 x 1
% Thetag_N_avg_15   1 x 1
% Thetag_N_avg_16   1 x 1
% Thetag_N_avg_17   1 x 1
% Thetag_N_avg_18   1 x 1
% Thetag_N_avg_19   1 x 1
% Thetag_N_avg_20   1 x 1
% Thetag_N_avg_21   1 x 1
% Thetag_N_avg_22   1 x 1
% Thetag_N_avg_23   1 x 1
% Thetag_N_avg_24   1 x 1
% Thetag_N_avg_25   1 x 1
% Thetag_N_avg_26   1 x 1
% Thetag_N_avg_27   1 x 1
% Thetag_N_avg_28   1 x 1
% Thetag_N_avg_29   1 x 1
% Thetag_N_avg_30   1 x 1
% Thetag_N_avg_31   1 x 1
% Thetag_N_avg_32   1 x 1
% Thetag_N_avg_33   1 x 1
% Thetag_N_avg_34   1 x 1
% Thetag_N_avg_35   1 x 1
% Thetag_N_avg_36   1 x 1
% Thetag_N_avg_37   1 x 1
% Thetag_N_avg_38   1 x 1
% Thetag_N_avg_39   1 x 1
% Thetag_N_avg_40   1 x 1
% Thetag_N_avg_41   1 x 1
% Thetag_N_avg_42   1 x 1
% Thetag_N_avg_43   1 x 1
% Thetag_N_avg_44   1 x 1
% Thetag_N_avg_45   1 x 1
% Thetag_N_avg_46   1 x 1
% Thetag_N_avg_47   1 x 1
% Thetag_N_avg_48   1 x 1
% Thetag_N_avg_49   1 x 1
% Thetag_N_avg_50   1 x 1
% Thetag_N_avg_51   1 x 1
% Thetag_N_avg_52   1 x 1
% Thetag_N_avg_53   1 x 1
% Thetag_N_avg_54   1 x 1
% Thetag_N_avg_55   1 x 1
% Thetag_N_avg_56   1 x 1
% Thetag_N_avg_57   1 x 1
% Thetag_N_avg_58   1 x 1
% Thetag_N_avg_59   1 x 1
% Thetag_N_avg_60   1 x 1
% Thetag_N_avg_61   1 x 1
% Thetag_N_avg_62   1 x 1
% Thetag_N_avg_63   1 x 1
% Thetag_N_avg_64   1 x 1
% Thetag_N_avg_65   1 x 1
% Thetag_N_avg_66   1 x 1
% Thetag_N_avg_67   1 x 1
% Thetag_N_avg_68   1 x 1
% Thetag_N_avg_69   1 x 1
% Thetag_N_avg_70   1 x 1
% Thetag_N_avg_71   1 x 1
% Thetag_N_avg_72   1 x 1
% Thetag_N_avg_73   1 x 1
% Thetag_N_avg_74   1 x 1
% Thetag_N_avg_75   1 x 1
% Thetag_N_avg_76   1 x 1
% Thetag_N_avg_77   1 x 1
% Thetag_N_avg_78   1 x 1
% Thetag_N_avg_79   1 x 1
% Thetag_N_avg_80   1 x 1
% Thetag_N_avg_81   1 x 1
% Thetag_N_avg_82   1 x 1
% Thetag_N_avg_83   1 x 1
% Thetag_N_avg_84   1 x 1
% Thetag_N_avg_85   1 x 1
% Thetag_N_avg_86   1 x 1
% Thetag_N_avg_87   1 x 1
% Thetag_N_avg_88   1 x 1
% Thetag_N_avg_89   1 x 1
% Thetag_N_avg_90   1 x 1
% Thetag_N_avg_91   1 x 1
% Thetag_N_avg_92   1 x 1
% Thetag_N_avg_93   1 x 1
% Thetag_N_avg_94   1 x 1
% Thetag_N_avg_95   1 x 1
% Thetag_N_avg_96   1 x 1
% Thetag_N_avg_97   1 x 1
% Thetag_N_avg_98   1 x 1
% Thetag_N_avg_99   1 x 1
% Thetag_N_avg_100   1 x 1
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
% Vg_N_avg_11   1 x 1
% Vg_N_avg_12   1 x 1
% Vg_N_avg_13   1 x 1
% Vg_N_avg_14   1 x 1
% Vg_N_avg_15   1 x 1
% Vg_N_avg_16   1 x 1
% Vg_N_avg_17   1 x 1
% Vg_N_avg_18   1 x 1
% Vg_N_avg_19   1 x 1
% Vg_N_avg_20   1 x 1
% Vg_N_avg_21   1 x 1
% Vg_N_avg_22   1 x 1
% Vg_N_avg_23   1 x 1
% Vg_N_avg_24   1 x 1
% Vg_N_avg_25   1 x 1
% Vg_N_avg_26   1 x 1
% Vg_N_avg_27   1 x 1
% Vg_N_avg_28   1 x 1
% Vg_N_avg_29   1 x 1
% Vg_N_avg_30   1 x 1
% Vg_N_avg_31   1 x 1
% Vg_N_avg_32   1 x 1
% Vg_N_avg_33   1 x 1
% Vg_N_avg_34   1 x 1
% Vg_N_avg_35   1 x 1
% Vg_N_avg_36   1 x 1
% Vg_N_avg_37   1 x 1
% Vg_N_avg_38   1 x 1
% Vg_N_avg_39   1 x 1
% Vg_N_avg_40   1 x 1
% Vg_N_avg_41   1 x 1
% Vg_N_avg_42   1 x 1
% Vg_N_avg_43   1 x 1
% Vg_N_avg_44   1 x 1
% Vg_N_avg_45   1 x 1
% Vg_N_avg_46   1 x 1
% Vg_N_avg_47   1 x 1
% Vg_N_avg_48   1 x 1
% Vg_N_avg_49   1 x 1
% Vg_N_avg_50   1 x 1
% Vg_N_avg_51   1 x 1
% Vg_N_avg_52   1 x 1
% Vg_N_avg_53   1 x 1
% Vg_N_avg_54   1 x 1
% Vg_N_avg_55   1 x 1
% Vg_N_avg_56   1 x 1
% Vg_N_avg_57   1 x 1
% Vg_N_avg_58   1 x 1
% Vg_N_avg_59   1 x 1
% Vg_N_avg_60   1 x 1
% Vg_N_avg_61   1 x 1
% Vg_N_avg_62   1 x 1
% Vg_N_avg_63   1 x 1
% Vg_N_avg_64   1 x 1
% Vg_N_avg_65   1 x 1
% Vg_N_avg_66   1 x 1
% Vg_N_avg_67   1 x 1
% Vg_N_avg_68   1 x 1
% Vg_N_avg_69   1 x 1
% Vg_N_avg_70   1 x 1
% Vg_N_avg_71   1 x 1
% Vg_N_avg_72   1 x 1
% Vg_N_avg_73   1 x 1
% Vg_N_avg_74   1 x 1
% Vg_N_avg_75   1 x 1
% Vg_N_avg_76   1 x 1
% Vg_N_avg_77   1 x 1
% Vg_N_avg_78   1 x 1
% Vg_N_avg_79   1 x 1
% Vg_N_avg_80   1 x 1
% Vg_N_avg_81   1 x 1
% Vg_N_avg_82   1 x 1
% Vg_N_avg_83   1 x 1
% Vg_N_avg_84   1 x 1
% Vg_N_avg_85   1 x 1
% Vg_N_avg_86   1 x 1
% Vg_N_avg_87   1 x 1
% Vg_N_avg_88   1 x 1
% Vg_N_avg_89   1 x 1
% Vg_N_avg_90   1 x 1
% Vg_N_avg_91   1 x 1
% Vg_N_avg_92   1 x 1
% Vg_N_avg_93   1 x 1
% Vg_N_avg_94   1 x 1
% Vg_N_avg_95   1 x 1
% Vg_N_avg_96   1 x 1
% Vg_N_avg_97   1 x 1
% Vg_N_avg_98   1 x 1
% Vg_N_avg_99   1 x 1
% Vg_N_avg_100   1 x 1
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
%  ug_N_11   1 x 1
%  ug_N_12   1 x 1
%  ug_N_13   1 x 1
%  ug_N_14   1 x 1
%  ug_N_15   1 x 1
%  ug_N_16   1 x 1
%  ug_N_17   1 x 1
%  ug_N_18   1 x 1
%  ug_N_19   1 x 1
%  ug_N_20   1 x 1
%  ug_N_21   1 x 1
%  ug_N_22   1 x 1
%  ug_N_23   1 x 1
%  ug_N_24   1 x 1
%  ug_N_25   1 x 1
%  ug_N_26   1 x 1
%  ug_N_27   1 x 1
%  ug_N_28   1 x 1
%  ug_N_29   1 x 1
%  ug_N_30   1 x 1
%  ug_N_31   1 x 1
%  ug_N_32   1 x 1
%  ug_N_33   1 x 1
%  ug_N_34   1 x 1
%  ug_N_35   1 x 1
%  ug_N_36   1 x 1
%  ug_N_37   1 x 1
%  ug_N_38   1 x 1
%  ug_N_39   1 x 1
%  ug_N_40   1 x 1
%  ug_N_41   1 x 1
%  ug_N_42   1 x 1
%  ug_N_43   1 x 1
%  ug_N_44   1 x 1
%  ug_N_45   1 x 1
%  ug_N_46   1 x 1
%  ug_N_47   1 x 1
%  ug_N_48   1 x 1
%  ug_N_49   1 x 1
%  ug_N_50   1 x 1
%  ug_N_51   1 x 1
%  ug_N_52   1 x 1
%  ug_N_53   1 x 1
%  ug_N_54   1 x 1
%  ug_N_55   1 x 1
%  ug_N_56   1 x 1
%  ug_N_57   1 x 1
%  ug_N_58   1 x 1
%  ug_N_59   1 x 1
%  ug_N_60   1 x 1
%  ug_N_61   1 x 1
%  ug_N_62   1 x 1
%  ug_N_63   1 x 1
%  ug_N_64   1 x 1
%  ug_N_65   1 x 1
%  ug_N_66   1 x 1
%  ug_N_67   1 x 1
%  ug_N_68   1 x 1
%  ug_N_69   1 x 1
%  ug_N_70   1 x 1
%  ug_N_71   1 x 1
%  ug_N_72   1 x 1
%  ug_N_73   1 x 1
%  ug_N_74   1 x 1
%  ug_N_75   1 x 1
%  ug_N_76   1 x 1
%  ug_N_77   1 x 1
%  ug_N_78   1 x 1
%  ug_N_79   1 x 1
%  ug_N_80   1 x 1
%  ug_N_81   1 x 1
%  ug_N_82   1 x 1
%  ug_N_83   1 x 1
%  ug_N_84   1 x 1
%  ug_N_85   1 x 1
%  ug_N_86   1 x 1
%  ug_N_87   1 x 1
%  ug_N_88   1 x 1
%  ug_N_89   1 x 1
%  ug_N_90   1 x 1
%  ug_N_91   1 x 1
%  ug_N_92   1 x 1
%  ug_N_93   1 x 1
%  ug_N_94   1 x 1
%  ug_N_95   1 x 1
%  ug_N_96   1 x 1
%  ug_N_97   1 x 1
%  ug_N_98   1 x 1
%  ug_N_99   1 x 1
% ug_N_100   1 x 1
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
%  vg_N_11   1 x 1
%  vg_N_12   1 x 1
%  vg_N_13   1 x 1
%  vg_N_14   1 x 1
%  vg_N_15   1 x 1
%  vg_N_16   1 x 1
%  vg_N_17   1 x 1
%  vg_N_18   1 x 1
%  vg_N_19   1 x 1
%  vg_N_20   1 x 1
%  vg_N_21   1 x 1
%  vg_N_22   1 x 1
%  vg_N_23   1 x 1
%  vg_N_24   1 x 1
%  vg_N_25   1 x 1
%  vg_N_26   1 x 1
%  vg_N_27   1 x 1
%  vg_N_28   1 x 1
%  vg_N_29   1 x 1
%  vg_N_30   1 x 1
%  vg_N_31   1 x 1
%  vg_N_32   1 x 1
%  vg_N_33   1 x 1
%  vg_N_34   1 x 1
%  vg_N_35   1 x 1
%  vg_N_36   1 x 1
%  vg_N_37   1 x 1
%  vg_N_38   1 x 1
%  vg_N_39   1 x 1
%  vg_N_40   1 x 1
%  vg_N_41   1 x 1
%  vg_N_42   1 x 1
%  vg_N_43   1 x 1
%  vg_N_44   1 x 1
%  vg_N_45   1 x 1
%  vg_N_46   1 x 1
%  vg_N_47   1 x 1
%  vg_N_48   1 x 1
%  vg_N_49   1 x 1
%  vg_N_50   1 x 1
%  vg_N_51   1 x 1
%  vg_N_52   1 x 1
%  vg_N_53   1 x 1
%  vg_N_54   1 x 1
%  vg_N_55   1 x 1
%  vg_N_56   1 x 1
%  vg_N_57   1 x 1
%  vg_N_58   1 x 1
%  vg_N_59   1 x 1
%  vg_N_60   1 x 1
%  vg_N_61   1 x 1
%  vg_N_62   1 x 1
%  vg_N_63   1 x 1
%  vg_N_64   1 x 1
%  vg_N_65   1 x 1
%  vg_N_66   1 x 1
%  vg_N_67   1 x 1
%  vg_N_68   1 x 1
%  vg_N_69   1 x 1
%  vg_N_70   1 x 1
%  vg_N_71   1 x 1
%  vg_N_72   1 x 1
%  vg_N_73   1 x 1
%  vg_N_74   1 x 1
%  vg_N_75   1 x 1
%  vg_N_76   1 x 1
%  vg_N_77   1 x 1
%  vg_N_78   1 x 1
%  vg_N_79   1 x 1
%  vg_N_80   1 x 1
%  vg_N_81   1 x 1
%  vg_N_82   1 x 1
%  vg_N_83   1 x 1
%  vg_N_84   1 x 1
%  vg_N_85   1 x 1
%  vg_N_86   1 x 1
%  vg_N_87   1 x 1
%  vg_N_88   1 x 1
%  vg_N_89   1 x 1
%  vg_N_90   1 x 1
%  vg_N_91   1 x 1
%  vg_N_92   1 x 1
%  vg_N_93   1 x 1
%  vg_N_94   1 x 1
%  vg_N_95   1 x 1
%  vg_N_96   1 x 1
%  vg_N_97   1 x 1
%  vg_N_98   1 x 1
%  vg_N_99   1 x 1
% vg_N_100   1 x 1
%
% Note:
%   - Check status.converged, which will be 1 if optimization succeeded.
%   - You don't have to specify settings if you don't want to.
%   - To hide output, use settings.verbose = 0.
%   - To change iterations, use settings.max_iters = 20.
%   - You may wish to compare with cvxsolve to check the solver is correct.
%
% Specify params.PgMax, ..., params.vg_N_100, then run
%   [vars, status] = csolve(params, settings)
% Produced by CVXGEN, 2015-02-05 18:10:13 -0500.
% CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2012 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: csolve.m.
% Description: Help file for the Matlab solver interface.