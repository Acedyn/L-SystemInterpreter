#include "l-SystemInterpreter/l-SystemExpression.h"

#include "l-SystemInterpreter/l-SystemAbstractModule.h"
#include "l-SystemInterpreter/l-SystemParameters.h"

#include <iostream>
#include <math.h>

////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemExpression::operator==(const LSystemExpression& _other) const
{
    // Test if the expressions matches
    if(expression != _other.getExpression()) { return false; }

    // If both modules are set
    if(module != nullptr && _other.getModule() != nullptr)
    {
        // Test if the modules matches
        if(*module != *(_other.getModule())) { return false; }
    }
    else
    {
        // Test if the modules matches
        if(module != _other.getModule()) { return false; }
    }

    // If both globalParameters are set
    if(globalParameters != nullptr && _other.getGlobalParameters() != nullptr)
    {
        // Test if the parameters matches
        if(*globalParameters != *(_other.getGlobalParameters())) { return false; }
    }
    else
    {
        // Test if the parametres matches
        if(globalParameters != _other.getGlobalParameters()) { return false; }
    }
    
    // If all the tests passes return true
    return true;
}

bool LSystemExpression::operator!=(const LSystemExpression& _other) const
{
    // Test if the expressions matches
    if(expression != _other.getExpression()) { return true; }

    // If both modules are set
    if(module != nullptr && _other.getModule() != nullptr)
    {
        // Test if the modules matches
        if(*module != *(_other.getModule())) { return true; }
    }
    else
    {
        // Test if the modules matches
        if(module != _other.getModule()) { return true; }
    }

    // If both globalParameters are set
    if(globalParameters != nullptr && _other.getGlobalParameters() != nullptr)
    {
        // Test if the parameters matches
        if(*globalParameters != *(_other.getGlobalParameters())) { return true; }
    }
    else
    {
        // Test if the parametres matches
        if(globalParameters != _other.getGlobalParameters()) { return true; }
    }
    
    // If all the tests passes return false
    return false;
}


////////////////////////////////////////
// Getters / setters
////////////////////////////////////////
void LSystemExpression::setExpression(std::string _expression)
{
    expression = _expression;
}

void LSystemExpression::setModule(LSystemAbstractModule* _module)
{
    module = _module;
}

void LSystemExpression::setGlobalParameters(LSystemParameters* _globalParameters)
{
    globalParameters = _globalParameters;
}


////////////////////////////////////////
// Public functions
////////////////////////////////////////
float LSystemExpression::parseDecimalExpression()
{
    if(expression.empty()) { return 0.0f; }
    expressionIterator = expression.begin();
    float _result = parseOperatorLvl8();
    return _result;
}

bool LSystemExpression::parseBinaryExpression()
{
    if(expression.empty()) { return false; }
    expressionIterator = expression.begin();
    float _result = parseOperatorLvl8();
    if(_result != 0.0f)
    {
        return true;
    }
    return false;
}


////////////////////////////////////////
// Parsing functions
////////////////////////////////////////
// Parse number
float LSystemExpression::parseNumber()
{
    // Store the result of the number
    float result = 0.0f;
    float floatingValueResult = 0.0f;
    
    int digitCount = 0;
    bool isFloatingValue = false;

    // Cast the character to integer
    int number = static_cast<int>(*expressionIterator) - 48;
    // Loop until the character is a number or a decimal comma
    while ((number >= 0 && number <= 9) || *expressionIterator == '.')
    {
        // If the character is a number
        if(number >= 0 && number <= 9)
        {
            // If we are parsing numbers before the decimal comma
            if(!isFloatingValue)
            {
                // Append the value to the result
                result = result * 10 + (static_cast<int>(*expressionIterator) - 48);
                // Increment the iterator
                expressionIterator++;
                // Cast the character to integer
                number = static_cast<int>(*expressionIterator) - 48;
            }
            // If we are parsing numbers after the decimal comma
            else
            {
                // Append the value to the floating result
                floatingValueResult = floatingValueResult * 10 + (static_cast<int>(*expressionIterator) - 48);
                // Increment the count of numbers after the decimal comma
                digitCount++;
                // Increment the iterator
                expressionIterator++;
                // Cast the character to integer
                number = static_cast<int>(*expressionIterator) - 48;
            }
        }
        // If the character is a '.'
        else
        {
            // Switch to parsing numbers after the decimal comma
            isFloatingValue = true;
        }
    }
    // Return the parsed value
    return result + (floatingValueResult / pow(10, digitCount));
}

// Parse variable
float LSystemExpression::parseParameter()
{
    // Store the result of the parameter
    float result = 0.0f;

    std::string _parsedParameter;

    while(isalpha(*expressionIterator))
    {
        _parsedParameter.push_back(*expressionIterator);
        expressionIterator++;
    }

    // Loop over all the global parameters
    for(LSystemParameter _globalParameter : *globalParameters)
    {
        // If the name of the parameter matches the parsed Parameter's name
        if(_parsedParameter == _globalParameter.name)
        {
            // Return the parameter's value
            return _globalParameter.value;
        }
    }

    // If the module is linked
    if(module->isLinked())
    {
        // Loop over all the module's parameters
        for(LSystemParameter _moduleParameter : module->getParameters())
        {
            // If the name of the parameter matches the parsed Parameter's name
            if(_parsedParameter == _moduleParameter.name)
            {
                // Return the parameter's value
                return _moduleParameter.value;
            }
        }
    }

    return result;
}

// Parse unary minus (TODO)
float LSystemExpression::parseOperatorLvl1()
{
    // Store the result of the operator, initialized with the parseNumber() or parseParameter()
    float result;
    
    if(isdigit(*expressionIterator)) { result = parseNumber(); }
    else if(isalpha(*expressionIterator)) { result = parseParameter(); }
    else { result = 0.0f; }

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
