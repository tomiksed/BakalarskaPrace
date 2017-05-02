#include "filemanipulator.h"
#include <QDebug>
#include <QFile>

FileManipulator::FileManipulator(QObject *parent) : QObject(parent) {

}

StateConfiguration *FileManipulator::loadContentsOfFile(QString *fileName) {
    QFile file(*fileName);

    if(!file.open(QIODevice::ReadOnly)) {
        return nullptr;
    }

    StateConfiguration *config = new StateConfiguration();

    QTextStream in(&file);

    FileManipulator::loadPoints(in, config);

    FileManipulator::loadTriangles(in, config);

    FileManipulator::loadBoundaries(in, config);

    FileManipulator::loadManipulationLines(in, config);

    file.close();

    return config;
}

void FileManipulator::loadPoints(QTextStream &in, StateConfiguration *config) {
    QString line = in.readLine();
    int numberOfPoints = line.toInt();

    QStringList fields;

    double x, y, z, xmax, ymax, xmin, ymin;
    xmax = std::numeric_limits<double>::min();
    xmin = std::numeric_limits<double>::max();
    ymax = std::numeric_limits<double>::min();
    ymin = std::numeric_limits<double>::max();

    for (int i = 0; i < numberOfPoints; i++) {
        line = in.readLine().trimmed();
        line.replace("\t", " ");
        line.replace("   ", " ");
        line.replace("  ", " ");

        fields = line.split(" ");

        x = fields.at(0).toDouble();
        y = fields.at(1).toDouble();
        z = fields.at(2).toDouble();

        config->points->append(Utilities::createPointWithCoordinatesAndIndex(x, y, z, i));
        config->originalPoints->append(Utilities::createPointWithCoordinatesAndIndex(x, y, z, i));

        if (x > xmax) {
            xmax = x;
        }
        if (y > ymax) {
            ymax = y;
        }

        if (x < xmin) {
            xmin = x;
        }
        if (y < ymin) {
            ymin = y;
        }
    }

    config->xmin = xmin;
    config->xmax = xmax;
    config->ymin = ymin;
    config->ymax = ymax;
}

void FileManipulator::loadTriangles(QTextStream &in, StateConfiguration *config) {
    QString line = in.readLine();
    QStringList fields;

    int numberOfTriangles = line.toInt();
    int t1, t2, t3;

    for (int i = 0; i < numberOfTriangles; i++) {
        line = in.readLine().trimmed();
        line.replace("\t", " ");
        line.replace("   ", " ");
        line.replace("   ", " ");
        line.replace("  ", " ");
        line.replace("  ", " ");

        fields = line.split(" ");

        t1 = fields.at(0).toInt();
        t2 = fields.at(1).toInt();
        t3 = fields.at(2).toInt();

        config->originalTriangles->append(new triangle_t {
                                              config->originalPoints->at(t1),
                                              config->originalPoints->at(t2),
                                              config->originalPoints->at(t3)
                                          });
        /*config->originalTriangles->append(new triangle_t {
                                              config->points->at(t1),
                                              config->points->at(t2),
                                              config->points->at(t3)
                                          });*/
    }
}

void FileManipulator::loadBoundaries(QTextStream &in, StateConfiguration *config) {
    QString line = in.readLine();
    QStringList fields;

    int numberOfNeighbors = line.toInt();
    int t1, t2, t3;

    for (int i = 0; i < numberOfNeighbors; i++) {
        line = in.readLine().trimmed();
        line.replace("\t", " ");
        line.replace("   ", " ");
        line.replace("   ", " ");
        line.replace("  ", " ");
        line.replace("  ", " ");

        fields = line.split(" ");

        t1 = fields.at(0).toInt();
        t2 = fields.at(1).toInt();
        t3 = fields.at(2).toInt();

        if (t1 == -1) {
            triangle_t *t = config->originalTriangles->at(i);

            config->boundaryLines->append(new dLine_t {t->p2->x, t->p2->y, t->p3->x, t->p3->y});
            config->boundary << QPointF(t->p2->x, t->p2->y);
            config->boundary << QPointF(t->p3->x, t->p3->y);

            config->points->at(t->p2->index)->movable = false;
            config->points->at(t->p3->index)->movable = false;
        }
        if (t2 == -1) {
            triangle_t *t = config->originalTriangles->at(i);

            config->boundaryLines->append(new dLine_t {t->p1->x, t->p1->y, t->p3->x, t->p3->y});
            config->boundary << QPointF(t->p1->x, t->p1->y);
            config->boundary << QPointF(t->p3->x, t->p3->y);

            config->points->at(t->p1->index)->movable = false;
            config->points->at(t->p3->index)->movable = false;
        }
        if (t3 == -1) {
            triangle_t *t = config->originalTriangles->at(i);

            config->boundaryLines->append(new dLine_t {t->p2->x, t->p2->y, t->p1->x, t->p1->y});
            config->boundary << QPointF(t->p2->x, t->p2->y);
            config->boundary << QPointF(t->p1->x, t->p1->y);

            config->points->at(t->p2->index)->movable = false;
            config->points->at(t->p1->index)->movable = false;
        }
    }
}

void FileManipulator::loadManipulationLines(QTextStream &in, StateConfiguration *config) {
    QString line = in.readLine();
    QStringList fields;

    int numberOfBounaryLines = line.toInt();

    for (int i = 0; i < numberOfBounaryLines; i++) {
        line = in.readLine().trimmed();
        line.replace("\t", " ");
        line.replace("   ", " ");
        line.replace("   ", " ");
        line.replace("  ", " ");
        line.replace("  ", " ");

        fields = line.split(" ");

        for (int j = 0; j < fields.count() - 1; j++) {
            int ip1 = fields.at(j).toInt();
            int ip2 = fields.at(j + 1).toInt();

            point_t *p1 = config->points->at(ip1);
            p1->movable = false;
            p1->onManipulationLine = true;
            point_t *p2 = config->points->at(ip2);
            p2->movable = false;
            p2->onManipulationLine = true;

            dLine_t *line = new dLine_t {p1->x, p1->y, p2->x, p2->y};

            config->manipulationLines->append(line);
        }
    }
}

void FileManipulator::savePointsToFile(QString *fileName, StateConfiguration *config) {
    QFile file(*fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    int numberOfPoints = config->points->count();

    out << QString::number(numberOfPoints) << '\n';
    for (point_t *p : *config->points) {
        out << QString::number(p->x, 'f', 6) << " "
            << QString::number(p->y, 'f', 6) << " "
            << QString::number(p->z, 'f', 6) << '\n';
    }

    out.flush();

    file.close();
}
