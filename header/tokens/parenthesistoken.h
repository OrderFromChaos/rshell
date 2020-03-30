#ifndef PARENTHESISTOKEN_H
#define PARENTHESISTOKEN_H

#include "token.h"

#include <deque>

class ParenthesisToken : public Token {
	public:
		// Acts like a decorator
		ParenthesisToken(std::deque<Token*> inside);
		virtual ~ParenthesisToken();
        
        virtual std::string stringify();
		virtual int execute(std::unordered_map<std::string, int>&);

        // Additional member variable
		std::deque<Token*> interior;
};

#endif