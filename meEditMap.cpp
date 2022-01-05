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
  if (op.editRectangle)
      drawSelectionRectangle();

  MPlot->replot();
}
//--------------------------------------------------------------------------
void MainWindow::drawSelectionCell()
{
    double dx[5] = {-0.5,+0.5,+0.5,-0.5, -0.5};
    double dy[5] = {-0.5,-0.5,+0.5,+0.5,-0.5};

    cur = new QwtPlotCurve();
    curves << cur;
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

    vx.clear();
    vy.clear();

    int l = op.eData.size()-1;

    for (int i = 0; i < 5; i++) {
        vx << op.eData[l].cx+dx[i]*_dx;
        vy << op.eData[l].cy+dy[i]*_dx;
    }

    cur->setSamples(vx,vy);
}
//--------------------------------------------------------------------------
void MainWindow::drawSelectionPolygon()
{
    vx.clear();
    vy.clear();
    cx.clear();
    ry.clear();

    if (op.polystart == op.eData.size()-1) {
        cur = new QwtPlotCurve();
        curves << cur;
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

        op.vvx << vx;
        op.vvy << vy;
    }

    for (int i = op.polystart; i < op.eData.size(); i++) {
        vx << op.eData[i].cx;
        vy << op.eData[i].cy;
    }

    vx << op.eData[op.polystart].cx; // always close the polygon
    vy << op.eData[op.polystart].cy;

    if (op.vvx.size() > 0) {
        op.vvx.removeLast();
        op.vvx << vx;
        op.vvy.removeLast();
        op.vvy << vy;
    }

    cur->setSamples(vx,vy);
}
//--------------------------------------------------------------------------
void MainWindow::drawSelectionLine()
{
    vx.clear();
    vy.clear();
    cx.clear();
    ry.clear();
    if (op.polystart == op.eData.size()-1) {
        cur = new QwtPlotCurve();
        curves << cur;
        QwtSymbol *whitedot = new QwtSymbol( QwtSymbol::Ellipse, Qt::white, QPen( Qt::black ), QSize( 10,10 ));
        cur->setSymbol(whitedot);

        cur->setPen( Qt::magenta, 2 );
        cur->setStyle( QwtPlotCurve::Lines );

        cur->attach( MPlot );
        cur->setAxes(MPlot->xBottom, MPlot->yLeft);

        vx << op.eData[op.polystart].cx;
        vy << op.eData[op.polystart].cy;
        op.vvx << vx;
        op.vvy << vy;
        cx << op.eData[op.polystart].c;
        ry << op.eData[op.polystart].r;
        op.ccx << cx;
        op.rry << ry;
    }

    for (int i = op.polystart; i < op.eData.size(); i++) {
        vx << op.eData[i].cx;
        vy << op.eData[i].cy;
        cx << op.eData[i].c;
        ry << op.eData[i].r;
    }

    if (op.ccx.size() > 0) {
        op.vvx.removeLast();
        op.vvx << vx;
        op.vvy.removeLast();
        op.vvy << vy;
        op.ccx.removeLast();
        op.ccx << cx;
        op.rry.removeLast();
        op.rry << ry;
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
        curves << cur;
      //  QwtSymbol *whitedot = new QwtSymbol( QwtSymbol::Ellipse, Qt::white, QPen( Qt::black ), QSize( 10,10 ));
      //  cur->setSymbol(whitedot);

        cur->setPen( Qt::magenta, 2 );
        cur->setStyle( QwtPlotCurve::Lines );

        cur->attach( MPlot );
        cur->setAxes(MPlot->xBottom, MPlot->yLeft);

        vx << op.eData[op.polystart].cx;
        vy << op.eData[op.polystart].cy;

        op.vvx << vx;
        op.vvy << vy;
    }

    for (int i = op.polystart; i < op.eData.size(); i++) {
        vx << op.eData[i].cx;
        vy << op.eData[i].cy;
    }

    if (op.vvx.size() > 0) {
        op.vvx.removeLast();
        op.vvx << vx;
        op.vvy.removeLast();
        op.vvy << vy;
    }

    cur->setSamples(vx,vy);
}
//--------------------------------------------------------------------------
void MainWindow::getCells()
{
    editValue = lineEdit_Value->text().toDouble();

    if (op.editCell) {
       for (int i = 0; i < op.eData.size(); i++) {

           int r = op.eData[i].r;
           int c = op.eData[i].c;

           topRMap->data[r][c] = editValue;
       }
    }

    if (op.editLine) {
        for (int k = 0; k < op.ccx.count(); k++)  {
            QVector <int> _cx;
            QVector <int> _ry;
            _cx << op.ccx[k];
            _ry << op.rry[k];
            QVector <double> _vx;
            QVector <double> _vy;
            _vx << op.vvx[k];
            _vy << op.vvy[k];

            for (int j = 0; j < _cx.count()-1; j++) {
                int rb = _ry.at(j);
                int re = _ry.at(j+1);
                int cb = _cx.at(j);
                int ce = _cx.at(j+1);

                double r0 = _vy.at(j);
                double rn = _vy.at(j+1);
                double c0 = _vx.at(j);
                double cn = _vx.at(j+1);
                if (rb == re) {
                    // vertical line
                    int st = std::min(cb,ce);
                    int en = std::max(cb,ce);
                    for(int c = st; c <= en; c++)
                        topRMap->data[rb][c] = editValue;
                } else
                    if (cb == ce) {
                        //horizontal line
                        int st = std::min(rb,re);
                        int en = std::max(rb,re);
                        for(int r = st; r <= en; r++)
                            topRMap->data[r][cb] = editValue;
                    } else {
                        //diagonal lines
                        double dx = cn-c0;
                        double dy = rn-r0;
                        if (r0 > rn) {
                            double begin = std::min(c0,cn);
                            double end = std::max(c0,cn);
                            for(double _c = begin; _c <= end; _c+=_dx*0.1)
                            {
                                double _r = r0 + dy*(_c - c0)/dx;
                                int r = _nrRows-1 - int((_r - 0.5*_dx)/_dx);
                                int c = int((_c - 0.5*_dx)/_dx);

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

                                topRMap->data[r][c] = editValue;

                            }
                        }
                    }
            }
        }
    }

    if (op.editPolygon) {
        for (int k = 0; k < op.vvx.count(); k++)  {
            QVector <double> _vx;
            QVector <double> _vy;
            _vx << op.vvx[k];
            _vy << op.vvy[k];

            int n = _vx.size();
            qDebug() << n;
            FOR_ROW_COL_MV {
                double cy = (_nrRows-r-1)*_dx + 0.5*_dx;
                double cx = c*_dx + 0.5*_dx;

                int res = 0;
                int i, j;
                for (i = 0, j = n-1; i < n; j = i++) {

                    if ( ((_vy[i] > cy) != (_vy[j] > cy)) &&
                         (cx < (_vx[j]-_vx[i]) * (cy-_vy[i]) / (_vy[j]-_vy[i]) + _vx[i]) )
                        res = !res;

                }

                if (res == 1) {
                    topRMap->data[r][c] = editValue;
                }
            }
        }
    }

    vx.clear();
    vy.clear();
    for (int i = 0; i < curves.count(); i++) {
        curves.at(i)->setSamples(vx, vy);
    }

    double res = fillDrawMapData(topRMap, RD, 0, &MinV2, &MaxV2);
    showTopMap();
    MPlot->replot();

}
//--------------------------------------------------------------------------
void MainWindow::restoreCells()
{
    vx.clear();
    vy.clear();
    for (int i = 0; i < curves.count(); i++) {
        curves.at(i)->setSamples(vx, vy);
    }

    FOR_ROW_COL_MV {
        topRMap->Drc = editRMap->Drc;
    }

    double res = fillDrawMapData(topRMap, RD, 0, &MinV2, &MaxV2);
    showTopMap();
    MPlot->replot();
}




