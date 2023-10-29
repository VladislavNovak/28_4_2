#include "../headers/Station.h"

// Если нужно отправить поезд
int Station::sentTrainOut() {
    // Если вокзал и очередь ожидания пусты, возвращаем -1;
    if (currentTrain == EMPTY_PLATFORM && waitingLine.empty()) {
        cout << "There are no trains at the station!" << endl;
        return EMPTY_PLATFORM;
    }

    int runawayTrain = EMPTY_PLATFORM;
    if (currentTrain != EMPTY_PLATFORM) {
        runawayTrain = currentTrain;
        cout << "Train #" << currentTrain << " left the platform" << endl;
        currentTrain = EMPTY_PLATFORM;
    }

    if (!waitingLine.empty()) {
        currentTrain = popFront<int>(waitingLine);
        cout << "Train #" << currentTrain << " has arrived on platform from the waiting line" << endl;
    }

    // Если понадобятся данные об ушедшем поезде
    return runawayTrain;
}

// Поезд пришёл на вокзал
void Station::addArrivingTrain(int id) {
    cout << "Train #" << id;
    // Если он пуст, сразу помещаем поезд на перон:
    if (currentTrain == EMPTY_PLATFORM && waitingLine.empty()) {
        cout << " arrived at the platform" << endl;
        currentTrain = id;
    }
        // иначе - в очередь ожидания:
    else {
        cout << " stood in a waiting line" << endl;
        waitingLine.emplace_back(id);
    }
}

void Station::printTrainList() {
    if (currentTrain != EMPTY_PLATFORM) {
        cout << "Train #" << currentTrain << " at the platform" << endl;
    }

    if (!waitingLine.empty()) {
        cout << "Trains on waiting line: ";
        for (const auto &id : waitingLine) { cout << id << ", "; }
        cout << endl;
    }

    if (currentTrain == EMPTY_PLATFORM && waitingLine.empty()) {
        cout << "Station is empty" << endl;
    }
}