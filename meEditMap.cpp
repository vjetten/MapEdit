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
    cx.clear();
    ry.clear();

    if (op.polystart == op.eData.size()-1) {
        cur = new QwtPlotCurve();
        curves << cur;

        cur->setSymbol(whitedot);
        cur->setBrush(b);
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

    // fill rectangle vectors
    for (int i = op.polystart; i < op.eData.size(); i++) {
        vx << op.eData[op.polystart].cx;
        vy << op.eData[i].cy;
        vx << op.eData[i].cx;
        vy << op.eData[i].cy;
        vx << op.eData[i].cx;
        vy << op.eData[op.polystart].cy;
        vx << op.eData[op.polystart].cx;
        vy << op.eData[op.polystart].cy;

        cx << op.eData[op.polystart].c;
        ry << op.eData[i].r;
        cx << op.eData[i].c;
        ry << op.eData[i].r;
        cx << op.eData[i].c;
        ry << op.eData[op.polystart].r;
        cx << op.eData[op.polystart].c;
        ry << op.eData[op.polystart].r;
    }

    if (op.vvx.size() > 0) {
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
void MainWindow::getCells()
{
    editValue = lineEdit_Value->text().toDouble();
    MinV2 =std::min(MinV2, editValue);
    MaxV2 =std::max(MaxV2, editValue);

    if (op.editCell) {
       for (int i = 0; i < op.eData.size(); i++) {

           int r = op.eData[i].r;
           int c = op.eData[i].c;
           topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
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
                    int r = rb;
                    for(int c = st; c <= en; c++)
                        topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
                } else
                    if (cb == ce) {
                        //horizontal line
                        int st = std::min(rb,re);
                        int en = std::max(rb,re);
                        int c = cb;
                        for(int r = st; r <= en; r++)
                            topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
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

                                topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;

                            }
                        } else {
                            double begin = std::min(c0,cn);
                            double end = std::max(c0,cn);
                            for(double _c = begin; _c <= end; _c+=_dx*0.1)
                            {
                                double _r = r0 + dy*(_c - c0)/dx;
                                int r = _nrRows-1 - int((_r - 0.5*_dx)/_dx);
                                int c = int((_c - 0.5*_dx)/_dx);

                                topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;

                            }
                        }
                    }
            }
        }
    }

    if (op.editRectangle) {
        for (int k = 0; k < op.ccx.count(); k++)  {
            QVector <int> _cx;
            QVector <int> _ry;
            _cx << op.ccx[k];
            _ry << op.rry[k];

            int r0 = *std::min_element(_ry.constBegin(), _ry.constEnd());
            int rn = *std::max_element(_ry.constBegin(), _ry.constEnd());
            int c0 = *std::min_element(_cx.constBegin(), _cx.constEnd());
            int cn = *std::max_element(_cx.constBegin(), _cx.constEnd());
            for (int r = r0 ; r <= rn; r++)
                for (int c = c0 ; c <= cn; c++)
                      topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
        }
    }

    if (op.editPolygon) {
        for (int k = 0; k < op.vvx.count(); k++)  {
            QVector <double> _vx;
            QVector <double> _vy;
            _vx << op.vvx[k];
            _vy << op.vvy[k];

            int n = _vx.size();

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
                    topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
                }
            }
        }
    }

    vx.clear();
    vy.clear();
    for (int i = 0; i < curves.count(); i++) {
        curves.at(i)->setSamples(vx, vy);
    }

    double res = fillDrawMapData(topRMap, RD, &MinV2, &MaxV2);


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

    double res = fillDrawMapData(topRMap, RD, &MinV2, &MaxV2);
    showTopMap();
    MPlot->replot();
}




