#include "pipetoken.h"
#include "../rshellutils.h"

#include <cstring>
// Dup libraries
#include <unistd.h>
#include <fcntl.h>

using namespace std;

PipeToken::PipeToken(vector<string> V) {
    this->content = V;
    this->isOperator = true;
}

string PipeToken::stringify() {
    return "PipeToken (|): \"" + joinVector(content, ' ') + "\"";
}

int PipeToken::execute(std::unordered_map<std::string, int>& statusMap) {
    string leftCommand = joinVector(leftChild->content, ' ');
    string rightCommand = joinVector(rightChild->content, ' ');

    // Set up buffer
    const int PATH_MX = 420;
    char buffer[PATH_MX];
    memset(buffer, '\0', PATH_MX);

    FILE* in_pipe = popen(leftCommand.c_str(), "r");
    FILE* out_pipe = popen(rightCommand.c_str(), "w");

    if ((in_pipe == nullptr) || (out_pipe == nullptr)) {
        this->status = 1;
        cout << "Piping error, check input";
        return 1;
    } else {
        this->status = 0;
        while (fgets(buffer, PATH_MX, in_pipe) != NULL) {
            cout << buffer << endl;
            fputs(buffer, out_pipe);
        }

        pclose(in_pipe);
        pclose(out_pipe);
    }

    return this->status;
}