#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>

#include <QString>
#include <QStringList>
#include <QTextStream>

#include "stateconfiguration.h"
#include "utilities.h"

class FileManipulator : public QObject
{
    Q_OBJECT
public:
    explicit FileManipulator(QObject *parent = 0);

    static StateConfiguration *loadContentsOfFile(QString *fileName);

    static void savePointsToFile(QString *fileName, StateConfiguration *config);

private:
    static void loadPoints(QTextStream &in, StateConfiguration *config);
    static void loadTriangles(QTextStream &in, StateConfiguration *config);
    static void loadBoundaries(QTextStream &in, StateConfiguration *config);

signals:

public slots:
};

#endif // FILELOADER_H
