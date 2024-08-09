#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>   // Include this header for multithreading
#include <chrono>   // Include this header for sleep

using namespace std;

class TicTacToe {
public:
    TicTacToe();
    void playgame();
private:
    vector<vector<char>>arr;
    int playerturn;
    void drawboard();
    int checkwin();
    void playermove();
    bool checkdraw();
    bool checkresult();
    void update_file();
    void winner_display(int player);
};

// Function to update the game state to a file
void TicTacToe::update_file() {
    ofstream stateFile("gamestate.txt");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            stateFile << arr[i][j];
        }
        stateFile << endl;
    }
    stateFile.close();
}

TicTacToe::TicTacToe() : arr(3, vector<char>(3, '?')) {
    
    srand(time(0));
    playerturn = rand() % 2 + 1;
    update_file();
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

void TicTacToe::winner_display(int player) {
    ofstream stateFile("gamestate.txt", ios::app);
    if (player == 1) {
        stateFile << "Winner: Player 1 (O)" << endl;
    } else if (player == 2) {
        stateFile << "Winner: Player 2 (X)" << endl;
    } else {
        stateFile << "Result: Draw" << endl;
    }
    stateFile.close();
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
                update_file();
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
        winner_display(1);
        return true;
    case 2:
        drawboard();
        cout << endl << "Player 2 won!" << endl;
        winner_display(2);
        return true;
    case -1:
        if (checkdraw()) {
            drawboard();
            cout << endl << "Match Drawn" << endl;
            winner_display(0);
            return true;
        }
        break;
    }
    return false;
}

int TicTacToe::checkwin() {
    for (int i = 0; i < 3; i++) {
        if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][0] != ' ') {
            return (arr[i][0] == 'O') ? 1 : 2;
        }
        if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[0][i] != ' ') {
            return (arr[0][i] == 'O') ? 1 : 2;
        }
    }
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
    // Start the Python script in a separate thread
    thread pythonThread([]() {
        system("python3 graphics.py");  // Adjust this if necessary (e.g., use "python graphics.py" if that's how it's invoked)
    });

    // Create and run the TicTacToe game
    TicTacToe obj;
    obj.playgame();

    // Wait for the Python thread to finish before exiting
    pythonThread.join();

    return 0;
}
