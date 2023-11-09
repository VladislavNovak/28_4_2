#ifndef INC_28_4_2_UTILITIES_H
#define INC_28_4_2_UTILITIES_H

#include <iostream>
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

#endif //INC_28_4_2_UTILITIES_H
