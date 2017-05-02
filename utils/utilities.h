#ifndef UTILITIES_H
#define UTILITIES_H

#include <QObject>

#include "definitions.h"
#include "stateconfiguration.h"

/*
 * Class for utility methods
 */
class Utilities : public QObject
{
    Q_OBJECT
public:
    explicit Utilities(QObject *parent = 0);

    /* Creates an empty point with default settings */
    static point_t *createEmptyPoint();
    /* Creates a point with given coordinates*/
    static point_t *createPointWithCoordinates(double x, double y, double z);
    /* Creates a point with given coordinates and index*/
    static point_t *createPointWithCoordinatesAndIndex(double x, double y, double z, int index);

    /* This method recalculates the z coordinates of all points in the config */
    static void recalculateZCoordinates(StateConfiguration *config);
    /* To test if two line segments intersect */
    static bool doIntersect(dLine_t *l1, dLine_t *l2);

signals:

public slots:
};

#endif // UTILITIES_H
