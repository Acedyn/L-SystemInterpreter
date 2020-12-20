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
    std::vector<LSystemModule> getModules() { return modules; }

private:
    // Private functions
    void parseWord(std::string _word);

    // Private variables
    std::vector<LSystemModule> modules;
};
