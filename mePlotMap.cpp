#include "mainwindow.h"
#include "global.h"


//---------------------------------------------------------------------------
void MainWindow::ssetAlpha(int v)
{
    //drawMap->setAlpha(v);

    MPlot->replot();
}
//----------------------------------------------------------------------------------------
void MainWindow::setupMapPlot()
{
    MPlot = new QwtPlot(title, this);
    // make the plot window
    layout_Map->insertWidget(1, MPlot, 0);
    // put it on screen
    MPlot->enableAxis( MPlot->yRight );

    // attach plot to widget in UI
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen( QPen( Qt::DotLine ) );
    grid->attach( MPlot );

    baseMap = new QwtPlotSpectrogram();
    baseMap->setRenderThreadCount( 0 );
    baseMap->attach( MPlot );
    // shaded relief base map

    drawMap = new QwtPlotSpectrogram();
    drawMap->setRenderThreadCount( 0 );
 //   drawMap->attach( MPlot );
    // NOTE the order in which these are attached is the order displayed.

    RD = new QwtMatrixRasterData();
    RDb = new QwtMatrixRasterData();
    // raster data to link to plot

    rightAxis = new QwtScaleWidget();
    rightAxis = MPlot->axisWidget( MPlot->yRight );
    rightAxis->setColorBarEnabled( true );
    rightAxis->setColorBarWidth( 24 );
    rightAxis->setMargin(8);
    rightAxis->setBorderDist(64, 64);
    // legend to the right of the plot

    magnifier = new QwtPlotMagnifier( MPlot->canvas() );
    magnifier->setAxisEnabled( MPlot->yRight, false );
    magnifier->setMouseButton( Qt::NoButton );
    // exclude right axis legend from rescaling
    magnifier->setZoomInKey(Qt::Key_Plus, Qt::ShiftModifier);
    magnifier->setZoomOutKey(Qt::Key_Minus, Qt::NoModifier );
    magnifier->setZoomInKey(Qt::Key_Plus, Qt::KeypadModifier);
    magnifier->setZoomOutKey(Qt::Key_Minus, Qt::KeypadModifier);

    panner = new QwtPlotPanner( MPlot->canvas() );
    panner->setAxisEnabled( MPlot->yRight, false );
    panner->setMouseButton( Qt::LeftButton, Qt::ControlModifier );
    // exclude right axis legend from panning

    // correct square aspect ratio
    mapRescaler = new QwtPlotRescaler( MPlot->canvas() );
    mapRescaler->setAspectRatio( QwtPlot::xBottom, 1.0 );
    mapRescaler->setAspectRatio( QwtPlot::yRight, 0.0 );
    mapRescaler->setAspectRatio( QwtPlot::xTop, 0.0 );
    mapRescaler->setExpandingDirection( QwtPlotRescaler::ExpandUp );

    cpicker = new CanvasPicker( MPlot );

    connect(cpicker, SIGNAL(show(QString)),this, SLOT(Show(QString)));
    connect(cpicker, SIGNAL(draw()),this, SLOT(drawSelection()));
    connect(cpicker, SIGNAL(get()),this, SLOT(getCells()));

}
//---------------------------------------------------------------------------

// fill the current raster data structure with new data, called each run step
double MainWindow::fillDrawMapData(cTMap *_M, QwtMatrixRasterData *_RD, double type, double *minv, double *maxv)
{
    double maxV = -1e20;
    double minV = 1e20;
    QVector<double> mapData;
    mapData.clear();

    if (_M == NULL)
        return (maxV);

    // copy map data into vector for the display structure
    for(int r = _nrRows-1; r >= 0; r--)
        for(int c=0; c < _nrCols; c++)
        {
            if(!IS_MV_REAL8(&_M->Drc) || _M->Drc <=-1e20)
            {
                mapData << _M->Drc;
                maxV = qMax(maxV, _M->Drc);
                minV = qMin(minV, _M->Drc);
            }
            else
                mapData << (double)-1e20;
        }
    *maxv = maxV;
    *minv = minV;

    _RD->setValueMatrix( mapData, _nrCols );
    // set column number to divide vector into rows

//    double cy = _M->north();
//    double cx = _M->west();

//     _RD->setInterval( Qt::XAxis, QwtInterval( cx,cx+_nrCols*_dx, QwtInterval::ExcludeMaximum ) );
 //   _RD->setInterval( Qt::YAxis, QwtInterval( cy,cy+_nrRows*_dx, QwtInterval::ExcludeMaximum ) );


    _RD->setInterval( Qt::XAxis, QwtInterval( 0, _nrCols*_dx, QwtInterval::ExcludeMaximum ) );
    _RD->setInterval( Qt::YAxis, QwtInterval( 0, _nrRows*_dx, QwtInterval::ExcludeMaximum ) );
    // set x/y axis intervals
    return maxV;
}

//---------------------------------------------------------------------------
void MainWindow::initBaseMap()
{
//    bpalette = new colorMapGray();
//    bpalette1 = new colorMapGray();
    bpalette = new colorMapRainbow();
    bpalette1 = new colorMapRainbow();

    double res = fillDrawMapData(baseRMap, RDb, 0, &MinV1, &MaxV1);

    baseMap->setAlpha(255);
    baseMap->setColorMap(bpalette);
    RDb->setInterval( Qt::ZAxis, QwtInterval( MinV1, MaxV1));
    baseMap->setData(RDb);
    // setdata sets a pointer to DRb to the private QWT d_data Qvector

    rightAxis->setColorMap( baseMap->data()->interval( Qt::ZAxis ), bpalette);

    MPlot->setAxisScale( MPlot->yRight, MinV1, MaxV1);
    MPlot->setAxisScaleEngine( MPlot->yRight, new QwtLinearScaleEngine() );

    // set spins
//    MinTop = MinV1;
//    MaxTop = MaxV1;

//    spinMinV->setMinimum(MinTop);
//    spinMinV->setMaximum(MaxTop);
//    spinMaxV->setMinimum(MinTop);
//    spinMaxV->setMaximum(MaxTop);
//    spinMinV->setValue(MinTop);
//    spinMaxV->setValue(MaxTop);
//    if ((MaxTop-MinTop) < 10)
//    {
//        spinMinV->setDecimals(3);
//        spinMaxV->setDecimals(3);
//        spinMinV->setSingleStep(0.001);
//        spinMaxV->setSingleStep(0.001);
//    }
}
//---------------------------------------------------------------------------
void MainWindow::showBaseMap()
{
    baseMap->setAlpha(255);
    baseMap->setColorMap(bpalette);
    RDb->setInterval( Qt::ZAxis, QwtInterval( MinV1, MaxV1));
    baseMap->setData(RDb);

    rightAxis->setColorMap( baseMap->data()->interval( Qt::ZAxis ), bpalette);
    MPlot->setAxisScale( MPlot->yRight, MinV1, MaxV1);
    MPlot->setAxisScaleEngine( MPlot->yRight, new QwtLinearScaleEngine() );
}
//---------------------------------------------------------------------------
void MainWindow::setMinTopMap()
{
    MinV1 = spinMinV->value();
    MaxV1 = spinMaxV->value();
    if (MinV1 == 0) MinV1 = MinTop;
    if (MaxV1 == 0) MaxV1 = MaxTop;

    showBaseMap();
//    showTopMap();

    MPlot->replot();
}
//---------------------------------------------------------------------------
void MainWindow::initTopMap()
{
    dpalette = new colorMapRainbow();
    dpalette1 = new colorMapRainbow();

    double res = fillDrawMapData(topRMap, RD, 0, &MinV2, &MaxV2);
    if (MinV2<=1e-20) MinV2 = 0;
    if (MaxV2<=1e-20) MaxV2 = 1;

    MPlot->setAxisAutoScale(MPlot->yRight, true);
    MPlot->setAxisAutoScale(MPlot->xBottom, true);
    MPlot->setAxisAutoScale(MPlot->yLeft, true);

    drawMap->setAlpha(128);
}
//---------------------------------------------------------------------------
void MainWindow::showTopMap()
{
    drawMap->setColorMap(dpalette);
    RD->setInterval( Qt::ZAxis, QwtInterval( MinV2, MaxV2));

    drawMap->setData(RD);

    rightAxis->setColorMap( drawMap->data()->interval( Qt::ZAxis ), dpalette1);
    MPlot->setAxisScale( MPlot->yRight, MinV2, MaxV2);
    MPlot->setAxisScaleEngine( MPlot->yRight, new QwtLinearScaleEngine() );

}
