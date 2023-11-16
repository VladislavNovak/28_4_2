#include <mutex>
#include "threads.h"

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

// Поток для меню
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
