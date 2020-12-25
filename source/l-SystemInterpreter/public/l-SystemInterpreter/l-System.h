#pragma once

#include <vector>

// l-system composed of an axiom and a set of rules used to output a word describing branching structure
class LSystem
{
public:
    // Constructors / desctructors
    LSystem(class LSystemWord* _axiom);
    LSystem(class LSystemWord* axiom, std::vector<class LSystemRule*> _rules);
    ~LSystem() {  }

    // Setters / getters
    void appendRule(class LSystemRule* _rule);
    class LSystemWord* getAxiom() { return axiom; }
    class LSystemWord* getOutputWord() { return outputWord; }

    // Public functions
    void iterate();
    
    // Public variables
    int seed = 0;

private:
    class LSystemWord* axiom;
    std::vector<class LSystemRule*> rules;
    class LSystemWord* outputWord;
};
