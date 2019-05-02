/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_part_2_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:26 by bsprigga          #+#    #+#             */
/*   Updated: 2019/05/02 11:50:14 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void	switch_to_next_line(char *line, int *name_or_comment_index)
{
	g_params->num_line++;
	*name_or_comment_index = 0;
	free(line);
}

void	check_slash_zero(int fd_input, int index)
{
	char	*line_fd;

	if (lseek(fd_input, -1, SEEK_CUR) == -1L)
		error_exit(e_lseek_error, g_params->num_line, index);
	if (!(line_fd = (char *)malloc(sizeof(char) * 1)))
		error_exit(e_malloc_error, g_params->num_line, index);
	read(fd_input, line_fd, 1);
	if (line_fd[0] != '\n')
		error_exit(e_instruction_not_slash_n, g_params->num_line, index);
	free(line_fd);
}

int		check_slash_zero_exit(int fd_input, int index, t_main *main)
{
	int		ret_value;
	char	*line_fd;

	if (lseek(fd_input, -1, SEEK_CUR) == -1L)
		error_exit(e_lseek_error, g_params->num_line, index);
	if (!(line_fd = (char *)malloc(sizeof(char) * 1)))
		error_exit(e_malloc_error, g_params->num_line, index);
	read(fd_input, line_fd, 1);
	ret_value = 0;
	if (line_fd[0] != '\n')
	{
		if (main->num_of_op == -1)
			error_exit(e_no_exec_code, g_params->num_line, 1);
		ret_value = 1;
	}
	free(line_fd);
	return (ret_value);
}
