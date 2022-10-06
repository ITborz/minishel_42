/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:45:24 by bkristen          #+#    #+#             */
/*   Updated: 2022/09/26 16:07:48 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	env_init_for_exec(char **env, t_shell **shell)
{
	*shell = (t_shell *)malloc(sizeof(t_shell));
	ms_env_init(env, *shell);
	init_export(*shell);
}

int	loop(t_shell *shell, char *cmd, t_lst *lst_env, t_cmd *ex_cmd)
{
	while (1)
	{
		cmd = readline("minishell-1.0$ ");
		add_history(cmd);
		if (!cmd)
			ctrl_d(cmd, shell, lst_env);
		if (parsing_main(cmd, &lst_env, &ex_cmd))
			return (-1);
		executer(ex_cmd, shell);
	}
	free_job_lst(ex_cmd);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	t_lst	*lst_env;
	t_cmd	*ex_cmd;
	char	*cmd;

	(void)av;
	if (ac != 1)
		return (1);
	lst_env = NULL;
	shell = NULL;
	ex_cmd = NULL;
	g_exit_status = 0;
	cmd = NULL;
	env_init_for_exec(env, &shell);
	if (env_init(&lst_env, env))
	{
		ft_lstclear(&lst_env, free);
		return (1);
	}
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	if (loop(shell, cmd, lst_env, ex_cmd))
		return (-1);
	ft_lstclear(&lst_env, free);
	return (0);
}
