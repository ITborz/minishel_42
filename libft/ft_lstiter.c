/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:27:48 by modysseu          #+#    #+#             */
/*   Updated: 2022/09/26 17:25:20 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_lst *lst, void (*f)(void *))
{
	t_lst	*f_element;

	f_element = lst;
	if (f != NULL)
	{
		while (f_element != NULL)
		{
			f(f_element->content);
			f_element = f_element->next;
		}
	}
}
