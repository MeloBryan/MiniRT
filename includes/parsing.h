/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 14:13:42 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/08 14:13:42 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "miniRT.h"

int		parse_file(char *file_name, t_data *data);
int		parse_line(char *line , t_data *data);
int		parse_ambient(char *line, t_data *data);
int		parse_camera(char *line, t_data *data);
int		parse_light(char *line, t_data *data);

int		matrix_length(char **tokens);
void	free_data(t_data *data);
void	free_matrix(char **matrix);

#endif