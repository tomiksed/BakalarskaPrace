#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define NUMBER_OF_POINTS_DFAULT 1000

#define NUMBER_OF_ITERATIONS_DEFAULT 1000

#define MIN(a, b) ((a) <= (b) ? (a) : (b))

/* Structure holding information about a point*/
struct point_t {
    /* Coordinates */
    double x;
    double y;
    double z;

    /* How many times was the point moved */
    int timesMoved;

    /* Can this point be moved */
    bool movable;

    /* Is the point selected? (note: not used) */
    bool selected;
    /* Is the point on a manipulation line? */
    bool onManipulationLine;

    /* What triangle the point is inside */
    struct triangle_t *triangle;

    /* Point index - to save the points in
     * the same order as they were read
     */
    int index;
};

/* Structure for holding information about a line segment */
struct dLine_t {
    /* Coordinates of the two points forming a line segment */
    double x1, y1, x2, y2;
};

/* Structure for holding information about a triangle */
struct triangle_t {
    /* Points forming the triangle. Only pointers,
     * so moving the points invalidates the triangle
     */
    point_t *p1, *p2, *p3;
};

#endif // DEFINITIONS_H
