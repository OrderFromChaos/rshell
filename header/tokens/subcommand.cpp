#include "subcommand.h"
#include "../convertVectorToCharArray.h"
#include "../executeCharArray.h"
#include "../rshellclass.h"
#include "../rshellutils.h"
#include "test_fxn.cpp"

extern int GLOBAL_EXIT_STATUS;
extern bool GLOBAL_DEBUG;

Subcommand::Subcommand(std::vector<std::string> V) {
    this->content = V;
    this->isOperator = false;
}

std::string Subcommand::stringify() {
    return "Subcommand: \"" + joinVector(this->content, ' ') + "\"";
}

int Subcommand::execute() {
    if (GLOBAL_EXIT_STATUS == 1) {
        // Do nothing
        return -2;
    } else if (content[0] == "exit") {
        GLOBAL_EXIT_STATUS = 1;
        this->status = 0;
        return this->status;
    } else if (content[0] == "test") {
        if (test(this->content, 1) == true) {
            std::cout << "(True)" << std::endl;
            this->status = 0;
        } else {
            std::cout << "(False)" << std::endl;
            this->status = 1;
        }
        return this->status;
    } else {
        char** chararr = convertVectorToCharArray(content);

        this->status = executeCharArray(chararr);

        if (this->status == 47) {
            std::cout << "RSHELL: Command not found! " 
                      << '\"' 
                      << this->content[0]
                      << '\"' 
                      << std::endl;
        }

        for (int i = 0; i < content.size() + 1; i++) {
            delete[] chararr[i];
        }
        delete[] chararr;

        return status;
    }
}