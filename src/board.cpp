Board::Board():
    is_changed(false),
    iterations_count(0)
#ifdef STEP_BY_STEP
    , last_cell_updated(nullptr)
#endif
    {}

short& Board::operator() (short row, short col) {
    return matrix[row][col].value;
}

bool Board::update_cell(Cell& cell, short (&values)[DIMENSION]) {
    iterations_count ++;
    short value = 0;
    for(short i = 0; i < DIMENSION; i ++) {
        value = values[i];
        if(value == 0)
            break;
        cell.states[value - 1] = false;
    }
    bool cell_updated = cell.update();
    if(cell_updated)
        cells_solved ++;
    return cell_updated;
}

bool Board::solve_cell(Cell& cell) {
    if(cell.value > 0)
        return false;

    bool cell_updated = false;
    // short value = 0;
    short idx = 0;
    short values[DIMENSION] {};
    
    // solve by row
    for(short j = 0; j < DIMENSION; j ++) {
        if(j == cell.col)
            continue;
        if(matrix[cell.row][j].value > 0)
            values[idx ++] = matrix[cell.row][j].value;
    }
    cell_updated = update_cell(cell, values);
    if(cell_updated) {
#ifdef STEP_BY_STEP
        last_cell_updated = &cell;
        print();
#endif
        // solve depended cells
        // in same row
        for(short col = 0; col < DIMENSION; col ++)
            if(cell.col != col)
                solve_cell(matrix[cell.row][col]);
        
        // in same column
        for(short row = 0; row < DIMENSION; row ++)
            if(cell.row != row)
                solve_cell(matrix[row][cell.col]);

        // in same square
        short i_beg = (short)(cell.row / SUB_DIMENSION) * SUB_DIMENSION;
        short j_beg = (short)(cell.col / SUB_DIMENSION) * SUB_DIMENSION;
        short i = 0, j = 0;
        for(short m = 0; m < SUB_DIMENSION; m ++) {
            for(short n = 0; n < SUB_DIMENSION; n ++) {
                i = i_beg + m;
                j = j_beg + n;
                if(i != cell.row || j != cell.col)
                    solve_cell(matrix[i][j]);
            }
        }
        return true;
    }
    
    // solve by column
    idx = 0;
    for(short i = 0; i < DIMENSION; i ++)
        values[i] = 0;
    for(short i = 0; i < DIMENSION; i ++) {
        if(i == cell.row)
            continue;
        if(matrix[i][cell.col].value > 0)
            values[idx ++] = matrix[i][cell.col].value;
    }
    cell_updated = update_cell(cell, values);
    if(cell_updated) {
#ifdef STEP_BY_STEP
        last_cell_updated = &cell;
        print();
#endif
        // solve depended cells
        // in same row
        for(short col = 0; col < DIMENSION; col ++)
            if(cell.col != col)
                solve_cell(matrix[cell.row][col]);
        
        // in same column
        for(short row = 0; row < DIMENSION; row ++)
            if(cell.row != row)
                solve_cell(matrix[row][cell.col]);

        // in same square
        short i_beg = (short)(cell.row / SUB_DIMENSION) * SUB_DIMENSION;
        short j_beg = (short)(cell.col / SUB_DIMENSION) * SUB_DIMENSION;
        short i = 0, j = 0;
        for(short m = 0; m < SUB_DIMENSION; m ++) {
            for(short n = 0; n < SUB_DIMENSION; n ++) {
                i = i_beg + m;
                j = j_beg + n;
                if(i != cell.row || j != cell.col)
                    solve_cell(matrix[i][j]);
            }
        }
        return true;
    }
    
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
            if(matrix[i][j].value > 0)
                values[idx ++] = matrix[i][j].value;
        }
    }
    cell_updated = update_cell(cell, values);
    
    if(cell_updated) {
#ifdef STEP_BY_STEP
        last_cell_updated = &cell;
        print();
#endif
        // solve depended cells
        // in same row
        for(short col = 0; col < DIMENSION; col ++)
            if(cell.col != col)
                solve_cell(matrix[cell.row][col]);
        
        // in same column
        for(short row = 0; row < DIMENSION; row ++)
            if(cell.row != row)
                solve_cell(matrix[row][cell.col]);

        // in same square
        short i_beg = (short)(cell.row / SUB_DIMENSION) * SUB_DIMENSION;
        short j_beg = (short)(cell.col / SUB_DIMENSION) * SUB_DIMENSION;
        short i = 0, j = 0;
        for(short m = 0; m < SUB_DIMENSION; m ++) {
            for(short n = 0; n < SUB_DIMENSION; n ++) {
                i = i_beg + m;
                j = j_beg + n;
                if(i != cell.row || j != cell.col)
                    solve_cell(matrix[i][j]);
            }
        }
    }
    return cell_updated;
}

short Board::solve() {
    bool matrix_is_changed = false;
    while(iterations_count < MAX_ITERATIONS) {
        matrix_is_changed = false;
        for(short i = 0; i < DIMENSION; i ++)
            for(short j = 0; j < DIMENSION; j ++)
                matrix_is_changed = 
                    matrix_is_changed || solve_cell(matrix[i][j]);
        if(!matrix_is_changed)
            break;
    }
    return iterations_count;
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

void Board::calculate_cells_solved() {
    cells_solved = 0;
    for(short i = 0; i < DIMENSION; i ++)
        for(short j = 0; j < DIMENSION; j ++)
            if(matrix[i][j].value > 0)
                cells_solved ++;
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
    calculate_cells_solved();
    return;
}

void Board::set_from_file(const char* path) {
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
    calculate_cells_solved();
    return;
}

void Board::print() {
    system("clear");
    for(short i = 0; i < DIMENSION; i ++) {
        for(short j = 0; j < DIMENSION; j ++) {
#ifdef STEP_BY_STEP
            if(i == last_cell_updated->row &&
                    j == last_cell_updated->col) {
                cout << colors::set_format(FOREGROUND_RED);
                cout << matrix[i][j].value << " ";
                cout << colors::reset_format();
            }
            else
                cout << matrix[i][j].value << " ";
#else
            cout << matrix[i][j].value << " ";
#endif
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "Solved cells: " << cells_solved << "\n";
    cout << "Solved in " << iterations_count << " iterations.\n";

#ifdef STEP_BY_STEP
    // cout << "Press enter to continue...";
    // cin.get();
    this_thread::sleep_for(chrono::milliseconds(SLEEP_MILLISECONDS));
#endif
    return;
}
