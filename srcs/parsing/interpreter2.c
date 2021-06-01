/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:32:15 by jonny             #+#    #+#             */
/*   Updated: 2021/06/01 17:33:00 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	add_empty_node(t_ast **new_tkn)
{
	t_ast	*new_node;

	new_node = create_node(ft_strdup(""), ARG);
	ast_add(new_tkn, new_node);
}
