#include "l-SystemInterpreter/l-SystemCondition.h"
#include "l-SystemInterpreter/l-SystemModule.h"

#include <iostream>
#include <math.h>

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemCondition::LSystemCondition(std::string _expression)
{
    setExpression(_expression);
}


////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemCondition::operator==(const LSystemCondition& _other) const
{
    if(expression == _other.getExpression())
    {
        return true;
    }
    return false;
}


////////////////////////////////////////
// Getters / setters
////////////////////////////////////////
void LSystemCondition::setExpression(std::string _expression)
{
    expression = _expression;
}


////////////////////////////////////////
// Public functions
////////////////////////////////////////
bool LSystemCondition::parseExpression(LSystemModule _module)
{
    if(expression.empty()) { return false; }
    expressionIterator = expression.begin();
    float result = parseOperatorLvl4();
    std::cout << result << std::endl;
    return true;
}


////////////////////////////////////////
// Parsing functions
////////////////////////////////////////
float LSystemCondition::parseNumber()
{
    float result = static_cast<float>(*expressionIterator) - 48;
    expressionIterator++;
    int number = static_cast<int>(*expressionIterator) - 48;
    while (number >= 0 && number <= 9)
    {
        result = result * 10 + (static_cast<int>(*expressionIterator) - 48);
        expressionIterator++;
        number = static_cast<int>(*expressionIterator) - 48;
    }
    return result;
}

float LSystemCondition::parseOperatorLvl1()
{
    float result = parseNumber();
    return result;
}

float LSystemCondition::parseOperatorLvl2()
{
    float result = parseOperatorLvl1();
    while (*expressionIterator == '^') 
    {
        expressionIterator++;
        result = pow(result, parseOperatorLvl1());
    }
    return result;
}

float LSystemCondition::parseOperatorLvl3()
{
    float result = parseOperatorLvl2();
    while (*expressionIterator == '*' || *expressionIterator == '/' || *expressionIterator == '%') 
    {
        if(*expressionIterator == '*')
        {
            expressionIterator++;
            result *= parseOperatorLvl3();
        }
        else if (*expressionIterator == '/')
        {
            expressionIterator++;
            result /= parseOperatorLvl3();
        }
        else
        {
            expressionIterator++;
            result = fmod(result, parseOperatorLvl3());
        }
    }
    return result;
}

float LSystemCondition::parseOperatorLvl4()
{
    float result = parseOperatorLvl3();
    while (*expressionIterator == '+' || *expressionIterator == '-') 
    {
        if(*expressionIterator == '+')
        {
            expressionIterator++;
            result += parseOperatorLvl3();
        }
        else
        {
            expressionIterator++;
            result -= parseOperatorLvl3();
        }
    }
    return result;
}

