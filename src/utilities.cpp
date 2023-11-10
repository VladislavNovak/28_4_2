#include "utilities.h"

int selectMenuItem(const std::vector<std::string> &list, const std::string &msg) {
    std::cout << msg << " (";
    for (const auto &item : list) { std::cout << item << ((item != list[list.size() - 1]) ? "|" : ")!"); }
    cout << endl;

    while (true) {
        std::string userInput;
        std::getline(std::cin >> std::ws, userInput);

        for (int i = 0; i < list.size(); ++i)
            if (list[i] == userInput) return i;

        std::cout << "Error. Try again:";
    }
}

int putInput() {
    int input;
    while (true) {
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input is invalid. Please try again:";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }
}

// cut version
int putNumeric(const std::vector<int> &list, const std::string &msg) {
    std::cout << "Enter (in the range "  << list[0] << "-" << list[1] << ") " << msg << ":";

    int userInput;

    while (true) {
        userInput = putInput();
        if (userInput >= list[0] && userInput <= list[1]) return userInput;
        std::cout << "Error.Try again:";
    }
}
