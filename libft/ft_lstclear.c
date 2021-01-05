/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:22:49 by josaykos          #+#    #+#             */
/*   Updated: 2021/01/05 16:10:41 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr_lst;
	t_list	*temp;

	ptr_lst = *lst;
	while (ptr_lst)
	{
		temp = ptr_lst->next;
		del(ptr_lst->content);
		free(ptr_lst);
		ptr_lst = temp;
	}
	*lst = NULL;
}
