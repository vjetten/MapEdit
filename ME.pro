#-------------------------------------------------
#
# Project created by QtCreator 2014-07-06T08:23:10
#
#-------------------------------------------------


QT       += core gui widgets
TARGET = mapedit
TEMPLATE = app
CONFIG += exceptions
CONFIG += warn_off

DEFINES += _CRT_SECURE_NO_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
    meEditMap.cpp \
    mePlotMap.cpp \
    CsfMap.cpp \
    CsfRGBMap.cpp \
    fixture.cpp\
    io.cpp\
    error.cpp\
    canvaspicker.cpp\
    meScaler.cpp

HEADERS  += mainwindow.h\
    canvaspicker.h\
    MEoutput.h\
    global.h\
    include/MEcolors.h \
    include/array.h\
    include/error.h\
    include/fixture.h\
    include/io.h\
    include/masked_raster.h\
    include/raster.h\
    include/pcrtypes.h\
    include/csf.h\
    include/csfattr.h\
    include/csfimpl.h\
    include/csftypes.h\
    include/CsfMap.h\
    include/CsfRGBMap.h


FORMS    += mainwindow.ui

CONFIG(debug, debug|release) {
  MOC_DIR = debug/moc
  OBJECTS_DIR= debug/objs
  UI_DIR= debug/ui
  RCC_DIR= debug/rcc
  DESTDIR = debug
} else {
  MOC_DIR = release/moc
  OBJECTS_DIR= release/objs
  UI_DIR= release/ui
  RCC_DIR= release/rcc
  DESTDIR = release
}

INCLUDEPATH += .\include
INCLUDEPATH += c:\qt\msys64\mingw64\include
INCLUDEPATH += C:\Qt\msys64\mingw64\lib
#INCLUDEPATH += C:\Qt\msys64\mingw64\include\qwt-qt5
#LIBS += c:/qt/msys64/mingw64/lib/libqwt-qt5.dll.a
LIBS += c:/qt/msys64/mingw64/lib/libgdal.dll.a
LIBS += C:/prgc/lisemgit/qwt/git/lib/libqwt.dll.a
INCLUDEPATH += C:/prgc/lisemgit/qwt/git/src

RESOURCES += resources/mapedit.qrc
RC_ICONS = mapedit.ico
