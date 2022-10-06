/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:47:07 by bkristen          #+#    #+#             */
/*   Updated: 2022/09/26 17:35:00 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env(char *str, t_lst **lst_env)
{
	t_lst	*tmp;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp = *lst_env;
	while (tmp)
	{
		while (tmp->content[j] && tmp->content[j] != '=')
			j++;
		if (i == j && ft_strncmp(tmp->content, str, i) == 0)
			return (ft_strdup(tmp->content + (j + 1)));
		j = 0;
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

void	get_len_var_env(char *str, int *j,
				int *question_mark, int *len_var)
{
	int	i;

	*question_mark = 0;
	*len_var = 0;
	i = 0;
	if (str[*j] == '$')
	{
		while (str[*j] && str[*j] == '$')
			(*j)++;
		if (str[*j] == '?')
		{
			(*question_mark)++;
			return ;
		}
	}
	str += (*j);
	while (str[*len_var]
		&& ((ft_isalnum(str[*len_var]) == 1) || str[*len_var] == '_'))
		(*len_var)++;
}
