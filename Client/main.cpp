#include "fakeclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FakeClient w;
    w.show();
    return a.exec();
}
