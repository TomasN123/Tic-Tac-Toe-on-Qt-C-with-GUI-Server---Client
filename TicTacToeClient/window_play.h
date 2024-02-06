#ifndef WINDOW_PLAY_H
#define WINDOW_PLAY_H

#include <QDialog>
#include <QTcpSocket>
#include <QHash>
#include <QPushButton>
#include <QPair>
#include <QDebug>
#include <game.h>
#include <QMediaPlayer>
#include <QMovie>
#include <QThread>

class Menu;

namespace Ui {
class window_play;
}

class window_play : public QDialog
{
    Q_OBJECT

public:
    explicit window_play(QWidget *parent = nullptr);
    ~window_play();

    void createBoard();
    void displayBoard(QVector<QVector<char>>&);
    void sendChatMessage(const QString& message);
    void saveGameDataToFile(const QString& fileName);
    void hideSuccessfulLabel();
    void updateNameLabel();
    void sendclickbuttondelay();
    void gif1clickdelay();
    void gif2clickdelay();
    void gif3clickdelay();
    void gif4clickdelay();
    void gif5clickdelay();
    void gif6clickdelay();
    void gif7clickdelay();
    void gif8clickdelay();
    int cross;
    void drawLine(int x1, int y1, int x2, int y2);
    void plotPoint(int x, int y);


private slots:
    void on_Backbutton3_clicked();

    void on_connectButton_clicked();

    void onCellClicked();

    void on_rematchButton_clicked();

    void on_SendnameButton_clicked();

    void on_Save_clicked();


private:
    Ui::window_play *ui;
    Menu *h7;
    QTcpSocket *socket;
    QByteArray data;
    QHash<QPushButton*, QPair<int, int>> coords;
    int gamesPlayed;
    int scorePlayer1;
    int scorePlayer2;
    int scorePlayer2for1;
    int scorePlayer1for2;
    int scoreid;
    bool isPlayerAllowedToMove;
    QString msg1;
    QString msg2;
    GAME* gameInstance;
public slots:
    void slotReadyRead();
};

#endif // WINDOW_PLAY_H
