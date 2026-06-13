/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 01:41:41 by marvin            #+#    #+#             */
/*   Updated: 2026/06/13 01:41:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void    parse_camera(char *line, t_data *data)
{
    char    **tokens;
    char    **pos_tokens;
    char    **dir_tokens;

    if (data->camera_already_set == 1)
    {
        printf("Error\nMultiple camera detected\n");
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
        printf("Error\nInvalid camera format\n");
        return (free_matrix(tokens));
    }
    pos_tokens = ft_split(tokens[0], ',');
    if (matrix_length(pos_tokens) != 3)
    {
        printf("Error\nPOSITION must have 3 values (x,y,z)\n");
        return (free_matrix(tokens), free_matrix(pos_tokens));
    }
    data->cam_pos.x = ft_atof(pos_tokens[0]);
    data->cam_pos.y = ft_atof(pos_tokens[1]);
    data->cam_pos.z = ft_atof(pos_tokens[2]);
    dir_tokens = ft_split(tokens[1], ',');
    if (matrix_length(dir_tokens) != 3)
    {
        printf("Error\nDIRECTION must have 3 values (x,y,z)\n");
        return (free_matrix(tokens), free_matrix(pos_tokens));
    }
    data->cam_dir.x = ft_atof(dir_tokens[0]);
    data->cam_dir.y = ft_atof(dir_tokens[1]);
    data->cam_dir.z = ft_atof(dir_tokens[2]);
    if (data->cam_dir.x < -1.0 || data->cam_dir.x > 1.0 ||
        data->cam_dir.y < -1.0 || data->cam_dir.y > 1.0 ||
        data->cam_dir.z < -1.0 || data->cam_dir.z > 1.0)
    {
        printf("Error\nInvalid direction value(must be between -1 and 1)\n");
        return (free_matrix(tokens), free_matrix(pos_tokens), free_matrix(dir_tokens));
    }
    data->cam_fov = ft_atof(tokens[2]);
    if (data->cam_fov < 0 || data->cam_fov > 180)
    {
        printf("Error\nFOV velue must be between 0 and 180\n");
        return (free_matrix(tokens), free_matrix(pos_tokens), free_matrix(dir_tokens));
    }
    data->camera_already_set = 1;
    free_matrix(tokens);
    free_matrix(pos_tokens);
    free_matrix(dir_tokens);
}