#ifndef RSHELLHEADERS_H
#define RSHELLHEADERS_H

// Standard library imports
#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>

using namespace std;

int GLOBAL_EXIT_STATUS = 0; // When set to 1, stop program execution.
						    // This is used for proper handling of exit() -
							// wasn't sure how to handle it otherwise since
							// Tokens have no access to RShell, and we're using composite pattern.
bool GLOBAL_DEBUG = false;

class Token {
    public:
        Token() {}
        virtual ~Token() {}

        virtual int execute() = 0;
        virtual string stringify();

        virtual bool hasChildren();
		bool operator==(Token const &rhs) const; // TODO: Fix this weird header

        // Member variables
        vector<string> content;
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

class Subcommand : public Token {
    public:
        virtual ~Subcommand() {}
        Subcommand(vector<string> V);
        virtual string stringify();
        
        // TODO: Split test functionality into a separate function (a la splitonchar.h)
		bool test();

		virtual int execute();
};

class AndToken: public Token {
	public: 
		virtual ~AndToken() {}
		AndToken(vector<string> V);

        virtual string stringify();

		virtual int execute();
};

class OrToken: public Token {
	public: 
		OrToken(vector<string> V);
        virtual string stringify();

        virtual int execute();
};

class SemiToken: public Token {
	public:
        virtual ~SemiToken() {}
		SemiToken(vector<string> V);
        virtual string stringify();

		virtual int execute();
};

class TestToken : public Token {
	public:
		// Holds stuff from [   ]
		// So this->content = {"-e", "path/to/file"} or something similar.

        virtual ~TestToken() {}
		
		TestToken(vector<string> V);
		virtual string stringify();

		virtual int execute();
};

class StorageToken : public Token {
	public:
        virtual ~StorageToken() {}
		StorageToken(int s);
		virtual int execute();
		virtual string stringify();
};

class RShell {
    public:
		RShell();
		RShell(bool b);
		RShell(string filename);
		virtual ~RShell();

		void makeCommandDeque(string);
		int executeCommandDeque();

		void deconstructDeque();
		
		// Member variables
		deque<Token*> commandDeque;
		unordered_map <string, string> configData;
		bool DEBUG = false;

		deque<Token*> shuntingYardConstruct(string);
		int shuntingExecute(deque<Token*>);
		int findClose(const string&, int, char); 
};

class ParenthesisToken : public Token {
	public:
		// Acts like a decorator
		ParenthesisToken(deque<Token*> inside);
		virtual ~ParenthesisToken();
        virtual string stringify();

		virtual int execute();

		deque<Token*> interior;
};

class AppendOutToken : public Token {
	public: 
		AppendOutToken(vector<string> V);
        virtual ~AppendOutToken() {}
		virtual string stringify();
		virtual int execute();
};

class EmptyOutToken : public Token {
	public:
		EmptyOutToken(vector<string> V);
        virtual ~EmptyOutToken() {}
		virtual string stringify();
		virtual int execute();
};

class RedirectInputToken : public Token {
	public:
		RedirectInputToken(vector<string> V);
        virtual ~RedirectInputToken() {}
		virtual string stringify();
		virtual int execute();
};

class PipeToken : public Token {
	public:
		PipeToken(vector<string> V);
        virtual ~PipeToken() {}
		virtual string stringify();
		virtual int execute();
};


#endif
