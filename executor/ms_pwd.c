/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:35:16 by iugolin           #+#    #+#             */
/*   Updated: 2022/09/26 17:34:03 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_pwd(void)
{
	char	c[PATH_MAX];

	if (getcwd(c, sizeof(c)) == NULL)
		return (1);
	printf("%s\n", c);
	return (0);
}
