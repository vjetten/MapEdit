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
    PCRlib/_getcell.c\
    PCRlib/_getrow.c\
    PCRlib/_gsomece.c\
    PCRlib/_putcell.c\
    PCRlib/_rputrow.c\
    PCRlib/angle.c\
    PCRlib/attravai.c\
    PCRlib/attrsize.c\
    PCRlib/cellsize.c\
    PCRlib/create2.c\
    PCRlib/csfglob.c\
    PCRlib/csfsup.c\
    PCRlib/delattr.c\
    PCRlib/dumconv.c\
    PCRlib/endian.c\
    PCRlib/file.c\
    PCRlib/filename.c\
    PCRlib/gattrblk.c\
    PCRlib/gattridx.c\
    PCRlib/gcellrep.c\
    PCRlib/gdattype.c\
    PCRlib/getattr.c\
    PCRlib/getx0.c\
    PCRlib/gety0.c\
    PCRlib/ggisfid.c\
    PCRlib/gmaxval.c\
    PCRlib/gminval.c\
    PCRlib/gnrcols.c\
    PCRlib/gnrrows.c\
    PCRlib/gproj.c\
    PCRlib/gputproj.c\
    PCRlib/gvalscal.c\
    PCRlib/gvartype.c\
    PCRlib/gversion.c\
    PCRlib/ismv.c\
    PCRlib/kernlcsf.c\
    PCRlib/legend.c\
    PCRlib/mclose.c\
    PCRlib/mopen.c\
    PCRlib/moreattr.c\
    PCRlib/mperror.c\
    PCRlib/pgisfid.c\
    PCRlib/pmaxval.c\
    PCRlib/pminval.c\
    PCRlib/putallmv.c\
    PCRlib/putattr.c\
    PCRlib/putsomec.c\
    PCRlib/putx0.c\
    PCRlib/puty0.c\
    PCRlib/pvalscal.c\
    PCRlib/rattrblk.c\
    PCRlib/rcomp.c\
    PCRlib/rcoords.c\
    PCRlib/rdup2.c\
    PCRlib/reseterr.c\
    PCRlib/rextend.c\
    PCRlib/rmalloc.c\
    PCRlib/rrowcol.c\
    PCRlib/ruseas.c\
    PCRlib/setangle.c\
    PCRlib/setmv.c\
    PCRlib/setvtmv.c\
    PCRlib/strconst.c\
    PCRlib/strpad.c\
    PCRlib/swapio.c\
    PCRlib/trackmm.c\
    PCRlib/vs2.c\
    PCRlib/vsdef.c\
    PCRlib/vsis.c\
    PCRlib/vsvers.c\
    PCRlib/wattrblk.c \
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
#INCLUDEPATH += C:\Qt\qwtma\src
#LIBS += c:/qt/qwtma/lib/libqwt.dll.a
INCLUDEPATH += C:\Qt\msys64\mingw64\include\qwt-qt5
LIBS += c:/qt/msys64/mingw64/lib/libqwt-qt5.dll.a
LIBS += c:/qt/msys64/mingw64/lib/libgdal.dll.a
RESOURCES += resources/mapedit.qrc
RC_ICONS = mapedit.ico
