#pragma once

#include <string>

class LSystemExpression
{
public:
    // Constructors / desctructors
    LSystemExpression() {  }
    LSystemExpression(std::string _expression);
    ~LSystemExpression() { }

    // Operators
    bool operator==(const LSystemExpression& _other) const;

    // Getters / setters
    void setExpression(std::string _expression);
    std::string getExpression() const { return expression; }

    // Public functions
    float parseDecimalExpression(class LSystemModule _module);

    bool parseBinaryExpression(class LSystemModule _module);


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
    float parseOperatorLvl5(); // parse less, greater, ...
    float parseOperatorLvl6(); // parse equality and inequality
    float parseOperatorLvl7(); // parse logial and
    float parseOperatorLvl8(); // parse logial or
};
