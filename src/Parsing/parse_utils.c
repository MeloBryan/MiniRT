/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 15:12:25 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/11 17:25:18 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	rt_error(char *msg)
{
	printf("Error\n%s\n", msg);
	return (0);
}

int	matrix_length(char **tokens)
{
	int	i;

	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

int	parse_vec3(char *token, t_vector *vec)
{
	char	**parts;

	parts = ft_split(token, ',');
	if (matrix_length(parts) != 3)
		return (free_matrix(parts), 0);
	if (!parse_double(parts[0], &vec->x) || !parse_double(parts[1], &vec->y)
		|| !parse_double(parts[2], &vec->z))
		return (free_matrix(parts), 0);
	free_matrix(parts);
	return (1);
}

int	parse_color(char *token, t_color *color)
{
	char	**parts;
	int		rgb[3];

	parts = ft_split(token, ',');
	if (matrix_length(parts) != 3)
		return (free_matrix(parts), 0);
	if (!is_valid_int(parts[0]) || !is_valid_int(parts[1])
		|| !is_valid_int(parts[2]))
		return (free_matrix(parts), 0);
	rgb[0] = ft_atoi(parts[0]);
	rgb[1] = ft_atoi(parts[1]);
	rgb[2] = ft_atoi(parts[2]);
	free_matrix(parts);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
		return (0);
	color->x = rgb[0] / 255.0;
	color->y = rgb[1] / 255.0;
	color->z = rgb[2] / 255.0;
	return (1);
}

int	parse_direction(char *token, t_vector *vec)
{
	if (!parse_vec3(token, vec))
		return (0);
	if (vec->x < -1.0 || vec->x > 1.0 || vec->y < -1.0 || vec->y > 1.0
		|| vec->z < -1.0 || vec->z > 1.0)
		return (0);
	if (vec->x == 0.0 && vec->y == 0.0 && vec->z == 0.0)
		return (0);
	*vec = normalization(*vec);
	return (1);
}
