#include "cMMVII_Appli.h"
#include "MMVII_Geom3D.h"
#include "MMVII_Sensor.h"


namespace MMVII
{
/* =============================================== */
/*                                                 */
/*                 cAppliTestSensor                */
/*                                                 */
/* =============================================== */

/**  An application for  testing the accuracy of a sensor : 
        - consistency of direct/inverse model
        - (optionnaly) comparison with a ground truth
 */

class cAppliTestSensor : public cMMVII_Appli
{
     public :
        cAppliTestSensor(const std::vector<std::string> & aVArgs,const cSpecMMVII_Appli & aSpec);
     private :
        int Exe() override;
        cCollecSpecArg2007 & ArgObl(cCollecSpecArg2007 & anArgObl) override ;
        cCollecSpecArg2007 & ArgOpt(cCollecSpecArg2007 & anArgOpt) override ;
	std::vector<std::string>  Samples() const override;


        void  DoOneImage(const std::string & aNameIm);

	///  Test that the accuracy of ground truth, i.e Proj(P3) = P2
        void TestGroundTruth(const  cSensorImage & aSI) const;
	///  Test coherence of Direct/Inverse model, i.e Id = Dir o Inv = Inv o Dir
        void TestCoherenceDirInv(const  cSensorImage & aSI) const;
	///  Export the synthetic 3d-2d measure
        void ExportMeasures(const  cSensorImage & aSI) const;
	///  Test coherence of Graddient  Grad/Dif finite ~ Grad analytic
        void TestCoherenceGrad(const  cSensorImage & aSI) const;


        cPhotogrammetricProject  mPhProj;
        std::string              mPatImage;
        bool                     mShowDetail;

	std::vector<int>         mSzGenerate;
	bool                     mTestCorDirInv;
        cPt2dr                   mDefIntDepth;  // Defautlt interval of depth if sensor has depth functs
        bool                     mDoTestGrad;

        cPt2dr                   mCurIntZD ;   // curent interval of Z or Depth
	bool                     mCurWDepth;   // does current sensor use depth or Z
        cSet2D3D                 mCurS23;      // current set of "3d-2d" correspondance
};

std::vector<std::string>  cAppliTestSensor::Samples() const
{
   return {
              "MMVII TestSensor SPOT_1B.tif SPOT_Init InPointsMeasure=XingB"
	};
}

cAppliTestSensor::cAppliTestSensor(const std::vector<std::string> & aVArgs,const cSpecMMVII_Appli & aSpec) :
    cMMVII_Appli    (aVArgs,aSpec),
    mPhProj         (*this),
    mShowDetail     (false),
    mSzGenerate     {15,3},
    mTestCorDirInv  (true),
    mDefIntDepth    (1.0,2.0),
    mDoTestGrad     (false)
{
}

cCollecSpecArg2007 & cAppliTestSensor::ArgObl(cCollecSpecArg2007 & anArgObl) 
{
      return    anArgObl
             << Arg2007(mPatImage,"Name of input Image", {eTA2007::FileDirProj,{eTA2007::MPatFile,"0"}})
             << mPhProj.DPOrient().ArgDirInMand()
      ;
}

cCollecSpecArg2007 & cAppliTestSensor::ArgOpt(cCollecSpecArg2007 & anArgOpt)
{
    return anArgOpt
               << mPhProj.DPPointsMeasures().ArgDirInOpt()
               << mPhProj.DPPointsMeasures().ArgDirOutOpt()
               << AOpt2007(mShowDetail,"ShowD","Show detail",{eTA2007::HDV})
               << AOpt2007(mTestCorDirInv,"TestCDI","Test coherence of direct/invers model",{eTA2007::HDV})
               << AOpt2007(mSzGenerate,"SzGen","Sz gen",{eTA2007::HDV,{eTA2007::ISizeV,"[2,2]"}})
               << AOpt2007(mDoTestGrad,"TestGrad","Test coherence anlytic grad/finit diff (if different)",{eTA2007::HDV})
            ;
}

void cAppliTestSensor::TestGroundTruth(const  cSensorImage & aSI) const
{
    // Load mesure from standard MMVII project
    cSetMesImGCP aSetMes;
    mPhProj.LoadGCP(aSetMes);
    mPhProj.LoadIm(aSetMes,aSI.NameImage());
    cSet2D3D aSetM23;
    aSetMes.ExtractMes1Im(aSetM23,aSI.NameImage());

    cStdStatRes  aStCheckIm;  //  Statistic of reproj errorr

    for (const auto & aPair : aSetM23.Pairs()) // parse all pair to accumulate stat of errors
    {
         cPt3dr  aPGr = aPair.mP3;
         cPt2dr  aPIm = aSI.Ground2Image(aPGr);
	 tREAL8 aDifIm = Norm2(aPIm-aPair.mP2);
	 aStCheckIm.Add(aDifIm);

         if (mShowDetail) 
         {
             StdOut()  << "ImGT=" <<  aDifIm << std::endl;

         }
    }
    StdOut() << "  ==============  Accuracy / Ground trurh =============== " << std::endl;
    StdOut()  << "    Avg=" <<  aStCheckIm.Avg() << ",  Worst=" << aStCheckIm.Max() << "\n";
}

void cAppliTestSensor::ExportMeasures(const  cSensorImage & aSI) const
{
    cSetMesGCP      aSet3D(aSI.NameImage());
    cSetMesPtOf1Im  aSet2D(aSI.NameImage());
    int aNb=0;
    for (const auto & aPair : mCurS23.Pairs())
    {
        std::string aName = "Pt_"+ ToStr(aNb) + "-" + aSI.NameImage();
        aNb++;
        aSet2D.AddMeasure(cMesIm1Pt(aSI.Ground2Image(aPair.mP3),aName,1.0));
        aSet3D.AddMeasure(cMes1GCP(aPair.mP3,aName,1.0));
    }
    mPhProj.SaveGCP(aSet3D);
    mPhProj.SaveMeasureIm(aSet2D);
}

void cAppliTestSensor::TestCoherenceGrad(const  cSensorImage & aSI) const
{
    for (const auto & aPair : mCurS23.Pairs())
    {
	tProjImAndGrad  aP1 = aSI.DiffGround2Im (aPair.mP3);
	tProjImAndGrad  aP2 = aSI.DiffG2IByFiniteDiff (aPair.mP3);

	StdOut() << "GGGG " <<  aP1.mPIJ - aP2.mPIJ << aP1.mGradI - aP2.mGradI << aP1.mGradJ - aP2.mGradJ << "\n";

        // DiffGround2Im DiffG2IByFiniteDiff
    }
}

void cAppliTestSensor::TestCoherenceDirInv(const  cSensorImage & aSI) const
{
     
     cStdStatRes  aStConsistIm;  // stat for image consit  Proj( Proj-1(PIm)) ?= PIm
     cStdStatRes  aStConsistGr;  // stat for ground consist  Proj-1 (Proj(Ground)) ?= Ground

     for (const auto & aPair : mCurS23.Pairs())
     {
         cPt3dr  aPGr = aPair.mP3;
         cPt3dr  aPIm (aPair.mP2.x(),aPair.mP2.y(),aPGr.z());

         cPt3dr  aPIm2 ;
         cPt3dr  aPGr2 ;
	
	 if (mCurWDepth)
	 {
	    aPIm2 = aSI.Ground2ImageAndDepth(aSI.ImageAndDepth2Ground(aPIm));
	    aPGr2 = aSI.ImageAndDepth2Ground(aSI.Ground2ImageAndDepth(aPGr));
	 }
	 else
	 {
	    aPIm2 = aSI.Ground2ImageAndZ(aSI.ImageAndZ2Ground(aPIm));
	    aPGr2 = aSI.ImageAndZ2Ground(aSI.Ground2ImageAndZ(aPGr));
	 }
	 tREAL8 aDifIm = Norm2(aPIm-aPIm2);
	 aStConsistIm.Add(aDifIm);

	 tREAL8 aDifGr = Norm2(aPGr-aPGr2);
	 aStConsistGr.Add(aDifGr);
	    
     }

     StdOut() << "  ==============  Consistencies Direct/Inverse =============== " << std::endl;

     StdOut() << "     * Image :  Avg=" <<   aStConsistIm.Avg() 
	      <<  ", Worst=" << aStConsistIm.Max()  
	      <<  ", Med=" << aStConsistIm.ErrAtProp(0.5)  
              << std::endl;

     StdOut() << "     * Ground:  Avg=" <<   aStConsistGr.Avg() 
	      <<  ", Worst=" << aStConsistGr.Max()  
	      <<  ", Med=" << aStConsistGr.ErrAtProp(0.5)  
              << std::endl;
}

void  cAppliTestSensor::DoOneImage(const std::string & aNameIm)
{
     cSensorImage *  aSI =  mPhProj.LoadSensor(FileOfPath(aNameIm,false /* Ok Not Exist*/),false /* Not SVP*/);

     //  Compute a set of synthetic  correspondance 3d-2d
     mCurWDepth = ! aSI->HasIntervalZ();  // do we use Im&Depth or Image&Z
     mCurIntZD = mDefIntDepth;
     if (mCurWDepth)
     {  // if depth probably doent matter which one is used
     }
     else
     {
        mCurIntZD = aSI->GetIntervalZ(); // at least with RPC, need to get validity interval
     }
     int mNbByDim = mSzGenerate.at(0);
     int mNbDepth = mSzGenerate.at(1);
     mCurS23 = aSI->SyntheticsCorresp3D2D(mNbByDim,mNbDepth,mCurIntZD.x(),mCurIntZD.y(),mCurWDepth);

    // cSensorImage *  aSI =  AllocAutoSensorFromFile(mNameRPC,mNameImage);

    if (mPhProj.DPPointsMeasures().DirInIsInit())
       TestGroundTruth(*aSI);

    if (mTestCorDirInv)
       TestCoherenceDirInv(*aSI);

    if (mPhProj.DPPointsMeasures().DirOutIsInit())
       ExportMeasures(*aSI);

    if (mDoTestGrad)
        TestCoherenceGrad(*aSI);

    StdOut() << "NAMEORI=[" << aSI->NameOriStd()  << "]\n";

    delete aSI;
}



int cAppliTestSensor::Exe()
{
    mPhProj.FinishInit();
    /*  Version "à la main" on parcourt les explicitement les images
    for (const auto & aNameIm :  VectMainSet(0))
    {
         DoOneImage(aNameIm);
    }
    */

    if (RunMultiSet(0,0))
    {
       return ResultMultiSet();
    }
    DoOneImage(mPatImage);
    return EXIT_SUCCESS;
}


tMMVII_UnikPApli Alloc_TestImportSensors(const std::vector<std::string> &  aVArgs,const cSpecMMVII_Appli & aSpec)
{
      return tMMVII_UnikPApli(new cAppliTestSensor(aVArgs,aSpec));
}


cSpecMMVII_Appli  TheSpecTestSensor
(
     "TestSensor",
      Alloc_TestImportSensors,
      "Test orientation functions of a sensor : coherence Direct/Inverse, ground truth 2D/3D correspondance, generate 3d-2d corresp",
      {eApF::Ori},
      {eApDT::Ori,eApDT::GCP},
      {eApDT::Console},
      __FILE__
);

};
