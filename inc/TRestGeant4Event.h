
#ifndef RestLibGeant4_TRestGeant4Event
#define RestLibGeant4_TRestGeant4Event

#include <TGraph.h>
#include <TGraph2D.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <TObject.h>
#include <TRestEvent.h>
#include <TRestGeant4Track.h>
#include <TVector3.h>

#include <iostream>
#include <map>

/// An event class to store geant4 generated event information

class G4Event;

class TRestGeant4Event : public TRestEvent {
   public:
    inline TRestGeant4Event() : TRestEvent() { Initialize(); }
    explicit TRestGeant4Event(
        const G4Event*);  // Not defined in Geant4Lib (defined and used in restG4 to insert data)

    inline ~TRestGeant4Event() override = default;

    void Initialize() override;

   protected:
    Int_t fRunOrigin;

    Int_t fRunID; // Geant4 Run ID
    //Int_t fEventID;
    //Int_t fSubEventID;

    TVector3 fPrimaryEventOrigin;

    Float_t fSensitiveVolumeEnergy;
    Float_t fTotalDepositedEnergy;

    std::vector<TString> fPrimaryParticleName;
    std::vector<Float_t> fPrimaryEnergy;
    std::vector<TVector3> fPrimaryPosition;
    std::vector<TVector3> fPrimaryDirection;

    TString fSubEventPrimaryParticleName = "";
    Float_t fSubEventPrimaryEnergy;
    TVector3 fSubEventPrimaryPosition;
    TVector3 fSubEventPrimaryDirection;

    std::vector<TRestGeant4Track> fTracks;

    TRestGeant4Hits fInitialStep;  //! first step (with SteppingVerbose) occurs before track is spawned!

    std::map<TString, Float_t> fEnergyDepositedInVolumeMap{};

    std::map<Int_t, Int_t> fTrackIDToIndex{};  //! // Used to retrieve track by ID faster

   public:
    void InsertTrack(const G4Track*);
    void UpdateTrack(const G4Track*);
    void InsertStep(const G4Step*);

    inline Int_t GetEventID() const { return fEventID; }
    inline Int_t GetSubEventID() const { return fSubEventID; }
    inline void SetSubEventID(Int_t subEventID) { fSubEventID = subEventID; }
    inline Float_t GetSensitiveVolumeEnergy() const { return fSensitiveVolumeEnergy; }
    inline void AddSensitiveVolumeEnergy(Float_t energy) { fSensitiveVolumeEnergy += energy; }
    inline void AddTotalEnergy(Float_t energy) { fTotalDepositedEnergy += energy; }
    inline Bool_t IsEmpty() const { return fTracks.empty(); }

    inline TVector3 GetPrimaryEventOrigin() { return fPrimaryPosition[0]; }

    inline size_t GetNumberOfPrimaries() const { return fPrimaryParticleName.size(); }
    inline TString GetPrimaryEventParticleName(Int_t n = 0) const { return fPrimaryParticleName[n]; }
    inline TVector3 GetPrimaryEventPosition(Int_t n = 0) const { return fPrimaryPosition[n]; }
    inline TVector3 GetPrimaryEventDirection(Int_t n = 0) const { return fPrimaryDirection[n]; }
    inline Double_t GetPrimaryEventEnergy(Int_t n = 0) { return fPrimaryEnergy[n]; }

    inline size_t GetNumberOfTracks() const { return fTracks.size(); }
    size_t GetNumberOfHits() const;

   private:
    Double_t fMinX, fMaxX;            //!
    Double_t fMinY, fMaxY;            //!
    Double_t fMinZ, fMaxZ;            //!
    Double_t fMinEnergy, fMaxEnergy;  //!

   protected:
    // TODO These graphs should be placed in TRestTrack?
    // (following GetGraph implementation in TRestDetectorSignal)
    TGraph* fXZHitGraph;  //!
    TGraph* fYZHitGraph;  //!
    TGraph* fXYHitGraph;  //!
    // TGraph2D *fXYZHitGraph; //! (TODO to implement XYZ visualization)

    std::vector<TGraph*> fXYPcsMarker;  //!
    std::vector<TGraph*> fYZPcsMarker;  //!
    std::vector<TGraph*> fXZPcsMarker;  //!

    TMultiGraph* fXZMultiGraph;  //!
    TMultiGraph* fYZMultiGraph;  //!
    TMultiGraph* fXYMultiGraph;  //!
    // TMultiGraph *fXYZMultiGraph; //! (TODO to implement XYZ visualization)

    TH2F* fXYHisto;  //!
    TH2F* fXZHisto;  //!
    TH2F* fYZHisto;  //!

    TH1D* fXHisto;  //!
    TH1D* fYHisto;  //!
    TH1D* fZHisto;  //!

    TLegend* fLegend_XY;  //!
    TLegend* fLegend_XZ;  //!
    TLegend* fLegend_YZ;  //!

    std::vector<Int_t> legendAdded;  //!

    Int_t fTotalHits;  //!

    TMultiGraph* GetXZMultiGraph(Int_t gridElement, std::vector<TString> pcsList, Double_t minPointSize = 0.4,
                                 Double_t maxPointSize = 4);
    TMultiGraph* GetYZMultiGraph(Int_t gridElement, std::vector<TString> pcsList, Double_t minPointSize = 0.4,
                                 Double_t maxPointSize = 4);
    TMultiGraph* GetXYMultiGraph(Int_t gridElement, std::vector<TString> pcsList, Double_t minPointSize = 0.4,
                                 Double_t maxPointSize = 4);

    TH2F* GetXYHistogram(Int_t gridElement, std::vector<TString> optList);
    TH2F* GetXZHistogram(Int_t gridElement, std::vector<TString> optList);
    TH2F* GetYZHistogram(Int_t gridElement, std::vector<TString> optList);

    TH1D* GetXHistogram(Int_t gridElement, std::vector<TString> optList);
    TH1D* GetYHistogram(Int_t gridElement, std::vector<TString> optList);
    TH1D* GetZHistogram(Int_t gridElement, std::vector<TString> optList);

   public:
    void SetBoundaries();
    void SetBoundaries(Double_t xMin, Double_t xMax, Double_t yMin, Double_t yMax, Double_t zMin,
                       Double_t zMax);

    //    Int_t isVolumeStored(int n) { return fVolumeStored[n]; }
    TRestGeant4Track* GetTrack(int n) { return (TRestGeant4Track*)&fTracks[n]; }
    TRestGeant4Track* GetTrackByID(int id);

    Double_t GetTotalDepositedEnergy() const { return fTotalDepositedEnergy; }
    Double_t GetTotalDepositedEnergyFromTracks();
    Float_t GetEnergyDepositedInVolume(const TString& volumeName) const {
        return fEnergyDepositedInVolumeMap.at(volumeName);
    }

    TVector3 GetMeanPositionInVolume(const TString& volumeName);
    TVector3 GetFirstPositionInVolume(const TString& volumeName);
    TVector3 GetLastPositionInVolume(const TString& volumeName);
    TVector3 GetPositionDeviationInVolume(const TString& volumeName);

    TRestHits GetHits();
    TRestHits GetHitsInVolume(const TString& volumeName);

    Int_t GetNumberOfTracksForParticle(const TString& particleName);
    Float_t GetEnergyDepositedByParticle(const TString& particleName);

    Int_t GetLowestTrackID() {
        Int_t lowestID = 0;
        if (GetNumberOfTracks() > 0) lowestID = GetTrack(0)->GetTrackID();

        for (int i = 0; i < GetNumberOfTracks(); i++) {
            TRestGeant4Track* tr = GetTrack(i);
            if (tr->GetTrackID() < lowestID) lowestID = tr->GetTrackID();
        }

        return lowestID;
    }

    /// maxTracks : number of tracks to print, 0 = all
    void PrintActiveVolumes();

    void PrintEvent(size_t numberOfTracksToPrintLimit = 0, size_t numberOfHitsToPrintLimit = 0);
    inline void Print(size_t numberOfTracksToPrintLimit = 0, size_t numberOfHitsToPrintLimit = 0) {
        PrintEvent(numberOfTracksToPrintLimit, numberOfHitsToPrintLimit);
    }

    TPad* DrawEvent(TString option = "") { return DrawEvent(option, true); }
    TPad* DrawEvent(TString option, Bool_t autoBoundaries);

    ClassDef(TRestGeant4Event, 7);  // REST event superclass
};
#endif
