
#include "TRestGeant4Hits.h"

using namespace std;

ClassImp(TRestGeant4Hits);

TRestGeant4Hits::TRestGeant4Hits() : TRestHits() {}

TRestGeant4Hits::~TRestGeant4Hits() = default;

void TRestGeant4Hits::Print(size_t numberOfHitsToPrintLimit) const {
    cout << TString::Format("---> ---> Hit information - N hits: %d", fNHits) << endl;
    for (int i = 0; i < fNHits; i++) {
        if (numberOfHitsToPrintLimit > 0 && i >= numberOfHitsToPrintLimit) {
            cout << TString::Format("---> ---> Hit print limit of %zu reached (total hits: %d)",
                                    numberOfHitsToPrintLimit, fNHits)
                 << endl;
            return;
        }
        cout << TString::Format(
                    "---> ---> Hit ID %d - process %s - energy deposited %.2f keV - volume %s%s - "
                    "position (mm) (%.2f, %.2f, %.2f) - time: %.2f us",                              //
                    fID[i], fProcessName[i].Data(), fEnergy[i], fVolumeName[i].Data(),               //
                    (fVolumeNamePost[i].IsNull() ? "" : TString("->" + fVolumeNamePost[i]).Data()),  //
                    fX[i], fY[i], fZ[i], fT[i]                                                       //
                    )
             << endl;
    }
}

// Getters

TVector3 TRestGeant4Hits::GetPosition(size_t n) const { return {fX[n], fY[n], fZ[n]}; }

TVector3 TRestGeant4Hits::GetMomentumDirection(size_t n) const {
    return {fMomentumDirection[n].x(), fMomentumDirection[n].y(), fMomentumDirection[n].z()};
}

Float_t TRestGeant4Hits::GetKineticEnergy(size_t n, Bool_t post) const {
    if (post) {
        return fKineticEnergyPost[n];
    }
    return fKineticEnergy[n];
}

// Analysis methods

Float_t TRestGeant4Hits::GetEnergyInVolume(const TString& volumeName) const {
    Float_t energy = 0;
    for (int n = 0; n < fNHits; n++) {
        if (fVolumeName[n].EqualTo(volumeName)) {
            energy += GetEnergy(n);
        }
    }
    return energy;
}

TVector3 TRestGeant4Hits::GetMeanPositionInVolume(const TString& volumeName) const {
    TVector3 pos;
    Double_t energy = 0;
    for (int n = 0; n < fNHits; n++)
        if (fVolumeName[n].EqualTo(volumeName)) {
            pos += GetPosition(n) * GetEnergy(n);
            energy += GetEnergy(n);
        }

    if (energy == 0) {
        Double_t nan = TMath::QuietNaN();
        return {nan, nan, nan};
    }

    return pos * (1.0 / energy);
}

TVector3 TRestGeant4Hits::GetFirstPositionInVolume(const TString& volumeName) const {
    for (int n = 0; n < fNHits; n++)
        if (fVolumeName[n].EqualTo(volumeName)) {
            return GetPosition(n);
        }
    Double_t nan = TMath::QuietNaN();
    return {nan, nan, nan};
}

TVector3 TRestGeant4Hits::GetLastPositionInVolume(const TString& volumeName) const {
    for (int n = fNHits - 1; n >= 0; n--)
        if (fVolumeName[n].EqualTo(volumeName)) {
            return GetPosition(n);
        }
    Double_t nan = TMath::QuietNaN();
    return {nan, nan, nan};
}

size_t TRestGeant4Hits::GetNumberOfHitsInVolume(const TString& volumeName) const {
    size_t count = 0;
    for (int n = 0; n < fNHits; n++) {
        if (fVolumeName[n].EqualTo(volumeName)) {
            count += 1;
        }
    }
    return count;
}
