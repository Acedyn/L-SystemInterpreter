# pragma once
#include "l-SystemInterpreter/l-SystemAbstractModule.h"
#include "l-SystemInterpreter/l-SystemWord.h"
#include "l-SystemInterpreter/l-SystemExpression.h"

class LSystemRule
{
public:
    // Constructors / desctructors
    LSystemRule(
            LSystemAbstractModule _mainModule = LSystemAbstractModule(), 
            LSystemWord _derivativeWord = LSystemWord(), 
            LSystemExpression _mainCondition = LSystemExpression(), 
            LSystemParameters* _globalParameters = nullptr,
            float _probabilityFactor = -1.0f);
    ~LSystemRule() { }

    // Operators
    bool operator==(const LSystemRule& _other) const;
    bool operator!=(const LSystemRule& _other) const;
    friend std::ostream& operator<<(std::ostream& stream, const LSystemRule& _rule);

    // Main module
    void setMainModule(LSystemAbstractModule _mainModule);
    LSystemAbstractModule getMainModule() const { return mainModule; }
    void linkMainModule(LSystemConcreteModule* _mainModuleLink);

    // Derivative word
    void setDerivativeWord(class LSystemWord _derivativeWord);
    LSystemWord getDerivativeWord() const { return derivativeWord; }

    // Main condition
    void setMainCondition(LSystemExpression _mainCondition, LSystemParameters* _globalParameters = nullptr);
    LSystemExpression getMainCondition() const { return mainCondition; }

    // Condition modules
    void setLeftConditionModule(LSystemAbstractModule _leftConditionModule);
    LSystemAbstractModule getLeftConditionModule() const { return leftConditionModule; }
    void linkLeftModule(LSystemConcreteModule* _leftModuleLink);
    void setRightConditionModule(LSystemAbstractModule _rightConditionModule);
    LSystemAbstractModule getRightConditionModule() const { return rightConditionModule; }
    void linkRightModule(LSystemConcreteModule* _rightModuleLink);

    // Probability factor
    void setProbabilityFactor(float _probabilityFactor);
    float getProbabilityFactor() const { return probalitityFactor; }

    // GlobalParameters
    void setGlobalParameters(LSystemParameters* _globalParameters);

    // LinkedModule
    void linkModules(
            LSystemConcreteModule* _mainModuleLink, 
            LSystemConcreteModule* _leftModuleLink, 
            LSystemConcreteModule* _rightModuleLink);
    
private:
    // Private variables
    LSystemAbstractModule mainModule;
    LSystemWord derivativeWord;
    LSystemExpression mainCondition;
    LSystemAbstractModule leftConditionModule;
    LSystemAbstractModule rightConditionModule;
    float probalitityFactor = -1;
};
