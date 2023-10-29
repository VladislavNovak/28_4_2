#ifndef INC_28_4_2_UTILITIES_H
#define INC_28_4_2_UTILITIES_H

#include <vector>

template<typename T>
T popFront (std::vector<T> &list) {
    T temp = list.front();
    list.erase(list.begin());
    return temp;
}

#endif //INC_28_4_2_UTILITIES_H
