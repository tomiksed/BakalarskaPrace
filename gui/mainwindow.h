#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QPointF>

#include "../utils/filemanipulator.h"
#include "../utils/stateconfiguration.h"
#include "../pointManipulation/pointmover.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void openClicked();
    void saveClicked();
    void CVTClicked();
    void CVTWithLineClicked();

    void recalculateZClicked();
};

#endif // MAINWINDOW_H
