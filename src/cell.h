const short DIMENSION = 9;
const short SUB_DIMENSION = 3;

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
    // void get_states(bool (&states)[DIMENSION]) {
    //     states = this->states;
};

