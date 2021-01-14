#pragma once

#include <vector>
#include <string>
#include <iostream>

// Element composed of a name and parameters that can form words
class LSystemConcreteModule
{
public:
    // Constructors / desctructors
    LSystemConcreteModule(class LSystemParameters* _parameters = nullptr) : 
        name('\0'), 
        parameters(_parameters) { }
    LSystemConcreteModule(char _name, class LSystemParameters* _parameters = nullptr) : 
        name(_name), 
        parameters(_parameters) { }
    LSystemConcreteModule(char _name, std::vector<float> _parameterValues, class LSystemParameters* _parameters = nullptr);
    LSystemConcreteModule(char _name, std::vector<std::string> _parameterNames, class LSystemParameters* _parameters = nullptr);
    LSystemConcreteModule(char _name, std::string _parameterString, class LSystemParameters* _parameters = nullptr);
    ~LSystemConcreteModule() { }
    
    // Operators
    bool operator==(const LSystemConcreteModule& _other) const;
    bool operator!=(const LSystemConcreteModule& _other) const;
    friend std::ostream& operator<<(std::ostream& stream, const LSystemConcreteModule& _module);

    // Setters / getters
    void setName(char _name) { name = _name; };
    char getName() const { return name; }
    void addParameter(float _parameterValue);
    void addParameter(std::string _parameterName);
    void setParameters(std::vector<float> _parameterValues);
    void setParameters(std::vector<std::string> _parameterNames);
    void setParameters(std::string _parameterString);
    std::vector<float> getParameters() const { return parameterValues; }

private:
    // Private variables
    char name;
    std::vector<float> parameterValues;
    class LSystemParameters* parameters = nullptr;
};
