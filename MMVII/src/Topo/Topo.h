#include "MMVII_SysSurR.h"
#include "MMVII_Sensor.h"
#include "MMVII_SysCo.h"
#include "ctopodata.h"

using namespace NS_SymbolicDerivative;

namespace MMVII
{

class cMMVII_BundleAdj;
class cPhotogrammetricProject;
class cSensorCamPC;
class cTopoObsSet;
class cTopoPoint;
class cBA_GCP;

class cBA_Topo : public cMemCheck
{
    friend class cTopoData;
public :

    cBA_Topo(cPhotogrammetricProject *aPhProj);
    ~cBA_Topo();
    void clear();

    void makePtsUnknowns(const std::vector<cBA_GCP *> &vGCP, cPhotogrammetricProject *aPhProj); //< to be called after points creation and before AddToSys and ObsSetStation::SetOrigin...

    void  AddToSys(cSetInterUK_MultipeObj<tREAL8> &); // The system must be aware of all the unknowns

    // fix the variable that are frozen
    void SetFrozenAndSharedVars(cResolSysNonLinear<tREAL8> &)  ;

    //  Do the kernel job : add topo constraints to the system
    void AddTopoEquations(cResolSysNonLinear<tREAL8> &);
    void FromData(const cTopoData &aTopoData, const std::vector<cBA_GCP *> &vGCP, cPhotogrammetricProject *aPhProj);
    void Init(const std::vector<cBA_GCP *> &vGCP, cPhotogrammetricProject *aPhProj);
    void ToFile(const std::string & aName) const;
    void print();
    void printObs(bool withDetails=false);
    double  Sigma0() {return mSigma0;}

    bool mergeUnknowns(cResolSysNonLinear<tREAL8> &aSys); //< if several stations share origin etc.
    void makeConstraints(cResolSysNonLinear<tREAL8> &aSys);
    const std::map<std::string, cTopoPoint> & getAllPts() const { return mAllPts; }
    std::map<std::string, cTopoPoint> & getAllPts() { return mAllPts; }
    cTopoPoint & getPoint(std::string name);
    cCalculator<double>* getEquation(eTopoObsType tot) const;
    tPtrSysCo getSysCo() const { return mSysCo; }

    friend void BenchTopoComp1example(cTopoData aTopoData, tREAL4 targetSigma0);
private :
    cTopoData mAllTopoDataIn;
    cPhotogrammetricProject * mPhProj;
    std::map<eTopoObsType, cCalculator<double>*> mTopoObsType2equation;
    std::map<std::string, cTopoPoint> mAllPts;
    std::vector<cTopoObsSet*> mAllObsSets;
    double                       mSigma0;
    bool                        mIsReady; //< if data has been read (via FromFile)
    tPtrSysCo                     mSysCo;
};


};

