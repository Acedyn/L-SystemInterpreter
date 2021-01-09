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
    LSystemModule(char _name, std::vector<std::string> _parameters);
    LSystemModule(char _name, std::string _parameters);
    ~LSystemModule() { }
    
    // Operators
    bool operator==(const LSystemModule& _other) const;
    bool operator!=(const LSystemModule& _other) const;
    friend std::ostream& operator<<(std::ostream& stream, const LSystemModule& module);

    // Setters / getters
    void addParameter(std::string _parameter);
    void setParameters(std::vector<std::string> _parameters);
    void setName(char _name) { name = _name; }
    std::vector<std::string> getParameters() const { return parameters; }
    char getName() const { return name; }

private:
    // Private variables
    char name;
    std::vector<std::string> parameters;
};
