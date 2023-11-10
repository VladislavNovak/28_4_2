#ifndef INC_28_4_2_UTILITIES_H
#define INC_28_4_2_UTILITIES_H

#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <sstream>
#include <iterator>
#include <vector>

using std::cout;
using std::endl;

template<typename T>
T popFront (std::vector<T> &list) {
    T temp = list.front();
    list.erase(list.begin());
    return temp;
}

int selectMenuItem(const std::vector<std::string> &list, const std::string &msg = "Choose between options");

int putInput();

int putNumeric(const std::vector<int> &list = {}, const std::string &msg = "");

#endif //INC_28_4_2_UTILITIES_H
