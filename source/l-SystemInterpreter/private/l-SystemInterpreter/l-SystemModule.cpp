#include "l-SystemInterpreter/l-SystemModule.h"

#include <ctype.h>

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemModule::LSystemModule(char _name, std::vector<std::string> _parameters) :
    name(_name)
{
    setParameters(_parameters);
}

LSystemModule::LSystemModule(char _name, std::string _parameters) :
    name(_name)
{
    // Initialize the buffer to store the parameters's name
    std::string _buffer;
    for(char _character : _parameters)
    {
        // If the character is a letter we append it to the buffer
        if(isalpha(_character))
        {
            _buffer.push_back(_character);
        }
        // If the character is a comma we add the buffer content to the parameters and clear it
        else if(_character == ',')
        {
            addParameter(_buffer);
            _buffer.clear();
        }
    }

}


////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemModule::operator==(const LSystemModule& _other) const
{
    // Test if the two modules have the same name
    if(name != _other.getName()) { return false; }
    // Test if the two modules have as many parameters
    if(parameters.size() != _other.getParameters().size()) { return false; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < parameters.size(); i++)
    {
        if(parameters[i] == (_other.getParameters())[i]) { return false; }
    }
    return true;
}

bool LSystemModule::operator!=(const LSystemModule& _other) const
{
    // Test if the two modules have the same name
    if(name == _other.getName()) { return false; }
    // Test if the two modules have as many parameters
    if(parameters.size() == _other.getParameters().size()) { return false; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < parameters.size(); i++)
    {
        if(parameters[i] != (_other.getParameters())[i]) { return false; }
    }
    return true;
}

std::ostream& operator<<(std::ostream& stream, const LSystemModule& module)
{
    // Print the name of the module
    stream << module.getName() << "(";

    // Loop over all the parameters of the module
    std::vector<std::string> _moduleParameters = module.getParameters();
    for(int i = 0; i < _moduleParameters.size(); i++)
    {
        // Print the parameter name
        stream << _moduleParameters[i];
        // If this is not the last parameter print a comma
        if(i != _moduleParameters.size() - 1)
        {
            stream << ",";
        }
    }

    // Print the closing braquet
    stream << ")";

   return stream;
}


////////////////////////////////////////
// Setters / getters
////////////////////////////////////////
void LSystemModule::addParameter(std::string _parameter)
{
    // Test if the string is empty
    if(_parameter.empty()) { return; }
    // Test if the name of the parameter does contain only letters
    for(char _character : _parameter)
    {
        if(!isalpha(_character)) 
        { 
            return;
        }
    }
    parameters.emplace_back(_parameter);
}

void LSystemModule::setParameters(std::vector<std::string> _parameters)
{
    // We reserve the space for the entire input vector after empty it
    parameters.clear();
    parameters.reserve(_parameters.size());
    
    // We store the input parameters one by one to check if they are valid
    for(std::string _parameter : _parameters)
    {
        addParameter(_parameter);
    }
}

