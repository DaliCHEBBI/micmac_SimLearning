#include "MMVII_2Include_Serial_Tpl.h"
#include "MMVII_PCSens.h"
#include "MMVII_Geom2D.h"


/**
   \file cSensorCamPC.cpp  

   \brief file for implementing class sensor for perspective central
*/


namespace MMVII
{

cPoseWithUK::cPoseWithUK(const tPoseR & aPose) :
      mPose (aPose),
      mOmega (0.0,0.0,0.0)
{
}

cPoseWithUK::cPoseWithUK() :
	cPoseWithUK(tPoseR())
{
}


void cPoseWithUK::SetPose(const tPoseR & aPose)
{
	mPose = aPose;
}

const tPoseR &   cPoseWithUK::Pose()   const  {return mPose;}
tPoseR &   cPoseWithUK::Pose()   {return mPose;}
const cPt3dr &   cPoseWithUK::Center() const {return mPose.Tr();}
cPt3dr &  cPoseWithUK::Center()  {return mPose.Tr();}
cPt3dr  cPoseWithUK::AxeI()   const {return mPose.Rot().AxeI();}
cPt3dr  cPoseWithUK::AxeJ()   const {return mPose.Rot().AxeJ();}
cPt3dr  cPoseWithUK::AxeK()   const {return mPose.Rot().AxeK();}
const cPt3dr &   cPoseWithUK::Tr() const {return mPose.Tr();}
cPt3dr &  cPoseWithUK::Tr()  {return mPose.Tr();}


cPt3dr &  cPoseWithUK::Omega()  {return mOmega;}
const cPt3dr &  cPoseWithUK::Omega() const {return mOmega;}


/*   Let R be the rotation of pose  P=(C,P= : Cam-> Word, what is optimized in colinearity for a ground point G
 *   is Word->Cam  :
 *
 *          tR(G-C)
 *
 * So the optimal rotation R' with get satisfy the equation :
 *
 *          (1+^W) tR0 =tR'   
 *
 * The we have the formula :
 *
 *          --->   R'=R0 t(1+^W)
 *
 *  And note that for axiators :
 *
 *       t Axiator(W) = Axiator(-W)
 *
 */

void cPoseWithUK::OnUpdate()
{
	//  used above formula to modify  rotation
     mPose.SetRotation(mPose.Rot() * cRotation3D<tREAL8>::RotFromAxiator(-mOmega));
        // now this have modify rotation, the "delta" is void :
     mOmega = cPt3dr(0,0,0);
}

void  cPoseWithUK::GetAdrInfoParam(cGetAdrInfoParam<tREAL8> & aGAIP)
{
   aGAIP.TestParam(this, &( mPose.Tr().x()),"Cx");
   aGAIP.TestParam(this, &( mPose.Tr().y()),"Cy");
   aGAIP.TestParam(this, &( mPose.Tr().z()),"Cz");

   aGAIP.TestParam(this, &( mOmega.x())    ,"Wx");
   aGAIP.TestParam(this, &( mOmega.y())    ,"Wy");
   aGAIP.TestParam(this, &( mOmega.z())    ,"Wz");
}

void cPoseWithUK::PutUknowsInSetInterval(cSetInterUK_MultipeObj<tREAL8> * aSetInterv) 
{
    aSetInterv->AddOneInterv(mPose.Tr());
    aSetInterv->AddOneInterv(mOmega);
}

void cPoseWithUK::PutUknowsInSetInterval()
{
    PutUknowsInSetInterval(mSetInterv);
}

void AddData(const  cAuxAr2007 & anAux,cPoseWithUK & aPUK)
{
    MMVII::AddData(anAux,aPUK.Pose());

    if (anAux.Input())
    {
	 aPUK.Omega() = cPt3dr(0,0,0);
    }
    else
    {
         MMVII_INTERNAL_ASSERT_tiny(IsNull(aPUK.Omega()),"Write unknown rot with omega!=0");
    }
}

void cPoseWithUK::PushObs(std::vector<double> & aVObs,bool TransposeMatr)
{
     if (TransposeMatr) 
        mPose.Rot().Mat().PushByCol(aVObs);
     else
        mPose.Rot().Mat().PushByLine(aVObs);
}



/* ******************************************************* */
/*                                                         */
/*                   cSensorCamPC                          */
/*                                                         */
/* ******************************************************* */

cSensorCamPC::cSensorCamPC(const std::string & aNameImage,const tPose & aPose,cPerspCamIntrCalib * aCalib) :
   cSensorImage     (aNameImage),
   mPose_WU         (aPose),
   mInternalCalib   (aCalib)
{
}

void cSensorCamPC::SetPose(const tPose & aPose)
{
   mPose_WU.SetPose(aPose);
}




#if (1)
std::vector<cObjWithUnkowns<tREAL8> *>  cSensorCamPC::GetAllUK() 
{
    // Dont work because unknown are added twice
    // return std::vector<cObjWithUnkowns<tREAL8> *> {this,mInternalCalib,&mPose_WU};
    
    return std::vector<cObjWithUnkowns<tREAL8> *> {this,mInternalCalib};
}
void cSensorCamPC::PutUknowsInSetInterval()
{
    mPose_WU.PutUknowsInSetInterval(mSetInterv);
}
#else
std::vector<cObjWithUnkowns<tREAL8> *>  cSensorCamPC::GetAllUK() 
{
    return std::vector<cObjWithUnkowns<tREAL8> *> {this,mInternalCalib,&mPose_WU};
}
void cSensorCamPC::PutUknowsInSetInterval()
{
    // Dont work because IndOfVal cannot be found
    // mPose_WU.PutUknowsInSetInterval(mSetInterv);
}
#endif




cPt2dr cSensorCamPC::Ground2Image(const cPt3dr & aP) const
{
     return mInternalCalib->Value(Pt_W2L(aP));
}


        //  Local(0,0,0) = Center, then mPose Cam->Word, then we use Inverse, BTW Inverse is as efficient as direct
cPt3dr cSensorCamPC::Pt_W2L(const cPt3dr & aP) const { return       Pose().Inverse(aP); }
cPt3dr cSensorCamPC::Vec_W2L(const cPt3dr & aP) const { return Pose().Rot().Inverse(aP); }

cPt3dr cSensorCamPC::Pt_L2W(const cPt3dr & aP) const { return       Pose().Value(aP); }
cPt3dr cSensorCamPC::Vec_L2W(const cPt3dr & aP) const { return Pose().Rot().Value(aP); }


double cSensorCamPC::DegreeVisibility(const cPt3dr & aP) const
{
     return mInternalCalib->DegreeVisibility(Pose().Inverse(aP));
}

double cSensorCamPC::DegreeVisibilityOnImFrame(const cPt2dr & aP) const
{
     return mInternalCalib->DegreeVisibilityOnImFrame(aP);
}

cPt3dr cSensorCamPC::Ground2ImageAndDepth(const cPt3dr & aP) const
{
    cPt3dr aPCam = Pose().Inverse(aP);  // P in camera coordinate
    cPt2dr aPIm = mInternalCalib->Value(aPCam);

    return cPt3dr(aPIm.x(),aPIm.y(),aPCam.z());
}

const cPt2di & cSensorCamPC::SzPix() const {return  mInternalCalib->SzPix();}

cPt3dr cSensorCamPC::ImageAndDepth2Ground(const cPt3dr & aPImAndD) const
{
    cPt2dr aPIm = Proj(aPImAndD);
    cPt3dr aPCam = mInternalCalib->DirBundle(aPIm);
    cPt3dr aRes =  Pose().Value(aPCam * (aPImAndD.z() / aPCam.z()));
    return aRes;
}

tSeg3dr  cSensorCamPC::Image2Bundle(const cPt2dr & aPIm) const 
{
   return  tSeg3dr(Center(),static_cast<const cSensorImage*>(this)->ImageAndDepth2Ground(aPIm,1.0));
}


const cPt3dr * cSensorCamPC::CenterOfPC() const { return  & Center(); }
         /// Return the calculator, adapted to the type, for computing colinearity equation
cCalculator<double> * cSensorCamPC::EqColinearity(bool WithDerives,int aSzBuf,bool ReUse) 
{
   return mInternalCalib->EqColinearity(WithDerives,aSzBuf,ReUse);
}

void cSensorCamPC::PushOwnObsColinearity(std::vector<double> & aVObs)
{
     mPose_WU.PushObs(aVObs,true);
}

const cPixelDomain & cSensorCamPC::PixelDomain() const 
{
	return mInternalCalib->PixelDomain();
}



cPerspCamIntrCalib * cSensorCamPC::InternalCalib() const {return mInternalCalib;}

const cPt3dr & cSensorCamPC::Center() const {return mPose_WU.Tr();}
const cPt3dr & cSensorCamPC::Omega()  const {return mPose_WU.Omega();}
cPt3dr & cSensorCamPC::Center() {return mPose_WU.Tr();}
cPt3dr & cSensorCamPC::Omega()  {return mPose_WU.Omega();}
cPt3dr  cSensorCamPC::PseudoCenterOfProj() const {return Center();}

cPt3dr cSensorCamPC::AxeI()   const {return mPose_WU.AxeI();}
cPt3dr cSensorCamPC::AxeJ()   const {return mPose_WU.AxeJ();}
cPt3dr cSensorCamPC::AxeK()   const {return mPose_WU.AxeK();}
const cIsometry3D<tREAL8> & cSensorCamPC::Pose() const {return mPose_WU.Pose();}

cPoseWithUK & cSensorCamPC::Pose_WU() {return mPose_WU;}


cIsometry3D<tREAL8>  cSensorCamPC::RelativePose(const cSensorCamPC& aCam2) const
{
	return Pose().MapInverse()*aCam2.Pose();
}


void cSensorCamPC::OnUpdate()
{
     mPose_WU.OnUpdate();
}


cSensorCamPC * cSensorCamPC::PCChangSys(cDataInvertibleMapping<tREAL8,3> & aMap) const 
{
    cDataNxNMapping<tREAL8,3>::tResJac aJac = aMap.Jacobian(Center());

    cPt3dr aNewC = aJac.first;
    cDenseMatrix<tREAL8>  aNewMatNonR  = aJac.second *  Pose().Rot().Mat();
    cDenseMatrix<tREAL8>  aNewMatR   =  aNewMatNonR.ClosestOrthog();

    if (1)
    {

        StdOut()  <<  "CCC  " << aNewC <<  " DRot=" << aNewMatR.L2Dist(aNewMatNonR) <<  std::endl;

	cPt3dr aI,aJ;
        GetCol(aI,aNewMatNonR,0);
        GetCol(aJ,aNewMatNonR,1);

        cDenseMatrix<tREAL8>  aM0 =  Pose().Rot().Mat();

	StdOut()  <<   "UUU  M0=" <<  Pose().Rot().Mat().Unitarity() << "\n";
	StdOut()  <<  " Glob   Dij  "  << Norm2(aI)- Norm2(aJ) << " D1="  << Norm2(aI)-1.0 << " Cos=" << Cos(aI,aJ) << "\n";


        GetCol(aI,aJac.second.Transpose(),0);
        GetCol(aJ,aJac.second.Transpose(),1);
	StdOut()  <<  " TTT Jac   Dij  "  << Norm2(aI)- Norm2(aJ) << " D1="  << Norm2(aI)-1.0 << " Cos=" << Cos(aI,aJ) << "\n";

        GetCol(aI,aJac.second,0);
        GetCol(aJ,aJac.second,1);
	StdOut()  <<  " Jac   Dij  "  << Norm2(aI)- Norm2(aJ) << " D1="  << Norm2(aI)-1.0 << " Cos=" << Cos(aI,aJ) << "\n";

        aI = aMap.Value(Center()+cPt3dr(0.5,0,0)) - aMap.Value(Center()+cPt3dr(-0.5,0,0));
        aJ = aMap.Value(Center()+cPt3dr(0,0.5,0)) - aMap.Value(Center()+cPt3dr(0,-0.5,0));


	StdOut()  <<  "  MMM  "  << Norm2(aI)- Norm2(aJ) << " D1="  << Norm2(aI)-1.0 << " Cos=" << Cos(aI,aJ) << "\n";
	StdOut()  <<  "  IJ  "  << aI << " " << aJ << "\n";

	for (int aK=0 ; aK<3 ; aK++)
	{
		cPt3dr aP1,aP2;
		GetCol(aP1,aNewMatNonR,aK);
		GetCol(aP2,aNewMatR,aK);
                StdOut()  <<  "    DP  " << aP1 - aP2 <<  std::endl;
	}
	getchar();
    }
    tPoseR aNewPose(aNewC,cRotation3D<tREAL8>(aNewMatR,false));
    FakeUseIt(aNewPose);

    // return new cSensorCamPC
    //  M(aC+I)-M(C) = GradM * I
    //
    return new cSensorCamPC(NameImage(),aNewPose,InternalCalib());

}

cSensorImage * cSensorCamPC::ChangSys(cDataInvertibleMapping<tREAL8,3> & aMap) const
{
	return PCChangSys(aMap);
}




//
tREAL8 cSensorCamPC::AngularProjResiudal(const cPair2D3D& aPair) const
{
    cPt2dr aPIm =  aPair.mP2;
    cPt3dr aDirBundleIm = ImageAndDepth2Ground(cPt3dr(aPIm.x(),aPIm.y(),1.0)) - Center();
    cPt3dr aDirProj =  aPair.mP3 - Center();              // direction of projection

    tREAL8 aRes = Norm2(VUnit(aDirBundleIm)-VUnit(aDirProj));  // equivalent to angular distance

    return aRes;
}

tREAL8  cSensorCamPC::AvgAngularProjResiudal(const cSet2D3D& aSet) const
{
   cWeightAv<tREAL8> aWA;

   for (const auto & aPair : aSet.Pairs())
   {
       aWA.Add(1.0,AngularProjResiudal(aPair));
   }

   return aWA.Average();

}


     // =================  READ/WRITE on files ===================

void cSensorCamPC::AddData(const cAuxAr2007 & anAux0)
{
    cAuxAr2007 anAux("CameraPose",anAux0);
    std::string aNameImage = NameImage();
    cPtxd<tREAL8,4>  aQuat =  MatrRot2Quat(Pose().Rot().Mat());
    std::string      aNameCalib = (anAux.Input() ? "" : mInternalCalib->Name());


    MMVII::AddData(cAuxAr2007("NameImage",anAux),aNameImage);
    MMVII::AddData(cAuxAr2007("NameInternalCalib",anAux),aNameCalib);

    MMVII::AddData(anAux,mPose_WU);
    if (anAux.Input())
    {
         SetNameImage(aNameImage);
	 mTmpNameCalib = aNameCalib;
    }

    MMVII::AddData(cAuxAr2007("EQ",anAux),aQuat);
    anAux.Ar().AddComment("EigenQuaternion, for information");

    cPt3dr aWPK = Pose().Rot().ToWPK() *  (180.0/M_PI);
    MMVII::AddData(cAuxAr2007("WPK",anAux),aWPK);
    anAux.Ar().AddComment("Omega Phi Kapa in degree, for information");


    cPt3dr aYPR = Pose().Rot().ToYPR() *  (180.0/M_PI);
    MMVII::AddData(cAuxAr2007("YPR",anAux),aYPR);
    anAux.Ar().AddComment("Yaw Pitch Roll in degree, for information");

}

void AddData(const cAuxAr2007 & anAux,cSensorCamPC & aPC)
{
    aPC.AddData(anAux);
}

void cSensorCamPC::ToFile(const std::string & aNameFile) const
{
    SaveInFile(const_cast<cSensorCamPC &>(*this),aNameFile);
    std::string aNameCalib = DirOfPath(aNameFile) + mInternalCalib->Name() + "." + GlobTaggedNameDefSerial();
    mInternalCalib->ToFileIfFirstime(aNameCalib);
}

cSensorCamPC * cSensorCamPC::FromFile(const std::string & aFile,bool Remanent)
{
   // Cannot use RemanentObjectFromFile because construction is not standard
   static std::map<std::string,cSensorCamPC*> TheMapRes;
   cSensorCamPC * & anExistingCam = TheMapRes[aFile];

   if (Remanent && (anExistingCam!= nullptr))
      return anExistingCam;


   cSensorCamPC * aPC = new cSensorCamPC("NONE",tPose::Identity(),nullptr);
   ReadFromFile(*aPC,aFile);

   aPC->mInternalCalib =  cPerspCamIntrCalib::FromFile(DirOfPath(aFile) + aPC->mTmpNameCalib + "." + GlobTaggedNameDefSerial());
   aPC->mTmpNameCalib = "";

   anExistingCam = aPC;
   return aPC;
}

std::string  cSensorCamPC::NameOri_From_Image(const std::string & aNameImage)
{
   return cSensorImage::NameOri_From_PrefixAndImage(PrefixName(),aNameImage);
}

std::vector<cPt2dr>  cSensorCamPC::PtsSampledOnSensor(int aNbByDim) const 
{
     return  mInternalCalib->PtsSampledOnSensor(aNbByDim,true);
}


std::string  cSensorCamPC::V_PrefixName() const { return PrefixName() ; }
std::string  cSensorCamPC::PrefixName()  { return "PerspCentral";}

void  cSensorCamPC::GetAdrInfoParam(cGetAdrInfoParam<tREAL8> & aGAIP)
{
     mPose_WU.GetAdrInfoParam(aGAIP);
}
     // =================  becnh ===================

void cSensorCamPC::Bench()
{
   cSet2D3D  aSet32 =  SyntheticsCorresp3D2D(20,3,1.0,10.0) ;
   tREAL8 aRes = AvgAngularProjResiudal(aSet32);

   MMVII_INTERNAL_ASSERT_bench(aRes<1e-8,"Avg res ang");
}

void cSensorCamPC::BenchOneCalib(cPerspCamIntrCalib * aCalib)
{
   cIsometry3D<tREAL8> aPose = cIsometry3D<tREAL8>::RandomIsom3D(10.0);

    cSensorCamPC aCam("BenchCam",aPose,aCalib);
    aCam.Bench();
}


}; // MMVII


