//
// Created by lobis on 11/10/2021.
//

#ifndef REST_TRESTGEANT4DATATRACK_H
#define REST_TRESTGEANT4DATATRACK_H

#include <vector>

#include "TRestGeant4DataSteps.h"

class G4Track;
class G4Step;

class TRestGeant4Track;

class TRestGeant4DataTrack {
   protected:
    Int_t fTrackID{};
    Int_t fParentID{};

    TString fParticleName;
    Int_t fParticleID{};

    TString fParticleType;
    TString fParticleSubType;

    TString fCreatorProcess;
    Int_t fNumberOfSecondaries{};
    Float_t fInitialKineticEnergy{};
    Float_t fTrackLength{};

    Float_t fWeight{};
    TRestGeant4DataSteps fHits;

   public:
    inline TRestGeant4DataTrack() = default;
    explicit TRestGeant4DataTrack(const G4Track*);

   public:
    void Print() const;

    void UpdateTrack(const G4Track*);  //!
    void InsertStep(const G4Step*);    //!

    operator TRestGeant4Track() const;

    inline void UpdateSteps(const TRestGeant4DataSteps& steps) { fHits = steps; }  //!

    inline size_t GetNumberOfSteps() const { return fHits.GetNumberOfSteps(); }

    inline TString GetParticleName() const { return fParticleName; }
    inline TString GetParticleType() const { return fParticleType; }
    inline TString GetParticleSubType() const { return fParticleSubType; }
    inline TString GetCreatorProcess() const { return fCreatorProcess; }

    inline Int_t GetTrackID() const { return fTrackID; }
    inline Int_t GetParentID() const { return fParentID; }

    inline Float_t GetTrackLength() const { return fTrackLength; }

    inline Int_t GetNumberOfSecondaries() const { return fNumberOfSecondaries; }
    inline Float_t GetKineticEnergy() const { return fInitialKineticEnergy; }

    inline Float_t GetInitialTime() const { return fHits.GetTime(0); }
    inline Float_t GetTrackTimeLength() const {
        return fHits.GetTime(fHits.GetNumberOfSteps() - 1) - fHits.GetTime(0);
    }

    ClassDef(TRestGeant4DataTrack, 1);
};
#endif  // REST_TRESTGEANT4DATATRACK_H
