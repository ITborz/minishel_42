/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:33:04 by iugolin           #+#    #+#             */
/*   Updated: 2022/09/26 16:06:59 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_string(char *arg)
{
	char	**strings;
	char	*string;
	int		i;

	i = 1;
	strings = ft_split(arg, '=');
	string = ft_strjoin(strings[0], "=");
	while (strings[i] && strings[i + 1])
	{
		string = ft_strjoin_free_s1(string, strings[i++]);
		string = ft_strjoin_free_s1(string, "=");
	}
	if (strings[i])
		string = ft_strjoin_free_s1(string, strings[i]);
	string = ft_strjoin_free_s1(string, "");
	free_tab(strings);
	return (string);
}

void	init_export(t_shell *shell)
{
	int		i;
	char	*string;

	i = 0;
	while (shell->env[i])
		i++;
	shell->export = malloc(sizeof(char *) * (i));
	i = 0;
	if (shell->env[i])
	{
		while (shell->env[i + 1])
		{
			string = make_string(shell->env[i]);
			shell->export[i] = ft_strdup(string);
			free(string);
			i++;
		}
	}
	shell->export[i] = NULL;
}
