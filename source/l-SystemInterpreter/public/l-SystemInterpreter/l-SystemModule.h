#pragma once

#include <vector>
#include <string>
#include <iostream>

class LSystemModule
{
public:
    // Constructors / desctructors
    LSystemModule() : name('\0') {  }
    LSystemModule(char _name) : name(_name) {  }
    LSystemModule(char _name, std::vector<char> _formalParameters);
    LSystemModule(char _name, std::string _formalParameters);
    LSystemModule(char _name, std::vector<float> _parameterValues);
    ~LSystemModule() { }
    
    // Operators
    bool operator==(const LSystemModule& _other) const;
    bool operator!=(const LSystemModule& _other) const;

    // Setters / getters
    void setFormalParameters(std::vector<char> _formalParameters);
    void setParametersValues(std::vector<float> _parameterValues);
    std::vector<char> getFormalParameters() const { return formalParameters; }
    std::vector<float> getParameterValues() const { return parameterValues; }
    char getName() const { return name; }

private:
    // Private variables
    char name;
    std::vector<char> formalParameters;
    std::vector<float> parameterValues;
};

