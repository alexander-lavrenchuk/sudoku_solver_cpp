#include "cell.h"

Cell::Cell():
    row(0), col(0), value(0),
    states {1, 1, 1, 1, 1, 1, 1, 1, 1} {
}

Cell::~Cell() {
}

bool Cell::update() {
    short states_sum = 0;
    short index = 0;
    bool state = false;
    for(short i = 0; i < DIMENSION; i ++)
    {
        state = states[i];
        if(state) {
            index = i;
            states_sum ++;
            if(states_sum > 1)
                return false;
        }
    }
    value = index + 1;
    return true;
}

