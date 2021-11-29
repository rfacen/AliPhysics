/*
 * AliAnalysisTaskNanoLK.h
 *
 *  Created on: Nov 12, 2021
 *      Author: Valentina Mantovani Sarti
 */

#ifndef PWGCF_FEMTOSCOPY_FEMTODREAM_ALIANALYSISTASKNANOLK_H_
#define PWGCF_FEMTOSCOPY_FEMTODREAM_ALIANALYSISTASKNANOLK_H_
#include "AliAnalysisTaskSE.h"
#include "AliFemtoDreamEventCuts.h"
#include "AliFemtoDreamEvent.h"
#include "AliFemtoDreamTrackCuts.h"
#include "AliFemtoDreamTrack.h"
#include "AliFemtoDreamv0.h"
#include "AliFemtoDreamv0Cuts.h"
#include "AliFemtoDreamCollConfig.h"
#include "AliFemtoDreamPairCleaner.h"
#include "AliFemtoDreamPartCollection.h"
#include "AliFemtoDreamControlSample.h"

class AliAnalysisTaskNanoLK : public AliAnalysisTaskSE {
 public:
  AliAnalysisTaskNanoLK();
  AliAnalysisTaskNanoLK(const char* name, bool isMC);
  virtual ~AliAnalysisTaskNanoLK();
  virtual void UserCreateOutputObjects();
  virtual void UserExec(Option_t *option);
  void ResetGlobalTrackReference();
  void StoreGlobalTrackReference(AliVTrack *track);

  void SetRunTaskLightWeight(bool light) { //for output histograms. Better to be . For fast runs 
    fisLightWeight = light;
  }

  void SetEventCuts(AliFemtoDreamEventCuts* evtCuts) { //cuts for our analysis
    fEventCuts = evtCuts;
  }

  void SetPosKaonCuts(AliFemtoDreamTrackCuts *trkCuts) { //kaon (particle)
    fPosKaonCuts = trkCuts;
  }

  void SetNegKaonCuts(AliFemtoDreamTrackCuts *trkCuts) { //kaon (antiparticle)
    fNegKaonCuts = trkCuts;
  }

  void Setv0Cuts(AliFemtoDreamv0Cuts* v0Cuts) { //lambda
    fLambdaCuts = v0Cuts;
  }
  void SetAntiv0Cuts(AliFemtoDreamv0Cuts* v0Cuts) { //antilambda
    fAntiLambdaCuts = v0Cuts;
  }

  void SetCorrelationConfig(AliFemtoDreamCollConfig* config) { //set output correlation. See "AliFemtoDreamCollConfig"
    fConfig=config;
  }

 private: //private members, used for cxx file
  AliAnalysisTaskNanoLK(const AliAnalysisTaskNanoLK &task); //first two rows are standard definition. Correspondence between the names. When you modify the code, AliAnalysisTaskNanoLK must be modified everywhere
  AliAnalysisTaskNanoLK &operator=(const AliAnalysisTaskNanoLK &task);
 //we now define every variables, the ones we talked about in the void classes. Everything will be used on the cxx file
 
  bool fisLightWeight;// //boolean for the histograms
  bool fIsMC;        //  //switch the MonteCarlo on or off
 
  TList *fQA;        //!  //Tlist is a folder on the root file, where you can store QA histograms (QA == quality assurance: check histograms, further information) 
  AliFemtoDreamEvent* fEvent;//!
  AliFemtoDreamEventCuts* fEventCuts;//
  TList* fEvtList;//!
  AliFemtoDreamTrack* fTrack;//!   //define track object
  AliFemtoDreamTrackCuts* fPosKaonCuts;//  //correspective track cut
  TList* fPosKaonList;//!
  TList* fPosKaonMCList;//!
  AliFemtoDreamTrackCuts* fNegKaonCuts;//
  TList* fNegKaonList;//!
  TList* fNegKaonMCList;//!
  AliFemtoDreamv0* fv0;//!
  AliFemtoDreamv0Cuts* fLambdaCuts;//
  TList* fLambdaList;//!
  TList* fLambdaMCList;//!
  AliFemtoDreamv0Cuts* fAntiLambdaCuts;//
  TList* fAntiLambdaList;//!
  TList* fAntiLambdaMCList;//!
  AliFemtoDreamCollConfig *fConfig; //      //from here to row 86, we have specific objects for the correlation
  AliFemtoDreamPairCleaner *fPairCleaner;   //!
  AliFemtoDreamPartCollection *fPartColl;   //!
  TList *fResults;//!
  TList *fResultsQA;//!
  AliFemtoDreamControlSample *fSample;   //!
  TList *fResultsSample;//!
  TList *fResultsSampleQA;//!
  int fTrackBufferSize;//    //vector to fill with particles to create pairs
  AliVTrack **fGTI;  //!
  ClassDef(AliAnalysisTaskNanoLK,4)   //important for the root streamer. Everytime we add a new member, we should increment the number (now it s 4)
   
   //rows with ! will not be "streamed" (e.g. neither copied nor stored): streamed: cuts, things for correlation, and the buffer
};

#endif /* PWGCF_FEMTOSCOPY_FEMTODREAM_ALIANALYSISTASKNANOLK_H_ */
