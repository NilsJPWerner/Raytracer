#include "raytracer.h"

v3 ray_position(ray r, double t)
{
  return v3_add(r.origin, v3_scale(t, r.direction));
}

char *ray_tos(ray r)
{
	char* string = malloc(sizeof(char)*92);
	snprintf(string, 92, "Origin:\n%s\nDirection:\n%s\n", 
		v3_tos(r.origin), v3_tos(r.direction));
	return string;
}

void ray_show(FILE *f, ray r)
{
	fprintf(f, "%s\n", ray_tos(r));
}