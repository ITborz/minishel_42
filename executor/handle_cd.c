/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:19:28 by iugolin           #+#    #+#             */
/*   Updated: 2022/09/26 17:33:34 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_pwd(char *arg, char	*c, t_shell *shell)
{
	char	*string;

	string = ft_strjoin(arg, c);
	ms_set_env(shell->env, string, shell);
	free (string);
}

int	ms_cd(char *arg, t_shell *shell)
{
	char	c[PATH_MAX];

	if (arg == NULL)
	{
		arg = ms_get_env(shell->env, "HOME") + 5;
		if ((arg - 5) == NULL)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
	}
	getcwd(c, sizeof(c));
	if (chdir(arg) == -1)
	{
		if (arg[0] == '\0')
			return (1);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	set_pwd("OLDPWD=", c, shell);
	getcwd(c, sizeof(c));
	set_pwd("PWD=", c, shell);
	return (0);
}
