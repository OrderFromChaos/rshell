#include "redirectinputtoken.h"
#include "../rshellutils.h"
#include "../convertVectorToCharArray.h"
#include "../executeCharArray.h"

#include <cstring>
#include <fstream>
// Dup libraries
#include <unistd.h>
#include <fcntl.h>

using namespace std;

RedirectInputToken::RedirectInputToken(vector<string> V) {
    this->content = V;
    this->isOperator = true;
}

string RedirectInputToken::stringify() {
    return "RedirectInputToken (<): \"" + joinVector(content, ' ') + "\"";
}

int RedirectInputToken::execute() {
    const int PATH_MX = 420;
    char** chararr = convertVectorToCharArray(leftChild->content);
    string filename = joinVector(rightChild->content, ' ');

    int stdin_save = dup(0);

    // Open file, catch if error
    int in_file = open(filename.c_str(), O_RDONLY);
    if (in_file == -1) {
        cout << "Open file error for: \"" << filename << '\"' << endl;
        this->status = 1;
        return this->status;
    }

    dup2(in_file, 0);  // Write
    close(in_file);

    this->status = executeCharArray(chararr);

    dup2(stdin_save, 0);  // Cleanup

    if (status == 47) {
        cout << "RSHELL: Command not found! " << '\"' << leftChild->content[0]
             << '\"' << endl;
        printVector(leftChild->content);
    }

    for (int i = 0; i < content.size() + 1; i++) {
        delete[] chararr[i];
    }
    delete[] chararr;

    return status;
}