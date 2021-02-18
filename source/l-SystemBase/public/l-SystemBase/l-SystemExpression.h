#pragma once

#include <string>
#include <vector>

class LSystemParameters;
class LSystemAbstractModule;

class LSystemExpression
{
public:
    // Constructors / desctructors
    LSystemExpression() { }
    LSystemExpression(std::string _expression) :
        expression(_expression) { }
    LSystemExpression(
            std::string _expression, 
            std::vector<LSystemAbstractModule*> _module,
            LSystemParameters* _globalParameters = nullptr) :
        expression(_expression),
        moduleParameters(_module),
        globalParameters(_globalParameters) { }
    LSystemExpression(
            std::string _expression, 
            LSystemParameters* _globalParameters,
            std::vector<LSystemAbstractModule*> _module = std::vector<LSystemAbstractModule*>()) :
        expression(_expression),
        globalParameters(_globalParameters),
        moduleParameters(_module) { }
    ~LSystemExpression() { }

    // Operators
    bool operator==(const LSystemExpression& _other) const;
    bool operator!=(const LSystemExpression& _other) const;

    // Getters / setters
    void setExpression(std::string _expression);
    std::string getExpression() const { return expression; }
    void setModuleParameters(std::vector<LSystemAbstractModule*> _moduleParameters);
    std::vector<LSystemAbstractModule*> getModuleParameters() const { return moduleParameters; }
    void setGlobalParameters(LSystemParameters* _globalParameters);
    LSystemParameters* getGlobalParameters() const { return globalParameters; }

    // Public functions
    float parseDecimalExpression();
    bool parseBinaryExpression();


private:
    // Private variables
    std::string expression;
    std::string::iterator expressionIterator;
    std::vector<LSystemAbstractModule*> moduleParameters;
    LSystemParameters* globalParameters = nullptr;

    // Parsing functions
    float parseNumber();       // parse numer
    float parseParameter();    // parse variable
    float parseOperatorLvl1(); // parse unary minus and logical negation
    float parseOperatorLvl2(); // parse exponent
    float parseOperatorLvl3(); // parse multiplication, division, modulo
    float parseOperatorLvl4(); // parse addition, substraction
    float parseOperatorLvl5(); // parse less, greater, ...
    float parseOperatorLvl6(); // parse equality and inequality
    float parseOperatorLvl7(); // parse logial and
    float parseOperatorLvl8(); // parse logial or
};
