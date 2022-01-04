/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef CANVAS_PICKER_H
#define CANVAS_PICKER_H

#include <qwt_global.h>
#include <qobject.h>
#include <QString>
#include "CsfMap.h"

class QPoint;
class QwtPlot;
class QwtPlotCurve;


//typedef struct xyzLIST {
//    int r;
//    int c;
//    double v;
//} xyzLIST;

class CanvasPicker: public QObject
{
    Q_OBJECT
public:
    CanvasPicker(QwtPlot *plot );
    virtual bool eventFilter( QObject *, QEvent * ) QWT_OVERRIDE;

    void setRowCol(int nrr, int nrc, double dx, cTMap *Map);
    void showinfo(int r, int c, int r1, int c1);

signals:
    void show(const QString &results);
    void draw();
    void get();

private:

    void select( const QPoint & );
    void move( const QPoint & );
    void moveBy( int dx, int dy );
    void release();

    void drawSelection();

    QwtPlot *plot();
    const QwtPlot *plot() const;

};

#endif
