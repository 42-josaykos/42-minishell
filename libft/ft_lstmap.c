/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:44:04 by josaykos          #+#    #+#             */
/*   Updated: 2021/01/05 16:06:09 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_list_init(t_list *lst, t_list *new_list, void *(*f)(void*))
{
	t_list	*new_node;

	new_node = new_list;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*new_list;

	new_list = NULL;
	new_list = ft_list_init(lst, new_list, f);
	if (!new_list)
	{
		ft_lstclear(&new_list, del);
		return (NULL);
	}
	return (new_list);
}
