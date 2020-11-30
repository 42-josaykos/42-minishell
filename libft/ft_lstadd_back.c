/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josaykos <josaykos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:29:57 by josaykos          #+#    #+#             */
/*   Updated: 2020/02/06 11:59:54 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *newlist)
{
	t_list *temp;

	if (alst != NULL)
	{
		if (*alst == NULL)
			*alst = newlist;
		else
		{
			temp = *alst;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = newlist;
		}
	}
}
