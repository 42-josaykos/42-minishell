/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josaykos <josaykos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:09:34 by josaykos          #+#    #+#             */
/*   Updated: 2019/11/20 11:32:55 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	int		len;

	if (s1 && s2)
	{
		tab = NULL;
		len = ft_strlen(s1) + ft_strlen(s2) + 1;
		if (!(tab = malloc(sizeof(char) * len)))
			return (0);
		tab[0] = '\0';
		tab = ft_strcat(tab, s1);
		tab = ft_strcat(tab, s2);
		return (tab);
	}
	return (NULL);
}
