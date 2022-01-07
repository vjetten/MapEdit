#ifndef MECOLORS_H
#define MECOLORS_H

#include "mainwindow.h"

//---------------------------------------------------------------------------
#define BGc "#eeeeee" // background grey for missing value in maps

//http://www.color-hex.com/color/
//http://colorbrewer2.org/
//http://www.colorschemer.com


//------------------------------------------
class colorMap1: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 220,220,220,0 );
        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMap1():
        QwtLinearColorMap( QColor(BGc),QColor("#bd0026") )
    {
    addColorStop(0.00, QColor("#ffffb2"));
    addColorStop(0.25, QColor("#fecc5c"));
    addColorStop(0.50, QColor("#fd8d3c"));
    addColorStop(0.75, QColor("#f03b20"));
    }
};
//------------------------------------------
class colorMap2: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 220,220,220,0 );
        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMap2():
        QwtLinearColorMap( QColor(BGc),QColor("#2c3898") )
    {
    addColorStop(0.00, QColor("#ffff99"));
    addColorStop(0.15, QColor("#ffff51"));
    addColorStop(0.30, QColor("#c7e55a"));
    addColorStop(0.50, QColor("#32b1df"));
    addColorStop(0.75, QColor("#3271ca"));
    }
};
//------------------------------------------
class colorMap3: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 220,220,220,0 );
        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMap3():
        QwtLinearColorMap( QColor(BGc),QColor("#2b83ba") )
    {
    addColorStop(0.00, QColor("#d7191c"));
    addColorStop(0.25, QColor("#fdae61"));
    addColorStop(0.50, QColor("#fdfd7e"));
    addColorStop(0.75, QColor("#abdda4"));
    }
};
//------------------------------------------
class colorMap4: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 220,220,220,0 );
        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMap4():
        QwtLinearColorMap( QColor(BGc),QColor("#d7191c") )
    {
    addColorStop(0.00, QColor("#2b83ba"));
    addColorStop(0.25, QColor("#a4ddd9"));
    addColorStop(0.50, QColor("#ffffef"));
    addColorStop(0.75, QColor("#d3b03e"));
    }
};
//------------------------------------------
class colorMap5: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 220,220,220,0 );
        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMap5():
        QwtLinearColorMap( QColor(BGc),QColor("#FF0000") )
    {
    addColorStop(0.00, QColor("#616ca2"));
    addColorStop(0.30, QColor("#50B547"));
    addColorStop(0.50, QColor("#FFFFFF"));
    addColorStop(0.70, QColor("#ffff88"));
    }
};
//------------------------------------------
class colorMap6: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 220,220,220,0 );
        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMap6():
        QwtLinearColorMap( QColor(BGc),QColor("#0868ac") )
    {
    addColorStop(0.00, QColor("#f0f9e8"));
    addColorStop(0.25, QColor("#bae4bc"));
    addColorStop(0.50, QColor("#7bccc4"));
    addColorStop(0.75, QColor("#43a2ca"));
    }
};
//------------------------------------------
class colorMapRainbow: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value < -1e19 )
            return qRgba( 220,220,220,0 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapRainbow():
        QwtLinearColorMap(  QColor("#ce0c82"), QColor("#ff0000"))
    {
        addColorStop(0.000,QColor("#ce0c82"));
        addColorStop(0.091,QColor("#800cce"));
        addColorStop(0.182,QColor("#1f0cce"));
        addColorStop(0.273,QColor("#0c5bce"));
        addColorStop(0.364,QColor("#0c99ce"));
        addColorStop(0.455,QColor("#2ece0c"));
        addColorStop(0.545,QColor("#bae806"));
        addColorStop(0.636,QColor("#feff00"));
        addColorStop(0.727,QColor("#ffcd00"));
        addColorStop(0.818,QColor("#ff9a00"));
        addColorStop(0.909,QColor("#ff6000"));
        addColorStop(1.000,QColor("#ff0000"));
    }
};
//------------------------------------------
class colorMapGray: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 220,220,220,0 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapGray():
        QwtLinearColorMap( QColor(BGc),Qt::black  )
    {
        addColorStop(0, QColor("#ffffff"));
       // addColorStop(0.5, QColor("#888888"));
    }
};

#endif // MECOLORS_H
