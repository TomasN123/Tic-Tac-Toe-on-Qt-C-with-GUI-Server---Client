#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <unordered_map>
#include "gamelogic.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    void sendGamesPlayed();
    int cross;
    int sendcross;

private:
    QVector<QTcpSocket*> sockets;
    QVector<int> id;
    QVector<int> id2;
    QVector<QVector<char>> board;
    std::unordered_map<int, int> rematch;
    QByteArray data;

    void send();
    void send2();
    void newGame();
    void deleteConnection();

    int turn;
    int win;
    int gamesPlayed;
    int scorePlayer1;
    int scorePlayer2;
    int scorePlayer2for1 =0;
    int scorePlayer1for2 =0 ;
    int scoreid;


    QString msg1;
    QString msg2;
    GameLogic* gameLogic;



public slots:
    void incomingConnection(qintptr descriptor);
    void slotReadyRead();
};

#endif // SERVER_H
