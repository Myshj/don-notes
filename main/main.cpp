#include "main-window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    don::notes::MainWindow w;
    w.show();

    return a.exec();
}
