/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:34:01 by iugolin           #+#    #+#             */
/*   Updated: 2022/09/26 16:06:59 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**tableau_add_line(char **tableau, char *new_line)
{
	int		i;
	char	**new_tableau;

	i = 0;
	while (tableau[i])
		i++;
	new_tableau = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tableau[i])
	{
		new_tableau[i] = ft_strdup(tableau[i]);
		i++;
	}
	new_tableau[i] = ft_strdup(new_line);
	i++;
	new_tableau[i] = NULL;
	free_tab(tableau);
	return (new_tableau);
}

void	ms_set_env(char **env, char *value, t_shell *shell)
{
	int		i;
	char	**arg;

	i = 0;
	arg = ft_split(value, '=');
	i = compare_env(env, arg, i);
	if (env[i] == NULL)
	{
		shell->env = tableau_add_line(env, value);
		free_tab(arg);
		return ;
	}
	free(env[i]);
	value = ft_strdup(value);
	env[i] = value;
	free_tab(arg);
}

char	*ms_get_env(char **env, char *arg)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], arg) == 0)
		{
			free_tab(split);
			break ;
		}
		else
			i++;
		free_tab(split);
	}
	if (env[i] == NULL)
		return (NULL);
	return (env[i]);
}

void	check_shlvl(t_shell *shell)
{
	char	*var;
	char	*var1;
	int		num;
	char	**arg;

	var = ms_get_env(shell->env, "SHLVL");
	if (var == NULL)
	{
		shell->env = tableau_add_line(shell->env, "SHLVL=1");
		return ;
	}
	arg = ft_split(var, '=');
	num = ft_atoi(arg[1]);
	num++;
	var = ft_itoa(num);
	var1 = ft_strjoin("SHLVL=", var);
	ms_set_env(shell->env, var1, shell);
	free (var);
	free (var1);
	free_tab(arg);
	return ;
}

void	ms_env_init(char **env, t_shell *shell)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	shell->env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		shell->env[i] = ft_strdup(env[i]);
	shell->env[i] = NULL;
	check_shlvl(shell);
	return ;
}
