#pragma once
#ifndef _CELL_H_
#define _CELL_H_

class Cell {
private:

public:
    short row;
    short col;
    short value;
    bool states[DIMENSION];
    Cell();
    ~Cell();
    bool update();
};

#include "cell.cpp"

#endif  // _CELL_H_
