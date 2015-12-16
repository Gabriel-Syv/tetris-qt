#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void reset_speed();
    void increase_speed();
    void game_over();
private slots:
    void on_startButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent*);
    int speed;
public slots:
    void tmr_game();
protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // MAINWINDOW_H
