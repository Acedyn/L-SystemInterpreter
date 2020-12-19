#include "l-SystemInterpreter/l-SystemWord.h"
#include "l-SystemInterpreter/l-SystemModule.h"

#include <iostream>
#include "ctype.h"

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemWord::LSystemWord(std::string _word)
{
    parseWord(_word);
}


////////////////////////////////////////
// Getters / setters / append
////////////////////////////////////////
void LSystemWord::appendModule(LSystemModule* _module)
{
    components.emplace_back(wordComponent::MODULE);
    modules.emplace_back(_module);
}

void LSystemWord::appendCommand(char _command)
{
    components.emplace_back(wordComponent::COMMAND);
    commands.emplace_back(_command);
}


////////////////////////////////////////
// Private functions
////////////////////////////////////////
void LSystemWord::parseWord(std::string _word)
{
    // Loop over all the characters
    for(std::string::iterator wordIterator = _word.begin(); wordIterator != _word.end(); wordIterator++)
    {
        // If the character is a module
        if(isalpha(*wordIterator))
        {
            LSystemModule newModule = parseModule(wordIterator);
            appendModule(&newModule);
            std::vector<float> newModuleParameterValues = newModule.getParameterValues();
        }
        // If the character is a command
        else
        {
            appendCommand(*wordIterator);
        }
    }
}

LSystemModule LSystemWord::parseModule(std::string::iterator& _characterIterator)
{
    // The name of the module
    char name = *_characterIterator;
    // The parameters values of the module
    std::vector<float> parameterValues;

    // Iterate the character to see if the module does have parameters
    _characterIterator++;
    // If the module doesn't have parameters
    if(*_characterIterator != '(')
    {
        // Cancel the last iteration
        _characterIterator--;
        // Return module with just a name
        return LSystemModule(name);
    }
    // If the module does have parameters
    else
    {
        float parameterValue = 0;
        // Loop over all the caracters until the end of the parameters
        while(*(_characterIterator++) != ')')
        {
            // If the caracter is a number
            if(isdigit(*_characterIterator)) 
            {
                parameterValue = (parameterValue * 10) + (static_cast<float>(*_characterIterator) - 48);
            }
            // If the caracter is a comma wich mark a new parameter
            else if(*_characterIterator == ',')
            {
                parameterValues.emplace_back(parameterValue);
                parameterValue = 0;
            }
        }
        parameterValues.emplace_back(parameterValue);
    }
    // Cancel the last iteration;
    _characterIterator--;
    // Return the final module
    return LSystemModule(name, parameterValues);
}
