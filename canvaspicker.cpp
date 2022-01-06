/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/
#include "mainwindow.h"
#include "global.h"

CanvasPicker::CanvasPicker(QwtPlot *plot ):
    QObject( plot )
{
    plot->canvas()->installEventFilter( this );
}

QwtPlot *CanvasPicker::plot()
{
    return qobject_cast<QwtPlot *>( parent() );
}

const QwtPlot *CanvasPicker::plot() const
{
    return qobject_cast<const QwtPlot *>( parent() );
}

bool CanvasPicker::eventFilter( QObject *object, QEvent *event )
{
    if ( plot() == NULL || object != plot()->canvas() )
        return false;
    if (op._M == NULL)
        return false;

//    if (event->type() == QEvent::KeyPress) {
//        QKeyEvent *keyEvent = static_cast<QKeyEvent *>( event );
//        qDebug() << keyEvent;
//    }

    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>( event );

        if (QGuiApplication::queryKeyboardModifiers() == Qt::ControlModifier)
            return QObject::eventFilter( object, event );
        // if ctrl mouse is pressed give it back for panning

        if (mouseEvent->button() == Qt::LeftButton) {
            if (op.editRectangle && op.clicks % 2 == 0)
                op.editStop = true;

            if (op.clicks == 0)
                op.polystart = 0;

            if(op.editStop) {
                // editSTop given by right mouseclick, start new curve
                op.polystart = op.clicks;
                op.editStop = false;
            }
            select( mouseEvent->pos() );
            return true;
        }
        if (mouseEvent->button() == Qt::RightButton) {
            if (!op.editStart)
                return QObject::eventFilter( object, event );
            op.editStop = true;
            return true;
        }

    }
    qDebug() << event->type();
    if (event->type() == QEvent::MouseMove)
    {
        const QMouseEvent *mouseEvent = static_cast<QMouseEvent *>( event );
        qDebug() << mouseEvent->pos() ;
        move( mouseEvent->pos() );
        return true;
    }

    return QObject::eventFilter( object, event );
}


void CanvasPicker::select( const QPoint &pos )
{
    if (op._M == nullptr)
        return;

    //double cy = _M->north();
    //double cx = _M->west();
    op.clicks++;

    double ri = plot()->invTransform(QwtPlot::yLeft,(double)pos.y());
    double ci = plot()->invTransform(QwtPlot::xBottom,(double)pos.x());

    int r = op.nrR - qFloor(ri/op._dx) - 1 ;
    int c = qFloor(ci/op._dx);

    showinfo(r,c,ri,ci);

    if (!op.editStop) {
        if (r >= 0 && r < op.nrR && c >= 0 && c < op.nrC && !pcr::isMV(op._M->data[r][c])) {
            xyzLIST cr;
            cr.cy = (op.nrR-r-1)*op._dx + 0.5*op._dx;
            cr.cx = c*op._dx + 0.5*op._dx;
            cr.r = r;
            cr.c = c;
            cr.v = op._M->data[r][c];
            op.eData << cr;

            emit draw();
        }
    }
    if (op.editStop)
        emit get();
}

void CanvasPicker::showinfo(int r, int c, int r1, int c1)
{
    QString txt = "[ 000, 000]=MV=[ 000000.00, 000000.00]";
    if (r >= 0 && r < op.nrR && c >= 0 && c < op.nrC && !pcr::isMV(op._M->data[r][c])) {
        double v = op._M->data[r][c];
        if (v < -1e19)
            txt = QString("[%1,%2]=MV").arg(r,4,10,0,' ').arg(c,4,10,0,' ');
        else
            txt = QString("[%1,%2]=%3").arg(r,4,10,0,' ').arg(c,4,10,0,' ').arg(v);
        txt = txt + QString("=[%1,%2]").arg(r1,9,'f',2,' ').arg(c1,9,'f',2,' ');//pos.y()).arg(pos.x());
    }
    emit show(txt);
}

// Move the selected point
void CanvasPicker::move( const QPoint &pos )
{
    if (op._M == nullptr)
        return;

    double ri = plot()->invTransform(QwtPlot::yLeft,(double)pos.y());
    double ci = plot()->invTransform(QwtPlot::xBottom,(double)pos.x());

    int r = op.nrR - qFloor(ri/op._dx) - 1 ;
    int c = qFloor(ci/op._dx);

    showinfo(r,c,ri,ci);
}



#include "moc_canvaspicker.cpp"
