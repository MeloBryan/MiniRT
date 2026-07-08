/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 13:40:27 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/08 13:40:27 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	strip_line_end(char *line)
{
	int	i;

	i = 0;
	while (line([i]))
	{
		if (line[i] == '\n' || line[i] == '\r')
			line[i] = '\0';
		i++;
	}
}

int parse_file(char *file_name, t_data *data)
{
    int     fd;
	int		ok;
    char    *line;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (printf("Error\nCould not open file\n"), 0);
    ok = 1;
	while ((line = get_next_line(fd)) != NULL)
    {
		strip_line_end(line);
        if (ok)
            ok = parse_line(line, data);
        free(line);
    }
    close(fd);
    return (ok);
}

int	parse_line(char *line , t_data *data)
{
    while (*line == ' ' || *line == '\t')
        line++;
    if (*line == '\0' || *line == '\n' || *line == '#')
        return (1);
    else if (line[0] == 'A' && (line[1] == ' ' || line[1] == '\t'))
        return (parse_ambient(line, data));
    else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
        return (parse_camera(line, data));
    else if (line[0] == 'L' && (line[1] == ' ' || line[1] == '\t'))
        return (parse_light(line, data));
    // else if (line[0] == 's' && line[1] == 'p' && (line[2] == ' ' || line[2] == '\t'))
    //     parse_sphere(line + 2, data);
    // else if (line[0] == 'p' && line[1] == 'l' && (line[2] == ' ' || line[2] == '\t'))
    //     parse_plane(line + 2, data);
    // else if (line[0] == 'c' && line[1] == 'y' && (line[2] == ' ' || line[2] == '\t'))
    //     parse_cylinder(line + 2, data);
    return (printf("Error\nUnknown element identifier : %c\n", line[0]), 0);
}

int matrix_length(char **tokens)
{
    int i;

    if (!tokens)
        return (0);
    i = 0;
    while (tokens[i])
        i++;
    return (i);
}
