/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *layout_Map;
    QFrame *frame;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_editMV;
    QLabel *label_4;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QLabel *label_12;
    QRadioButton *radioButton_e1;
    QLabel *label_9;
    QSlider *slider_editMin;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_openFile;
    QToolButton *toolButton_saveFile;
    QToolButton *toolButton_saveFileas;
    QToolButton *toolButton_resize;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton_help;
    QSlider *slider_editMax;
    QToolButton *toolButton_editRectangle;
    QLabel *label_11;
    QFrame *line_3;
    QLabel *label_edit;
    QSlider *slider_baseMin;
    QToolButton *toolButton_doEdit;
    QToolButton *toolButton_fixTopminmax;
    QLabel *label_6;
    QLineEdit *lineEdit_Value;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_8;
    QToolButton *toolButton_restoreEdit;
    QToolButton *toolButton_doEdit_AVG;
    QLabel *label_7;
    QToolButton *toolButton_paletteBase;
    QFrame *line;
    QLabel *label_10;
    QToolButton *toolButton_editLine;
    QToolButton *toolButton_fixBaseminmax;
    QToolButton *toolButton_editPolygon;
    QCheckBox *checkBox_editBase;
    QLineEdit *lineEdit_Value2;
    QLabel *label_13;
    QToolButton *toolButton_editCell;
    QSlider *slider_baseMax;
    QFrame *line_2;
    QToolButton *toolButton_paletteTop;
    QRadioButton *radioButton_e2;
    QLabel *label_base;
    QLabel *label_5;
    QSlider *transparency;
    QMenuBar *menuBar;
    QToolBar *toolBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(910, 712);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Shape::NoFrame);
        frame_2->setFrameShadow(QFrame::Shadow::Plain);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setSpacing(1);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(1, 1, 1, 1);
        layout_Map = new QHBoxLayout();
        layout_Map->setSpacing(0);
        layout_Map->setObjectName(QString::fromUtf8("layout_Map"));

        gridLayout_2->addLayout(layout_Map, 0, 0, 1, 1);


        gridLayout_3->addWidget(frame_2, 0, 1, 1, 1);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Shape::Box);
        frame->setFrameShadow(QFrame::Shadow::Plain);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkBox_editMV = new QCheckBox(frame);
        checkBox_editMV->setObjectName(QString::fromUtf8("checkBox_editMV"));
        checkBox_editMV->setChecked(true);

        gridLayout->addWidget(checkBox_editMV, 14, 0, 1, 6);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 9, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(verticalSpacer, 18, 0, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 8, 1, 1, 1);

        label_12 = new QLabel(frame);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        QFont font;
        font.setItalic(true);
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_12, 20, 5, 1, 1);

        radioButton_e1 = new QRadioButton(frame);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButton_e1);
        radioButton_e1->setObjectName(QString::fromUtf8("radioButton_e1"));
        radioButton_e1->setChecked(true);

        gridLayout->addWidget(radioButton_e1, 12, 0, 1, 1);

        label_9 = new QLabel(frame);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_9, 24, 0, 1, 1);

        slider_editMin = new QSlider(frame);
        slider_editMin->setObjectName(QString::fromUtf8("slider_editMin"));
        slider_editMin->setOrientation(Qt::Orientation::Horizontal);

        gridLayout->addWidget(slider_editMin, 24, 1, 1, 5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolButton_openFile = new QToolButton(frame);
        toolButton_openFile->setObjectName(QString::fromUtf8("toolButton_openFile"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Folder-Open-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_openFile->setIcon(icon);

        horizontalLayout->addWidget(toolButton_openFile);

        toolButton_saveFile = new QToolButton(frame);
        toolButton_saveFile->setObjectName(QString::fromUtf8("toolButton_saveFile"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/filesave2X.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_saveFile->setIcon(icon1);

        horizontalLayout->addWidget(toolButton_saveFile);

        toolButton_saveFileas = new QToolButton(frame);
        toolButton_saveFileas->setObjectName(QString::fromUtf8("toolButton_saveFileas"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/filesaveas2X.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_saveFileas->setIcon(icon2);

        horizontalLayout->addWidget(toolButton_saveFileas);

        toolButton_resize = new QToolButton(frame);
        toolButton_resize->setObjectName(QString::fromUtf8("toolButton_resize"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/adjustsize.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_resize->setIcon(icon3);

        horizontalLayout->addWidget(toolButton_resize);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButton_help = new QToolButton(frame);
        toolButton_help->setObjectName(QString::fromUtf8("toolButton_help"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/question-mark-button2x.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_help->setIcon(icon4);

        horizontalLayout->addWidget(toolButton_help);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 6);

        slider_editMax = new QSlider(frame);
        slider_editMax->setObjectName(QString::fromUtf8("slider_editMax"));
        slider_editMax->setMinimum(1);
        slider_editMax->setValue(99);
        slider_editMax->setOrientation(Qt::Orientation::Horizontal);

        gridLayout->addWidget(slider_editMax, 25, 1, 1, 5);

        toolButton_editRectangle = new QToolButton(frame);
        toolButton_editRectangle->setObjectName(QString::fromUtf8("toolButton_editRectangle"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/editrect.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_editRectangle->setIcon(icon5);
        toolButton_editRectangle->setCheckable(true);

        gridLayout->addWidget(toolButton_editRectangle, 10, 0, 1, 1);

        label_11 = new QLabel(frame);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 21, 1, 1, 1);

        line_3 = new QFrame(frame);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShadow(QFrame::Shadow::Plain);
        line_3->setFrameShape(QFrame::HLine);

        gridLayout->addWidget(line_3, 15, 0, 1, 6);

        label_edit = new QLabel(frame);
        label_edit->setObjectName(QString::fromUtf8("label_edit"));

        gridLayout->addWidget(label_edit, 3, 0, 1, 6);

        slider_baseMin = new QSlider(frame);
        slider_baseMin->setObjectName(QString::fromUtf8("slider_baseMin"));
        slider_baseMin->setToolTipDuration(-1);
        slider_baseMin->setMinimum(1);
        slider_baseMin->setOrientation(Qt::Orientation::Horizontal);

        gridLayout->addWidget(slider_baseMin, 28, 1, 1, 5);

        toolButton_doEdit = new QToolButton(frame);
        toolButton_doEdit->setObjectName(QString::fromUtf8("toolButton_doEdit"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/checkmark.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_doEdit->setIcon(icon6);

        gridLayout->addWidget(toolButton_doEdit, 12, 3, 1, 1);

        toolButton_fixTopminmax = new QToolButton(frame);
        toolButton_fixTopminmax->setObjectName(QString::fromUtf8("toolButton_fixTopminmax"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/clip.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_fixTopminmax->setIcon(icon7);
        toolButton_fixTopminmax->setCheckable(true);

        gridLayout->addWidget(toolButton_fixTopminmax, 21, 5, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 11, 1, 1, 4);

        lineEdit_Value = new QLineEdit(frame);
        lineEdit_Value->setObjectName(QString::fromUtf8("lineEdit_Value"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_Value->sizePolicy().hasHeightForWidth());
        lineEdit_Value->setSizePolicy(sizePolicy1);
        lineEdit_Value->setMaxLength(7);

        gridLayout->addWidget(lineEdit_Value, 12, 1, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 27, 1, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_2, 28, 0, 1, 1);

        label_8 = new QLabel(frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_8, 29, 0, 1, 1);

        toolButton_restoreEdit = new QToolButton(frame);
        toolButton_restoreEdit->setObjectName(QString::fromUtf8("toolButton_restoreEdit"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_restoreEdit->setIcon(icon8);

        gridLayout->addWidget(toolButton_restoreEdit, 12, 5, 1, 1);

        toolButton_doEdit_AVG = new QToolButton(frame);
        toolButton_doEdit_AVG->setObjectName(QString::fromUtf8("toolButton_doEdit_AVG"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/average_icon_155781.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_doEdit_AVG->setIcon(icon9);

        gridLayout->addWidget(toolButton_doEdit_AVG, 12, 4, 1, 1);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 19, 0, 1, 4);

        toolButton_paletteBase = new QToolButton(frame);
        toolButton_paletteBase->setObjectName(QString::fromUtf8("toolButton_paletteBase"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/palette.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_paletteBase->setIcon(icon10);

        gridLayout->addWidget(toolButton_paletteBase, 27, 0, 1, 1);

        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShadow(QFrame::Shadow::Plain);
        line->setFrameShape(QFrame::HLine);

        gridLayout->addWidget(line, 7, 0, 1, 6);

        label_10 = new QLabel(frame);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_10, 25, 0, 1, 1);

        toolButton_editLine = new QToolButton(frame);
        toolButton_editLine->setObjectName(QString::fromUtf8("toolButton_editLine"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/editline.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_editLine->setIcon(icon11);
        toolButton_editLine->setCheckable(true);

        gridLayout->addWidget(toolButton_editLine, 9, 0, 1, 1);

        toolButton_fixBaseminmax = new QToolButton(frame);
        toolButton_fixBaseminmax->setObjectName(QString::fromUtf8("toolButton_fixBaseminmax"));
        toolButton_fixBaseminmax->setIcon(icon7);
        toolButton_fixBaseminmax->setCheckable(true);

        gridLayout->addWidget(toolButton_fixBaseminmax, 27, 5, 1, 1);

        toolButton_editPolygon = new QToolButton(frame);
        toolButton_editPolygon->setObjectName(QString::fromUtf8("toolButton_editPolygon"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/editpoly.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_editPolygon->setIcon(icon12);
        toolButton_editPolygon->setCheckable(true);

        gridLayout->addWidget(toolButton_editPolygon, 11, 0, 1, 1);

        checkBox_editBase = new QCheckBox(frame);
        checkBox_editBase->setObjectName(QString::fromUtf8("checkBox_editBase"));
        checkBox_editBase->setEnabled(false);

        gridLayout->addWidget(checkBox_editBase, 4, 0, 1, 6);

        lineEdit_Value2 = new QLineEdit(frame);
        lineEdit_Value2->setObjectName(QString::fromUtf8("lineEdit_Value2"));
        sizePolicy1.setHeightForWidth(lineEdit_Value2->sizePolicy().hasHeightForWidth());
        lineEdit_Value2->setSizePolicy(sizePolicy1);
        lineEdit_Value2->setMaxLength(7);

        gridLayout->addWidget(lineEdit_Value2, 13, 1, 1, 4);

        label_13 = new QLabel(frame);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font);
        label_13->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_13, 20, 0, 1, 1);

        toolButton_editCell = new QToolButton(frame);
        toolButton_editCell->setObjectName(QString::fromUtf8("toolButton_editCell"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/editcell.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_editCell->setIcon(icon13);
        toolButton_editCell->setCheckable(true);

        gridLayout->addWidget(toolButton_editCell, 8, 0, 1, 1);

        slider_baseMax = new QSlider(frame);
        slider_baseMax->setObjectName(QString::fromUtf8("slider_baseMax"));
        slider_baseMax->setMinimum(1);
        slider_baseMax->setValue(99);
        slider_baseMax->setOrientation(Qt::Orientation::Horizontal);

        gridLayout->addWidget(slider_baseMax, 29, 1, 1, 5);

        line_2 = new QFrame(frame);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShadow(QFrame::Shadow::Plain);
        line_2->setFrameShape(QFrame::HLine);

        gridLayout->addWidget(line_2, 1, 0, 1, 6);

        toolButton_paletteTop = new QToolButton(frame);
        toolButton_paletteTop->setObjectName(QString::fromUtf8("toolButton_paletteTop"));
        toolButton_paletteTop->setIcon(icon10);

        gridLayout->addWidget(toolButton_paletteTop, 21, 0, 1, 1);

        radioButton_e2 = new QRadioButton(frame);
        buttonGroup->addButton(radioButton_e2);
        radioButton_e2->setObjectName(QString::fromUtf8("radioButton_e2"));

        gridLayout->addWidget(radioButton_e2, 13, 0, 1, 1);

        label_base = new QLabel(frame);
        label_base->setObjectName(QString::fromUtf8("label_base"));
        QPalette palette;
        label_base->setPalette(palette);
        QFont font1;
        font1.setBold(false);
        label_base->setFont(font1);

        gridLayout->addWidget(label_base, 5, 0, 1, 6);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 10, 1, 1, 1);

        transparency = new QSlider(frame);
        transparency->setObjectName(QString::fromUtf8("transparency"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(transparency->sizePolicy().hasHeightForWidth());
        transparency->setSizePolicy(sizePolicy2);
        transparency->setMinimum(1);
        transparency->setMaximum(255);
        transparency->setValue(128);
        transparency->setSliderPosition(128);
        transparency->setOrientation(Qt::Orientation::Horizontal);

        gridLayout->addWidget(transparency, 20, 1, 1, 3);


        gridLayout_3->addWidget(frame, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 910, 25));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMovable(false);
        toolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MapEdit v3.2.1  -  PCRaster map editor (20 Mar 2022)", nullptr));
        checkBox_editMV->setText(QCoreApplication::translate("MainWindow", "Allow editng Missing Values", nullptr));
#if QT_CONFIG(tooltip)
        label_4->setToolTip(QCoreApplication::translate("MainWindow", "left mouse to digitize , right mouse to end the line", nullptr));
#endif // QT_CONFIG(tooltip)
        label_4->setText(QCoreApplication::translate("MainWindow", "Edit lines", nullptr));
#if QT_CONFIG(tooltip)
        label_3->setToolTip(QCoreApplication::translate("MainWindow", "left mouse selects a single cell", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("MainWindow", "Edit single cells", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        radioButton_e1->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "Min", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_openFile->setToolTip(QCoreApplication::translate("MainWindow", "Open 1 or 2 maps", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_openFile->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_saveFile->setToolTip(QCoreApplication::translate("MainWindow", "Save edit layer map", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_saveFile->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_saveFileas->setToolTip(QCoreApplication::translate("MainWindow", "Save edit layer map under a new name", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_saveFileas->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_resize->setToolTip(QCoreApplication::translate("MainWindow", "Set zoom to the whole map", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_resize->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_help->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_editRectangle->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Edit Map legend", nullptr));
        label_edit->setText(QCoreApplication::translate("MainWindow", "Edit map: <empty>", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_doEdit->setToolTip(QCoreApplication::translate("MainWindow", "Replace selection with this value", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_doEdit->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_fixTopminmax->setToolTip(QCoreApplication::translate("MainWindow", "fix distance min - max sliders", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_fixTopminmax->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(tooltip)
        label_6->setToolTip(QCoreApplication::translate("MainWindow", "left mouse to dgitize, right mouse to end the polygon", nullptr));
#endif // QT_CONFIG(tooltip)
        label_6->setText(QCoreApplication::translate("MainWindow", "Edit polygons", nullptr));
        lineEdit_Value->setInputMask(QString());
        lineEdit_Value->setText(QCoreApplication::translate("MainWindow", "1.0", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Base map legend", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Min", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Max", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_restoreEdit->setToolTip(QCoreApplication::translate("MainWindow", "Restore original values in selection", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_restoreEdit->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_doEdit_AVG->setToolTip(QCoreApplication::translate("MainWindow", "Replace the selection with the average of values inside", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_doEdit_AVG->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Transparancy of the edited map:", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_paletteBase->setToolTip(QCoreApplication::translate("MainWindow", "Change palette of base map", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_paletteBase->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Max", nullptr));
        toolButton_editLine->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_fixBaseminmax->setToolTip(QCoreApplication::translate("MainWindow", "fix distance min - max sliders", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_fixBaseminmax->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_editPolygon->setText(QCoreApplication::translate("MainWindow", "P", nullptr));
        checkBox_editBase->setText(QCoreApplication::translate("MainWindow", "Edit an empty layer", nullptr));
        lineEdit_Value2->setText(QCoreApplication::translate("MainWindow", "0.0", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        toolButton_editCell->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_paletteTop->setToolTip(QCoreApplication::translate("MainWindow", "Change palette of edit map", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_paletteTop->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        radioButton_e2->setText(QString());
        label_base->setText(QCoreApplication::translate("MainWindow", "Base map: <empty>", nullptr));
#if QT_CONFIG(tooltip)
        label_5->setToolTip(QCoreApplication::translate("MainWindow", "click opposite corners", nullptr));
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("MainWindow", "Edit rectangles", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "MapEdit v3.0  -  PCRaster map editor (12 jan 2022)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
