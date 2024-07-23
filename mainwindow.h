#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include <QApplication>
#include <QMainWindow>
#include <qobject.h>
#include <qrect.h>

//QWT library files
#include <qwt_color_map.h>
#include <qwt_legend.h>
#include <qwt_matrix_raster_data.h>
#include <qwt_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_rescaler.h>
#include <qwt_plot_zoomer.h>
#include <qwt_scale_engine.h>
#include <qwt_scale_widget.h>
#include <qwt_symbol.h>

#include "ui_mainwindow.h"
#include "MEcolors.h"
#include "CsfMap.h"
#include "io.h"
#include "error.h"
#include "canvaspicker.h"
#include "MEoutput.h"

#define MVe 1e18

#define Drc     data[r][c]
#define FOR_ROW_COL_MV for(int r = 0; r < _nrRows; r++)\
    for (int c = 0; c < _nrCols; c++)\
    if(!pcr::isMV(baseRMap->data[r][c]))

#define FOR_ROW_COL for(int r = 0; r < _nrRows; r++)\
    for (int c = 0; c < _nrCols; c++)

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT


public:

    MainWindow(QWidget *parent = 0, bool doBatch = false, QString names = "");
    ~MainWindow();

    void setupMapPlot();
    double fillDrawMapData(cTMap *_M, QwtMatrixRasterData *_RD, double *minv, double *maxv);
    void initBaseMap();
    void showBaseMap();
    void initTopMap();
    void showTopMap();

    int processMaps();
    cTMap *ReadMap(QString name);
    void WriteMap(QString name);
    cTMap *NewMap(double value);
    QErrorMessage *errorMessageDialog;

    void initOP(bool doit);
    void SetToolBar();
    void setStorePath();
    void getStorePath();

    QString currentDir;

    QString ErrorString;

    QwtPlotSpectrogram *drawMap;  // raster map drawing
    QwtPlotSpectrogram *baseMap;  // raster map drawing
    QwtPlot *MPlot;               // plot in which the raster map is drawn
    QwtMatrixRasterData *RD;
    QwtMatrixRasterData *RDb;
    QwtLinearScaleEngine scaleEngine;
    //QwtLogScaleEngine scaleEngine;
    QwtInterval interval;

    QLabel statusLabel;

    QwtLinearColorMap *bpalette, *bpalette1;
    QwtLinearColorMap *dpalette, *dpalette1;

    QwtScaleWidget *rightAxis;
    QwtScaleWidget *leftAxis;
    QwtPlotRescaler *mapRescaler;

    QwtPlotMagnifier *magnifier;
    QwtPlotPanner *panner;
    CanvasPicker *cpicker;

    double _dx, _nrRows, _nrCols, _lly, _llx;
    int vs_scale;

    cTMap *baseRMap;
    cTMap *topRMap;
    cTMap *editRMap;
    QStringList PathNames;
    QString savetype;

    QDialog *helpbox;
    QTextEdit *helptxt;
    QHBoxLayout *helpLayout;

    double MinV1, MaxV1, MinV2, MaxV2, MinTop, MaxTop, MinBase, MaxBase;

    double editValue;

    QList <QwtPlotCurve*> curves;

    QwtPlotCurve *cur;
    QVector <double> vx;
    QVector <double> vy;
    QVector <int> cx;
    QVector <int> ry;
    int _h, _w;

    QBrush b;
    QwtSymbol *whitedot;

    int palette1nr;
    int palette2nr;
    bool editBase;
    bool mapsLoaded;
    int baseMinMaxdistance;
    int topMinMaxdistance;
    QGraphicsScene scene;
    QString AppPath;


  //  bool eventFilter(QObject *obj, QEvent *event);
    void drawSelectionCell();
    void drawSelectionPolygon();
    void drawSelectionLine();
    void drawSelectionRectangle();
    void changePalette(int nr);
    void changePaletteBase();
    void changePaletteTop();
    void setMinMaxBaseMap(int i);
    void setMinMaxTopMap(int i);

public slots:
    void openMapFile();
    void saveMapFile();
    void saveMapFileas();
    void setAlphaTop(int v);
    void setMinBaseMap();
    void setMaxBaseMap();
    void setMinTopMap();
    void setMaxTopMap();
    void Show(const QString &results);
    void drawSelection();
    void getCells();
    void restoreCells();
    void changeSize();
    void zoomPoint();

private slots:

    void on_toolButton_editCell_clicked(bool checked);

    void on_toolButton_editPolygon_clicked(bool checked);

    void on_toolButton_editLine_clicked(bool checked);

    void on_toolButton_editRectangle_clicked(bool checked);

    void on_toolButton_doEdit_clicked();

    void on_toolButton_restoreEdit_clicked();

    void on_toolButton_paletteBase_clicked();

    void on_toolButton_paletteTop_clicked();


    void on_toolButton_openFile_clicked();

    void on_toolButton_saveFile_clicked();

    void on_toolButton_saveFileas_clicked();

    void on_toolButton_resize_clicked();

    void on_toolButton_help_clicked();

    void on_checkBox_editBase_clicked(bool checked);

    void on_toolButton_fixBaseminmax_clicked(bool checked);

    void on_toolButton_fixTopminmax_clicked(bool checked);

    void on_toolButton_doEdit_AVG_clicked();

private:
   //toolbar actions
   QAction *openAct;
   QAction *saveAct;
   QAction *saveasAct;
//   QAction *PaletteTopAct;
//   QAction *PaletteBaseAct;
   QAction *ResizeAct;

//   QAction *shootscreenAct;
//   QAction *shootMscreenAct;
//   QAction *aboutAct;
//   QAction *aboutActI;
};

#endif // MAINWINDOW_H
