/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:04:48 by iugolin           #+#    #+#             */
/*   Updated: 2022/09/26 16:06:59 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process(t_cmd *cmd, t_cmd *first, t_shell *shell)
{
	signal(SIGINT, nothing);
	cmd->pid = fork();
	if (cmd->pid == -1)
		printf("error");
	if (cmd->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (cmd->prev != NULL)
			dup2(cmd->prev->fd[0], STDIN_FILENO);
		if (cmd->next != NULL)
			dup2(cmd->fd[1], STDOUT_FILENO);
		check_red(cmd, 0);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		free_fd(first);
		if (cmd->av && is_builtins_exec(cmd->av, 1, first, shell) == 1)
			executer_2(cmd->av, first, shell);
	}
	if (cmd->prev != NULL)
		close(cmd->prev->fd[0]);
	close(cmd->fd[1]);
}

void	executer(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*first;
	int		status;

	status = 0;
	first = cmd;
	pipe_init(first);
	if (handle_heredocs(cmd, shell) == 1 || if_builtin(cmd, shell) == 1)
		return ;
	if (cmd && cmd->av)
	{
		while (cmd)
		{
			process(cmd, first, shell);
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			cmd = cmd->next;
		}
	}
	signal(SIGINT, ctrl_c);
}
