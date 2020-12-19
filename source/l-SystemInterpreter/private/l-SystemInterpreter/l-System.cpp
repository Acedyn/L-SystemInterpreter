#include "l-SystemInterpreter/l-System.h"
#include "l-SystemInterpreter/l-SystemWord.h"
#include "l-SystemInterpreter/l-SystemRule.h"


////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystem::LSystem(LSystemWord* _axiom) : axiom(_axiom) {  }

LSystem::LSystem(LSystemWord* _axiom, std::vector<LSystemRule*> _rules) : 
    axiom(_axiom),
    rules(_rules) {  }


////////////////////////////////////////
// Setters / getters
////////////////////////////////////////
void LSystem::appendRule(LSystemRule* _rule)
{
    rules.emplace_back(_rule);
}


////////////////////////////////////////
// Public functions
////////////////////////////////////////
void LSystem::iterate()
{

}
