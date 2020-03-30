#include "rshellclass.h"

using namespace std;

RShell::RShell(bool b) { 
    this->DEBUG = b;
}

RShell::RShell(string filename) {
    // TODO: Import config file a la .rshellrc
}

RShell::~RShell() {
    deconstructDeque();
}

void RShell::deconstructDeque() {
    if (this->commandDeque.size() > 0) {
        for (Token* t : this->commandDeque) {
            delete t;
        }
    }
}

void RShell::makeCommandDeque(string userInput) {
    deque<Token*> result_deque = shuntingYardConstruct(userInput);
    this->commandDeque = result_deque;

    if (this->DEBUG) {
        // Print out commandDeque
        for (Token* t : this->commandDeque) {
            cout << t->stringify() << endl;
        }
    }
}

int RShell::executeCommandDeque() {
    if (DEBUG) {
        cout << "EXECUTING:" << endl;
        cout << "{" << endl;
    }

    int execute_result = shuntingExecute(this->commandDeque);

    if (DEBUG) {
        cout << "}" << endl;
        cout << "Final execution status:" << endl;
        for (Token* t : this->commandDeque) {
            cout << t->status << " ";
        }
        cout << endl;
    }

    // Clean up memory
    deconstructDeque();
    this->commandDeque.clear();

    return execute_result;
}

unordered_map<string, int> RShell::prepareStatusMap() {
    unordered_map<string, int> retmap;
    
    retmap["DEBUG"] = this->DEBUG;
    retmap["EXIT_STATUS"] = this->EXIT_STATUS;
    // TODO: Take stuff from configData

    return retmap;
}

void RShell::writeStatusMap(std::unordered_map<std::string, int>& statusMap) {
    this->DEBUG = statusMap["DEBUG"];
    this->EXIT_STATUS = statusMap["EXIT_STATUS"];
}

// Defined in separate files:
//      deque<Token*> shuntingYardConstruct(string);
//      int findClose(const string&, int, char); 
//      int shuntingExecute(deque<Token*>);