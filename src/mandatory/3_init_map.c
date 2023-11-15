#include "../../include/fdf.h"

void	init_each_line(int fd, uint32_t h, uint32_t width, t_map *map)
{
	uint32_t	w;
	char		*gnl_line;
	char		**split_line;

	gnl_line = get_next_line(fd);
	if(gnl_line == NULL)
		error("invalid map size");
	split_line = ft_split(gnl_line, ' ');
	map->matrix[h] = (t_matrix *)malloc(sizeof(t_matrix) * width);
	if (map->matrix[h] == NULL)
		free_matrix((void **)map->matrix);
	w = 0;
	while (w < width)
	{ 
		map->matrix[h][w].x = w;
		map->matrix[h][w].y = h;
		map->matrix[h][w].z = ft_atoi(split_line[w]);
		map->matrix[h][w].color = get_color(split_line[w]);
		printf("x: %d, y: %d, color: %x", map->matrix[h][w].x, map->matrix[h][w].y, map->matrix[h][w].color);
		w++;
	}
	free(gnl_line);
	free_matrix((void **)split_line);
}

t_map	*initialize_matrix(char *map_name, uint32_t width,
		uint32_t height)
{
	int			fd;
	uint32_t	h;
	t_map	*map;

	fd = check_fd(map_name);
	map = (t_map *)malloc(sizeof(t_map) * 1);
	if (map == NULL)
		return (NULL);
	map->matrix = (t_matrix **)malloc(sizeof(t_matrix *) * (height + 1));
	if (map->matrix == NULL)
		return (NULL);
	h = 0;
	while (h < height)
	{
		init_each_line(fd, h, width, map);
		h++;
	}
	map->matrix[h] = NULL;
	close(fd);
	return (map);
}

t_map	*init_map(char *map_name)
{
	uint32_t	width;
	uint32_t	height;
	t_map		*map;

	map = NULL;
	find_width(map_name, &width);
	printf("\nwidth: %d\n", width);
	find_height(map_name, &height);
	printf("height: %d\n", height);
	check_map(map_name, width, height);
	map = initialize_matrix(map_name, width, height);
	map->width = width;
	map->height = height;
	return (map);
}
