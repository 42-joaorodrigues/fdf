/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:14:31 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/26 16:42:52 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "helper.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	get_height(char *path)
{
	int		fd;
	char	*line;
	int		height;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit (1);
	}
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

int	get_width(char *path)
{
	int		fd;
	char	*line;
	char	**split;
	int		width;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("open"), exit (1), -1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), exit (1), -1);
	split = ft_split(line, ' ');
	if (!split)
		exit (1);
	width = 0;
	while (split[width])
		width++;
	free_split(split);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (width);
}

void	alloc_map(t_map *map)
{
	int	i;
	
	map->points = malloc(sizeof(t_point *) * map->height);
	if (!map->points)
		exit (1);
	i = -1;
	while (++i < map->height)
	{
		map->points[i] = malloc(sizeof(t_point) * map->width);
		if (!map->points[i])
		{
			while (--i >= 0)
				free(map->points[i]);
			free(map->points);
			exit (1);
		}
	}
}

int	fill_map_line(t_map *map, int fd, int y)
{
	char	*line;
	char	**split;
	int		x;
	char	*comma;

	line = get_next_line(fd);
	if (!line)
		return (0);
	split = ft_split(line, ' ');
	free(line);
	if (!split)
		return (close(fd), free_map(map), exit(1), -1);
	x = -1;
	while (split[++x] && x < map->width)
	{
		map->points[y][x].z = ft_atoi(split[x]);
		comma = ft_strchr(split[x], ',');
		if (comma)
			map->points[y][x].color = ft_atoi_base(comma + 1, 16);
		else
			map->points[y][x].color = -1;
	}
	free_split(split);
	return (1);
}

void	parse_map(t_map *map, char *path)
{
	int	fd;
	int	y;
	
	map->height = get_height(path);
	map->width = get_width(path);
	alloc_map(map);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		free_map(map);
		exit(1);
	}
	y = 0;
	while (fill_map_line(map, fd, y) > 0 && y < map->height)
		y++;
	close(fd);
}
