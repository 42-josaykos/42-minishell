/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascal <alpascal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 17:04:28 by alpascal          #+#    #+#             */
/*   Updated: 2021/05/26 17:05:05 by alpascal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

int	quotes_skip(enum e_type *types, int i)
{
	int	j;

	j = i + 1;
	while (types[j] != VOID && types[j] != types[i])
		j++;
	return (j - i);
}
