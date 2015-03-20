#include "raytracer.h"

char *camera_tos(camera cm)
{
	char* string = malloc(sizeof(char)*70);
	snprintf(string, 70, "Location:\n%sHeight:%d\nWidth:%d\n",
		v3_tos(cm.loc), cm.h, cm.w);
	return string;
}

void camera_show(FILE *f, camera cm)
{
	fprintf(f, "%s\n", camera_tos(cm));
}
