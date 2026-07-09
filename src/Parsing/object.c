/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 13:29:47 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/09 13:31:28 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*add_object(t_scene *scene, t_object obj)
{
	t_object	*node;
	t_object	*last;

	node = malloc(sizeof(t_object));
	if (!node)
		return (NULL);
	*node = obj;
	node->next = NULL;
	if (!scene->objects)
		scene->objects = node;
	else
	{
		last = scene->objects;
		while (last->next)
			last = last->next;
		last->next = node;
	}
	return (node);
}

void	free_objects(t_scene *scene)
{
	t_object	*node;
	t_object	*next;

	node = scene->objects;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	scene->objects = NULL;
}
