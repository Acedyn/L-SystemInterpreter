#include "l-SystemInterpreter/l-SystemWord.h"

#include <iostream>
#include "ctype.h"

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemWord::LSystemWord(std::string _word)
{
    // We parse the input string into modules of commands
    parseWord(_word);
}
LSystemWord::LSystemWord(LSystemWord& _lSystemWord)
{
    // For the modules we need to copy them one by one to make sure we have two separate copies
    for(LSystemModule _module : _lSystemWord.getModules())
    {
        modules.emplace_back(_module);
    }
}


////////////////////////////////////////
// Getters / setters / append
////////////////////////////////////////
void LSystemWord::appendModule(LSystemModule _module)
{
    modules.emplace_back(_module);
}

void LSystemWord::appendWord(LSystemWord _word)
{
    for(LSystemWord::Iterator _wordIterator = _word.begin(); _wordIterator != _word.end(); _wordIterator++)
    {
        this->appendModule(*(*_wordIterator));
    }
}


////////////////////////////////////////
// Private functions
////////////////////////////////////////
void LSystemWord::parseWord(std::string _word)
{
    // Loop over all the modules of the word
    for(std::string::iterator _wordIterator = _word.begin(); _wordIterator != _word.end(); _wordIterator++)
    {
        // The name of the module
        char name = *_wordIterator;
        // The parameters values of the module
        std::vector<float> parameterValues;

        // Iterate the character to see if the module does have parameters
        _wordIterator++;
        // If the module doesn't have parameters
        if(*_wordIterator != '(')
        {
            // Store a module with just a name
            appendModule(LSystemModule(name));
        }
        // If the module does have parameters
        else
        {
            float parameterValue = 0;
            // Loop over all the caracters until the end of the parameters
            while(*(_wordIterator++) != ')')
            {
                // If the caracter is a number
                if(isdigit(*_wordIterator)) 
                {
                    parameterValue = (parameterValue * 10) + (static_cast<float>(*_wordIterator) - 48);
                }
                // If the caracter is a comma wich mark a new parameter
                else if(*_wordIterator == ',')
                {
                    parameterValues.emplace_back(parameterValue);
                    parameterValue = 0;
                }
            }
            parameterValues.emplace_back(parameterValue);
        // Store the module
        appendModule(LSystemModule(name, parameterValues));
        }
        // Undo the last iteration
        _wordIterator--;
    }
}
