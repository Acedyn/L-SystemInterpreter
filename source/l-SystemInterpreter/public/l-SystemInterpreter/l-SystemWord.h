#pragma once

#include "l-SystemInterpreter/l-SystemModule.h"

#include <string>
#include <vector>

// Array of elements representing the result or a step of an l-system
class LSystemWord
{
public:
    // Constructors / desctructors
    LSystemWord(class LSystemParameters* _parameters = nullptr) : parameters(_parameters) { }
    LSystemWord(std::string _word, class LSystemParameters* _parameters = nullptr);
    LSystemWord(std::vector<LSystemModule> _modules, class LSystemParameters* _parameters = nullptr) : 
        modules(_modules) { }
    ~LSystemWord() { }

    // Operators
    bool operator==(const LSystemWord& _other) const;
    bool operator!=(const LSystemWord& _other) const;
    friend std::ostream& operator<<(std::ostream& stream, const LSystemWord& _word);

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
    class LSystemParameters* parameters = nullptr;
};
