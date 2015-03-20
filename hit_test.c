#include "raytracer.h"

char *hit_test_tos(hit_test t)
{
	char* string = malloc(sizeof(char)*235);
	snprintf(string, 235, 
		"HIT TEST\nMiss?: %d\nTime: %f\nHit Point:\n%sSurface Colour:\
		\n%sShine:\n%sSurface Normal:\n%s\n", t.miss, t.t, 
		v3_tos(t.hit_point), rgb_tos(t.surf), rgb_tos(t.shine), 
		v3_tos(t.surf_norm));
	return string;
}

void hit_test_show(FILE *f, hit_test t)
{
	fprintf(f, "%s", hit_test_tos(t));
}
