#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

using std::cout;
using std::endl;
using std::vector;

const int EMPTY_PLATFORM = -1;
std::mutex watchStation;
std::mutex watchCycle;

template<typename T>
T popFront (std::vector<T> &list) {
    T temp = list.front();
    list.erase(list.begin());
    return temp;
}

struct Station {
    int currentTrain = EMPTY_PLATFORM;
    vector<int> waitingLine{};

    // Нужно отправить поезд
    int sentTrainOut() {
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

        if (currentTrain == EMPTY_PLATFORM && !waitingLine.empty()) {
            currentTrain = popFront<int>(waitingLine);
            cout << "Train #" << currentTrain << " has arrived on platform from the waiting line" << endl;
        }

        return runawayTrain;
    }

    // Поезд пришёл на вокзал
    void addArrivingTrain(int id) {
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

    void printTrainList() {
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
};

// ID поезда, его время в пути и станция, которая принимает поезд:
void asyncCountdown(int id, int travelTime, Station* station) {

    for (int i = 0; i < travelTime; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        watchCycle.lock();
        if (i != travelTime - 1) { cout << "(" << i << ") Train #" << id << " on the way" << endl; }
        watchCycle.unlock();
    }

    watchStation.lock();
    station->addArrivingTrain(id);
    watchStation.unlock();
}

int main() {
    Station station;
    const int TRAINS_COUNT = 4;
    vector<int> trains = { 1, 2, 3, 4 };
    vector<int> travelTimes = { 5, 10, 10, 10 };
    vector<std::thread> threads(TRAINS_COUNT);

    for (int i = 0; i < TRAINS_COUNT; ++i) {
        threads.emplace_back(asyncCountdown, trains[i], travelTimes[i], &station);
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

    return 0;
}
