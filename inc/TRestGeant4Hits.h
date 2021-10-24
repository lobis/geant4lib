
#ifndef RestLibGeant4_TRestGeant4Hits
#define RestLibGeant4_TRestGeant4Hits

#include <TRestHits.h>

class G4Step;

class TRestGeant4Hits : public TRestHits {
   public:
    TRestGeant4Hits();
    ~TRestGeant4Hits() override;
    void InsertStep(const G4Step*);  // Not defined in Geant4Lib (defined and used in restG4 to insert data)
                                     /*
                                      * Data members defined in TRestHits
                                      */
   public:                           // Data members defined in TRestHits (not required to be declared here)
    Int_t fNHits = 0;
    Double_t fTotEnergy;
    std::vector<Float_t> fX;
    std::vector<Float_t> fY;
    std::vector<Float_t> fZ;
    std::vector<Float_t> fT;
    std::vector<Float_t> fEnergy;
    std::vector<REST_HitType> fType = {};  // We do not need this for Geant4 right?

   protected:
    std::vector<Int_t> fID;
    std::vector<TVector3> fMomentumDirection;
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
    // TRestHits derived Getters
    inline size_t GetSize() const { return fNHits; }             // defined in TRestHits but not const
    inline size_t GetNumberOfHits() const { return GetSize(); }  // defined in TRestHits but not const
    size_t GetNumberOfHitsInVolume(const TString& volumeName) const;

    TVector3 GetPosition(size_t n) const;
    /* Not sure why the parent class GetX/Y/Z don't work, probably something to
        do with Float_t to Double_t conversion*/
    Double_t GetX(size_t n) const { return GetPosition(n).x(); }
    Double_t GetY(size_t n) const { return GetPosition(n).y(); }
    Double_t GetZ(size_t n) const { return GetPosition(n).z(); }

    Float_t GetEnergy(size_t n) const { return fEnergy[n]; }
    Float_t GetTotalEnergy() const { return fTotEnergy; }

    // Basic Getters
    inline Int_t GetID(size_t n) const { return fID[n]; }
    inline Int_t GetTime(size_t n) const { return fT[n]; }
    TVector3 GetMomentumDirection(size_t n) const;
    Float_t GetKineticEnergy(size_t n, Bool_t post = false) const;
    inline Float_t GetKineticEnergyPost(size_t n) const { return GetKineticEnergy(n, true); }
    inline Float_t GetLength(size_t n) const { return fLength[n]; }
    inline TString GetVolumeName(size_t n) const { return fVolumeName[n]; }
    inline TString GetfVolumeNamePost(size_t n) const { return fVolumeNamePost[n]; }
    inline Int_t GetVolumeID(size_t n) const { return fVolumeID[n]; }
    inline TString GetProcessName(size_t n) const { return fProcessName[n]; }
    inline Int_t GetProcessID(size_t n) const { return fProcessID[n]; }
    inline TString GetProcessType(size_t n) const { return fProcessType[n]; }
    inline TString GetTargetNucleus(size_t n) const { return fTargetNucleus[n]; }
    // Basic Setters:
    // There are no setters! Geant4Lib Data Classes should be initialized in restG4 from Geant4 classes

   public:
    void Print(size_t numberOfHitsToPrintLimit = 0) const;
    // Advanced Getters (analysis)
    Float_t GetEnergyInVolume(const TString& volumeName) const;
    TVector3 GetMeanPositionInVolume(const TString& volumeName) const;
    TVector3 GetFirstPositionInVolume(const TString& volumeName) const;
    TVector3 GetLastPositionInVolume(const TString& volumeName) const;

    ClassDef(TRestGeant4Hits, 7);
};
#endif
