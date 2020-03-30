#include "parenthesistoken.h"
#include "../rshellutils.h"
#include "../rshellclass.h"
#include "../shuntingExecute.cpp"

extern int GLOBAL_EXIT_STATUS;
extern bool GLOBAL_DEBUG;

ParenthesisToken::ParenthesisToken(std::deque<Token*> inside) {
    this->interior = inside;
    this->isOperator = false;
}

ParenthesisToken::~ParenthesisToken() {
    if (this->interior.size() > 0) {
        for (Token* t : this->interior) {
            delete t;
        }
        interior.clear();
    }
}

std::string ParenthesisToken::stringify() { 
    std::vector<std::string> outputV;

    outputV.push_back("ParenthesisToken:");
    std::string indent(4, ' ');

    for (Token* t : interior) {
        outputV.push_back(indent + t->stringify());
    }
    outputV.push_back("}");

    return joinVector(outputV, "\n");
}

int ParenthesisToken::execute() {
    RShell temp = RShell(GLOBAL_DEBUG);
    this->status = temp.shuntingExecute(interior);
    return status;
}