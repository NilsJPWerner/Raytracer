#include "raytracer.h"

rgb rgb_expr(double r, double g, double b)
{
	if (r > 1.0 || r < 0.0 || g > 1.0 || g < 0.0 || b > 1.0 || b < 0.0)
	{
		fprintf(stderr, "rgb values outside range\n");
		exit(0);
	}
	rgb color;
	color.r = r;
	color.g = g;
	color.b = b;
	return color;
}

rgb rgb_modulate(rgb c1, rgb c2)
{
	rgb cfinal;
	cfinal.r = c1.r * c2.r;
	cfinal.g = c1.g * c2.g;
	cfinal.b = c1.b * c2.b;
	return cfinal;
}

rgb rgb_scale(double s, rgb c)
{
	rgb cfinal;
	cfinal.r = (c.r*s < 0)? 0 : (c.r*s > 1)? 1 : c.r * s;
	cfinal.g = (c.g*s < 0)? 0 : (c.g*s > 1)? 1 : c.g * s;
	cfinal.b = (c.b*s < 0)? 0 : (c.b*s > 1)? 1 : c.b * s;
	return cfinal;
}

rgb rgb_add(rgb c1, rgb c2)
{
	rgb cfinal;
	cfinal.r = (c1.r + c2.r > 1)? 1 : c1.r + c2.r;
	cfinal.g = (c1.g + c2.g > 1)? 1 : c1.g + c2.g;
	cfinal.b = (c1.b + c2.b > 1)? 1 : c1.b + c2.b;
	return cfinal;
}

char *rgb_tos(rgb c)
{
	char* string = malloc(sizeof(char)*35);
	snprintf(string, 35, "%.2f, %.2f, %.2f\n", 
		c.r, c.g, c.b);
	return string;
}

void rgb_show(FILE *f, rgb c)
{
	fprintf(f, "%s\n", rgb_tos(c));
}

void rgb_show_bytes(FILE *f, rgb c)
{
	fprintf(f, "%d %d %d\n", (int)(c.r*255), 
		(int)(c.g*255), (int)(c.b*255));
}



