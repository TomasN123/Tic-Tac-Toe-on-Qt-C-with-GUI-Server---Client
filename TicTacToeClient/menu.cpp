#include "menu.h"
#include "./ui_menu.h"
#include <QMovie>
#include <QThread>
#include <QLabel>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QDialog>
#include <QPixmap>
#include<QStylePainter>


Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    ui->label->setVisible(true);

    //Gif

    QMovie *movie = new QMovie(":/Img/GIF.gif");
    ui->label->setMovie(movie);
    ui->label->setFixedSize(100, 100);
    movie->setScaledSize(ui->label->size());
    movie->start();

}

Menu::~Menu()
{
    delete ui;

}


void Menu::on_Startgamebtn_clicked()
{

    hide();
    h6=new window_play(this);
    h6->show();
}

void Menu::on_Rules_clicked()
{
    hide();
    h2=new window_rules(this);
    h2->show();
}

void Menu::on_Scoreboard_clicked()
{
    hide();
    h5=new window_scoreboard(this);
    h5->show();
}

void Menu::on_Quit_clicked()
{
    QCoreApplication::quit();
}

void Menu::on_label_linkActivated(const QString &link)              //Gif
{

    QMovie *movie = new QMovie("C:/dev/GIF.gif");
    QLabel *label = new QLabel(this);
    label->setMovie(movie);
    movie->start();
}

void Menu::on_pushButton_clicked()                                  // Music
{
    //Background music
    QMediaPlayer *music = new QMediaPlayer();
    connect(music,&QMediaPlayer::mediaStatusChanged,music,&QMediaPlayer::play);
    music->setSource(QUrl("qrc:/Music/Elevatormusic.mp3"));
    music->play();

}
