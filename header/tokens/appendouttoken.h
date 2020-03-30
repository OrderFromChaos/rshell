#ifndef APPENDOUTTOKEN_H
#define APPENDOUTTOKEN_H

#include "token.h"

class AppendOutToken : public Token {
	public:
		AppendOutToken(std::vector<std::string> V);
        virtual ~AppendOutToken() {}

		virtual std::string stringify();
		virtual int execute();
};

#endif