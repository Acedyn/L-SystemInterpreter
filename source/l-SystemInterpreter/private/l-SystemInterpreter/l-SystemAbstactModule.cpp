#include "l-SystemInterpreter/l-SystemAbstactModule.h"

#include "l-SystemInterpreter/l-SystemModule.h"

////////////////////////////////////////
// Constructors / Destructors
////////////////////////////////////////
LSystemAbstactModule::LSystemAbstactModule(char _name, std::vector<std::string> _parameterNames, LSystemModule* _module) : 
        name(_name),
        parameterNames(_parameterNames),
        module(_module) 
{ 
    updateParameterNames();
}

LSystemAbstactModule::LSystemAbstactModule(char _name, std::string _parameterNames, LSystemModule* _module) : 
    name(_name),
    module(_module)
{
    setParameterNames(_parameterNames);
    updateParameterNames();
}
    

////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemAbstactModule::operator==(const LSystemAbstactModule& _other) const
{
    // Test if the two modules have the same name
    if(name != _other.getName()) { return false; }
    // Test if the modules are the same
    if(*module != *(_other.getModule())) { return false; }
    // Test if the two modules have as many parameters
    if(parameterNames.size() != _other.getParameters().size()) { return false; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < parameterNames.size(); i++)
    {
        if(parameterNames[i] != (_other.getParameters())[i]) { return false; }
    }
    return true;
}

bool LSystemAbstactModule::operator!=(const LSystemAbstactModule& _other) const
{
    // Test if the two modules have the same name
    if(name == _other.getName()) { return false; }
    // Test if the modules are the same
    if(*module == *(_other.getModule())) { return false; }
    // Test if the two modules have as many parameters
    if(parameterNames.size() != _other.getParameters().size()) { return true; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < parameterNames.size(); i++)
    {
        if(parameterNames[i] == (_other.getParameters())[i]) { return false; }
    }
    return true;
}

std::ostream& operator<<(std::ostream& stream, const LSystemAbstactModule& _abstractModule)
{
    // Print the name of the module
    stream << _abstractModule.getName();

    // Get the parameters of the module
    std::vector<std::string> _moduleParameters = _abstractModule.getParameters();

    // If the module doesn't have parameters only return the name
    if(_moduleParameters.empty()) { return stream; }
    // Else start printing the parameters
    else { std::cout << '('; }

    // Loop over all the parameters of the module
    for(int i = 0; i < _moduleParameters.size(); i++)
    {
        // Print the parameter's name
        stream << _moduleParameters[i] << " = ";
        // Print the parameters's value
        stream << _abstractModule.getModule()->getParameters()[i];
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
// Setters / Getters
////////////////////////////////////////
void LSystemAbstactModule::setName(char _name)
{
    name = _name;
}

void LSystemAbstactModule::setParameterNames(std::vector<std::string> _parameterNames)
{
    parameterNames = _parameterNames;
}

void LSystemAbstactModule::setParameterNames(std::string _parameterNames)
{
    // Buffer for all the parameters
    std::vector<std::string> _namesBuffer;
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
            // Append the name buffer to the names buffer
            _namesBuffer.emplace_back(_nameBuffer);
            // Clear the name buffer
            _nameBuffer.clear();
        }
    }

    // Empty the buffers one last time
    if(!_nameBuffer.empty())
    {
        // Append the name buffer to the names buffer
        _namesBuffer.emplace_back(_nameBuffer);
        // Clear the name buffer
        _nameBuffer.clear();
    }

    parameterNames = _namesBuffer;
}

void LSystemAbstactModule::setModule(LSystemModule* _module)
{
    module = _module;
    updateParameterNames();
}

bool LSystemAbstactModule::getParameterName(float _parameterValue, std::string& _parameterName) const
{
    int _parameterIndex = 0;
    // Loop over all the parameters
    for(float _moduleParameter : module->getParameters())
    {
        // If the parameter's values matches
        if(_parameterValue == _moduleParameter)
        {
            // Return the parameter's name
            _parameterName = parameterNames[_parameterIndex];
            return true;
        }
        _parameterIndex++;
    }

    // Return false if no match found
    return false;
}

std::vector<float> LSystemAbstactModule::getParameterValues() const
{
    if(module != nullptr) { return module->getParameters(); }
    else { return {}; }
}

bool LSystemAbstactModule::getParameterValue(std::string _parameterName, float& _parameterValue) const
{
    int _parameterIndex = 0;
    // Loop over all the parameters
    for(std::string _abstractParameterName : parameterNames)
    {
        // Is the parameter's name matches
        if(_abstractParameterName == _parameterName)
        {
            _parameterValue = module->getParameters()[_parameterIndex];
            return true;
        }
        _parameterIndex++;
    }
    
    // Return false if no match found
    return false;
}


////////////////////////////////////////
// Private Functions
////////////////////////////////////////
void LSystemAbstactModule::updateParameterNames()
{
    if(module == nullptr) { return; }

    // Get the difference of item count with the given module
    int difference = parameterNames.size() - module->getParameters().size();
    
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
        for(int i = parameterNames.size() + difference; i >= module->getParameters().size(); i++)
        {
            parameterNames.emplace_back("\0");
        }
    }
}
