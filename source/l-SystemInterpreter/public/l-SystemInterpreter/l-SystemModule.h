#pragma once

#include <vector>

class LSystemModule
{
public:
    LSystemModule(char _name, std::vector<char> _formalParameters);
    
    bool testCondition();
    bool testSideCondition(LSystemModule sideModule);

private:
    char name;
    std::vector<char> formalParameters;
    
};
