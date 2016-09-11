#include "geometric_operations.h"

int is_triangule(struct dot first, struct dot second, struct dot third){

	struct triangule supposed_triangule;

	supposed_triangule.first = first;
	supposed_triangule.second = second;
	supposed_triangule.third = third;

	double *sides = side_size(supposed_triangule);

	if( sides[0] + sides[1] > sides[2] && sides[1] + 
		sides[2] > sides[0] && sides[0] + sides[2] > sides[1] )
		return 1;
	else
		return 0;
}

double * side_size(struct triangule t){

	static double sides_size[3];

	sides_size[0] = hypot(t.first.x - t.second.x, t.first.y - t.second.y);
	sides_size[1] = hypot(t.first.x - t.third.x, t.first.y - t.third.y);
	sides_size[2] = hypot(t.second.x - t.third.x, t.second.y - t.third.y);

	return sides_size;
}

double perimeter_triangule(struct triangule t){

	double *sides = side_size(t);
	double p = 0.0;
	int i;

	for ( i = 0; i < 3; i++ ){
		p += sides[i];
	}

	return p;
}

double area_triangule(struct triangule t){

	double half = perimeter_triangule(t)/2.0;

	// printf("half = %lf\n", half);

	double *sides = side_size(t);

	double area = sqrt(half * ( half - sides[0] ) * ( half - sides[1] ) * ( half - sides[2] ) );

	return area;
}