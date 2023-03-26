#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_

#define MAX_ITERATIONS 10000
#define DIMENSION 9
#define SUB_DIMENSION 3
#define SLEEP_MILLISECONDS 200

#include <fstream>
#include <thread>
#include <chrono>
#include "cell.h"
#include "colors.h"

using namespace std;

class Board {
private:
    bool is_changed;
    Cell matrix[DIMENSION][DIMENSION];
    short cells_solved;
    short iterations_count;
    
    bool update_cell(Cell& cell, short (&values)[DIMENSION]);
    bool solve_cell(Cell& cell);
    void set_line(const short row, const std::string string_values);
    void calculate_cells_solved();
    
#ifdef STEP_BY_STEP
    Cell* last_cell_updated;
#endif
public:
    Board();
    short& operator() (short row, short col);
    void input();
    void set_from_file(const char* path);
    short solve();
    void print();
};

#include "board.cpp"

#endif  // _BOARD_H_
