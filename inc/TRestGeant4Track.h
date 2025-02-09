///_______________________________________________________________________________
///_______________________________________________________________________________
///_______________________________________________________________________________
///
///
///             RESTSoft : Software for Rare Event Searches with TPCs
///
///             TRestTrack.h
///
///             jul 2015:   First concept
///                 Created as part of the conceptualization of existing REST
///                 software.
///                 J. Galan
///_______________________________________________________________________________

#ifndef RestCore_TRestGeant4Track
#define RestCore_TRestGeant4Track

#include <TArrayI.h>
#include <TColor.h>
#include <TRestGeant4Hits.h>
#include <TString.h>
#include <TVector3.h>

#include <iostream>
#include <vector>

#include "TObject.h"

// Perhaps there might be need for a mother class TRestTrack (if there is future
// need)
class TRestGeant4Track : public TObject {
   protected:
    Int_t fTrack_ID;
    Int_t fParent_ID;

    Int_t fSubEventId;

    // We must change this to save space! (Might be not needed after all)
    // Int_t fParticle_ID;
    TString fParticleName;

    Double_t fGlobalTimestamp;  // in seconds precision
    Double_t fTrackTimestamp;   // in ns precision (seconds have been removed)
    Double_t fKineticEnergy;

    TRestGeant4Hits fHits;

    TVector3 fTrackOrigin;

   public:
    inline void Initialize() {
        RemoveHits();
        fSubEventId = 0.;
    }

    inline const TRestGeant4Hits& GetHits() const { return fHits; }

    inline Double_t GetEnergy() const { return fHits.GetEnergy(); }

    Int_t GetNumberOfHits(Int_t volID = -1) const;
    inline Int_t GetTrackID() const { return fTrack_ID; }
    inline Int_t GetParentID() const { return fParent_ID; }

    inline TString GetParticleName() const { return fParticleName; }
    EColor GetParticleColor() const;

    inline Double_t GetGlobalTime() const { return fGlobalTimestamp; }
    inline Double_t GetTrackTimeLength() const { return fTrackTimestamp; }
    inline Double_t GetKineticEnergy() const { return fKineticEnergy; }
    inline Double_t GetTotalDepositedEnergy() const { return fHits.GetTotalDepositedEnergy(); }
    inline TVector3 GetTrackOrigin() const { return fTrackOrigin; }
    inline Int_t GetSubEventID() const { return fSubEventId; }

    inline Double_t GetEnergyInVolume(Int_t volID) const { return fHits.GetEnergyInVolume(volID); }
    inline TVector3 GetMeanPositionInVolume(Int_t volID) const {
        return fHits.GetMeanPositionInVolume(volID);
    }
    inline TVector3 GetFirstPositionInVolume(Int_t volID) const {
        return fHits.GetFirstPositionInVolume(volID);
    }
    inline TVector3 GetLastPositionInVolume(Int_t volID) const {
        return fHits.GetLastPositionInVolume(volID);
    }

    void SetSubEventID(Int_t id) { fSubEventId = id; }
    void SetTrackID(Int_t id) { fTrack_ID = id; }
    void SetParentID(Int_t id) { fParent_ID = id; }
    //       void SetParticleID( Int_t id ) { fParticle_ID = id; }
    void SetParticleName(const TString& particleName) { fParticleName = particleName; }
    void SetGlobalTrackTime(Double_t time) { fGlobalTimestamp = time; }
    void SetTrackTimeLength(Double_t time) { fTrackTimestamp = time; }
    void SetKineticEnergy(Double_t en) { fKineticEnergy = en; }
    void SetTrackOrigin(const TVector3& pos) { fTrackOrigin = pos; }
    void SetTrackOrigin(Double_t x, Double_t y, Double_t z) { fTrackOrigin.SetXYZ(x, y, z); }

    void AddG4Hit(const TVector3& pos, Double_t en, Double_t hit_global_time, Int_t pcs, Int_t vol,
                  Double_t eKin, const TVector3& momentumDirection) {
        fHits.AddG4Hit(pos, en, hit_global_time, pcs, vol, eKin, momentumDirection);
    }

    Double_t GetTrackLength() const;

    inline static Double_t GetDistance(const TVector3& v1, const TVector3& v2) {
        return TMath::Sqrt((v1.X() - v2.X()) * (v1.X() - v2.X()) + (v1.Y() - v2.Y()) * (v1.Y() - v2.Y()) +
                           (v1.Z() - v2.Z()) * (v1.Z() - v2.Z()));
    }

    inline void RemoveHits() { fHits.RemoveHits(); }

    // TODO move this to a namespace header??
    Int_t GetProcessID(const TString& pcsName);
    TString GetProcessName(Int_t id) const;

    inline Bool_t isRadiactiveDecay() const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if (fHits.GetHitProcess(n) == 11||fHits.GetHitProcess(n) == 13||fHits.GetHitProcess(n) == 14)return true;
        return false;
    }
    inline Bool_t isPhotoElectric() const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if (fHits.GetHitProcess(n) == 3) return true;
        return false;
    }
    inline Bool_t isCompton() const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if (fHits.GetHitProcess(n) == 7) return true;
        return false;
    }
    inline Bool_t isBremstralung() const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if (fHits.GetHitProcess(n) == 5) return true;
        return false;
    }

    inline Bool_t ishadElastic() const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if (fHits.GetHitProcess(n) == 36) return true;
        return false;
    }
    inline Bool_t isneutronInelastic() const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if (fHits.GetHitProcess(n) == 37) return true;
        return false;
    }
    inline Bool_t isnCapture() const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if (fHits.GetHitProcess(n) == 38) return true;
        return false;
    }

    inline Bool_t ishIoni() const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if (fHits.GetHitProcess(n) == 33) return true;
        return false;
    }
    inline Bool_t isphotonNuclear() const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if (fHits.GetHitProcess(n) == 42) return true;
        return false;
    }
    // Processes in active volume
    inline Bool_t isRadiactiveDecayInVolume(Int_t volID) const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if ((fHits.GetHitProcess(n) == 11) && (fHits.GetHitVolume(n)) == volID) return true;
        return false;
    }
    inline Bool_t isPhotoElectricInVolume(Int_t volID) const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if ((fHits.GetHitProcess(n) == 3) && (fHits.GetHitVolume(n)) == volID) return true;
        return false;
    }
    inline Bool_t isPhotonNuclearInVolume(Int_t volID) const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if ((fHits.GetHitProcess(n) == 42) && (fHits.GetHitVolume(n)) == volID) return true;
        return false;
    }

    inline Bool_t isComptonInVolume(Int_t volID) const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if ((fHits.GetHitProcess(n) == 7) && (fHits.GetHitVolume(n)) == volID) return true;
        return false;
    }
    inline Bool_t isBremstralungInVolume(Int_t volID) const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if ((fHits.GetHitProcess(n) == 5) && (fHits.GetHitVolume(n)) == volID) return true;
        return false;
    }

    inline Bool_t isHadElasticInVolume(Int_t volID) const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if ((fHits.GetHitProcess(n) == 36) && (fHits.GetHitVolume(n)) == volID) return true;
        return false;
    }
    inline Bool_t isNeutronInelasticInVolume(Int_t volID) const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if ((fHits.GetHitProcess(n) == 37) && (fHits.GetHitVolume(n)) == volID) return true;
        return false;
    }

    inline Bool_t isNCaptureInVolume(Int_t volID) const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if ((fHits.GetHitProcess(n) == 38) && (fHits.GetHitVolume(n)) == volID) return true;
        return false;
    }

    inline Bool_t isHIoniInVolume(Int_t volID) const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if ((fHits.GetHitProcess(n) == 33) && (fHits.GetHitVolume(n)) == volID) return true;
        return false;
    }

    inline Bool_t isAlphaInVolume(Int_t volID) const {
        if (GetParticleName() == "alpha") {
            for (int n = 0; n < fHits.GetNumberOfHits(); n++)
                if ((fHits.GetHitVolume(n)) == volID) return true;
        }
        return false;
    }

    inline Bool_t isNeutronInVolume(Int_t volID) const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if ((fHits.GetHitVolume(n) == volID) && (GetParticleName() == "neutron")) return true;
        return false;
    }

    inline Bool_t isArgonInVolume(Int_t volID) const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if ((fHits.GetHitVolume(n) == volID) && (GetParticleName().Contains("Ar"))) return true;
        return false;
    }

    inline Bool_t isNeonInVolume(Int_t volID) const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if ((fHits.GetHitVolume(n) == volID) && (GetParticleName().Contains("Ne"))) return true;
        return false;
    }

    inline Bool_t isXenonInVolume(Int_t volID) const {
        for (int n = 0; n < fHits.GetNumberOfHits(); n++)
            if ((fHits.GetHitVolume(n) == volID) && (GetParticleName().Contains("Xe"))) return true;
        return false;
    }
    /////////////////////////////////

    /// Prints the track information. N number of hits to print, 0 = all
    void PrintTrack(int maxHits = 0) const;

    //    Int_t GetElement( Int_t n ) { return X.At(n); }

    //    Int_t GetParticleID();
    // Constructor
    TRestGeant4Track();
    // Destructor
    virtual ~TRestGeant4Track();

    ClassDef(TRestGeant4Track, 3);  // REST event superclass
};

#endif
