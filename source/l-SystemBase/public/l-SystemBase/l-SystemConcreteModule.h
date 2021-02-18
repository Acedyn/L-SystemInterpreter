#pragma once

#include "l-SystemParameters.h"

#include <vector>
#include <string>
#include <iostream>

class LSystemParameters;
class LSystemAbstractModule;

// Element composed of a name and parameters that can form words
class LSystemConcreteModule
{
public:
    // Constructors / desctructors
    LSystemConcreteModule(LSystemParameters* _parameters = nullptr) : 
        name('\0'), 
        globalParameters(_parameters) { }
    LSystemConcreteModule(
        char _name, 
        LSystemParameters* _parameters = nullptr, 
        std::vector<LSystemAbstractModule*> _moduleParameters = std::vector<LSystemAbstractModule*>()) :
        name(_name),
        globalParameters(_parameters),
        moduleParameters(_moduleParameters) { }
    LSystemConcreteModule(
        char _name, 
        std::vector<float> _parameterValues, 
        LSystemParameters* _parameters = nullptr,
        std::vector<LSystemAbstractModule*> _moduleParameters = std::vector<LSystemAbstractModule*>());
    LSystemConcreteModule(
        char _name, 
        std::string _parameterString, 
        LSystemParameters* _parameters = nullptr,
        std::vector<LSystemAbstractModule*> _moduleParameters = std::vector<LSystemAbstractModule*>());
    ~LSystemConcreteModule() { }
    
    // Operators
    bool operator==(const LSystemConcreteModule& _other) const;
    bool operator!=(const LSystemConcreteModule& _other) const;
    bool operator==(const LSystemAbstractModule& _other) const;
    bool operator!=(const LSystemAbstractModule& _other) const;
    friend std::ostream& operator<<(std::ostream& stream, const LSystemConcreteModule& _module);

    // Module's name
    void setName(char _name) { name = _name; };
    char getName() const { return name; }
    // Parameter names
    void setParameterNames(std::vector<std::string> _parameterNames);
    void setParameterNames(std::string _parameterNames);
    std::vector<std::string> getParameterNames() const;
    bool getParameterName(float _parameterValue, std::string& _parameterName) const;
    void addParameterName(std::string _parameterName);
    // Parameter values
    void setParameterValues(std::vector<float> _parameterValues);
    void setParameterValues(std::string _parameterValues);
    std::vector<float> getParameterValues() const { return parameterValues; }
    bool getParameterValue(std::string _parameterName, float& _parameterValue) const;
    void addParameterValue(float _parameterValue);
    void addParameterValue(std::string _parameterValue);
    // Linked module
    bool setLinkedModule(LSystemAbstractModule* _module);
    class LSystemAbstractModule* getLinkedModule() const { return linkedModule; }
    bool isLinked() const { return linkedModule != nullptr; }
    // LSystemParameters
    LSystemParameters getParameters() const;
    // Global parameters
    LSystemParameters* getGlobalParameters() const { return globalParameters; }
    void setGlobalParameters(LSystemParameters* _globalParameters) { globalParameters = _globalParameters; }
    // Module parameters
    void setModuleParameters(std::vector<LSystemAbstractModule*> _moduleParameters) { moduleParameters = _moduleParameters; };
    std::vector<LSystemAbstractModule*> getModuleParameters() const { return moduleParameters; }

private:
    // Private variables
    char name;
    std::vector<float> parameterValues;
    std::vector<LSystemAbstractModule*> moduleParameters;
    LSystemParameters* globalParameters = nullptr;
    LSystemAbstractModule* linkedModule = nullptr;

    // Matches the parameters with the linked module
    void matchParameters();
};
