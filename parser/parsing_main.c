/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:08:24 by bkristen          #+#    #+#             */
/*   Updated: 2022/09/26 16:07:48 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	separation_by_pipes(char *cmd, t_lst **cmd_lst)
{
	int		i;
	int		j;
	int		quote;
	int		return_value;

	i = 0;
	j = 0;
	quote = 0;
	return_value = 0;
	while (cmd[j])
	{
		check_quotes(cmd[j], &quote);
		if ((cmd[j] == '|' && !quote))
		{
			if (i != j)
				return_value = new_node_back(ft_substr(cmd, i, j - i), cmd_lst);
			return_value = new_node_back(ft_strdup("|"), cmd_lst);
			i = j + 1;
		}
		if (cmd[j + 1] == '\0' && cmd[j] != '|')
			return_value = new_node_back(ft_substr(cmd, i, j + 1 - i), cmd_lst);
		j++;
	}
	return (return_value);
}

int	parsing_main(char *cmd, t_lst **lst_env, t_cmd **ex_cmd)
{
	t_lst	*cmd_with_pipes_delimetr;
	t_lst	*tokens;
	int		ret_value;

	ret_value = 0;
	cmd_with_pipes_delimetr = NULL;
	tokens = NULL;
	if (*ex_cmd != NULL)
	{
		free_job_lst(*ex_cmd);
		*ex_cmd = NULL;
	}
	if (((quotes_error(cmd, 0, 0)) || (pipe_error(cmd))) && ret_value != -1)
		ret_value = 0;
	if (separation_by_pipes(cmd, &cmd_with_pipes_delimetr) && ret_value != -1)
		ret_value = -1;
	if (tokenizer(&cmd_with_pipes_delimetr, &tokens) && ret_value != -1)
		ret_value = -1;
	if (tokens_edit(&tokens, lst_env) && ret_value != -1)
		ret_value = -1;
	merge_parts(ex_cmd, tokens, NULL, NULL);
	ft_lstclear(&tokens, free);
	ft_lstclear(&cmd_with_pipes_delimetr, free);
	free(cmd);
	return (0);
}
