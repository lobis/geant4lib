//
// Created by lobis on 11/10/2021.
//

#ifndef REST_TRESTGEANT4DATASTEPS_H
#define REST_TRESTGEANT4DATASTEPS_H

#include <TString.h>
#include <TVector3.h>

#include <vector>

class G4Step;

class TRestGeant4Hits;

class TRestGeant4DataSteps {
   protected:
    Int_t fN = 0;
    std::vector<Int_t> fStepID;
    std::vector<TVector3> fPosition;
    std::vector<TVector3> fMomentumDirection;
    std::vector<Float_t> fTimeGlobal;
    std::vector<Float_t> fEnergy;
    std::vector<Float_t> fKineticEnergy;
    std::vector<Float_t> fKineticEnergyPost;
    std::vector<Float_t> fLength;
    std::vector<TString> fVolumeName;
    std::vector<TString> fVolumeNamePost;
    std::vector<Int_t> fVolumeID;
    std::vector<TString> fProcessName;
    std::vector<Int_t> fProcessID;
    std::vector<TString> fProcessType;
    std::vector<TString> fTargetNucleus;

   public:
    inline TRestGeant4DataSteps() = default;
    void InsertStep(const G4Step*);

    // Casting
    // operator TRestGeant4Hits() const;

    inline Int_t GetNumberOfSteps() const { return fN; }
    inline TVector3 GetPosition(size_t index) const { return fPosition[index]; }
    inline TVector3 GetDirection(size_t index) const { return fMomentumDirection[index]; }
    inline Float_t GetEnergy(size_t index) const { return fEnergy[index]; }
    inline Float_t GetKineticEnergy(size_t index) const { return fKineticEnergy[index]; }
    inline Float_t GetTime(size_t index) const { return fTimeGlobal[index]; }
    inline Int_t GetProcessID(size_t index) const { return fProcessID[index]; }
    inline Int_t GetVolumeID(size_t index) const { return fVolumeID[index]; }

    ClassDef(TRestGeant4DataSteps, 1);
};

#endif  // REST_TRESTGEANT4DATASTEPS_H
