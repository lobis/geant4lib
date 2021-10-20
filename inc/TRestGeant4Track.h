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
///
///             oct 2021:   First concept
///                 Updated to new datamodel
///                 L. Obis
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

#include "TRestGeant4DataTrack.h"

class TRestGeant4Track : public TRestGeant4DataTrack {
   protected:
    TRestGeant4Hits fHits;

   public:
    TRestGeant4Hits* GetHits() { return &fHits; }

    Double_t GetEnergy() { return fHits.TRestHits::GetEnergy(); }

    EColor GetParticleColor();

    inline TVector3 GetTrackOrigin() const {
        if (fHits.GetProcessName(0) != "Init") {
            std::cout << "ERROR IN TRestGeant4Track::GetTrackOrigin, please check" << std::endl;
            exit(1);
        }
        return fHits.TRestHits::GetPosition(0);
    }

    Double_t GetEnergyInVolume(Int_t volID) { return fHits.GetEnergyInVolume(volID); }
    TVector3 GetMeanPositionInVolume(Int_t volID) { return fHits.GetMeanPositionInVolume(volID); }
    TVector3 GetFirstPositionInVolume(Int_t volID) { return fHits.GetFirstPositionInVolume(volID); }
    TVector3 GetLastPositionInVolume(Int_t volID) { return fHits.GetLastPositionInVolume(volID); }

    Int_t GetNumberOfHits() const { return fHits.GetNumberOfSteps(); }

    /*
    Bool_t isRadiactiveDecay() {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if (GetHits()->GetHitProcess(n) == 11) return true;
        return false;
    }
    Bool_t isPhotoElectric() {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if (GetHits()->GetHitProcess(n) == 3) return true;
        return false;
    }
    Bool_t isCompton() {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if (GetHits()->GetHitProcess(n) == 7) return true;
        return false;
    }
    Bool_t isBremstralung() {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if (GetHits()->GetHitProcess(n) == 5) return true;
        return false;
    }

    Bool_t ishadElastic() {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if (GetHits()->GetHitProcess(n) == 36) return true;
        return false;
    }
    Bool_t isneutronInelastic() {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if (GetHits()->GetHitProcess(n) == 37) return true;
        return false;
    }
    Bool_t isnCapture() {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if (GetHits()->GetHitProcess(n) == 38) return true;
        return false;
    }

    Bool_t ishIoni() {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if (GetHits()->GetHitProcess(n) == 33) return true;
        return false;
    }
    Bool_t isphotonNuclear() {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if (GetHits()->GetHitProcess(n) == 42) return true;
        return false;
    }
    // Processes in active volume
    Bool_t isRadiactiveDecayInVolume(Int_t volID) {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if ((GetHits()->GetHitProcess(n) == 11) && (GetHits()->GetHitVolume(n)) == volID) return true;
        return false;
    }
    Bool_t isPhotoElectricInVolume(Int_t volID) {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if ((GetHits()->GetHitProcess(n) == 3) && (GetHits()->GetHitVolume(n)) == volID) return true;
        return false;
    }
    Bool_t isPhotonNuclearInVolume(Int_t volID) {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if ((GetHits()->GetHitProcess(n) == 42) && (GetHits()->GetHitVolume(n)) == volID) return true;
        return false;
    }

    Bool_t isComptonInVolume(Int_t volID) {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if ((GetHits()->GetHitProcess(n) == 7) && (GetHits()->GetHitVolume(n)) == volID) return true;
        return false;
    }
    Bool_t isBremstralungInVolume(Int_t volID) {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if ((GetHits()->GetHitProcess(n) == 5) && (GetHits()->GetHitVolume(n)) == volID) return true;
        return false;
    }

    Bool_t isHadElasticInVolume(Int_t volID) {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if ((GetHits()->GetHitProcess(n) == 36) && (GetHits()->GetHitVolume(n)) == volID) return true;
        return false;
    }
    Bool_t isNeutronInelasticInVolume(Int_t volID) {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if ((GetHits()->GetHitProcess(n) == 37) && (GetHits()->GetHitVolume(n)) == volID) return true;
        return false;
    }

    Bool_t isNCaptureInVolume(Int_t volID) {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if ((GetHits()->GetHitProcess(n) == 38) && (GetHits()->GetHitVolume(n)) == volID) return true;
        return false;
    }

    Bool_t isHIoniInVolume(Int_t volID) {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if ((GetHits()->GetHitProcess(n) == 33) && (GetHits()->GetHitVolume(n)) == volID) return true;
        return false;
    }

    Bool_t isAlphaInVolume(Int_t volID) {
        if (GetParticleName() == "alpha") {
            for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
                if ((GetHits()->GetHitVolume(n)) == volID) return true;
        }
        return false;
    }

    Bool_t isNeutronInVolume(Int_t volID) {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if ((GetHits()->GetHitVolume(n) == volID) && (GetParticleName() == "neutron")) return true;
        return false;
    }

    Bool_t isArgonInVolume(Int_t volID) {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if ((GetHits()->GetHitVolume(n) == volID) && (GetParticleName().Contains("Ar"))) return true;
        return false;
    }

    Bool_t isNeonInVolume(Int_t volID) {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if ((GetHits()->GetHitVolume(n) == volID) && (GetParticleName().Contains("Ne"))) return true;
        return false;
    }

    Bool_t isXenonInVolume(Int_t volID) {
        for (int n = 0; n < GetHits()->GetNumberOfHits(); n++)
            if ((GetHits()->GetHitVolume(n) == volID) && (GetParticleName().Contains("Xe"))) return true;
        return false;
    }
     */
    /////////////////////////////////

    /// Prints the track information. N number of hits to print, 0 = all
    void PrintTrack(int maxHits = 0);

    // Constructor
    TRestGeant4Track();
    // Destructor
    ~TRestGeant4Track();

    ClassDef(TRestGeant4Track, 3);  // REST event superclass
};

#endif
