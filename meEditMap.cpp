#include "mainwindow.h"
#include "global.h"

#define MV(r,c) pcr::isMV(topRMap->data[r][c])
#define MVchecked(r,c) checkBox_editMV->isChecked() ? false : pcr::isMV(topRMap->data[r][c])

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
    double dx[5] = {-0.5,+0.5,+0.5,-0.5,-0.5};
    double dy[5] = {-0.5,-0.5,+0.5,+0.5,-0.5};



    cur = new QwtPlotCurve();
    curves << cur;

    cur->setPen( Qt::magenta, 2 );
    cur->setStyle( QwtPlotCurve::Lines );
    cur->setBrush(b);
    cur->attach( MPlot );
    cur->setAxes(QwtAxis::XBottom,QwtAxis::YLeft);
   // MPlot->setAxisScale( QwtAxis::XBottom, op._llx, op._llx+(double)op._nrRows*op._dx*w/h);//, op._dx*10);
   // MPlot->setAxisScale( QwtAxis::YLeft, op._lly, op._lly+(double)op._nrRows*op._dx);//, op._dx*10);

    vx.clear();
    vy.clear();

    int l = op.eData.size()-1;

    for (int i = 0; i < 5; i++) {
        vx << op.eData[l].cx+dx[i]*_dx;
        vy << op.eData[l].cy+dy[i]*_dx;
    }

    for (int i = 0; i < 5 ; i++) { //vx.size()
        double vxi = vx.at(i)+_llx;
        vx.replace(i, vxi);
        double vyi = vy.at(i)+_lly;
        vy.replace(i, vyi);
    }
    cur->setSamples(vx,vy);

    // QPolygonF points;
    // for (int i = 0; i < vx.size(); i++ )
    //     points << QPointF(vx.at(i), vy.at(i));

    // cur->setSamples(points);
/*
    double vx[5];
    double vy[5];

    cur = new QwtPlotCurve();
    curves << cur;

    cur->setPen( Qt::magenta, 2 );
    cur->setStyle( QwtPlotCurve::Lines );
    cur->setBrush(b);
    cur->attach( MPlot );
    cur->setAxes(MPlot->xBottom, MPlot->yLeft);

    //vx.clear();
    //vy.clear();

    int l = op.eData.size()-1;

    for (int i = 0; i < 5; i++) {
        vx[i] = op.eData[l].cx+dx[i]*_dx;
        vy[i] = op.eData[l].cy+dy[i]*_dx;
    }

    for (int i = 0; i < 5 ; i++) { //vx.size()
        double vxi = vx[i]+_llx;//vx.at(i)+_llx;
        //vx.replace(i, vxi);
        vx[i] = vxi;
        double vyi = vy[i] + _lly;//vy.at(i)+_lly;
        //vy.replace(i, vyi);
        vy[i] = vyi;
    }

    cur->setSamples(vx,vy,5);
    */
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
        cur->setAxes(QwtAxis::XBottom,QwtAxis::YLeft);

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

    for (int i = 0; i < vx.size(); i++) {
        double vxi = vx.at(i)+_llx;
        vx.replace(i, vxi);
        double vyi = vy.at(i)+_lly;
        vy.replace(i, vyi);
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
         cur->setAxes(QwtAxis::XBottom,QwtAxis::YLeft);

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
    for (int i = 0; i < vx.size(); i++) {
        double vxi = vx.at(i)+_llx;
        vx.replace(i, vxi);
        double vyi = vy.at(i)+_lly;
        vy.replace(i, vyi);
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
         cur->setAxes(QwtAxis::XBottom,QwtAxis::YLeft);

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
    for (int i = 0; i < vx.size(); i++) {
        double vxi = vx.at(i)+_llx;
        vx.replace(i, vxi);
        double vyi = vy.at(i)+_lly;
        vy.replace(i, vyi);
    }


    cur->setSamples(vx,vy);
}
//--------------------------------------------------------------------------
void MainWindow::getCells()
{
    if (radioButton_e1->isChecked())
        editValue = lineEdit_Value->text().toDouble();
    else
        editValue = lineEdit_Value2->text().toDouble();

    if (op.editCell) {
        if (op.editAVG) {
            double sum = 0;
            double nn = 0;
            for (int i = 0; i < op.eData.size(); i++) {
                int r = op.eData[i].r;
                int c = op.eData[i].c;
                if (!MV(r,c)) {
                    sum += topRMap->data[r][c];
                    nn += 1.0;
                }
            }
            if (nn > 0)
                editValue = sum/nn;
        }


        for (int i = 0; i < op.eData.size(); i++) {
            int r = op.eData[i].r;
            int c = op.eData[i].c;
            if (checkBox_editMV->isChecked())
                topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
            else
                if (!MV(r,c))
                    topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
        }
    }

    if (op.editLine) {
        if (op.editAVG) {
            double sum = 0;
            double nn = 0;

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
                            if (!MV(r,c)) {
                                sum = sum + topRMap->data[r][c];
                                nn += 1.0;
                            }
                    } else
                        if (cb == ce) {
                            //horizontal line
                            int st = std::min(rb,re);
                            int en = std::max(rb,re);
                            int c = cb;
                            for(int r = st; r <= en; r++)
                                if (!MV(r,c)) {
                                    sum = sum + topRMap->data[r][c];
                                    nn += 1.0;
                                }

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
                                    if (!MV(r,c)) {
                                        sum = sum + topRMap->data[r][c];
                                        nn += 1.0;
                                    }


                                }
                            } else {
                                double begin = std::min(c0,cn);
                                double end = std::max(c0,cn);
                                for(double _c = begin; _c <= end; _c+=_dx*0.1)
                                {
                                    double _r = r0 + dy*(_c - c0)/dx;
                                    int r = _nrRows-1 - int((_r - 0.5*_dx)/_dx);
                                    int c = int((_c - 0.5*_dx)/_dx);
                                    if (!MV(r,c)) {
                                        sum = sum + topRMap->data[r][c];
                                        nn += 1.0;
                                    }

                                }
                            }
                        }
                }
            } // k
            if (nn > 0)
                editValue = sum/nn;
        } // editAVG

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
                    for(int c = st; c <= en; c++) {
                        if (checkBox_editMV->isChecked())
                            topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
                        else
                        if (!MV(r,c))
                            topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
                    }
                } else
                    if (cb == ce) {
                        //horizontal line
                        int st = std::min(rb,re);
                        int en = std::max(rb,re);
                        int c = cb;
                        for(int r = st; r <= en; r++){
                            if (checkBox_editMV->isChecked())
                                topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
                            else
                            if (!MV(r,c))
                                topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
                        }
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
                                if (checkBox_editMV->isChecked())
                                    topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
                                else
                                    if (!MV(r,c))
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
                                if (checkBox_editMV->isChecked())
                                    topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
                                else
                                    if (!MV(r,c))
                                        topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
                            }
                        }
                    }
            }
        } // k
    } // editline

    if (op.editRectangle) {

        if (op.editAVG) {
            double sum = 0;
            double nn = 0;
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
                        if (!MV(r,c)) {
                            sum += topRMap->data[r][c];
                            nn += 1.0;
                        }
            }
            if (nn > 0)
                editValue = sum/nn;
        }


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
                for (int c = c0 ; c <= cn; c++) {
                    if (checkBox_editMV->isChecked())
                        topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
                    else
                        if (!MV(r,c))
                            topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
                }
        }

    }

    if (op.editPolygon) {

        if (op.editAVG) {
            double sum = 0;
            double nn = 0;
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
                        sum = sum + topRMap->data[r][c];
                        nn += 1.0;
                    }
                }
            } // k

            if (nn > 0)
                editValue = sum / nn;
        }


        for (int k = 0; k < op.vvx.count(); k++)  {
            QVector <double> _vx;
            QVector <double> _vy;
            _vx << op.vvx[k];
            _vy << op.vvy[k];

            int n = _vx.size();

            FOR_ROW_COL {
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
                    if (checkBox_editMV->isChecked())
                        topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
                    else
                        if (!MV(r,c))
                            topRMap->data[r][c] = op.editRestore ? editRMap->Drc : editValue;
                }
            }
        } // k


    } // polygon

    vx.clear();
    vy.clear();
    for (int i = 0; i < curves.count(); i++) {
        curves.at(i)->setSamples(vx, vy);
    }

    double res = fillDrawMapData(topRMap, RD, &MinV2, &MaxV2);
    MinTop = MinV2;
    MaxTop = MaxV2;
    showTopMap();
    setMinMaxTopMap(1);
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




