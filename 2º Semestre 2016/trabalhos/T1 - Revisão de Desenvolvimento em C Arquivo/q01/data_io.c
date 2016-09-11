#include "data_io.h"

struct dot * data_entry(){

	static struct dot dots[3];

	struct triangule triangule_target;

	printf("Entry the first x and y coordinates of the triangule (double).\n");
	scanf("%lf %lf", &dots[0].x, &dots[0].y);

	printf("Entry the second x and y coordinates of the triangule (double).\n");
	scanf("%lf %lf", &dots[1].x, &dots[1].y);

	printf("Entry the third x and y coordinates of the triangule (double).\n");
	scanf("%lf %lf", &dots[2].x, &dots[2].y);

	return dots;
}

void data_output(const struct dot dots[]){

	if ( is_triangule(dots[0], dots[1], dots[2]) ){

		struct triangule triangule;
		triangule.first = dots[0];
		triangule.second = dots[1];
		triangule.third = dots[2];

		print_sides(side_size(triangule));
		print_perimeter(triangule);
		print_area(triangule);
	}else{

		printf("Not a triangule!\n");
	}
}

void print_sides(const double sidess[]){

	int i;

	printf("The sides of the triangule are:\n");

	for ( i = 0; i < 3; i++ ){

		printf("side %d = %lf\n", i + 1, sidess[i]);
	}
}

void print_perimeter(const struct triangule triangule){

	printf("Perimeter of the triangule is: %lf\n", perimeter_triangule(triangule));
}

void print_area(const struct triangule triangule){

	double area = area_triangule(triangule);

	printf("Area of the triangule is: %lf\n", area);
}