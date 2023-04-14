#include <iostream>
#include <chrono>
#include "src/Board.h"

using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");

    Board sudoku;

    if (argc == 1) {
        // sudoku.input();
        sudoku.set_from_file("input/test.sudoku");
    } else {
        sudoku.set_from_file(argv[1]);
    }

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    sudoku.solve();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    // sudoku.print();
    // sudoku.print_to_file(OUTFILE);

    // cout << "Time elapsed = " <<
    //     chrono::duration_cast<chrono::microseconds>(end - begin).count()
    //     << "[µs]" << endl;
     cout << "Time elapsed = " <<
         chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << "[ms]" << endl;

    return 0;
}

