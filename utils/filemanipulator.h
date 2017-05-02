#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>

#include <QString>
#include <QStringList>
#include <QTextStream>

#include "stateconfiguration.h"
#include "utilities.h"

/*
 * Class responsible for reading and saving data
 */
class FileManipulator : public QObject
{
    Q_OBJECT
public:
    explicit FileManipulator(QObject *parent = 0);

    /* Loads content of given file into a new configuration */
    static StateConfiguration *loadContentsOfFile(QString *fileName);

    /* Saves points from given configuration into a file */
    static void savePointsToFile(QString *fileName, StateConfiguration *config);

private:
    /* Loads points from stream into a configuration */
    static void loadPoints(QTextStream &in, StateConfiguration *config);
    /* Loads triangles from stream into a configuration */
    static void loadTriangles(QTextStream &in, StateConfiguration *config);
    /* Loads boundaries from stream into a configuration */
    static void loadBoundaries(QTextStream &in, StateConfiguration *config);
    /* Loads line segments from stream into a configuration */
    static void loadManipulationLines(QTextStream &in, StateConfiguration *config);

signals:

public slots:
};

#endif // FILELOADER_H
