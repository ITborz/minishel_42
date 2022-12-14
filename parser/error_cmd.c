/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:39:53 by bkristen          #+#    #+#             */
/*   Updated: 2022/09/26 16:07:48 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_error(char *cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ' && cmd[i] != '|')
			flag = 1;
		if (cmd[i] == '|' && flag == 0)
		{
			write(2, "minishell: syntax error near unexpected token `|\'\n", 51);
			return (1);
		}
		i++;
	}
	return (0);
}

int	quotes_error(char	*cmd, int i, int quotes)
{
	while (cmd[i])
	{
		if (cmd[i] == '\"')
		{
			if (quotes == 0)
				quotes = 2;
			else if (quotes == 2)
				quotes = 0;
		}
		if (cmd[i] == '\'')
		{
			if (quotes == 0)
				quotes = 1;
			else if (quotes == 1)
				quotes = 0;
		}
		i++;
	}
	if (quotes != 0)
		return (write(2, "minishell: miss quote\n", 23));
	return (quotes);
}
