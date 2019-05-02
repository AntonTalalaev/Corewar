/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_1_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/05/01 03:34:38 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

static void	parse_instruction(char **line, int i, int fd_input,
								t_header **header)
{
	if (startswith(*line + i, NAME_CMD_STRING))
		parse_name(line, i, fd_input, header);
	else if (startswith(*line + i, COMMENT_CMD_STRING))
		parse_comment(line, i, fd_input, header);
}

void		check_prog_name_and_comment_existence(t_header *header, int i)
{
	if (!(header->prog_name))
		error_exit(e_no_name, g_params->num_line, i + 1);
	else if (!(header->comment))
		error_exit(e_no_comment, g_params->num_line, i + 1);
}

void		name_comment_parsing(char **line, int i, t_main_header *main_header,
								int fd_input)
{
	if (startswith(*line + i, NAME_CMD_STRING)
	|| startswith(*line + i, COMMENT_CMD_STRING))
		parse_instruction(line, i, fd_input, main_header->header);
	else if (!((*(main_header->header))->prog_name) ||
	!((*(main_header->header))->comment))
		check_prog_name_and_comment_existence(*(main_header->header), i);
	else
		parse_operation(line, i, fd_input, main_header->main);
}
