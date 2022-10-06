/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:45:56 by bkristen          #+#    #+#             */
/*   Updated: 2022/09/26 17:32:44 by bkristen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <limits.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define NONE 0				// defaut set
# define ARG 1				// word
# define FILE_IN 2			// word == '<'
# define HERE_DOC 3			// word == '<<'
# define FILE_OUT 4			// word == '>'
# define FILE_OUT_SUR 5		// word == '>>'
# define OPEN_FILE 6		// word following '<'
# define LIMITOR 7			// word following '<<'
# define EXIT_FILE 8		// word following '>'
# define EXIT_FILE_RET 9	// word following '>>'
# define PIPE 10			// word == '|'
# define BUILTIN 11			// word == command

extern int	g_exit_status;

typedef struct s_cmd
{
	pid_t			pid;
	char			**av;
	char			**file;
	int				fd[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

typedef struct s_shell
{
	char	**env;
	char	**export;
}				t_shell;

int		main(int ac, char **av, char **env);
int		parsing_main(char *cmd, t_lst **lst_env, t_cmd **ex_cmd);
int		pipe_error(char *cmd);
int		quotes_error(char	*cmd, int i, int quotes);
void	check_quotes(char ch, int *quote);
int		new_node_back(char *cmd, t_lst **cmd_lst);
int		tokenizer(t_lst **cmd_with_pipes_delimetr, t_lst **tokens);
void	specify_token(t_lst **tokens);
int		token_type_error(t_lst **tokens);
void	redir_assignment(t_lst **tokens);
int		tokens_edit(t_lst **tokens, t_lst **lst_env);
int		tokens_mod(t_lst *tokens, t_lst **lst_env);
char	*get_env(char *str, t_lst **lst_env);
void	get_len_var_env(char *str, int *j,
			int *question_mark, int *len_var);
char	*handle_env(char *str, int *j, t_lst **lst_env, int dollar);
int		env_init(t_lst **lst_env, char **env);
void	copy_av(char **av, char *tokens, int type);
void	copy_file(char **file, char *tokens, int type);
void	merge_parts(t_cmd **ex_cmd, t_lst *tokens,
			char **av, char **file);
int		type_check(int type);
t_cmd	*new_ex_cmd(char **av, char **file);
void	ex_cmd_push_back(t_cmd **ex_cmd, t_cmd *new);
void	copy_end(char **av, char **file, t_cmd **ex_cmd);

//executer_2
void	executer(t_cmd *cmd, t_shell *shell);
int		check_export(char *arg);
void	export_sort(t_shell *shell);
void	export_valid(char *arg, char *strings, t_shell *shell);
int		ms_export(char **arg, t_shell *shell);
int		search_env_path(t_shell *shell);
char	*path_finder(char *cmd, t_cmd *cmdl, t_shell *shell);
void	free_tab(char **tabs);
void	executer_2(char **av, t_cmd *cmd, t_shell *shell);
t_cmd	*head_lst(t_cmd *cmd);
int		if_builtin(t_cmd *cmd, t_shell *shell);
int		check_builtins(char **arg);
int		check_red(t_cmd *job, int quit);
int		is_builtins_exec(char **arg, int i, t_cmd *first, t_shell *shell);
void	restore_fd(int saved_stdin, int saved_stdout);
void	pipe_init(t_cmd *cmd);
int		handle_heredocs(t_cmd *cmd, t_shell *shell);
int		check_heredoc(char **redir, int stdin_fd, t_cmd *cmd, t_shell *shell);
int		red_heredoc(char *limiter, int fd, t_cmd *cmd, t_shell *shell);
void	heredoc(char *limiter, int *fd, t_cmd *cmd, t_shell *shell);
char	*make_string(char *arg);
void	init_export(t_shell *shell);
int		ms_cd(char *arg, t_shell *shell);
int		ms_echo(char **arg);
int		compare_env(char **env, char **arg, int i);
int		ms_env(t_shell *shell);
int		check_exit_arg(char *arg);
void	ms_exit(char **arg, t_cmd *job, t_shell *shell);
void	free_exit(t_cmd *job, t_shell *shell);
char	**tableau_add_line(char **tableau, char *new_line);
void	ms_set_env(char **env, char *value, t_shell *shell);
char	*ms_get_env(char **env, char *arg);
void	check_shlvl(t_shell *shell);
void	ms_env_init(char **env, t_shell *shell);
int		ms_pwd(void);
int		ft_isalpha(int c);
int		check_unset_arg(char *arg);
char	**tableau_remove_line(char **tableau, char *line);
char	**ms_unset_remove(char *arg, t_shell *shell);
int		ms_unset(char **arg, t_shell *shell);
int		open_file(char *av, int i, int quit);
void	free_fd(t_cmd *first);
void	free_job_lst(t_cmd *job);
void	error(char *arg, int i, t_cmd *cmd, t_shell *shell);
void	stop_heredoc(int signal);
void	nothing(int signal);
void	ft_newline(int signal);
void	ctrl_c(int signal);
void	ctrl_d(char *line, t_shell *shell, t_lst *lst);
void	ft_sort_tab(char **arr);

#endif