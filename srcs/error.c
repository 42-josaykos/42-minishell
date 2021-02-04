/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:24:33 by jonny             #+#    #+#             */
/*   Updated: 2021/01/22 13:24:37 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh.h"

void	error_cases(int errnum, char *cmd, char *arg)
{
	ft_printf("bash: %s: %s: %s\n", cmd, arg, strerror(errnum));
}

void	error_quotes()
{
	ft_printf("bash: error: invalid arguments: opened quotes are not closed\n");
}