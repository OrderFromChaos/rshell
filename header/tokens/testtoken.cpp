#include "testtoken.h"
#include "../rshellutils.h"
#include "test_fxn.cpp"

TestToken::TestToken(std::vector<std::string> V) {
    this->content = V;
    this->isOperator = false;
}

std::string TestToken::stringify() { 
    return "TestToken: \"" + joinVector(this->content, ' ') + "\""; 
}

int TestToken::execute() {
    this->status = test(this->content, 0);
    return this->status;
}