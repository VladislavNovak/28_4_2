#include "Train.h"

Train::Train(int inId, int inTimeSpent) {
    id = inId;
    travelTime = inTimeSpent;
}

[[nodiscard]] int Train::getId() const { return id; }
[[nodiscard]] int Train::getTravelTime() const { return travelTime; }

