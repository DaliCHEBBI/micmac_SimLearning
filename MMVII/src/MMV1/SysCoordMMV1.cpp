#include "V1VII.h"
#include "MMVII_util.h"
#include "MMVII_Stringifier.h"
#include "MMVII_2Include_Serial_Tpl.h"


#include "MMVII_Ptxd.h"
#include "cMMVII_Appli.h"
#include "MMVII_Geom3D.h"
#include "MMVII_PCSens.h"
#include "MMVII_Tpl_Images.h"
#include "MMVII_2Include_Serial_Tpl.h"


namespace MMVII
{

/*********************************************/
/*                                           */
/*             cSysCoordV1                   */
/*                                           */
/*********************************************/

class cSysCoordV1 : public cSysCoordV2
{
	public :
           //cSysCoordV1(cSysCoord *,eSysCoGeo,const std::vector<double>& aVAttrD,const std::vector<std::string>& aVAttrS);
	   cSysCoordV1(eSysCoGeo,const std::map<std::string,std::string> &);

           void AddData(const  cAuxAr2007 & anAuxInit) ;
           void ToFile(const std::string &) const override;
	   static cSysCoordV1 * FromFile(const std::string &);

           tPt ToGeoC(const tPt &) const override;
           tPt FromGeoC(const tPt &) const  override;

	   cSysCoordV1();
           ~cSysCoordV1();
           void  InterpretAttr();

	   static cSysCoordV1*   RTL(const cPt3dr & aPt,const std::string & aSysRef);

        private :

	   /// Conventional value for string that has been consumed
	   static const std::string SConsumed;

	   static const std::string KeyRTLSys;
	   static const std::string KeyRTL_x0;
	   static const std::string KeyRTL_y0;
	   static const std::string KeyRTL_z0;

	   static std::string  GetAttr(std::map<std::string,std::string> & aMap,const std::string & aKey);
	   static void  SetAttr(std::map<std::string,std::string> & aMap,const std::string & aKey,const std::string & aVal);

	   void Init(eSysCoGeo,std::map<std::string,std::string> &);

	   cSysCoord *                        mSV1;
	   eSysCoGeo                          mType;
	   std::map<std::string,std::string>  mAttribs;
};

// Any value that will never be a valide value
const std::string cSysCoordV1::SConsumed = "@#%Zy_!";
const std::string cSysCoordV1::KeyRTLSys = "Sys_RTL";
const std::string cSysCoordV1::KeyRTL_x0 = "x0_RTL";
const std::string cSysCoordV1::KeyRTL_y0 = "y0_RTL";
const std::string cSysCoordV1::KeyRTL_z0 = "z0_RTL";

std::string  cSysCoordV1::GetAttr(std::map<std::string,std::string> & aMap,const std::string & aKey)
{
     auto anIter = aMap.find(aKey);
     if (anIter == aMap.end())
         MMVII_UnclasseUsEr("Key not found in cSysCoordV1::GetAttr : " + aKey);

     if (anIter->second == SConsumed)
         MMVII_UnclasseUsEr("Key multiple consumed in cSysCoordV1::GetAttr : " + aKey);

     std::string aRes = anIter->second;
     anIter->second = SConsumed;

     return aRes;
}

void  cSysCoordV1::SetAttr(std::map<std::string,std::string> & aMap,const std::string & aKey,const std::string & aVal)
{
     auto anIter = aMap.find(aKey);
     if (anIter != aMap.end())
         MMVII_UnclasseUsEr("Key multiple found in cSysCoordV1::GetAttr : " + aKey);

     aMap[aKey] = aVal;
}


cSysCoordV1::cSysCoordV1() :
  mSV1   (nullptr),
  mType  (eSysCoGeo::eNbVals)
{
}

cSysCoordV1::cSysCoordV1(eSysCoGeo aType,const std::map<std::string,std::string> & aAttribs) :
    mSV1      (nullptr),
    mType     (aType),
    mAttribs  (aAttribs)
{
    InterpretAttr();
}

void cSysCoordV1::AddData(const  cAuxAr2007 & anAuxInit) 
{
     cAuxAr2007 anAux("SysCoGeo",anAuxInit);

     MMVII::EnumAddData(anAux,mType,"Type");
     MMVII::AddData(cAuxAr2007("Attrbutes",anAux),mAttribs);
}

void AddData(const  cAuxAr2007 & anAux,cSysCoordV1 & aSysC)
{
    aSysC.AddData(anAux);
}

void cSysCoordV1::ToFile(const std::string & aNameFile) const 
{
   SaveInFile(*this,aNameFile);
}

void cSysCoordV1::Init(eSysCoGeo aType,std::map<std::string,std::string> & aMap)
{
     if  (aType == eSysCoGeo::eLambert93)
         mSV1 = cProj4::Lambert93();
     else if  (aType == eSysCoGeo::eGeoC)
         mSV1 = cSysCoord::GeoC();
     else
     {
         MMVII_UnclasseUsEr("Unhandled sys-co in read");
     }
}


cSysCoordV1 * cSysCoordV1::FromFile(const std::string & aNameFile)
{
     cSysCoordV1 * aRes = new cSysCoordV1;
     ReadFromFile(*aRes,aNameFile);
     aRes->InterpretAttr();

     return aRes;
}

void  cSysCoordV1::InterpretAttr()
{
     std::map<std::string,std::string>  aCpAttr = mAttribs;

     if (mType  != eSysCoGeo::eRTL)
     {
         Init(mType,aCpAttr);
     }
     else
     {
          std::string aStrSysOri =  GetAttr(aCpAttr,KeyRTLSys);  // extract the string of system storing ori
	  eSysCoGeo  aTypeSysOri = Str2E<eSysCoGeo>(aStrSysOri); // convert it to enum
	  cSysCoordV1 aSysOri;
	  aSysOri.Init(aTypeSysOri,aCpAttr);  // initialize a system

	  tREAL8 aXOri = cStrIO<tREAL8>::FromStr(GetAttr(aCpAttr,KeyRTL_x0));
	  tREAL8 aYOri = cStrIO<tREAL8>::FromStr(GetAttr(aCpAttr,KeyRTL_y0));
	  tREAL8 aZOri = cStrIO<tREAL8>::FromStr(GetAttr(aCpAttr,KeyRTL_z0));

	  cPt3dr  aOriSys(aXOri,aYOri,aZOri);
	  aOriSys = aSysOri.ToGeoC(aOriSys);

	  mSV1 = cSysCoord::RTL(ToMMV1(aOriSys));
     }

}

cSysCoordV1*   cSysCoordV1::RTL(const cPt3dr & aPt,const std::string & aSysRef)
{
    cSysCoordV1 *  aSys = cSysCoordV1::FromFile(aSysRef);

    std::map<std::string,std::string> aAttr = aSys->mAttribs;

    SetAttr(aAttr,KeyRTLSys,E2Str(aSys->mType));
    SetAttr(aAttr,KeyRTL_x0,ToStr(aPt.x()));
    SetAttr(aAttr,KeyRTL_y0,ToStr(aPt.y()));
    SetAttr(aAttr,KeyRTL_z0,ToStr(aPt.z()));

    cSysCoordV1* aRes = new cSysCoordV1(eSysCoGeo::eRTL,aAttr);

    delete aSys;

    return aRes;
}

cPt3dr cSysCoordV1::ToGeoC(const cPt3dr & aP) const
{
    return ToMMVII(mSV1->ToGeoC(ToMMV1(aP)));
}
cPt3dr cSysCoordV1::FromGeoC(const cPt3dr & aP) const
{
    return ToMMVII(mSV1->FromGeoC(ToMMV1(aP)));
}

cSysCoordV1::~cSysCoordV1()
{
    // delete mSV1;
}




/*********************************************/
/*                                           */
/*             cSysCoordV2                   */
/*                                           */
/*********************************************/

cSysCoordV2::cSysCoordV2(tREAL8  aEpsDeriv) :
    cDataInvertibleMapping<tREAL8,3>(tPt::PCste(aEpsDeriv))
{
}

cSysCoordV2::~cSysCoordV2() {}

cPt3dr  cSysCoordV2::Value(const cPt3dr &aP) const
{
	return ToGeoC(aP);
}
cPt3dr  cSysCoordV2::Inverse(const cPt3dr &aP) const
{
	return FromGeoC(aP);
}

tPtrSysCo cSysCoordV2::Lambert93()
{
   return tPtrSysCo(new cSysCoordV1(eSysCoGeo::eLambert93,{}));
}

tPtrSysCo cSysCoordV2::GeoC()
{
   return tPtrSysCo(new cSysCoordV1(eSysCoGeo::eGeoC,{}));
}

tPtrSysCo cSysCoordV2::FromFile(const std::string & aName)
{
    return tPtrSysCo(cSysCoordV1::FromFile(aName));
}

tPtrSysCo cSysCoordV2::RTL(const cPt3dr & anOriInit,const std::string & aName)
{
     return tPtrSysCo(cSysCoordV1::RTL(anOriInit,aName));
}

#if (0)



/*********************************************/
/*                                           */
/*            cChangSysCoordV2               */
/*                                           */
/*********************************************/


cChangSysCoordV2::cChangSysCoordV2(tPtrSysCo aSysInit,tPtrSysCo aSysTarget,tREAL8  aEpsDeriv)  :
    cDataInvertibleMapping<tREAL8,3> (cPt3dr::PCste(aEpsDeriv)),
    mSysInit      (aSysInit),
    mSysTarget    (aSysTarget)
{
}

cChangSysCoordV2::~cChangSysCoordV2() {}

cPt3dr cChangSysCoordV2::Value(const cPt3dr & aPInit) const 
{
	return mSysTarget->FromGeoC(mSysInit->ToGeoC(aPInit));
}

cPt3dr cChangSysCoordV2::Inverse(const cPt3dr & aPInit) const 
{
	return mSysInit->FromGeoC(mSysTarget->ToGeoC(aPInit));
}


#endif


};
