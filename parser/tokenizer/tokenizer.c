/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:56:51 by bkristen          #+#    #+#             */
/*   Updated: 2022/09/23 13:33:09 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	if_the_arrow(char *str, int *j)
{
	char	sep;
	int		br;

	br = 0;
	sep = str[*j];
	while (str[*j] && str[*j] == sep)
	{
		(*j)++;
		br++;
		if (br == 2)
			break ;
	}
}

static void	if_not_the_arrow(char *str, int *j, int *quote)
{
	while (str[*j])
	{
		check_quotes(str[*j], quote);
		if ((ft_isspace(str[*j]) || str[*j] == '>' || str[*j] == '<')
			&& !(*quote))
			break ;
		(*j)++;
	}
}

static int	init_tokens(char *str, t_lst **tokens)
{
	int		i;
	int		j;
	int		quote;
	int		return_value;

	j = 0;
	quote = 0;
	return_value = 0;
	while (str[j])
	{
		while (ft_isspace(str[j]) && str[j])
			j++;
		i = j;
		if (str[j] && (str[j] == '>' || str[j] == '<'))
			if_the_arrow(str, &j);
		else
			if_not_the_arrow(str, &j, &quote);
		if (i != j)
			return_value = new_node_back(ft_substr(str, i, j - i), tokens);
	}
	specify_token(tokens);
	return (return_value);
}

int	tokenizer(t_lst **cmd_with_pipes_delimetr, t_lst **tokens)
{
	t_lst	*step;

	step = *cmd_with_pipes_delimetr;
	while (step)
	{
		if (init_tokens(step->content, tokens))
			return (-1);
		step = step->next;
	}
	if (token_type_error(tokens))
		return (1);
	redir_assignment(tokens);
	return (0);
}
