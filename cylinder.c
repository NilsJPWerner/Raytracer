#include "raytracer.h"

cylinder cylinder_expr(v3 c, double r, double h, rgb(*sc)(v3,v3), rgb sh)
{
	cylinder cyl;
	cyl.center = c;
	cyl.radius = r;
	cyl.height = h;
	cyl.surface_color = sc;
	cyl.shine = sh;
	return cyl;
}

char *cylinder_tos(cylinder c)
{
	char* string = malloc(sizeof(char)*110);
	snprintf(string, 110, 
		"CYLINDER\nCenter:\n%sRadius: %.2f\nHeight: %.2f\nShine:\n%s\n", 
		v3_tos(c.center), c.radius, c.height, rgb_tos(c.shine));
	return string;
}

void cylinder_show(FILE *f, cylinder c)
{
	fprintf(f, "%s\n", cylinder_tos(c));
}