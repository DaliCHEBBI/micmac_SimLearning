#include "include/MMVII_all.h"

// include model architecture 
#include "cCnnModelPredictor.h"

// Without Attention
std::vector<double> spaceCorr = {0.0 ,5.01321116e-03 ,1.00131324e-02 ,1.50130531e-02
 ,2.00129747e-02, 2.50128955e-02, 3.00128162e-02, 3.50127369e-02
 ,4.00126576e-02, 4.50125784e-02, 5.00124991e-02, 5.50124198e-02
 ,6.00123443e-02, 6.50122613e-02, 7.00121820e-02, 7.50121027e-02
 ,8.00120234e-02, 8.50119442e-02, 9.00118724e-02, 9.50117931e-02
 ,1.00011714e-01, 1.05011635e-01, 1.10011555e-01, 1.15011476e-01
 ,1.20011397e-01, 1.25011310e-01, 1.30011231e-01, 1.35011151e-01
 ,1.40011072e-01, 1.45010993e-01, 1.50010929e-01, 1.55010849e-01
 ,1.60010770e-01, 1.65010691e-01, 1.70010611e-01, 1.75010532e-01
 ,1.80010453e-01, 1.85010374e-01, 1.90010294e-01, 1.95010215e-01
 ,2.00010136e-01, 2.05010056e-01, 2.10009977e-01, 2.15009898e-01
 ,2.20009819e-01, 2.25009739e-01, 2.30009660e-01, 2.35009581e-01
 ,2.40009502e-01, 2.45009422e-01, 2.50009328e-01, 2.55009264e-01
 ,2.60009170e-01, 2.65009105e-01, 2.70009011e-01, 2.75008947e-01
 ,2.80008882e-01, 2.85008788e-01, 2.90008724e-01, 2.95008630e-01
 ,3.00008565e-01, 3.05008471e-01, 3.10008407e-01, 3.15008312e-01
 ,3.20008248e-01, 3.25008154e-01, 3.30008090e-01, 3.35007995e-01
 ,3.40007931e-01, 3.45007837e-01, 3.50007772e-01, 3.55007678e-01
 ,3.60007614e-01, 3.65007520e-01, 3.70007455e-01, 3.75007361e-01
 ,3.80007297e-01, 3.85007203e-01, 3.90007138e-01, 3.95007044e-01
 ,4.00006980e-01, 4.05006886e-01, 4.10006821e-01, 4.15006727e-01
 ,4.20006663e-01, 4.25006568e-01, 4.30006504e-01, 4.35006410e-01
 ,4.40006346e-01, 4.45006251e-01, 4.50006187e-01, 4.55006093e-01
 ,4.60006028e-01, 4.65005934e-01, 4.70005870e-01, 4.75005776e-01
 ,4.80005711e-01, 4.85005617e-01, 4.90005553e-01, 4.95005459e-01
 ,5.00005364e-01, 5.05005300e-01, 5.10005236e-01, 5.15005171e-01
 ,5.20005107e-01, 5.25004983e-01, 5.30004919e-01, 5.35004854e-01
 ,5.40004790e-01, 5.45004666e-01, 5.50004601e-01, 5.55004537e-01
 ,5.60004473e-01, 5.65004349e-01, 5.70004284e-01, 5.75004220e-01
 ,5.80004156e-01, 5.85004032e-01, 5.90003967e-01, 5.95003903e-01
 ,6.00003839e-01, 6.05003715e-01, 6.10003650e-01, 6.15003586e-01
 ,6.20003521e-01, 6.25003397e-01, 6.30003333e-01, 6.35003269e-01
 ,6.40003204e-01, 6.45003080e-01, 6.50003016e-01, 6.55002952e-01
 ,6.60002887e-01, 6.65002763e-01, 6.70002699e-01, 6.75002635e-01
 ,6.80002570e-01, 6.85002446e-01, 6.90002382e-01, 6.95002317e-01
 ,7.00002253e-01, 7.05002129e-01, 7.10002065e-01, 7.15002000e-01
 ,7.20001936e-01, 7.25001812e-01, 7.30001748e-01, 7.35001683e-01
 ,7.40001619e-01, 7.45001495e-01, 7.50001431e-01, 7.55001366e-01
 ,7.60001302e-01, 7.65001237e-01, 7.70001113e-01, 7.75001049e-01
 ,7.80000985e-01, 7.85000920e-01, 7.90000796e-01, 7.95000732e-01
 ,8.00000668e-01, 8.05000603e-01, 8.10000479e-01, 8.15000415e-01
 ,8.20000350e-01, 8.25000286e-01, 8.30000162e-01, 8.35000098e-01
 ,8.40000033e-01, 8.44999969e-01, 8.49999845e-01, 8.54999781e-01
 ,8.59999716e-01, 8.64999652e-01, 8.69999528e-01, 8.74999464e-01
 ,8.79999399e-01, 8.84999335e-01, 8.89999211e-01, 8.94999146e-01
 ,8.99999082e-01, 9.04999018e-01, 9.09998894e-01, 9.14998829e-01
 ,9.19998765e-01, 9.24998701e-01, 9.29998577e-01, 9.34998512e-01
 ,9.39998448e-01, 9.44998384e-01, 9.49998260e-01, 9.54998195e-01
 ,9.59998131e-01, 9.64998066e-01, 9.69997942e-01, 9.74997878e-01
 ,9.79997814e-01, 9.84997749e-01, 9.89997625e-01, 1.0};

std::vector<double> spaceProb = {0.0,0.0,  0.00195898, 0.00357165, 0.00500644, 0.00632557, 0.00757813
 ,0.00879118, 0.00997973 ,0.01115117 ,0.01230161 ,0.01342482 ,0.01452877
 ,0.0156378 , 0.01675254 ,0.01785096 ,0.01894217 ,0.02003805 ,0.02112368
 ,0.0222167 , 0.02333164 ,0.02445237 ,0.02556642 ,0.02668225 ,0.02780843
 ,0.02893386, 0.03007511 ,0.03122621 ,0.03236788 ,0.03353747 ,0.0347253
 ,0.03591878, 0.03712798 ,0.03834578 ,0.03958075 ,0.04082456 ,0.04206875
 ,0.04333074, 0.04461367 ,0.0459212  ,0.04725447 ,0.04859619 ,0.04994938
 ,0.05132945, 0.05274087 ,0.05416503 ,0.05560787 ,0.05707806 ,0.05855657
 ,0.06005333, 0.061579   ,0.06312901 ,0.06471673 ,0.06634192 ,0.06800086
 ,0.06969038, 0.07141285 ,0.07318433 ,0.07497784 ,0.07679436 ,0.07866776
 ,0.08060382, 0.08259203 ,0.08461203 ,0.08667635 ,0.08878635 ,0.09095531
 ,0.0932076 , 0.09552373 ,0.09789391 ,0.10031998 ,0.10282052 ,0.10541038
 ,0.10807577, 0.11086499 ,0.1137604  ,0.11674222 ,0.11983796 ,0.12307273
 ,0.1264293 , 0.12989361 ,0.13349112 ,0.13726083 ,0.14117398 ,0.14521353
 ,0.14940494, 0.15375911 ,0.15827291 ,0.16290825 ,0.16768941 ,0.17264312
 ,0.17771155, 0.18291504 ,0.18821775 ,0.19360144 ,0.19902581 ,0.20449289
 ,0.21128797, 0.2182034  ,0.22391162 ,0.22943283 ,0.23475296 ,0.23990154
 ,0.24490849, 0.24977815 ,0.25452919 ,0.25914809 ,0.26359309 ,0.26794047
 ,0.27216553, 0.27627924 ,0.28027826 ,0.28417864 ,0.2880058  ,0.29174497
 ,0.29538617, 0.29893073 ,0.30240822 ,0.30582336 ,0.30917198 ,0.31245205
 ,0.31565569, 0.31885875 ,0.32200886 ,0.3251049  ,0.32817631 ,0.33121182
 ,0.33420893, 0.33718241 ,0.34014412 ,0.34308985 ,0.34600925 ,0.348933
 ,0.35184324, 0.35472998 ,0.35758348 ,0.36045033 ,0.3633205  ,0.36619498
 ,0.36905595, 0.37190915 ,0.37478305 ,0.37768372 ,0.38060239 ,0.38351149
 ,0.38641736, 0.38936165 ,0.3923065  ,0.39528112 ,0.39826586 ,0.40129391
 ,0.40433463, 0.40741637 ,0.41055872 ,0.41371462 ,0.41691095 ,0.42013752
 ,0.4234201 , 0.4267431  ,0.43014208 ,0.43358588 ,0.43708435 ,0.44066213
 ,0.44432003, 0.4480487  ,0.45183663 ,0.4557246  ,0.45971897 ,0.46380786
 ,0.46801893, 0.47231142 ,0.47677562 ,0.48137264 ,0.48610318 ,0.49099675
 ,0.49605909, 0.50132195 ,0.50680723 ,0.51252826 ,0.51848957 ,0.52469391
 ,0.53121003, 0.53808913 ,0.54537401 ,0.55308251 ,0.56131861 ,0.57008489
 ,0.57950252, 0.58968345 ,0.6007666  ,0.6129281  ,0.62638153 ,0.64149181
 ,0.65872244, 0.67878127 ,0.7027543  ,0.73249943 ,0.77204769 ,0.8320679
 ,1.};


 // With ATTENTION
/*
std::vector<double> spaceCorr = {0.0, 5.00340527e-03, 1.00033870e-02, 1.50033692e-02
 ,2.00033505e-02, 2.50033326e-02, 3.00033130e-02, 3.50032970e-02
 ,4.00032774e-02, 4.50032577e-02, 5.00032417e-02, 5.50032221e-02
 ,6.00032024e-02, 6.50031865e-02, 7.00031668e-02, 7.50031471e-02
 ,8.00031275e-02, 8.50031152e-02, 9.00030956e-02, 9.50030759e-02
 ,1.00003056e-01, 1.05003037e-01, 1.10003024e-01, 1.15003005e-01
 ,1.20002985e-01, 1.25002965e-01, 1.30002946e-01, 1.35002926e-01
 ,1.40002906e-01, 1.45002887e-01, 1.50002867e-01, 1.55002862e-01
 ,1.60002843e-01, 1.65002823e-01, 1.70002803e-01, 1.75002784e-01
 ,1.80002764e-01, 1.85002744e-01, 1.90002725e-01, 1.95002705e-01
 ,2.00002685e-01, 2.05002680e-01, 2.10002661e-01, 2.15002641e-01
 ,2.20002621e-01, 2.25002602e-01, 2.30002582e-01, 2.35002562e-01
 ,2.40002543e-01, 2.45002523e-01, 2.50002503e-01, 2.55002499e-01
 ,2.60002464e-01, 2.65002459e-01, 2.70002425e-01, 2.75002420e-01
 ,2.80002385e-01, 2.85002381e-01, 2.90002376e-01, 2.95002341e-01
 ,3.00002337e-01, 3.05002302e-01, 3.10002297e-01, 3.15002263e-01
 ,3.20002258e-01, 3.25002223e-01, 3.30002218e-01, 3.35002184e-01
 ,3.40002179e-01, 3.45002174e-01, 3.50002140e-01, 3.55002135e-01
 ,3.60002100e-01, 3.65002096e-01, 3.70002061e-01, 3.75002056e-01
 ,3.80002022e-01, 3.85002017e-01, 3.90001982e-01, 3.95001978e-01
 ,4.00001973e-01, 4.05001938e-01, 4.10001934e-01, 4.15001899e-01
 ,4.20001894e-01, 4.25001860e-01, 4.30001855e-01, 4.35001820e-01
 ,4.40001816e-01, 4.45001781e-01, 4.50001776e-01, 4.55001771e-01
 ,4.60001737e-01, 4.65001732e-01, 4.70001698e-01, 4.75001693e-01
 ,4.80001658e-01, 4.85001653e-01, 4.90001619e-01, 4.95001614e-01
 ,5.00001609e-01, 5.05001545e-01, 5.10001540e-01, 5.15001535e-01
 ,5.20001531e-01, 5.25001526e-01, 5.30001462e-01, 5.35001457e-01
 ,5.40001452e-01, 5.45001447e-01, 5.50001383e-01, 5.55001378e-01
 ,5.60001373e-01, 5.65001369e-01, 5.70001364e-01, 5.75001299e-01
 ,5.80001295e-01, 5.85001290e-01, 5.90001285e-01, 5.95001221e-01
 ,6.00001216e-01, 6.05001211e-01, 6.10001206e-01, 6.15001142e-01
 ,6.20001137e-01, 6.25001132e-01, 6.30001128e-01, 6.35001123e-01
 ,6.40001059e-01, 6.45001054e-01, 6.50001049e-01, 6.55001044e-01
 ,6.60000980e-01, 6.65000975e-01, 6.70000970e-01, 6.75000966e-01
 ,6.80000961e-01, 6.85000896e-01, 6.90000892e-01, 6.95000887e-01
 ,7.00000882e-01, 7.05000818e-01, 7.10000813e-01, 7.15000808e-01
 ,7.20000803e-01, 7.25000739e-01, 7.30000734e-01, 7.35000730e-01
 ,7.40000725e-01, 7.45000720e-01, 7.50000656e-01, 7.55000651e-01
 ,7.60000646e-01, 7.65000641e-01, 7.70000577e-01, 7.75000572e-01
 ,7.80000567e-01, 7.85000563e-01, 7.90000558e-01, 7.95000494e-01
 ,8.00000489e-01, 8.05000484e-01, 8.10000479e-01, 8.15000415e-01
 ,8.20000410e-01, 8.25000405e-01, 8.30000401e-01, 8.35000336e-01
 ,8.40000331e-01, 8.45000327e-01, 8.50000322e-01, 8.55000317e-01
 ,8.60000253e-01, 8.65000248e-01, 8.70000243e-01, 8.75000238e-01
 ,8.80000174e-01, 8.85000169e-01, 8.90000165e-01, 8.95000160e-01
 ,9.00000155e-01, 9.05000091e-01, 9.10000086e-01, 9.15000081e-01
 ,9.20000076e-01, 9.25000012e-01, 9.30000007e-01, 9.35000002e-01
 ,9.39999998e-01, 9.44999933e-01, 9.49999928e-01, 9.54999924e-01
 ,9.59999919e-01, 9.64999914e-01, 9.69999850e-01, 9.74999845e-01
 ,9.79999840e-01, 9.84999835e-01, 9.89999771e-01, 1.0};

std::vector<double> spaceProb ={0.0,0.0,  0.0023275, 0.00413935, 0.00567632, 0.00707687, 0.00837724
 ,0.00959742, 0.01075961, 0.01188539, 0.01298508, 0.01406045, 0.01512478
 ,0.01617204, 0.01720136, 0.01822613, 0.01924003, 0.02023535, 0.02122792
 ,0.02223662, 0.02325179, 0.0242555 , 0.02525951, 0.02625524, 0.02725385
 ,0.02826448, 0.02927567, 0.03028474, 0.03130191, 0.0323413 , 0.03337659
 ,0.03441324, 0.03547175, 0.0365403 , 0.03761203, 0.03867733, 0.03975112
 ,0.04085598, 0.04197432, 0.04310311, 0.04424088, 0.04537661, 0.04653133
 ,0.04770968, 0.04892037, 0.0501447 , 0.05137529, 0.05262343, 0.05388302
 ,0.05516737, 0.0564766 , 0.05780604, 0.05915369, 0.06053872, 0.06195259
 ,0.06339009, 0.06484771, 0.06633813, 0.06787255, 0.06943299, 0.0710172
 ,0.07262644, 0.07428397, 0.0760071 , 0.07776741, 0.07955411, 0.08137665
 ,0.08324873, 0.0851748 , 0.08715197, 0.08918697, 0.09127854, 0.09345182
 ,0.09571027, 0.09803384, 0.10043483, 0.10292652, 0.10550697, 0.10817934
 ,0.1109515 , 0.11381878, 0.11679181, 0.11988664, 0.12310635, 0.12644772
 ,0.12990293, 0.1335058 , 0.1372584 , 0.14116238, 0.14523239, 0.14945836
 ,0.15385254, 0.15839232, 0.16308341, 0.16791936, 0.17289035, 0.17800292
 ,0.18324386, 0.19004635, 0.19722501, 0.2030889 , 0.20859386, 0.21391617
 ,0.21908868, 0.22412305, 0.22904112, 0.23385839, 0.23856151, 0.24314941
 ,0.24763851, 0.25201129, 0.25627612, 0.26043778, 0.26450251, 0.26846729
 ,0.27236604, 0.27618322, 0.27992247, 0.2836081 , 0.2872127 , 0.29075075
 ,0.29422377, 0.29763869, 0.30099527, 0.30430599, 0.30756343, 0.31079199
 ,0.31398683, 0.31713475, 0.32025039, 0.32332875, 0.32636088, 0.32936938
 ,0.33238255, 0.33537545, 0.33834067, 0.34129113, 0.34422244, 0.3471377
 ,0.35003779, 0.35292254, 0.35581124, 0.35869707, 0.36157943, 0.36447602
 ,0.36735757, 0.37024276, 0.37313592, 0.37605948, 0.37901559, 0.38198234
 ,0.38496333, 0.38796779, 0.39100898, 0.39405672, 0.39714292, 0.40026094
 ,0.40342625, 0.40662912, 0.40988186, 0.41320004, 0.41658308, 0.42005953
 ,0.42357724, 0.42717705, 0.43084872, 0.43460328, 0.43845765, 0.44244333
 ,0.4465394 , 0.45073076, 0.45502564, 0.45946272, 0.46406995, 0.4688119
 ,0.47373219, 0.47884337, 0.48419155, 0.48974662, 0.49554732, 0.50161187
 ,0.50801137, 0.51478962, 0.52192225, 0.52950534, 0.53756967, 0.54624003
 ,0.5555338 , 0.56557039, 0.57654628, 0.58865304, 0.60206409, 0.61712885
 ,0.63433656, 0.65438753, 0.67842073, 0.7083464 , 0.74820577, 0.80889095
 ,1.0 };
 */

// With ATTENTION MULTI SCALE FEATURES 
std::vector<double> spaceCorrAttMS = {0.0 ,5.0019301e-03 ,1.0001909e-02 ,1.5001888e-02 ,2.0001866e-02
 ,2.5001846e-02, 3.0001825e-02, 3.5001803e-02, 4.0001784e-02, 4.5001760e-02
 ,5.0001740e-02, 5.5001721e-02, 6.0001697e-02, 6.5001674e-02, 7.0001654e-02
 ,7.5001635e-02, 8.0001615e-02, 8.5001595e-02, 9.0001568e-02, 9.5001549e-02
 ,1.0000153e-01, 1.0500151e-01, 1.1000149e-01, 1.1500147e-01, 1.2000144e-01
 ,1.2500143e-01, 1.3000140e-01, 1.3500138e-01, 1.4000136e-01, 1.4500134e-01
 ,1.5000132e-01, 1.5500130e-01, 1.6000128e-01, 1.6500126e-01, 1.7000124e-01
 ,1.7500122e-01, 1.8000120e-01, 1.8500116e-01, 1.9000115e-01, 1.9500113e-01
 ,2.0000111e-01, 2.0500109e-01, 2.1000107e-01, 2.1500105e-01, 2.2000103e-01
 ,2.2500101e-01, 2.3000099e-01, 2.3500095e-01, 2.4000093e-01, 2.4500091e-01
 ,2.5000089e-01, 2.5500089e-01, 2.6000085e-01, 2.6500082e-01, 2.7000082e-01
 ,2.7500078e-01, 2.8000078e-01, 2.8500074e-01, 2.9000074e-01, 2.9500070e-01
 ,3.0000070e-01, 3.0500066e-01, 3.1000066e-01, 3.1500062e-01, 3.2000059e-01
 ,3.2500058e-01, 3.3000055e-01, 3.3500054e-01, 3.4000051e-01, 3.4500051e-01
 ,3.5000047e-01, 3.5500047e-01, 3.6000043e-01, 3.6500043e-01, 3.7000039e-01
 ,3.7500036e-01, 3.8000035e-01, 3.8500032e-01, 3.9000031e-01, 3.9500028e-01
 ,4.0000027e-01, 4.0500024e-01, 4.1000023e-01, 4.1500020e-01, 4.2000017e-01
 ,4.2500016e-01, 4.3000013e-01, 4.3500012e-01, 4.4000009e-01, 4.4500008e-01
 ,4.5000005e-01, 4.5500004e-01, 4.6000001e-01, 4.6500000e-01, 4.6999997e-01
 ,4.7499993e-01, 4.7999993e-01, 4.8499990e-01, 4.8999989e-01, 4.9499986e-01
 ,4.9999985e-01, 5.0499982e-01, 5.0999981e-01, 5.1499981e-01, 5.1999974e-01
 ,5.2499974e-01, 5.2999973e-01, 5.3499967e-01, 5.3999966e-01, 5.4499966e-01
 ,5.4999965e-01, 5.5499959e-01, 5.5999959e-01, 5.6499958e-01, 5.6999958e-01
 ,5.7499951e-01, 5.7999951e-01, 5.8499950e-01, 5.8999944e-01, 5.9499943e-01
 ,5.9999943e-01, 6.0499942e-01, 6.0999936e-01, 6.1499935e-01, 6.1999935e-01
 ,6.2499934e-01, 6.2999928e-01, 6.3499928e-01, 6.3999927e-01, 6.4499921e-01
 ,6.4999920e-01, 6.5499920e-01, 6.5999919e-01, 6.6499913e-01, 6.6999912e-01
 ,6.7499912e-01, 6.7999911e-01, 6.8499905e-01, 6.8999904e-01, 6.9499904e-01
 ,6.9999897e-01, 7.0499897e-01, 7.0999897e-01, 7.1499896e-01, 7.1999890e-01
 ,7.2499889e-01, 7.2999889e-01, 7.3499888e-01, 7.3999882e-01, 7.4499881e-01
 ,7.4999881e-01, 7.5499874e-01, 7.5999874e-01, 7.6499873e-01, 7.6999873e-01
 ,7.7499866e-01, 7.7999866e-01, 7.8499866e-01, 7.8999859e-01, 7.9499859e-01
 ,7.9999858e-01, 8.0499858e-01, 8.0999851e-01, 8.1499851e-01, 8.1999850e-01
 ,8.2499850e-01, 8.2999843e-01, 8.3499843e-01, 8.3999842e-01, 8.4499836e-01
 ,8.4999835e-01, 8.5499835e-01, 8.5999835e-01, 8.6499828e-01, 8.6999828e-01
 ,8.7499827e-01, 8.7999827e-01, 8.8499820e-01, 8.8999820e-01, 8.9499819e-01
 ,8.9999813e-01, 9.0499812e-01, 9.0999812e-01, 9.1499811e-01, 9.1999805e-01
 ,9.2499804e-01, 9.2999804e-01, 9.3499804e-01, 9.3999797e-01, 9.4499797e-01
 ,9.4999796e-01, 9.5499790e-01, 9.5999789e-01, 9.6499789e-01, 9.6999788e-01
 ,9.7499782e-01, 9.7999781e-01, 9.8499781e-01, 9.8999780e-01, 1.0};

std::vector<double> spaceProbAttMS ={0.0,0.0,0.00214986, 0.00382798, 0.00532545, 0.00671304, 0.00800585,
 0.00924477, 0.01045326 ,0.01162766 ,0.01277646 ,0.0138971  ,0.01499359,
 0.01608113, 0.01716253 ,0.01824312 ,0.01933726 ,0.02043475 ,0.02151054,
 0.02259537, 0.02369295 ,0.02477946 ,0.02586904 ,0.02697107 ,0.02808974,
 0.02921161, 0.03032578 ,0.03144761 ,0.03257444 ,0.03371111 ,0.03486551,
 0.03603454, 0.03722386 ,0.03842307 ,0.03962014 ,0.04082826 ,0.04206391,
 0.04331764, 0.04457811 ,0.04584424 ,0.04712626 ,0.0484255  ,0.04974509,
 0.05108302, 0.05244481 ,0.05380457 ,0.05516813 ,0.05657726 ,0.05799613,
 0.05944114, 0.06091691 ,0.06240041 ,0.06390678 ,0.06544568 ,0.06701973,
 0.0686173 , 0.07022406 ,0.07184613 ,0.07349416 ,0.0751733  ,0.07690396,
 0.07866531, 0.08044476 ,0.08224323 ,0.08408934 ,0.08599389 ,0.08794699,
 0.08994524, 0.09198331 ,0.09406416 ,0.09619658 ,0.09838728 ,0.10062104,
 0.10291839, 0.10528834 ,0.10773185 ,0.11023234 ,0.11279544 ,0.11545326,
 0.11820759, 0.12105082 ,0.12397774 ,0.12702016 ,0.13017969 ,0.13344889,
 0.13683827, 0.14035615 ,0.14401336 ,0.14780237 ,0.15173141 ,0.15580815,
 0.16004158, 0.16440984 ,0.16894441 ,0.1736093  ,0.17834517 ,0.1831817 ,
 0.18809685, 0.19406086 ,0.20023602 ,0.20538795 ,0.2102688  ,0.21504691,
 0.21973592, 0.22432817 ,0.22881988 ,0.23321632 ,0.23754095 ,0.24178409,
 0.24593461, 0.24998011 ,0.25393324 ,0.25781708 ,0.26160831 ,0.26532435,
 0.26896465, 0.27256642 ,0.2761025  ,0.27956796 ,0.28297056 ,0.2863008 ,
 0.2895711 , 0.29280528 ,0.29599796 ,0.29913025 ,0.30224104 ,0.30532242,
 0.30837524, 0.31137856 ,0.3143413  ,0.31728873 ,0.32020769 ,0.3230928 ,
 0.32596772, 0.32884227 ,0.33171072 ,0.33454568 ,0.33736578 ,0.34020304,
 0.34302006, 0.34583479 ,0.34865663 ,0.35147412 ,0.35430255 ,0.3571241 ,
 0.35996187, 0.36282269 ,0.36570238 ,0.36861318 ,0.37153809 ,0.37447187,
 0.37743619, 0.38043238 ,0.38345412 ,0.38650393 ,0.38961951 ,0.39277735,
 0.3959589 , 0.39920599 ,0.40253769 ,0.40591117 ,0.40934353 ,0.41282615,
 0.41640201, 0.42005599 ,0.42379348 ,0.42762522 ,0.43155791 ,0.43559011,
 0.43971647, 0.4439752  ,0.44835832 ,0.45290891 ,0.45762176 ,0.46251719,
 0.46755919, 0.47278039 ,0.47821801 ,0.48389916 ,0.48983449 ,0.49604524,
 0.50262824, 0.50954698 ,0.51684883 ,0.52458706 ,0.53286111 ,0.54169161,
 0.55119783, 0.5614883  ,0.57274916 ,0.58513156 ,0.59886031 ,0.61433334,
 0.63198369, 0.65254843 ,0.67719517 ,0.70799207 ,0.74893783 ,0.81133126,
 1. };
 
void InterpolatePos(std::vector<double> aX,std::vector<double> aF, double& value)
{
    // Value to Index 
    auto i = std::lower_bound(aX.begin(), aX.end(), value); // sorted in increasing order from 0 to 1
    int k = i - aX.begin();
    //std::cout<<"KKK "<<k<<std::endl;
    int l = k ? k - 1 : 1 ;
    if(aF[k]<aF[l]) 
    {
        value = aF[k]+(value-aX[k])*(aF[l]-aF[k])/(aX[l]-aX[k]);
        //std::cout<<"values "<<value<<std::endl;
    }
    else 
    {
       value = aF[l]+(value-aX[l])*(aF[k]-aF[l])/(aX[k]-aX[l]);
        //std::cout<<"value before  "<<aF[l]<<"  values "<<value<<"  value after "<<aF[k]<<std::endl;
    }
}
 
/*
namespace {
	void display_weights(torch::nn::Module & module)
	{
		torch::NoGradGuard no_grad;
        
        
        std::cout<<"MODULE NAME "<<module.name()<<std::endl;
        std::cout<<"MODULE PARAMETERS SIZE "<<module.parameters().size()<<std::endl;

        if (auto conv = module.as<torch::nn::Conv2d>()) {
            std::cout<<"WGHT MATRIX MIN "<<conv->weight.min()<<std::endl;
            std::cout<<"WGHT MATRIX MAX "<<conv->weight.max()<<std::endl;
            //std::cout<<"BIAS VETCOR "<<conv->bias.sizes()<<std::endl;
			}
        if (auto linear = module.as<torch::nn::Linear>()) {
            std::cout<<"WGHT MATRIX "<<linear->weight<<std::endl;
            std::cout<<"BIAS VETCOR "<<linear->bias.sizes()<<std::endl;
			}
	}
}
*/
namespace MMVII
{
namespace  cNS_MatchMultipleOrtho
{

class cAppliMatchMultipleOrtho;

class cAppliMatchMultipleOrtho : public cMMVII_Appli
{
     public :
        typedef tU_INT1               tElemMasq;
        typedef tREAL4                tElemOrtho;
        typedef tREAL4                tElemSimil;
        typedef cIm2D<tElemMasq>      tImMasq;
        typedef cIm2D<tElemOrtho>     tImOrtho;
        typedef cIm2D<tElemSimil>     tImSimil;
        typedef cDataIm2D<tElemMasq>  tDImMasq;
        typedef cDataIm2D<tElemOrtho> tDImOrtho;
        typedef cDataIm2D<tElemSimil> tDImSimil;
        typedef std::vector<tImOrtho>  tVecOrtho;
        typedef std::vector<tImMasq>   tVecMasq;


        cAppliMatchMultipleOrtho(const std::vector<std::string> & aVArgs,const cSpecMMVII_Appli & aSpec);
    const std::string  & NameArch() const {return mArchitecture;} // ACCESSOR
    const std::string  & NameDirModel() const {return mModelBinDir;} // ACCESSOR
     private :
	std::string NameIm(int aKIm,int aKScale,const std::string & aPost) const
	{
             return mPrefixZ + "_I" +ToStr(aKIm) + "_S" + ToStr(aKScale) + "_"+ aPost  + ".tif";
	}
	std::string NameOrtho(int aKIm,int aKScale) const {return NameIm(aKIm,aKScale,"O");}
	std::string NameMasq(int aKIm,int aKScale) const {return NameIm(aKIm,aKScale,"M");}

        int Exe() override;
        cCollecSpecArg2007 & ArgObl(cCollecSpecArg2007 & anArgObl) override ;
        cCollecSpecArg2007 & ArgOpt(cCollecSpecArg2007 & anArgOpt) override ;

	//  One option, to replace by whatever you want
	void ComputeSimilByCorrelMaster();
    void ComputeSimilByLearnedCorrelMaster(std::vector<torch::Tensor> * AllEmbeddings);
    void ComputeSimilByLearnedCorrelMasterEnhanced(std::vector<torch::Tensor> * AllOrthosEmbeddings);
    void ComputeSimilByLearnedCorrelMasterDecision();
    void ComputeSimilByLearnedCorrelMasterMaxMoy(std::vector<torch::Tensor> * AllOrthosEmbeddings);
    void ComputeSimilByLearnedCorrelMasterMaxMoyMulScale(std::vector<torch::Tensor> * AllOrthosEmbeddings);
    void ComputeSimilByLearnedCorrelMasterDempsterShafer(std::vector<torch::Tensor> * AllOrthosEmbeddings);
    tREAL4 ComputeConflictBetween2SEts(tREAL4 aCorrel1, tREAL4 aCorrel2, tREAL4 aPonder1,tREAL4 aPonder2);
    tREAL4 ComputeJointMassBetween2Sets(tREAL4 aCorrel1, tREAL4 aCorrel2, tREAL4 aPonder1,tREAL4 aPonder2);
	void CorrelMaster(const cPt2di &,int aKIm,bool & AllOk,float &aWeight,float & aCorrel);
    void MakeNormalizedIms();
    void InitializePredictor ();
	// -------------- Mandatory args -------------------
	std::string   mPrefixGlob;   // Prefix to all names
	int           mNbZ;      // Number of independant ortho (=number of Z)
	int           mNbIm;     // Number of images
	int           mNbScale;  // Number of scale in image
	cPt2di        mSzW;      // Sizeof of windows
	bool          mIm1Mast;  //  Is first image the master image ?
	
	// -------------- Internal variables -------------------
	tImSimil                   mImSimil;   // computed image of similarity
	std::string                mPrefixZ;   // Prefix for a gizen Z
	cPt2di                     mSzIms;     // common  size of all ortho
	
	// ADDED LEARNING ENV
    aCnnModelPredictor *  mCNNPredictor=nullptr;
    bool                  mWithIntCorr=true;  // initialized in the begining 
    bool                  mWithExtCorr=false;  // initialized in the begining 
    bool                  mWithDecisionNet=true;
    std::string           mArchitecture;
    std::string           mResol;
    std::string           mModelBinDir;
    cPt2di                mCNNWin;
    
    // Networks architectures 
    ConvNet_Fast mNetFastStd= ConvNet_Fast(3,4);  // Conv Kernel= 3x3 , Convlayers=4
    ConvNet_FastBn  mNetFastMVCNN=ConvNet_FastBn(3,7);// Conv Kernel= 3x3 , Convlayers=7
    ConvNet_FastBnRegister mNetFastMVCNNReg=ConvNet_FastBnRegister(3,5,1,112,torch::kCPU);// changed from 64 to 112
    Fast_ProjectionHead mNetFastPrjHead=Fast_ProjectionHead(3,5,1,1,112,112,64,torch::kCPU);
    //MSNet_Attention mMSNet=MSNet_Attention(32);
    //MSNetHead mMSNet=MSNetHead(32);
    torch::jit::script::Module mMSNet /* MSNet_AttentionCustom mMSNet=MSNet_AttentionCustom(32)*/;
    FastandHead mNetFastMVCNNMLP=FastandHead(3,5,4,1,184,184,9,64,torch::kCPU);
    SimilarityNet mNetFastMVCNNDirectSIM=SimilarityNet(3,5,4,1,184,184,64,torch::kCPU);
    //FastandHead mNetFastMVCNNMLP; // Fast MVCNN + MLP for Multiview Features Aggregation
    // LATER SLOW NET 
    ConvNet_Slow mNetSlowStd=ConvNet_Slow(3,4,4); // Conv Kernel= 3x3 , Convlayers=4, Fully Connected Layers =4

	std::vector<tVecOrtho>      mVOrtho;    // vector of loaded ortho at a given Z
	std::vector<tVecMasq>       mVMasq;     // vector of loaded masq  at a given Z
};

// ARCHITECTURES OF CNN TRAINED 
static const std::string TheFastArch = "MVCNNFast";
static const std::string TheFastArchReg = "MVCNNFastReg";
static const std::string TheFastandPrjHead = "MVCNNFastProjHead";
static const std::string TheFastStandard = "MCNNStd";
static const std::string TheFastArchWithMLP= "MVCNNFastMLP";
static const std::string TheFastArchDirectSim="MVCNNFastDirectSIM";
//static const std::string TheMSNet="MSNetHead";
static const std::string TheMSNet="MSNet_Attention";
/* *************************************************** */
/*                                                     */
/*              cAppliMatchMultipleOrtho               */
/*                                                     */
/* *************************************************** */

cAppliMatchMultipleOrtho::cAppliMatchMultipleOrtho(const std::vector<std::string> & aVArgs,const cSpecMMVII_Appli & aSpec) :
   cMMVII_Appli  (aVArgs,aSpec),
   mImSimil      (cPt2di(1,1)),
   mCNNWin          (0,0)
   
{

}


cCollecSpecArg2007 & cAppliMatchMultipleOrtho::ArgObl(cCollecSpecArg2007 & anArgObl) 
{
 return
      anArgObl
          <<   Arg2007(mPrefixGlob,"Prefix of all names")
          <<   Arg2007(mNbZ,"Number of Z/Layers")
          <<   Arg2007(mNbIm,"Number of images in one layer")
          <<   Arg2007(mNbScale,"Number of scaled in on images")
          <<   Arg2007(mSzW,"Size of window")
          <<   Arg2007(mIm1Mast,"Is first image a master image ?")
   ;
}

cCollecSpecArg2007 & cAppliMatchMultipleOrtho::ArgOpt(cCollecSpecArg2007 & anArgOpt)
{
   return anArgOpt
          // << AOpt2007(mStepZ, "StepZ","Step for paralax",{eTA2007::HDV})
          << AOpt2007(mModelBinDir,"CNNParams" ,"Model Directory : Contient des fichiers binaires *.bin")
          << AOpt2007(mArchitecture,"CNNArch" ,"Model architecture : "+TheFastArch+" || "+TheFastStandard+" || "+TheFastArchWithMLP)
          << AOpt2007(mResol,"RESOL" ,"RESOL OPTION FOR THE MULTISCALE TRAINING: ")
   ;
}


void cAppliMatchMultipleOrtho::InitializePredictor ()
{
    StdOut()<<"MODEL ARCHITECTURE:: "<<mArchitecture<<"\n";
    bool IsArchWellDefined=false;
    IsArchWellDefined = (mArchitecture==TheFastArch) ||  (mArchitecture==TheFastArchReg) ||  (mArchitecture==TheFastStandard) || (mArchitecture==TheFastArchWithMLP) || (mArchitecture==TheFastArchDirectSim) || (mArchitecture==TheFastandPrjHead)|| (mArchitecture==TheMSNet) ;
    MMVII_INTERNAL_ASSERT_strong(IsArchWellDefined,"The network architecture should be specified : "+TheFastArch+" || "+TheFastStandard 
        +" || "+TheFastArchWithMLP+" || "+TheFastArchDirectSim+ " !");      
    MMVII_INTERNAL_ASSERT_strong(this->mModelBinDir!=""," Model params dir must be specified ! ");
    
    mWithExtCorr = (mArchitecture!="");
    
    if (mWithExtCorr)
    {
        // ARCHITECTURE and Location of Model Binaries 
        if(mArchitecture==TheFastArch)
        {
            mCNNPredictor = new aCnnModelPredictor(TheFastArch,mModelBinDir);
            // CREATE AN INSTANCE OF THE NETWORK 
            torch::Device device(torch::kCPU);
            mNetFastMVCNN->createModel(184,7,1,3,device); // becareful to change these values with respect to network architecture
				
				
            // Populate layers by learned weights and biases 
            mCNNPredictor->PopulateModelFromBinaryWithBN(mNetFastMVCNN);
            
            mCNNWin=mCNNPredictor->GetWindowSizeBN(mNetFastMVCNN);
				
            //Add padding to maintain the same size as output 
            auto Fast=mNetFastMVCNN->getFastSequential(); 
            
            // ACTIVATE PADDING (NOW DEACTIVATED)
            
            size_t Sz=Fast->size();
            size_t cc=0;
            for (cc=0;cc<Sz;cc++)
            {
                std::string LayerName=Fast->named_children()[cc].key();
                if (LayerName.rfind(std::string("conv"),0)==0)
                {   //torch::nn::Conv2dImpl *mod=Fast->named_children()[cc].value().get()->as<torch::nn::Conv2dImpl>();
                        //std::cout<<"condition verified on name of convolution "<<std::endl;
                    Fast->named_children()[cc].value().get()->as<torch::nn::Conv2dImpl>()->options.padding()=1;
                }
            }
        }
        if(mArchitecture==TheFastArchReg)
        {
            mCNNPredictor = new aCnnModelPredictor(TheFastArchReg,mModelBinDir);
            mCNNPredictor->PopulateModelFromBinaryWithBNReg(mNetFastMVCNNReg);
            
            //mCNNWin=mCNNPredictor->GetWindowSizeBNReg(mNetFastMVCNNReg);  just changed to test
			mCNNWin=cPt2di(7,7);	
            //Add padding to maintain the same size as output 
            auto Fast=mNetFastMVCNNReg->mFast; 
            size_t Sz=Fast->size();
            size_t cc=0;
            for (cc=0;cc<Sz;cc++)
            {
                std::string LayerName=Fast->named_children()[cc].key();
                if (LayerName.rfind(std::string("conv"),0)==0)
                {  
                    Fast->named_children()[cc].value().get()->as<torch::nn::Conv2dImpl>()->options.padding()=1;
                }
            }
        }
        if(mArchitecture==TheFastandPrjHead)
        {
            mCNNPredictor = new aCnnModelPredictor(TheFastandPrjHead,mModelBinDir);
            mCNNPredictor->PopulateModelPrjHead(mNetFastPrjHead);
            
            mCNNWin=mCNNPredictor->GetWindowSizePrjHead(mNetFastPrjHead);
				
            //Add padding to maintain the same size as output 
            auto Fast=mNetFastPrjHead->mFast; 
            size_t Sz=Fast->size();
            size_t cc=0;
            for (cc=0;cc<Sz;cc++)
            {
                std::string LayerName=Fast->named_children()[cc].key();
                if (LayerName.rfind(std::string("conv"),0)==0)
                {  
                    Fast->named_children()[cc].value().get()->as<torch::nn::Conv2dImpl>()->options.padding()=1;
                }
            }
        }
        if(mArchitecture==TheMSNet)
        { 
            mCNNPredictor = new aCnnModelPredictor(TheMSNet,mModelBinDir);
            mCNNPredictor->PopulateModelMSNetHead(mMSNet);
    
            mCNNWin=cPt2di(7,7); // The chosen window size is 7x7
        }
        if(mArchitecture==TheFastArchWithMLP)
        {
            mCNNPredictor = new aCnnModelPredictor(TheFastArchWithMLP,mModelBinDir);
            // CREATE AN INSTANCE OF THE NETWORK 
            //auto cuda_available = torch::cuda::is_available();
            //torch::Device device(cuda_available ? torch::kCUDA : torch::kCPU);
            //mNetFastMVCNNMLP=FastandHead(3,7,4,1,184,184,3,64,device); // not to change for the moment 
            //mNetFastMVCNNMLP->to(devicecuda);
            // Populate layers by learned weights and biases 
            mCNNPredictor->PopulateModelFastandHead(mNetFastMVCNNMLP);
            StdOut()<<"MODEL LOADED-------> "<<"\n";
            //mNetFastMVCNNMLP->to(torch::kCPU);
            mCNNWin=mCNNPredictor->GetWindowSizeFastandHead(mNetFastMVCNNMLP);
				
            //Add padding to maintain the same size as output 
            auto Fast=mNetFastMVCNNMLP->mFast; 
            
            // ACTIVATE PADDING (NOW DEACTIVATED)
            
            size_t Sz=Fast->size();
            size_t cc=0;
            for (cc=0;cc<Sz;cc++)
            {
                std::string LayerName=Fast->named_children()[cc].key();
                if (LayerName.rfind(std::string("conv"),0)==0)
                {   //torch::nn::Conv2dImpl *mod=Fast->named_children()[cc].value().get()->as<torch::nn::Conv2dImpl>();
                        //std::cout<<"condition verified on name of convolution "<<std::endl;
                    Fast->named_children()[cc].value().get()->as<torch::nn::Conv2dImpl>()->options.padding()=1;
                }
            }
        }
        if(mArchitecture==TheFastArchDirectSim)
        {
            mCNNPredictor = new aCnnModelPredictor(TheFastArchDirectSim,mModelBinDir);
            StdOut()<<"LOADING NETWORKKKK   ------> "<<"\n";
            mCNNPredictor->PopulateModelSimNet(mNetFastMVCNNDirectSIM);
            StdOut()<<"MODEL LOADED-SIMILARITY NETWORK    ------> "<<"\n";
            //mNetFastMVCNNMLP->to(torch::kCPU);
            mCNNWin=mCNNPredictor->GetWindowSizeSimNet(mNetFastMVCNNDirectSIM);
				
            //Add padding to maintain the same size as output 
            auto Fast=mNetFastMVCNNDirectSIM->mFast; 
            
            // ACTIVATE PADDING (NOW DEACTIVATED)
            
            size_t Sz=Fast->size();
            size_t cc=0;
            for (cc=0;cc<Sz;cc++)
            {
                std::string LayerName=Fast->named_children()[cc].key();
                if (LayerName.rfind(std::string("conv"),0)==0)
                {   //torch::nn::Conv2dImpl *mod=Fast->named_children()[cc].value().get()->as<torch::nn::Conv2dImpl>();
                        //std::cout<<"condition verified on name of convolution "<<std::endl;
                    Fast->named_children()[cc].value().get()->as<torch::nn::Conv2dImpl>()->options.padding()=1;
                }
            }
        }
        else if (mArchitecture==TheFastStandard)
        {
           mCNNPredictor = new aCnnModelPredictor(TheFastStandard,mModelBinDir); 
           
           // CREATE A CNN MODULE AND LOAD PARAMS 
            mNetFastStd->createModel(64,4,1,3);
            
            // Populate layers by learned weights and biases 
            mCNNPredictor->PopulateModelFromBinary(mNetFastStd);
            mCNNWin=mCNNPredictor->GetWindowSize(mNetFastStd);
            //Add padding to maintain the same size as input
            auto Fast=mNetFastStd->getFastSequential(); 
            
            size_t Sz=Fast->size();
            size_t cc=0;
            for (cc=0;cc<Sz;cc++)
            {
                std::string LayerName=Fast->named_children()[cc].key();
                if (LayerName.rfind(std::string("conv"),0)==0)
                    
                    {   //torch::nn::Conv2dImpl *mod=Fast->named_children()[cc].value().get()->as<torch::nn::Conv2dImpl>();
                        //std::cout<<"condition verified on name of convolution "<<std::endl;
                        Fast->named_children()[cc].value().get()->as<torch::nn::Conv2dImpl>()->options.padding()=1;
                    }
	         }   // DO NOT APPLY PADDING TO GET A VECTOR EMBDEDDING OF THE PATCH 
	         // PADDING IS USED WHENEVER THE WHOLE TILE IS CONCERNED 
        }
    }   
}

void cAppliMatchMultipleOrtho::CorrelMaster
     (
         const cPt2di & aCenter,   // Central Pixel
	 int aKIm,                  // Num of Image
	 bool & AllOk,              // Is all Window in masq ?
	 float &aWeight,            //  Weight of inside pixel
	 float & aCorrel            // Correl
     )
{
    AllOk = true;
    aWeight = 0;

    cMatIner2Var<tElemOrtho> aMatI;
    for (int aKScale = 0 ; aKScale < mNbScale ; aKScale++)
    {
         const tDImMasq & aDIM1  =  mVMasq.at(0   ).at(aKScale).DIm();
         const tDImMasq & aDIM2  =  mVMasq.at(aKIm).at(aKScale).DIm();
         const tDImOrtho & aDIO1 =  mVOrtho.at(0   ).at(aKScale).DIm();
         const tDImOrtho & aDIO2 =  mVOrtho.at(aKIm).at(aKScale).DIm();

	 double aPds = 1/(1+aKScale); // weight, more less arbitrary
         for (const auto & aLocNeigh : cRect2::BoxWindow(cPt2di(0,0),mSzW))  // Parse the window`
         {
              cPt2di  aNeigh = aCenter + aLocNeigh * (1<<aKScale);
              bool Ok = aDIM1.DefGetV(aNeigh,0) && aDIM2.DefGetV(aNeigh,0) ;  // Are both pixel valide
	      if (Ok)
	      {
                  aWeight++;
	          aMatI.Add(aPds,aDIO1.GetV(aNeigh),aDIO2.GetV(aNeigh));
	      }
	      else
	      {
                  AllOk=false;
	      }
         }
    }
    aCorrel =  aMatI.Correl(1e-15);
}




void cAppliMatchMultipleOrtho::ComputeSimilByCorrelMaster()
{
   MMVII_INTERNAL_ASSERT_strong(mIm1Mast,"DM4MatchMultipleOrtho, for now, only handle master image mode");

   tDImSimil & aDImSim = mImSimil.DIm();
   // Parse all pixels
   for (const auto & aP : aDImSim)
   {
        // method : average of image all ok if any, else weighted average of partial corr
        float aSumCorAllOk = 0.0; // Sum of correl of image where point are all ok
        float aSumWeightAllOk = 0.0; //   Nb of All Ok
        float aSumCorPart  = 0.0; //  Sum of weighted partial correl
        float aSumWeightPart = 0.0; //  Sum of weight
	// Parse secondary images 
        for (int aKIm=1 ; aKIm<mNbIm ; aKIm++)
	{
        bool AllOk;
	    float aWeight,aCorrel;
        CorrelMaster(aP,aKIm,AllOk,aWeight,aCorrel);
	    if (AllOk)
	    {
               aSumCorAllOk     += aCorrel;
	       aSumWeightAllOk  += 1;
	    }
	    else
	    {
               aSumCorPart     += aCorrel * aWeight;
	       aSumWeightPart  +=   aWeight;
	    }
	}
	float aAvgCorr =  (aSumWeightAllOk !=0)            ? 
                          (aSumCorAllOk / aSumWeightAllOk) :
                          (aSumCorPart / std::max(1e-5f,aSumWeightPart)) ;

	aDImSim.SetV(aP,1-aAvgCorr);
   }
}


void cAppliMatchMultipleOrtho::ComputeSimilByLearnedCorrelMaster(std::vector<torch::Tensor> * AllOrthosEmbeddings)
{
   MMVII_INTERNAL_ASSERT_strong(mIm1Mast,"DM4MatchMultipleOrtho, for now, only handle master image mode");

   tDImSimil & aDImSim = mImSimil.DIm();
   // Parse all pixels
	const tDImMasq & aDIM1  =  mVMasq.at(0   ).at(0   ).DIm();
    auto MasterEmbedding=AllOrthosEmbeddings->at(0);
    int FeatSize=MasterEmbedding.size(0);
    //std::cout<<" feature vector size : "<<FeatSize<<std::endl;
   for (const auto & aP : aDImSim)
   {
        // method : average of image all ok if any, else weighted average of partial corr
        float aSumCorAllOk = 0.0; // Sum of correl of image where point are all ok
        float aSumWeightAllOk = 0.0; //   Nb of All Ok
        float aSumCorPart  = 0.0; //  Sum of weighted partial correl
        float aSumWeightPart = 0.0; //  Sum of weight
	// Parse secondary images 
	using namespace torch::indexing;
    auto aVecRef=MasterEmbedding.slice(0,0,FeatSize,1).slice(1,aP.y(),aP.y()+1,1).slice(2,aP.x(),aP.x()+1,1);
    //std::cout<<" reference vector "<<aVecRef<<std::endl;
    //int smpl=1;
        for (int aKIm=1 ; aKIm<mNbIm ; aKIm++)
	{
        bool AllOk;
	    float aWeight,aCorrel;
        //CorrelMaster(aP,aKIm,AllOk,aWeight,aCorrel);
        // Compute cosine simialrity with respect to master ortho embeddings 
        
        /**************************************************************************************/
        AllOk = true;
        aWeight = 0;
        const tDImMasq & aDIM2  =  mVMasq.at(aKIm).at(  0).DIm();
        for (const auto & aPvoisin : cRect2::BoxWindow(aP,mCNNWin))  // Parse the window`
        {
            bool Ok = aDIM1.DefGetV(aPvoisin,0) && aDIM2.DefGetV(aPvoisin,0) ;  // Are both pixel valide
            if (Ok)
            {
                aWeight++;
            }
            else
            {
                AllOk=false;
            }
        }
        // Compute correl separately 
        //using namespace torch::indexing;
        auto aVecOther=AllOrthosEmbeddings->at(aKIm).slice(0,0,FeatSize,1).slice(1,aP.y(),aP.y()+1,1).slice(2,aP.x(),aP.x()+1,1);
        auto aSim=torch::mm(aVecRef.view({1,FeatSize}),aVecOther.view({FeatSize,1}));
        //std::cout<<" slave vector "<<aVecOther<<std::endl;
        aCorrel=(float)aSim.item<float>();
        //std::cout<<"correl val "<<aCorrel<<std::endl;
        /*if (smpl){
            std::cout<<"correl val "<<aCorrel<<std::endl;
            smpl--;
        }*/
        //std::cout<<" CORREL "<<aCorrel<<std::endl;
        /**************************************************************************************/  
	    if (AllOk)
	    {
           aSumCorAllOk     += aCorrel;
	       aSumWeightAllOk  += 1;
	    }
	    else
	    {
           aSumCorPart     += aCorrel * aWeight;
	       aSumWeightPart  +=   aWeight;
	    }
	}
	float aAvgCorr =  (aSumWeightAllOk !=0)            ? 
                          (aSumCorAllOk / aSumWeightAllOk) :
                          (aSumCorPart / std::max(1e-5f,aSumWeightPart)) ;

	aDImSim.SetV(aP,1-aAvgCorr);
   }
}

void cAppliMatchMultipleOrtho::ComputeSimilByLearnedCorrelMasterEnhanced(std::vector<torch::Tensor> * AllOrthosEmbeddings)
{
   MMVII_INTERNAL_ASSERT_strong(mIm1Mast,"DM4MatchMultipleOrtho, for now, only handle master image mode");

   tDImSimil & aDImSim = mImSimil.DIm();
   // Parse all pixels
	const tDImMasq & aDIM1  =  mVMasq.at(0   ).at(0   ).DIm();
    //compute similarity matrices at the beginning 
    std::vector<torch::Tensor> * AllSimilarities= new std::vector<torch::Tensor>;;
    for (int k=1; k<mNbIm; k++)
    {
        // compute element wise cross product along feature size dimension 
        auto aCrossProd=at::cosine_similarity(AllOrthosEmbeddings->at(0),AllOrthosEmbeddings->at(k),0).squeeze();
        AllSimilarities->push_back(aCrossProd);
        // Here display similarity images of tiles 
    }
    
    // Free all ortho OneOrthoEmbeding 
    delete AllOrthosEmbeddings; 
    //std::cout<<" feature vector size : "<<FeatSize<<std::endl;
   for (const auto & aP : aDImSim)
   {
        // method : average of image all ok if any, else weighted average of partial corr
        float aSumCorAllOk = 0.0; // Sum of correl of image where point are all ok
        float aSumWeightAllOk = 0.0; //   Nb of All Ok
        float aSumCorPart  = 0.0; //  Sum of weighted partial correl
        float aSumWeightPart = 0.0; //  Sum of weight
	 // Parse secondary images 
	 using namespace torch::indexing;;
        for (int aKIm=1 ; aKIm<mNbIm ; aKIm++)
	{
        bool AllOk;
	    float aWeight,aCorrel;
        //CorrelMaster(aP,aKIm,AllOk,aWeight,aCorrel);
        // Compute cosine simialrity with respect to master ortho embeddings 
        
        /**************************************************************************************/
        AllOk = true;
        aWeight = 0;
        const tDImMasq & aDIM2  =  mVMasq.at(aKIm).at(0   ).DIm();
        for (const auto & aPvoisin : cRect2::BoxWindow(aP,mCNNWin))  // Parse the window`
        {
            bool Ok = aDIM1.DefGetV(aPvoisin,0) && aDIM2.DefGetV(aPvoisin,0) ;  // Are both pixel valide
            if (Ok)
            {
                aWeight++;
            }
            else
            {
                AllOk=false;
            }
        }
        // Compute correl separately 
        //using namespace torch::indexing;
        auto aSim=AllSimilarities->at(aKIm-1).slice(0,aP.y(),aP.y()+1,1).slice(1,aP.x(),aP.x()+1,1);
        //std::cout<<" slave vector "<<aSim<<std::endl;
        aCorrel=(float)aSim.item<float>();
        /**************************************************************************************/  
	    if (AllOk)
	    {
           aSumCorAllOk     += aCorrel;
	       aSumWeightAllOk  += 1;
	    }
	    else
	    {
           aSumCorPart     += aCorrel * aWeight;
	       aSumWeightPart  +=   aWeight;
	    }
	}
	float aAvgCorr =  (aSumWeightAllOk !=0)            ? 
                          (aSumCorAllOk / aSumWeightAllOk) :
                          (aSumCorPart / std::max(1e-5f,aSumWeightPart)) ;

	aDImSim.SetV(aP,1-aAvgCorr);
   }

   // delete All Similarities 
   delete AllSimilarities;
}


/////////////////////////////////////////////////////////////////////////////////////////////////

void cAppliMatchMultipleOrtho::ComputeSimilByLearnedCorrelMasterDecision()
{
   MMVII_INTERNAL_ASSERT_strong(mIm1Mast,"DM4MatchMultipleOrtho, for now, only handle master image mode");

   tDImSimil & aDImSim = mImSimil.DIm();
   // Parse all pixels
	const tDImMasq & aDIM1  =  mVMasq.at(0   ).at(0   ).DIm();
    //compute similarity matrices at the beginning 
    std::vector<torch::Tensor> * AllSimilarities= new std::vector<torch::Tensor>;
    auto MasterOrtho=mVOrtho.at(0); //vector<tImOrtho>
    for (unsigned int i=1;i<mVOrtho.size();i++)
    {
        cPt2di aSzOrtho=mVOrtho.at(i).at(0).DIm().Sz();
        auto aCrossProd=mCNNPredictor->PredictUNetWDecision(mMSNet,MasterOrtho,mVOrtho.at(i),aSzOrtho);
        AllSimilarities->push_back(aCrossProd);     
    }
   for (const auto & aP : aDImSim)
   {
        // method : average of image all ok if any, else weighted average of partial corr
        float aSumCorAllOk = 0.0; // Sum of correl of image where point are all ok
        float aSumWeightAllOk = 0.0; //   Nb of All Ok
        float aSumCorPart  = 0.0; //  Sum of weighted partial correl
        float aSumWeightPart = 0.0; //  Sum of weight
	 // Parse secondary images 
	 using namespace torch::indexing;;
        for (int aKIm=1 ; aKIm<mNbIm ; aKIm++)
	{
        bool AllOk;
	    float aWeight,aCorrel;
        //CorrelMaster(aP,aKIm,AllOk,aWeight,aCorrel);
        // Compute cosine simialrity with respect to master ortho embeddings 
        
        /**************************************************************************************/
        AllOk = true;
        aWeight = 0;
        const tDImMasq & aDIM2  =  mVMasq.at(aKIm).at(0   ).DIm();
        for (const auto & aPvoisin : cRect2::BoxWindow(aP,mCNNWin))  // Parse the window`
        {
            bool Ok = aDIM1.DefGetV(aPvoisin,0) && aDIM2.DefGetV(aPvoisin,0) ;  // Are both pixel valide
            if (Ok)
            {
                aWeight++;
            }
            else
            {
                AllOk=false;
            }
        }
        // Compute correl separately 
        //using namespace torch::indexing;
        auto aSim=AllSimilarities->at(aKIm-1).slice(0,aP.y(),aP.y()+1,1).slice(1,aP.x(),aP.x()+1,1);
        //std::cout<<" slave vector "<<aSim<<std::endl;
        aCorrel=(float)aSim.item<float>();
        /**************************************************************************************/  
	    if (AllOk)
	    {
           aSumCorAllOk     += aCorrel;
	       aSumWeightAllOk  += 1;
	    }
	    else
	    {
           aSumCorPart     += aCorrel * aWeight;
	       aSumWeightPart  +=   aWeight;
	    }
	}
	double aAvgCorr =  (aSumWeightAllOk !=0)            ? 
                          (aSumCorAllOk / aSumWeightAllOk) :
                          (aSumCorPart / std::max(1e-5f,aSumWeightPart)) ;
    //std::cout<<"avant "<<aAvgCorr<<std::endl;
    // Interpolate correlation values 
    InterpolatePos(spaceCorrAttMS,spaceProbAttMS,aAvgCorr);
    //std::cout<<"apres "<<aAvgCorr<<std::endl;
	aDImSim.SetV(aP,1-aAvgCorr);
   }

   // delete All Similarities 
   delete AllSimilarities;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void cAppliMatchMultipleOrtho::ComputeSimilByLearnedCorrelMasterMaxMoy(std::vector<torch::Tensor> * AllOrthosEmbeddings)
{
   MMVII_INTERNAL_ASSERT_strong(mIm1Mast,"DM4MatchMultipleOrtho, for now, only handle master image mode");

   tDImSimil & aDImSim = mImSimil.DIm();
   // Parse all pixels
	const tDImMasq & aDIM1  =  mVMasq.at(0   ).at(0   ).DIm();
    //compute similarity matrices at the beginning 
    std::vector<torch::Tensor> * AllSimilarities= new std::vector<torch::Tensor>;;
    for (int k=1; k<mNbIm; k++)
    {
        
        // compute element wise cross product along feature size dimension 
        auto aCrossProd=at::cosine_similarity(AllOrthosEmbeddings->at(0),AllOrthosEmbeddings->at(k),0).squeeze();
        AllSimilarities->push_back(aCrossProd);
    }
    // Free all ortho OneOrthoEmbeding 
    delete AllOrthosEmbeddings; 

    //std::cout<<" feature vector size : "<<FeatSize<<std::endl;
   for (const auto & aP : aDImSim)
   {
	 // Parse secondary images 
    tREAL4 aTab[mNbIm-1];
    tREAL4 aPonder[mNbIm-1];
	 using namespace torch::indexing;
        for (int aKIm=1 ; aKIm<mNbIm ; aKIm++)
	{
        bool AllOk;
	    float aWeight,aCorrel;
        //CorrelMaster(aP,aKIm,AllOk,aWeight,aCorrel);
        // Compute cosine simialrity with respect to master ortho embeddings 
        
        /**************************************************************************************/
        AllOk = true;
        aWeight = 0;
        const tDImMasq & aDIM2  =  mVMasq.at(aKIm).at(0   ).DIm();
        for (const auto & aPvoisin : cRect2::BoxWindow(aP,mCNNWin))  // Parse the window`
        {
            bool Ok = aDIM1.DefGetV(aPvoisin,0) && aDIM2.DefGetV(aPvoisin,0) ;  // Are both pixel valide
            if (Ok)
            {
                aWeight++;
            }
            else
            {
                AllOk=false;
            }
        }
        // Compute correl separately 
        //using namespace torch::indexing;
        auto aSim=AllSimilarities->at(aKIm-1).slice(0,aP.y(),aP.y()+1,1).slice(1,aP.x(),aP.x()+1,1);
        //std::cout<<" slave vector "<<aSim<<std::endl;
        aCorrel=(float)aSim.item<float>();
        /**************************************************************************************/  
	    if (AllOk)
	    {
            aTab[aKIm-1]    = aCorrel;
            aPonder[aKIm-1] = 1.0;
	    }
	    else
	    {
           aTab[aKIm-1]    = aCorrel ; 
           aPonder[aKIm-1] = aWeight/(mCNNWin.x()*mCNNWin.y());
	    }
	}
	// Moyennes deux à deux des corrélations
    tREAL4 AggCorr=-2.0;
    for (int j=0;j<mNbIm-2;j++)
    {
        for (int i=j+1;i<mNbIm-1;i++)
        {
            tREAL4 aCorr=(aTab[i]*aPonder[i]+ aTab[j]*aPonder[j])/std::max(1e-5f,aPonder[i]+aPonder[j]); 
            if (AggCorr<aCorr)
            {
                AggCorr=aCorr;
            }
        }
    }
    if(AggCorr==-2.0) AggCorr=0.5;   // no max is found 
    aDImSim.SetV(aP,1-AggCorr);
   }

   // delete All Similarities 
   delete AllSimilarities;
}

void cAppliMatchMultipleOrtho::ComputeSimilByLearnedCorrelMasterMaxMoyMulScale(std::vector<torch::Tensor> * AllOrthosEmbeddings)
{
    
    // Here we jointly fuse Similarity measures from Multi-Scale information 
    // Size of embeddings vector = 4 (scales)*features
    
    // Ortho 1
    // 0 --> Resol 1
    // 1 --> Resol / 2
    // 2 --> Resol / 4
    // 3 --> Resol / 8
    
    // Ortho 2
    // 4 --> Resol 1
    // 5 --> Resol / 2 
    // 6 --> Resol / 4
    // 7 --> Resol / 8
    
    //.....
    
    
   MMVII_INTERNAL_ASSERT_strong(mIm1Mast,"DM4MatchMultipleOrtho, for now, only handle master image mode");

   tDImSimil & aDImSim = mImSimil.DIm();
   // Parse all pixels
	const tDImMasq & aDIM1  =  mVMasq.at(0   ).at(0   ).DIm();
    //compute similarity matrices at the beginning 
    std::vector<torch::Tensor> * AllSimilarities= new std::vector<torch::Tensor>;;
    for (int scales=0;scales<4;scales++)
    {
        for (int k=1; k<mNbIm; k++)
        {
            // compute element wise cross product along feature size dimension 
            auto aCrossProd=at::cosine_similarity(AllOrthosEmbeddings->at(scales),AllOrthosEmbeddings->at(4*k+scales),0).squeeze();
            AllSimilarities->push_back(aCrossProd);
        }
    }
    
    // Free all ortho OneOrthoEmbeding 
    delete AllOrthosEmbeddings; 
    //std::cout<<" feature vector size : "<<FeatSize<<std::endl;
   for (const auto & aP : aDImSim)
   {
	 // Parse secondary images 
    tREAL4 aTab[(mNbIm-1)*4];
    tREAL4 aPonder[(mNbIm-1)*4];
    
	 using namespace torch::indexing;
     for (int aKIm=1 ; aKIm<=(mNbIm-1)*4 ; aKIm++)
	{
        bool AllOk;
	    float aWeight,aCorrel;
        //CorrelMaster(aP,aKIm,AllOk,aWeight,aCorrel);
        // Compute cosine simialrity with respect to master ortho embeddings 
        
        /**************************************************************************************/
        AllOk = true;
        aWeight = 0;
        const tDImMasq & aDIM2  =  mVMasq.at(aKIm%(mNbIm-1) ? aKIm%(mNbIm-1) : (mNbIm-1)).at(0 ).DIm();
        for (const auto & aPvoisin : cRect2::BoxWindow(aP,mCNNWin))  // Parse the window`
        {
            bool Ok = aDIM1.DefGetV(aPvoisin,0) && aDIM2.DefGetV(aPvoisin,0) ;  // Are both pixel valid
            if (Ok)
            {
                aWeight++;
            }
            else
            {
                AllOk=false;
            }
        }
        // Compute correl separately 
        //using namespace torch::indexing;
        auto aSim=AllSimilarities->at(aKIm-1).slice(0,aP.y(),aP.y()+1,1).slice(1,aP.x(),aP.x()+1,1);
        //std::cout<<" slave vector "<<aVecOther<<std::endl;
        aCorrel=(float)aSim.item<float>();
        /**************************************************************************************/  
	    if (AllOk)
	    {
            aTab[aKIm-1]    = aCorrel;
            aPonder[aKIm-1] = 1.0;
	    }
	    else
	    {
           aTab[aKIm-1]    = aCorrel ; 
           aPonder[aKIm-1] = aWeight/(mCNNWin.x()*mCNNWin.y());
	    }
	}
	// Moyennes deux à deux des corrélations
    tREAL4 AggCorr=-2.0;
    tREAL4 AggCorrMaxAllScales=-2.0;
    
    for (int scales=0;scales<4;scales++)
    {
        AggCorr=-2.0;
        for (int j=0;j<mNbIm-2;j++)
        {
            for (int i=j+1;i<mNbIm-1;i++)
            {
                tREAL4 aCorr=(aTab[i+(mNbIm-1)*scales]*aPonder[i+(mNbIm-1)*scales]+ aTab[j+(mNbIm-1)*scales]*aPonder[j+(mNbIm-1)*scales])/std::max(1e-5f,aPonder[i+(mNbIm-1)*scales]+aPonder[j+(mNbIm-1)*scales]); 
                if (AggCorr<aCorr)
                {
                    AggCorr=aCorr;
                }
            }
        }
        if (AggCorrMaxAllScales<AggCorr)
        {
            AggCorrMaxAllScales=AggCorr;
        }
    }
    if(AggCorrMaxAllScales==-2.0) AggCorrMaxAllScales=0.5;   // no max is found 
    aDImSim.SetV(aP,1-AggCorrMaxAllScales);
   }

   // delete All Similarities 
   delete AllSimilarities;
}


void cAppliMatchMultipleOrtho::ComputeSimilByLearnedCorrelMasterDempsterShafer(std::vector<torch::Tensor> * AllOrthosEmbeddings)
{
   MMVII_INTERNAL_ASSERT_strong(mIm1Mast,"DM4MatchMultipleOrtho, for now, only handle master image mode");

   tDImSimil & aDImSim = mImSimil.DIm();
   // Parse all pixels
	const tDImMasq & aDIM1  =  mVMasq.at(0   ).at(0   ).DIm();
    //compute similarity matrices at the beginning 
    std::vector<torch::Tensor> * AllSimilarities= new std::vector<torch::Tensor>;;
    for (int k=1; k<mNbIm; k++)
    {
        // compute element wise cross product along feature size dimension 
        auto aCrossProd=at::cosine_similarity(AllOrthosEmbeddings->at(0),AllOrthosEmbeddings->at(k),0).squeeze();
        AllSimilarities->push_back(aCrossProd);
    }
    // Free all ortho OneOrthoEmbeding 
    delete AllOrthosEmbeddings; 
    //std::cout<<" feature vector size : "<<FeatSize<<std::endl;
   for (const auto & aP : aDImSim)
   {
	 // Parse secondary images 
    tREAL4 aTab[mNbIm-1];
    tREAL4 aPonder[mNbIm-1];
	 using namespace torch::indexing;
        for (int aKIm=1 ; aKIm<mNbIm ; aKIm++)
	{
        bool AllOk;
	    float aWeight,aCorrel;
        //CorrelMaster(aP,aKIm,AllOk,aWeight,aCorrel);
        // Compute cosine simialrity with respect to master ortho embeddings 
        
        /**************************************************************************************/
        AllOk = true;
        aWeight = 0;
        const tDImMasq & aDIM2  =  mVMasq.at(aKIm).at(0   ).DIm();
        for (const auto & aPvoisin : cRect2::BoxWindow(aP,mCNNWin))  // Parse the window`
        {
            bool Ok = aDIM1.DefGetV(aPvoisin,0) && aDIM2.DefGetV(aPvoisin,0) ;  // Are both pixel valide
            if (Ok)
            {
                aWeight++;
            }
            else
            {
                AllOk=false;
            }
        }
        // Compute correl separately 
        auto aSim=AllSimilarities->at(aKIm-1).slice(0,aP.y(),aP.y()+1,1).slice(1,aP.x(),aP.x()+1,1);
        //std::cout<<" slave vector "<<aVecOther<<std::endl;
        aCorrel=(float)aSim.item<float>();
        /**************************************************************************************/  
	    if (AllOk)
	    {
            aTab[aKIm-1]    = aCorrel;
            aPonder[aKIm-1] = 1.0;
	    }
	    else
	    {
           aTab[aKIm-1]    = aCorrel ; 
           aPonder[aKIm-1] = aWeight/(mCNNWin.x()*mCNNWin.y());
	    }
	}
	// COmbinaison des corrélations par la méthode de D-S
	tREAL4 AggCorr;
    if (mNbIm==2) 
    {
        AggCorr=aTab[0];
    }
    else
    {
        AggCorr=ComputeJointMassBetween2Sets(aTab[0],aTab[1],aPonder[0],aPonder[1]);
        //std::cout<<" Value of correl "<<AggCorr<<std::endl;
        if (mNbIm>3)
        {
            for (int j=0;j<mNbIm-2;j++)
            {
                for (int i=(j==0) ? j+2:j+1;i<mNbIm-1;i++)
                {
                    AggCorr=ComputeJointMassBetween2Sets(AggCorr,aTab[i],1.0,aPonder[i]);
                }
            }
        }
    }
    //std::cout<<" Value of correl ))  "<<AggCorr<<std::endl;
    aDImSim.SetV(aP,1-AggCorr);
   }

   // delete All Similarities 
   delete AllSimilarities;
}

tREAL4 cAppliMatchMultipleOrtho::ComputeConflictBetween2SEts(tREAL4 aCorrel1, tREAL4 aCorrel2, tREAL4 aPonder1,tREAL4 aPonder2)
{
    return aPonder1*aCorrel1*(1-aPonder2*aCorrel2)+ (1-aPonder1*aCorrel1)+aPonder2*aCorrel2;
}
    
tREAL4 cAppliMatchMultipleOrtho::ComputeJointMassBetween2Sets(tREAL4 aCorrel1, tREAL4 aCorrel2, tREAL4 aPonder1,tREAL4 aPonder2)
{
    tREAL4 k=ComputeConflictBetween2SEts(aCorrel1,aCorrel2,aPonder1,aPonder2);
    //std::cout<<"Conflict between both values "<<k<<std::endl;
    if (k==1.0)  // conflict between 2 Correlations measures  ==> returm mean of correl
    {
        // for now return average but if there is a conflict between correl, it should be considered as an indicator !!!
        return (aCorrel1*aPonder1+aCorrel2*aPonder2)/std::max(1e-5f,aPonder1+aPonder2);
    }
    else
    {
        return aCorrel1*aPonder1*aPonder2*aCorrel2/(1-k);
    }
}

void cAppliMatchMultipleOrtho::MakeNormalizedIms()  // Possible errors here 
{
    // NORMALIZING IMAGES BEFORE INFERENCE 
    for( auto& MsOrth: mVOrtho)
    {
        for (auto& Im:MsOrth)
        {
            Im=NormalizedAvgDev(Im,1e-4);
        }
    }
}



int  cAppliMatchMultipleOrtho::Exe()
{

   // Parse all Z
   // If using a model (CNN) Initialize the predictor 
   if (mArchitecture!="")
   {
        InitializePredictor();
   }
   for (int aZ=0 ; aZ<mNbZ ; aZ++)
   {
        mPrefixZ =  mPrefixGlob + "_Z" + ToStr(aZ);

        bool NoFile = ExistFile(mPrefixZ+ "_NoData");  // If no data in masq thie file exist
        bool WithFile = ExistFile(NameOrtho(0,0));
	// A little check
        MMVII_INTERNAL_ASSERT_strong(NoFile!=WithFile,"DM4MatchMultipleOrtho, incoherence file");
        if ((aZ==0)  && (true))
        {
             cDataFileIm2D aDF = cDataFileIm2D::Create(NameOrtho(0,0),false);
             StdOut() << " * NbI=" << mNbIm << " NbS=" <<  mNbScale << " NbZ=" <<  mNbZ << " Sz=" << aDF.Sz() << " SzW=" << mSzW << "\n";
        }
	if (WithFile)
        {
	    // Read  orthos and masq in  vectors of images
	    mSzIms = cPt2di(-1234,6789);
	    for (int aKIm=0 ; aKIm<mNbIm ; aKIm++)
	    {
                 mVOrtho.push_back(tVecOrtho());
                 mVMasq.push_back(tVecMasq());
                 for (int aKScale=0 ; aKScale<mNbScale ; aKScale++)
                    {
                        mVOrtho.at(aKIm).push_back(tImOrtho::FromFile(NameOrtho(aKIm,aKScale)));
                        if ((aKIm==0) && (aKScale==0))
                            mSzIms = mVOrtho[0][0].DIm().Sz();  // Compute the size at level

                        mVMasq.at(aKIm).push_back(tImMasq::FromFile(NameMasq(aKIm,aKScale)));

                        // check all images have the same at a given level
                        MMVII_INTERNAL_ASSERT_strong(mVOrtho[aKIm][aKScale].DIm().Sz()==mSzIms,"DM4O : variable size(ortho)");
                        MMVII_INTERNAL_ASSERT_strong(mVMasq [aKIm][aKScale].DIm().Sz()==mSzIms,"DM4O : variable size(masq)");
                    }
	    }

	    
	    // NORMALIZE IF LEARNING BASED CORRELATION 
        if (mWithExtCorr)
        {
           // MakeNormalizedIms();
        
        }
    
	    // Create similarity image with good size
	    mImSimil = tImSimil(mSzIms);
	    mImSimil.DIm().InitCste(2.0);   //  2 => correl of -1
    

        if(mWithExtCorr)
        {
            std::vector<torch::Tensor> * OrthosEmbeddings= new std::vector<torch::Tensor>;
            if (!mWithDecisionNet)
            {
                // Inference based correlation 
                // Create Embeddings 
                // Calculate the EMBEDDINGS ONE TIME USING FOWARD OVER THE WHOLE TILEs
                for (unsigned int i=0;i<mVOrtho.size();i++)
                {
                    cPt2di aSzOrtho=mVOrtho.at(i).at(0).DIm().Sz();
                    // Initialize Feature Size ;
                    /*int FeatSize=0;
                    if (mArchitecture==TheFastStandard) FeatSize=64 ;
                    if (mArchitecture==TheFastArchReg) FeatSize=64 ;  // change here to account for a new model 
                    if (mArchitecture==TheFastandPrjHead) FeatSize=112 ; 
                    if (mArchitecture==TheFastArch)   FeatSize=184;
                    if (mArchitecture==TheFastArchWithMLP)   FeatSize=184;
                    if (mArchitecture==TheFastArchDirectSim)   FeatSize=184;*/
                    //  Initialize Embeddings and store them for correlation calculus 
                    //auto OneOrthoEmbeding=torch::empty({1,FeatSize,aSzOrtho.y(),aSzOrtho.x()},torch::TensorOptions().dtype(torch::kFloat32));
                    
                    torch::Tensor OneOrthoEmbeding;
                    if (mArchitecture==TheFastStandard)
                        {
                        OneOrthoEmbeding=mCNNPredictor->PredictTile(mNetFastStd,mVOrtho.at(i).at(0),aSzOrtho);
                        }
                    else if (mArchitecture==TheFastArch)
                        {
                        OneOrthoEmbeding=mCNNPredictor->PredictWithBNTile(mNetFastMVCNN,mVOrtho.at(i).at(0),aSzOrtho);
                        }
                    else if (mArchitecture==TheFastArchReg)
                        {
                            OneOrthoEmbeding=mCNNPredictor->PredictWithBNTileReg(mNetFastMVCNNReg,mVOrtho.at(i).at(0),aSzOrtho);
                        }
                    else if (mArchitecture==TheFastandPrjHead)
                        {
                        // std::cout<<"ORTOHS SIZES :  ====> "<<aSzOrtho<<std::endl;
                            OneOrthoEmbeding=mCNNPredictor->PredictPrjHead(mNetFastPrjHead,mVOrtho.at(i).at(0),aSzOrtho);
                        }
                    else if (mArchitecture==TheMSNet)
                        {
                        //  OneOrthoEmbeding=mCNNPredictor->PredictMSNetCommon(mMSNet,mVOrtho.at(i),aSzOrtho);
                        // OneOrthoEmbeding=mCNNPredictor->PredictMSNet(mMSNet,mVOrtho.at(i),aSzOrtho);
                            
                            /*int Resol=1;
                            if (mResol!="")
                            {
                                Resol=std::atoi(mResol.c_str());
                            auto CommonEmbedding=mCNNPredictor->PredictMSNet(mMSNet,mVOrtho.at(i),aSzOrtho);
                            switch (Resol)
                            {
                                case 1:
                                    OneOrthoEmbeding=mCNNPredictor->PredictMSNet1(mMSNet,CommonEmbedding);
                                    break;
                                case 2:
                                    OneOrthoEmbeding=mCNNPredictor->PredictMSNet2(mMSNet,CommonEmbedding);
                                    break;
                                case 4:
                                    OneOrthoEmbeding=mCNNPredictor->PredictMSNet3(mMSNet,CommonEmbedding);
                                    break;
                                case 8:
                                    OneOrthoEmbeding=mCNNPredictor->PredictMSNet4(mMSNet,CommonEmbedding);
                                    break;
                                default:
                                    // Full Resolution Inference 
                                    OneOrthoEmbeding=mCNNPredictor->PredictMSNet1(mMSNet,CommonEmbedding);
                                    break;
                            }*/
                    
                            OneOrthoEmbeding=mCNNPredictor->PredictMSNetHead(mMSNet,mVOrtho.at(i),aSzOrtho);
                        }
                    else if (mArchitecture==TheFastArchWithMLP)
                        {
                            OneOrthoEmbeding=mCNNPredictor->PredictFastWithHead(mNetFastMVCNNMLP,mVOrtho.at(i).at(0),aSzOrtho);
                        }
                    else if (mArchitecture==TheFastArchDirectSim)
                        {
                            OneOrthoEmbeding=mCNNPredictor->PredictSimNetConv(mNetFastMVCNNDirectSIM,mVOrtho.at(i).at(0),aSzOrtho);
                        }
                    
                    StdOut()  <<" EMBEDDING FOR VECTOR OR FULL RESOLUTION ORTHO : "<<i<<OneOrthoEmbeding.sizes()<<"\n";
                
                    // store in relevant vector 
                    OrthosEmbeddings->push_back(OneOrthoEmbeding);
                }
            }
            //StdOut()  <<" Size OF EMBEDDINGS MS : " <<OrthosEmbeddings->size()<<"\n";
            
            // GIVEN THE ORTHOS EMBEDDINGS, Compute Correlation for each pixel in the similarity image => index work to get vectors from from tensors 
            if (mArchitecture==TheMSNet)
            {
                //ComputeSimilByLearnedCorrelMasterMaxMoyMulScale(OrthosEmbeddings); // Size 4*numberofOrthos
                //ComputeSimilByLearnedCorrelMasterEnhanced(OrthosEmbeddings);
                ComputeSimilByLearnedCorrelMasterDecision();
            }
            else
            {
               ComputeSimilByLearnedCorrelMasterMaxMoy(OrthosEmbeddings); 
            }
            
        }
        else
        {
            ComputeSimilByCorrelMaster();    
        }
        
	    mImSimil.DIm().ToFile(mPrefixZ+ "_Sim.tif"); // Save similarities
	    mVOrtho.clear();
	    mVMasq.clear();
        }
   }
   return EXIT_SUCCESS;
}



};

/* =============================================== */
/*                                                 */
/*                       ::                        */
/*                                                 */
/* =============================================== */
using namespace  cNS_MatchMultipleOrtho;

tMMVII_UnikPApli Alloc_MatchMultipleOrtho(const std::vector<std::string> &  aVArgs,const cSpecMMVII_Appli & aSpec)
{
   return tMMVII_UnikPApli(new cAppliMatchMultipleOrtho(aVArgs,aSpec));
}

cSpecMMVII_Appli  TheSpecMatchMultipleOrtho
(
     "DM4MatchMultipleOrtho",
      Alloc_MatchMultipleOrtho,
      "Compute similarite of overlapping ortho images",
      {eApF::Match},
      {eApDT::Image},
      {eApDT::Image},
      __FILE__
);



};
