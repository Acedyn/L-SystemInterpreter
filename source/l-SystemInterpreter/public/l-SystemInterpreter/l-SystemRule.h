# pragma once

class LSystemRule
{
public:
    // Constructors / desctructors
    LSystemRule(class LSystemModule* _mainModule);
    LSystemRule(class LSystemModule* _mainModule, class LSystemCondition* _mainCondition);
    LSystemRule(class LSystemModule* _mainModule, float _probabilityFactor);
    LSystemRule(class LSystemModule* _mainModule, class LSystemCondition* _mainCondition, float _probabilityFactor);
    ~LSystemRule() { }

    // Setters / getters
    void setMainCondition(class LSystemCondition* _mainCondition);
    void setProbabilityFactor(float _probabilityFactor);
    void setLeftConditionModule(class LSystemModule* _leftConditionModule);
    void setRightConditionModule(class LSystemModule* _rightConditionModule);
    
private:
    // Private variables
    class LSystemModule* mainModule;
    class LSystemCondition* mainCondition;
    class LSystemModule* leftConditionModule;
    class LSystemModule* rightConditionModule;
    float probalitityFactor = -1;
};
