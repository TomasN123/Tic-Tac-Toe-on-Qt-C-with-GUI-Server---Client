#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <QVector>

class GameLogic {
public:



    GameLogic(QVector<QVector<char>>& board);
    int checkWin() const;

    void resetGame(int& gamesPlayed, int& turn, int& win, std::unordered_map<int, int>& rematch);
    void setCross(int& cross);
private:
    QVector<QVector<char>>& board;

};



#endif // GAME_LOGIC_H
