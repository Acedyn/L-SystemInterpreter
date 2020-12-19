#pragma once

#include <string>
#include <vector>

// Array of elements representing the result or a step of an l-system
class LSystemWord
{
public:
    // Enums
    enum wordComponent
    {
        MODULE,
        COMMAND
    };

    // Constructors / desctructors
    LSystemWord(std::string _word);

    // Getters / setters / append
    void appendModule(class LSystemModule* _module);
    void appendCommand(char _command);

private:
    // Private functions
    void parseWord(std::string _word);
    class LSystemModule parseModule(std::string::iterator& _character);

    // Private variables
    std::vector<wordComponent> components;
    std::vector<class LSystemModule*> modules;
    std::vector<char> commands;
};
