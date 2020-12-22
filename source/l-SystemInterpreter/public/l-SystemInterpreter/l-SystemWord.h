#pragma once
#include "l-SystemInterpreter/l-SystemModule.h"

#include <string>
#include <vector>

// Iterator for LSystemWord
class LSystemWordIterator
{
public:
    // Constructors / desctructors
    LSystemWordIterator(LSystemModule* _lSystemModule) : lSystemModule(_lSystemModule) { }
    
    // Operators
    LSystemWordIterator& operator++()
    {
        lSystemModule++;
        return *this;
    }
    LSystemWordIterator operator++(int)
    {
        LSystemWordIterator _iterator = *this;
        lSystemModule++;
        return _iterator;
    }
    LSystemWordIterator& operator--()
    {
        lSystemModule--;
        return *this;
    }
    LSystemWordIterator operator--(int)
    {
        LSystemWordIterator _iterator = *this;
        lSystemModule--;
        return _iterator;
    }
    bool operator==(LSystemWordIterator _lSystemWordIterator)
    {
        return lSystemModule == *_lSystemWordIterator;
    }
    bool operator!=(LSystemWordIterator _lSystemWordIterator)
    {
        return lSystemModule != *_lSystemWordIterator;
    }
    LSystemModule* operator*()
    {
        return lSystemModule;
    }
    


private:
    LSystemModule* lSystemModule; 
};

// Array of elements representing the result or a step of an l-system
class LSystemWord
{
public:
    // Enums
    enum wordComponent
    {
        MODULE,
        COMMAND
    };

    // Aliases
    using Iterator = LSystemWordIterator;

    // Constructors / desctructors
    LSystemWord() {  }
    LSystemWord(std::string _word);
    LSystemWord(LSystemWord& _lSystemWord);
    ~LSystemWord() {  }

    // Getters / setters / append
    void appendModule(LSystemModule _module);
    void appendWord(LSystemWord _word);
    std::vector<LSystemModule> getModules() { return modules; }

    // Iterator
    Iterator begin() { return Iterator(&(modules[0])); }
    Iterator end() 
    { 
        LSystemModule* lastModule = &modules[modules.size()-1];
        return Iterator(++lastModule); 
    }

private:
    // Private functions
    void parseWord(std::string _word);

    // Private variables
    std::vector<LSystemModule> modules;
};
