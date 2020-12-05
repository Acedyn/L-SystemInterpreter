#pragma once

class LSystemCondition
{
public:
    LSystemCondition(const char* _condition);
    ~LSystemCondition() { }

    bool matchModule();

    bool operator==(const LSystemCondition& _other) const;
    
    const char* condition;
};
