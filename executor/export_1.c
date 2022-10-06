/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:42:05 by iugolin           #+#    #+#             */
/*   Updated: 2022/09/26 16:06:59 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
	{
		printf("export: '%s': not a valid identifier\n", arg);
		return (1);
	}
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			printf("export: '%s': not a valid identifier\n", arg);
			return (1);
		}
		i++;
	}
	return (0);
}

void	export_sort(t_shell *shell)
{
	int	i;

	i = 0;
	ft_sort_tab(shell->export);
	while (shell->export[i])
		printf("%s\n", shell->export[i++]);
}

void	export_valid(char *arg, char *strings, t_shell *shell)
{
	char	*string;

	if (ft_strchr(arg, '=') == NULL)
	{
		if (ms_get_env(shell->export, strings) == NULL)
			shell->export = tableau_add_line(shell->export, arg);
	}
	else
	{
		string = make_string(arg);
		if (ms_get_env(shell->export, strings) != NULL)
		{
			arg = ft_strdup(arg);
			ms_set_env(shell->env, arg, shell);
			ms_set_env(shell->export, string, shell);
			free(arg);
		}
		else
		{	
			shell->env = tableau_add_line(shell->env, arg);
			shell->export = tableau_add_line(shell->export, string);
		}
		free(string);
	}
}

int	ms_export(char **arg, t_shell *shell)
{
	char	**strings;
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (arg[i])
	{
		if (check_export(arg[i]) != 0)
		{
			i++;
			continue ;
			ret = 1;
		}
		strings = ft_split(arg[i], '=');
		export_valid(arg[i], strings[0], shell);
		free_tab(strings);
		i++;
	}
	if (arg[0] == NULL)
		export_sort(shell);
	return (ret);
}
