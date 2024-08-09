#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class TicTacToe {
public:
    TicTacToe();
    void playgame();
private:
    char arr[3][3];
    int playerturn;
    void drawboard();
    int checkwin();
    void playermove();
    bool checkdraw();
    bool checkresult();
};

TicTacToe::TicTacToe() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            arr[i][j] = ' ';
        }
    }
    srand(time(0));
    playerturn = rand() % 2 + 1;
}

void TicTacToe::drawboard() {
    cout << "Player 1(O) -- Player 2(X)" << endl << endl;
    cout << "Turn: Player: " << playerturn << endl << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << arr[i][j];
            if (j != 2) cout << " | ";
        }
        if (i != 2) cout << endl << "___________" << endl;
    }
    cout << endl;
}

void TicTacToe::playermove() {
    int pos;
    bool correctmove = false;
    cout << endl << "Make your move" << endl;
    while (!correctmove) {
        cout << "Enter block number (1-9): ";
        cin >> pos;
        int index = pos - 1;
        if (pos >= 1 && pos <= 9) {
            if (arr[index / 3][index % 3] != 'O' && arr[index / 3][index % 3] != 'X') {
                arr[index / 3][index % 3] = (playerturn == 1) ? 'O' : 'X';
                correctmove = true;
                playerturn = (playerturn == 1) ? 2 : 1;
            } else {
                cout << "Cell already occupied, try again!" << endl;
            }
        } else {
            cout << "Invalid input, try again!" << endl;
        }
    }
}

bool TicTacToe::checkresult() {
    int check = checkwin();
    switch (check) {
    case 1:
        drawboard();
        cout << endl << "Player 1 won!" << endl;
        return true;
    case 2:
        drawboard();
        cout << endl << "Player 2 won!" << endl;
        return true;
    case -1:
        if (checkdraw()) {
            drawboard();
            cout << endl << "Match Drawn" << endl;
            return true;
        }
        break;
    }
    return false;
}

int TicTacToe::checkwin() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][0] != ' ') {
            return (arr[i][0] == 'O') ? 1 : 2;
        }
        if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[0][i] != ' ') {
            return (arr[0][i] == 'O') ? 1 : 2;
        }
    }
    // Check diagonals
    if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[0][0] != ' ') {
        return (arr[0][0] == 'O') ? 1 : 2;
    }
    if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0] && arr[0][2] != ' ') {
        return (arr[0][2] == 'O') ? 1 : 2;
    }
    return -1;
}

bool TicTacToe::checkdraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void TicTacToe::playgame() {
    while (true) {
        drawboard();
        playermove();
        if (checkresult()) {
            break;
        }
    }
    cout << endl;
}

int main() {
    TicTacToe obj;
    obj.playgame();
    return 0;
}
