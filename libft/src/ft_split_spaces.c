/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 00:46:40 by marvin            #+#    #+#             */
/*   Updated: 2026/06/13 00:46:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' &&
			(s[i + 1] == ' ' || s[i + 1] == '\t' || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*fill_word(char const *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static char	**free_all(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

char	**ft_split_spaces(char const *s)
{
	char	**tab;
	int		i;
	int		j;
	int		start;

	tab = malloc(sizeof(char *) * (count_words(s) + 1));
	if (!tab || !s)
		return (NULL);
	i = 0;
	j = 0;
	start = -1;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && start < 0)
			start = i;
		else if ((s[i] == ' ' || s[i] == '\t') && start >= 0)
		{
			tab[j++] = fill_word(s, start, i);
			if (!tab[j - 1])
				return (free_all(tab, j - 2));
			start = -1;
		}
		i++;
	}
	if (start >= 0)
	{
		tab[j++] = fill_word(s, start, i);
		if (!tab[j - 1])
			return (free_all(tab, j - 2));
	}
	tab[j] = NULL;
	return (tab);
}