#ifndef PIPETOKEN_H
#define PIPETOKEN_H

#include "token.h"

class PipeToken : public Token {
	public:
		PipeToken(std::vector<std::string> V);
        virtual ~PipeToken() {}
        
		virtual std::string stringify();
		virtual int execute(std::unordered_map<std::string, int>&);
};

#endif