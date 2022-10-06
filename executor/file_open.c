/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 19:02:34 by iugolin           #+#    #+#             */
/*   Updated: 2022/09/26 16:21:42 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(char *av, int i, int quit)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(av, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(av, O_RDONLY, 0777);
	if (file == -1)
	{
		if (access(av, F_OK) == 0)
			printf("minishell: %s Is a directory\n", av);
		else
			printf("minishell: no such file or directory: %s\n", av);
		if (quit == 0)
			exit(1);
	}
	return (file);
}

void	free_fd(t_cmd *first)
{
	while (first)
	{
		close(first->fd[0]);
		close(first->fd[1]);
		first = first->next;
	}
}

void	free_job_lst(t_cmd *job)
{
	t_cmd	*temp;

	temp = NULL;
	while (job)
	{
		temp = job->next;
		if (job->av)
			free_tab(job->av);
		if (job->file)
			free_tab(job->file);
		free(job);
		job = temp;
	}
	job = NULL;
}

void	error(char *arg, int i, t_cmd *cmd, t_shell *shell)
{
	if (i == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (i == 1)
		printf("minishell: %s: No such file or directory\n", arg);
	else if (i == 2)
	{
		printf("minishell: %s: is a directory\n", arg);
		free_exit(cmd, shell);
		exit(126);
	}
	free_exit(cmd, shell);
	exit (127);
}
