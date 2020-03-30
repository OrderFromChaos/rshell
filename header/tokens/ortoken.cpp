#include "ortoken.h"
#include "../rshellutils.h"

OrToken::OrToken(std::vector<std::string> V) {
    this->content = V;
    this->isOperator = true;
}

std::string OrToken::stringify() {
    return "OrToken: \"" + joinVector(this->content, ' ') + '\"';
}

int OrToken::execute() {
    int statusLeft, statusRight = -2;
    statusLeft = leftChild->execute();

    if (statusLeft != 0) {
        // "false || ..."
        statusRight = rightChild->execute();
        if (statusRight == 0) {
            // "false || echo b"
            this->status = 0;
        } else {
            // "false || false"
            this->status = 1;
        }
    } else {
        // "echo a || ..."
        this->status = 0;
    }

    return this->status;
}