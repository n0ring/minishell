/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 19:10:54 by namina             #+#    #+#            */
/*   Updated: 2021/09/10 19:10:54 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_input_mode(char **input_str, t_mshell *shell,
					t_list_params *el, t_list_io_params *io_el)
{
	(void) el;
	while (ft_isspace(**input_str))
		(*input_str)++;
	if (!ft_strncmp(*input_str, "<<", 2))
	{
		io_el->mode = HERE_DOC;
		(*input_str) += 2;
	}
	else
	{
		io_el->mode = REDRCT_INPUT;
		(*input_str)++;
	}
	if (get_io_name(&(io_el->file_name), input_str) == -1)
		return (-1);
	if (!io_el->file_name || !*(io_el->file_name))
		return (handle_token_error(input_str, **input_str));
	process_io_tokens(&(io_el->file_name), shell, io_el->mode);
	while (ft_isspace(**input_str))
		(*input_str)++;
	return (0);
}

int	set_output_mode(char **input_str, t_mshell *shell,
					t_list_params *el, t_list_io_params *io_el)
{
	while (ft_isspace(**input_str))
		(*input_str)++;
	if (**input_str == '|')
		return (check_for_pipe_error(input_str, el, io_el));
	if (!ft_strncmp(*input_str, ">>", 2))
		io_el->mode = REDRCT_APPEND;
	else
		io_el->mode = REDRCT_OUTPUT;
	if (io_el->mode == REDRCT_APPEND)
		(*input_str) += 2;
	else
		(*input_str)++;
	if (get_io_name(&(io_el->file_name), input_str) == -1)
		return (-1);
	if (!io_el->file_name || !*(io_el->file_name))
		return (handle_token_error(input_str, **input_str));
	process_io_tokens(&(io_el->file_name), shell, io_el->mode);
	while (ft_isspace(**input_str))
		(*input_str)++;
	return (0);
}

int	token_process(char **input_str, t_mshell *shell, int (*set_io) (char **,
		t_mshell*, t_list_params*, t_list_io_params*), t_list_params *el)
{
	t_list_io_params	*io_el;
	int					set_mode_status;

	el->str_to_cmd[el->cmd_str_i] = ' ';
	el->cmd_str_i++;
	io_el = malloc(sizeof(t_list_io_params));
	io_el->file_name = NULL;
	io_el->fd = -1;
	set_mode_status = set_io(input_str, shell, el, io_el);
	if (set_io == set_output_mode)
		ft_lstadd_back(&(el->output), ft_lstnew(io_el));
	else
		ft_lstadd_back(&(el->input), ft_lstnew(io_el));
	return (set_mode_status);
}

int	set_params_to_el(char **input_str, t_list_params *el, t_mshell *shell)
{
	int		set_mode_res;

	el->cmd_str_i = 0;
	set_mode_res = 0;
	while (**input_str)
	{
		if (**input_str == '\"' || **input_str == '\'')
			handle_quotes(input_str, el);
		while (!set_mode_res && **input_str && **input_str == '<')
			set_mode_res = token_process(input_str, shell, set_input_mode, el);
		while (!set_mode_res && **input_str
			&& (**input_str == '|' || **input_str == '>'))
			set_mode_res = token_process(input_str, shell, set_output_mode, el);
		if (set_mode_res == -1 || set_mode_res == PIPE)
			break ;
		el->str_to_cmd[el->cmd_str_i++] = **input_str;
		if (**input_str && **input_str != '|')
			(*input_str)++;
	}
	el->str_to_cmd[el->cmd_str_i] = '\0';
	if (!check_for_cmd(el->str_to_cmd))
		el->cmd_arr = parse_args(el->str_to_cmd, shell);
	return (set_mode_res);
}

int	parser(char *input_str, t_list **list, t_mshell *shell)
{
	t_list_params	*el;

	while (*input_str)
	{
		el = malloc(sizeof(t_list_params));
		init_el(el);
		el->str_to_cmd = malloc(ft_strlen(input_str) * 2 + 1);
		if (!el->str_to_cmd)
			return (-1);
		if (set_params_to_el(&input_str, el, shell) == -1)
		{
			ft_lstadd_back(list, ft_lstnew(el));
			return (-1);
		}
		ft_lstadd_back(list, ft_lstnew(el));
	}
	return (0);
}
