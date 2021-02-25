/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 11:49:58 by jonny             #+#    #+#             */
/*   Updated: 2021/02/25 10:37:35 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *str)
{
	int	count;
	int	is_word;

	count = 0;
	is_word = 0;
	if (*str == '\0')
		return (0);
	while (*str != '\0')
	{
		if (*str == ' ' || *str == '\t')
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static int	ft_wordlen(const char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char	**ft_memfree(char const **tab, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)tab[j]);
	}
	free(tab);
	return (NULL);
}

static char	**ft_splitstr(char const *s, char **tab, int wc)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < wc)
	{
		k = 0;
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		tab[j] = malloc(sizeof(char) * ft_wordlen(s, i) + 1);
		if (tab[j] == NULL)
			return (ft_memfree((char const **)tab, j));
		while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
			tab[j][k++] = s[i++];
		tab[j][k] = '\0';
		j++;
	}
	tab[j] = 0;
	return (tab);
}

char	**split_whitespace(char const *s)
{
	char	**tab;
	int		wc;

	if (s == NULL)
		return (NULL);
	wc = ft_count_words(s);
	tab = malloc(sizeof(char *) * (wc + 1));
	if (tab == NULL)
		return (NULL);
	return (ft_splitstr(s, tab, wc));
}
