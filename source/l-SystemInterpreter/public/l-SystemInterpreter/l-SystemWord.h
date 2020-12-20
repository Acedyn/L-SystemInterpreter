#pragma once
#include "l-SystemInterpreter/l-SystemModule.h"

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
    LSystemWord(LSystemWord& _lSystemWord);
    ~LSystemWord() {  }

    // Getters / setters / append
    void appendModule(LSystemModule _module);
    void appendCommand(char _command);
    std::vector<wordComponent> getComponents() { return components; }
    std::vector<LSystemModule> getModules() { return modules; }
    std::vector<char> getCommands() { return commands; }

private:
    // Private functions
    void parseWord(std::string _word);
    LSystemModule parseModule(std::string::iterator& _character);

    // Private variables
    std::vector<wordComponent> components;
    std::vector<LSystemModule> modules;
    std::vector<char> commands;
};
