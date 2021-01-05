/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:46:14 by josaykos          #+#    #+#             */
/*   Updated: 2021/01/05 16:13:29 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;
	t_list	*n;

	list = NULL;
	n = malloc(sizeof(t_list));
	if (!n)
		return (NULL);
	if (n != NULL)
	{
		n->content = content;
		n->next = NULL;
	}
	list = n;
	return (list);
}
