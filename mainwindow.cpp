#include "mainwindow.h"
#include "global.h"
#include "io.h"
#include "csf.h"

output op;

//----------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent, bool doBatch, QString names)
    : QMainWindow(parent)
{
    setupUi(this);
    resize(QGuiApplication::primaryScreen()->availableGeometry().size() * 0.7);
    currentDir = "";

    setWindowTitle("MapEdit v3.32  -  PCRaster map editor (2 Oct 2022)");

    initOP(true);

    errorMessageDialog = new QErrorMessage(this);

    mapsLoaded = false;
    editBase = false;

    int size = qApp->font().pointSize()*0.8;
    whitedot = new QwtSymbol( QwtSymbol::Ellipse, Qt::white, QPen( Qt::black ), QSize( size,size ));
    QColor col(Qt::magenta);
    col.setAlpha(96);
    b.setColor(col);
    b.setStyle(Qt::SolidPattern);//Dense7Pattern);
    helptxt = new QTextEdit();

    getStorePath();

    SetToolBar();

    setupMapPlot();

    if (doBatch)
    {
        QStringList tmp = names.split(";");
        PathNames << tmp[0];
        if (tmp.size() > 1)
            PathNames << tmp[1];
        currentDir = QFileInfo(PathNames[0]).absoluteDir().absolutePath();

        if (!QFileInfo(PathNames[0]).exists())
            return;
        if (PathNames.size() > 1 && !QFileInfo(PathNames[1]).exists())
            return;

//        QSize r = QGuiApplication::primaryScreen()->availableGeometry().size() * 0.7;
//        MPlot->setGeometry(0,0,r.width(),r.height());
//        MPlot->setGeometry(0,0,1080,786);
//        MPlot->repaint();
//        qApp->processEvents();

        // load the map(s)
        if (processMaps() == 0);
            //changeSize();
    }
}
//----------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    setStorePath();
}

//---------------------------------------------------------------------------------------
void MainWindow::initOP(bool doit)
{
    op.editCell = false;
    op.editRectangle= false;
    op.editLine= false;
    op.editPolygon= false;
    op.editStart= false;
    op.editStop= false;
    op.editRestore= false;
    op.editAVG = false;
    op.clicks = 0;
    op.wx = 0;
    op.wy = 0;
    op.wd = 0;

    if (doit) {
        op._M = nullptr;
        op._Mb = nullptr;
        op.nrC = 0;
        op.nrR = 0;
        op._dx = 0;
    }

    op.eData.clear();

    op.vvx.clear();
    op.vvy.clear();
    op.ccx.clear();
    op.rry.clear();
}
//---------------------------------------------------------------------------------------
void MainWindow::SetToolBar()
{
     toolBar->setVisible(false);
//    toolBar->setIconSize(QSize(24,24));

//    openAct = new QAction(QIcon(":/Folder-Open-icon1.png"), "&Open...", this);
//    connect(openAct, SIGNAL(triggered()), this, SLOT(openMapFile()));
//    toolBar->addAction(openAct);

//    saveAct = new QAction(QIcon(":/filesave2X.png"), "&Save...", this);
//    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveMapFile()));
//    toolBar->addAction(saveAct);

//    saveasAct = new QAction(QIcon(":/filesaveas2X.png"), "Save &As...", this);
//    connect(saveasAct, SIGNAL(triggered()), this, SLOT(saveMapFileas()));
//    toolBar->addAction(saveasAct);

//    PaletteBaseAct = new QAction(QIcon(":/palette1.png"), "Change palette of base map", this);
//    connect(PaletteBaseAct, SIGNAL(triggered()), this, SLOT(changePaletteBase()));
//    toolBar->addAction(PaletteBaseAct);

//    PaletteTopAct = new QAction(QIcon(":/palette2.png"), "Change palette of edit map", this);
//    connect(PaletteTopAct, SIGNAL(triggered()), this, SLOT(changePaletteTop()));
//    toolBar->addAction(PaletteTopAct);

//    ResizeAct = new QAction(QIcon(":/adjustsize.png"), "Reset the map size", this);
//    connect(ResizeAct, SIGNAL(triggered()), this, SLOT(changeSize()));
//    toolBar->addAction(ResizeAct);

 //    toolBar->setMovable( false);

    statusLabel.setText("[row,col]  [y,x]");
    statusBar()->addWidget(&statusLabel);

    connect(transparency, SIGNAL(sliderMoved(int)), this, SLOT(setAlphaTop(int)));

    connect(slider_baseMin, SIGNAL(valueChanged(int)),this, SLOT(setMinBaseMap()));
    connect(slider_baseMax, SIGNAL(valueChanged(int)),this, SLOT(setMaxBaseMap()));
    connect(slider_editMin, SIGNAL(valueChanged(int)),this, SLOT(setMinTopMap()));
    connect(slider_editMax, SIGNAL(valueChanged(int)),this, SLOT(setMaxTopMap()));
}
//--------------------------------------------------------------------
void MainWindow::changePaletteTop()
{
    if (op._M == nullptr)
        return;
    changePalette(1);
    drawMap->setColorMap(dpalette);
    rightAxis->setColorMap( drawMap->data()->interval( Qt::ZAxis ), dpalette1);
    showTopMap();
    MPlot->replot();
}

void MainWindow::changePaletteBase()
{
    if (op._M == nullptr)
        return;
    changePalette(0);
    baseMap->setColorMap(bpalette);
    leftAxis->setColorMap( baseMap->data()->interval( Qt::ZAxis ), bpalette1);
    showBaseMap();
    MPlot->replot();
}
//--------------------------------------------------------------------
// loads two different maps or makes a copy of the base map
int MainWindow::processMaps()
{
    if (!mapsLoaded)
        checkBox_editBase->setEnabled(false);

    baseRMap = ReadMap(PathNames[0]);
    _dx = baseRMap->cellSize()*1.0000000;
    _nrRows = (double)baseRMap->nrRows();
    _nrCols = (double)baseRMap->nrCols();
    _llx = baseRMap->west();
    _lly = baseRMap->north() - _nrRows * _dx;

    op.nrC = _nrCols;
    op.nrR = _nrRows;
    op._dx = _dx;
    op._llx = _llx;
    op._lly = _lly;

    QString name1 = QFileInfo(PathNames[0]).fileName();
    QString name2;
    savetype = "PCRaster";

    if (PathNames.size() > 1) {
        checkBox_editBase->setEnabled(false);
        topRMap = ReadMap(PathNames[1]);
        name2 = QFileInfo(PathNames[1]).fileName();
        int i = 0;
        if(topRMap->cellSize() != baseRMap->cellSize()) i++;
        if(topRMap->nrCols() != baseRMap->nrCols()) i++;
        if(topRMap->nrRows() != baseRMap->nrRows()) i++;
        if(topRMap->west() != baseRMap->west()) i++;
        if(topRMap->north() != baseRMap->north()) i++;

        if (i > 0){
            if (i == 1) ErrorString ="Cellsize of the two maps does not match, maps have to have the same cellsize().";
            if (i ==2 || i == 3) ErrorString ="Nr Rows or Columns of the two maps do not match, you have to load maps with the same size.";
            if (i > 3) ErrorString ="Coordinates of the two maps do not match, you have to load maps with the same coordinates.";
            errorMessageDialog->showMessage(ErrorString);
            return 1;
        }

    } else {
        topRMap = ReadMap(PathNames[0]);
        name2 = QFileInfo(PathNames[0]).fileName();
        PathNames << name2;
    }

    if (QFileInfo(PathNames[1]).suffix() == "tif")
        savetype = "GTiff";

    op._Mb = baseRMap;
    op._M = topRMap;

    label_base->setText(QString("Base map: %1").arg(name1));
    label_edit->setText(QString("Edit map: %1").arg(name2));

    editRMap = NewMap(0);
    FOR_ROW_COL_MV {
        editRMap->Drc = topRMap->Drc;
    }

    initBaseMap();

    showBaseMap();

    initTopMap();

    showTopMap();

    slider_baseMin->setValue(1);
    slider_baseMax->setValue(99);
    slider_editMin->setValue(1);
    slider_editMax->setValue(99);

    mapsLoaded = true;
    checkBox_editBase->setEnabled(true);

    return 0;
}
//--------------------------------------------------------------------
cTMap *MainWindow::NewMap(double value)
{
    cTMap *_M = new cTMap();

    _M->MakeMap(baseRMap, value);

    return(_M);
}
//--------------------------------------------------------------------
void MainWindow::getStorePath()
{
    QFile fff(qApp->applicationDirPath() + "/mapedit.ini");
    QStringList  list;

    if (!fff.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    while (!fff.atEnd())
    {
        QString line = fff.readLine();
        if (line.contains('\n'))
            line.remove(line.count()-1,1);
        //remove '/n'
        if (line.isEmpty())
            continue;
        list << line;

    }
    fff.close();

    currentDir = list[0];
}
//---------------------------------------------------------------------------
void MainWindow::setStorePath()
{
    if(currentDir.isEmpty())
        return;

    QFile fff(qApp->applicationDirPath() + "/mapedit.ini");
    if (!fff.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream ts( &fff );
    ts << currentDir;

    fff.close();
}

//--------------------------------------------------------------------------
void MainWindow::Show(const QString &results)
{
    QStringList s = results.split('=');
    statusLabel.setText(QString("Coord: %1 [r,c]:%2 Values: %3").arg(s[0]).arg(s[1]).arg(s[2]));
}
//---------------------------------------------------------------------------

void MainWindow::on_toolButton_editCell_clicked(bool checked)
{
    initOP(false);
    op.editCell = true;
    op.editStart = true;
    op.editStop = false;

    toolButton_editPolygon->setChecked(false);
    toolButton_editLine->setChecked(false);
    toolButton_editRectangle->setChecked(false);
}

void MainWindow::on_toolButton_editPolygon_clicked(bool checked)
{
    initOP(false);
    op.editPolygon = true;
    op.editStart = true;
    op.editStop = false;


    toolButton_editCell->setChecked(false);
    toolButton_editLine->setChecked(false);
    toolButton_editRectangle->setChecked(false);

}

void MainWindow::on_toolButton_editLine_clicked(bool checked)
{
    initOP(false);
    op.editLine = true;
    op.editStart = true;
    op.editStop = false;


    toolButton_editCell->setChecked(false);
    toolButton_editPolygon->setChecked(false);
    toolButton_editRectangle->setChecked(false);
}


void MainWindow::on_toolButton_editRectangle_clicked(bool checked)
{
    initOP(false);
    op.editRectangle = true;
    op.editStart = true;
    op.editStop = false;

    toolButton_editCell->setChecked(false);
    toolButton_editPolygon->setChecked(false);
    toolButton_editLine->setChecked(false);
}
//--------------------------------------------------------------------
void MainWindow::saveMapFile()
{
    if (PathNames.size() == 0)
        return;
    if(!editBase)
        writeRaster(*topRMap, PathNames[1],savetype);
    else
        saveMapFileas();
}
//--------------------------------------------------------------------
void MainWindow::saveMapFileas()
{
    if (PathNames.size() == 0)
        return;
    //   QString ext = "*.map";
    //   if (savetype == "GTiff")
    //       ext = "*.tif";

    QString ext = "PCR (*.map);;GTiff (*.tif)";
//    savetype = "PCRaster";
    QString fileName = QFileDialog::getSaveFileName(this, "Save map under a new name ",currentDir,ext);

    if (QFileInfo(fileName).suffix().contains("tif")) {
        if (savetype == "PCRaster")
            errorMessageDialog->showMessage("Saving PCRaster maps as GeoTiff file, not that EPSG information is not available");
        savetype = "GTiff";
    }

    if (!fileName.isEmpty()) {
        writeRaster(*topRMap, fileName,savetype);
        PathNames.at(1) == fileName;

        label_edit->setText(QString("Edit map: %1").arg(QFileInfo(PathNames[1]).fileName()));
    }
}
//--------------------------------------------------------------------
void MainWindow::openMapFile()
{
    QString filter = "PCR (*.map);;PCR (*.map *.0* *.1* *.2*);;GTiff (*.tif);;all (*.*)";
    QStringList files = QFileDialog::getOpenFileNames(this, QString("Select 1 or 2 Maps"),currentDir,filter);

    if (files.count() > 0) {
        currentDir = QFileInfo(files[0]).absoluteDir().absolutePath();
    }

    PathNames.clear();
    if (files.count() == 0)
        return;

    // only copy the first two selected
    PathNames << files[0];
    if (files.count() > 1)
        PathNames << files[1];

    // load the map(s)    
    if (processMaps() == 0)
        // set the window
        changeSize();
}
//--------------------------------------------------------------------
cTMap *MainWindow::ReadMap(QString name)
{
    cTMap *_M = new cTMap(readRaster(name));

    MAP *m = Mopen(name.toLatin1(),M_READ);
    _M->valueScale = RgetValueScale(m);
    //qDebug() << _M->valueScale;
    Mclose(m);

    return(_M);
}
//--------------------------------------------------------------------


void MainWindow::on_toolButton_doEdit_clicked()
{
    op.editRestore = false;
    getCells();
    initOP(false);
    toolButton_editCell->setChecked(false);
    toolButton_editPolygon->setChecked(false);
    toolButton_editRectangle->setChecked(false);
    toolButton_editLine->setChecked(false);
}


void MainWindow::on_toolButton_doEdit_AVG_clicked()
{
    op.editRestore = false;
    op.editAVG = true;
    getCells();
    initOP(false);
    toolButton_editCell->setChecked(false);
    toolButton_editPolygon->setChecked(false);
    toolButton_editRectangle->setChecked(false);
    toolButton_editLine->setChecked(false);
}

void MainWindow::on_toolButton_restoreEdit_clicked()
{
    op.editRestore = true;
    getCells();
    initOP(false);
    toolButton_editCell->setChecked(false);
    toolButton_editPolygon->setChecked(false);
    toolButton_editRectangle->setChecked(false);
    toolButton_editLine->setChecked(false);
  //  restoreCells();
}

void MainWindow::on_toolButton_paletteBase_clicked()
{
    changePaletteBase();
}


void MainWindow::on_toolButton_paletteTop_clicked()
{
    changePaletteTop();
}


void MainWindow::on_toolButton_openFile_clicked()
{
    openMapFile();
}


void MainWindow::on_toolButton_saveFile_clicked()
{
    saveMapFile();
}


void MainWindow::on_toolButton_saveFileas_clicked()
{
    saveMapFileas();
}


void MainWindow::on_toolButton_resize_clicked()
{
    changeSize();
}


void MainWindow::on_toolButton_help_clicked()
{
    QString filename =":/help1.html";

    QFile file(filename);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    helptxt->setHtml(stream.readAll());

    QTextEdit *view = new QTextEdit(helptxt->toHtml());
    view->createStandardContextMenu();
    view->setWindowTitle("Mapedit help");
    view->setMinimumWidth(640);
    view->setMinimumHeight(480);
    view->setAttribute(Qt::WA_DeleteOnClose);

    view->show();
}


void MainWindow::on_checkBox_editBase_clicked(bool checked)
{
    editBase = checked;
    if (mapsLoaded) {
        if(!editBase) {
            QString name = PathNames[0];
            PathNames[1] == name;
            FOR_ROW_COL_MV {
                topRMap->Drc = baseRMap->Drc;
            }
            label_edit->setText(QString("Edit map: %1").arg(name));
        } else {
            FOR_ROW_COL_MV {
                topRMap->Drc = 0;
            }
            label_edit->setText(QString("Edit map: <edit layer>"));
            PathNames[1] == "empty";
        }
        initTopMap();
        showTopMap();
    }
}


void MainWindow::on_toolButton_fixBaseminmax_clicked(bool checked)
{
    int mi = slider_baseMin->value();
    int ma = slider_baseMax->value();
    if (toolButton_fixBaseminmax->isChecked())
        baseMinMaxdistance = ma - mi;
    else
        baseMinMaxdistance = 1;
}


void MainWindow::on_toolButton_fixTopminmax_clicked(bool checked)
{
    int mi = slider_editMin->value();
    int ma = slider_editMax->value();
    if (toolButton_fixTopminmax->isChecked())
        topMinMaxdistance = ma - mi;
    else
        topMinMaxdistance = 1;
}



