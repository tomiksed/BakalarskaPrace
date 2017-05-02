#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QPointF>
#include <QInputDialog>

#include "../utils/filemanipulator.h"
#include "../utils/stateconfiguration.h"
#include "../pointManipulation/pointmover.h"

namespace Ui {
class MainWindow;
}

/*
 * Class representing the main window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    /* File section - loading and opening data */
    void openClicked();
    void saveClicked();

    /* Processing section */
    void CVTClicked();
    void CVTWithLineClicked();
    void recalculateZClicked();

    /* Settings section */
    void numberOfIterationsClicked();
    void resetMoveCounterClicked();

};

#endif // MAINWINDOW_H
