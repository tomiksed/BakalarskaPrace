#ifndef STATECONFIGURATION_H
#define STATECONFIGURATION_H

#include <QObject>
#include <QList>
#include <QPolygonF>

#include "definitions.h"

class StateConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit StateConfiguration(QObject *parent = 0);

    QList<point_t *> *originalPoints;
    QList<point_t *> *points;

    QList<triangle_t *> *originalTriangles;

    QList<dLine_t *> *boundaryLines;

    QList<dLine_t *> *manipulationLines;

    QPolygonF boundary;

    double xmin, ymin, xmax, ymax;

signals:

public slots:
};

#endif // STATECONFIGURATION_H
