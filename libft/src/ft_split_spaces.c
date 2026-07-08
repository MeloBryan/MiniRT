/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:43:41 by bmelo             #+#    #+#             */
/*   Updated: 2025/11/21 11:34:50 by bmelo            ###   ########.fr       */
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
		if (s[i] != ' ' && s[i] != '\t'
			&& (s[i + 1] == ' ' || s[i + 1] == '\t' || s[i + 1] == '\0'))
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

static void	*free_all(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

static int	split_loop(char **tab, char const *s)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = -1;
	while (1)
	{
		if (s[i] && s[i] != ' ' && s[i] != '\t' && start < 0)
			start = i;
		else if ((!s[i] || s[i] == ' ' || s[i] == '\t') && start >= 0)
		{
			tab[j] = fill_word(s, start, i);
			if (!tab[j])
				return (free_all(tab, j - 1), -1);
			j++;
			start = -1;
		}
		if (!s[i++])
			return (j);
	}
}

char	**ft_split_spaces(char const *s)
{
	char	**tab;
	int		words;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_words(s) + 1));
	if (!tab)
		return (NULL);
	words = split_loop(tab, s);
	if (words < 0)
		return (NULL);
	tab[words] = NULL;
	return (tab);
}
