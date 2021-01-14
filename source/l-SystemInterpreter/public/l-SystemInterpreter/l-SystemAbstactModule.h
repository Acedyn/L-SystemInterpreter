#pragma once

#include <iostream>
#include <vector>

class LSystemAbstactModule
{
public:
    // Constructors / Destructors
    LSystemAbstactModule(
            char _name = '\0', 
            std::vector<std::string> _parameterNames = {}, 
            class LSystemConcreteModule* _module = nullptr);
    LSystemAbstactModule(
            char _name = '\0', 
            std::string _parameterNames = "", 
            class LSystemConcreteModule* _module = nullptr);

    // Operators
    bool operator==(const LSystemAbstactModule& _other) const;
    bool operator!=(const LSystemAbstactModule& _other) const;
    friend std::ostream& operator<<(std::ostream& stream, const LSystemAbstactModule& _abstractModule);

    // Setters / Getters
    void setName(char _name) { name = _name; };
    char getName() const { return name; }
    void setParameterNames(std::vector<std::string> _parameterNames);
    void setParameterNames(std::string _parameterNames);
    void setModule(class LSystemConcreteModule* _module);
    std::vector<std::string> getParameters() const { return parameterNames; }
    bool getParameterName(float _parameterValue, std::string& _parameterName) const;
    std::vector<float> getParameterValues() const;
    bool getParameterValue(std::string _parameterName, float& _parameterValue) const;
    class LSystemConcreteModule* getModule() const { return module; }

private:
    // Private variables
    char name;
    std::vector<std::string> parameterNames;
    class LSystemConcreteModule* module = nullptr;
    
    // Make sure the quantity of parameters matches with the given module
    void updateParameterNames();
};