/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:48:45 by bkristen          #+#    #+#             */
/*   Updated: 2022/09/26 16:07:48 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_quotes(char ch, int *quote)
{
	if (ch == '\"')
	{
		if (*quote == 0)
			*quote = 2;
		else if (*quote == 2)
			*quote = 0;
	}
	else if (ch == '\'')
	{
		if (*quote == 0)
			*quote = 1;
		else if (*quote == 1)
			*quote = 0;
	}
}

int	new_node_back(char *cmd, t_lst **cmd_lst)
{
	t_lst	*new;

	new = create_node(cmd);
	if (new == NULL || new->content == NULL)
		return (-1);
	push_back(cmd_lst, new);
	return (0);
}
