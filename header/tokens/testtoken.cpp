#include "testtoken.h"
#include "../rshellutils.h"
#include "test_fxn.h"

TestToken::TestToken(std::vector<std::string> V) {
    this->content = V;
    this->isOperator = false;
}

std::string TestToken::stringify() { 
    return "TestToken: \"" + joinVector(this->content, ' ') + "\""; 
}

int TestToken::execute(std::unordered_map<std::string, int>& statusMap) {
    this->status = test(this->content, 0);
    return this->status;
}