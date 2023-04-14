#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <fstream>
#include "constants.h"

using namespace std;

class Board {
private:
    bool is_wrong;
    int cells_solved;
    int matrix[DIMENSION][DIMENSION];
    static int sol_count;

    bool find_first_unresolved_cell(int& row, int& col) const;
    void set_line(const int& row, std::string const string_values);
    void state_off(const int& row, const int& col,
        bool *states, int &count);
    bool solve_cell(const int& row, const int& col);
    void solve_depended_cells(const int& row, const int& col);
    void try_solve();

public:
    Board();
    Board(Board const &copy);
    Board& operator=(const Board &copy);
    int get_sol_count() {return sol_count;};
    void set_from_file(const char* path);
    void print();
    void print_to_file(const char* path, const bool& append_mode = false);
    void solve();
};

#endif  // _BOARD_H_
