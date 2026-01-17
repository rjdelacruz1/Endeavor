#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Endeavor.h"
#include <QMovie>

class Endeavor : public QMainWindow
{
    Q_OBJECT

public:
    Endeavor(QWidget *parent = nullptr);
    ~Endeavor();

private:
    Ui::EndeavorClass ui;
    QMovie* introGif = nullptr; //with tetonic animation affect
    QMovie* finalGif = nullptr;
};

