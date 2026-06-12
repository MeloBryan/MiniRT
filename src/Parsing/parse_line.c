/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 18:27:46 by marvin            #+#    #+#             */
/*   Updated: 2026/06/12 18:27:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int parse_file(char *file_name, t_data *data)
{
    int     fd;
    char    *line;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (printf("Error\nCOuld not open file\n"), 0);
    while ((line = get_next_line(fd)) != NULL)
    {
        if (line && line[0] != '\n')
            parse_line(line, data);
        free(line);
    }
    close(fd);
    return (1);
}

void    parse_line(char *line , t_data *data)
{
    while (*line == ' ' || *line == '\t')
        line++;
    if (*line == '\0' || *line == '\n' || *line == '#')
        return ;
    else if (line[0] == 'A' && (line[1] == ' ' || line[1] == '\t'))
        parse_ambient(line + 1, data);
    // else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
    //     parse_camera(line + 1, data);
    // else if (line[0] == 'L' && (line[1] == ' ' || line[1] == '\t'))
    //     parse_light(line + 1, data);
    // else if (line[0] == 's' && line[1] == 'p' && (line[2] == ' ' || line[2] == '\t'))
    //     parse_sphere(line + 2, data);
    // else if (line[0] == 'p' && line[1] == 'l' && (line[2] == ' ' || line[2] == '\t'))
    //     parse_plane(line + 2, data);
    // else if (line[0] == 'c' && line[1] == 'y' && (line[2] == ' ' || line[2] == '\t'))
    //     parse_cylinder(line + 2, data);
    else
    {
        printf("Error\nUnknown element identifier : %c\n", line[0]);
        //set flag pour erreur
    }
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