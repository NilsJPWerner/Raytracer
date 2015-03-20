#include "raytracer.h"

char *scene_tos(scene sc)
{
	int objlen = obj_list_length(sc.objects) * 130;
	char* string = malloc(sizeof(char)*200 + objlen);
	snprintf(string, 200 + objlen, 
		"SCENE:\nBackground:\n%s\nLight:\n%s\nAmbient:\n%s\nObjects:\n\n%s",
		rgb_tos(sc.bg), light_tos(sc.light), rgb_tos(sc.amb), 
		obj_list_tos(sc.objects));
	return string;
}

void scene_show(FILE *f, scene sc)
{
	fprintf(f, "%s", scene_tos(sc));
}