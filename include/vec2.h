#ifndef VEC2_H
# define VEC2_H

# include "shared.h"

typedef struct vec2
{
	double	x;
	double	y;
}			t_vec2;

typedef struct vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

t_vec3		vec3_scale(t_vec3 a, float s);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);

t_vec2		add_vec2(t_vec2 a, t_vec2 b);
t_vec2		vec2_sub_vec2(t_vec2 a, t_vec2 b);
t_vec2		vec2_scale(t_vec2 a, double b);
t_vec2		vec2_mul_vec2(t_vec2 a, t_vec2 b);
void		vec2_normalized(t_vec2 *vec);
void		vec2_rotate(t_vec2 *vec, double angle);
double		vec2_to_angle(t_vec2 vec2);
double		vec2_mag(t_vec2 vec);

#endif

