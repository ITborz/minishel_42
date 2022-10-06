/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_parts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:18:24 by bkristen          #+#    #+#             */
/*   Updated: 2022/09/23 15:10:46 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_av(t_lst *tokens)
{
	t_lst	*step;
	int		count_av;

	count_av = 0;
	step = tokens;
	while (step && step->type != PIPE)
	{
		if (step->type == BUILTIN || step->type == ARG)
			count_av++;
		step = step->next;
	}
	return (count_av);
}

static int	count_file(t_lst *tokens)
{
	t_lst	*step;
	int		count_file;

	count_file = 0;
	step = tokens;
	while (step && step->type != PIPE)
	{
		if (step->type == FILE_IN || step->type == HERE_DOC
			|| step->type == FILE_OUT || step->type == FILE_OUT_SUR
			|| step->type == OPEN_FILE || step->type == LIMITOR
			|| step->type == EXIT_FILE || step->type == EXIT_FILE_RET)
			count_file++;
		step = step->next;
	}
	return (count_file);
}

void	copy_av(char **av, char *tokens, int type)
{
	static int	i = 0;

	if (type != 3)
	{
		av[i] = ft_strdup(tokens);
		i++;
	}
	else
	{
		av[i] = NULL;
		i = 0;
	}
}

void	copy_file(char **file, char *tokens, int type)
{
	static int	i = 0;

	if (type != 3)
	{
		file[i] = ft_strdup(tokens);
		i++;
	}
	else
	{
		file[i] = NULL;
		i = 0;
	}
}

void	merge_parts(t_cmd **ex_cmd, t_lst *tokens,
		char **av, char **file)
{
	t_lst	*step;

	step = tokens;
	av = (char **)malloc(sizeof(char *) * (count_av(step) + 1));
	file = (char **)malloc(sizeof(char *) * (count_file(step) + 1));
	while (step)
	{
		if (type_check(step->type) == 1)
			copy_av(av, step->content, 1);
		if (type_check(step->type) == 2)
			copy_file(file, step->content, 2);
		if (type_check(step->type) == 3)
		{
			copy_end(av, file, ex_cmd);
			step = step->next;
			av = (char **)malloc(sizeof(char *) * (count_av(step) + 1));
			file = (char **)malloc(sizeof(char *) * (count_file(step) + 1));
			continue ;
		}
			step = step->next;
	}
	copy_end(av, file, ex_cmd);
}
