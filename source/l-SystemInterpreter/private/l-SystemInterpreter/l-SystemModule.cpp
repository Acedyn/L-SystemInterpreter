#include "l-SystemInterpreter/l-SystemModule.h"
#include "l-SystemInterpreter/l-SystemCondition.h"

#include <iostream>
#include <ctype.h>

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
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


////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemModule::operator==(const LSystemModule& _other) const
{
    if(name == _other.name && formalParameters.size() == _other.formalParameters.size())
    {
        return true;
    }
    return false;
}

bool LSystemModule::operator!=(const LSystemModule& _other) const
{
    if(name != _other.name || formalParameters.size() != _other.formalParameters.size())
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
    // If there is no values, we initialize the values to null
    else if(isValidParameters)
    {
        parameterValues = std::vector<float>(0.0f, _formalParameters.size());
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
    // If there is no parameters set we initialize them
    else if(formalParameters.empty())
    {
        formalParameters.reserve(_parameterValues.size());
        char parameterName = '\0';
        for(float _parameterValue : _parameterValues)
        {
            formalParameters.emplace_back(parameterName);
            parameterName++;
        }
    }

    if(isValidValues) { parameterValues = _parameterValues; }
}
