#include "test_fxn.h"

// Stat libraries
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool test(std::vector<std::string> content, int offset) {
    if (content[offset] == "-e") {
        struct stat check;
        // TODO: Fix this to properly return bools
        // (And have no exit issues)
        return (stat(content[offset+1].c_str(), &check) == 0);
        // checks if the file/directory exists
    } else if (content[offset] == "-f") {
        // checks if the file/directory exists and is a regular file
        struct stat check;
        if (stat(content[offset+1].c_str(), &check) == 0) {
            if (check.st_mode & S_IFREG) {
                return true;
            } else {
                return false;
            }
        }
        return false;
    } else if (content[offset] == "-d") {
        struct stat check;
        if (stat(content[offset+1].c_str(), &check) == 0) {
            if (check.st_mode & S_IFDIR) {
                return true;
            } else {
                return false;
            }
        }
        return false;
        // checks if the file/directory exists and is a directory
    } else {
        struct stat check;
        return (stat(content[offset].c_str(), &check) == 0);
        // checks if the file/directory exists
    }
}