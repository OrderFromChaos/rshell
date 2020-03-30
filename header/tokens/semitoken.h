#ifndef SEMITOKEN_H
#define SEMITOKEN_H

#include "token.h"

class SemiToken: public Token {
	public:
        SemiToken(std::vector<std::string> V);
        virtual ~SemiToken() {}
		
        virtual std::string stringify();
		virtual int execute(std::unordered_map<std::string, int>&);
};

#endif