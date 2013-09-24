// File Automatically generated by eLiSe
#include "general/all.h"
#include "private/all.h"
#include "cEqAppui_PTInc_M2CPolyn2.h"


cEqAppui_PTInc_M2CPolyn2::cEqAppui_PTInc_M2CPolyn2():
    cElCompiledFonc(2)
{
   AddIntRef (cIncIntervale("Intr",0,9));
   AddIntRef (cIncIntervale("Orient",9,15));
   AddIntRef (cIncIntervale("Tmp_PTer",15,18));
   Close(false);
}



void cEqAppui_PTInc_M2CPolyn2::ComputeVal()
{
   double tmp0_ = mCompCoord[9];
   double tmp1_ = mCompCoord[10];
   double tmp2_ = cos(tmp1_);
   double tmp3_ = sin(tmp0_);
   double tmp4_ = cos(tmp0_);
   double tmp5_ = sin(tmp1_);
   double tmp6_ = mCompCoord[11];
   double tmp7_ = mCompCoord[15];
   double tmp8_ = mCompCoord[12];
   double tmp9_ = tmp7_-tmp8_;
   double tmp10_ = sin(tmp6_);
   double tmp11_ = -(tmp10_);
   double tmp12_ = -(tmp5_);
   double tmp13_ = cos(tmp6_);
   double tmp14_ = mCompCoord[16];
   double tmp15_ = mCompCoord[13];
   double tmp16_ = tmp14_-tmp15_;
   double tmp17_ = mCompCoord[17];
   double tmp18_ = mCompCoord[14];
   double tmp19_ = tmp17_-tmp18_;
   double tmp20_ = -(tmp3_);
   double tmp21_ = tmp4_*tmp12_;
   double tmp22_ = tmp3_*tmp12_;
   double tmp23_ = mCompCoord[0];
   double tmp24_ = tmp20_*tmp11_;
   double tmp25_ = tmp21_*tmp13_;
   double tmp26_ = tmp24_+tmp25_;
   double tmp27_ = (tmp26_)*(tmp9_);
   double tmp28_ = tmp4_*tmp11_;
   double tmp29_ = tmp22_*tmp13_;
   double tmp30_ = tmp28_+tmp29_;
   double tmp31_ = (tmp30_)*(tmp16_);
   double tmp32_ = tmp27_+tmp31_;
   double tmp33_ = tmp2_*tmp13_;
   double tmp34_ = tmp33_*(tmp19_);
   double tmp35_ = tmp32_+tmp34_;
   double tmp36_ = tmp23_/(tmp35_);
   double tmp37_ = tmp4_*tmp2_;
   double tmp38_ = tmp37_*(tmp9_);
   double tmp39_ = tmp3_*tmp2_;
   double tmp40_ = tmp39_*(tmp16_);
   double tmp41_ = tmp38_+tmp40_;
   double tmp42_ = tmp5_*(tmp19_);
   double tmp43_ = tmp41_+tmp42_;
   double tmp44_ = (tmp43_)*(tmp36_);
   double tmp45_ = mCompCoord[1];
   double tmp46_ = tmp44_+tmp45_;
   double tmp47_ = (tmp46_)-mLocPolyn2_State_1_0;
   double tmp48_ = (tmp47_)/mLocPolyn2_State_0_0;
   double tmp49_ = tmp20_*tmp13_;
   double tmp50_ = tmp21_*tmp10_;
   double tmp51_ = tmp49_+tmp50_;
   double tmp52_ = (tmp51_)*(tmp9_);
   double tmp53_ = tmp4_*tmp13_;
   double tmp54_ = tmp22_*tmp10_;
   double tmp55_ = tmp53_+tmp54_;
   double tmp56_ = (tmp55_)*(tmp16_);
   double tmp57_ = tmp52_+tmp56_;
   double tmp58_ = tmp2_*tmp10_;
   double tmp59_ = tmp58_*(tmp19_);
   double tmp60_ = tmp57_+tmp59_;
   double tmp61_ = (tmp60_)*(tmp36_);
   double tmp62_ = mCompCoord[2];
   double tmp63_ = tmp61_+tmp62_;
   double tmp64_ = (tmp63_)-mLocPolyn2_State_2_0;
   double tmp65_ = (tmp64_)/mLocPolyn2_State_0_0;
   double tmp66_ = mCompCoord[3];
   double tmp67_ = mCompCoord[4];
   double tmp68_ = mCompCoord[5];
   double tmp69_ = (tmp48_)*(tmp65_);
   double tmp70_ = mCompCoord[6];
   double tmp71_ = (tmp65_)*(tmp65_);
   double tmp72_ = (tmp48_)*(tmp48_);

  mVal[0] = ((mLocPolyn2_State_1_0+(((1+tmp66_)*(tmp48_)+tmp67_*(tmp65_))-tmp68_*2*tmp72_+tmp70_*tmp69_+mCompCoord[7]*tmp71_)*mLocPolyn2_State_0_0)-mLocXIm)*mLocScNorm;

  mVal[1] = ((mLocPolyn2_State_2_0+(((1-tmp66_)*(tmp65_)+tmp67_*(tmp48_)+tmp68_*tmp69_)-tmp70_*2*tmp71_+mCompCoord[8]*tmp72_)*mLocPolyn2_State_0_0)-mLocYIm)*mLocScNorm;

}


void cEqAppui_PTInc_M2CPolyn2::ComputeValDeriv()
{
   double tmp0_ = mCompCoord[9];
   double tmp1_ = mCompCoord[10];
   double tmp2_ = cos(tmp1_);
   double tmp3_ = sin(tmp0_);
   double tmp4_ = cos(tmp0_);
   double tmp5_ = sin(tmp1_);
   double tmp6_ = mCompCoord[11];
   double tmp7_ = mCompCoord[15];
   double tmp8_ = mCompCoord[12];
   double tmp9_ = tmp7_-tmp8_;
   double tmp10_ = sin(tmp6_);
   double tmp11_ = -(tmp10_);
   double tmp12_ = -(tmp5_);
   double tmp13_ = cos(tmp6_);
   double tmp14_ = mCompCoord[16];
   double tmp15_ = mCompCoord[13];
   double tmp16_ = tmp14_-tmp15_;
   double tmp17_ = mCompCoord[17];
   double tmp18_ = mCompCoord[14];
   double tmp19_ = tmp17_-tmp18_;
   double tmp20_ = -(tmp3_);
   double tmp21_ = tmp4_*tmp12_;
   double tmp22_ = tmp3_*tmp12_;
   double tmp23_ = mCompCoord[0];
   double tmp24_ = tmp20_*tmp11_;
   double tmp25_ = tmp21_*tmp13_;
   double tmp26_ = tmp24_+tmp25_;
   double tmp27_ = (tmp26_)*(tmp9_);
   double tmp28_ = tmp4_*tmp11_;
   double tmp29_ = tmp22_*tmp13_;
   double tmp30_ = tmp28_+tmp29_;
   double tmp31_ = (tmp30_)*(tmp16_);
   double tmp32_ = tmp27_+tmp31_;
   double tmp33_ = tmp2_*tmp13_;
   double tmp34_ = tmp33_*(tmp19_);
   double tmp35_ = tmp32_+tmp34_;
   double tmp36_ = tmp23_/(tmp35_);
   double tmp37_ = tmp4_*tmp2_;
   double tmp38_ = tmp37_*(tmp9_);
   double tmp39_ = tmp3_*tmp2_;
   double tmp40_ = tmp39_*(tmp16_);
   double tmp41_ = tmp38_+tmp40_;
   double tmp42_ = tmp5_*(tmp19_);
   double tmp43_ = tmp41_+tmp42_;
   double tmp44_ = (tmp43_)*(tmp36_);
   double tmp45_ = mCompCoord[1];
   double tmp46_ = tmp44_+tmp45_;
   double tmp47_ = (tmp46_)-mLocPolyn2_State_1_0;
   double tmp48_ = (tmp47_)/mLocPolyn2_State_0_0;
   double tmp49_ = tmp20_*tmp13_;
   double tmp50_ = tmp21_*tmp10_;
   double tmp51_ = tmp49_+tmp50_;
   double tmp52_ = (tmp51_)*(tmp9_);
   double tmp53_ = tmp4_*tmp13_;
   double tmp54_ = tmp22_*tmp10_;
   double tmp55_ = tmp53_+tmp54_;
   double tmp56_ = (tmp55_)*(tmp16_);
   double tmp57_ = tmp52_+tmp56_;
   double tmp58_ = tmp2_*tmp10_;
   double tmp59_ = tmp58_*(tmp19_);
   double tmp60_ = tmp57_+tmp59_;
   double tmp61_ = (tmp60_)*(tmp36_);
   double tmp62_ = mCompCoord[2];
   double tmp63_ = tmp61_+tmp62_;
   double tmp64_ = (tmp63_)-mLocPolyn2_State_2_0;
   double tmp65_ = (tmp64_)/mLocPolyn2_State_0_0;
   double tmp66_ = mCompCoord[3];
   double tmp67_ = 1+tmp66_;
   double tmp68_ = ElSquare(tmp35_);
   double tmp69_ = (tmp35_)/tmp68_;
   double tmp70_ = ElSquare(mLocPolyn2_State_0_0);
   double tmp71_ = mCompCoord[4];
   double tmp72_ = (tmp69_)*(tmp43_);
   double tmp73_ = tmp72_*mLocPolyn2_State_0_0;
   double tmp74_ = (tmp73_)/tmp70_;
   double tmp75_ = (tmp74_)*(tmp48_);
   double tmp76_ = mCompCoord[5];
   double tmp77_ = tmp76_*2;
   double tmp78_ = (tmp69_)*(tmp60_);
   double tmp79_ = tmp78_*mLocPolyn2_State_0_0;
   double tmp80_ = (tmp79_)/tmp70_;
   double tmp81_ = mCompCoord[6];
   double tmp82_ = (tmp80_)*(tmp65_);
   double tmp83_ = mCompCoord[7];
   double tmp84_ = mLocPolyn2_State_0_0/tmp70_;
   double tmp85_ = (tmp84_)*(tmp48_);
   double tmp86_ = (tmp84_)*(tmp65_);
   double tmp87_ = (tmp48_)*(tmp48_);
   double tmp88_ = (tmp48_)*(tmp65_);
   double tmp89_ = (tmp65_)*(tmp65_);
   double tmp90_ = -(1);
   double tmp91_ = tmp90_*tmp3_;
   double tmp92_ = -(tmp4_);
   double tmp93_ = tmp91_*tmp12_;
   double tmp94_ = tmp92_*tmp11_;
   double tmp95_ = tmp93_*tmp13_;
   double tmp96_ = tmp94_+tmp95_;
   double tmp97_ = (tmp96_)*(tmp9_);
   double tmp98_ = tmp91_*tmp11_;
   double tmp99_ = tmp98_+tmp25_;
   double tmp100_ = (tmp99_)*(tmp16_);
   double tmp101_ = tmp97_+tmp100_;
   double tmp102_ = tmp23_*(tmp101_);
   double tmp103_ = -(tmp102_);
   double tmp104_ = tmp103_/tmp68_;
   double tmp105_ = tmp91_*tmp2_;
   double tmp106_ = tmp105_*(tmp9_);
   double tmp107_ = tmp37_*(tmp16_);
   double tmp108_ = tmp106_+tmp107_;
   double tmp109_ = (tmp108_)*(tmp36_);
   double tmp110_ = (tmp104_)*(tmp43_);
   double tmp111_ = tmp109_+tmp110_;
   double tmp112_ = (tmp111_)*mLocPolyn2_State_0_0;
   double tmp113_ = (tmp112_)/tmp70_;
   double tmp114_ = (tmp113_)*(tmp48_);
   double tmp115_ = tmp92_*tmp13_;
   double tmp116_ = tmp93_*tmp10_;
   double tmp117_ = tmp115_+tmp116_;
   double tmp118_ = (tmp117_)*(tmp9_);
   double tmp119_ = tmp91_*tmp13_;
   double tmp120_ = tmp119_+tmp50_;
   double tmp121_ = (tmp120_)*(tmp16_);
   double tmp122_ = tmp118_+tmp121_;
   double tmp123_ = (tmp122_)*(tmp36_);
   double tmp124_ = (tmp104_)*(tmp60_);
   double tmp125_ = tmp123_+tmp124_;
   double tmp126_ = (tmp125_)*mLocPolyn2_State_0_0;
   double tmp127_ = (tmp126_)/tmp70_;
   double tmp128_ = (tmp127_)*(tmp65_);
   double tmp129_ = tmp90_*tmp5_;
   double tmp130_ = -(tmp2_);
   double tmp131_ = tmp130_*tmp4_;
   double tmp132_ = tmp130_*tmp3_;
   double tmp133_ = tmp131_*tmp13_;
   double tmp134_ = tmp133_*(tmp9_);
   double tmp135_ = tmp132_*tmp13_;
   double tmp136_ = tmp135_*(tmp16_);
   double tmp137_ = tmp134_+tmp136_;
   double tmp138_ = tmp129_*tmp13_;
   double tmp139_ = tmp138_*(tmp19_);
   double tmp140_ = tmp137_+tmp139_;
   double tmp141_ = tmp23_*(tmp140_);
   double tmp142_ = -(tmp141_);
   double tmp143_ = tmp142_/tmp68_;
   double tmp144_ = tmp129_*tmp4_;
   double tmp145_ = tmp144_*(tmp9_);
   double tmp146_ = tmp129_*tmp3_;
   double tmp147_ = tmp146_*(tmp16_);
   double tmp148_ = tmp145_+tmp147_;
   double tmp149_ = tmp2_*(tmp19_);
   double tmp150_ = tmp148_+tmp149_;
   double tmp151_ = (tmp150_)*(tmp36_);
   double tmp152_ = (tmp143_)*(tmp43_);
   double tmp153_ = tmp151_+tmp152_;
   double tmp154_ = (tmp153_)*mLocPolyn2_State_0_0;
   double tmp155_ = (tmp154_)/tmp70_;
   double tmp156_ = (tmp155_)*(tmp48_);
   double tmp157_ = tmp131_*tmp10_;
   double tmp158_ = tmp157_*(tmp9_);
   double tmp159_ = tmp132_*tmp10_;
   double tmp160_ = tmp159_*(tmp16_);
   double tmp161_ = tmp158_+tmp160_;
   double tmp162_ = tmp129_*tmp10_;
   double tmp163_ = tmp162_*(tmp19_);
   double tmp164_ = tmp161_+tmp163_;
   double tmp165_ = (tmp164_)*(tmp36_);
   double tmp166_ = (tmp143_)*(tmp60_);
   double tmp167_ = tmp165_+tmp166_;
   double tmp168_ = (tmp167_)*mLocPolyn2_State_0_0;
   double tmp169_ = (tmp168_)/tmp70_;
   double tmp170_ = (tmp169_)*(tmp65_);
   double tmp171_ = -(tmp13_);
   double tmp172_ = tmp90_*tmp10_;
   double tmp173_ = tmp171_*tmp20_;
   double tmp174_ = tmp172_*tmp21_;
   double tmp175_ = tmp173_+tmp174_;
   double tmp176_ = (tmp175_)*(tmp9_);
   double tmp177_ = tmp171_*tmp4_;
   double tmp178_ = tmp172_*tmp22_;
   double tmp179_ = tmp177_+tmp178_;
   double tmp180_ = (tmp179_)*(tmp16_);
   double tmp181_ = tmp176_+tmp180_;
   double tmp182_ = tmp172_*tmp2_;
   double tmp183_ = tmp182_*(tmp19_);
   double tmp184_ = tmp181_+tmp183_;
   double tmp185_ = tmp23_*(tmp184_);
   double tmp186_ = -(tmp185_);
   double tmp187_ = tmp186_/tmp68_;
   double tmp188_ = (tmp187_)*(tmp43_);
   double tmp189_ = tmp188_*mLocPolyn2_State_0_0;
   double tmp190_ = (tmp189_)/tmp70_;
   double tmp191_ = (tmp190_)*(tmp48_);
   double tmp192_ = tmp172_*tmp20_;
   double tmp193_ = tmp13_*tmp21_;
   double tmp194_ = tmp192_+tmp193_;
   double tmp195_ = (tmp194_)*(tmp9_);
   double tmp196_ = tmp172_*tmp4_;
   double tmp197_ = tmp13_*tmp22_;
   double tmp198_ = tmp196_+tmp197_;
   double tmp199_ = (tmp198_)*(tmp16_);
   double tmp200_ = tmp195_+tmp199_;
   double tmp201_ = tmp13_*tmp2_;
   double tmp202_ = tmp201_*(tmp19_);
   double tmp203_ = tmp200_+tmp202_;
   double tmp204_ = (tmp203_)*(tmp36_);
   double tmp205_ = (tmp187_)*(tmp60_);
   double tmp206_ = tmp204_+tmp205_;
   double tmp207_ = (tmp206_)*mLocPolyn2_State_0_0;
   double tmp208_ = (tmp207_)/tmp70_;
   double tmp209_ = (tmp208_)*(tmp65_);
   double tmp210_ = tmp90_*(tmp26_);
   double tmp211_ = tmp23_*tmp210_;
   double tmp212_ = -(tmp211_);
   double tmp213_ = tmp212_/tmp68_;
   double tmp214_ = tmp90_*tmp37_;
   double tmp215_ = tmp214_*(tmp36_);
   double tmp216_ = (tmp213_)*(tmp43_);
   double tmp217_ = tmp215_+tmp216_;
   double tmp218_ = (tmp217_)*mLocPolyn2_State_0_0;
   double tmp219_ = (tmp218_)/tmp70_;
   double tmp220_ = (tmp219_)*(tmp48_);
   double tmp221_ = tmp90_*(tmp51_);
   double tmp222_ = tmp221_*(tmp36_);
   double tmp223_ = (tmp213_)*(tmp60_);
   double tmp224_ = tmp222_+tmp223_;
   double tmp225_ = (tmp224_)*mLocPolyn2_State_0_0;
   double tmp226_ = (tmp225_)/tmp70_;
   double tmp227_ = (tmp226_)*(tmp65_);
   double tmp228_ = tmp90_*(tmp30_);
   double tmp229_ = tmp23_*tmp228_;
   double tmp230_ = -(tmp229_);
   double tmp231_ = tmp230_/tmp68_;
   double tmp232_ = tmp90_*tmp39_;
   double tmp233_ = tmp232_*(tmp36_);
   double tmp234_ = (tmp231_)*(tmp43_);
   double tmp235_ = tmp233_+tmp234_;
   double tmp236_ = (tmp235_)*mLocPolyn2_State_0_0;
   double tmp237_ = (tmp236_)/tmp70_;
   double tmp238_ = (tmp237_)*(tmp48_);
   double tmp239_ = tmp90_*(tmp55_);
   double tmp240_ = tmp239_*(tmp36_);
   double tmp241_ = (tmp231_)*(tmp60_);
   double tmp242_ = tmp240_+tmp241_;
   double tmp243_ = (tmp242_)*mLocPolyn2_State_0_0;
   double tmp244_ = (tmp243_)/tmp70_;
   double tmp245_ = (tmp244_)*(tmp65_);
   double tmp246_ = tmp90_*tmp33_;
   double tmp247_ = tmp23_*tmp246_;
   double tmp248_ = -(tmp247_);
   double tmp249_ = tmp248_/tmp68_;
   double tmp250_ = tmp129_*(tmp36_);
   double tmp251_ = (tmp249_)*(tmp43_);
   double tmp252_ = tmp250_+tmp251_;
   double tmp253_ = (tmp252_)*mLocPolyn2_State_0_0;
   double tmp254_ = (tmp253_)/tmp70_;
   double tmp255_ = (tmp254_)*(tmp48_);
   double tmp256_ = tmp90_*tmp58_;
   double tmp257_ = tmp256_*(tmp36_);
   double tmp258_ = (tmp249_)*(tmp60_);
   double tmp259_ = tmp257_+tmp258_;
   double tmp260_ = (tmp259_)*mLocPolyn2_State_0_0;
   double tmp261_ = (tmp260_)/tmp70_;
   double tmp262_ = (tmp261_)*(tmp65_);
   double tmp263_ = tmp23_*(tmp26_);
   double tmp264_ = -(tmp263_);
   double tmp265_ = tmp264_/tmp68_;
   double tmp266_ = tmp37_*(tmp36_);
   double tmp267_ = (tmp265_)*(tmp43_);
   double tmp268_ = tmp266_+tmp267_;
   double tmp269_ = (tmp268_)*mLocPolyn2_State_0_0;
   double tmp270_ = (tmp269_)/tmp70_;
   double tmp271_ = (tmp270_)*(tmp48_);
   double tmp272_ = (tmp51_)*(tmp36_);
   double tmp273_ = (tmp265_)*(tmp60_);
   double tmp274_ = tmp272_+tmp273_;
   double tmp275_ = (tmp274_)*mLocPolyn2_State_0_0;
   double tmp276_ = (tmp275_)/tmp70_;
   double tmp277_ = (tmp276_)*(tmp65_);
   double tmp278_ = tmp23_*(tmp30_);
   double tmp279_ = -(tmp278_);
   double tmp280_ = tmp279_/tmp68_;
   double tmp281_ = tmp39_*(tmp36_);
   double tmp282_ = (tmp280_)*(tmp43_);
   double tmp283_ = tmp281_+tmp282_;
   double tmp284_ = (tmp283_)*mLocPolyn2_State_0_0;
   double tmp285_ = (tmp284_)/tmp70_;
   double tmp286_ = (tmp285_)*(tmp48_);
   double tmp287_ = (tmp55_)*(tmp36_);
   double tmp288_ = (tmp280_)*(tmp60_);
   double tmp289_ = tmp287_+tmp288_;
   double tmp290_ = (tmp289_)*mLocPolyn2_State_0_0;
   double tmp291_ = (tmp290_)/tmp70_;
   double tmp292_ = (tmp291_)*(tmp65_);
   double tmp293_ = tmp23_*tmp33_;
   double tmp294_ = -(tmp293_);
   double tmp295_ = tmp294_/tmp68_;
   double tmp296_ = tmp5_*(tmp36_);
   double tmp297_ = (tmp295_)*(tmp43_);
   double tmp298_ = tmp296_+tmp297_;
   double tmp299_ = (tmp298_)*mLocPolyn2_State_0_0;
   double tmp300_ = (tmp299_)/tmp70_;
   double tmp301_ = (tmp300_)*(tmp48_);
   double tmp302_ = tmp58_*(tmp36_);
   double tmp303_ = (tmp295_)*(tmp60_);
   double tmp304_ = tmp302_+tmp303_;
   double tmp305_ = (tmp304_)*mLocPolyn2_State_0_0;
   double tmp306_ = (tmp305_)/tmp70_;
   double tmp307_ = (tmp306_)*(tmp65_);
   double tmp308_ = 1-tmp66_;
   double tmp309_ = (tmp74_)*(tmp65_);
   double tmp310_ = (tmp80_)*(tmp48_);
   double tmp311_ = tmp309_+tmp310_;
   double tmp312_ = tmp82_+tmp82_;
   double tmp313_ = tmp81_*2;
   double tmp314_ = tmp75_+tmp75_;
   double tmp315_ = mCompCoord[8];
   double tmp316_ = (tmp84_)*tmp71_;
   double tmp317_ = tmp85_+tmp85_;
   double tmp318_ = tmp86_+tmp86_;
   double tmp319_ = (tmp48_)*mLocPolyn2_State_0_0;
   double tmp320_ = tmp319_*mLocScNorm;
   double tmp321_ = tmp88_*mLocPolyn2_State_0_0;
   double tmp322_ = tmp321_*mLocScNorm;
   double tmp323_ = (tmp113_)*(tmp65_);
   double tmp324_ = (tmp127_)*(tmp48_);
   double tmp325_ = tmp323_+tmp324_;
   double tmp326_ = tmp128_+tmp128_;
   double tmp327_ = tmp114_+tmp114_;
   double tmp328_ = (tmp155_)*(tmp65_);
   double tmp329_ = (tmp169_)*(tmp48_);
   double tmp330_ = tmp328_+tmp329_;
   double tmp331_ = tmp170_+tmp170_;
   double tmp332_ = tmp156_+tmp156_;
   double tmp333_ = (tmp190_)*(tmp65_);
   double tmp334_ = (tmp208_)*(tmp48_);
   double tmp335_ = tmp333_+tmp334_;
   double tmp336_ = tmp209_+tmp209_;
   double tmp337_ = tmp191_+tmp191_;
   double tmp338_ = (tmp219_)*(tmp65_);
   double tmp339_ = (tmp226_)*(tmp48_);
   double tmp340_ = tmp338_+tmp339_;
   double tmp341_ = tmp227_+tmp227_;
   double tmp342_ = tmp220_+tmp220_;
   double tmp343_ = (tmp237_)*(tmp65_);
   double tmp344_ = (tmp244_)*(tmp48_);
   double tmp345_ = tmp343_+tmp344_;
   double tmp346_ = tmp245_+tmp245_;
   double tmp347_ = tmp238_+tmp238_;
   double tmp348_ = (tmp254_)*(tmp65_);
   double tmp349_ = (tmp261_)*(tmp48_);
   double tmp350_ = tmp348_+tmp349_;
   double tmp351_ = tmp262_+tmp262_;
   double tmp352_ = tmp255_+tmp255_;
   double tmp353_ = (tmp270_)*(tmp65_);
   double tmp354_ = (tmp276_)*(tmp48_);
   double tmp355_ = tmp353_+tmp354_;
   double tmp356_ = tmp277_+tmp277_;
   double tmp357_ = tmp271_+tmp271_;
   double tmp358_ = (tmp285_)*(tmp65_);
   double tmp359_ = (tmp291_)*(tmp48_);
   double tmp360_ = tmp358_+tmp359_;
   double tmp361_ = tmp292_+tmp292_;
   double tmp362_ = tmp286_+tmp286_;
   double tmp363_ = (tmp300_)*(tmp65_);
   double tmp364_ = (tmp306_)*(tmp48_);
   double tmp365_ = tmp363_+tmp364_;
   double tmp366_ = tmp307_+tmp307_;
   double tmp367_ = tmp301_+tmp301_;

  mVal[0] = ((mLocPolyn2_State_1_0+(((tmp67_)*(tmp48_)+tmp71_*(tmp65_))-tmp77_*tmp87_+tmp81_*tmp88_+tmp83_*tmp89_)*mLocPolyn2_State_0_0)-mLocXIm)*mLocScNorm;

  mCompDer[0][0] = (((tmp74_)*(tmp67_)+(tmp80_)*tmp71_)-(tmp314_)*tmp77_+(tmp311_)*tmp81_+(tmp312_)*tmp83_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][1] = ((tmp84_)*(tmp67_)-(tmp317_)*tmp77_+tmp86_*tmp81_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][2] = (tmp316_+tmp85_*tmp81_+(tmp318_)*tmp83_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][3] = tmp320_;
  mCompDer[0][4] = (tmp65_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][5] = -(2*tmp87_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][6] = tmp322_;
  mCompDer[0][7] = tmp89_*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][8] = 0;
  mCompDer[0][9] = (((tmp113_)*(tmp67_)+(tmp127_)*tmp71_)-(tmp327_)*tmp77_+(tmp325_)*tmp81_+(tmp326_)*tmp83_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][10] = (((tmp155_)*(tmp67_)+(tmp169_)*tmp71_)-(tmp332_)*tmp77_+(tmp330_)*tmp81_+(tmp331_)*tmp83_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][11] = (((tmp190_)*(tmp67_)+(tmp208_)*tmp71_)-(tmp337_)*tmp77_+(tmp335_)*tmp81_+(tmp336_)*tmp83_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][12] = (((tmp219_)*(tmp67_)+(tmp226_)*tmp71_)-(tmp342_)*tmp77_+(tmp340_)*tmp81_+(tmp341_)*tmp83_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][13] = (((tmp237_)*(tmp67_)+(tmp244_)*tmp71_)-(tmp347_)*tmp77_+(tmp345_)*tmp81_+(tmp346_)*tmp83_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][14] = (((tmp254_)*(tmp67_)+(tmp261_)*tmp71_)-(tmp352_)*tmp77_+(tmp350_)*tmp81_+(tmp351_)*tmp83_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][15] = (((tmp270_)*(tmp67_)+(tmp276_)*tmp71_)-(tmp357_)*tmp77_+(tmp355_)*tmp81_+(tmp356_)*tmp83_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][16] = (((tmp285_)*(tmp67_)+(tmp291_)*tmp71_)-(tmp362_)*tmp77_+(tmp360_)*tmp81_+(tmp361_)*tmp83_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[0][17] = (((tmp300_)*(tmp67_)+(tmp306_)*tmp71_)-(tmp367_)*tmp77_+(tmp365_)*tmp81_+(tmp366_)*tmp83_)*mLocPolyn2_State_0_0*mLocScNorm;
  mVal[1] = ((mLocPolyn2_State_2_0+(((tmp308_)*(tmp65_)+tmp71_*(tmp48_)+tmp76_*tmp88_)-tmp313_*tmp89_+tmp315_*tmp87_)*mLocPolyn2_State_0_0)-mLocYIm)*mLocScNorm;

  mCompDer[1][0] = (((tmp80_)*(tmp308_)+(tmp74_)*tmp71_+(tmp311_)*tmp76_)-(tmp312_)*tmp313_+(tmp314_)*tmp315_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][1] = (tmp316_+tmp86_*tmp76_+(tmp317_)*tmp315_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][2] = (((tmp84_)*(tmp308_)+tmp85_*tmp76_)-(tmp318_)*tmp313_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][3] = tmp90_*(tmp65_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][4] = tmp320_;
  mCompDer[1][5] = tmp322_;
  mCompDer[1][6] = -(2*tmp89_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][7] = 0;
  mCompDer[1][8] = tmp87_*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][9] = (((tmp127_)*(tmp308_)+(tmp113_)*tmp71_+(tmp325_)*tmp76_)-(tmp326_)*tmp313_+(tmp327_)*tmp315_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][10] = (((tmp169_)*(tmp308_)+(tmp155_)*tmp71_+(tmp330_)*tmp76_)-(tmp331_)*tmp313_+(tmp332_)*tmp315_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][11] = (((tmp208_)*(tmp308_)+(tmp190_)*tmp71_+(tmp335_)*tmp76_)-(tmp336_)*tmp313_+(tmp337_)*tmp315_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][12] = (((tmp226_)*(tmp308_)+(tmp219_)*tmp71_+(tmp340_)*tmp76_)-(tmp341_)*tmp313_+(tmp342_)*tmp315_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][13] = (((tmp244_)*(tmp308_)+(tmp237_)*tmp71_+(tmp345_)*tmp76_)-(tmp346_)*tmp313_+(tmp347_)*tmp315_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][14] = (((tmp261_)*(tmp308_)+(tmp254_)*tmp71_+(tmp350_)*tmp76_)-(tmp351_)*tmp313_+(tmp352_)*tmp315_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][15] = (((tmp276_)*(tmp308_)+(tmp270_)*tmp71_+(tmp355_)*tmp76_)-(tmp356_)*tmp313_+(tmp357_)*tmp315_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][16] = (((tmp291_)*(tmp308_)+(tmp285_)*tmp71_+(tmp360_)*tmp76_)-(tmp361_)*tmp313_+(tmp362_)*tmp315_)*mLocPolyn2_State_0_0*mLocScNorm;
  mCompDer[1][17] = (((tmp306_)*(tmp308_)+(tmp300_)*tmp71_+(tmp365_)*tmp76_)-(tmp366_)*tmp313_+(tmp367_)*tmp315_)*mLocPolyn2_State_0_0*mLocScNorm;
}


void cEqAppui_PTInc_M2CPolyn2::ComputeValDerivHessian()
{
  ELISE_ASSERT(false,"Foncteur cEqAppui_PTInc_M2CPolyn2 Has no Der Sec");
}

void cEqAppui_PTInc_M2CPolyn2::SetPolyn2_State_0_0(double aVal){ mLocPolyn2_State_0_0 = aVal;}
void cEqAppui_PTInc_M2CPolyn2::SetPolyn2_State_1_0(double aVal){ mLocPolyn2_State_1_0 = aVal;}
void cEqAppui_PTInc_M2CPolyn2::SetPolyn2_State_2_0(double aVal){ mLocPolyn2_State_2_0 = aVal;}
void cEqAppui_PTInc_M2CPolyn2::SetScNorm(double aVal){ mLocScNorm = aVal;}
void cEqAppui_PTInc_M2CPolyn2::SetXIm(double aVal){ mLocXIm = aVal;}
void cEqAppui_PTInc_M2CPolyn2::SetYIm(double aVal){ mLocYIm = aVal;}



double * cEqAppui_PTInc_M2CPolyn2::AdrVarLocFromString(const std::string & aName)
{
   if (aName == "Polyn2_State_0_0") return & mLocPolyn2_State_0_0;
   if (aName == "Polyn2_State_1_0") return & mLocPolyn2_State_1_0;
   if (aName == "Polyn2_State_2_0") return & mLocPolyn2_State_2_0;
   if (aName == "ScNorm") return & mLocScNorm;
   if (aName == "XIm") return & mLocXIm;
   if (aName == "YIm") return & mLocYIm;
   return 0;
}


cElCompiledFonc::cAutoAddEntry cEqAppui_PTInc_M2CPolyn2::mTheAuto("cEqAppui_PTInc_M2CPolyn2",cEqAppui_PTInc_M2CPolyn2::Alloc);


cElCompiledFonc *  cEqAppui_PTInc_M2CPolyn2::Alloc()
{  return new cEqAppui_PTInc_M2CPolyn2();
}


