/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:24:54 by modysseu          #+#    #+#             */
/*   Updated: 2022/09/26 17:25:20 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstlast(t_lst *lst)
{
	t_lst	*f_element;

	if (lst == NULL)
		return (NULL);
	f_element = lst;
	while (f_element->next != NULL)
		f_element = f_element->next;
	return (f_element);
}
