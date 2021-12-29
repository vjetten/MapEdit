#include "mainwindow.h"
#include "LisUImapplot.h"



//---------------------------------------------------------------------------
void MainWindow::ssetAlpha(int v)
{
    drawMap->setAlpha(v);

    MPlot->replot();
}
//----------------------------------------------------------------------------------------
void MainWindow::setupMapPlot()
{
//    baseRMap = new cTMap();
//    topRMap = new cTMap();
//    editRMap = new cTMap();

//    FOR_ROW_COL_MV {
//        editRMap->Drc = 0;
//    }

    MPlot = new QwtPlot(title, this);
    // make the plot window
    layout_Map->insertWidget(1, MPlot, 0);
    // put it on screen
    MPlot->enableAxis( MPlot->yRight );
//    MPlot->setAxisTitle(MPlot->xBottom, "m");
//    MPlot->setAxisTitle(MPlot->yLeft, "m");

    //MPlot->installEventFilter(this);

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
    rightAxis->setColorBarWidth( 24 );
   // rightAxis->setMargin(8);
   // rightAxis->setBorderDist(64, 64);
    // legend to the right of the plot

    mapRescaler = new QwtPlotRescaler( MPlot->canvas() );
   // mapRescaler->setReferenceAxis( QwtPlot::yLeft );
    mapRescaler->setAspectRatio( QwtPlot::xBottom, 1.0 );
    mapRescaler->setAspectRatio( QwtPlot::yRight, 0.0 );
    mapRescaler->setAspectRatio( QwtPlot::xTop, 0.0 );
 //   mapRescaler->setRescalePolicy( QwtPlotRescaler::Fitting );
    mapRescaler->setExpandingDirection( QwtPlotRescaler::ExpandUp );
 //   mapRescaler->setEnabled( true );
    // rescaling fixed to avoid deformation

    magnifier = new QwtPlotMagnifier( MPlot->canvas() );
    magnifier->setAxisEnabled( MPlot->yRight, false );
    magnifier->setZoomInKey((int)Qt::Key_Plus, Qt::NoModifier );
    magnifier->setZoomOutKey((int)Qt::Key_Minus, Qt::NoModifier );

//    panner = new QwtPlotPanner( MPlot->canvas() );
//    panner->setAxisEnabled( MPlot->yRight, false );

//    picker = new MyPicker( (QwtPlotCanvas *) MPlot->canvas() );
//    connect(picker, SIGNAL(moved(const QPoint &)), SLOT(moved(const QPoint &)));
//    connect(picker, SIGNAL( selected( const QPolygon & ) ), SLOT( selected( const QPolygon & ) ) );


//    picker->setStateMachine(new QwtPickerDragRectMachine);
//    picker->setTrackerMode(QwtPicker::AlwaysOn);
//    picker->setRubberBand(QwtPicker::RectRubberBand);

 //   mpicker = new MyPicker( (QwtPlotCanvas *) MPlot->canvas() );
    picker = new QwtPlotPicker( QwtAxis::xBottom, QwtAxis::yLeft,
        QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
        MPlot->canvas() );

    connect(picker, SIGNAL(moved(const QPoint &)), SLOT(moved(const QPoint &)));
    connect(picker, SIGNAL( selected( const QPolygon & ) ), SLOT( selected( const QPolygon & ) ) );

//    picker->setStateMachine(new QwtPickerDragRectMachine);
 //   mpicker->setTrackerMode(QwtPicker::AlwaysOn);
//    picker->setRubberBand(QwtPicker::RectRubberBand);


}
//---------------------------------------------------------------------------
// fill the current raster data structure with new data, called each run step
double MainWindow::fillDrawMapData(cTMap *_M, QwtMatrixRasterData *_RD, double type, double *minv, double *maxv)
{
    double maxV = -1e20;
    double minV = 1e20;
    QVector<double> mapData;
    mapData.clear();  //QVector double

    if (_M == NULL)
        return (maxV);

    // copy map data into vector for the display structure
    for(int r = _nrRows-1; r >= 0; r--)
        for(int c=0; c < _nrCols; c++)
        {
            if(!IS_MV_REAL8(&_M->Drc))
            {
                mapData << _M->Drc;
                maxV = qMax(maxV, _M->Drc);
                minV = qMin(minV, _M->Drc);
            }
            else
                mapData << (double)-1e20;
        }

    //    mapData.replace(0, (double)type);
    // highjack position 0,0 with flag to get the variable unit in the cursor in trackerTextF

    *maxv = maxV;
    *minv = minV;

    _RD->setValueMatrix( mapData, _nrCols );
    // set column number to divide vector into rows

    _RD->setInterval( Qt::XAxis, QwtInterval( 0, (double)_nrCols*_dx, QwtInterval::ExcludeMaximum ) );
    _RD->setInterval( Qt::YAxis, QwtInterval( 0, (double)_nrRows*_dx, QwtInterval::ExcludeMaximum ) );
    // set x/y axis intervals
    return maxV;
}
//---------------------------------------------------------------------------
// show the maps on screen
// the order of showing layers is determined by the order in how they are added to MPlot,
// not how they are done here!
void MainWindow::showMap()
{
    MPlot->replot();
}
//---------------------------------------------------------------------------
void MainWindow::showBaseMap()
{
    bpalette = new colorMapGray();
    bpalette1 = new colorMapGray();

    double res = fillDrawMapData(baseRMap, RDb, 0, &MinV1, &MaxV1);
//    if (res == -1e20)
//        return;

    baseMap->setAlpha(255);
    baseMap->setColorMap(bpalette);
    RDb->setInterval( Qt::ZAxis, QwtInterval( MinV1-0.01, MaxV1+0.01));
    baseMap->setData(RDb);
    // setdata sets a pointer to DRb to the private QWT d_data Qvector

    double nrCols = _nrCols*_dx;
    double nrRows = _nrRows*_dx;
    double dx = qMax(nrCols,nrRows)/20;
    // reset the axes to the correct rows/cols,
    // do only once because resets zooming and panning

    MPlot->setAxisAutoScale(MPlot->yRight, false);
    MPlot->setAxisAutoScale(MPlot->xBottom, false);
    MPlot->setAxisAutoScale(MPlot->yLeft, false);

    MPlot->setAxisScale( MPlot->xBottom, 0.0, nrCols, dx);
    MPlot->setAxisMaxMinor( MPlot->xBottom, 0 );
    MPlot->setAxisScale( MPlot->yLeft, 0.0, nrRows, dx);
    MPlot->setAxisMaxMinor( MPlot->yLeft, 0 );

    rightAxis->setColorMap( baseMap->data()->interval( Qt::ZAxis ), bpalette1);

    MPlot->setAxisScale( MPlot->yRight, MinV1, MaxV1);
    MPlot->setAxisScaleEngine( MPlot->yRight, new QwtLinearScaleEngine() );
}
//---------------------------------------------------------------------------
void MainWindow::setMinTopMap()
{
    MinV2 = spinMinV->value();
    MaxV2 = spinMaxV->value();
    if (MinV2 == 0) MinV2 = MinTop;
    if (MaxV2 == 0) MaxV2 = MaxTop;

    showTopMap();

    MPlot->replot();
}
//---------------------------------------------------------------------------
void MainWindow::showTopMap()
{
    drawMap->setColorMap(dpalette);
    RD->setInterval( Qt::ZAxis, QwtInterval( MinV2, MaxV2));
    drawMap->setData(RD);
    // setdata sets a pointer to DRb to the private QWT d_data Qvector

    double nrCols = _nrCols*_dx;
    double nrRows = _nrRows*_dx;
    double dx = qMax(nrCols,nrRows)/20;
    // reset the axes to the correct rows/cols,
    // do only once because resets zooming and panning

    MPlot->setAxisAutoScale(MPlot->yRight, false);
    MPlot->setAxisAutoScale(MPlot->xBottom, false);
    MPlot->setAxisAutoScale(MPlot->yLeft, false);

    MPlot->setAxisScale( MPlot->xBottom, 0.0, nrCols, dx);
    MPlot->setAxisMaxMinor( MPlot->xBottom, 0 );
    MPlot->setAxisScale( MPlot->yLeft, 0.0, nrRows, dx);
    MPlot->setAxisMaxMinor( MPlot->yLeft, 0 );

    rightAxis->setColorMap( drawMap->data()->interval( Qt::ZAxis ), dpalette1);

    MPlot->setAxisScale( MPlot->yRight, MinV2, MaxV2);
    MPlot->setAxisScaleEngine( MPlot->yRight, new QwtLinearScaleEngine() );

}
//---------------------------------------------------------------------------
void MainWindow::initTopMap()
{
    dpalette = new colorMapRainbow();
    dpalette1 = new colorMapRainbow();

    double res = fillDrawMapData(topRMap, RD, 0, &MinV2, &MaxV2);
    if (res == -1e20)
        return;

    MinTop = MinV2;
    MaxTop = MaxV2;

    spinMinV->setMinimum(MinTop);
    spinMinV->setMaximum(MaxTop);
    spinMaxV->setMinimum(MinTop);
    spinMaxV->setMaximum(MaxTop);
    spinMinV->setValue(MinTop);
    spinMaxV->setValue(MaxTop);
    if ((MaxTop-MinTop) < 10)
    {
        spinMinV->setDecimals(3);
        spinMaxV->setDecimals(3);
        spinMinV->setSingleStep(0.001);
        spinMaxV->setSingleStep(0.001);
    }
    drawMap->setAlpha(255);
}
//---------------------------------------------------------------------------
/*
bool MainWindow::event(QEvent* event)
{
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
                OnTouch(x, y, event->type() != QEvent::MouseButtonRelease, 0);
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
                OnTouch(x, y, p.state() != Qt::TouchPointReleased, p.id());
            }
        }
        return true;
    default:
        return QWidget::event(event);
    }
}
*/
