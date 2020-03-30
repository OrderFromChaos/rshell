#ifndef ORTOKEN_H
#define ORTOKEN_H

#include "token.h"

class OrToken: public Token {
	public: 
		OrToken(std::vector<std::string> V);
        virtual ~OrToken() {}

        virtual std::string stringify();
        virtual int execute();
};

#endif