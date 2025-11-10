/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:52:50 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/08 12:52:51 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_vec2	vec2_mul_vec2(t_vec2 a, t_vec2 b)
{
	t_vec2	res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	return (res);
}

t_vec2	vec2_scale(t_vec2 a, double b)
{
	t_vec2	res;

	res.x = a.x * b;
	res.y = a.y * b;
	return (res);
}

double	vec2_mag(t_vec2 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

void	vec2_normalized(t_vec2 *vec)
{
	double	magnitude;

	magnitude = sqrt(vec->x * vec->x + vec->y * vec->y);
	if (magnitude != 0.f)
	{
		vec->x /= magnitude;
		vec->y /= magnitude;
	}
}

void	vec2_rotate_vec2(t_vec2 *vec, double angle)
{
	double	x;
	double	y;

	x = vec->x;
	y = vec->y;
	vec->x = x * cos(angle) - y * sin(angle);
	vec->y = x * sin(angle) + y * cos(angle);
}
