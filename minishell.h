/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalannys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:46:41 by aalannys          #+#    #+#             */
/*   Updated: 2021/10/12 16:46:44 by aalannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include "libft/libft.h"
# include <readline.h>
# include <history.h>
# include <rltypedefs.h>
# include <fcntl.h>
# define ARG_OK 0
# define NOT_NUMERIC -1
# define PROMPT "Minishell$ "
# define PIPE 1
# define REDRCT_OUTPUT 2
# define REDRCT_APPEND 3
# define REDRCT_INPUT 4
# define HERE_DOC 5
# define PIPE_FD -3
# define SUCCESS 69

extern int	g_last_exit_code;

typedef struct s_envvar
{
	char	*key;
	char	*value;
	int		display_flag;
}	t_envvar;

typedef struct s_quotes
{
	int	singl;
	int	doubl;
}	t_quotes;

typedef struct s_list_io_params
{
	int		mode;
	char	*file_name;
	int		fd;
}			t_list_io_params;

typedef struct s_mshell
{
	t_list			*env_copy;
	t_list			*cmds;
}	t_mshell;

typedef struct s_list_params
{
	char	**cmd_arr;
	char	*str_to_cmd;
	char	*path_app;
	int		fd[2];
	int		cmd_str_i;
	t_list	*input;
	t_list	*output;
	int		pid;
	int		file_fd[2];
	int		pipe_fd[2];
	void	(*builtin)(t_mshell *, struct s_list_params *);
}			t_list_params;

typedef struct s_set_fd
{
	char	*str;
	int		fd;
	void	*next;
	int		read_res;
}			t_set_fd;

void		handle_sigs(int argc);
void		handle_for_child(char *path_app);
void		error_exit(char *prog);
void		free_node(void *node);
void		free_params_lst(void *param_node);
void		print_node(void *node);
void		print_export(void *node);
void		print_error(char *prog, char *arg);
int			invalid_key(char *key);
void		free_arr(char **arr);
char		*crop(char *path);
char		**split_args(char *prep);
void		move_spaces(char **str, char **start);
void		print_err_msg(char *prog, char *arg, char *msg);
size_t		chr_arr_len(char **arr);
long long	ft_atoi_ll(const char *nptr);
void		init_shell(t_mshell *shell, char **env);
void		exit_routine(t_mshell *shell);
/* env manipulations */
void		parse_env(t_mshell *shell, char **env);
t_list		*get_by_key(t_mshell *shell, char *key);
int			set_by_key(t_mshell *shell, char *key, char *val);
char		**lst_to_arr(t_mshell *shell);
void		add_var(t_mshell *shell, char *key, char *val, int display);
void		set_val(char **splt_arg, t_mshell *shell);
/* builtins */
void		assign_func(t_list_params *param);
void		my_env(t_mshell *shell, struct s_list_params *params);
void		my_pwd(t_mshell *shell, struct s_list_params *params);
void		my_cd(t_mshell *shell, struct s_list_params *params);
void		my_export(t_mshell *shell, struct s_list_params *params);
void		my_unset(t_mshell *shell, struct s_list_params *params);
void		my_exit(t_mshell *shell, struct s_list_params *params);
void		my_echo(t_mshell *shell, struct s_list_params *params);
/* parsing */
int			check_quotes(char *str);
char		*remove_quotes(char *pre_res);
char		*add_expanded(char **start, char **str, char *res, t_mshell *shell);
char		*preprocessor(char *str, t_mshell *shell);
char		**parse_args(char *args, t_mshell *shell);
void		init_el(t_list_params *el);
/* parsing to tokens*/
void		handle_quotes(char **s, t_list_params *el);
int			get_io_name(char **param_to_set, char **s);
int			handle_token_error(char **input_str, char token);
int			check_for_pipe_error(char **input_str, t_list_params *el,
				t_list_io_params *io_el);
void		process_io_tokens(char **param_to_set, t_mshell *shell, int mode);
int			check_for_cmd(char *cmd_str);
int			validation(t_list *param_list, char **envp);
int			parser(char *input_str, t_list **list, t_mshell *shell);
char		**get_path_arr(char **envp, char *app_name);
int			handle_no_cmd_io_error(t_list_params *el, int set_mode_res);
/* gnl */
char		*ft_strdup_gnl(char *src, int len, int offset);
char		*ft_strjoin_gnl(char *s1, char *s2, int len);
int			ft_strlen_gnl(const char *s);
t_set_fd	*get_current_el(t_set_fd **list, int fd);
void		lst_free(t_set_fd **list);
/* exec part*/
int			execution(char *cmd_str, t_mshell *shell);
void		get_input_from_std(char *limiter, int fd);
int			get_next_line(int fd, char **line);
int			app_to_null(t_list_params *params, int check_pipe);
void		set_child_fd(t_list *params);
int			builtin_exec(t_list *params, t_mshell *shell);
void		parent_process_handler(t_list *params);
int			check_exec_access(t_list_params *element);
int			fork_manager(t_list_params *element);
void		close_pipes_parent(void *params);
int			pipe_error_handler(void);
int			here_doc(t_list_io_params *io_el);

#endif
