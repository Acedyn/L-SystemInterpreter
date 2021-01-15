#pragma once

#include <iostream>
#include <vector>

class LSystemAbstractModule
{
public:
    // Constructors / Destructors
    LSystemAbstractModule(
            char _name = '\0', 
            std::vector<std::string> _parameterNames = {}, 
            class LSystemConcreteModule* _module = nullptr);
    LSystemAbstractModule(
            char _name = '\0', 
            std::string _parameterNames = "", 
            class LSystemConcreteModule* _module = nullptr);

    // Operators
    bool operator==(const LSystemAbstractModule& _other) const;
    bool operator!=(const LSystemAbstractModule& _other) const;
    bool operator==(const class LSystemConcreteModule& _other) const;
    bool operator!=(const class LSystemConcreteModule& _other) const;
    friend std::ostream& operator<<(std::ostream& stream, const LSystemAbstractModule& _abstractModule);

    // Module'name
    void setName(char _name) { name = _name; };
    char getName() const { return name; }
    // Parameter names
    void setParameterNames(std::vector<std::string> _parameterNames);
    void setParameterNames(std::string _parameterNames);
    std::vector<std::string> getParameterNames() const { return parameterNames; }
    bool getParameterName(float _parameterValue, std::string& _parameterName) const;
    void addParameterName(std::string _parameterName);
    // Parameter values
    void setParameterValues(std::vector<float> _parameterValues);
    void setParameterValues(std::string _parameterValues);
    std::vector<float> getParameterValues() const;
    bool getParameterValue(std::string _parameterName, float& _parameterValue) const;
    void addParameterValue(float _parameterValue);
    // Linked module
    bool setLinkedModule(class LSystemConcreteModule* _module);
    class LSystemConcreteModule* getLinkedModule() const { return linkedModule; }
    bool isLinked() const { return linkedModule != nullptr; }

private:
    // Private variables
    char name;
    std::vector<std::string> parameterNames;
    class LSystemConcreteModule* linkedModule = nullptr;
    
    // Matches the parameters with the linked module
    void matchParameters();
};
