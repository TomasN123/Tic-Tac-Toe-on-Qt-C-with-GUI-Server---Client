#include "window_rules.h"
#include "ui_window_rules.h"
#include "game.h"
#include <QtWidgets>
#include "menu.h" // Include the mainwindow.h header

window_rules::window_rules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window_rules)
{
    ui->setupUi(this);

    game.displayRules();
    QString rulesText = game.displayRules();
    ui->label->setText(rulesText);
}

window_rules::~window_rules()
{
    delete ui;
}

void window_rules::on_Backbutton_clicked()
{
    hide();
    h3=new Menu(this);
    h3->show();

}
