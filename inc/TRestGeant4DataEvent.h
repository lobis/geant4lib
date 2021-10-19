//
// Created by lobis on 11/10/2021.
//

#ifndef REST_TRESTGEANT4DATAEVENT_H
#define REST_TRESTGEANT4DATAEVENT_H

#include <TRestEvent.h>
#include <TString.h>

#include "TRestGeant4DataSteps.h"
#include "TRestGeant4DataTrack.h"

class G4Event;
class G4Track;
class G4Step;

class TRestGeant4Event;

class TRestGeant4DataEvent : public TRestEvent {
   private:
    void Initialize() override {}

   protected:
    Int_t fRunOrigin{};

    Int_t fRunID{};
    Int_t fEventID{};
    Int_t fSubEventID{};

    Float_t fSensitiveVolumeEnergy{};

    TString fPrimaryParticleName = "";
    Float_t fPrimaryEnergy{};
    TVector3 fPrimaryPosition{};
    TVector3 fPrimaryMomentum{};

    TString fSubEventPrimaryParticleName = "";
    Float_t fSubEventPrimaryEnergy{};
    TVector3 fSubEventPrimaryPosition{};
    TVector3 fSubEventPrimaryMomentum{};

    std::vector<TRestGeant4DataTrack> fTracks{};

   public:
    inline TRestGeant4DataEvent() = default;
    explicit TRestGeant4DataEvent(const G4Event*);

   public:
    void Print() const;

    void InsertTrack(const G4Track*);
    void UpdateTrack(const G4Track*);
    void InsertStep(const G4Step*);
    inline Int_t GetEventID() const { return fEventID; }
    inline Int_t GetSubEventID() const { return fSubEventID; }
    inline void SetSubEventID(Int_t subEventID) { fSubEventID = subEventID; }
    inline Float_t GetSensitiveVolumeEnergy() const { return fSensitiveVolumeEnergy; }
    inline void AddSensitiveVolumeEnergy(Float_t energy) { fSensitiveVolumeEnergy += energy; }
    operator TRestGeant4Event() const;

    inline size_t GetNumberOfTracks() const { return fTracks.size(); }
    inline size_t GetNumberOfSteps() const {
        size_t n = 0;
        for (const auto& track : fTracks) {
            n += track.GetNumberOfSteps();
        }
        return n;
    }

    Bool_t IsEmpty() const { return fTracks.empty(); }

   private:
    TRestGeant4DataSteps fInitialStep;  //!

    ClassDef(TRestGeant4DataEvent, 2);
};

#endif  // REST_TRESTGEANT4DATAEVENT_H
