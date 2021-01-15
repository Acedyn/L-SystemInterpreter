#include "l-SystemInterpreter/l-SystemAbstractModule.h"

#include "l-SystemInterpreter/l-SystemConcreteModule.h"

////////////////////////////////////////
// Constructors / Destructors
////////////////////////////////////////
LSystemAbstractModule::LSystemAbstractModule(char _name, std::vector<std::string> _parameterNames, LSystemConcreteModule* _module) : 
        name(_name),
        parameterNames(_parameterNames),
        linkedModule(_module) 
{ 
    matchParameters();
}

LSystemAbstractModule::LSystemAbstractModule(char _name, std::string _parameterNames, LSystemConcreteModule* _module) : 
    name(_name),
    linkedModule(_module)
{
    setParameterNames(_parameterNames);
    matchParameters();
}
    

////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemAbstractModule::operator==(const LSystemAbstractModule& _other) const
{
    // Test if the two modules have the same name
    if(name != _other.getName()) { return false; }
    // Test if the linked modules are the same
    if(isLinked() && _other.isLinked())
    {
        if(*linkedModule != *(_other.getLinkedModule())) { return false; }
    }
    else
    {
        if(linkedModule != _other.getLinkedModule()) { return false; }
    }
    // Test if the two modules have as many parameters
    if(parameterNames.size() != _other.getParameterNames().size()) { return false; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < parameterNames.size(); i++)
    {
        if(parameterNames[i] != (_other.getParameterNames())[i]) { return false; }
    }
    return true;
}

bool LSystemAbstractModule::operator!=(const LSystemAbstractModule& _other) const
{
    // Test if the two modules have the same name
    if(name != _other.getName()) { return true; }
    // Test if the linked modules are the same
    if(isLinked() && _other.isLinked())
    {
        if(*linkedModule != *(_other.getLinkedModule())) { return true; }
    }
    else
    {
        if(linkedModule != _other.getLinkedModule()) { return true; }
    }
    // Test if the two modules have as many parameters
    if(parameterNames.size() != _other.getParameterNames().size()) { return true; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < parameterNames.size(); i++)
    {
        if(parameterNames[i] != (_other.getParameterNames())[i]) { return true; }
    }
    return false;
}

bool LSystemAbstractModule::operator==(const LSystemConcreteModule& _other) const
{
    // Test if the two modules have the same name
    if(name != _other.getName()) { return false; }
    // Test if the two modules have as many parameters
    if(parameterNames.size() != _other.getParameterValues().size()) { return false; }

    // If everything is ok
    return true;
}

bool LSystemAbstractModule::operator!=(const LSystemConcreteModule& _other) const
{
    // Test if the two modules have the same name
    if(name == _other.getName()) { return false; }
    // Test if the two modules have as many parameters
    if(parameterNames.size() == _other.getParameterValues().size()) { return false; }

    // If everything is ok
    return true;
}

std::ostream& operator<<(std::ostream& stream, const LSystemAbstractModule& _module)
{
    // Print the name of the module
    stream << _module.getName();

    // Get the parameters of the module
    std::vector<std::string> _moduleParameters = _module.getParameterNames();

    // If the module doesn't have parameters only return the name
    if(_moduleParameters.empty()) { return stream; }
    // Else start printing the parameters
    else { std::cout << '('; }

    // Loop over all the parameters of the module
    for(int i = 0; i < _moduleParameters.size(); i++)
    {
        // Print the parameter's name
        stream << _moduleParameters[i];
        
        // If the module as a linked module
        if(_module.isLinked())
        {
            // Print the parameters's value
            stream << " = " << _module.getLinkedModule()->getParameterValues()[i];
        }

        // If this is not the last parameter print a comma
        if(i != _moduleParameters.size() - 1)
        {
            stream << ",";
        }
    }

    stream << ")";

   return stream;
}


////////////////////////////////////////
// Parameter names
////////////////////////////////////////
void LSystemAbstractModule::setParameterNames(std::vector<std::string> _parameterNames)
{
    parameterNames = _parameterNames;
    matchParameters();
}

void LSystemAbstractModule::setParameterNames(std::string _parameterNames)
{
    // Buffer for the parsing parameter
    std::string _nameBuffer;

    // Loop over all the character of the string
    for(char _character : _parameterNames)
    {
        // If the character is a letter
        if(isalpha(_character))
        {
            // Append it to the name buffer
            _nameBuffer.push_back(_character);
        }
        // If the character is a comma and the name buffer is not empty
        else if(_character == ',' && !_nameBuffer.empty())
        {
            // Append the parameter to the parameter names
            addParameterName(_nameBuffer);
            // Clear the name buffer
            _nameBuffer.clear();
        }
    }

    // Empty the buffers one last time
    if(!_nameBuffer.empty())
    {
        // Append the parameter to the parameter names
        addParameterName(_nameBuffer);
        // Clear the name buffer
        _nameBuffer.clear();
    }

    matchParameters();
}

bool LSystemAbstractModule::getParameterName(float _parameterValue, std::string& _parameterName) const
{
    // If there is no abstract module linked return false
    if(!isLinked()) { return false; }

    // Loop over all the parameter values of the linked module
    int _parameterIndex = 0;
    std::vector<float> _linkedParameterValues = linkedModule->getParameterValues();
    for(float _linkedParameterValue : _linkedParameterValues)
    {
        // If the parameter's value matches
        if(_linkedParameterValue == _parameterValue)
        {
            // Return the parameter's name and true
            _parameterName = parameterNames[_parameterIndex];
            return true;
        }
        _parameterIndex++;
    }

    // If there were no match return false
    return false;
}

void LSystemAbstractModule::addParameterName(std::string _parameterName)
{
    parameterNames.emplace_back(_parameterName);
    matchParameters();
}


////////////////////////////////////////
// Parameter values
////////////////////////////////////////
void LSystemAbstractModule::setParameterValues(std::vector<float> _parameterValues)
{
    // If the module is not linked to an other module cancel the operation
    if(!isLinked()) { return; }

    linkedModule->setParameterValues(_parameterValues);
}

void LSystemAbstractModule::setParameterValues(std::string _parameterValues)
{
    // If the module is not linked to an other module cancel the operation
    if(!isLinked()) { return; }

    linkedModule->setParameterValues(_parameterValues);
}

std::vector<float> LSystemAbstractModule::getParameterValues() const
{
    // If the module is not linked to an other module return nothing
    if(!isLinked()) { return {}; }

    return linkedModule->getParameterValues();
}

bool LSystemAbstractModule::getParameterValue(std::string _parameterName, float& _parameterValue) const
{
    // If the module is not linked to an other module return nothing
    if(!isLinked()) { return false; }

    return linkedModule->getParameterValue(_parameterName, _parameterValue);
}

void LSystemAbstractModule::addParameterValue(float _parameterValue)
{
    // If the module is not linked to an other module cancel the operation
    if(!isLinked()) { return; }

    linkedModule->addParameterValue(_parameterValue);
}


////////////////////////////////////////
// Linked module
////////////////////////////////////////
bool LSystemAbstractModule::setLinkedModule(LSystemConcreteModule* _module)
{
    if(_module == nullptr) { return false; }

    // If the name matches
    if(*this == *_module)
    {
        // Set the linked module
        linkedModule = _module;
        return true;
    }
    return false;
}


////////////////////////////////////////
// LSystemParameters
////////////////////////////////////////
LSystemParameters LSystemAbstractModule::getParameters() const
{
    // If the module is not linked to an other module return nothing
    if(!isLinked()) { return LSystemParameters(); }

    return LSystemParameters(getParameterNames(), getParameterValues());
}


////////////////////////////////////////
// Private Functions
////////////////////////////////////////
void LSystemAbstractModule::matchParameters()
{
    // If the module is not linked to an other module cancel the operation
    if(!isLinked()) { return; }

    // Get the difference of item count with the given module
    int difference = parameterNames.size() - linkedModule->getParameterValues().size();
    
    // If there is more parameter names than parameters in the given module
    if(difference > 0)
    {
        // For each items that are exeding the max lenght
        for(int i = parameterNames.size() - difference; i >= parameterNames.size(); i++)
        {
            parameterNames.pop_back();
        }
    }

    // There is not enough parameter names compared to the given module
    if(difference < 0)
    {
        // For each items that should exists
        for(int i = parameterNames.size() + difference; i >= linkedModule->getParameterValues().size(); i++)
        {
            addParameterName("\0");
        }
    }
}
