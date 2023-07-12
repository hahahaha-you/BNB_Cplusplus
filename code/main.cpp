#include "app/bombapp.h"
#include <QObject>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BombApp app;
    app.initialize();
    app.show();
    return a.exec();
}
