#include "window_play.h"
#include "ui_window_play.h"
#include "menu.h"
#include "game.h"
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QMediaPlayer>


window_play::window_play(QWidget *parent) : QDialog(parent)
{
    ui = new Ui::window_play;
    ui->setupUi(this);


    // Hide ui labels
    ui->p1s->hide();
    ui->p2s->hide();
    ui->label_6->hide();
    ui->label_7->show();
    ui->line->hide();
    ui->line_2->hide();
    ui->line_3->hide();
    ui->line_5->hide();
    ui->line_6->hide();
    ui->line_7->hide();
    ui->label_9->hide();
    ui->label_8->hide();
    ui->turnLabel->hide();
    ui->Save->hide();
    ui->label_11->hide();
    ui->label_12->hide();
    ui->label_13->hide();
    ui->label_14->hide();
    ui->label_16->hide();
    ui->label_17->hide();
    ui->label_18->hide();
    ui->label_19->hide();
    ui->label_3->hide();
    ui->me_name_label->hide();
    ui->label_4->hide();
    ui->Game->hide();


    //Background music
    QMediaPlayer *music = new QMediaPlayer();
    connect(music,&QMediaPlayer::mediaStatusChanged,music,&QMediaPlayer::play);
    music->setSource(QUrl("qrc:/Music/Elevatormusic.mp3"));
    music->play();

    setWindowTitle("Tic Tac Toe Client");
    setFixedSize(size());

    createBoard();

    // Initialize the TCP socket
    socket = new QTcpSocket;

    // Connect signals and slots for the socket
    connect(socket, &QTcpSocket::readyRead, this, &window_play::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    // Initialize player permission and UI elements
    isPlayerAllowedToMove = false;
    ui->SendnameButton->setEnabled(false);
    ui->Save->setEnabled(false);
    ui->rematchButton->hide();

    gameInstance = new GAME();

}

window_play::~window_play()
{
    socket->disconnectFromHost();
    delete ui;

}

void window_play::createBoard()                                                     // Function to create the game board with buttons
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            auto button = new QPushButton;
            button->setFixedHeight(90);
            button->setFixedWidth(90);
            button->setFont(QFont("Times", 27, QFont::Bold));
            ui->gridLayout->addWidget(button, i, j);
            button->show();
            coords[button] = {i, j};
            connect(button, &QPushButton::clicked, this, &window_play::onCellClicked);
        }
}

void window_play::displayBoard(QVector<QVector<char> > &board)                      // Function to display the game board on the UI with the current state.
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            auto button = dynamic_cast<QPushButton*>
                (ui->gridLayout->itemAtPosition(i, j)->widget());
            button->setText((board[i][j] == '.') ? QString() : QChar(board[i][j]));
        }
}

void window_play::on_Backbutton3_clicked()                                          // Function to handle the "Back" button click event.
{
    hide();
    h7=new Menu(this);
    h7->show();
}

void window_play::updateNameLabel()                                                 // Function to update the UI label with a message about setting a nickname.
{
    if (ui->write_name_Edit->isReadOnly()) {
        ui->Doyouhavename_label->setText("");
    } else {ui->Doyouhavename_label->setText("You can set your nick now.");
    }
}

void window_play::on_SendnameButton_clicked()                                       // Function to handle the "Send Name" button click event.
{                                                                                   // It sends the entered name and allows the player to make a move
    if (!ui->write_name_Edit->text().isEmpty()) {
        QString message = ui->write_name_Edit->text();
        ui->SendnameButton->setDisabled(true);
        sendChatMessage(message);
        ui->write_name_Edit->setReadOnly(true);
        isPlayerAllowedToMove = true;

        ui->Doyouhavename_label->setText("");
        ui->me_name_label->setText(message);
        ui->SendnameButton->hide();
        ui->write_name_Edit->hide();

        ui->ipLine->hide();
        ui->portLine->hide();
        ui->label->hide();
        ui->label_2->hide();
        ui->label_7->hide();

        ui->p1s->show();
        ui->p2s->show();
        ui->label_6->show();
        ui->line_7->hide();
        ui->label_5->hide();
        ui->Save->show();

        ui->turnLabel->show();
        ui->label_3->show();
        ui->me_name_label->show();
        ui->Doyouhavename_label->hide();
        ui->Game->show();


    }
}


void window_play::on_connectButton_clicked()                              // Function to handle the "Connect" button click event.
{                                                                         // It connects or disconnects from the server based on the current state.
    qDebug() << socket->state();
    if (socket->state() == QTcpSocket::ConnectedState)
    {
        socket->disconnectFromHost();
        socket->deleteLater();
        socket = new QTcpSocket;
        ui->connectButton->setText("Connect");

    }
    else
    {
        QString ip = ui->ipLine->text();
        QString port = ui->portLine->text();
        ui->connectButton->setText("Connecting...");
        socket->connectToHost(ip, port.toInt());

        if (socket->waitForConnected())
        {

           ui->connectButton->hide();
           ui->portLine->hide();
           ui->ipLine->hide();
           ui->label->hide();
           ui->label_2->hide();

        }
        else
        {
            ui->connectButton->setText("Connect");
            qDebug() << "Connection failed";
        }
    }
}

void window_play::on_rematchButton_clicked()                                    // Function to handle the "Rematch" button click event.
{                                                                               // It initiates a rematch offer and updates the UI.

    ui->rematchButton->setText("Offer sent");
    ui->rematchButton->setEnabled(0);
    gameInstance->sendRematch(socket, data);
    ui->label_11->hide();
    ui->label_12->hide();
    ui->label_13->hide();
    ui->label_14->hide();
    ui->label_16->hide();
    ui->label_17->hide();
    ui->label_18->hide();
    ui->label_19->hide();
}

void window_play::onCellClicked()                                               // Function to handle a button click event on the game board.
{
    if (isPlayerAllowedToMove) {
        auto pos = coords[dynamic_cast<QPushButton*>(sender())];
        gameInstance->send(socket, data, pos.first, pos.second);
    }
}

void window_play::slotReadyRead()                                               // Function to handle incoming data from the server.
 {                                                                              // It updates the game board, game state, and other UI elements.
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_3);

    if (in.status() != QDataStream::Ok)
    {
        qDebug() << "Error reading";
        return;
    }

    QVector<QVector<char>> board;
    int turn, win;                                                              // in - receiveing
    in >> board >> turn >> win;
    in >>cross;
    displayBoard(board);

    in >> gamesPlayed;
    in >> scorePlayer1;
    in >> scorePlayer2;
    in >> scoreid;
    in >> msg1;
    in >> msg2;


    ui->label_3->setText(msg1);


    if (scoreid)                                                                //My and Enemy score
    {
        ui->p1s->setText(QString::number(scorePlayer2));
        ui->p2s->setText(QString::number(scorePlayer1));
    }
    else
    {
        ui->p1s->setText(QString::number(scorePlayer1));
        ui->p2s->setText(QString::number(scorePlayer2));
    }

    ui->Game->setText("Games Played: " + QString::number(gamesPlayed));


    if (win == 2)
    {
        ui->turnLabel->setText("Draw");
    }
    else if (win == 1)
    {

        if(cross == 6){ui->line->show();  gif3clickdelay();                    // If player won, it's shows crossing out on board
        }if(cross == 5){ui->line_2->show();  gif2clickdelay();
        }if(cross == 4){ui->line_3->show();  gif1clickdelay();
        }if(cross == 1){ui->line_5->show();  gif4clickdelay();
        }if(cross == 2){ui->line_6->show();  gif5clickdelay();
        }if(cross == 3){ui->line_7->show();  gif6clickdelay();
        }if(cross == 7){ui->label_8->show(); gif7clickdelay();
        }if(cross == 8){ui->label_9->show(); gif8clickdelay();
        }

        ui->turnLabel->setText(turn ? "You lost" : "You won");

    }
    else
    {
        if (gamesPlayed == 1)
        {
            ui->SendnameButton->setEnabled(true);
            updateNameLabel();
            ui->turnLabel->setText(turn ? "Your turn" : "Enemy turn");


        }
        else
        {
            ui->turnLabel->setText(turn ? "Your turn" : "Enemy turn");
        }
    }

    if (win)
    {
        ui->rematchButton->show();
        ui->rematchButton->setText("Rematch");
        ui->rematchButton->setEnabled(1);
        ui->Save->setEnabled(true);

    }
    else
    {
        ui->rematchButton->hide();
        ui->line->hide();
        ui->line_2->hide();
        ui->line_3->hide();
        ui->line_5->hide();
        ui->line_6->hide();
        ui->line_7->hide();
        ui->label_9->hide();
        ui->label_8->hide();
    }
}

void window_play::sendChatMessage(const QString& message)                       // Function to send a chat message to the server using for changing names.
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_3);
    out << QString("chat") << message;
    socket->write(data);
}

void window_play::saveGameDataToFile(const QString& fileName) {                 // Function to save game data, including the score,moves and player names to a file.
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);

        if (scoreid) {
            out << QString::number(scorePlayer2);
            out << ":" << QString::number(scorePlayer1);
            out << "   ";
            QString enemyName = ui->me_name_label->text();
            out << " " << enemyName;
            out << "  vs  ";
            out << msg1;
        } else {
            out << QString::number(scorePlayer1);
            out << ":" << QString::number(scorePlayer2);
            out << "   ";
            QString enemyName = ui->me_name_label->text();
            out << " " << enemyName;
            out << "  vs  ";
            out << msg1;
        }

        out << "\n";
        file.close();
    }
}

void window_play::sendclickbuttondelay() {                                             // It saves the game data and shows a success message.
    QString fileName = "scoreboard.txt";
    saveGameDataToFile(fileName);
    gameInstance->startTimerToHideLabel(this);
    ui->label_4->show();
    ui->label_4->setText("Successful");


}

void window_play::gif1clickdelay(){                                                     //Gif 1 row


    QMovie *movie = new QMovie(":/Img/GIF.gif");
    ui->label_11->setMovie(movie);
    ui->label_11->setFixedSize(200, 300);
    movie->setScaledSize(ui->label_11->size());
    ui->label_11->show();

    gameInstance->startTimerToHideLabel(this);
    movie->start();

}
void window_play::gif2clickdelay(){                                                      //Gif 2 row


    QMovie *movie2 = new QMovie(":/Img/GIF.gif");
    ui->label_12->setMovie(movie2);
    ui->label_12->setFixedSize(200, 300);
    movie2->setScaledSize(ui->label_12->size());
    ui->label_12->show();

    gameInstance->startTimerToHideLabel(this);
    movie2->start();

}
void window_play::gif3clickdelay(){                                                      //Gif 3 row


    QMovie *movie3 = new QMovie(":/Img/GIF.gif");
    ui->label_13->setMovie(movie3);
    ui->label_13->setFixedSize(200, 300);
    movie3->setScaledSize(ui->label_13->size());
    ui->label_13->show();

    gameInstance->startTimerToHideLabel(this);
    movie3->start();

}

void window_play::gif4clickdelay(){                                                      //Gif 1 coulumn


    QMovie *movie4 = new QMovie(":/Img/GIF2.gif");
    ui->label_14->setMovie(movie4);
    ui->label_14->setFixedSize(300, 200);
    movie4->setScaledSize(ui->label_14->size());
    ui->label_14->show();

    gameInstance->startTimerToHideLabel(this);
    movie4->start();

}

void window_play::gif5clickdelay(){                                                      //Gif 2 coulumn


    QMovie *movie5 = new QMovie(":/Img/GIF2.gif");
    ui->label_16->setMovie(movie5);
    ui->label_16->setFixedSize(300, 200);
    movie5->setScaledSize(ui->label_16->size());
    ui->label_16->show();

    gameInstance->startTimerToHideLabel(this);
    movie5->start();

}

void window_play::gif6clickdelay(){                                                      //Gif 3 coulumn


    QMovie *movie6 = new QMovie(":/Img/GIF2.gif");
    ui->label_17->setMovie(movie6);
    ui->label_17->setFixedSize(300, 200);
    movie6->setScaledSize(ui->label_17->size());
    ui->label_17->show();

    gameInstance->startTimerToHideLabel(this);
    movie6->start();

}

void window_play::gif7clickdelay(){                                                      //Gif diagonal left


    QMovie *movie7 = new QMovie(":/Img/gif_diagonal_left.gif");
    ui->label_18->setMovie(movie7);
    ui->label_18->setFixedSize(300, 300);
    movie7->setScaledSize(ui->label_18->size());
    ui->label_18->show();

    gameInstance->startTimerToHideLabel(this);
    movie7->start();

}

void window_play::gif8clickdelay(){                                                      //Gif diagonal right


    QMovie *movie8 = new QMovie(":/Img/gif_diagonal_right.gif");
    ui->label_19->setMovie(movie8);
    ui->label_19->setFixedSize(300, 300);
    movie8->setScaledSize(ui->label_19->size());
    ui->label_19->show();

    gameInstance->startTimerToHideLabel(this);
    movie8->start();

}



void window_play::on_Save_clicked()                                                     // Show label and start timer for hide
{
    sendclickbuttondelay();
    ui->label_4->show();
}

void window_play::hideSuccessfulLabel()                                                 // Function to hide the success message label on the UI.
{
    ui->label_4->hide();
    ui->label_11->hide();
    ui->label_12->hide();
    ui->label_13->hide();
    ui->label_14->hide();
    ui->label_16->hide();
    ui->label_17->hide();
    ui->label_18->hide();
    ui->label_19->hide();
}




