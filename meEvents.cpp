#include "mainwindow.h"

//---------------------------------------------------------------

void MainWindow::moved( const QPoint &pos )
{
    QString info( "Freq=%1, Ampl=%2, Phase=%3" );
    info = info.arg( MPlot->invTransform( QwtPlot::xBottom, pos.x() ) );
    info = info.arg( MPlot->invTransform( QwtPlot::yLeft, pos.y() ) );
    info = info.arg( MPlot->invTransform( QwtPlot::yRight, pos.y() ) );

   qDebug() << info ;
}

void MainWindow::selected( const QPolygon & )
{
    qDebug() << "oei";
   // showInfo();
}

//bool MainWindow::eventFilter(QObject *obj, QEvent *event)
//{

//    if (event->type() == QEvent::KeyPress) {
//        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
//        qDebug() << "hoi" << keyEvent->key();
//    }

//    if (event->type() == QEvent::QEvent::MouseButtonPress) {
//        QMouseEvent* me = (QMouseEvent*)event;
//        if (me->buttons() & Qt::LeftButton != 0) {
//          qDebug() <<"left";
////            eData <<
//        }

//    }


/*
    switch(event->type())
    {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
        {
            QMouseEvent* me = (QMouseEvent*)event;
            bool ok = event->type() == QEvent::MouseMove ? ((me->buttons() & Qt::LeftButton) != 0) : (me->button() == Qt::LeftButton);
            if(ok)
            {
                float x = float(me->x())/width();
                float y = float(me->y())/height();
                //OnTouch(x, y, event->type() != QEvent::MouseButtonRelease, 0);
                return true;
            }
        }
        return true;
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
        {
            QTouchEvent* te = (QTouchEvent*)event;
            foreach(const QTouchEvent::TouchPoint& p, te->touchPoints())
            {
                float x = p.pos().x()/width();
                float y = p.pos().x()/height();
               // OnTouch(x, y, p.state() != Qt::TouchPointReleased, p.id());
            }
        }
        return true;
    default:
        return QWidget::event(event);
    }

*/
  //  return QMainWindow::eventFilter(obj, event);
//}

//---------------------------------------------------------------

