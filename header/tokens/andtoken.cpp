#include "andtoken.h"
#include "../rshellutils.h"

AndToken::AndToken(std::vector<std::string> V) {
    this->content = V;
    this->isOperator = true;
}

std::string AndToken::stringify() {
    return "AndToken: \"" + joinVector(this->content, ' ') + '\"';
}

int AndToken::execute() {
    int statusLeft, statusRight = -2;
    statusLeft = leftChild->execute();

    if (statusLeft == 0) { 
        // "echo a && ..."
        statusRight = rightChild->execute();
        if (statusRight == 0) {
            // "echo a && echo b"
            this->status = 0;
        } else {
            // "echo a && false"
            this->status = 1;
        }
    } else {
        // "false && ..."
        this->status = 1;
    }

    return this->status;
}