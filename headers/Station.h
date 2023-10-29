#ifndef INC_28_4_2_STATION_H
#define INC_28_4_2_STATION_H

#include <iostream>
#include <vector>
#include "utilities.h"

using std::cout;
using std::endl;
using std::vector;

class Station {
    const int EMPTY_PLATFORM = -1;
    int currentTrain = EMPTY_PLATFORM;
    vector<int> waitingLine{};
public:
    // Если нужно отправить поезд
    int sentTrainOut();

    // Поезд пришёл на вокзал
    void addArrivingTrain(int id);

    void printTrainList();
};

#endif //INC_28_4_2_STATION_H
