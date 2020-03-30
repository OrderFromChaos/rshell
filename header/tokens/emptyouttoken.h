#ifndef EMPTYOUTTOKEN_H
#define EMPTYOUTTOKEN_H

#include "token.h"

class EmptyOutToken : public Token {
	public:
		EmptyOutToken(std::vector<std::string> V);
        virtual ~EmptyOutToken() {}
        
		virtual std::string stringify();
		virtual int execute(std::unordered_map<std::string, int>&);
};

#endif