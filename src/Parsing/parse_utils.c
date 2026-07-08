/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 15:12:25 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/08 15:12:40 by edefoy           ###   ########.fr       */
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
	vec->x = ft_atof(parts[0]);
	vec->y = ft_atof(parts[1]);
	vec->z = ft_atof(parts[2]);
	free_matrix(parts);
	return (1);
}

int	parse_rgb(char *token, int *color)
{
	char	**parts;
	int		rgb[3];

	parts = ft_split(token, ',');
	if (matrix_length(parts) != 3)
		return (free_matrix(parts), 0);
	rgb[0] = ft_atoi(parts[0]);
	rgb[1] = ft_atoi(parts[1]);
	rgb[2] = ft_atoi(parts[2]);
	free_matrix(parts);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
		return (0);
	*color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (1);
}

int	check_extension(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	if (len < 4)
		return (0);
	return (ft_strncmp(file_name + len - 3, ".rt", 3) == 0);
}
