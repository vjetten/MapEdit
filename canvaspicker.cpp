/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/
#include "mainwindow.h"
#include "canvaspicker.h"

//#include <qwt_plot.h>
//#include <qwt_plot_curve.h>

//#include <qevent.h>

CanvasPicker::CanvasPicker(QwtPlot *plot ):
    QObject( plot ),
    d_selectedPoint( -1 )
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

    switch( event->type() )
    {
        case QEvent::MouseButtonPress:
        {
            const QMouseEvent *mouseEvent = static_cast<QMouseEvent *>( event );
            select( mouseEvent->pos() );            
            return true;
        }
        case QEvent::MouseMove:
        {
            const QMouseEvent *mouseEvent = static_cast<QMouseEvent *>( event );
            move( mouseEvent->pos() );
            return true;
        }
        default:
            break;
    }

    return QObject::eventFilter( object, event );
}

// Select the point at a position. If there is no point
// deselect the selected point

void CanvasPicker::setRowCol(int nrr, int nrc, double dx)
{
    nrR = nrr;
    nrC = nrc;
    _dx = dx;
}


void CanvasPicker::select( const QPoint &pos )
{
    QRect rect = plot()->canvas()->rect();
//    double cf = (double)pos.x()/(double)rect.width() * nrC;
//    double rf = (1-(double)pos.y()/(double)rect.height()) * nrR;
//    int c = qFloor(cf) + 1;
//    int r = qFloor(rf) + 1;
 //   double dxf = (double)(rect.width()-16)/(double)(nrC*_dx);

    //double cf = plot()->invTransform(QwtPlot::xBottom,(double) pos.x()); //<= map coord
    //double rf = plot()->invTransform(QwtPlot::yLeft,(double) pos.y());
//    double ct = plot()->transform(QwtPlot::yLeft,cf);
//    double rt = plot()->transform(QwtPlot::yLeft,rf);
//    double ct = plot()->transform(QwtPlot::xBottom,nrC);
//    double rt = plot()->transform(QwtPlot::yLeft,nrR);
//    double c0 = plot()->transform(QwtPlot::xBottom,10.0);
//    double r0 = plot()->transform(QwtPlot::yLeft,0.0);
//    double r1 = plot()->transform(QwtPlot::yLeft,(double)nrR);
   // QPointF cr = plot()->invTransform(pos);

    int r = (int)qFloor(pos.y()/_dx);
    int c = (int)qFloor(pos.x()/_dx);

//    qDebug() << nrC << nrR<< pos.x() << pos.y() << c << r;// r0 << r1;//c0 << rt << ct;// << cr.y() << cr.x();



    QwtPlotItemList list = plot()->itemList(QwtPlotItem::Rtti_PlotSpectrogram);
    QwtPlotSpectrogram * sp0 = static_cast<QwtPlotSpectrogram *> (list.at(0));
    QwtPlotSpectrogram * sp1 = static_cast<QwtPlotSpectrogram *> (list.at(1));
    double z0 = 0, z1 = 0;
    if (sp0->data() != NULL)
        z0 = sp0->data()->value(pos.x(), pos.y());
    if (sp1->data() != NULL)
        z1 = sp1->data()->value(pos.x(), pos.y());

   qDebug() << "yes" << r << c << pos.y() << pos.x() << z0 << z1;

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
