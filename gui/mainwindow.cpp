#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    /* Connecting actions with according methods */
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
    if (this->ui->centralWidget->config != nullptr &&
            this->ui->centralWidget->config->points != nullptr &&
            !this->ui->centralWidget->config->points->empty()) {



        PointMover::proceedCVT(this->ui->centralWidget->config, false);

        this->repaint();
    } else {
        QMessageBox mess;
        mess.setText("There are no points!");
        mess.setIcon(QMessageBox::Critical);
        mess.addButton(QMessageBox::Ok);
        mess.exec();
    }
}

void MainWindow::CVTWithLineClicked() {
    if (this->ui->centralWidget->config != nullptr &&
            this->ui->centralWidget->config->points != nullptr &&
            !this->ui->centralWidget->config->points->empty() &&
            this->ui->centralWidget->config->manipulationLines != nullptr &&
            !this->ui->centralWidget->config->manipulationLines->empty()) {


        PointMover::proceedCVT(this->ui->centralWidget->config, true);

        this->repaint();
    } else {
        QMessageBox mess;
        mess.setText("There are no points or lines!");
        mess.setIcon(QMessageBox::Critical);
        mess.addButton(QMessageBox::Ok);
        mess.exec();
    }
}

void MainWindow::openClicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open points", QDir::currentPath(),
                                                    "Point Files (*.dat *.txt)");

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
    if (this->ui->centralWidget->config != nullptr &&
            this->ui->centralWidget->config->points != nullptr &&
            !this->ui->centralWidget->config->points->empty()) {

        QString fileName = QFileDialog::getSaveFileName(this,
                                                        "Save points", QDir::currentPath(),
                                                        "Point Files (*.dat *.txt)");
        FileManipulator::savePointsToFile(&fileName, this->ui->centralWidget->config);
    } else {
        QMessageBox mess;
        mess.setText("No points to save!");
        mess.setIcon(QMessageBox::Critical);
        mess.addButton(QMessageBox::Ok);
        mess.exec();
    }
}

void MainWindow::recalculateZClicked() {
    if (this->ui->centralWidget->config != nullptr &&
            this->ui->centralWidget->config->points != nullptr &&
            !this->ui->centralWidget->config->points->empty() &&
            this->ui->centralWidget->config->originalTriangles != nullptr &&
            !this->ui->centralWidget->config->originalTriangles->empty()) {


        Utilities::recalculateZCoordinates(this->ui->centralWidget->config);
    } else {
        QMessageBox mess;
        mess.setText("Not enough data!");
        mess.setIcon(QMessageBox::Critical);
        mess.addButton(QMessageBox::Ok);
        mess.exec();
    }
}

void MainWindow::numberOfIterationsClicked() {
    if (this->ui->centralWidget->config != nullptr &&
            this->ui->centralWidget->config->points != nullptr &&
            !this->ui->centralWidget->config->points->empty()) {

        bool ok;
        int numberOfIterations = QInputDialog::getInt(this, "Number of iterations",
                                                    "Enter number of iterations to be performed",
                                                    this->ui->centralWidget->config->numberOfIterations, 1, 1000000, 1, &ok);

        if (ok) {
            this->ui->centralWidget->config->numberOfIterations = numberOfIterations;
        }
    } else {
        QMessageBox mess;
        mess.setText("Load data first!");
        mess.setIcon(QMessageBox::Critical);
        mess.addButton(QMessageBox::Ok);
        mess.exec();
    }
}

void MainWindow::resetMoveCounterClicked() {
    if (this->ui->centralWidget->config != nullptr &&
            this->ui->centralWidget->config->points != nullptr &&
            !this->ui->centralWidget->config->points->empty()) {

        for (point_t *p : *this->ui->centralWidget->config->points) {
            p->timesMoved = 0;
        }
    } else {
        QMessageBox mess;
        mess.setText("Load data first!");
        mess.setIcon(QMessageBox::Critical);
        mess.addButton(QMessageBox::Ok);
        mess.exec();
    }
}
