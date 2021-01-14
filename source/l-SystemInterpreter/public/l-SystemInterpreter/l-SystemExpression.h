#pragma once

#include <string>

class LSystemExpression
{
public:
    // Constructors / desctructors
    LSystemExpression(class LSystemConcreteModule* _module = nullptr, class LSystemParameters* _parameters = nullptr) :
        module(_module),
        parameters(_parameters) { }
    LSystemExpression(std::string _expression, class LSystemConcreteModule* _module = nullptr, class LSystemParameters* _parameters = nullptr);
    ~LSystemExpression() { }

    // Operators
    bool operator==(const LSystemExpression& _other) const;
    bool operator!=(const LSystemExpression& _other) const;

    // Getters / setters
    void setExpression(std::string _expression);
    std::string getExpression() const { return expression; }
    void setModule(class LSystemConcreteModule* _module);
    void setParameters(class LSystemParameters* _parameters);

    // Public functions
    float parseDecimalExpression(class LSystemConcreteModule _module);
    bool parseBinaryExpression(class LSystemConcreteModule _module);


private:
    // Private variables
    std::string expression;
    std::string::iterator expressionIterator;
    class LSystemConcreteModule* module  = nullptr;
    class LSystemParameters* parameters = nullptr;

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
