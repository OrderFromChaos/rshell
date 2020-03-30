#ifndef REDIRECTINPUTTOKEN_H
#define REDIRECTINPUTTOKEN_H

#include "token.h"

class RedirectInputToken : public Token {
	public:
		RedirectInputToken(std::vector<std::string> V);
        virtual ~RedirectInputToken() {}
        
		virtual std::string stringify();
		virtual int execute(std::unordered_map<std::string, int>&);
};

#endif