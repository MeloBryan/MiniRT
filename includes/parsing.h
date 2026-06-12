/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 01:01:36 by marvin            #+#    #+#             */
/*   Updated: 2026/06/13 01:01:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "miniRT.h"

void    parse_line(char *line , t_data *data);
int     parse_file(char *file_name, t_data *data);
void    parse_ambient(char *line, t_data *data);

int     matrix_length(char **tokens);
void    free_data(t_data *data);
void    free_matrix(char **matrix);

#endif