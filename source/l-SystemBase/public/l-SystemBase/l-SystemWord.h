#pragma once

#include "l-SystemConcreteModule.h"

#include <string>
#include <vector>

// Array of elements representing the result or a step of an l-system
class LSystemWord
{
public:
    // Constructors / desctructors
    LSystemWord(class LSystemParameters* _parameters = nullptr) : parameters(_parameters) { }
    LSystemWord(std::vector<LSystemConcreteModule> _modules, class LSystemParameters* _parameters = nullptr) : 
        modules(_modules) { }
    LSystemWord(std::string _word, class LSystemParameters* _parameters = nullptr);
    ~LSystemWord() { }

    void reParseWord();

    // Operators
    bool operator==(const LSystemWord& _other) const;
    bool operator!=(const LSystemWord& _other) const;
    friend std::ostream& operator<<(std::ostream& stream, const LSystemWord& _word);

    // Getters / setters / append
    void appendModule(LSystemConcreteModule _module);
    void appendWord(LSystemWord _word);
    std::vector<LSystemConcreteModule> getModules() const { return modules; }
    LSystemParameters* getParameters() const { return parameters; }
    void setParameters(LSystemParameters* _parameters) { parameters = _parameters; }

    // Iterator
    std::vector<LSystemConcreteModule>::iterator begin() { return modules.begin(); }
    std::vector<LSystemConcreteModule>::iterator end() { return modules.end(); }

private:
    // Private functions
    void parseWord();

    // Private variables
    std::vector<LSystemConcreteModule> modules;
    class LSystemParameters* parameters = nullptr;
    std::string originalString;
};
