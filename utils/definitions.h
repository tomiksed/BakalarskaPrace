#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define NUMBER_OF_POINTS_DFAULT 1000

#define NUMBER_OF_ITERATIONS_DEFAULT 1000

#define MIN(a, b) ((a) <= (b) ? (a) : (b))

/* VSECHNY ZMENY ZANEST DO UTILIT */
struct point_t {
    double x;
    double y;
    double z;

    int timesMoved;

    bool movable;
    bool selected;

    /* What triangle the point is inside */
    struct triangle_t *triangle;

    int index;
};

struct dLine_t {
    double x1, y1, x2, y2;
};

struct triangle_t {
    point_t *p1, *p2, *p3;
};

#endif // DEFINITIONS_H
