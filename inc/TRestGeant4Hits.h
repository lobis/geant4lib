///_______________________________________________________________________________
///_______________________________________________________________________________
///_______________________________________________________________________________
///
///
///             RESTSoft : Software for Rare Event Searches with TPCs
///
///             TRestGeant4Hits.h
///
///             Base class from which to inherit all other event classes in REST
///
///             jul 2015:   First concept
///                 Created as part of the conceptualization of existing REST
///                 software.
///                 J. Galan
///_______________________________________________________________________________

#ifndef RestCore_TRestGeant4Hits
#define RestCore_TRestGeant4Hits

#include <TArrayF.h>
#include <TArrayI.h>
#include <TObject.h>
#include <TRestHits.h>

#include <iostream>

#include "TRestGeant4DataSteps.h"

class TRestGeant4Hits : public TRestGeant4DataSteps {
   public:
    inline TVector3 GetMomentumDirection(int n) const {
        return {fMomentumDirection[n].x(), fMomentumDirection[n].y(), fMomentumDirection[n].z()};
    }

    inline Int_t GetProcessID(int n) const { return fProcessID[n]; }
    inline TString GetProcessType(int n) const { return fProcessType[n]; }

    inline Int_t GetVolumeID(int n) const { return fVolumeID[n]; }
    inline TString GetVolumeName(int n) const { return fVolumeName[n]; }
    inline TString GetVolumeNamePost(int n) const { return fVolumeNamePost[n]; }

    inline Double_t GetKineticEnergy(int n) { return fKineticEnergy[n]; }
    inline Double_t GetKineticEnergyPost(int n) { return fKineticEnergyPost[n]; }

    Double_t GetEnergyInVolume(const TString& volumeName);

    TVector3 GetMeanPositionInVolume(const TString& volumeName);
    TVector3 GetFirstPositionInVolume(const TString& volumeName);
    TVector3 GetLastPositionInVolume(const TString& volumeName);

    inline TString GetProcessName(int n) const { return fProcessName[n]; };
    // Constructor
    TRestGeant4Hits();
    // Destructor
    ~TRestGeant4Hits() override;

    ClassDef(TRestGeant4Hits, 7);
};
#endif
