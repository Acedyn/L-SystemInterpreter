#pragma once

#include <string>

class LSystemCondition
{
public:
    // Constructors / desctructors
    LSystemCondition(std::string _expression);
    ~LSystemCondition() { }

    // Operators
    bool operator==(const LSystemCondition& _other) const;

    // Getters / setters
    void setExpression(std::string _expression);
    std::string getExpression() const { return expression; }

    // Public functions
    bool parseExpression(class LSystemModule _module);


private:
    // Private variables
    std::string expression;
    std::string::iterator expressionIterator;

    // Parsing functions
    float parseNumber();       // parse numer
    float parseParameter();    // parse variable
    float parseOperatorLvl1(); // parse unary minus and logical negation
    float parseOperatorLvl2(); // parse exponent
    float parseOperatorLvl3(); // parse multiplication, division, modulo
    float parseOperatorLvl4(); // parse addition, substraction
    float parseOperatorLvl5(); // parse less, greater, equal, ...
    float parseOperatorLvl6(); // parse equality and inequality
    float parseOperatorLvl7(); // parse logial and
    float parseOperatorLvl8(); // parse logial or
};
