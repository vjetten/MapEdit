#ifndef LISUIMAPCOLOR_H
#define LISUIMAPCOLOR_H

#include "mainwindow.h"

//---------------------------------------------------------------------------
#define BGc "#eeeeee" // background grey for missing value in maps

//http://www.color-hex.com/color/
//http://colorbrewer2.org/
//http://www.colorschemer.com

//---------------------------------------------------------------------------

class colorMapMagenta: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 220,220,220,0 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapMagenta():
        QwtLinearColorMap( QColor(BGc),Qt::magenta  )
    {
        addColorStop(0, QColor("#ffffff"));
    }
};
/// Gray scale legend for shaded relief map display
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
//---------------------------------------------------------------------------
/// Logarithmic Yellow to blue legend for runoff map display
class colorMapYellowBlueLog: public QwtLinearColorMap
{

public:
    colorMapYellowBlueLog():
        QwtLinearColorMap( QColor(BGc), QColor("#000080"))
    {
        addColorStop( 0.0, QColor("#f6f633"));//Qt::yellow );
        addColorStop( 0.003,QColor("#8080FF"));
        addColorStop( 0.03, QColor("#4040ff") );
        addColorStop( 0.5, QColor("#0000FF"));

    }
};
//---------------------------------------------------------------------------
/// Linear Yellow to blue legend for infil map display
class colorMapYellowBlue: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 0, 0, 0, 0 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapYellowBlue():
        QwtLinearColorMap( QColor(BGc),QColor("#0000AA"))
    {
        addColorStop( 0.0, Qt::yellow );
        addColorStop( 0.1, QColor("#FFFF55") );
        addColorStop( 0.4, QColor("#8080FF") );
        addColorStop( 0.9, Qt::blue );
    }
};
//---------------------------------------------------------------------------
/// Transparent  light to dark blue legend for flood display
class colorMapFlood: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 0, 0, 0, 0 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapFlood():
        QwtLinearColorMap( QColor(BGc),  QColor("#000098"))
    {
        addColorStop(0.000,QColor("#6565FF"));
        //        addColorStop(0.002,QColor("#6565FF"));
        //        addColorStop(0.125,QColor("#4B4BFF"));
        //        addColorStop(0.250,QColor("#3333FF"));
        //        addColorStop(0.375,QColor("#1919FF"));
        //        addColorStop(0.500,QColor("#0000FE"));
        //        addColorStop(0.625,QColor("#0000E4"));
        //        addColorStop(0.750,QColor("#0000CC"));
        //        addColorStop(0.875,QColor("#0000B2"));
    }
};
//---------------------------------------------------------------------------
/// Cyan to red legend for sediment display
class colorMapCyanYellowRed: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 0, 0, 0, 0 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapCyanYellowRed():
        QwtLinearColorMap( QColor(BGc),Qt::red)//QColor("#903000") )//QColor("#cc3000"));//Qt::darkYellow);
    {
        addColorStop( 0.0, Qt::darkCyan );//QColor("#108030"));
        addColorStop( 0.3, Qt::cyan );//QColor("#30ffcc"));
        addColorStop( 0.5, Qt::white );
        addColorStop( 0.7, Qt::yellow);
    }
};
//---------------------------------------------------------------------------
/// Blue to red legend for sediment display
class colorMapBlueYellowRed: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 0, 0, 0, 0 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapBlueYellowRed():
        QwtLinearColorMap( QColor(BGc),Qt::red)
    {
        addColorStop( 0.0, Qt::blue );
        addColorStop( 0.3, Qt::cyan );
        //    addColorStop( 0.5, Qt::white );
        addColorStop( 0.7, Qt::yellow);
    }
};
//---------------------------------------------------------------------------
class colorMapGreenYellowRed: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 0, 0, 0, 0 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapGreenYellowRed():
        QwtLinearColorMap( QColor(BGc),QColor("#BF0000"))
    {
        addColorStop( 0.0, QColor("#006600"));
        addColorStop( 0.4, Qt::yellow);
        addColorStop( 0.8, Qt::red);
    }
};
//---------------------------------------------------------------------------
class colorMapRedBlue: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 0, 0, 0, 0 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapRedBlue():
        QwtLinearColorMap( QColor(BGc),Qt::red)
    {
        addColorStop(0.0,QColor("#8888FF"));
        addColorStop( 0.5, Qt::blue);
    }
};
//---------------------------------------------------------------------------
class colorMapColorBrewer: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value <= -1e19 )
            return qRgba( 0, 0, 0, 0 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapColorBrewer():
        QwtLinearColorMap( QColor(BGc),QColor("#542788"))
    {
        addColorStop(0.000,QColor("#b35806"));
        addColorStop(0.125,QColor("#e08214"));
        addColorStop(0.250,QColor("#fdb863"));
        addColorStop(0.375,QColor("#fee0b6"));
        addColorStop(0.500,QColor("#f7f7f7"));
        addColorStop(0.615,QColor("#d8daeb"));
        addColorStop(0.750,QColor("#b2abd2"));
        addColorStop(0.875,QColor("#8073ac"));
    }
};
//---------------------------------------------------------------------------
class colorMapRainbowInv: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value < -1e19 )
            return qRgba( 220,220,220,255 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapRainbowInv():
        QwtLinearColorMap( QColor("#ff0000"), QColor("#ce0c82"))
    {
        addColorStop(0.000,QColor("#ff0000"));
        addColorStop(0.091,QColor("#ff6000"));
        addColorStop(0.182,QColor("#ff9a00"));
        addColorStop(0.273,QColor("#ffcd00"));
        addColorStop(0.364,QColor("#feff00"));
        addColorStop(0.455,QColor("#bae806"));
        addColorStop(0.545,QColor("#2ece0c"));
        addColorStop(0.636,QColor("#0c99ce"));
        addColorStop(0.727,QColor("#0c5bce"));
        addColorStop(0.818,QColor("#1f0cce"));
        addColorStop(0.909,QColor("#800cce"));
        addColorStop(1.000,QColor("#ce0c82"));
    }
};
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
class colorMapColorfull: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value < -1e19 )
            return qRgba( 220,220,220,255 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapColorfull():
        QwtLinearColorMap(  QColor("#fbb735"), QColor("#39c0b3"))
    {
        addColorStop(0,QColor("#fbb735"));
        addColorStop(0.1,QColor("#e98931"));
        addColorStop(0.2,QColor("#eb403b"));
        addColorStop(0.3,QColor("#b32e37"));
        addColorStop(0.4,QColor("#6c2a6a"));
        addColorStop(0.5,QColor("#5c4399"));
        addColorStop(0.6,QColor("#274398"));
        addColorStop(0.7,QColor("#1f5ea8"));
        addColorStop(0.8,QColor("#227fb0"));
        addColorStop(0.9,QColor("#2ab0c5"));
        addColorStop(1,QColor("#39c0b3"));
    }
};
//---------------------------------------------------------------------------

#endif // LISUIMAPCOLOR_	H



