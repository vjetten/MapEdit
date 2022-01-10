#include "mainwindow.h"
#include "global.h"
#include "io.h"

output op;

//----------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent, bool doBatch, QString names)
    : QMainWindow(parent)
{
    setupUi(this);

    currentDir = "";

    initOP(true);

    int size = qApp->font().pointSize()*0.8;
    whitedot = new QwtSymbol( QwtSymbol::Ellipse, Qt::white, QPen( Qt::black ), QSize( size,size ));
    QColor col(Qt::magenta);
    col.setAlpha(96);
    b.setColor(col);
    b.setStyle(Qt::SolidPattern);//Dense7Pattern);

    getStorePath();

    SetToolBar();

    setupMapPlot();

    if (doBatch)
    {
        QStringList list = names.split(";");
        PathNames << list;

        processMaps();
    }

//    helpbox = new QDialog();
//    helpbox->resize(1080, 600);
//    helpbox->setWindowTitle("Mapedit elp");
//    helpLayout = new QHBoxLayout(helpbox);
    helptxt = new QTextEdit();
//    helpLayout->addWidget(helptxt);
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

    connect(slider_baseMin, SIGNAL(valueChanged(int)),this, SLOT(setMinMaxBaseMap()));
    connect(slider_baseMax, SIGNAL(valueChanged(int)),this, SLOT(setMinMaxBaseMap()));
    connect(slider_editMin, SIGNAL(valueChanged(int)),this, SLOT(setMinMaxTopMap()));
    connect(slider_editMax, SIGNAL(valueChanged(int)),this, SLOT(setMinMaxTopMap()));
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
void MainWindow::processMaps()
{
    baseRMap = ReadMap(PathNames[0]);
    op._Mb = baseRMap;
    _dx = baseRMap->cellSize()*1.0000000;
    _nrRows = baseRMap->nrRows();
    _nrCols = baseRMap->nrCols();

    op.nrC = _nrCols;
    op.nrR = _nrRows;
    op._dx = _dx;

    QString name1 = QFileInfo(PathNames[0]).fileName();
    QString name2;
    savetype = "PCRaster";

    if (PathNames.size() > 1) {
        topRMap = ReadMap(PathNames[1]);
        name2 = QFileInfo(PathNames[1]).fileName();
        if (QFileInfo(PathNames[1]).suffix() == "tif")
            savetype = "GTiff";
    } else {
        topRMap = NewMap(0);//-1e20);
        name2 = "<empty>";//"Empty map to edit!";
        if (QFileInfo(PathNames[0]).suffix() == "tif")
            savetype = "GTiff";
    }
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

    MPlot->replot();
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

    toolButton_editPolygon->setChecked(false);
    toolButton_editLine->setChecked(false);
    toolButton_editRectangle->setChecked(false);
}

void MainWindow::on_toolButton_editPolygon_clicked(bool checked)
{
    initOP(false);
    op.editPolygon = true;
    op.editStart = true;

    toolButton_editCell->setChecked(false);
    toolButton_editLine->setChecked(false);
    toolButton_editRectangle->setChecked(false);

}

void MainWindow::on_toolButton_editLine_clicked(bool checked)
{
    initOP(false);
    op.editLine = true;
    op.editStart = true;

    toolButton_editCell->setChecked(false);
    toolButton_editPolygon->setChecked(false);
    toolButton_editRectangle->setChecked(false);
}


void MainWindow::on_toolButton_editRectangle_clicked(bool checked)
{
    initOP(false);
    op.editRectangle = true;
    op.editStart = true;

    toolButton_editCell->setChecked(false);
    toolButton_editPolygon->setChecked(false);
    toolButton_editLine->setChecked(false);
}
//--------------------------------------------------------------------
void MainWindow::saveMapFile()
{
    if (PathNames.size() > 1)
        writeRaster(*topRMap, PathNames[1],savetype);
    else
        saveMapFileas();
}
//--------------------------------------------------------------------
void MainWindow::saveMapFileas()
{
   if (PathNames.size() == 0)
       return;
   QString ext = "*.map";
   if (savetype == "GTiff")
       ext = "*.tif";

    QString fileName = QFileDialog::getSaveFileName(this, "Save map under a new name ",currentDir,ext);
    if (!fileName.isEmpty()) {
        writeRaster(*topRMap, fileName,savetype);
        if (PathNames.size() == 1)
            PathNames << fileName;
        else
            PathNames.at(1) == fileName;

        label_edit->setText(QString("Edit map: %1").arg(QFileInfo(PathNames[1]).fileName()));
        qDebug() << PathNames;
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

    if (files.count() == 0)
        return;

    PathNames.clear();
    PathNames << files;

    processMaps();
}
//--------------------------------------------------------------------
cTMap *MainWindow::ReadMap(QString name)
{
    cTMap *_M = new cTMap(readRaster(name));

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


