#pragma once

#include "l-SystemParameter.h"

#include <vector>
#include <string>

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
