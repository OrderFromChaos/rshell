#ifndef RSHELLUTILS_H
#define RSHELLUTILS_H

#include <iostream>
#include <vector>

// Prints a vector's elements with a specific string delimiter.
// Pass "\n" to get multiple lines.
template <class T>
void printVector(std::vector<T>, std::string delimiter=" ");

// Join a vector with a string or a char (or anything else that supports +=)
template <class T>
std::string joinVector(std::vector<std::string>, T);

// Join a vector assuming the delimiters are already in the vector
std::string joinVector(std::vector<std::string>);

#endif
