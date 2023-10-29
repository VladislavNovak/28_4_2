#ifndef INC_28_4_2_TRAIN_H
#define INC_28_4_2_TRAIN_H

class Train {
    int id{};
    int travelTime{};
public:
    Train(int inId, int inTimeSpent);

    [[nodiscard]] int getId() const;
    [[nodiscard]] int getTravelTime() const;
};

#endif //INC_28_4_2_TRAIN_H
