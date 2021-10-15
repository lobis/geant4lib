//
// Created by lobis on 15/10/2021.
//

#ifndef REST_TRESTGEANT4GENERATOR_H
#define REST_TRESTGEANT4GENERATOR_H

#include <TRestMetadata.h>
#include <TString.h>

#include <set>

#include "TRestGeant4ParticleSource.h"

class TRestGeant4Generator : public TRestMetadata {
   protected:
    static std::set<std::string> fAvailableGeneratorTypes;
    static std::set<std::string> fAvailableShapeTypes;
    static std::set<std::string> fAvailableEnergyTypes;
    static std::set<std::string> fAvailableAngularTypes;

    TString fGeneratorType{};
    TString fShapeType{};
    TString fEnergyType{};
    TString fAngularType{};

    TVector3 fPosition;

    TVector3 fRotation1;
    TVector3 fRotation2;

    TString fDensity;
    TString fFromVolume;

    std::vector<TRestGeant4ParticleSource*> fParticleSource;

   public:
    TRestGeant4Generator() = default;
    TRestGeant4Generator(const TiXmlElement*);

    void InitFromConfigFile() override;

    ClassDef(TRestGeant4Generator, 1);
};

#endif  // REST_TRESTGEANT4GENERATOR_H
