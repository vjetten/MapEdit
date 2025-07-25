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

    if (event->type() == QEvent::Wheel) {
        QWheelEvent *wEvent = static_cast<QWheelEvent  *>( event );
        op.wd = wEvent->angleDelta().y() < 0 ? -1 : 1;
        double ri = plot()->invTransform( QwtAxis::YLeft,wEvent->position().y());
        double ci = plot()->invTransform(QwtAxis::XBottom,wEvent->position().x());
        op.wy = ri;
        op.wx = ci;

        emit zoom();
        return true;
    }

    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>( event );

        double ri = plot()->invTransform( QwtAxis::YLeft,(double)mouseEvent->pos().y());// - op._lly;
        double ci = plot()->invTransform(QwtAxis::XBottom,(double)mouseEvent->pos().x());// - op._llx;
        //when mouse in LL corner op_llx = pos.x()
        int r = op.nrR - qFloor((ri- op._lly)/op._dx) - 1;
        int c = qFloor((ci- op._llx)/op._dx);
        //qDebug() << op._llx << op._lly << ci << ri;
        showinfo(r,c,ri,ci);

        if (QGuiApplication::queryKeyboardModifiers() == Qt::ControlModifier)
            return QObject::eventFilter( object, event );
        // if ctrl mouse is pressed give it back for panning

        if (mouseEvent->button() == Qt::LeftButton) {


            if (op.editCell)
                op.editStop = true;

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

//            if (!op.editStart)
//                return QObject::eventFilter( object, event );

//            return true;
        }

        if (mouseEvent->button() == Qt::RightButton) {

            if (!op.editStart)
                return QObject::eventFilter( object, event );
            op.editStop = true;
            return true;
        }

    }

    return QObject::eventFilter( object, event );
}


void CanvasPicker::select( const QPoint &pos )
{
    if (op._M == nullptr)
        return;

    op.clicks++;

    double ri = plot()->invTransform( QwtAxis::YLeft,(double)pos.y()) - op._lly;
    double ci = plot()->invTransform(QwtAxis::XBottom,(double)pos.x()) - op._llx;
    // real coordinates

    int r = op.nrR - qFloor(ri/op._dx) - 1 ;
    int c = qFloor(ci/op._dx);

  //  showinfo(r,c,ri,ci);

    if (!op.editStop) {
        if (r >= 0 && r < op.nrR && c >= 0 && c < op.nrC) {
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

void CanvasPicker::showinfo(int r, int c, int ri, int ci)
{
  //  if (r < 0 || c < 0)
  //      return;

    QString txt;
    QString txtcoor = QString("(%1,%2)=").arg((double)ri,9,'f',2,' ').arg((double)ci,9,'f',2,' ');
    QString txtrc = QString("[%1,%2]=").arg(r,4,10,' ').arg(c,4,10,' ');
    QString txtv;
//qDebug() << txtcoor << txtrc;
    txtv = "Base[MV] - Edit[MV]";
    if (r >= 0 && r < op.nrR && c >= 0 && c < op.nrC && !pcr::isMV(op._M->data[r][c])) {
        double v = op._M->data[r][c];
        double vb = op._Mb->data[r][c];
        if (v > -1e19)
            txtv = QString("Base[%1] - Edit[%2]").arg(vb).arg(v);
        else
            txtv = QString("Base[%1] - Edit[MV]").arg(vb);
    }
    txt = txtcoor + txtrc + txtv;

    emit show(txt);

}

// Move the selected point
void CanvasPicker::move( const QPoint &pos )
{
        if (op._M == nullptr)
            return;

    //    double ri = plot()->invTransform( QwtAxis::YLeft,(double)pos.y());
    //    double ci = plot()->invTransform(QwtAxis::XBottom,(double)pos.x());

    //    int r = op.nrR - qFloor(ri/op._dx) - 1 ;
    //    int c = qFloor(ci/op._dx);

    //    showinfo(r,c,ri,ci);
}



#include "moc_canvaspicker.cpp"
