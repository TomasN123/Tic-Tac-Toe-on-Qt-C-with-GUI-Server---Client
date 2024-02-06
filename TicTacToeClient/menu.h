#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "window_rules.h"
#include "window_scoreboard.h"
#include "window_play.h"
#include <QMovie>
#include <QThread>
#include <QLabel>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QUrl>

class window_rules;

QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    QMediaPlayer *music = new QMediaPlayer();
    ~Menu();

private slots:
    void on_Startgamebtn_clicked();

    void on_Rules_clicked();

    void on_Scoreboard_clicked();

    void on_Quit_clicked();

    void on_label_linkActivated(const QString &link);

    void on_pushButton_clicked();

private:
    Ui::Menu *ui;
    window_rules *h2;
    window_scoreboard *h5;
    window_play *h6;
};
#endif // MENU_H
