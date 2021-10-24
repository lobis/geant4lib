
#include "TRestGeant4Track.h"

using namespace std;

ClassImp(TRestGeant4Track);

/// \brief Returns the origin of the track which is the position of the first step,
/// which has the process name of `Init`
TVector3 TRestGeant4Track::GetTrackOrigin() const {
    if (fHits.GetProcessName(0) != "Init") {
        cout << "ERROR IN TRestGeant4Track::GetTrackOrigin, please check" << endl;
        exit(1);
    }
    return fHits.GetPosition(0);
}

size_t TRestGeant4Track::GetNumberOfHitsInVolume(const TString& volumeName) const {
    return fHits.GetNumberOfHitsInVolume(volumeName);
}

EColor TRestGeant4Track::GetParticleColor() const {
    EColor color = kGray;

    if (GetParticleName() == "e-") {
        color = kRed;
    } else if (GetParticleName() == "e+") {
        color = kBlue;
    } else if (GetParticleName() == "alpha") {
        color = kOrange;
    } else if (GetParticleName() == "mu-") {
        color = kViolet;
    } else if (GetParticleName() == "gamma") {
        color = kGreen;
    }

    return color;
}

void TRestGeant4Track::PrintTrack(size_t numberOfHitsToPrintLimit) const {
    TString secondariesString;
    if (!fSecondaryTrackIDs.empty()) {
        secondariesString += "{";
        for (const auto& trackID : fSecondaryTrackIDs) {
            secondariesString += TString::Format("%d", trackID);
            if (trackID != fSecondaryTrackIDs.back()) {
                secondariesString += ", ";
            }
        }
        secondariesString += "}";
    }

    cout << TString::Format(
                "---> Track information - track ID: %d - Parent ID: %d - Particle: %s - Creator Process: %s "
                "- Initial KE: %.2f keV - Length: %.2f mm - Time Span: %.2f us - Secondaries(%zu): %s",
                fTrackID, fParentID, fParticleName.Data(), fCreatorProcess.Data(), fInitialKineticEnergy,
                fTrackLength, GetTrackTimeLength(), fSecondaryTrackIDs.size(), secondariesString.Data())
         << endl;

    fHits.Print(numberOfHitsToPrintLimit);
}