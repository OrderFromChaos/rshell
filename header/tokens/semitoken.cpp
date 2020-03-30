#include "semitoken.h"
#include "../rshellutils.h"

SemiToken::SemiToken(std::vector<std::string> V) {
    this->content = V; 
    this->isOperator = true;
}

std::string SemiToken::stringify() { 
    return "SemiToken: \"" + joinVector(this->content, ' ') + "\""; 
}

int SemiToken::execute(std::unordered_map<std::string, int>& statusMap) { 
    leftChild->execute(statusMap);
    this->status = rightChild->execute(statusMap);
    return this->status;
}