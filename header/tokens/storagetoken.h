#ifndef STORAGETOKEN_H
#define STORAGETOKEN_H

#include "token.h"

class StorageToken : public Token {
	public:
        virtual ~StorageToken() {}
		StorageToken(int s);
		virtual int execute();
		virtual std::string stringify();
};

#endif