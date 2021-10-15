//
// Created by lobis on 11/10/2021.
//

#include "TRestGeant4DataEvent.h"

#include "spdlog/spdlog.h"

void TRestGeant4DataEvent::Print() const {
    spdlog::warn("Printing information for event ID {}", fEventID);

    for (const auto& track : fTracks) {
        track.Print();
    }
}