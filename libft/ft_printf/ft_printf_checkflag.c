/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_checkflag.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 21:35:24 by jonny             #+#    #+#             */
/*   Updated: 2021/03/13 10:16:59 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** If the width is > to length of the number and no precision,
** check the flag to print whitespaces or zeros.
*/

static void	nbr_flag_zero(t_specs *specs, char *str, int len, int *ret)
{
	if (specs->width > len && specs->precision < 0)
	{
		if (specs->flag == '0')
			nbr_zero_padding(specs, str, len, ret);
		else
			nbr_whitespace(specs, str, len, ret);
		if (specs->flag != '0')
			ft_putstr(str, ret);
	}
	else if (specs->width >= specs->precision && specs->width >= 0)
	{
		nbr_whitespace(specs, str, len, ret);
		nbr_zero_padding(specs, str, len, ret);
	}
}

/*
** If flag is '0' with (width - precision) > (number length) and precision
** is specified: set flag to '+'.
** If precision > number length and no width specified OR
** precision is greater than width: print zeros before the number.
** Else if flag is not '-' and width is specified:
** print zeros or whitespaces before the number.
*/

void	check_nbr_flag(t_specs *specs, char *str, int *ret)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	if (specs->flag == '0' && specs->width - specs->precision > len
		&& specs->precision != -1)
		specs->flag = '+';
	if ((specs->precision > len && specs->width == -1)
		|| specs->precision > specs->width)
		nbr_zero_padding(specs, str, len, ret);
	else if ((specs->flag == '0' || specs->flag == '+') && specs->width >= 0)
		nbr_flag_zero(specs, str, len, ret);
	else if (specs->flag == '-')
	{
		nbr_zero_padding(specs, str, len, ret);
		nbr_whitespace(specs, str, len, ret);
	}
	else
		ft_putstr(str, ret);
	free(str);
	str = NULL;
}

/*
** If flag is '-' print "0x", then print the number with necessary
** whitespaces (up to the widt hvia str_padding function call).
** If flag is '0' also print "0x", then print zeros before the number
** (via str_zero_padding function call), print the number up to the width.
** Otherwise, no left padding and no zero padding is necessary: print
** necessary whitespaces, then "0x" followed by the number.
*/

void	check_p_flag(t_specs *specs, char *str, int len, int *ret)
{
	if (specs->flag == '-')
	{
		ft_putstr("0x", ret);
		str_padding(specs, str, len, ret);
	}
	else if (specs->flag == '0')
	{
		ft_putstr("0x", ret);
		str_zero_padding(specs, str, len, ret);
	}
	else
	{
		while (specs->width > len + 2)
		{
			ft_putchar_ret(' ', ret);
			specs->width--;
		}
		ft_putstr("0x", ret);
		ft_putstr(str, ret);
	}
	free(str);
	str = NULL;
}
