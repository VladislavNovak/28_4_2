#include "Station.h"

bool Station::hasTrain() const { return !list.empty(); }

// Соответствует кол. поездов, которые в пути. Будет уменьшаться с каждым прибывшим на станцию поездом
void Station::setExpected(int count) { expected = count; }

int Station::getExpected() const { return expected; }

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
    --expected;

    cout << "ACTION:  Train #" << id << " arrive";
    if (list.size() == 1) { cout << " on platform." << endl; }
    else { cout << " and is waiting on the siding." << endl; }
    printTrainList();
}

void Station::printTrainList() {
    if (list.empty()) { cout << "Station is empty." << endl; }
    else {
        cout << "STATION: Train #" << list[0] << " at the platform.";
        if (list.size() > 1) {
            cout << " Trains waiting: ";
            for (int i = 1; i < list.size(); ++i) {
                int id = list[i];
                cout << id << (id != list[list.size() - 1] ? ", " : "");
            }
        }
        cout << endl;
    }
}