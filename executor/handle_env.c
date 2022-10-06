/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:35:03 by iugolin           #+#    #+#             */
/*   Updated: 2022/09/26 16:06:59 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
		printf("%s\n", shell->env[i++]);
	return (0);
}

int	compare_env(char **env, char **arg, int i)
{
	char	**split;

	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], arg[0]) == 0)
		{
			free_tab(split);
			break ;
		}
		i++;
		free_tab(split);
	}
	return (i);
}
