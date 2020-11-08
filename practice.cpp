// Welcome to LEAF (Low Effort Accesible Fun)
// This was not low effort, but it IS fun!

#include <iostream>
#include <string>
#include <locale>
#include <vector>
#include <cmath>
using namespace std;

void sizeRequest(string &answer);
void printGridWithNum();
void grid_setup(string& answer, vector<string>& grid);
void grid_draw (vector<string>& grid);
int row (int size, int column);
int column (int size, int row);
int length;
void play(string& answer, vector<string>& grid, int moves[9], char& player, char& player1, char& player2, string& player1_name, string& player2_name);
bool winningConditions (string& answer, vector<string>& grid, int moves[9]);

// main function
int main () {
    string player1_name;
    string player2_name;
    string answer = "nothing";
    vector<string> grid;
    int moves [9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    char player1 = 'x';
    char player2 = 'y';
    char player = player1;
    cout << "Welcome to LEAF (Low Effort Accesible Fun)" << endl;
    string playAgain = "y";
    cout << "Please enter a name for player 1" << endl;
    cin >> player1_name;
    cout << "Please enter a name for player 2" << endl;
    cin >> player2_name;
    while (playAgain == "y") { //runs if player wants to play (again), runs main game
        printGridWithNum();
        sizeRequest(answer);
        grid_setup(answer, grid);
        int playNineTimes = 0;
        cout << "Choose a box, " << player1_name << "!" << endl;
        while (winningConditions(answer, grid, moves) == false && playNineTimes < 9) {
            play(answer, grid, moves, player, player1, player2, player1_name, player2_name);
            playNineTimes ++;
        }
        if (playNineTimes == 9 && winningConditions(answer, grid, moves) == false) {
            cout << "dafuq? play better" << endl;
        }
        if (winningConditions(answer, grid, moves) == true) {
            cout << "Good shit!" << endl;
            if (player == player1) {
                cout << player2_name << " wins!" << endl;
            } else {
                cout << player1_name << " wins!" << endl;
            }
        }
        cout << "Would you like to play again?" << endl;
        cin >> playAgain;
        while (playAgain != "y" && playAgain != "n") { //lets player choose to play again (y/n)
            for (int i = 0; i <= playAgain.length(); i++) {
                playAgain[i] = tolower(playAgain[i]);
            }
            if (playAgain == "y" || playAgain == "yes"){
                playAgain = "y";
            } else if (playAgain == "n" || playAgain == "no") {
                playAgain = "n";
            } else {
                cout << "Please try again" << endl << "Type yes or no OR y or n" << endl;
                cin >> playAgain;
            }
            if (playAgain == "n") {
                exit(0);
            }
            
            }
        answer.clear();
        grid.clear();
        for (int i = 0; i < 9; i ++) {
        moves[i] = 0;
        }
        
    }
    return 0;
}

// draws grid (WOW)
void grid_draw (vector<string>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        cout << grid[i] << endl;
    }
}

// void function to setup grid with the proper size and setup grid vector
void grid_setup (string& answer, vector<string>& grid) {
    string row_small = "   |   |   ";
    string row_corner_small = "───┼───┼───";

    string row_medium = "         |         |         ";
    string row_corner_medium = "─────────┼─────────┼─────────";
    int length = 0;
    string row_large = "             |             |             ";
    string row_corner_large = "─────────────┼─────────────┼─────────────";
    string row;
    string row_corner;
    if (answer == "s") {
        length = 5;
        row_corner = row_corner_small;
        row = row_small;
    } else if (answer == "m") {
        length = 11;
        row_corner = row_corner_medium;
        row = row_medium;
    } else if (answer == "l") {
        length = 17;
        row_corner = row_corner_large;
        row = row_large;
    }
    int corner_1 = (length + 1)/3 - 1;
    int corner_2 = 2*(length + 1)/3 - 1;
    for (int i = 0; i < length; i++) {
        if (i == corner_1 || i == corner_2) {
            grid.push_back(row_corner);
        } else {
            grid.push_back(row);
        }
    }
    cout << endl;
}

// void function to let user choose board size
void sizeRequest (string& answer) {
    cout << "What size board would you like? (small, medium, or large OR s, m or l)" << endl;

    while (answer != "s" && answer != "m" && answer != "l") {
        cin >> answer;
        for (int i = 0; i <= answer.length(); i++) {
            answer[i] = tolower(answer[i]);
        }
        if (answer == "small" || answer == "s"){
            answer = "s";
        } else if (answer == "medium" || answer == "m") {
            answer = "m";
        } else if (answer == "large" || answer == "l") {
            answer = "l";
        } else {
             cout << "Please try again" << endl << "small, medium, or large OR s, m or l" << endl;
        }
    }
}

// tutorial grid, shows numbered boxes used to make moves
void printGridWithNum() {
    cout << " 1 ║ 2 ║ 3 " << endl;     
    cout << "═══╬═══╬═══" << endl;  
    cout << " 4 ║ 5 ║ 6 " << endl;            
    cout << "═══╬═══╬═══" << endl;
    cout << " 7 ║ 8 ║ 9 " << endl;
}

// big play function, finds size, draws x/o, handles basic input error, alternates players
void play(string& answer, vector<string>& grid, int moves[9], char& player, char& player1, char& player2, string& player1_name, string& player2_name) {
    int boxNum = 0;
    cin >> boxNum;
    while(boxNum > 9 || boxNum < 1) {
        cout << "The number must be between 1 and 9!" << endl;
        cin >> boxNum;
    }
    int length = 0;
    while (moves[boxNum - 1] != 0) {
        cout << "Sorry " << player1_name << ", that one's taken" << endl;
        cout << "Have another crack at it" << endl;
        cin >> boxNum;
    }
    
    int x;
    if (answer == "s") {
        length = 5;
        x = 1;
    } else if (answer == "m") {
        length = 11;
        x = 2;
    } else if (answer == "l") {
        length = 17;
        x = 3;
    }
    
    if (boxNum == 1) {
        grid[column(x, 0)][row(x, 0)] = player;
    } else if (boxNum == 2) {
        grid[column(x, 0)][row(x, 1)] = player;
    } else if (boxNum == 3) {
        grid[column(x, 0)][row(x, 2)] = player;
    } else if (boxNum == 4) {
        grid[column(x, 1)][row(x, 0)] = player;
    } else if (boxNum == 5) {
        grid[column(x, 1)][row(x, 1)] = player;
    } else if (boxNum == 6) {
        grid[column(x, 1)][row(x, 2)] = player;
    } else if (boxNum == 7) {
        grid[column(x, 2)][row(x, 0)] = player;
    } else if (boxNum == 8) {
        grid[column(x, 2)][row(x, 1)] = player;
    } else if (boxNum == 9) {
        grid[column(x, 2)][row(x, 2)] = player;
    }
    if (player == player1) {
        moves[boxNum - 1] = 1;
        player = player2;
        grid_draw(grid);
        if (winningConditions(answer, grid, moves) == false) {
        cout << "Choose a box, " << player2_name << "!" << endl;
        }
    } else {
        moves[boxNum - 1] = 2;
        player = player1;
        grid_draw(grid);
        if (winningConditions(answer, grid, moves) == false) {
        cout << "Choose a box, " << player1_name << "!" << endl;
        }
    }
}

// becomes true if either player achieves win condition
bool winningConditions (string& answer, vector<string>& grid, int moves[9]) {
    
    if (moves[0] == moves[1] && moves[0] == moves[2] && moves[0] != 0) {
        return true;
    }
    if (moves[3] == moves[4] && moves[3] == moves[5] && moves[3] != 0) {
        return true;
    }
    if (moves[6] == moves[7] && moves[6] == moves[8] && moves[6] != 0)  {
        return true;
    }
    if (moves[0] == moves[4] && moves[0] == moves[8] && moves[0] != 0) {
        return true;
    }
    if (moves[2] == moves[4] && moves[2] == moves[6] && moves[2] != 0) {
        return true;
    }
    if (moves[0] == moves[3] && moves[0] == moves[6] && moves[0] != 0) {
        return true;
    }
    if (moves[1] == moves[4] && moves[1] == moves[7] && moves[1] != 0) {
        return true;
    }
    if (moves[2] == moves[5] && moves[2] == moves[8] && moves[2] != 0) {
        return true;
    }
    return false;
}

// this was too hard for my smol brain
// calculate column coordinates for any size
int column (int size, int row) {
    return size - 1 + 2*size*row;
}

// this was too hard for my smol brain
// calculate row coordinates for any size
int row (int size, int column) {
     return (0.5*(-(pow(size, 2)) + 9*size - 6)) + ((2*(0.5*(-(pow(size, 2)) + 9*size - 6)))+2)*column;
}

//    ║   ║         
// ═══╬═══╬═══   
//  o ║ x ║ x            
// ═══╬═══╬═══
//  x ║ x ║ 0    


//     if (answer == "small") {
//         cout << "O";
//     } else if (answer == "medium") {
//         cout << "╭ ╮\n"
//                 "╰ ╯";
//     } else {
//         cout << "╭ - ╮" << endl;
//         cout << "|   |" << endl;
//         cout << "╰ - ╯";
//     }
// }

// void printX(string answer) {
//     answer = sizeRequest();
//     if (answer == "s") {
//         cout << "╳" << endl;
//     } else if (answer == "medium") {
//         cout << "\\ /" << endl;
//         cout << "╳" << endl;
//         cout << "/ \\" << endl;
//     } else {
//         cout << "\\  /" << endl;
//         cout << "\\ /" << endl;
//         cout << "╳" << endl;
//         cout << "/ \\" << endl;
//         cout << "/  \\" << endl;
//     }
// }


//    |   |   
// ───┼───┼───
//    |   |   
// ───┼───┼───
//    |   |   

//          |         |         
//          |         |         
//          |         |         
// ─────────┼─────────┼─────────
//          |         |         
//          |         |         
//          |         |         
// ─────────┼─────────┼─────────
//          |         |         
//          |         |         
//          |         |         

//              |             |             
//              |             |             
//              |             |             
//              |             |             
//              |             |             
// ─────────────┼─────────────┼─────────────
//              |             |             
//              |             |             
//              |             |             
//              |             |             
//              |             |             
// ─────────────┼─────────────┼─────────────
//              |             |             
//              |             |             
//              |             |             
//              |             |             
//              |             |             