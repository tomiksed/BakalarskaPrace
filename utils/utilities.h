#ifndef UTILITIES_H
#define UTILITIES_H

#include <QObject>

#include "definitions.h"
#include "stateconfiguration.h"

class Utilities : public QObject
{
    Q_OBJECT
public:
    explicit Utilities(QObject *parent = 0);

    static point_t *createEmptyPoint();
    static point_t *createPointWithCoordinates(double x, double y, double z);
    static point_t *createPointWithCoordinatesAndIndex(double x, double y, double z, int index);

    static void recalculateZCoordinates(StateConfiguration *config);

    static bool doIntersect(dLine_t *l1, dLine_t *l2);

signals:

public slots:
};

#endif // UTILITIES_H
