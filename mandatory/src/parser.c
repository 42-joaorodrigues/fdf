/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:14:31 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:14:37 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
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
		exit(1);
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
		return (perror("open"), exit(1), -1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), exit(1), -1);
	split = ft_split(line, ' ');
	if (!split)
		exit(1);
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

void	alloc_map(t_fdf *fdf)
{
	int	i;

	fdf->map = malloc(sizeof(t_point *) * fdf->map_height);
	if (!fdf->map)
		exit(1);
	i = -1;
	while (++i < fdf->map_height)
	{
		fdf->map[i] = malloc(sizeof(t_point) * fdf->map_width);
		if (!fdf->map[i])
		{
			while (--i >= 0)
				free(fdf->map[i]);
			free(fdf->map);
			exit(1);
		}
	}
}

int	fill_map_line(t_fdf *fdf, int fd, int y)
{
	char	*temp;
	char	**split;
	int		x;

	temp = get_next_line(fd);
	if (!temp)
		return (0);
	split = ft_split(temp, ' ');
	free(temp);
	if (!split)
		return (close(fd), free_map(fdf), exit(1), -1);
	x = -1;
	while (split[++x] && x < fdf->map_width)
	{
		fdf->map[y][x].x = x;
		fdf->map[y][x].y = y;
		fdf->map[y][x].z = ft_atoi(split[x]);
		temp = ft_strchr(split[x], ',');
		if (temp)
			fdf->map[y][x].color = ft_atoi_base(temp + 1, 16);
		else
			fdf->map[y][x].color = -1;
	}
	free_split(split);
	return (1);
}

void	parse_map(t_fdf *fdf, char *path)
{
	int	fd;
	int	y;

	fdf->map_height = get_height(path);
	fdf->map_width = get_width(path);
	alloc_map(fdf);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		free_map(fdf);
		exit(1);
	}
	y = 0;
	while (y < fdf->map_height && fill_map_line(fdf, fd, y) > 0)
		y++;
	close(fd);
}
