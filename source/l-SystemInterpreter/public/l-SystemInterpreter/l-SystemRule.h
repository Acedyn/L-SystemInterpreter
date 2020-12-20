# pragma once

class LSystemRule
{
public:
    // Constructors / desctructors
    LSystemRule(class LSystemModule* _mainModule, class LSystemWord* _derivativeWord = nullptr, class LSystemCondition* _mainCondition = nullptr, float _probabilityFactor = -1.0f);
    ~LSystemRule() { }

    // Setters / getters
    void setMainCondition(class LSystemCondition* _mainCondition);
    void setProbabilityFactor(float _probabilityFactor);
    void setLeftConditionModule(class LSystemModule* _leftConditionModule);
    void setRightConditionModule(class LSystemModule* _rightConditionModule);
    void setDerivativeWord(class LSystemWord* _derivativeWord);
    
private:
    // Private variables
    class LSystemModule* mainModule = nullptr;
    class LSystemCondition* mainCondition = nullptr;
    class LSystemModule* leftConditionModule = nullptr;
    class LSystemModule* rightConditionModule = nullptr;
    class LSystemWord* derivativeWord = nullptr;
    float probalitityFactor = -1;
};
