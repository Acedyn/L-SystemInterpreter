#pragma once

#include <vector>
#include <string>

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
