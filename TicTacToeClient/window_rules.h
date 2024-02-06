#ifndef WINDOW_RULES_H
#define WINDOW_RULES_H

#include <QDialog>

#include "game.h"

class Menu;

namespace Ui {
class window_rules;
}

class window_rules : public QDialog
{
    Q_OBJECT

public:
    explicit window_rules(QWidget *parent = nullptr);
    ~window_rules();

private slots:
    void on_Backbutton_clicked();

private:
    Ui::window_rules *ui;
    GAME game;
    Menu *h3;
};

#endif // WINDOW_RULES_H
