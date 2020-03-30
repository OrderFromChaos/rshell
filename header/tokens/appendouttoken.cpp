#include "appendouttoken.h"
#include "../rshellutils.h"

#include <cstring>
#include <fstream>

AppendOutToken::AppendOutToken(std::vector<std::string> V) {
    this->content = V;
    this->isOperator = true;
}

std::string AppendOutToken::stringify() {
    return "AppendOutToken \"" + joinVector(this->content, ' ') + "\"";
}

int AppendOutToken::execute() {
    // Assign the values of the leftChild's content as a completed commmand,
    // Store value into a cstring, and take in the filename from the
    // rightChild's content.
    std::string fileName = rightChild->content[0];
    const int PATH_MX = 1000;
    std::string commandOutput;

    // Take in command from leftChild.
    std::string command = joinVector(leftChild->content, ' ');

    // Create buffer to store value of comamnd.
    char buffer2[PATH_MX];
    std::memset(buffer2, '\0', PATH_MX);

    // Use popen to invoke the shell and get an fstream for the command.
    FILE* in_pipe = popen(command.c_str(), "r");

    // Store the result of the file into a string.
    if (!in_pipe) {
        std::cout << "Command not found:" << std::endl;
        std::cout << "   ";
        printVector(leftChild->content, "; ");
        return 47;
    } else {
        while (fgets(buffer2, PATH_MX, in_pipe) !=
               NULL) {  // Reads lines from file pipe
            commandOutput.append(buffer2);
        }
        pclose(in_pipe);

        std::ofstream ofs;

        if (this->content[0] == ">>") {
            ofs.open(fileName.c_str(), std::ofstream::out | std::ofstream::app);
            if (!ofs.is_open()) {
                std::cout << "Unable to open file; may already be open" << std::endl;
                this->status = 1;
            } else {
                ofs << commandOutput;
                ofs.close();
                this->status = 0;
            }
        } else {
            std::cout << "Token incorrectly constructed. Expected \">>\", found \""
                      << content[0] 
                      << "\"" 
                      << std::endl;
            this->status = 1;
        }
        return this->status;
    }
}