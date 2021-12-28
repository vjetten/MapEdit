#ifndef LISUIMAPCOLOR_H
#define LISUIMAPCOLOR_H

#include "mainwindow.h"

//---------------------------------------------------------------------------
#define BGc "#eeeeee" // background grey for missing value in maps

//http://www.color-hex.com/color/
//http://colorbrewer2.org/
//http://www.colorschemer.com

//---------------------------------------------------------------------------
/// Shows value on cursor in map window
class MyPicker: public QwtPlotPicker
{
public:
    MyPicker( QwtPlotCanvas *canvas ):
        QwtPlotPicker( canvas )
    {
        setTrackerMode( AlwaysOn );
    }

    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
        QColor bg( Qt::white );
        bg.setAlpha( 100 );
        QString txt = "";
        QString unit = "";

        QwtPlotItemList list = plot()->itemList(QwtPlotItem::Rtti_PlotSpectrogram);
        QwtPlotSpectrogram * sp = static_cast<QwtPlotSpectrogram *> (list.at(1));
        QwtPlotSpectrogram * sp0 = static_cast<QwtPlotSpectrogram *> (list.at(list.count()-1));
        // elevation info

        if (sp->data() == NULL)
            return QwtText(txt);
        double z = sp->data()->value(pos.x(), pos.y());
        double z0 = sp0->data()->value(pos.x(), pos.y());

        if (z > -1e10)
        {
            if (sp->data()->value(0,0) == 1) txt = QString("%1 l/s[%3m]").arg(z,0,'f',1).arg(z0,0,'f',1);
            if (sp->data()->value(0,0) == 2) txt = QString("%1 mm[%3m]").arg(z,0,'f',1).arg(z0,0,'f',1);
            if (sp->data()->value(0,0) == 3)
                txt = QString("%1 %2[%3m]").arg(z,0,'f',1).arg(unit).arg(z0,0,'f',1);
            if (sp->data()->value(0,0) == 4) txt = QString("%1 m[%3m]").arg(z,0,'f',3).arg(z0,0,'f',1);
            if (sp->data()->value(0,0) == 5) txt = QString("%1 m/s[%3m]").arg(z,0,'f',3).arg(z0,0,'f',1);
            if (sp->data()->value(0,0) == 6) txt = QString("%1 mm[%3m]").arg(z,0,'f',3).arg(z0,0,'f',1);
        }

        QwtText text = QwtText(txt);
        text.setColor(Qt::black);
        text.setBackgroundBrush( QBrush( bg ) );
        return text;
    }
};
//---------------------------------------------------------------------------
/// Gray scale legend for shaded relief map display
class colorMapGray: public QwtLinearColorMap
{
public:
    colorMapGray():
        QwtLinearColorMap( QColor(BGc),Qt::white  )
    {
        addColorStop(0, QColor("#111111"));
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
        if ( value < 0.001 )
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
        if ( value < 0.001 )
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
        if ( value < 0.001 )
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
            return qRgba( 220,220,220,255 );

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
class colorMapLime: public QwtLinearColorMap
{
    virtual QRgb rgb( const QwtInterval &interval, double value ) const
    {
        if ( value < -1e19 )
            return qRgba( 220,220,220,255 );

        return QwtLinearColorMap::rgb( interval, value );
    }
public:
    colorMapLime():
        QwtLinearColorMap(  QColor("#006802"), QColor("#FFFECB"))
    {
        addColorStop(0.000,QColor("#006802"));
      //  addColorStop(0.500,QColor("#B1CA25"));
        addColorStop(0.5,QColor("#CCFF00"));
                addColorStop(1.000,QColor("#FFFECB"));
    }
};
#endif // LISUIMAPCOLOR_	H



