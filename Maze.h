#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Maze.h"
#include "Graf.h"
#include <queue>
class Maze : public QMainWindow
{
    Q_OBJECT

public:
    Maze(QWidget *parent = Q_NULLPTR);
    void paintEvent(QPaintEvent* event)override;
    void drawGraf(QPainter& painter);
    void drawBFS(QPainter& painter);
private:
    Ui::MazeClass ui;
    Graf graf;

private:
    void SetPathBack(uint16_t node);
    void drawPixels(QPainter& painter);
};
