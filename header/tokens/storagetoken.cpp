#include "storagetoken.h"

using namespace std;

StorageToken::StorageToken(int s) {
    this->isOperator = false;
    this->status = s;
}

int StorageToken::execute(unordered_map<string, int>& statusMap) {
    return this->status;
}

string StorageToken::stringify() {
    return "StorageToken: " + to_string(status);
}