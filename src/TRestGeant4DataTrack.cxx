//
// Created by lobis on 11/10/2021.
//

#include "TRestGeant4DataTrack.h"

#include "TRestGeant4Track.h"
#include "spdlog/spdlog.h"

TRestGeant4DataTrack::operator TRestGeant4Track() const {
    auto track = TRestGeant4Track();

    // Add track info
    track.SetTrackID(fTrackID);
    track.SetParentID(fParentID);
    track.SetParticleName(fParticleName);
    track.SetKineticEnergy(fInitialKineticEnergy);
    // Add hits
    for (int i = 0; i < fSteps.GetNumberOfSteps(); i++) {
        track.AddG4Hit(fSteps.GetPosition(i), fSteps.GetEnergy(i), fSteps.GetTime(i), fSteps.GetProcessID(i),
                       fSteps.GetVolumeID(i), fSteps.GetKineticEnergy(i), fSteps.GetDirection(i));
    }

    return track;
}
void TRestGeant4DataTrack::Print() const {
    spdlog::warn(
        "Track ID: {} - Parent ID: {} - Particle: {} - Creator process: {} - Initial KE: {:0.2f} keV - "
        "#secondaries: {}",
        fTrackID, fParentID, fParticleName, fCreatorProcess, fInitialKineticEnergy, fNumberOfSecondaries);

    fSteps.Print();
}