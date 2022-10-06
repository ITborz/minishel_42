/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:26:59 by modysseu          #+#    #+#             */
/*   Updated: 2022/09/26 17:25:20 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_lst **lst, void (*del)(void*))
{
	t_lst	*node;

	if (*lst != NULL && del != NULL)
	{
		node = *lst;
		while (node)
		{
			ft_lstdelone(node, del);
			node = node->next;
		}
		*lst = NULL;
	}
}
