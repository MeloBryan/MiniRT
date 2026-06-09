/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec_Length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:09:19 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/09 16:10:44 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	vec_length(t_vector A)
{
	double	length;

	length = sqrt(dot_product(A, A));
	return (length);
}
