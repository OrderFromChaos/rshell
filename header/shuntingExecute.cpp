#ifndef SHUNTINGEXECUTE_H
#define SHUNTINGEXECUTE_H

#include "rshellclass.h"
#include "tokens/storagetoken.h"

#include <deque>
#include <stack>
#include <vector>

int RShell::shuntingExecute(std::deque<Token*> V) {
    std::stack<Token*> toExecute;
    std::unordered_map<std::string, int> statusMap;

    if (V.size() == 0) {
        return 0;
    } else if (V.size() == 1) {
        statusMap = this->prepareStatusMap();
        int retVal = V[0]->execute(statusMap);
        writeStatusMap(statusMap);
        return retVal;
    } else {
        for (Token* t : V) {
            statusMap = this->prepareStatusMap();

            if (t->isOperator == false) {
                toExecute.push(t);
            } else {
                Token* r = toExecute.top();
                toExecute.pop();
                Token* l = toExecute.top();
                toExecute.pop();

                t->leftChild = l;
                t->rightChild = r;

                t->execute(statusMap);
                this->writeStatusMap(statusMap);

                // Clean up storageToken pointers
                std::vector<Token*> pointers = {l, r, t};
                for (Token* currToken : pointers) {
                    StorageToken* sptr = dynamic_cast<StorageToken*>(currToken);
                    if (sptr != nullptr) {
                        delete sptr;
                    }
                }

                // if statusMap["EXIT_STATUS"] is reached, exit execution
                if (statusMap["EXIT_STATUS"] == 1) {
                    // Clean up stack
                    while (!toExecute.empty()) {
                        Token* stop = toExecute.top();
                        toExecute.pop();
                        delete stop;
                    }
                    return t->status;
                }

                // Need to re-add execution value
                Token* s = new StorageToken(t->status);
                toExecute.push(s);
            }
        }
        return V[V.size() - 1]->status;
    }
}

#endif
