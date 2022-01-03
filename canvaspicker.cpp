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
            if (op.clicks == 0) {
                op.polystart = 0;
            }
            if(op.editStop) {
                op.polystart = op.clicks;
                op.editStop = false;
            }
            select( mouseEvent->pos() );
            return true;
        }
        if (mouseEvent->button() == Qt::RightButton) {
            op.editStop = true;
//            op.polystart = op.clicks;//op.eData.size();
            return true;
        }

    }

    return QObject::eventFilter( object, event );
}


void CanvasPicker::select( const QPoint &pos )
{
    //double cy = _M->north();
    //double cx = _M->west();
    op.clicks++;

    double ri = plot()->invTransform(QwtPlot::yLeft,(double)pos.y());
    double ci = plot()->invTransform(QwtPlot::xBottom,(double)pos.x());

    int r = op.nrR - qFloor(ri/op._dx) - 1 ;
    int c = qFloor(ci/op._dx);

    showinfo(r,c,ri,ci);
    //emit signal

  //  qDebug() << pos.y() << pos.x() << r << c  << r2 << c2;


    if (op.editCell) {
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
    }
    if (op.editPolygon) {
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
    }
    if (op.editStop)
        emit draw();
}

void CanvasPicker::showinfo(int r, int c, int r1, int c1)
{
    QString txt = "[ 000, 000]=MV=[ 000000.00, 000000.00]";
    if (r >= 0 && r < op.nrR && c >= 0 && c < op.nrC && !pcr::isMV(op._M->data[r][c])) {
        txt = QString("[%1,%2]=%3").arg(r,4,10,0,' ').arg(c,4,10,0,' ').arg(op._M->data[r][c]);
        txt = txt + QString("=[%1,%2]").arg(r1,9,'f',2,' ').arg(c1,9,'f',2,' ');//pos.y()).arg(pos.x());
    }
    emit show(txt);
}

// Move the selected point
void CanvasPicker::move( const QPoint &pos )
{
    /*
    if ( d_selectedCurve == 0 || d_selectedPoint < 0  )
        return;

    QVector<double> xData( d_selectedCurve->dataSize() );
    QVector<double> yData( d_selectedCurve->dataSize() );

    double dx = 0.0;
    double dy = 0.0;

    int numPoints = static_cast<int>( d_selectedCurve->dataSize() );
    for ( int i = 0; i < numPoints; i++ )
    {
        const QPointF sample = d_selectedCurve->sample( i );

        if ( i == d_selectedPoint )
        {
            double x = plot()->invTransform(
                d_selectedCurve->xAxis(), pos.x() );
            double y = plot()->invTransform(
                d_selectedCurve->yAxis(), pos.y() );

            if ( d_sortedX )
            {
                if ( i > 0 )
                {
                    const double xMin = d_selectedCurve->sample( i - 1 ).x();
                    if ( x <= xMin )
                        x = xMin + 1;
                }

                if ( i < numPoints - 1 )
                {
                    const double xMax = d_selectedCurve->sample( i + 1 ).x();
                    if ( x >= xMax )
                        x = xMax - 1;
                }
            }

            xData[i] = x;
            yData[i] = y;

            dx = x - sample.x();
            dy = y - sample.y();
        }
        else
        {
            xData[i] = sample.x();
            yData[i] = sample.y();
        }
    }
    d_selectedCurve->setSamples( xData, yData );

    QwtPlotItemList curves = plot()->itemList( QwtPlotItem::Rtti_PlotCurve );
    for ( int i = 0; i < curves.size(); i++ )
    {
        QwtPlotCurve *curve = static_cast<QwtPlotCurve *>( curves[i] );
        if ( curve == d_selectedCurve )
            continue;

        xData.resize( curve->dataSize() );
        yData.resize( curve->dataSize() );

        numPoints = static_cast<int>( curve->dataSize() );
        for ( int j = 0; j < numPoints; j++ )
        {
            const QPointF sample = curve->sample( j );

            xData[j] = sample.x();
            yData[j] = sample.y();

            if ( j == d_selectedPoint )
            {
                xData[j] += dx;
                yData[j] += dy;
            }
        }
        curve->setSamples( xData, yData );
    }
*/
    plot()->replot();
}



#include "moc_canvaspicker.cpp"
