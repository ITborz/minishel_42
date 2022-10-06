/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:24:26 by modysseu          #+#    #+#             */
/*   Updated: 2022/09/26 17:25:20 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_lst *lst)
{
	int		count;
	t_lst	*node;

	count = 0;
	if (lst != NULL)
	{
		node = lst;
		while (node != NULL)
		{
			node = node->next;
			count++;
		}
	}
	return (count);
}
