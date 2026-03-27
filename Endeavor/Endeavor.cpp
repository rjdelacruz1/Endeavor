#include "Endeavor.h"
#include "TasksWindow.h"
#include <QMovie>
#include <QLabel>

Endeavor::Endeavor(QWidget *parent)
    : QMainWindow(parent)
{
    //UI Starting Specifications
    ui.setupUi(this);
    setEndeavorWindowSpecifications();
    setEndeavorBanner();

    commands = new Commands(this);
    tasksWindow = new TasksWindow();
    logWindow = new LogWindow();

    setUpConnections();
}

void Endeavor::setEndeavorWindowSpecifications()
{
    this->resize(810, 200);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui.outputFrame->setFixedHeight(120);
    ui.output->setFrameStyle(QFrame::NoFrame);

    //Style Sheet Specs
    ui.centralWidget->setStyleSheet("background-color: #121212;");
    ui.commandEntry->setStyleSheet(R"(
        QLineEdit {
            background-color: #000000;
            color: #36BE1A;
            border: 1px solid #2e7d32;
            padding: 6px;
        }
    )");
    ui.outputFrame->setStyleSheet(R"(
        QFrame#outputFrame {
            border: 1px solid #2E7D32;
            background-color: #000000;
        }
    )");
    ui.output->setStyleSheet(R"(
            QPlainTextEdit#output {
                border: none;
                background: #000000;
                color: #36BE1A;
            }            

            QPlainTextEdit#output::viewport {
                background-color: #000000;
                color: #36BE1A;
            }
    
    )");
    
    ui.output->setReadOnly(true);
    ui.output->setFocusPolicy(Qt::NoFocus);
    ui.output->moveCursor(QTextCursor::End);
    ui.output->ensureCursorVisible();

    //Cursor starting point set to CommandEntry QLineEdit
    ui.commandEntry->setFocus();

    ui.commandEntry->installEventFilter(this);

    ui.commandEntry->setText("> ");
}
void Endeavor::setEndeavorBanner() 
{
    introGif = new QMovie(":/new/images/EndeavorBannerGif.gif", QByteArray(), this);
    finalGif = new QMovie(":/new/images/EndeavorBannerNoTetonicGif.gif", QByteArray(), this);

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
        if (total > 0 && frame == total - 1)
        {
            introGif->stop();
            ui.bannerLabel->setMovie(finalGif);
            finalGif->start();
        }
        });
}
void Endeavor::setUpConnections() {
    connect(ui.commandEntry, &QLineEdit::returnPressed, this, [this]() {
        QString text = ui.commandEntry->text();
        ui.commandEntry->clear();
        text.remove(0, 2);
        commands->handle(text);
        ui.commandEntry->setText("> ");
        ui.commandEntry->setCursorPosition(2);
        });

    connect(commands, &Commands::outputRequested, this, [this](const QString& line) {
        ui.output->appendPlainText("> " + line);
        });

    connect(commands, &Commands::tasksRequested, this, [this]() {
        //ui.output->appendPlainText("> ");
        tasksWindow->show();
        tasksWindow->raise();
        tasksWindow->activateWindow();
        });
    connect(commands, &Commands::logRequested, this, [this]() {
        logWindow->show();
        logWindow->raise();
        logWindow->activateWindow();
        });
    connect(commands, &Commands::exitRequested, this, &QWidget::close);
}
bool Endeavor::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == ui.commandEntry && event->type() == QEvent::KeyPress) {
        auto* keyEvent = static_cast<QKeyEvent*>(event);

        if (keyEvent->key() == Qt::Key_Backspace && ui.commandEntry->cursorPosition() <= 2)
            return true;

        if (keyEvent->key() == Qt::Key_Left && ui.commandEntry->cursorPosition() <= 2)
            return true;
    }

    return QMainWindow::eventFilter(obj, event);
}
void Endeavor::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        dragStartPosition = event->globalPosition().toPoint();
    }
}

void Endeavor::mouseMoveEvent(QMouseEvent* event){
    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = event->globalPosition().toPoint() - dragStartPosition;
        move(pos() + delta);
        dragStartPosition = event->globalPosition().toPoint();
    }
}

Endeavor::~Endeavor()
{}

