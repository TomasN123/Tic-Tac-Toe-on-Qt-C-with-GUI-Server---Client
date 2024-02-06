#include "game.h"
#include <QFile>
#include <QString>
#include <QDebug>
#include <QRegularExpression>
#include <algorithm>
#include "window_play.h"
#include <QTimer>
#include <QMovie>
#include <QThread>
#include <QMediaPlayer>

GAME::GAME()
{


}

QString GAME::displayRules() {              // Function to generate and return game rules as a string.
    QString rulesText;
    rulesText += "Game Rules:\n";
    rulesText += "1. The game is played on a grid that's 3 squares by 3 squares.\n";
    rulesText += "2. Player 1 is choosing between X/O and Player 2's icon based on \n   Player 1's choice. Players take turns putting their marks in empty squares.\n";
    rulesText += "3. The first player to get 3 of her marks in a row (up, down, \n   across, or diagonally) is the winner.\n";
    rulesText += "4. When all 9 squares are full, the game is over. If no player \n   has 3 marks in a row, the game ends in a tie.\n";
    return rulesText;
}


QString GAME::getSortedScoreboard() {                    // Function to read and sort scoreboard data from a file and return it as a formatted string.
    QFile inputFile("scoreboard.txt");
    QString sortedScoreboardText;

    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << " TOP   GAME";
        int rank = 1;

        QTextStream in(&inputFile);
        QList<QPair<QString, int>> scoreboardData;

        while (!in.atEnd()) {
            QString line = in.readLine();
            QRegularExpression re("(\\d+):(\\d+)");
            QRegularExpressionMatch match = re.match(line);

            if (match.hasMatch()) {
                int player1Score = match.captured(1).toInt();
                int player2Score = match.captured(2).toInt();
                int scoreDifference = qAbs(player1Score - player2Score);

                scoreboardData.append(QPair<QString, int>(line, scoreDifference));
            }
        }

        std::sort(scoreboardData.begin(), scoreboardData.end(), [](const QPair<QString, int>& a, const QPair<QString, int>& b) {
            return a.second > b.second;
        });

        for (const QPair<QString, int>& data : scoreboardData) {
            sortedScoreboardText += QString(" ") + (rank < 10 ? QString(" ") : QString()) + QString::number(rank) + "    " + data.first + "\n";
            rank++;
        }

        inputFile.close();
    } else {
        qDebug() << "Failed to open scoreboard.txt. Error: " << inputFile.errorString();
    }

    return sortedScoreboardText;
}


void GAME::sendRematch(QTcpSocket* socket, QByteArray& data)                                // Function to send a rematch request to the server.
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_3);
    out << QString("rematch");
    socket->write(data);
}

void GAME::send(QTcpSocket* socket, QByteArray& data, int i, int j)                         // Function to send the player's move (i, j) to the server.
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_3);
    out << QString("place") << i << j;
    socket->write(data);
}

void GAME::startTimerToHideLabel(window_play *windowPlay) {                                     // Function to create and start a timer for hiding a label and saving game data.
    QTimer *timer = new QTimer(windowPlay);                                                     // This timer is used to display a "Successful" message for a short time.
    // Set the time interval (in milliseconds) to hide the label after 3 seconds
    int displayDurationInSeconds = 4; // Adjust as needed
    timer->setInterval(displayDurationInSeconds * 1000); // Convert to milliseconds
    // Connect the timer to a slot that hides the label and saves game data
    QObject::connect(timer, &QTimer::timeout, [this, windowPlay]() {
        windowPlay->hideSuccessfulLabel();
    });

    // Start the timer
    timer->start();

}


