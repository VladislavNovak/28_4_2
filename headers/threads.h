#ifndef INC_28_4_2_THREADS_H
#define INC_28_4_2_THREADS_H

#include <thread>
#include "constants.h"
#include "utilities.h"
#include "Train.h"
#include "Station.h"

void trainThread(Train* train, Station* station);

void menuThread(Station *station);

#endif //INC_28_4_2_THREADS_H