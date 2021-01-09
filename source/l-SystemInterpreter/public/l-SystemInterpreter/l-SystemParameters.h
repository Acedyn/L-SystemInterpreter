#pragma once

#include <vector>
#include <string>
#include <ctype.h>

// Data structure containing a name and a value of a parameter for an l-system
struct LSystemParameter
{
    // Constructors / Destructors
    LSystemParameter(std::string _name, float _value)
    {
        // Test if the name of the parameter does contain only letters
        bool _isValidString = true;
        for(char _character : name)
        {
            if(!isalpha(_character)) { _isValidString = false; }
        }

        if(_isValidString)
        {
            name = _name;
            value = _value;
            isValidParameter = true;
        }
        else
        {
            isValidParameter = false;
        }
    }
    ~LSystemParameter() { }

    // Public functions
    bool isValid() { return isValidParameter; }

    // Data
    std::string name;
    float value;
    bool isValidParameter;
};


// Entity containing valid parameters used by LSystem classes
class LSystemParameters
{
public:
    // Constructors / Destructors
    LSystemParameters(std::vector<std::string> _parameterNames, std::vector<float> _parameterValues);
    LSystemParameters(std::vector<LSystemParameter> _parameters);
    ~LSystemParameters() { }

    // Setters / Getters
    void addParameter(LSystemParameter _parameter);
    void setParameters(std::vector<LSystemParameter> _parameters);
    void removeParameter(int _index);
    std::vector<LSystemParameter> getParameters() const { return parameters; }
    LSystemParameter getParameter(int _index) const {return parameters[_index]; }

private:
    std::vector<LSystemParameter> parameters;
};
