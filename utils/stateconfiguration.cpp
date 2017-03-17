#include "stateconfiguration.h"

StateConfiguration::StateConfiguration(QObject *parent) : QObject(parent)
{
    this->points = new QList<point_t *>();
    this->originalPoints = new QList<point_t *>();

    this->originalTriangles = new QList<triangle_t *>();

    this->boundaryLines = new QList<dLine_t *>();

    this->manipulationLines = new QList<dLine_t *>();
}
