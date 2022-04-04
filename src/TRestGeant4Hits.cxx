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

using namespace std;

ClassImp(TRestGeant4Hits);

TRestGeant4Hits::TRestGeant4Hits() : TRestHits() {
    // TRestGeant4Hits default constructor
}

TRestGeant4Hits::~TRestGeant4Hits() {
    // TRestGeant4Hits destructor
}

Double_t TRestGeant4Hits::GetEnergyInVolume(Int_t volID) const {
    Double_t en = 0;

    for (int n = 0; n < fNHits; n++)
        if (fVolumeID[n] == volID) en += GetEnergy(n);

    return en;
}

TVector3 TRestGeant4Hits::GetMeanPositionInVolume(Int_t volID) const {
    TVector3 pos;
    Double_t en = 0;
    for (int n = 0; n < fNHits; n++)
        if (fVolumeID[n] == volID) {
            pos += GetPosition(n) * GetEnergy(n);
            en += GetEnergy(n);
        }

    if (en == 0) {
        Double_t nan = TMath::QuietNaN();
        return {nan, nan, nan};
    }

    pos = (1. / en) * pos;
    return pos;
}

TVector3 TRestGeant4Hits::GetFirstPositionInVolume(Int_t volID) const {
    for (int n = 0; n < fNHits; n++)
        if (fVolumeID[n] == volID) return GetPosition(n);

    Double_t nan = TMath::QuietNaN();
    return {nan, nan, nan};
}

TVector3 TRestGeant4Hits::GetLastPositionInVolume(Int_t volID) const {
    for (int n = fNHits - 1; n >= 0; n--)
        if (fVolumeID[n] == volID) return GetPosition(n);

    Double_t nan = TMath::QuietNaN();
    return {nan, nan, nan};
}
