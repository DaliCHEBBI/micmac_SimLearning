#include "cMMVII_Appli.h"
#include "MMVII_PCSens.h"
#include "MMVII_Geom2D.h"
#include "MMVII_DeclareCste.h"
#include "MMVII_2Include_Serial_Tpl.h"
#include "MMVII_Triangles.h"
#include "MMVII_Image2D.h"
#include "MeshDev.h"
#include "MMVII_Sys.h"
#include "MMVII_Triangles.h"

namespace MMVII
{


class cAppliMeshImageDevlp : public cMMVII_Appli
{
     public :

        cAppliMeshImageDevlp(const std::vector<std::string> & aVArgs,const cSpecMMVII_Appli & aSpec);

     private :
        int Exe() override;
        cCollecSpecArg2007 & ArgObl(cCollecSpecArg2007 & anArgObl) override ;
        cCollecSpecArg2007 & ArgOpt(cCollecSpecArg2007 & anArgOpt) override ;


	void DoAnIm(size_t aKIm);

        // cAppliBenchAnswer BenchAnswer() const override;  ///< this command is used in the bench
	// int  ExecuteBench(cParamExeBench &) override ;   ///< indicate what is done in the bench



     // --- Mandatory ----
	std::string mNameCloud2DIn;
	std::string mNameFile_MDBI;  ///<  Name for cMeshDev_BestIm

     // --- Optionnal ----
	bool                           mMiror; 
	/*
	double      mResolZBuf;
	int         mNbPixImRedr;
        bool        mDoImages;
        bool        mSKE;
        bool        mNameBenchMode;
	*/

     // --- constructed ---
        cPhotogrammetricProject     mPhProj;
	cTriangulation2D<tREAL8>*   mTriDev;
	cTriangulation3D<tREAL8>*   mTri3;
	cBox2dr                     mBoxDev;

        cHomot2D<tREAL8>               mHDev2Pix ;
	cPt2di                         mSzPix;
	std::string                    mNameImRes;

        cMeshDev_BestIm                mMDBI;
	size_t                         mNbIm;
	size_t                         mNbF;
	size_t                         mNbPts;
	std::vector<std::list<size_t>> mVListIndTri;  

	std::vector<cPt2dr>            mPtsCurIm;
	std::vector<cPt2dr>            mPtsGlob;
	cSetIntDyn                     mSetPCurIm;
	cRGBImage                      mGlobIm;

};

cCollecSpecArg2007 & cAppliMeshImageDevlp::ArgObl(cCollecSpecArg2007 & anArgObl) 
{
   return anArgObl
	  <<   Arg2007(mNameCloud2DIn,"Name of 2d devloped mesh",{eTA2007::FileDirProj} )
	  <<   Arg2007(mNameFile_MDBI,"Name of file resulting of MeshProjImage")

   ;
}

cAppliMeshImageDevlp::cAppliMeshImageDevlp(const std::vector<std::string> & aVArgs,const cSpecMMVII_Appli & aSpec) :
   cMMVII_Appli     (aVArgs,aSpec),
    // opt args
   mMiror           (true),
    // internal vars
   mPhProj          (*this),
   mTriDev          (nullptr),
   mBoxDev          (cBox2dr::Empty()),
   mSetPCurIm       (0),
   mGlobIm          (cPt2di(1,1))
{
}



cCollecSpecArg2007 & cAppliMeshImageDevlp::ArgOpt(cCollecSpecArg2007 & anArgOpt)
{
   return anArgOpt
/*
           << AOpt2007(mNameCloud2DIn,"M2","Mesh 2D, dev of cloud 3D,to generate a visu of hiden part ",{eTA2007::FileCloud,eTA2007::Input})
           << AOpt2007(mResolZBuf,"ResZBuf","Resolution of ZBuffer", {eTA2007::HDV})
	  <<  AOpt2007(mDoImages,"DoIm","Do images", {eTA2007::HDV})
           << AOpt2007(mNbPixImRedr,"NbPixIR","Resolution of ZBuffer", {eTA2007::HDV})
           << AOpt2007(mSKE,CurOP_SkipWhenExist,"Skip command when result exist")
           << AOpt2007(mNameBenchMode,"NameBM","Use name as in bench mode",{eTA2007::HDV,eTA2007::Tuning})
	   << AOptBench()
*/
   ;

}

void cAppliMeshImageDevlp::DoAnIm(size_t aKIm)
{
   if (mVListIndTri.at(aKIm).empty())
   {
      return;
   }

   std::string aNameIm = mMDBI.mNames[aKIm];
   cDataFileIm2D aDFIIm = cDataFileIm2D::Create(aNameIm,false);

   cSensorCamPC * aCamPC = mPhProj.AllocCamPC(aNameIm,false);

   // compute Ind of pts used in this image
   for (const auto & aIndF :   mVListIndTri.at(aKIm))
   {
       const cPt3di  & aFace =  mTriDev->KthFace(aIndF);
       for (int aK3=0 ; aK3<3 ; aK3++)
           mSetPCurIm.AddIndFixe(aFace[aK3]);
   }
   // conpute  coord of pts in ortho and in cur Im
   cTplBoxOfPts<tREAL8,2> aBoxDev;
   cTplBoxOfPts<tREAL8,2> aBoxIm;
   for (const auto & anIndPts : mSetPCurIm.mVIndOcc)
   {
       cPt2dr aPGlob = mPtsGlob.at(anIndPts);
       aBoxDev.Add(aPGlob);

       cPt2dr aPIm = aCamPC->Ground2Image(mTri3->KthPts(anIndPts));
       aBoxIm.Add(aPIm);
       mPtsCurIm.at(anIndPts) = aPIm;
   }

   // Create box of pix from box of Tri Proj : dilate (for margin),  cast to int, intersect with box of image
   cBox2di  aBoxPixIm =  aBoxIm.CurBox().Dilate(4.0).ToI();
   aBoxPixIm = aBoxPixIm.Inter(aDFIIm);


   cRGBImage  aImCur = cRGBImage::FromFile(aNameIm,aBoxPixIm);

   StdOut() << " KKIm" << aKIm
	    << " " << aNameIm
	    << " " << aCamPC->InternalCalib()->F()
	    << " " << aBoxDev.CurBox().Sz()
	    << " " << aBoxIm.CurBox().Sz()
	    << " " << aBoxPixIm
	    << "\n"; 


   for (const auto & aIndF :   mVListIndTri.at(aKIm))
   {
        const cPt3di  & aFace =  mTriDev->KthFace(aIndF);

        cTriangle2DCompiled<tREAL8> aTriGlob  = TriFromFace(mPtsGlob,aFace);
        cTri2dR aTriCurIm = TriFromFace(mPtsCurIm,aFace);

        cAffin2D<tREAL8> aAffG2I = cAffin2D<tREAL8>::Tri2Tri(aTriGlob,aTriCurIm);
	aAffG2I = cAffin2D<tREAL8>::Translation(-ToR(aBoxPixIm.P0())) * aAffG2I;

//StdOut() << "FFF " << aAffG2I.Tr() << aAffG2I.VX() << aAffG2I.VY() << "\n";

	std::vector<cPt2di>  aVPixGlob;
	aTriGlob.PixelsInside(aVPixGlob,1e-8);

	for (const auto & aPixG : aVPixGlob)
	{
            cPt2dr aPtIm = aAffG2I.Value(ToR(aPixG));
//StdOut() <<  "IiIm=" <<  aPtIm <<  " "    <<  aImCur.ImR().DIm().Sz()   << " GLOB=" << aPixG << "\n";
//getchar();

	    cPt3di aRGB = aImCur.GetRGBPixBL(aPtIm);


            mGlobIm.SetRGBPix(aPixG,aRGB);
	}
   }

   delete aCamPC;
   mSetPCurIm.Clear();
}


int cAppliMeshImageDevlp::Exe() 
{
     //  Init mMDBI & mPhProj
     ReadFromFile(mMDBI,DirProject()+mNameFile_MDBI);
     mPhProj.SetOriIn(mMDBI.mNameOri);
     mPhProj.FinishInit();

     //  Read triangulations
     mTriDev = new cTriangulation2D<tREAL8>(DirProject() + FileOfPath(mNameCloud2DIn ));
     if (mMiror)
     {
         for (size_t aKP=0 ; aKP<mTriDev->NbPts() ; aKP++)
              mTriDev->KthPts(aKP).y() *= -1;
     }
     mNbF = mTriDev->NbFace();
     mNbPts = mTriDev->NbPts();
     mBoxDev = mTriDev->BoxEngl();
     mTri3 = new cTriangulation3D<tREAL8>(DirProject() +  mMDBI.mNamePly);

     MMVII_INTERNAL_ASSERT_tiny(mTri3->NbFace()==mNbF,"Incoherent NbFace 2d/3d");
     MMVII_INTERNAL_ASSERT_tiny(mTri3->NbPts()==mNbPts,"Incoherent NbPts 2d/3d");

     //  Initialize mVListIndTri
     mNbIm = mMDBI.mNames.size();
     mVListIndTri.resize(mNbIm);
     for (size_t aKTri=0 ; aKTri<mMDBI.mNumBestIm.size() ; aKTri++)
     {
         int aIndBI = mMDBI.mNumBestIm.at(aKTri);
         if (aIndBI>=0)
            mVListIndTri.at(aIndBI).push_back(aKTri);
     }

     // Initialize Mapping Tri2 / Pixel
     tREAL8 aScale = mMDBI.mAvgResol;
     cPt2dr aBrd(2,2);
     mHDev2Pix = cHomot2D<tREAL8>(aBrd - mBoxDev.P0()*aScale, aScale);

     mPtsGlob.resize(mNbPts);
     mPtsCurIm.resize(mNbPts);
     for (size_t aKp=0 ; aKp<mNbPts ; aKp++)
     {
         mPtsGlob.at(aKp) = mHDev2Pix.Value(mTriDev->KthPts(aKp));
     }
     mSetPCurIm = cSetIntDyn(mNbPts);

     // Create file if required
     mSzPix = Pt_round_up(aBrd+mHDev2Pix.Value(mBoxDev.P1()));
     mNameImRes = MMVIIDirMeshDev + "DevIm-" +  LastPrefix(FileOfPath(mNameFile_MDBI)) + ".tif";
     if ( (LevelCall()==0) &&  (!ExistFile(mNameImRes)) )
     {
        cDataFileIm2D::Create(mNameImRes,eTyNums::eTN_U_INT1,mSzPix,3);
     }

     mGlobIm = cRGBImage::FromFile(mNameImRes);


     for (size_t aKIm = 0 ; aKIm < mNbIm ; aKIm++)
     {
          DoAnIm(aKIm);
     }

     mGlobIm.Write(mNameImRes,cPt2di(0,0));

     delete mTriDev;
     delete mTri3;
     return EXIT_SUCCESS;
}

     /* =============================================== */
     /*                       ::                        */
     /* =============================================== */


tMMVII_UnikPApli Alloc_MeshImageDevlp(const std::vector<std::string> &  aVArgs,const cSpecMMVII_Appli & aSpec)
{
   return tMMVII_UnikPApli(new cAppliMeshImageDevlp(aVArgs,aSpec));
}

cSpecMMVII_Appli  TheSpecMeshImageDevlp
(
     "MeshImageDevlp",
      Alloc_MeshImageDevlp,
      " Compute devlopped images from 3d-mesh, 2d-dev-mesh and ori",
      {eApF::ImProc},
      {eApDT::Ply,eApDT::Orient,eApDT::Image},
      {eApDT::Image},
      __FILE__
);

}
