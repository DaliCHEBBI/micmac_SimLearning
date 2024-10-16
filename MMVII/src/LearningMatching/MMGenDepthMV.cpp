#include "cCnnModelPredictor.h"
#include "general/PlyFile.h"
//#include "../src/saisieQT/include_QT/Cloud.h"
#include <StdAfx.h>

namespace  MMVII {

namespace  cNS_MMGenDepthMV
{

  class cAppliMMGenDepthMV;

  class cAppliMMGenDepthMV : public cMMVII_Appli
  {

   public :
    typedef tU_INT1               tElemMasq;
    typedef tU_INT2               tElemImage;
    typedef tREAL4                tElemDepth;
    typedef cIm2D<tElemMasq>      tImMasq;
    typedef cIm2D<tElemImage>     tImImage;
    typedef cIm2D<tElemDepth>     tImDepth;
    typedef cDataIm2D<tElemMasq>  tDImMasq;
    typedef cDataIm2D<tElemImage> tDImImage;
    typedef cDataIm2D<tElemDepth> tDImDepth;
    typedef std::vector<tImImage>  tVecIms;
    typedef std::vector<tImMasq>   tVecMasq;

    cAppliMMGenDepthMV(const std::vector<std::string> & aVArgs,const cSpecMMVII_Appli & aSpec);
    cCollecSpecArg2007 & ArgObl(cCollecSpecArg2007 & anArgObl) override ;
    cCollecSpecArg2007 & ArgOpt(cCollecSpecArg2007 & anArgOpt) override ;
    //GlCloud * ReadPlyFile(std::string i_filename);
    void GenerateDepthCloud(CamStenope * aCam, std::string & aFile2Store,sPlyOrientedColoredAlphaVertex **glist, int num_elements);
    void GenerateProfondeurDeChamps(CamStenope * aCam, std::ofstream & aFile2Store,sPlyOrientedColoredAlphaVertex **glist, int num_elements);

    int Exe() override;

    std::string mPatternImages;
    std::string mMasterImage;
    std::string mPointCloud;
    std::string mNameOutDepth;
    std::string mOriFolder;
    std::vector<std::string> mSetOfLidarClouds;
    std::vector<std::string> mSetOfOris;
    std::vector<std::string> mSetOfImages;


    tImDepth mImDepthImage;
    tImMasq mImMasqVisib;
    cPt2di          mSzIms;


  };

  /* *************************************************** */
  /*                                                     */
  /*              cAppliMMGenDepthMV                     */
  /*                                                     */
  /* *************************************************** */


  // OBJECTIVE:
  // FOR EACH IMAGES --> DEPTH MAP GIVEN LIDAR
  //                 --> LIST OF IMAGES AND BOUNDING BOXES OVERLAPPING WITH IT

  cAppliMMGenDepthMV::cAppliMMGenDepthMV(const std::vector<std::string> & aVArgs,const cSpecMMVII_Appli & aSpec) :
     cMMVII_Appli  (aVArgs,aSpec),
     mImDepthImage      (cPt2di(1,1)),
     mImMasqVisib       (cPt2di(1,1)),
     mSzIms          (0,0)

  {

  }


  cCollecSpecArg2007 & cAppliMMGenDepthMV::ArgObl(cCollecSpecArg2007 & anArgObl)
  {
   return
        anArgObl
            <<   Arg2007(mPatternImages,"Image names pattern")
            <<   Arg2007(mOriFolder,"Micmac Orientation Folder with Ori")
            <<   Arg2007(mMasterImage,"Master image to project point cloud to it !")
            <<   Arg2007(mPointCloud,"Point cloud in ply or las format !")
     ;
  }

  // Load a point cloud

  /*GlCloud * cAppliMMGenDepthMV::ReadPlyFile(std::string i_filename)
  {
          GlCloud * cloud=GlCloud::loadPly(i_filename);
          return cloud;
  }*/

  cCollecSpecArg2007 & cAppliMMGenDepthMV::ArgOpt(cCollecSpecArg2007 & anArgOpt)
  {
     return anArgOpt
            << AOpt2007(mNameOutDepth,"DepthMap" ,"Depth Map image Name")
     ;
  }


  void cAppliMMGenDepthMV::GenerateDepthCloud(CamStenope * aCam, std::string & aFile2Store,sPlyOrientedColoredAlphaVertex **glist, int num_elements)
  {
    // store x y z u v : 3d coordinates in image reference frame Pt-opticalCenter and u,v coordinates in image plan

    std::ofstream File(aFile2Store.c_str());

    for (int aK=0;aK<num_elements;aK++)
      {
        sPlyOrientedColoredAlphaVertex * pt = glist[aK];
        Pt3dr aTer(pt->x,pt->y,pt->z);
        bool IsVisibleInSensorCamera=aCam->PIsVisibleInImage(aTer);
        if (IsVisibleInSensorCamera)
          {
            std::string FormattedPt;
            Pt3dr Vecteur_OptCenter_Point=aTer-aCam->OrigineProf();
            Pt2dr PtCam1=aCam->Ter2Capteur(aTer);
            FormattedPt+=std::to_string(Vecteur_OptCenter_Point.x)+" ";
            FormattedPt+=std::to_string(Vecteur_OptCenter_Point.y)+" ";
            FormattedPt+=std::to_string(Vecteur_OptCenter_Point.z)+" ";
            FormattedPt+=std::to_string(PtCam1.x)+" ";
            FormattedPt+=std::to_string(PtCam1.y);

            // Save line
            File << FormattedPt+"\n";
          }
      }
    File.close();

  }


void cAppliMMGenDepthMV::GenerateProfondeurDeChamps(CamStenope * aCam, std::ofstream & File,sPlyOrientedColoredAlphaVertex **glist, int num_elements)
{
    // store x y z u v : 3d coordinates in image reference frame Pt-opticalCenter and u,v coordinates in image plan
    for (int aK=0;aK<num_elements;aK++)
      {
        sPlyOrientedColoredAlphaVertex * pt = glist[aK];
        Pt3dr aTer(pt->x,pt->y,pt->z);
        //std::cout<<aNormal<<std::endl;
        bool IsVisibleInSensorCamera=aCam->PIsVisibleInImage(aTer);
        if (IsVisibleInSensorCamera)
          {
            std::string FormattedPt;
            tElemDepth PtCamProfondeur =aCam->ProfondeurDeChamps(aTer);
            //Pt3dr Vecteur_OptCenter_Point=aTer-aCam->OrigineProf();
            Pt2dr PtCam1=aCam->Ter2Capteur(aTer);
                  FormattedPt+=std::to_string(PtCamProfondeur)+" ";
                  //FormattedPt+=std::to_string(Vecteur_OptCenter_Point.y)+" ";
                  //FormattedPt+=std::to_string(Vecteur_OptCenter_Point.z)+" ";
                  FormattedPt+=std::to_string(PtCam1.x)+" ";
                  FormattedPt+=std::to_string(PtCam1.y);

                  // Save line
                  File << FormattedPt+"\n";
          }
      }
}

  int cAppliMMGenDepthMV::Exe()
  {
    // Read information patterns images, lidar and geometry
    std::string aDirLidar,aPatLidar;
    std:: string aDirOris,aPatOri;
    std::string aDirImages,aPatImages;

    SplitDirAndFile(aDirLidar,aPatLidar,mPointCloud,false);
    SplitDirAndFile(aDirOris,aPatOri,mOriFolder,false);
    SplitDirAndFile(aDirImages,aPatImages,mPatternImages,false);
    std::cout<<"Cloud Pattern ==> "<<aPatLidar<<std::endl;
    std::cout<<"Orientation pattern "<<aPatOri<<std::endl;
    cInterfChantierNameManipulateur * aICNM=cInterfChantierNameManipulateur::BasicAlloc(aDirImages);
    cInterfChantierNameManipulateur * aICNMLD=cInterfChantierNameManipulateur::BasicAlloc(aDirLidar);
    cInterfChantierNameManipulateur * aICNMOris=cInterfChantierNameManipulateur::BasicAlloc(aDirOris);

    // Compute depth images with respect to the master image
    mSetOfLidarClouds = *(aICNMLD->Get(aPatLidar));
    mSetOfOris = *(aICNMOris->Get(aPatOri));
    mSetOfImages= * (aICNM->Get(aPatImages));


    // loading orientations

    //std::vector<CamStenope*> aSetOfCameras =new std::vector<CamStenope*>;
    std::vector<std::string>::iterator itOri=mSetOfOris.begin();
    std::vector<std::string>::iterator itIma=mSetOfImages.begin();
    for (; itOri != mSetOfOris.end();itOri++,itIma++)
      {
        std::cout<<"Image "<<(*itIma)<<std::endl;
        std::cout<<"Name Orientation ==> "<<(*itOri)<<std::endl;
        //CamStenope * aCamV1 =  Std_Cal_From_File (aDirOris+(*itOri));
        CamStenope * aCamV1 = CamOrientGenFromFile((*itOri),aICNMOris);

        // initialize empty image to compute depth
        mSzIms=cPt2di(aCamV1->Sz().x,aCamV1->Sz().y);
        mImDepthImage=tImDepth(mSzIms,nullptr,eModeInitImage::eMIA_Null);
        mImMasqVisib =tImMasq(mSzIms,nullptr,eModeInitImage::eMIA_Null);
        tDImDepth & aDImDepth = mImDepthImage.DIm();
        tDImMasq  & aDImMasqVisib= mImMasqVisib.DIm();

        // intialize output cloud here
        std::string pc2store=(*itIma)+"_depth.xyz";
        std::ofstream aStore(pc2store.c_str());

        std::vector<std::string>::iterator itCld=mSetOfLidarClouds.begin();
        for (;itCld != mSetOfLidarClouds.end();itCld++)
          {
              //GlCloud * aPC =this->ReadPlyFile(aCldFile);
            /**************************************************************/
            sPlyOrientedColoredAlphaVertex **glist=NULL;
            int Cptr = 0;
            bool wNormales = false;
            int type = 0;
            if (type) {} // Warning setbutnotused
            PlyFile * thePlyFile;
            int nelems, nprops, num_elems, file_type;
            float version;
            char **elist;
            char *elem_name;
            PlyProperty **plist=NULL;
            thePlyFile = ply_open_for_reading( const_cast<char *>((aDirLidar + ELISE_CAR_DIR + (*itCld)).c_str()), &nelems, &elist, &file_type, &version);
#ifdef _DEBUG
            cout << "version "	<< version		<< endl;
            cout << "type "		<< file_type	<< endl;
            cout << "nb elem "	<< nelems		<< endl;
#endif

            elem_name = elist[0];
            plist = ply_get_element_description (thePlyFile, elem_name, &num_elems, &nprops);

            std::cout<<"NPROPS "<<nprops<<"   and number of points :"<<nelems<<"  num_elements  "<<num_elems<<std::endl;
            // nprops set to 6 to get coordinates and normals
            //nprops=10;
            // malloc glist

            glist = (sPlyOrientedColoredAlphaVertex **) malloc (sizeof (sPlyOrientedColoredAlphaVertex *) * num_elems);

            for (int i = 0; i < nelems; i++)
            {
                // get the description of the first element
                elem_name = elist[i];
                plist = ply_get_element_description (thePlyFile, elem_name, &num_elems, &nprops);

                if (equal_strings ("vertex", elem_name))
                {
                    printf ("element %s number= %d\n", elem_name, num_elems);

                    switch(nprops)
                    {
                        case 10: // x y z nx ny nz r g b a
                        {
                            type = 5;
                            for (int j = 0; j < nprops ;++j)
                                ply_get_property (thePlyFile, elem_name, &oriented_colored_alpha_vert_props[j]);

                            sPlyOrientedColoredAlphaVertex *vertex = (sPlyOrientedColoredAlphaVertex *) malloc (sizeof (sPlyOrientedColoredAlphaVertex));

                            // grab all the vertex elements
                            for (int j = 0; j < num_elems; j++, Cptr++)
                            {

                                ply_get_element (thePlyFile, (void *) vertex);
                                std::cout<<vertex->x<<" "<<vertex->y<<" "<<vertex->z<<" "<<vertex->nx<<" "<<vertex->ny<<" "<<vertex->nz<<" "<<vertex->red<<" "<<vertex->green<<" "<<vertex->alpha<<std::endl;
                                glist[Cptr] = vertex;
                            }
                            break;
                        }
                        case 9: // x y z nx ny nz r g b
                        {
                            type = 4;
                            for (int j = 0; j < nprops ;++j)
                                ply_get_property (thePlyFile, elem_name, &oriented_colored_vert_props[j]);

                            sPlyOrientedColoredVertex *vertex = (sPlyOrientedColoredVertex *) malloc (sizeof (sPlyOrientedColoredVertex));

                            // grab all the vertex elements
                            for (int j = 0; j < num_elems; j++, Cptr++)
                            {

                                ply_get_element (thePlyFile, (void *) vertex);

        #ifdef _DEBUG
            printf ("vertex--: %g %g %g %g %g %g %u %u %u\n", vertex->x, vertex->y, vertex->z, vertex->nx, vertex->ny, vertex->nz, vertex->red, vertex->green, vertex->blue);
        #endif

                                sPlyOrientedColoredAlphaVertex *fvertex = (sPlyOrientedColoredAlphaVertex *) malloc (sizeof (sPlyOrientedColoredAlphaVertex));

                                fvertex->x = vertex->x;
                                fvertex->y = vertex->y;
                                fvertex->z = vertex->z;

                                fvertex->nx = vertex->nx;
                                fvertex->ny = vertex->ny;
                                fvertex->nz = vertex->nz;

                                fvertex->red   = vertex->red;
                                fvertex->green = vertex->green;
                                fvertex->blue  = vertex->blue;

                                glist[Cptr] = fvertex;

                            }
                            break;
                        }
                        case 7:
                        {
                            type = 2;
                            // setup for getting vertex elements
                            for (int j = 0; j < nprops ;++j)
                                ply_get_property (thePlyFile, elem_name, &colored_a_vert_props[j]);

                            sPlyColoredVertexWithAlpha * vertex = (sPlyColoredVertexWithAlpha *) malloc (sizeof (sPlyColoredVertexWithAlpha));

                            // grab all the vertex elements
                            for (int j = 0; j < num_elems; j++, Cptr++)
                            {
                                ply_get_element (thePlyFile, (void *) vertex);

                                #ifdef _DEBUG
                                    printf ("vertex--: %g %g %g %u %u %u %u\n", vertex->x, vertex->y, vertex->z, vertex->red, vertex->green, vertex->blue, vertex->alpha);
                                #endif

                                sPlyOrientedColoredAlphaVertex *fvertex = (sPlyOrientedColoredAlphaVertex *) malloc (sizeof (sPlyOrientedColoredAlphaVertex));

                                fvertex->x = vertex->x;
                                fvertex->y = vertex->y;
                                fvertex->z = vertex->z;

                                fvertex->red   = vertex->red;
                                fvertex->green = vertex->green;
                                fvertex->blue  = vertex->blue;
                                fvertex->alpha = vertex->alpha;

                                glist[Cptr] = fvertex;
                            }
                            break;
                        }
                        case 6:
                        {
                            // can be (x y z r g b) or (x y z nx ny nz)
                            PlyElement *elem = NULL;

                            for (int i = 0; i < nelems; i++)
                                if (equal_strings ("vertex", thePlyFile->elems[i]->name))
                                    elem = thePlyFile->elems[i];

                            for (int i = 0; i < nprops; i++)
                                if ( "nx"==elem->props[i]->name )   wNormales = true;

                            if (!wNormales)
                            {
                                type = 1;
                                for (int j = 0; j < nprops ;++j)
                                    ply_get_property (thePlyFile, elem_name, &colored_vert_props[j]);

                                sPlyColoredVertex *vertex = (sPlyColoredVertex *) malloc (sizeof (sPlyColoredVertex));

                                for (int j = 0; j < num_elems; j++, Cptr++)
                                {

                                    ply_get_element (thePlyFile, (void *) vertex);

                                    #ifdef _DEBUG
                                        printf ("vertex: %g %g %g %u %u %u\n", vertex->x, vertex->y, vertex->z, vertex->red, vertex->green, vertex->blue);
                                    #endif

                                        sPlyOrientedColoredAlphaVertex *fvertex = (sPlyOrientedColoredAlphaVertex *) malloc (sizeof (sPlyOrientedColoredAlphaVertex));

                                        fvertex->x = vertex->x;
                                        fvertex->y = vertex->y;
                                        fvertex->z = vertex->z;

                                        fvertex->red   = vertex->red;
                                        fvertex->green = vertex->green;
                                        fvertex->blue  = vertex->blue;

                                        glist[Cptr] = fvertex;
                                }
                            }
                            else
                            {
                                type = 3;
                                for (int j = 0; j < nprops ;++j)
                                    ply_get_property (thePlyFile, elem_name, &oriented_vert_props[j]);

                                sPlyOrientedVertex *vertex = (sPlyOrientedVertex *) malloc (sizeof (sPlyOrientedVertex));

                                for (int j = 0; j < num_elems; j++, Cptr++)
                                {
                                    ply_get_element (thePlyFile, (void *) vertex);

                                    #ifdef _DEBUG
                                        printf ("vertex: %g %g %g %g %g %g\n", vertex->x, vertex->y, vertex->z, vertex->nx, vertex->ny, vertex->nz);
                                    #endif

                                    sPlyOrientedColoredAlphaVertex *fvertex = (sPlyOrientedColoredAlphaVertex *) malloc (sizeof (sPlyOrientedColoredAlphaVertex));

                                    fvertex->x = vertex->x;
                                    fvertex->y = vertex->y;
                                    fvertex->z = vertex->z;

                                    fvertex->nx = vertex->nx;
                                    fvertex->ny = vertex->ny;
                                    fvertex->nz = vertex->nz;

                                    glist[Cptr] = fvertex;
                                }
                            }
                            break;
                        }
                        case 3:
                        {
                            for (int j = 0; j < nprops ;++j)
                                ply_get_property (thePlyFile, elem_name, &vert_props[j]);

                            sVertex *vertex = (sVertex *) malloc (sizeof (sVertex));

                            for (int j = 0; j < num_elems; j++, Cptr++)
                            {

                                ply_get_element (thePlyFile, (void *) vertex);

        #ifdef _DEBUG
                            printf ("vertex: %g %g %g\n", vertex->x, vertex->y, vertex->z);
        #endif

                                sPlyOrientedColoredAlphaVertex *fvertex = (sPlyOrientedColoredAlphaVertex *) malloc (sizeof (sPlyOrientedColoredAlphaVertex));

                                fvertex->x = vertex->x;
                                fvertex->y = vertex->y;
                                fvertex->z = vertex->z;

                                glist[Cptr] = fvertex;
                            }
                            break;
                        }
                        default:
                        {


                          // ONLY LOAD POINT COORINATES
                          {
                           std::cout<<"Load coordinates only x y z: "<<std::endl;
                              for (int j = 0; j < 3 ;++j)
                                  ply_get_property (thePlyFile, elem_name, &vert_props[j]);

                              sVertex *vertex = (sVertex *) malloc (sizeof (sVertex));

                              for (int j = 0; j < num_elems; j++, Cptr++)
                              {

                                  ply_get_element (thePlyFile, (void *) vertex);

          #ifdef _DEBUG
                              printf ("vertex: %g %g %g\n", vertex->x, vertex->y, vertex->z);
          #endif

                                  sPlyOrientedColoredAlphaVertex *fvertex = (sPlyOrientedColoredAlphaVertex *) malloc (sizeof (sPlyOrientedColoredAlphaVertex));

                                  fvertex->x = vertex->x;
                                  fvertex->y = vertex->y;
                                  fvertex->z = vertex->z;

                                  glist[Cptr] = fvertex;
                              }
                              std::cout<<"LOAD COORDINATES XYZ " <<std::endl;
                              break;
                          }


                        }
                    }
                }
            }
            ply_close (thePlyFile);

              /**************************************************************/
                for (int aK=0;aK<num_elems;aK++)
                  {
                    sPlyOrientedColoredAlphaVertex * pt = glist[aK];
                    Pt3dr aTer(pt->x,pt->y,pt->z);
                    bool IsVisibleInSensorCamera=aCamV1->PIsVisibleInImage(aTer);
                    if (IsVisibleInSensorCamera)
                      {
                        Pt2dr PtCam1=aCamV1->Ter2Capteur(aTer);
                            // condition on visibility with normals information
                            tElemDepth PtCamProfondeur =aCamV1->ProfondeurDeChamps(aTer);
                            // store depth
                            //aDImDepth.SetV();
                            cPt2di PtCamInt((int)PtCam1.x,(int)PtCam1.y);
                            aDImDepth.SetV(PtCamInt,PtCamProfondeur);
                            aDImMasqVisib.SetV(PtCamInt,1);
                        //mImDepthImage.SetElem(PtCamInt.x,PtCamInt.y,PtCamProfondeur);
                      }
                    /*else
                      {
                        Pt2dr PtCam1=aCamV1->Ter2Capteur(aTer);
                        cPt2di PtCamInt((int)PtCam1.x,(int)PtCam1.y);
                        aDImDepth.SetV(PtCamInt,0.0);
                        aDImMasqVisib.SetV(PtCamInt,0);
                      }*/
                  }
                //GenerateDepthCloud(aCamV1,pc2store,glist,num_elems);
                GenerateProfondeurDeChamps(aCamV1,aStore,glist,num_elems);
                      if ( glist!=NULL ) free(glist); // G++11 delete glist;
                      if ( plist!=NULL ) delete plist;
              }
        aStore.close();
        aDImDepth.ToFile((*itIma)+"_Depth.tif");
        aDImMasqVisib.ToFile((*itIma)+"_Masq.tif");
      }
    return EXIT_SUCCESS;
  }

};



using namespace  cNS_MMGenDepthMV;


tMMVII_UnikPApli Alloc_MMGenDepthMV(const std::vector<std::string> &  aVArgs,const cSpecMMVII_Appli & aSpec)
{
   return tMMVII_UnikPApli(new cAppliMMGenDepthMV(aVArgs,aSpec));
}

cSpecMMVII_Appli TheSpecMMGenDepthMV
(
     "DepthMapForImage",
      Alloc_MMGenDepthMV,
      "Generate a depth map for each image given orientation and Lidar point clouds",
      {eApF::Match},
      {eApDT::Image},
      {eApDT::ToDef},
      __FILE__
);



};
