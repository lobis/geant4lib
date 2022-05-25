/*************************************************************************
 * This file is part of the REST software framework.                     *
 *                                                                       *
 * Copyright (C) 2016 GIFNA/TREX (University of Zaragoza)                *
 * For more information see http://gifna.unizar.es/trex                  *
 *                                                                       *
 * REST is free software: you can redistribute it and/or modify          *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * REST is distributed in the hope that it will be useful,               *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have a copy of the GNU General Public License along with   *
 * REST in $REST_PATH/LICENSE.                                           *
 * If not, see http://www.gnu.org/licenses/.                             *
 * For the list of contributors see $REST_PATH/CREDITS.                  *
 *************************************************************************/

#ifndef RestCore_TRestGeant4Metadata
#define RestCore_TRestGeant4Metadata

#include <TMath.h>
#include <TRestMetadata.h>
#include <TString.h>
#include <TVector2.h>
#include <TVector3.h>
#include <stdio.h>
#include <stdlib.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "TRestGeant4BiasingVolume.h"
#include "TRestGeant4GeometryInfo.h"
#include "TRestGeant4ParticleSource.h"
#include "TRestGeant4PhysicsInfo.h"
//------------------------------------------------------------------------------------------------------------------------
//
// * This section was added by Luis A. Obis (lobis@unizar.es) on 17/06/2019
//
// Here we add all the possible options for different configurations such as all the types of generators, etc.
// We use a structure called 'enum' and a function to clean the strings so that we can easily implement case
// insensitivity or more options such as ignoring underscores.
//

namespace g4_metadata_parameters {
std::string CleanString(std::string);

enum class generator_types {
    CUSTOM,
    VOLUME,
    SURFACE,
    POINT,
};
extern std::map<std::string, generator_types> generator_types_map;

enum class generator_shapes {
    GDML,
    WALL,
    CIRCLE,
    BOX,
    SPHERE,
    CYLINDER,
};
extern std::map<std::string, generator_shapes> generator_shapes_map;

enum class energy_dist_types {
    TH1D,
    MONO,
    FLAT,
    LOG,
};
extern std::map<std::string, energy_dist_types> energy_dist_types_map;

enum class angular_dist_types {
    TH1D,
    ISOTROPIC,
    FLUX,
    BACK_TO_BACK,
};
extern std::map<std::string, angular_dist_types> angular_dist_types_map;
}  // namespace g4_metadata_parameters

/// The main class to store the *Geant4* simulation conditions that will be used by *restG4*.
class TRestGeant4Metadata : public TRestMetadata {
   private:
    void Initialize() override;

    void InitFromConfigFile() override;

    void ReadGenerator();
    void ReadParticleSource(TRestGeant4ParticleSource* src, TiXmlElement* sourceDefinition);

    void ReadStorage();
    void ReadBiasing();

    /// Class used to store and retrieve geometry info
    TRestGeant4GeometryInfo fGeant4GeometryInfo;

    /// Class used to store and retrieve physics info such as process names
    TRestGeant4PhysicsInfo fGeant4PhysicsInfo;

    /// The version of Geant4 used to generate the data
    TString fGeant4Version;

    /// The local path to the GDML geometry
    TString fGeometryPath;  //!

    /// The filename of the GDML geometry
    TString fGdmlFilename;  //!

    /// A GDML geometry reference introduced in the header of the GDML main setup
    TString fGdmlReference;

    /// A GDML materials reference introduced in the header of the GDML of materials definition
    TString fMaterialsReference;

    /// Type of spatial generator (surface, volume, custom)
    TString fGenType;

    /// Shape of spatial generator (point, wall, gdml, sphere, etc)
    TString fGenShape;

    /// The volume name where the events are generated, in case of volume or
    /// surface generator types.
    TString fGenFrom;

    /// The position of the generator for virtual, and point, generator types.
    TVector3 fGenPosition;

    /// \brief A 3d-std::vector with the angles, measured in degrees, of a XYZ rotation
    /// applied to the virtual generator. This rotation is used by virtualWall,
    /// virtualCircleWall and virtualCylinder generators.
    TVector3 fGenRotationAxis;

    /// \brief degrees of rotation for generator virtual shape along the axis
    Double_t fGenRotationDegree;

    /// \brief The size of the generator. Stores up to three deminsions according to the shape
    /// box: length, width, height
    /// sphere: radius
    /// wall: length, width
    /// circle: radius
    /// cylinder: radius, length
    TVector3 fGenSize;

    /// \brief Defines density distribution of the generator shape. rho=F(x,y,z), in range 0~1
    TString fGenDensityFunction;

    /// \brief A 2d-std::vector storing the energy range, in keV, to decide if a particular
    /// event should be written to disk or not.
    TVector2 fEnergyRangeStored;

    /// \brief A std::vector to store the names of the active volumes.
    std::vector<TString> fActiveVolumes;

    /// \brief A std::vector to store the probability value to write to disk the hits in a
    /// particular event.
    std::vector<Double_t> fChance;

    /// \brief A std::vector to store the maximum step size at a particular volume.
    std::vector<Double_t> fMaxStepSize;

    /// \brief It the defines the primary source properties, particle type, momentum,
    /// energy, etc.
    std::vector<TRestGeant4ParticleSource*> fParticleSource;  //->

    /// \brief The number of biasing volumes used in the simulation. If zero, no biasing
    /// technique is used.
    Int_t fNBiasingVolumes;

    /// A std::vector containing the biasing volume properties.
    std::vector<TRestGeant4BiasingVolume> fBiasingVolumes;

    /// \brief The maximum target step size, in mm, allowed in Geant4 for the target
    /// volume (usually the gas volume). It is obsolete now. We define it at the active
    /// volume.
    Double_t fMaxTargetStepSize = 0;  //!

    /// \brief A time gap, in us, determinning if an energy hit should be considered (and
    /// stored) as an independent event.
    Double_t fSubEventTimeDelay;

    /// \brief Defines if a radioactive isotope decay is simulated in full chain
    /// (fFullChain=true), or just a single decay (fFullChain=false).
    Bool_t fFullChain;

    /// \brief The volume that serves as trigger for data storage. Only events that
    /// deposit a non-zero energy on this volume will be registered.
    TString fSensitiveVolume;

    /// The number of events simulated, or to be simulated.
    Int_t fNEvents;

    /// \brief The seed value used for Geant4 random event generator. If it is zero
    /// its value will be assigned using the system timestamp.
    Long_t fSeed = 0;

    /// \brief If this parameter is set to 'true' it will save all events even if they leave no energy in the
    /// sensitive volume (used for debugging purposes). It is set to 'false' by default.
    Bool_t fSaveAllEvents = false;

    /// If this parameter is set to 'true' it will print out on screen every time 10k events are reached.
    Bool_t fPrintProgress = false;  //!

    /// \brief If this parameter is enabled it will register tracks with no hits inside. This is the default
    /// behaviour. If it is disabled then empty tracks will not be written to disk at the risk of loosing
    /// traceability, but saving disk space and likely improving computing performance for extense events.
    Bool_t fRegisterEmptyTracks = true;

    /// The world magnetic field
    TVector3 fMagneticField = {0, 0, 0};

   public:
    /// \brief Returns the random seed that was used to generate the corresponding Geant4 dataset.
    Long_t GetSeed() const { return fSeed; }

    /// \brief Returns a reference to the geometry info
    inline const TRestGeant4GeometryInfo& GetGeant4GeometryInfo() const { return fGeant4GeometryInfo; }

    /// \brief Returns a reference to the physics info
    inline const TRestGeant4PhysicsInfo& GetGeant4PhysicsInfo() const { return fGeant4PhysicsInfo; }

    /// \brief Returns a string with the version of Geant4 used on the simulation event data
    inline TString GetGeant4Version() const { return fGeant4Version; }

    size_t GetGeant4VersionMajor() const;

    /// Returns the local path to the GDML geometry
    inline TString GetGeometryPath() const { return fGeometryPath; }

    /// Returns the main filename of the GDML geometry
    inline TString GetGdmlFilename() const { return fGdmlFilename; }

    /// Returns the reference provided at the GDML file header
    inline TString GetGdmlReference() const { return fGdmlReference; }

    /// Returns the reference provided at the materials file header
    inline TString GetMaterialsReference() const { return fMaterialsReference; }

    /// \brief Returns a std::string specifying the generator type (volume, surface, point,
    /// virtualWall, etc )
    inline TString GetGeneratorType() const { return fGenType; }

    /// \brief Returns a std::string specifying the generator shape (point, wall, box, etc )
    inline TString GetGeneratorShape() const { return fGenShape; }

    /// \brief Returns the name of the GDML volume where primary events are
    /// produced. This value has meaning only when using volume or surface
    /// generator types.
    inline TString GetGeneratedFrom() const { return fGenFrom; }

    /// \brief Returns the name of the GDML volume where primary events are
    /// produced. This value has meaning only when using volume or surface
    /// generator types.
    inline TString GetGDMLGeneratorVolume() const { return fGenFrom; }

    /// \brief Returns a 3d-std::vector with the position of the primary event
    /// generator. This value has meaning only when using point and virtual
    /// generator types.
    inline TVector3 GetGeneratorPosition() const { return fGenPosition; }

    /// \brief Returns a 3d-std::vector, fGenRotation, with the XYZ rotation angle
    /// values in degrees. This value is used by virtualWall, virtualCircleWall
    /// and virtualCylinder generator types.
    inline TVector3 GetGeneratorRotationAxis() const { return fGenRotationAxis; }

    /// \brief Returns the degree of rotation
    inline Double_t GetGeneratorRotationDegree() const { return fGenRotationDegree; }

    /// \brief Returns the main spatial dimension of virtual generator.
    /// It is the size of a  virtualBox.
    inline TVector3 GetGeneratorSize() const { return fGenSize; }

    /// \brief Returns the density function of the generator
    inline TString GetGeneratorSpatialDensity() const { return fGenDensityFunction; }

    /// \brief Returns true in case full decay chain simulation is enabled.
    inline Bool_t isFullChainActivated() const { return fFullChain; }

    /// \brief Returns the value of the maximum Geant4 step size in mm for the
    /// target volume.
    inline Double_t GetMaxTargetStepSize() const { return fMaxTargetStepSize; }

    /// \brief Returns the time gap, in us, required to consider a Geant4 hit as a
    /// new independent event. It is used to separate simulated events that in
    /// practice will appear as such in our detector. I.e. to separate multiple
    /// decay products (sometimes with years time delays) into independent events.
    inline Double_t GetSubEventTimeDelay() const { return fSubEventTimeDelay; }

    /// It returns true if save all events is active
    inline Bool_t GetSaveAllEvents() const { return fSaveAllEvents; }

    /// It returns true if `printProgress` parameter was set to true
    inline Bool_t PrintProgress() const { return fPrintProgress; }

    /// It returns false if `registerEmptyTracks` parameter was set to false.
    inline Bool_t RegisterEmptyTracks() const { return fRegisterEmptyTracks; }

    /// \brief Used exclusively by restG4 to set the value of the random seed used on
    /// Geant4 simulation.
    inline void SetSeed(Long_t seed) { fSeed = seed; }

    /// Enables or disables the save all events feature
    inline void SetSaveAllEvents(const Bool_t value) { fSaveAllEvents = value; }

    /// Sets the value of the Geant4 version
    inline void SetGeant4Version(const TString& versionString) { fGeant4Version = versionString; }

    ///  \brief Sets the generator type. I.e. volume, surface, point, virtualWall,
    ///  virtualCylinder, etc.
    inline void SetGeneratorType(TString type) { fGenType = type; }

    ///  \brief Sets the generator main spatial dimension. In a virtual generator is the
    ///  radius of cylinder, size of wall, etc.
    inline void SetGeneratorSize(const TVector3& size) { fGenSize = size; }

    ///  Enables/disables the full chain decay generation.
    inline void SetFullChain(Bool_t fullChain) { fFullChain = fullChain; }

    ///  Sets the position of the virtual generator using a TVector3.
    inline void SetGeneratorPosition(const TVector3& pos) { fGenPosition = pos; }

    ///  Sets the position of the virtual generator using x,y,z coordinates.
    inline void SetGeneratorPosition(double x, double y, double z) { fGenPosition = TVector3(x, y, z); }

    /// Sets the number of events to be simulated.
    inline void SetNEvents(Int_t n) { fNEvents = n; }

    /// It sets the location of the geometry files
    inline void SetGeometryPath(std::string path) { fGeometryPath = path; }

    /// It sets the main filename to be used for the GDML geometry
    inline void SetGdmlFilename(std::string gdmlFile) { fGdmlFilename = gdmlFile; }

    /// Returns the reference provided at the GDML file header
    inline void SetGdmlReference(std::string reference) { fGdmlReference = reference; }

    /// Returns the reference provided at the materials file header
    inline void SetMaterialsReference(std::string reference) { fMaterialsReference = reference; }

    /// Returns the number of events to be simulated.
    inline Int_t GetNumberOfEvents() const { return fNEvents; }
    ///////////////////////////////////////////////////////////

    // Direct access to sources definition in primary generator
    ///////////////////////////////////////////////////////////
    /// Returns the number of primary event sources defined in the generator.
    inline Int_t GetNumberOfSources() const { return fParticleSource.size(); }

    /// Returns the name of the particle source with index n (Geant4 based names).
    inline TRestGeant4ParticleSource* GetParticleSource(int n) { return fParticleSource[n]; }

    /// Remove all the particle sources.
    void RemoveParticleSources();

    /// Adds a new particle source.
    void AddParticleSource(TRestGeant4ParticleSource* src);
    ///////////////////////////////////////////////////////////

    // Direct access to biasing volumes definition
    //////////////////////////////////////////////
    /// Returns the number of biasing volumes defined

    inline size_t GetNumberOfBiasingVolumes() const { return fBiasingVolumes.size(); }

    /// Return the biasing volume with index n
    inline TRestGeant4BiasingVolume GetBiasingVolume(int n) { return fBiasingVolumes[n]; }

    /// \brief Returns the number of biasing volumes defined. If 0 the biasing technique
    /// is not being used.
    inline Int_t isBiasingActive() const { return fBiasingVolumes.size(); }

    /// Returns a std::string with the name of the sensitive volume.
    inline TString GetSensitiveVolume() const { return fSensitiveVolume; }

    /// Sets the name of the sensitive volume
    inline void SetSensitiveVolume(const TString& sensitiveVolume) { fSensitiveVolume = sensitiveVolume; }

    /// \brief Returns the probability per event to register (write to disk) hits in the
    /// storage volume with index n.
    inline Double_t GetStorageChance(Int_t n) { return fChance[n]; }

    /// Returns the probability per event to register (write to disk) hits in a
    /// GDML volume given its geometry name.
    Double_t GetStorageChance(TString vol);

    Double_t GetMaxStepSize(TString vol);

    /// Returns the minimum event energy required for an event to be stored.
    inline Double_t GetMinimumEnergyStored() const { return fEnergyRangeStored.X(); }

    /// Returns the maximum event energy required for an event to be stored.
    inline Double_t GetMaximumEnergyStored() const { return fEnergyRangeStored.Y(); }

    /// \brief Returns the number of active volumes, or geometry volumes that have been
    /// selected for data storage.
    inline Int_t GetNumberOfActiveVolumes() const { return fActiveVolumes.size(); }

    /// Returns a std::string with the name of the active volume with index n
    inline TString GetActiveVolumeName(Int_t n) { return fActiveVolumes[n]; }

    /// Returns the world magnetic field in Tesla
    inline TVector3 GetMagneticField() const { return fMagneticField; }

    Int_t GetActiveVolumeID(TString name);

    Bool_t isVolumeStored(TString volName);

    void SetActiveVolume(const TString& name, Double_t chance, Double_t maxStep = 0);

    void PrintMetadata() override;

    TRestGeant4Metadata();
    TRestGeant4Metadata(const char* configFilename, const std::string& name = "");

    ~TRestGeant4Metadata();

    ClassDef(TRestGeant4Metadata, 10);

    // Allow modification of otherwise inaccessible / immutable members that shouldn't be modified by the user
    friend class SteppingAction;
    friend class DetectorConstruction;
};
#endif  // RestCore_TRestGeant4Metadata
