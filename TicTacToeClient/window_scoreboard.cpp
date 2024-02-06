#include "window_scoreboard.h"
#include "ui_window_scoreboard.h"
#include "menu.h"
#include "game.h"
#include <QString>


window_scoreboard::window_scoreboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window_scoreboard)
{
    ui->setupUi(this);
    QString scoreboardText = game.getSortedScoreboard();
    ui->label2->setText(scoreboardText);

}

window_scoreboard::~window_scoreboard()
{
    delete ui;
}

void window_scoreboard::on_Backbutton2_clicked()
{
    hide();
    h4 = new Menu(this);
    h4->show();
}
