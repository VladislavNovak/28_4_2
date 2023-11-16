#include <iostream>
#include <vector>
#include <thread>
#include "utilities.h"
#include "Train.h"
#include "Station.h"
#include "threads.h"

using std::cout;
using std::endl;
using std::vector;

void initialTrains(vector<Train*> &trains, int trainCount) {
    trains.reserve(trainCount);

    cout << "Number of train: " << trainCount << ". Enter travel time for each one" << endl;
    for (int i = 0; i < trainCount; ++i) {
        trains.emplace_back(new Train(i, putNumeric({1, 20}, ("for train #" + std::to_string(i)))));
    }
}

void clearHeap(vector<Train*> &trains) {
    cout << "LOG:Deleted heap" << endl;
    if (trains.empty()) { return; }
    for (auto &train : trains) { delete train; }
    trains.clear();
}

int main() {
    const int TRAIN_COUNT = 6;
    // Будет регистрировать прибытие новых поездов
    Station station;
    station.setExpected(TRAIN_COUNT);

    vector<Train*> trains;
    initialTrains(trains, TRAIN_COUNT);

    cout << "NOTE: After the first train arrives at the station, you can enter 'depart' or 'exit'" << endl;
    cout << "START!" << endl;

    // Создаем потоки по количеству поездов
    vector<std::thread> runTrains(TRAIN_COUNT);
    // Каждый поезд отправляется своим потоком
    for (const auto &train : trains) { runTrains.emplace_back(trainThread, train, &station); }

    // Параллельно запускаем поток для меню
    std::thread runMenu(menuThread, &station);

    for (auto &thread : runTrains) { if (thread.joinable()) { thread.join(); }}
    if (runMenu.joinable()) { runMenu.join(); }

    clearHeap(trains);

    cout << "THE END!" << endl;

    return 0;
}
