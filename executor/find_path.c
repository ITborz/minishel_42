/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 19:04:46 by iugolin           #+#    #+#             */
/*   Updated: 2022/09/26 17:33:19 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_env_path(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i] && ft_strnstr(shell->env[i], "PATH", 4) == 0)
		i++;
	return (i);
}

char	*path_finder(char *cmd, t_cmd *cmdl, t_shell *shell)
{
	char	**paths;
	char	*path;
	int		i;

	path = NULL;
	i = search_env_path(shell);
	if (shell->env[i] == NULL)
		error(cmd, 1, cmdl, shell);
	paths = ft_split(shell->env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		if (path)
			free(path);
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free_s1(path, cmd);
		if (access(path, F_OK) == 0)
		{
			free_tab(paths);
			return (path);
		}
	}
	free(path);
	free_tab(paths);
	return (NULL);
}

void	free_tab(char **tabs)
{
	int	i;

	i = 0;
	while (tabs[i])
	{
		free(tabs[i]);
		i++;
	}
	free(tabs);
}

void	executer_2(char **av, t_cmd *cmd, t_shell *shell)
{
	char	*path;

	execve(av[0], av, shell->env);
	if (ft_strchr(av[0], '/') != NULL)
	{
		if (access(av[0], F_OK) == 0)
			error(av[0], 2, cmd, shell);
		error(av[0], 1, cmd, shell);
	}
	path = path_finder(av[0], cmd, shell);
	if (path && (execve(path, av, shell->env) == -1))
		error(av[0], 0, cmd, shell);
	error(av[0], 0, cmd, shell);
}

t_cmd	*head_lst(t_cmd *cmd)
{
	while (cmd)
	{
		if (!cmd->prev)
			return (cmd);
		cmd = cmd->prev;
	}
	return (cmd);
}
