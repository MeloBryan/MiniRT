/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 02:12:04 by marvin            #+#    #+#             */
/*   Updated: 2026/06/13 02:12:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void    parse_light(char *line, t_data *data)
{
    char    **tokens;
    char    **pos_tokens;
    char    **color_tokens;
    int     r;
    int     g;
    int     b;

    if (data->light_already_set == 1)
    {
        printf("Error\nMultiple light detected\n");
        return ;
    }
    tokens = ft_split_spaces(line);
    printf("DEBUG: matrix_length = %d\n", matrix_length(tokens));
    for (int k = 0; tokens && tokens[k]; k++)
        printf("  tokens[%d] = '%s'\n", k, tokens[k]);
    if (!tokens)
        return ;
    if (matrix_length(tokens) != 4)
    {
        printf("Error\nInvalid light format\n");
        return (free_matrix(tokens));
    }
    pos_tokens = ft_split(tokens[1], ',');
    if (matrix_length(pos_tokens) != 3)
    {
        printf("Error\nPOSITION must have 3 values (x,y,z)\n");
        return (free_matrix(tokens), free_matrix(pos_tokens));
    }
    data->light_pos.x = ft_atof(pos_tokens[0]);
    data->light_pos.y = ft_atof(pos_tokens[1]);
    data->light_pos.z = ft_atof(pos_tokens[2]);
    data->light_ratio = ft_atof(tokens[2]);
    if (data->light_ratio < 0.0 || data->light_ratio > 1.0)
    {
        printf("Error\nInvalid light ratio value(must be between 0 and 1)\n");
        return (free_matrix(tokens), free_matrix(pos_tokens));
    }
    color_tokens = ft_split(tokens[3], ',');
    if (matrix_length(color_tokens) != 3)
    {
        printf("Error\nLight RGB must have 3 values (R,G,B)\n");
        return (free_matrix(tokens), free_matrix(pos_tokens), free_matrix(color_tokens));
    }
    r = ft_atoi(color_tokens[0]);
    g = ft_atoi(color_tokens[1]);
    b = ft_atoi(color_tokens[2]);
    if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
    {
        printf("Error\nRGB color values must be between 0 and 255\n");
        return (free_matrix(tokens), free_matrix(pos_tokens), free_matrix(color_tokens));
    }
    data->light_color = (r << 16) | (g << 8) | b;
    data->light_already_set = 1;
    free_matrix(tokens);
    free_matrix(pos_tokens);
    free_matrix(color_tokens);
}