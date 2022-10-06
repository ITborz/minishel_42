/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specify_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:23:48 by bkristen          #+#    #+#             */
/*   Updated: 2022/03/11 15:10:51 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	choose_action_builtin(char *str)
{
	if ((ft_strcmp("cd", str) == 0)
		|| (ft_strcmp("exit", str) == 0)
		|| (ft_strcmp("echo", str) == 0)
		|| (ft_strcmp("env", str) == 0)
		|| (ft_strcmp("pwd", str) == 0)
		|| (ft_strcmp("export", str) == 0)
		|| ft_strcmp("unset", str) == 0)
		return (1);
	return (0);
}

static void	choose_action_for_1(char *content, int *type)
{
	if (!(ft_strcmp(content, "<")))
		*type = FILE_IN;
	else if (!(ft_strcmp(content, ">")))
		*type = FILE_OUT;
	else if (!(ft_strcmp(content, "|")))
		*type = PIPE;
	else
		*type = ARG;
}

static void	choose_action_for_2(char *content, int *type)
{
	if (!(ft_strcmp(content, "<<")))
		*type = HERE_DOC;
	else if (!(ft_strcmp(content, ">>")))
		*type = FILE_OUT_SUR;
	else
		*type = ARG;
}

void	specify_token(t_lst **tokens)
{
	t_lst	*step;

	step = *tokens;
	while (step)
	{
		if (ft_strlen(step->content) == 1)
			choose_action_for_1(step->content, &step->type);
		else if (ft_strlen(step->content) == 2)
			choose_action_for_2(step->content, &step->type);
		else if (choose_action_builtin(step->content) == 1)
			step->type = BUILTIN;
		else if (ft_strlen(step->content) != 0 && step->type == NONE)
			step->type = ARG;
		step = step->next;
	}
}
