#ifndef MECOLORS_H
#define MECOLORS_H

#include "mainwindow.h"

//---------------------------------------------------------------------------
#define BGc "#eeeeee" // background grey for missing value in maps

//http://www.color-hex.com/color/
//http://colorbrewer2.org/
//http://www.colorschemer.com
//qgis


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
        QwtLinearColorMap( QColor("#ffffb2"),QColor("#bd0026") )
    {
        addColorStop(0.00, QColor("#ffffb2"));
        addColorStop(0.25, QColor("#fecc5c"));
        addColorStop(0.50, QColor("#fd8d3c"));
        addColorStop(0.75, QColor("#f03b20"));
        addColorStop(1.00, QColor("#bd0026"));
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
        QwtLinearColorMap(QColor("#ffffcc"),QColor("#253494") )
    {
        addColorStop(0.00, QColor("#ffffcc"));//#ffff51"));
        addColorStop(0.25, QColor("#a1dab4"));//#c7e55a"));
        addColorStop(0.50, QColor("#41b6c4"));//#32b1df"));
        addColorStop(0.75, QColor("#2c7fb8"));//#3271ca"));
        addColorStop(1.00, QColor("#253494"));//#2c3898"));
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
        QwtLinearColorMap(QColor("#2b83ba"),QColor("#d7191c") )
    {
        addColorStop(1.00, QColor("#2b83ba"));
        addColorStop(0.75, QColor("#abdda4"));
        addColorStop(0.50, QColor("#fdfd7e"));
        addColorStop(0.25, QColor("#fdae61"));
        addColorStop(0.00, QColor("#d7191c"));
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
        QwtLinearColorMap( QColor("#733957"),QColor("#5C538B") )
    {
        addColorStop(0.000, QColor("#733957"));
        addColorStop(0.125, QColor("#874037"));
        addColorStop(0.250, QColor("#A3672C"));
        addColorStop(0.375, QColor("#C3A34B"));
        addColorStop(0.500, QColor("#D6D893"));
        addColorStop(0.625, QColor("#B4DEC6"));
        addColorStop(0.750, QColor("#74BBCD"));
        addColorStop(0.875, QColor("#4F88B9"));
        addColorStop(0.100, QColor("#5C538B"));
        //addColorStop(1.000, QColor("#723959"));
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
        QwtLinearColorMap(QColor("#440154"), QColor("#fde725"))
    {

        addColorStop(0.00, QColor("#440154"));
        addColorStop(0.25, QColor("#3b528b"));
        addColorStop(0.50, QColor("#21908d"));
        addColorStop(0.75, QColor("#5dc963"));
        addColorStop(1.00, QColor("#fde725"));

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
        QwtLinearColorMap( QColor("#2b83ba"),QColor("#d7191c") )
    {
        addColorStop(1.00, QColor("#d7191c")); //#d7191c"));
        addColorStop(0.75, QColor("#fdae61")); //#fdae61"));
        addColorStop(0.50, QColor("#ffffbf")); //#ffffbf"));
        addColorStop(0.25, QColor("#abdda4")); //#abdda4"));
        addColorStop(0.00, QColor("#4f92bb")); //#2b83ba"));
    }
};
//------------------------------------------
class colorMap7: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 220,220,220,0 );
        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMap7():
        QwtLinearColorMap( QColor("#6a2884"),QColor("#a60404") )
    {
        addColorStop(0.00, QColor("#6a2884"));
        addColorStop(0.25, QColor("#4e88eb"));
        addColorStop(0.50, QColor("#cefc28"));
        addColorStop(0.75, QColor("#fb7e21"));
        addColorStop(1.00, QColor("#a60404"));
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
        QwtLinearColorMap(  QColor("#193cbc"), QColor("#ea594e"))
    {
        addColorStop(0.000,QColor("#193cbc"));//6a2884"));
        addColorStop(0.167,QColor("#1473af"));//800cce"));
        addColorStop(0.333,QColor("#589acf"));//1f0cce"));
        addColorStop(0.500,QColor("#89c3ef"));//0c5bce"));
        addColorStop(0.667,QColor("#ede65a"));//0c99ce"));
        addColorStop(0.833,QColor("#e6b039"));//2ece0c"));
        addColorStop(1.000,QColor("#ea594e"));//bae806"));
        //addColorStop(0.636,QColor("#feff00"));
        //addColorStop(0.727,QColor("#ffcd00"));
        //addColorStop(0.818,QColor("#ff9a00"));
       // addColorStop(0.909,QColor("#ff6000"));
       // addColorStop(1.000,QColor("#ff0000"));
    }
};
//------------------------------------------
class colorMapRandom: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value < -1e19 )
            return qRgba( 220,220,220,0 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapRandom():
        QwtLinearColorMap(  QColor("#6a2884"), QColor("#ff0000"))
    {
        addColorStop(0.000,QColor("#6a2884"));
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
        QwtLinearColorMap( QColor("#ffffff"), QColor("#000000"))
    {
    }
};

#endif // MECOLORS_H
