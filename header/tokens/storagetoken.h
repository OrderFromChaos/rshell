#ifndef STORAGETOKEN_H
#define STORAGETOKEN_H

#include "token.h"

class StorageToken : public Token {
	public:
		StorageToken(int s);
		virtual ~StorageToken() {}

		virtual int execute(std::unordered_map<std::string, int>&);
		virtual std::string stringify();
};

#endif