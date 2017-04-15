#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openClicked()));
    connect(ui->actionCVT, SIGNAL(triggered()), this, SLOT(CVTClicked()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveClicked()));
    connect(ui->actionCVT_with_line, SIGNAL(triggered()), this, SLOT(CVTWithLineClicked()));
    connect(ui->actionNumber_of_iterations, SIGNAL(triggered()), this, SLOT(numberOfIterationsClicked()));
    connect(ui->actionReset_move_counter, SIGNAL(triggered()), this, SLOT(resetMoveCounterClicked()));

    connect(ui->actionRecalculate_z_coordinate, SIGNAL(triggered()), this, SLOT(recalculateZClicked()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::CVTClicked() {
    PointMover::proceedCVT(this->ui->centralWidget->config, false);

    this->repaint();
}

void MainWindow::CVTWithLineClicked() {
    PointMover::proceedCVT(this->ui->centralWidget->config, true);

    this->repaint();
}

void MainWindow::openClicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open points", QDir::currentPath(),
                                                    "Point Files (*.dat *.txt)");

//QString f("/Users/justme/Downloads/DTbotannonconvex.dat");
    StateConfiguration *config = FileManipulator::loadContentsOfFile(&fileName);

    if (config == nullptr) {
        QMessageBox::information(0, "Reading error", "An unknown error occured while reading file");
        return;
    }

    this->ui->centralWidget->config = config;

    this->setWindowTitle(fileName);

    this->repaint();
}

void MainWindow::saveClicked() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save points", QDir::currentPath(),
                                                    "Point Files (*.dat *.txt)");

//QString f("/Users/justme/Documents/output.dat");
    FileManipulator::savePointsToFile(&fileName, this->ui->centralWidget->config);
}

void MainWindow::recalculateZClicked() {
    Utilities::recalculateZCoordinates(this->ui->centralWidget->config);
}

void MainWindow::numberOfIterationsClicked() {
    bool ok;
    int numberOfIterations = QInputDialog::getInt(this, "Number of iterations",
                                                "Enter number of iterations to be performed",
                                                this->ui->centralWidget->config->numberOfIterations, 1, 1000000, 1, &ok);

    if (ok) {
        this->ui->centralWidget->config->numberOfIterations = numberOfIterations;
    }
}

void MainWindow::resetMoveCounterClicked() {
    for (point_t *p : *this->ui->centralWidget->config->points) {
        p->timesMoved = 0;
    }
}
