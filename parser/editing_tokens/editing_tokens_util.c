/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_edit_utilities.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:04:44 by bkristen          #+#    #+#             */
/*   Updated: 2022/09/23 15:05:30 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	merge_strings(int i, int j, char **new_str, char *content)
{
	if (i < j && content[i] != '\"')
		*new_str = ft_strjoin(*new_str, ft_substr(content, i, j - i));
	else
		*new_str = ft_strjoin(*new_str, ft_strdup(""));
	if (*new_str == NULL)
		return (-1);
	return (0);
}

static int	if_rabbit_ears(int *j, char **new_str,
			char *content, t_lst **lst_env)

{
	int	i;

	i = ++(*j);
	while (content[*j] && content[*j] != '\"')
	{
		if (content[*j] == '$')
		{
			if (i < *j)
				*new_str = ft_strjoin(*new_str,
						ft_substr(content, i, (*j - i)));
			*new_str = ft_strjoin(*new_str, handle_env(content + *j, j,
						lst_env, 0));
			if (*new_str == NULL)
				return (-1);
			i = *j;
		}
		if (content[*j] == '\"')
			break ;
		else if (content[*j] == '$')
			continue ;
		(*j)++;
	}
	if (merge_strings(i, *j, new_str, content))
		return (-1);
	return (0);
}

static int	if_one_comma(int *j, char **new_str, char *content)
{
	int	i;

	i = ++(*j);
	while (content[*j] && content[*j] != '\'')
		(*j)++;
	if (i < *j)
		*new_str = ft_strjoin(*new_str, ft_substr(content, i, (*j - i)));
	else
		*new_str = ft_strjoin(*new_str, ft_strdup(""));
	if (*new_str == NULL)
		return (-1);
	return (0);
}

static int	if_no_quotes(int *j, char **new_str,
			char *content, t_lst **lst_env)
{
	int	i;

	i = *j;
	while (content[*j] && content[*j] != '\'' && content[*j] != '\"')
	{
		if (content[*j] == '$')
		{
			if (i < *j)
				*new_str = ft_strjoin(*new_str, ft_substr(content, i, *j - i));
			*new_str = ft_strjoin(*new_str, handle_env(content + *j, j,
						lst_env, 0));
			if (*new_str == NULL)
				return (-1);
			i = *j;
		}
		if ((content[*j] == '\"' || content[*j] == '\''))
			break ;
		else if (content[*j] == '$')
			continue ;
		(*j)++;
	}
	if (merge_strings(i, *j, new_str, content))
		return (-1);
	return (0);
}

int	tokens_mod(t_lst *tokens, t_lst **lst_env)
{
	char	*new_str;
	int		j;

	new_str = ft_strdup("");
	if (new_str == NULL)
		return (-1);
	j = 0;
	while (tokens->content[j])
	{
		if (tokens->content[j] != '\'' && tokens->content[j] != '\"')
			if (if_no_quotes(&j, &new_str, tokens->content, lst_env))
				return (-1);
		if (tokens->content[j] == '\'')
			if (if_one_comma(&j, &new_str, tokens->content))
				return (-1);
		if (tokens->content[j] == '\"')
			if (if_rabbit_ears(&j, &new_str, tokens->content, lst_env))
				return (-1);
		j++;
	}
	free(tokens->content);
	tokens->content = new_str;
	return (0);
}
