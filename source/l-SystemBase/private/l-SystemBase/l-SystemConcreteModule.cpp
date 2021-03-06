#include "l-SystemBase/l-SystemConcreteModule.h"

#include "l-SystemBase/l-SystemParameters.h"
#include "l-SystemBase/l-SystemAbstractModule.h"
#include "l-SystemBase/l-SystemExpression.h"

#include <ctype.h>
#include <math.h>

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemConcreteModule::LSystemConcreteModule(
    char _name, 
    std::vector<float> _parameterValues, 
    LSystemParameters* _parameters,
    std::vector<LSystemAbstractModule*> _moduleParameters) :
    name(_name),
    globalParameters(_parameters),
    moduleParameters(_moduleParameters)
{
    setParameterValues(_parameterValues);
    matchParameters();
}

LSystemConcreteModule::LSystemConcreteModule(
    char _name, 
    std::string _parameterString, 
    LSystemParameters* _parameters,
    std::vector<LSystemAbstractModule*> _moduleParameters) :
    name(_name),
    globalParameters(_parameters),
    moduleParameters(_moduleParameters)
{
    setParameterValues(_parameterString);
    matchParameters();
}


////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemConcreteModule::operator==(const LSystemConcreteModule& _other) const
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
    if(parameterValues.size() != _other.getParameterValues().size()) { return false; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < parameterValues.size(); i++)
    {
        if(parameterValues[i] != (_other.getParameterValues())[i]) { return false; }
    }
    return true;
}

bool LSystemConcreteModule::operator!=(const LSystemConcreteModule& _other) const
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
    if(parameterValues.size() != _other.getParameterValues().size()) { return true; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < parameterValues.size(); i++)
    {
        if(parameterValues[i] != (_other.getParameterValues())[i]) { return true; }
    }
    return false;
}

bool LSystemConcreteModule::operator==(const LSystemAbstractModule& _other) const
{
    // Test if the two modules have the same name
    if(name != _other.getName()) { return false; }
    // Test if the two modules have as many parameters
    if(parameterValues.size() != _other.getParameterNames().size()) { return false; }

    // If everything is ok
    return true;
}

bool LSystemConcreteModule::operator!=(const LSystemAbstractModule& _other) const
{
    // Test if the two modules have the same name
    if (name != _other.getName()) { return true; }
    // Test if the two modules have as many parameters
    if (parameterValues.size() != _other.getParameterNames().size()) { return true; }

    // If everything is ok
    return false;
}

std::ostream& operator<<(std::ostream& stream, const LSystemConcreteModule& _module)
{
    // Print the name of the module
    stream << _module.getName();

    // Get the parameters of the module
    std::vector<float> _moduleParameters = _module.getParameterValues();

    // If the module doesn't have parameters only return the name
    if(_moduleParameters.empty()) { return stream; }
    // Else start printing the parameters
    else { std::cout << '('; }

    // Loop over all the parameters of the module
    for(int i = 0; i < _moduleParameters.size(); i++)
    {
        // If the module as a linked module
        if(_module.isLinked())
        {
            // Print the parameters's value
            stream << _module.getLinkedModule()->getParameterNames()[i] << " = ";
        }

        // Print the parameter's value
        stream << _moduleParameters[i];

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
void LSystemConcreteModule::setParameterNames(std::vector<std::string> _parameterNames)
{
    // If the module is not linked to an other module cancel the operation
    if(!isLinked()) { return; }

    linkedModule->setParameterNames(_parameterNames);
}

void LSystemConcreteModule::setParameterNames(std::string _parameterNames)
{
    // If the module is not linked to an other module cancel the operation
    if(!isLinked()) { return; }

    linkedModule->setParameterNames(_parameterNames);
}

std::vector<std::string> LSystemConcreteModule::getParameterNames() const
{
    // If the module is not linked to an other module return nothing
    if(!isLinked()) { return {}; }

    return linkedModule->getParameterNames();
}

bool LSystemConcreteModule::getParameterName(float _parameterValue, std::string& _parameterName) const
{
    // If the module is not linked to an other module return nothing
    if(!isLinked()) { return false; }

    return linkedModule->getParameterName(_parameterValue, _parameterName);
}

void LSystemConcreteModule::addParameterName(std::string _parameterName)
{
    // If the module is not linked to an other module cancel the operation
    if(!isLinked()) { return; }

    linkedModule->addParameterName(_parameterName);
}


////////////////////////////////////////
// Parameter values
////////////////////////////////////////
void LSystemConcreteModule::setParameterValues(std::vector<float> _parameterValues)
{
    parameterValues = _parameterValues;
    matchParameters();
}

void LSystemConcreteModule::setParameterValues(std::string _parameterString)
{
    // Initialize buffers to store the parsing data
    std::string _expressionBuffer;

    // Loop over each characters to parse them
    for(char _character : _parameterString)
    {
        // If the character is a space, ignore it
        if (_character == ' ') { continue; }
        // If the character is a comma we store the content of the buffer and clear it
        else if(_character == ',')
        {
            LSystemExpression _expression(_expressionBuffer, globalParameters, moduleParameters);
            addParameterValue(_expression.parseDecimalExpression());
            _expressionBuffer.clear();
        }
        // else, we just add the character to the expression
        else
        {
            _expressionBuffer.push_back(_character);
        }
    }

    // We store the content of the buffer one last time
    LSystemExpression _expression(_expressionBuffer, globalParameters, moduleParameters);
    addParameterValue(_expression.parseDecimalExpression());
    _expressionBuffer.clear();

    matchParameters();
}

bool LSystemConcreteModule::getParameterValue(std::string _parameterName, float& _parameterValue) const
{
    // If there is no abstract module linked return false
    if(!isLinked()) { return false; }

    // Loop over all the parameter names of the linked module
    int _parameterIndex = 0;
    std::vector<std::string> _linkedParameterNames = linkedModule->getParameterNames();
    for(std::string _linkedParameterName : _linkedParameterNames)
    {
        // If the parameter's name matches
        if(_linkedParameterName == _parameterName)
        {
            // Return the parameter's value and true
            _parameterValue = parameterValues[_parameterIndex];
            return true;
        }
        _parameterIndex++;
    }

    // If there were no match return false
    return false;
}

void LSystemConcreteModule::addParameterValue(float _parameterValue)
{
    parameterValues.emplace_back(_parameterValue);
    matchParameters();
}

void LSystemConcreteModule::addParameterValue(std::string _parameterName)
{
    // Test if we have parameters
    if(globalParameters == nullptr) { return; }
    // Test if the string is empty
    if(_parameterName.empty()) { return; }
    // Loop over all the global parameters to find a match
    for(LSystemParameter _globalParameter : *globalParameters)
    {
        if(_parameterName == _globalParameter.name)
        {
            addParameterValue(_globalParameter.value);
            break;
        }
    }

    // Loop over all the module parameters
    for (LSystemAbstractModule* _moduleParameter : moduleParameters)
    {
        // If the module is linked
        if (!_moduleParameter->isLinked()) { continue; }

        // Loop over all the module's parameters
        for (LSystemParameter _moduleParameter : _moduleParameter->getParameters())
        {
            // If the name of the parameter matches the parsed Parameter's name
            if (_parameterName == _moduleParameter.name)
            {
                addParameterValue(_moduleParameter.value);
                break;
            }
        }
    }

    matchParameters();
}


////////////////////////////////////////
// Linked module
////////////////////////////////////////
bool LSystemConcreteModule::setLinkedModule(LSystemAbstractModule* _module)
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
LSystemParameters LSystemConcreteModule::getParameters() const
{
    // If the module is not linked to an other module return nothing
    if(!isLinked()) { return LSystemParameters(); }

    return LSystemParameters(getParameterNames(), getParameterValues());
}


////////////////////////////////////////
// Private Functions
////////////////////////////////////////
void LSystemConcreteModule::matchParameters()
{
    // If the module is not linked to an other module cancel the operation
    if(!isLinked()) { return; }

    // Get the difference of item count with the given module
    int difference = static_cast<int>(parameterValues.size()) - static_cast<int>(linkedModule->getParameterNames().size());
    
    // If there is more parameter names than parameters in the given module
    if(difference > 0)
    {
        // For each items that are exeding the max lenght
        for(int i = static_cast<int>(parameterValues.size()) - difference; i >= static_cast<int>(parameterValues.size()); i++)
        {
            parameterValues.pop_back();
        }
    }

    // There is not enough parameter names compared to the given module
    if(difference < 0)
    {
        // For each items that should exists
        for(int i = static_cast<int>(parameterValues.size()) + difference; i >= static_cast<int>(linkedModule->getParameterNames().size()); i++)
        {
            addParameterValue(0.0f);
        }
    }
}
