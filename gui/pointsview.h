#ifndef POINTSVIEW_H
#define POINTSVIEW_H

#include <QObject>
#include <QWidget>
#include <QPainter>

#include <math.h>

#include "../utils/stateconfiguration.h"
#include "../utils/definitions.h"

class PointsView : public QWidget
{
    Q_OBJECT
public:
    explicit PointsView(QWidget *parent = 0);

    StateConfiguration *config;

protected:
    void paintEvent(QPaintEvent *);

    void drawPoints(QPainter &painter, double dimx, double dimy);
    void drawTriangles(QPainter &painter, double dimx, double dimy);
    void drawBoundary(QPainter &painter, double dimx, double dimy);
    void drawManipulationLines(QPainter &painter, double dimx, double dimy);
};

#endif // POINTSVIEW_H
