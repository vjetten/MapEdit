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

    initOP();

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
void MainWindow::initOP()
{
    op.editCell = false;
    op.editRectangle= false;
    op.editLine= false;
    op.editPolygon= false;
    op.editStart= false;
    op.editStop= false;
    op.clicks = 0;

    op._M = NULL;
    op.nrC = 0;
    op.nrR = 0;
    op._dx = 0;;

    op.eData.clear();
}
//---------------------------------------------------------------------------------------
void MainWindow::SetToolBar()
{
    toolBar->setIconSize(QSize(24,24));

    openAct = new QAction(QIcon(":/Folder-Open-icon1.png"), "&Open...", this);
  //  openAct->setShortcuts(QKeySequence::Open);
 //   openAct->setStatusTip("Open a PCRaster map");
    connect(openAct, SIGNAL(triggered()), this, SLOT(openMapFile()));
    toolBar->addAction(openAct);

    saveAct = new QAction(QIcon(":/filesave2X.png"), "&Save...", this);
 //   saveAct->setShortcuts(QKeySequence::Save);
  //  saveAct->setStatusTip("Save ...");
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveMapFile()));
    toolBar->addAction(saveAct);

    saveasAct = new QAction(QIcon(":/filesaveas2X.png"), "Save &As...", this);
//    saveasAct->setShortcuts(QKeySequence::SaveAs);
 //   saveasAct->setStatusTip("Save as ...");
    connect(saveasAct, SIGNAL(triggered()), this, SLOT(saveMapFileas()));
    toolBar->addAction(saveasAct);


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
void MainWindow::processMaps()
{
    baseRMap = ReadMap(PathNames[0]);
    topRMap = ReadMap(PathNames[1]);
    editRMap = NewMap(0);

    _dx = baseRMap->cellSize()*1.0000000;
    _nrRows = topRMap->nrRows();
    _nrCols = topRMap->nrCols();

    FOR_ROW_COL_MV {
        editRMap->Drc = topRMap->Drc;
    }

    showBaseMap();

    initTopMap();

    showTopMap();

}
//--------------------------------------------------------------------
cTMap *MainWindow::NewMap(double value)
{
    cTMap *_M = new cTMap();

    _M->MakeMap(topRMap, value);

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
    statusLabel.setText(QString("row,col:%1 Coordinates:%2 Value:%3").arg(s[0]).arg(s[2]).arg(s[1]));
}
//---------------------------------------------------------------------------

void MainWindow::on_toolButtonResetMin_clicked()
{
    MinV2 = MinTop;
    spinMinV->setValue(MinTop);
}


void MainWindow::on_toolButtonResetMax_clicked()
{
    MaxV2 = MaxTop;
    spinMaxV->setValue(MaxTop);
}

void MainWindow::on_toolButton_editCell_clicked(bool checked)
{
    // if map loaded!
    op.editCell = true;
    op.editRectangle = false;
    op.editLine = false;
    op.editPolygon = false;
    op.editStart = true;
    op.editStop = false;
    op.clicks = 0;
    op.eData.clear();

    toolButton_editPolygon->setChecked(false);
    toolButton_editLine->setChecked(false);
    toolButton_editRectangle->setChecked(false);
}

void MainWindow::on_toolButton_editPolygon_clicked(bool checked)
{
    op.editCell = false;
    op.editRectangle = false;
    op.editLine = false;
    op.editPolygon = true;
    op.editStart = true;
    op.editStop = false;
    op.clicks = 0;
    op.eData.clear();

    toolButton_editCell->setChecked(false);
    toolButton_editLine->setChecked(false);
    toolButton_editRectangle->setChecked(false);

}

void MainWindow::on_toolButton_editLine_clicked(bool checked)
{
    op.editCell = false;
    op.editRectangle = false;
    op.editLine = true;
    op.editPolygon = false;
    op.editStart = true;
    op.editStop = false;
    op.clicks = 0;
    op.eData.clear();

    toolButton_editCell->setChecked(false);
    toolButton_editPolygon->setChecked(false);
    toolButton_editRectangle->setChecked(false);
}


void MainWindow::on_toolButton_editRactangle_clicked(bool checked)
{
    op.editCell = false;
    op.editRectangle = true;
    op.editLine = false;
    op.editPolygon = false;
    op.editStart = true;
    op.editStop = false;
    op.clicks = 0;
    op.eData.clear();

    toolButton_editCell->setChecked(false);
    toolButton_editPolygon->setChecked(false);
    toolButton_editLine->setChecked(false);
}
//--------------------------------------------------------------------
void MainWindow::saveMapFile()
{
    writeRaster(*topRMap, PathNames[1],"PCRaster");
}
//--------------------------------------------------------------------
void MainWindow::saveMapFileas()
{
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
    if (PathNames.size() == 1) {
        PathNames << files;
    }

//    qDebug() << files << currentDir;

    processMaps();
}
//--------------------------------------------------------------------
cTMap *MainWindow::ReadMap(QString name)
{
    cTMap *_M = new cTMap(readRaster(name));

    return(_M);
}

void MainWindow::on_toolButton_3_clicked()
{
    openMapFile();
}


void MainWindow::on_toolButton_4_clicked()
{
    saveMapFile();
}


void MainWindow::on_toolButton_5_clicked()
{
    saveMapFileas();
}


void MainWindow::on_toolButton_doEdit_clicked()
{
    getCells();
}


void MainWindow::on_toolButton_restoreEdit_clicked()
{
    restoreCells();
}

