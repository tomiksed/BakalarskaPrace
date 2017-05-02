#include "pointsview.h"
#include <QDebug>

PointsView::PointsView(QWidget *parent) : QWidget(parent) {
    this->config = nullptr;
}

void PointsView::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::SolidPattern);

    painter.fillRect(0, 0, this->width(), this->height(), Qt::GlobalColor::white);

    if (this->config != nullptr && !this->config->points->empty()) {
        double first = ((double) this->width() - 20) / (config->xmax - config->xmin);
        double second = ((double) this->height() - 20) / (config->ymax - config->ymin);

        /* To fit the data bouding box into the window */
        double scale = MIN(first, second);

        double dimx = scale * (config->xmax - config->xmin);
        double dimy = scale * (config->ymax - config->ymin);

        if (!this->config->originalTriangles->empty()) {
            this->drawTriangles(painter, dimx, dimy);
        }
        if (!this->config->boundaryLines->empty()) {
            this->drawBoundary(painter, dimx, dimy);
        }
        if (!this->config->manipulationLines->empty()) {
            this->drawManipulationLines(painter, dimx, dimy);
        }


        this->drawPoints(painter, dimx, dimy);
    }
}

void PointsView::drawPoints(QPainter &painter, double dimx, double dimy) {
    for (point_t *p : *this->config->points) {
        if (p->selected) {
            if (p->movable) {
                painter.setPen(Qt::black);
            } else {
                painter.setPen(Qt::blue);
            }
            painter.drawPoint((int) round(((this->width() - dimx) / 2) + ((p->x - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx - 1),
                              this->height() - (int) round(((this->height() - dimy) / 2) + ((p->y - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy));
            painter.drawPoint((int) round(((this->width() - dimx) / 2) + ((p->x - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx + 1),
                              this->height() - (int) round(((this->height() - dimy) / 2) + ((p->y - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy));
            painter.drawPoint((int) round(((this->width() - dimx) / 2) + ((p->x - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx),
                              this->height() - (int) round(((this->height() - dimy) / 2) + ((p->y - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy - 1));
            painter.drawPoint((int) round(((this->width() - dimx) / 2) + ((p->x - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx),
                              this->height() - (int) round(((this->height() - dimy) / 2) + ((p->y - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy + 1));
        } else {
            painter.setPen(Qt::red);
        }

        painter.drawPoint((int) round(((this->width() - dimx) / 2) + ((p->x - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx),
                          this->height() - (int) round(((this->height() - dimy) / 2) + ((p->y - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy));
    }
}

void PointsView::drawTriangles(QPainter &painter, double dimx, double dimy) {
    painter.setPen(Qt::green);

    for (triangle_t *t : *this->config->originalTriangles) {
        painter.drawLine((int) round(((this->width() - dimx) / 2) + ((t->p1->x - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx - 1),
                         this->height() - (int) round(((this->height() - dimy) / 2) + ((t->p1->y - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy),
                         (int) round(((this->width() - dimx) / 2) + ((t->p2->x - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx - 1),
                         this->height() - (int) round(((this->height() - dimy) / 2) + ((t->p2->y - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy));
        painter.drawLine((int) round(((this->width() - dimx) / 2) + ((t->p2->x - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx - 1),
                         this->height() - (int) round(((this->height() - dimy) / 2) + ((t->p2->y - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy),
                         (int) round(((this->width() - dimx) / 2) + ((t->p3->x - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx - 1),
                         this->height() - (int) round(((this->height() - dimy) / 2) + ((t->p3->y - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy));
        painter.drawLine((int) round(((this->width() - dimx) / 2) + ((t->p3->x - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx - 1),
                         this->height() - (int) round(((this->height() - dimy) / 2) + ((t->p3->y - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy),
                         (int) round(((this->width() - dimx) / 2) + ((t->p1->x - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx - 1),
                         this->height() - (int) round(((this->height() - dimy) / 2) + ((t->p1->y - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy));
    }
}

void PointsView::drawBoundary(QPainter &painter, double dimx, double dimy) {
    painter.setPen(Qt::red);

    for (dLine_t *l : *this->config->boundaryLines) {
        painter.drawLine((int) round(((this->width() - dimx) / 2) + ((l->x1 - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx - 1),
                         this->height() - (int) round(((this->height() - dimy) / 2) + ((l->y1 - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy),
                         (int) round(((this->width() - dimx) / 2) + ((l->x2 - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx - 1),
                         this->height() - (int) round(((this->height() - dimy) / 2) + ((l->y2 - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy));
    }
}

void PointsView::drawManipulationLines(QPainter &painter, double dimx, double dimy) {
    painter.setPen(Qt::blue);

    for (dLine_t *l : *this->config->manipulationLines) {
        painter.drawLine((int) round(((this->width() - dimx) / 2) + ((l->x1 - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx - 1),
                         this->height() - (int) round(((this->height() - dimy) / 2) + ((l->y1 - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy),
                         (int) round(((this->width() - dimx) / 2) + ((l->x2 - this->config->xmin) / (this->config->xmax - this->config->xmin)) * dimx - 1),
                         this->height() - (int) round(((this->height() - dimy) / 2) + ((l->y2 - this->config->ymin) / (this->config->ymax - this->config->ymin)) * dimy));
    }
}
