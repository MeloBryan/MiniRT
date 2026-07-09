/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 15:14:50 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/08 15:14:50 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	strip_line_end(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\r')
			line[i] = '\0';
		i++;
	}
}

int	parse_line(char *line, t_scene *scene)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0' || *line == '#')
		return (1);
	if (line[0] == 'A' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_ambient(line, scene));
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_camera(line, scene));
	if (line[0] == 'L' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_light(line, scene));
	if (line[0] == 's' && line[1] == 'p'
		&& (line[2] == ' ' || line[2] == '\t'))
		return (parse_sphere(line, scene));
	if (line[0] == 'p' && line[1] == 'l'
		&& (line[2] == ' ' || line[2] == '\t'))
		return (parse_plane(line, scene));
	return (rt_error("Unknown element identifier"));
}
 
int	check_extension(char *file_name)
{
	int	len;
 
	len = ft_strlen(file_name);
	if (len < 4)
		return (0);
	return (ft_strncmp(file_name + len - 3, ".rt", 3) == 0);
}

int	parse_file(char *file_name, t_scene *scene)
{
	int		fd;
	int		ok;
	char	*line;

	if (!check_extension(file_name))
		return (rt_error("Scene file must have a .rt extension"));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (rt_error("Could not open file"));
	ok = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		strip_line_end(line);
		if (ok)
			ok = parse_line(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (ok && (!scene->ambient_set || !scene->camera_set
			|| !scene->light_set))
		return (rt_error("Scene must define A, C and L elements"));
	return (ok);
}
