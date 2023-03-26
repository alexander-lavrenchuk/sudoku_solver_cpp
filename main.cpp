#define FROM_FILE
// #define STEP_BY_STEP

#include <iostream>
#include <chrono>
#include "src/board.h"

using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");

    Board sudoku;

#ifndef FROM_FILE
    argc == 1 ? sudoku.input() : sudoku.set_from_file(argv[1]);
#else
    sudoku.set_from_file("input/input.vim");
#endif

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    sudoku.solve();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

#ifndef STEP_BY_STEP
    sudoku.print();
#endif

    cout << "Time elapsed = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
    // cout << "Time elapsed = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;

    return 0;
}

