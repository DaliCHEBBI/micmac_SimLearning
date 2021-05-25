#include "include/MMVII_all.h"

namespace MMVII
{

/* ============================================= */
/*      cLeastSqComputeMaps<Type>                */
/* ============================================= */

template <class Type,const int  DimIn,const int DimOut> 
     cLeastSqComputeMaps<Type,DimIn,DimOut>::cLeastSqComputeMaps(size_t aNbFunc) :
        mNbFunc  (aNbFunc),
        mLSQ     (aNbFunc),
        mCoeffs  (aNbFunc),
        mBufPOut (aNbFunc)
{
}

template <class Type,const int  DimIn,const int DimOut> 
     void cLeastSqComputeMaps<Type,DimIn,DimOut>::AddObs
            (const tPtIn & aPtIn,const tPtOut & aValue,const tPtOut & aPds)
{
    ComputeValFuncsBase(mBufPOut,aPtIn);
    cDataIm1D<Type> & aDIm = mCoeffs.DIm();

    for (size_t aD=0 ; aD<DimOut ; aD++)
    {
       for (size_t aKFunc=0 ; aKFunc<mNbFunc ; aKFunc++)
       {
           aDIm.SetV(aKFunc,mBufPOut.at(aKFunc)[aD]);
       }
       mLSQ.AddObservation(aPds[aD],mCoeffs,aValue[aD]);
    }
}

template <class Type,const int  DimIn,const int DimOut> 
     void cLeastSqComputeMaps<Type,DimIn,DimOut>::AddObs
            (const tPtIn & aPtIn,const tPtOut & aValue,const Type & aPds)
{
     AddObs(aPtIn,aValue,tPtOut::PCste(aPds));
}

template <class Type,const int  DimIn,const int DimOut> 
     void cLeastSqComputeMaps<Type,DimIn,DimOut>::AddObs
            (const tPtIn & aPtIn,const tPtOut & aValue)
{
     AddObs(aPtIn,aValue,1.0);
}

/* ============================================= */
/*      cLeastSqCompMapCalcSymb<Type>            */
/* ============================================= */


template <class Type,const int DimIn,const int DimOut>
    class cLeastSqCompMapCalcSymb : public cLeastSqComputeMaps<Type,DimIn,DimOut>
{
    public :
         typedef  cLeastSqComputeMaps<Type,DimIn,DimOut>  tSuper;
         using typename tSuper::tPtOut;
         using typename tSuper::tPtIn;
         using typename tSuper::tVecIn;
         using typename tSuper::tVecOut;

       typedef typename NS_SymbolicDerivative::cCalculator<Type> tCalc;
       cLeastSqCompMapCalcSymb(tCalc *);
       void ComputeValFuncsBase(tVecOut &,const tPtIn & aPt) override;
    private :
       cLeastSqCompMapCalcSymb(const cLeastSqCompMapCalcSymb<Type,DimIn,DimOut>&)=delete;

       tCalc * mCalc;
       std::vector<Type> mVUk;
       std::vector<Type> mVObs;
};

template <class Type,const int  DimIn,const int DimOut> 
     cLeastSqCompMapCalcSymb<Type,DimIn,DimOut>::cLeastSqCompMapCalcSymb(tCalc * aCalc) :
       cLeastSqComputeMaps<Type,DimIn,DimOut>(size_t(mCalc->NbElem()/DimOut)),
       mCalc (aCalc),
       mVUk  (DimIn),
       mVObs (0)
{
    MMVII_INTERNAL_ASSERT_strong(!mCalc->WithDer(),"LeastSqSymb with Derivatives");
    MMVII_INTERNAL_ASSERT_strong(DimIn==mCalc->NbUk(),"LeastSqSymb incoh DimIn/NbUk");
    MMVII_INTERNAL_ASSERT_strong(0==mCalc->NbObs(),"LeastSqSymb NoObs required");
    MMVII_INTERNAL_ASSERT_strong(this->NbFunc()*DimOut==mCalc->NbElem(),"LeastSqSymb incoh elem/Dim/Func");
}

template <class Type,const int  DimIn,const int DimOut> 
  void  cLeastSqCompMapCalcSymb<Type,DimIn,DimOut>::ComputeValFuncsBase(tVecOut & aResPt,const tPtIn & aPt) 
{
    MMVII_INTERNAL_ASSERT_medium(mCalc->NbInBuf()==0,"Buf should be empty");
    for (size_t aD=0 ; aD<DimIn; aD++)
       mVUk.at(aD) = aPt[aD];
    mCalc->PushNewEvals(mVUk,mVObs);
    const std::vector<std::vector<Type> *> & aVAllVal = mCalc->EvalAndClear();
    std::vector<Type>  & aResVal = *(aVAllVal[0]);

    size_t aKVal=0;
    for (size_t aKDim=0 ; aKDim<DimOut ; aKDim++)
    {
        for (auto & aP : aResPt)
        {
            aP[aKDim] = aResVal[aKVal++];
        }
    }
    MMVII_INTERNAL_ASSERT_tiny(aKVal==aResVal.size(),"Size in ComputeValFuncsBase");
}

/* ===================================================== */
/* =====              INSTANTIATION                ===== */
/* ===================================================== */

#define INSTANTIATE_LSQMAP(TYPE,DIMIN,DIMOUT)\
template class cLeastSqComputeMaps<TYPE,DIMIN,DIMOUT>;\
template class cLeastSqCompMapCalcSymb<TYPE,DIMIN,DIMOUT>;

INSTANTIATE_LSQMAP(tREAL8,3,2)
INSTANTIATE_LSQMAP(tREAL8,2,2)

/*
#define INSTANTIATE_OPMulMatVect(T1,T2)\
template  cDenseVect<T1> operator * (const cDenseVect<T1> & aVL,const cUnOptDenseMatrix<T2>& aMat);\
template  cDenseVect<T1> operator * (const cUnOptDenseMatrix<T2>& aVC,const cDenseVect<T1> & aMat);\
template  cDenseVect<T1> operator * (const cDenseVect<T1> & aVL,const cDenseMatrix<T2>& aMat);\
template  cDenseVect<T1> operator * (const cDenseMatrix<T2>& aVC,const cDenseVect<T1> & aMat);\


#define INSTANTIATE_DENSE_MATRICES(Type)\
template  class  cUnOptDenseMatrix<Type>;\
template  class  cDenseMatrix<Type>;\
template  cDenseMatrix<Type> operator * (const cDenseMatrix<Type> &,const cDenseMatrix<Type>&);\
template  cUnOptDenseMatrix<Type> operator * (const cUnOptDenseMatrix<Type> &,const cUnOptDenseMatrix<Type>&);\
INSTANTIATE_OPMulMatVect(Type,Type)\


INSTANTIATE_DENSE_MATRICES(tREAL4)
INSTANTIATE_DENSE_MATRICES(tREAL8)
INSTANTIATE_DENSE_MATRICES(tREAL16)
*/


};
