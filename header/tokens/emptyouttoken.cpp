#include "emptyouttoken.h"
#include "../rshellutils.h"

#include <cstring>
#include <fstream>

using namespace std;

EmptyOutToken::EmptyOutToken(vector<string> V) {
    this->content = V;
    this->isOperator = true;
}

string EmptyOutToken::stringify() {
    return "EmptyOutToken \"" + joinVector(this->content, ' ') + "\"";
}

int EmptyOutToken::execute() {
    // Assign the values of the leftChild's content as a completed commmand,
    // Store value into a cstring, and take in the filename from the
    // rightChild's content.
    string fileName = rightChild->content[0];
    const int PATH_MX = 1000;
    string commandOutput;

    // Take in command from leftChild.
    string command = joinVector(leftChild->content, ' ');

    // Create buffer to store value of comamnd.
    char buffer2[PATH_MX];
    memset(buffer2, '\0', PATH_MX);

    // Use popen to invoke the shell and get an fstream for the command.
    FILE* in_pipe = popen(command.c_str(), "r");

    // Store the result of the file into a string.
    if (!in_pipe) {
        cout << "Command not found:" << endl;
        cout << "   ";
        printVector(leftChild->content, "; ");
        this->status = 47;
        return this->status;
    } else {
        leftChild->status = 0;
        while (fgets(buffer2, PATH_MX, in_pipe) !=
               NULL) {  // Reads lines from file pipe
            commandOutput.append(buffer2);
        }
        pclose(in_pipe);

        if (commandOutput == "") {
            // This catches both empty output (eg "echo a > txt.txt") and
            // failed commands, a la "echa"
            this->status = 0;
            return this->status;
        }

        ofstream ofs;

        if (content[0] == ">") {
            ofs.open(fileName.c_str(), ofstream::out | ofstream::trunc);
            if (!ofs.is_open()) {
                cout << "Unable to open file; may already be open" << endl;
                this->status = 1;
            } else {
                ofs << commandOutput;
                ofs.close();
                this->status = 0;
            }
        } else {
            cout << "Token incorrectly constructed. Expected \">\", found \""
                 << content[0] << "\"" << endl;
            this->status = 1;
        }
        return this->status;
    }
}