//
// Created by lobis on 11/10/2021.
//

#include "TRestGeant4DataEvent.h"

#include "TRestGeant4Event.h"

TRestGeant4DataEvent::operator TRestGeant4Event() const {
    auto event = TRestGeant4Event();

    event.SetID(fEventID);

    for (const auto& track : fTracks) {
        event.AddTrack(track);
    }

    return event;
}
