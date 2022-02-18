#include<iostream>
#include<chrono>
#include<thread>
using namespace std::chrono_literals;

//* Spaces that the players have set (0 = none, 1 = X, 2 = O)
//* Do not change the first one
//* The first one is there to avoid having to
//* change 1 to 0 when a user inputs a number
int spaces[10] = {0,0,0,0,0,0,0,0,0,0};

int winningCombo[8][3] = {
    {1,2,3},
    {4,5,6},
    {7,8,9},
    {1,4,7},
    {2,5,8},
    {3,6,9},
    {1,5,9},
    {3,5,7}
};

bool playerOne = true;

bool hasPlayerWon = false;
bool isPlayerOneWin = false;

void start();
void reset();
void displayBoard();
void chooseSpace();
void setSpace(int num, bool isPlayerOne);
void checkWin();
void winScreen();
void drawScreen();

int main()
{
    start();
    return 0;
}

//* Resets the game and starts again
void start() {
    reset();
    displayBoard();
}

//* Clear the board
void reset() {
    for (int i = 1; i < 10; i++) {
        spaces[i] = 0;
    }
    playerOne = true;
    hasPlayerWon = false;
}

//* Display letters to board
void displayBoard() {
    if(hasPlayerWon == true) {
        return;
    }

    std::string boardSpace[10] = {"-","-","-","-","-","-","-","-","-","-"};

    //* Turn numbers into letter or dash
    for(int i = 1; i < 10; i++) {
        if (spaces[i] == 0) {
            boardSpace[i] = "-";
        } else if(spaces[i] == 1) {
            boardSpace[i] = "X";
        } else if(spaces[i] == 2) {
            boardSpace[i] = "O";
        }
    }
    //* The actual board
    std::cout << "      |     |     \n   " << boardSpace[1] <<"  |  " << boardSpace[2] <<"  |  "<< boardSpace[3] <<"  \n _____|_____|_____\n      |     |     \n   " << boardSpace[4] <<"  |  " << boardSpace[5] <<"  |  " << boardSpace[6] <<"  \n _____|_____|_____\n      |     |     \n   " << boardSpace[7] <<"  |  " << boardSpace[8] <<"  |  " << boardSpace[9] <<"  \n      |     |     \n";
    checkWin();
    chooseSpace();
}

//* Ask player what space they choose and set the number and call setSpace()
void chooseSpace() {
    int spaceChosen;
    if(playerOne) {
        std::cout << "Player One, choose move (number between 1 and 9) \n";
        std::cin >> spaceChosen;
        playerOne = false;
        setSpace(spaceChosen, true);
    } else {
        std::cout << "Player Two, choose move (number between 1 and 9) \n";
        std::cin >> spaceChosen;
        playerOne = true;
        setSpace(spaceChosen, false);
    }
}

//* Take player input and set space
void setSpace(int num, bool isPlayerOne) {
    if(isPlayerOne) {
        if(spaces[num] == 0 && num <= 9 && num > 0) {
            spaces[num] = 1;
        } else {
            std::cout << "\n\n\n\n\nThat spot is taken or does not exist\n\n\n\n\n";
            std::this_thread::sleep_for(1s);
            playerOne = true;
            displayBoard();
        }
    } else {
        if(spaces[num] == 0 && num <= 9 && num > 0) {
            spaces[num] = 2;
        } else {
            std::cout << "\n\n\n\n\nThat spot is taken or does not exist\n\n\n\n\n";
            std::this_thread::sleep_for(1s);
            playerOne = false;
            displayBoard();
        }
    }
    displayBoard();
}

void checkWin() {
    for(int i = 0; i < 8; i++) {
        if(spaces[winningCombo[i][0]] == 1 && spaces[winningCombo[i][1]] == 1 && spaces[winningCombo[i][2]] == 1) {
            isPlayerOneWin = true;
            hasPlayerWon = true;
            winScreen();
        } else if(spaces[winningCombo[i][0]] == 2 && spaces[winningCombo[i][1]] == 2 && spaces[winningCombo[i][2]] == 2) {
            isPlayerOneWin = false;
            hasPlayerWon = true;
            winScreen();
        } else if((spaces[1] != 0) && (spaces[2] != 0) && (spaces[3] != 0) && (spaces[4] != 0) && (spaces[5] != 0) && (spaces[6] != 0) && (spaces[7] != 0) && (spaces[8] != 0) && (spaces[9] != 0)) {
            drawScreen();
        }
    }
}

void winScreen() {
    if(isPlayerOneWin == true) {
        std::cout << "\n\n\n\n\nPlayer One Wins!\nRestarting...\n\n\n";
        std::this_thread::sleep_for(5s);
        reset();
        displayBoard();
    } else {
        std::cout << "\n\n\n\n\nPlayer Two Wins!\nRestarting...\n\n\n";
        std::this_thread::sleep_for(5s);
        reset();
        displayBoard();
    }
    
}

void drawScreen() {
    std::cout << "\n\n\n\n\nIt's a draw!\nRestarting...\n\n\n";
    std::this_thread::sleep_for(5s);
    reset();
    displayBoard();
}