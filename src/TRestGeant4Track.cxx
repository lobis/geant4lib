///_______________________________________________________________________________
///_______________________________________________________________________________
///_______________________________________________________________________________
///
///
///             RESTSoft : Software for Rare Event Searches with TPCs
///
///             TRestGeant4Track.cxx
///
///             Base class from which to inherit all other event classes in REST
///
///             jul 2015:   First concept
///                 Created as part of the conceptualization of existing REST
///                 software.
///                 J. Galan
///_______________________________________________________________________________

#include "TRestGeant4Track.h"

using namespace std;

ClassImp(TRestGeant4Track);

TRestGeant4Track::TRestGeant4Track() = default;

TRestGeant4Track::~TRestGeant4Track() = default;

EColor TRestGeant4Track::GetParticleColor() {
    EColor color = kGray;

    if (GetParticleName() == "e-")
        color = kRed;
    else if (GetParticleName() == "e+")
        color = kBlue;
    else if (GetParticleName() == "alpha")
        color = kOrange;
    else if (GetParticleName() == "mu-")
        color = kViolet;
    else if (GetParticleName() == "gamma")
        color = kGreen;
    else
        cout << "TRestGeant4Track::GetParticleColor. Particle NOT found! Returning "
                "gray color."
             << endl;

    return color;
}

///////////////////////////////////////////////
/// \brief Function that returns the number of hit depositions found inside
/// the TRestGeant4Track. If a specific volume id is given as argument only
/// the hits of that specific volume will be counted.
/*
Int_t TRestGeant4Track::GetNumberOfHits(Int_t volID) {
    Int_t hits = 0;
    for (int n = 0; n < fHits.GetNumberOfHits(); n++) {
        if (volID != -1 && fHits.GetVolumeID(n) != volID) continue;
        hits++;
    }
    return hits;
}
*/

/*
TString TRestGeant4Track::GetProcessName(Int_t id) {
    if (id == 0)
        return "initStep";
    else if (id == 1)
        return "Transportation";
    else if (id == 2)
        return "ionIoni";
    else if (id == 3)
        return "phot";
    else if (id == 4)
        return "eIoni";
    else if (id == 5)
        return "eBrem";
    else if (id == 6)
        return "msc";
    else if (id == 7)
        return "compt";
    else if (id == 8)
        return "Rayl";
    else if (id == 9)
        return "conv";
    else if (id == 10)
        return "annihil";
    else if (id == 11)
        return "RadioactiveDecay";
    else if (id == 12)
        return "muIoni";
    else if (id == 20)
        return "e-Step";
    else if (id == 21)
        return "e+Step";
    else if (id == 22)
        return "ionStep";
    // else if ( id == 22 ) return "neutronStep";
    // else if ( id == 23 ) return "alphaStep";
    // else if ( id == 24 ) return "He3Step";
    else if (id == 30)
        return "muBrems";
    else if (id == 31)
        return "muPairProd";
    else if (id == 32)
        return "Decay";
    else if (id == 33)
        return "hIoni";
    else if (id == 34)
        return "hBrems";
    else if (id == 35)
        return "hPairProd";
    else if (id == 36)
        return "hadElastic";
    else if (id == 37)
        return "neutronInelastic";
    else if (id == 38)
        return "nCapture";
    else if (id == 39)
        return "nKiller";
    else if (id == 40)
        return "nuclearStopping";
    else if (id == 41)
        return "CoulombScat";
    else if (id == 42)
        return "photonNuclear";
    else if (id == 43)
        return "protonInelastic";
    else if (id == 44)
        return "pi-Inelastic";
    else if (id == 45)
        return "pi+Inelastic";
    else if (id == 46)
        return "tInelastic";
    else if (id == 47)
        return "dInelastic";
    else if (id == 48)
        return "electronNuclear";
    else if (id == 49)
        return "muonNuclear";
    else if (id == 50)
        return "positronNuclear";
    else if (id == 51)
        return "mu-Step";
    else if (id == 52)
        return "mu+Step";
    else if (id == 53)
        return "ePairProd";
    else if (id == 54)
        return "alphaInelastic";
    else if (id == 55)
        return "H3Inelastic";
    else if (id == 56)
        return "He3Inelastic";
    else if (id == 57)
        return "kaon+Inelastic";
    else if (id == 58)
        return "kaon-Inelastic";
    else if (id == 59)
        return "kaon0LInelastic";
    else if (id == 60)
        return "kaon0SInelastic";
    else if (id == 61)
        return "lambdaInelastic";
    else if (id == 70)
        return "nFission";
    else
        cout << "WARNING : The process ID : " << id << " could not be found" << endl;

    return "";
}
*/

/*
void TRestGeant4Track::PrintTrack(int maxHits) {
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
            "++++++++++++"
         << endl;
    cout.precision(10);
    cout << " SubEvent ID : " << fSubEventId << " Global timestamp : " << GetGlobalTime() << " seconds"
         << endl;
    cout.precision(5);
    cout << " Track ID : " << GetTrackID() << " Parent ID : " << GetParentID();
    cout << " Particle : " << GetParticleName() << " Time track length : " << GetTrackTimeLength() << " us"
         << endl;
    cout << " Origin : X = " << GetTrackOrigin().X() << "mm Y = " << GetTrackOrigin().Y()
         << "mm Z = " << GetTrackOrigin().Z() << "mm  Ekin : " << GetKineticEnergy() << " keV" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
            "++++++++++++"
         << endl;

    int nHits = GetNumberOfHits();
    if (maxHits > 0) {
        nHits = min(maxHits, GetNumberOfHits());
        cout << " Printing only the first " << nHits << " hits of the track" << endl;
    }

    TRestGeant4Hits* hits = GetHits();
    for (int i = 0; i < nHits; i++) {
        cout << " # Hit " << i << " # process : " << GetProcessName(hits->GetHitProcess(i))
             << " volume : " << hits->GetHitVolume(i) << " X : " << hits->GetX(i) << " Y : " << hits->GetY(i)
             << " Z : " << hits->GetZ(i) << " mm" << endl;
        cout << " Edep : " << hits->GetEnergy(i) << " keV Ekin : " << hits->GetKineticEnergy(i) << " keV"
             << " Global time : " << hits->GetTime(i) << " us" << endl;
    }
    cout << endl;
    cout.precision(2);
}
*/