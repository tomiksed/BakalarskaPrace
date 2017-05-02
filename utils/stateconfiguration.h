#ifndef STATECONFIGURATION_H
#define STATECONFIGURATION_H

#include <QObject>
#include <QList>
#include <QPolygonF>

#include "definitions.h"
/*
 * This class holds all information about the data
 * that are manipulated
 */
class StateConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit StateConfiguration(QObject *parent = 0);

    /* Original points - for holding original triangles
     * so the moved points do not invalidate them*/
    QList<point_t *> *originalPoints;
    /* Points that can be moved */
    QList<point_t *> *points;

    /* Triangles */
    QList<triangle_t *> *originalTriangles;

    /* Boundary lines - the boundary of the area */
    QList<dLine_t *> *boundaryLines;

    /* Blue line segments for */
    QList<dLine_t *> *manipulationLines;

    /* Boundary polyhon - not used */
    QPolygonF boundary;

    /* Bounding box coordinates */
    double xmin, ymin, xmax, ymax;

    /* Number of iterations to be performed */
    int numberOfIterations;

signals:

public slots:
};

#endif // STATECONFIGURATION_H
