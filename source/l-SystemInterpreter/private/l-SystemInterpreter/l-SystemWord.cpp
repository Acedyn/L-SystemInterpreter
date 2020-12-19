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
    std::cout << "Parsing word" << std::endl;
    // Loop over all the characters
    for(std::string::iterator wordIterator = _word.begin(); wordIterator != _word.end(); wordIterator++)
    {
        // If the character is a module
        if(isalpha(*wordIterator))
        {
            std::cout << "Parsing module" << std::endl;
            LSystemModule newModule = parseModule(wordIterator);
            appendModule(&newModule);
            std::cout << newModule.getName();
            std::vector<float> newModuleParameterValues = newModule.getParameterValues();
            for(float newModuleParameter : newModuleParameterValues)
            {
                std::cout << " " << newModuleParameter;
            }
            std::cout << " parsed" << std::endl;
        }
        // If the character is a command
        else
        {
            std::cout << "Parsing command" << std::endl;
            appendCommand(*wordIterator);
            std::cout << *wordIterator << " parsed" << std::endl;
        }
    }
}

LSystemModule LSystemWord::parseModule(std::string::iterator& _character)
{
    // The name of the module
    char name = *_character;
    // The parameters values of the module
    std::vector<float> parameterValues;

    // If the module doesn't have parameters
    if(*(_character++) != '(')
    {
        // Cancel the last iteration
        _character--;
        // Return module with just a name
        return LSystemModule(name);
    }
    // If the module does have parameters
    else
    {
        float parameterValue = 0;
        // Loop over all the caracters until the end of the parameters
        while(*(_character++) != ')')
        {
            // If the caracter is a number
            if(!isdigit(*_character)) 
            {
                parameterValue = (parameterValue * 10) + (static_cast<int>(*_character) - 48);
            }
            // If the caracter is a comma wich mark a new parameter
            else if(*_character == ',')
            {
                parameterValues.emplace_back(parameterValue);
                parameterValue = 0;
            }
        }
    }
    return LSystemModule(name, parameterValues);
}
