/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 12:13:40 by jonny             #+#    #+#             */
/*   Updated: 2021/03/13 10:16:40 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	is_type(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

/*
** Print percentage sign. Check flag and width for padding before
** or after the sign
*/

void	print_percent(t_specs *specs, int *ret)
{
	char	padding;

	if (specs->flag == '0')
		padding = '0';
	else
		padding = ' ';
	if (specs->flag == '-')
		ft_putchar_ret('%', ret);
	while (specs->width-- > 1)
		ft_putchar_ret(padding, ret);
	if (specs->flag != '-')
		ft_putchar_ret('%', ret);
}

/*
** initialize the specifications format in the structure, then check each char
** in the string and set the specs, in this RESPECSTIVE ORDER:
** - '0' and '-' specificy the padding with zeros or whitespaces in the format
** - a number <0-9> or '*' sppecify the width of the format
** - '.' specifies the precision (call to get_w will check the next char,
** check number or '*' and set the precision)
** - the type in the charset 'csdiupxX%'
*/

static void	check_specs(va_list params, const char *str, int *i, t_specs *specs)
{
	specs->type = -1;
	specs->flag = '+';
	specs->width = -1;
	specs->precision = -1;
	if (str[*i] == '0' || str[*i] == '-')
		get_flag(str, i, specs);
	if ((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '*')
		get_w(params, str, i, specs);
	if (str[*i] == '.')
		get_p(params, str, i, specs);
	if (is_type(str[*i]) == 1)
	{
		specs->type = str[*i];
		(*i)++;
	}
}

/*
** parse the formatted string. if not a '%', print the char, else
** check the specs. Do it until end of string or no '%' or no format type
** specifier is found
*/

static int	parse_str(va_list params, const char *str, t_specs *specs, int *ret)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '%' && str[i] != '\0')
			ft_putchar_ret(str[i++], ret);
		if (str[i] == '%')
		{
			i++;
			check_specs(params, str, &i, specs);
			if (is_type(specs->type) == 1)
				get_type(params, specs, ret);
			else
				break ;
		}
	}
	return (*ret);
}

/*
** create a structure t_specs to store the infos about the specifications of the
** formatted string
*/

int	ft_printf(const char *str, ...)
{
	int		ret;
	va_list	params;
	t_specs	*specs;

	ret = 0;
	va_start(params, str);
	specs = malloc(sizeof(t_specs));
	if (!specs)
		return (-1);
	parse_str(params, str, specs, &ret);
	va_end(params);
	free(specs);
	return (ret);
}
