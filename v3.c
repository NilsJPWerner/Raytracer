#include "raytracer.h"

v3 v3_expr(double x, double y, double z)
{
	v3 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}

v3 v3_add(v3 v1, v3 v2)
{
	v3 vfinal;
	vfinal.x = v1.x + v2.x;
	vfinal.y = v1.y + v2.y;
	vfinal.z = v1.z + v2.z;
	return vfinal;
}

v3 v3_sub(v3 v1, v3 v2)
{
	v3 vfinal;
	vfinal.x = v1.x - v2.x;
	vfinal.y = v1.y - v2.y;
	vfinal.z = v1.z - v2.z;
	return vfinal;
}

v3 v3_neg(v3 v)
{
	v3 vfinal;
	vfinal.x = v.x * -1;
	vfinal.y = v.y * -1;
	vfinal.z = v.z * -1;
	return vfinal;
}

v3 v3_scale(double s, v3 v)
{
	v3 vfinal;
	vfinal.x = v.x * s;
	vfinal.y = v.y * s;
	vfinal.z = v.z * s;
	return vfinal;
}

double v3_dot(v3 v1, v3 v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

double v3_mag(v3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

v3 v3_norm(v3 v)
{
	double mag = v3_mag(v);
	return (mag==0)? v : v3_scale(1.0/mag, v);
}

char *v3_tos(v3 v)
{
	char* string = malloc(sizeof(char)*30);
	snprintf(string, 30, "%.2f, %.2f, %.2f\n", v.x, v.y, v.z);
	return string;
}

void v3_show(FILE *f, v3 v)
{
	fprintf(f, "%s\n", v3_tos(v));
}
