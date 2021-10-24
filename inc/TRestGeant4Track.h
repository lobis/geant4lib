
#ifndef RestLibGeant4_TRestGeant4Track
#define RestLibGeant4_TRestGeant4Track

#include <TColor.h>
#include <TRestGeant4Hits.h>

class G4Track;
class G4Step;

class TRestGeant4Track {
   public:
    inline TRestGeant4Track() = default;
    inline ~TRestGeant4Track() = default;

    explicit TRestGeant4Track(
        const G4Track*);  // Not defined in Geant4Lib (defined and used in restG4 to insert data)
    void UpdateTrack(const G4Track*);
    void InsertStep(const G4Step*);

    void AddSecondary(Int_t trackID);

   protected:
    Int_t fTrackID;
    Int_t fParentID;

    TString fParticleName;
    Int_t fParticleID;

    TString fParticleType;
    TString fParticleSubType;

    TString fCreatorProcess;
    std::vector<Int_t> fSecondaryTrackIDs;

    Float_t fInitialKineticEnergy;
    Float_t fTrackLength;

    Float_t fWeight;  // Used in biasing
    TRestGeant4Hits fHits;

   public:
    inline size_t GetNumberOfHits() const { return fHits.GetNumberOfHits(); }
    size_t GetNumberOfHitsInVolume(const TString& volumeName) const;
    inline TString GetParticleName() const { return fParticleName; }
    inline TString GetParticleType() const { return fParticleType; }
    inline TString GetParticleSubType() const { return fParticleSubType; }
    inline TString GetCreatorProcess() const { return fCreatorProcess; }
    inline Int_t GetTrackID() const { return fTrackID; }
    inline Int_t GetParentID() const { return fParentID; }
    inline Float_t GetTrackLength() const { return fTrackLength; }
    inline size_t GetNumberOfSecondaries() const { return fSecondaryTrackIDs.size(); }
    inline std::vector<Int_t> GetSecondaries() const { return fSecondaryTrackIDs; }
    inline Float_t GetKineticEnergy() const { return fInitialKineticEnergy; }
    inline Float_t GetInitialTime() const { return fHits.GetTime(0); }
    inline Float_t GetTrackTimeLength() const {
        return fHits.GetTime(fHits.GetNumberOfHits() - 1) - fHits.GetTime(0);
    }

   public:
    inline TRestGeant4Hits* GetHits() { return &fHits; }  // why return a pointer??
    inline TRestGeant4Hits GetHitsConst() const { return fHits; }
    inline void UpdateHits(const TRestGeant4Hits& hits) { fHits = hits; }
    inline Float_t GetDepositedEnergy() const { return fHits.GetTotalEnergy(); }
    EColor GetParticleColor() const;
    TVector3 GetTrackOrigin() const;
    void PrintTrack(size_t numberOfHitsToPrintLimit = 0) const;
    inline void Print(size_t numberOfHitsToPrintLimit = 0) const { PrintTrack(numberOfHitsToPrintLimit); }

    // Analysis

    inline Double_t GetEnergyInVolume(const TString& volumeName) const {
        return fHits.GetEnergyInVolume(volumeName);
    }
    inline TVector3 GetMeanPositionInVolume(const TString& volumeName) const {
        return fHits.GetMeanPositionInVolume(volumeName);
    }
    inline TVector3 GetFirstPositionInVolume(const TString& volumeName) const {
        return fHits.GetFirstPositionInVolume(volumeName);
    }
    inline TVector3 GetLastPositionInVolume(const TString& volumeName) const {
        return fHits.GetLastPositionInVolume(volumeName);
    }

    ClassDef(TRestGeant4Track, 3);  // REST event superclass
};

#endif
