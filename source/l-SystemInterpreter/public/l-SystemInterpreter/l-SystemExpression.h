#pragma once

#include <string>

class LSystemExpression
{
public:
    // Constructors / desctructors
    LSystemExpression() { }
    LSystemExpression(
            class LSystemAbstractModule* _module, 
            class LSystemParameters* _globalParameters = nullptr) :
        module(_module),
        globalParameters(_globalParameters) { }
    LSystemExpression(
            class LSystemParameters* _globalParameters,
            class LSystemAbstractModule* _module = nullptr) : 
        globalParameters(_globalParameters),
        module(_module) { }
    LSystemExpression(
            std::string _expression, 
            class LSystemAbstractModule* _module, 
            class LSystemParameters* _globalParameters = nullptr) :
        expression(_expression),
        module(_module),
        globalParameters(_globalParameters) { }
    LSystemExpression(
            std::string _expression, 
            class LSystemParameters* _globalParameters,
            class LSystemAbstractModule* _module = nullptr) :
        expression(_expression),
        globalParameters(_globalParameters),
        module(_module) { }
    ~LSystemExpression() { }

    // Operators
    bool operator==(const LSystemExpression& _other) const;
    bool operator!=(const LSystemExpression& _other) const;

    // Getters / setters
    void setExpression(std::string _expression);
    std::string getExpression() const { return expression; }
    void setModule(class LSystemAbstractModule* _module);
    class LSystemAbstractModule* getModule() const { return module; }
    void setGlobalParameters(class LSystemParameters* _globalParameters);
    class LSystemParameters* getGlobalParameters() const { return globalParameters; }

    // Public functions
    float parseDecimalExpression();
    bool parseBinaryExpression();


private:
    // Private variables
    std::string expression;
    std::string::iterator expressionIterator;
    class LSystemAbstractModule* module  = nullptr;
    class LSystemParameters* globalParameters = nullptr;

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
