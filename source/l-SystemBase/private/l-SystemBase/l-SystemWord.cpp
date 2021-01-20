#include "l-SystemBase/l-SystemWord.h"

#include "l-SystemBase/l-SystemParameters.h"

#include <iostream>
#include "ctype.h"

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemWord::LSystemWord(std::string _word, LSystemParameters* _parameters) :
    parameters(_parameters)
{
    // We parse the input string into modules of commands
    parseWord(_word);
}


////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemWord::operator==(const LSystemWord& _other) const
{
    // Test if the two modules have as many parameters
    if(modules.size() != _other.getModules().size()) { return false; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < modules.size(); i++)
    {
        if(modules[i] != (_other.getModules())[i]) { return false; }
    }
    return true;
}

bool LSystemWord::operator!=(const LSystemWord& _other) const
{
    // Test if the two modules have as many parameters
    if(modules.size() != _other.getModules().size()) { return true; }
    // Loop over all the parameters to compare them
    for(int i = 0; i < modules.size(); i++)
    {
        if(modules[i] == (_other.getModules())[i]) { return false; }
    }
    return true;
}

std::ostream& operator<<(std::ostream& stream, const LSystemWord& _word)
{
    // Loop over all the modules of the word
    std::vector<LSystemConcreteModule> _wordModules = _word.getModules();
    for(int i = 0; i < _wordModules.size(); i++)
    {
        // Print the module
        stream << _wordModules[i];
    }

    return stream;
}


////////////////////////////////////////
// Getters / setters / append
////////////////////////////////////////
void LSystemWord::appendModule(LSystemConcreteModule _module)
{
    modules.emplace_back(_module);
}

void LSystemWord::appendWord(LSystemWord _word)
{
    modules.insert(end(), _word.begin(), _word.end());
}


////////////////////////////////////////
// Private functions
////////////////////////////////////////
void LSystemWord::parseWord(std::string _word)
{
    // Initialize buffers to store the parsing data
    char _nameBuffer = '\0';
    std::string _parametersBuffer;
    bool isParsingParameter = false;

    // Loop over all the characters of the word
    for(char _character : _word)
    {
        // If no name is set and we are not parsing parameters
        if(_nameBuffer == '\0' && isParsingParameter == false)
        {
            // Store the current character as the name
            _nameBuffer = _character;
        }
        // If the character isn't '(' and we are note parsing parameter
        else if(_character != '(' && isParsingParameter == false)
        {
            // Append the module with only a name
            appendModule(LSystemConcreteModule(_nameBuffer, parameters));
            // Clear the buffers and initialize the name buffer
            _nameBuffer = _character;
            _parametersBuffer.clear();
            isParsingParameter = false;
        }
        // If the character is '(' and we are not parsing parameters
        else if(_character == '(' && isParsingParameter == false)
        {
            // Switch to pasring parameters
            isParsingParameter = true;
        }
        // If the character isn't ')' and we are parsing parameters
        else if(_character != ')' && isParsingParameter == true)
        {
            // Append the character to the parameter buffer
            _parametersBuffer.push_back(_character);
        }
        // If the character is ')' and we are parsing parameters
        else if(_character == ')' && isParsingParameter == true)
        {
            // Append the module with the name and the parameters
            appendModule(LSystemConcreteModule(_nameBuffer, _parametersBuffer, parameters));
            // Clear the buffers
            _nameBuffer = '\0';
            _parametersBuffer.clear();
            isParsingParameter = false;
            
        }
    }
}
