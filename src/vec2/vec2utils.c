/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:52:53 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/08 12:52:54 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_vec2	calculate_plane(t_vec2 dir)
{
	t_vec3	result;

	result = vec3_cross((t_vec3){dir.x, dir.y, 0}, (t_vec3){0, 0, 1});
	result = vec3_scale(result, sin((R_FOV / 2)));
	return ((t_vec2){result.x, result.y});
}

double	vec2_to_angle(t_vec2 vec2)
{
	double	res;

	res = atan2(vec2.y, vec2.x);
	if (res < 0)
		res += M_PI * 2;
	return (res);
}

t_vec2	vec2_add_vec2(t_vec2 a, t_vec2 b)
{
	t_vec2	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

t_vec2	vec2_sub_vec2(t_vec2 a, t_vec2 b)
{
	t_vec2	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return (res);
}
