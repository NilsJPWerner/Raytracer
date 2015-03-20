#include "raytracer.h"

char *light_tos(light l)
{
	char* string = malloc(sizeof(char)*100);
	snprintf(string, 100, "Direction:\n%sColour:\n%s",
		v3_tos(l.direction), rgb_tos(l.color));
	return string;
}

void light_show(FILE *f, light l)
{
	fprintf(f, "%s\n", light_tos(l));
}