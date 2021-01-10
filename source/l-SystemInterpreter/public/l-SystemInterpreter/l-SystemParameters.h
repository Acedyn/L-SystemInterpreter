#pragma once

#include <vector>
#include <string>
#include <ctype.h>

// Data structure containing a name and a value of a parameter for an l-system
struct LSystemParameter
{
    // Constructors / Destructors
    LSystemParameter() { }
    LSystemParameter(std::string _name, float _value)
    {
        // Test if the name of the parameter does contain only letters
        for(char _character : name)
        {
            if(!isalpha(_character)) 
            { 
                isValidParameter = false;
                return;
            }
        }
        
        name = _name;
        value = _value;
        isValidParameter = true;
    }
    ~LSystemParameter() { }

    // Operators
    bool operator==(const LSystemParameter& _other) const { return name == _other.name && value == _other.value; }
    bool operator!=(const LSystemParameter& _other) const { return name != _other.name || value != _other.value; }

    // Public functions
    bool isValid() { return isValidParameter; }

    // Data
    std::string name;
    float value;
    bool isValidParameter = false;
};


// Entity containing valid parameters used by LSystem classes
class LSystemParameters
{
public:
    // Constructors / Destructors
    LSystemParameters() { }
    LSystemParameters(std::vector<std::string> _parameterNames, std::vector<float> _parameterValues);
    LSystemParameters(std::vector<LSystemParameter> _parameters);
    ~LSystemParameters() { }

    // Operators
    bool operator==(const LSystemParameters& _other) const;
    bool operator!=(const LSystemParameters& _other) const;

    // Setters / Getters
    void addParameter(LSystemParameter _parameter);
    void setParameters(std::vector<LSystemParameter> _parameters);
    void setNames(std::vector<std::string> _parameterNames);
    void setValues(std::vector<float> _parameterValues);
    void removeParameter(int _index);
    std::vector<LSystemParameter> getParameters() const { return parameters; }
    LSystemParameter getParameter(int _index) const;

    // Iterator
    std::vector<LSystemParameter>::iterator begin() { return parameters.begin(); }
    std::vector<LSystemParameter>::iterator end() { return parameters.end(); }

private:
    std::vector<LSystemParameter> parameters;
};
