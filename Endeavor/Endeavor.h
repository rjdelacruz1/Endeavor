#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Endeavor.h"
#include "Commands.h"
#include <QMovie>
#include <QPoint>
#include <QMouseEvent>


class Endeavor : public QMainWindow
{
    Q_OBJECT

public:
    Endeavor(QWidget *parent = nullptr);
    ~Endeavor();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    Ui::EndeavorClass ui;
    Commands* commands = nullptr;
    void setEndeavorWindowSpecifications();
    void setEndeavorBanner();
    
    //For displaying custom banner
    QMovie* introGif = nullptr; //with tetonic animation affect
    QMovie* finalGif = nullptr;

    //For dragging borderless window
    QPoint dragStartPosition;
};

