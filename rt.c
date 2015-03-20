#include "raytracer.h"

int main(int argc, char* argv[])
{
	FILE* f = fopen("i.ppm", "w");
	render(f, get_stage(2));
	fclose(f);
	stage_show(stderr,get_stage(2));
	return 0;
}