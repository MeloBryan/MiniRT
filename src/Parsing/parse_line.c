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

int	parse_line(char *line, t_data *data)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0' || *line == '#')
		return (1);
	if (line[0] == 'A' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_ambient(line, data));
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_camera(line, data));
	if (line[0] == 'L' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_light(line, data));
	return (rt_error("Unknown element identifier"));
}

int	parse_file(char *file_name, t_data *data)
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
			ok = parse_line(line, data);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (ok && (!data->ambient_already_set || !data->camera_already_set
			|| !data->light_already_set))
		return (rt_error("Scene must define A, C and L elements"));
	return (ok);
}
