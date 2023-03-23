#include "cell.cpp"
#include <fstream>
#include <string>

const short MAX_ITERATIONS = 100;

class Board {
private:
    bool is_changed;
    Cell matrix[DIMENSION][DIMENSION];
    
    bool update_cell(Cell& cell, short (&values)[DIMENSION]);
    bool solve_cell(Cell& cell);
    void set_line(const short row, const std::string string_values);
    
public:
    Board();
    short& operator() (short row, short col);
    void input();
    void set_from_file(const char* path);
    short solve();
    void print();
};



