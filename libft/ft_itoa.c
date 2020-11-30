/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josaykos <josaykos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:29:20 by josaykos          #+#    #+#             */
/*   Updated: 2019/11/19 14:40:39 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_positive(char *tab, int nbr, int index)
{
	while (index >= 0)
	{
		tab[index] = nbr % 10 + 48;
		nbr = nbr / 10;
		index--;
	}
	return (tab);
}

static char		*ft_negative(char *tab, int nbr, int index)
{
	unsigned int nbr_min;

	tab[0] = '-';
	while (index > 0)
	{
		if (nbr == INT_MIN)
		{
			nbr_min = nbr;
			tab[index] = nbr_min % 10 + 48;
			nbr = nbr / 10;
			index--;
		}
		else
		{
			tab[index] = -nbr % 10 + 48;
			nbr = nbr / 10;
			index--;
		}
	}
	return (tab);
}

static int		ft_nbrlen(int nbr)
{
	int len;

	len = 1;
	if (nbr >= 0)
	{
		if (nbr <= 9)
			return (len);
		while (nbr > 9)
		{
			nbr = nbr / 10;
			len++;
		}
	}
	else
	{
		len = 2;
		if (nbr >= -9)
			return (len);
		while (nbr < -9)
		{
			nbr = nbr / 10;
			len++;
		}
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		i;

	str = NULL;
	i = ft_nbrlen(n);
	if (!(str = malloc(sizeof(char) * i + 1)))
		return (NULL);
	str[i] = '\0';
	i--;
	if (n >= 0)
		ft_positive(str, n, i);
	else
		ft_negative(str, n, i);
	return (str);
}
