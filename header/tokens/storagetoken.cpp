#include "storagetoken.h"

StorageToken::StorageToken(int s) {
    this->isOperator = false;
    this->status = s;
}

int StorageToken::execute() {
    return this->status;
}

std::string StorageToken::stringify() {
    return "StorageToken: " + std::to_string(status);
}