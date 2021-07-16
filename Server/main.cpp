#include "fakeserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FakeServer w;
    w.show();
    return a.exec();
}
