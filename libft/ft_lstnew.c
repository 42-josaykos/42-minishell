/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josaykos <josaykos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:46:14 by josaykos          #+#    #+#             */
/*   Updated: 2019/11/14 15:36:35 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list *list;
	t_list *n;

	list = NULL;
	if (!(n = malloc(sizeof(t_list))))
		return (NULL);
	if (n != NULL)
	{
		n->content = content;
		n->next = NULL;
	}
	list = n;
	return (list);
}
