#pragma once

#include <vector>
#include <string>
#include <iostream>

// Element composed of a name and parameters that can form words
class LSystemModule
{
public:
    // Constructors / desctructors
    LSystemModule() : name('\0') {  }
    LSystemModule(char _name) : name(_name) {  }
    LSystemModule(char _name, std::vector<float> _parameterValues, class LSystemParameters* _parameters = nullptr);
    LSystemModule(char _name, std::vector<std::string> _parameterNames, class LSystemParameters* _parameters = nullptr);
    LSystemModule(char _name, std::string _parameterString, class LSystemParameters* _parameters = nullptr);
    ~LSystemModule() { }
    
    // Operators
    bool operator==(const LSystemModule& _other) const;
    bool operator!=(const LSystemModule& _other) const;
    friend std::ostream& operator<<(std::ostream& stream, const LSystemModule& module);

    // Setters / getters
    void addParameter(float _parameterValue);
    void addParameter(std::string _parameterName);
    void setParameters(std::vector<float> _parameterValues);
    void setParameters(std::vector<std::string> _parameterNames);
    void setParameters(std::string _parameterString);
    void setName(char _name) { name = _name; }
    std::vector<float> getParameters() const { return parameterValues; }
    char getName() const { return name; }

private:
    // Private variables
    char name;
    std::vector<float> parameterValues;
    class LSystemParameters* parameters = nullptr;
};
