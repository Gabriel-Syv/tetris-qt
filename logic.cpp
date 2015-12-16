#include "logic.h"
#include "mainwindow.h"
#include <ctime>
#include <iostream>

MainWindow* main_app;
int num_lines = 0;

Logic::Logic(MainWindow* context)
{
    PIECES = "1111000000000000100010001000100011110000000000001000100010001000100011100000000011001000100000001110001000000000010001001100000000101110000000001000100011000000111010000000000011000100010000001100110000000000110011000000000011001100000000001100110000000000011011000000000010001100010000000110110000000000100011000100000001001110000000001000110010000000111001000000000001001100010000001100011000000000010011001000000011000110000000000100110010000000";
    gameover = false;
    dropping = false;
    main_app = context;
    score = 0;
    for (int i = 0; i < 22; i++)
        for (int j = 0; j < 12; j++)
            Board[i][j] = 0;
    InitPiece();

}

void Logic::InitPiece()
{
    std::time_t result = std::time(0);
    srand(result);
    rot = rand() % 4;
    piece = rand() % 7;

    CurrentPiece.PieceColor = piece + 1;

    CurrentPiece.X = 3;
    CurrentPiece.Y = 0;

    int s = piece * (16 * 4) + rot * 16;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            CurrentPiece.PieceArray[i][j] = PIECES[s] == '0' ? false : true;
            s++;
        }
}

void Logic::ReloadPiece()
{
    int s = piece * (16 * 4) + rot * 16;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            CurrentPiece.PieceArray[i][j] = PIECES[s] == '0' ? false : true;
            s++;
        }
}

bool Logic::PieceIsBlocked()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (CurrentPiece.PieceArray[i][j] && Board[CurrentPiece.Y + i + 1][CurrentPiece.X + j] != 0)
                return true;
            if (CurrentPiece.PieceArray[i][j] && i + CurrentPiece.Y + 1 == 20) return true;

        }
    return false;
}

void Logic::DropPiece()
{
    if (!PieceIsBlocked() && !gameover)
        CurrentPiece.Y++;
    else if (gameover)
    {

    }
    else
    {
        BlockPiece();
        Gameover();
        RowFull();
        InitPiece();
    }



}

void Logic::Gameover()
{
    for (int i = 0; i < 10; i++)
        if (Board[0][i] != 0)
        {
            gameover = true;
            main_app->game_over();
            break;
        }

}

void Logic::RowFull()
{
    for (int k = 19; k >= 1; k--)
    {
        int c = 0;
        for (int i = 0; i < 10; i++)
            if (Board[k][i] != 0)
                c++;
        if (c == 10)
        {
            for (int i = k; i >= 1; i--)
                for (int j = 0; j < 10; j++)
                    Board[i][j] = Board[i - 1][j];
            score += 100;
            k++;
            num_lines++;
            if (num_lines % 5 == 0)
                main_app->increase_speed();
        }
    }
}

void Logic::BlockPiece()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (CurrentPiece.PieceArray[i][j])
                Board[CurrentPiece.Y + i][CurrentPiece.X + j] = CurrentPiece.PieceColor;

        }
    if (dropping)
    {
        main_app->reset_speed();
        dropping = false;
    }
    score += 10;
}

bool Logic::PieceCanGoRight()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (CurrentPiece.PieceArray[i][j])
            {
                if (CurrentPiece.X + j + 1 == 10) return false;
                if (Board[CurrentPiece.Y + i][CurrentPiece.X + j + 1] != 0) return false;
            }


        }
    return true;
}

bool Logic::PieceCanGoLeft()
{
    if (CurrentPiece.X == 0) return false;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (CurrentPiece.PieceArray[i][j])
            {
                if (CurrentPiece.X + j - 1 >= 0)
                    if (Board[CurrentPiece.Y + i][CurrentPiece.X + j - 1] != 0) return false;
            }


        }
    return true;
}

bool Logic::PieceCanRotate(int piece_rot)
{
    int s = piece * (16 * 4) + piece_rot * 16;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            bool b = PIECES[s] == '0' ? false : true;
            if (b)
            {
                if (i + CurrentPiece.Y > 19) return false;
                if (j + CurrentPiece.X > 9) return false;
                if (Board[i + CurrentPiece.Y][j + CurrentPiece.X] != 0) return false;
            }
            s++;
        }
    return true;
}
