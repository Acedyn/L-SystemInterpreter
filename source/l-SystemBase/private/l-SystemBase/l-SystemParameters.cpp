#include "l-SystemBase/l-SystemParameters.h"

#include <algorithm>

////////////////////////////////////////
// Constructors / Destructors
////////////////////////////////////////
LSystemParameters::LSystemParameters(std::vector<std::string> _parameterNames, std::vector<float> _parameterValues)
{
    // loop the minimim item count given so each name has its value
    int minimumSize = std::min(static_cast<int>(_parameterNames.size()), static_cast<int>(_parameterValues.size()));
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
// Operators
////////////////////////////////////////
bool LSystemParameters::operator==(const LSystemParameters& _other) const
{
    // Test if the two parameters have as many items
    if(parameters.size() != _other.getParameters().size()) { return false; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < parameters.size(); i++)
    {
        if(parameters[i] != (_other.getParameters())[i]) { return false; }
    }
    return true;
}

bool LSystemParameters::operator!=(const LSystemParameters& _other) const
{
    // Test if the two parameters have as many items
    if(parameters.size() == _other.getParameters().size()) { return false; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < parameters.size(); i++)
    {
        if(parameters[i] == (_other.getParameters())[i]) { return false; }
    }
    return true;
}


////////////////////////////////////////
// Setters / Getters
////////////////////////////////////////
void LSystemParameters::addParameter(LSystemParameter _parameter)
{
    // If the parameter if valid, we add it
    if(_parameter.isValid()) { parameters.emplace_back(_parameter); }
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

void LSystemParameters::setNames(std::vector<std::string> _parameterNames)
{
    // loop the minimim item count given so each name has its value
    int minimumSize = std::min(static_cast<int>(_parameterNames.size()), static_cast<int>(parameters.size()));
    
    for(int i = 0; i < minimumSize; i++)
    {
        // Create a parameter with the new name and the old value
        LSystemParameter _parameter(_parameterNames[i], (parameters[i]).value);
        // If the new parameter is valid, we replace the old parameter with the new one
        if(_parameter.isValid()) { parameters[i] = _parameter; }
    }
}

void LSystemParameters::setValues(std::vector<float> _parameterValues)
{
    // loop the minimim item count given so each name has its value
    int minimumSize = std::min(static_cast<int>(_parameterValues.size()), static_cast<int>(parameters.size()));
    
    for(int i = 0; i < minimumSize; i++)
    {
        // Create a parameter with the new name and the old value
        LSystemParameter _parameter((parameters[i]).name, _parameterValues[i]);
        // If the new parameter is valid, we replace the old parameter with the new one
        if(_parameter.isValid()) { parameters[i] = _parameter; }
    }
}

void LSystemParameters::removeParameter(int _index)
{
    // If the parameter vector is empty we cancel
    if(parameters.size() < 1) { return; }
    // If the index is under 0 we count backard from the parameter's index count
    while(_index < 0) { _index = static_cast<int>(parameters.size()) + _index; }
    // If the index is higher that the parameter's index count it is equal to the max
    if(_index >= parameters.size()) { _index = static_cast<int>(parameters.size()) - 1; }

    // We erase the parameter at the given index
    parameters.erase(parameters.begin() + _index);
}

LSystemParameter LSystemParameters::getParameter(int _index) const
{
    // If the parameter vector is empty we cancel
    if(parameters.size() < 1) { return LSystemParameter(); }
    // If the index is under 0 we count backard from the parameter's index count
    while(_index < 0) { _index = static_cast<int>(parameters.size()) + _index; }
    // If the index is higher that the parameter's index count it is equal to the max
    if(_index >= parameters.size()) { _index = static_cast<int>(parameters.size()) - 1; }

    // We return the parameter at the right index
    return parameters[_index];
}
