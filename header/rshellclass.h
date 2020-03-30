#ifndef RSHELLHEADER_H
#define RSHELLHEADER_H

#include "tokens/token.h"

#include <deque>
#include <unordered_map>

// TODO: Put this in a namespace.
namespace rshellstatus {
	int GLOBAL_EXIT_STATUS = 0; // When set to 1, stop program execution.
								// This is used for proper handling of exit().
	bool GLOBAL_DEBUG = false;
}

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

		// Member variables
		std::deque<Token*> commandDeque;
		std::unordered_map <std::string, std::string> configData;
		bool DEBUG = false;
};

#endif