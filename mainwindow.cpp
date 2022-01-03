#include "mainwindow.h"
#include "global.h"

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
    openAct = new QAction(QIcon(":/fileopen.png"), "&Open...", this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip("Open a PCRaster map");
    connect(openAct, SIGNAL(triggered()), this, SLOT(openMapFile()));
    toolBar->addAction(openAct);

    //    saveAct = new QAction(QIcon(":/filesave.png"), "&Save...", this);
    //    saveAct->setShortcuts(QKeySequence::Save);
    //    saveAct->setStatusTip("Save ...");
    //    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveMapFile()));
    //    toolBar->addAction(saveAct);

    //    saveasAct = new QAction(QIcon(":/filesaveas.png"), "Save &As...", this);
    //    saveasAct->setShortcuts(QKeySequence::SaveAs);
    //    saveasAct->setStatusTip("Save as ...");
    //    connect(saveasAct, SIGNAL(triggered()), this, SLOT(savefileas()));
    //    toolBar->addAction(saveasAct);
    //    toolBar->addSeparator();

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


    connect(transparency, SIGNAL(sliderMoved(int)), this, SLOT(ssetAlpha(int)));
    connect(spinMinV, SIGNAL(valueChanged(double)),this, SLOT(setMinTopMap()));
    connect(spinMaxV, SIGNAL(valueChanged(double)),this, SLOT(setMinTopMap()));

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
   // qDebug() << files << currentDir;


    processMaps();
}
//--------------------------------------------------------------------
cTMap *MainWindow::ReadMap(QString name)
{
    cTMap *_M = new cTMap(readRaster(name));

    return(_M);
}
//--------------------------------------------------------------------
void MainWindow::processMaps()
{
    if (PathNames.size() > 1) {
        baseRMap = ReadMap(PathNames[0]);
        topRMap = ReadMap(PathNames[1]);
    } else {
        baseRMap = ReadMap(PathNames[0]);
        topRMap = ReadMap(PathNames[0]);
    }
//    editRMap = new cTMap();
//    FOR_ROW_COL_MV {
//        editRMap->Drc = 0;
//    }


    _dx = baseRMap->cellSize()*1.0000000;
    _nrRows = topRMap->nrRows();
    _nrCols = topRMap->nrCols();

    showBaseMap();

    initTopMap();

    showTopMap();
}
//--------------------------------------------------------------------
void MainWindow::saveMapfile(QString name)
{

    QFile fp(name);
    if (!fp.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, QString("MapEdit"),
                             QString("Cannot write file %1:\n%2.").arg(name).arg(fp.errorString()));
        return;
    }
    fp.close();
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
    toolButton_editPolygon->setChecked(false);
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
    toolButton_editCell->setChecked(false);
}
//--------------------------------------------------------------------------
void MainWindow::Show(const QString &results)
{
    QStringList s = results.split('=');
    label_rowcol->setText(s[0]);
    label_value->setText(s[1]);
    label_coor->setText(s[2]);
}
