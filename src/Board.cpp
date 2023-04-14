#include <filesystem>
#include <iostream>
#include <cstring>
#include "Board.h"
#include "constants.h"

int Board::sol_count = 0;

Board::Board():
    is_wrong(false),
    cells_solved(0),
    matrix {} {}


Board::Board(Board const &copy):
    is_wrong(copy.is_wrong),
    cells_solved(copy.cells_solved) {
    memcpy(this, &copy, sizeof(Board));
    // memcpy(&matrix[0][0], &copy.matrix[0][0], sizeof(int) * DIMENSION * DIMENSION);
    // for(int i = 0; i < DIMENSION; ++i)
    //     for(int j = 0; j < DIMENSION; ++j)
    //         matrix[i][j] = copy.matrix[i][j];
}


Board& Board::operator=(const Board &copy) {
    is_wrong = copy.is_wrong;
    cells_solved = copy.cells_solved;
    memcpy(this, &copy, sizeof(Board));
    // memcpy(&matrix[0][0], &copy.matrix[0][0], sizeof(int) * DIMENSION * DIMENSION);
    // for(int i = 0; i < DIMENSION; ++i)
    //     for(int j = 0; j < DIMENSION; ++j)
    //         matrix[i][j] = copy.matrix[i][j];
    return *this;
}


void Board::set_from_file(const char* path) {
    ifstream fin;
    fin.open(path);
    if(!fin.is_open())
        return;     //Raise exception

    int row = 0;
    string str = "";
    while(!fin.eof())
    {
        getline(fin, str);
        set_line(row, str);
        ++row;
    }

    fin.close();
}


void Board::print() {
    system("clear");
    cout << "*************************\n";
    for(int row = 0; row < DIMENSION; ++row)
        for(int col = 0; col < DIMENSION; ++col) {
            cout << matrix[row][col] << ((col < DIMENSION - 1) ? " " : "\n");
        }
}


void Board::print_to_file(const char* path, const bool& append_mode) {
    ofstream fout;
    if(append_mode)
        fout.open(path, fstream::app);
    else
        fout.open(path);
    if(!fout.is_open())
        return;

    // fout << "\n*****************\n";
    fout << "\n";
    for(int row = 0; row < DIMENSION; ++row)
        for(int col = 0; col < DIMENSION; ++col)
            fout << matrix[row][col] << ((col < DIMENSION - 1) ? " " : "\n");
    fout.close();
}


void Board::solve() {
    ofstream fout;
    fout.open(OUTFILE);
    if(!fout.is_open())
        return;
    fout << "";
    fout.close();

    for(int row = 0; row < DIMENSION && cells_solved < DIMENSION * DIMENSION; ++row)
        for(int col = 0; col < DIMENSION && cells_solved < DIMENSION * DIMENSION; ++col) {
            if(matrix[row][col])
                continue;
            if(cells_solved < DIMENSION * DIMENSION && solve_cell(row, col)) {
                solve_depended_cells(row, col);
            }
        }

    try_solve();
}


bool Board::find_first_unresolved_cell(int& row, int& col) const {
    for(int r = 0; r < DIMENSION; ++r)
        for(int c = 0; c < DIMENSION; ++c)
            if(matrix[r][c] == 0) {
                row = r;
                col = c;
                return true;
            }
    return false;
}


void Board::set_line(const int& row, string const string_values) {
    int value = 0;
    for(size_t col = 0; col < string_values.size(); ++col) {
        value = string_values[col] - '0';
        if(value) {
            matrix[row][col] = value;
            ++cells_solved;
        }
    }
}


void Board::state_off(const int& row, const int& col,
        bool *states, int &count) {

    int value = matrix[row][col];

    if(value > 0 && states[value - 1]) {
        states[value - 1] = false;
        count --;
    }
}


bool Board::solve_cell(const int& row, const int& col) {
    int value = matrix[row][col];
    if(value > 0)
        return false;

    bool states[DIMENSION] {true, true, true, true, true, true, true, true, true};
    int count = 9;

    for(int i = 0; i < DIMENSION; ++i) {
        int r, c;
        // Check in row
        r = row;
        c = i;
        if(c != col) {
            state_off(r, c, states, count);
            if(!count) {
                is_wrong = true;
                return false;
            }
        }

        // Check in column
        r = i;
        c = col;
        if(i != row) {
            state_off(r, c, states, count);
            if(!count) {
                is_wrong = true;
                return false;
            }
        }

        // Check in square
        r = row / SUB_DIMENSION * SUB_DIMENSION + i / SUB_DIMENSION;
        c = col / SUB_DIMENSION * SUB_DIMENSION  + i % SUB_DIMENSION;
        if(r != row && c != col) {
            state_off(r, c, states, count);
            if(!count) {
                is_wrong = true;
                return false;
            }
        }
    }

    if(count > 1)
        return false;

    for(int i = 0; i < DIMENSION; ++i) {
        if(states[i]) {
            matrix[row][col] = i + 1;
            ++cells_solved;
            if(cells_solved == DIMENSION * DIMENSION) {
                ++sol_count;
                print_to_file(OUTFILE, true);
            }
            return true;
        }
    }

    return false;
}


void Board::solve_depended_cells(const int& row, const int& col) {
    // if(!matrix[row][col])
    //     return;
    for(int i = 0; i < DIMENSION; ++i) {
        int r, c;
        // Solve in row
        r = row;
        c = i;
        if(c != col)
            if(cells_solved < DIMENSION * DIMENSION && solve_cell(r, c))
                solve_depended_cells(r, c);

        // Solve in column
        r = i;
        c = col;
        if(i != row)
            if(cells_solved < DIMENSION * DIMENSION && solve_cell(r, c))
                solve_depended_cells(r, c);

        // Solve in square
        r = row / SUB_DIMENSION * SUB_DIMENSION + i / SUB_DIMENSION;
        c = col / SUB_DIMENSION * SUB_DIMENSION  + i % SUB_DIMENSION;
        if(r != row && c != col)
            if(cells_solved < DIMENSION * DIMENSION && solve_cell(r, c))
                solve_depended_cells(r, c);
    }
}


void Board::try_solve() {
    int row = 0;
    int col = 0;
    if(!find_first_unresolved_cell(row, col))
        return;

    bool states[DIMENSION] {true, true, true, true, true, true, true, true, true};
    int count = 9;

    for(int i = 0; i < DIMENSION; ++i) {
        int r, c;
        // State off in row
        r = row;
        c = i;
        if(c != col)
            state_off(r, c, states, count);

        // State off in column
        r = i;
        c = col;
        if(i != row)
            state_off(r, c, states, count);

        // State off in square
        r = row / SUB_DIMENSION * SUB_DIMENSION + i / SUB_DIMENSION;
        c = col / SUB_DIMENSION * SUB_DIMENSION  + i % SUB_DIMENSION;
        if(r != row && c != col)
            state_off(r, c, states, count);
    }

    if(!count) {
        is_wrong = true;
        return;
    }

    for(int i = 0; i < DIMENSION; ++i)
        if(states[i]) {
            Board copy_sudoku = *this;
            matrix[row][col] = i + 1;
            ++cells_solved;
            solve_depended_cells(row, col);

            if(!is_wrong && cells_solved < DIMENSION * DIMENSION)
                try_solve();

            *this = copy_sudoku;
        }

    return;
}

