/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:51:52 by iugolin           #+#    #+#             */
/*   Updated: 2022/09/26 17:33:50 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ms_newline(char *arg)
{
	int	i;

	i = 0;
	if (arg && arg[i++] == '-')
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				break ;
			if (arg[i + 1] == '\0')
				return (true);
			i++;
		}
	}	
	return (false);
}

int	ms_echo(char **arg)
{
	int	n;
	int	i;

	n = false;
	i = -1;
	while (ms_newline(arg[++i]))
		n = true;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n == false)
		printf("\n");
	return (0);
}
