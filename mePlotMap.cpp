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

  //  MPlot->enableAxis( MPlot->yRight );
  //  MPlot->enableAxis( MPlot->yLeft );

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


 //   QwtLinearScaleEngine scaleEngine;

    rightAxis = new QwtScaleWidget(this);
    //rightAxis = MPlot->axisWidget( MPlot->yRight );
    rightAxis->setAlignment( QwtScaleDraw::RightScale );
    rightAxis->setColorBarEnabled( true );
 //   rightAxis->setColorBarWidth( 16 );
 //   rightAxis->setMargin(8);
    rightAxis->setTitle( QwtText("edit map") );

    leftAxis = new QwtScaleWidget(this);
    //leftAxis = MPlot->axisWidget( MPlot->yLeft);
    leftAxis->setAlignment( QwtScaleDraw::RightScale );
    leftAxis->setColorBarEnabled( true );
  //  leftAxis->setColorBarWidth( 16 );
  //  leftAxis->setMargin(8);
    leftAxis->setTitle( QwtText("base map") );

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

    layout_Map->insertWidget(0,leftAxis, 0);
    layout_Map->insertWidget(1, MPlot, 1);
    layout_Map->insertWidget(2,rightAxis,0 );


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
    if (minV == maxV) {
        minV = maxV-1;
    }
 //   qDebug() << minV << maxV;
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
    palette1nr = -1;
    changePalette(0);

    double res = fillDrawMapData(baseRMap, RDb, &MinV1, &MaxV1);
    RDb->setInterval( Qt::ZAxis, QwtInterval( MinV1, MaxV1));
    baseMap->setData(RDb);

    baseMap->setAlpha(255);
    baseMap->setColorMap(bpalette);
    MPlot->setAxisAutoScale(MPlot->xBottom, true);

    interval = baseMap->data()->interval( Qt::ZAxis );
    leftAxis->setColorMap( interval, bpalette1);
    leftAxis->setScaleDiv(scaleEngine.divideScale( interval.minValue(), interval.maxValue(),10,5) );
}
//---------------------------------------------------------------------------
void MainWindow::showBaseMap()
{
// show base map with new spin values

    RDb->setInterval( Qt::ZAxis, QwtInterval( MinV1, MaxV1));
    baseMap->setData(RDb);
    interval = baseMap->data()->interval( Qt::ZAxis );
    leftAxis->setColorMap( interval, bpalette1);
    leftAxis->setScaleDiv(scaleEngine.divideScale( interval.minValue(), interval.maxValue(),10,5) );
    // adjust legend to new spin values
}
//---------------------------------------------------------------------------
void MainWindow::initTopMap()
{
    palette2nr = 0;
    changePalette(1);

    double res = fillDrawMapData(topRMap, RD, &MinV2, &MaxV2);
    RD->setInterval( Qt::ZAxis, QwtInterval(MinV2,MaxV2));
    drawMap->setData(RD);

    drawMap->setColorMap(dpalette);
    drawMap->setAlpha(200);
    MPlot->setAxisAutoScale(MPlot->xBottom, true);

    interval = drawMap->data()->interval( Qt::ZAxis );
    rightAxis->setColorMap( interval, dpalette1);
    rightAxis->setScaleDiv(scaleEngine.divideScale( interval.minValue(), interval.maxValue(),10,5) );
}
//---------------------------------------------------------------------------
void MainWindow::showTopMap()
{
    double ma = MaxV2; //(MaxV2 <= -1e20 ? 0 : MaxV2);//
    double mi = MinV2;// (MinV2 <= -1e20 ? 0 : MinV2);//MinV2;

    RD->setInterval( Qt::ZAxis, QwtInterval(mi,ma));//
    drawMap->setData(RD);
    interval = drawMap->data()->interval( Qt::ZAxis );
    rightAxis->setColorMap( interval, dpalette1);
    rightAxis->setScaleDiv(scaleEngine.divideScale( interval.minValue(), interval.maxValue(),10,5) );
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
//---------------------------------------------------------------------------
void MainWindow::changePalette(int nr)
{
    if (op._M == nullptr)
        return;
    if (nr == 0){
        palette2nr++;
        if (palette2nr > 5)
            palette2nr = 0;

        switch (palette2nr) {
        case (0):
            bpalette = new colorMapGray();
            bpalette1 = new colorMapGray();
            break;
        case (1):
            bpalette = new colorMapRainbow();
            bpalette1 = new colorMapRainbow();
            break;
        case(2):
            bpalette = new colorMap2();
            bpalette1 = new colorMap2();
            break;
        case(3):
            bpalette = new colorMap3();
            bpalette1 = new colorMap3();
            break;
        case(4):
            bpalette = new colorMap4();
            bpalette1 = new colorMap4();
            break;
        case(5):
            bpalette = new colorMap1();
            bpalette1 = new colorMap1();
            break;
        }
    }
    if (nr == 1){
        palette1nr++;
        if (palette1nr > 5)
            palette1nr = 0;

        switch (palette1nr) {
        case (0):
            dpalette = new colorMapGray();
            dpalette1 = new colorMapGray();
            break;
        case (1):
            dpalette = new colorMapRainbow();
            dpalette1 = new colorMapRainbow();
            break;
        case(2):
            dpalette = new colorMap2();
            dpalette1 = new colorMap2();
            break;
        case(3):
            dpalette = new colorMap3();
            dpalette1 = new colorMap3();
            break;
        case(4):
            dpalette = new colorMap4();
            dpalette1 = new colorMap4();
            break;
        case(5):
            dpalette = new colorMap1();
            dpalette1 = new colorMap1();
            break;
        }
    }

}
