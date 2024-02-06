#include "gamelogic.h"

GameLogic::GameLogic(QVector<QVector<char>>& board) : board(board) {}


int GameLogic::checkWin() const {

    // Check rows
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == '.') continue;
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2]) return 1;
    }

    // Check columns
    for(int i = 0; i < 3; i++) {
        if(board[0][i] == '.') continue;
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i]) return 1;
    }

    // Check diagonals
    if(board[0][0] != '.' && board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        return 1;
    }if(board[0][2] != '.' && board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        return 1;
    }

    // Check if the game is drawn
    int cnt = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cnt += (board[i][j] == '.');
        }
    }
    if(!cnt) return 2;

    return 0;
}

void GameLogic::resetGame(int& gamesPlayed, int& turn, int& win, std::unordered_map<int, int>& rematch) {       // Reset game like clearing,resizing board and increment how many games was played
    board.clear();
    board.resize(3, QVector<char>(3, '.'));
    gamesPlayed++; // Increment gamesPlayed
    turn = win = 0;
    for (auto &[key, val] : rematch)
        val = 0; // Reset rematch map
}


void GameLogic::setCross(int& cross) {

    // Check rows
    if(board[0][0] != '.' && board[0][0] == board[0][1] && board[0][1] == board[0][2] )cross = 1;
    if(board[1][0] != '.' && board[1][0] == board[1][1] && board[1][1] == board[1][2] )cross = 2;
    if(board[2][0] != '.' && board[2][0] == board[2][1] && board[2][1] == board[2][2] )cross = 3;

    // Check columns

    if(board[0][0] != '.' && board[0][0] == board[1][0] && board[1][0] == board[2][0] ) cross = 4;
    if(board[0][1] != '.' && board[0][1] == board[1][1] && board[1][1] == board[2][1] ) cross = 5;
    if(board[0][2] != '.' && board[0][2] == board[1][2] && board[1][2] == board[2][2] ) cross = 6;

    // Check diagonals
    if(board[0][0] != '.' && board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        cross=7;
    }if(board[0][2] != '.' && board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        cross=8;
    }


}








