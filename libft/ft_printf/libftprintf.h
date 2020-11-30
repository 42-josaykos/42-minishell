/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 12:36:01 by jonny             #+#    #+#             */
/*   Updated: 2020/02/08 11:54:10 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct	s_specs
{
	char	type;
	char	flag;
	int		width;
	int		precision;
}				t_specs;

/*
** ft_printf.c
*/
int				ft_printf(const char *str, ...);
void			print_percent(t_specs *specs, int *ret);

/*
** ft_printf_checkflag)
*/
void			check_p_flag(t_specs *specs, char *str, int len, int *ret);
void			check_nbr_flag(t_specs *specs, char *str, int *ret);

/*
** ft_printf_convertbase
*/
char			*itoa_base(long int nb, int base, char *tab);
int				mini_atoi(const char *str, int *i);

/*
** ft_printf_getspecs.c
*/
void			get_type(va_list params, t_specs *specs, int *ret);
void			get_flag(const char *str, int *(i), t_specs *specs);
void			get_w(va_list params, const char *str, int *i, t_specs *specs);
void			get_p(va_list params, const char *str, int *i, t_specs *specs);

/*
** ft_printf_nbr
*/
void			nbr_whitespace(t_specs *specs, char *str, int len, int *ret);
void			nbr_padding(t_specs *specs, char *str, int len, int *ret);
void			nbr_zero_padding(t_specs *specs, char *str, int len, int *ret);

/*
** ft_printf_print.c
*/
void			print_char(va_list params, t_specs *specs, int *ret);
void			print_str(va_list params, t_specs *specs, int *ret);
void			print_pointer(va_list params, t_specs *specs, int *ret);
void			print_integer(va_list params, t_specs *specs, int *ret);
void			print_dectohexa(va_list params, t_specs *specs, int *ret);

/*
** ft_printf_str.c
*/
void			ft_putchar(char c, int *ret);
void			ft_putstr(char *str, int *ret);
void			str_whitespace(t_specs *specs, char *str, int len, int *ret);
void			str_padding(t_specs *specs, char *str, int len, int *ret);
void			str_zero_padding(t_specs *specs, char *str, int len, int *ret);

#endif
