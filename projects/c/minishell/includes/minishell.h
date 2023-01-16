/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:48:48 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 17:39:36 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>

# define OPEN 1
# define YES 1
# define NO 0
# define CLOSED 0
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'
# define NO_EXIT -2
# define NO_OPERATOR_FOUND -1
# define UNCLOSED_QUOTE -1
# define FULL_LENGTH -1
# define IS_BUILTIN 1
# define IS_NOT_BUILTIN 0
# define ERROR -1
# define NO_ERROR_FOUND 0
# define OK 0
# define CMD_NOT_FOUND 127
# define TOO_MANY_ARGUMENTS -3
# define NO_SUCH -4
# define UNSET -5
# define STOP 1
# define KILL_FORK 1
# define CONTINUE 0
# define EXISTS != NULL

typedef struct s_global
{
	char	*line;
	char	**sequence_tab;
	char	**operator_tab;
	char	**env;
	char	***cmd_matrix;
	int		shell_level;
	int		last_exit;
	pid_t	pid;
}	t_global;

extern t_global	*g_g;

// UTILS
int			ft_atoi(const char *str);
char		**ft_split(char const *str, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strjoin_and_free(char *s1, char *s2);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strcmp(char *s1, char *s2);
char		*extract_string(char *str, int len);
int			matrixlen(char ***matrix);
int			tablen(char **tab);
int			is_whitespace(char c);
int			is_it_whitespace(char *str);
int			is_alphabet(char c);
int			only_whitespaces(char *str);
int			only_pipes(char **op);
void		error_management(char *cmd, int exitcode);
void		error_management_cd(char *cmd, int error_type);

// EXECUTION
int			execute_bin(t_global *g, char **cmd_tab);
int			execute_builtin(t_global *g, char **cmd_tab);
int			execute_single_command(t_global *g, char ***cmd, int *status);
void		execute_pipeline(t_global *g, char ***cmd, int *status);
void		execute_redirections(t_global *g, int *status);

//ENV
char		*custom_getenv(char *str, char **env);
void		add_or_replace_env_variable(t_global *g, char *key_and_value);
void		init_env(t_global *g, char *minishell_path, char **env);
char		check_minishell_lvl(t_global *g);
char		*ft_itoa(int n);

// SIGNALS
void		manage_main_signal(t_global *g);
void		manage_sub_signal(t_global *g);
void		heredoc_signal(int sig);
void		disable_main_signal_heredoc(int sig);

// PARSING
int			extract_tokens(t_global *g);
char		**split_at_operators(char *cmd_str);
char		**trim_whitespaces(char **tab);
int			check_for_unclosed_quotes(char **tab);
char		**extract_operators(char **tab);
char		***exctract_commands(char **tab);
char		***trim_quotes(t_global *g, char ***cmd_tab);
char		*wrap_each_word_with_double_quotes(char *ret_str, \
int i, int j, int k);
char		**expand_env_variables(t_global *g, char **tab);
int			contains_only_whitespaces(char *line);

// MEMORY MANAGEMENT
void		free_all(t_global *g);
void		free_env(t_global *g);
void		double_free(void **tab);
void		free_cmd_data(t_global *g);
t_global	*init_cmd_data(t_global *g);

// PIPEX
int			pipex(int ac, char **av, char **env);
void		call_child(char **av, int *fd, char **env);
void		call_parent(char **av, int *fd, char **env);
char		*find_absolute_path(t_global *g, char *cmd);

// BUILTINS
int			pwd(t_global *g, char **cmd_tab);
int			echo(t_global *g, char **cmd_tab);
int			cd(t_global *g, char **cmd_tab);
int			env(t_global *g, char **cmd_tab);
int			unset(t_global *g, char **cmd_tab);
int			export(t_global *g, char **cmd_tab);
int			catch_exit(t_global *g, char **cmd_tab, int *status);
int			is_builtin(char **cmd_tab);
void		increment_env_variable(t_global *g, char *key);

// REDIRECTIONS
int			is_redirection(char *op);
int			catch_unexpected_token(t_global *g, int *head);
int			redirect(t_global *g, int *i, int *fd, int *original_io);
int			heredoc(char **op, int *i, int *fd, int *original_io);
void		sub_heredoc(int *fd, char ***cmd, int *i);
int			readline_and_send_to_void(char ***cmd, int *i);
int			is_last_heredoc(char **op);
void		catch_empty_double_quotes(char ***cmd, int *i);
int			restore_io_continue(int *original_io, int *i);
int			restore_io_error(int *original_io);
void		restore_io(int *i, int *fd, int *fd_in, int *original_io);

#endif
