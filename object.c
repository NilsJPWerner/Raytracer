#include "raytracer.h"

char *object_tos(object o)
{
	if (o.tag == SPHERE) return sphere_tos(o.o.s); 
	if (o.tag == POSTER) return poster_tos(o.o.p);
	if (o.tag == CYLINDER) return cylinder_tos(o.o.c);
	else
	{
		fprintf(stderr, "Shape not recognized\n");
		exit(0);
	}
}

void object_show(FILE *f, object o)
{
	fprintf(f, "%s\n", object_tos(o));
}