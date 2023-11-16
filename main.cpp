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
void trainThread(Train* train, Station* station) {
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

void menuThread(Station *station) {
    std::vector<std::string> menuTitles = { "exit", "depart" };

    while (true) {
        if (station->hasTrain()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            int command = selectMenuItem(menuTitles);

            if (command == static_cast<int>(Menu::EXIT)) { return; }
            else if (command == static_cast<int>(Menu::DEPART)) {
                watchStation.lock();
                station->doDepart();
                watchStation.unlock();
                // Автоматически выходим, если поездов нет ни на станции, ни в пути
                if (!station->hasTrain() && !station->getExpected()) { return; }
                station->printTrainList();
            }
        }
    }
}

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
    int trainCount = 6;
    // Будет регистрировать прибытие новых поездов
    Station station;
    station.setExpected(trainCount);

    vector<Train*> trains;
    initialTrains(trains, trainCount);

    cout << "NOTE: After the first train arrives at the station, you can enter 'depart' or 'exit'" << endl;
    cout << "START!" << endl;

    // Создаем потоки по количеству поездов
    vector<std::thread> runTrains(trainCount);
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
