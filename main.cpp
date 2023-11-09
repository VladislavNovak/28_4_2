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
void trainHandler(Train* train, Station* station) {
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
                if (!station->hasTrain()) { return; }
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
    vector<int> times = { 1, 5, 10, 10, 10, 14 };
    // Будет регистрировать прибытие новых поездов
    Station station;

    vector<Train*> trains;
    trains.reserve(times.size());
    // Количество времени, которое затрачивает каждый поезд до прибытия на вокзал. Нужно для тестирования

    for (int i = 0; i < times.size(); ++i) {
        trains.emplace_back(new Train(i, times[i]));
    }

    // Создаем потоки по количеству поездов (просто для отработки многопоточности):
    vector<std::thread> threads(times.size());

    // Каждый поезд отправляется своим потоком
    for (int i = 0; i < times.size(); ++i) {
        threads.emplace_back(trainHandler, trains[i], &station);
    }

    std::thread menuThread(menuHandler, &station);

    for (auto &thread : threads) { if (thread.joinable()) { thread.join(); }}
    if (menuThread.joinable()) { menuThread.join(); }

    clearHeap(trains);

    cout << "THE END!" << endl;

    return 0;
}
