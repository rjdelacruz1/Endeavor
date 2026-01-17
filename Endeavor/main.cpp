#include "Endeavor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Endeavor window;
    window.show();
    return app.exec();
}
