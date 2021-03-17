/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:04:58 by jonny             #+#    #+#             */
/*   Updated: 2021/03/17 11:06:45 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

char	*ft_readlinev2(t_state *st, t_env *env_lst, char *prompt)
{
	char	*str;
	char	buf;

	str = NULL;
	(void)buf;
	print_prompt(prompt, GREEN);
	enable_raw_mode(st, env_lst);
	return (str);
}
