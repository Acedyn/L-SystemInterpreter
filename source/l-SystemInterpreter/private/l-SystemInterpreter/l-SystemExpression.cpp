#include "l-SystemInterpreter/l-SystemExpression.h"
#include "l-SystemInterpreter/l-SystemModule.h"

#include <iostream>
#include <math.h>

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemExpression::LSystemExpression(std::string _expression)
{
    setExpression(_expression);
}


////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemExpression::operator==(const LSystemExpression& _other) const
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
void LSystemExpression::setExpression(std::string _expression)
{
    expression = _expression;
}


////////////////////////////////////////
// Public functions
////////////////////////////////////////
float LSystemExpression::parseDecimalExpression(LSystemModule _module)
{
    if(expression.empty()) { return 0.0f; }
    expressionIterator = expression.begin();
    float _result = parseOperatorLvl8();
    return _result;
}

bool LSystemExpression::parseBinaryExpression(LSystemModule _module)
{
    if(expression.empty()) { return false; }
    expressionIterator = expression.begin();
    return true;
}


////////////////////////////////////////
// Parsing functions
////////////////////////////////////////
// Parse number
float LSystemExpression::parseNumber()
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

// Parse variable
float LSystemExpression::parseParameter()
{
    float result = 0;
    return result;
}

// Parse unary minus (TODO)
float LSystemExpression::parseOperatorLvl1()
{
    float result = parseNumber();
    return result;
}

// Parse exponent
float LSystemExpression::parseOperatorLvl2()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl1();
    while (*expressionIterator == '^') 
    {
        expressionIterator++;
        // Compute the operation with the left side and the right side of the operator
        _result = pow(_result, parseOperatorLvl1());
    }
    return _result;
}

// Parse multiplication, division, modulo
float LSystemExpression::parseOperatorLvl3()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl2();
    while (*expressionIterator == '*' || *expressionIterator == '/' || *expressionIterator == '%') 
    {
        if(*expressionIterator == '*')
        {
            expressionIterator++;
                // Compute the operation with the left side and the right side of the operator
            _result = _result * parseOperatorLvl2();
        }
        else if (*expressionIterator == '/')
        {
            expressionIterator++;
                // Compute the operation with the left side and the right side of the operator
            _result = _result / parseOperatorLvl2();
        }
        else
        {
            expressionIterator++;
                // Compute the operation with the left side and the right side of the operator
            _result = fmod(_result, parseOperatorLvl2());
        }
    }
    return _result;
}

// Parse addition, substraction
float LSystemExpression::parseOperatorLvl4()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl3();
    // Will store the result of the operator
    while (*expressionIterator == '+' || *expressionIterator == '-') 
    {
        if(*expressionIterator == '+')
        {
            expressionIterator++;
                // Compute the operation with the left side and the right side of the operator
            _result = _result + parseOperatorLvl3();
        }
        else
        {
            expressionIterator++;
                // Compute the operation with the left side and the right side of the operator
            _result = _result - parseOperatorLvl3();
        }
    }
    return _result;
}

// Parse less, greater, ...
float LSystemExpression::parseOperatorLvl5()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl4();
    while(*expressionIterator == '<' || *expressionIterator == '>')
    {
        if(*expressionIterator == '<')
        {
            expressionIterator++;
            if(*expressionIterator == '=')
            {
                expressionIterator++;
                // Compute the operation with the left side and the right side of the operator
                _result = _result <= parseOperatorLvl4();
            }
            else
            {
                // Compute the operation with the left side and the right side of the operator
                _result = _result < parseOperatorLvl4();
            }
        }
        else
        {
            expressionIterator++;
            if(*expressionIterator == '=')
            {
                expressionIterator++;
                // Compute the operation with the left side and the right side of the operator
                _result = _result >= parseOperatorLvl4();
            }
            else
            {
                // Compute the operation with the left side and the right side of the operator
                _result = _result > parseOperatorLvl4();
            }
        }
    }
    return _result;
}

// Parse equality and inequality
float LSystemExpression::parseOperatorLvl6()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl5();
    while(*expressionIterator == '=' || *expressionIterator == '!')
    {
        if(*expressionIterator == '=')
        {
            expressionIterator++;
            if(*expressionIterator == '=')
            {
                // Compute the operation with the left side and the right side of the operator
                _result = _result == parseOperatorLvl5();
            }
        }
        else
        {
            expressionIterator++;
            if(*expressionIterator == '=')
            {
                // Compute the operation with the left side and the right side of the operator
                _result = _result != parseOperatorLvl5();
            }
        }
    }
    return _result;
}

// Parse logial and
float LSystemExpression::parseOperatorLvl7()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl6();
    while (*expressionIterator == '&')
    {
        expressionIterator++;
        if(*expressionIterator == '&')
        {
            expressionIterator++;
            // Compute the operation with the left side and the right side of the operator
            _result = _result && parseOperatorLvl6();
        }
    }
    return _result;
}

// Parse logial or
float LSystemExpression::parseOperatorLvl8()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl7();
    while (*expressionIterator == '|')
    {
        expressionIterator++;
        if(*expressionIterator == '|')
        {
            expressionIterator++;
            // Compute the operation with the left side and the right side of the operator
            _result = _result || parseOperatorLvl7();
        }
    }
    return _result;
}
