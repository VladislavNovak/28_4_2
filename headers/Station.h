#ifndef INC_28_4_2_STATION_H
#define INC_28_4_2_STATION_H

#include <iostream>
#include <vector>
#include "utilities.h"

using std::cout;
using std::endl;
using std::vector;

class Station {
    vector<int> list{};
public:
    [[nodiscard]] bool hasTrain() const;

    // Если нужно отправить поезд
    int doDepart();

    // Поезд пришёл на вокзал
    void addArrivingTrain(int id);

    void printTrainList();
};

#endif //INC_28_4_2_STATION_H
