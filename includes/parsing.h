/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 14:59:57 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/09 14:59:57 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structures.h"
# include "image.h"

int			parse_file(char *file_name, t_scene *scene);
int			parse_line(char *line, t_scene *scene);
int			parse_ambient(char *line, t_scene *scene);
int			parse_camera(char *line, t_scene *scene);
int			parse_light(char *line, t_scene *scene);
int			parse_sphere(char *line, t_scene *scene);
int			parse_plane(char *line, t_scene *scene);
int			parse_cylinder(char *line, t_scene *scene);

int			rt_error(char *msg);
int			parse_vec3(char *token, t_vector *vec);
int			parse_direction(char *token, t_vector *vec);
int			parse_color(char *token, t_color *color);
int			check_extension(char *file_name);
int			matrix_length(char **tokens);
int			is_valid_double(char *str);
int			is_valid_int(char *str);
int			parse_double(char *token, double *out);

t_object	*add_object(t_scene *scene, t_object obj);
void		free_objects(t_scene *scene);
void		free_data(t_data *data);
void		free_matrix(char **matrix);

#endif
