/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 12:41:47 by jonny             #+#    #+#             */
/*   Updated: 2020/01/06 14:20:54 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putchar(char c, int *ret)
{
	write(1, &c, 1);
	*ret += 1;
}

void	ft_putstr(char *str, int *ret)
{
	int i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++], ret);
}

/*
** if width > len, print (width - len) whitespace(s) then print the string
*/

void	str_whitespace(t_specs *specs, char *str, int len, int *ret)
{
	int i;

	i = 0;
	while (specs->width - len > 0)
	{
		ft_putchar(' ', ret);
		specs->width--;
	}
	while (i < len)
		ft_putchar(str[i++], ret);
}

/*
** Align to the left. Print the string then
** print whitespaces up to the total width if necessary
*/

void	str_padding(t_specs *specs, char *str, int len, int *ret)
{
	int i;

	i = 0;
	while (i < len)
		ft_putchar(str[i++], ret);
	while (specs->width - len > 0)
	{
		ft_putchar(' ', ret);
		specs->width--;
	}
}

/*
** if width > len, print (width - len) zero char(s) then print the string
*/

void	str_zero_padding(t_specs *specs, char *str, int len, int *ret)
{
	int i;

	i = 0;
	while (specs->width - len > 0)
	{
		ft_putchar('0', ret);
		specs->width--;
	}
	while (i < len)
		ft_putchar(str[i++], ret);
}
