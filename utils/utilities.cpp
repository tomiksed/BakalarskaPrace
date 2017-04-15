#include "utilities.h"
#include <QDebug>

Utilities::Utilities(QObject *parent) : QObject(parent) {

}

point_t *Utilities::createEmptyPoint() {
    point_t *p = new point_t;

    p->triangle = nullptr;
    p->movable = true;
    p->selected = true;
    p->onManipulationLine = false;

    p->timesMoved = 0;

    p->index = -1;

    return p;
}

point_t *Utilities::createPointWithCoordinates(double x, double y, double z) {
    point_t *p = Utilities::createEmptyPoint();

    p->x = x;
    p->y = y;
    p->z = z;

    return p;
}

point_t *Utilities::createPointWithCoordinatesAndIndex(double x, double y, double z, int index) {
    point_t *p = Utilities::createEmptyPoint();

    p->x = x;
    p->y = y;
    p->z = z;

    p->index = index;

    return p;
}

double calculateArea(point_t *p1, point_t *p2, point_t *p3) {
    double result = p1->x * (p2->y - p3->y) + p2->x * (p3->y - p1->y) + p3->x * (p1->y - p2->y);
    return ((result < 0) ? -result : result);
}

void Utilities::recalculateZCoordinates(StateConfiguration *config) {
    double ta, w1, w2, w3;
    for (triangle_t *t : *config->originalTriangles) {
        QPolygonF poly;
        poly << QPointF(t->p1->x, t->p1->y) << QPointF(t->p2->x, t->p2->y) << QPointF(t->p3->x, t->p3->y);

        for (point_t *p : *config->points) {
            if (p->movable) {
                QPointF test(p->x, p->y);
                if (poly.containsPoint(test, Qt::OddEvenFill)) {
                    /*qDebug() << "Point" << p->x << ":" << p->y << "lies in triangle:"
                             << t->p1->x << ":" << t->p1->y << ":" << t->p1->z << ", "
                             << t->p2->x << ":" << t->p2->y << ":" << t->p2->z << ", "
                             << t->p3->x << ":" << t->p3->y << ":"  << t->p3->z;*/

                    ta = calculateArea(t->p1, t->p2, t->p3);
                    w1 = calculateArea(p, t->p2, t->p3) / ta;
                    w2 = calculateArea(p, t->p1, t->p3) / ta;
                    w3 = calculateArea(p, t->p1, t->p2) / ta;

                    p->z = w1 * t->p1->z + w2 * t->p2->z + w3 * t->p3->z;

                    //qDebug() << "Point's z is:" << p->z;
                }
            }
        }
    }
}
