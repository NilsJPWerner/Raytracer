#include "raytracer.h"

hit_test intersect(ray r, object obj)
{
	hit_test test;

	if (obj.tag == SPHERE) // If Sphere
	{
		v3 a = v3_sub(r.origin, obj.o.s.center);
		double b = v3_dot(a, r.direction);
		double c = v3_dot(a, a) - (obj.o.s.radius * obj.o.s.radius);
		double d = (b * b) - c;
		double t = -b - sqrt(d);
		if (d > 0 && t > 0) // If hit
		{
			test.miss = HIT;
			test.t = t;
			test.hit_point = ray_position(r, t);
			test.surf = obj.o.s.surface_color(obj.o.s.center, 
				test.hit_point);
			test.shine = obj.o.s.shine;
			test.surf_norm = v3_norm(v3_sub(test.hit_point, 
				obj.o.s.center));
			return test;
		}
		else //If Miss
		{
			test.miss = MISS;
			return test;
		}
	}
	else if (obj.tag == POSTER) // If Poster
	{
		v3 n = v3_expr(0, 0, -1);
		double d = obj.o.p.upper_left.z;
		double t = -(v3_dot(r.origin, n) + d) 
			/ v3_dot(v3_norm(r.direction), n);
		
		v3 pos = ray_position(r, t);
		v3 ULC = obj.o.p.upper_left;
		v3 LRC = ULC;
		LRC.x += obj.o.p.w;
		LRC.y -= obj.o.p.h;
		if (t > 0 && pos.x >= ULC.x && pos.x <= LRC.x && pos.y <= ULC.y 
			&& pos.y >= LRC.y)
		{
			test.miss = HIT;
			test.t = t;
			test.hit_point = pos;
			test.surf = obj.o.p.surface_color(ULC, test.hit_point);
			test.shine = obj.o.p.shine;
			test.surf_norm = n;
			return test;
		}
		else //If Miss
		{
			test.miss = MISS;
			return test;
		}
	}
	else if (obj.tag == CYLINDER) // If Cylinder
	{
		v3 ro = r.origin;
		v3 rd = r.direction;

		v3 rp = v3_expr(rd.x, 0, rd.z);
		double mp = v3_mag(rp);
		v3 np = v3_norm(rp);

		double vx = np.x;
		double vz = np.z;
		double sx = ro.x;
		double sz = ro.z;

		v3 cc = obj.o.c.center;
		double cr = obj.o.c.radius;
		double ch = obj.o.c.height;

		double xbar = sx - cc.x;
		double zbar = sz - cc.z;

		double A = vx * vx + vz * vz;
		double B = 2 * (xbar * vx + zbar * vz);
		double C = xbar * xbar + zbar * zbar - cr * cr;
		double D = (B * B) - (4 * A * C);

		if (D >= 0) //If hit
		{
			double t_front = (-B - sqrt(D)) / (2 * A);
			double t_back = (-B + sqrt(D)) / (2 * A);

			v3 p_front = ray_position(r, (t_front/mp));
			v3 p_back = ray_position(r, (t_back/mp));

			if (v3_mag(v3_sub(p_front,ro)) < v3_mag(v3_sub(p_back,ro))
				&& p_front.z > ro.z && p_front.y < cc.y + ch && 
				p_front.y > cc.y && t_front > 0) // If front hit
			{
				test.miss = HIT;
				test.t = t_front;
				test.hit_point = p_front;
				test.surf = obj.o.c.surface_color(cc, test.hit_point);
				test.shine = obj.o.c.shine;
				v3 c = v3_expr(cc.x, test.hit_point.y, cc.z);
				test.surf_norm = v3_norm(v3_sub(test.hit_point, c));
				return test;
			}
			else if (p_back.z > ro.z && p_back.y < cc.y + ch 
					&& p_back.y > cc.y && t_back > 0) // If back hit
			{
				test.miss = HIT;
				test.t = t_back;
				test.hit_point = p_back;
				test.surf = obj.o.c.surface_color(cc, test.hit_point);
				test.shine = obj.o.c.shine;
				v3 c = v3_expr(cc.x, test.hit_point.y, cc.z);
				test.surf_norm = v3_norm(v3_sub(c, test.hit_point));
				return test;
			}
			else //If Miss
			{
				test.miss = MISS;
				return test;
			}
		}
		else //If Miss
		{
			test.miss = MISS;
			return test;
		}
	}
	else
	{
		fprintf(stderr, "ERROR: SHAPE NOT RECOGNIZED\n");
		exit(0);
	}
}