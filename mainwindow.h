#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include <QApplication>
#include <QMainWindow>
//#include <QFileDialog>
//QWT library files
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_legend.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_color_map.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_plot_layout.h>
#include <qwt_matrix_raster_data.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_rescaler.h>
#include <qwt_scale_engine.h>
#include <qwt_plot_zoomer.h>
#include <qwt_picker.h>
#include <qwt_wheel.h>


#include "ui_mainwindow.h"
//#include "LisUImapplot.h"
#include "CsfMap.h"
#include "io.h"
#include "error.h"

#define Drc     data[r][c]
#define FOR_ROW_COL_MV for(int r = 0; r < _nrRows; r++)\
    for (int c = 0; c < _nrCols; c++)\
    if(!pcr::isMV(topRMap->data[r][c]))

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0, bool doBatch = false, QString names = "");
    ~MainWindow();

    void setupMapPlot();
    double fillDrawMapData(cTMap *_M, QwtMatrixRasterData *_RD, double type, double *minv, double *maxv);
    void showBaseMap();
    void initTopMap();
    void showTopMap();
    void showMap();
    void processMaps();
    cTMap *ReadMap(QString name);

    void SetToolBar();
    void setStorePath();
    void getStorePath();

    QString currentDir;

    QString ErrorString;

    QwtText title;
    QwtPlotSpectrogram *drawMap;  // raster map drawing
    QwtPlotSpectrogram *baseMap;  // raster map drawing
    QwtPlot *MPlot;               // plot in which the raster map is drawn
    QwtMatrixRasterData *RD;
    QwtMatrixRasterData *RDb;

    QwtLinearColorMap *bpalette, *bpalette1;
    QwtLinearColorMap *dpalette, *dpalette1;

 //   QVector<double> mapData;
    QwtInterval legend;
    QwtScaleWidget *rightAxis;
    QwtPlotRescaler *mapRescaler;
    QwtPlotMagnifier *magnifier;
    QwtPlotPanner *panner;
    QwtPlotZoomer* zoomer;
  //  MyPicker *picker;

    double _dx, _nrRows, _nrCols;

    cTMap *baseRMap;
    cTMap *topRMap;
    cTMap *editRMap;
    QStringList PathNames;

    double MinV1, MaxV1, MinV2, MaxV2, MinTop, MaxTop;
//    int _nrRows;
//    int _nrCols;

public slots:
    void openMapFile();
    void saveMapfile(QString name);
 //   void savefileas();
    void ssetAlpha(int v);
    void setMinTopMap();


private slots:

    void on_toolButtonResetMin_clicked();

    void on_toolButtonResetMax_clicked();

private:
   //toolbar actions
   QAction *openAct;
//   QAction *saveAct;
//   QAction *saveasAct;

//   QAction *shootscreenAct;
//   QAction *shootMscreenAct;
//   QAction *aboutAct;
//   QAction *aboutActI;


//   QAction *fontAct;
//   QAction *fontIncreaseAct;
//   QAction *fontDecreaseAct;
};

#endif // MAINWINDOW_H
