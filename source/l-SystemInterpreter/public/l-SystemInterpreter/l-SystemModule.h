#pragma once

#include <string>
#include <vector>

class LSystemModule
{
public:
    LSystemModule(char _name, const char* _formalParameters);
    ~LSystemModule() {  }
    
    bool matchCondition(class LSystemCondition _lSystemCondition);
    bool operator==(const LSystemModule& _other) const;

    char name;
    const char* formalParameters;
};
