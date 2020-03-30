#ifndef TESTTOKEN_H
#define TESTTOKEN_H

#include "token.h"

class TestToken : public Token {
	public:
		// Holds stuff from [   ]
		// So this->content = {"-e", "path/to/file"} or something similar.
        TestToken(std::vector<std::string> V);
        virtual ~TestToken() {}
		
		virtual std::string stringify();
		virtual int execute(std::unordered_map<std::string, int>&);
};

#endif