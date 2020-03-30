#ifndef SUBCOMMAND_H
#define SUBCOMMAND_H

#include "token.h"

class Subcommand : public Token {
    public:
        Subcommand(std::vector<std::string> V);
        virtual ~Subcommand() {}
        
        virtual std::string stringify();
        virtual int execute(std::unordered_map<std::string, int>&);
};

#endif