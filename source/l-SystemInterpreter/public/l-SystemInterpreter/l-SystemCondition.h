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
};
