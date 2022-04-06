/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_handlers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 18:59:40 by namina             #+#    #+#            */
/*   Updated: 2021/10/23 18:59:40 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_token_error(char **input_str, char token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token \'", 2);
	if (!token)
	{
		ft_putstr_fd("newline", 2);
		ft_putstr_fd("\'\n", 2);
		return (-1);
	}
	while (**input_str && **input_str == token)
	{
		ft_putchar_fd(token, 2);
		(*input_str)++;
	}
	ft_putstr_fd("\'\n", 2);
	return (-1);
}

int	check_for_pipe_error(char **input_str, t_list_params *el,
							t_list_io_params *io_el)
{
	char	*input_str_ptr;
	int		len;

	io_el->mode = PIPE;
	len = el->cmd_str_i - 1;
	while (len >= 0 && ft_isspace(el->str_to_cmd[len]))
		len--;
	if (len < 0 && !el->input && !el->output)
		return (handle_token_error(input_str, '|'));
	(*input_str)++;
	input_str_ptr = *input_str;
	while (ft_isspace(*input_str_ptr) && *input_str_ptr)
		input_str_ptr++;
	if (*input_str_ptr == '\0')
	{
		ft_putstr_fd("minishell: syntax error: multiline pipe\n", 2);
		return (-1);
	}
	else if (*input_str_ptr == '|')
		return (handle_token_error(&input_str_ptr, '|'));
	return (PIPE);
}
