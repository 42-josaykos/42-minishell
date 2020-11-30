/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:47:07 by jonny             #+#    #+#             */
/*   Updated: 2019/11/19 14:47:28 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_words(char const *str, char c)
{
	int count;
	int is_word;

	count = 0;
	is_word = 0;
	if (*str == '\0')
		return (0);
	while (*str != '\0')
	{
		if (*str == c)
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

static int		ft_wordlen(const char *str, char c, int i)
{
	int len;

	len = 0;
	while (str[i] != c && str[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char		**ft_memfree(char const **tab, int j)
{
	while (j > 0)
	{
		j--;
		free((void*)tab[j]);
	}
	free(tab);
	return (NULL);
}

static char		**ft_splitstr(char const *s, char **tab, char c, int wc)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < wc)
	{
		k = 0;
		while (s[i] == c)
			i++;
		tab[j] = malloc(sizeof(char) * ft_wordlen(s, c, i) + 1);
		if (tab[j] == NULL)
			return (ft_memfree((char const**)tab, j));
		while (s[i] != '\0' && s[i] != c)
			tab[j][k++] = s[i++];
		tab[j][k] = '\0';
		j++;
	}
	tab[j] = 0;
	return (tab);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	int		wc;

	if (s == NULL)
		return (NULL);
	wc = ft_count_words(s, c);
	tab = malloc(sizeof(char*) * (wc + 1));
	if (tab == NULL)
		return (NULL);
	return (ft_splitstr(s, tab, c, wc));
}
