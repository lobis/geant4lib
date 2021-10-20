
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

void TRestGeant4Track::PrintTrack(size_t numberOfHitsToPrintLimit) const { return; }