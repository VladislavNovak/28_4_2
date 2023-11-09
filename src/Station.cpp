#include "../headers/Station.h"

bool Station::hasTrain() const { return !list.empty(); }

// Если нужно отправить поезд
int Station::doDepart() {
    if (list.empty()) { return -1; }

    cout << "Train #" << list[0] << " sent out from platform." << endl;
    if (list.size() > 1) { cout << "Train #" << list[1] << " arrive on platform from a siding." << endl; }

    return popFront(list);
}

// Поезд пришёл на вокзал
void Station::addArrivingTrain(int id) {
    list.emplace_back(id);

    cout << "Train #" << id << " arrive";
    if (list.size() == 1) { cout << " on platform." << endl; }
    else { cout << " and is waiting on the siding." << endl; }
}

void Station::printTrainList() {
    if (list.empty()) { cout << "Station is empty." << endl; }
    else {
        cout << "STATION: Train #" << list[0] << " at the platform.";
        if (list.size() > 1) {
            cout << " Trains waiting: ";
            for (const auto &id : list) { cout << id << ((id != list[list.size() - 1]) ? ", " : ""); }
        }
        cout << endl;
    }
}