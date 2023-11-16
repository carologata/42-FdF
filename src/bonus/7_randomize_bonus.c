/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_randomize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:57:40 by cogata            #+#    #+#             */
/*   Updated: 2023/11/16 13:57:42 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	transform(t_coordinate *point_1, t_coordinate *point_2, t_map *map)
{
	scale(point_1, point_2, map);
	rotation_in_z(point_1, point_2, map);
	rotation_in_x(point_1, point_2, map);
	rotation_in_y(point_1, point_2, map);
	oblique(point_1, point_2, map);
	translate(point_1, point_2, map);
	bresenham(point_1, point_2, map);
}

void	init_points(int x1, int y1, char type, t_map *map)
{
	t_coordinate	point_1;
	t_coordinate	point_2;

	point_1.x = map->matrix[y1][x1].x;
	point_1.y = map->matrix[y1][x1].y;
	point_1.z = map->matrix[y1][x1].z;
	point_1.color = map->matrix[y1][x1].color;
	if (type == 'w')
	{
		point_2.x = map->matrix[y1][x1 + 1].x;
		point_2.y = map->matrix[y1][x1 + 1].y;
		point_2.z = map->matrix[y1][x1 + 1].z;
	}
	else
	{
		point_2.x = map->matrix[y1 + 1][x1].x;
		point_2.y = map->matrix[y1 + 1][x1].y;
		point_2.z = map->matrix[y1 + 1][x1].z;
	}
	transform(&point_1, &point_2, map);
}

void	randomize(t_map *map)
{
	uint32_t	w;
	uint32_t	h;

	h = 0;
	while (h < map->height)
	{
		w = 0;
		while (w < map->width)
		{
			if ((w + 1) < map->width)
				init_points(w, h, 'w', map);
			if ((h + 1) < map->height)
				init_points(w, h, 'h', map);
			w++;
		}
		h++;
	}
}
