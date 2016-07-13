#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include "piece.h"
#include "logic.h"
#include <QMessageBox>

QTimer *timer;
Logic* boardlogic;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->grabKeyboard();
    // Connecting the timer
    speed = 350;
    boardlogic = new Logic(this);
    timer  = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(tmr_game()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 10; j++)
        {
            painter.setPen(QPen("#000000"));
            switch(boardlogic->Board[i][j])
            {
                case 0:
                    painter.setBrush(QBrush("#ffffff"));
                    break;
                case 1:
                    painter.setBrush(QBrush("#00ffff"));
                    break;
                case 2:
                    painter.setBrush(QBrush("#0000ff"));
                    break;
                case 3:
                    painter.setBrush(QBrush("#ffa500"));
                    break;
                case 4:
                    painter.setBrush(QBrush("#ffff00"));
                    break;
                case 5:
                    painter.setBrush(QBrush("#00ff00"));
                    break;
                case 6:
                    painter.setBrush(QBrush("#ff00ff"));
                    break;
                case 7:
                    painter.setBrush(QBrush("#ff0000"));
                    break;
            }

            painter.drawRect(j * 29 + 165, i * 29 + 10, 29, 29);

        }
    if (timer->isActive())
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                painter.setPen(QPen("#000000"));
                switch(boardlogic->CurrentPiece.PieceColor)
                {
                    case 0:
                        painter.setBrush(QBrush("#ffffff"));
                        break;
                    case 1:
                        painter.setBrush(QBrush("#00ffff"));
                        break;
                    case 2:
                        painter.setBrush(QBrush("#0000ff"));
                        break;
                    case 3:
                        painter.setBrush(QBrush("#ffa500"));
                        break;
                    case 4:
                        painter.setBrush(QBrush("#ffff00"));
                        break;
                    case 5:
                        painter.setBrush(QBrush("#00ff00"));
                        break;
                    case 6:
                        painter.setBrush(QBrush("#ff00ff"));
                        break;
                    case 7:
                        painter.setBrush(QBrush("#ff0000"));
                        break;
                }
                if (boardlogic->CurrentPiece.PieceArray[i][j])
                    painter.drawRect(165 + (boardlogic->CurrentPiece.X + j) * 29, 10 + (boardlogic->CurrentPiece.Y + i) * 29, 29, 29);

            }


}

void MainWindow::on_startButton_clicked()
{
    if (!timer->isActive()) {
        if (boardlogic->dropping)
            timer->start(50);
        else
            timer->start(speed);
    }
}

void MainWindow::on_pauseButton_clicked()
{
    timer->stop();
}

void MainWindow::on_stopButton_clicked()
{

    timer->stop();
    boardlogic = new Logic(this);
    ui->score->display(0);
    speed = 350;
    this->repaint();
}

void MainWindow::tmr_game()
{
    boardlogic->DropPiece();
    ui->score->display(boardlogic->score);
    this->repaint();

}

void MainWindow::reset_speed()
{
    timer->setInterval(speed);
}

void MainWindow::increase_speed()
{
    speed *= 0.95;
    timer->setInterval(speed);
}

void MainWindow::game_over()
{
    timer->stop();
    QMessageBox * msg = new QMessageBox(this);
    msg->setText("Game over!\nScore: " + QString::number(ui->score->value()));
    msg->show();
    on_stopButton_clicked();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (timer->isActive()) {
        switch(e->key())
        {
        case Qt::Key_Left:
            if (!boardlogic->dropping)
                if (boardlogic->PieceCanGoLeft()) boardlogic->CurrentPiece.X--;
            break;
        case Qt::Key_Right:
            if (!boardlogic->dropping)
                if (boardlogic->PieceCanGoRight()) boardlogic->CurrentPiece.X++;
            break;
        case Qt::Key_Up:
            if (!boardlogic->dropping)
                if (boardlogic->PieceCanRotate(boardlogic->rot < 3 ? boardlogic->rot + 1 : 0))
                {
                    if (boardlogic->rot < 3)
                        boardlogic->rot++;
                    else boardlogic->rot = 0;
                    boardlogic->ReloadPiece();
                }

            break;
        case Qt::Key_Down:
            if (!boardlogic->dropping)
            {
                boardlogic->dropping = true;
                timer->setInterval(50);
            }
            break;
        }
        this->repaint();
    }
}
