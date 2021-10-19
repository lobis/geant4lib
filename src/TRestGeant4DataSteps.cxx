//
// Created by lobis on 11/10/2021.
//

#include "TRestGeant4DataSteps.h"

#include "spdlog/spdlog.h"

void TRestGeant4DataSteps::Print() const {
    spdlog::warn("Step information - #steps: {}", fN);
    for (int i = 0; i < fN; i++) {
        spdlog::warn(
            "\tStep ID {} - process {} - energy deposited {:0.2f} keV - volume {}{} - position "
            "(mm) ({:03.2f}, {:03.2f}, {:03.2f})",                           //
            fStepID[i], fProcessName[i], fEnergy[i], fVolumeName[i],         //
            (fVolumeNamePost[i].IsNull() ? "" : "->" + fVolumeNamePost[i]),  //
            fPosition[i].x(), fPosition[i].y(), fPosition[i].z()             //
        );
    }
}