#include "mainwindow.h"
#include "global.h"


//----------------------------------------------------------------------------------------
void MainWindow::setupMapPlot()
{
    MPlot = new QwtPlot();
    MPlot->setAutoReplot(true);

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen( QPen( Qt::DotLine ) );
    //grid->setXDiv()
    grid->attach( MPlot );

    baseMap = new QwtPlotSpectrogram();
    baseMap->setRenderThreadCount( 0 );
 //   baseMap->setCachePolicy( QwtPlotRasterItem::PaintCache ); <=== does not do changes immediately but cashes them!
    baseMap->attach( MPlot );

    drawMap = new QwtPlotSpectrogram();
    drawMap->setRenderThreadCount( 0 );
    drawMap->attach( MPlot );

    RD = new QwtMatrixRasterData();
    RDb = new QwtMatrixRasterData();

    rightAxis = new QwtScaleWidget(this);
    rightAxis->setAlignment( QwtScaleDraw::RightScale );
    rightAxis->setColorBarEnabled( true );
    rightAxis->setColorBarWidth( 16 );
    rightAxis->setMargin(8);
    rightAxis->setTitle( QwtText("edit map") );
    int startDist, endDist;
    rightAxis->getBorderDistHint( startDist, endDist );
    rightAxis->setBorderDist( startDist, endDist+32 );

    leftAxis = new QwtScaleWidget(this);
    leftAxis->setAlignment( QwtScaleDraw::LeftScale );
    leftAxis->setColorBarEnabled( true );
    leftAxis->setColorBarWidth( 16 );
    leftAxis->setMargin(8);
    leftAxis->setTitle( QwtText("base map") );
    leftAxis->getBorderDistHint( startDist, endDist );
    leftAxis->setBorderDist( startDist, endDist+32 );

    magnifier = new QwtPlotMagnifier( MPlot->canvas() );
    magnifier->setMouseButton( Qt::NoButton );
    magnifier->setZoomInKey(Qt::Key_Plus, Qt::ShiftModifier);
    magnifier->setZoomOutKey(Qt::Key_Minus, Qt::NoModifier );
    magnifier->setZoomInKey(Qt::Key_Plus, Qt::KeypadModifier);
    magnifier->setZoomOutKey(Qt::Key_Minus, Qt::KeypadModifier);

    panner = new QwtPlotPanner( MPlot->canvas() );
   // panner->setMouseButton( Qt::LeftButton, Qt::ControlModifier );
    panner->setMouseButton( Qt::RightButton, Qt::NoModifier );

    mapRescaler = new QwtPlotRescaler( MPlot->canvas() );
    mapRescaler->setAspectRatio( QwtPlot::xBottom, 1.0 );
    mapRescaler->setAspectRatio( QwtPlot::yRight, 0.0 );
    mapRescaler->setAspectRatio( QwtPlot::xTop, 0.0 );
    mapRescaler->setExpandingDirection( QwtPlotRescaler::ExpandUp );
 //   mapRescaler->setRescalePolicy(QwtPlotRescaler::Fixed);
//    mapRescaler->setRescalePolicy(QwtPlotRescaler::Fitting );

    cpicker = new CanvasPicker( MPlot );
    connect(cpicker, SIGNAL(show(QString)),this, SLOT(Show(QString)));
    connect(cpicker, SIGNAL(draw()),this, SLOT(drawSelection()));
    connect(cpicker, SIGNAL(get()),this, SLOT(getCells()));
    connect(cpicker, SIGNAL(zoom()),this, SLOT(zoomPoint()));

    layout_Map->insertWidget(0,leftAxis, 0);
    layout_Map->insertWidget(1, MPlot, 1);
    layout_Map->insertWidget(2,rightAxis,0 );
}
//---------------------------------------------------------------------------

// fill the current raster data structure with new data
// set min and max
double MainWindow::fillDrawMapData(cTMap *_M, QwtMatrixRasterData *_RD, double *minv, double *maxv)
{
    double maxV = -MVe;
    double minV = MVe;
    QVector<double> mapData;
    mapData.clear();  //QVector double

    if (_M == NULL)
        return (maxV);

    // copy map data into vector for the display structure
    for(int r = _nrRows-1; r >= 0; r--)
        for(int c=0; c < _nrCols; c++)
        {
            if(!pcr::isMV(_M->Drc)) //baseRMap->data[r][c]))
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

    if (maxV < 0 && maxV > -MVe && minV == MVe) {
        minV = maxV;
        maxV = 0;
    }
    if (minV == MVe && maxV == -MVe) {
        minV = 0;
        maxV = 1;
    }
    if (minV == maxV) {
        double v = maxV;
        maxV = v*1.1;
        minV = v * 0.9;
    }
    if (minV == 0 && maxV == 0) {
        maxV = 1;
        minV = 0;
    }

    *maxv = maxV;
    *minv = minV;

    _RD->setValueMatrix( mapData, _nrCols );
    // set column number to divide vector into rows

    _RD->setInterval( Qt::XAxis, QwtInterval( _llx,_llx+_nrCols*_dx, QwtInterval::ExcludeMaximum ) );
    _RD->setInterval( Qt::YAxis, QwtInterval( _lly,_lly+_nrRows*_dx, QwtInterval::ExcludeMaximum ) );
    // use real coordinates

    return maxV;
}
//---------------------------------------------------------------------------
// initialise bottom layer for reference
void MainWindow::initBaseMap()
{
    baseMinMaxdistance = 1;

    palette1nr = 0;
    changePalette(0);

    double res = fillDrawMapData(baseRMap, RDb, &MinV1, &MaxV1);
    RDb->setInterval( Qt::ZAxis, QwtInterval( MinV1, MaxV1));
    baseMap->setData(RDb);

    MinBase = MinV1;
    MaxBase = MaxV1;

    baseMap->setAlpha(255);
    if (baseRMap->valueScale != VS_SCALAR)
        bpalette->setMode(QwtLinearColorMap::FixedColors);
    baseMap->setColorMap(bpalette);


    interval = baseMap->data()->interval( Qt::ZAxis );
    leftAxis->setColorMap( interval, bpalette1);
    leftAxis->setScaleDiv(scaleEngine.divideScale( interval.minValue(), interval.maxValue(),10,5) );
}
//---------------------------------------------------------------------------
// display bottom layer for reference with bpalette1
void MainWindow::showBaseMap()
{
    RDb->setInterval( Qt::ZAxis, QwtInterval( MinV1, MaxV1));
    baseMap->setData(RDb);
    interval = baseMap->data()->interval( Qt::ZAxis );
    interval = interval.normalized();
    leftAxis->setColorMap( interval, bpalette1);
    leftAxis->setScaleDiv(scaleEngine.divideScale( interval.minValue(), interval.maxValue(),10,5) );
}
//---------------------------------------------------------------------------
// initialize map to be edited
void MainWindow::initTopMap()
{
    topMinMaxdistance = 1;

    palette2nr = -1;
    changePalette(1);

    double res = fillDrawMapData(topRMap, RD, &MinV2, &MaxV2);
    RD->setInterval( Qt::ZAxis, QwtInterval(MinV2,MaxV2));
    drawMap->setData(RD);

    MinTop = MinV2;
    MaxTop = MaxV2;

    if (topRMap->valueScale != VS_SCALAR)
        dpalette->setMode(QwtLinearColorMap::FixedColors);
    drawMap->setColorMap(dpalette);
    transparency->setValue(128);
    setAlphaTop(128);

    interval = drawMap->data()->interval( Qt::ZAxis );
    rightAxis->setColorMap( interval, dpalette1);
    rightAxis->setScaleDiv(scaleEngine.divideScale( interval.minValue(), interval.maxValue(),10,5) );
}
//---------------------------------------------------------------------------
// display map to be edited
void MainWindow::showTopMap()
{
    RD->setInterval( Qt::ZAxis, QwtInterval(MinV2, MaxV2));
    drawMap->setData(RD);
    interval = drawMap->data()->interval( Qt::ZAxis );
    rightAxis->setColorMap( interval, dpalette1);
    rightAxis->setScaleDiv(scaleEngine.divideScale( interval.minValue(), interval.maxValue(),10,5) );
}

//---------------------------------------------------------------------------
// find optimum display size
void MainWindow::changeSize()
{
    double h = MPlot->height();
    double w = MPlot->width();

    if(_nrCols >= _nrRows ) {
        MPlot->setAxisScale( MPlot->xBottom, _llx, _llx+_nrCols*_dx*w/h, _dx*10);
        MPlot->setAxisScale( MPlot->yLeft, _lly, _lly+_nrCols*_dx, _dx*10);
    } else {
        MPlot->setAxisScale( MPlot->xBottom, _llx, _llx+_nrRows*_dx*w/h,_dx*10);
        MPlot->setAxisScale( MPlot->yLeft, _lly, _lly+_nrRows*_dx, _dx*10);
    }
    MPlot->replot();


}
//---------------------------------------------------------------------------
// slider for palette
void MainWindow::setMinMaxBaseMap(int i)
{
    if (op._M == nullptr)
        return;
    int mi = slider_baseMin->value();
    int ma = slider_baseMax->value();

    if (i == 0) {
        mi = std::min(mi, slider_baseMax->value()-baseMinMaxdistance);
        slider_baseMin->setValue(mi);

        ma = std::max(ma, slider_baseMin->value()+baseMinMaxdistance);
        slider_baseMax->setValue(ma);
    } else {
        ma = std::max(ma, slider_baseMin->value()+baseMinMaxdistance);
        slider_baseMax->setValue(ma);

        mi = std::min(mi, slider_baseMax->value()-baseMinMaxdistance);
        slider_baseMin->setValue(mi);
    }

    MinV1 = MinBase+(MaxBase-MinBase)*((double)mi/100);
    MaxV1 = MaxBase-(MaxBase-MinBase)*(1-(double)ma/100);

    showBaseMap();

    MPlot->replot();
}
//---------------------------------------------------------------------------
void MainWindow::setMinBaseMap()
{
    setMinMaxBaseMap(1);
}
//---------------------------------------------------------------------------
void MainWindow::setMaxBaseMap()
{
    setMinMaxBaseMap(0);
}
//---------------------------------------------------------------------------
void MainWindow::setMinMaxTopMap(int i)
{
    if (op._M == nullptr)
        return;

    int mi = slider_editMin->value();
    int ma = slider_editMax->value();

    if (i == 0) {
        mi = std::min(mi, slider_editMax->value()-topMinMaxdistance);
        slider_editMin->setValue(mi);

        ma = std::max(ma, slider_editMin->value()+topMinMaxdistance);
        slider_editMax->setValue(ma);
    } else {
        ma = std::max(ma, slider_editMin->value()+topMinMaxdistance);
        slider_editMax->setValue(ma);

        mi = std::min(mi, slider_editMax->value()-topMinMaxdistance);
        slider_editMin->setValue(mi);
    }

    MinV2 = MinTop+(MaxTop-MinTop)*((double)mi/100);
    MaxV2 = MaxTop-(MaxTop-MinTop)*(1-(double)ma/100);

    showTopMap();

    MPlot->replot();
}
//---------------------------------------------------------------------------
void MainWindow::setMinTopMap()
{
    setMinMaxTopMap(1);
}
//---------------------------------------------------------------------------
void MainWindow::setMaxTopMap()
{
    setMinMaxTopMap(0);
}
//---------------------------------------------------------------------------
void MainWindow::changePalette(int nr)
{
    if (op._M == nullptr)
        return;
    if (nr == 0){
        palette1nr++;
        if (palette1nr > 3)
            palette1nr = 0;

        switch (palette1nr) {
        case(0):
            bpalette = new colorMapGray();
            bpalette1 = new colorMapGray();
            break;
        case(1):
            bpalette = new colorMapRainbow();
            bpalette1 = new colorMapRainbow();
            break;
        case(2):
            bpalette = new colorMap2();
            bpalette1 = new colorMap2();
            break;
        case(3):
            bpalette = new colorMap6();
            bpalette1 = new colorMap6();
            break;
//        case(4):
//            bpalette = new colorMap4();
//            bpalette1 = new colorMap4();
//            break;
//        case(5):
//            bpalette = new colorMap7();
//            bpalette1 = new colorMap7();
//            break;
        }
    }
    if (nr == 1){
        palette2nr++;
        if (palette2nr > 3)
            palette2nr = 0;

        switch (palette2nr) {
        case(0):
            dpalette = new colorMapGray();
            dpalette1 = new colorMapGray();
            break;
        case(1):
            dpalette = new colorMapRainbow();
            dpalette1 = new colorMapRainbow();
            break;
        case(2):
            dpalette = new colorMap2();
            dpalette1 = new colorMap2();
            break;
        case(3):
            dpalette = new colorMap6();
            dpalette1 = new colorMap6();
            break;
//        case(4):
//            dpalette = new colorMap4();
//            dpalette1 = new colorMap4();
//            break;
//        case(5):
//            dpalette = new colorMap7();
//            dpalette1 = new colorMap7();
//            break;
        }
    }

}
//---------------------------------------------------------------------------
// trasnparency of top map
void MainWindow::setAlphaTop(int v)
{
    drawMap->setAlpha(v);

    MPlot->replot();
}
//--------------------------------------------------------


/*
 *     // MouseMove only fires while a mouse button is pressed
 *     https://www.qtcentre.org/threads/47543-redraw-the-axes-of-a-QwtPlot-during-a-panning-(QwtPlotPanner)?highlight=qwt+reset+panner
    if (event->type() == QEvent::MouseMove)
    {
        // User wants to pan the plot
        if (m_middleMouseDown)
        {
            // Get current zoom rectangle
            QRectF zoomRect = m_zoomer->zoomRect();

            // Convert the change in position for the last drag (1px) from
            // pixel space to plot space.
            double deltaX   = invTransform(QwtPlot::xBottom, m_mouseDragLocation.x()) - invTransform(QwtPlot::xBottom, cursor().pos().x());
            double deltaY   = invTransform(QwtPlot::yLeft,   m_mouseDragLocation.y()) - invTransform(QwtPlot::yLeft,   cursor().pos().y());

            // Update the zoom rect with the new values
            zoomRect.setX(zoomRect.x() + deltaX);
            zoomRect.setY(zoomRect.y() + deltaY);
            zoomRect.setWidth (zoomRect.width()  + deltaX);
            zoomRect.setHeight(zoomRect.height() + deltaY);

            // Store for continued dragging
            m_mouseDragLocation = cursor().pos();

            // Set the zoom to its new position
            m_zoomer->zoom(zoomRect);
        }
    }
    */
