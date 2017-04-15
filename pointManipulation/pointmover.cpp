#include "pointmover.h"
#include <math.h>
#include <QDebug>

PointMover::PointMover(QObject *parent) : QObject(parent) {

}

/* Odprasit */
point_t *generateRandomPointForNormalCVT(StateConfiguration *config) {
    double max_rand = static_cast<double>(RAND_MAX);

    double x = rand() / max_rand;
    double y = rand() / max_rand;

    x = (x * (config->xmax - config->xmin)) + config->xmin;
    y = (y * (config->ymax - config->ymin)) + config->ymin;

    return Utilities::createPointWithCoordinates(x, y, 0.);
}

point_t *generateRandomPointFromLine(StateConfiguration *config) {
    double rand_max = static_cast<double>(RAND_MAX);

    double totalLength = 0.;
    for (dLine_t *line : *config->manipulationLines) {
        totalLength += sqrt((line->x1 + line->x2) * (line->y1 + line->y2));
    }

    double pos = rand() / rand_max;

    double actual_distance = 0., line_length;
    double point_position = pos * totalLength;

    for (dLine_t *line : *config->manipulationLines) {
        line_length = sqrt((line->x1 + line->x2) * (line->y1 + line->y2));

        if (actual_distance + line_length > point_position) {
            double rest = point_position - actual_distance;

            double rel_pos = rest / line_length;

            double new_x = line->x1 +  (( line->x2 - line->x1) * rel_pos);
            double new_y = line->y1 +  (( line->y2 - line->y1) * rel_pos);

            return Utilities::createPointWithCoordinates(new_x, new_y, 0.);
        } else {
            actual_distance += line_length;
        }
    }
}

#include <limits>
point_t *findNearestPoint(QList<point_t *> *movablePoints, point_t *generated) {
    point_t *nearest;
    double dist_min = std::numeric_limits<double>::max(), actual_dist;

    for (point_t *p : *movablePoints) {
        actual_dist = (((p->x - generated->x) * (p->x - generated->x)) + ((p->y - generated->y) * (p->y - generated->y)));
        if (actual_dist < dist_min) {
            nearest = p;
            dist_min = actual_dist;
        }
    }

    return nearest;
}

bool doIntersect(dLine_t *l1, dLine_t *l2) {
    QLineF ll1(l1->x1, l1->y1, l1->x2, l1->y2);
    QLineF ll2(l2->x1, l2->y1, l2->x2, l2->y2);

    if (ll1.intersect(ll2, NULL) == QLineF::BoundedIntersection) {
        return true;
    } else {
        return false;
    }
}

bool isInBoundingPolygon(point_t *p, StateConfiguration *config) {
    QLineF l2(config->xmin - 1., p->y, p->x, p->y);
    int numberOfIntersections = 0;
    for (dLine_t *b : *config->boundaryLines) {
        QLineF l1(b->x1, b->y1, b->x2, b->y2);

        if (l2.intersect(l1, NULL) == QLineF::BoundedIntersection) {
            numberOfIntersections++;
        }
    }

    return !(numberOfIntersections % 2 == 0);
}

void PointMover::proceedCVT(StateConfiguration *config, bool useLine) {
    QList<point_t *> *movablePoints = new QList<point_t *>();

    for (point_t *p : *config->points) {
        if (p->movable && p->selected)
            movablePoints->append(p);
    }

    int iterationsDone = 0;

    while (iterationsDone < config->numberOfIterations) {
        point_t *generated;
        if (useLine) {
            generated = generateRandomPointFromLine(config);
        } else {
            generated = generateRandomPointForNormalCVT(config);
        }

        if (!useLine && !isInBoundingPolygon(generated, config)) {
            continue;
        }

        /*generated->movable = false;
        config->points->append(generated);*/

        point_t *nearest  = findNearestPoint(movablePoints, generated);
        nearest->x = ((generated->x + (nearest->x * nearest->timesMoved)) / (nearest->timesMoved + 1));
        nearest->y = ((generated->y + (nearest->y * nearest->timesMoved)) / (nearest->timesMoved + 1));

        nearest->timesMoved++;
        iterationsDone++;
    }
}
