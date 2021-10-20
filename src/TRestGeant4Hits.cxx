///_______________________________________________________________________________
///_______________________________________________________________________________
///_______________________________________________________________________________
///
///
///             RESTSoft : Software for Rare Event Searches with TPCs
///
///             TRestGeant4Hits.cxx
///
///             Base class from which to inherit all other event classes in REST
///
///             jul 2015:   First concept
///                 Created as part of the conceptualization of existing REST
///                 software.
///                 J. Galan
///_______________________________________________________________________________

#include "TRestGeant4Hits.h"

ClassImp(TRestGeant4Hits);

TRestGeant4Hits::TRestGeant4Hits() : TRestGeant4DataSteps() {}

TRestGeant4Hits::~TRestGeant4Hits() {}

Double_t TRestGeant4Hits::GetEnergyInVolume(const TString& volumeName) {
    Double_t energy = 0;
    for (int n = 0; n < fNHits; n++) {
        if (fVolumeName[n].EqualTo(volumeName)) {
            energy += GetEnergy(n);
        }
    }
    return energy;
}

TVector3 TRestGeant4Hits::GetMeanPositionInVolume(const TString& volumeName) {
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

TVector3 TRestGeant4Hits::GetFirstPositionInVolume(const TString& volumeName) {
    for (int n = 0; n < fNHits; n++)
        if (fVolumeName[n].EqualTo(volumeName)) {
            return GetPosition(n);
        }
    Double_t nan = TMath::QuietNaN();
    return {nan, nan, nan};
}

TVector3 TRestGeant4Hits::GetLastPositionInVolume(const TString& volumeName) {
    for (int n = fNHits - 1; n >= 0; n--)
        if (fVolumeName[n].EqualTo(volumeName)) {
            return GetPosition(n);
        }
    Double_t nan = TMath::QuietNaN();
    return {nan, nan, nan};
}
