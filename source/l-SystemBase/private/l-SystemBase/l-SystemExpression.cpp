#include "l-SystemBase/l-SystemExpression.h"

#include "l-SystemBase/l-SystemAbstractModule.h"
#include "l-SystemBase/l-SystemParameters.h"

#include <iostream>
#include <math.h>

////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemExpression::operator==(const LSystemExpression& _other) const
{
    // Test if the expressions matches
    if(expression != _other.getExpression()) { return false; }

    // Test if the modules matches
    if (moduleParameters != _other.getModuleParameters()) { return false; }

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

    // Test if the modules matches
    if (moduleParameters != _other.getModuleParameters()) { return true; }

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
    
    // If all the tests passes return true
    return false;
}


////////////////////////////////////////
// Getters / setters
////////////////////////////////////////
void LSystemExpression::setExpression(std::string _expression)
{
    expression = _expression;
}

void LSystemExpression::setModuleParameters(std::vector<LSystemAbstractModule*> _moduleParameters)
{
    moduleParameters = _moduleParameters;
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

    // Security check if we are at the end of the expression
    if (expressionIterator == expression.end()) { return result; }

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
                // Security check if we are at the end of the expression
                if (expressionIterator == expression.end()) { break; }
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
                // Security check if we are at the end of the expression
                if (expressionIterator == expression.end()) { break; }
                // Cast the character to integer
                number = static_cast<int>(*expressionIterator) - 48;
            }
        }
        // If the character is a '.'
        else
        {
            // Switch to parsing numbers after the decimal comma
            isFloatingValue = true;
            // Increment the iterator
            expressionIterator++;
            // Security check if we are at the end of the expression
            if (expressionIterator == expression.end()) { break; }
            // Cast the character to integer
            number = static_cast<int>(*expressionIterator) - 48;
        }
    }
    // Return the parsed value
    return result + (floatingValueResult / static_cast<float>(pow(10, digitCount)));
}

// Parse variable
float LSystemExpression::parseParameter()
{
    std::string _parsedParameter;


    // Security check if we are at the end of the expression
    if (expressionIterator == expression.end()) { return 0.0f; }

    while(isalpha(*expressionIterator) || isdigit(*expressionIterator))
    {
        _parsedParameter.push_back(*expressionIterator);
        expressionIterator++;

        // Security check if we are at the end of the expression
        if (expressionIterator == expression.end()) { break; }
    }

    // If global parameters is set
    if(globalParameters != nullptr)
    {
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
    }

    // Loop over all the module parameters
    for(LSystemAbstractModule* _moduleParameter : moduleParameters)
    {
        // If the module is linked
        if (!_moduleParameter->isLinked()) { continue; }

        // Loop over all the module's parameters
        for(LSystemParameter _moduleParameter : _moduleParameter->getParameters())
        {
            // If the name of the parameter matches the parsed Parameter's name
            if(_parsedParameter == _moduleParameter.name)
            {
                // Return the parameter's value
                return _moduleParameter.value;
            }
        }
    }

    return 0.0f;
}

// Parse unary minus (TODO)
float LSystemExpression::parseOperatorLvl1()
{
    // Store the result of the operator, initialized with the parseNumber() or parseParameter()
    float _result = 0.0f;
    // Security check if we are at the end of the expression
    if (expressionIterator == expression.end()) { return _result; }

    
    if(isdigit(*expressionIterator)) { _result = parseNumber(); }
    else if(isalpha(*expressionIterator)) { _result = parseParameter(); }

    return _result;
}

// Parse exponent
float LSystemExpression::parseOperatorLvl2()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl1();
    // Security check if we are at the end of the expression
    if (expressionIterator == expression.end()) { return _result; }

    while (*expressionIterator == '^') 
    {
        expressionIterator++;
        // Compute the operation with the left side and the right side of the operator
        _result = pow(_result, parseOperatorLvl1());


        // Security check if we are at the end of the expression
        if (expressionIterator == expression.end()) { break; }
    }
    return _result;
}

// Parse multiplication, division, modulo
float LSystemExpression::parseOperatorLvl3()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl2();
    // Security check if we are at the end of the expression
    if (expressionIterator == expression.end()) { return _result; }

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


        // Security check if we are at the end of the expression
        if (expressionIterator == expression.end()) { break; }
    }
    return _result;
}

// Parse addition, substraction
float LSystemExpression::parseOperatorLvl4()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl3();
    // Security check if we are at the end of the expression
    if (expressionIterator == expression.end()) { return _result; }

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

        // Security check if we are at the end of the expression
        if (expressionIterator == expression.end()) { break; }
    }
    return _result;
}

// Parse less, greater, ...
float LSystemExpression::parseOperatorLvl5()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl4();
    // Security check if we are at the end of the expression
    if (expressionIterator == expression.end()) { return _result; }

    while(*expressionIterator == '<' || *expressionIterator == '>')
    {
        if(*expressionIterator == '<')
        {
            expressionIterator++;

            // Security check if we are at the end of the expression
            if (expressionIterator == expression.end()) { break; }

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

            // Security check if we are at the end of the expression
            if (expressionIterator == expression.end()) { break; }

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

        // Security check if we are at the end of the expression
        if (expressionIterator == expression.end()) { break; }
    }
    return _result;
}

// Parse equality and inequality
float LSystemExpression::parseOperatorLvl6()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl5();
    // Security check if we are at the end of the expression
    if (expressionIterator == expression.end()) { return _result; }

    while(*expressionIterator == '=' || *expressionIterator == '!')
    {
        if(*expressionIterator == '=')
        {
            expressionIterator++;

            // Security check if we are at the end of the expression
            if (expressionIterator == expression.end()) { break; }

            if(*expressionIterator == '=')
            {
                expressionIterator++;
                // Compute the operation with the left side and the right side of the operator
                _result = _result == parseOperatorLvl5();
            }
        }
        else
        {
            expressionIterator++;

            // Security check if we are at the end of the expression
            if (expressionIterator == expression.end()) { break; }

            if(*expressionIterator == '=')
            {
                expressionIterator++;
                // Compute the operation with the left side and the right side of the operator
                _result = _result != parseOperatorLvl5();
            }
        }

        // Security check if we are at the end of the expression
        if (expressionIterator == expression.end()) { break; }
    }
    return _result;
}

// Parse logial and
float LSystemExpression::parseOperatorLvl7()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl6();
    // Security check if we are at the end of the expression
    if (expressionIterator == expression.end()) { return _result; }

    while (*expressionIterator == '&')
    {
        expressionIterator++;

        // Security check if we are at the end of the expression
        if (expressionIterator == expression.end()) { break; }

        if(*expressionIterator == '&')
        {
            expressionIterator++;
            // Compute the operation with the left side and the right side of the operator
            _result = _result && parseOperatorLvl6();
        }

        // Security check if we are at the end of the expression
        if (expressionIterator == expression.end()) { break; }
    }
    return _result;
}

// Parse logial or
float LSystemExpression::parseOperatorLvl8()
{
    // Store the result of the operator, initialized with the computed left side of the operator
    float _result = parseOperatorLvl7();
    // Security check if we are at the end of the expression
    if (expressionIterator == expression.end()) { return _result; }

    while (*expressionIterator == '|')
    {
        expressionIterator++;

        // Security check if we are at the end of the expression
        if (expressionIterator == expression.end()) { break; }

        if(*expressionIterator == '|')
        {
            expressionIterator++;
            // Compute the operation with the left side and the right side of the operator
            _result = _result || parseOperatorLvl7();
        }

        // Security check if we are at the end of the expression
        if (expressionIterator == expression.end()) { break; }
    }
    return _result;
}
