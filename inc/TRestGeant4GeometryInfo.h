//
// Created by lobis on 3/5/2022.
//

#ifndef REST_TRESTGEANT4GEOMETRYINFO_H
#define REST_TRESTGEANT4GEOMETRYINFO_H

#include <TString.h>
#include <TVector3.h>

#include <map>
#include <set>
#include <vector>

class G4VPhysicalVolume;

class TRestGeant4GeometryInfo {
    ClassDef(TRestGeant4GeometryInfo, 2);

   private:
    bool fIsAssembly = false;

   public:
    // Insertion order is important for GDML containers. These containers are filled from GDML only not Geant4
    std::vector<TString> fGdmlNewPhysicalNames;
    std::vector<TString> fGdmlLogicalNames;

    std::map<TString, TString>
        fGeant4PhysicalNameToNewPhysicalNameMap; /*
                                                  * only makes sense when using assembly
                                                  */

    std::map<TString, TString> fPhysicalToLogicalVolumeMap;
    std::map<TString, std::vector<TString> > fLogicalToPhysicalMap;
    // many physical volumes can point to one single logical
    std::map<TString, TString> fLogicalToMaterialMap;
    std::map<TString, TVector3> fPhysicalToPositionInWorldMap;

   public:
    inline TRestGeant4GeometryInfo() = default;

    void PopulateFromGdml(const TString&);

    TString GetAlternativeNameFromGeant4PhysicalName(const TString&) const;
    TString GetGeant4PhysicalNameFromAlternativeName(const TString&) const;

    Int_t GetIDFromVolumeName(const TString&) const;

    void PopulateFromGeant4World(const G4VPhysicalVolume*);

    std::vector<TString> GetAllLogicalVolumes() const;
    std::vector<TString> GetAllPhysicalVolumes() const;
    std::vector<TString> GetAllAlternativePhysicalVolumes() const;

    std::vector<TString> GetAllLogicalVolumesMatchingExpression(const TString&) const;
    std::vector<TString> GetAllPhysicalVolumesMatchingExpression(const TString&) const;

    inline bool IsValidGdmlName(const TString& volume) const {
        for (const auto& name : fGdmlNewPhysicalNames) {
            if (name == volume) {
                return true;
            }
        }
        return false;
    }

    inline bool IsValidPhysicalVolume(const TString& volume) const {
        return fPhysicalToLogicalVolumeMap.count(volume) > 0;
    }
    inline bool IsValidLogicalVolume(const TString& volume) const {
        return fLogicalToPhysicalMap.count(volume) > 0;
    }
    inline std::vector<TString> GetAllPhysicalVolumesFromLogical(const TString& logicalVolume) const {
        if (IsValidLogicalVolume(logicalVolume)) {
            return fLogicalToPhysicalMap.at(logicalVolume);
        }
        return {};
    }

    inline bool IsAssembly() const { return fIsAssembly; }

    void Print() const;
};

#endif  // REST_TRESTGEANT4GEOMETRYINFO_H
