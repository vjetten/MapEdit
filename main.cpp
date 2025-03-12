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

    // Echo arguments to the console
    QStringList arguments = QCoreApplication::arguments();
    qDebug() << "Command-line arguments:";
    for (int i = 0; i < arguments.size(); ++i) {
        qDebug() << QString("arg[%1]: %2").arg(i).arg(arguments[i]);
    }

    if (argc <= 1)
    {
        printf("hoi\n");
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
