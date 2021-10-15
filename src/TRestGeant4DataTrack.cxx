//
// Created by lobis on 11/10/2021.
//

#include "TRestGeant4DataTrack.h"

#include "spdlog/spdlog.h"

void TRestGeant4DataTrack::Print() const {
    spdlog::warn(
        "Track ID: {} - Parent ID: {} - Particle: {} - Creator process: {} - Initial KE: {:0.2f} keV - "
        "#secondaries: {}",
        fTrackID, fParentID, fParticleName, fCreatorProcess, fInitialKineticEnergy, fNumberOfSecondaries);

    fSteps.Print();
}