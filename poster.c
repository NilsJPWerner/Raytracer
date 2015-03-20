#include "raytracer.h"

poster poster_expr(v3 ulc, double w, double h, rgb(*sc)(v3,v3), rgb sh)
{
	poster p;
	p.upper_left = ulc;
	p.w = w;
	p.h = h;
	p.surface_color = sc;
	p.shine = sh;
	return p;
}

char *poster_tos(poster s)
{
	char* string = malloc(sizeof(char)*120);
	snprintf(string, 120, 
		"POSTER\nULC:\n%sWidth: %.2f\nHeight: %.2f\nShine:\n%s\n", 
		v3_tos(s.upper_left), s.w, s.h, rgb_tos(s.shine));
	return string;
}

void poster_show(FILE *f, poster s)
{
	fprintf(f, "%s", poster_tos(s));
}