/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_parts_utilities.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:19:40 by bkristen          #+#    #+#             */
/*   Updated: 2022/09/23 15:10:28 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**tableau_copy(char **args)
{
	char	**copy;
	int		i;

	i = 0;
	while (args[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (args[i])
	{
		copy[i] = ft_strdup(args[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	type_check(int type)
{
	if (type == BUILTIN || type == ARG)
		return (1);
	if (type == FILE_IN || type == HERE_DOC
		|| type == FILE_OUT || type == FILE_OUT_SUR
		|| type == OPEN_FILE || type == LIMITOR
		|| type == EXIT_FILE || type == EXIT_FILE_RET)
		return (2);
	if (type == PIPE)
		return (3);
	return (0);
}

t_cmd	*new_ex_cmd(char **av, char **file)
{
	t_cmd	*ex_cmd;

	ex_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!ex_cmd)
		return (NULL);
	ex_cmd->av = tableau_copy(av);
	ex_cmd->file = tableau_copy(file);
	ex_cmd->next = NULL;
	ex_cmd->prev = NULL;
	return (ex_cmd);
}

void	ex_cmd_push_back(t_cmd **ex_cmd, t_cmd *new)
{
	t_cmd	*step;

	if (*ex_cmd != NULL)
	{
		step = *ex_cmd;
		while (step->next != NULL)
			step = step->next;
		new->prev = step;
		step->next = new;
	}
	else
		*ex_cmd = new;
}

void	copy_end(char **av, char **file, t_cmd **ex_cmd)
{
	copy_av(av, NULL, 3);
	copy_file(file, NULL, 3);
	ex_cmd_push_back(ex_cmd, new_ex_cmd(av, file));
	tableau_free(av);
	tableau_free(file);
}
