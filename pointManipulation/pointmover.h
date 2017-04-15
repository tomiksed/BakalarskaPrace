#ifndef POINTMOVER_H
#define POINTMOVER_H

#include <QObject>

#include <QList>
#include <QPointF>
#include <QLine>

#include "../utils/definitions.h"
#include "../utils/stateconfiguration.h"
#include "../utils/utilities.h"

class PointMover : public QObject
{
    Q_OBJECT
public:
    explicit PointMover(QObject *parent = 0);

    static void proceedCVT(StateConfiguration *config, bool useLine);

signals:

public slots:
};

#endif // POINTMOVER_H
