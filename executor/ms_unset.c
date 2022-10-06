/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:25:18 by iugolin           #+#    #+#             */
/*   Updated: 2022/09/26 16:06:59 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	check_unset_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
	{
		printf("unset: '%s': not a valid identifier\n", arg);
		return (1);
	}
	i++;
	while (arg[i])
	{	
		if ((ft_isalnum(arg[i]) == 0 && arg[i] != '_') || arg[i] == '=')
		{
			printf("unset: '%s': not a valid identifier\n", arg);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**tableau_remove_line(char **tableau, char *line)
{
	int		i;
	int		j;
	char	**new_tableau;

	i = 0;
	j = 0;
	while (tableau[i])
		i++;
	new_tableau = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tableau[i])
	{
		if (ft_strcmp(tableau[i], line) == 0)
			i++;
		if (tableau[i])
		{
			new_tableau[j++] = ft_strdup(tableau[i]);
			i++;
		}
	}
	new_tableau[j] = NULL;
	free_tab(tableau);
	return (new_tableau);
}

char	**ms_unset_remove(char *arg, t_shell *shell)
{
	char	*line;

	line = NULL;
	line = ms_get_env(shell->env, arg);
	if (line != NULL)
		shell->env = tableau_remove_line(shell->env, line);
	return (shell->env);
}

int	ms_unset(char **arg, t_shell *shell)
{
	int		i;
	char	**strings;
	int		ret;

	ret = 0;
	i = 0;
	while (arg[i])
	{
		if (check_unset_arg(arg[i]) != 0)
		{
			i++;
			ret = 1;
			continue ;
		}
		strings = ft_split(arg[i], '=');
		shell->env = ms_unset_remove(strings[0], shell);
		shell->export = ms_unset_remove(strings[0], shell);
		free_tab(strings);
		i++;
	}
	return (ret);
}
