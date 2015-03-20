#include "raytracer.h"

char *stage_tos(stage stg)
{
	int objlen = obj_list_length(stg.s.objects) * 130;
	char* string = malloc(sizeof(char)*300 +objlen);
	snprintf(string, 300+objlen, "STAGE:\n\nCAMERA:\n%s\n%s\n",
		camera_tos(stg.c), scene_tos(stg.s));
	return string;
}

void stage_show(FILE *f, stage stg)
{
	fprintf(f, "%s\n", stage_tos(stg));
}

rgb k_white(v3 cen, v3 loc);
rgb k_white(v3 cen, v3 loc)
{
  if ((loc.x > 0 && loc.y >0) || (loc.x < 0 && loc.y < 0)) 
  	return rgb_expr(0.2,0.2,0.2);
  else return rgb_expr(0.8,0.8,0.8);
}


rgb k_constant(v3 cen, v3 loc);
rgb k_constant(v3 cen, v3 loc)
{
  return rgb_expr(0.5,0.5,0.8);
}

rgb k_silver(v3 cen, v3 loc)
{
  return rgb_expr(0.75,0.75,0.75);
}

stage get_stage(unsigned int selection)
{
	cylinder sph = cylinder_expr(v3_expr(0,-2,10), 0.2, 4.0,  
		k_silver, rgb_expr(1,1,1));
	object os;
	os.tag = CYLINDER;
	os.o.c = sph;

	obj_list* ss = ol_cons(os, NULL);

	light l;
	l.direction = v3_expr(-0.58, 0.58, -0.58);
	l.color = rgb_expr(1, 1, 1);

	scene s;
	s.bg = rgb_expr(0.40, 0.20, 0.10);
	s.objects = ss;
	s.light = l;
	s.amb = rgb_expr(0.3, 0.3, 0.3);

	camera c;
	c.loc = v3_expr(0,0,-5);
	c.h = 300;
	c.w = 400;

	stage stg;
	stg.c = c;
	stg.s = s;

	if (selection == 1) return stg;

	sphere sp2 = sphere_expr(v3_expr(0, 0, 3), 1, 
		k_silver, rgb_expr(0.4,0.4,0.4));
	object os2;
	os2.tag = SPHERE;
	os2.o.s = sp2;

	obj_list* ss2 = ol_cons(os2, NULL);

	scene s2;
	s2.bg = rgb_expr(0, 0, 0);
	s2.objects = ss2;
	s2.light = l;
	s2.amb = rgb_expr(0.1, 0.1, 0.1);

	stage stg2;
	stg2.c = c;
	stg2.s = s2;

	if (selection == 2) return stg2;

	else
	{
		fprintf(stderr, "Wrong Selection\n");
		exit(0);
	} 
}
