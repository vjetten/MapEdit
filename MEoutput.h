
#include <QList>
#include "csfmap.h"


#ifndef LISUIOUTPUT_H_
#define LISUIOUTPUT_H_

typedef struct xyzLIST {
    int r;
    int c;
    double cx;
    double cy;
    double v;
} xyzLIST;

struct output{
	bool editCell;
	bool editRectangle;
	bool editLine;
    bool editPolygon;
	bool editStart;
	bool editStop;
    int clicks;
    int polystart;

    cTMap *_M;
    int nrC;
    int nrR;
    double _dx;

    QVector <xyzLIST> eData;
	
};



#endif /* LISUIOUTPUT_H_ */
