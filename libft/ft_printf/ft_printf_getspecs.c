/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_getspecs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:08:22 by jonny             #+#    #+#             */
/*   Updated: 2020/01/06 15:56:22 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** Check the type and call the specified printing function
*/

void	get_type(va_list params, t_specs *specs, int *ret)
{
	if (specs->type == 'c')
		print_char(params, specs, ret);
	else if (specs->type == 's')
		print_str(params, specs, ret);
	else if (specs->type == 'd' || specs->type == 'i' || specs->type == 'u')
		print_integer(params, specs, ret);
	else if (specs->type == 'p')
		print_pointer(params, specs, ret);
	else if (specs->type == 'x' || specs->type == 'X')
		print_dectohexa(params, specs, ret);
	else if (specs->type == '%')
		print_percent(specs, ret);
}

/*
** Set the flag to '0' or '.' if found.
*/

void	get_flag(const char *str, int *i, t_specs *specs)
{
	while (str[*i] == '0' || str[*i] == '-')
	{
		specs->flag = str[*i];
		(*i)++;
	}
}

/*
** If '*' is specified, set the width with the next va_arg of type int.
** Then if the va_arg is negative, it means the string will be left padding so
** set the flag to '-', and the width is equals to its absolute value.
** Otherwise, the width is equal to the number before the type specifier char.
*/

void	get_w(va_list params, const char *str, int *i, t_specs *specs)
{
	if ((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '*')
	{
		if (str[*i] == '*')
		{
			specs->width = va_arg(params, int);
			if (specs->width < 0)
			{
				specs->flag = '-';
				specs->width *= -1;
			}
			(*i)++;
		}
		else
			specs->width = mini_atoi(str, i);
	}
}

/*
** Set the precision after the '.' char. If '*', get the next va_arg of
** type int.
** Otherwise convert the string number to an int and set the precision.
*/

void	get_p(va_list params, const char *str, int *i, t_specs *specs)
{
	++(*i);
	if ((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '*')
	{
		if (str[*i] == '*')
		{
			specs->precision = va_arg(params, int);
			if (specs->precision < 0)
				specs->precision = -1;
			(*i)++;
		}
		else
			specs->precision = mini_atoi(str, i);
	}
	else
		specs->precision = 0;
}
