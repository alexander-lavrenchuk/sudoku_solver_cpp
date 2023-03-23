#include <iostream>
#include "src/board.cpp"

using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");

    Board sudoku;
    argc == 1 ? sudoku.input() : sudoku.set_from_file(argv[1]);
    int iterations = 0;
    iterations = sudoku.solve();
    sudoku.print();
    cout << "Solved for " << iterations << " iterations.\n";

    return 0;
}

