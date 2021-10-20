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
   protected:
    void Initialize() override {}

    Int_t fRunOrigin{};

    Int_t fRunID{};
    Int_t fEventID{};
    Int_t fSubEventID{};

    Float_t fSensitiveVolumeEnergy{};

    std::vector<TString> fPrimaryParticleName;
    std::vector<Float_t> fPrimaryEnergy;
    std::vector<TVector3> fPrimaryPosition;
    std::vector<TVector3> fPrimaryDirection;

    TString fSubEventPrimaryParticleName = "";
    Float_t fSubEventPrimaryEnergy{};
    TVector3 fSubEventPrimaryPosition{};
    TVector3 fSubEventPrimaryDirection{};

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
    // operator TRestGeant4Event() const;

    Bool_t IsEmpty() const { return fTracks.empty(); }

   private:
    TRestGeant4DataSteps fInitialStep;  //!

    ClassDef(TRestGeant4DataEvent, 2);

   public:
    // from TRestGeant4Event
    inline TVector3 GetPrimaryEventOrigin() { return fPrimaryPosition[0]; }

    inline size_t GetNumberOfPrimaries() const { return fPrimaryParticleName.size(); }
    inline TString GetPrimaryEventParticleName(Int_t n = 0) const { return fPrimaryParticleName[n]; }
    inline TVector3 GetPrimaryEventPosition(Int_t n = 0) const { return fPrimaryPosition[n]; }
    inline TVector3 GetPrimaryEventDirection(Int_t n = 0) const { return fPrimaryDirection[n]; }
    inline Double_t GetPrimaryEventEnergy(Int_t n = 0) { return fPrimaryEnergy[n]; }

    inline size_t GetNumberOfTracks() const { return fTracks.size(); }
    inline size_t GetNumberOfSteps() const {
        size_t n = 0;
        for (const auto& track : fTracks) {
            n += track.GetNumberOfSteps();
        }
        return n;
    }
    inline size_t GetNumberOfHits() const { return GetNumberOfSteps(); }
};

#endif  // REST_TRESTGEANT4DATAEVENT_H
