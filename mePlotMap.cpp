#include "mainwindow.h"
#include "global.h"



void MainWindow::drawSelection()
{
  if (op.editCell)
      drawSelectionCell();
  if (op.editPolygon)
      drawSelectionPolygon();
  if (op.editLine)
      drawSelectionLine();

  MPlot->replot();
}

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
    drawMap->attach( MPlot );
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
    *maxv = maxV;
    *minv = minV;

    _RD->setValueMatrix( mapData, _nrCols );
    // set column number to divide vector into rows


    double cy = _M->north();
    double cx = _M->west();

//     _RD->setInterval( Qt::XAxis, QwtInterval( cx,cx+_nrCols*_dx, QwtInterval::ExcludeMaximum ) );
 //   _RD->setInterval( Qt::YAxis, QwtInterval( cy,cy+_nrRows*_dx, QwtInterval::ExcludeMaximum ) );


   _RD->setInterval( Qt::XAxis, QwtInterval( 0, (double)_nrCols*_dx, QwtInterval::ExcludeMaximum ) );
    _RD->setInterval( Qt::YAxis, QwtInterval( 0, (double)_nrRows*_dx, QwtInterval::ExcludeMaximum ) );
    // set x/y axis intervals
    return maxV;
}
//---------------------------------------------------------------------------
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

    rightAxis->setColorMap( drawMap->data()->interval( Qt::ZAxis ), dpalette1);

    MPlot->setAxisScale( MPlot->yRight, MinV2, MaxV2);
    MPlot->setAxisScaleEngine( MPlot->yRight, new QwtLinearScaleEngine() );

}
//---------------------------------------------------------------------------
void MainWindow::initTopMap()
{
    op.nrC = _nrCols;
    op.nrR = _nrRows;
    op._dx = _dx;
    op._M = topRMap;

    dpalette = new colorMapRainbow();
    dpalette1 = new colorMapRainbow();

    double res = fillDrawMapData(topRMap, RD, 0, &MinV2, &MaxV2);
    if (res == -1e20)
        return;

    MPlot->setAxisAutoScale(MPlot->yRight, true);
    MPlot->setAxisAutoScale(MPlot->xBottom, true);
    MPlot->setAxisAutoScale(MPlot->yLeft, true);
//    MPlot->setAxisScale( MPlot->xBottom, 0.0, _nrCols*_dx, _dx*10);
//    MPlot->setAxisScale( MPlot->yLeft, 0.0, _nrRows*_dx, _dx*10);

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
//--------------------------------------------------------------------------
void MainWindow::drawSelectionCell()
{
    double dx[5] = {-0.5,+0.5,+0.5,-0.5, -0.5};
    double dy[5] = {-0.5,-0.5,+0.5,+0.5,-0.5};

  //  if (op.clicks == 1) {
        cur = new QwtPlotCurve();
        QBrush b;
        QColor col(Qt::magenta);
        col.setAlpha(96);
        b.setColor(col);
        b.setStyle(Qt::SolidPattern);//Dense7Pattern);

        cur->setPen( Qt::magenta, 2 );
        cur->setStyle( QwtPlotCurve::Lines );
        cur->setBrush(b);
        cur->attach( MPlot );
        cur->setAxes(MPlot->xBottom, MPlot->yLeft);
//    }
    vx.clear();
    vy.clear();


    int l = op.eData.size()-1;

    for (int i = 0; i < 5; i++) {
        vx << op.eData[l].cx+dx[i]*_dx;
        vy << op.eData[l].cy+dy[i]*_dx;
    }

    cur->setSamples(vx,vy);
   // free(cur);
}
//--------------------------------------------------------------------------
void MainWindow::drawSelectionPolygon()
{
    vx.clear();
    vy.clear();
//qDebug() << op.clicks << op.polystart << op.eData.size();
    if (op.polystart == op.eData.size()-1) {
        cur = new QwtPlotCurve();
        QBrush b;
        QColor col(Qt::magenta);
        col.setAlpha(96);
        b.setColor(col);
        b.setStyle(Qt::SolidPattern);//Dense7Pattern);

        QwtSymbol *whitedot = new QwtSymbol( QwtSymbol::Ellipse, Qt::white, QPen( Qt::black ), QSize( 10,10 ));
        cur->setSymbol(whitedot);

        cur->setPen( Qt::magenta, 2);
        cur->setStyle( QwtPlotCurve::Lines );
        cur->setBrush(b);
        cur->attach( MPlot );
        cur->setAxes(MPlot->xBottom, MPlot->yLeft);

        vx << op.eData[op.polystart].cx;
        vy << op.eData[op.polystart].cy;
    }

    for (int i = op.polystart; i < op.eData.size(); i++) {
        vx << op.eData[i].cx;
        vy << op.eData[i].cy;
    }

    vx << op.eData[op.polystart].cx;
    vy << op.eData[op.polystart].cy;

    cur->setSamples(vx,vy);

}
//--------------------------------------------------------------------------
void MainWindow::drawSelectionLine()
{
    vx.clear();
    vy.clear();

    if (op.polystart == op.eData.size()-1) {
        cur = new QwtPlotCurve();
        QwtSymbol *whitedot = new QwtSymbol( QwtSymbol::Ellipse, Qt::white, QPen( Qt::black ), QSize( 10,10 ));
        cur->setSymbol(whitedot);

        cur->setPen( Qt::magenta, 2 );
        cur->setStyle( QwtPlotCurve::Lines );

        cur->attach( MPlot );
        cur->setAxes(MPlot->xBottom, MPlot->yLeft);

        vx << op.eData[op.polystart].cx;
        vy << op.eData[op.polystart].cy;
    }

    for (int i = op.polystart; i < op.eData.size(); i++) {
        vx << op.eData[i].cx;
        vy << op.eData[i].cy;
    }

    cur->setSamples(vx,vy);

}
//--------------------------------------------------------------------------
void MainWindow::drawSelectionRectangle()
{
    vx.clear();
    vy.clear();

    if (op.polystart == op.eData.size()-1) {
        cur = new QwtPlotCurve();
      //  QwtSymbol *whitedot = new QwtSymbol( QwtSymbol::Ellipse, Qt::white, QPen( Qt::black ), QSize( 10,10 ));
      //  cur->setSymbol(whitedot);

        cur->setPen( Qt::magenta, 2 );
        cur->setStyle( QwtPlotCurve::steps );

        cur->attach( MPlot );
        cur->setAxes(MPlot->xBottom, MPlot->yLeft);

        vx << op.eData[op.polystart].cx;
        vy << op.eData[op.polystart].cy;
    }

    for (int i = op.polystart; i < op.eData.size(); i++) {
        vx << op.eData[i].cx;
        vy << op.eData[i].cy;
    }

    cur->setSamples(vx,vy);

}
//--------------------------------------------------------------------------
void MainWindow::getCells()
{
    editValue = 1;
    if (op.editCell) {
       for (int i = 0; i < op.eData.size(); i++) {

           int r = op.eData[i].r;
           int c = op.eData[i].c;

           topRMap->data[r][c] = editValue;

       }
    }

    if (op.editLine) {

        for (int j = op.polystart; j < op.eData.size()-1; j++)  {

          int rb = op.eData[j].r;
          int re = op.eData[j+1].r;
          int cb = op.eData[j].c;
          int ce = op.eData[j+1].c;

          if (rb == re) {
              if (cb > ce) {int tmp = cb; cb = ce; ce = tmp;}
              for(int c = cb; c <= ce; c++)
                    topRMap->data[rb][c] = editValue;
          } else
              if (cb == ce) {
                  if (rb > re) {int tmp = rb; rb = re; re = tmp;}
                  for(int r = rb; r <= re; r++)
                        topRMap->data[r][cb] = editValue;
              } else {
                  double r0 = op.eData[j].cy;
                  double c0 = op.eData[j].cx;
                  double rn = op.eData[j+1].cy;
                  double cn = op.eData[j+1].cx;
                  double dx = cn-c0;
                  double dy = rn-r0;
                 // qDebug() << r0<<rn<<c0<<cn<<dy<<dx;
                  if (r0 > rn) {
                      double begin = std::min(c0,cn);
                      double end = std::max(c0,cn);
                      for(double _c = begin; _c <= end; _c+=_dx*0.1)
                      {
                          double _r = r0 + dy*(_c - c0)/dx;
                          int r = _nrRows-1 - int((_r - 0.5*_dx)/_dx);
                          int c = int((_c - 0.5*_dx)/_dx);
                         // qDebug() << _r << _c << r << c;

                          topRMap->data[r][c] = editValue;

                      }
                  } else {
                      double begin = std::min(c0,cn);
                      double end = std::max(c0,cn);
                          for(double _c = begin; _c <= end; _c+=_dx*0.1)
                          {
                              double _r = r0 + dy*(_c - c0)/dx;
                              int r = _nrRows-1 - int((_r - 0.5*_dx)/_dx);
                              int c = int((_c - 0.5*_dx)/_dx);
                              qDebug() << _r << _c << r << c;

                              topRMap->data[r][c] = editValue;

                          }
                   }
            }
      }
    }

    if (op.editPolygon) {
        int n = vx.size();
        FOR_ROW_COL_MV {
            double cy = (_nrRows-r-1)*_dx + 0.5*_dx;
            double cx = c*_dx + 0.5*_dx;

            int res = 0;
            int i, j;
            for (i = 0, j = n-1; i < n; j = i++) {
              if ( ((vy[i]>cy) != (vy[j]>cy)) &&
               (cx < (vx[j]-vx[i]) * (cy-vy[i]) / (vy[j]-vy[i]) + vx[i]) )
                 res = !res;
            }

            if (res == 1)
                topRMap->data[r][c] = editValue;
        }
    }

    //QVector <double> nx;
    vx.clear();
    vy.clear();
    cur->setSamples(vx, vy);

    double res = fillDrawMapData(topRMap, RD, 0, &MinV2, &MaxV2);
    showTopMap();
    MPlot->replot();

}




