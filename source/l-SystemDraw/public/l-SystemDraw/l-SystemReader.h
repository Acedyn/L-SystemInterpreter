#pragma once

#include "l-SystemBase/l-SystemWord.h"
#include "l-SystemDraw/l-SystemTurtle.h"

namespace LSystem
{
	class Reader
	{
	public:
		// Constructors / desctructors
		Reader(LSystemWord _word);
		~Reader() { }

		// Getters
		LSystemWord getWord() { return word; }
		Turtle getTurtle() { return turtle; }
		DrawBuffer getDrawBuffer() { return buffer; }

		void parseWord();
		void interpretModule(LSystemConcreteModule& _module);

	private:
		LSystemWord word;
		std::vector<LSystemConcreteModule>::iterator wordIterator;
		Turtle turtle;
		DrawBuffer buffer;
	};
}