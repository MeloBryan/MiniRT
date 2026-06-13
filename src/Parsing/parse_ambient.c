/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 00:57:29 by marvin            #+#    #+#             */
/*   Updated: 2026/06/13 00:57:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void    parse_ambient(char *line, t_data *data)
{
    char    **tokens;
    char    **rgb_tokens;
    int     r;
    int     g;
    int     b;

    if (data->ambient_already_set == 1)
    {
        printf("Error\nMultiple Ambient lights detected\n");
        return ;
    }
    tokens = ft_split_spaces(line);
    printf("DEBUG: matrix_length = %d\n", matrix_length(tokens));
    for (int k = 0; tokens && tokens[k]; k++)
        printf("  tokens[%d] = '%s'\n", k, tokens[k]);
    if (!tokens)
        return ;
    if (matrix_length(tokens) != 3)
    {
        printf("Error\nInvalid Ambient light format\n");
        return (free_matrix(tokens));
    }
    data->ambient_ratio = ft_atof(tokens[1]);
    if (data->ambient_ratio < 0.0 || data->ambient_ratio > 1.0)
    {
        printf("Error\nAmbient ratio must be between 0.0 and 1.0\n");
        return (free_matrix(tokens));
    }
    rgb_tokens = ft_split(tokens[2], ',');
    if (matrix_length(rgb_tokens) != 3)
    {
        printf("Error\nAmbient RGB must have 3 values (R,G,B)\n");
        return (free_matrix(tokens), free_matrix(rgb_tokens));
    }
    r = ft_atoi(rgb_tokens[0]);
    g = ft_atoi(rgb_tokens[1]);
    b = ft_atoi(rgb_tokens[2]);
    if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
    {
        printf("Error\nRGB color values must be between 0 and 255\n");
        return (free_matrix(tokens), free_matrix(rgb_tokens));
    }
    data->ambient_color = (r << 16) | (g << 8) | b;
    data->ambient_already_set = 1;
    free_matrix(tokens);
    free_matrix(rgb_tokens);
}