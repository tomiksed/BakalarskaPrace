#ifndef POINTSVIEW_H
#define POINTSVIEW_H

#include <QObject>
#include <QWidget>
#include <QPainter>

#include <math.h>

#include "../utils/stateconfiguration.h"
#include "../utils/definitions.h"

/*
 * Class for the widget responsible for data drawing
 */
class PointsView : public QWidget
{
    Q_OBJECT
public:
    explicit PointsView(QWidget *parent = 0);

    /* This class holds all the data */
    StateConfiguration *config;

protected:
    /* Main painting event, paints the data */
    void paintEvent(QPaintEvent *);

private:
    /* Draws points */
    void drawPoints(QPainter &painter, double dimx, double dimy);
    /* Draws triangles */
    void drawTriangles(QPainter &painter, double dimx, double dimy);
    /* Draws boundaries (red lines) */
    void drawBoundary(QPainter &painter, double dimx, double dimy);
    /* Draws the lines for manipulation (blue ones) */
    void drawManipulationLines(QPainter &painter, double dimx, double dimy);
};

#endif // POINTSVIEW_H
