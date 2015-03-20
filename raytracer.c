#include "raytracer.h"

v3 logical_loc(camera c, unsigned int x, unsigned int y)
{
	float pixelw = 2.0/((c.h > c.w)? c.h : c.w);
	v3 pos;
	pos.z = 0.0;
	pos.x = (c.h > c.w)? -1.0 * (double)c.w/c.h : -1.0;
	pos.x += pixelw * (double)x + pixelw/2.0;
	pos.y = (c.h > c.w)? 1.0 : (double)c.h/c.w;
	pos.y -= pixelw * (double)y + pixelw/2.0;
	return pos;
}

int shadow(v3 p, light l, obj_list *objs)
{
	v3 nudge = v3_scale(0.0001, l.direction);
	v3 lifted = v3_add(p, nudge);
	ray shadowray; 
	shadowray.origin = lifted;
	shadowray.direction = l.direction;
	while (objs)
	{
		hit_test h = intersect(shadowray, objs->obj);
		if (h.miss == HIT) return 1;
		objs = objs->next;
	}
	return 0;
}

double max(double a, double b)
{
	return (a > b)? a : b;
}

rgb lighting(scene s, ray r, hit_test h)
{
	rgb colour;
	if (h.miss == MISS)
	{
		colour = s.bg;
		return colour;
	}
	else if (shadow(h.hit_point, s.light, s.objects))
	{
		colour = rgb_modulate(h.surf, s.amb);
	}
	else
	{
		rgb dif = rgb_scale(max(0, v3_dot(h.surf_norm, s.light.direction)),
							s.light.color);
		colour = rgb_modulate(rgb_add(dif, s.amb), h.surf);
	}
	v3 Ns = h.surf_norm;
	v3 Ls = s.light.direction;
	rgb Ss = h.shine;
	v3 Rs = v3_sub(v3_scale(2 * v3_dot(Ns, Ls), Ns), Ls);
	v3 Vs = v3_neg(r.direction);
	rgb spec;
	if (v3_dot(Ns, Ls) > 0)
	{
		spec = rgb_scale(pow(max(v3_dot(Rs, Vs), 0), 6), Ss);
	}
	else 
	{
		spec = rgb_expr(0,0,0);
	}
	return rgb_add(colour, spec);
}

rgb trace_ray(scene s, ray r)
{
	hit_test htemp;
	htemp.miss = MISS;
	hit_test hfinal;
	hfinal.miss = MISS;
	hfinal.t = 1000000000.0;
	obj_list* list = s.objects;
	while (list) 
	{
		htemp = intersect(r, list->obj);
		if (htemp.miss == HIT && htemp.t < hfinal.t)
		{
			hfinal = htemp;
		}
		list = list->next;
	}
	return lighting(s, r, hfinal);
}

void render(FILE *f, stage g)
{
	g.s.light.direction = v3_norm(g.s.light.direction);
	fprintf(f, "P3\n%d %d\n255\n",g.c.w, g.c.h);
	int y, x;
	ray r;
	r.origin = g.c.loc;
	for (y = 0; y < g.c.h; y++)
	{
		for (x = 0; x < g.c.w; x++)
		{
			r.direction = v3_norm(v3_sub(logical_loc(g.c, x, y), g.c.loc));
			rgb_show_bytes(f, trace_ray(g.s, r));
		}
	}
}


