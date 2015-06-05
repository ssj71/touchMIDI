#include <QtGui/QApplication>
#include <QIcon>
#include "touchmidi.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("touchicon.svg"));

    TouchMIDI w;
    w.show();

    return a.exec();
}
