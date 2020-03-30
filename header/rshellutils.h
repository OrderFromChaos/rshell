#ifndef RSHELLUTILS_H
#define RSHELLUTILS_H

#include <iostream>
#include <vector>

template <class T>
void printVector(std::vector<T> V, std::string delimiter=" ") {
	auto it = V.begin();
	std::cout << '{';
	while (it != V.end()) {
		std::cout << *it << delimiter;
		it++;
	}
	std::cout << '}' << std::endl;
}

template <class T>
std::string joinVector(std::vector<std::string> V, T joiner) {
	std::string concat;
	bool first = true;
	for (const std::string& substr : V) {
		if (first) {
			concat += substr;
			first = false;
		} else {
			concat += joiner;
			concat += substr;
		}
	}
	return concat;
}

std::string joinVector(std::vector<std::string> V) {
	std::string concat;
	for (const std::string& substr : V) {
		concat += substr;
	}
	return concat;
}

#endif
