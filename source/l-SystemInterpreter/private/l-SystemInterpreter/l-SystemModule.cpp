#include "l-SystemInterpreter/l-SystemModule.h"

#include "l-SystemInterpreter/l-SystemParameters.h"

#include <ctype.h>
#include <math.h>

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemModule::LSystemModule(char _name, std::vector<float> _parameterValues, LSystemParameters* _parameters) :
    name(_name),
    parameters(_parameters)
{
    setParameters(_parameterValues);
}

LSystemModule::LSystemModule(char _name, std::vector<std::string> _parameterNames, LSystemParameters* _parameters) :
    name(_name),
    parameters(_parameters)
{
    setParameters(_parameterNames);
}

LSystemModule::LSystemModule(char _name, std::string _parameterString, LSystemParameters* _parameters) :
    name(_name),
    parameters(_parameters)
{
    setParameters(_parameterString);
}


////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemModule::operator==(const LSystemModule& _other) const
{
    // Test if the two modules have the same name
    if(name != _other.getName()) { return false; }
    // Test if the two modules have as many parameters
    if(parameterValues.size() != _other.getParameters().size()) { return false; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < parameterValues.size(); i++)
    {
        if(parameterValues[i] == (_other.getParameters())[i]) { return false; }
    }
    return true;
}

bool LSystemModule::operator!=(const LSystemModule& _other) const
{
    // Test if the two modules have the same name
    if(name == _other.getName()) { return false; }
    // Test if the two modules have as many parameters
    if(parameterValues.size() == _other.getParameters().size()) { return false; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < parameterValues.size(); i++)
    {
        if(parameterValues[i] != (_other.getParameters())[i]) { return false; }
    }
    return true;
}

std::ostream& operator<<(std::ostream& stream, const LSystemModule& module)
{
    // Print the name of the module
    stream << module.getName() << "(";

    // Loop over all the parameters of the module
    std::vector<float> _moduleParameters = module.getParameters();
    for(int i = 0; i < _moduleParameters.size(); i++)
    {
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
// Setters / getters
////////////////////////////////////////
void LSystemModule::addParameter(float _parameterValue)
{
    parameterValues.emplace_back(_parameterValue);
}

void LSystemModule::addParameter(std::string _parameterName)
{
    // Test if we have parameters
    if(parameters == nullptr) { return; }
    // Test if the string is empty
    if(_parameterName.empty()) { return; }
    // Test if the name of the parameter does contain only letters
    for(char _character : _parameterName)
    {
        if(!isalpha(_character)) 
        { 
            return;
        }
    }
    // Loop over all the given parameters to find a match
    for(auto parametersIterator = parameters->begin(); parametersIterator != parameters->end(); parametersIterator++)
    {
        if(_parameterName == parametersIterator->name)
        {
            addParameter(parametersIterator->value);
            break;
        }
    }
}

void LSystemModule::setParameters(std::vector<float> _parameterValues)
{
    parameterValues = _parameterValues;
}

void LSystemModule::setParameters(std::vector<std::string> _parameterNames)
{
    // We reserve the space for the entire input vector after empty it
    parameterValues.clear();
    parameterValues.reserve(_parameterNames.size());
    
    // We store the input parameters one by one to check if they are valid
    for(std::string _parameterName : _parameterNames)
    {
        addParameter(_parameterName);
    }
}

void LSystemModule::setParameters(std::string _parameterString)
{
    // Enum to set the parsing parameter type
    enum ParameterType
    {
        NONE,
        VALUE,
        NAME
    };

    // Initialize buffers to store the parsing data
    bool isFloatingValue = false;
    int digitCount = 0;
    float _valueBuffer = 0.0f;
    float _floatingValueBuffer = 0.0f;
    std::string _nameBuffer;
    ParameterType type = ParameterType::NONE;

    // Loop over each characters to parse them
    for(char _character : _parameterString)
    {
        // If the character is a number we append it to the value buffer
        if(isdigit(_character))
        {
            if(!isFloatingValue)
            {
                _valueBuffer = _valueBuffer * 10 + (static_cast<int>(_character) - 48);
            }
            else
            {
                _floatingValueBuffer = _floatingValueBuffer * 10 + (static_cast<int>(_character) - 48);
                digitCount++;
            }
            
            type = ParameterType::VALUE;
        }
        // If the character is a point we switch the value to floating value mode
        else if(_character == '.')
        {
            isFloatingValue = true;
        }
        // If the character is a letter we append it to the name buffer
        else if(isalpha(_character))
        {
            _nameBuffer.push_back(_character);
            type = ParameterType::NAME;
        }
        // If the character is a comma we store the content of the buffer en empty them
        else if(_character == ',')
        {
            switch(type)
            {
                case ParameterType::NONE :
                    break;
                
                case ParameterType::VALUE :
                    addParameter(_valueBuffer + (_floatingValueBuffer / pow(10, digitCount)));
                    break;

                case ParameterType::NAME :
                    addParameter(_nameBuffer);
                    break;
            }

            _valueBuffer = 0.0f;
            _floatingValueBuffer = 0.0f;
            _nameBuffer.clear();
            type = ParameterType::NONE;
        }
    }
    // Store the content of the buffer one last time
    switch(type)
    {
        case ParameterType::NONE :
            break;
        
        case ParameterType::VALUE :
            addParameter(_valueBuffer + (_floatingValueBuffer / pow(10, digitCount)));
            break;

        case ParameterType::NAME :
            addParameter(_nameBuffer);
            break;
    }
    _valueBuffer = 0.0f;
    _floatingValueBuffer = 0.0f;
    _nameBuffer.clear();
    type = ParameterType::NONE;
}
