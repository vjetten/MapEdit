#include "mainwindow.h"
#include "global.h"
#include "qwt_plot.h"
#include "qwt_scale_map.h"
#include "qwt_plot_magnifier.h"
//--------------------------------------------------------
void MainWindow::zoomPoint()
{
    double factor = 1.0;
    if (op.wd < 0)
        factor = 0.95;
    else
        factor = 1.05;

    for ( int axisPos = 0; axisPos < 4 /*QwtAxis::PosCount*/; axisPos++ )
    {
        QwtAxisId axisId( axisPos );

        const QwtScaleMap scaleMap = MPlot->canvasMap( axisId );

        double v1 = scaleMap.s1(); // scale interval boundaries
        double v2 = scaleMap.s2();

        double center;
        center = 0.5 * ( v1 + v2 );
        //qDebug() << axisPos <<  axisId  << center;
        if (axisPos  == 0 ) center = op.wy;
        if (axisPos  == 2 ) center = op.wx;

        v1 = center - (center-v1)*factor;
        v2 = center + (v2-center)*factor;
        if (axisPos % 2 == 0)
            MPlot->setAxisScale( axisId, v1, v2 );
    }

    MPlot->replot();
}

