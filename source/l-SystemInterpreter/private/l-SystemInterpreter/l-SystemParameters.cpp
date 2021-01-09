#include "l-SystemInterpreter/l-SystemParameters.h"

#include <algorithm>

////////////////////////////////////////
// Constructors / Destructors
////////////////////////////////////////
LSystemParameters::LSystemParameters(std::vector<std::string> _parameterNames, std::vector<float> _parameterValues)
{
    // loop the minimim item count given so each name has its value
    int minimumSize = std::min(_parameterNames.size(), _parameterValues.size());
    parameters.reserve(minimumSize);

    // Combine the names and the values together to create parameters
    for(int i = 0; i < minimumSize; i++)
    {
        LSystemParameter _parameter(_parameterNames[i], _parameterValues[i]);
        addParameter(_parameter);
    }
}

LSystemParameters::LSystemParameters(std::vector<LSystemParameter> _parameters)
{
    setParameters(_parameters);
}


////////////////////////////////////////
// Setters / Getters
////////////////////////////////////////
void LSystemParameters::addParameter(LSystemParameter _parameter)
{
    // If the parameter if valid, we add it
    if(_parameter.isValid())
    {
        parameters.emplace_back(_parameter);
    }
}

void LSystemParameters::setParameters(std::vector<LSystemParameter> _parameters)
{
    // We reserve the space for the entire input vector after empty it
    parameters.clear();
    parameters.reserve(_parameters.size());
    
    // We store the input parameters one by one to check if they are valid
    for(LSystemParameter _parameter : _parameters)
    {
        addParameter(_parameter);
    }
}

void LSystemParameters::removeParameter(int _index)
{
    // If the parameter vector is empty we cancel
    if(parameters.size() < 1) { return; }
    // If the index is under 0 we count backard from the parameter's index count
    while(_index < 0) { _index = parameters.size() + _index; }
    // If the index is higher that the parameter's index count it is equal to the max
    if(_index >= parameters.size()) { _index = parameters.size() - 1; }

    // We erase the parameter at the given index
    parameters.erase(parameters.begin() + _index);
}
