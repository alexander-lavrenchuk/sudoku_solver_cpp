#include "board.h"

using namespace std;

Board::Board():
    is_changed(false) {
}
short& Board::operator() (short row, short col) {
    return matrix[row][col].value;
}

bool Board::update_cell(Cell& cell, short (&values)[DIMENSION]) {
    short value = 0;
    for(short i = 0; i < DIMENSION; i ++) {
        value = values[i];
        if(value == 0)
            break;
        cell.states[value - 1] = false;
    }
    return cell.update();
}

bool Board::solve_cell(Cell& cell) {
    if(cell.value > 0)
        return false;

    bool cell_updated = false;
    short value = 0;
    short idx = 0;
    short values[DIMENSION] {};
    
    // solve by row
    for(short j = 0; j < DIMENSION; j ++) {
        if(j == cell.col)
            continue;
        value = matrix[cell.row][j].value;
        if(value > 0)
            values[idx ++] = value;
    }
    cell_updated = update_cell(cell, values);
    if(cell_updated)
        return true;
    
    // solve by column
    idx = 0;
    for(short i = 0; i < DIMENSION; i ++)
        values[i] = 0;
    for(short i = 0; i < DIMENSION; i ++) {
        if(i == cell.row)
            continue;
        value = matrix[i][cell.col].value;
        if(value > 0)
            values[idx ++] = value;
    }
    cell_updated = update_cell(cell, values);
    if(cell_updated)
        return true;
    
    // solve by square
    idx = 0;
    for(short i = 0; i < DIMENSION; i ++)
        values[i] = 0;

    short i_beg = (short)(cell.row / SUB_DIMENSION) * SUB_DIMENSION;
    short j_beg = (short)(cell.col / SUB_DIMENSION) * SUB_DIMENSION;
    short i = 0, j = 0;
    
    for(short m = 0; m < SUB_DIMENSION; m ++) {
        for(short n = 0; n < SUB_DIMENSION; n ++) {
            i = i_beg + m;
            j = j_beg + n;
            if(i == cell.row && j == cell.col)
                continue;
            value = matrix[i][j].value;
            if(value > 0)
                values[idx ++] = value;
        }
    }
    cell_updated = update_cell(cell, values);
    
    return cell_updated;
}

short Board::solve() {
    short iteration = 0;
    bool matrix_is_changed = false;
    while(iteration < MAX_ITERATIONS) {
        iteration ++;
        matrix_is_changed = false;
        for(short i = 0; i < DIMENSION; i ++)
            for(short j = 0; j < DIMENSION; j ++)
                matrix_is_changed = 
                    matrix_is_changed || solve_cell(matrix[i][j]);
        if(!matrix_is_changed)
            break;
    }
    return iteration;
}

void Board::set_line(const short row, const string string_values) {
    Cell* cell;
    for(short col = 0; col < string_values.size(); col ++) {
        cell = &matrix[row][col];
        cell->value = string_values[col] - '0';
        cell->row = row;
        cell->col = col;
    }
    return;
}

void Board::input() {
    string str = "";
    cout << "Enter sudoku rows:\n";
    for(short row = 0; row < DIMENSION; row ++) {
        str = "";
        cout << "Row " << row + 1 << ": ";
        cin >> str;
        set_line(row, str);
    }
    return;
}

void Board::set_from_file(const char* path) {
    // string path;
    // path = "input.vim";  
    ifstream fin;
    fin.open(path);
    if(fin.is_open())
    {
        short row = 0;
        string str;
        while(!fin.eof())
        {
            str = "";
            getline(fin, str);
            set_line(row, str);
            row ++;
        }
    }
    fin.close();
    return;
}

void Board::print() {
    for(short i = 0; i < DIMENSION; i ++) {
        for(short j = 0; j < DIMENSION; j ++)
            cout << matrix[i][j].value << " ";
        cout << "\n";
    }
    return;
}
