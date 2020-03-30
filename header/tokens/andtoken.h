#ifndef ANDTOKEN_H
#define ANDTOKEN_H

#include "token.h"

class AndToken: public Token {
	public:
        AndToken(std::vector<std::string> V);
		virtual ~AndToken() {}

        virtual std::string stringify();
		virtual int execute();
};

#endif