#ifndef WINDOW_SCOREBOARD_H
#define WINDOW_SCOREBOARD_H

#include <QDialog>
#include <QLabel>
#include "game.h"


class Menu;

namespace Ui {
class window_scoreboard;
}

class window_scoreboard : public QDialog
{
    Q_OBJECT

public:
    explicit window_scoreboard(QWidget *parent = nullptr);
    ~window_scoreboard();

private slots:
    void on_Backbutton2_clicked();

private:
    Ui::window_scoreboard *ui;
    Menu *h4;
    GAME game;
    QString scoreboard();

};

#endif // WINDOW_SCOREBOARD_H
