/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:50:37 by bkristen          #+#    #+#             */
/*   Updated: 2022/09/26 17:34:37 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	tokens_edit(t_lst **tokens, t_lst **lst_env)
{
	t_lst	*step;

	step = *tokens;
	while (step)
	{
		if (step->content != NULL)
		{
			if (tokens_mod(step, lst_env))
				return (-1);
		}
		step = step->next;
	}
	return (0);
}
