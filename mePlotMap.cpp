#include "mainwindow.h"
#include "global.h"


//---------------------------------------------------------------------------
void MainWindow::ssetAlpha(int v)
{
    drawMap->setAlpha(v);

    MPlot->replot();
}
//----------------------------------------------------------------------------------------
void MainWindow::setupMapPlot()
{
    MPlot = new QwtPlot(title, this);
    layout_Map->insertWidget(1, MPlot, 0);

    MPlot->enableAxis( MPlot->yRight );
    MPlot->enableAxis( MPlot->yLeft );

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
    drawMap->attach( MPlot );
    // NOTE the order in which these are attached is the order displayed.

    RD = new QwtMatrixRasterData();
    RDb = new QwtMatrixRasterData();
    // raster data to link to plot

    rightAxis = new QwtScaleWidget();
    rightAxis = MPlot->axisWidget( MPlot->yRight );
    rightAxis->setColorBarEnabled( true );
    rightAxis->setColorBarWidth( 16 );
    rightAxis->setMargin(8);
    rightAxis->setBorderDist(64, 64);
    MPlot->setAxisScaleEngine( MPlot->yRight, new QwtLinearScaleEngine() );
    MPlot->setAxisScale( MPlot->yRight, 0,1);
  //  MPlot->setAxisAutoScale(MPlot->yRight, true);

    leftAxis = new QwtScaleWidget();
    leftAxis = MPlot->axisWidget( MPlot->yLeft);
    leftAxis->setColorBarEnabled( true );
    leftAxis->setColorBarWidth( 16 );
    leftAxis->setMargin(8);
    leftAxis->setBorderDist(64,64);
    MPlot->setAxisScaleEngine( MPlot->yLeft, new QwtLinearScaleEngine() );
    MPlot->setAxisAutoScale(MPlot->yLeft, true);

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
double MainWindow::fillDrawMapData(cTMap *_M, QwtMatrixRasterData *_RD, double *minv, double *maxv)
{
    double maxV = -1e18;
    double minV = 1e18;
    QVector<double> mapData;
    mapData.clear();  //QVector double

    if (_M == NULL)
        return (maxV);

    // copy map data into vector for the display structure
    for(int r = _nrRows-1; r >= 0; r--)
        for(int c=0; c < _nrCols; c++)
        {
            if(!pcr::isMV(baseRMap->data[r][c]))
            {
                mapData << _M->Drc;
                if (_M->Drc != -1e20) {
                    maxV = std::max(maxV, _M->Drc);
                    minV = std::min(minV, _M->Drc);
                }

            }
            else
                mapData << (double)-1e20;
        }

    if (minV == 1e18 && maxV == -1e18) {
        minV = 0;
        maxV = 0;
    }
    qDebug() << minV << maxV;
    *maxv = maxV;
    *minv = minV;

    _RD->setValueMatrix( mapData, _nrCols );
    // set column number to divide vector into rows


  //  double cy = _M->north();
  //  double cx = _M->west();

//    _RD->setInterval( Qt::XAxis, QwtInterval( cx,cx+_nrCols*_dx, QwtInterval::ExcludeMaximum ) );
 //   _RD->setInterval( Qt::YAxis, QwtInterval( cy,cy+_nrRows*_dx, QwtInterval::ExcludeMaximum ) );


    _RD->setInterval( Qt::XAxis, QwtInterval( 0, (double)_nrCols*_dx, QwtInterval::ExcludeMaximum ) );
    _RD->setInterval( Qt::YAxis, QwtInterval( 0, (double)_nrRows*_dx, QwtInterval::ExcludeMaximum ) );
    // set x/y axis intervals
    return maxV;
}
//---------------------------------------------------------------------------
void MainWindow::initBaseMap()
{
//    bpalette = new colorMapRainbow();
//    bpalette1 = new colorMapRainbow();
    bpalette = new colorMapGray();
    bpalette1 = new colorMapGray();

    double res = fillDrawMapData(baseRMap, RDb, &MinV1, &MaxV1);
    RDb->setInterval( Qt::ZAxis, QwtInterval( MinV1, MaxV1));
    baseMap->setData(RDb);

    baseMap->setAlpha(255);
    baseMap->setColorMap(bpalette);
    MPlot->setAxisAutoScale(MPlot->xBottom, true);

    leftAxis->setColorMap( baseMap->data()->interval( Qt::ZAxis ), bpalette1);
    MPlot->setAxisScale( MPlot->yLeft, MinV1, MaxV1);
    MPlot->setAxisScaleEngine( MPlot->yLeft, new QwtLinearScaleEngine() );
}
//---------------------------------------------------------------------------
void MainWindow::showBaseMap()
{
// show base map with new spin values

    RDb->setInterval( Qt::ZAxis, QwtInterval( MinV1, MaxV1));
    baseMap->setData(RDb);
    leftAxis->setColorMap( baseMap->data()->interval( Qt::ZAxis ), bpalette1);
    MPlot->setAxisScale( MPlot->yLeft, MinV1, MaxV1);

    // adjust legend to new spin values
}
//---------------------------------------------------------------------------
void MainWindow::initTopMap()
{
   // dpalette = new colorMapGray();
  //  dpalette1 = new colorMapGray();
    dpalette = new colorMapRainbow();
    dpalette1 = new colorMapRainbow();

    double res = fillDrawMapData(topRMap, RD, &MinV2, &MaxV2);
    RD->setInterval( Qt::ZAxis, QwtInterval(MinV2,MaxV2));
    drawMap->setData(RD);

    drawMap->setColorMap(dpalette);
    drawMap->setAlpha(128);
  //  MPlot->setAxisAutoScale(MPlot->xBottom, true);

    rightAxis->setColorMap( drawMap->data()->interval( Qt::ZAxis ), dpalette1);
    MPlot->setAxisAutoScale(MPlot->yRight, true);

}
//---------------------------------------------------------------------------
void MainWindow::showTopMap()
{

    double ma = MaxV2; //(MaxV2 <= -1e20 ? 0 : MaxV2);//
    double mi = MinV2;// (MinV2 <= -1e20 ? 0 : MinV2);//MinV2;

    RD->setInterval( Qt::ZAxis, QwtInterval(mi,ma));//
    drawMap->setData(RD);
    rightAxis->setColorMap( drawMap->data()->interval( Qt::ZAxis ), dpalette1);
    MPlot->setAxisScale( MPlot->yRight, mi,ma);
}

//---------------------------------------------------------------------------
void MainWindow::setMinTopMap()
{
    MinV1 = spinMinV->value();
    MaxV1 = spinMaxV->value();
    if (MinV1 == 0) MinV1 = MinTop;
    if (MaxV1 == 0) MaxV1 = MaxTop;

    showBaseMap();
  //  showTopMap();

    MPlot->replot();
}
