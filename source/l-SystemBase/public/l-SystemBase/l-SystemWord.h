#pragma once

#include "l-SystemConcreteModule.h"

#include <string>
#include <vector>

class LSystemAbstractModule;
class LSystemParameters;

// Array of elements representing the result or a step of an l-system
class LSystemWord
{
public:
    // Constructors / desctructors
    LSystemWord(
        LSystemParameters* _parameters = nullptr, 
        std::vector<LSystemAbstractModule*> _moduleParameters = std::vector<LSystemAbstractModule*>()) : 
        parameters(_parameters),
        moduleParameters(_moduleParameters) { }
    LSystemWord(
        std::vector<LSystemConcreteModule> _modules, 
        LSystemParameters* _parameters = nullptr,
        std::vector<LSystemAbstractModule*> _moduleParameters = std::vector<LSystemAbstractModule*>()) :
        modules(_modules),
        parameters(_parameters),
        moduleParameters(_moduleParameters) { }
    LSystemWord(
        std::string _word,
        LSystemParameters* _parameters = nullptr,
        std::vector<LSystemAbstractModule*> _moduleParameters = std::vector<LSystemAbstractModule*>());
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
    std::vector<LSystemAbstractModule*> getModuleParameters() const { return moduleParameters; }
    void setModuleParameters(std::vector<LSystemAbstractModule*> _moduleParameters) { moduleParameters = _moduleParameters; }

    // Iterator
    std::vector<LSystemConcreteModule>::iterator begin() { return modules.begin(); }
    std::vector<LSystemConcreteModule>::iterator end() { return modules.end(); }

private:
    // Private functions
    void parseWord();

    // Private variables
    std::vector<LSystemConcreteModule> modules;
    LSystemParameters* parameters = nullptr;
    std::vector<LSystemAbstractModule*> moduleParameters;
    std::string originalString;
};
