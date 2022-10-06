/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_assignment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:20:47 by bkristen          #+#    #+#             */
/*   Updated: 2022/03/10 20:43:29 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	if_zero_flag(int type, int *flag)
{
	if (type == FILE_IN)
		*flag = OPEN_FILE;
	else if (type == HERE_DOC)
		*flag = LIMITOR;
	else if (type == FILE_OUT)
		*flag = EXIT_FILE;
	else if (type == FILE_OUT_SUR)
		*flag = EXIT_FILE_RET;
}

static void	if_not_zero_flag(int *type, int *flag)
{
	if (*flag == OPEN_FILE)
		*type = OPEN_FILE;
	else if (*flag == LIMITOR)
		*type = LIMITOR;
	else if (*flag == EXIT_FILE)
		*type = EXIT_FILE;
	else if (*flag == EXIT_FILE_RET)
		*type = EXIT_FILE_RET;
	*flag = 0;
}

void	redir_assignment(t_lst **tokens)
{
	int		flag;
	t_lst	*step;

	flag = 0;
	step = *tokens;
	while (step)
	{
		if (flag == 0)
			if_zero_flag(step->type, &flag);
		else if (flag != 0 && step->content)
			if_not_zero_flag(&step->type, &flag);
		step = step->next;
	}
}
