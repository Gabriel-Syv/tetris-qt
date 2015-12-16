#ifndef LOGIC_H
#define LOGIC_H
#include <QString>
#include <QBrush>
#include "piece.h"
#include "mainwindow.h"
class Logic
{
public:
    Logic(MainWindow*);
    void InitPiece();
    void ReloadPiece();
    bool PieceIsBlocked();
    void DropPiece();
    void Gameover();
    void RowFull();
    void BlockPiece();
    bool PieceCanGoRight();
    bool PieceCanGoLeft();
    bool PieceCanRotate(int);

    QString PIECES;

    int Board[22][12];
    Piece CurrentPiece;
    bool gameover;
    bool dropping;
    int rot;
    int piece;
    int score;


};

#endif // LOGIC_H
