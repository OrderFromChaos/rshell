#include "andtoken.h"
#include "../rshellutils.h"

AndToken::AndToken(std::vector<std::string> V) {
    this->content = V;
    this->isOperator = true;
}

std::string AndToken::stringify() {
    return "AndToken: \"" + joinVector(this->content, ' ') + '\"';
}

int AndToken::execute(std::unordered_map<std::string, int>& statusMap) {
    int statusLeft, statusRight = -2;
    statusLeft = leftChild->execute(statusMap);

    if (statusMap["EXIT_STATUS"] == 1) {
        return 0;
    }

    if (statusLeft == 0) { 
        // "echo a && ..."
        statusRight = rightChild->execute(statusMap);
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