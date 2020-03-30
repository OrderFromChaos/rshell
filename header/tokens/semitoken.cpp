#include "semitoken.h"
#include "../rshellutils.h"

SemiToken::SemiToken(std::vector<std::string> V) {
    this->content = V; 
    this->isOperator = true;
}

std::string SemiToken::stringify() { 
    return "SemiToken: \"" + joinVector(this->content, ' ') + "\""; 
}

int SemiToken::execute() { 
    leftChild->execute();
    this->status = rightChild->execute();
    return this->status;
}