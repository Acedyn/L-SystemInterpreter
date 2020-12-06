#include "l-SystemInterpreter/l-SystemModule.h"
#include "l-SystemInterpreter/l-SystemCondition.h"

#include <ctype.h>

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemModule::LSystemModule(char _name) : name(_name) { }

LSystemModule::LSystemModule(char _name, std::vector<char> _formalParameters) :
    name(_name)
{
    setFormalParameters(_formalParameters);
}

LSystemModule::LSystemModule(char _name, std::vector<float> _parameterValues) :
    name(_name)
{
    setParametersValues(_parameterValues);
}

LSystemModule::LSystemModule(char _name, std::vector<char> _formalParameters, std::vector<float> _parameterValues) :
    name(_name)
{
    setFormalParameters(_formalParameters);
    setParametersValues(_parameterValues);
}


////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemModule::operator==(const LSystemModule& _other) const
{
    if(name == _other.name && formalParameters == _other.formalParameters)
    {
        return true;
    }
    return false;
}


////////////////////////////////////////
// Setters / getters
////////////////////////////////////////
void LSystemModule::setFormalParameters(std::vector<char> _formalParameters)
{
    bool isValidParameters = true;

    // Test if the given parameters are leters;
    for(char _formalParameter : _formalParameters)
    {
        if(!isalpha(_formalParameter))
        {
            isValidParameters = false;
            break;
        }
    }

    // If there is some values, we check if there is as much parameters as values
    if(!(parameterValues.empty()) && parameterValues.size() != _formalParameters.size())
    {
        isValidParameters = false;
    }

    if(isValidParameters) { formalParameters = _formalParameters; }
}

void LSystemModule::setParametersValues(std::vector<float> _parameterValues)
{
    bool isValidValues = true;

    // If there is some parameters, we check if there is as much values as parameters
    if(!(formalParameters.empty()) && formalParameters.size() != _parameterValues.size())
    {
        isValidValues = false;
    }

    if(isValidValues) { parameterValues = _parameterValues; }
}
