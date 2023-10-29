#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include "Train.h"
#include "Station.h"

using std::cout;
using std::endl;
using std::vector;

// Регулирует асинхронное размещение в station.waitingLine
std::mutex watchStation;
// Регулирует вывод сообщений в каждом потоке
std::mutex watchCycle;

void asyncCountdown(Train* train, Station* station) {

    for (int i = 0; i < train->getTravelTime(); ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        watchCycle.lock();
        if (i != train->getTravelTime() - 1) {
            cout << "(" << i << ") Train #" << train->getId() << " on the way" << endl;
        }
        watchCycle.unlock();
    }

    watchStation.lock();
    station->addArrivingTrain(train->getId());
    watchStation.unlock();
}

int main() {
    Station station;
    const int TRAINS_COUNT = 4;

    vector<Train*> trains;
    trains.reserve(TRAINS_COUNT);
    vector<int> travelTimes = { 5, 10, 10, 10 };

    for (int i = 0; i < TRAINS_COUNT; ++i) {
        trains.emplace_back(new Train(i, travelTimes[i]));
    }

    vector<std::thread> threads(TRAINS_COUNT);

    for (int i = 0; i < TRAINS_COUNT; ++i) {
        threads.emplace_back(asyncCountdown, trains[i], &station);
    }

    cout << "Start" << endl;
    for (auto &thread : threads) { if (thread.joinable()) { thread.join(); }}

    station.printTrainList();
    station.sentTrainOut();
    station.printTrainList();
    station.sentTrainOut();
    station.printTrainList();
    station.sentTrainOut();
    station.printTrainList();
    station.sentTrainOut();
    station.printTrainList();
    station.sentTrainOut();
    station.printTrainList();

    for (auto &train : trains) { delete train; }
    trains.clear();

    return 0;
}
