#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include "fixture.h"
#include "global.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    Fixture fixture;

    if (argc <= 1)
    {
        MainWindow w;
        w.show();

        return a.exec();
    }
    else
    {
        QStringList names;
        for (int i = 1; i < argc; i++)
            names << QString(argv[i]);
        QString name = names.join(";");

        MainWindow w(0, true, name);
        w.show();

        return a.exec();
    }

}
