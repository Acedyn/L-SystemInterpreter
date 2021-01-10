#pragma once

#include "l-SystemInterpreter/l-SystemModule.h"

#include <string>
#include <vector>

// Array of elements representing the result or a step of an l-system
class LSystemWord
{
public:
    // Constructors / desctructors
    LSystemWord() { }
    LSystemWord(std::string _word);
    LSystemWord(std::vector<LSystemModule> _modules) : modules(_modules) { }
    ~LSystemWord() { }

    // Getters / setters / append
    void appendModule(LSystemModule _module);
    void appendWord(LSystemWord _word);
    std::vector<LSystemModule> getModules() const { return modules; }

    // Iterator
    std::vector<LSystemModule>::iterator begin() { return modules.begin(); }
    std::vector<LSystemModule>::iterator end() { return modules.end(); }

private:
    // Private functions
    void parseWord(std::string _word);

    // Private variables
    std::vector<LSystemModule> modules;
};
