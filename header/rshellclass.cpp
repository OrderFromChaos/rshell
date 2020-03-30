#include "rshellclass.h"

extern int GLOBAL_EXIT_STATUS;
extern bool GLOBAL_DEBUG;

RShell::RShell(bool b) { 
    this->DEBUG = b;
    GLOBAL_DEBUG = b;
}

RShell::RShell(std::string filename) {
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

void RShell::makeCommandDeque(std::string userInput) {
    std::deque<Token*> result_deque = shuntingYardConstruct(userInput);
    this->commandDeque = result_deque;

    if (this->DEBUG) {
        // Print out commandDeque
        for (Token* t : this->commandDeque) {
            std::cout << t->stringify() << std::endl;
        }
    }
}

int RShell::executeCommandDeque() {
    if (DEBUG) {
        std::cout << "EXECUTING:" << std::endl;
        std::cout << "{" << std::endl;
    }

    int execute_result = shuntingExecute(this->commandDeque);

    if (DEBUG) {
        std::cout << "}" << std::endl;

        std::cout << "Final execution status:" << std::endl;
        for (Token* t : this->commandDeque) {
            std::cout << t->status << " ";
        }
        std::cout << std::endl;
    }

    // Clean up memory
    deconstructDeque();
    this->commandDeque.clear();

    return execute_result;
}

// Defined in separate files:
//      std::deque<Token*> shuntingYardConstruct(std::string);
//      int findClose(const std::string&, int, char); 
//      int shuntingExecute(std::deque<Token*>);