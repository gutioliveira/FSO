#include "cartesian_plane.h"
#include <math.h>

int is_triangule(struct dot first, struct dot second, struct dot third);

double *side_size(struct triangule t);

double perimeter_triangule(struct triangule t);

double area_triangule(struct triangule t);