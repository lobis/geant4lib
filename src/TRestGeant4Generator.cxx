//
// Created by lobis on 15/10/2021.
//

#include "TRestGeant4Generator.h"

using namespace std;

set<string> TRestGeant4Generator::fAvailableGeneratorTypes = {"Custom", "Volume", "Surface", "Point"};
set<string> TRestGeant4Generator::fAvailableShapeTypes = {"Gdml", "Plate",  "Wall",
                                                          "Box",  "Sphere", "Cylinder"};
set<string> TRestGeant4Generator::fAvailableEnergyTypes = {"TH1D", "Mono", "Flat", "Log"};
set<string> TRestGeant4Generator::fAvailableAngularTypes = {"TH1D", "Isotropic", "Flux", "BackToBack"};

TString ToLowerCase(const TString& value) {
    string s = (string)value;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return {s.c_str()};
}

map<TString, TString> GetParameterMap(const TiXmlElement* element) {
    map<TString, TString> parameterMap;

    auto attribute = element->FirstAttribute();

    while (attribute) {
        auto value = attribute->Value();
        auto name = ToLowerCase(attribute->Name());

        // Parameters cannot be duplicated (XML syntax)
        parameterMap[name] = value;

        attribute = attribute->Next();
    }

    return parameterMap;
}

Bool_t IsParameterInSet(const TString& parameterName, const set<string>& availableParameters) {
    set<string> lowerCaseSet;
    for (auto& name : availableParameters) {
        lowerCaseSet.insert((string)ToLowerCase(name));
    }
    return lowerCaseSet.count((string)ToLowerCase(parameterName)) > 0;
}

void TRestGeant4Generator::InitFromConfigFile() {
    cout << "TRestGeant4Generator::InitFromConfigFile - ERROR - NOT IMPLEMENTED!" << endl;
    exit(1);
}

TRestGeant4Generator::TRestGeant4Generator(const TiXmlElement* generator) : TRestGeant4Generator() {
    auto generatorDefinition = const_cast<TiXmlElement*>(generator);
    // XML section named "generator"
    auto parameterMap = GetParameterMap(generator);

    for (const auto& [key, value] : parameterMap) {
        cout << key << ": " << value << endl;
    }

    /*
     * We check all parameters to see if they have valid names only
     */

    // Generator type
    fGeneratorType = GetParameter("type", generatorDefinition);
    if (fGeneratorType == PARAMETER_NOT_FOUND_STR) {
        cout << "TRestGeant4Generator - parameter 'type' not declared, setting it to default value 'Volume'"
             << endl;
        fGeneratorType = "Volume";
    }
    if (!IsParameterInSet(fGeneratorType, fAvailableGeneratorTypes)) {
        cout << "TRestGeant4Generator - parameter 'type' with value '" << fGeneratorType
             << "' is not a valid parameter. Valid parameters are: ";
        for (const auto& name : fAvailableGeneratorTypes) {
            cout << name << " ";
        }
        cout << endl;
    }

    // Generator shape
    fShapeType = GetParameter("shape", generatorDefinition);
    if (fShapeType == PARAMETER_NOT_FOUND_STR) {
        cout << "TRestGeant4Generator - parameter 'shape' not declared, setting it to default value 'Box'"
             << endl;
        fShapeType = "Box";
    }
    if (!IsParameterInSet(fShapeType, fAvailableShapeTypes)) {
        cout << "TRestGeant4Generator - parameter 'shape' with value '" << fShapeType
             << "' is not a valid parameter. Valid parameters are: ";
        for (const auto& name : fAvailableShapeTypes) {
            cout << name << " ";
        }
        cout << endl;
    }

    // Generator "from" volume
    fFromVolume = GetParameter("from", generatorDefinition);
    if (fFromVolume != PARAMETER_NOT_FOUND_STR) {
        // Raise exception if we have explicitly defined parameters that are incompatible/useless with "from"
        bool isInvalid = false;
        for (const auto& name : {"position", "rot1", "rot2"}) {
            if (parameterMap.count(name) > 0) {
                cout << "Defining '" << name << "' along 'from' volume is not allowed" << endl;
                isInvalid = true;
            }
        }
        if (isInvalid) {
            exit(1);
        }
    }

    // Position
    if (parameterMap.count("position") == 0) {
        // position not defined, this is only OK when using generators such as Gdml
        if (!fShapeType.EqualTo("Gdml", TString::kIgnoreCase)) {
            cout << "TRestGeant4Generator - need to specify parameter 'position'" << endl;
            exit(1);
        }
    } else {
        if (fShapeType.EqualTo("Gdml", TString::kIgnoreCase)) {
            cout << "TRestGeant4Generator - cannot specify position for generator of type 'Gdml'" << endl;
            exit(1);
        }
    }
    auto position = Get3DVectorParameterWithUnits("position", generatorDefinition, TVector3());

    // Rotation
    if (parameterMap.count("rot1") >= 0 || parameterMap.count("rot2") >= 0) {
        if (fShapeType.EqualTo("Gdml", TString::kIgnoreCase)) {
            cout << "TRestGeant4Generator - cannot specify rotation for generator of type 'Gdml'" << endl;
            exit(1);
        }
    }

    fRotation1 = StringTo3DVector(GetParameter("rot1", generatorDefinition, "(1,0,0)"));
    fRotation2 = StringTo3DVector(GetParameter("rot2", generatorDefinition, "(0,1,0)"));

    // TODO: validate this
    fDensity = GetParameter("densityFunc", generatorDefinition, "1");

    exit(1);
}
