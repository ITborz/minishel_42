/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:13:11 by bkristen          #+#    #+#             */
/*   Updated: 2022/09/26 16:07:48 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	increment_shlvl(t_lst **lst_env)
{
	char	*shlvl_value;
	int		shlvl;
	char	*cshlvl;
	t_lst	*step;

	step = *lst_env;
	shlvl_value = getenv("SHLVL");
	if (ft_strcmp(shlvl_value, "") == 0)
		return (1);
	shlvl = ft_atoi(shlvl_value) + 1;
	while (step)
	{
		if (ft_strncmp("SHLVL", step->content, 5) == 0)
		{
			free(step->content);
			cshlvl = ft_itoa(shlvl);
			step->content = ft_strjoin("SHLVL=", cshlvl);
			free(cshlvl);
			if (step->content == NULL)
				return (-1);
			return (0);
		}
		step = step->next;
	}
	return (0);
}

int	env_init(t_lst **lst_env, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (new_node_back(ft_strdup(env[i]), lst_env))
			return (-1);
		i++;
	}
	if (increment_shlvl(lst_env))
		return (-1);
	return (0);
}
