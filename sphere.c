#include "raytracer.h"

sphere sphere_expr(v3 v, double r, rgb(*sc)(v3,v3), rgb sh)
{
	sphere s;
	s.center = v;
	s.radius = r;
	s.surface_color = sc;
	s.shine = sh;
	return s;
}

char *sphere_tos(sphere s)
{
	char* string = malloc(sizeof(char)*110);
	snprintf(string, 110, 
		"SPHERE\nCenter:\n%sRadius: %.2f\nShine:\n%s\n", 
		v3_tos(s.center), s.radius, rgb_tos(s.shine));
	return string;
}

void sphere_show(FILE *f, sphere s)
{
	fprintf(f, "%s", sphere_tos(s));
}