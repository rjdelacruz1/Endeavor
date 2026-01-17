#include "Endeavor.h"
#include <QMovie>
#include <QLabel>

Endeavor::Endeavor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->resize(810, 200);
    
    introGif = new QMovie(":/new/images/EndeavorBannerGif.gif",QByteArray(),this);
    finalGif = new QMovie(":/new/images/EndeavorBannerNoTetonicGif.gif",QByteArray(),this);

    QSize bannerSize = introGif->frameRect().size();
    QSize bannerWindowSize(bannerSize.width() + 10, bannerSize.height() + 5);
    
    //ui.bannerLabel->setMinimumSize(bannerWindowSize);
    ui.bannerLabel->resize(800, 100);
    ui.commandEntry->resize(800, 25);
    

    ui.bannerLabel->setMovie(introGif);
    ui.bannerLabel->setScaledContents(true);
    introGif->start();

    connect(introGif, &QMovie::frameChanged, this, [this](int frame) {
        int total = introGif->frameCount();
        if(total>0 && frame == total-1)
        {
            introGif->stop();
            ui.bannerLabel->setMovie(finalGif);
            finalGif->start();
        }
        });
}

Endeavor::~Endeavor()
{}

