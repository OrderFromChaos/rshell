#ifndef RSHELLHEADER_H
#define RSHELLHEADER_H

#include "tokens/token.h"

#include <deque>
#include <unordered_map>

// TODO: Put this in a namespace.

class RShell {
    public:
		// Constructors
		RShell();
		RShell(bool b);
		RShell(std::string filename);

		// Automatic memory cleanup on deconstruction
		virtual ~RShell();
		void deconstructDeque();

		// Parsing
		void makeCommandDeque(std::string);
		std::deque<Token*> shuntingYardConstruct(std::string);
		int findClose(const std::string&, int, char); 

		// Execution
		int executeCommandDeque();
		int shuntingExecute(std::deque<Token*>);
		std::unordered_map<std::string, int> prepareStatusMap();

		// Member variables
		std::deque<Token*> commandDeque;
		std::unordered_map <std::string, std::string> configData;

		bool DEBUG = false;
		bool EXIT_STATUS = false;
};

#endif