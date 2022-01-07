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
//    QRegExpValidator *Validator = new QRegExpValidator(QRegExp("^[1-9][0-9]*$"),this);// ^[1-9][0-9]{0,2}(?:.[0-9]{3})$"),this);   //[0-9]{1,8}(?.[0-9]{0,6})$"), this);
//    lineEdit_Value->setValidator(Validator);
    palette1nr = 0;
    palette2nr = 0;


    getStorePath();

    SetToolBar();

    setupMapPlot();

    if (doBatch)
    {
        QStringList list = names.split(";");
        PathNames << list;

        processMaps();
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
    op.clicks = 0;

    if (doit) {
        op._M = nullptr;
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
    toolBar->setIconSize(QSize(24,24));

    openAct = new QAction(QIcon(":/Folder-Open-icon1.png"), "&Open...", this);
    connect(openAct, SIGNAL(triggered()), this, SLOT(openMapFile()));
    toolBar->addAction(openAct);

    saveAct = new QAction(QIcon(":/filesave2X.png"), "&Save...", this);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveMapFile()));
    toolBar->addAction(saveAct);

    saveasAct = new QAction(QIcon(":/filesaveas2X.png"), "Save &As...", this);
    connect(saveasAct, SIGNAL(triggered()), this, SLOT(saveMapFileas()));
    toolBar->addAction(saveasAct);

    PaletteBaseAct = new QAction(QIcon(":/palette1.png"), "Save &As...", this);
    connect(PaletteBaseAct, SIGNAL(triggered()), this, SLOT(changePaletteBase()));
    toolBar->addAction(PaletteBaseAct);

    PaletteTopAct = new QAction(QIcon(":/palette2.png"), "Save &As...", this);
    connect(PaletteTopAct, SIGNAL(triggered()), this, SLOT(changePaletteTop()));
    toolBar->addAction(PaletteTopAct);

   // toolBar->addSeparator();

    //    shootscreenAct = new QAction(QIcon(":/screenshots.png"), "make a screendump of the current page", this);
    //    connect(shootscreenAct, SIGNAL(triggered()), this, SLOT(shootScreen()));
    //    toolBar->addAction(shootscreenAct);


    //    aboutActI = new QAction(QIcon(":/Info.png"), "", this);
    //    connect(aboutActI, SIGNAL(triggered()), this, SLOT(aboutInfo()));
    //    toolBar_2->addAction(aboutActI);

    //aboutAct = new QAction(QIcon(":/Info.png"), "", this);
    //connect(aboutAct, SIGNAL(triggered()), this, SLOT(aboutQT()));
    //toolBar_2->addAction(aboutAct);

    //    toolBar_2->setMovable( false);
    //    toolBar->setMovable( false);

    statusLabel.setText("[row,col]  [y,x]");
    statusBar()->addWidget(&statusLabel);

    connect(transparency, SIGNAL(sliderMoved(int)), this, SLOT(ssetAlpha(int)));
    connect(spinMinV, SIGNAL(valueChanged(double)),this, SLOT(setMinTopMap()));
    connect(spinMaxV, SIGNAL(valueChanged(double)),this, SLOT(setMinTopMap()));
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
    _dx = baseRMap->cellSize()*1.0000000;
    _nrRows = baseRMap->nrRows();
    _nrCols = baseRMap->nrCols();

    op.nrC = _nrCols;
    op.nrR = _nrRows;
    op._dx = _dx;
//    int w = MPlot->canvas()->width();
//    int h = MPlot->canvas()->height();
//    qDebug() << w << h;
//    this->setMinimumSize(QSize((int)0.5*w, (int)0.5*h));
//    this->setMaximumSize(QSize(3*w, 2*h));
//    MPlot->canvas()->resize(w+200,h+200);

    qApp->setMaximumSize(QSize(2000, 1200));
    qApp->resize( 1500, 1000 );

    if (PathNames.size() > 1)
        topRMap = ReadMap(PathNames[1]);
    else
        topRMap = NewMap(-1e20);
    op._M = topRMap;


    editRMap = NewMap(0);
    //topRMap->data[(int)_nrRows/2][(int)_nrCols/2]=1;
    FOR_ROW_COL_MV {
        editRMap->Drc = topRMap->Drc;
    }

    initBaseMap();

    showBaseMap();

    initTopMap();

    showTopMap();

    MinTop = MinV1;
    MaxTop = MaxV1;

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
    statusLabel.setText(QString("row,col:%1 Coordinates:%2 Value: %3").arg(s[0]).arg(s[2]).arg(s[1]));
}
//---------------------------------------------------------------------------

void MainWindow::on_toolButtonResetMin_clicked()
{
    MinV1 = MinTop;
    spinMinV->setValue(MinTop);
}


void MainWindow::on_toolButtonResetMax_clicked()
{
    MaxV1 = MaxTop;
    spinMaxV->setValue(MaxTop);
}

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
    if (PathNames.size() > 0)
    writeRaster(*topRMap, PathNames[1],"PCRaster");
}
//--------------------------------------------------------------------
void MainWindow::saveMapFileas()
{
   if (PathNames.size() == 0)
       return;

    QString fileName = QFileDialog::getSaveFileName(this, "Save File as map",
                           currentDir,
                           "*.map");
    if (!fileName.isEmpty()) {
        writeRaster(*topRMap, fileName,"PCRaster");
    }
}
//--------------------------------------------------------------------
void MainWindow::openMapFile()
{
    QString filter = "PCR (*.map);;PCR (*.map *.0* *.1* *.2*);;all (*.*)";
    QStringList files = QFileDialog::getOpenFileNames(
                this, QString("Select PCRaster Maps"),
                currentDir,
                filter);
    if (files.count() > 0)
    {
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

