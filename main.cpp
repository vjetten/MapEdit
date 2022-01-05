#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include "fixture.h"
#include "global.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    Fixture fixture; // for gdal


    if (argc <= 1)
    {
        MainWindow w;
        w.show();

        return a.exec();
    }
    else
    {
        QString allnames;
        QStringList names;
        if (argc > 1)
        {
            names << QString(argv[1]);
        }
        if (argc > 2)
        {
            names << QString(argv[2]);
        }
        allnames = names.join(";");

        MainWindow w(0, true, allnames);
        w.show();

        return a.exec();
    }

}
