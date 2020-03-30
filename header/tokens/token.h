#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <vector>

class Token {
    public:
        Token() {}

        // Polymorphic functions
        virtual ~Token() {}
        virtual int execute() = 0;
        virtual std::string stringify();

        // Member variables
        std::vector<std::string> content;
	    bool isOperator;
        Token* leftChild = nullptr;
        Token* rightChild = nullptr;
        int status = -2; // Current exit status of Token.

		// Meanings of status:
		// -3: Subcommand segfaulted when we tried to run it with execvp
		// -2: Token has not run
		// 47: Subcommand not found
		// 0: Subcommand ran successfully
		// anything else: Subcommand failed
};

#endif