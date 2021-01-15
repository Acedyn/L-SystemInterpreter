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
        globalParameters(_parameters) { }
    LSystemConcreteModule(char _name, class LSystemParameters* _parameters = nullptr) : 
        name(_name), 
        globalParameters(_parameters) { }
    LSystemConcreteModule(char _name, std::vector<float> _parameterValues, class LSystemParameters* _parameters = nullptr);
    LSystemConcreteModule(char _name, std::string _parameterString, class LSystemParameters* _parameters = nullptr);
    ~LSystemConcreteModule() { }
    
    // Operators
    bool operator==(const LSystemConcreteModule& _other) const;
    bool operator!=(const LSystemConcreteModule& _other) const;
    bool operator==(const class LSystemAbstractModule& _other) const;
    bool operator!=(const class LSystemAbstractModule& _other) const;
    friend std::ostream& operator<<(std::ostream& stream, const LSystemConcreteModule& _module);

    // Module's name
    void setName(char _name) { name = _name; };
    char getName() const { return name; }
    // Parameter names
    void setParameterNames(std::vector<std::string> _parameterNames);
    void setParameterNames(std::string _parameterNames);
    std::vector<std::string> getParameterNames() const;
    bool getParameterName(float _parameterValue, std::string& _parameterName) const;
    void addParameterName(std::string _parameterName);
    // Parameter values
    void setParameterValues(std::vector<float> _parameterValues);
    void setParameterValues(std::string _parameterValues);
    std::vector<float> getParameterValues() const { return parameterValues; }
    bool getParameterValue(std::string _parameterName, float& _parameterValue) const;
    void addParameterValue(float _parameterValue);
    void addParameterValue(std::string _parameterValue);
    // Linked module
    bool setLinkedModule(class LSystemAbstractModule* _module);
    class LSystemAbstractModule* getLinkedModule() const { return linkedModule; }
    bool isLinked() const { return linkedModule != nullptr; }


private:
    // Private variables
    char name;
    std::vector<float> parameterValues;
    class LSystemParameters* globalParameters = nullptr;
    class LSystemAbstractModule* linkedModule = nullptr;

    // Matches the parameters with the linked module
    void matchParameters();
};
