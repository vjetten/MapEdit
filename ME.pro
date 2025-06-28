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
    meScaler.cpp \
    pcrlib/mopen.c \
    pcrlib/angle.c \
    pcrlib/dumconv.c \
    pcrlib/_getrow.c \
    pcrlib/_gsomece.c \
    pcrlib/mperror.c \
    pcrlib/pvalscal.c \
    pcrlib/rrowcol.c \
    pcrlib/vsdef.c \
    pcrlib/attravai.c \
    pcrlib/endian.c \
    pcrlib/getx0.c \
    pcrlib/gvalscal.c \
    pcrlib/pgisfid.c \
    pcrlib/rattrblk.c \
    pcrlib/ruseas.c \
    pcrlib/vsis.c \
    pcrlib/attrsize.c \
    pcrlib/file.c \
    pcrlib/gety0.c \
    pcrlib/gvartype.c \
    pcrlib/pmaxval.c \
    pcrlib/rcomp.c \
    pcrlib/setangle.c \
    pcrlib/vsvers.c \
    pcrlib/filename.c \
    pcrlib/ggisfid.c \
    pcrlib/gversion.c \
    pcrlib/pminval.c \
    pcrlib/rcoords.c \
    pcrlib/setmv.c \
    pcrlib/wattrblk.c \
    pcrlib/cellsize.c \
    pcrlib/gattrblk.c \
    pcrlib/gmaxval.c \
    pcrlib/ismv.c \
    pcrlib/putallmv.c \
    pcrlib/rdup2.c \
    pcrlib/setvtmv.c \
    pcrlib/gattridx.c \
    pcrlib/gminval.c \
    pcrlib/kernlcsf.c \
    pcrlib/putattr.c \
    pcrlib/strconst.c \
    pcrlib/create2.c \
    pcrlib/gcellrep.c \
    pcrlib/gnrcols.c \
    pcrlib/legend.c \
    pcrlib/_putcell.c \
    pcrlib/reseterr.c \
    pcrlib/strpad.c \
    pcrlib/csfglob.c \
    pcrlib/gdattype.c \
    pcrlib/gnrrows.c \
    pcrlib/mclose.c \
    pcrlib/putsomec.c \
    pcrlib/rextend.c \
    pcrlib/swapio.c \
    pcrlib/csfsup.c \
    pcrlib/getattr.c \
    pcrlib/gproj.c \
    pcrlib/putx0.c \
    pcrlib/rmalloc.c \
    pcrlib/trackmm.c \
    pcrlib/delattr.c \
    pcrlib/_getcell.c \
    pcrlib/gputproj.c \
    pcrlib/moreattr.c \
    pcrlib/puty0.c \
    pcrlib/_rputrow.c \
    pcrlib/vs2.c

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

INCLUDEPATH += ./include

win32 {
INCLUDEPATH += c:\qt\msys64\mingw64\include
INCLUDEPATH += C:\Qt\msys64\mingw64\lib
#INCLUDEPATH += C:\Qt\msys64\mingw64\include\qwt-qt5
#LIBS += c:/qt/msys64/mingw64/lib/libqwt-qt5.dll.a
LIBS += c:/qt/msys64/mingw64/lib/libgdal.dll.a
LIBS += C:/prgc/lisemgit/qwt/qwt-multiaxes/build/lib/libqwt.dll.a
INCLUDEPATH += C:/prgc/lisemgit/qwt/qwt-multiaxes/src
}

unix {
    INCLUDEPATH += /usr/include
    INCLUDEPATH += /usr/inlcude/qwt
    INCLUDEPATH += /usr/include/gdal
    INCLUDEPATH += /usr/local/qwt-6.4.0-ma/include
    LIBS += -L/usr/local/qwt-6.4.0-ma/lib -lqwt   
    LIBS += -lcurl
    LIBS += -L/usr/lib/x86_64-linux-gnu -lgdal
}

RESOURCES += resources/mapedit.qrc
RC_ICONS = mapedit.ico
