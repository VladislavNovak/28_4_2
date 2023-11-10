#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include "constants.h"
#include "utilities.h"
#include "Train.h"
#include "Station.h"

using std::cout;
using std::endl;
using std::vector;

// Регулирует асинхронное размещение в station.waitingLine
std::mutex watchStation;

// Поток для каждого конкретного поезда
void trainsHandler(Train* train, Station* station) {
    // Отсчитываем время для каждого поезда
    for (int i = 0; i < train->getTravelTime(); ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Прибытие на станцию. Будем лишь помещать id поезда.
    // Блокируем поток, чтобы добавление новых позиций в массив не пересекалось:
    watchStation.lock();
    station->addArrivingTrain(train->getId());
    watchStation.unlock();
}

void menuHandler(Station *station) {
    std::vector<std::string> menuTitles = { "exit", "depart" };

    while (true) {
        if (station->hasTrain()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            int command = selectMenuItem(menuTitles);

            if (command == static_cast<int>(Menu::EXIT)) { return; }
            else if (command == static_cast<int>(Menu::DEPART)) {
                station->doDepart();
                // Автоматически выходим, если поездов нет ни на станции, ни в пути
                if (!station->hasTrain() && !station->getExpected()) { return; }
                station->printTrainList();
            }
        }
    }
}

void clearHeap(vector<Train*> &trains) {
    cout << "LOG:Deleted heap" << endl;
    if (trains.empty()) { return; }
    for (auto &train : trains) { delete train; }
    trains.clear();
}

int main() {
    int trainCount = 6;
    // Будет регистрировать прибытие новых поездов
    Station station;
    station.setExpected(trainCount);
    // Создаем потоки по количеству поездов (просто для отработки многопоточности):
    vector<std::thread> threads(trainCount);

    vector<Train*> trains;
    trains.reserve(trainCount);

    cout << "Number of train: " << trainCount << ". Enter travel time for each one" << endl;
    for (int i = 0; i < trainCount; ++i) {
        trains.emplace_back(new Train(i, putNumeric({1, 20}, ("for train #" + std::to_string(i)))));
    }

    cout << "START!" << endl;

    // Каждый поезд отправляется своим потоком
    for (int i = 0; i < trainCount; ++i) {
        threads.emplace_back(trainsHandler, trains[i], &station);
    }

    std::thread menuThread(menuHandler, &station);

    for (auto &thread : threads) { if (thread.joinable()) { thread.join(); }}
    if (menuThread.joinable()) { menuThread.join(); }

    clearHeap(trains);

    cout << "THE END!" << endl;

    return 0;
}
