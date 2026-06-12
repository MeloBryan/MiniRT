/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cross_Vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 23:59:36 by marvin            #+#    #+#             */
/*   Updated: 2026/06/11 23:59:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector    cross_vec(t_vector A, t_vector B)
{
    t_vector    res;

    res.x = (A.y * B.z) - (A.z * B.y);
    res.y = (A.z * B.x) - (A.x * B.z);
    res.z = (A.x * B.y) - (A.y * B.x);
    return (res);
}